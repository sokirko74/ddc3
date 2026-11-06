#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ConcordLib/ConcSession.h"
#include "CommonLib/ddcTime.h"
#include "CommonLib/ddcProcess.h"
#include "nlp_base/common/argparse.h"

using namespace std;

//======================================================================
const char *prog = "ddc_split";
string infilename;
string optfilename;
string outfmt = "split%02d/split%1$02d.con";
int n_splits = 2;

//--------------------------------------------------------------
void copyOptionsFile(const string &srcFile, const string &dstFile) {
    if (FileExists(dstFile))
        ddcLogWarn("copyOptionsFile(): Warning: destination file '" + dstFile + "' will be overwritten");
    if (!RmlCopyFile(srcFile.c_str(), dstFile.c_str()))
        throw CDDCExpc("copyOptionsFile(): failed to copy options options from " + srcFile + " to " + dstFile);
}

//======================================================================
int main(int argc, char *argv[]) {
    //-- command-line
    ddc_thread_init("ddc_split");
    SetLogLevel(ddcLLInfo);
    ddcLogToFiles = false;
    ddcLogToSyslog = false;
    ddcLogToStderr = true;

    ArgumentParser args;
    args.SetVersion(DDCVersionStr);
    args.SetDescription("Split a DDC corpus index");
    args.AddArgument("-v, --verbose", "log level: none|error|warn|info|debug|trace", true);
    args.AddArgument("-n, --n-corpora", "number of output corpora (default: 2)", true);
    args.AddArgument("-o, --output", "printf-style output format (default: \"split%02d/split%1$02d.con\")", true);
    args.AddArgument("-O, --options", "load the output options from this file (default: inherit)", true);
    args.AddPositional("project", "the DDC project file (*.con)");
    args.SetOpenStreams(false);
    args.Parse(argc, (const char **) argv);
    if (args.Exists("verbose"))
        SetLogLevel(GetLogLevel(args.Retrieve("verbose")));
    infilename = args.Retrieve("project");
    n_splits = args.Retrieve("n-corpora", n_splits);
    if (args.Exists("output")) outfmt = args.Retrieve("output");
    optfilename = args.Retrieve("options");

    //-- sanity check(s)
    if (n_splits > 1) {
        //-- check output format
        string out1 = Format(outfmt.c_str(), 1);
        string out2 = Format(outfmt.c_str(), 2);
        if (out1 == out2) {
            std::cerr << "Error: output format should contain at least a \"%d\" specifier\n";
            exit(1);
        }
    }


    try {
        //-- timer
        DDCTime t0 = DDCTime::Now();

        //-- load input project
        ddcLogInfo("LoadProject " + infilename);
        CConcIndexator Ix;
        Ix.LoadProject(infilename, false);

        //-- load output options
        string OutputOptions;
        if (!optfilename.empty() && !LoadFileToString(optfilename, OutputOptions))
            throw CDDCExpc(Format("%s: Error: failed to load options from '%s'", prog, optfilename.c_str()));

        //-- create output projects
        vector<CConcIndexator *> Splits(n_splits);
        for (int i = 0; i < n_splits; ++i) {
            Splits[i] = new CConcIndexator();
            Splits[i]->SetPath(Format(outfmt.c_str(), i));
        }
        Ix.SplitProject(Splits, OutputOptions);
        for (int i = 0; i < n_splits; ++i) {
            delete Splits[i];
        }
        //-- all done
        ddcLogInfo("Split project " + infilename);
        ddcLogInfo(Format("+ Total time elapsed = %.3f second(s)", DDCTime::Now().Elapsed(t0)));
        DDCProcessMemoryStatus mstat(getpid());
        ddcLogInfo(Format("+ Memory Usage (kB) = VmPeak:%zd , VmSize:%zd , VmHWM:%zd , VmRSS:%zd , VmSwap:%zd",
                          mstat.VmPeak, mstat.VmSize, mstat.VmHWM, mstat.VmRSS, mstat.VmSwap));
    }
    catch (exception &e) {
        std::cerr << prog << ": Exception: " << e.what() << "\n";
        exit(-1);
    }



    //-- cleanup
    return 0;
}
