//-*- Mode: bison; c-basic-offset: 8; -*-*/
//  Copyright 2011-2020 by Bryan Jurish
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
%pure-parser
%lex-param {CQueryCompiler* _qcompiler}
%parse-param {CQueryCompiler* _qcompiler}

//2020-04-02/debian-buster: yyQParser.y:25.1-18: warning: deprecated directive, use ‘%define api.prefix {yyq}’ [-Wdeprecated]
%name-prefix "yyq"
// %define api.prefix {yyq}

%output  "yyQParser.cpp"
%defines "yyQParser.h"

//-- expect conflicts
// - 1 shift/reduce conflict for KW_COMMENT in "query_conditions: q_clause q_filters . (q_filters: q_filters . q_comment)"
%expect 1

/*%debug*/

//-----------------------------------------------------------------------------------------------------------------
//			Simple  Parser && , ||  without negation and words as atoms 
//-----------------------------------------------------------------------------------------------------------------

%{
/*======================================================================
 * Bison C Header
 */

#define YY_HEADER_EXPORT_START_CONDITIONS 1 /* export start conditions */

#define yyqlex_ALREADY_DEFINED // let flex 2.6 not insert #undef yylex

#include "yyQLexer.h"

#include "QueryCompiler.h"
#include "../CommonLib/ddcString.h"
#include <sstream>

using namespace std;

#ifndef YYDEBUG
# define YYDEBUG 1
#endif

#define NOINT INT_MIN
#define _qc ((CQueryCompiler*)_qcompiler)
#define _newFilter(class,ftype)			new class ((ftype), _qc->m_FilterLB, _qc->m_FilterUB)
#define _newBFilter(ftype,field)		new CQFBiblSort ((ftype), field, _qc->m_FilterLB, _qc->m_FilterUB)
#define _newCFilter(ftype,DefaultOffset)	new CQFContextSort ((ftype), _qc->m_FilterField, _qc->m_FilterMatchId, (_qc->m_FilterOffset==NOINT ? (DefaultOffset) : _qc->m_FilterOffset), _qc->m_FilterLB, _qc->m_FilterUB)

#ifdef DETECT_MEMORY_LEAK
	#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
	#endif
#endif

#define YYERROR_VERBOSE 1
#ifdef yyqerror
# undef yyqerror
#endif
#define yyqerror(qc,msg) qc->yybarf(msg)

int yylex (void*,  CQueryCompiler*);
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
%type	<m_pfilt>	q_directives
%type	<m_pfilt>	q_comment

%type   <m_pfilt>	count_filters
%type   <m_pfilt>	count_filter
%type   <m_pfilt>	count_by
%type	<m_pfilt>	count_sample
%type	<m_pfilt>	count_limit
%type	<m_pfilt>	count_sort
%type	<m_pfilt>	count_sort_op
%type	<m_pfilt>	count_sort_minmax

%type	<m_pfilt>	qd_subcorpora

%type	<m_pfilt>	qf_has_field
%type	<m_pfilt>	qf_rank_sort
%type	<m_pfilt>	qf_context_sort
%type	<m_pfilt>	qf_size_sort
%type	<m_pfilt>	qf_date_sort
%type	<m_pfilt>	qf_bibl_sort
%type	<m_pfilt>	qf_random_sort
%type	<m_pfilt>	qf_prune_sort
			
%type	<m_pfilt>	qfb_int
%type	<m_pfilt>	qfb_date
%type	<m_pfilt>	qfb_bibl
%type	<m_pfilt>	qfb_bibl_ne
%type	<m_int>		qfb_ctxsort
%type	<m_int>		qfb_ctxkey
%type   <m_int>		qfbc_matchref
%type   <m_int>		qfbc_offset

//------------------------------------------------------
// Types: Queries

%type   <m_pnode>	query_conditions
%type	<m_pnode>	q_clause
%type	<m_pnode>	qc_basic
%type	<m_pnode>	qc_boolean
%type	<m_pnode>	qc_concat
%type	<m_pnode>	qc_matchid
%type	<m_pnode>	qc_tokens
%type	<m_pnode>	qc_near
%type	<m_pnode>	qc_word
%type	<m_pnode>	qc_phrase

//------------------------------------------------------
// Types: count-queries and prune-keys

%type	<m_pnode>	count_query
%type	<m_pnode>	count_key
%type	<m_pnode>	count_key_const
%type	<m_pnode>	count_key_meta
%type	<m_pnode>	count_key_token
%type	<m_int>		ck_matchid
%type	<m_int>		ck_offset

%type	<m_pnode>	qw_keys
%type	<m_pnode>	qwk_indextuple
%type	<m_pnode>	qwk_countsrc
%type	<m_pnode>	l_indextuple

%type	<m_pnode>	prune_key

//------------------------------------------------------
// Types: Queries: Single-token queries

%type	<m_pnode>	qw_bareword
%type	<m_pnode>	qw_exact
%type	<m_pnode>	qw_regex
%type	<m_pnode>	qw_any
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
%type	<m_pnode>	qw_anchor
%type	<m_pnode>	qw_with
%type	<m_pnode>	qw_without
%type	<m_pnode>	qw_withor
%type	<m_pnode>	qw_matchid

//------------------------------------------------------
// Types: Lists (dummy types)
%type	<m_pnode>	l_morph
%type	<m_pnode>	l_phrase
%type	<m_pnode>	l_set
%type	<m_pnode>	l_txchain
%type	<m_pnode>	l_countkeys
%type	<m_pnode>	l_prunekeys
%type	<m_pnode>	l_subcorpora
%type	<m_str>		l_comment

//------------------------------------------------------
// Types: Semantic Sugar (symbols)

%type	<m_str>		s_index
%type	<m_str>		s_indextuple_item
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
%type	<m_str>		s_biblname
%type	<m_str>		s_breakname

//------------------------------------------------------
// Types: Preterminals

%type	<m_str>		symbol
%type	<m_str>		index
%type	<m_str>		sym_str
%type	<m_str>		regex
%type	<m_str>		neg_regex
%type	<m_str>		replace_regex
%type	<m_str>		int_str
%type	<m_int>		integer
%type	<m_str>		date
%type	<m_int>		matchid

//------------------------------------------------------
// Types: Terminals

%token	<m_str>	SYMBOL
%token	<m_str>	INDEX
%token	<m_str>	REGEX
%token	<m_str>	NEG_REGEX
%token	<m_str>	REGOPT
%token	<m_str>	REGEX_SEARCH
%token	<m_str>	REGEX_REPLACE
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
%token	<m_str>	HASH_LESS
%token	<m_str>	HASH_GREATER
%token	<m_str>	HASH_EQUAL
%token	<m_str>	DOLLAR_DOT

%token	<m_str>	KW_COMMENT
%token	<m_str>	CNTXT
%token	<m_str>	WITHIN
%token	<m_str>	SEPARATE_HITS
%token	<m_str>	NOSEPARATE_HITS
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
%token	<m_str>	GREATER_BY_LEFT
%token	<m_str>	LESS_BY_RIGHT
%token	<m_str>	GREATER_BY_RIGHT
%token	<m_str>	LESS_BY_MIDDLE
%token	<m_str>	GREATER_BY_MIDDLE
%token	<m_str>	DEBUG_RANK
%token	<m_str>	RANDOM
%token	<m_str>	BY
%token	<m_str>	SAMPLE
%token	<m_str>	LESS_BY_KEY
%token	<m_str>	GREATER_BY_KEY
%token	<m_str>	LESS_BY_COUNT
%token	<m_str>	GREATER_BY_COUNT
%token	<m_str>	PRUNE_ASC
%token	<m_str>	PRUNE_DESC
%token	<m_str>	CLIMIT

%token	<m_str>	KW_DATE
%token	<m_str>	KW_FILEID
%token	<m_str>	KW_FILENAME

%token	<m_str>	BLOCK_COMMENT
%token	<m_str>	LINE_COMMENT

//------------------------------------------------------
// Start Symbol
%start  query

//------------------------------------------------------
// Operator precedence and associativity
%nonassoc OP_CLAUSE_MATCHID
%nonassoc OP_CLAUSE_CONCAT
%nonassoc OP_CLAUSE_BOOL
%nonassoc OP_CLAUSE_BASIC

//%nonassoc OP_CLAUSE
%nonassoc OP_PHRASE
%nonassoc OP_WORD

%left	  OP_BOOL_AND OP_BOOL_OR
%nonassoc '!'

%nonassoc	COUNT
%nonassoc	KEYS
%nonassoc	NEAR
%left		','
%left		WITH WITHOUT WITHOR
%left   	'='
%nonassoc 	'<'
%nonassoc	'$' 
%nonassoc	'@' '^' '%' '#' '/' '~'

 //%left	SIM_PRECISE  //-- what was this for?

/*======================================================================
 * Bison Rules
 */
%%

 /*-------------------------------------------------------------
  * query (query*): Top Level (Query Root)
  */
query:
		query_conditions q_directives	{ $$ = _qc->SetQuery($1); }
 	|	count_query q_directives	{ $$ = _qc->SetQuery($1); }
	;

 /*-------------------------------------------------------------
  * count_query (count_*)
  */
count_query:
		COUNT '(' query_conditions count_filters ')' count_filters	{ $$ = _qc->PushCountQuery($3); }
	;

count_filters:
		/* empty */			{ $$=NULL; }
	|	count_filters count_filter	{ $$=$1;   }
	;

count_filter:
		count_by 			{ $$=$1; }
	|	count_sample			{ $$=$1; }
	|	count_limit			{ $$=$1; }
	|	count_sort			{ $$=$1; }
	|	q_comment			{ $$=$1; }
	;

count_by:
		BY l_countkeys 			{ $$=NULL; }
	|	BY '[' l_countkeys ']'  	{ $$=NULL; }
	;

count_sample:
		SAMPLE integer			{ $$=NULL; _qc->m_qCountSample = $2; }
	|	SAMPLE '[' integer ']'		{ $$=NULL; _qc->m_qCountSample = $3; }
	;

count_limit:
		CLIMIT integer			{ _qc->m_qCountLimit = $2; }
	|	CLIMIT '[' integer ']'		{ _qc->m_qCountLimit = $3; }
	;

count_sort:
		count_sort_op count_sort_minmax	{ $$=$1; }
	;

count_sort_op:
		LESS_BY_KEY			{ $$=NULL; _qc->m_qCountSort = LessByCountKey; }
	|	GREATER_BY_KEY			{ $$=NULL; _qc->m_qCountSort = GreaterByCountKey; }
	|	LESS_BY_COUNT			{ $$=NULL; _qc->m_qCountSort = LessByCountValue; }
	|	GREATER_BY_COUNT		{ $$=NULL; _qc->m_qCountSort = GreaterByCountValue; }
	;

count_sort_minmax:
		/* empty */			{ $$=NULL; }
	|	'[' ']'				{ $$=NULL; }
	|	'[' ',' ']'			{ $$=NULL; }
	|	'[' symbol ']'			{ $$=NULL; _qc->m_qCountLo = *$2; }
	|	'[' symbol ',' ']'		{ $$=NULL; _qc->m_qCountLo = *$2; }
	|	'[' ',' symbol ']'		{ $$=NULL; _qc->m_qCountHi = *$3; }
	|	'[' symbol ',' symbol ']'	{ $$=NULL; _qc->m_qCountLo = *$2; _qc->m_qCountHi = *$4; }
	;

 /*-------------------------------------------------------------
  * query_conditions (q*)
  */
query_conditions:
		q_clause q_filters 		{ $$ = $1; }
	;

 /*-------------------------------------------------------------
  * q_filters (qf*): Filters and Global Query Flags
  */
q_filters:
		/* empty */			{ $$=NULL; }
	|	q_filters q_comment		{ $$=NULL; }
	|	q_filters q_flag		{ $$=NULL; }
	|	q_filters q_filter		{ $$=NULL; _qc->m_qOptions.m_QFilters.push_back($2); }
	;


q_comment:
		KW_COMMENT symbol		{ $$=NULL; _qc->m_qOptions.m_Comments.push_back(*$2); }
	|	KW_COMMENT '[' l_comment ']'	{ $$=NULL; _qc->m_qOptions.m_Comments.push_back(*$3); }
	;


q_flag:	
		CNTXT integer 		{ $$=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)$2; }
	|	CNTXT '[' integer ']'	{ $$=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)$3; }
	|	WITHIN s_breakname	{ $$=NULL; _qc->m_qOptions.m_Within.push_back(*$2); }
	|	SEPARATE_HITS		{ $$=NULL; _qc->m_qOptions.m_bSeparateHits = 1; }
	|	NOSEPARATE_HITS		{ $$=NULL; _qc->m_qOptions.m_bSeparateHits = 0; }
	|	FILENAMES_ONLY 		{ $$=NULL; _qc->m_qOptions.m_bEnableBibliography = false;  }
	|	'!' FILENAMES_ONLY	{ $$=NULL; _qc->m_qOptions.m_bEnableBibliography = true;  }
	|	DEBUG_RANK		{ $$=NULL; _qc->m_qOptions.m_bDebugRank = true;  }
	|	'!' DEBUG_RANK		{ $$=NULL; _qc->m_qOptions.m_bDebugRank = false;  }
	;


