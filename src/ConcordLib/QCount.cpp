//-*- Mode: C++; c-basic-offset: 2; -*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2015 by Bryan Jurish
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

#include <QCount.h>
#include <QueryCompiler.h>
#include <ConcHolder.h>

//==============================================================================
// CQCountKeyExpr

//----------------------------------------------------------------------
bool CQCountKeyExpr::Compile(CQueryCompiler *compiler)
{
  SetCompiler(compiler);
  return true;
}

//----------------------------------------------------------------------
string& CQCountKeyExpr::Evaluate(const CHit &Hit)
{
  throw CExpc(errRuntime, Format("abstract method CQCountKeyExpr::Evaluate() called for class %s", typeid(*this).name()));
};

//==============================================================================
// CQCountKeyExpr ...

//----------------------------------------------------------------------
string& CQCountKeyExprFileId::Evaluate(const CHit &Hit)
{
  if (Hit.m_FileNo != m_CurFile) {
    sprintf(buf,"%d",Hit.m_FileNo);
    m_CurKey  = buf;
    m_CurFile = Hit.m_FileNo;
  }
  return m_CurKey;
}

//----------------------------------------------------------------------
bool CQCountKeyExprIndexed::Compile(CQueryCompiler *compiler)
{
  CQCountKeyExpr::Compile(compiler);
  assert(compiler->m_pHolder != NULL);
  assert(compiler->m_pHolder->m_pIndexator != NULL);
  m_pIndexator = compiler->m_pHolder->m_pIndexator;
  return true;
}

//----------------------------------------------------------------------
string& CQCountKeyExprFileName::Evaluate(const CHit &Hit)
{
  if (Hit.m_FileNo != m_CurFile) {
    m_CurKey  = m_pIndexator->GetShortFilename(Hit.m_FileNo);
    m_CurFile = Hit.m_FileNo;
  }
  return m_CurKey;
}

//----------------------------------------------------------------------
bool CQCountKeyExprDate::Compile(CQueryCompiler *compiler)
{
  CQCountKeyExprIndexed::Compile(compiler);
  m_pDates = &(m_pIndexator->m_Bibl.GetDates());
  return true;
}

//----------------------------------------------------------------------
string& CQCountKeyExprDate::Evaluate(const CHit &Hit)
{
  if (Hit.m_FileNo != m_CurFile) {
    int2date((*m_pDates)[Hit.m_FileNo], &m_year, &m_month, &m_day);
    sprintf(buf, "%u-%02u-%02u", m_year, m_month, m_day);
    m_CurKey  = buf;
    m_CurFile = Hit.m_FileNo;
  }
  return m_CurKey;
}

//----------------------------------------------------------------------
bool CQCountKeyExprDateSlice::Compile(CQueryCompiler *compiler)
{
  CQCountKeyExprDate::Compile(compiler);
  if (!m_slice) m_slice = 1; //-- avoid divide-by-zero errors
  return true;
}

//----------------------------------------------------------------------
string& CQCountKeyExprDateSlice::Evaluate(const CHit &Hit)
{
  if (Hit.m_FileNo != m_CurFile) {
    int2date((*m_pDates)[Hit.m_FileNo], &m_year, NULL, NULL);
    m_year /= m_slice;
    sprintf(buf, "%u", m_slice*m_year);
    m_CurKey  = buf;
    m_CurFile = Hit.m_FileNo;
  }
  return m_CurKey;
}

//----------------------------------------------------------------------
bool CQCountKeyExprBibl::Compile(CQueryCompiler *compiler)
{
  CQCountKeyExprIndexed::Compile(compiler);
  m_Bibl = m_pIndexator->m_Bibl.GetFreeBiblIndex(m_Label);
  if (m_Bibl == NULL)
    throw CExpc(errRuntime, Format("CQCountKeyExprBibl()::Compile(): cannot use unknown bibliographic attribute `%s' as count-key", m_Label.c_str()));
  return true;
}

