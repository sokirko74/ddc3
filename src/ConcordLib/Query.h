#ifndef DDC_QUERY_H
#define DDC_QUERY_H

#include "../ConcordLib/QueryNode.h"    //-- DDC-v1.x query API, wrapped here
#include "../ConcordLib/QueryOptions.h"

extern const BYTE DefaultMatchId;

//======================================================================
/*
  
  Truly abstract (index-independent) representation of a parsed query
  
  Should eventually replace old ad-hoc QueryNode.h 
*/
class CQuery : public CQueryObject {
public:
    // arbitrary name for this query node (e.g. string from which it was parsed)
    std::string m_Label;

    // associated query compiler (only set on Compile())
    CQueryCompiler *m_Compiler;

    // underlying CQueryNode (DDC-v1.x API)
    CQueryNode *m_Node;

    // root-level options (root queries only)
    CQueryOptions *m_Options;

public:
    //------------------------------------------------------------
    // Constructors etc.
    //
    // Default constructor
    CQuery(const std::string &label=std::string(""))
        : m_Label(label),
          m_Compiler(NULL),
          m_Node(NULL),
          m_Options(NULL)
    {};

    // Default destructor.
    // - child classes should propagate deletion to daughter nodes
    // - default implementation calls CQuery::Clear(true) [i.e. ClearNode() and ClearOptions()]
    virtual ~CQuery(void);
    //

public:
    //------------------------------------------------------------
    // API
    //
    // Run fast (un)satisfiability checks for query before Compile() is called.
    // - called via CQueryCompiler::CheckSatisfiable()
    // - default implementation just wraps m_Options->CheckSatisfiable(compiler)
    // returns false if this query is trivially unsatisfiable for compiler
    virtual bool CheckSatisfiable(CQueryCompiler *compiler);
    
    // Compile index-dependent query properties (required for evaluation).  Required.
    // - called once per leaf-corpus query by CConcHolder::GetOccurrences() or CConcHolder::GetHits() via CQueryCompiler::Compile()
    virtual bool Compile(CQueryCompiler *compiler);

    // Compile index-dependent options in m_Options.  Optional.
    // - compiler defaults to this->m_Compiler
    virtual bool CompileOptions(CQueryCompiler *compiler=NULL);

    // Wrapper for m_Node->Evaluate()
    // - called once per leaf-corpus "search period" by CConcHolder::GetAllHits() via CQueryCompiler::Evaluate()
    virtual void Evaluate();

    // For sanity checks.  Default just returns false.
    virtual bool Negated() { return false; };

    // Toggle negation flag, returns new value.  Default throws an exception.
    virtual bool Negate();

    // Get current match-id (should return a nontrivial match-id if any was used, else 0; default just returns 0)
    virtual BYTE GetMatchId() const;

    // Set match-id, returns new value.  Default throws an exception.
    virtual BYTE SetMatchId(BYTE matchId);

    // Returns true iff this query uses a nontrival match-id operator; default checks (this->GetMatchId() != 0)
    virtual bool HasMatchId() const;

    // Is this query an admissible root of a compiled parse tree (default returns !this->Negated())
    virtual bool RootOK()
    { return !this->Negated(); };
    //

    //------------------------------------------------------------
    // Stringification (CQueryObject API & associated utilities)
    //
    // DEBUG: return a canonical string form for this query (default just returns m_Label)
    virtual std::string toString() { return m_Label; };

    // DEBUG: return canonical option string
    virtual std::string optionsToString();

    // return json format option string
    virtual std::string optionsToJson();

    // return a JSON representation of this query
    // - default just returns this->toString()
    // - JSON query structures relflect C++ class structures with an additional "class" key
    virtual std::string toJson() { return std::string("{\"class\":"+jsonStr(this->jsonClass())+","+this->jsonData()+"}"); };
    virtual std::string jsonClass() { return "CQuery"; };
    virtual std::string jsonData()  { return ""; };
    //

    //------------------------------------------------------------
    // Misc Utilities
    //
    // - sets m_Compiler=compiler
    // - throws an exception if compiler==NULL
    // - calls CQuery::ClearNode()
    void SetCompiler(CQueryCompiler *compiler);

    // deletes m_Node if non-NULL
    virtual void ClearNode();

