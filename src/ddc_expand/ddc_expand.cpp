//-*- Mode: C++; c-basic-offset: 4; -*-
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2014 by Bryan Jurish
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <locale.h>

#include "../ConcordLib/ConcCommon.h"
#include "../ConcordLib/TermExpander.h"

//-- suppress gcc warnings of the form "ignoring return value of `fread', declared with attribute warn_unused_result [-Wunused-result]"
#pragma GCC diagnostic ignored "-Wunused-result"

const char *prog = "ddcExpand";
CTermExpander *tx = NULL;
TxChain       txc;
TxDispatcher  txd;

void PrintUsage()
{
    printf("\n"
	   "Usage: %s [OPTIONS] [INPUT...]\n", prog);
    printf("\n"
	   "Options:\n"
	   "  -h         ##-- this help message\n"
	   "  -c CLASS   ##-- set expander class (default='Morph')\n"
	   "  -l LABEL   ##-- set expander label (default='')\n"
	   "  -p PARAM   ##-- set expander parameter string (default='')\n"
	   "  -f CONFIG  ##-- parse config file (default=none)\n"
	   "  -w         ##-- if given, INPUT(s) are words to analyze, otherwise files\n"
	   "\n"
	   "Examples:\n"
	   "  ddcExpand -c Case file.txt\n"
	   "  ddcExpand -c Case -\n"
	   "  ddcExpand -c Morph -p German -w sein\n"
	   "  ddcExpand -c cab -p 'http://localhost:9099/query/?a=expand&fmt=xl' -w sein\n"
	   "  ddcExpand -f config.txt\n"
	   "\n"
	   "Interactive mode:\n"
	   "  Type #h [ENTER] for help\n"
	   "\n"
	   );
    exit(-1);	
};

void expand(const set<string> &src)
{
    set<string> dst;
    tx->expand(src, dst);
    for (set<string>::const_iterator xi=dst.begin(); xi!=dst.end(); xi++) {
	fputs(xi->c_str(), stdout);
	fputc('\t', stdout);
    }
    fputc('\n',stdout);
    fflush(stdout);
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
	fprintf(stderr, "%s: open failed for config file %s: %s", prog, txfile.c_str(), strerror(errno));
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
	fprintf(stderr, "Exception: %s\n", e.what());
    }
}

int main(int argc, char **argv)
{
    //---- command-line params
    prog=*argv;

    string txfile("");
    string txclass("Id");
    string txlabel("Token");;
    string txparam;
    bool fileMode = true;
    vector<string> inputs;
    for (argv++,argc--; argc > 0; argv++,argc--) {
	string p = argc > 1 ? string(*(argv+1)) : string("");
	if (strcmp(*argv,"-h")==0) { PrintUsage(); }
	else if (strcmp(*argv,"-c")==0) {
	    txclass=p;
	    argv++; argc--;
	}
	else if (strcmp(*argv,"-l")==0) {
	    txlabel=p;
	    argv++; argc--;
	}
	else if (strcmp(*argv,"-p")==0) {
	    if (!txparam.empty()) txparam.push_back(' ');
	    txparam.append(p);
	    argv++; argc--;
	}
	else if (strcmp(*argv,"-f")==0) {
	    txfile=p;
	    argv++; argc--;
	}
	else if (strcmp(*argv,"-w")==0) { fileMode=false; }
	else {
	    inputs.push_back(string(*argv));
	}
    }

    //---- load dicts
    printf ("%s: Loading...\n", prog);
    InitConcordDicts();

    //-- load config file
    if (!txfile.empty()) {
	loadTxFile(txfile);
	txd.ensureDefaultExpanders(morphGeneric);
	txd.compile();
	fprintf(stderr, "%s: loaded dispatcher file `%s':\n%s\n", prog, txfile.c_str(), txd.configString("> ").c_str());
	fflush(stderr);
    }
    else {
	//-- create new expander
	tx = newTermExpander(txclass, txlabel, txparam);
	if (!tx) {
	    fprintf(stderr, "%s: could not create term expander of class `%s'\n", prog, txclass.c_str());
	    exit(-1);
	}
	tx->compile();
	txd.insert(tx);
	fprintf(stderr, "%s: created term expander [%s]\n", prog, tx->configString().c_str());
	fflush(stderr);
    }
    selectChain(txlabel);
    fprintf(stderr, "%s: using expander [%s]\n", prog, tx->configString().c_str());

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
		fprintf(stderr, "%s: open failed for input file %s: %s", prog, infilename.c_str(), strerror(errno));
		exit(-1);
	    }
	    if (infilename.empty()) {
		fprintf(stderr, "%s: type #h [ENTER] for help\n", prog);
	    }

	    //---- guts
	    while (!feof(infile)) {
		if (infilename.empty()) {
		    printf("%s:[%s]> ", prog, tx->configString().c_str());
		    fflush(stdout);
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
			    fprintf(stderr, "%s: could not parse expander spec `%s'\n", prog, arg.c_str());
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
			fputs(txd.configString("\t").c_str(),stdout);
			continue;
		    }
		    else if (op == "#quit" || op == "#exit" || op=="#q") {
			fputc('\n',stdout);
			break;
		    }
		    else if (op == "#help" || op == "#h") {
			printf("%s: interactive mode commands\n", prog);
			printf("  #help                         : this help message\n"
			       "  #define LABEL [CLASS [PARAM]] : define a new expander\n"
			       "  #set    LABEL...              : select a new expansion chain\n"
			       "  #list                         : list current expanders\n"
			       "  #quit                         : quit the program\n"
			       "\n"
			       " Known expander classes and parameters:\n"
			       "  CLASS   PARAM         DESCRIPTION\n"
			       //"  -----------------------------------------------------------------------------\n"
			       "  Id      (none)        Identity map\n"
			       "  Case    LANG          Letter-case tweaker\n"
			       "  ToLower LANG          Force to lower-case\n"
			       "  ToUpper LANG          Force to upper-case\n"
			       "  Infl    LANG          Lemmatizer + re-inflection (morphy)\n"
			       "  Cab     URL TIMEOUT   External DTA::CAB server\n"
			       "\n");
		    }
		}

		StringTokenizer stok(s.c_str(), "\t\r\n");
		set<string> src, dst;
		while (stok()) {
		    src.insert(stok.val());
		}
		if (src.empty()) {
		    if (!infilename.empty()) printf("\n");
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





