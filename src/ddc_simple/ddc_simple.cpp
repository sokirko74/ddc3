//-*- Mode: C++; c-basic-offset: 8; -*-
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
// ConcordSimple.cpp : Defines the entry point for the 



#include <time.h>

#include "../ConcordLib/ConcHolder.h"
#include "../common/utilit.h"
extern size_t AllBytesRead;;

#ifdef DETECT_MEMORY_LEAK
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

const char *prog = "ddc_simple";

void PrintUsageAndExit()
{
	fprintf (stderr,"%s\n", DDCVersionStr.c_str());	
	fprintf (stderr,
		 "Usage: %s <Concordance_Project> <query_in_CODEPAGE> <out_file> [OPTIONS]\n"
		 "\n"
		 "Options:\n"
		 "  -Limit n\n"
		 "  -ProfileRun n\n"
		 "  -ResultFormat TXT|HTML|TABLE|JSON\n"
		 "  -PrintProfile\n"
		 "  -OnlyGetHitsCount\n"
		 "  -From HitStart\n"
		 "  -NoMorphology\n"
		 "\n"
		 "Where \"-Limit\" is maximum count of occurrences to find\n"
		 "and \"-From\" is the occurence number from which to start\n"
		 "\n"
		 "Example(1): ddcSimple test.con \"thank && God\" out.txt -Limit 10\n",
		 prog
		 );
	exit(1);

};