    // deletes m_Options if non-NULL
    virtual void ClearOptions();

    // clear query contents.  if deep is true, propagates operation to daughters
    virtual void Clear(bool deep=true);

    // set global query options ; deletes any pre-existing m_Options
    virtual void SetOptions(CQueryOptions *opts);
    //
};

//======================================================================
// CQNegatable: negatable queries
class CQNegatable : public CQuery {
public:
    // whether this query is negated
    bool m_Negated;

public:
    // Default constructor
    CQNegatable(const std::string &label=std::string(""), bool negated=false)
        : CQuery(label), m_Negated(negated)
    {};
    CQNegatable(bool negated)
        : m_Negated(negated)
    {};

    virtual ~CQNegatable() {};

    // toggle negation flag; returns new value
    virtual bool Negate(void);

    // override returns current value of m_Negated
    virtual bool Negated() { return m_Negated; };

    // string creation utility
    virtual std::string NegString(const std::string &s);

    // override just calls m_Node->SetNegation(m_Negated)
    virtual bool Compile(CQueryCompiler *compiler);

    //-- CQueryObject API
    virtual std::string jsonClass() { return "CQNegatable"; };
    virtual std::string jsonData()  { return std::string("\"Negated\":")+(m_Negated ? "1" : "0"); };
};

//======================================================================
// CQAtomic: atomic (sequencable) queries
class CQAtomic : public CQNegatable {
public:
    // Default constructor
    CQAtomic(const std::string &label=std::string(""), bool negated=false)
        : CQNegatable(label,negated)
    {};
    virtual ~CQAtomic() {};

    //-- CQueryObject API
    virtual std::string jsonClass() { return "CQAtomic"; };
};


//======================================================================
// CQBinOp: Binary operations

//------------------------------------------------------------
// binary operation (abstract)
class CQBinOp : public CQNegatable {
public:
    // first argument
    CQuery *m_dtr1;

    // second argument
    CQuery *m_dtr2;

    // convenience: operation name
    std::string m_OpName;

public:
    CQBinOp(CQuery *dtr1=NULL, CQuery *dtr2=NULL, const std::string &opName="", bool negated=false)
        : CQNegatable(opName,negated), m_dtr1(dtr1), m_dtr2(dtr2), m_OpName(opName)
    {};

    // destructor deletes daughters
    virtual ~CQBinOp();

    // get match id: dtr2 > dtr1
    virtual BYTE GetMatchId() const;

    // override propagates matchId to daughters
    virtual BYTE SetMatchId(BYTE matchId);

    // deletes associated daughter nodes (avoiding double-free)
    virtual void ClearNode();

    // clear query contents.  if deep is true, propagates operation to daughters
    virtual void Clear(bool deep=true);

    // compile the query
    virtual bool Compile(CQueryCompiler *compiler);

    //-- CQueryObject API
    virtual std::string toString();
    virtual std::string jsonClass() { return "CQBinOp"; };
    virtual std::string jsonData();
};

//------------------------------------------------------------
// logical conjunction
class CQAnd : public CQBinOp {
public:
    CQAnd(CQuery *dtr1=NULL, CQuery *dtr2=NULL)
        : CQBinOp(dtr1,dtr2,"&&")
    {};
    virtual ~CQAnd() {};

    virtual bool RootOK() { return true; };
    virtual bool Compile(CQueryCompiler *compiler);
    virtual std::string jsonClass() { return "CQAnd"; };
};

//------------------------------------------------------------
// logical conjunction (implicit)
class CQAndImplicit : public CQAnd {
public:
    CQAndImplicit(CQuery *dtr1=NULL, CQuery *dtr2=NULL)
        : CQAnd(dtr1,dtr2)
    {
        //m_OpName.clear();
    };

    virtual ~CQAndImplicit() {};

    virtual std::string jsonClass() { return "CQAndImplicit"; };
};

//------------------------------------------------------------
// logical disjunction
class CQOr : public CQBinOp {
public:
    CQOr(CQuery *dtr1=NULL, CQuery *dtr2=NULL)
        : CQBinOp(dtr1,dtr2,"||")
    {};
    virtual ~CQOr() {};

    virtual bool RootOK() { return true; };
    virtual bool Compile(CQueryCompiler *compiler);
    virtual std::string jsonClass() { return "CQOr"; };
};

