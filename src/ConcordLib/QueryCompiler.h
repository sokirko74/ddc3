#if !defined(__DDC_QUERY_COMPILER_H_)
#define __DDC_QUERY_COMPILER_H_

#include <list>

#include "QueryNode.h"    // v1.x query-node API
#include "QueryFilter.h"  // v2.x query-filter API
#include "Query.h"        // v2.x query-node API (wrapper)
#include "QCount.h"       // v2.0.23+ count-query API

#include "yyQParser.h"
//#include "yyQLexer.h" //-- included from yyQParser.h (2017-03-01)

// the system <FlexLexer.h> (package libfl-dev), for the C++ scanner class yyqFlexLexer (%option prefix="yyq");
// it may have been included already by the generated yyQLexer.h
#if !defined(yyFlexLexerOnce)
#undef yyFlexLexer
#define yyFlexLexer yyqFlexLexer
#include <FlexLexer.h>
#endif


//-- moo: re-working parse-tree API
#define PARSER_USE_OLD_API
#undef PARSER_USE_OLD_API

/*
  CQueryCompiler  is a class for the parse tree of the input query and its general properties.

  Descended from the flex scanner class yyqFlexLexer: yylex() generated from yyQLexer.l is a method
  of CQueryCompiler (%option yyclass), so the scanner actions can use its members.

  moo: renamed CQueryParser to CQueryCompiler to reflect actual functionality.
*/
// ddcq::QParser::token: the token codes (SYMBOL, REGEX, ...) returned by the scanner methods
class CQueryCompiler : public CQueryObject, public yyqFlexLexer, public ddcq::QParser::token
{
public:
    //--------------------------------------------------------------
    // constants

    // maximum context size for #cntxt operator
    static const size_t m_MaxContextSentencesCount = 5;

public:
    //--------------------------------------------------------------
    // top-level query properties

    //  a reference to the holder, for which this query is parsed
    const CConcHolder* m_pHolder;

    // root of the abstract parse tree
    CQuery* m_pQuery;

    // query options (adopted into top-level m_pQuery on SetQuery())
    CQueryOptions m_qOptions;

    // query limit (anything but 0 (default) overrides CConcHolder arguments)
    size_t m_Limit;

    // is query satisfiable? (default is true, may be set to false by CheckSatisfiable())
    bool m_bSatisfiable;

    //--------------------------------------------------------------
    // temporaries

    // count()-query keys
    CQCountKeyExprList m_qCountKeys;

    // count()-query sample size (overrides count-query m_dtr->m_Options->m_Limit if set)
    size_t m_qCountSample;

    // count()-query result-set size (for keys()-queries)
    size_t m_qCountLimit;

    // count()-query sort order
    HitSortEnum m_qCountSort;

    // count()-query lower bound
    std::string m_qCountLo;

    // count()-query upper bound
    std::string m_qCountHi;

    // keys()-query tuple
    std::vector<std::string> m_IndexTuple;

    // temporary for $i={w1,w2,...,wN} word-set queries
    std::set<std::string> m_WordSet;

    // temporary for "% X1 % X2 ..." expansion queries
    std::vector<std::string> m_Expanders;

    // temporary for [m1,m2,...,mN] morph-pattern queries
    std::vector<std::string> m_MorphItems;

    // temporary for filter field (#less_by_xyz, #greater_by_xyz)
    std::string m_FilterField;

    // temporary for filter lower bound (#less_by_xyz, #greater_by_xyz)
    std::string m_FilterLB;

    // temporary for filter upper bound (#less_by_xyz, #greater_by_xyz)
    std::string m_FilterUB;

    // temporary for filter reference match-id (#left, #right, #mid; default=0:any)
    BYTE m_FilterMatchId;

    // temporary for filter offsets (#left, #right, #mid; default=0:any)
    int m_FilterOffset;

    // temporary for regex patterns
    std::string m_RegexPattern;

    // temporary for regex replacement strings (used by count-keys)
    std::string m_RegexReplacement;

    // temporary for regex modifiers
    std::string m_RegexModifiers;

    //--------------------------------------------------------------
    // administrivia

    // current node index to set CQueryTokenNode::m_NodeIndex
    int m_CurrentNodeIndex;

    // set of all query nodes allocated during current parse
    std::vector<CQuery*> m_Queries;

    // a special slot for YACC (which contains all string leaves of the parse tree)
    std::list<std::string> m_Labels;

    // enable collection of lexer comments in m_pQuery->m_Options->m_LexerComments (default=false)
    bool m_KeepLexerComments;

public:
    // default constructor
    CQueryCompiler(const CConcHolder* pHolder=NULL);

    // default destructor
    virtual ~CQueryCompiler();

    // make this parse ready for a new call of ParseQuery()
    // - re-sets filters and subcorpora, deletes current parse tree (if any)
    void CleanParser();

    // wrapper for yylex() as called from bison parser (valp is a ddcq::QParser::value_type*)
    int yyqlex (void* valp);

    // wrapper to push a new string pointer onto the m_Labels stack (to be freed on CleanParser())
    std::string* newString(const std::string &s=std::string(""));

    // wrapper for regexes, similar to "(?" + modifers + ":" + pattern + ")"
    // isMatch: if true (default), /g modifier will cause regex to be wrapped in '^' and '$' anchors (match whole string)
    std::string* newRegex(const std::string &pattern, const std::string &modifiers=std::string(""), bool isMatch=true);

