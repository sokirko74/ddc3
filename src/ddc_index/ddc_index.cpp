//  Original by Alexey Sokirko.
//
//  Modifications sopyright 2011-2018 by Bryan Jurish
//
// ConcordIndex.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "../CommonLib/ddcTime.h"
#include "../ConcordLib/ConcCommon.h"
#include "../ConcordLib/ConcIndexatorInvoker.h"
#include "nlp_base/common/utilit.h"
#include "nlp_base/common/argparse.h"

using namespace std;

const char *prog = "ddc_index";

int main(int argc, char* argv[])
{
    ddcInitGlobal();
    ddc_thread_init(prog);

    SetLogLevel(ddcLLDebug);
    ddcLogToSyslog = false;
    ddcLogToFiles  = false;
    ddcLogToStderr = true;

    prog = argv[0];
    ArgumentParser args;
    args.SetVersion(DDCVersionStr);
    args.SetDescription("Index a DDC project (*.con) file");
    args.AddArgument("-v, --verbose", "log level: none|error|warn|info|debug|trace", true);
    args.AddOption("-a, --anonymize", "enable anonymous tokens (beginning with '-#')");
    args.AddOption("--only-reindex-morph", "rebuild only the morphological pattern index");
    args.AddOption("--print-profiler-info", "print the profiler information");
    args.AddOption("--skip-initial-file-checking", "do not check the input files before indexing");
    args.AddPositional("project", "the DDC project file (*.con)");
    args.SetEpilog("Notes:\n  + may generate large temporary files in $TMP or /tmp");
    args.SetOpenStreams(false);
    args.Parse(argc, (const char **) argv);
    if (args.Exists("verbose"))
        SetLogLevel(GetLogLevel(args.Retrieve("verbose")));

    ConcIndexatorInvoker S;
    string ProjectFile = args.Retrieve("project");
    if (args.Exists("anonymize"))
        ddcEnableAnonymousTokens = true;
    S.m_bOnlyReindexMorphology = args.Exists("only-reindex-morph");
    S.m_bSkipInitialFileChecking = args.Exists("skip-initial-file-checking");
    S.m_Profiler.m_bTimeSpanHolderEnabled = args.Exists("print-profiler-info");

    InitConcordDicts();
        
    DDCTimeHiRes t0 = DDCTimeHiRes::Now();
    S.m_bStdout = true;

    //-- verbose log label
    string loglabel = FileBasename(prog) + " " + FileBasename(ProjectFile);
    ddc_set_log_label(loglabel.c_str());

    //-- guts
    try {
        if (!S.BuildIndex(ProjectFile ))
        {
            ddcLogError("cannot index the project!");
            FreeConcordDicts();
            return 1;
        };
    }
    catch (std::exception &e) {
        //-- e.g. an input file that is not valid UTF-8
        ddcLogError(Format("cannot index the project: %s", e.what()));
        FreeConcordDicts();
        return 1;
    }


    double elapsed = DDCTimeHiRes::Now().Elapsed(t0);
    ddcLogInfo(Format("Elapsed time = %gs\n", elapsed));
    FreeConcordDicts();
    return 0;
}
