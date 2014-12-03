//-*- Mode: C++ -*-
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

#ifndef DDC_QUERY_H
#define DDC_QUERY_H

#include "../ConcordLib/QueryNode.h" 	//-- DDC-v1.x query API, wrapped here
#include "../ConcordLib/QueryOptions.h"

//======================================================================
/*!
 \brief
   Truly abstract (index-independent) representation of a parsed query
 \detail
   Should eventually replace old ad-hoc QueryNode.h 
*/
class CQuery {
public:
  //! arbitrary name for this query node (e.g. string from which it was parsed)
  string m_Label;

  //! associated query compiler (only set on Compile())
  CQueryCompiler *m_Compiler;

  //! underlying CQueryNode (DDC-v1.x API)
  CQueryNode *m_Node;

  //! root-level options (root queries only)
  CQueryOptions *m_Options;

public:
  //------------------------------------------------------------
  ///\name Constructors etc.
  //@{
  //! Default constructor
  CQuery(const string &label=string(""))
    : m_Label(label),
      m_Compiler(NULL),
      m_Node(NULL),
      m_Options(NULL)
  {};

  //! Default destructor.
  //! \li child classes should propagate deletion to daughter nodes
  //! \li default implementation calls CQuery::Clear(true) [i.e. ClearNode() and ClearOptions()]
  virtual ~CQuery(void);
  //@}

public:
  //------------------------------------------------------------
  ///\name API
  //@{
  //! Compile index-dependent query properties (required for evaluation).  Required.
  virtual bool Compile(CQueryCompiler *compiler);

  //! Compile index-dependent options in m_Options.  Optional.
  //! \li compiler defaults to this->m_Compiler
  virtual bool CompileOptions(CQueryCompiler *compiler=NULL);

  //! Wrapper for m_Node->Evaluate()
  virtual void Evaluate();

  //! For sanity checks.  Default just returns false.
  virtual bool Negated() { return false; };

  //! Toggle negation flag, returns new value.  Default throws an exception.
  virtual bool Negate();

  //! Set match-id, returns new value.  Default throws an exception
  virtual BYTE SetMatchId(BYTE matchId);

  //! Returns true iff this query uses a nontrival match-id operator; default just returns false
  virtual bool HasMatchId() const;

  //! Is this query an admissible root of a compiled parse tree (default returns !this->Negated())
  virtual bool RootOK()
  { return !this->Negated(); };

  //! \b DEBUG: return a canonical string form for this query (default just returns m_Label)
  virtual string toString() { return m_Label; };

  //! \b DEBUG: return canonical option string
  virtual string optionsToString();

  //! return a JSON representation of this query
  //! \li default just returns this->toString()
  //! \li JSON query structures relflect C++ class structures with an additional 'class_' key
  virtual string toJson() { return string("{\"class\":"+jsonStr(this->jsonClass())+","+this->jsonData()+"}"); };
  virtual string jsonClass() { return "CQuery"; };
  virtual string jsonData()  { return ""; };

  //! return json format option string
  virtual string optionsToJson();

  //@}

  //------------------------------------------------------------
  ///\name Misc Utilities
  //@{
  //! \li sets m_Compiler=compiler
  //! \li throws an exception if compiler==NULL
  //! \li calls CQuery::ClearNode()
  void SetCompiler(CQueryCompiler *compiler);

  //! deletes m_Node if non-NULL
  virtual void ClearNode();

  //! deletes m_Options if non-NULL
  virtual void ClearOptions();

  //! clear query contents.  if \c deep is true, propagates operation to daughters
  virtual void Clear(bool deep=true);

  //! set global query options ; deletes any pre-existing m_Options
  virtual void SetOptions(CQueryOptions *opts);
  //@}
};

//======================================================================
//! CQNegatable: negatable queries
class CQNegatable : public CQuery {
public:
  //! whether this query is negated
  bool m_Negated;

public:
  //! Default constructor
  CQNegatable(const string &label=string(""), bool negated=false)
    : CQuery(label), m_Negated(negated)
  {};
  CQNegatable(bool negated)
    : m_Negated(negated)
  {};

  //! toggle negation flag; returns new value
  virtual bool Negate(void);

  //! override returns current value of m_Negated
  virtual bool Negated() { return m_Negated; };

  //! string creation utility
  virtual string NegString(const std::string &s);

