#!/usr/bin/perl -w

my ($y,$m,$d) = map {split(/(?<!^)\-/,$_//'0')} @ARGV; ##-- ddc >= v2.2.4: allow negative years
my $i =
#  ((($y&0xfffffe00)<<9) | (($m&0x0f)<<5) | (($d&0x1f)<<0));
#  ((($y&0xfffff)<<12) | (($m&0x0f)<<8) | (($d&0xff)<<0));
  (((($y//0)&0xffff)<<16) | ((($m//0)&0xff)<<8) | ((($d//0)&0xff)<<0)); ##-- ddc <= v2.0.8
#  ($y*10000 + $m*100 + $d);

#printf "%0.4d-%0.2d-%0.2d = %d\n", $y,$m,$d, $i;
print "$i\n";
