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
const char *prog = "ddc_union";
string outfilename;
string optfilename;
vector<string> infilenames;

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
    ddc_thread_init("ddc_union");
    SetLogLevel(ddcLLInfo);
    ddcLogToFiles = false;
    ddcLogToSyslog = false;
    ddcLogToStderr = true;

    ArgumentParser args;
    args.SetVersion(DDCVersionStr);
    args.SetDescription("Unite DDC corpus indices");
    args.AddArgument("-v, --verbose", "log level: none|error|warn|info|debug|trace", true);
    args.AddArgument("-o, --output", "output project file (*.con)");
    args.AddArgument("-O, --options", "load the output options from this file (default: the options of the first project)", true);
    args.AddPositionalList("projects", "the DDC project files (*.con)");
    args.SetOpenStreams(false);
    args.Parse(argc, (const char **) argv);
    if (args.Exists("verbose"))
        SetLogLevel(GetLogLevel(args.Retrieve("verbose")));
    infilenames = args.RetrieveList("projects");
    outfilename = args.Retrieve("output");
    optfilename = args.Retrieve("options");

    try {
        //-- timer
        DDCTime t0 = DDCTime::Now();

        //-- ensure output directory
        MakeDirP(FileDirectory(outfilename));

        //-- create destination object
        CConcIndexator Ix;
        Ix.SetPath(outfilename);

        //-- setup output options
        string optfile_out = MakeFName(outfilename, "opt");
        if (!optfilename.empty() && optfilename != optfile_out)
            copyOptionsFile(optfilename, optfile_out);

        bool inheritOptions = !FileExists(optfile_out);
        if (!inheritOptions) {
            ddcLogInfo(Format("%s: loading target options from '%s'", prog, optfile_out.c_str()));
            Ix.LoadOptionsFromFile(optfile_out);
        }
        Ix.CreateAsUnion(infilenames, inheritOptions);

        //-- all done
        ddcLogInfo("Created project " + outfilename);
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
