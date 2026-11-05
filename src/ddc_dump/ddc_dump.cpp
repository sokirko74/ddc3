#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../ConcordLib/ConcHolder.h"
#include "nlp_base/common/argparse.h"

using namespace std;

//======================================================================
const char *prog = "ddc_dump";
string confilename;

bool  dump_opt  = false;
bool  dump_full = false;
CIndexDumpFormat dump_fmt = idfJson;

FILE* getOutputStream(string outfilename){
    if (outfilename == "-")
        return stdout;
    else {
        FILE* outfile = fopen(outfilename.c_str(), "wb");
        if (!outfile)
            throw CDDCExpc(errRuntime, "Error: cannot open output file `%s': %s", outfilename.c_str(), strerror(errno));
        return outfile;
    }
}

string getOutputDirectory(string outdir) {
    //-- full dump: check for dump directory
    if (outdir == "-")
        throw CDDCExpc(errRuntime, "Error: full dump requested but no output directory specified with --output");

    size_t slashpos = outdir.find_last_not_of("/");
    outdir.erase(slashpos + 1);

    struct stat s;
    if (stat(outdir.c_str(), &s)==-1) {
        if (errno == ENOENT) {
            //-- doesn't exist
            throw CDDCExpc(errRuntime, "Error: output directory `%s' does not exist", outdir.c_str());
        } else {
            //-- error during stat()
            throw CDDCExpc(errRuntime, "could not open output directory `%s': %s", outdir.c_str(), strerror(errno));
        }
    }
    else if (!S_ISDIR(s.st_mode)) {
        //-- exists but is not a directory
        throw CDDCExpc(errRuntime, "Error: invalid output directory `%s': %s", outdir.c_str(), strerror(errno));
    }
    return outdir;
}

//======================================================================
int main(int argc, char *argv[]) {
    ArgumentParser args;
    args.SetVersion(DDCVersionStr);
    args.SetDescription("Dump the metadata of a DDC corpus index");
    args.AddArgument("-o, --output", "output file or directory (default: stdout)", true);
    args.AddOption("-O, --options", "just dump PROJECT.opt");
    args.AddOption("-f, --full", "full dump, output to a directory");
    args.AddOption("-j, --json", "for a full dump: output as JSON (default)");
    args.AddOption("-t, --tabs", "for a full dump: output as TAB-separated records (aka TT)");
    args.AddOption("-T, --tabs-stream", "output the --tabs format to one file or stdout");
    args.AddOption("-b, --bibl", "bibliography only dump (default)");
    args.AddPositional("project", "the DDC project file (*.con)");
    args.SetOpenStreams(false);
    args.Parse(argc, (const char **) argv);

    confilename = args.Retrieve("project");
    string outfilename = args.Exists("output") ? args.Retrieve("output") : "-";
    dump_opt = args.Exists("options");
    dump_full = args.Exists("full") && !args.Exists("bibl");
    if (args.Exists("tabs"))
        dump_fmt = idfTabs;
    if (args.Exists("tabs-stream")) {
        dump_fmt = idfTabsStream;
        dump_full = true;
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
        else if (dump_fmt == idfTabsStream) {
            //-- full dump, stream
            FILE* outfile = getOutputStream(outfilename);
            R.m_pConcordance->DumpIndexToSingleTabFile(outfile);
            fclose(outfile);
        }
        else {
            //-- full dump, multiple files
            string output = getOutputDirectory(outfilename);
      
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
