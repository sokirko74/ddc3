#!/usr/bin/perl -w

use Getopt::Long qw(:config no_ignore_case);
use File::Basename qw(basename dirname);
use File::Map qw(map_file);
use strict;

##======================================================================
## Command-Line
my ($help);
my $force = 0;
GetOptions(
	   'h|help' => \$help,
	   'force|f!' => \$force,
	  );

if (!@ARGV || $help) {
  print STDERR <<EOF;

Usage: $0 [OPTIONS] DDC_TOKATTR_FILE

Options:
 -h, -help       # this help message
 -f, -force      # force-overwrite existing index (default: don't)

Description:
  Creates CORPUS._suffix_TOKATTR from CORPUS._TOKATTR

EOF
  exit 1;
}


##======================================================================
## MAIN
my $arg_file = shift;
my $arg_dir  = dirname($arg_file);
my $arg_base = basename($arg_file);
my ($ix_base,$ix_attr);
if ($arg_base =~ m{^(.*)\._(?:occ_hdr_)?(.*)$}) {
  ($ix_base,$ix_attr) = ($1,$2);
} else {
  die("$0: could not parse index filename '$arg_file'");
}

##-- relevant filenames
my $buf_file = "${arg_dir}/${ix_base}._${ix_attr}";
my $hdr_file = "${arg_dir}/${ix_base}._occ_hdr_${ix_attr}";
my $suff_file = "${arg_dir}/${ix_base}._suffix_${ix_attr}";
if (-e $suff_file && !$force) {
  die("$0: output file '$suff_file' exists: specify --force to overwrite!");
}

##-- map *._TOKATTR
my ($buf);
map_file($buf, $buf_file, '<');
die("$0: open failed to map value-file '$buf_file'") if (!defined($buf));

my $boff_end = length($buf);
sub rbufstr {
  my $boff = shift;
  my $str  = '';
  my ($c);
  for ( ; $boff < $boff_end && ($c=substr($buf,$boff,1)) ne "\0"; ++$boff ) {
    $str .= $c;
  }
  return scalar(reverse $str);
}

##-- buffer reversed-strings
open(my $hfh, "<:raw", $hdr_file)
  or die("$0: open failed for header-file '$hdr_file': $!");

my @Items=qw();
my $ItemId=0;
my $AllFlags = (1<<31);
my ($h_buf, $h_IndexItemOffsetAndFlags,$h_EndOccurOffset, $h_Offset,$h_Flags, $Item);
for ($ItemId=0; !eof($hfh); ++$ItemId) {
  read($hfh, $h_buf, 8)==8
    or die("$0: read failed for '$hdr_file' for item #$ItemId: $!");
  ($h_IndexItemOffsetAndFlags,$h_EndOccurOffset) = unpack('LL',$h_buf);

  $Items[$ItemId] = rbufstr( $h_IndexItemOffsetAndFlags & ~$AllFlags );
}
close($hfh)
  or die("$0: close failed for '$hdr_file': $!");

##-- sort item indices && dump
my @SuffIds = sort {$Items[$a] cmp $Items[$b]} (0..$#Items);
open(my $suff_fh, ">:raw", $suff_file)
  or die("$0: open failed for output file '$suff_file': $!");
print $suff_fh pack('L*',@SuffIds);
close($suff_fh)
  or die("$0: close failed for output file '$suff_file': $!");

##-- debug: dump items
#print map {"$_\t$SuffIds[$_]\t$Items[$SuffIds[$_]]\n"} (0..$#Items);
