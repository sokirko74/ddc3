//-*- Mode: C++ -*-
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
//

#ifndef DDC_QCOUNT_H
#define DDC_QCOUNT_H

#include "../ConcordLib/Query.h"

//======================================================================
//typedef vector<string>    	CQCountByList;

/** default count()-query sample size */
const size_t DDCDefaultCountSampleSize = (size_t)-1;

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

  /** returns true iff this expression can count at the file-level; default returns true */
  virtual bool CanCountByFile() const { return true; };

  /** compile the expression relative to a CQueryCompiler and its associated index */
  virtual bool Compile(CQueryCompiler *compiler);

  /** get string key for the hit \a Hit ; default just throws an exception */
  virtual string& Evaluate(const CHit &Hit);

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
  virtual string& Evaluate(const CHit &Hit) { return m_Label; };
  virtual string jsonClass() { return "CQCountKeyExprConstant"; };
  virtual string toString() { return string("@'") + escapeChars(m_Label,"\\'") + "'"; };
};

//----------------------------------------------------------------------
/*! count-key expression: metadata-attribute */
class CQCountKeyExprMeta : public CQCountKeyExpr {
public:
  //! last file-number evaluated
  DWORD  m_CurFile;

  //! last key generated
  string m_CurKey;

public:
  CQCountKeyExprMeta(const string &label="*") : CQCountKeyExpr(label), m_CurFile(-1), m_CurKey("") {};
  virtual ~CQCountKeyExprMeta() {};
};

//----------------------------------------------------------------------
/*! count-key expression: fileid (aka docid) */
class CQCountKeyExprFileId : public CQCountKeyExprMeta {
private:
  char buf[16];
public:
  CQCountKeyExprFileId(const string &label="fileid") : CQCountKeyExprMeta(label) {};
  virtual ~CQCountKeyExprFileId() {};
  virtual string& Evaluate(const CHit &Hit);
  virtual string jsonClass() { return "CQCountKeyExprFileId"; };
};

//----------------------------------------------------------------------
/*! count-key expression: indexed */
class CQCountKeyExprIndexed : public CQCountKeyExprMeta {
public:
  class CConcIndexator* m_pIndexator;
public:
  CQCountKeyExprIndexed(const string &label="file") : CQCountKeyExprMeta(label) {};
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
  virtual string& Evaluate(const CHit &Hit);
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
  virtual string& Evaluate(const CHit &Hit);
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
  virtual string& Evaluate(const CHit &Hit);
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
  virtual string& Evaluate(const CHit &Hit);
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
  virtual bool CanCountByFile() const { return m_Src->CanCountByFile(); };
  virtual bool Compile(CQueryCompiler *compiler);
  virtual string& Evaluate(const CHit &Hit);
  virtual string toString();
  virtual string jsonClass() { return "CQCountKeyExprRegex"; };
  virtual string jsonData();
};

//----------------------------------------------------------------------
/*! count-key expression: context (token) attribute */
class CQCountKeyExprToken : public CQCountKeyExprIndexed
{
public:
  //! name of token index attribute
  string m_IndexName;

  //! match-id of anchor token (0 for any)
  BYTE   m_MatchId;

  //! offset of reference token
  int    m_Offset;

  //! underlying index-set (post-compile())
  CStringIndexSet *m_pIndex;

public:
  CQCountKeyExprToken(const string &IndexName="Token", BYTE MatchId=0, int Offset=0)
    : CQCountKeyExprIndexed("token"), m_IndexName(IndexName), m_MatchId(MatchId), m_Offset(Offset), m_pIndex(NULL)
  {};
  virtual ~CQCountKeyExprToken() {};
  virtual bool HasMatchId() const { return (m_MatchId != 0); };
  virtual bool CanCountByFile() const { return false; };
  virtual bool Compile(CQueryCompiler *compiler);
  virtual string& Evaluate(const CHit &Hit);
  virtual string toString();
  virtual string jsonClass() { return "CQCountKeyExprToken"; };
  virtual string jsonData();
};

//----------------------------------------------------------------------
// count-key expr: list
class CQCountKeyExprList : public CQCountKeyExpr
{
public:
  /** underlying expression list */
  vector<CQCountKeyExpr*> m_Exprs;

  /** temporary key */
  string m_Key;

public:
  CQCountKeyExprList() : m_Key("") {};
  virtual ~CQCountKeyExprList();

  /*! clear and delete all sub-expressions */
  virtual void Clear();

  /*! wrapper for m_Exprs.empty() */
  inline bool empty() const { return m_Exprs.empty(); };

  /*! append a count-by expression */
  void PushKey(CQCountKeyExpr *expr)
  { m_Exprs.push_back(expr); };

  /*! returns true iff all sub-expressions can count by file */
  virtual bool CanCountByFile() const;

  /*! returns true iff any sub-expression uses match-ids */
  virtual bool HasMatchId() const;

  virtual bool Compile(CQueryCompiler *compiler);
  virtual string& Evaluate(const CHit &Hit);

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

  //! sample size (sub-query limit)
  size_t m_sample;

  //! sort-order one of: NoSort, (Less|Greater)ByCount(Key|Value)
  HitSortEnum m_sort;

  //! list of count-bin metadata key expressions
  CQCountKeyExprList m_keys;

public:
  //! bison constructor
  CQCount(CQuery *dtr_, const CQCountKeyExprList &keys_, size_t sample_=DDCDefaultCountSampleSize, HitSortEnum sort_=NoSort)
  : CQuery("count"),
    m_dtr(dtr_),
    m_sample(sample_),
    m_sort(sort_),
    m_keys(keys_)
  {};

  //! Default destructor.
  virtual ~CQCount(void);

public:
  //! Compile index-dependent query properties
  virtual bool Compile(CQueryCompiler *compiler);

  //! evaluate query
  virtual void Evaluate();

  //! returns true iff this query uses a nontrival match-id operator
  virtual bool HasMatchId() const
  { return (m_dtr && m_dtr->HasMatchId()) || m_keys.HasMatchId(); };

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
void GenerateCountString(string &ResultStr, DDCFormatTypeEnum fmt, const string& key, size_t count);

/** generate a single count string from a CHit */
inline void GenerateCountString(string &ResultStr, DDCFormatTypeEnum fmt, const CHit &hit)
{ GenerateCountString(ResultStr, fmt, hit.m_SortKey.s, hit.m_Value.m_Count); };


#endif /* DDC_QCOUNT_H */