q_filter:
		qf_has_field	{ $$=$1; }
	|	qf_rank_sort	{ $$=$1; }
	|	qf_context_sort	{ $$=$1; }
	|	qf_size_sort	{ $$=$1; }
	|	qf_date_sort	{ $$=$1; }
	|	qf_bibl_sort	{ $$=$1; }
	|	qf_random_sort	{ $$=$1; }
	|	qf_prune_sort   { $$=$1; }
	;

qf_has_field:
		HAS_FIELD '[' s_biblname ',' symbol ']'	{ $$ = new CQFHasFieldValue(*$3,*$5); }
	|	HAS_FIELD '[' s_biblname ',' regex ']'	{ $$ = new CQFHasFieldRegex(*$3,*$5); }
	|	HAS_FIELD '[' s_biblname ',' neg_regex ']'	{ $$ = new CQFHasFieldRegex(*$3,*$5); ((CQFHasFieldRegex*)$$)->Negate(); }
	|	HAS_FIELD '[' s_biblname ',' s_prefix ']'	{ $$ = new CQFHasFieldPrefix(*$3,*$5); }
	|	HAS_FIELD '[' s_biblname ',' s_suffix ']'	{ $$ = new CQFHasFieldSuffix(*$3,*$5); }
	|	HAS_FIELD '[' s_biblname ',' s_infix ']'	{ $$ = new CQFHasFieldInfix(*$3,*$5); }
	|	HAS_FIELD '[' s_biblname ',' '{' l_set '}' ']'	{ $$ = new CQFHasFieldSet(*$3,_qc->m_WordSet); }
	|	'!' qf_has_field 				{ $$ = $2; ((CQFHasFieldValue*)$$)->Negate(); }
	;

