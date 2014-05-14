#!/usr/bin/perl -w

use POSIX qw(strftime);
use DDC::Client::Distributed;
use open ':std',':utf8';
use utf8;

my $dclient = DDC::Client::Distributed->new(connect=>{PeerAddr=>"localhost:50290"}, mode=>'req');
$|=1;

#my $srand=0;
#srand($srand);

my $sleep_min = 0;
my $sleep_max = 0;

my $lemmalist = @ARGV ? shift : "$ENV{HOME}/www/dta-lemmadist/data/full-top-30000.1g";
my (@lemmata);
sub ensure_lemmata {
  open(LEMMATA,"<:utf8", $lemmalist)
    or die("$0: failed to open lemma-list `$lemmalist': $!");
  @lemmata = map {chomp; utf8::decode($_) if (!utf8::is_utf8($_)); s/.*\t//; $_} <LEMMATA>;
  close LEMMATA;
}

my $qmode = @ARGV ? shift : 'count';
print STDERR "$0: qmode=$qmode\n";

my $i=0;
for (; 1; ++$i) {
  print "$0 [$i] ", strftime("%F %H:%M:%S", localtime(time())), ": ";

  if ($qmode =~ /^(?:v?status|info)$/) {
    my $rsp = $dclient->queryJson($qmode);
    print (($rsp->{started}//$rsp->{version}//'-undef-'), "\n");
  }
  else {
    ##-- 'count' or default query mode
    ensure_lemmata() if ($i==0);
    my $lemma = $lemmata[int(rand($#lemmata+1))];
    $lemma = quotemeta($lemma) if ($lemma =~ /\W/);
    print "$lemma ";

    my $qstr    = "\$l=@".$lemma." #has[textClass,/^(?:Belletristik|Gebrauchsliteratur|Zeitung)\\b/] #sep";
    my $countby = "date/1,textClass~s/:.*//";
    my $rsp = $dclient->queryJson(join("\x{01}",
				       "run_query Distributed",
				       ($qmode eq 'count' ? "count($qstr) #by[$countby]" : $qstr),
				       'json',
				       '0 '.($qmode eq 'count' ? "1000" : 0).' 10'));
    if ($rsp->{istatus_} || $rsp->{nstatus_} || $rsp->{error_}) {
      print "ERROR: ", ($rsp->{error_}||'(unknown)'), "\n";
    } else {
      print "$rsp->{nhits_}\n";
    }
  }

  sleep($sleep_min + int(rand($sleep_max)));
  last if ($i >= 100);
}
