//-*- Mode: bison; c-basic-offset: 8; -*-*/
//  Copyright 2011 by Bryan Jurish
//
//  This file is part of DDC.
// 
//  DDC is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
// 
//  DDC is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
// 
//  You should have received a copy of the GNU Lesser General Public License
//  along with DDC.  If not, see <http://www.gnu.org/licenses/>.
//
/*======================================================================
 * Bison Options
 */
%define api.pure
%name-prefix "yyq"
%output  "yyQParser.cpp"
%defines "yyQParser.h"


//-----------------------------------------------------------------------------------------------------------------
//			Simple  Parser && , ||  without negation and words as atoms 
//-----------------------------------------------------------------------------------------------------------------

%{
/*======================================================================
 * Bison C Header
 */

/*#include "yyQLexer.h"*/
#include "QueryCompiler.h"
#include "../common/ddcString.h"
#include <sstream>

#define YYDEBUG 1
#define YYPARSE_PARAM _qcompiler
#define YYLEX_PARAM _qcompiler

#define _qc ((CQueryCompiler*)_qcompiler)
#define _newFilter(class,ftype)		new class ((ftype), _qc->m_FilterLB, _qc->m_FilterUB)
#define _newBFilter(ftype,field)	new CQFBiblSort ((ftype), field, _qc->m_FilterLB, _qc->m_FilterUB)

#ifdef DETECT_MEMORY_LEAK
	#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
	#endif
#endif

#define YYERROR_VERBOSE 1
#define yyqerror(msg) _qc->yybarf(msg)

int yylex (void*,  void*);
%} 

/*======================================================================
 * Bison Definitions
 */
%union {
  std::string*	 	m_str;     /* For returning simple strings  */
  int                   m_int;     /* For returning integers */
  class CQuery*	 	m_pnode;   /* For returning basic query nodes */
  class CQFilter* 	m_pfilt;   /* For returning single query filters */
}

//------------------------------------------------------
// Types: Top-Level

%type   <m_pnode>	query

//------------------------------------------------------
// Types: Filters

%type   <m_pfilt>	q_filters
%type	<m_pfilt>	q_filter
%type	<m_pfilt>	q_flag

%type	<m_pfilt>	qf_subcorpora
%type	<m_pfilt>	qf_has_field
%type	<m_pfilt>	qf_rank_sort
%type	<m_pfilt>	qf_bigram_sort
%type	<m_pfilt>	qf_size_sort
%type	<m_pfilt>	qf_date_sort
%type	<m_pfilt>	qf_bibl_sort
%type	<m_pfilt>	qf_random_sort

%type	<m_pfilt>	qfb_int
%type	<m_pfilt>	qfb_date
%type	<m_pfilt>	qfb_bibl

//------------------------------------------------------
// Types: Queries

%type	<m_pnode>	q_clause
%type	<m_pnode>	qc_basic
%type	<m_pnode>	qc_tokens
%type	<m_pnode>	qc_near
%type	<m_pnode>	qc_word
%type	<m_pnode>	qc_sequence

//------------------------------------------------------
// Types: Queries: Single-token queries

%type	<m_pnode>	qw_bareword
%type	<m_pnode>	qw_exact
%type	<m_pnode>	qw_regex
%type	<m_pnode>	qw_set_infl
%type	<m_pnode>	qw_set_exact

%type	<m_pnode>	qw_prefix
%type	<m_pnode>	qw_prefix_set
%type	<m_pnode>	qw_suffix
%type	<m_pnode>	qw_suffix_set
%type	<m_pnode>	qw_infix
%type	<m_pnode>	qw_infix_set

%type	<m_pnode>	qw_thesaurus
%type	<m_pnode>	qw_morph
%type	<m_pnode>	qw_lemma
%type	<m_pnode>	qw_chunk
%type	<m_pnode>	qw_listfile
%type	<m_pnode>	qw_with


//------------------------------------------------------
// Types: Lists (dummy types)
%type	<m_pnode>	l_morph
%type	<m_pnode>	l_seq
%type	<m_pnode>	l_set
%type	<m_pnode>	l_txchain

