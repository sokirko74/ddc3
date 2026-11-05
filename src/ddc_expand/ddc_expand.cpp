#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <locale.h>

#include "../ConcordLib/ConcCommon.h"
#include "../ConcordLib/TermExpander.h"
#include "nlp_base/common/argparse.h"

using namespace std;

//-- suppress gcc warnings of the form "ignoring return value of `fread', declared with attribute warn_unused_result [-Wunused-result]"
#pragma GCC diagnostic ignored "-Wunused-result"

const char *prog = "ddc_expand";
CTermExpander *tx = NULL;
TxChain       txc;
TxDispatcher  txd;


void expand(const set<string> &src)
{
    for (const string& w : src)
        if (!IsValidUtf8(w)) {
            std::cerr << prog << ": the input is not valid UTF-8 (ddc accepts only UTF-8): " << w << "\n";
            return;
        }
    set<string> dst;
    tx->expand(src, dst);
    for (const auto &x : dst)
        std::cout << x << '\t';
    std::cout << std::endl;
}
void expand(const string &s)
{
    set<string> tmp;
    tmp.insert(s);
    expand(tmp);
}

#define TX_BUFSIZE 8192
void loadTxFile(const string &txfile)
{
    FILE *f = fopen(txfile.c_str(),"r");
    if (!f) {
        std::cerr << prog << ": open failed for config file " << txfile << ": " << strerror(errno);
        exit(-1);
    }
    while (!feof(f)) {
        char buffer[TX_BUFSIZE];
        fgets(buffer, TX_BUFSIZE, f);
        if (feof(f)) break;
        string s(buffer);
        Trim(s);
        if (s.empty()) continue;
        txd.addExpander(s);
    }
    fclose(f);
}

