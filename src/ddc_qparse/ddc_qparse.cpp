#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ConcordLib/ConcCommon.h"
#include "../ConcordLib/QueryCompiler.h"

using namespace std;

const char *prog = "ddc_qparse";
bool outputJson = false;
bool outputComments = false;
CQueryCompiler qc;

void PrintUsage()
{
    printf("\n"
           "Usage: %s [OPTIONS] [--] [QUERY...]\n", prog);
    printf("\n"
           "Options:\n"
           "  -h, -help          # this help message\n"
           "  -v, -verbose LEVEL # set ddc log level (silent|error|warn|info|debug|trace)\n"
           "  -d, -ddc           # select DDC output (default)\n"
           "  -j, -json          # select JSON output\n"
           "  -c, -[no]comments  # do/don't keep lexer comments (default=don't)\n"
           "\n"
        );
    exit(-1);   
};

int main(int argc, char **argv)
{
    //---- command-line params
    string prog_base = FileBasename(*argv);
    prog = prog_base.c_str();

    //-- debug: logging
    ddcLogToStderr = true;
    ddcLogLevel    = ddcLLWarn;
    ddc_thread_init(prog);

    bool   optsDone = false;
    string qstr;
    for (argv++,argc--; argc > 0; argv++,argc--) {
        string a = *argv;
        if (!optsDone) {
            string av = argc > 1 ? string(*(argv+1)) : string("");
            if (a=="-h" || a=="-help" || a=="--help") {
                PrintUsage();
            } else if (a=="-j" || a=="-json" || a=="--json") {
                outputJson = true;
                continue;
            } else if (a=="-d" || a=="-ddc" || a=="--ddc") {
                outputJson = false;
                continue;
            } else if (a=="-v" || a=="-verbose" || a=="--verbose") {
                ddcLogLevel = GetLogLevel(av);
                ddcLogToStderr = (ddcLogLevel!=ddcLLSilent);
                argv++; argc--;
                continue;
            } else if (a=="-c" || a=="-comments" || a=="--comments") {
                outputComments = true;
                continue;
            }
            else if (a=="-noc" || a=="-nocomments" || a=="--nocomments") {
                outputComments = false;
                continue;
            }
            else if (a=="--") {
                optsDone = true;
                continue;
            }
        }
        if (!qstr.empty()) qstr.push_back(' ');
        qstr += a;
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