//------------------------------------------------------------
// 'WITH' query
class CQWith : public CQBinOp {
public:
    // match-id for highlighting (TODO: and context-sort reference)
    // initialized to 0; anything other than 0 is considered a non-trivial user-specified match-id
    BYTE m_MatchId;

public:
    CQWith(CQuery *dtr1=NULL, CQuery *dtr2=NULL, BYTE matchId=0)
        : CQBinOp(dtr1,dtr2,"WITH"), m_MatchId(matchId)
    {};
    virtual ~CQWith() {};

    // get match id: local > dtr2 > dtr1
    virtual BYTE GetMatchId() const;

    // set local match-id ONLY
    virtual BYTE SetMatchId(BYTE matchId);

    virtual bool Compile(CQueryCompiler *compiler);

    //-- CQueryObject API
    virtual std::string jsonClass() { return "CQWith"; };
    virtual std::string jsonData();
    virtual std::string toString();
};

//------------------------------------------------------------
// 'WITHOUT' query
class CQWithout : public CQWith {
public:
    CQWithout(CQuery *dtr1=NULL, CQuery *dtr2=NULL, BYTE matchId=0)
        : CQWith(dtr1,dtr2,matchId)
    {
        m_OpName = "WITHOUT";
    };
    virtual ~CQWithout() {};

    virtual bool Compile(CQueryCompiler *compiler);
    virtual std::string jsonClass() { return "CQWithout"; };
};

//------------------------------------------------------------
// 'WITHOR' query
class CQWithor : public CQWith {
public:
    CQWithor(CQuery *dtr1=NULL, CQuery *dtr2=NULL, BYTE matchId=0)
        : CQWith(dtr1,dtr2,matchId)
    {
        m_OpName = "WITHOR";
    };
    virtual ~CQWithor() {};

    virtual bool Compile(CQueryCompiler *compiler);
    virtual std::string jsonClass() { return "CQWithor"; };
};


//======================================================================
// CQToken: single-token queries

//------------------------------------------------------------
// single-token query (abstract)
class CQToken : public CQAtomic {
public:
    // name of index to be queried (default="" (->"Token"))
    std::string m_IndexName;

    // value to be searched for (default="")
    std::string m_Value;

    // match-id for highlighting (TODO: and context-sort reference)
    // initialized to 0; anything other than 0 is considered a non-trivial user-specified match-id
    BYTE m_MatchId;

public:
    CQToken(const std::string &indexName=std::string(""), const std::string &value=std::string(""), const BYTE matchId=0)
        : CQAtomic(value), m_IndexName(indexName), m_Value(value), m_MatchId(matchId)
    {};
    virtual ~CQToken() {};

    // get local match-id
    virtual BYTE GetMatchId() const;

    // Set match-id, returns new value.  Override sets m_MatchId.
    virtual BYTE SetMatchId(BYTE matchId);

    // Compile query.  Default implementation just calls CQueryTokenNode::CreateStringPattern(m_IndexName,m_Value)
    virtual bool Compile(CQueryCompiler *compiler);

    // Compilation utility called by default Compile() method
    // - SetCompiler() has already been called when this method runs
    // - pNode = this->m_Node is the local CQueryTokenNode created for this query
    // - default implementation just calls pNode->CreateStringPattern(m_IndexName,m_Value) 
    virtual bool Create(CQueryTokenNode *pNode);

    // Compilation utility: return query-operator key for use with CConcIndexator::m_OpDefaultIndexNames
    virtual const char *OperatorKey(void) const { return "_"; };

    // Compilation utility: get long index name (requires non-NULL compiler), empty string is returned if not found
    std::string IndexName(const std::string& DefaultIndexName=std::string(""));

    // Compilation utility: get long break name (requires non-NULL compiler), empty string is returned if not found
    std::string BreakName(const std::string& DefaultBreakName=std::string(""));

    // Stringification utility for use by subclasses; returns string "$INDEX=" or empty
    virtual std::string IndexString(void);

    // Stringification utility for use by subclasses; default returns sqString(m_Value)
    virtual std::string ValueString(void);

    // Stringification utility for use by subclasses; default should be sensible
    virtual std::string MatchIdString(void);

