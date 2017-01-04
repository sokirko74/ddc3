//-*- Mode: C++; c-basic-offset: 2; -*-
//  Copyright 2011-2016 by Bryan Jurish
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
#include "../CommonLib/utilit.h"

//======================================================================
// globals

//======================================================================
// CQFilter

//--------------------------------------------------------------
bool CQFilter::Compile(CQueryCompiler *compiler, CQueryOptions *options)
{
  assert(compiler!=NULL);
  assert(options!=NULL);
  throw CExpc(errParseError,"CQFilter::Compile(): abstract method called!");
  return false;
}


//======================================================================
// CQFSort

//--------------------------------------------------------------
CQFSort::CQFSort(HitSortEnum   ftype,
		 const string &arg0,
		 const string &arg1,
		 const string &arg2
		 )
  : m_arg0(arg0),
    m_arg1(arg1),
    m_arg2(arg2)
{
    m_Filter.m_FilterType = ftype;
    m_Filter.m_AttrName = arg0;
    m_Filter.m_bSet = false;
    m_Filter.m_KeyLo = CHitSortKey(INT_MIN); //-- instantiate later!
    m_Filter.m_KeyHi = CHitSortKey(INT_MAX); //-- instantiate later!
}

//--------------------------------------------------------------
CQFSort::CQFSort(HitSortEnum   ftype,
		 const string &arg0,
		 int           arg1i,
		 int           arg2i
		 )
  : m_arg0(arg0)
{
  m_arg1 = Format("%d", arg1i); //-- debug
  m_arg2 = Format("%d", arg2i); //-- debug

  m_Filter.m_FilterType = ftype;
  m_Filter.m_AttrName = arg0;
  m_Filter.m_bSet       = false;
  m_Filter.m_KeyLo      = arg1i;
  m_Filter.m_KeyHi      = arg2i;
}

//--------------------------------------------------------------
void CQFSort::SortBounds(void) {
  if (m_Filter.m_KeyLo > m_Filter.m_KeyHi)
    std::swap(m_Filter.m_KeyLo, m_Filter.m_KeyHi);
}

//--------------------------------------------------------------
bool CQFSort::Compile(CQueryCompiler *compiler, CQueryOptions *options)
{
  /*
  assert(compiler!=NULL);
  assert(compiler->m_pQuery!=NULL);
  assert(compiler->m_pQuery->m_Options!=NULL);
  */
  assert(options != NULL);
  options->m_Filters.push_back(m_Filter);
  return true;
}

//--------------------------------------------------------------
string CQFSort::ResolveAttributeName(CQueryCompiler *compiler, const string& attrName, bool allowBiblExpander)
{
  CConcIndexator *ix = compiler->m_pHolder->m_pIndexator;
  assert(ix != NULL);

  if (!attrName.empty() && ((ix->m_Bibl.GetFreeBiblIndex(attrName)!=NULL)
			    ||
			    (allowBiblExpander && ix->m_Bibl.GetBiblExpander(attrName)!=NULL)))
      return attrName;

  if (!ix->m_Bibl.m_DefaultAttrName.empty() && ix->m_Bibl.GetFreeBiblIndex(ix->m_Bibl.m_DefaultAttrName)!=NULL)
    return ix->m_Bibl.m_DefaultAttrName;

  return string("");
}

//--------------------------------------------------------------
string CQFSort::argString(const string &arg) const
{
  if (arg.empty()) return arg;
  return string("'") + escapeChars(arg,"\\'") + "'";
}


