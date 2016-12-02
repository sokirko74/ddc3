//-*- Mode: C++ -*-
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2016 by Bryan Jurish
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

#ifndef DDC_QUERY_OPTIONS_H
#define DDC_QUERY_OPTIONS_H

#include "../ConcordLib/QueryFilter.h"

//======================================================================
// typedefs

class CQueryCompiler;  //-- forward decl

typedef vector<CQFilter*> 	CQFilterList;
typedef vector<string>    	CQSubcorpusList;

//======================================================================
/*!
  \brief root-level query options (filters and flags)
*/
class CQueryOptions : public ddcObject {
public:
  //! how many hits of the left and right context should be output (must be &lt;= m_MaxContextSentencesCount)
  size_t m_ContextSentencesCount;

  // if true, DDC shows file names, instead of bibliographical information for this query
  //! (CConcIndexator::m_bOutputBibliographyOfHits is default value for outputting bibliography
  bool m_bEnableBibliography;
  
  //! if true, DDC initializes CHit::m_DebugRank
  bool m_bDebugRank;

  //! whether to return a separate hit for each occurrence, or collect into distinct instances of the selected container (sentence)
  //! default=false; used by CQueryNode::Evaluate()
  bool m_bSeparateHits;

  //! the index of text area where DDC should perform the input query
  int m_TextAreaNo;

  //! list of all '#WITHIN' arguments (break collections or text areas) from currently parsed query 
  vector<string> m_Within;

  //! the break collection name which should be used while querying
  string m_HitTypeStr;
  
  //! (abstract) filters and sort operators which should be applied to the resulted hit set
  CQFilterList m_QFilters;

  //! (runtime) filters and sort operators which should be applied to the resulted hit set (available after Compile())
  vector<CDDCFilterWithBounds> m_Filters; 

  //! selected subcorpora for this query
  CQSubcorpusList m_Subcorpora;

public:
  //------------------------------------------------------------
  ///\name Constructors etc.
  //@{

  //! Default constructor
  CQueryOptions()
    : 
      m_ContextSentencesCount(0),
      m_bEnableBibliography(true),
      m_bDebugRank(false),
      m_bSeparateHits(false),
      m_TextAreaNo(UnknownTextAreaNo),
      m_HitTypeStr("")
  {};

  //! Default destructor; calls Clear
  virtual ~CQueryOptions(void);

  //! swap options
  void swap(CQueryOptions &x);

  //! assign options (wraps assignment operator)
  inline void assign(const CQueryOptions &src)
  { *this = src; };

  //! clone object (wraps copy constructor)
  inline CQueryOptions* Clone(void) const
  { return new CQueryOptions(*this); };
  //@}

public:
  //------------------------------------------------------------
  ///\name CQueryOptions API
  //@{
  //! Compile index-dependent filter properties (required for evaluation)
  virtual bool Compile(CQueryCompiler *compiler);

  //! clear options.
  virtual void Clear();

  //! returns true iff all defined filters are file-based (for optimized count(*) evaluation)
  bool CanFilterByFile() const;

  //! returns true iff all defined filters are trivial (i.e. do not change default hit-sort order)
  bool IsTrivialFilter() const;
  //@}

public:
  //------------------------------------------------------------
  ///\name ddcObject API
  //@{
  virtual ddcObjectList Children() const;
  virtual void DisownChildren();
  virtual string toString();
  virtual string jsonClass() { return "CQueryOptions"; };
  virtual string jsonData();
  //@}
};

#endif /* DDC_QUERY_OPTIONS_H */

