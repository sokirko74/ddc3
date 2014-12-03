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

#ifndef DDC_QCOUNT_H
#define DDC_QCOUNT_H

#include "../ConcordLib/Query.h"

//======================================================================
//typedef vector<string>    	CQCountByList;

//==============================================================================
// CQCountKeyExpr and subclasses

//----------------------------------------------------------------------
/*! runtime count-key expression base class */
class CQCountKeyExpr : public CQuery
{
public:
  /** default constructor */
  CQCountKeyExpr(const string& label="")
    : CQuery(label)
  {};

  /** clear */
  //virtual void Clear(bool deep=true);

  /** default destuctor */
  virtual ~CQCountKeyExpr()
  {};

  /** compile the expression relative to a CQueryCompiler and its associated index */
  virtual bool Compile(CQueryCompiler *compiler);
  
  /** get string key for the document \a fileno ; default just throws an exception */
  virtual string Evaluate(DWORD fileno);

  /** stringification (default returns m_Label) */
  virtual string toString() { return m_Label; };

  /** json stringification: class */
  string jsonClass() { return "CQCountKeyExpr"; };

  /** json stringification: data */
  string jsonData() { return "\"label\":" + jsonStr(m_Label); };
};

//----------------------------------------------------------------------
/*! count-key expression: constant */
class CQCountKeyExprConstant : public CQCountKeyExpr {
public:
  CQCountKeyExprConstant(const string &label="*") : CQCountKeyExpr(label) {};
  virtual ~CQCountKeyExprConstant() {};
  virtual string Evaluate(DWORD fileno) { return m_Label; };
  virtual string jsonClass() { return "CQCountKeyExprConstant"; };
  virtual string toString() { return string("@'") + escapeChars(m_Label,"\\'") + "'"; };
};

//----------------------------------------------------------------------
/*! count-key expression: fileid (aka docid) */
class CQCountKeyExprFileId : public CQCountKeyExpr {
private:
  char buf[16];
public:
  CQCountKeyExprFileId(const string &label="fileid") : CQCountKeyExpr(label) {};
  virtual ~CQCountKeyExprFileId() {};
  virtual string Evaluate(DWORD fileno);
  virtual string jsonClass() { return "CQCountKeyExprFileId"; };
};

//----------------------------------------------------------------------
/*! count-key expression: indexed */
class CQCountKeyExprIndexed : public CQCountKeyExpr {
public:
  class CConcIndexator* m_pIndexator;
public:
  CQCountKeyExprIndexed(const string &label="file") : CQCountKeyExpr(label) {};
  virtual ~CQCountKeyExprIndexed() {};
  virtual bool Compile(CQueryCompiler *compiler);
  virtual string jsonClass() { return "CQCountKeyExprIndexed"; };
};

//----------------------------------------------------------------------
/*! count-key expression: filename */
class CQCountKeyExprFileName : public CQCountKeyExprIndexed {
public:
  CQCountKeyExprFileName(const string &label="filename") : CQCountKeyExprIndexed(label) {};
  virtual ~CQCountKeyExprFileName() {};
  virtual string Evaluate(DWORD fileno);
  virtual string jsonClass() { return "CQCountKeyExprFileName"; };
};

//----------------------------------------------------------------------
/*! count-key expression: date: full */
class CQCountKeyExprDate : public CQCountKeyExprIndexed
{
public:
  const vector<int> *m_pDates;
  unsigned int       m_year;
  unsigned int       m_month;
  unsigned int       m_day;
  char               buf[16];

public:
  CQCountKeyExprDate(const string &label="date") : CQCountKeyExprIndexed(label), m_pDates(NULL) {};
  virtual ~CQCountKeyExprDate() {};
  virtual bool Compile(CQueryCompiler *compiler);
  virtual string Evaluate(DWORD fileno);
  virtual string jsonClass() { return "CQCountKeyExprDate"; };
};

//----------------------------------------------------------------------
/*! count-key expr: date: slice (by year) */
class CQCountKeyExprDateSlice : public CQCountKeyExprDate
{
public:
  unsigned int m_slice;
public:
  CQCountKeyExprDateSlice(const string &label="date", int slice=1) : CQCountKeyExprDate(label), m_slice(slice) {};
  virtual ~CQCountKeyExprDateSlice() {};
  virtual bool Compile(CQueryCompiler *compiler);
  virtual string Evaluate(DWORD fileno);
  virtual string toString() { return m_Label + Format("/%d",m_slice); };
  virtual string jsonClass() { return "CQCountKeyExprDateSlice"; };
  virtual string jsonData() { return CQCountKeyExprDate::jsonData() + Format(",\"slice\":%d",m_slice); };
};