//--------------------------------------------------------------
string CQFSort::toString(void)
{
  string os("#");
  os += HitSortEnumStrings[m_Filter.m_FilterType];
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

//--------------------------------------------------------------
string CQFSort::jsonMinMax()
{
  return (string("\"Min\":")+jsonStr(m_arg1)
	  +",\"Max\":"+jsonStr(m_arg2)
	  );
};

//--------------------------------------------------------------
string CQFSort::jsonType()
{
  return string("\"FilterType\":")+jsonStr(HitSortEnumStrings[m_Filter.m_FilterType]);
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

bool CQFDateSort::Compile(CQueryCompiler *compiler, CQueryOptions *options)
{
  m_Filter.m_KeyLo = INT_MIN+1;
  m_Filter.m_KeyHi = INT_MAX-1;

  if (!m_arg1.empty()) m_Filter.m_KeyLo.i = Str2Date(m_arg1);
  if (!m_arg2.empty()) m_Filter.m_KeyHi.i = Str2Date(m_arg2)+1;

  return CQFSort::Compile(compiler, options);
}

  
//======================================================================
// CQFSizeSort

CQFSizeSort::CQFSizeSort(HitSortEnum ftype, int lb, int ub)
    : CQFSort(ftype)
{
  m_arg1 = Format("%d", lb);
  m_arg2 = Format("%d", ub);
}

bool CQFSizeSort::Compile(CQueryCompiler *compiler, CQueryOptions *options)
{
  m_Filter.m_KeyLo = (m_arg1.empty() ? INT_MIN : atoi(m_arg1.c_str())  );
  m_Filter.m_KeyHi = (m_arg2.empty() ? INT_MAX : atoi(m_arg2.c_str())+1);
  return CQFSort::Compile(compiler, options);
}

//======================================================================
// CQFRandomSort

CQFRandomSort::CQFRandomSort(int seed0)
    : CQFSort(RandomSort)
{
  m_arg1 = Format("%d", seed0);
}

bool CQFRandomSort::Compile(CQueryCompiler *compiler, CQueryOptions *options)
{
  //-- #RANDOM[] is equivalent to #RANDOM[0]
  //   + we __could__ use time(NULL) to seed here, but DDC's cache prevents re-sorting for identical query strings
  int seed = m_arg1.empty() ? 0 : atoi(m_arg1.c_str());
  compiler->m_pHolder->SetRandomSeed((unsigned int)seed);
  return CQFSort::Compile(compiler, options);
}


//======================================================================
// CQFBiblSort

bool CQFBiblSort::Compile(CQueryCompiler *compiler, CQueryOptions *options)
{
  CConcIndexator *ix = compiler->m_pHolder->m_pIndexator;
  assert(ix != NULL);

  if (m_arg0.empty())
    throw CExpc(errParseError,"Empty bibliographic field not allowed in sort operator `%s'", this->toString().c_str());

  //-- resolve attribute name (fallback to DefaultBibl)
  m_Filter.m_AttrName = ResolveAttributeName(compiler, m_arg0);
  if (m_Filter.m_AttrName.empty()) {
    throw CExpc(errParseError,"Can't resolve attribute name `%s' for bibliographic sort operator `%s'", m_arg0.c_str(), this->toString().c_str());
  }

  //-- guts: get filter bounds
  if (!ix->m_Bibl.GetFilterBounds(m_Filter, m_arg1, m_arg2)) {
    throw CExpc(errParseError,"Can't determine bound(s) for bibliographic sort operator `%s'", this->toString().c_str());
  }

  return CQFSort::Compile(compiler, options);
}

string CQFBiblSort::toString(void)
{
  string os("#");
  os += HitSortEnumStrings[m_Filter.m_FilterType];
  EngMakeUpper(os);
  os += string("['") + escapeChars(m_arg0,"\\'") + "',";

  if (!m_arg1.empty() || !m_arg2.empty()) {
    os += argString(m_arg1) + "," + argString(m_arg2);
  }
  os.push_back(']');
  return os;
};

string CQFBiblSort::jsonData(void)
{
  return (this->jsonType()
	  +",\"Field\":"+jsonStr(m_arg0)
	  +","+this->jsonMinMax()
	  );
};

string CQFBiblSort::jsonMinMax(void)
{
  return (string("\"Min\":")+jsonStr(m_arg1)
	  +",\"Max\":"+jsonStr(m_arg2)
	  );
};

//======================================================================
// CQFContextSort

bool CQFContextSort::Compile(CQueryCompiler *compiler, CQueryOptions *options)
{
  CConcIndexator *ix = compiler->m_pHolder->m_pIndexator;
  assert(ix != NULL);

  m_Filter.m_AttrName  = m_arg0.empty() ? ix->GetTokenIndex()->m_Name : m_arg0;
  CStringIndexSet* ixx = ix->GetIndexByNameOrShortName(m_Filter.m_AttrName);
  if (ixx == NULL)
    throw CExpc(errParseError,"Can't find index `%s' for context-sort operator `%s'", m_Filter.m_AttrName.c_str(), toString().c_str());

  if (!ixx->GetContextBounds(m_Filter, m_arg1, m_arg2))
      throw CExpc(errParseError,"Can't determine bound(s) for context-sort operator `%s'", toString().c_str());

  return CQFSort::Compile(compiler,options);
}

string CQFContextSort::toString(void)
{
  string os("#");
  os += HitSortEnumStrings[m_Filter.m_FilterType];
  EngMakeUpper(os);

  //if (!m_arg0.empty() || m_Filter.m_ContextOffset!=0 || !m_arg1.empty() || !m_arg2.empty()) {...}
  os += string("[") + argString(m_arg0);
  if (m_Filter.m_ContextMatchId != 0)
    os += Format(" =%u", m_Filter.m_ContextMatchId);
  os += Format(" %+d", m_Filter.m_ContextOffset);
  if (!m_arg1.empty() || !m_arg2.empty()) {
    os += string(",") + argString(m_arg1) + "," + argString(m_arg2);
  }
  os.push_back(']');

  return os;
};

string CQFContextSort::jsonData(void)
{
  return (this->jsonType()
	  +",\"Field\":"+jsonStr(m_arg0)
	  +",\"MatchId\":"+Format("%u", m_Filter.m_ContextMatchId)
	  +",\"Offset\":"+Format("%d", m_Filter.m_ContextOffset)
	  +","+this->jsonMinMax()
	  );
};


//======================================================================
// CQFHasField

void CQFHasField::Negate(void)
{
  m_Negated = !m_Negated;
}

bool CQFHasField::Compile(CQueryCompiler *compiler, CQueryOptions *options)
{
  if (m_arg0.empty())
    throw CExpc(errParseError,"Empty bibliographic field not allowed in filter operator `%s'", toString().c_str());

  if (m_arg1.empty())
    throw CExpc(errParseError,"Empty value field not allowed in filter operator `%s'", toString().c_str());

  //-- resolve attribute name (allow expanders, fallback to DefaultBibl)
  m_Filter.m_AttrName = ResolveAttributeName(compiler, m_arg0, true);
  if (m_Filter.m_AttrName.empty()) {
    throw CExpc(errParseError,"Can't resolve attribute name `%s' in bibliographic filter operator `%s'", m_arg0.c_str(), this->toString().c_str());
  }

  return true;
}

string CQFHasField::toString()
{
  return 
    std::string(m_Negated ? "!" : "")
    + "#HAS["
    + sqString(m_arg0)
    + ","
    + valueString()
    + "]";
}

string CQFHasField::valueString()
{
  return sqString(m_arg1);
}

string CQFHasField::jsonMinMax(void)
{
  return (string("\"Field\":")+jsonStr(m_arg0)
	  +",\"Value\":"+this->jsonFieldValue()
	  +",\"Negated\":"+(m_Negated ? "1" : "0")
	  );
}

//======================================================================
// CQFHasFieldValue

bool CQFHasFieldValue::Compile(CQueryCompiler *compiler, CQueryOptions *options)
{
  CQFHasField::Compile(compiler,options);

  m_Filter.m_bNegated = m_Negated;
  CConcIndexator *ix = compiler->m_pHolder->m_pIndexator;

  if (!ix->m_Bibl.GetFilterValue(m_Filter, m_arg1))
    throw CExpc(errParseError,"Can't compile literal filter condition `%s'", toString().c_str());

  return CQFSort::Compile(compiler,options);
}

//======================================================================
// CQFHasFieldRegex

bool CQFHasFieldRegex::Compile(CQueryCompiler *compiler, CQueryOptions *options)
{
  CQFHasField::Compile(compiler,options);

  m_Filter.m_bNegated = m_Negated;
  CConcIndexator *ix = compiler->m_pHolder->m_pIndexator;
  if (!ix->m_Bibl.GetFilterValues(m_Filter, m_Regex))
    throw CExpc(errParseError,"Can't compile regex filter condition `%s'", toString().c_str());

  return CQFSort::Compile(compiler,options);
}

string CQFHasFieldRegex::valueString()
{
  return reString(m_arg1);
}

//======================================================================
// CQFHasFieldPrefix

string CQFHasFieldPrefix::valueString()
{
  return sqString(m_arg1) + "*";
}

//======================================================================
// CQFHasFieldSuffix

string CQFHasFieldSuffix::valueString()
{
  return std::string("*") + sqString(m_arg1);
}

//======================================================================
// CQFHasFieldInfix

string CQFHasFieldInfix::valueString()
{
  return std::string("*") + sqString(m_arg1) + "*";
}

//======================================================================
// CQFHasFieldSet

bool CQFHasFieldSet::Compile(CQueryCompiler *compiler, CQueryOptions *options)
{
  CQFHasField::Compile(compiler,options);

  m_Filter.m_bNegated = m_Negated;
  CConcIndexator *ix = compiler->m_pHolder->m_pIndexator;
  if (!ix->m_Bibl.GetFilterValues(m_Filter, m_Values))
    throw CExpc(errParseError,"Can't compile set-valued filter restriction `%s'", toString().c_str());

  return CQFSort::Compile(compiler,options);
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

string CQFHasFieldSet::valueString()
{
  return std::string("{") + SetValueString() + "}";
}

string CQFHasFieldSet::jsonFieldValue()
{
  string s("[");
  for (set<string>::const_iterator vi=m_Values.begin(); vi != m_Values.end(); vi++) {
    if (s.size() > 1) s.push_back(',');
    s += jsonStr(*vi);
  }
  s.push_back(']');
  return s;
}
