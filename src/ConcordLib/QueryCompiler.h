//-*- Mode: C++; c-basic-offset: 8; -*-
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
#if !defined(__DDC_QUERY_COMPILER_H_)
#define __DDC_QUERY_COMPILER_H_

#include <list>

#include "QueryNode.h"   // OLD query-node API
#include "Query.h"       // NEW query-node API
#include "QueryFilter.h" // NEW query-node API

#include "yyQParser.h"

//#include "yyQLexer.h"
#undef yyFlexLexer
#define yyFlexLexer yyqLexer
#include "FlexLexer.h"

//-- moo: re-working parse-tree API
#define PARSER_USE_OLD_API
#undef PARSER_USE_OLD_API

typedef vector<string>    CQSubcorpusList;
typedef vector<CQFilter*> CQFilterList;

/*!
	CQueryCompiler  is a class for the parse tree of the input query and its general properties.

	Descended from FlexLexer (abstract class of flex tool), so it should implement also 
	flex parser's  functionality (DDC uses YACC in thread-safe mode).

	moo: renamed CQueryParser to CQueryCompiler to reflect actual functionality.
*/
class CQueryCompiler : public yyqLexer
{
public:
	//! maximum context size for #cntxt operator
	static const size_t m_MaxContextSentencesCount = 5;

public:
	//! current node index to set CQueryTokenNode::m_NodeIndex
	int m_CurrentNodeIndex;

	//! list of all '#WITHIN' arguments (break collections or text areas) from currently parsed query 
	vector<string> m_Within;

	//! the break collection name which should be used while querying
	string m_HitTypeStr;

	//! the index of text area where DDC should perform the input query
	int m_TextAreaNo;

	//! (abstract) filters and sort operators which should be applied to the resulted hit set
	CQFilterList m_QFilters;

	//! (runtime) filters and sort operators which should be applied to the resulted hit set (available after Compile())
	vector<CDDCFilterWithBounds> m_Filters; 

	//! selected subcorpora for this query
	CQSubcorpusList m_Subcorpora;

	//! temporary for $i={w1,w2,...,wN} word-set queries
	set<string> m_WordSet;

	//! temporary for "% X1 % X2 ..." expansion queries
	vector<string> m_Expanders;

	//! temporary for [m1,m2,...,mN] morph-pattern queries
	vector<string> m_MorphItems;

	//! temporary for filter lower bound (#less_by_xyz, #greater_by_xyz)
	string m_FilterLB;

	//! temporary for filter upper bound (#less_by_xyz, #greater_by_xyz)
	string m_FilterUB;

	//! temporary for regexes (used for lexer handling of regex modifiers)
	string m_Regex;

	//! how many hits of the left and right context should be output (must be &lt;= m_MaxContextSentencesCount)
	size_t m_ContextSentencesCount;

	//! root of the abstract parse tree
	CQuery* m_pQuery;

	//! set of all query nodes allocated during current parse
	vector<CQuery*> m_Queries;

	//!  a reference to the holder, for which this query is parsed
	const CConcHolder* m_pHolder;


	//! a special slot for YACC (which contains all string leaves of the parse tree)
	list<string> m_Labels;

	// if true, DDC shows file names, instead of bibliographical information for this query
	//! (CConcIndexator::m_bOutputBibliographyOfHits is default value for outputting bibliography
	bool m_bEnableBibliographyForThisQuery;

	//! if true, DDC initializes CHit::m_DebugRank
	bool m_bDebugRank;

	//! if #left is specified, then m_BigramsUse is bdLeftBigram, if  #right, then m_BigramsUse is bdRightBigram, otherwize bdDontUseBigrams
	BigramDirectionEnum m_BigramsUse;

public:
	//! default constructor
	CQueryCompiler(const CConcHolder* pHolder);

	//! default destructor
	virtual ~CQueryCompiler();

	//! make this parse ready for a new call of ParseQuery()
	//! \li re-sets filters and subcorpora, deletes current parse tree (if any)
	void CleanParser();

	//! wrapper for yylex() as called from bison parser (valp is a YYSTYPE*)
	int yyqlex (void* valp);

	//! wrapper to push a new string pointer onto the m_Labels stack (to be freed on CleanParser())
	string* newString(const string &s=string(""));

	//! flex convenience wrapper
	inline const char* yytext() const { return YYText(); };

	//! flex convenience wrapper
	inline int yyleng() const { return YYLeng(); };

	//! flex convenience wrapper
	inline string yystring() const { return string(YYText(),YYLeng()); };

	//! delete parse tree (m_pQuery) if non-NULL
	void DeleteTree();

	//! parse \c QueryStr and build a parse tree for it in \c m_pQuery
	//! \li moo: this method should be safe to call even if (m_pHolder==NULL).
	//! \returns false on failure (and may throw an exception)
	bool ParseQuery(const string &QueryStr);

	//! moo: compile and apply filters in m_QFilters
	//! \li implicitly called by Compile()
	bool CompileFilters();

	//! moo: compile the current parsed query (m_pQuery) with respect to
	//! the current index (m_pHolder) and compiler options (m_HitTypeStr etc.)
	//! \li really just a wrapper for CompileFilters() && m_pQuery->Compile(this);
	//! \returns false on failure (and may throw an exception)
	bool Compile(void);

	//! evaluate parse tree bottom-up
	//! \li moo: not at all sure what this does
	bool Evaluate();

	//! return current node index to set CQueryTokenNode::m_NodeIndex
	int GetNewNodeIndex();

	//! return m_CurrentNodeIndex
	size_t	GetNodeIndicesCount() const;

	//! push a newly allocated CQuery* onto the stack.
	//! Called by bison during the parse.
	inline CQuery* PushQuery(CQuery* qp) { m_Queries.push_back(qp); return qp; };

	//! set string bounds for current filter (called by bison parser)
	void SetFilterBounds(const string& lb="", const string& ub="");

	//! debug: return a string form for the current query + operators
	string QueryToString(void);

	//! error reporting: throws a errParseError exception
	void barf(const std::string &msg) const throw(CExpc);

	//! error reporting: throws a errParseError exception with a printf() format
	void barf(const char *fmt, ...) const throw(CExpc);

	//! error reporting: throw a verbose errParseError exception using current lexer+parser context
	//! \li this is called by underlying bison parser's yyerror() routine
	void yybarf(const char *yymsg) const throw(CExpc);
};

#endif
