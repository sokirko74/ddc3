//-*- Mode: C++; c-basic-offset: 2; -*-
//
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

#include <Query.h>
#include <QueryCompiler.h>

//======================================================================
// CQuery

//--------------------------------------------------------------
bool CQuery::Compile(CQueryCompiler *compiler)
{
  assert(compiler!=NULL);
  throw CExpc(errParseError,"CQuery::Compile(): abstract method called!");
  return false;
}

//--------------------------------------------------------------
bool CQuery::CompileOptions(CQueryCompiler *compiler)
{
  if (compiler==NULL) compiler = m_Compiler;
  assert(compiler!=NULL);

  if (m_Options == NULL)
    m_Options = new CQueryOptions();

  return m_Options->Compile(compiler);
}

//--------------------------------------------------------------
void CQuery::SetCompiler(CQueryCompiler *compiler)
{
  assert(compiler!=NULL);
  m_Compiler = compiler;
  ClearNode();
}

//--------------------------------------------------------------
void CQuery::ClearNode()
{
  if (m_Node != NULL) {
    delete m_Node;
    m_Node = NULL;
  }
}

//--------------------------------------------------------------
void CQuery::ClearOptions()
{
  if (m_Options != NULL) {
    delete m_Options;
    m_Options = NULL;
  }
}

//--------------------------------------------------------------
void CQuery::Clear(bool deep)
{
  ClearNode();
  ClearOptions();
}

//--------------------------------------------------------------
CQuery::~CQuery(void)
{
  CQuery::Clear(true);
};

//--------------------------------------------------------------
void CQuery::Evaluate()
{
  assert(m_Node != NULL);
  assert(m_Options != NULL);
  //assert(m_Compiler != NULL);
  m_Node->Evaluate(m_Options->m_bSeparateHits);
}

//--------------------------------------------------------------
bool CQuery::Negate(void)
{
  throw CExpc(errParseError, "attempt to negate non-negatable query `%s'", toString().c_str());
  return this->Negated();
};

//--------------------------------------------------------------
void CQuery::SetOptions(CQueryOptions *opts)
{
  if (m_Options) delete m_Options;
  m_Options = opts;
}

//--------------------------------------------------------------
string CQuery::optionsToString()
{
  if (m_Options!=NULL) 
    return m_Options->toString();
  return string("");
}

//--------------------------------------------------------------
string CQuery::optionsToJson()
{
  if (m_Options!=NULL) 
    return m_Options->toJson();
  return string("null");
}


//======================================================================
// CQNegatable

//! toggle negation flag; returns new value
bool CQNegatable::Negate(void)
{
  m_Negated = !m_Negated;
  return m_Negated;
}

string CQNegatable::NegString(const std::string &s)
{
  if (!m_Negated) return s;
  //return string("(!") + s + ")";
  return string("!") + s;
};

bool CQNegatable::Compile(CQueryCompiler *compiler)
{
  if (m_Node) m_Node->SetNegation(m_Negated);
  return true;
}

//======================================================================
// CQAtomic

//======================================================================
// CQBinOp

CQBinOp::~CQBinOp()
{
  Clear(true);
}

void CQBinOp::ClearNode()
{
  if (m_dtr1) m_dtr1->ClearNode();
  if (m_dtr2) m_dtr2->ClearNode();
  if (m_Node) {
    CQueryBinaryOperationNode *bn = (CQueryBinaryOperationNode*)m_Node;
    bn->m_pChild1 = NULL;
    bn->m_pChild2 = NULL;
  }
  CQuery::ClearNode();
}

void CQBinOp::Clear(bool deep)
{
  ClearNode();
  ClearOptions();
  if (deep) {
    if (m_dtr1) delete m_dtr1;
    if (m_dtr2) delete m_dtr2;
  }
  m_dtr1=NULL;
  m_dtr2=NULL;
}

