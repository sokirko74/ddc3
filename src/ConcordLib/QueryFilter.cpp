//-*- Mode: C++; c-basic-offset: 2; -*-
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

#include "QueryFilter.h"
#include "QueryCompiler.h"
#include "../common/utilit.h"

//======================================================================
// globals

static const char *HitSortNames[11] = {
  "no_sort",
  "asc_by_date",
  "desc_by_date",
  "asc_by_size",
  "desc_by_size",
  "asc",
  "desc",
  "asc_by_rank",
  "desc_by_rank",
  "left",
  "right",
};

//======================================================================
// CQFilter

bool CQFilter::Compile(CQueryCompiler *compiler)
{
  assert(compiler!=NULL);
  throw CExpc(errParseError,"CQFilter::Compile(): abstract method called!");
  return false;
}


//======================================================================
// CQFSort

CQFSort::CQFSort(HitSortEnum   ftype,
		 const string &arg0,
		 const string &arg1,
		 const string &arg2,
		 bool          isRegex
		 )
  : m_arg0(arg0),
    m_arg1(arg1),
    m_arg2(arg2)
{
    m_Filter.m_FilterType = ftype;
    m_Filter.m_FreeBiblAttribName = arg0;
    m_Filter.m_bRegExp = isRegex;
    m_Filter.m_LevelStart = INT_MIN; //-- instantiate later!
    m_Filter.m_LevelEnd   = INT_MAX; //-- instantiate later!
}

CQFSort::CQFSort(HitSortEnum   ftype,
		 const string &arg0,
		 int           arg1i,
		 int           arg2i,
		 bool          isRegex
		 )
  : m_arg0(arg0)
{
  m_arg1 = Format("%d", arg1i); //-- debug
  m_arg2 = Format("%d", arg2i); //-- debug

  m_Filter.m_FilterType = ftype;
  m_Filter.m_FreeBiblAttribName = arg0;
  m_Filter.m_bRegExp    = isRegex;
  m_Filter.m_LevelStart = arg1i;
  m_Filter.m_LevelEnd   = arg2i;
}

bool CQFSort::Compile(CQueryCompiler *compiler)
{
  assert(compiler!=NULL);
  compiler->m_Filters.push_back(m_Filter);
  return true;
}


string CQFSort::toString(void)
{
  string os("#");
  os += HitSortNames[m_Filter.m_FilterType];
  EngMakeUpper(os);

  string as("");
  if (!m_arg0.empty()) {
    as += m_arg0;
  }
  if (!m_arg1.empty() || !m_arg2.empty()) {
    if (!as.empty()) as.push_back(',');
    as += m_arg1;
    if (!m_arg2.empty()) {
      as.push_back(',');
      as += m_arg2;
    }
  }
  if (!as.empty()) {
    os.push_back('[');
    os += as;
    os.push_back(']');
  }
  return os;
};

//======================================================================
// CQFRankSort

//======================================================================
// CQFDateSort

int CQFDateSort::Str2Date(const std::string &datestr, int onEmpty)
{
  int val = onEmpty;
  if (!datestr.empty()) {
    CBibliography B;
    B.m_DateStr = datestr;
    B.ConvertDateToInt(val);
  }
  return val;
}

bool CQFDateSort::Compile(CQueryCompiler *compiler)
{
  m_Filter.m_LevelStart = Str2Date(m_arg1,INT_MIN);
  m_Filter.m_LevelEnd   = Str2Date(m_arg2,INT_MAX-1) + 1;
  return CQFSort::Compile(compiler);
}

  
//======================================================================
// CQFSizeSort

CQFSizeSort::CQFSizeSort(HitSortEnum ftype, int lb, int ub)
    : CQFSort(ftype)
{
  m_arg1 = Format("%d", lb);
  m_arg2 = Format("%d", ub);
}

bool CQFSizeSort::Compile(CQueryCompiler *compiler)
{
  m_Filter.m_LevelStart = (m_arg1.empty() ? INT_MIN : atoi(m_arg1.c_str()));
  m_Filter.m_LevelEnd   = (m_arg2.empty() ? INT_MAX : atoi(m_arg2.c_str()));
  return CQFSort::Compile(compiler);
}

//======================================================================
// CQFRandomSort

CQFRandomSort::CQFRandomSort(int seed0)
    : CQFSort(RandomSort)
{
  m_arg1 = Format("%d", seed0);
}

bool CQFRandomSort::Compile(CQueryCompiler *compiler)
{
  //-- #RANDOM[] is equivalent to #RANDOM[0]
  //   + we __could__ use time(NULL) to seed here, but DDC's cache prevents re-sorting for identical query strings
  int seed = m_arg1.empty() ? 0 : atoi(m_arg1.c_str());
  compiler->m_pHolder->SetRandomSeed((unsigned int)seed);
  return CQFSort::Compile(compiler);
}

//======================================================================
// CQFBiblSort