    //-- CQueryObject API & utilities
    // Default stringification: NegString(IndexString() + ValueString())
    virtual std::string toString(void);

    // json stringification utility
    virtual std::string jsonValue(void);

    virtual std::string jsonClass() { return "CQToken"; };
    virtual std::string jsonData();
};

//------------------------------------------------------------
// single-token query: exact full-string match
class CQTokExact : public CQToken {
public:
    CQTokExact(const std::string &indexName=std::string(""), const std::string &value=std::string(""))
        : CQToken(indexName,value)
    {};
    virtual ~CQTokExact() {};

    virtual const char *OperatorKey(void) const { return "@_"; };
    virtual std::string ValueString();

    virtual std::string jsonClass() { return "CQTokExact"; };
};

//------------------------------------------------------------
// single-token query: arbitrary token (indexName and value are ignored)
class CQTokAny : public CQToken {
public:
    CQTokAny(const std::string &indexName=std::string(""), const std::string &value=std::string("*"))
        : CQToken(indexName,value)
    {};
    virtual ~CQTokAny() {};

    virtual const char *OperatorKey(void) const { return "*"; };
    virtual bool Create(CQueryTokenNode *pNode);
    virtual std::string ValueString();
    virtual std::string jsonClass() { return "CQTokAny"; };
};


//------------------------------------------------------------
// single-token query: positional anchor
class CQTokAnchor : public CQToken {
public:
    int m_ValueInt;

public:
    CQTokAnchor(const std::string &indexName=std::string(""), const std::string &value=std::string(""))
        : CQToken(indexName,value)
    {
        m_ValueInt = strtol(value.c_str(), NULL, 0);
    };
    virtual ~CQTokAnchor() {};

    virtual const char *OperatorKey(void) const { return "."; };
    virtual bool Create(CQueryTokenNode *pNode);
    virtual std::string IndexString(void);
    virtual std::string ValueString();
    virtual std::string jsonClass() { return "CQTokAnchor"; };
    virtual std::string jsonValue() { return Format("%d", m_ValueInt); };
};

//------------------------------------------------------------
// single-token query: regex
class CQTokRegex : public CQToken {
public:
    bool m_bRegexNegated;
public:
    CQTokRegex(const std::string &indexName=std::string(""), const std::string &regex=std::string(""), bool negated=false)
        : CQToken(indexName,regex), m_bRegexNegated(negated)
    {};
    virtual ~CQTokRegex() {};

    virtual const char *OperatorKey(void) const { return "/_/"; };
    virtual bool Create(CQueryTokenNode *pNode);
    virtual std::string ValueString();
    virtual std::string jsonClass() { return "CQTokRegex"; };
};

//------------------------------------------------------------
// single-token query: disjunction over a finite set of values
class CQTokSet : public CQToken {
public:
    // set of user-specified target forms
    std::set<std::string> m_Values;

public:
    CQTokSet(const std::string &indexName=std::string(""), const std::string& rawValue=std::string(""), const std::set<std::string>& values=std::set<std::string>())
        : CQToken(indexName,rawValue), m_Values(values)
    {};
    virtual ~CQTokSet() {};

    virtual bool Create(CQueryTokenNode *pNode);
    virtual const char *OperatorKey(void) const { return "@_"; };

    // utility for use by subclasses: comma-separated list of strings in values
    std::string SetValueString(const std::set<std::string> &values);

    // wrapper for SetValueString(m_Values)
    inline std::string SetValueString(void) { return SetValueString(m_Values); };

    // wrapper for jsonArray(m_Values)
    inline std::string jsonValues(void) { return jsonArray(m_Values); };

    // ValueString() returns "" + SetValueString() + "}"
    virtual std::string ValueString(void);

    virtual std::string jsonClass() { return "CQTokSet"; };
    virtual std::string jsonValue() { return jsonValues(); };
};

//------------------------------------------------------------
// single-token query: expanded using CTermExpander.h interface
class CQTokInfl : public CQTokSet {
public:
    // expansion chain labels (empty list uses default expander for current index or identity)
    std::vector<std::string> m_Expanders;

    // expansion chain; see TermExpander.h
    TxChain m_Txc;

public:
    CQTokInfl(const std::string &indexName=std::string(""), const std::string &value=std::string(""), const std::vector<std::string> expanders=std::vector<std::string>())
        : CQTokSet(indexName,value), m_Expanders(expanders), m_Txc("(CQTokInfl)")
    {};

