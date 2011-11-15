//  Copyright 2011 by Bryan Jurish
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

#include <time.h>
#include "../ConcordLib/ConcCommon.h"
#include "../ConcordLib/ConcIndexator.h"

const char *prog = "ddc_index";
void  PrintUsageAndExit()
{
  printf ("%s\n", DDCVersionStr.c_str());
  printf ("Usage: %s <ProjectCon> [--only-reindex-morph] [--print-profiler-info] [--skip-initial-file-checking]\n", prog);
  exit(1);

};



int main(int argc, char* argv[])
{
	ddcInitGlobal();
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
		if (s == "--only-reindex-morph")
		{
			printf ("--only-reindex-morph\n");
			S.m_bOnlyReindexMorphology = true;
		}
		else
			if (s == "--skip-initial-file-checking")
			{
				printf ("--skip-initial-file-checking\n");
				S.m_bSkipInitialFileChecking = true;
			}
		else
		    if (  (s == "--version") || (s== "-v"))
			{
			  fprintf (stderr,"%s\n", DDCVersionStr.c_str());
			  fprintf (stderr,"%s: DDC corpus indexer\n", argv[0]);
			  return 1;
			}
		else
			if (s == "--print-profiler-info")
			{
				printf ("--print-profiler-info\n");
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
	
	time_t t1;
	time(&t1);

	S.m_bStdout = true;
	
	if (!S.BuildIndex(ProjectFile ))
	{
		printf ("cannot index the project!\n");
		FreeConcordDicts();
		return 1;
	};


	time_t t2;
	time(&t2);
	printf ("Seconds = %i\n", t2 - t1);
	FreeConcordDicts();
	return 0;
}

