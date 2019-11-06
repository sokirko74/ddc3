//-*- Mode: C++ -*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2013-2019 by Bryan Jurish
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
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../ConcordLib/ConcHolder.h"

using namespace std;

//======================================================================
const char *prog = "ddc_dump";
const char *confilename = NULL;

bool  dump_opt  = false;
bool  dump_full = false;
CIndexDumpFormat dump_fmt = idfJson;

//--------------------------------------------------------------
void show_version(void) {
    fprintf(stderr, "%s\n", DDCVersionStr.c_str());
    fprintf(stderr, "%s: DDC corpus index metadata dumper\n", prog);
}

//--------------------------------------------------------------
void show_usage(void) {
    show_version();
    fprintf(stderr, "\n");
    fprintf(stderr, "Usage: %s [OPTIONS] CON_FILE\n", prog);
    fprintf(stderr,
            "\n"
            " Options:\n"
            "  -h, --help         # this help message\n"
            "  -v, --version      # show version and exit\n"
            "  -o, --output OUT   # specify output file or directory (default=stdout)\n"
            "  -O, --options      # just dump PROJECT.opt\n"
            "  -f, --full         # full dump, output to directory\n"
            "  -j, --json         # for full dump: output as JSON (default)\n"
            "  -t, --tabs         # for full dump: output as TAB-separated records (aka TT)\n"
            "  -b, --bibl         # bibliography only dump (default; output to file)\n"
            "  --tab-single-file  # dump tab-formatted to the file, specified by --output\n"
            "\n"
            );
}

FILE* getOutputStream(string outfilename){
    if (outfilename == "-")
        return stdout;
    else {
        FILE* outfile = fopen(outfilename.c_str(), "wb");
        if (!outfile)
            throw CExpc(errRuntime, "Error: cannot open output file `%s': %s", outfilename, strerror(errno));
        return outfile;
    }
}

string getOutputFolder(string outdir) {
    //-- full dump: check for dump directory
    if (outdir == "-")
        throw CExpc(errRuntime, "Error: full dump requested but no output directory specified with --output");

    size_t slashpos = outdir.find_last_not_of("/");
    outdir.erase(slashpos + 1);

    struct stat s;
    if (stat(outdir.c_str(), &s)==-1) {
        if (errno == ENOENT) {
            //-- doesn't exist
            throw CExpc(errRuntime, "Error: output directory `%s' does not exist", outdir.c_str());
        } else {
            //-- error during stat()
            throw CExpc(errRuntime, "could not open output directory `%s': %s", outdir.c_str(), strerror(errno));
        }
    }
    else if (!S_ISDIR(s.st_mode)) {
        //-- exists but is not a directory
        throw CExpc(errRuntime, "Error: invalid output directory `%s': %s", outdir.c_str(), strerror(errno));
    }
    return outdir;
}

//======================================================================
int main(int argc, char *argv[]) {
    string outfilename = "-";
    for (int argi = 1; argi < argc; ++argi) {
        string s = argv[argi];

        if (s == "--version" || s == "-v") {
            show_version();
            return 0;
        } else if (s == "--help" || s == "-h") {
            show_usage();
            return 0;
        } else if (s == "--output" || s == "-o") {
            ++argi;
            if (argi < argc)
                outfilename = argv[argi];
        } else if (s=="--options" || s=="-O") {
            dump_opt = true;
        } else if (s == "--full" || s == "-f") {
            dump_full = true;
        } else if (s == "--bibl" || s == "-b") {
            dump_full = false;
        } else if (s == "--json" || s == "-j") {
            dump_fmt = idfJson;
        } else if (s == "--tabs" || s == "-t" || s == "--tt") {
            dump_fmt = idfTabs;
        } else if (s == "--tab-single-file") {
            dump_fmt = idfTabsSingleFile;
        } else {
            confilename = argv[argi];
        }
    }

    //-- sanity check(s)
    if (!confilename) {
        fprintf(stderr, "Error: no con-file specified!\n");
        show_usage();
        exit(1);
    }

    //-- load project
    CConcHolder R;
    R.m_pConcordance = new CConcIndexator;

    try {
        R.m_pConcordance->LoadProject(confilename, false);

        if (dump_opt) {
            //-- option dump
            fprintf(stderr, "%s: dumping project options ...", prog);
            if (outfilename.empty()) outfilename = "-";
            R.m_pConcordance->SaveOptions(outfilename);
            fprintf(stderr, " done.\n");
        }
        else if (!dump_full) {
            //-- bibliographic dump
            FILE* outfile = getOutputStream(outfilename);
            fprintf(stderr, "%s: dumping bibliographic metadata to %s ...", prog,
                    (outfile == stdout ? "standard output" : outfilename.c_str()));
            R.m_pConcordance->DumpBibliography(outfile);
            fprintf(stderr, " done.\n");

            fclose(outfile);
        }
        else if (dump_fmt == idfTabsSingleFile) {
            FILE* outfile = getOutputStream(outfilename);
            R.m_pConcordance->DumpIndexToSingleTabFile(outfile);
            fclose(outfile);
        }
        else {
            //-- full dump
            string output = getOutputFolder(outfilename);
      
            //-- full dump: data
            fprintf(stderr, "%s: dumping index data to %s ...\n", prog, output.c_str());
            R.m_pConcordance->DumpIndex(output, dump_fmt);
            fprintf(stderr, "%s: done.\n", prog);
        }
    }
    catch (exception &e) {
        fprintf(stderr, "%s: Exception: %s\n", prog, e.what());
        exit(-1);
    }

    //-- cleanup
    delete R.m_pConcordance;
    return 0;
}


/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-default-style: "linux"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
