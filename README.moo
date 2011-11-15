##-*- Mode: Shell-Script -*-

Tue, 03 May 2011 15:57:41 +0200 (moocow)
 + managed to build ddc from (this) source on linux (debian squeeze, 32bit) using the following procedure:

##-- checkout
$ svn co svn+ssh://moocow@odo.dwds.de/home/svn/dev/ddc/trunk ddc
$ cd ddc

##-- set annoying environment variables
$ export RML=$PWD
$ export RML_PCRE_INCLUDE=/usr/include ##-- annoying (libpcre3-dev=8.02-1.1 installed)
$ export RML_PCRE_LIB=/usr/lib         ##-- annoying (make breaks b/c of dangling -L flag otherwise)

##-- compile basic package
$ ./compile_concord.sh
$ ./gen_graphan_bin.sh German
$ ./gen_graphan_bin.sh Russian
$ ./compile_morph.sh
$ ./generate_morph_bin.sh German
$ ./generate_morph_bin.sh English
$ ./generate_morph_bin.sh Russian

##-- now at least ./Bin/ConcordConsole starts up without errors

##--------------------------------------------------------------
## autotool-ification
##  + re-factored sources from Source/*/* to src/*
##  + lump all sources together and let automake take care
##    of dependencies
##  + libtool libraries instead of static
##  + distribution targets probably broken for now

##----- PREREQUISITES / build trace
./compile_concord.sh:
# + ConcordIndex
#   + ConcordLib/libConcord
#    + GraphanLib/libGraphan
#    + StructDictLib/libStructDict
#    + LemmatizerLib/libLemmatizer
#    + AgramtabLib/libAgramtab
#    + tinyxml/libTinyXml
#    + RmlTar/libRmlTar
#    + MorphWizardLib/libMorphWizard
#  + ConcordSimple
#  + ConcordConsole
#  + ConcordDaemon
#  + Search
#  + ddc_xml
#  + ./gen_graphan_bin.sh Russian
#    + ./compile_ross.sh Obor
#      + make -C src/StructDictLoader
#      + Bin/StructDictLoader FromTxt Dicts/$1/ross.txt Dicts/$1
#  + ./gen_graphan_bin.sh German
#    + ./compile_ross.sh GerObor
#+ ./compile_morph.sh
#  + make -C src/MorphGen
#  + make -C src/TestLem
#  + make -C src/FileLem
#  + ./gen_graphan_bin.sh Russian
#  + ./gen_graphan_bin.sh German
#  + echo "try generate_morph_bin.sh"
#+ ./generate_morph_bin.sh $lang ##-- for $lang in qw(German English Russian)
#  + require $RML
#  + require compile_morph.sh (MorphGen)
#  + require Dicts/SrcMorph/$lang.mwz
#    + echo "Error: you should first download and install the morphological dictionary (http://sf.net/projects/morph-lexicon/)"
#  + compile: $RML/Source/MorphGen/MorphGen Dicts/SrcMorph/$lang.mwz Dicts/Morph/$lang 5 3
#~  + test: Bin/TestLem $1 <Test/Morph/$lang/test.txt  >test.tem
#~  + test: cmp test.temp Test/Morph/$lang/result.txt
#~  + manual test: Bin/TestLem $lang

##--------------------------------------------------------------
## install

+ ConcordConsole
  - require $RML/Dicts/Morph/{Rus,Eng,Ger}/{morph.forms_autom,morph.annot,npredict.bin}
+ ConcordIndex
  - require $RML/Dicts/GraphAn/{space.dic,enames.txt,idents.txt,keyboard.txt,extensions.txt}
  - require/Russian: REG("Software\\Dialing\\Obor\\DictPath") = $RML/Dicts/Obor
  - require/German:  REG("Software\\Dialing\\GerObor\\DictPath") = $RML/Dicts/GerObor
    * $RML/Dicts/GerObor/{*.txt,*.bin}

##--------------------------------------------------------------
## I/O formats

ConcordLib/ConcHolder.cpp:1514: CConcHolder::SetResultFormat(string ResultTypeStr)
 ##-- e.g. Holder.SetResultFormat("table");
 : just sets m_ResultFormat = GetResultFormatByString(ResultTypeStr);

ConcordLib/ConcHolder.cpp:1498: CConcHolder::FormatTypeEnum CConcHolder::GetResultFormatByString(const string& ResultTypeStr )
##-- hacked: added DDC_ResultJson

##-- actual hit-local generation in

ConcordLib/ConcHolder.cpp:1260: DDCErrorEnum CConcHolder::GetHits(string Query,  DWORD& EndHitNo) 
ConcordLib/ConcHolder.cpp:438: bool CConcHolder::GenerateOneHitString(DWORD PageNumber, const CHit& Hit, const vector<COutputToken>& Tokens)