    CQTokInfl(const std::string &indexName=std::string(""), const std::set<std::string> &values=std::set<std::string>(), const std::vector<std::string> expanders=std::vector<std::string>())
        : CQTokSet(indexName,std::string(""),values), m_Expanders(expanders), m_Txc("(CQTokInfl)")
    {};

    virtual ~CQTokInfl() {};


    // utility gets expansion chain for m_Expanders in m_Txc; requires non-NULL m_Compiler
    // - if m_Expanders is empty, uses default expansion chain for index, or identity expander if none is defined
    // - an empty string in m_Expanders likewise corresponds to the default expansion chain
    // - throws an exception if an otherwise unknown expander is referenced
    // - returns m_Txc (by reference)
    TxChain& GetChain(void);

    virtual const char *OperatorKey(void) const { return "_"; };
    virtual bool Create(CQueryTokenNode *pNode);
    virtual std::string ValueString(void);

    // Stringification utility: returns string "%X1%X2%X3..." for m_Expanders
    virtual std::string ExpanderString(void);
    virtual std::string ExpanderJson(void);

    virtual std::string jsonClass() { return "CQTokInfl"; };
    virtual std::string jsonValue() { return CQToken::jsonValue(); };
    virtual std::string jsonData();
};

//------------------------------------------------------------
// single-token query: set expanded using CTermExpander.h interface
class CQTokSetInfl : public CQTokInfl {
public:
    // raw input values
    std::set<std::string> m_RawValues;

public:
    CQTokSetInfl(const std::string &indexName=std::string(""), const std::set<std::string> &values=std::set<std::string>(), const std::vector<std::string> expanders=std::vector<std::string>())
        : CQTokInfl(indexName,values,expanders)
    { m_RawValues = m_Values; };

    virtual ~CQTokSetInfl() {};

    virtual bool Create(CQueryTokenNode *pNode);
    virtual std::string ValueString(void);

    virtual std::string jsonClass() { return "CQTokSetInfl"; };
    virtual std::string jsonValue() { return CQTokSet::jsonValue(); };
};

//------------------------------------------------------------
// single-token query: prefix (right-truncated) query PREFIX*
class CQTokPrefix : public CQToken {
public:
    CQTokPrefix(const std::string &indexName=std::string(""), const std::string &prefix=std::string(""))
        : CQToken(indexName,prefix)
    {};

    virtual ~CQTokPrefix() {};

    virtual const char *OperatorKey(void) const { return "/_/"; };
    virtual bool Create(CQueryTokenNode *pNode);
    virtual std::string ValueString();

    virtual std::string jsonClass() { return "CQTokPrefix"; };
};

//------------------------------------------------------------
// single-token query: suffix (left-truncated) query *SUFFIX
class CQTokSuffix : public CQToken {
public:
    CQTokSuffix(const std::string &indexName=std::string(""), const std::string &suffix=std::string(""))
        : CQToken(indexName,suffix)
    {};
    virtual ~CQTokSuffix() {};
    virtual const char *OperatorKey(void) const { return "/_/"; };
    virtual bool Create(CQueryTokenNode *pNode);
    virtual std::string ValueString();
    virtual std::string jsonClass() { return "CQTokSuffix"; };
};

//------------------------------------------------------------
// single-token query: infix (substring) query *INFIX*
class CQTokInfix : public CQToken {
public:
    CQTokInfix(const std::string &indexName=std::string(""), const std::string &infix=std::string(""))
        : CQToken(indexName,infix)
    {};
    virtual ~CQTokInfix() {};
    virtual const char *OperatorKey(void) const { return "/_/"; };
    virtual bool Create(CQueryTokenNode *pNode);
    virtual std::string ValueString();
    virtual std::string jsonClass() { return "CQTokInfix"; };
};

//------------------------------------------------------------
// single-token query: prefix-set (right-truncated) query {PREFIX,...}*
class CQTokPrefixSet : public CQTokSet {
public:
    CQTokPrefixSet(const std::string &indexName=std::string(""), const std::set<std::string> &prefixes=std::set<std::string>())
        : CQTokSet(indexName,"",prefixes)
    {};
    virtual ~CQTokPrefixSet() {};
    virtual const char *OperatorKey(void) const { return "/_/"; };
    virtual bool Create(CQueryTokenNode *pNode);
    virtual std::string ValueString();
    virtual std::string jsonClass() { return "CQTokPrefixSet"; };
};

