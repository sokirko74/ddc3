#!/usr/bin/perl -w

use forks;
use DDC::Client::Distributed;
use Getopt::Long qw(:config no_ignore_case);
use Time::HiRes qw(gettimeofday tv_interval);
use POSIX qw(strftime);
use File::Basename qw(basename);
use JSON;
use open ':std'=>':utf8';
use strict;

BEGIN {
  select STDERR; $|=1;
  select STDOUT; $|=1;
}

##======================================================================
## Options
our ($help);
our $prog = basename($0);
our $server = 'localhost';
our $port   = 5200;
our $mode  = 'req';
our $check = 0;
our $debug = 0;
our $nforks = 1;
our $niters = 1;
our $reqfiles = 0;
our $limit = 10;
our $extended = 0;
our $n_serial = undef; ##-- default=$niters
our $n_threads = undef;
my $logid = 'main';

GetOptions(
	   'help|h' => \$help,
	   'server|s=s' => \$server,
	   'port|p=s' => \$port,
	   'nforks|n|forks=i' => \$nforks,
	   'niters|ni|iters|i=i' => \$niters,
	   'request|req|r' => sub { $mode='req' },
	   'query|q' => sub { $mode='json' },
	   'limit|l=i' => \$limit,
	   'files|file|f' => \$reqfiles,
	   'extended|x!' => \$extended,
	   'check|c!' => \$check,
	   'debug|d:s' => sub { $debug=($_[1] eq '' ? 1 : $_[1]); },
	   'serial|S=s' => \$n_serial,
	   'nthreads|N=i' => \$n_threads,
	  );
if ($help || !@ARGV) {
  print STDERR <<EOF;

Usage: $prog \[OPTIONS] REQUEST(s)...

Options:
  -h, -help          # this help message
  -s, -server SRV    # DDC server address (default=$server)
  -p, -port PORT     # DDC server port (default=$port)
  -n, -nforks NFORKS # number of forks to create (default=$nforks)
  -i, -niters NITERS # number of request iterations per fork (default=$niters)
  -r, -request       # request mode (default)
  -q, -query         # query mode (arguments are multiple queries)
  -l, -limit LIMIT   # query hit limit (default=$limit)
  -f, -files         # REQUEST(s) are filenames with 1 request/line
  -x, -extended      # parse C-escapes in requests (default=off)
  -c, -check         # check response consistency
  -d, -debug LEVEL?  # die on errors in check mode (LEVEL=1:die immediately, 2:wait and report:default)
  -S, -serial SERIAL # serial request processing \@TIME or ITERS (for Amdahl estimation); default=NITERS
  -N, -nthreads NTHR # number of server threads for Amdahl estimation; default=NFORKS

EOF
  exit ($help ? 0 : 1);
}

##======================================================================
## logging

sub logmsg {
  my ($sec,$usec) = (gettimeofday);
  print STDERR
    (strftime("%F %T", localtime($sec)),
     sprintf(".%0.6d", $usec),
     " ${prog}\#${logid}: ", @_, "\n");
}

##======================================================================
## debugging

## undef = jsonDump($obj, $file)
sub jsonDump {
  my ($obj,$file) = @_;
  my $buf = JSON::to_json($obj, {utf8=>1, pretty=>1, canonical=>1});
  my @toks = qw();
  while ($buf =~ /\[\n\s+[0-9+],[^\{\}\]]*\]/sg) {
    push(@toks, [$-[0],$+[0]-$-[0]]);
  }
  foreach (reverse @toks) {
    my $tok = substr($buf, $_->[0],$_->[1]);
    $tok =~ s/\s+/ /sg;
    substr($buf, $_->[0],$_->[1]) = $tok;
  }

  open(my $fh, ">$file") or die("$0: open failed for file '$file': $!");
  $fh->print($buf);
  close($fh);
}

sub jsonDumpBuf {
  return jsonDump(JSON::from_json($_[0], {utf8=>!utf8::is_utf8($_[0]), allow_nonref=>1}), $_[1]);
}