  //! override just calls m_Node->SetNegation(m_Negated)
  virtual bool Compile(CQueryCompiler *compiler);

  virtual string jsonClass() { return "CQNegatable"; };
  virtual string jsonData()  { return string("\"Negated\":")+(m_Negated ? "1" : "0"); };
};

//======================================================================
//! CQAtomic: atomic (sequencable) queries
class CQAtomic : public CQNegatable {
public:
  //! Default constructor
  CQAtomic(const string &label=string(""), bool negated=false)
    : CQNegatable(label,negated)
  {};

  virtual string jsonClass() { return "CQAtomic"; };
};


//======================================================================
// CQBinOp: Binary operations

//------------------------------------------------------------
//! binary operation (abstract)
class CQBinOp : public CQNegatable {
public:
  //! first argument
  CQuery *m_dtr1;

  //! second argument
  CQuery *m_dtr2;

  //! convenience: operation name
  string m_OpName;

public:
  CQBinOp(CQuery *dtr1=NULL, CQuery *dtr2=NULL, const string &opName="", bool negated=false)
    : CQNegatable(opName,negated), m_dtr1(dtr1), m_dtr2(dtr2), m_OpName(opName)
  {};

  //! destructor deletes daughters
  virtual ~CQBinOp();

  //! override propagates matchId to daughters
  virtual BYTE SetMatchId(BYTE matchId);

  //! returns true iff this query uses a nontrival match-id operator; override returns true iff either daughter does.
  virtual bool HasMatchId() const;

  //! deletes associated daughter nodes (avoiding double-free)
  virtual void ClearNode();

  //! clear query contents.  if \c deep is true, propagates operation to daughters
  virtual void Clear(bool deep=true);

  virtual bool Compile(CQueryCompiler *compiler);
  virtual string toString();
  virtual string jsonClass() { return "CQBinOp"; };
  virtual string jsonData();
};

//------------------------------------------------------------
//! logical conjunction
class CQAnd : public CQBinOp {
public:
  CQAnd(CQuery *dtr1=NULL, CQuery *dtr2=NULL)
    : CQBinOp(dtr1,dtr2,"&&")
  {};

  //! Is this query an admissible root of a compiled parse tree?
  virtual bool RootOK() { return true; };

  virtual bool Compile(CQueryCompiler *compiler);
  virtual string jsonClass() { return "CQAnd"; };
};

//------------------------------------------------------------
//! logical disjunction
class CQOr : public CQBinOp {
public:
  CQOr(CQuery *dtr1=NULL, CQuery *dtr2=NULL)
    : CQBinOp(dtr1,dtr2,"||")
  {};

  //! Is this query an admissible root of a compiled parse tree?
  virtual bool RootOK() { return true; };

  virtual bool Compile(CQueryCompiler *compiler);
  virtual string jsonClass() { return "CQOr"; };
};

//------------------------------------------------------------
//! 'WITH' query
class CQWith : public CQBinOp {
public:
  CQWith(CQuery *dtr1=NULL, CQuery *dtr2=NULL)
    : CQBinOp(dtr1,dtr2,"WITH")
  {};

  virtual bool Compile(CQueryCompiler *compiler);
  virtual string jsonClass() { return "CQWith"; };
};

//------------------------------------------------------------
//! 'WITHOUT' query
class CQWithout : public CQBinOp {
public:
  CQWithout(CQuery *dtr1=NULL, CQuery *dtr2=NULL)
    : CQBinOp(dtr1,dtr2,"WITHOUT")
  {};

  virtual bool Compile(CQueryCompiler *compiler);
  virtual string jsonClass() { return "CQWithout"; };
};


//======================================================================
// CQToken: single-token queries

//------------------------------------------------------------
//! single-token query (abstract)
class CQToken : public CQAtomic {
public:
  //! name of index to be queried (default="" (->"Token"))
  string m_IndexName;

  //! value to be searched for (default="")
  string m_Value;

  //! match-id for highlighting and context-sort reference
  //! initialized to 0; anything other than 0 or 1 is considered a non-trivial user-specified match-id
  BYTE m_MatchId;

public:
  CQToken(const string &indexName=string(""), const string &value=string(""), const BYTE matchId=0)
    : CQAtomic(value), m_IndexName(indexName), m_Value(value), m_MatchId(matchId)
  {};

  //! Set match-id, returns new value.  Override sets m_MatchId.
  virtual BYTE SetMatchId(BYTE matchId);

