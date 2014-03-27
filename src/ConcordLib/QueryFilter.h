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

#ifndef DDC_QFILTER_H
#define DDC_QFILTER_H

#include "ConcHolder.h"

class CQueryCompiler; //-- forward decl

//======================================================================
// CQFilter

//! class for global query filters aka "query operators"
class CQFilter {
public:
  //!\name API
  //@{
  //! apply the filter to the given compiler
  virtual bool Compile(CQueryCompiler *compiler);

  //! convert filter to a canonical string
  virtual string toString(void) { return string("#FILTER[?]"); };

  //! convert filter to a json string, including class_ key
  virtual string toJson(void) { return string("{\"class_\":")+this->jsonClass()+","+this->jsonData()+"}"; };
  virtual string jsonClass(void) { return "CQFilter"; };
  virtual string jsonData(void) { return ""; };
  //@}
};

//======================================================================
// CQFSort

//! class for global query sort filters, associated with a CDDCFilterWithBounds object (ConcCommon.h)
//! m_arg0: unused, m_arg1: lower_bound, m_arg2: upper_bound
class CQFSort : public CQFilter {
public:
  //! underlying DDC Filter struct
  CDDCFilterWithBounds m_Filter;

  //! 0th argument (e.g. field name)
  std::string m_arg0;

  //! 1st argument (e.g. lower bound)
  std::string m_arg1;

  //! 2nd argument (e.g. upper bound)
  std::string m_arg2;

public:
  CQFSort(HitSortEnum   ftype=NoSort,
	  const string &arg0=string(""),
	  const string &arg1=string(""),
	  const string &arg2=string("")
	  );

  CQFSort(HitSortEnum   ftype,
	  const string &arg0,
	  int           arg1i,
	  int           arg2i
	  );

  //! swap lower- and upper-bounds if they not in logical order
  void SortBounds(void);

  //! compile the filter.  Default implementation just pushes m_Filter onto compiler->m_Filters
  virtual bool Compile(CQueryCompiler *compiler);

  //! stringification utility: quoted strign for arg, or empty string
  string argString(const string &arg) const;

  //! stringification
  virtual string toString(void);
  virtual string jsonClass(void) { return "CQFSort"; };
  virtual string jsonMinMax(void);
  virtual string jsonType(void);
  virtual string jsonData(void) { return (this->jsonType()+","+this->jsonMinMax()); };
};

//======================================================================
// CQFRankSort

class CQFRankSort : public CQFSort {
public:
  CQFRankSort(HitSortEnum ftype=GreaterByRank)
    : CQFSort(ftype)
  {};

  virtual string jsonClass(void) { return "CQFRankSort"; };
  virtual string jsonData(void) { return this->jsonType(); };
};

//======================================================================
// CQFDateSort

class CQFDateSort : public CQFSort {
public:
  CQFDateSort(HitSortEnum ftype=LessByDate, const string &lb=string(""), const string &ub=string(""))
    : CQFSort(ftype,string(""),lb,ub)
  {};

  int Str2Date(const std::string &datestr, int onEmpty=0);

  virtual bool Compile(CQueryCompiler *compiler);
  virtual string jsonClass(void) { return "CQFDateSort"; };
};

//======================================================================
// CQFSizeSort

class CQFSizeSort : public CQFSort {
public:
  CQFSizeSort(HitSortEnum ftype=LessBySize, const string &lb=string(""), const string &ub=string(""))
    : CQFSort(ftype,string(""),lb,ub)
  {};

  CQFSizeSort(HitSortEnum ftype=LessBySize, int lb=INT_MIN, int ub=INT_MAX);

  virtual bool Compile(CQueryCompiler *compiler);
  virtual string jsonClass(void) { return "CQFSizeSort"; };
};

//======================================================================
// CQFRandomSort

class CQFRandomSort : public CQFSort {
public:
  CQFRandomSort(const string &seed0=string(""))
    : CQFSort(RandomSort,string(""),seed0)
  {};

  CQFRandomSort(int seed0);

  virtual bool Compile(CQueryCompiler *compiler);
  virtual string jsonClass(void) { return "CQFRandomSort"; };
  virtual string jsonData(void) { return (this->jsonType()+",\"Seed\":"+jsonStr(m_arg1)); };
};

//======================================================================
// CQFBiblSort

//! m_arg0: field name, m_arg1: lower_bound, m_arg2: upper_bound
class CQFBiblSort : public CQFSort {
public:
  CQFBiblSort(HitSortEnum ftype=LessByFreeBiblField,
	      const string &field=string(""),
	      const string &lb=string(""),
	      const string &ub=string(""))
    : CQFSort(ftype,field,lb,ub)
  {};


  //! compile the filter.  requires reference to underlying CConcIndexator
  virtual bool Compile(CQueryCompiler *compiler);

  virtual string toString(void);
  virtual string jsonClass(void) { return "CQFBiblSort"; };
  virtual string jsonData(void);
};

//======================================================================
// CQFContextSort (formerly CQFBigramSort)

