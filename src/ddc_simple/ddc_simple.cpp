// ConcordSimple.cpp : Defines the entry point for the 
// ConcordSimple.cpp : Defines the entry point for the

#include <time.h>

#include "../ConcordLib/ConcHolder.h"
#include "nlp_base/common/utilit.h"
#include "../CommonLib/ddcUtil.h"
#include "nlp_base/common/rapidjson.h"
#include "../CommonLib/ddcProcess.h"
#include "nlp_base/common/argparse.h"


using namespace std;

extern size_t AllBytesRead;;


const char *prog = "ddc_simple";

string PrettifyJson (string s) {
    rapidjson::Document doc;
    if (doc.Parse(s.c_str()).HasParseError())
        return s;
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    writer.SetIndent(' ', 3);
    doc.Accept(writer);
    return string(buffer.GetString()) + "\n";
}

int main(int argc, char *argv[]) {
    ddcInitGlobal();
    ddc_thread_init(prog);

    SetLogLevel(ddcLLInfo);
    ddcLogToSyslog = false;
    ddcLogToFiles = false;
    ddcLogToStderr = true;

    prog = argv[0];
    {
        ArgumentParser args;
        args.SetVersion(DDCVersionStr);
        args.SetDescription("Run a query against a DDC project");
        args.AddArgument("-v, --verbose", "log level: none|error|warn|info|debug|trace", true);
        args.AddArgument("-o, --output", "output file (default: stdout); its extension selects the result format", true);
        args.AddArgument("-f, --query-file", "a file with queries, one per line", true);
        args.AddArgument("--start", "the number of the first hit (default: 0)", true);
        args.AddArgument("--limit", "the maximal number of hits (default: 10)", true);
        args.AddArgument("--hint", "navigation hint sort key", true);
        args.AddArgument("--result-format", "txt|html|table|json (default: by the output file extension, else txt)", true);
        args.AddArgument("--profile-run", "repeat the queries N times", true);
        args.AddOption("--hit-count", "call GetHits() rather than SimpleQuery()");
        args.AddOption("--hit-ids", "call GetHitIds() (simulate a subcorpus server)");
        args.AddOption("--no-morphology", "do not load the morphological dictionaries");
        args.AddOption("--pretty", "pretty-print the result (json only)");
        args.AddPositional("project", "the DDC project file (*.con)");
        args.AddPositional("query", "the query (or use --query-file)", true);
        args.SetEpilog("Example: ddc_simple --limit 10 -o out.txt test.con \"thank && God\"");
        args.SetOpenStreams(false);
        args.Parse(argc, (const char **) argv);
        if (args.Exists("verbose"))
            SetLogLevel(GetLogLevel(args.Retrieve("verbose")));

        string Corpus = args.Retrieve("project");
        string _Query = args.Retrieve("query");
        string QueryFileName = args.Retrieve("query-file");
        if (_Query.empty() && QueryFileName.empty()) {
            fprintf(stderr, "%s: no query (give QUERY or --query-file)\n%s", prog, args.Usage().c_str());
            return 1;
        }
        string OutFileName = args.Exists("output") ? args.Retrieve("output") : "-";
        bool bResultLimitGiven = args.Exists("limit");
        int ResultLimit = args.Retrieve("limit", -1);
        string ResultMinKey = args.Retrieve("hint");
        uint32_t StartFrom = args.Retrieve("start", 0);
        string ResultFormat = args.Exists("result-format") ? stoupper(args.Retrieve("result-format")) : "GUESS";
        int CountOfCycles = args.Retrieve("profile-run", 1);
        bool bOnlyGetHitsCount = args.Exists("hit-count");
        bool bOnlyGetHitIds = args.Exists("hit-ids");
        bool bInitConcordDicts = !args.Exists("no-morphology");
        bool bPretty = args.Exists("pretty");

        {

            CConcHolder R;

            R.m_pConcordance = new CConcordance;

            try {
                R.m_pConcordance->LoadProject(Corpus, false);
            }
            catch (exception &e) {
                fprintf(stderr, "cannot load project %s: %s\n", Corpus.c_str(), e.what());
                return -1;
            };

            if (bInitConcordDicts)
                InitConcordDicts();

            FILE *OutFile = 0;

            if (OutFileName == "-") {
                //-- output to stdout
                fprintf(stderr, "Output to stdout\n");
                OutFile = stdout;
            } else {
                fprintf(stderr, "Open output file %s\n", OutFileName.c_str());
                remove(OutFileName.c_str());
                OutFile = fopen(OutFileName.c_str(), "w");
            }
            if (!OutFile) {
                fprintf(stderr, "cannot open output file  %s\n", OutFileName.c_str());
                return -1;
            }

            R.m_ResultLimit = 10;

            if (bResultLimitGiven)
                R.m_ResultLimit = ResultLimit;

            R.m_ResultMinKey = ResultMinKey;
            fprintf(stderr, "Finding at least %zi occurrences\n", R.m_ResultLimit);

            if (ResultFormat == "GUESS") {
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

            vector<string> queries;
            if (!QueryFileName.empty()) {
                FILE *fp = fopen(QueryFileName.c_str(), "r");
                if (!fp) {
                    fprintf(stderr, "cannot open input file  %s\n", QueryFileName.c_str());
                    return 1;
                } else {
                    char s[1024];
                    while (fgets(s, 1024, fp)) {
                        string q = s;
                        Trim(q);
                        if (!q.empty())
                            queries.push_back(q);
                    }
                    fclose(fp);
                }
            } else {
                queries.push_back(_Query + " "); //-- query parser needs trailing whitespace!
            };


            uint32_t EndHitNo = StartFrom;
            uint32_t HitsCount = 0;
            clock_t AllStartTime = clock();

            for (int ProfileCycleNo = 0; ProfileCycleNo < CountOfCycles; ProfileCycleNo++) {
                if (ProfileCycleNo == 1) {
                    fprintf(stderr, "Profiling %d iterations...", CountOfCycles);
                } else if (ProfileCycleNo > 0 && (ProfileCycleNo % 100) == 0) {
                    fputc('.', stderr);
                }

                for (int QueryNo = 0; QueryNo < queries.size(); QueryNo++) {

                    string Query = queries[QueryNo];
                    if (ProfileCycleNo == 0) {
                        fprintf(stderr, "Query[%d / %zi] = %s\n", QueryNo, queries.size(), Query.c_str());
                        try {
                            fprintf(stderr, "Canon[%d / %zi] = %s\n", QueryNo, queries.size(),
                                    R.CanonicalQueryString(Query).c_str());
                            fprintf(stderr, "Json [%d / %zi] = %s\n", QueryNo, queries.size(),
                                    R.JsonQueryString(Query).c_str());
                        }
                        catch (exception &e) {
                            fprintf(stderr, "Exception: %s\n", e.what());
                        }
                    }
                    EndHitNo = StartFrom;
                    if (bOnlyGetHitsCount || bOnlyGetHitIds) {
                        clock_t StartTime = clock();
                        DDCErrorEnum Error = R.GetHits(Query, EndHitNo);
                        clock_t EndTime = clock();

                        long TimeSpan = EndTime - StartTime;

                        if (ProfileCycleNo == 0) {
                            fprintf(stderr, "ticks %zi\n", TimeSpan);

                            if (Error != errNone) {
                                fprintf(stderr, "Error! %s \n", GetDDCErrorString(Error));
                                return -1;
                            } else {
                                fprintf(stderr, "Number of hits found : %zi\n", R.m_AllHitsCount);
                                fprintf(stderr, "Next available hit   : %i\n", EndHitNo);
                            }

                            if (bOnlyGetHitIds) {
                                string Result = R.GetHitIds();
                                printf("HitIDs = %s\n", Result.c_str());
                            }
                        }
                    } else {
                        try {
                            DDCErrorEnum Error = R.SimpleQuery(Query, EndHitNo, HitsCount);
                            if (Error != errNone) {
                                fprintf(stderr, "Error! %s \n", GetDDCErrorString(Error));
                                return -1;
                            };
                        }
                        catch (CExpc &e) {
                            fprintf(stderr, "Exception[%d]: %s\n", ddcExpcCode(e), e.what());
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
            if (CountOfCycles > 1) fputs(" done.\n", stderr);


            clock_t AllEndTime = clock();
            double elapsed = (double) (AllEndTime - AllStartTime) / (double) CLOCKS_PER_SEC;
            double q_sec = (double) CountOfCycles * (double) queries.size() / elapsed;
            fprintf(stderr, "Seconds = %.3f\n", elapsed);
            fprintf(stderr, "Queries/Sec = %.3f\n", q_sec);
            fprintf(stderr, "HitsCount = %i\n", HitsCount);

            DDCProcessMemoryStatus mstat(getpid());
            fprintf(stderr, "Memory Usage (kB) = VmPeak:%zd , VmSize:%zd , VmHWM:%zd , VmRSS:%zd , VmSwap:%zd\n",
                    mstat.VmPeak, mstat.VmSize, mstat.VmHWM, mstat.VmRSS, mstat.VmSwap);


            string result = R.m_QueryResultStr;
            if (bPretty) {
                result = PrettifyJson(result);
            }
            fprintf(OutFile, "%s", result.c_str());
            if (OutFile != stdout) fclose(OutFile);

            fprintf(stderr, "All bytes read while querying = %zi\n", AllBytesRead);

            delete R.m_pConcordance;

        }
        FreeConcordDicts();
    }


    return 0;
}