void selectChain(const string& chainSpec="Token")
{
    //-- get user-specified chain
    try {
        txc = txd.getChain(chainSpec);
        if (txc.m_Chain.size()==1) tx = txc.m_Chain[0];
        else tx = &txc;
    }
    catch (exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

int main(int argc, char **argv)
{
    ddcLogToFiles = false;
    //---- command-line params
    prog=*argv;

    //-- debug: logging
    ddcLogToStderr = true;
    ddcLogLevel    = ddcLLWarn;

    ArgumentParser args;
    args.SetVersion(DDCVersionStr);
    args.SetDescription("Expand terms with a DDC term expander");
    args.AddArgument("-v, --verbose", "log level: none|error|warn|info|debug|trace", true);
    args.AddArgument("-c, --class", "expander class (default: Id)", true);
    args.AddArgument("-l, --label", "expander label (default: Token)", true);
    args.AddArgument("-p, --param", "expander parameter string (several are joined with a space)", true, true);
    args.AddArgument("-f, --config", "a config file with expanders", true);
    args.AddOption("-w, --words", "the inputs are words to expand, not files");
    args.AddPositionalList("inputs", "input files ('-' for stdin) or words (with --words); none: interactive mode", true);
    args.SetEpilog("Examples:\n"
           "  ddc_expand -c Case file.txt\n"
           "  ddc_expand -c Case -\n"
           "  ddc_expand -c Morph -p German -w sein\n"
           "  ddc_expand -c cab -p 'http://localhost:9099/query/?a=expand&fmt=xl' -w sein\n"
           "  ddc_expand -c cab -p 'http+unix:/tmp/cab-xlit.sock//query/?a=expand&fmt=xl' -w sein\n"
           "  ddc_expand -f config.txt\n"
           "\n"
           "Interactive mode:\n"
           "  Type #h [ENTER] for help");
    args.SetOpenStreams(false);
    args.Parse(argc, (const char **) argv);
    if (args.Exists("verbose")) {
        ddcLogLevel = GetLogLevel(args.Retrieve("verbose"));
        ddcLogToStderr = (ddcLogLevel!=ddcLLSilent);
    }

    string txfile = args.Retrieve("config");
    string txclass = args.Exists("class") ? args.Retrieve("class") : "Id";
    string txlabel = args.Exists("label") ? args.Retrieve("label") : "Token";
    string txparam;
    for (auto &p : args.RetrieveList("param")) {
        if (!txparam.empty()) txparam.push_back(' ');
        txparam.append(p);
    }
    bool fileMode = !args.Exists("words");
    vector<string> inputs = args.RetrieveList("inputs");

    //---- load dicts
    std::cout << prog << ": Loading...\n";
    InitConcordDicts();

    //-- load config file
    if (!txfile.empty()) {
        loadTxFile(txfile);
        txd.ensureDefaultExpanders(morphGeneric);
        txd.compile();
        std::cerr << prog << ": loaded dispatcher file `" << txfile << "':\n" << txd.configString("> ") << "\n";
    }
    else {
        //-- create new expander
        tx = newTermExpander(txclass, txlabel, txparam);
        if (!tx) {
            std::cerr << prog << ": could not create term expander of class `" << txclass << "'\n";
            exit(-1);
        }
        tx->compile();
        txd.insert(tx);
        std::cerr << prog << ": created term expander [" << tx->configString() << "]\n";
    }
    selectChain(txlabel);
    std::cerr << prog << ": using expander [" << tx->configString() << "]\n";

    if (!fileMode) {
        //-- process command-line arguments
        for (vector<string>::iterator ii=inputs.begin(); ii != inputs.end(); ii++) {
            expand(*ii);
        }
    }
    else {
        //-- process files
        if (inputs.empty()) inputs.push_back(string(""));
        for (vector<string>::iterator ii=inputs.begin(); ii != inputs.end(); ii++) {
            string &infilename = *ii;
            FILE *infile = infilename.empty() || infilename==string("-") ? stdin : fopen(infilename.c_str(),"r");
            if (!infile) {
                std::cerr << prog << ": open failed for input file " << infilename << ": " << strerror(errno);
                exit(-1);
            }
            if (infilename.empty()) {
                std::cerr << prog << ": type #h [ENTER] for help\n";
            }

            //---- guts
            while (!feof(infile)) {
                if (infilename.empty()) {
                    std::cout << prog << ":[" << tx->configString() << "]> " << std::flush;
                }
                char buffer[TX_BUFSIZE];
                fgets(buffer, TX_BUFSIZE, infile);
                string s = buffer;
                Trim(s);
                if (feof(infile)) break;

                //-- check for special commands
                if (s[0]=='#') {
                    size_t argpos = s.find_first_of(" \t\n\r");
                    string op(s,0,argpos);
                    string arg;
                    if (argpos != s.npos) arg = s.substr(argpos);
                    if (!arg.empty()) Trim(arg);
                    if (op == "#define" || op == "#def") {
                        CTermExpander *tx_ = txd.addExpander(arg);
                        if (!tx_) {
                            std::cerr << prog << ": could not parse expander spec `" << arg << "'\n";
                            exit(-1);
                        }
                        tx->compile();
                        selectChain(tx_->m_Label);
                        continue;
                    }
                    else if (op == "#set" || op == "#select" || op == "#chain") {
                        selectChain(arg);
                        continue;
                    }
                    else if (op == "#list" || op == "#ls" || op=="#dump") {
                        std::cout << txd.configString("\t");
                        continue;
                    }
                    else if (op == "#quit" || op == "#exit" || op=="#q") {
                        std::cout << '\n';
                        break;
                    }
                    else if (op == "#help" || op == "#h") {
                        std::cout << prog << ": interactive mode commands\n";
                        std::cout << "  #help                         : this help message\n  #define LABEL [CLASS [PARAM]] : define a new expander\n  #set    LABEL...              : select a new expansion chain\n  #list                         : list current expanders\n  #quit                         : quit the program\n\n Known expander classes and parameters:\n  CLASS   PARAM         DESCRIPTION\n  Id      (none)        Identity map\n  Case    LANG          Letter-case tweaker\n  ToLower LANG          Force to lower-case\n  ToUpper LANG          Force to upper-case\n  Infl    LANG          Lemmatizer + re-inflection (morphy)\n  Cab     URL TIMEOUT   External DTA::CAB server\n\n";
                    }
                }

                StringTokenizer stok(s.c_str(), "\t\r\n");
                set<string> src, dst;
                while (stok()) {
                    src.insert(stok.val());
                }
                if (src.empty()) {
                    if (!infilename.empty()) std::cout << "\n";
                    continue;
                }
                expand(src);
            }
            if (infile != stdin) fclose(infile);
        }
    }

    FreeConcordDicts();
    return 0;
}
