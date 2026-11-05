#include "nlp_base/common/utilit.h"
#include "nlp_base/common/argparse.h"
#include "../CommonLib/ddcUtil.h"
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
#include "../CommonLib/ddcExpc.h"
#include "../CommonLib/ddcFile.h"
#endif

using namespace std;

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
vector<string> ServerOptionsFiles;
bool LoadedServerOptions = false;

size_t nWorkers = 0;
bool got_nWorkers;


const char *prog = "ddc_daemon";

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
            throw( CDDCExpc("could not open wait file `%s': %s", WaitFileName.c_str(), StrError(errno)) );
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
    exit(0);
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

bool  read_pid_from_lock_file(pid_t& pid) {
    if (access(LockFileName.c_str(), R_OK) != 0) {
        fprintf(stderr, "cannot access lock file `%s' (ddc_daemon not started?)\n", LockFileName.c_str());
        return false;
    }

    FILE* fp = fopen(LockFileName.c_str(), "r");
    if (!fp) {
        fprintf(stderr, "open failed for lock file `%s': %s\n", LockFileName.c_str(), StrError(errno));
        return false;
    }
    fscanf(fp, "%i", &pid);
    fclose(fp);
    return true;
}

int print_status() {
    pid_t pid;
    if (!read_pid_from_lock_file(pid)) {
        return 1;
    }
    if (kill (pid, 0) != 0) { //it is not a kill
        fprintf (stderr, "ddc_daemon (pid=%d) cannot be found \n", pid);
        return 1;
    }
    fprintf(stderr, "ddc is running, pid=%d\n", pid);
    return 0;
}
//----------------------------------------------------------------------
// stop
int do_stop(void)
{
    pid_t pid;

    fprintf(stderr, "Stopping ddc_daemon...\n");
    if (!read_pid_from_lock_file(pid)) {
        RemoveLockFile();
        return 1;
    }
    RemoveLockFile();

    if (kill (pid, SIGTERM) == 0) {
        fprintf (stderr, "ddc_daemon (pid=%d) was stopped\n", pid);
        return 0;
    }
    else {
        fprintf(stderr, "cannot send a SIGTERM to daemon process (pid=%d): %s\n", pid, StrError(errno));
        return 1;
    }
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

        string startmsg = Format("Starting ddc_daemon v" PACKAGE_VERSION " in %s %s mode with log-level `%s'%s",
                                 (doFork ? "forked" : "unforked"),
                                 (clientMode ? "client" : "server"),
                                 LogLevelName(ddcLogLevel),
                                 (ServerOptions.m_VersionCompat==DDCVersionT::current() ? ""
                                  : (string(" (compatibility ~ ")+ServerOptions.m_VersionCompat.str()+")").c_str())
            );

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


        //syslog(LOG_ALERT, "Open       lock file `%s'", LockFileName.c_str());
        ddcLogDebug(Format("Open lock file `%s'", LockFileName.c_str()));
        FILE* fp = fopen (LockFileName.c_str(), "w");
        if (!fp) {
            ddcLogError(Format("Cannot open lock-file `%s': %s",    LockFileName.c_str(), StrError(errno)));
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
            fprintf (stderr, "\nWaiting for accept...\n");
        else {
            //-- remove the wait-file to let the caller know we've started up ok
            sleep(1);
            RemoveWaitFile();
        }

        //-- moo 2019-11-13: why does this loop exist?
        // + maybe it's a leftover from the one-fork-per-server-node era which keeps the main PID around forever?
        // + raising the sleep() interval up to 60 sec (original was 40 sec) because polling is icky, and icinga does that for us
        while (CheckDaemonAlive()) {
            sleep(60);
        }
    }
    catch (CExpc& e) {
        return puke(Format("Exception[%d]: %s", ddcExpcCode(e), e.what()));
    }
    catch (exception &e) {
        return puke(Format("Exception: %s", e.what()));
    }
    catch (...) {
        return puke("Exception: (unhandled exception)");
    }

    RemoveLockFile();
    SocketDeinitialize();     
    return 1;
}