    // flex convenience wrapper
    inline std::string yystring() const { return std::string(YYText(),YYLeng()); };

    // wrapper for yy_begin()
    void yybegin(int new_state);

    //--------------------------------------------------------------
    // scanner (yyQLexer.l): yylex() is generated as a method of this class (%option yyclass)
    int yylex() override;

    // absolute byte offset in the query string (incremented by YY_USER_ACTION, reset by ParseQuery())
    int yybyteno;
    int byteno() const { return yybyteno; }

    // byte offset and length of the subcorpus list after ':' (-1 if there is none)
    int yyDtrsPos;
    int yyDtrsLen;

    // BEGIN(new_state), callable outside of the scanner actions
    void yy_begin(int new_state);

    // scanner start conditions Q_MATCHID and INITIAL, for the parser (yyQParser.y: matchid)
    void yybeginMatchId();
    void yybeginInitial();

    // delete parse tree (m_pQuery) if non-NULL; actually wipes all queries in m_Queries and m_qCountKeys
    void DeleteTree();

    // parse QueryStr and build a parse tree for it in m_pQuery
    // - moo: this method should be safe to call even if (m_pHolder==NULL).
    // returns false on failure (and may throw an exception)
    bool ParseQuery(const std::string &QueryStr);

    // moo: compile and apply filters in m_pQuery->m_Options->m_QFilters
    // OBSOLETE : now just a wrapper for m_pQuery->CompileOptions(this)
    bool CompileFilters();

    // moo: check the current parsed query (m_pQuery) for unsatisfiability with respect to
    // the current index (m_pHolder) and compiler options (m_HitTypeStr etc.)
    // - sets m_bSatisfiable to false if any trivially unsatisfiable global constraints (e.g subcorpus match, etc) are found
    // - call this and act on its return value (if at all) before calling Compile()
    // - really just a wrapper for m_pQuery->CheckSatisfiable(this)
    // returns new value of m_bSatisfiable
    bool CheckSatisfiable(CQuery* query);

    // moo: compile the given query (query) with respect to
    // the current index (m_pHolder) and compiler options (m_HitTypeStr etc.)
    // - really just a wrapper for query->CompileOptions(this) && query->Compile(this)
    // returns false on failure (and may throw an exception)
    bool Compile(CQuery *query);

    // evaluate parse tree bottom-up
    // - query defaults to m_pQuery
    bool Evaluate(CQuery *query);
    
    // wrapper for CheckSatisfiable(m_pQuery)
    // returns false on failure (and may throw an exception)
    inline bool CheckSatisfiable()
    { return CheckSatisfiable(m_pQuery); };

    // wrapper for Compile(m_pQuery)
    // returns false on failure (and may throw an exception)
    inline bool Compile()
    { return Compile(m_pQuery); };

    // evaluate parse tree bottom-up; wrapper for Evaluate(m_pQuery)
    inline bool Evaluate()
    { return Evaluate(m_pQuery); };

    // return current node index to set CQueryTokenNode::m_NodeIndex
    int GetNewNodeIndex();

    // return m_CurrentNodeIndex
    size_t  GetNodeIndicesCount() const;

    // set current top-level query, adopting filters and flags; sets this->m_pQuery=qp
    // Called by bison during the parse.
    CQuery* SetQuery(CQuery* qp);

    // push a newly allocated CQuery* onto the stack.
    // Called by bison during the parse.
    inline CQuery* PushQuery(CQuery* qp) { m_Queries.push_back(qp); return qp; };

    // push a newly allocated CQCount* count-query onto the stack, setting m_CountBy
    // Called by bison during the parse.
    CQCount* PushCountQuery(CQuery *qConditions);

    // push a newly allocated CQKeys* query onto the stack.
    // called by bison during the parse.
    CQKeys* PushKeysQuery(CQCount *qCount);

    //  allocated CQFPrune* filter onto 
    // Called by bison during the parse.
    CQFPrune* newPruneFilter(HitSortEnum ftype, const std::string& limitStr="-1");
    
    // set string bounds for current filter (called by bison parser)
    void SetFilterBounds(const std::string& lb="", const std::string& ub="");

    // set context-filter key
    void SetFilterKey(const std::string &field="", BYTE matchid=0, int offset=INT_MIN);

    // debug: return a string form for the current query; wraps m_pQuery->toString() + m_pQuery->optionsToString()
    std::string QueryToString(void);

    // return a json string form for the current query; wraps m_pQuery->toJson() + m_pQuery->optionsToJson()
    std::string QueryToJson(void);

    // error reporting: throws a errParseError exception
    void barf(const std::string &msg) const;  //throw(CExpc)

    void barf(const char *fmt, ...) const; //throw(CExpc)

    // error reporting: throw a verbose errParseError exception using current lexer+parser context
    // - this is called by underlying bison parser's yyerror() routine
    void yybarf(const char *yymsg) const; //throw(CExpc)

    //-- CQueryObject API
    virtual std::string jsonClass() { return "CQueryCompiler"; };
    virtual std::string jsonData()  { return std::string("\"Query\":" + jsonStr(m_pQuery)); };
};

#endif