//------------------------------------------------------
// Types: Semantic Sugar (symbols)

%type	<m_str>		s_index
%type	<m_str>		s_word
%type	<m_str>		s_prefix
%type	<m_str>		s_suffix
%type	<m_str>		s_infix
%type	<m_str>		s_semclass
%type	<m_str>		s_lemma
%type	<m_str>		s_chunk
%type	<m_str>		s_filename
%type	<m_str>		s_morphitem
%type	<m_str>		s_expander
%type	<m_str>		s_subcorpus

//------------------------------------------------------
// Types: Preterminals

%type	<m_str>		symbol
%type	<m_str>		regex
%type	<m_str>		neg_regex
%type	<m_str>		int_str
%type	<m_int>		integer
%type	<m_str>		date

//------------------------------------------------------
// Types: Terminals

%token	<m_str>	SYMBOL
%token	<m_str>	REGEX
%token	<m_str>	NEG_REGEX
%token	<m_str>	REGOPT
%token	<m_str>	INTEGER
%token	<m_str>	DATE
%token	<m_str>	PREFIX
%token	<m_str>	SUFFIX
%token	<m_str>	INFIX
%token	<m_str>	AT_LBRACE
%token	<m_str>	COLON_LBRACE
%token	<m_str>	STAR_LBRACE
%token	<m_str> RBRACE_STAR
%token	<m_str> EXPANDER

%token	<m_str>	CNTXT
%token	<m_str>	WITHIN
%token	<m_str>	HAS_FIELD
%token	<m_str>	FILENAMES_ONLY
%token	<m_str>	GREATER_BY_RANK
%token	<m_str>	LESS_BY_RANK
%token	<m_str>	GREATER_BY_SIZE
%token	<m_str>	LESS_BY_SIZE
%token	<m_str>	IS_SIZE
%token	<m_str>	GREATER_BY_DATE
%token	<m_str>	LESS_BY_DATE
%token	<m_str>	IS_DATE
%token	<m_str>	GREATER_BY
%token	<m_str>	LESS_BY
%token	<m_str>	LESS_BY_LEFT
%token	<m_str>	LESS_BY_RIGHT
%token	<m_str>	DEBUG_RANK
%token	<m_str>	RANDOM

//------------------------------------------------------
// Start Symbol
%start  query

//------------------------------------------------------
// Operator precedence and associativity
//%left   OP_NONE
%left	OP_AND OP_OR
%right  '!'
%left	NEAR
%left	','
%left	WITH 
%left   '=' '<'
%left   '$' 
%left	'@' '^' '%' '#'

 //%left	SIM_PRECISE  //-- what was this for?

/*======================================================================
 * Bison Rules
 */
%%

 /*-------------------------------------------------------------
  * query (q*): Top Level (Query Root)
  */
query:
		q_clause q_filters 	  	{ _qc->m_pQuery = $$ = $1; }
	;

 /*-------------------------------------------------------------
  * q_filters (qf*): Filters and Global Query Flags
  */
q_filters:
		/* empty */			{ $$ = NULL; }
	|	q_filters q_flag		{ $$ = NULL; }
	|	q_filters q_filter		{ _qc->m_QFilters.push_back($2); }
	;

q_flag:	
		':' qf_subcorpora 	{ $$ = NULL; }
	|	CNTXT integer 		{ _qc->m_ContextSentencesCount = (size_t)$2; $$ = NULL; }
	|	WITHIN symbol 		{ _qc->m_Within.push_back(*$2); $$ = NULL; }
	|	FILENAMES_ONLY 		{ _qc->m_bEnableBibliographyForThisQuery = false; $$ = NULL; }
	|	'!' FILENAMES_ONLY	{ _qc->m_bEnableBibliographyForThisQuery = true; $$ = NULL; }
	|	DEBUG_RANK		{ _qc->m_bDebugRank = true; $$ = NULL; }
	|	'!' DEBUG_RANK		{ _qc->m_bDebugRank = false; $$ = NULL; }

