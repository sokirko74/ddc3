//-*- Mode: C++; c-basic-offset: 8; -*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2016 by Bryan Jurish
//
//  This file is part of DDC.
// 
//  DDC is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
// 
//  DDC is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
// 
//  You should have received a copy of the GNU Lesser General Public License
//  along with DDC.  If not, see <http://www.gnu.org/licenses/>.
//

#include "../CommonLib/utilit.h"
#include "../ConcordLib/ConcCommon.h"
#include "../ConcordDmnLib/Corpora.h"
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

#if HAVE_SYS_RESOURCE_H
#include <sys/resource.h>
#endif

#ifdef HAVE_SYSLOG_H
#include <syslog.h>
#endif

//-- suppress gcc warnings of the form "ignoring return value of `fread', declared with attribute warn_unused_result [-Wunused-result]"
#pragma GCC diagnostic ignored "-Wunused-result"

//----------------------------------------------------------------------
// Globals
string LockFileName; //-- lock file: stores pid of running server, indicates whether server *should* be running
string WaitFileName; //-- wait file: created by main process, removed by server when it is ready: absence indicates that the server is really running
string CorporaFile;
string ServerCorporaFile;
string Action;
bool   doFork;
bool   gotLogLevel=false;
bool   log_stderr=false;
bool   log_syslog=false;
bool   log_files=true;
char   log_label[64]; //-- ddc log-label

CDDCServerOptions ServerOptions;
bool LoadedServerOptions = false;

const char *prog = "ddc_daemon";

void PrintUsage()
{
	printf ("%s\n", DDCVersionStr.c_str() );
	printf ("Daemon for working with Dialing-DWDS Concordance\n");
	printf ("\nUsage: %s ACTION [OPTIONS]\n", prog);
	printf ("\nOptions:\n"
		"  -V, --version             # report program version and exit\n"
		"  -v, --verbose LEVEL       # set log-verbosity level (none|error|warn|info=weak|debug=medium|trace=heavy)\n"
		"  -l, --local LOCAL_CFG     # set local corpus config (default=$RML/etc/ddc_local_corpora.cfg)\n"
		"  -s, --server SERVER_CFG   # set server config (default=$RML/etc/ddc_server.cfg)\n"
		"  -O, --options SERVER_OPT  # load server options file (default=$RML/etc/ddc_server.opt)\n"
		"  -t, --threads N           # use N worker threads (default=0: serial mode)\n"
		"      --[no]fork            # do/don't detach from the running terminal (default=--fork)\n"
		"      --[no]stderr          # do/don't log to stderr (default=--nostderr)\n"
		"      --[no]syslog          # do/don't log to syslog (default=--nosyslog)\n"
		"      --[no]logfiles        # do/don't log to local files (default=--logfiles)\n"
		);
	printf ("\nActions:\n");
	printf ("  start                 # start daemon\n");
	printf ("  stop                  # stop running daemon\n");
	printf ("  restart               # re-start running daemon\n");
	printf ("  start_cli             # starts the program not as a daemon bat as a simple console program [BROKEN]\n");	
	printf ("\n");
	exit(1);
};


void RemoveFile(const string& filename)
{
	if (!filename.empty() && access(filename.c_str(), W_OK)==0)
		remove(filename.c_str());
}

void RemoveLockFiles()
{
	RemoveFile(LockFileName);
	RemoveFile(WaitFileName);
}

void RemoveLockFile() { RemoveFile(LockFileName); }
void RemoveWaitFile() { RemoveFile(WaitFileName); }


void CreateWaitFile()
{
	if (!WaitFileName.empty()) {
		FILE *fp = fopen(WaitFileName.c_str(), "w");
		if (fp==NULL)
			throw( CExpc("could not open wait file `%s': %s", WaitFileName.c_str(), StrError(errno)) );
		fclose(fp);
	}
}


void UnloadData()
{
	FreeConcordDicts();
	UnloadLocalCorporaAndServer();
	SocketDeinitialize();
	RemoveLockFile();
	closelog();
};