qf_rank_sort:
		GREATER_BY_RANK { $$ = new CQFRankSort(GreaterByRank); }
	|	LESS_BY_RANK    { $$ = new CQFRankSort(LessByRank); }
	;

qf_context_sort:
		LESS_BY_LEFT       qfb_ctxsort	{ $$ = _newCFilter(LessByLeftContext,      -1); }
	|	GREATER_BY_LEFT	   qfb_ctxsort	{ $$ = _newCFilter(GreaterByLeftContext,   -1); }
	|	LESS_BY_RIGHT      qfb_ctxsort	{ $$ = _newCFilter(LessByRightContext,      1); }
	|	GREATER_BY_RIGHT   qfb_ctxsort	{ $$ = _newCFilter(GreaterByRightContext,   1); }
	|	LESS_BY_MIDDLE     qfb_ctxsort	{ $$ = _newCFilter(LessByMiddleContext,     0); }
	|	GREATER_BY_MIDDLE  qfb_ctxsort	{ $$ = _newCFilter(GreaterByMiddleContext,  0); }
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
		LESS_BY    '[' KW_DATE qfb_bibl ']'	{ $$ = _newFilter(CQFDateSort, LessByDate); }
	|	GREATER_BY '[' KW_DATE qfb_bibl ']'	{ $$ = _newFilter(CQFDateSort, GreaterByDate); }
	|	LESS_BY    '[' s_biblname qfb_bibl ']'	{ $$ = _newBFilter(LessByFreeBiblField, *$3); }
	|	GREATER_BY '[' s_biblname qfb_bibl ']'	{ $$ = _newBFilter(GreaterByFreeBiblField, *$3); }
	;