bool CQBinOp::Compile(CQueryCompiler *compiler)
{
  SetCompiler(compiler);

  //-- sanity checks
  if (!m_dtr1 || !m_dtr2)
    throw CExpc(errParseError,"not enough arguments for `%s'-clause `%s'", m_OpName.c_str(), this->toString().c_str());

  //-- compile daughters
  if (!m_dtr1->Compile(compiler))
    throw CExpc(errParseError,"could not compile sub-query `%s' for `%s'-clause", m_dtr1->toString().c_str(), m_OpName.c_str());
  if (!m_dtr2->Compile(compiler))
    throw CExpc(errParseError,"could not compile sub-query `%s' for `%s'-clause", m_dtr2->toString().c_str(), m_OpName.c_str());

  //-- child methods hook in here
  return true;
}

string CQBinOp::toString() {
  return NegString(string("(") + m_dtr1->toString() + " " + m_OpName + " " + m_dtr2->toString() + ")");
}

string CQBinOp::jsonData() {
  return (CQNegatable::jsonData()
	  +","+string("\"OpName\":")+jsonStr(m_OpName)
	  +","+string("\"Dtr1\":")+m_dtr1->toJson()
	  +","+string("\"Dtr2\":")+m_dtr2->toJson()
	  );
}

//======================================================================
// CQAnd

bool CQAnd::Compile(CQueryCompiler *compiler)
{
  if (!CQBinOp::Compile(compiler)) return false;

  //-- query logic
  bool neg1 = m_dtr1->Negated();
  bool neg2 = m_dtr2->Negated();
  if (!m_Negated) {
    //-- non-negated query (P&Q)
    if (neg1) {
      if (!neg2) {
	//-- (!P&Q): underlying CQueryAndOperation doesn't parse these right, but (Q&!P) works
	CQuery *tmp = m_dtr2;
	m_dtr2 = m_dtr1;
	m_dtr1 = tmp;
      }
      else {
	//-- (!P&!Q)
	throw CExpc(errParseError,"conjunction of negations not supported in `%s'-query `%s'", m_OpName.c_str(), this->toString().c_str());
      }
    }
  } else if (!neg1 || !neg2) {
    // !(P&Q)=(!P|!Q), !(P&!Q)=(!P|Q), !(!P&Q)=(P|!Q)
    throw CExpc(errParseError,"non-negated sub-queries not supported in negated `%s'-query `%s'", m_OpName.c_str(), this->toString().c_str());
  }

  //-- create underyling node
  CQueryAndOperation* pObj = new CQueryAndOperation;
  m_Node = pObj;
  pObj->Create(compiler->m_pHolder, m_dtr1->m_Node, m_dtr2->m_Node, string("&&"));

  return CQNegatable::Compile(compiler);
}

//======================================================================
// CQOr

bool CQOr::Compile(CQueryCompiler *compiler)
{
  if (!CQBinOp::Compile(compiler)) return false;

  //-- query logic
  bool neg1 = m_dtr1->Negated();
  bool neg2 = m_dtr2->Negated();
  if (neg1 != neg2) {
    //-- (P|!Q), (!P|Q), !(P|!Q), !(!P|Q)
    // : we could check for m_Negated here and dispatch to CQAnd, but we'll ignore it for now
    throw CExpc(errParseError,"disjunction of negated and non-negated sub-queries not supported in query `%s'", this->toString().c_str());
  } else if (m_Negated && !neg1) {
    //-- !(P|Q)
    throw CExpc(errParseError,"negated disjunction not supported in query `%s'", this->toString().c_str());
  } else if (!m_Negated && neg1) {
    //-- (!P|!Q)
    throw CExpc(errParseError,"disjunction of negations not supported in query `%s'", this->toString().c_str());
  }

  //-- create underyling node
  CQueryOrOperation* pObj = new CQueryOrOperation;
  m_Node = pObj;
  pObj->Create(compiler->m_pHolder, m_dtr1->m_Node, m_dtr2->m_Node, string("||"));

  return CQNegatable::Compile(compiler);
}

//======================================================================
// CQWith

bool CQWith::Compile(CQueryCompiler *compiler)
{
  if (!CQBinOp::Compile(compiler)) return false;

  //-- extra sanity checks
  if (m_dtr1->Negated() || m_dtr2->Negated())
    throw CExpc(errParseError, "negated sub-queries not supported in WITH query `%s'", this->toString().c_str());

  //-- create underyling node
  CQueryWithNode* pObj = new CQueryWithNode;
  m_Node = pObj;
  if ( !pObj->Create(compiler->m_pHolder, m_dtr1->m_Node, m_dtr2->m_Node) )
    throw CExpc(errParseError,"could not compile WITH clause `%s'", this->toString().c_str());

  return CQNegatable::Compile(compiler);
}

