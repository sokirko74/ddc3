//  Original by Alexey Sokirko.
//
//  Modifications sopyright 2011-2018 by Bryan Jurish
//
// ConcordIndex.cpp : Defines the entry point for the console application.
//

#include "../CommonLib/ddcTime.h"
#include "../ConcordLib/ConcCommon.h"
#include "../ConcordLib/ConcIndexatorInvoker.h"

using namespace std;

const char *prog = "ddc_index";
void  PrintUsageAndExit()
{
    printf ("%s\n", DDCVersionStr.c_str());
    printf ("Index a DDC project (*.con) file\n");
    printf ("\nUsage: %s [OPTIONS] PROJECT\n", prog);
    printf ("\nOptions:\n"
            "  -V, --version                      # report program version and exit\n"
            "  -h, --help                         # this help message\n"
            "  -v, --verbose LEVEL                # set log-verbosity level (none|error|warn|info=weak|debug=medium|trace=heavy)\n"
            "  -a, --anonymize                    # enable anonymous tokens (beginning with '-#')?\n"
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
    ConcIndexatorInvoker S;
    bool bOnlyReindexMorphology = false;
    bool bPrintProfile = false;
    bool bSkipInitialFileChecking = false;
    string ProjectFile;
    for (size_t i=1; i < argc; i++)
    {
        string s = argv[i];
        if (s=="-h" || s=="--help") {
            PrintUsageAndExit();
        }
        else if (  (s == "--version") || (s== "-V")) {
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
        else if (s == "-a" || s == "--anonymize") {
            ddcEnableAnonymousTokens = true;
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

    //-- verbose log label
    string loglabel = FileBasename(prog) + " " + FileBasename(ProjectFile);
    ddc_set_log_label(loglabel.c_str());

    //-- guts
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
