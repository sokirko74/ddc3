#!/usr/bin/perl -w

my $i = shift || 0;
my ($y,$m,$d) = map { ($i>>$_->[0])&$_->[1] } (
					       #[9,0xfffffe00],[5,0x0f],[0,0x1f],
					       #[12,0xfffff],[8,0x0f],[0,0xff],
					       [16,0xffff],[8,0xff],[0,0xff], ##-- ddc <= v2.0.8
					       #  ($y*10000 + $m*100 + $d);
					      );
$y = unpack('s',pack('S',$y)); ##-- ddc >= v2.2.4: signed years


#printf "%d = %0.4d-%0.2d-%0.2d\n", $i, $y,$m,$d;
printf "%0.4d-%0.2d-%0.2d\n", $y,$m,$d;