qf_prune_sort:
		PRUNE_ASC '[' INTEGER l_prunekeys ']'	{ $$ = _qc->newPruneFilter(LessByPruneKey, *$3); }
	| 	PRUNE_DESC '[' INTEGER l_prunekeys ']'	{ $$ = _qc->newPruneFilter(GreaterByPruneKey, *$3); }
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
	|	qfb_bibl_ne		{ $$=$1; }
	;

qfb_bibl_ne:
		',' 			{ $$=NULL; _qc->SetFilterBounds(); }
	|	','        ','		{ $$=NULL; _qc->SetFilterBounds(); }
	|	',' symbol		{ $$=NULL; _qc->SetFilterBounds(*$2); }
	|	',' symbol ','		{ $$=NULL; _qc->SetFilterBounds(*$2); }
	|	','        ',' symbol	{ $$=NULL; _qc->SetFilterBounds(string(""),*$3); }
	|	',' symbol ',' symbol	{ $$=NULL; _qc->SetFilterBounds(*$2,*$4); }
	;

qfb_ctxsort:
		/* empty */			{ $$=0; _qc->SetFilterKey(); }
	|	'[' qfb_ctxkey             ']'	{ $$=0; _qc->SetFilterBounds(); }
	|	'[' qfb_ctxkey qfb_bibl_ne ']'	{ $$=0; }
	;