void ShutdownServerSockets() {
	ddcLogInfo("shutting down server socket(s)");
	ShutdownDDCServer();
	ShutdownLocalCorpora();
};


void  termination_handler(int signum)
{
	ShutdownServerSockets();
	UnloadData();
	ddcLogInfo("Exiting from concordance");
	exit(1);
};

int puke(const std::string& msg) {
	fputs(msg.c_str(), stdout);
	fputc('\n', stdout);
	ddcLogError(msg);
	UnloadData();
	RemoveLockFile();
	SocketDeinitialize();
	return -1;
}

//----------------------------------------------------------------------
// stop
int do_stop(void)
{
	int rc=0;
	FILE *fp=NULL;
	pid_t pid=0;

	fprintf(stderr, "Stopping ddc_daemon...\n");
	
	if (access(LockFileName.c_str(), R_OK) != 0) {
		fprintf(stderr, "cannot access lock file `%s' (ddc_daemon not started?)\n", LockFileName.c_str());
		rc=1;
		goto stop_clean;
	}

	fp = fopen(LockFileName.c_str(), "r");
	if (!fp) {
		fprintf(stderr, "open failed for lock file `%s': %s\n", LockFileName.c_str(), StrError(errno));
		rc=1;
		goto stop_clean;
	}
	fscanf(fp, "%i", &pid);

	if (kill (pid, SIGTERM)	== 0) {
		fprintf (stderr, "ddc_daemon (pid=%d) was stopped\n", pid);
	}
	else {
		fprintf(stderr, "cannot send a SIGTERM to daemon process (pid=%d): %s\n", pid, StrError(errno));
		rc=1;
	}

 stop_clean:
	if (fp) fclose(fp);
	RemoveLockFile();
	return rc;
}

