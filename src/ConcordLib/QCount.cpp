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
string CQCountKeyExpr::Evaluate(DWORD fileno)
{
  throw CExpc(errRuntime, Format("abstract method CQCountKeyExpr::Evaluate() called for class %s", typeid(*this).name()));
};

//==============================================================================
// CQCountKeyExpr ...

//----------------------------------------------------------------------
string CQCountKeyExprFileId::Evaluate(DWORD fileno)
{
  sprintf(buf,"%d",fileno);
  return buf;
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
string CQCountKeyExprFileName::Evaluate(DWORD fileno)
{
  return m_pIndexator->GetShortFilename(fileno);
}

//----------------------------------------------------------------------
bool CQCountKeyExprDate::Compile(CQueryCompiler *compiler)
{
  CQCountKeyExprIndexed::Compile(compiler);
  m_pDates = &(m_pIndexator->m_Bibl.GetDates());
  return true;
}

//----------------------------------------------------------------------
string CQCountKeyExprDate::Evaluate(DWORD fileno)
{
  int2date((*m_pDates)[fileno], &m_year, &m_month, &m_day);
  sprintf(buf, "%u-%02u-%02u", m_year, m_month, m_day);
  return buf;
}

//----------------------------------------------------------------------
bool CQCountKeyExprDateSlice::Compile(CQueryCompiler *compiler)
{
  CQCountKeyExprDate::Compile(compiler);
  if (!m_slice) m_slice = 1; //-- avoid divide-by-zero errors
  return true;
}

//----------------------------------------------------------------------
string CQCountKeyExprDateSlice::Evaluate(DWORD fileno)
{
  int2date((*m_pDates)[fileno], &m_year, NULL, NULL);
  m_year /= m_slice;
  sprintf(buf, "%u", m_slice*m_year);
  return buf;
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
string CQCountKeyExprBibl::Evaluate(DWORD fileno)
{
  return m_Bibl->GetStringValue(fileno);
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
string CQCountKeyExprRegex::Evaluate(DWORD fileno)
{
  string key = m_Src->Evaluate(fileno);
  if (isGlobal)
    m_Regex->GlobalReplace(m_Replacement, &key);
  else
    m_Regex->Replace(m_Replacement, &key);
  return key;
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
// CQCountKeyExprList


//----------------------------------------------------------------------
CQCountKeyExprList::~CQCountKeyExprList()
{
  this->Clear();
}

//----------------------------------------------------------------------
void CQCountKeyExprList::Clear()
{
  for (vector<CQCountKeyExpr*>::iterator ri=m_Exprs.begin(); ri!=m_Exprs.end(); ri++) {
    if (*ri) delete *ri;
  }
  m_Exprs.clear();
};

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
string CQCountKeyExprList::Evaluate(DWORD fileno)
{
  string k("");
  for (vector<CQCountKeyExpr*>::iterator ri=m_Exprs.begin(); ri!=m_Exprs.end(); ri++) {
    if (ri != m_Exprs.begin()) k.push_back(globalCountKeyDelim);
    k.push_back(' ');
    k += (*ri)->Evaluate(fileno);
  }
  return k;
};

//----------------------------------------------------------------------
string CQCountKeyExprList::toString()
{
  string s("");
  for (vector<CQCountKeyExpr*>::iterator ri=m_Exprs.begin(); ri!=m_Exprs.end(); ri++) {
    if (ri != m_Exprs.begin()) s.push_back(',');
    s += (*ri)->toString();
  }
  return s;
}

//----------------------------------------------------------------------
string CQCountKeyExprList::jsonData()
{
  string s("\"Exprs\":[");
  for (vector<CQCountKeyExpr*>::iterator ri=m_Exprs.begin(); ri!=m_Exprs.end(); ri++) {
    if (ri != m_Exprs.begin()) s.push_back(',');
    s += (*ri)->toJson();
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
