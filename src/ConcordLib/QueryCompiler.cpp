//-*- Mode: C++ -*-
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2020 by Bryan Jurish
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
#undef DEBUG_COMPILER
#undef DEBUG_QSTRING

//#define DEBUG_PARSER 1
//#define DEBUG_LEXER 1
//#define DEBUG_QSTRING 1

#include <sstream>


extern int yyqdebug;
int yyqparse (CQueryCompiler *_qcompiler);

int yyqlex (void* valp, CQueryCompiler* _prs)
{
    return _prs->yyqlex(valp);
};


void yyqerror(const char *a)
{
    const char * s = a;
};





CQueryCompiler::CQueryCompiler(const CConcHolder* pHolder) 
{
    m_pHolder = pHolder;
    m_pQuery  = NULL;
    m_qCountSample = DDCDefaultCountSampleSize;
    m_qCountLimit = DDCDefaultCountSampleSize;
    m_qCountSort = NoSort;
    m_CurrentNodeIndex = 0;
    m_Limit = 0;
    m_KeepLexerComments = false;
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
    assert(m_pQuery != NULL);
    return m_pQuery->CompileOptions(this);
}

bool CQueryCompiler::CheckSatisfiable(CQuery *query)
{
    return m_bSatisfiable = (query != NULL && query->CheckSatisfiable(this));
}

bool CQueryCompiler::Compile(CQuery *query)
{
    assert(query != NULL);
    if (!query->RootOK())
        throw CDDCExpc(errParseError, "unsupported negation or invalid query root `%s'", query->toString().c_str());

    return query->CompileOptions(this) && query->Compile(this);
}

bool    CQueryCompiler::Evaluate(CQuery *query)
{
    assert(query != NULL);
    if (!query)
        return false;
    if (query->m_Compiler != this && !Compile(query))
        return false;
    query->Evaluate() ; 
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
    //switch_streams((istream*)(&QueryStream), NULL);
    yybegin(0);
    yyrestart((istream*)(&QueryStream));

    //-- actual parse
    yylineno = 1;
    yybyteno = 0;
    yyDtrsPos = -1;
    yyDtrsLen = 0;
    int rc = yyqparse(this);
    if (rc != 0) {
        CleanParser();
        return false;
    }

    //-- DEBUG: dump finished parse
    assert(m_pQuery != NULL);
#if DEBUG_QSTRING
    fprintf(stderr, "\nCQueryCompiler::ParseQuery(): parsed final query: %s\n", QueryToString().c_str());
#endif

    //fprintf(stderr, "DEBUG: got subcorpora pos=%d ; len=%d -> \"%s\"\n", yyDtrsPos, yyDtrsLen, QueryStr.substr(yyDtrsPos,yyDtrsLen).c_str());

    return true;
}

void CQueryCompiler::yybegin(int new_state)
{
#if DEBUG_LEXER
    fprintf(stderr, "CQueryCompiler::yybegin(%d)\n", new_state);
#endif
    yy_begin(new_state);
}

void CQueryCompiler::CleanParser()
{
    //-- clear temporary options (before DeleteTree())
    m_qOptions.Clear();

    m_Labels.clear();
    DeleteTree();
    m_CurrentNodeIndex = 0;
    m_bSatisfiable = true;

    //-- clear global query flags
    m_qCountKeys.Clear();
    m_qCountSample = DDCDefaultCountSampleSize;
    m_qCountLimit = DDCDefaultCountSampleSize;
    m_qCountSort = NoSort;
    m_Limit = 0;
    m_qCountLo.clear();
    m_qCountHi.clear();
    m_WordSet.clear();
    m_MorphItems.clear();
    m_Expanders.clear();
    m_IndexTuple.clear();
    m_FilterField.clear();
    m_FilterLB.clear();
    m_FilterUB.clear();
    m_FilterMatchId = 0;
    m_FilterOffset = 0;
    m_RegexPattern.clear();
    m_RegexReplacement.clear();
    m_RegexModifiers.clear();
}

void CQueryCompiler::DeleteTree()
{
    for (vector<CQuery*>::reverse_iterator qi=m_Queries.rbegin(); qi != m_Queries.rend(); qi++) {
        if (*qi == NULL) continue;
        (*qi)->Clear(false);
        delete *qi;
    }
    m_Queries.clear();
    m_qCountKeys.Clear();
    m_qCountSample = DDCDefaultCountSampleSize;
    m_qCountLimit = DDCDefaultCountSampleSize;
    m_qCountSort = NoSort;
    m_Limit = 0;
    m_qCountLo.clear();
    m_qCountHi.clear();
    m_pQuery = NULL;
}