qfb_ctxkey:
		sym_str qfbc_matchref qfbc_offset	{ $$=0; _qc->SetFilterKey(*$1, $2, $3); }
	|		qfbc_matchref qfbc_offset	{ $$=0; _qc->SetFilterKey("",  $1, $2); }
	;

qfbc_matchref:	
		/* empty */	{ $$=0; }
	|	matchid		{ $$=$1; }
	;

qfbc_offset:
		/* empty */	{ $$=NOINT; }
	|	integer		{ $$=$1; }
	|	'+' integer	{ $$=$2; }
	|	'-' integer	{ $$=-$2; }
	;

 /*-------------------------------------------------------------
  * q_directives: global server directives
  */

q_directives:
		/* empty */			{ $$=NULL; }
	|	q_directives qd_subcorpora	{ $$=NULL; }
	;

qd_subcorpora:
		':' 	l_subcorpora 	{ $$=NULL; }
	;

 /*-------------------------------------------------------------
  * q_clause (qc*): query clauses (logical operations)
  */
q_clause:
		qc_basic		%prec OP_CLAUSE_BASIC	{ $$ = $1; }
	|	qc_boolean		%prec OP_CLAUSE_BOOL	{ $$ = $1; }
	|	qc_concat		%prec OP_CLAUSE_CONCAT	{ $$ = $1; }
	|	qc_matchid		%prec OP_CLAUSE_MATCHID	{ $$ = $1; }
	;

qc_matchid:
		q_clause matchid	 { $$ = $1; $$->SetMatchId($2); }
	|	'(' qc_matchid ')' 	 { $$ = $2; }
	;


 /*-------------------------------------------------------------
  * qc_boolean: query clause: complex boolean expression
  */
qc_boolean:
		q_clause OP_BOOL_AND q_clause	{ $$ = _qc->PushQuery(new CQAnd($1,$3)); }
	|	q_clause OP_BOOL_OR q_clause	{ $$ = _qc->PushQuery(new CQOr($1,$3)); }
	|	'!' q_clause 			{ $$ = $2; $$->Negate(); }
	|	'(' qc_boolean ')'		{ $$ = $2; }
	;

 /*-------------------------------------------------------------
  * qc_concat: query clause: implicit logical conjunction
  */