  //! returns true iff this query uses a nontrival match-id operator; override returns true if m_MatchId>1
  virtual bool HasMatchId() const;

  //! Compile query.  Default implementation just calls CQueryTokenNode::CreateStringPattern(m_IndexName,m_Value)
  virtual bool Compile(CQueryCompiler *compiler);

  //! Compilation utility called by default Compile() method
  //! \li SetCompiler() has already been called when this method runs
  //! \li pNode = this->m_Node is the local CQueryTokenNode created for this query
  //! \li default implementation just calls pNode->CreateStringPattern(m_IndexName,m_Value) 
  virtual bool Create(CQueryTokenNode *pNode);

  //! Compilation utility: return query-operator key for use with CConcIndexator::m_OpDefaultIndexNames
  virtual const char *OperatorKey(void) const { return "_"; };

  //! Compilation utility: get long index name (requires non-NULL compiler), empty string is returned if not found
  string IndexName(const string& DefaultIndexName=string(""));

  //! Compilation utility: get long break name (requires non-NULL compiler), empty string is returned if not found
  string BreakName(const string& DefaultBreakName=string(""));

  //! Stringification utility for use by subclasses; returns string "$INDEX=" or empty
  virtual string IndexString(void);

  //! Stringification utility for use by subclasses; default returns sqString(m_Value)
  virtual string ValueString(void);

  //! Stringification utility for use by subclasses; default should be sensible
  virtual string MatchIdString(void);

  //! Default stringification: NegString(IndexString() + ValueString())
  virtual string toString(void);

  //! json stringification utility
  virtual string jsonValue(void);

  virtual string jsonClass() { return "CQToken"; };
  virtual string jsonData();
};

//------------------------------------------------------------
//! single-token query: exact full-string match
class CQTokExact : public CQToken {
public:
  CQTokExact(const string &indexName=string(""), const string &value=string(""))
    : CQToken(indexName,value)
  {};

  virtual const char *OperatorKey(void) const { return "@_"; };
  virtual string ValueString();

  virtual string jsonClass() { return "CQTokExact"; };
};

//------------------------------------------------------------
//! single-token query: arbitrary token (indexName and value are ignored)
class CQTokAny : public CQToken {
public:
  CQTokAny(const string &indexName=string(""), const string &value=string("*"))
    : CQToken("",value)
  {};

  virtual const char *OperatorKey(void) const { return "*"; };
  virtual bool Create(CQueryTokenNode *pNode);
  virtual string ValueString();
  virtual string jsonClass() { return "CQTokAny"; };
};


//------------------------------------------------------------
//! single-token query: positional anchor
class CQTokAnchor : public CQToken {
public:
  int m_ValueInt;

public:
  CQTokAnchor(const string &indexName=string(""), const string &value=string(""))
    : CQToken(indexName,value)
  {
    m_ValueInt = strtol(value.c_str(), NULL, 0);
  };

  virtual const char *OperatorKey(void) const { return "."; };
  virtual bool Create(CQueryTokenNode *pNode);
  virtual string IndexString(void);
  virtual string ValueString();
  virtual string jsonClass() { return "CQTokAnchor"; };
  virtual string jsonValue() { return Format("%d", m_ValueInt); };
};

//------------------------------------------------------------
//! single-token query: regex
class CQTokRegex : public CQToken {
public:
  bool m_bRegexNegated;
public:
  CQTokRegex(const string &indexName=string(""), const string &regex=string(""), bool negated=false)
    : CQToken(indexName,regex), m_bRegexNegated(negated)
  {};

  virtual const char *OperatorKey(void) const { return "/_/"; };
  virtual bool Create(CQueryTokenNode *pNode);
  virtual string ValueString();
  virtual string jsonClass() { return "CQTokRegex"; };
};

//------------------------------------------------------------
// json-stringification utilities

inline string jsonStr(BYTE b)
{ return Format("%u",b); };

inline string jsonStr(CQuery *q)
{ return q->toJson(); };

template<class Container>
string jsonArray(const Container &values)
{
  string s("[");
  for (typename Container::const_iterator vi=values.begin(); vi != values.end(); vi++) {
    if (s.size() > 1) s.push_back(',');
    s += jsonStr(*vi);
  }
  s.push_back(']');
  return s;
};



