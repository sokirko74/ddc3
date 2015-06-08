#!/usr/bin/perl -w

## File: remove_empty_breaks.perl
## Author: Bryan Jurish <moocow@cpan.org>
## Description:
##  + remove empty "borders" (aka "breaks", e.g. sentences) from an existing ddc index
## Usage:
##  $ BORDERS=c4_chtk_utf8._s_border
##  $ mv $BORDERS $BORDERS.orig
##  $ perl remove_empty_borders.perl $BORDERS.orig > $BORDERS

use Getopt::Long;
use strict;

##======================================================================
## Command-Line
my ($help,$force);
my $backup = '.orig';
GetOptions('help|h' => \$help,
	   'backup|bak|b=s' => \$backup,
	   'nobackup|nobak|nob' => sub { $backup=''; },
	   'force|f' => \$force,
	  );

if ($help || !@ARGV) {
  print STDERR <<EOF;

Usage $0 [OPTIONS] PROJECT.con

 Options:
    -help           # this help message
    -backup=SUFFIX  # backup original files as \${FILE}\${SUFFIX} (default=.orig)
    -nobackup       # don't backup original files at all
    -[no]force      # force-remove any old backup files (default=don't)

 Description:
   Removes empty "borders" aka "breaks" (e.g. sentences) from an existing ddc index.

EOF
  exit $help ? 0 : 1;
}

##======================================================================
## MAIN

my $confile = shift;
$confile =~ s/\.con$//i;

my @bfiles = glob("${confile}._*_border");
foreach my $bfile (@bfiles) {
  print STDERR "$0: processing $bfile... ";

  ##-- slurp data
  open(BFILE,"<$bfile") or die("$0: ERROR: failed to open '$bfile' for reading: $!");
  my $size0 = (-s $bfile);
  my $data;
  local $/ = undef;
  $data = <BFILE>;
  close(BFILE) or die("$0: ERROR: close failed for '$bfile': $!");

  ##-- make backup if required
  if ($backup) {
    if (-e "$bfile$backup") {
      die("$0: ERROR: backup file '$bfile$backup' exists; specify -force to overwrite") if (!$force);
      unlink("$bfile$backup") or die("$0: ERROR: failed to remove stale '$bfile$backup': $!");
    }
    rename($bfile, "$bfile$backup")
  }

  ##-- write new file
  open(BFILE,">$bfile") or die("$0: ERROR: failed to open new '$bfile' for writing: $!");
  my $prev=-1;
  print BFILE pack('L*',
		   map { $prev==$_ ? qw() : ($prev=$_) }
		   unpack('L*', $data)
		  );
  close(BFILE) or die("$0: ERROR: failed to close new '$bfile': $!");

  ##-- report
  print STDERR "removed ", (($size0 - (-s $bfile)) / 4), " of ", ($size0/4), " break(s).\n";
}
print STDERR "$0: done.\n";