qf_subcorpora:
		/* empty */			{ $$=NULL; }
	|	s_subcorpus			{ _qc->m_Subcorpora.push_back(*$1); $$ = NULL; }
	|	qf_subcorpora ',' s_subcorpus	{ _qc->m_Subcorpora.push_back(*$3); $$ = $1; }
	;

q_filter:
		qf_has_field	{ $$=$1; }
	|	qf_rank_sort	{ $$=$1; }
	|	qf_bigram_sort	{ $$=$1; }
	|	qf_size_sort	{ $$=$1; }
	|	qf_date_sort	{ $$=$1; }
	|	qf_bibl_sort	{ $$=$1; }
	|	qf_random_sort	{ $$=$1; }
	;

qf_has_field:
		HAS_FIELD '[' symbol ',' symbol ']'	{ $$ = new CQFHasFieldValue(*$3,*$5); }
	|	HAS_FIELD '[' symbol ',' regex ']'	{ $$ = new CQFHasFieldRegex(*$3,*$5); }
	;

qf_rank_sort:
		GREATER_BY_RANK { $$ = new CQFRankSort(GreaterByRank); }
	|	LESS_BY_RANK    { $$ = new CQFRankSort(LessByRank); }
	;

qf_bigram_sort:
		LESS_BY_LEFT  	{ $$ = new CQFLeftSort(); }
	|	LESS_BY_RIGHT	{ $$ = new CQFRightSort(); }
	;

qf_size_sort:
		LESS_BY_SIZE qfb_int		{ $$ = _newFilter(CQFSizeSort, LessBySize); }
	|	GREATER_BY_SIZE qfb_int		{ $$ = _newFilter(CQFSizeSort, GreaterBySize); }
	|	IS_SIZE '[' int_str ']'		{ $$ = new CQFSizeSort(LessBySize, *$3, *$3); }
	;

qf_date_sort:
		LESS_BY_DATE qfb_date		{ $$ = _newFilter(CQFDateSort, LessByDate); }
	|	GREATER_BY_DATE qfb_date	{ $$ = _newFilter(CQFDateSort, GreaterByDate); }
	|	IS_DATE '[' date ']'		{ $$ = new CQFDateSort(LessByDate, *$3, *$3); }
	;

qf_random_sort:
		RANDOM					{ $$ = new CQFRandomSort(); }
	|	RANDOM '[' ']'				{ $$ = new CQFRandomSort(); }
	|	RANDOM '[' int_str ']'			{ $$ = new CQFRandomSort(*$3); }
	;

qf_bibl_sort:
		LESS_BY '[' symbol qfb_bibl ']'		{ $$ = _newBFilter(LessByFreeBiblField, *$3); }
	|	GREATER_BY '[' symbol qfb_bibl ']'	{ $$ = _newBFilter(GreaterByFreeBiblField, *$3); }
	;

 /*-------------------------------------------------------------
  * (qfb*): Filter Bounds
  */

qfb_int:
		/* empty */			{ $$=NULL; _qc->SetFilterBounds(); }
	|	'[' ']'				{ $$=NULL; _qc->SetFilterBounds(); }
	|	'[' int_str ']'			{ $$=NULL; _qc->SetFilterBounds(*$2); }
	|	'[' int_str ',' ']'		{ $$=NULL; _qc->SetFilterBounds(*$2); }
	|	'[' int_str ',' int_str ']'	{ $$=NULL; _qc->SetFilterBounds(*$2,*$4); }
	|	'[' ',' int_str ']'		{ $$=NULL; _qc->SetFilterBounds(string(""),*$3); }
	;

qfb_date:
		/* empty */			{ $$=NULL; _qc->SetFilterBounds(); }
	|	'[' ']'				{ $$=NULL; _qc->SetFilterBounds(); }
	|	'[' date ']'			{ $$=NULL; _qc->SetFilterBounds(*$2); }
	|	'[' date ',' ']'		{ $$=NULL; _qc->SetFilterBounds(*$2); }
	|	'[' date ',' date ']'		{ $$=NULL; _qc->SetFilterBounds(*$2,*$4); }
	|	'[' ',' date ']'		{ $$=NULL; _qc->SetFilterBounds(string(""),*$3); }
	;

