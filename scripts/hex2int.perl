#!/usr/bin/perl -w

##-- hex-to-integer decoding a la utilit.cpp hex2int()
## + suitable for CConcHolder::GetHitIds(), as returned by subcorpus-server "get_first_hits"

foreach my $s (@ARGV) {
  $s =~ s/^\#//;
  my @bytes = ($s=~/[[:xdigit:]]{1,2}/g);
  $_ = hex(length($_)==2 ? $_ : "${_}0") foreach (@bytes);

  my $i = (($bytes[3]&0xff)
	   | ($bytes[2]&0xff)<<8
	   | ($bytes[1]&0xff)<<16
	   | ($bytes[0]&0x7f)<<24
	  );
  $i = -$i if (!($bytes[0] & 0x80));
  print "$i\n";
}
