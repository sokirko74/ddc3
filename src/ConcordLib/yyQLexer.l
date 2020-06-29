/*-*- Mode: Flex; c-basic-offset: 8 -*-*/
/*
//  Copyright 2011-2019 by Bryan Jurish
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
*/

/*======================================================================
 * Flex Options
 */
%option c++
%option yyclass="yyqLexer"
   /*
     %option reentrant
     %option bison-bridge
     %option bison-locations
     %option noyywrap
     %option stack
   */

%option yylineno
%option yywrap
%option nounistd

%option outfile="yyQLexer.cpp"
%option header-file="yyQLexer.h"
%option prefix="yyq"
%option 8bit

%{
/*======================================================================
 * User C Header
 */

#define YY_QUERY_LEXER

//-- we need export  constants from yacc, like "SYMBOL"
#include "QueryCompiler.h"

#ifdef DETECT_MEMORY_LEAK
	#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
	#endif
#endif

#define yyqDEBUG
#ifdef yyqDEBUG
# define DBG(code) code;
#else
# define DBG(code)
#endif

#define DPRINTF2(a1,a2) DBG(fprintf(stderr,a1,a2);)

//-- DDC_WANT_LEXER_COMMENTS : define this to return lexer comments from yylex()
// + lexer comments were introduced for v2.1.16
// + prior to v2.2.3, lexer comments were __never__ kept (no CQueryOptions::m_LexerComments field)
// + as of v2.2.3, lexer comments are enabled here, and disabled for runtime in  CQueryCompiler::m_KeepLexerComments
#define DDC_WANT_LEXER_COMMENTS 1
#ifdef DDC_WANT_LEXER_COMMENTS
 #define DDC_LEXER_COMMENT(x) x
#else
 #define DDC_LEXER_COMMENT(x)
#endif

%}

/*======================================================================
 * Flex Definitions
 */

 /* whitespace */
ws		[ \t\n\r\f\v]

 /* integer boundary characters */
