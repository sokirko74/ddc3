//  DDC originally by Alexey Sokirko
//  Changes and modifications 2013-2014 by Bryan Jurish
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
const char *outfilename = NULL;
bool  dump_full = false;

//--------------------------------------------------------------
void show_version(void) {
  fprintf(stderr,"%s\n", DDCVersionStr.c_str());
  fprintf(stderr,"%s: DDC corpus index metadata dumper\n", prog);
}

//--------------------------------------------------------------
void show_usage(void) {
  show_version();
  fprintf(stderr,"\n");
  fprintf(stderr,"Usage: %s [OPTIONS] CON_FILE\n", prog);
  fprintf(stderr,
	  "\n"
	  " Options:\n"
	  "  -h, --help         # this help message\n"
	  "  -v, --version      # show version and exit\n"
	  "  -o, --output OUT   # specify output file or directory (default=stdout)\n"
	  "  -f, --full         # full dump, output to directory\n"
	  "  -b, --bibl         # bibliography only dump (default; output to file)\n"
	  "\n"
	  );
}

//--------------------------------------------------------------

//======================================================================
int main(int argc, char* argv[])
{
  //-- command-line
  for (int argi=1; argi < argc; ++argi) {
    string s = argv[argi];

    if (s=="--version" || s=="-v") {
      show_version();
      return 0;
    }
    else if (s=="--help" || s=="-h") {
      show_usage();
      return 0;
    }
    else if (s=="--output" || s=="-o") {
      ++argi;
      if (argi < argc)
	outfilename = argv[argi];
    }
    else if (s=="--full" || s=="-f") {
      dump_full = true;
    }
    else if (s=="--bibl" || s=="-b") {
      dump_full = false;
    }
    else {
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
  R.m_pIndexator = new CConcIndexator;
  if (!R.m_pIndexator->LoadProject(confilename)) {
    fprintf(stderr, "Error: cannot load project `%s'\n", confilename);
    exit(-1);
  }

  try {
    if (!dump_full) {
      //-- bibliographic dump

      //-- bibl dump: output file
      FILE *outfile = stdout;
      if (!outfilename) outfilename = "-";
      if (string(outfilename) != "-")
	outfile = fopen(outfilename,"wb");
      if (!outfile)
	throw CExpc(errRuntime, "Error: cannot open output file `%s': %s", outfilename, strerror(errno));

      //-- bibl dump: data
      fprintf(stderr, "%s: dumping bibliographic metadata to %s ...", prog, (outfile==stdout ? "standard output" : outfilename));
      R.m_pIndexator->DumpBibliography(outfile); 
      fprintf(stderr, " done.\n");

      fclose(outfile);
    }
    else {
      //-- full dump

      //-- full dump: check for dump directory
      if (!outfilename)
	throw CExpc(errRuntime,"Error: full dump requested but no output directory specified with -output");

      string outdir_s  = outfilename;
      size_t slashpos  = outdir_s.find_last_not_of("/");
      outdir_s.erase(slashpos+1);
      const char *outdir = outdir_s.c_str();

      struct stat s;
      if (stat(outdir, &s)==-1) {
	if (errno == ENOENT) {
	  //-- doesn't exist
	  throw CExpc(errRuntime,"Error: output directory `%s' does not exist", outdir);
	} else {
	  //-- error during stat()
	  throw CExpc(errRuntime,"could not open output directory `%s': %s", outdir, strerror(errno));
	}
      }
      else if(!S_ISDIR(s.st_mode)) {
        //-- exists but is not a directory
	throw CExpc(errRuntime,"Error: invalid output directory `%s': %s", outdir, strerror(errno));
      }
      
      //-- full dump: data
      fprintf(stderr, "%s: dumping index data to %s ...\n", prog, outdir);
      R.m_pIndexator->DumpIndex(outdir);
      fprintf(stderr, "%s: done.\n", prog);
    }
  }
  catch (exception &e) {
    fprintf(stderr, "%s: Exception: %s\n", prog, e.what());
    exit(-1);
  }

  //-- cleanup
  delete R.m_pIndexator;
  return 0;
}