qfb_bibl:
		/* empty */		{ $$=NULL; _qc->SetFilterBounds(); }
	|	','			{ $$=NULL; _qc->SetFilterBounds(); }
	|	',' ','			{ $$=NULL; _qc->SetFilterBounds(); }
	|	',' symbol		{ $$=NULL; _qc->SetFilterBounds(*$2); }
	|	',' symbol ','		{ $$=NULL; _qc->SetFilterBounds(*$2); }
	|	',' ',' symbol		{ $$=NULL; _qc->SetFilterBounds(string(""),*$3); }
	|	',' symbol ',' symbol	{ $$=NULL; _qc->SetFilterBounds(*$2,*$4); }
	;

 /*-------------------------------------------------------------
  * q_clause (qc*): query clauses (logical operations)
  */
q_clause:
		qc_basic			{ $$ = $1; }
	/*|	q_clause q_clause %prec OP_NONE	{ $$ = _qc->PushQuery(new CQAnd($1,$2)); }*/
	|	q_clause OP_AND q_clause	{ $$ = _qc->PushQuery(new CQAnd($1,$3)); }
	|	q_clause OP_OR q_clause		{ $$ = _qc->PushQuery(new CQOr($1,$3)); }
	|	'!' q_clause %prec '!'			{ $$ = $2; $$->Negate(); }
	|	'(' q_clause ')'		{ $$ = $2; }
	;


 /*-------------------------------------------------------------
  * qc_basic: query clause: basic (single logical condition)
  */
qc_basic:
		qc_tokens	{ $$ = $1; }
	|	qc_near		{ $$ = $1; }
	;

qc_near:
		NEAR '(' qc_tokens ',' qc_tokens ',' integer ')'
		{
		  $$ = _qc->PushQuery(new CQNear($7,$3,$5));
		}

	|	NEAR '(' qc_tokens ',' qc_tokens ',' qc_tokens ',' integer ')'
		{
		  $$ = _qc->PushQuery(new CQNear($9,$3,$5,$7));
		}

	|	'(' qc_near ')'
		{
		  $$ = $2;
		}
	;


 /*-------------------------------------------------------------
  * qc_tokens: condition with hit position (can be arg to NEAR()):
  */
qc_tokens: 	
		qc_word		{ $$ = $1; }
	|	qc_sequence 	{ $$ = $1; }
	;

qc_sequence:
		'"' l_seq '"'		{ $$ = $2; }
	|	'(' qc_sequence ')'	{ $$ = $2; }
	;

 /*-------------------------------------------------------------
  * qc_word (qw*): Single-Token Queries
  */
qc_word:
		qw_bareword		{ $$ = $1; }
	|	qw_exact		{ $$ = $1; }
	|	qw_regex		{ $$ = $1; }
	|	qw_set_infl		{ $$ = $1; }
	|	qw_set_exact		{ $$ = $1; }
	|	qw_infix		{ $$ = $1; }
	|	qw_infix_set		{ $$ = $1; }
	|	qw_prefix		{ $$ = $1; }
	|	qw_prefix_set		{ $$ = $1; }
	|	qw_suffix		{ $$ = $1; }
	|	qw_suffix_set		{ $$ = $1; }
	|	qw_thesaurus		{ $$ = $1; }
	|	qw_morph		{ $$ = $1; }
	|	qw_lemma		{ $$ = $1; }
	|	qw_chunk		{ $$ = $1; }
	|	qw_listfile		{ $$ = $1; }
	|	qw_with			{ $$ = $1; }
	|	'(' qc_word ')'		{ $$ = $2; }
	;

qw_bareword:
	 	s_word l_txchain		{ $$ = _qc->PushQuery(new CQTokInfl("", *$1,_qc->m_Expanders)); }
	| 	s_index '=' s_word l_txchain	{ $$ = _qc->PushQuery(new CQTokInfl(*$1,*$3,_qc->m_Expanders)); }
	;