bool CQFBiblSort::Compile(CQueryCompiler *compiler)
{
  bool bGreaterOperator = (m_Filter.m_FilterType == GreaterByFreeBiblField);
  CConcIndexator *ix = compiler->m_pHolder->m_pIndexator;

  if (m_arg0.empty())
    throw CExpc(errParseError,"Empty bibliographic field not allowed in sort operator `%s'", toString().c_str());

  if (!m_arg1.empty()) {
    if (!ix->m_Bibl.GetValueFromBiblSet(ix->GetRegexOptions(), m_arg1, m_Filter))
      throw CExpc(errParseError,"Can't determine lower bound for sort operator `%s'", toString().c_str());

    if (bGreaterOperator)
      m_Filter.m_LevelStart = -m_Filter.m_LevelStart;
  }

  if (!m_arg2.empty()) {
    CDDCFilterWithBounds TempFilter;
    TempFilter.m_FreeBiblAttribName = m_arg0;

    if (!ix->m_Bibl.GetValueFromBiblSet(ix->GetRegexOptions(), m_arg2, TempFilter))
      throw CExpc(errParseError,"Can't determine upper bound for sort operator `%s'", toString().c_str());

    if (bGreaterOperator)
      m_Filter.m_LevelEnd = -TempFilter.m_LevelStart+1;
    else
      m_Filter.m_LevelEnd = TempFilter.m_LevelEnd;
  }

  m_Filter.m_SatisfiedValues.clear();
  return CQFSort::Compile(compiler);
}

string CQFBiblSort::toString(void)
{
  string os("#");
  os += HitSortNames[m_Filter.m_FilterType];
  EngMakeUpper(os);
  os += string("['") + escapeChars(m_arg0,"\\'") + "',";

  if (!m_arg1.empty() || !m_arg2.empty()) {
    if (!m_arg1.empty())
      os += string("'") + escapeChars(m_arg1,"\\'") + "'";
    os.push_back(',');
    if (!m_arg2.empty())
      os += string("'") + escapeChars(m_arg2,"\\'") + "'";
  }
  os.push_back(']');
  return os;
};

//======================================================================
// CQFBigramSort

bool CQFBigramSort::Compile(CQueryCompiler *compiler)
{
  if (compiler) compiler->m_BigramsUse = m_Dir;
  return CQFSort::Compile(compiler);
}

//======================================================================
// CQFLeftSort

//======================================================================
// CQFRightSort

//======================================================================
// CQFHasFieldValue

void CQFHasFieldValue::Negate(void)
{
  m_Negated = !m_Negated;
}

bool CQFHasFieldValue::Compile(CQueryCompiler *compiler)
{
  if (m_arg0.empty())
    throw CExpc(errParseError,"Empty bibliographic field not allowed in filter operator `%s'", toString().c_str());

  if (m_arg1.empty())
    throw CExpc(errParseError,"Empty value field not allowed in filter operator `%s'", toString().c_str());

  m_Filter.m_bNegated = m_Negated;
  CConcIndexator *ix = compiler->m_pHolder->m_pIndexator;
  if (!ix->m_Bibl.GetValueFromBiblSet(ix->GetRegexOptions(), m_arg1, m_Filter, m_Filter.m_bRegExp))
    throw CExpc(errParseError,"Can't compile filter restriction `%s'", toString().c_str());

  return CQFSort::Compile(compiler);
}

std::string CQFHasFieldValue::negString()
{
  return std::string(m_Negated ? "!" : "");
}

string CQFHasFieldValue::toString()
{
  return 
    negString()
    + "#HAS["
    + sqString(m_Filter.m_FreeBiblAttribName)
    + ","
    + sqString(m_arg1)
    + "]";
}

//======================================================================
// CQFHasFieldRegex

string CQFHasFieldRegex::toString()
{
  return
    negString()
    + "#HAS["
    + sqString(m_Filter.m_FreeBiblAttribName)
    + ","
    + reString(m_arg1)
    + "]";
}

//======================================================================
// CQFHasFieldPrefix

string CQFHasFieldPrefix::toString()
{
  return
    negString()
    + "#HAS["
    + sqString(m_Filter.m_FreeBiblAttribName)
    + ","
    + sqString(m_prefix) + "*"
    + "]";
}

//======================================================================
// CQFHasFieldSuffix

string CQFHasFieldSuffix::toString()
{
  return
    negString()
    + "#HAS["
    + sqString(m_Filter.m_FreeBiblAttribName)
    + ","
    + "*" + sqString(m_suffix)
    + "]";
}

//======================================================================
// CQFHasFieldInfix

string CQFHasFieldInfix::toString()
{
  return
    negString()
    + "#HAS["
    + sqString(m_Filter.m_FreeBiblAttribName)
    + ","
    + "*" + sqString(m_infix) + "*"
    + "]";
}

//======================================================================
// CQFHasFieldSet

bool CQFHasFieldSet::Compile(CQueryCompiler *compiler)
{
  //if (m_Values.empty()) throw CExpc(errParseError,"Empty value set not allowed in filter operator `%s'", toString().c_str());

  m_arg1 = "^(?:";
  for (set<string>::const_iterator vi = m_Values.begin(); vi != m_Values.end(); vi++) {
    if (vi != m_Values.begin()) m_arg1 += "|";
    m_arg1 += "\\Q" + *vi + "\\E";
  }
  m_arg1 += ")$";

  return CQFHasFieldValue::Compile(compiler);
}

string CQFHasFieldSet::SetValueString(const set<string> &values)
{
  string s("");
  for (set<string>::const_iterator vi=values.begin(); vi != values.end(); vi++) {
    if (!s.empty()) s.push_back(',');
    s += sqString(*vi);
  }
  return s;
}

string CQFHasFieldSet::toString()
{
  return
    negString()
    + "#HAS["
    + sqString(m_Filter.m_FreeBiblAttribName)
    + ","
    + "{" + SetValueString() + "}"
    + "]";
}


