#!/usr/bin/perl -w

use XML::LibXML;

BEGIN {
  *isa = \&UNIVERSAL::isa;
  *can = \&UNIVERSAL::can;
}

use utf8;
use open IO => ':encoding(utf8)';
use open IN => ':encoding(utf8)', OUT => ':encoding(utf8)';
BEGIN {
  binmode(STDIN, ':encoding(utf8)');
  binmode(STDOUT,':encoding(utf8)');
}

##======================================================================
## subs: useful aliases

## $nod_or_undef = xpnod($nod, $xpath)
sub xpnod {
  my ($ref,$xpath) = @_;
  $xpath = '.' if (!$xpath);
  return undef if (!$ref);
  my $nod = $ref->findnodes($xpath)->[0];
}

## $escaped_text = xpval($ref,$xpath,$doEscape)
sub xpval {
  my ($ref,$xpath,$escape) = @_;
  $xpath = '.' if (!$xpath);
  my $nod = xpnod($ref,$xpath);
  return '' if (!$nod);
  my $str = isa($nod,'XML::LibXML::Attr') ? $nod->value : $nod->textContent;
  $str = podescape($str) if (!defined($escape) || $escape);
  return $str;
}

## $esc = podescape($str)
sub podescape {
  my $str = shift;
  my %esc = ('<'=>'E<lt>', '>'=>'E<gt>');
  while ($str =~ m/[<>]/gp) {
    substr($str,pos($str),length(${^MATCH})) = $esc{${^MATCH}};
    pos($str) = pos($str) + length($esc{${^MATCH}})-length(${^MATCH}) if (defined(pos($str)));
  }
  $str =~ s/([^[:ascii:]])/sprintf("E<0x%x>",ord($1))/eg;
  $str =~ s/^\s+//mg;
  return $str;
}

##======================================================================
## subs

sub xml2pod {
  my $doc = shift;
  my $root = $doc->documentElement;

  ##----------------------------------------------------
  ## pod options
  print "=encoding utf8\n\n";

  ##----------------------------------------------------
  ## headers
  print
    ("=head1 ", xpval($root,'head/title'), "\n\n",
    );

  ##----------------------------------------------------
  ## main: body
  my $body = xpnod($root,'body');
  expandBodyNode($body,2);

  ##----------------------------------------------------
  ## footers
  print
    ("=head1 AUTHOR\n\n",
     xpval($root,'head/author'),
     " E<lt>", xpval($root,'head/author/@email'), "E<gt>\n\n",
     "=cut\n",
    );

  return;
}

sub expandBodyNode {
  my ($bnod,$level) = @_;
  if ($bnod->hasAttribute('title')) {
    print "=head${level} ", xpval($bnod,'@title'), "\n\n";
    $level++;
  }
  my ($nod,$name);
  foreach $nod ($bnod->childNodes) {
    if (isa($nod,'XML::LibXML::Comment')) {
      ##-- comment: skip
      ;
    }
    elsif (isa($nod,'XML::LibXML::Text')) {
      print xpval($nod);
    }
    elsif (isa($nod,'XML::LibXML::Element')) {
      $name = lc($nod->nodeName);
      if ($name eq 'body') { ; } ##-- body: ignore
      elsif ($name =~ /section$/) { expandBodyNode($nod,$level); } ##-- section: recurse
      elsif ($name eq 'rules') {
	expandRules($nod);
	;
      }
      elsif ($name eq 'table') {
	expandTable($nod);
	;
      }
      elsif ($name eq 'a') {
	my $href = xpval($nod,'@href',0);
	if (!$href) {
	  ##-- anchor: skip
	  ;
	}
	elsif ($href =~ /^\#/) {
	  ##-- local link
	  $href =~ s/^\#//;
	  print "L<", xpval($nod), "|/$href>";
	}
	else {
	  ##-- external link
	  print "B<", xpval($nod), "> (L<$href>)";
	}
      }
      elsif ($name eq 'dl' || $name eq 'ul') {
	##-- list node: recurse
	print "\n\n=over 4";
	expandBodyNode($nod,$level);
	print "=back\n\n";
      }
      elsif ($name eq 'dt') {
	##-- definition list: item
	print "\n\n=item B<", xpval($nod), ">\n\n";
      }
      elsif ($name eq 'dd') {
	##-- definition list: content
	expandBodyNode($nod,$level);
      }
      elsif ($name eq 'li') {
	##-- bullet list: item
	print "\n\n=item *\n\n";
	expandBodyNode($nod,$level);
      }
      elsif ($name eq 'p') { print xpval($nod), "\n\n"; }
      elsif ($name eq 'pre') { print preformat($nod->textContent),"\n\n"; }
      elsif ($name eq 'tt' || $name eq 'code') { print "C<", xpval($nod), ">"; }
      elsif ($name eq 'b') { print "B<", xpval($nod), ">"; }
      elsif ($name eq 'i') { print "I<", xpval($nod), ">"; }
      else {
	print STDERR "$0: unknown element '$name'\n";
	print xpval($nod);
      }
    }
  }
  print "\n\n";
}

