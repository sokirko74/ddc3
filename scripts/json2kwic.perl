#!/usr/bin/perl -w

use JSON;
use File::Basename qw(basename);
use utf8;
use open ':std', ':utf8';

BEGIN {
  binmode(STDIN,':utf8');
  binmode(STDOUT,':utf8');
}

our $txtkey = 'u'; ##-- token "text" attribute name

our ($buf);
{ local $/=undef; $buf=<>; }
our $hits = from_json($buf, {utf8=>!utf8::is_utf8($buf)})
  or die("$0: could not decode JSON buffer: $!");
$hits = $hits->{hits_} if (UNIVERSAL::isa($hits,'HASH') && $hits->{hits_});

my $useMatchIds   = grep {$_>0 && $_!=1} map {$_->[0]} map {@{$_->{ctx_}[1]}} @$hits;
my $targetMatchId = 1;

our @hits  = qw();
foreach my $hit (@$hits) {
  my $f = basename($hit->{meta_}{file_});
  $f =~ s/\..*$//;
  my $p = ($hit->{meta_}{page_}//0);
  my $pagei = (grep {$hit->{meta_}{indices_}[$_] eq 'page'}   (0..$#{$hit->{meta_}{indices_}}))[0];
  my $texti = ((grep {$hit->{meta_}{indices_}[$_] eq $txtkey} (0..$#{$hit->{meta_}{indices_}}))[0] // 0) +1;
  $texti    = 1 if (($hit->{ctx_}[1][0][$texti]//'') eq '');

  my (@l,@c,@r);
  my $ary = \@l;
  my $hl  = '__';
  foreach (map {@$_} @{$hit->{ctx_}}) {
    if    ($ary eq \@l && ref($_) && ($useMatchIds ? $_->[0]==$targetMatchId : $_->[0])) { $ary=\@c; $p=$_->[$pagei+1] if (!$p && $pagei) }
    elsif ($ary eq \@c) { $ary=\@r; }
    $hl = ($ary eq \@c ? '__' : '_');
    push(@$ary, (ref($_)
		 ? ($_->[0]
		    ? ($hl.$_->[$texti].$hl.($useMatchIds ? "/$_->[0]" : ''))
		    : $_->[$texti])
		 : $_));
  }

  push(@hits, ["$f:$p",map {join(' ',@$_)} (\@l,\@c,\@r)]);
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

  substr($l,0,length($l)-$xlen+3,'...') if ($xlen && length($l)>$xlen);
  substr($r,$xlen-3,length($r)-$xlen+3,'...') if ($xlen && length($r)>$xlen);
  #$r = substr($r,0,$xlen) if (length($r)>$xlen);
  @$_ = ($f,$l,$c,$r);
}

##-- format
our ($llen,$rlen,$xlen);
$llen=$rlen=$xlen;
$fmt = " %${flen}s: %${llen}s  %-${clen}s  %s\n";
foreach (@hits) {
  printf($fmt, @$_);
}