qc_concat:
 	  qc_basic qc_basic	{ $$ = _qc->PushQuery(new CQAndImplicit($1,$2)); };
	| qc_concat  qc_basic	{ $$ = _qc->PushQuery(new CQAndImplicit($1,$2)); };
	| '(' qc_concat ')'	{ $$ = $2; }
	;

 /*-------------------------------------------------------------
  * qc_basic: query clause: basic (single logical condition)
  */
qc_basic:
		qc_tokens	%prec OP_PHRASE	{ $$ = $1; }
	|	qc_near		%prec OP_PHRASE { $$ = $1; }
	;


qc_near:
		NEAR '(' qc_tokens ',' qc_tokens ',' integer ')'		{ $$ = _qc->PushQuery(new CQNear($7,$3,$5)); }
	|	NEAR '(' qc_tokens ',' qc_tokens ',' qc_tokens ',' integer ')'	{ $$ = _qc->PushQuery(new CQNear($9,$3,$5,$7)); }
 	|	qc_near matchid		{ $$ = $1; $$->SetMatchId($2); }
	|	'(' qc_near ')' 	{ $$ = $2; }
	;


 /*-------------------------------------------------------------
  * qc_tokens: condition with hit position (can be arg to NEAR()):
  */
qc_tokens: 	
		qc_word			%prec OP_WORD	{ $$ = $1; }
	|	qc_phrase 		%prec OP_PHRASE	{ $$ = $1; }
	|	qc_tokens matchid	%prec OP_PHRASE { $$ = $1; $$->SetMatchId($2); }
	;

qc_phrase:
		'"' l_phrase '"'	{ $$ = $2; }
	|	'(' qc_phrase ')'	{ $$ = $2; }
	;

 /*-------------------------------------------------------------
  * qc_word (qw*): Single-Token Queries
  */
qc_word:
		qw_bareword		{ $$ = $1; }
	|	qw_exact		{ $$ = $1; }
	|	qw_regex		{ $$ = $1; }
	|	qw_any			{ $$ = $1; }
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
	|	qw_anchor		{ $$ = $1; }
	|	qw_listfile		{ $$ = $1; }
	|	qw_with			{ $$ = $1; }
	|	qw_without		{ $$ = $1; }
	|	qw_withor		{ $$ = $1; }
	|	qw_keys			{ $$ = $1; }
 	|	qw_matchid		{ $$ = $1; }
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

qw_any:
		'*'				{ $$ = _qc->PushQuery(new CQTokAny("")); }
	|	s_index '=' '*'			{ $$ = _qc->PushQuery(new CQTokAny(*$1)); }
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
	|	s_index '=' COLON_LBRACE s_semclass '}'	{ $$ = _qc->PushQuery(new CQTokThes(*$1,*$4)); }
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

qw_anchor:
		DOLLAR_DOT        '=' int_str	{ $$ = _qc->PushQuery(new CQTokAnchor( "", *$3)); }
	|	DOLLAR_DOT symbol '=' int_str	{ $$ = _qc->PushQuery(new CQTokAnchor(*$2, *$4)); }
	;

qw_listfile:
	 	'<' s_filename			{ $$ = _qc->PushQuery(new CQTokFile("",*$2)); }
	| 	s_index '=' '<' s_filename	{ $$ = _qc->PushQuery(new CQTokFile(*$1,*$4)); }
	;

qw_with:
		qc_word WITH    qc_word		{ $$ = _qc->PushQuery(new CQWith($1,$3)); }
	;

qw_without:
		qc_word WITHOUT qc_word		{ $$ = _qc->PushQuery(new CQWithout($1,$3)); }
	;

qw_withor:
		qc_word WITHOR qc_word		{ $$ = _qc->PushQuery(new CQWithor($1,$3)); }
	;

qw_keys:
		KEYS '(' qwk_countsrc ')'			{ $$ = _qc->PushKeysQuery((CQCount*)$3); }
	|	qwk_indextuple '=' KEYS '(' qwk_countsrc ')'	{ $$ = _qc->PushKeysQuery((CQCount*)$5); }
	;