//======================================================================
// CQWithout

bool CQWithout::Compile(CQueryCompiler *compiler)
{
  if (!CQBinOp::Compile(compiler)) return false;

  //-- extra sanity checks
  if (m_dtr1->Negated() || m_dtr2->Negated())
    throw CExpc(errParseError, "negated sub-queries not supported in WITHOUT query `%s'", this->toString().c_str());

  //-- create underyling node
  CQueryWithoutNode* pObj = new CQueryWithoutNode;
  m_Node = pObj;
  if ( !pObj->Create(compiler->m_pHolder, m_dtr1->m_Node, m_dtr2->m_Node) )
    throw CExpc(errParseError,"could not compile WITHOUT clause `%s'", this->toString().c_str());

  return CQNegatable::Compile(compiler);
}

//======================================================================
// CQToken

bool CQToken::Compile(CQueryCompiler *compiler)
{
  SetCompiler(compiler);
  CQueryTokenNode* pObj = new CQueryTokenNode(compiler->GetNewNodeIndex());
  m_Node  = pObj;
  bool rc = this->Create(pObj);
  if (!rc)
    throw CExpc(errParseError,"could not compile query condition `%s'", this->toString().c_str());
  return CQNegatable::Compile(compiler);
}

bool CQToken::Create(CQueryTokenNode *pNode)
{
  return pNode->CreateStringPattern(m_Compiler->m_pHolder, this->IndexName("Token"), m_Value);
}

string CQToken::IndexName(const string& DefaultIndexName)
{
  assert(m_Compiler->m_pHolder->m_pIndexator);
  string name(m_IndexName);
  if (m_IndexName.empty()) {
    const map<string,string> &op2name = m_Compiler->m_pHolder->m_pIndexator->m_OpDefaultIndexNames;
    map<string,string>::const_iterator namei;
    if ( (namei = op2name.find(this->OperatorKey())) != op2name.end() ) {
      name = namei->second;
    } else if ( (namei = op2name.find("*")) != op2name.end() ) {
      name = namei->second;
    } else {
      name = DefaultIndexName;
    }
  }
  const CStringIndexSet* pIndexSet = m_Compiler->m_pHolder->m_pIndexator->GetIndexByNameOrShortName(name);
  if (!pIndexSet) return name; //-- default
  return pIndexSet->m_Name;
}

string CQToken::BreakName(const string& DefaultBreakName)
{
  assert(m_Compiler->m_pHolder->m_pIndexator);
  string name(m_IndexName);
  if (m_IndexName.empty()) {
    const map<string,string> &op2name = m_Compiler->m_pHolder->m_pIndexator->m_OpDefaultIndexNames;
    map<string,string>::const_iterator namei;
    if ( (namei = op2name.find(this->OperatorKey())) != op2name.end() ) {
      name = namei->second;
    } else {
      name = DefaultBreakName;
    }
  }
  const CHitBorders::CBreakCollection* pBreaks = m_Compiler->m_pHolder->m_pIndexator->GetBreakCollectionByName(name);
  if (!pBreaks) return name; //-- default
  return pBreaks->m_LongName;
}

string CQToken::IndexString(void) {
  return (m_IndexName.empty() ? string("") : (string("$") + m_IndexName + "="));
}

string CQToken::ValueString(void) {
  return sqString(m_Value);
}
string CQToken::jsonValue(void) {
  return jsonStr(m_Value);
}

string CQToken::toString(void) {
  return NegString(this->IndexString() + this->ValueString());
}

string CQToken::jsonData() {
  return (CQNegatable::jsonData()
	  +","+string("\"IndexName\":")+jsonStr(m_IndexName)
	  +","+string("\"Value\":")+this->jsonValue()
	  );
}


//======================================================================
// CQTokExact

string CQTokExact::ValueString() {
  return string("@")+sqString(m_Value);

}

//======================================================================
// CQTokAny

