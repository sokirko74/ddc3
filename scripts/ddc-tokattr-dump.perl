#!/usr/bin/perl -w

use Getopt::Long qw(:config no_ignore_case);
use File::Basename qw(basename dirname);
use File::Map qw(map_file);
use strict;

##======================================================================
## Command-Line
my ($help);
GetOptions(
	   'h|help' => \$help,
	  );

if (!@ARGV || $help) {
  print STDERR <<EOF;

Usage: $0 [OPTIONS] INDEX

Options:
 -h, -help       # this help message

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

##-- map *._TOKATTR
my $buf_file = "${arg_dir}/${ix_base}._${ix_attr}";
my ($buf);
map_file($buf, $buf_file, '<');
die("$0: open failed to map value-file '$buf_file'") if (!defined($buf));

my $boff_end = length($buf);
sub bufstr {
  my $boff = shift;
  my $str  = '';
  my ($c);
  for ( ; $boff < $boff_end && ($c=substr($buf,$boff,1)) ne "\0"; ++$boff ) {
    $str .= $c;
  }
  return $str;
}

##-- map *._occ_hdr_TOKATTR
my $hdr_file = "${arg_dir}/${ix_base}._occ_hdr_${ix_attr}";
my ($hdr);
map_file($hdr, $hdr_file, '<');
die("$0: open failed to map header-file '$hdr_file'") if (!defined($hdr));


##-- headers
my @cols = qw(ItemId ItemOffsetAndFlags ItemOffset ItemFlags EndOccurOffset Item);
print join("\t", map {"#$_"} @cols), "\n";

my $AllFlags = (1<<31);
my $hpos_end = length($hdr);
my ($hpos,$ItemId, $h_IndexItemOffsetAndFlags,$h_EndOccurOffset, $h_Offset,$h_Flags, $Item);
for ($hpos=0, $ItemId=0; $hpos < $hpos_end; $hpos += 8, ++$ItemId) {
  ($h_IndexItemOffsetAndFlags,$h_EndOccurOffset) = unpack('LL',substr($hdr,$hpos,8));

  $h_Offset = ($h_IndexItemOffsetAndFlags & ~$AllFlags);
  $h_Flags  = ($h_IndexItemOffsetAndFlags &  $AllFlags);
  $Item     = bufstr($h_Offset);
  print join("\t", $ItemId, $h_IndexItemOffsetAndFlags, $h_Offset, $h_Flags, $h_EndOccurOffset, $Item), "\n";
}