//------------------------------------------------------------
// single-token query: suffix-set (left-truncated) query *{SUFFIX,...}
class CQTokSuffixSet : public CQTokSet {
public:
    CQTokSuffixSet(const std::string &indexName=std::string(""), const std::set<std::string> &suffixes=std::set<std::string>())
        : CQTokSet(indexName,"",suffixes)
    {};
    virtual ~CQTokSuffixSet() {};
    virtual const char *OperatorKey(void) const { return "/_/"; };
    virtual bool Create(CQueryTokenNode *pNode);
    virtual std::string ValueString();
    virtual std::string jsonClass() { return "CQTokSuffixSet"; };
};

//------------------------------------------------------------
// single-token query: infix-set (substring) query *{INFIX,...}*
class CQTokInfixSet : public CQTokSet {
public:
    CQTokInfixSet(const std::string &indexName=std::string(""), const std::set<std::string> &infixes=std::set<std::string>())
        : CQTokSet(indexName,"",infixes)
    {};
    virtual ~CQTokInfixSet() {};
    virtual const char *OperatorKey(void) const { return "/_/"; };
    virtual bool Create(CQueryTokenNode *pNode);
    virtual std::string ValueString();
    virtual std::string jsonClass() { return "CQTokInfixSet"; };
};

//------------------------------------------------------------
// single-token query: morph pattern (compiles, but UNTESTED)
class CQTokMorph : public CQToken {
public:
    // morph query items
    std::vector<std::string> m_Items;

public:
    CQTokMorph(const std::string &indexName=std::string("MorphPattern"), const std::vector<std::string>& items=std::vector<std::string>())
        : CQToken(indexName), m_Items(items)
    { if (!m_Items.empty()) m_Value=m_Items[0]; };

    virtual ~CQTokMorph() {};

    // append an item to the current list
    void Append(const std::string &item) { m_Items.push_back(item); };

    virtual const char *OperatorKey(void) const { return "[_]"; };
    virtual bool Create(CQueryTokenNode *pNode);
    virtual std::string ValueString();

    virtual std::string jsonClass() { return "CQTokMorph"; };
    virtual std::string jsonValue() { return jsonArray(m_Items); };
};

//------------------------------------------------------------
// single-token query: lemma-search "%LEMMA" (UNTESTED under LemmaQueryUsesMorphPattern=true (default))
class CQTokLemma : public CQTokMorph {
public:
    CQTokLemma(const std::string &indexName=std::string("Lemma"), const std::string &value=std::string(""))
        : CQTokMorph(indexName,std::vector<std::string>(1,value))
    {};
    virtual ~CQTokLemma() {};

    virtual const char *OperatorKey(void) const { return "%_"; };
    virtual bool Create(CQueryTokenNode *pNode);
    virtual std::string ValueString();

    virtual std::string jsonClass() { return "CQTokLemma"; };
    virtual std::string jsonValue() { return CQToken::jsonValue(); };
};

//------------------------------------------------------------
// single-token query: thesaurus (compiles, but UNTESTED)
class CQTokThes : public CQToken {
public:
    CQTokThes(const std::string &indexName=std::string("Thes"), const std::string &value=std::string(""))
        : CQToken(indexName,value)
    {};
    virtual ~CQTokThes() {};

    virtual const char *OperatorKey(void) const { return ":{_}"; };
    virtual bool Create(CQueryTokenNode *pNode);
    virtual std::string ValueString();

    virtual std::string jsonClass() { return "CQTokThes"; };
};

//------------------------------------------------------------
// single-token query: chunk (compiles, but UNTESTED)
class CQTokChunk : public CQToken {
public:
    CQTokChunk(const std::string &indexName=std::string(""), const std::string &value=std::string(""))
        : CQToken(indexName,value)
    {};
    virtual ~CQTokChunk() {};

    virtual const char *OperatorKey(void) const { return "^_"; };
    virtual bool Create(CQueryTokenNode *pNode);
    virtual std::string ValueString();
    virtual std::string jsonClass() { return "CQTokChunk"; };
};

