#!/usr/bin/perl -w

use open ':std', ':encoding(utf8)';

our $tokSep = "\x{1e}";
our $fieldSep = "\x{1f}";
our $fpos = @ARGV ? shift : 0;

BEGIN {
  binmode(STDIN,':utf8');
  binmode(STDOUT,':utf8');
}

our  @hits = qw();
while (<>) {
  chomp;
  @rest=split(/\s*\#\#\#/,$_);
  $f = splice(@rest,$fpos,1) // '';
  #print STDERR "f=$f\n";
  next if (!@rest);
  $f =~ s/\..*$//;
  $f =~ s/^.*\///;

  $_ = pop(@rest);
  s/\Q$fieldSep\E[^$tokSep]*//g;
  s/(\Q$tokSep\E\s*)_\&([^$tokSep]*)/${1}_${2}_/g;
  s/\Q$tokSep\E//g;

  if (/^(.*)\&\&(\S+)(.*)/) {
    ($l,$c,$r) = ($1,$2,$3);
    push(@hits, [$f,$l,$c,$r]);
  }
}

##-- get lengths
$flen=$clen=0;

#$llen=0;
$xlen = 32;

foreach (@hits) {
  ($f,$l,$c,$r) = @$_;
  $flen = length($f) if (length($f)>$flen);
  #$llen = length($l) if (length($l)>$llen);
  $clen = length($c) if (length($c)>$clen);

  substr($l,0,length($l)-$xlen+3,'...') if (length($l)>$xlen);
  substr($r,$xlen-3,length($r)-$xlen+3,'...') if (length($r)>$xlen);
  #$r = substr($r,0,$xlen) if (length($r)>$xlen);
  @$_ = ($f,$l,$c,$r);
}

##-- format
our ($llen,$rlen,$xlen);
$llen=$rlen=$xlen;
$fmt = " %${flen}s: %${llen}s  __%-${clen}s__  %s\n";
foreach (@hits) {
  printf($fmt, @$_);
}