//----------------------------------------------------------------------
string& CQCountKeyExprBibl::Evaluate(const CHit &Hit)
{
  if (m_CurFile != Hit.m_FileNo) {
    m_CurKey = m_Bibl->GetStringValue(Hit.m_FileNo);
    m_CurFile = Hit.m_FileNo ;
  }
  return m_CurKey;
};

//==============================================================================
// CQCountKeyExprRegex

//----------------------------------------------------------------------
CQCountKeyExprRegex::~CQCountKeyExprRegex()
{
  if (m_Src) delete m_Src;
  if (m_Regex) delete m_Regex;
}

//----------------------------------------------------------------------
bool CQCountKeyExprRegex::Compile(CQueryCompiler *compiler)
{
  if (!m_Src || !m_Src->Compile(compiler)) return false;
  CQCountKeyExprIndexed::Compile(compiler);
  m_Regex = new RML_RE(m_Pattern, m_pIndexator->GetRegexOptions());
  //m_Pcre  = m_Regex->Compile(RML_RE::UNANCHORED);
  isGlobal = (m_Modifiers.find('g') != m_Modifiers.npos);
  return true;
}

//----------------------------------------------------------------------
string& CQCountKeyExprRegex::Evaluate(const CHit &Hit)
{
  if (!m_Src->CanCountByFile() || Hit.m_FileNo != m_CurFile) {
    m_CurKey = m_Src->Evaluate(Hit);
    if (isGlobal)
      m_Regex->GlobalReplace(m_Replacement, &m_CurKey);
    else
      m_Regex->Replace(m_Replacement, &m_CurKey);
    m_CurFile = Hit.m_FileNo;
  }
  return m_CurKey;
}

//----------------------------------------------------------------------
string CQCountKeyExprRegex::toString()
{
  return string("(") + m_Src->toString() + " ~ s/" + m_Pattern + "/" + m_Replacement + "/" + m_Modifiers + ")";
}

//----------------------------------------------------------------------
string CQCountKeyExprRegex::jsonData()
{
  return "\"Src\":" + m_Src->toJson() + ",\"Pattern\":" + jsonStr(m_Pattern) + ",\"Replacement\":" + jsonStr(m_Replacement) + ",\"Modifiers\":" + jsonStr(m_Modifiers);
}

//==============================================================================
// CQCountKeyExprToken

//----------------------------------------------------------------------
bool CQCountKeyExprToken::Compile(CQueryCompiler *compiler)
{
  CQCountKeyExprIndexed::Compile(compiler);

  /* sanity check */
  if (!compiler->m_pHolder->m_pIndexator->m_bAllowCountByTokenAttributes)
    throw CExpc(errParseError,"counting by token attribute `%s' disabled", this->toString().c_str());

  /* get index */
  if (m_IndexName.empty())
    m_IndexName = "Token";

  m_pIndex = compiler->m_pHolder->m_pIndexator->GetIndexByNameOrShortName(m_IndexName);
  if (!m_pIndex)
    throw CExpc(errParseError,"CQCountKeyExprToken::Compile(): unknown index `%s'", m_IndexName.c_str());

  return true;
}

//----------------------------------------------------------------------
string& CQCountKeyExprToken::Evaluate(const CHit &Hit)
{
  const CConcHolder *holder = m_Compiler->m_pHolder;
  const vector<CHit> &hits  = holder->m_Hits;
  const vector<CTokenNo> &occurrences = holder->m_HighlightOccurs;
  const vector<CTokenNo> &breaks = holder->GetBreaks();
  const vector<BYTE>  &matchids = holder->m_HighlightIds;

  //-- get context anchor occurrence-index occur_i
  DWORD hitno = &Hit - &*hits.begin();
  DWORD occur_i = (hitno==0 ? 0 : hits[hitno-1].m_HighlightOccurrenceEnd);
  if (m_MatchId != 0) {
    DWORD end = Hit.m_HighlightOccurrenceEnd >= occurrences.size() ? occurrences.size() : Hit.m_HighlightOccurrenceEnd;
    for ( ; occur_i < end && matchids[occur_i] != m_MatchId; occur_i++) ;
    if (occur_i >= end)
      occur_i = (DWORD)-1;
  }

  //-- get break limits and token-id
  DWORD StartTokenNo = (Hit.m_BreakNo==0) ?  0 : breaks[Hit.m_BreakNo-1];
  DWORD EndTokenNo   = breaks[Hit.m_BreakNo];
  CTokenNo tok = (occur_i >= occurrences.size() ? (CTokenNo)-1 : (occurrences[occur_i] + m_Offset));
  DWORD    key;

  if (tok >= StartTokenNo && tok < EndTokenNo && (key=m_pIndex->GetTokenIndexId(tok)) != DWORD_MAX) {
    //-- usual case: within target break and with a valid item id
    m_CurKey = m_pIndex->GetIndexItemStr( m_pIndex->m_Index[key] );
  } else {
    //-- break-overflow (EOS etc) or invalid key item: treat as empty sort-key
    m_CurKey.clear();
  }
  
  return m_CurKey;
}

