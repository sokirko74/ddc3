//-*- Mode: C++; c-basic-offset: 8; -*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2018 by Bryan Jurish
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
//#include "../ConcordLib/QueryCompiler.h" //-- for debugging ddcObject::Descendants()
#include "../CommonLib/utilit.h"
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
		 "  -Start FROM                           # alias -From; default=0\n"
		 "  -Limit LIMIT                          # default=10\n"
		 "  -MinKey KEY                           # implicit key-based pruning\n"
		 "  -ResultFormat TXT|HTML|TABLE|JSON     # default=TXT\n"
		 "  -ProfileRun NITERS                    # none by default\n"
		 "  -PrintProfile                         # print profile results\n"
		 "  -HitCount                             # call GetHits() rather than SimpleQuery()\n"
		 "  -HitIds                               # call GetHitIds() (simulate subcorpus server)\n"
		 "  -NoMorphology                         # suppress call to InitConcordDicts()\n"
 		 "  -verbose LEVEL                        # set log-verbosity level (none|error|warn|info=weak|debug=medium|trace=heavy)\n"
		 "\n"
		 "Where \"-Limit\" gives the maximum count of occurrences to find\n"
		 "and \"-Start\" indicates the occurence number from which to start\n"
		 "QUERY argument can be specified as '<FILE' to read from the named file.\n"
		 "\n"
		 "Example(1): %s test.con \"thank && God\" out.txt -Limit 10\n",
		 
		 prog, prog
		 );
	exit(1);

};