//----------------------------------------------------------------------
// start
int do_start(bool clientMode=false)
{
      try {
      //-- clobber global log-level from server options (only if not read from command-line option)
      if (gotLogLevel)
	      ServerOptions.m_LogLevel = ddcLogLevel;
      if (ServerOptions.m_LogLevel > ddcLLUnknown)
	      SetLogLevel(ServerOptions.m_LogLevel);

      string startmsg = Format("Starting ddc_daemon v" PACKAGE_VERSION " in %s %s mode with log-level `%s'",
				 (doFork ? "forked" : "unforked"),
				 (clientMode ? "client" : "server"),
				 LogLevelName(ddcLogLevel));

	//-- setup logging options
	ddcLogToFiles=log_files;
	ddcLogToStderr=log_stderr;
	if (log_syslog) {
#ifdef HAVE_SYSLOG_H
		ddcLogToSyslog=true;
		openlog("ddc_daemon", LOG_PID|LOG_CONS, LOG_DAEMON);
#else
		fprintf(stderr, "%s: syslog logging disabled because ddc_daemon wasn't compiled with syslog support\n", prog);
		ddcLogToSyslog = false;
#endif
	}

	ddcLogInfo(startmsg);
	if (!log_stderr) fprintf(stderr, "%s\n", startmsg.c_str());
	
	if (clientMode) {
		fprintf(stderr, "removing %s\n",LockFileName.c_str());
		remove(LockFileName.c_str());
	}
	if (access(LockFileName.c_str(), R_OK) == 0) {
		fprintf(stderr, "Daemon lock-file `%s' already exists: is ddc_daemon already running?\n", LockFileName.c_str());
		return 1;
	}

	//-- show server options
	if (ddcLogLevel >= ddcLLInfo) {
		ddcLog( "ServerOptions:" );
		vector<string> srvOptLines = stringSplitE(ServerOptions.toString(),"\n");
		for (vector<string>::const_iterator li=srvOptLines.begin(); li!=srvOptLines.end(); ++li) {
			ddcLog(string("    ")+*li);
		}
		ClearVector(srvOptLines);
	}

	if (!clientMode) {		
		// running as a daemon
		int fd, i;
		struct rlimit flim;

		if (getppid()!=1) {
			signal(SIGTTOU,SIG_IGN);
			signal(SIGTTIN,SIG_IGN);
			signal(SIGTSTP,SIG_IGN);
			if (doFork) {
				CreateWaitFile();
				int fpid = fork();
				if (fpid != 0) {
					//-- parent
					fprintf(stderr, "spawned server process on pid=%d\n", fpid);
					exit(0);
				} else {
					//-- daemon==child
					setsid();
				}
			} else {
				//-- daemon==parent
				fprintf(stderr, "running server in non-forking mode on pid=%d\n", getpid());
			}
		}

		//-- close all open filehandles (forking mode only)
		if (doFork) {
		  getrlimit(RLIMIT_NOFILE, &flim);
		  for(fd=0;fd<flim.rlim_max;fd++)
		    close(fd);
		}
	}


	//syslog(LOG_ALERT, "Open	lock file `%s'\n", LockFileName.c_str());
	ddcLogDebug(Format("Open lock file `%s'", LockFileName.c_str()));
	FILE* fp = fopen (LockFileName.c_str(),	"w");
	if (!fp) {
		ddcLogError(Format("Cannot open lock-file `%s': %s",	LockFileName.c_str(), StrError(errno)));
		return 1;
	}
	fprintf(fp, "%i", getpid());
	fclose (fp);
	ddcLogDebug(Format("Wrote PID=%i to lock-file `%s'", getpid(), LockFileName.c_str()));

	ddcLogDebug("SocketInitialize");
	SocketInitialize(false);

	ddcLogDebug("InitLemmatizers");
	if (!InitConcordDicts())
		{
			ddcLogDebug("Cannot load Morphology");
			//SocketDeinitialize();
			//return 1;
		
		}

	sprintf(log_label, "server-main[pid=%i]", getpid());
	ddc_thread_init(log_label);

	ddcLogInfo(string("LoadCorpora (CWD=") + CurrentDirectory() + ")");
	LoadLocalCorpora(CorporaFile, ServerOptions);

	ddcLogInfo("LoadServer");
	LoadDDCServer(ServerCorporaFile, ServerOptions);

	//-- moo 2016-12-20: wtf is this?  it looks like a no-op (ignore signal handlers only if they're already ignored)
	if (signal (SIGTERM, termination_handler) == SIG_IGN)
		signal (SIGTERM, SIG_IGN);
	if (signal (SIGINT, termination_handler) == SIG_IGN)
		signal (SIGINT, SIG_IGN);

	if (clientMode)
		fprintf	(stderr, "\nWaiting for accept...\n");
	else {
		//-- remove the wait-file to let the caller know we've started up ok
		sleep(1);
		RemoveWaitFile();
	}

	while (1) {
		sleep(40);
	}
      }
      catch (CExpc& e) {
	      return puke(Format("Exception[%d]: %s", e.code(), e.what()));
      }
      catch (exception &e) {
	      return puke(Format("Exception: %s", e.what()));
      }
      catch (...) {
	      return puke("Exception: (unhandled exception)");
      }

      RemoveLockFile();
      SocketDeinitialize();	
      return 0;
}


