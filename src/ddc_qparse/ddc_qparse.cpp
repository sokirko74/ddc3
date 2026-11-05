#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ConcordLib/ConcCommon.h"
#include "../ConcordLib/QueryCompiler.h"
#include "nlp_base/common/argparse.h"

using namespace std;

const char *prog = "ddc_qparse";
bool outputJson = false;
bool outputComments = false;
CQueryCompiler qc;


int main(int argc, char **argv)
{
    //---- command-line params
    string prog_base = FileBasename(*argv);
    prog = prog_base.c_str();

    //-- debug: logging
    ddcLogToStderr = true;
    ddcLogLevel    = ddcLLWarn;
    ddc_thread_init(prog);

    ArgumentParser args;
    args.SetVersion(DDCVersionStr);
    args.SetDescription("Parse a DDC query and print it in the canonical form or as JSON");
    args.AddArgument("-v, --verbose", "log level: none|error|warn|info|debug|trace", true);
    args.AddOption("-j, --json", "JSON output (default: DDC query syntax)");
    args.AddOption("-c, --comments", "keep the lexer comments");
    args.AddPositionalList("query", "the query (the words are joined with a space); use -- before a query starting with '-'");
    args.SetOpenStreams(false);
    args.Parse(argc, (const char **) argv);
    if (args.Exists("verbose")) {
        ddcLogLevel = GetLogLevel(args.Retrieve("verbose"));
        ddcLogToStderr = (ddcLogLevel!=ddcLLSilent);
    }
    outputJson = args.Exists("json");
    outputComments = args.Exists("comments");
    string qstr;
    for (auto &w : args.RetrieveList("query")) {
        if (!qstr.empty()) qstr.push_back(' ');
        qstr += w;
    }

    //-- log configuration
    ddcLogInfo(string("Query = ") + qstr);
    ddcLogInfo(Format("Output = %s", (outputJson ? "JSON" : "DDC")));
    ddcLogInfo(Format("Comments = %s", (outputComments ? "true" : "false")));

    //-- compile
    qc.m_KeepLexerComments = outputComments;
    if (!qc.ParseQuery(qstr)) {
        ddcLogError("failed to parse query");
        return 1;
    }

#if 0
    //-- prune comments (should be controlled by qc.m_KeepLexerComments
    if (!outputComments && qc.m_pQuery->m_Options) {
        qc.m_pQuery->m_Options->ClearComments();
    }
#endif

    //-- dump
    string ostr = (outputJson
                   ? qc.QueryToJson()
                   : qc.QueryToString());
    printf("%s\n", ostr.c_str());

    //-- cleanup
    qc.CleanParser();

    return 0;
}
