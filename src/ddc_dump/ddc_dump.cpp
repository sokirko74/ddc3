//  Copyright 2013 by Bryan Jurish
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
#include "../ConcordLib/ConcHolder.h"
using namespace std;

//======================================================================
const char *prog = "ddc_dump";
const char *confilename = NULL;
const char *outfilename = "-";

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
	  "  -o, --output FILE  # specify output file (default=stdout)\n"
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

  //-- output file
  FILE *outfile = stdout;
  if (string(outfilename) != "-")
    outfile = fopen(outfilename,"wb");
  if (!outfile) {
    fprintf(stderr, "Error: cannot open output file `%s': %s", outfilename, strerror(errno));
    exit(-1);
  }

  //-- load project
  CConcHolder R;
  R.m_pIndexator = new CConcIndexator;
  if (!R.m_pIndexator->LoadProject(confilename)) {
    fprintf(stderr, "Error: cannot load project `%s'\n", confilename);
    exit(-1);
  }

  //-- dump
  fprintf(stderr, "%s: dumping bibliographic metadata to %s ...", prog, (outfile==stdout ? "standard output" : outfilename));
  R.m_pIndexator->DumpBibliography(outfile); 
  fprintf(stderr, " done.\n");

  //-- cleanup
  delete R.m_pIndexator;
  return 0;
}