##======================================================================
## callback

## ($time,$nok) = doChild($threadid,$request,$niters,$expectResponseBuf=undef)
sub doChild {
  my ($id,$req,$niters,$expect) = @_;
  $logid = $id;
  my $cli = DDC::Client::Distributed->new(mode=>$mode, limit=>$limit, connect=>{PeerAddr=>$server,PeerPort=>$port})
    or die("${prog}#".threads->tid.": failed to create DDC::Client object");
  my ($response,$expect0,$response0);
  ($expect0 = $expect) =~ s/\"worker_\":[0-9]+/\"worker_\":null/sg if ($expect);
  my $nok = 0;
  my $t_total = 0;
  my (@t0);
  for (my $i=0; $i < $niters; ++$i) {
    @t0 = gettimeofday;
    $cli->open() or die("$0\#$id: failed to open client connection: $!");
    $response = $cli->queryRaw($req);
    $t_total += tv_interval(\@t0);
    if ($check && defined($expect)) {
      ($response0 = $response) =~ s/\"worker_\":[0-9]+/\"worker_\":null/sg;
      if (defined($response0) && $response0 eq $expect0) {
	++$nok;
      } elsif ($debug) {
	my $rsp = from_json($response, {utf8=>!utf8::is_utf8($response)});
	my $srvid = $rsp->{worker_} // '???';
	my $wrkid = $rsp->{hits_}[0]{debug_}{worker_} // '???';
	logmsg("unexpected response at iteration #$id.$i for request '$req' (server=#$srvid, sub=#$wrkid)");
	my $f_expected = "expected.$id.$i.json";
	my $f_response = "response.$id.$i.json";
	jsonDumpBuf($expect0,   $f_expected);
	jsonDumpBuf($response0, $f_response);

	kill('TERM'=>getppid()) if ($debug < 2);
	return (undef,{f_expected=>$f_expected,f_response=>$f_response,id=>$id,iter=>$i,req=>$req});
      }
    }
  }
  return ($t_total,$nok);
}

##======================================================================
## MAIN

