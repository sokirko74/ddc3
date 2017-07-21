#!/usr/bin/perl -w

use Getopt::Long qw(:config no_ignore_case);
use File::Basename qw(dirname basename);
use strict;

my ($help);
my $numeric = 1;
my $basenames = 0;
my $packas = 'L';
GetOptions(
	   'help|h' => \$help,
	   'n|numeric' => sub { $numeric=1; },
	   'f|filenames' => sub { $numeric=!$_[1]; $basenames=0; },
	   'b|basenames' => sub { $numeric=0; $basenames=1; },
	   'p|packas|pack=s' => \$packas,
	  );

if ($help || @ARGV < 2) {
  print STDERR <<EOF;
Usage: $0 [OPTIONS] CON ATTR

 Options:
   -h, -help        # this help message
   -n, -numeric     # just print numeric file offset keys wrt CON (default)
   -f, -filenames   # print full filename keys from CON
   -b, -basenames   # print basename keys from CON
   -p, -packas PACK # pack-format for stored value offsets (default=$packas)

 Arguments:
   CON           # ddc project *.con file
   ATTR          # bibliographic metadata attribute to dump

 Output:
   TAB-separated KEY "\\t" VALUE "\\n"

EOF
  exit $help ? 0 : 1;
}

##======================================================================
## MAIN

my ($con,$attr) = @ARGV;

##-- read con-file if required
my @con = qw();
if (!$numeric) {
  print STDERR "$0: reading con-file '$con'...\n";
  open(CON,"<$con")
    or die("$0: open failed for con-file '$con': $!");
  while (defined($_=<CON>)) {
    chomp;
    push(@con,$_);
  }
  close(CON);

  ##-- map to basenames if required
  if ($basenames) {
    $_ = basename($_) foreach (@con);
  }

  print STDERR "$0: loaded ", scalar(@con), " ", ($basenames ? 'basename' : 'filename'), "(s) from '$con'\n";
}

##-- read bibl-strings
my $cbase = $con;
$cbase =~ s{\.con$}{};

my $bstrings = "$cbase._bibl_${attr}_strings";
print STDERR "$0: loading bibl-strings from '$bstrings'...\n";
open(BSTR, "<$bstrings")
  or die("$0: open failed for '$bstrings': $!");
my @bstrings = qw();
while (defined($_=<BSTR>)) {
  chomp;
  push(@bstrings,$_);
}
close(BSTR);
print STDERR "$0: loaded ", scalar(@bstrings), " possible string value(s) from '$bstrings'\n";

##-- read bibl-offsets & dump
print STDERR "$0: dumping bibl-string table for attribute '$attr'...\n";
my $bints = "$cbase._bibl_${attr}_integers";
open(BINT,"<$bints")
  or die("$0: open failed for '$bints': $!");
binmode(BINT,':raw');
my $packlen = length(pack($packas,0));
my ($buf,$boff,$nread);
my $filei=0;
while ( ($nread=read(BINT,$buf,$packlen)) != 0 ) {
  die("$0: read failed on '$bints': $!") if ($nread != $packlen);
  $boff = unpack($packas,$buf);
  print
    (($numeric ? $filei : $con[$filei]),
     "\t",
     $bstrings[$boff],
     "\n");
  ++$filei;
}
close(BINT);

print STDERR "$0: dumped $filei entries from '$bints'\n";