//! m_arg0: field name, m_arg1: lower_bound, m_arg2: upper_bound
class CQFContextSort : public CQFSort {
public:
  CQFContextSort(HitSortEnum ftype=LessByMiddleContext,
		 const string &field=string(""),
		 int offset=0,
		 const string &lb=string(""),
		 const string &ub=string(""))
    : CQFSort(ftype,field,lb,ub)
  {
    m_Filter.m_ContextOffset = offset;
  };

  //! compile the filter
  virtual bool Compile(CQueryCompiler *compiler);

  //! stringify
  virtual string toString(void);
  virtual string jsonClass(void) { return "CQFContextSort"; };
  virtual string jsonData(void);
};

//======================================================================
// CQFHasField (abstract)

class CQFHasField : public CQFSort {
public:
  //! is this a negated filter?
  bool m_Negated;

public:
  CQFHasField(const std::string &field, const std::string &val=string(""), bool isNegated=false)
    : CQFSort(NoSort, field, val, string("")), m_Negated(isNegated)
  {};

  //! negate the filter condition
  virtual void Negate(void);

  //! compile the filter.  requires reference to underlying CConcIndexator.
  //! CQFHasField implementation just ensures that m_arg0, m_arg1 are non-empty, throwing a CExpc otherwise
  virtual bool Compile(CQueryCompiler *compiler);

  //! value string for stringification
  virtual std::string valueString(void);

  //! generic stringification; uses valueString()
  virtual string toString(void);

  virtual string jsonClass(void) { return "CQFHasField"; };
  virtual string jsonFieldValue(void) { return jsonStr(m_arg1); };
  virtual string jsonMinMax(void);
};


//======================================================================
// CQFHasFieldValue

class CQFHasFieldValue : public CQFHasField {
public:
  CQFHasFieldValue(const std::string &field, const std::string &val=string(""), bool isNegated=false)
    : CQFHasField(field, val, isNegated)
  {};

  //! compile the filter.  requires reference to underlying CConcIndexator
  virtual bool Compile(CQueryCompiler *compiler);
  virtual string jsonClass(void) { return "CQFHasFieldValue"; };
};

//======================================================================
// CQFHasFieldRegex

class CQFHasFieldRegex : public CQFHasField {
public:
  //! target regex (same as m_arg1 for direct regex filters; auto-generated for prefix-, suffix-, and infix-filters)
  std::string m_Regex;

public:
  CQFHasFieldRegex(const std::string &field, const std::string &val=string(""), bool isNegated=false)
    : CQFHasField(field, val, isNegated), m_Regex(val)
  {};

  //! compile the filter.  requires reference to underlying CConcIndexator
  virtual bool Compile(CQueryCompiler *compiler);

  virtual string valueString(void);
  virtual string jsonClass(void) { return "CQFHasFieldRegex"; };
};

//======================================================================
// CQFHasFieldPrefix

class CQFHasFieldPrefix : public CQFHasFieldRegex {
public:
  CQFHasFieldPrefix(const std::string &field, const std::string &val=string(""), bool isNegated=false)
    : CQFHasFieldRegex(field, val, isNegated)
  {
    m_Regex = std::string("^") + escapeRegex(val);
  };

  virtual string valueString(void);
  virtual string jsonClass(void) { return "CQFHasFieldPrefix"; };
};

//======================================================================
// CQFHasFieldSuffix

class CQFHasFieldSuffix : public CQFHasFieldRegex {
public:
  CQFHasFieldSuffix(const std::string &field, const std::string &val=string(""), bool isNegated=false)
    : CQFHasFieldRegex(field, val, isNegated)
  {
    m_Regex = escapeRegex(val) + "$";
  };

  virtual string valueString(void);
  virtual string jsonClass(void) { return "CQFHasFieldSuffix"; };
};

//======================================================================
// CQFHasFieldInfix

class CQFHasFieldInfix : public CQFHasFieldRegex {
public:
  CQFHasFieldInfix(const std::string &field, const std::string &val=string(""), bool isNegated=false)
    : CQFHasFieldRegex(field, val, isNegated)
  {
    m_Regex = escapeRegex(val);
  };

  virtual string valueString(void);
  virtual string jsonClass(void) { return "CQFHasFieldInfix"; };
};

//======================================================================
// CQFHasFieldSet

class CQFHasFieldSet : public CQFHasField {
public:
  //! original target strings string
  std::set<std::string> m_Values;

public:
  CQFHasFieldSet(const std::string &field, const set<string>& vals=set<string>(), bool isNegated=false)
    : CQFHasField(field, string("{}"), isNegated), m_Values(vals)
  {};

  //! compile the filter.  requires reference to underlying CConcIndexator
  virtual bool Compile(CQueryCompiler *compiler);

  //! utility for use by subclasses: comma-separated list of strings in \a values
  string SetValueString(const set<string> &values);

  //! wrapper for SetValueString(m_Values)
  inline string SetValueString(void)
  { return SetValueString(m_Values); };

  //! stringification virtual method
  virtual string valueString(void);

  virtual string jsonClass(void) { return "CQFHasFieldSet"; };
  virtual string jsonFieldValue(void);
};


#endif /* DDC_QFILTER_H */