##-- now working on drop-in replacement
#  bool CConcHolder::GenerateOneHitStringJson(DWORD PageNumber, const CHit& Hit, const vector<COutputToken>& Tokens)
#  : need to wrap context-generation
#  : original call(s):
#     LEFT:      GetContext((int)Hit.m_BreakNo-(int)m_pQueryEvaluator->m_ContextSentencesCount, Hit.m_BreakNo,  Hit.m_FileNo,  bConvASCIIToHtml, LeftContext )
#     MID/html:  BuildHtmlHitStrWithHighlighting(Tokens, bConvASCIIToHtml, m_pIndexator->m_HtmlHighlighting, true);
#     MID/text:  BuildHtmlHitStrWithHighlighting(Tokens, bConvASCIIToHtml, m_pIndexator->m_TextHighlighting, false);
#     MID/table: "<s part=\"m\">"+ BuildHtmlHitStrWithHighlighting(Tokens,bConvASCIIToHtml, CHighlightTags(), false) + "</s>";
#     RIGHT:     GetContext(Hit.m_BreakNo+1, Hit.m_BreakNo+m_pQueryEvaluator->m_ContextSentencesCount+1, Hit.m_FileNo, bConvASCIIToHtml, RightContext )

##-- ugly regex stuff: /(?i:sapere)/ matches just about everything from '30sten' to 'Abgerupft' to ...
## + culprit search (backtrace)

#0  RML_RE::TryMatch (this=0xbfffe2ac, text=..., startpos=0, anchor=RML_RE::UNANCHORED, vec=0xbfffe0ec, vecsize=51) at ../PCRE/pcre_rml.cpp:475
#1  0x080b9d45 in RML_RE::DoMatchImpl (this=0xbfffe2ac, text=..., anchor=RML_RE::UNANCHORED, consumed=0xbfffe1f8, args=0xbfffe1b8, n=0, vec=0xbfffe0ec, vecsize=51) at ../PCR/pcre_rml.cpp:521
#2  0x080b9227 in RML_RE::PartialMatch (this=0xbfffe2ac, text=..., ptr1=..., ptr2=..., ptr3=..., ptr4=..., ptr5=..., ptr6=..., ptr7=..., ptr8=..., ptr9=..., ptr10=..., ptr11=..., ptr12=..., ptr13=..., ptr14=..., ptr15=..., ptr16=...) at ../PCRE/pcre_rml.cpp:295
#3  0x0809284b in CStringIndexSet::QueryTokenListUsingRegExp (this=0x821c6a0, RegExp=..., MatchWords=...) at IndexSet.cpp:84
#4  0x080c9ddd in CQueryTokenNode::BuildRegExp (this=0x9194e10, RegExpStr=..., IndexItems=...) at QueryNode.cpp:581
#5  0x080caca3 in CQueryTokenNode::CreateTokenPattern (this=0x9194e10, pHolder=0xbffff014, src=0x8a455dc "(?i:sapere)", bRegularExpession=true, bExact=false) at QueryNode.cpp:744
#6  0x080e5670 in yyqparse (_parser=0x8219a90) at yyQParser.y:270
#7  0x080ddf5c in CQueryParser::ParseQuery (this=0x8219a90, src=0x821981c "/(?i:sapere)/") at QueryParser.cpp:387
#8  0x08062075 in CConcHolder::GetHits (this=0xbffff014, Query=..., EndHitNo=@0xbffff100) at ConcHolder.cpp:1466
#9  0x08062588 in CConcHolder::SimpleQuery (this=0xbffff014, Query=..., EndHitNo=@0xbffff100, HitsCount=@0xbffff0fc) at ConcHolder.cpp:1533
#10 0x0804cbc1 in main (argc=4, argv=0xbffff274) at ConcordSimple.cpp:263

 with options_ = {match_limit_ = 0, match_limit_recursion_ = 0, all_options_ = 0}
 and extra    = {flags = 0, study_data = 0x0, match_limit = 0, callout_data = 0x0, tables = 0x0, match_limit_recursion = 0}

479     int rc = pcre_exec(re,              // The regular expression object
480                      &extra,
481                      text.data(),
482                      text.size(),
483                      startpos,
484                      (anchor == UNANCHORED) ? 0 : PCRE_ANCHORED,
485                      vec,
486                      vecsize)

 where:
   re = this->re_full_ (== this->re_partial_)
   text.data() = "30sten"
   test.size() = 6
   startpos = 0
   ancor = UNANCHORED (:--> pcre_exec() anchor arg = 0)
   vec = ??
   vecsize = 51

 pcre_exec() returns rc==1.  why?!
