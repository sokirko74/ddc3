//-*- Mode: C++; c-basic-offset: 8; -*-
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2014 by Bryan Jurish
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

#include "QueryNode.h"    // v1.x query-node API
#include "QueryFilter.h"  // v2.x query-filter API
#include "Query.h"        // v2.x query-node API (wrapper)
#include "QCount.h"	  // v2.0.23+ count-query API

#include "yyQParser.h"

//#include "yyQLexer.h"
#undef yyFlexLexer
#define yyFlexLexer yyqLexer
#include "FlexLexer.h"

//-- moo: re-working parse-tree API
#define PARSER_USE_OLD_API
#undef PARSER_USE_OLD_API

/*!
	CQueryCompiler  is a class for the parse tree of the input query and its general properties.

	Descended from FlexLexer (abstract class of flex tool), so it should implement also 
	flex parser's  functionality (DDC uses YACC in thread-safe mode).

	moo: renamed CQueryParser to CQueryCompiler to reflect actual functionality.
*/
class CQueryCompiler : public yyqLexer
{
public:
	//--------------------------------------------------------------
	// constants

	//! maximum context size for #cntxt operator
	static const size_t m_MaxContextSentencesCount = 5;

public:
	//--------------------------------------------------------------
	// top-level query properties

	//!  a reference to the holder, for which this query is parsed
	const CConcHolder* m_pHolder;

	//! root of the abstract parse tree
	CQuery* m_pQuery;

	//! query options (adopted into top-level m_pQuery on SetQuery())
	CQueryOptions m_qOptions;

	//! NEW temporary for count-by lists
	CQCountKeyExprList m_qCountKeys;

	//--------------------------------------------------------------
	// temporaries

	//! temporary for $i={w1,w2,...,wN} word-set queries
	set<string> m_WordSet;

	//! temporary for "% X1 % X2 ..." expansion queries
	vector<string> m_Expanders;

	//! temporary for [m1,m2,...,mN] morph-pattern queries
	vector<string> m_MorphItems;

	//! temporary for filter field (#less_by_xyz, #greater_by_xyz)
	string m_FilterField;

	//! temporary for filter lower bound (#less_by_xyz, #greater_by_xyz)
	string m_FilterLB;

	//! temporary for filter upper bound (#less_by_xyz, #greater_by_xyz)
	string m_FilterUB;

	//! temporary for regex patterns
	string m_RegexPattern;

	//! temporary for regex replacement strings (used by count-keys)
	string m_RegexReplacement;

	//! temporary for regex modifiers
	string m_RegexModifiers;

	//--------------------------------------------------------------
	// administrivia

	//! current node index to set CQueryTokenNode::m_NodeIndex
	int m_CurrentNodeIndex;

	//! set of all query nodes allocated during current parse
	vector<CQuery*> m_Queries;

	//! a special slot for YACC (which contains all string leaves of the parse tree)
	list<string> m_Labels;

public:
	//! default constructor
	CQueryCompiler(const CConcHolder* pHolder=NULL);

	//! default destructor
	virtual ~CQueryCompiler();

	//! make this parse ready for a new call of ParseQuery()
	//! \li re-sets filters and subcorpora, deletes current parse tree (if any)
	void CleanParser();

	//! wrapper for yylex() as called from bison parser (valp is a YYSTYPE*)
	int yyqlex (void* valp);

	//! wrapper to push a new string pointer onto the m_Labels stack (to be freed on CleanParser())
	string* newString(const string &s=string(""));

	//! wrapper for regexes, similar to "(?" + modifers + ":" + pattern + ")"
	//! \param isMatch if true (default), /g modifier will cause regex to be wrapped in '^' and '$' anchors (match whole string)
	string* newRegex(const string &pattern, const string &modifiers=string(""), bool isMatch=true);

	//! flex convenience wrapper
	inline const char* yytext() const { return YYText(); };

	//! flex convenience wrapper
	inline int yyleng() const { return YYLeng(); };

	//! flex convenience wrapper
	inline string yystring() const { return string(YYText(),YYLeng()); };

	//! delete parse tree (m_pQuery) if non-NULL; actually wipes all queries in m_Queries and m_qCountKeys
	void DeleteTree();

	//! parse \c QueryStr and build a parse tree for it in \c m_pQuery
	//! \li moo: this method should be safe to call even if (m_pHolder==NULL).
	//! \returns false on failure (and may throw an exception)
	bool ParseQuery(const string &QueryStr);

	//! moo: compile and apply filters in m_pQuery->m_Options->m_QFilters
	//! \b OBSOLETE : now just a wrapper for m_pQuery->CompileOptions(this)
	bool CompileFilters();

	//! moo: compile the given query (query) with respect to
	//! the current index (m_pHolder) and compiler options (m_HitTypeStr etc.)
	//! \li really just a wrapper for query->CompileOptions(this) && query->Compile(this)
	//! \returns false on failure (and may throw an exception)
	bool Compile(CQuery *query);

	//! evaluate parse tree bottom-up
	//! \li query defaults to m_pQuery
	bool Evaluate(CQuery *query);

	//! moo: compile the current parsed query (m_pQuery) with respect to
	//! the current index (m_pHolder) and compiler options (m_HitTypeStr etc.)
	//! \li really just a wrapper for m_pQuery->CompileOptions(this) && m_pQuery->Compile(this)
	//! \returns false on failure (and may throw an exception)
	inline bool Compile()
	{ return Compile(m_pQuery); };

	//! evaluate parse tree bottom-up; wrapper for Evaluate(m_pQuery)
	inline bool Evaluate()
	{ return Evaluate(m_pQuery); };

	//! return current node index to set CQueryTokenNode::m_NodeIndex
	int GetNewNodeIndex();

	//! return m_CurrentNodeIndex
	size_t	GetNodeIndicesCount() const;

	//! set current top-level query, adopting filters and flags; sets this->m_pQuery=qp
	//! Called by bison during the parse.
	CQuery* SetQuery(CQuery* qp);

	//! push a newly allocated CQuery* onto the stack.
	//! Called by bison during the parse.
	inline CQuery* PushQuery(CQuery* qp) { m_Queries.push_back(qp); return qp; };

	//! push a newly allocated CQCount* count-query onto the stack, setting m_CountBy
	//! Called by bison during the parse.
	CQCount* PushCountQuery(CQuery *qConditions);

	//! set string bounds for current filter (called by bison parser)
	void SetFilterBounds(const string& lb="", const string& ub="");

	//! debug: return a string form for the current query; wraps m_pQuery->toString() + m_pQuery->optionsToString()
	string QueryToString(void);

	//! return a json string form for the current query; wraps m_pQuery->toJson() + m_pQuery->optionsToJson()
	string QueryToJson(void);

	//! error reporting: throws a errParseError exception
	void barf(const std::string &msg) const throw(CExpc);

	//! error reporting: throws a errParseError exception with a printf() format
	void barf(const char *fmt, ...) const throw(CExpc);

	//! error reporting: throw a verbose errParseError exception using current lexer+parser context
	//! \li this is called by underlying bison parser's yyerror() routine
	void yybarf(const char *yymsg) const throw(CExpc);
};

#endif
