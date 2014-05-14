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
open(LEMMATA,"<:utf8", $lemmalist)
  or die("$0: failed to open lemma-list `$lemmalist': $!");
my @lemmata = map {chomp; utf8::decode($_) if (!utf8::is_utf8($_)); s/.*\t//; $_} <LEMMATA>;
close LEMMATA;

my $i=0;
for (; 1; ++$i) {
  my $lemma = $lemmata[int(rand($#lemmata+1))];
  $lemma = quotemeta($lemma) if ($lemma =~ /\W/);

  print "$0 [$i] ", strftime("%F %H:%M:%S", localtime(time())), " $lemma ";

  if (1) {
    my $qstr    = "\$l=@".$lemma." #has[textClass,/^(?:Belletristik|Gebrauchsliteratur|Zeitung)\\b/] #sep";
    my $countby = "date/1,textClass~s/:.*//";
    my $docount = 1;
    my $rsp = $dclient->queryJson(join("\x{01}",
				       "run_query Distributed",
				       ($docount ? "count($qstr) #by[$countby]" : $qstr),
				       'json',
				       '0 '.($docount ? "1000" : 0).' 10'));
    if ($rsp->{istatus_} || $rsp->{nstatus_} || $rsp->{error_}) {
      print "ERROR: ", ($rsp->{error_}||'(unknown)'), "\n";
    } else {
      print "$rsp->{nhits_}\n";
    }
  } else {
    my $rsp = $dclient->queryJson("info");
    print (($rsp->{started}//'-undef-'), "\n");
  }

  sleep($sleep_min + int(rand($sleep_max)));
  last if ($i >= 100);
}
