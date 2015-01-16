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

#ifndef DDC_TERM_EXPANDER_H
#define DDC_TERM_EXPANDER_H

#include "../common/utilit.h"
#include "CCurl.h"

//======================================================================
/*!
  \brief
   Abstract API for term-expansion modules (e.g. thesauri, morphologies, equivalence maps, ...)
*/
class CTermExpander {
public:
  //! class name for this expander
  string m_Class;

  //! unique name for this expander
  string m_Label;

  //! string argument(s) for this expander (parameters, for stringification)
  string m_Param;

public:
  //------------------------------------------------------------
  ///\name Constructors etc.
  //@{
  //! Full constructor (abstract base classes only)
  CTermExpander(const string &cls, const string& label, const string& param)
    : m_Class(cls), m_Label(label), m_Param(param)
  {};

  //! Default constructor, to be overridden by subclasses
  CTermExpander(const string &label=string("NoLabel"), const string& param=string(""))
    : m_Class("None"), m_Label(label), m_Param(param)
  {};

  //! Default destructor.
  virtual ~CTermExpander(void) {};

  //! set up object based on label and/or parameter string; default implementation does nothing
  virtual void compile(void) {};
  //@}

public:
  //------------------------------------------------------------
  ///\name API
  //@{
  //! String form of this expander. Default is m_Class + " " + m_Label + " " + m_Param
  virtual string configString(void) const;

  //! Expand a single term \a term to a set of terms \a dst
  virtual void expand(const string& src, set<string>& dst);

  //! Expand a set of terms \a src to a set of terms \a dst
  virtual void expand(const set<string>& src, set<string>& dst);
  //@}
};

//======================================================================
//! TxId: identity expander (null-op): params: none
class TxId : public CTermExpander {
public:
  TxId(const string &label=string("Id"), const string& param=string(""))
    : CTermExpander("Id",label,param)
  {};
  virtual ~TxId(void) {};
  virtual void expand(const set<string>& src, set<string>& dst);
};

//======================================================================
//! TxChain: serial chain of (multiple) expanders
typedef vector<CTermExpander*> TxList;

class TxChain : public CTermExpander {
public:
  //! chain of sub-expanders; these must be explicitly freed
  TxList m_Chain;

public:
  //! default constructor
  TxChain(const string &label=string("Chain"), const string& param=string(""))
    : CTermExpander("Chain",label,param)
  {};

  //! Destructor: sub-expanders are NOT implicitly destroyed!
  virtual ~TxChain(void) {};

  //! append a TxList
  void append(TxList& txl);

  //! append contents of another chain (explicit un-nesting)
  inline void append(TxChain& txc);

  //! append contents of another dispatcher, implicitly un-nesting chains
  void append(CTermExpander *tx);

  //! stringification for query canonicalization: joins chained labels on \a joinstr
  string chainString(const string& joinstr=string("|"));

  //! expand() calls each chained expander on the output of the previous expander
  virtual void expand(const set<string>& src, set<string>& dst);
};

//======================================================================
//! TxLang: abstract base class for language-dependent term expanders
class TxLang : public CTermExpander {
public:
  //! DDC-language to use for expansion
  MorphLanguageEnum m_Lang;

public:
  //! param: language name supported by GetLanguageByString()
  TxLang(const string& cls=string("Lang"), const string &label=string("Lang"), const string& param=string("Generic"));
  virtual ~TxLang(void) {};

  //virtual void expand(const set<string>& src, set<string>& dst);

  //! Set language by enum.  Default just sets m_Lang=lang and m_Param=GetStringByLanguage(lang)
  virtual void setLanguage(MorphLanguageEnum lang);

  //! Set language by string identifier using GetLanguageByString()
  //! \li calls setLanguage(MorphLanguageEnum l)
  //! \li throws CExpc if langugage is unknown
  virtual void setLanguage(const string &lang);
};