qwk_indextuple:
		'$' '(' l_indextuple ')'			{ $$=NULL; }
	;

qwk_countsrc:
		count_query					{ $$ = $1; }
	|	query_conditions count_filters 			{ $$ = _qc->PushCountQuery($1); }
	;

qw_matchid:
		qc_word matchid 		{ $$ = $1; $$->SetMatchId($2); }
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

l_phrase :
		qc_word					{ $$ = _qc->PushQuery(new CQSeq((CQToken*)$1)); }
	| 	l_phrase qc_word			{ ((CQSeq*)$1)->Append((CQToken*)$2); $$ = $1; }
	|	l_phrase '#'           integer qc_word	{ ((CQSeq*)$1)->Append((CQToken*)$4,$3); $$ = $1; }
	|	l_phrase HASH_LESS     integer qc_word	{ ((CQSeq*)$1)->Append((CQToken*)$4,$3,'<'); $$ = $1; }
	|	l_phrase HASH_GREATER  integer qc_word	{ ((CQSeq*)$1)->Append((CQToken*)$4,$3,'>'); $$ = $1; }
	|	l_phrase HASH_EQUAL    integer qc_word	{ ((CQSeq*)$1)->Append((CQToken*)$4,$3,'='); $$ = $1; }
	;

l_txchain:
		/* empty */		{ $$ = NULL; _qc->m_Expanders.clear(); }
	|	l_txchain s_expander	{ $$ = $1;   _qc->m_Expanders.push_back(*$2); }
	;

l_countkeys:
		/* empty */			{ $$=NULL; _qc->m_qCountKeys.Clear(); }
	|	count_key			{ $$=NULL; _qc->m_qCountKeys.Clear(); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)$1); }
	|	l_countkeys ',' count_key	{ $$=$1; _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)$3); }
	;

l_prunekeys:
		/* empty */			{ $$=NULL; _qc->m_qCountKeys.Clear(); }
	|	prune_key			{ $$=NULL; _qc->m_qCountKeys.Clear(); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)$1); }
	|	l_prunekeys ',' prune_key	{ $$=$1; _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)$3); }
	;

l_indextuple:
		/* empty */					{ $$=NULL; _qc->m_IndexTuple.clear(); }
	|	s_indextuple_item				{ $$=NULL; _qc->m_IndexTuple.clear(); _qc->m_IndexTuple.push_back(*$1); }
	|	l_indextuple ',' s_indextuple_item		{ $$=NULL; _qc->m_IndexTuple.push_back(*$3); }
	;

l_comment:
		/* empty */			{ $$=_qc->newString(""); }
	|	l_comment symbol		{ $$=$1; if (!$$->empty()) $$->push_back(' '); $$->append(*$2); };
	;

l_subcorpora:
	        /* empty */			{ _qc->m_qOptions.m_Subcorpora.clear(); $$=NULL; }
 	|	s_subcorpus			{ _qc->m_qOptions.m_Subcorpora.clear(); _qc->m_qOptions.m_Subcorpora.push_back(*$1); $$=NULL; }
	|	l_subcorpora ',' s_subcorpus	{ _qc->m_qOptions.m_Subcorpora.push_back(*$3); $$=$1; }
	;

 /*-------------------------------------------------------------
  * count_key, prune_key: count- and prune-key expressions
  */

count_key:
		count_key_const			{ $$=$1; }
	|	count_key_meta			{ $$=$1; }
	|	count_key_token			{ $$=$1; }
 	|	count_key '~' replace_regex	{ $$=new CQCountKeyExprRegex((CQCountKeyExpr*)$1,*$3,_qc->m_RegexReplacement,_qc->m_RegexModifiers); }
	|	'(' count_key ')'		{ $$=$2; }
	;

prune_key:
		count_key_const			{ $$=$1; }
	|	count_key_meta			{ $$=$1; }
 	|	prune_key '~' replace_regex	{ $$=new CQCountKeyExprRegex((CQCountKeyExpr*)$1,*$3,_qc->m_RegexReplacement,_qc->m_RegexModifiers); }
	|	'(' prune_key ')'		{ $$=$2; }
	;