int main(int argc, char* argv[])
{
	ddcInitGlobal();
	ddc_thread_init(prog);

	SetLogLevel(ddcLLInfo);
	ddcLogToSyslog = false;
	ddcLogToFiles  = false;
	ddcLogToStderr = true;
	
	prog = argv[0];
	{
		StringVector Args;
		bool bResultLimitGiven = false;
		int ResultLimit  = -1;
		string ResultMinKey = "";
		bool bPrintProfile = false;
		bool bOnlyGetHitsCount = false;
		bool bOnlyGetHitIds = false;
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
			string s    = argv[i];
			string s_lo = stolower(s);
			if (s_lo == "-h" || s_lo == "--help") {
				PrintUsageAndExit();
			}
			else if (s_lo == "-limit")
			{
				if (i+1 >= argc)
					PrintUsageAndExit();

				bResultLimitGiven = true;
				ResultLimit = atoi(argv[i+1]);
				i++;
			}
			else if (s_lo == "-minkey")
			{
				if (i+1 >= argc)
					PrintUsageAndExit();

				ResultMinKey = argv[i+1];
				i++;
			}
                        else
			if (s_lo == "-from" || s_lo == "-start")
			{
				if (i+1 >= argc)
					PrintUsageAndExit();

				StartFrom = atoi(argv[i+1]);
				i++;
			}
                        else
			if (s_lo == "-resultformat" || s_lo == "-format" || s_lo == "-format")
			{
				if (i+1 >= argc)
					PrintUsageAndExit();

				ResultFormat = stoupper(argv[i+1]);
				i++;
			}
			else if (s_lo == "-text" || s_lo == "-txt") { ResultFormat = "txt"; }
			else if (s_lo == "-html" || s_lo == "-html") { ResultFormat = "html"; }
			else if (s_lo == "-table" || s_lo == "-tab") { ResultFormat = "table"; }
			else if (s_lo == "-json" || s_lo == "-js") { ResultFormat = "json"; }
			else
			if (s_lo == "-printprofile")
			{
				bPrintProfile = true;
				fprintf  (stderr, "print profiling afterwards\n");
			}
			else
			if (s_lo == "-nomorphology" || s_lo == "-nomorph")
			{
				bInitConcordDicts = false;
				fprintf  (stderr, "no call to InitConcordDicts\n");
			}
			else
			if (s_lo == "-onlygethitids" || s_lo == "-hitids" || s_lo == "-ids")
                        {
				bOnlyGetHitIds = true;
				fprintf  (stderr, "OnlyGetHitIds\n");
			}
			else
			if (s_lo == "-onlygethitscount" || s_lo == "hitcount" || s_lo == "-count")
			{
				bOnlyGetHitsCount = true;
				fprintf  (stderr, "OnlyGetHitsCount\n");
			}
			else
			if (s_lo == "-profilerun" || s_lo == "-profile")
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
		    	if (  (s == "--version") || (s== "-V"))
			{
				fprintf (stderr,"%s\n", DDCVersionStr.c_str());	
				fprintf (stderr,"ddc_simple: command line query processor\n");	
				return 1;
			}
			else if (s == "--verbose" || s=="-v" || s=="--log-level" || s=="--log" || s=="--protocol") {
				if (i+1 >= argc) 
					PrintUsageAndExit();
				SetLogLevel( GetLogLevel(argv[i+1]) );
				i++;
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

			if (bResultLimitGiven)
				R.m_ResultLimit = ResultLimit;

			R.m_ResultMinKey = ResultMinKey;
			fprintf  (stderr, "Finding at least %zi occurrences\n", R.m_ResultLimit);

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
			if (!_Query.empty() && (_Query[0]=='<' || _Query=="query.txt")) {
				//-- read from named file
				if (_Query[0]=='<') _Query.erase(0,1);

		 		FILE *fp = fopen(_Query.c_str(), "r");
				if (!fp)
				{
					fprintf (stderr, "cannot open input file  %s\n", _Query.c_str());
					return 1;
				}
				else
				{
					char s[1024];
					while (fgets(s,1024,fp)) {
						string q = s;
						Trim(q);
						if (!q.empty())
							queries.push_back(q);
					}
					fclose (fp);
				}
			}
			else
			{
				queries.push_back(_Query + " "); //-- query parser needs trailing whitespace!
			};


			DWORD  EndHitNo = StartFrom;		
			DWORD  HitsCount = 0;
			clock_t AllStartTime = clock();

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
					    fprintf (stderr, "Query[%d / %zi] = %s\n", QueryNo, queries.size(), Query.c_str());
					    try {
						    fprintf (stderr, "Canon[%d / %zi] = %s\n", QueryNo, queries.size(), R.CanonicalQueryString(Query).c_str());
						    fprintf (stderr, "Json [%d / %zi] = %s\n", QueryNo, queries.size(), R.JsonQueryString(Query).c_str());
#if 0
						    //-- test ddcObject::Descendants()
						    fprintf(stderr, "Descendants[%d / %zi] (Compiler) =\n", QueryNo, queries.size());
						    ddcObjectList objs = R.m_pQueryCompiler->Descendants();
						    for (ddcObjectList::const_iterator oi=objs.begin(); oi != objs.end(); ++oi) {
							    fprintf(stderr, " + %s\n", *oi ? (*oi)->toString().c_str() : "NULL");
						    }
#endif
					    }
					    catch (exception &e) {
						    fprintf(stderr, "Exception: %s\n", e.what());
					    }
					}
					EndHitNo = StartFrom;
					if (bOnlyGetHitsCount || bOnlyGetHitIds)
					{
						clock_t     StartTime = clock();
						DDCErrorEnum Error =   R.GetHits(Query, EndHitNo);
						clock_t     EndTime = clock();

						long      TimeSpan = EndTime - StartTime;
						
						if (ProfileCycleNo==0) {
							fprintf (stderr, "ticks %zi\n", TimeSpan ); 
						
							if (Error != errNone) {
								fprintf (stderr, "Error! %s \n", GetDDCErrorString(Error));
								return -1;
							}
							else {
								fprintf (stderr, "Number of hits found : %zi\n", R.m_AllHitsCount);
								fprintf (stderr, "Next available hit   : %i\n", EndHitNo);
							}

							if (bOnlyGetHitIds) {
								string Result = R.GetHitIds();
								printf("HitIDs = %s\n", Result.c_str());
							}
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
					R.ClearQuery();
				}
			}
			if (CountOfCycles>1) fputs(" done.\n",stderr);
			
			
			clock_t     AllEndTime = clock();
			double elapsed = (double)(AllEndTime - AllStartTime)/(double)CLOCKS_PER_SEC;
			double q_sec  = (double)CountOfCycles * (double)queries.size() / elapsed;
			fprintf (stderr, "Seconds = %.3f\n", elapsed);
			fprintf (stderr, "Queries/Sec = %.3f\n", q_sec);
			fprintf (stderr, "HitsCount = %i\n", HitsCount);

			DDCProcessMemoryStatus mstat(getpid());
			fprintf(stderr, "Memory Usage (kB) = VmPeak:%zd , VmSize:%zd , VmHWM:%zd , VmRSS:%zd , VmSwap:%zd\n",
				mstat.VmPeak, mstat.VmSize, mstat.VmHWM, mstat.VmRSS, mstat.VmSwap);


			fprintf (OutFile, "%s", R.m_QueryResultStr.c_str());
			if (OutFile != stdout) fclose(OutFile);

			fprintf (stderr, "All bytes read while querying = %zi\n", AllBytesRead);
			if (bPrintProfile)
				fprintf (stderr, "===== Profiler  ====\n %s\n",R.m_Profiler.GetStrRepresentation().c_str());

			delete R.m_pIndexator;

		}
		FreeConcordDicts();
	}



	return 0;
}





