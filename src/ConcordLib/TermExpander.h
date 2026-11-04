#ifndef DDC_TERM_EXPANDER_H
#define DDC_TERM_EXPANDER_H

#include "morph_dict/common/utilit.h"
#include "../CommonLib/ddcUtil.h"
#include "CCurl.h"

//======================================================================
/*!
  \brief
  Abstract API for term-expansion modules (e.g. thesauri, morphologies, equivalence maps, ...)
*/
class CTermExpander {
public:
    //! class name for this expander
    std::string m_Class;

    //! unique name for this expander
    std::string m_Label;

    //! string argument(s) for this expander (parameters, for stringification)
    std::string m_Param;

public:
    //------------------------------------------------------------
    ///\name Constructors etc.
    //@{
    //! Full constructor (abstract base classes only)
    CTermExpander(const std::string &cls, const std::string& label, const std::string& param)
        : m_Class(cls), m_Label(label), m_Param(param)
    {};

    //! Default constructor, to be overridden by subclasses
    CTermExpander(const std::string &label=std::string("NoLabel"), const std::string& param=std::string(""))
        : m_Class("None"), m_Label(label), m_Param(param)
    {};

    //! clone constructor, handles sub-object cloning according to \a xlate map */
    virtual CTermExpander* mapClone(std::map<CTermExpander*,CTermExpander*>& xlate) const;

    //! clone constructor to create a new expansion object (override this for derived classes) */
    virtual CTermExpander* clone(std::map<CTermExpander*,CTermExpander*>& xlate) const
    { return new CTermExpander(m_Class, m_Label, m_Param); };

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
    virtual std::string configString(void) const;

    //! Expand a single term \a term to a set of terms \a dst
    virtual void expand(const std::string& src, std::set<std::string>& dst);

    //! Expand a set of terms \a src to a set of terms \a dst
    virtual void expand(const std::set<std::string>& src, std::set<std::string>& dst);
    //@}
};

//======================================================================
//! TxId: identity expander (null-op): params: none
class TxId : public CTermExpander {
public:
    TxId(const std::string &label=std::string("Id"), const std::string& param=std::string(""))
        : CTermExpander("Id",label,param)
    {};
    virtual ~TxId(void) {};

    virtual CTermExpander* clone(std::map<CTermExpander*,CTermExpander*>& xlate) const
    { return new TxId(m_Label,m_Param); };
    
    virtual void expand(const std::set<std::string>& src, std::set<std::string>& dst);
};

//======================================================================
//! TxChain: serial chain of (multiple) expanders
typedef std::vector<CTermExpander*> TxList;

class TxChain : public CTermExpander {
public:
    //! chain of sub-expanders; these must be explicitly freed
    TxList m_Chain;

public:
    //! default constructor
    TxChain(const std::string &label=std::string("Chain"), const std::string& param=std::string(""))
        : CTermExpander("Chain",label,param)
    {};

    //! clone constructor
    virtual CTermExpander* clone(std::map<CTermExpander*,CTermExpander*>& xlate) const;

    //! Destructor: sub-expanders are NOT implicitly destroyed!
    virtual ~TxChain(void) {};

    //! append a TxList
    void append(TxList& txl);

    //! append contents of another chain (explicit un-nesting)
    inline void append(TxChain& txc);

    //! append contents of another dispatcher, implicitly un-nesting chains
    void append(CTermExpander *tx);

    //! stringification for query canonicalization: joins chained labels on \a joinstr
    std::string chainString(const std::string& joinstr=std::string("|"));

    //! expand() calls each chained expander on the output of the previous expander
    virtual void expand(const std::set<std::string>& src, std::set<std::string>& dst);
};

//======================================================================
//! TxLang: abstract base class for language-dependent term expanders
class TxLang : public CTermExpander {
public:
    //! DDC-language to use for expansion
    MorphLanguageEnum m_Lang;

public:
    //! param: language name supported by GetLanguageByString()
    TxLang(const std::string& cls=std::string("Lang"), const std::string &label=std::string("Lang"), const std::string& param=std::string("Generic"));
    virtual ~TxLang(void) {};