bool CQTokAny::Create(CQueryTokenNode *pNode)
{
  return pNode->CreateUniversalPattern(m_Compiler->m_pHolder, m_Value); //-- no index name for CQTokAny
}

string CQTokAny::ValueString()
{
  return string("*");
}

//======================================================================
// CQTokAnchor

bool CQTokAnchor::Create(CQueryTokenNode *pNode)
{
  return pNode->CreateAnchorPattern(m_Compiler->m_pHolder, this->BreakName("s"), m_ValueInt);
}

string CQTokAnchor::IndexString(void) {
  return string("$.") + m_IndexName + "=";
}

string CQTokAnchor::ValueString() {
  return Format("%d", m_ValueInt);
}

//======================================================================
// CQTokRegex

bool CQTokRegex::Create(CQueryTokenNode *pNode) {
  return pNode->CreateRegexPattern(m_Compiler->m_pHolder, this->IndexName("Token"), m_Value, m_bRegexNegated);
}

string CQTokRegex::ValueString() {
  return (m_bRegexNegated ? string("!") : string("")) + reString(m_Value);
}

//======================================================================
// CQTokSet

bool CQTokSet::Create(CQueryTokenNode *pNode) {
  return pNode->CreateSetPattern(m_Compiler->m_pHolder, this->IndexName("Token"), m_Values);
}

string CQTokSet::SetValueString(const set<string> &values)
{
  string s("");
  for (set<string>::const_iterator vi=values.begin(); vi != values.end(); vi++) {
    if (!s.empty()) s.push_back(',');
    s += sqString(*vi);
  }
  return s;
}

string CQTokSet::ValueString() {
  return string("@{") + SetValueString() + "}";
}

//======================================================================
// CQTokInfl

TxChain& CQTokInfl::GetChain(void)
{
  assert(m_Compiler->m_pHolder->m_pIndexator != NULL);
  if (m_Expanders.empty())
    m_Expanders.push_back(string(""));

  m_Txc.m_Chain.clear();
  m_Txc.m_Chain.reserve(m_Expanders.size());
  TxDispatcher &txd = m_Compiler->m_pHolder->m_pIndexator->m_Txd;
  CTermExpander *tx;
  for (vector<string>::const_iterator xi=m_Expanders.begin(); xi != m_Expanders.end(); xi++) {
    if (xi->empty()) {
      tx = txd.get(this->IndexName("Token"));
      if (tx == NULL) continue; //-- ignore undeclared default expander (identity map)
    }
    else {
      tx = txd.get(*xi);
      if (tx == NULL)
	throw CExpc(errParseError, "CQTokInfl::GetChain(): unknown term expander `%s' in query `%s'", xi->c_str(), this->toString().c_str());
    }
    m_Txc.append(tx);
  }
  m_Txc.m_Param = string("|") + m_Txc.chainString(); //-- debug

  return m_Txc;
}

bool CQTokInfl::Create(CQueryTokenNode *pNode)
{
  set<string> src;
  src.insert(m_Value);
  GetChain();
  m_Values.clear();
  m_Txc.expand(src,m_Values);
  return pNode->CreateSetPattern(m_Compiler->m_pHolder, this->IndexName("Token"), m_Values);  
}

string CQTokInfl::ExpanderString(void) {
  string s;
  for (vector<string>::const_iterator xi=m_Expanders.begin(); xi != m_Expanders.end(); xi++) {
    if (!s.empty()) s.push_back('|');
    if (xi->empty()) s.push_back('-');
    else s += sqString(*xi);
  }
  if (!s.empty()) s.insert(0,"|");
  return s;
}

string CQTokInfl::ExpanderJson(void) {
  string s("[");
  for (vector<string>::const_iterator xi=m_Expanders.begin(); xi != m_Expanders.end(); xi++) {
    if (s.size()>1) s.push_back(',');
    s += jsonStr(*xi);
  }
  s.push_back(']');
  return s;
}

string CQTokInfl::ValueString(void) {
  return CQToken::ValueString() + this->ExpanderString();
}

string CQTokInfl::jsonData() {
  return (CQToken::jsonData()
	  +",\"Expanders\":"+this->ExpanderJson()
	  );
}

//======================================================================
// CQTokSetInfl