##-- parse server string if specified as HOST:PORT
$port = $1 if ($server =~ s/\:([0-9]+)$//);

##-- get requests
my (@reqs);
if ($reqfiles) {
  logmsg "reading requests from command-line file(s)...";
  foreach my $file (@ARGV) {
     open(my $fh, "<$file") or die("$0: open failed for '$file': $!");
    binmode($fh,,':utf8');
    while (defined($_=<$fh>)) {
      next if (/^\s*\#/ || /^\s*$/);
      chomp;
      push(@reqs,$_);
    }
    close($fh);
  }
} else {
  @reqs = @ARGV;
}

##-- unescape requests
if ($extended) {
  @reqs = map { eval qq{qq($_)} } @reqs;
}
logmsg "parsed ", scalar(@reqs), " request(s)";

##-- trim requests
if (@reqs > $nforks) {
  logmsg "using only first $nforks of ", scalar(@reqs), " request(s)";
  @reqs = @reqs[0..($nforks-1)] ;
}
if (@reqs < $nforks) {
  logmsg "nrequests=", scalar(@reqs), " > nforks=$nforks : some request(s) will be re-used!";
} else {
  logmsg "using at most 1 request per fork";
}

my (@expect);

$check |= $debug;
logmsg "setting debug level = $debug";

my $cli = DDC::Client::Distributed->new(mode=>$mode, limit=>$limit, connect=>{PeerAddr=>$server,PeerPort=>$port})
  or die("${prog}: failed to create DDC::Client object");


if ($check) {
  logmsg "caching expected responses...";
  $cli->queryRaw( ["clear_cache -1"] );
  foreach (0..$#reqs) {
    $cli->open() or die("$0: failed to open client connection: $!");
    push(@expect, $cli->queryRaw($reqs[$_]));
  }
}

my ($t_serial);
$n_serial = $niters if (($n_serial//'') eq '');
if ($n_serial =~ s/^@//) {
  logmsg "setting expected serial response time = $n_serial second(s)";
  $t_serial = $n_serial;
}
elsif ($n_serial != 0) {
  logmsg "estimating expected serial response time using $n_serial iteration(s)";
  $cli->queryRaw( ["clear_cache -1"] );
  my @t_serial = map {0} (@reqs);
  foreach (0..$#reqs) {
    my ($t_child) = doChild("main", $reqs[$_], $n_serial, undef);
    $t_serial[$_] += $t_child;
  }
  logmsg "t_serial=[", join(' ', map {sprintf("%.4fs",$_)} @t_serial), "]";
  $t_serial  = 0;
  $t_serial += $t_serial[$_ % scalar(@reqs)] foreach (1..$nforks);
  logmsg "t_serial.sum=", sprintf("%.4fs",$t_serial);
  $t_serial /= ($nforks * $n_serial);
  logmsg "t_serial.req=", sprintf("%.4fs",$t_serial);
}

logmsg "clearing query cache...";
$cli->queryRaw( ["clear_cache -1"] );


##-- get total & average time
logmsg "spawning $nforks thread(s)...";
my $t0 = [gettimeofday];
my (@threads,$reqi);
for (my $i=0; $i < $nforks; ++$i) {
  $reqi = $i % scalar(@reqs);
  push(@threads, threads->create(\&doChild, $i, $reqs[$reqi], $niters, $expect[$reqi]));
}

##-- join threads
logmsg "joining ", scalar(@threads), " thread(s)...";
my $t_child = 0;
my $n_ok = 0;
foreach my $ti (0..$#threads) {
  my ($t,$nok) = $threads[$ti]->join();
  if (!defined($t)) {
    my $err = $nok;
    print "$0\#main: DEBUG: unexpected response failed for child #$err->{id}.$err->{iter}, request $err->{req}:\n";
    #system("sdiff -s -w128 $err->{f_expected} $err->{f_response}");
    system("diff -u $err->{f_expected} $err->{f_response}");
    $n_ok = -inf;
    #unlink($err->{f_expected});
    #unlink($err->{f_response});
    next;
  }
  $t_child += $t;
  $n_ok    += $nok;
}
die("$0\#main: child errors detected") if ($n_ok < 0);

my $t_parent    = tv_interval($t0);
my $t_avg_child = $t_child / ($nforks);
my $t_avg_req   = $t_child / ($nforks*$niters);

my $p_ok = $n_ok / ($nforks*$niters);

##-- report
sub labline {
  my ($lab,$val,$vfmt) = @_;
  $vfmt //= '%s';
  return sprintf("  + %-24s: ${vfmt}\n", $lab,$val);
}

##-- Amdahl's law
my $N = $n_threads // $nforks;
my $S = ($t_serial ? $t_serial*$nforks*$niters : $t_child) / $t_parent;
my $P = $N>1 ? ((1-1/$S)/(1-1/$N)): (1 - (1/$S));
print
  ("$prog summary\n",
   labline("n children", $nforks),
   labline("n iters/child", $niters),
   labline("total time (parent)", $t_parent, "%.4fs"),
   labline("total time (children)", $t_child, "%.4fs"),
   labline("average time (child)", $t_avg_child, "%.4fs"),
   labline("average time (request)", $t_avg_req, "%.4fs"),
   ($t_serial
    ? (labline("serial time (request)", $t_serial, "%.4fs"),
       labline("serial time (parent)", $t_serial*$nforks*$niters, "%.4fs"),
       labline("Amdahl N", $N, "%d"),
       labline("Amdahl S", $S, "%.2fx"),
       labline("Amdahl P",  (100 * $P), "%+.2f%%"),
      )
    : qw()),
   ($check
    ? (labline("expected responses", 100*$p_ok, "%.2f%%"))
    : qw()),
  );
