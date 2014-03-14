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
#include "StdConc.h"
#include "QueryCompiler.h"
#include "Bibliography.h"
#include <stdarg.h>

#ifdef DETECT_MEMORY_LEAK
	#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
	#endif
#endif

// DEBUG_PARSER : define this to debug the lexer+parser pair
#undef DEBUG_PARSER
#undef DEBUG_LEXER
#undef DEBUG_QSTRING

//#define DEBUG_PARSER 1
//#define DEBUG_LEXER 1
//#define DEBUG_QSTRING 1

#include <sstream>


extern int yyqdebug;
int yyqparse (void *);

int yyqlex (void* valp, void* _p)
{
	CQueryCompiler* _prs =  (CQueryCompiler*)_p;

	return _prs->yyqlex(valp);
};


void yyqerror(const char *a)
{
	const char * s = a;
};





CQueryCompiler::CQueryCompiler(const CConcHolder* pHolder) 
	:	m_pQuery(NULL)
{
	m_pHolder = pHolder;
	m_ContextSentencesCount = 0;
	m_bSeparateHits = false;
	m_bEnableBibliographyForThisQuery = true;
	m_bDebugRank = false;
	m_CurrentNodeIndex = 0;
}

CQueryCompiler::~CQueryCompiler()
{
	CleanParser();	
}

int CQueryCompiler::GetNewNodeIndex()
{
	m_CurrentNodeIndex++;
	return m_CurrentNodeIndex - 1;
}
size_t CQueryCompiler::GetNodeIndicesCount() const
{
	return (size_t)m_CurrentNodeIndex;
}

bool CQueryCompiler::CompileFilters()
{
	bool rc=true;

	//-- clear compiled filter list
	m_Filters.clear();
	m_Filters.reserve(m_QFilters.size());

	//-- compile abstract filters in m_QFilters to old-style m_Filters
	for (CQFilterList::iterator fi=m_QFilters.begin(); rc && fi != m_QFilters.end(); fi++) {
		assert(*fi != NULL);
		rc = (rc && (*fi)->Compile(this));
	}

	//-- find the last run-time sort operator and swap it out the back of the list
	//   for easy access (used to present the result hit set in the proper order)
	for (int i=m_Filters.size()-1;  i>=0; i--) {
		if(m_Filters[i].m_FilterType != NoSort) {
			if (i+1 != m_Filters.size())
				swap(m_Filters[i],  m_Filters.back());
			break;
		}
	}

	//-- sanity checks for compiler-global flags
	if (m_ContextSentencesCount > m_MaxContextSentencesCount)
		throw CExpc(errParseError, "Requested context window of length=%d exceeds maximum context size=%d", m_ContextSentencesCount, m_MaxContextSentencesCount);

	//-- index-dependent flag-setting from old CQueryParser::ParseQuery()
	m_HitTypeStr = m_pHolder->m_pIndexator->WithinBreakName(m_Within);
	m_TextAreaNo = m_pHolder->m_pIndexator->m_Bibl.WithinTextArea(m_Within);

	return rc;
}

bool CQueryCompiler::Compile()
{
	assert(m_pQuery != NULL);

	if (!m_pQuery->RootOK())
		throw CExpc(errParseError, "unsupported negation or invalid query root `%s'", m_pQuery->toString().c_str());

	return (CompileFilters() && m_pQuery->Compile(this));
}

bool	CQueryCompiler::Evaluate()
{
	assert (m_pQuery != NULL);
	if (!m_pQuery)
		return false;
	if (m_pQuery->m_Compiler != this && !Compile())
		return false;
	m_pQuery->Evaluate() ; 
	return true;
}


const char* ContextStarter =  "#Cntxt";
const char* ContextStarterLower =  "#cntxt";

const size_t SortOperatorsCount = 13;
string SortOperators[SortOperatorsCount] = 
{"#less_by_date", "#greater_by_date", "#is_date",
"#less_by", "#greater_by", 
"#less_by_size", "#greater_by_size", "#is_size",
"#has_field", "#less_by_rank", "#greater_by_rank",
"#left", "#right"};


// It is very  important that our LEX@Yacc is reentrant
// since we use bison declaration %pure-parser
// we also use %option c++ for flex compilation, so  we believe that 
// CQueryCompiler::ParseQuery is thread-safe

bool CQueryCompiler::ParseQuery(const string &QueryStr)
{
#ifdef DEBUG_LEXER
	yy_flex_debug = 1;
#endif
#ifdef DEBUG_PARSER
	yyqdebug = 1;
	fprintf(stderr, "CQueryCompiler::ParseQuery(): BEGIN: q=(%s)\n", QueryStr.c_str());
#endif
	CleanParser();
	if (QueryStr.empty()) return false;
	istringstream QueryStream(QueryStr+"\n"); //-- ensure that query ends with whitespace!

	// We must reset the scanner start condition, i.e., call BEGIN(INITIAL)
	// For example, if the previous call was halted in the
	// state which was not "INITIAL", and the previous call returned "Parse error", 
	// then right now the parser is in  the last state,  which is not  "INITIAL".
	//yy_start = 0;
	//switch_streams((istream*)(&QueryStream), 0);
	yyrestart((istream*)(&QueryStream));
	yylineno = 1;


	if (yyqparse((void*)this) != 0) {
		CleanParser();
		return false;
	}

	//-- DEBUG: dump finished parse
	assert(m_pQuery != NULL);
#if DEBUG_QSTRING
	fprintf(stderr, "\nCQueryCompiler::ParseQuery(): parsed final query: %s\n", QueryToString().c_str());
#endif

	return true;
}