//------------------------------------------------------------
//! single-token query: disjunction over a finite set of values
class CQTokSet : public CQToken {
public:
  //! set of user-specified target forms
  set<string> m_Values;

public:
  CQTokSet(const string &indexName=string(""), const string& rawValue=string(""), const set<string>& values=set<string>())
    : CQToken(indexName,rawValue), m_Values(values)
  {};

  virtual bool Create(CQueryTokenNode *pNode);
  virtual const char *OperatorKey(void) const { return "@_"; };

  //! utility for use by subclasses: comma-separated list of strings in \a values
  string SetValueString(const set<string> &values);

  //! wrapper for SetValueString(m_Values)
  inline string SetValueString(void) { return SetValueString(m_Values); };

  //! wrapper for jsonArray(m_Values)
  inline string jsonValues(void) { return jsonArray(m_Values); };

  //! ValueString() returns "@{" + SetValueString() + "}"
  virtual string ValueString(void);

  virtual string jsonClass() { return "CQTokSet"; };
  virtual string jsonValue() { return jsonValues(); };
};

//------------------------------------------------------------
//! single-token query: expanded using CTermExpander.h interface
class CQTokInfl : public CQTokSet {
public:
  //! expansion chain labels (empty list uses default expander for current index or identity)
  vector<string> m_Expanders;

  //! expansion chain; see TermExpander.h
  TxChain m_Txc;

public:
  CQTokInfl(const string &indexName=string(""), const string &value=string(""), const vector<string> expanders=vector<string>())
    : CQTokSet(indexName,value), m_Expanders(expanders), m_Txc("(CQTokInfl)")
  {};

  CQTokInfl(const string &indexName=string(""), const set<string> &values=set<string>(), const vector<string> expanders=vector<string>())
    : CQTokSet(indexName,string(""),values), m_Expanders(expanders), m_Txc("(CQTokInfl)")
  {};


  //! utility gets expansion chain for m_Expanders in m_Txc; requires non-NULL m_Compiler
  //! \li if m_Expanders is empty, uses default expansion chain for index, or identity expander if none is defined
  //! \li an empty string in m_Expanders likewise corresponds to the default expansion chain
  //! \li throws an exception if an otherwise unknown expander is referenced
  //! \li returns m_Txc (by reference)
  TxChain& GetChain(void);

  virtual const char *OperatorKey(void) const { return "_"; };
  virtual bool Create(CQueryTokenNode *pNode);
  virtual string ValueString(void);

  //! Stringification utility: returns string "%X1%X2%X3..." for m_Expanders
  virtual string ExpanderString(void);
  virtual string ExpanderJson(void);

  virtual string jsonClass() { return "CQTokInfl"; };
  virtual string jsonValue() { return CQToken::jsonValue(); };
  virtual string jsonData();
};

//------------------------------------------------------------
//! single-token query: set expanded using CTermExpander.h interface
class CQTokSetInfl : public CQTokInfl {
public:
  //! raw input values
  set<string> m_RawValues;

public:
  CQTokSetInfl(const string &indexName=string(""), const set<string> &values=set<string>(), const vector<string> expanders=vector<string>())
    : CQTokInfl(indexName,values,expanders)
  { m_RawValues = m_Values; };

  virtual bool Create(CQueryTokenNode *pNode);
  virtual string ValueString(void);

  virtual string jsonClass() { return "CQTokSetInfl"; };
  virtual string jsonValue() { return CQTokSet::jsonValue(); };
};

//------------------------------------------------------------
//! single-token query: prefix (right-truncated) query PREFIX*
class CQTokPrefix : public CQToken {
public:
  CQTokPrefix(const string &indexName=string(""), const string &prefix=string(""))
    : CQToken(indexName,prefix)
  {};

  virtual const char *OperatorKey(void) const { return "/_/"; };
  virtual bool Create(CQueryTokenNode *pNode);
  virtual string ValueString();

  virtual string jsonClass() { return "CQTokPrefix"; };
};

//------------------------------------------------------------
//! single-token query: suffix (left-truncated) query *SUFFIX
class CQTokSuffix : public CQToken {
public:
  CQTokSuffix(const string &indexName=string(""), const string &suffix=string(""))
    : CQToken(indexName,suffix)
  {};
  virtual const char *OperatorKey(void) const { return "/_/"; };
  virtual bool Create(CQueryTokenNode *pNode);
  virtual string ValueString();
  virtual string jsonClass() { return "CQTokSuffix"; };
};

