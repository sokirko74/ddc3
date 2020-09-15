#!/usr/bin/perl -w

use File::Map;

if (!@ARGV) {
  die("Usage: $0 CONFILE\n");
}


$con = shift;
$con =~ s/\.con$//i;

##-- open index
my $bxfile = "$con._bibl_idx";
my ($bxbuf);
File::Map::map_file($bxbuf, $bxfile, '<');
die("$0: ERROR: failed to mmap bibl-idx file '$bxfile' for reading: $!")
  if (!defined($bxbuf));

##-- open bibl data
my $bfile = "$con._bibl";
my ($bbuf);
File::Map::map_file($bbuf, $bfile, '<');
die("$0: ERROR: failed to mmap bibl file '$bfile' for reading: $!")
  if (!defined($bbuf));

##-- churn
my $nbibl = length($bxbuf)/8;#
my $off   = 0;
my ($end, $bitem);
for (my $fi=0; $fi < $nbibl; ++$fi) {
  $end = unpack('Q',substr($bxbuf, $fi*8, 8));
  $end = $off if (($end//0) < $off);

  $bitem = substr($bbuf, $off, $end-$off);
  $bitem =~ s/\n/ /g;
  print $bitem, "\n";

  $off = $end;
}

##-- all done
File::Map::unmap($bbuf);
File::Map::unmap($bxbuf);