//----------------------------------------------------------------------
string CQCountKeyExprToken::toString()
{
  string s("$");
  s += m_IndexName;
  if (m_MatchId != 0)
    s += Format(" =%hhu", m_MatchId);
  if (m_Offset != 0)
    s += Format(" %+d", m_Offset);
  return s;
}

//----------------------------------------------------------------------
string CQCountKeyExprToken::jsonData()
{
  return string("\"IndexName\":") + jsonStr(m_IndexName) + Format(",\"MatchId\":%hhu,\"Offset\":%d", m_MatchId, m_Offset);
}


//==============================================================================
// CQCountKeyExprList


//----------------------------------------------------------------------
CQCountKeyExprList::~CQCountKeyExprList()
{
  this->Clear();
}

//----------------------------------------------------------------------
void CQCountKeyExprList::Clear()
{
  for (vector<CQCountKeyExpr*>::iterator xi=m_Exprs.begin(); xi!=m_Exprs.end(); xi++) {
    if (*xi) delete *xi;
  }
  m_Exprs.clear();
};

//----------------------------------------------------------------------
bool CQCountKeyExprList::CanCountByFile() const
{
  for (vector<CQCountKeyExpr*>::const_iterator xi=m_Exprs.begin(); xi!=m_Exprs.end(); xi++) {
    if (*xi && !(*xi)->CanCountByFile()) return false;
  }
  return true;
}

//----------------------------------------------------------------------
bool CQCountKeyExprList::HasMatchId() const
{
  for (vector<CQCountKeyExpr*>::const_iterator xi=m_Exprs.begin(); xi!=m_Exprs.end(); xi++) {
    if (*xi && (*xi)->HasMatchId()) return true;
  }
  return false;
}

//----------------------------------------------------------------------
bool CQCountKeyExprList::Compile(CQueryCompiler *compiler)
{
  if (m_Exprs.empty()) {
    //-- sanity check: ensure at least 1 key field
    this->PushKey(new CQCountKeyExprConstant("*"));
  }

  bool rc = true;  
  for (vector<CQCountKeyExpr*>::iterator xi=m_Exprs.begin(); rc && xi != m_Exprs.end(); xi++) {
    rc = rc && (*xi)->Compile(compiler);
  }

  return rc;
};

//----------------------------------------------------------------------
string& CQCountKeyExprList::Evaluate(const CHit &Hit)
{
  m_Key.clear();
  for (vector<CQCountKeyExpr*>::iterator xi=m_Exprs.begin(); xi!=m_Exprs.end(); xi++) {
    if (xi != m_Exprs.begin()) m_Key.push_back(globalCountKeyDelim);
    m_Key.push_back(' ');
    m_Key += (*xi)->Evaluate(Hit);
  }
  return m_Key;
};

//----------------------------------------------------------------------
string CQCountKeyExprList::toString()
{
  string s("");
  for (vector<CQCountKeyExpr*>::iterator xi=m_Exprs.begin(); xi!=m_Exprs.end(); xi++) {
    if (xi != m_Exprs.begin()) s.push_back(',');
    s += (*xi)->toString();
  }
  return s;
}