    virtual CTermExpander* clone(std::map<CTermExpander*,CTermExpander*>& xlate) const
    { return (CTermExpander*)new TxLang(*this); };
  
    //virtual void expand(const set<string>& src, set<string>& dst);

    //! Set language by enum.  Default just sets m_Lang=lang and m_Param=GetStringByLanguage(lang)
    virtual void setLanguage(MorphLanguageEnum lang);

    //! Set language by string identifier using GetLanguageByString()
    //! \li calls setLanguage(MorphLanguageEnum l)
    //! \li throws CExpc if langugage is unknown
    virtual void setLanguage(const std::string &lang);
};

//======================================================================
//! TxMorph: default backwards-compatible morphological expansion (morphy)
class TxMorph : public TxLang {
public:
    //! param: language name, passed to GetLanguageByString()
    TxMorph(const std::string &label=std::string("Morph"), const std::string& param=std::string(""))
        : TxLang("Morph",label,param)
    {};
    virtual ~TxMorph(void) {};

    virtual CTermExpander* clone(std::map<CTermExpander*,CTermExpander*>& xlate) const
    { return (CTermExpander*)new TxMorph(*this); };

    //! modified version of GetWordForms() from QueryNode.cpp
    virtual void expand(const std::set<std::string>& src, std::set<std::string>& dst);
};

//======================================================================
//! TxToLower: convert input to all-lower-case
class TxToLower : public TxLang {
public:
    //! param: language name, passed to GetLanguageByString()
    TxToLower(const std::string &label=std::string("ToLower"), const std::string& param=std::string(""))
        : TxLang("ToLower",label,param)
    {};
    virtual ~TxToLower(void) {};

    virtual CTermExpander* clone(std::map<CTermExpander*,CTermExpander*>& xlate) const
    { return (CTermExpander*)new TxToLower(*this); };
  
    //! wraps ddcMakeLower()
    virtual void expand(const std::set<std::string>& src, std::set<std::string>& dst);
};

//======================================================================
//! TxToUpper: convert input to all-upper-case
class TxToUpper : public TxLang {
public:
    //! param: language name, passed to GetLanguageByString()
    TxToUpper(const std::string &label=std::string("ToUpper"), const std::string& param=std::string(""))
        : TxLang("ToUpper",label,param)
    {};
    virtual ~TxToUpper(void) {};

    virtual CTermExpander* clone(std::map<CTermExpander*,CTermExpander*>& xlate) const
    { return (CTermExpander*)new TxToUpper(*this); };
  
    //! wraps ddcMakeUpper()
    virtual void expand(const std::set<std::string>& src, std::set<std::string>& dst);
};

//======================================================================
//! TxCase: letter-case (upper<->lower) expander
class TxCase : public TxLang {
public:
    //! param: language name, passed to GetLanguageByString()
    TxCase(const std::string &label=std::string("Case"), const std::string& param=std::string(""))
        : TxLang("Case",label,param)
    {};
    virtual ~TxCase(void) {};

    virtual CTermExpander* clone(std::map<CTermExpander*,CTermExpander*>& xlate) const
    { return (CTermExpander*)new TxCase(*this); };
  
    //! modified version of AddFormsWithDifferentRegisters() from QueryNode.cpp
    virtual void expand(const std::set<std::string>& src, std::set<std::string>& dst);
};


//======================================================================
//! \brief TxCurl: abstract term expander using libcurl
class TxCurl : public CTermExpander {
public:
    //! CCurl object to use for expansion query
    CCurl m_CCurl;

public:
    //! default constructor; no implicit compilation
    TxCurl(const std::string &cls=std::string("Curl"), const std::string &label=std::string("Curl"), const std::string& param=std::string(""))
        : CTermExpander(cls,label,param)
    {};

    //! Destructor frees m_Curl if non-NULL
    virtual ~TxCurl(void) {};

    //! clone constructor calls default constructor
    virtual CTermExpander* clone(std::map<CTermExpander*,CTermExpander*>& xlate) const;
  
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
    std::string m_UrlBase;