bool CQTokSetInfl::Create(CQueryTokenNode *pNode)
{
  set<string> src(m_RawValues);
  GetChain();
  m_Values.clear();
  m_Txc.expand(src,m_Values);
  return pNode->CreateSetPattern(m_Compiler->m_pHolder, this->IndexName("Token"), m_Values);  
}

string CQTokSetInfl::ValueString(void) {
  return string("{") + SetValueString(m_RawValues) + "}" + this->ExpanderString();
}

//======================================================================
// CQTokPrefix

bool CQTokPrefix::Create(CQueryTokenNode *pNode) {
  return pNode->CreatePrefixPattern(m_Compiler->m_pHolder, this->IndexName("Token"), m_Value);
}
string CQTokPrefix::ValueString(void) {
  return sqString(m_Value) + "*";
}

//======================================================================
// CQTokSuffix

bool CQTokSuffix::Create(CQueryTokenNode *pNode) {
  return pNode->CreateSuffixPattern(m_Compiler->m_pHolder, this->IndexName("Token"), m_Value);
}
string CQTokSuffix::ValueString(void) {
  return string("*") + sqString(m_Value);
}

//======================================================================
// CQTokInfix

bool CQTokInfix::Create(CQueryTokenNode *pNode) {
  return pNode->CreateInfixPattern(m_Compiler->m_pHolder, this->IndexName("Token"), m_Value);
}
string CQTokInfix::ValueString(void) {
  return string("*") + sqString(m_Value) + string("*");
}

//======================================================================
// CQTokPrefixSet

bool CQTokPrefixSet::Create(CQueryTokenNode *pNode) {
  return pNode->CreatePrefixSetPattern(m_Compiler->m_pHolder, this->IndexName("Token"), m_Values);
}
string CQTokPrefixSet::ValueString(void) {
  return string("{") + SetValueString() + "}*";
}

//======================================================================
// CQTokSuffixSet

bool CQTokSuffixSet::Create(CQueryTokenNode *pNode) {
  return pNode->CreateSuffixSetPattern(m_Compiler->m_pHolder, this->IndexName("Token"), m_Values);
}
string CQTokSuffixSet::ValueString(void) {
  return string("*{") + SetValueString() + "}";
}

//======================================================================
// CQTokInfixSet

bool CQTokInfixSet::Create(CQueryTokenNode *pNode) {
  return pNode->CreateInfixSetPattern(m_Compiler->m_pHolder, this->IndexName("Token"), m_Values);
}
string CQTokInfixSet::ValueString(void) {
  return string("*{") + SetValueString() + "}*";
}

//======================================================================
// CQTokMorph

bool CQTokMorph::Create(CQueryTokenNode *pNode)
{
  if (m_IndexName.empty()) m_IndexName = this->IndexName("MorphPattern");

  //-- sanity checks
  if (m_Items.empty())
    throw CExpc(errParseError,"empty pattern not allowed in morphological pattern query `%s'", this->toString().c_str());
  if (m_IndexName.empty())
    throw CExpc(errParseError,"unknown index $%s in morphological pattern query `%s'", m_IndexName.c_str(), this->toString().c_str());


  return pNode->CreateMorphAnnotationPattern(m_Compiler->m_pHolder, m_IndexName, m_Items);
}

string CQTokMorph::ValueString(void) {
  string s(1,'[');
  for (vector<string>::const_iterator ii=m_Items.begin(); ii != m_Items.end(); ii++) {
    if (s.size() > 1) s.push_back(',');
    s += sqString(*ii);
  }
  s.push_back(']');
  return s;
}

//======================================================================
// CQTokLemma

bool CQTokLemma::Create(CQueryTokenNode *pNode)
{
  assert(m_Compiler->m_pHolder->m_pIndexator);
  if (m_IndexName.empty()) m_IndexName = this->IndexName("Lemma");

  if (m_Compiler->m_pHolder->m_pIndexator->m_bLemmaQueryUsesMorphPattern) 
    return CQTokMorph::Create(pNode);
  else
    return CQToken::Create(pNode);
}

string CQTokLemma::ValueString() {
  return string("%") + sqString(m_Value);
}

//======================================================================
// CQTokThes