//----------------------------------------------------------------------
// MAIN
int     main(int argc, char     **argv)
{

    prog = argv[0];
    sprintf(log_label, "main[pid=%i]", getpid());

    ddcInitGlobal();
    ddc_thread_init(log_label);

    ddcLogLevel   = ddcLLInfo;
    ddcLogToFiles = false;
    ddcLogToStderr = true;
    ddcLogToSyslog = false;

    ArgumentParser args;
    args.SetVersion(DDCVersionStr);
    args.SetDescription("The DDC server daemon");
    args.AddArgument("-v, --verbose", "log level: none|error|warn|info|debug|trace", true);
    args.AddArgument("-l, --local", "local corpus config (default: RML_INI_FOLDER/ddc_local_corpora.cfg)", true);
    args.AddArgument("-s, --server", "server config (default: RML_INI_FOLDER/ddc_server.cfg)", true);
    args.AddArgument("-O, --options", "server options file (default: RML_INI_FOLDER/ddc_server.opt)", true, true);
    args.AddArgument("-t, --threads", "number of worker threads (default: 0, serial mode)", true);
    args.AddOption("--no-fork", "do not detach from the terminal");
    args.AddOption("--stderr", "log to stderr");
    args.AddOption("--syslog", "log to syslog");
    args.AddOption("--no-log-files", "do not log to local files");
    args.AddPositional("action", "start|stop|status|restart (default)|start_cli (not as a daemon)", true);
    args.SetOpenStreams(false);
    args.Parse(argc, (const char **) argv);
    if (args.Exists("verbose")) {
        SetLogLevel(GetLogLevel(args.Retrieve("verbose")));
        gotLogLevel = true;
    }

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

    //-- queue default server options for loading
    string ServerOptionsFile = GetIniFilePath()+"/ddc_server.opt";
    if (FileExists(ServerOptionsFile.c_str()))
        ServerOptionsFiles.push_back(ServerOptionsFile);

    if (args.Exists("local")) CorporaFile = args.Retrieve("local");
    if (args.Exists("server")) ServerCorporaFile = args.Retrieve("server");
    for (auto &f : args.RetrieveList("options")) ServerOptionsFiles.push_back(f);
    if (args.Exists("threads")) {
        nWorkers = strtoul(args.Retrieve("threads").c_str(), NULL, 0);
        got_nWorkers = true;
    }
    if (args.Exists("no-fork")) doFork = false;
    if (args.Exists("stderr")) log_stderr = true;
    if (args.Exists("syslog")) log_syslog = true;
    if (args.Exists("no-log-files")) log_files = false;
    if (args.Exists("action")) Action = args.Retrieve("action");

    //-- load server options
    for (vector<string>::const_iterator optfi=ServerOptionsFiles.begin(); optfi!=ServerOptionsFiles.end(); ++optfi) {
        try {
            //ddcLogDebug(Format("%s: loading server options file %s",prog,optfi->c_str()));
            ServerOptions.LoadFile(*optfi);
        }
        catch (exception &e) {
            fprintf(stderr, "%s: Error loading server options file '%s': %s\n", prog, optfi->c_str(), e.what());
            exit(1);
        }
    }
    //-- command-line overrides for server options
    if (got_nWorkers) ServerOptions.m_nWorkers = nWorkers;

    if (!FileExists(CorporaFile.c_str()))
    {
        fprintf (stderr, "cannot access %s\n", CorporaFile.c_str());
        exit(1);
    };

    LockFileName = MakeFName(CorporaFile,"ddc_lck");
    WaitFileName = MakeFName(CorporaFile,"ddc_wait");

        
    if (            (Action != "start")
                    &&      (Action != "start_cli")
                    &&      (Action != "stop")
                    &&      (Action != "restart")
                    &&      (Action != "status")
        ) {
        fprintf(stderr, "%s: unknown action '%s'\n%s", prog, Action.c_str(), args.Usage().c_str());
        return 1;
    }

    int resultCode = 0;
    try {
        if (Action == "start") {
            return do_start(false);
        } else if (Action == "start_cli") {
            return do_start(true);
        } else if (Action == "status") {
            return print_status();
        } else if (Action == "stop") {
            return do_stop();
        } else if (Action == "restart") {
            do_stop();
            sleep(1);
            return do_start();
        }
    } catch (exception& e) {
        fprintf (stderr, "Exception: %s", e.what());
        resultCode = 1;
    }

    //-- should never get here
    RemoveLockFile();
    SocketDeinitialize();   
    return resultCode;
}