//------------------------------------------------------------
//! single-token query: infix (substring) query *INFIX*
class CQTokInfix : public CQToken {
public:
  CQTokInfix(const string &indexName=string(""), const string &infix=string(""))
    : CQToken(indexName,infix)
  {};
  virtual const char *OperatorKey(void) const { return "/_/"; };
  virtual bool Create(CQueryTokenNode *pNode);
  virtual string ValueString();
  virtual string jsonClass() { return "CQTokInfix"; };
};

//------------------------------------------------------------
//! single-token query: prefix-set (right-truncated) query {PREFIX,...}*
class CQTokPrefixSet : public CQTokSet {
public:
  CQTokPrefixSet(const string &indexName=string(""), const set<string> &prefixes=set<string>())
    : CQTokSet(indexName,"",prefixes)
  {};
  virtual const char *OperatorKey(void) const { return "/_/"; };
  virtual bool Create(CQueryTokenNode *pNode);
  virtual string ValueString();
  virtual string jsonClass() { return "CQTokPrefixSet"; };
};

//------------------------------------------------------------
//! single-token query: suffix-set (left-truncated) query *{SUFFIX,...}
class CQTokSuffixSet : public CQTokSet {
public:
  CQTokSuffixSet(const string &indexName=string(""), const set<string> &suffixes=set<string>())
    : CQTokSet(indexName,"",suffixes)
  {};
  virtual const char *OperatorKey(void) const { return "/_/"; };
  virtual bool Create(CQueryTokenNode *pNode);
  virtual string ValueString();
  virtual string jsonClass() { return "CQTokSuffixSet"; };
};

//------------------------------------------------------------
//! single-token query: infix-set (substring) query *{INFIX,...}*
class CQTokInfixSet : public CQTokSet {
public:
  CQTokInfixSet(const string &indexName=string(""), const set<string> &infixes=set<string>())
    : CQTokSet(indexName,"",infixes)
  {};
  virtual const char *OperatorKey(void) const { return "/_/"; };
  virtual bool Create(CQueryTokenNode *pNode);
  virtual string ValueString();
  virtual string jsonClass() { return "CQTokInfixSet"; };
};

//------------------------------------------------------------
//! single-token query: morph pattern (compiles, but UNTESTED)
class CQTokMorph : public CQToken {
public:
  //! morph query items
  vector<string> m_Items;

public:
  CQTokMorph(const string &indexName=string("MorphPattern"), const vector<string>& items=vector<string>())
    : CQToken(indexName), m_Items(items)
  { if (!m_Items.empty()) m_Value=m_Items[0]; };

  //! append an item to the current list
  void Append(const string &item) { m_Items.push_back(item); };

  virtual const char *OperatorKey(void) const { return "[_]"; };
  virtual bool Create(CQueryTokenNode *pNode);
  virtual string ValueString();

  virtual string jsonClass() { return "CQTokMorph"; };
  virtual string jsonValue() { return jsonArray(m_Items); };
};

//------------------------------------------------------------
//! single-token query: literal lemma match "%LEMMA" (compiles, but UNTESTED under LemmaQueryUsesMorphPattern=true (default))
class CQTokLemma : public CQTokMorph {
public:
  CQTokLemma(const string &indexName=string("Lemma"), const string &value=string(""))
    : CQTokMorph(indexName,vector<string>(1,value))
  {};

  virtual const char *OperatorKey(void) const { return "%_"; };
  virtual bool Create(CQueryTokenNode *pNode);
  virtual string ValueString();

  virtual string jsonClass() { return "CQTokLemma"; };
  virtual string jsonValue() { return CQToken::jsonValue(); };
};

//------------------------------------------------------------
//! single-token query: thesaurus (compiles, but UNTESTED)
class CQTokThes : public CQToken {
public:
  CQTokThes(const string &indexName=string("Thes"), const string &value=string(""))
    : CQToken(indexName,value)
  {};

  virtual const char *OperatorKey(void) const { return ":{_}"; };
  virtual bool Create(CQueryTokenNode *pNode);
  virtual string ValueString();

  virtual string jsonClass() { return "CQTokThes"; };
};

//------------------------------------------------------------
//! single-token query: chunk (compiles, but UNTESTED)
class CQTokChunk : public CQToken {
public:
  CQTokChunk(const string &indexName=string(""), const string &value=string(""))
    : CQToken(indexName,value)
  {};