void CQueryCompiler::CleanParser()
{
	m_Labels.clear();
	DeleteTree();
	m_CurrentNodeIndex = 0;

	//-- clear global filter list
	for (CQFilterList::iterator fi=m_QFilters.begin(); fi != m_QFilters.end(); fi++) {
		if (*fi != NULL) delete *fi;
	}
	m_QFilters.clear();
	m_Filters.clear();

	//-- clear global query flags
	m_Within.clear();
	m_HitTypeStr.clear();
	m_Subcorpora.clear();
	m_WordSet.clear();
	m_MorphItems.clear();
	m_Expanders.clear();
	m_FilterField.clear();
	m_FilterLB.clear();
	m_FilterUB.clear();
	m_TextAreaNo = UnknownTextAreaNo;
	m_bEnableBibliographyForThisQuery = true;
	m_bDebugRank = false;
	m_ContextSentencesCount = 0;
	m_bSeparateHits = false;
}

void CQueryCompiler::DeleteTree()
{
	for (vector<CQuery*>::reverse_iterator qi=m_Queries.rbegin(); qi != m_Queries.rend(); qi++) {
		if (*qi == NULL) continue;
		(*qi)->Clear(false);
		delete *qi;
	}
	m_Queries.clear();
	m_pQuery = NULL;
}


int CQueryCompiler::yyqlex(void* valp)
{
	int iRetVal = this->yylex();
	const char* __s = yytext();
	int len = yyleng();

	//-- sanity check
	if (yyleng() >= DDC_STATIC_BUFLEN) {
		//assert (yyleng() < DDC_STATIC_BUFLEN);
		throw CExpc(errParseError, "CQueryCompiler::yyqlex(): query string exceeds maximum static buffer length (%d)", DDC_STATIC_BUFLEN);
	}
	
	string s(yytext(), yyleng()); //-- temporary
	size_t gpos; //-- temporary

	switch (iRetVal) {
	case REGEX:
	case NEG_REGEX:
		m_Regex = s;
	case SYMBOL:
	case INFIX:
	case PREFIX:
	case SUFFIX:
	case INTEGER:
	case DATE:
	case EXPANDER:
		((YYSTYPE *)valp)->m_str = newString(s);
		break;
	case REGOPT:
		//-- hack: interpret 'g' modifer as "match whole string only"
		if ((gpos=s.find('g')) != s.npos) {
			m_Regex.insert(0,"^(?:");
			m_Regex.append(")$");
			do {
				s.erase(gpos,1);
				gpos = s.find('g',gpos);
			} while (gpos != s.npos);
		}
		if (!s.empty()) m_Regex.insert(0, string("(?") + s + ")");  //-- insert pcre modifiers
		((YYSTYPE *)valp)->m_str = newString(m_Regex);
		break;
	default:
		((YYSTYPE *)valp)->m_str = NULL;
		break;
	}

	return (iRetVal);
}

string* CQueryCompiler::newString(const string& s)
{
	m_Labels.push_back(s);
	return &(m_Labels.back());
}

void CQueryCompiler::SetFilterBounds(const string& lb, const string& ub)
{
	m_FilterLB=lb;
	m_FilterUB=ub;
}

//-- debug
string CQueryCompiler::QueryToString(void)
{
	string qs;
	if (m_pQuery != NULL) {
		qs += m_pQuery->toString();
	}
	if (!m_HitTypeStr.empty()) {
		qs += string(" #WITHIN '") + escapeChars(m_HitTypeStr,"\\'") + "'";
	}
	if (m_ContextSentencesCount != 0) {
		qs += Format(" #CNTXT %u", m_ContextSentencesCount);
	}
	if (m_bSeparateHits) {
		qs += " #SEPARATE";
	}
	if (!m_bEnableBibliographyForThisQuery) {
		qs += " #FILENAMES";
	}
	if (m_bDebugRank) {
		qs += " #DEBUG_RANK";
	}
	if (!m_QFilters.empty()) {
		string fs;
		for (CQFilterList::iterator fi=m_QFilters.begin(); fi != m_QFilters.end(); fi++) {
			if (*fi == NULL) continue; //-- should never happen
			if (!fs.empty()) fs.push_back(' ');
			fs += (*fi)->toString();
		}
		qs += string(" ") + fs;
	}
	if (!m_Subcorpora.empty()) {
		string cs;
		for (CQSubcorpusList::iterator ci=m_Subcorpora.begin(); ci != m_Subcorpora.end(); ci++) {
			if (!cs.empty()) cs.push_back(',');
			cs += string("'") + escapeChars(*ci,"\\'") + "'";
		}
		if (!cs.empty()) qs += string(" :") + cs;
	}
	return qs;
}

//----------------------------------------------------------------------
// ERROR REPORTING

void CQueryCompiler::barf(const std::string& msg) const throw(CExpc)
{
	throw CExpc(errParseError, msg);
}

#define BARFSIZE 1024
void CQueryCompiler::barf(const char *fmt, ...) const throw(CExpc)
{
	char buf[BARFSIZE];
	va_list arglst;
	va_start(arglst, fmt);
	vsnprintf(buf, BARFSIZE, fmt, arglst);
	va_end(arglst);

	throw CExpc(errParseError, buf);
}

void CQueryCompiler::yybarf(const char *yymsg) const throw(CExpc)
{
	barf("could not parse query: %s at line %d, near token `%s'", yymsg, lineno(), YYText());
}