//------------------------------------------------------------
// single-token query: file list (UNSAFE)
class CQTokFile : public CQToken {
public:
    CQTokFile(const std::string &indexName=std::string(""), const std::string &fileName=std::string(""))
        : CQToken(indexName,fileName)
    {};
    virtual ~CQTokFile() {};

    virtual const char *OperatorKey(void) const { return "<_"; };
    virtual bool Create(CQueryTokenNode *pNode);
    virtual std::string ValueString();
    virtual std::string jsonClass() { return "CQTokFile"; };
};


//======================================================================
// Misc

//------------------------------------------------------------
// 'NEAR' query (e.g. NEAR(a,b,2))
// un-ordered proximity constraint over 2 sub-queries
class CQNear : public CQNegatable {
public:
    // first query argument (required)
    CQuery *m_dtr1;

    // second query argument (required)
    CQuery *m_dtr2;

    // thrid query argument (NULL for none)
    CQuery *m_dtr3;

    // maximum distance
    BYTE    m_Dist;

public:
    CQNear(BYTE dist=1, CQuery *dtr1=NULL, CQuery *dtr2=NULL, CQuery *dtr3=NULL)
        : m_dtr1(dtr1), m_dtr2(dtr2), m_dtr3(dtr3), m_Dist(dist)
    {};

    // destructor deletes daughter nodes
    virtual ~CQNear();

    // deletes associated daughter nodes (avoiding double-free)
    virtual void ClearNode();

    // clear query contents.  if deep is true, propagates operation to daughters
    virtual void Clear(bool deep=true);

    // get match-id: dtr3 > dtr2 > dtr1
    virtual BYTE GetMatchId() const;

    // Set match-id, returns new value; override propagates matchId to daughers.
    virtual BYTE SetMatchId(BYTE matchId);

    // Compile() method implicitly compiles daughter nodes
    virtual bool Compile(CQueryCompiler *compiler);

    virtual std::string toString();

    virtual std::string jsonClass() { return "CQNear"; };
    virtual std::string jsonData();
};

//------------------------------------------------------------
// sequence query (e.g. "a #1 b #1 c")
// This class holds a sequence of nodes of type CQToken (slot m_Items).
// Distance constraints: between m_Items[i] and m_Items[i+1] must be
//  - no more than m_Dists[i] tokens if m_DistOps[i] == '<' (default)
//  - no less than m_Dists[i] tokens if m_DistOps[i] == '>'
//  - exactly      m_Dists[i] tokens if m_DistOps[i] == '='
class CQSeq : public CQAtomic {
public:
    // items to be queried (must be token nodes)
    std::vector<CQToken*> m_Items;

    // distances between items
    std::vector<BYTE>  m_Dists;

    // distance constraint relations
    std::vector<BYTE>  m_DistOps;

public:
    // literal constructor (unused)
    CQSeq(const std::vector<CQToken*> &items, const std::vector<BYTE> &dists, const std::vector<BYTE> &distops)
        : m_Items(items), m_Dists(dists), m_DistOps(distops)
    {};

    // constructor for atomic (1-token) sequences
    CQSeq(CQToken *item)
        : m_Items(1,item)
    {};

    // destructor deletes all child nodes in m_Items
    virtual ~CQSeq();

    // get match-id: later nonzero matchid-items clobber earlier ones
    virtual BYTE GetMatchId() const;

    // Set match-id, returns new value; override propagates matchId to daughters.
    virtual BYTE SetMatchId(BYTE matchId);

    // ClearNode() clears associated m_Node's pointer vector to avoid double-free
    virtual void ClearNode();

    // clear query contents.  if deep is true, propagates operation to daughters
    virtual void Clear(bool deep=true);

    // append another (item,distance) pair onto this sequence
    // nextDist is ignored if this is the first item in the sequence
    void Append(CQToken *nextItem, BYTE nextDist=0, BYTE nextDistOp='<');

    // Compile() method implicitly compiles daughter nodes
    virtual bool Compile(CQueryCompiler *compiler);

    //-- CQueryObject API
    virtual std::string toString();
    virtual std::string jsonClass() { return "CQSeq"; };
    virtual std::string jsonData();
};


#endif /* DDC_QUERY_H */