//----------------------------------------------------------------------
// MAIN
int	main(int argc, char	**argv)
{

	prog = argv[0];
	sprintf(log_label, "main[pid=%i]", getpid());

	ddcInitGlobal();
	ddc_thread_init(log_label);


	if (argc == 2) 	
	{		
		string s = argv[1];		
		if (  (s == "--version") || (s== "-V"))		
		{			
			printf ("%s\n", DDCVersionStr.c_str());				
			printf ("%s: Daemon for working with Dialing-DWDS Concordance\n", argv[0]);
			return 1;		
		}	
	};
	if (argc < 2 || argv[1]=="-h" || argv[1]=="--help") 
		PrintUsage();

	string Error;
	if (!IsRmlRegistered(Error)) 
	{
		fprintf (stderr, "%s\n", Error.c_str()  );
		return 1;
	};

	//-- init globals
	CorporaFile = GetIniFilePath()+"/ddc_local_corpora.cfg";
	ServerCorporaFile = GetIniFilePath()+"/ddc_server.cfg";
	Action = "restart"; //-- default action
	doFork = true;

	//-- load default server options
	string ServerOptionsFile = GetIniFilePath()+"/ddc_server.opt";
	if (FileExists(ServerOptionsFile.c_str())) {
		try {
			//fprintf(stderr, "Loading default server-options file '%s'\n", prog, ServerOptionsFile.c_str());
			ServerOptions.LoadFile(ServerOptionsFile);
		}
		catch (exception &e) {
			fprintf(stderr, "%s: Error loading default server-options file '%s': %s\n", prog, ServerOptionsFile.c_str(), e.what());
			exit(1);
		}
	}

	//-- parse command-line
	for (size_t i=1; i<argc; i++)
	{
		string s = argv[i];
		if ((s == "-h")
		    || (s == "--help")
		    || (s == "/h")
		    || (s == "/help")
		    ) {
			PrintUsage();
		}
		else if (s == "--verbose" || s=="-v" || s=="--log-level" || s=="--log" || s=="--protocol") {
			if (i+1 >= argc) 
				PrintUsage();
			SetLogLevel( GetLogLevel(argv[i+1]) );
			gotLogLevel = true;
			i++;
		}
		else if (s == "--local" || s == "-l") {
			if (i+1 >= argc) 
				PrintUsage();
			i++;
			CorporaFile = argv[i];
		}
		else if (s == "--server" || s == "-s") {
			if (i+1 >= argc) 
				PrintUsage();
			i++;
			ServerCorporaFile = argv[i];
		}
		else if (s == "--options" || s == "-O") {
			if (i+1 >= argc) 
				PrintUsage();
			i++;
			try {
				ServerOptions.LoadFile(argv[i]); //-- load in-place
			}
			catch (exception &e) {
				fprintf(stderr, "%s: Error loading server options file '%s': %s\n", prog, argv[i], e.what());
				exit(1);
			}
		}
		else if (s == "--nthreads" || s == "--threads" || s == "-t") {
			if (i+1 >= argc)
				PrintUsage();
			i++;
			ServerOptions.m_nWorkers = strtoul(argv[i],NULL,0);
		}
		else if (s == "--fork") { doFork = true; }
		else if (s == "--nofork") { doFork = false; }
		else if (s == "--stderr") { log_stderr = true; }
		else if (s == "--nostderr") { log_stderr = false; }
		else if (s == "--syslog") { log_syslog = true; }
		else if (s == "--nosyslog") { log_syslog = false; }
		else if (s == "--logfiles" || s == "--logfile") { log_files = true; }
		else if (s == "--nologfiles" || s == "--nologfile") { log_files = false; }
		else {
			Action = argv[i];
		}
	}

	if (!FileExists(CorporaFile.c_str()))
	{
		fprintf (stderr, "cannot access %s\n", CorporaFile.c_str());
		exit(1);
	};

	LockFileName = MakeFName(CorporaFile,"ddc_lck");
	WaitFileName = MakeFName(CorporaFile,"ddc_wait");

	
	if (		(Action	!= "start")
		&&	(Action	!= "start_cli")
		&&	(Action	!= "stop")
		&&	(Action	!= "restart")
		)
		PrintUsage();

	if (Action == "start") {
		return do_start(false);
	}
	else if (Action == "start_cli") {
		return do_start(true);
	}
	else if (Action == "stop")  {
		return do_stop();
	}
	else if (Action == "restart") {
		do_stop();
		sleep(1);
		return do_start();
	}

	//-- should never get here
	RemoveLockFile();
	SocketDeinitialize();	
	return 0;
}





