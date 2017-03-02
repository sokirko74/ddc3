//-*- Mode: C++; c-basic-offset: 8; -*-
//
//  Original by Alexey Sokirko.
//
//  Modifications sopyright 2011-2016 by Bryan Jurish
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
// ConcordIndex.cpp : Defines the entry point for the console application.
//

#include "../CommonLib/ddcTime.h"
#include "../ConcordLib/ConcCommon.h"
#include "../ConcordLib/ConcIndexator.h"

const char *prog = "ddc_index";
void  PrintUsageAndExit()
{
  printf ("%s\n", DDCVersionStr.c_str());
  printf ("Index a DDC project (*.con) file\n");
  printf ("\nUsage: %s [OPTIONS] PROJECT\n", prog);
  printf ("\nOptions:\n"
	  "  -V, --version                      # report program version and exit\n"
	  "  -v, --verbose LEVEL                # set log-verbosity level (none|error|warn|info=weak|debug=medium|trace=heavy)\n"
	  "      --only-reindex-morph\n"
	  "      --print-profiler-info\n"
	  "      --skip-initial-file-checking\n"
	  );
  printf("\nNotes:\n"
	 "  + may generate large temporary files in $TMP or /tmp\n"
	 );
  exit(1);
};



int main(int argc, char* argv[])
{
	ddcInitGlobal();
	ddc_thread_init(prog);

	SetLogLevel(ddcLLDebug);
	ddcLogToSyslog = false;
	ddcLogToFiles  = false;
	ddcLogToStderr = true;

	prog = argv[0];
	if (argc < 2) 
		PrintUsageAndExit();
	CConcIndexatorInvoker S;
	bool bOnlyReindexMorphology = false;
	bool bPrintProfile = false;
	bool bSkipInitialFileChecking = false;
	string ProjectFile;
	for (size_t i=1; i < argc; i++)
	{
		string s = argv[i];
		if (  (s == "--version") || (s== "-V")) {
			fprintf (stderr,"%s\n", DDCVersionStr.c_str());	
			fprintf (stderr,"ddc_index: create index from a DDC project *.con file\n");	
			return 1;
		}
		else if (s == "--verbose" || s=="-v" || s=="--log-level" || s=="--log" || s=="--protocol") {
			if (i+1 >= argc) 
				PrintUsageAndExit();
			SetLogLevel( GetLogLevel(argv[i+1]) );
			i++;
		}
		else if (s == "--only-reindex-morph")
		{
			ddcLogInfo("--only-reindex-morph");
			S.m_bOnlyReindexMorphology = true;
		}
		else
			if (s == "--skip-initial-file-checking")
			{
				ddcLogInfo("--skip-initial-file-checking");
				S.m_bSkipInitialFileChecking = true;
			}
		else
			if (s == "--print-profiler-info")
			{
				ddcLogInfo("--print-profiler-info");
				S.m_Profiler.m_bTimeSpanHolderEnabled = true;
			}
			else
			{
				if (!ProjectFile.empty())
					PrintUsageAndExit();
				ProjectFile = s;
			}

	};
	

	InitConcordDicts();
	
	DDCTimeHiRes t0 = DDCTimeHiRes::Now();
	S.m_bStdout = true;
	
	if (!S.BuildIndex(ProjectFile ))
	{
		ddcLogError("cannot index the project!");
		FreeConcordDicts();
		return 1;
	};


	double elapsed = DDCTimeHiRes::Now().Elapsed(t0);
	ddcLogInfo(Format("Elapsed time = %gs\n", elapsed));
	FreeConcordDicts();
	return 0;
}