//======================================================================
//! TxMorph: default backwards-compatible morphological expansion (morphy)
class TxMorph : public TxLang {
public:
  //! param: language name, passed to GetLanguageByString()
  TxMorph(const string &label=string("Morph"), const string& param=string(""))
    : TxLang("Morph",label,param)
  {};
  virtual ~TxMorph(void) {};

  //! modified version of GetWordForms() from QueryNode.cpp
  virtual void expand(const set<string>& src, set<string>& dst);
};

//======================================================================
//! TxToLower: convert input to all-lower-case
class TxToLower : public TxLang {
public:
  //! param: language name, passed to GetLanguageByString()
  TxToLower(const string &label=string("ToLower"), const string& param=string(""))
    : TxLang("ToLower",label,param)
  {};
  virtual ~TxToLower(void) {};

  //! wraps RmlMakeLower()
  virtual void expand(const set<string>& src, set<string>& dst);
};

//======================================================================
//! TxToUpper: convert input to all-upper-case
class TxToUpper : public TxLang {
public:
  //! param: language name, passed to GetLanguageByString()
  TxToUpper(const string &label=string("ToUpper"), const string& param=string(""))
    : TxLang("ToUpper",label,param)
  {};
  virtual ~TxToUpper(void) {};

  //! wraps RmlMakeUpper()
  virtual void expand(const set<string>& src, set<string>& dst);
};

//======================================================================
//! TxCase: letter-case (upper<->lower) expander
class TxCase : public TxLang {
public:
  //! param: language name, passed to GetLanguageByString()
  TxCase(const string &label=string("Case"), const string& param=string(""))
    : TxLang("Case",label,param)
  {};
  virtual ~TxCase(void) {};

  //! modified version of AddFormsWithDifferentRegisters() from QueryNode.cpp
  virtual void expand(const set<string>& src, set<string>& dst);
};


//======================================================================
//! \brief TxCurl: abstract term expander using libcurl
class TxCurl : public CTermExpander {
public:
  //! CCurl object to use for expansion query
  CCurl m_CCurl;

public:
  //! default constructor; no implicit compilation
  TxCurl(const string &cls=string("Curl"), const string &label=string("Curl"), const string& param=string(""))
    : CTermExpander(cls,label,param)
  {};

  //! Destructor frees m_Curl if non-NULL
  virtual ~TxCurl(void) {};

  //--------------------------------------------------------------
  //\name Subclass API
  //@{

  //! Initializer sets up m_Curl object based on object parameters
  //! Default implementation sets CCurl url(""), timeout(5), noSignal(1), failOnError(1), and setDataCallback()
  virtual void compile(void);

  //! Wrapper for m_CCurl.perform_cached()
  virtual bool perform(void)
  { return m_CCurl.perform_cached(); };
  //@}

  //--------------------------------------------------------------
  // expansion API (nothing here)
  //virtual void expand(const set<string>& src, set<string>& dst);
};


//======================================================================
//! \brief TxCab: HTTP-based term expander using DTA::CAB HTTP protocol
//! \detail I/O format is DTA::CAB::Format::ExpandList (newline- and TAB-separated lists)
class TxCab : public TxCurl {
public:
  //! base URL; newline-separated query argument(s) will be appended for each expansion query
  string m_UrlBase;

  //! debug?
  int m_Debug;

  //! \li if true ("map-mode"), argument term(s) must occur in the query response to be included in the output set
  //! \li otherwise ("union-mode", default), literal argument term(s) will always be included in output set
  int m_MapMode;

public:
  //------------------------------------------------------------
  TxCab(const string &label=string("Cab"), const string& param=string(""), int Debug=0, int MapMode=0)
    : TxCurl("Cab",label,param), m_Debug(Debug), m_MapMode(MapMode)
  {};
  virtual ~TxCab(void) {};

