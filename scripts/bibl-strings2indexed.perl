#!/usr/bin/perl -w

use File::Basename qw(basename);
use Getopt::Long qw(:config no_ignore_case);
use strict;

my $prog = basename($0);
my $packi = 'L';
my ($help);
GetOptions(
	   'h|help' => \$help,
	   'p|pack=s' => \$packi,
	  );
if ($help || !@ARGV) {
  print STDERR <<EOF;

Usage: $prog \[OPTIONS] DDC_BIBL_STRINGS_FILE(s)...

Options:
  -h, -help       # this help message
  -p, -pack FMT   # pack-format for offsets (default=$packi)

Description:
  Converts a pre-v2.1.12 DDC bibl index string-file to
  a pair of v2.1.12 format files suitable for use
  with the MemoryMap option introduced in DDC v2.1.12:

   input:  \${PROJECT}._bibl_\${NAME}_strings
  output:  \${PROJECT}._bibl_\${NAME}_strings_values
  output:  \${PROJECT}._bibl_\${NAME}_strings_idx

EOF
}



foreach my $infile (@ARGV) {
  my $sfile  = "${infile}_values";
  my $ifile  = "${infile}_idx";
  print STDERR "$prog: $infile -> ($sfile + $ifile)\n";

  ##-- sanity checks
  #if (-e $ifile) {
  #  warn("$prog: index file '$ifile' exists: skipping conversion of '$sfile'");
  #  next;
  #}
  open(my $infh, "<$infile")
    or die("$prog: open failed for input file '$infile': $!");
  open(my $sfh, ">$sfile")
    or die("$prog: open failed for output strings file '$sfile': $!");
  open(my $ifh, ">$ifile")
    or die("$prog: open failed for output index file '$ifile': $!");

  ##-- ye olde loope
  while (defined($_=<$infh>)) {
    s/\s*\z//s;
    print $ifh pack($packi,tell($sfh));
    print $sfh $_, "\0";
  }

  ##-- cleanup
  close($infh)
    or die("$prog: close failed for input file '$infile': $!");
  close($sfh)
    or die("$prog: close failed for string output file '$sfile': $!");
  close($ifh)
    or die("$prog: close failed for index output file '$ifile': $!");
}