int_boundary	 [ \t\n\r\f\v\0&|!?^%,:;#*=~(){}<>\[\]\\/\'\".$@_+-]

 /* bareword symbols */
symbol_cfirst	[^ \t\n\r\f\v\0&|!?^%,:;#*=~(){}<>\[\]\\/\'\".$@]
symbol_crest	[^ \t\n\r\f\v\0&|!?^%,:;#*=~(){}<>\[\]\\/\'\"]
symbol_cescape  (\\.)
symbol_text	({symbol_cescape}|{symbol_cfirst})({symbol_cescape}|{symbol_crest})*

/* subcorpus symbols */
corpus_cfirst	[^ \t\n\r\f\v\0&|!?^%,:;#=~(){}<>\[\]\\\'\"$@]
corpus_crest	[^ \t\n\r\f\v\0&|!?^%,:;#=~(){}<>\[\]\\\'\"]
corpus_text	({symbol_cescape}|{corpus_cfirst})({symbol_cescape}|{corpus_crest})*

 /* bareword index names (underscore and digits ok, but no '.', '-', or '+') */
index_char	[^ \t\n\r\f\v\0&|!?^%,:;#*=~(){}<>\[\]\\/\'\".$@+-]
index_name      ({index_char}|{symbol_cescape})+

 /* single-quoted symbols */
sq_text         ([^\']|{symbol_cescape})*

 /* bareword dates (>= 4 digits of year, otherwise breaks {count(...) #by[$w=1-1]}) */
 /*date_bare	[0-9]{4,}(-[0-9]{1,2}){1,2}*/
date_bare	[+-]?[0-9]{4,}(-[0-9]{1,2}){1,2}

 /* regexes */
regex_text      ((\\.)|[^\\/])*
regex_modifier	[dgimsx]

 /* lexer block-comments */
comment_text	(\\.|[^\]])*

/*======================================================================
 * Start States
 */
 /*%x Q_INT*/

%s S_NOID

%x Q_DATE
%x Q_REGOPT
%x Q_REGREP
%x Q_XPIPE
%x Q_COMMENT
%x Q_CORPORA

 /* Q_MATCHID: non-exclusive state for expecting match-IDs
  * - ignores (hyphenated) bareword symbols
  * - used for parsing e.g. count(..) #by[$x=1+1] --> count(...) #by[$x =1 + 1]
  */
%s Q_MATCHID

/*======================================================================
 * Rules
 */
%%

 /* block-comments */
"#["				{ yy_push_state(Q_COMMENT); }
<Q_COMMENT>"]"			{ yy_pop_state(); }
<Q_COMMENT>{comment_text}	{ DDC_LEXER_COMMENT(return BLOCK_COMMENT); }

 /* line-comments */
"#:"([^\n]*)			{ DDC_LEXER_COMMENT(return LINE_COMMENT); }

 /* operators */
"&&"				{ return OP_BOOL_AND; }
"||"				{ return OP_BOOL_OR; }
(?i:near)			{ return NEAR; }
(?i:"!="|"&!="|"&="{ws}*!|!with|with(out|{ws}*!))   { return WITHOUT; }
(?i:"|="|withor|orwith|wor)   	{ return WITHOR; }
(?i:"&="|with)			{ return WITH; }
(?i:count)			{ return COUNT; }
(?i:keys)			{ return KEYS; }

 /* count-by keywords */
(?i:(file|doc)_?id)		{ return KW_FILEID; }
(?i:(file|doc)_?(name)?)	{ return KW_FILENAME; }
(?i:date)			{ BEGIN(Q_DATE); return KW_DATE; }
<Q_DATE>{ws}+			{ ; /* whitespace: skip */ }
<Q_DATE>"/"			{ BEGIN(INITIAL); return '/'; }
<Q_DATE>""/.			{ BEGIN(INITIAL); }

 /* query operators */
(?i:#(comment|cmt))			{ return KW_COMMENT; }
(?i:#(co?n?te?xt?|n))			{ return CNTXT; }
(?i:#(with)?in)				{ return WITHIN; }
(?i:#(sep(arate)?|nojoin)(_hits)?)	{ return SEPARATE_HITS; }
(?i:#(nosep(arate)?|join)(_hits)?)	{ return NOSEPARATE_HITS; }
(?i:#has(_field)?)			{ return HAS_FIELD; }
(?i:#file(_?)names)			{ return FILENAMES_ONLY; }
(?i:#debug_rank)			{ return DEBUG_RANK; }
(?i:#(greater|de?sc)(_by)?_rank)	{ return GREATER_BY_RANK; }
(?i:#(less|asc)(_by)?_rank)		{ return LESS_BY_RANK; }
(?i:#(greater|de?sc)(_by)?_date)	{ return GREATER_BY_DATE; }
(?i:#(less|asc)(_by)?_date)		{ return LESS_BY_DATE; }
(?i:#(is_|has_)?date)			{ return IS_DATE; }
(?i:#(greater|de?sc)(_by)?_size)	{ return GREATER_BY_SIZE; }
(?i:#(less|asc)(_by)?_size)		{ return LESS_BY_SIZE; }
(?i:#(is_|has_)?size)			{ return IS_SIZE; }
(?i:#((less|asc)(_by)?_)?left)		{ return LESS_BY_LEFT; }
(?i:#((greater|de?sc)(_by)?_)left)	{ return GREATER_BY_LEFT; }
(?i:#((less|asc)(_by)?_)?right)		{ return LESS_BY_RIGHT; }
(?i:#((greater|de?sc)(_by)?_)right)	{ return GREATER_BY_RIGHT; }
(?i:#((less|asc)(_by)?_)?mid(dle)?)	{ return LESS_BY_MIDDLE; }
(?i:#((greater|de?sc)(_by)?_)mid(dle)?) { return GREATER_BY_MIDDLE; }
(?i:#(less|asc)(_by)?)			{ return LESS_BY; }
(?i:#(greater|de?sc)(_by)?)		{ return GREATER_BY; }
(?i:#rand(om)?)				{ return RANDOM; }
(?i:#by)				{ return BY; }
(?i:#samp(le)?)				{ return SAMPLE; }
(?i:#clim(it)?)				{ return CLIMIT; }
(?i:#((less|asc)(_by)?_key))		{ return LESS_BY_KEY; }
(?i:#((greater|de?sc)(_by)?_key))	{ return GREATER_BY_KEY; }
(?i:#((less|asc)(_by)?_(count|val(ue)?)))	{ return LESS_BY_COUNT; }
(?i:#((greater|de?sc)(_by)?_(count|val(ue)?)))	{ return GREATER_BY_COUNT; }


 /* regexes */
"!/"{regex_text}"/"/{regex_modifier}		{ yytext+=2; yyleng-=3; BEGIN(Q_REGOPT); return NEG_REGEX; /* negated regex, +modifiers */ }
"!/"{regex_text}"/"				{ yytext+=2; yyleng-=3;                  return NEG_REGEX; /* negated regex, -modifiers */ }
"/"{regex_text}"/"/{regex_modifier}		{ yytext++;  yyleng-=2; BEGIN(Q_REGOPT); return REGEX; /* slash-quoted regex, +modifiers */ }
"/"{regex_text}"/"				{ yytext++;  yyleng-=2;                  return REGEX; /* slash-quoted regex, -modifiers */ }
"s/"{regex_text}"/"				{ yytext+=2; yyleng-=3; BEGIN(Q_REGREP); return REGEX_SEARCH;  /* search-replace pattern */ }
<Q_REGREP>{regex_text}"/"/{regex_modifier}	{            yyleng--;  BEGIN(Q_REGOPT); return REGEX_REPLACE; /* search-replace replacement, +modifiers */ }
<Q_REGREP>{regex_text}"/"			{            yyleng--;  BEGIN(INITIAL);  return REGEX_REPLACE; /* search-replace replacement, -modifiers */ }
<Q_REGOPT>{regex_modifier}+			{                       BEGIN(INITIAL);  return REGOPT; }

 /* punctuation */
"#="				{ return HASH_EQUAL; /* hash+equal: exact distance */ }
"#<"				{ return HASH_LESS; /* hash+less: max distance */ }
"#>"				{ return HASH_GREATER; /* hash+greater: min distance */ }
"$."				{ return DOLLAR_DOT; /* dollar+dot: anchor operator (position-index in segment) */ }
":{"				{ return COLON_LBRACE; /* thesaurus-query opener */ }
"@{"				{ return AT_LBRACE; /* literal-set opener */ }
"*{"				{ return STAR_LBRACE; /* prefix-set opener */ }
"}*"				{ return RBRACE_STAR; /* suffix-set closer */ }
[!.,;=@%^#~/]			{ return (int)yytext[0]; /* single-character punctuation operators */ }
[\[\]{}()<>]			{ return (int)yytext[0]; /* parentheses */ }
[\"]				{ return (int)yytext[0]; /* double-quotes */ }

 /* subcorpus lists */
":"				{ BEGIN(Q_CORPORA); return ':'; }
<Q_CORPORA>{corpus_text}	{ return SYMBOL;			/* corpora: bare subcorpus label */ }
<Q_CORPORA>\'{sq_text}\'        { yytext++; yyleng-=2; return SYMBOL;	/* corpora: single-quoted symbol */ }
<Q_CORPORA>","			{ return (int)yytext[0];		/* corpora: comma separator */ }
<Q_CORPORA>{ws}+		{ ;					/* corpora: whitespace: skip */ }
<Q_CORPORA>""/.			{ BEGIN(INITIAL); 			/* corpora: end of list */ }

 /* truncated symbols */
"*"\'{sq_text}\'"*"		{ yytext+=2; yyleng-=4; return INFIX;  /* dual-truncated quoted string (infix symbol) */ }
\'{sq_text}\'"*"		{ yytext++;  yyleng-=3; return PREFIX; /* right-truncated quoted string (prefix symbol) */ }
"*"\'{sq_text}\'		{ yytext+=2; yyleng-=3; return SUFFIX; /* left-truncated quoted string (suffix symbol) */ }

"*"{symbol_text}"*"		{ yytext++; yyleng-=2; return INFIX;  /* dual-truncated bare string (infix symbol) */ }
{symbol_text}"*"		{           yyleng--; return PREFIX; /* right-truncated bare string (prefix symbol) */ }
"*"{symbol_text}		{ yytext++; yyleng--; return SUFFIX; /* left-truncated bare string (suffix symbol) */ }

 /* numeric tokens */
 /* + fix mantis bug #14812: put these AFTER truncated symbols so that e.g. (19*) is paresed as ('19'*) rather than ('19' && *) */
\'[+-]?[0-9]+\'			{ yytext++; yyleng-=2; return INTEGER; }
[+-]?[0-9]+/{int_boundary}	{ return INTEGER; }
[+-]?[0-9]+			{ return INTEGER; }

\'[0-9\-]+\'			{ yytext++; yyleng-=2; return DATE; }
{date_bare}/{int_boundary}	{ return DATE; /* bareword date: beware of mantis #19051 (symbol:"6-er") */ }

 /* single-term wildcard */
"*"				{ return '*'; }

 /* term expander pipelines */
"|"				{ BEGIN(Q_XPIPE); }
<Q_XPIPE>{ws}+			{ ; /* whitespace: skip */ }
<Q_XPIPE>"-"			{ yyleng=0;            BEGIN(INITIAL); return EXPANDER; /* default term expander (alias "-" for "") */ }
<Q_XPIPE>\'{sq_text}\'		{ yytext++; yyleng-=2; BEGIN(INITIAL); return EXPANDER; /* quoted term expander label */ }
<Q_XPIPE>{symbol_text}		{                      BEGIN(INITIAL); return EXPANDER; /* bare term expander label */ }
<Q_XPIPE><<EOF>>		{ yyleng=0;	       BEGIN(INITIAL); return EXPANDER; /* empty term expander label (default) */ }
<Q_XPIPE>""			{ yyleng=0;	       BEGIN(INITIAL); return EXPANDER; /* empty term expander label (default) */ }

 /* index names (special handling to allow count(foo) #by[$w+1] */
"$"{index_name}			{ yytext++; yyleng--;   return INDEX; /* dollar-prefixed index name bareword */ }
"$'"{sq_text}"'"		{ yytext+=2; yyleng-=3; return INDEX; /* dollar-prefixed index name, quoted */ }
"$"				{ return '$';   		      /* bare dollar */ }

 /* symbols (initial state only) */
\'{sq_text}\'                   { yytext++; yyleng-=2; return SYMBOL; /* single-quoted symbol */ }
<INITIAL>{symbol_text}		{ return SYMBOL;                      /* bareword symbol (initial state only; not in Q_MATCHID) */ }

 /* misc */
{ws}+    			{ ; /* whitespace: skip */ }
.				{ return (int)yytext[0]; /* any other character (byte) is its own token */ }

%%
/*======================================================================
 * C Code
 */
int yyqLexer::yywrap(void) { return 1; }

void yyqLexer::yy_begin(int new_state) { BEGIN(new_state); }