  //! Setup m_Curl object based on object parameters
  //! Default parses space-separated m_Param to set m_UrlBase and m_CCurl->timeout()
  //! \li 1st param: base URL (with trailing query parameter name e.g. "qd=")
  //! \li 2nd param: timeout (seconds)
  //! \li 3rd param: debug (int~bool)
  //! \li 4th param: map-mode (int~bool)
  virtual void compile(void);

  virtual void expand(const set<string>& src, set<string>& dst);
};

//======================================================================
//! \brief TxCabMap: HTTP-based term expander using DTA::CAB HTTP protocol in "map-mode"
class TxCabMap : public TxCab {
public:
  //------------------------------------------------------------
  TxCabMap(const string &label=string("CabMap"), const string& param=string(""), int Debug=0, int MapMode=1)
    : TxCab(label,param,Debug,MapMode)
  {
    m_Class = "CabMap";
  };
  virtual ~TxCabMap(void) {};
};


//======================================================================
//! TxDispatcher: name-based expansion dispatcher
class TxDispatcher {
public:
  //! typedef for label->expander map
  typedef map<string,CTermExpander*> TxMap;

  //! maps expander labels to expanders (label keys are case-sensitive!)
  TxMap m_tx;

public:
  //--------------------------------------------------------------
  //\name Constructors etc.
  //@{
  //! Default constructor
  TxDispatcher(void)
  {};

  //! Default destructor: frees all expanders in m_tx
  ~TxDispatcher(void);

  //! clear all named expanders; also deletes them if doDelete is true (default)
  void clear(bool doDelete=true);

  //! add default expanders for morph language \a mlang and case language \a clang
  //! \li adds expanders TxMorph "infl mlang", TxCase "case clang", TxId "id", TxChain "Token infl case"
  //!     if not already defined
  //! \li if caseSensitive is false, case-expander will NOT be included in default chain
  void ensureDefaultExpanders(MorphLanguageEnum mlang, MorphLanguageEnum clang, bool doInfl=true, bool doCase=true);

  //! wrapper for ensureDefaultExpanders(lang,lang)
  inline void ensureDefaultExpanders(MorphLanguageEnum lang=morphGeneric)
  { ensureDefaultExpanders(lang,lang); };
  //@}

public:
  //--------------------------------------------------------------
  //\name I/O API
  //@{
  //! parse a term expander specification from a string \a spec
  //! \li \a spsec is interpreted by parseExpanderSpec()
  //! \li calls newTermExpander() to allocate the new expander
  //! \li does NOT add expander to the map
  //! \returns newly created expander
  CTermExpander *addExpander(const string &spec);

  //! compile all defined expanders
  void compile(void);

  //! dump dispatcher specifications in a form parseable by parseExpanderSpec() to a string
  //! \param prefix if specified gives a string prefix for the dump
  string configString(const string &prefix="") const;
  //@}

public:
  //--------------------------------------------------------------
  //\name Runtime API
  //@{
  //! insert or override a label->tx mapping (implicitly sets tx->m_Label=label)
  void insert(const string &label, CTermExpander *tx);

  //! insert or override a label->tx mapping; uses tx->m_Label as label
  void insert(CTermExpander *tx);

  //! delete and remove any expander or alias labelled by \a label
  void remove(const string &label);

  //! lookup the expander for \a label; returns NULL if no such expander exists
  CTermExpander *get(const string &label);

  //! extended lookup for an expansion chain; throws CExpc on unknown label
  TxChain getChain(const vector<string> &labels);

  //! extended lookup for an expansion chain; splits \a spec on " \t\r\n|"
  TxChain getChain(const string& spec);
  //@}
};


//======================================================================
// Utilities

//! parse a term expander specification as a space-separated (" \t\n\r") list "LABEL [CLASS=LABEL [PARAM='']]"
void parseTermExpanderSpec(const string &spec, string &txclass, string &txlabel, string &txparam);

//! create a new TermExpander from a parsed specification
CTermExpander *newTermExpander(const string& class_="Id", const string& label=string(""), const string& param=string(""));

#endif /* DDC_TERM_EXPANDER_H */