    //! debug?
    int m_Debug;

    //! \li if true ("map-mode"), argument term(s) must occur in the query response to be included in the output set
    //! \li otherwise ("union-mode", default), literal argument term(s) will always be included in output set
    int m_MapMode;

public:
    //------------------------------------------------------------
    TxCab(const std::string &label=std::string("Cab"), const std::string& param=std::string(""), int Debug=0, int MapMode=0)
        : TxCurl("Cab",label,param), m_Debug(Debug), m_MapMode(MapMode)
    {};
    virtual ~TxCab(void) {};

    virtual CTermExpander* clone(std::map<CTermExpander*,CTermExpander*>& xlate) const;
  
    //! Setup m_Curl object based on object parameters
    //! Default parses space-separated m_Param to set m_UrlBase and m_CCurl->timeout()
    //! \li 1st param: base URL (with trailing query parameter name e.g. "qd=")
    //! \li 2nd param: timeout (seconds)
    //! \li 3rd param: debug (int~bool)
    //! \li 4th param: map-mode (int~bool)
    virtual void compile(void);

    virtual void expand(const std::set<std::string>& src, std::set<std::string>& dst);
};

//======================================================================
//! \brief TxCabMap: HTTP-based term expander using DTA::CAB HTTP protocol in "map-mode"
class TxCabMap : public TxCab {
public:
    //------------------------------------------------------------
    TxCabMap(const std::string &label=std::string("CabMap"), const std::string& param=std::string(""), int Debug=0, int MapMode=1)
        : TxCab(label,param,Debug,MapMode)
    {
        m_Class = "CabMap";
    };
    virtual ~TxCabMap(void) {};

    virtual CTermExpander* clone(std::map<CTermExpander*,CTermExpander*>& xlate) const;
};


//======================================================================
//! TxDispatcher: name-based expansion dispatcher
class TxDispatcher {
public:
    //! typedef for label->expander map
    typedef std::map<std::string,CTermExpander*> TxMap;

    //! maps expander labels to expanders (label keys are case-sensitive!)
    TxMap m_tx;

    //! list of defined expander names in definition order (for config-string generation)
    std::list<std::string> m_txlist;

public:
    //--------------------------------------------------------------
    //\name Constructors etc.
    //@{
    //! Default constructor
    TxDispatcher(void)
    {};

    //! clone constructor copies sub-objects
    TxDispatcher* clone() const;

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
    CTermExpander *addExpander(const std::string &spec);

    //! compile all defined expanders
    void compile(void);

    //! dump dispatcher specifications in a form parseable by parseExpanderSpec() to a string
    //! \param prefix if specified gives a string prefix for the dump
    std::string configString(const std::string &prefix="") const;
    //@}

public:
    //--------------------------------------------------------------
    //\name Runtime API
    //@{
    //! insert or override a label->tx mapping (implicitly sets tx->m_Label=label)
    void insert(const std::string &label, CTermExpander *tx);

    //! insert or override a label->tx mapping; uses tx->m_Label as label
    void insert(CTermExpander *tx);

    //! delete and remove any expander or alias labelled by \a label
    void remove(const std::string &label);

    //! lookup the expander for \a label; returns NULL if no such expander exists
    CTermExpander *get(const std::string &label) const;

    //! extended lookup for an expansion chain; throws CExpc on unknown label
    TxChain getChain(const std::vector<std::string> &labels);

    //! extended lookup for an expansion chain; splits \a spec on " \t\r\n|"
    TxChain getChain(const std::string& spec);
    //@}
};


//======================================================================
// Utilities

//! parse a term expander specification as a space-separated (" \t\n\r") list "LABEL [CLASS=LABEL [PARAM='']]"
void parseTermExpanderSpec(const std::string &spec, std::string &txclass, std::string &txlabel, std::string &txparam);

//! create a new TermExpander from a parsed specification
CTermExpander *newTermExpander(const std::string& class_="Id", const std::string& label=std::string(""), const std::string& param=std::string(""));

#endif /* DDC_TERM_EXPANDER_H */
