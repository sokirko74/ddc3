#!/usr/bin/perl -w

##-- integer-to-hex encoding a la utilit.cpp int2hex()
## + simulates ddc CConcHolder::GetHitIds(), as used by subcorpus-server "get_first_hits"

foreach my $i (@ARGV) {
  my $sgn = $i < 0 ? 0 : 1;
  $i = -$i if (!$sgn);
  printf("#%02x%02x%02x%02x\n",
	 ($sgn<<7)|(($i>>24)&0x7f),
	 ($i>>16)&0xff,
	 ($i>> 8)&0xff,
	 ($i)&0xff,
	);
}