bool CQTokThes::Create(CQueryTokenNode *pNode)
{
  string name = this->IndexName("Thes");

  //-- sanity checks
  if (name.empty())
    throw CExpc(errParseError,"unknown index $%s in thesaurus query `%s'", m_IndexName.c_str(), this->toString().c_str());

  return pNode->CreateThesPattern(m_Compiler->m_pHolder, name, m_Value);
}

string CQTokThes::ValueString() {
  return string(":{") + sqString(m_Value) + "}";
}

//======================================================================
// CQTokChunk

bool CQTokChunk::Create(CQueryTokenNode *pNode)
{
  //-- sanity checks
  string name = this->IndexName("Chunk");
  if (!m_Compiler->m_pHolder->m_pIndexator->m_pChunkIndex)
    throw CExpc(errParseError,"no chunk index defined for query `%s'", this->toString().c_str());

  return pNode->CreateChunkPattern(m_Compiler->m_pHolder, name, m_Value);
}

string CQTokChunk::ValueString() {
  return string("^") + sqString(m_Value);
}

//======================================================================
// CQTokFile

bool CQTokFile::Create(CQueryTokenNode *pNode) {
  if (!m_Compiler->m_pHolder->m_pIndexator->m_AllowUnsafeQueries)
    throw CExpc(errParseError,"unsafe file-list query `%s' disabled", this->toString().c_str());
  return pNode->CreateFileList(m_Compiler->m_pHolder, this->IndexName("Token"), m_Value);
}

string CQTokFile::ValueString() {
  return string("<") + sqString(m_Value);
}

//======================================================================
// CQNear

void CQNear::ClearNode()
{
  if (m_dtr1) m_dtr1->ClearNode();
  if (m_dtr2) m_dtr2->ClearNode();
  if (m_dtr3) m_dtr3->ClearNode();
  if (m_Node) {
    CQueryNearNode *nn = (CQueryNearNode*)m_Node;
    nn->m_pChild1 = NULL;
    nn->m_pChild2 = NULL;
    nn->m_pChild3 = NULL;
  }
  CQuery::ClearNode();
}

void CQNear::Clear(bool deep)
{
  ClearNode();
  ClearOptions();
  if (deep) {
    if (m_dtr1) delete m_dtr1;
    if (m_dtr2) delete m_dtr2;
    if (m_dtr3) delete m_dtr3;
  }
  m_dtr1 = NULL;
  m_dtr2 = NULL;
  m_dtr3 = NULL;
}

CQNear::~CQNear()
{
  Clear(true);
}

bool CQNear::Compile(CQueryCompiler *compiler)
{
  //-- inherited compilation
  SetCompiler(compiler);

  //-- compile sub-queries
  if (m_dtr1 && !m_dtr1->Compile(compiler))
    throw CExpc(errParseError,"could not compile near item sub-query `%s'", m_dtr1->toString().c_str());
  if (m_dtr2 && !m_dtr2->Compile(compiler))
    throw CExpc(errParseError,"could not compile near item sub-query `%s'", m_dtr2->toString().c_str());
  if (m_dtr3 && !m_dtr3->Compile(compiler))
    throw CExpc(errParseError,"could not compile near item sub-query `%s'", m_dtr3->toString().c_str());

  //-- sanity checks
  if (m_Dist > MaxDistanceForNear)
    throw CExpc(errParseError,"distance #%d too large (max=%d) in near query `%s'", (int)m_Dist, MaxDistanceForNear, toString().c_str());
  if (!m_dtr1 || !m_dtr2)
    throw CExpc(errParseError,"not enough arguments in near query `%s'", (int)m_Dist, MaxDistanceForNear, toString().c_str());

  //-- create near query node
  CQueryNearNode* pObj = new CQueryNearNode;
  m_Node = pObj;
  if (!pObj->Create(compiler->m_pHolder, m_Dist, m_dtr1->m_Node, m_dtr2->m_Node, (m_dtr3 ? m_dtr3->m_Node : NULL)))
    throw CExpc(errParseError,"could not compile near query `%s'", toString().c_str());

  return CQNegatable::Compile(compiler);
}

