//  DDC originally by Alexey Sokirko
//  Changes and modifications 2013-2018 by Bryan Jurish
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
#include "../ConcordLib/ConcSession.h"
#include "../CommonLib/ddcTime.h"
using namespace std;

//======================================================================
const char *prog = "ddc_split";
string infilename;
string optfilename;
string outfmt = "split%02d/split%1$02d.con";
int    n_splits = 2;

//--------------------------------------------------------------
void show_version(void) {
  fprintf(stderr,"%s\n", DDCVersionStr.c_str());
  fprintf(stderr,"%s: DDC corpus index split\n", prog);
}

//--------------------------------------------------------------
void show_usage(void) {
  show_version();
  fprintf(stderr,"\n");
  fprintf(stderr,"Usage: %s [OPTIONS] CON_FILE\n", prog);
  fprintf(stderr,
	  "\n"
	  " Options:\n"
	  "  -h, --help            # this help message\n"
	  "  -n, --n-corpora N     # number of output corpora (default=2)\n"
	  "  -o, --output OUTFMT   # specify printf-style output format (default=\"split%%02d/split%%1$02d.con\")\n"
	  "  -O, --options OPTFILE # load output options from OPTFILE (default:empty ~ inherit)\n"
	  "  -v, --verbose LEVEL   # specify log-verbosity level (none|error|warn|info=weak|debug=medium|trace=heavy)\n"
	  "\n",
	  outfmt.c_str()
	  );
}

//--------------------------------------------------------------
void copyOptionsFile(const string& srcFile, const string &dstFile)
{
  if (FileExists(dstFile))
    ddcLogWarn("copyOptionsFile(): Warning: destination file '"+dstFile+"' will be overwritten");
  if (!RmlCopyFile(srcFile.c_str(), dstFile.c_str()))
    throw CExpc("copyOptionsFile(): failed to copy options options from "+srcFile+" to "+dstFile);
}

//======================================================================
int main(int argc, char* argv[])
{
  //-- command-line
  ddc_thread_init("ddc_split");
  SetLogLevel(ddcLLInfo);
  ddcLogToFiles = false;
  ddcLogToSyslog = false;
  ddcLogToStderr = true;

  for (int argi=1; argi < argc; ++argi) {
    string s = argv[argi];

    if (s=="--help" || s=="-h") {
      show_usage();
      return 0;
    }
    else if (s=="--n-corpora" || s=="-n") {
      ++argi;
      if (argi < argc)
	n_splits = strtol(argv[argi],NULL,0);
    }
    else if (s=="--output" || s=="--outfmt" || s=="-o") {
      ++argi;
      if (argi < argc)
	outfmt = argv[argi];
    }
    else if (s=="--options" || s=="--opt" || s=="-O") {
      ++argi;
      if (argi < argc)
	optfilename = argv[argi];
    }
    else if (s == "--verbose" || s == "-verbose" || s=="-v" || s=="--log-level" || s=="--log" || s=="--protocol") {
      if (argi+1 >= argc) {
	show_usage();
	exit(1);
      }
      SetLogLevel( GetLogLevel(argv[argi+1]) );
      argi++;
    }
    else if (!infilename.empty()) {
      fprintf(stderr, "Error: multiple input files specified!\n");
      show_usage();
      exit(1);
    }
    else {
      infilename = argv[argi];
    }
  }

  //-- sanity check(s)
  if (infilename.empty()) {
    fprintf(stderr, "Error: no input con-file specified!\n");
    show_usage();
    exit(1);
  }
  if (n_splits > 1) {
    //-- check output format
    string out1 = Format(outfmt.c_str(),1);
    string out2 = Format(outfmt.c_str(),2);
    if (out1 == out2) {
      fprintf(stderr, "Error: output format should contain at least a \"%%d\" specifier\n");
      show_usage();
      exit(1);
    }
  }

 
  try {
    //-- timer
    DDCTime t0 = DDCTime::Now();

    //-- load input project
    ddcLogInfo("LoadProject "+infilename);
    CConcIndexator Ix;
    if (!Ix.LoadProject(infilename, false))
      throw CExpc(Format("%s: failed to load input project '%s'", prog, infilename.c_str()));

    //-- load output options
    string OutputOptions;
    if (!optfilename.empty() && !LoadFileToString(optfilename,OutputOptions))
      throw CExpc(Format("%s: Error: failed to load options from '%s'", prog, optfilename.c_str()));

    //-- create output projects
    vector<CConcIndexator> Splits(n_splits);
    for (int i=0; i < n_splits; ++i) {
      Splits[i].SetPath( Format(outfmt.c_str(),i) );
    }
    Ix.SplitProject(Splits, OutputOptions);

    //-- all done
    ddcLogInfo("Split project "+infilename);
    ddcLogInfo(Format("+ Total time elapsed = %.3f second(s)", DDCTime::Now().Elapsed(t0)));
    DDCProcessMemoryStatus mstat(getpid());
    ddcLogInfo(Format("+ Memory Usage (kB) = VmPeak:%zd , VmSize:%zd , VmHWM:%zd , VmRSS:%zd , VmSwap:%zd",
		      mstat.VmPeak, mstat.VmSize, mstat.VmHWM, mstat.VmRSS, mstat.VmSwap));
  }
  catch (exception &e) {
    fprintf(stderr, "%s: Exception: %s\n", prog, e.what());
    exit(-1);
  }



  //-- cleanup
  return 0;
}