//----------------------------------------------------------------------
string CQCountKeyExprList::jsonData()
{
  string s("\"Exprs\":[");
  for (vector<CQCountKeyExpr*>::iterator xi=m_Exprs.begin(); xi!=m_Exprs.end(); xi++) {
    if (xi != m_Exprs.begin()) s.push_back(',');
    s += (*xi)->toJson();
  }
  s.push_back(']');
  return s;
}

//======================================================================
// CQCount

//--------------------------------------------------------------
CQCount::~CQCount()
{
  Clear(true);
}

//--------------------------------------------------------------
void CQCount::ClearNode()
{
  if (m_dtr) m_dtr->ClearNode();
  CQuery::ClearNode();
}

//--------------------------------------------------------------
void CQCount::Clear(bool deep)
{
  ClearNode();
  ClearOptions();
  if (deep) {
    if (m_dtr) delete m_dtr;
    m_keys.Clear();
  }
  m_dtr = NULL;
}

//--------------------------------------------------------------
bool CQCount::Compile(CQueryCompiler *compiler)
{
  SetCompiler(compiler);

  //-- sanity check(s)
  if (!m_dtr)
    throw CExpc(errParseError,"no argument conditions specified for count-query `%s'", this->toString().c_str());

  //-- compile daughter(s)
  if (!m_dtr->CompileOptions(compiler) || !m_dtr->Compile(compiler))
    throw CExpc(errParseError,"could not compile sub-query `%s' for count-query", m_dtr->toString().c_str());

  //-- compile key expression(s)
  if (!m_keys.Compile(compiler)) 
    throw CExpc(errParseError,"could not compile key expression(s) `%s' for count-query", m_keys.toString().c_str());

  //-- child methods hook in here
  return true;
}

//--------------------------------------------------------------
void CQCount::Evaluate()
{
  //-- sanity check(s)
  assert(m_dtr != NULL);
  m_dtr->Evaluate();
}

//--------------------------------------------------------------
string CQCount::toString()
{
  string qs("COUNT(" + m_dtr->toString() + m_dtr->optionsToString() + ")");
  if (!m_keys.empty()) {
    qs += " #BY[" + m_keys.toString() + "]";
  }
  if (m_sample != DDCDefaultCountSampleSize)
    qs += Format(" #SAMPLE[%zi]", m_sample);
  if (m_sort != NoSort) {
    string sortstr(" #");
    sortstr += HitSortEnumStrings[m_sort];
    EngMakeUpper(sortstr);
    qs += sortstr;
  }
  return qs;
}

//--------------------------------------------------------------
string CQCount::jsonData()
{
  string qs("\"Dtr\":" + m_dtr->toJson() + ",\"DtrOptions\":" + m_dtr->optionsToJson());
  if (!m_keys.empty()) {
    qs += string(",\"Keys\":") + m_keys.toJson();
  }
  return qs;
}

//======================================================================
// functions

void GenerateCountString(string &ResultStr, DDCFormatTypeEnum fmt, const string& key, size_t count)
{
  char keysep[2] = {globalCountKeyDelim,'\0'};
  StringTokenizer keytok(key.c_str(), keysep);

  switch (fmt) {
  case DDC_ResultJson:
    //-- count strings, json format "[[COUNT, KEY0, KEY1, ... ], ..., [COUNT, KEY0, KEY1, ...]"
    ResultStr += Format("[%zi", count);
    while (keytok()) {
      ResultStr.push_back(',');
      ResultStr.append(jsonStr(keytok.val()+1));
    }
    ResultStr.push_back(']');
    break;
			
  case DDC_ResultHTML:
    //-- count strings, html
    ResultStr += Format("<TR><TD>%zi</TD>", count);
    while (keytok()) {
      ResultStr += "<TD>" + ConvertASCIIToHtmlSymbols(keytok.val()+1) + "</TD>";
    }
    ResultStr += "</TR>\n";
    break;

			
  case DDC_ResultText:
  case DDC_ResultTable:
  default:
    //-- count strings, text or table
    ResultStr += Format("%zi", count);
    while (keytok()) {
      ResultStr.push_back('\t');
      ResultStr += keytok.val()+1;
    }
    ResultStr.push_back('\n');
    break;
  }
}