## $str = preformat($raw)
sub preformat {
  my ($str,$indent) = @_;
  $indent = ' ' if (!defined($indent));
  my @lines = split(/\n/,$str);
  shift(@lines) if ($lines[0] eq '');
  return join("\n", map {$indent.$_} @lines);
}

## undef = expandRules($ruleNod)
sub expandRules {
  my $rroot = shift;

  ##-- get rules
  my @rules = qw();
  my ($nod,$rhsl,$rhs,$syms,$sym);
  foreach $nod (@{$rroot->findnodes('rule')}) {
    $rhsl=[];
    push(@rules,{lhs=>xpval($nod,'@lhs',0), cmt=>xpval($nod,'@cmt',0), rhs=>$rhsl});
    foreach $rhs (@{$nod->findnodes('rhs')}) {
      $syms = [];
      push(@$rhsl, {syms=>$syms,cmt=>xpval($rhs,'@cmt',0)});
      foreach $sym (grep {isa($_,'XML::LibXML::Element')} $rhs->childNodes) {
	push(@$syms, {name=>$sym->nodeName, sym=>xpval($sym,'.',0)});
      }
    }
  }

  ##-- sanity check
  return if (!@rules);

  ##-- get lengths
  my $len_l = maxlen(map {$_->{lhs}} @rules);
  my $len_r = maxlen(
		     map {
		       map {
			 join(' ', map {$_->{sym}} @{$_->{syms}})
		       } @{$_->{rhs}}
		     } @rules
		    );

  ##-- format
  printf "\n\n";
  foreach $rule (@rules) {
    printf(" %-${len_l}s %3s %-${len_r}s  /*-- %s --*/\n", $rule->{lhs}, '::=', '', ($rule->{cmt}||''));
    foreach $rhs (@{$rule->{rhs}}) {
      printf(" %-${len_l}s %3s %-${len_r}s  /* %s */\n",
	     '',
	     ($rhs eq $rule->{rhs}[0] ? '' : '|'),
	     join(' ', map {$_->{sym}||''} @{$rhs->{syms}}),
	     ($rhs->{cmt}||''),
	    );
    }
    printf(" %-${len_l}s %3s\n \n", '', ';');
  }
  print "\n";
}

## undef = expandTable($tableNod)
sub expandTable {
  my $troot = shift;

  my @rows = qw();
  my ($tr,$row,$td,$val);
  my $ncols = 0;
  foreach $tr (@{$troot->findnodes('tr')}) {
    push(@rows, ($row=[]));
    foreach $td (@{$tr->findnodes('th|td')}) {
      $val = xpval($td,'.',0);
      $val =~ s/^\s+//sg;
      $val =~ s/\s+$//sg;
      push(@$row, xpval($td,'.',0));
    }
    $ncols = @$row if (@$row > $ncols);
  }

  my ($col);
  my @clen = map {$col=$_; maxlen(map {$_->[$col]} @rows)} (0..($ncols-1));
  my $fmt = ' '.join(' ', map {"%-${_}s"} @clen)."\n";
  print "\n\n";
  foreach $row (@rows) {
    printf $fmt, @$row;
  }
  print "\n";
}


##-- util: $max = max(@vals)
sub max {
  my $max = shift;
  foreach (@_) {
    $max = $_ if (defined($_) && $_ > $max);
  }
  return $max;
}

##-- util: $maxlen = maxlen(@strs)
sub maxlen {
  return max map {defined($_) ? length($_) : qw()} @_;
}

##======================================================================
## MAIN
our $parser = XML::LibXML->new();
$parser->keep_blanks(0);
$parser->expand_entities(1);

push(@ARGV,'-') if (!@ARGV);
our $file = shift(@ARGV);
our $doc = $parser->parse_file($file)
  or die("$0: could not parse file '$file': $!");
xml2pod($doc);