qw_exact:
		'@' s_word			{ $$ = _qc->PushQuery(new CQTokExact("",*$2)); }
	|	s_index '=' '@' s_word		{ $$ = _qc->PushQuery(new CQTokExact(*$1,*$4)); }
	;

qw_regex:
		regex				{ $$ = _qc->PushQuery(new CQTokRegex("",*$1)); }
	|	s_index '=' regex		{ $$ = _qc->PushQuery(new CQTokRegex(*$1,*$3)); }
	|	neg_regex			{ $$ = _qc->PushQuery(new CQTokRegex("",*$1,true)); }
	|	s_index '=' neg_regex		{ $$ = _qc->PushQuery(new CQTokRegex(*$1,*$3,true)); }
	;

qw_set_exact:
		AT_LBRACE l_set '}'		{ $$ = _qc->PushQuery(new CQTokSet("", "", _qc->m_WordSet)); }
	|	s_index '=' AT_LBRACE l_set '}'	{ $$ = _qc->PushQuery(new CQTokSet(*$1, "", _qc->m_WordSet)); }
	;

qw_set_infl:
		'{' l_set '}' l_txchain			{ $$ = _qc->PushQuery(new CQTokSetInfl("", _qc->m_WordSet, _qc->m_Expanders)); }
	|	s_index '=' '{' l_set '}' l_txchain	{ $$ = _qc->PushQuery(new CQTokSetInfl(*$1, _qc->m_WordSet, _qc->m_Expanders)); }
	;

qw_prefix:
		s_prefix			{ $$ = _qc->PushQuery(new CQTokPrefix("",*$1)); }
	|	s_index '=' s_prefix		{ $$ = _qc->PushQuery(new CQTokPrefix(*$1,*$3)); }
	;

qw_suffix:
		s_suffix			{ $$ = _qc->PushQuery(new CQTokSuffix("",*$1)); }
	|	s_index '=' s_suffix		{ $$ = _qc->PushQuery(new CQTokSuffix(*$1,*$3)); }
	;

qw_infix:
		s_infix				{ $$ = _qc->PushQuery(new CQTokInfix("",*$1)); }
	|	s_index '=' s_infix		{ $$ = _qc->PushQuery(new CQTokInfix(*$1,*$3)); }
	;

qw_infix_set:
		STAR_LBRACE l_set RBRACE_STAR			{ $$ = _qc->PushQuery(new CQTokInfixSet("", _qc->m_WordSet)); }
	|	s_index '=' STAR_LBRACE l_set RBRACE_STAR	{ $$ = _qc->PushQuery(new CQTokInfixSet(*$1, _qc->m_WordSet)); }
	;

qw_prefix_set:
		'{' l_set RBRACE_STAR				{ $$ = _qc->PushQuery(new CQTokPrefixSet("", _qc->m_WordSet)); }
	|	s_index '=' '{' l_set RBRACE_STAR		{ $$ = _qc->PushQuery(new CQTokPrefixSet(*$1, _qc->m_WordSet)); }
	;

qw_suffix_set:
		STAR_LBRACE l_set '}'				{ $$ = _qc->PushQuery(new CQTokSuffixSet("", _qc->m_WordSet)); }
	|	s_index '=' STAR_LBRACE l_set '}'		{ $$ = _qc->PushQuery(new CQTokSuffixSet(*$1, _qc->m_WordSet)); }
	;

qw_thesaurus:
		COLON_LBRACE s_semclass '}'		{ $$ = _qc->PushQuery(new CQTokThes("Thes",*$2)); }
	|	s_index '=' ':' '{' s_semclass '}'	{ $$ = _qc->PushQuery(new CQTokThes(*$1,*$5)); }
	;

qw_morph:
		'[' l_morph ']'			{ $$ = _qc->PushQuery(new CQTokMorph("MorphPattern",_qc->m_MorphItems)); }
	|	s_index '=' '[' l_morph ']'	{ $$ = _qc->PushQuery(new CQTokMorph(*$1,_qc->m_MorphItems)); }
	;