  virtual const char *OperatorKey(void) const { return "^_"; };
  virtual bool Create(CQueryTokenNode *pNode);
  virtual string ValueString();
  virtual string jsonClass() { return "CQTokChunk"; };
};

//------------------------------------------------------------
//! single-token query: file list (UNSAFE)
class CQTokFile : public CQToken {
public:
  CQTokFile(const string &indexName=string(""), const string &fileName=string(""))
    : CQToken(indexName,fileName)
  {};

  virtual const char *OperatorKey(void) const { return "<_"; };
  virtual bool Create(CQueryTokenNode *pNode);
  virtual string ValueString();
  virtual string jsonClass() { return "CQTokFile"; };
};


//======================================================================
// Misc

//------------------------------------------------------------
//! 'NEAR' query (e.g. NEAR(a,b,2))
//! un-ordered proximity constraint over 2 sub-queries
class CQNear : public CQNegatable {
public:
  //! first query argument (required)
  CQuery *m_dtr1;

  //! second query argument (required)
  CQuery *m_dtr2;

  //! thrid query argument (NULL for none)
  CQuery *m_dtr3;

  //! maximum distance
  BYTE    m_Dist;

public:
  CQNear(BYTE dist=1, CQuery *dtr1=NULL, CQuery *dtr2=NULL, CQuery *dtr3=NULL)
    : m_dtr1(dtr1), m_dtr2(dtr2), m_dtr3(dtr3), m_Dist(dist)
  {};

  //! destructor deletes daughter nodes
  virtual ~CQNear();

  //! deletes associated daughter nodes (avoiding double-free)
  virtual void ClearNode();

  //! clear query contents.  if \c deep is true, propagates operation to daughters
  virtual void Clear(bool deep=true);

  //! Set match-id, returns new value.
  virtual BYTE SetMatchId(BYTE matchId);

  //! Returns true iff this query uses a nontrival match-id operator.
  virtual bool HasMatchId() const;

  //! Compile() method implicitly compiles daughter nodes
  virtual bool Compile(CQueryCompiler *compiler);

  virtual string toString();

  virtual string jsonClass() { return "CQNear"; };
  virtual string jsonData();
};

//------------------------------------------------------------
//! sequence query (e.g. "a #1 b #1 c")
//! This class holds a sequence of nodes of type CQToken (slot m_Items).
//! Distance constraints: between \c m_Items[i] and \c m_Items[i+1] must be
//!  \li no more than \c m_Dists[i] tokens if \c m_DistOps[i] == '<' (default)
//!  \li no less than \c m_Dists[i] tokens if \c m_DistOps[i] == '>'
//!  \li exactly      \c m_Dists[i] tokens if \c m_DistOps[i] == '='
class CQSeq : public CQAtomic {
public:
  //! items to be queried (must be token nodes)
  vector<CQToken*> m_Items;

  //! distances between items
  vector<BYTE>	m_Dists;

  //! distance constraint relations
  vector<BYTE>	m_DistOps;

public:
  //! literal constructor (unused)
  CQSeq(const vector<CQToken*> &items, const vector<BYTE> &dists, const vector<BYTE> &distops)
    : m_Items(items), m_Dists(dists), m_DistOps(distops)
  {};

  //! constructor for atomic (1-token) sequences
  CQSeq(CQToken *item)
    : m_Items(1,item)
  {};

  //! destructor deletes all child nodes in m_Items
  virtual ~CQSeq();

  //! Set match-id, returns new value.
  virtual BYTE SetMatchId(BYTE matchId);

  //! Returns true iff this query uses a nontrival match-id operator.
  virtual bool HasMatchId() const;

  //! ClearNode() clears associated m_Node's pointer vector to avoid double-free
  virtual void ClearNode();

  //! clear query contents.  if \c deep is true, propagates operation to daughters
  virtual void Clear(bool deep=true);

  //! append another (item,distance) pair onto this sequence
  //! \c nextDist is ignored if this is the first item in the sequence
  void Append(CQToken *nextItem, BYTE nextDist=0, BYTE nextDistOp='<');

  //! Compile() method implicitly compiles daughter nodes
  virtual bool Compile(CQueryCompiler *compiler);
  virtual string toString();

  virtual string jsonClass() { return "CQSeq"; };
  virtual string jsonData();
};


#endif /* DDC_QUERY_H */