string CQNear::toString() {
  string os("NEAR(");
  if (m_dtr1) os += m_dtr1->toString();
  if (m_dtr2) os += string(",") + m_dtr2->toString();
  if (m_dtr3) os += string(",") + m_dtr3->toString();
  os += Format(",%u)", (unsigned int)m_Dist);
  return NegString(os);
}

string CQNear::jsonData() {
  return (CQNegatable::jsonData()
	  +",\"Dtr1\":"+m_dtr1->toJson()
	  +",\"Dtr2\":"+m_dtr1->toJson()
	  +",\"Dtr3\":"+(m_dtr3 ? m_dtr3->toJson() : "null")
	  +",\"Dist\":"+Format("%u", m_Dist)
	  );
}

//======================================================================
// CQSeq

void CQSeq::ClearNode() {
  if (m_Node) {
    if (m_Items.size() > 1) {
      ((CQuerySequenceNode*)m_Node)->m_Items.clear();
      delete m_Node;
    }
    m_Node = NULL;
  }
}

void CQSeq::Clear(bool deep) {
  ClearNode();
  ClearOptions();
  for (vector<CQToken*>::iterator ii=m_Items.begin(); ii != m_Items.end(); ii++) {
    if (deep && *ii) delete *ii;
    *ii = NULL;
  }
  m_Items.clear();
  m_Dists.clear();
  m_DistOps.clear();
}

CQSeq::~CQSeq()
{
  Clear(true);
}

void CQSeq::Append(CQToken *nextItem, BYTE nextDist, BYTE nextDistOp)
{
  m_Items.push_back(nextItem);
  if (m_Items.size()>1) {
    m_Dists.push_back(nextDist);
    m_DistOps.push_back(nextDistOp);
  }
}

bool CQSeq::Compile(CQueryCompiler *compiler)
{
  //-- inherited compilation
  SetCompiler(compiler);

  //-- compile sub-queries
  vector<CQueryTokenNode*> ItemNodes;
  ItemNodes.reserve(m_Items.size());

  for (size_t i=0; i < m_Items.size(); i++) {
    assert(m_Items[i] != NULL);

    if (!m_Items[i]->Compile(compiler))
      throw CExpc(errParseError,"could not compile sequence item query `%s'", m_Items[i]->toString().c_str());

    if (i<m_Dists.size() && m_Dists[i] > MaxDistanceForNear)
      throw CExpc(errParseError,"distance #%c%d too large (max=%d) in sequence query `%s'", m_DistOps[i], (int)m_Dists[i], MaxDistanceForNear, toString().c_str());

    ItemNodes.push_back((CQueryTokenNode*)m_Items[i]->m_Node);
  }

  if (ItemNodes.size()>1)  {
    //-- instantiate m_Node: multi-token sequence
    CQuerySequenceNode* pObj = new CQuerySequenceNode;
    m_Node = pObj;
    if (!pObj->Create(compiler->m_pHolder, ItemNodes, m_Dists, m_DistOps))
      throw CExpc(errParseError,"could not compile sequence query `%s'", toString().c_str());
  } else {
    //-- singleton or null sequence
    m_Node = ItemNodes[0];
  }

  return CQNegatable::Compile(compiler);
}

string CQSeq::toString() {
  string os("\"");
  int i;
  for (i=0; i < m_Items.size(); i++) {
    os += m_Items[i]->toString();
    if (i < m_Dists.size()) {
      os.push_back(' ');
      if (m_Dists[i] != 0 || m_DistOps[i] != '<')
	os += Format("#%c%d ", m_DistOps[i], (int)m_Dists[i]);
    }
  }
  os += "\"";
  return NegString(os);
}

string CQSeq::jsonData() {
  string s =  (CQNegatable::jsonData()
	       +",\"Items\":"+jsonArray(m_Items)
	       +",\"Dists\":"+jsonArray(m_Dists)
	       +",\"DistOps\":["
	       );
  for (vector<BYTE>::const_iterator doi=m_DistOps.begin(); doi != m_DistOps.end(); ++doi) {
    if (doi != m_DistOps.begin()) s.push_back(',');
    s.push_back('"');
    s.push_back(*doi);
    s.push_back('"');
  }
  s.push_back(']');
  return s;
}