int main(int argc, char* argv[])
{
	ddcInitGlobal();
	prog = argv[0];

	{
		StringVector Args;
		int ResultLimit  = -1;
		bool bPrintProfile = false;
		bool bOnlyGetHitsCount = false;
		bool bInitConcordDicts = true;
		int CountOfCycles = 1;
		string _Query;
		string Corpus;
		string OutFileName = "-";
                string ResultFormat = "GUESS"; 
		int ContextSize = -1;
                DWORD StartFrom = 0;

		for (size_t i=1; i<argc; i++)
		{
			string s  = argv[i];
			if (s == "-Limit")
			{
				if (i+1 >= argc)
					PrintUsageAndExit();

				ResultLimit = atoi(argv[i+1]);
				i++;
			}
                        else
			if (s == "-From")
			{
				if (i+1 >= argc)
					PrintUsageAndExit();

				StartFrom = atoi(argv[i+1]);
				i++;
			}
                        else
			if (s == "-ResultFormat")
			{
				if (i+1 >= argc)
					PrintUsageAndExit();

				ResultFormat = argv[i+1];
				i++;
			}
			else
			if (s == "-PrintProfile")
			{
				bPrintProfile = true;
				fprintf  (stderr, "print profililng afterwards\n");
			}
			else
			if (s == "-NoMorphology")
			{
				bInitConcordDicts = false;
				fprintf  (stderr, "no call to InitConcordDicts\n");
			}
			else
			if (s == "-OnlyGetHitsCount")
			{
				bOnlyGetHitsCount = true;
				fprintf  (stderr, "OnlyGetHitsCount\n");
			}
			else
			if (s == "-ProfileRun")
			{
				if (i+1 >= argc)
					PrintUsageAndExit();
				else
				{
					CountOfCycles = atoi(argv[i+1]);
					fprintf (stderr,"Count of profile cycles = %i\n", CountOfCycles);
					i++;
				};

			}
			else
		    if (  (s == "--version") || (s== "-v"))
			{
				fprintf (stderr,"%s\n", DDCVersionStr.c_str());	
				fprintf (stderr,"ddcSimple, command line query processor\n");	
				return 1;
			}
			else
				Args.push_back(argv[i]);

		};

		if (Args.size() < 2)
			PrintUsageAndExit();
		Corpus = Args[0];
		_Query = Args[1];
		if (Args.size() > 2)
		    OutFileName =  Args[2];


		{
		
			CConcHolder R;

			R.m_pIndexator = new CConcIndexator;

			if (bPrintProfile)
				R.m_Profiler.m_bTimeSpanHolderEnabled = true;

			if (!R.m_pIndexator->LoadProject(Corpus) )
			{
				fprintf (stderr, "cannot load project %s\n", Corpus.c_str());
				return -1;
			};

			if (bInitConcordDicts)
				InitConcordDicts();
			
			FILE* OutFile = 0;

			if (OutFileName == "-") {
			  //-- output to stdout
			  fprintf  (stderr, "Output to stdout\n");
			  OutFile = stdout;
			} else {
			  fprintf  (stderr, "Open output file %s\n", OutFileName.c_str());
			  remove(OutFileName.c_str());
			  OutFile = fopen (OutFileName.c_str(), "w");
			}
			if (!OutFile)
			{
				fprintf (stderr, "cannot open output file  %s\n", OutFileName.c_str());
				return -1;
			}

			R.m_ResultLimit = 10;

			if (ResultLimit != -1)
				R.m_ResultLimit = ResultLimit;

			fprintf  (stderr, "Finding at least %i occurrences\n", R.m_ResultLimit);

                        if (ResultFormat=="GUESS")
                        {
			    if (IsJsonFile(OutFileName)) {
				ResultFormat = "JSON";
    		            } else if (IsHtmlFile(OutFileName)) {
				ResultFormat = "HTML";
			    } else if (IsTableFile(OutFileName)) {
				ResultFormat = "TABLE";
			    } else {
				ResultFormat = "TEXT";
			    }
                        };
			fprintf(stderr, "Using result format %s\n", ResultFormat.c_str());
                        R.SetResultFormat(ResultFormat);

			R.m_QueryResultStr = "";
			
			vector<string>	queries;
			if (_Query != "query.txt")
				queries.push_back(_Query);
			else
			{
		 		FILE *fp = fopen(_Query.c_str(), "r");
				if (!fp)
				{
					fprintf (stderr, "cannot open input file  %s\n", _Query.c_str());
					return 1;
				}
				else
				{
					char s[1000];
					while (fgets(s,1000,fp)) {
						string q = s;
						Trim(q);
						if (!q.empty())
							queries.push_back(q);
					}
					fclose (fp);
				};
			};
			
			

			DWORD  EndHitNo = StartFrom;		
			DWORD  HitsCount = 0;
			

			clock_t     AllStartTime = clock();
			
			

			for (int ProfileCycleNo=0; ProfileCycleNo < CountOfCycles; ProfileCycleNo++) {
				if (ProfileCycleNo==1) {
					fprintf(stderr,"Profiling %d iterations...", CountOfCycles);
				}
				else if (ProfileCycleNo>0 && (ProfileCycleNo%100)==0) {
					fputc('.',stderr);
				}

				for (int QueryNo=0; QueryNo < queries.size(); QueryNo++)
				{
			
					string Query = queries[QueryNo];
					if (ProfileCycleNo==0) {
					    fprintf (stderr, "Query[%d / %d] = %s\n", QueryNo, queries.size(), Query.c_str());
					    try {
						    fprintf (stderr, "Canon[%d / %d] = %s\n", QueryNo, queries.size(), R.CanonicalQueryString(Query).c_str());
					    }
					    catch (exception &e) {
						    fprintf(stderr, "Exception: %s\n", e.what());
					    }
					}
					EndHitNo = StartFrom;
					if (bOnlyGetHitsCount)
					{
						clock_t     StartTime = clock();
						DDCErrorEnum Error =   R.GetHits(Query, EndHitNo);
						clock_t     EndTime = clock();

						long      TimeSpan = EndTime - StartTime;
						
						fprintf (stderr, "ticks %i\n", TimeSpan ); 
						
						if (Error != errNone)
						{
							fprintf (stderr, "Error! %s \n", GetDDCErrorString(Error));
							return -1;
						}
						else
						{
						    fprintf (stderr, "Number of found docs : %i\n", R.m_AllHitsCount);
						}
					}
					else
					{
						try {
							DDCErrorEnum Error =   R.SimpleQuery(Query, EndHitNo, HitsCount);
							if (Error != errNone)
								{
									fprintf (stderr, "Error! %s \n", GetDDCErrorString(Error));
									return -1;
								};
						}
						catch (CExpc& e) {
							fprintf(stderr, "Exception[%d]: %s\n", e.code(), e.what());
							return -1;
						}
						catch (exception &e) {
							fprintf(stderr, "Exception: %s\n", e.what());
							return -1;
						}
						catch (...) {
							fprintf(stderr, "Exception: (unhandled exception)\n");
							return -1;
						}

					}
					R.ClearQueryCache();
				}
			}
			if (CountOfCycles>1) fputs(" done.\n",stderr);
			
			
			clock_t     AllEndTime = clock();
			double elapsed = (double)(AllEndTime - AllStartTime)/(double)CLOCKS_PER_SEC;
			double q_sec  = (double)CountOfCycles * (double)queries.size() / elapsed;
			fprintf (stderr, "Seconds = %.3f\n", elapsed);
			fprintf (stderr, "Queries/Sec = %.3f\n", q_sec);
			fprintf (stderr, "HitsCount = %i\n", HitsCount);
			fprintf (OutFile, "%s", R.m_QueryResultStr.c_str());
			if (OutFile != stdout) fclose(OutFile);

			fprintf (stderr, "All bytes read while querying = %i\n", AllBytesRead);
			if (bPrintProfile)
				fprintf (stderr, "===== Profiler  ====\n %s\n",R.m_Profiler.GetStrRepresentation().c_str());

			delete R.m_pIndexator;

		}
		FreeConcordDicts();
	}



	return 0;
}





