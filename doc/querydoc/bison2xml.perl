#!/usr/bin/perl -w

use XML::LibXML;

## @rules = ($rule1, ...)
## $rules[$i] = [$lhs, $rhs1, $rhs2, ...]
our @rules = qw();
our $rule = undef;

## @terms = ($terminal, ...)
our @terms = qw();

## %term2str = ($terminal=>$str
##  + terminal expansions
our %term2str =
  (
   (##-- query filters
    map {($_=>"#$_")}
    qw(CNTXT WITHIN DEBUG_RANK),
    qw(HAS_FIELD),
    qw(GREATER_BY_RANK LESS_BY_RANK),
    qw(LESS_BY_LEFT LESS_BY_RIGHT LESS_BY_MIDDLE),
    qw(GREATER_BY_LEFT GREATER_BY_RIGHT GREATER_BY_MIDDLE),
    qw(LESS_BY_SIZE GREATER_BY_SIZE IS_SIZE SIZE),
    qw(LESS_BY_DATE GREATER_BY_DATE IS_DATE),
    qw(LESS_BY GREATER_BY),
    qw(RANDOM),
   ),
   'FILENAMES_ONLY' => '#FILENAMES',
   'DOLLAR_DOT' => '$.',
   STAR_LBRACE => '*{',
   RBRACE_STAR => '}*',
   AT_LBRACE => '@{',

   ##-- literals
   (map {($_=>$_)}
    qw(WITH NEAR),
   ),

   ##-- logical operators
   'OP_AND' => '&&',
   'OP_OR'  => '||',

   ##-- yacc specials
   '$accept' => '<<ACCEPT>>',
   '$end'    => '<<EOF>>',
   'error'   => '<<ERROR>>',
  );

## @xterms: special terminals (go in '<xt>' rather than '<t>' elements)
our @xterms = (qw(SYMBOL INTEGER DATE REGEX), '$end');
our %xterms = map {($_=>undef)} @xterms;

##-- read in grammar
do { $_=<>; } while ($_ !~ /^Grammar$/);
while (defined($_=<>)) {
  chomp;
  last if (/^Terminals/);
  next if (/^\s*$/);
  if ($_ =~ /^\s*\d+\s+([^\:]+)\:\s+(.*)$/) {
    ##-- new rule
    push(@rules, $rule = [$1,$2]);
  }
  elsif ($rule && $_ =~ /^\s*\d+\s+\|\s+(.*)$/) {
    push(@$rule, $1);
  }
}

##-- read in terminals
while (defined($_=<>)) {
  chomp;
  last if (/^Nonterminals/);
  next if (/^\s/);
  if (/^\'(.)\'/) {
    push(@terms,$1);
  } elsif (/^(\S+)\s/) {
    push(@terms,$1);
  }
}

##-- expand rules: $rules[$i][$j] = [$rhs_sym1, ...]
foreach $rule (@rules) {
  foreach $ri (1..$#$rule) {
    $rhs_s = $rule->[$ri];
    my ($rhs);
    if ($rhs_s eq '/* empty */') {
      $rhs = [];
    } else {
      $rhs = [
	      map {/^\'(.)\'$/ ? $1 : $_}
	      split(/\s+/, $rhs_s)
	     ];
    }

    ##-- set rule content
    $rule->[$ri] = $rhs;
  }
}

##-- get hash list of terms, nonterms
our %terms    = map {($_=>1)} @terms;
our %nonterms = map {($_->[0]=>1)} @rules;

##-- format: doc
my $doc = XML::LibXML::Document->new('1.0','UTF-8');
my $droot = XML::LibXML::Element->new('doc');
$doc->setDocumentElement($droot);
my $dbody = $droot->addNewChild(undef,'body');

my $groot = $dbody->addNewChild(undef,'section');
$groot->setAttribute('name','grammar');
$groot->setAttribute('title','Grammar');


##-- format: rules
my $rroot = $groot->addNewChild(undef,'rules');
foreach $rule (@rules) {
  $rroot->appendChild(XML::LibXML::Comment->new("~~~~~~~~ RULES: $rule->[0] "));
  my $rnod = $rroot->addNewChild(undef,'rule');
  $rnod->setAttribute('lhs', $rule->[0]);
  foreach $rhs (@$rule[1..$#$rule]) {
    my $rrnod = $rnod->addNewChild(undef, 'rhs');
    $rrnod->setAttribute('cmt','');
    foreach $sym (@$rhs) {
      my $tn = (exists($nonterms{$sym}) ? 'n'
		: (exists($xterms{$sym}) ? 'xt'
		   : (exists($terms{$sym}) ? 't'
		      : 'u')));

      ##-- expand selected terminals
      $sym = $term2str{$sym} if (exists($term2str{$sym}));
      $rrnod->appendTextChild($tn, $sym);
    }
  }
}

##-- format: terminals
my $troot = $groot->addNewChild(undef,'terminals');
foreach $term (grep {exists($xterms{$_}) || (length($_)>1 && !$term2str{$_})} @terms) {
  my $tnod = $troot->addNewChild(undef,'term');
  $tnod->setAttribute('type', $term);
}

##-- dump doc
my $str = $doc->toString(1);
$str =~ s/^(\s*\Q<!--\E)/\n$1/mg;
print $str;