//----------------------------------------------------------------------
/*! count-key expr: bibl string */
class CQCountKeyExprBibl : public CQCountKeyExprIndexed
{
public:
  class CConcXml::CFreeBiblIndex *m_Bibl;
public:
  CQCountKeyExprBibl(const string &attrName="") : CQCountKeyExprIndexed(attrName) {};
  virtual ~CQCountKeyExprBibl() {};
  virtual bool Compile(CQueryCompiler *compiler);
  virtual string Evaluate(DWORD fileno);
  virtual string jsonClass() { return "CQCountKeyExprBibl"; };
  virtual string toString() { return string("'") + escapeChars(m_Label,"\\'") + "'"; };
};

//----------------------------------------------------------------------
/*! count-key expr: regular expression replacement */
class CQCountKeyExprRegex : public CQCountKeyExprIndexed
{
public:
  CQCountKeyExpr *m_Src;
  string      m_Pattern;
  string      m_Replacement;
  string      m_Modifiers;
  bool	      isGlobal;
  RML_RE     *m_Regex;

public:
  CQCountKeyExprRegex(CQCountKeyExpr *src, const string& pattern, const string &replacement, const string& modifiers=string(""))
    : CQCountKeyExprIndexed("regex"), m_Src(src), m_Pattern(pattern), m_Replacement(replacement), m_Modifiers(modifiers), isGlobal(false), m_Regex(NULL) {};
  virtual ~CQCountKeyExprRegex();
  virtual bool Compile(CQueryCompiler *compiler);
  virtual string Evaluate(DWORD fileno);
  virtual string toString();
  virtual string jsonClass() { return "CQCountKeyExprRegex"; };
  virtual string jsonData();
};

//----------------------------------------------------------------------
// count-key expr: list
class CQCountKeyExprList : public CQCountKeyExpr
{
public:
  /** underlying expression list */
  vector<CQCountKeyExpr*> m_Exprs;

public:
  CQCountKeyExprList() {};
  virtual ~CQCountKeyExprList();

  /*! clear and delete all sub-expressions */
  virtual void Clear();

  /*! wrapper for m_Exprs.empty() */
  inline bool empty() const { return m_Exprs.empty(); };

  /*! append a count-by expression */
  void PushKey(CQCountKeyExpr *expr)
  { m_Exprs.push_back(expr); };

  virtual bool Compile(CQueryCompiler *compiler);
  virtual string Evaluate(DWORD fileno);

  virtual string toString();
  virtual string jsonClass() { return "CQCountKeyExprList"; };
  virtual string jsonData();

};

//======================================================================
/*!
 \brief
   count query
*/
class CQCount : public CQuery {
public:
  //! underlying query conditions to be counted
  CQuery *m_dtr;

  //! list of count-bin metadata key expressions
  CQCountKeyExprList m_keys;

public:
  //! bison constructor
  CQCount(CQuery *dtr, const CQCountKeyExprList &keys)
  : CQuery("count"),
    m_dtr(dtr),
    m_keys(keys)
  {};

  //! Default destructor.
  virtual ~CQCount(void);

public:
  //! Compile index-dependent query properties
  virtual bool Compile(CQueryCompiler *compiler);

  //! evaluate query
  virtual void Evaluate();

  //! \b DEBUG: return a canonical string form for this query
  virtual string toString();
  virtual string optionsToString() { return ""; };

  virtual string jsonClass() { return "CQCount"; };
  virtual string jsonData();
  virtual string optionsToJson() { return "null"; };

  //! wrapper for m_dtr->ClearNode()
  virtual void ClearNode();

  //! clear query contents.  if \c deep is true, propagates operation to daughters
  virtual void Clear(bool deep=true);
};

//======================================================================
// functions

/** generate a single count string from a (key,count)-pair */
void GenerateCountString(string &ResultStr, DDCFormatTypeEnum fmt, const string& key, DWORD count);

/** generate a single count string from a CHit */
inline void GenerateCountString(string &ResultStr, DDCFormatTypeEnum fmt, const CHit &hit)
{ GenerateCountString(ResultStr, fmt, hit.m_SortKey.s, hit.m_Value.m_Count); };


#endif /* DDC_QCOUNT_H */