count_key_const:
		'*'				{ $$=new CQCountKeyExprConstant("*"); }
	|	'@' symbol			{ $$=new CQCountKeyExprConstant(*$2); }
	;

count_key_meta:	
		KW_FILEID			{ $$=new CQCountKeyExprFileId(*$1); }
	|	KW_FILENAME			{ $$=new CQCountKeyExprFileName(*$1); }
	|	KW_DATE				{ $$=new CQCountKeyExprDate(*$1); }
	|	KW_DATE '/' integer		{ $$=new CQCountKeyExprDateSlice(*$1,$3); }
	|	s_biblname			{ $$=new CQCountKeyExprBibl(*$1); }
	;

count_key_token:
		s_index ck_matchid ck_offset	{ $$=new CQCountKeyExprToken(*$1,$2,$3); }
	;


ck_matchid:
		/* empty */	{ $$=0; }
	|	matchid		{ $$=$1; }
	;

ck_offset:
		/* empty */	{ $$=0; }
	|	integer		{ $$=$1; }
	|	'+' integer	{ $$=$2; }
	|	'-' integer	{ $$=-$2; }
	;

 /*-------------------------------------------------------------
  * s_*: semantic sugar for symbols
  */

s_index:	index		{ $$ = $1; };

s_indextuple_item:
		s_index		{ $$ = $1; }
	|	symbol		{ $$ = $1; /* for default item '-' */ }
	;

s_word:		symbol 		{ $$ = $1; };
s_semclass:	symbol		{ $$ = $1; };
s_lemma:	symbol		{ $$ = $1; };
s_chunk: 	symbol		{ $$ = $1; };
s_filename:	symbol		{ $$ = $1; };
s_morphitem:	symbol		{ $$ = $1; };
s_subcorpus:	symbol		{ $$ = $1; };
s_biblname:	symbol		{ $$ = $1; };

s_breakname:	symbol		{ $$ = $1; }
	|	KW_FILENAME	{ $$ = _qc->newString("file"); }
	;

 /*-------------------------------------------------------------
  * Preterminals
  */
symbol:		SYMBOL	{ *$1 = unescapeCString(*$1); $$ = $1; }
	|	INTEGER { $$ = $1; }
	|	DATE    { $$ = $1; }
	;

index:		'$'	{ $$  = _qc->newString(""); }
	|	INDEX	{ *$1 = unescapeCString(*$1); $$ = $1; }
	;

sym_str:	SYMBOL	{ *$1 = unescapeCString(*$1); $$ = $1; }
	;

s_prefix:	PREFIX		{ *$1 = unescapeCString(*$1); $$ = $1; };
s_suffix:	SUFFIX		{ *$1 = unescapeCString(*$1); $$ = $1; };
s_infix:	INFIX		{ *$1 = unescapeCString(*$1); $$ = $1; };

s_expander:	EXPANDER	{ *$1 = unescapeCString(*$1); $$ = $1; };

regex:		REGEX		{ $$ = _qc->newRegex(*$1); }
	|	REGEX REGOPT	{ $$ = _qc->newRegex(*$1,*$2); }
	;

neg_regex:	NEG_REGEX		{ $$ = _qc->newRegex(*$1); }
	|	NEG_REGEX REGOPT	{ $$ = _qc->newRegex(*$1,*$2); }
	;

 /* replace_regex leaves replacement string in _qc->m_RegexReplacement */
replace_regex:	REGEX_SEARCH REGEX_REPLACE		{ $$ = _qc->newRegex(*$1,"",false); }
	|	REGEX_SEARCH REGEX_REPLACE REGOPT	{ $$ = _qc->newRegex(*$1,*$3,false); }
	;

int_str: 	INTEGER	{ $$ = $1; }
	;

integer: 	int_str	{ $$ = strtol($1->c_str(), NULL, 0); }
	;

date:		DATE	{ $$ = $1; }
	|	INTEGER { $$ = $1; }
	;

matchid:	'=' 	{ _qc->yybegin(Q_MATCHID); }
		integer	{ _qc->yybegin(INITIAL); $$ = $3; }
	;


%%
/*======================================================================
 * User C Code
 */