int CQueryCompiler::yyqlex(void* valp)
{
    int iRetVal;
    do {
        iRetVal = this->yylex();
        const char* __s = yytext();
        int len = yyleng();

        //-- sanity check
        if (yyleng() >= DDC_STATIC_BUFLEN) {
            //assert (yyleng() < DDC_STATIC_BUFLEN);
            throw CDDCExpc(errParseError, "CQueryCompiler::yyqlex(): query string exceeds maximum static buffer length (%d)", DDC_STATIC_BUFLEN);
        }
        
        string s(yytext(), yyleng()); //-- temporary
        size_t gpos; //-- temporary

        switch (iRetVal) {
            case REGEX:
            case NEG_REGEX:
            case REGEX_SEARCH:
                m_RegexPattern = s;
                // 2016-11-25: setting valp->m_str=&m_RegexPattern chokes on (/foo/ /bar/) --> (/bar/ /bar/)
                ((YYSTYPE *)valp)->m_str = newString(s);
                break;
            case REGOPT:
                m_RegexModifiers = s;
                ((YYSTYPE *)valp)->m_str = &m_RegexModifiers;
                break;
            case REGEX_REPLACE:
                m_RegexReplacement = s;
                ((YYSTYPE *)valp)->m_str = &m_RegexReplacement;
                break;
            case SYMBOL:
            case INDEX:
            case INFIX:
            case PREFIX:
            case SUFFIX:
            case INTEGER:
            case DATE:
            case EXPANDER:
            case KW_DATE:
            case KW_FILENAME:
            case KW_FILEID:
                ((YYSTYPE *)valp)->m_str = newString(s);
                break;
            case BLOCK_COMMENT:
                if (m_KeepLexerComments)
                    m_qOptions.m_LexerComments.push_back(string("#[")+s+"]");
                continue;
            case LINE_COMMENT:
                if (m_KeepLexerComments)
                    m_qOptions.m_LexerComments.push_back(s+"\n");
                continue;
            default:
                ((YYSTYPE *)valp)->m_str = NULL;
                break;
        }
        break;
    } while (true);

    return (iRetVal);
}

string* CQueryCompiler::newString(const string& s)
{
    m_Labels.push_back(s);
    return &(m_Labels.back());
}

string *CQueryCompiler::newRegex(const string &pattern, const string &modifiers, bool isMatch)
{
    //-- hack: interpret 'g' modifer as "match whole string only"
    string regex(pattern);
    string regopts(modifiers);
    int gpos;
    if ( (gpos=regopts.find('g')) != regopts.npos ) {
        if (isMatch) {
            regex.insert(0,"^(?:");
            regex.append(")$");
        }
        do {
            regopts.erase(gpos,1);
            gpos = regopts.find('g',gpos);
        } while (gpos != regopts.npos);
    }
    if (!regopts.empty()) {
        //-- insert pcre modifiers (except for /g)
        regex.insert(0, string("(?") + regopts + ")"); 
    }

    return newString(regex);
}

CQuery* CQueryCompiler::SetQuery(CQuery* qp)
{
    CQueryOptions *opts = new CQueryOptions();
    opts->swap(m_qOptions);
    m_qOptions.Clear();
    m_pQuery = qp;
    m_pQuery->SetOptions(opts);
    return qp;
}

CQCount* CQueryCompiler::PushCountQuery(CQuery* qConditions)
{
    this->SetQuery(qConditions);
    CQCount *qc = new CQCount(qConditions, new CQCountKeyExprList(m_qCountKeys), m_qCountSample, m_qCountSort, m_qCountLo, m_qCountHi);
    m_qCountKeys.m_Exprs.clear();
    m_qCountSample = DDCDefaultCountSampleSize;
    m_qCountSort   = NoSort;
    m_qCountLo.clear();
    m_qCountHi.clear();
    return (CQCount*)(this->PushQuery(qc));
}

CQFPrune* CQueryCompiler::newPruneFilter(HitSortEnum ftype, const string& limitStr)
{
    size_t limit = strtoul(limitStr.c_str(), NULL, 0);
    CQFPrune *fp = new CQFPrune(ftype, limit, new CQCountKeyExprList(m_qCountKeys));
    m_qCountKeys.m_Exprs.clear();
    return fp;
}

CQKeys* CQueryCompiler::PushKeysQuery(CQCount *qCount)
{
    CQKeys *qk = new CQKeys(qCount, m_qCountLimit, m_IndexTuple);
    m_IndexTuple.clear();
    m_Limit = 0;
    return (CQKeys*)(this->PushQuery(qk));
}


void CQueryCompiler::SetFilterBounds(const string& lb, const string& ub)
{
    m_FilterLB=lb;
    m_FilterUB=ub;
    //fprintf(stderr, "DEBUG: SetFilterBounds(field=%s, id=%u, offset=%d)\n", m_FilterField.c_str(), m_FilterMatchId, m_FilterOffset);
}

void CQueryCompiler::SetFilterKey(const string &field, BYTE matchid, int offset)
{
    m_FilterField   = field;
    m_FilterMatchId = matchid;
    m_FilterOffset  = offset;
    SetFilterBounds();
}

//-- debug
string CQueryCompiler::QueryToString(void)
{
    if (m_pQuery != NULL)
        return m_pQuery->toString() + m_pQuery->optionsToString();
    return "";
}

string CQueryCompiler::QueryToJson(void)
{
    if (m_pQuery)
        return string("{\"Query\":") + m_pQuery->toJson() + ",\"Options\":" + m_pQuery->optionsToJson() + "}";
    return "null";
}

//----------------------------------------------------------------------
// ERROR REPORTING

void CQueryCompiler::barf(const std::string& msg) const //throw(CExpc)
{
    throw CDDCExpc(errParseError, msg);
}

#define BARFSIZE 1024
void CQueryCompiler::barf(const char *fmt, ...) const //throw(CExpc)
{
    char buf[BARFSIZE];
    va_list arglst;
    va_start(arglst, fmt);
    vsnprintf(buf, BARFSIZE, fmt, arglst);
    va_end(arglst);

    throw CDDCExpc(errParseError, buf);
}

void CQueryCompiler::yybarf(const char *yymsg) const //throw(CExpc)
{
    barf("could not parse query: %s at line %d, near token `%s'", yymsg, lineno(), YYText());
}

ddcObjectList CQueryCompiler::Children() const
{
    ddcObjectList kids;
    if (m_pQuery) kids.push_back(m_pQuery);
    return kids;
}

void CQueryCompiler::DisownChildren()
{
    m_pQuery = NULL;
    m_Queries.clear(); //-- may leak memory after parse errors!
}

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