qw_lemma:
	 	'%' s_lemma			{ $$ = _qc->PushQuery(new CQTokLemma("Lemma",*$2)); }
	|	s_index '=' '%' s_lemma		{ $$ = _qc->PushQuery(new CQTokLemma(*$1,*$4)); }
	;

qw_chunk:
		'^' s_chunk			{ $$ = _qc->PushQuery(new CQTokChunk("",*$2)); }
	| 	s_index '=' '^' s_chunk		{ $$ = _qc->PushQuery(new CQTokChunk(*$1,*$4)); }
	;

qw_listfile:
	 	'<' s_filename			{ $$ = _qc->PushQuery(new CQTokFile("",*$2)); }
	| 	s_index '=' '<' s_filename	{ $$ = _qc->PushQuery(new CQTokFile(*$1,*$4)); }
	;

qw_with:
		qc_word WITH qc_word		{ $$ = _qc->PushQuery(new CQWith($1,$3)); }
	;


 /*-------------------------------------------------------------
  * l_*: List-like constituents
  */

l_set:
		/* empty */		{ _qc->m_WordSet.clear();     $$ = NULL; }
	|	l_set s_word		{ _qc->m_WordSet.insert(*$2); $$ = $1;}
	|	l_set ','		{ $$ = $1; }
	/*|	l_set ';'		{ $$ = $1; }*/
	;

l_morph:
		/* empty */		{ _qc->m_MorphItems.clear();        $$ = NULL; }
	|	l_morph s_morphitem	{ _qc->m_MorphItems.push_back(*$2); $$ = $1;}
	|	l_morph ','		{ $$ = $1; }
	|	l_morph ';'		{ $$ = $1; } /* backwards-compatible */
	;

l_seq :
		qc_word				{ $$ = _qc->PushQuery(new CQSeq((CQToken*)$1)); }
	| 	l_seq qc_word			{ ((CQSeq*)$1)->Append((CQToken*)$2); $$ = $1; }
	|	l_seq '#' integer qc_word	{ ((CQSeq*)$1)->Append((CQToken*)$4,$3); $$ = $1; }
	;

l_txchain:
	/* empty */				{ $$ = NULL; _qc->m_Expanders.clear(); }
	|	l_txchain s_expander		{ $$ = $1;   _qc->m_Expanders.push_back(*$2); }
	;

 /*-------------------------------------------------------------
  * s_*: semantic sugar for symbols
  */

s_index:
		'$'		{ $$ = _qc->newString(); }
	|	'$' symbol	{ $$ = $2; }
	;

s_word:		symbol 		{ $$ = $1; };
s_semclass:	symbol		{ $$ = $1; };
s_lemma:	symbol		{ $$ = $1; };
s_chunk: 	symbol		{ $$ = $1; };
s_filename:	symbol		{ $$ = $1; };
s_morphitem:	symbol		{ $$ = $1; };
s_subcorpus:	symbol		{ $$ = $1; };

 /*-------------------------------------------------------------
  * Preterminals
  */
symbol:		SYMBOL	{ *$1 = unescapeCString(*$1); $$ = $1; }
	|	INTEGER { $$ = $1; }
	|	DATE    { $$ = $1; }
	;

s_prefix:	PREFIX		{ *$1 = unescapeCString(*$1); $$ = $1; };
s_suffix:	SUFFIX		{ *$1 = unescapeCString(*$1); $$ = $1; };
s_infix:	INFIX		{ *$1 = unescapeCString(*$1); $$ = $1; };

s_expander:	EXPANDER	{ *$1 = unescapeCString(*$1); $$ = $1; };

regex:		REGEX		{ $$ = $1 }
	|	REGEX REGOPT	{ $$ = $2 }
	;

neg_regex:	NEG_REGEX		{ $$ = $1 }
	|	NEG_REGEX REGOPT	{ $$ = $2 }
	;

int_str: 	INTEGER	{ $$ = $1; }
	;

integer: 	int_str	{ $$ = atoi($1->c_str()); }
	;

date:		DATE	{ $$ = $1; }
	|	INTEGER { $$ = $1; }
	;


%%
/*======================================================================
 * User C Code
 */
