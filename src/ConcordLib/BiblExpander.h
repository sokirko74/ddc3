#ifndef DDC_BIBL_EXPANDER_H
#define DDC_BIBL_EXPANDER_H

#include "TermExpander.h"

//======================================================================
/*!
  \brief
  Abstract API for bibliographic metadata-expansion modules
*/
class CBiblExpander {
public:
    //! unique label for this expander
    std::string m_BxLabel;

    //! physically indexed target bibliographic field name
    std::string m_BxTarget;

    //! string parameters (for stringification)
    std::string m_BxParam;

public:
    //------------------------------------------------------------
    ///\name Constructors etc.
    //@{
    CBiblExpander(const std::string& label=std::string("NoLabel"), const std::string& target=std::string("NoTarget"), const std::string& param=std::string(""))
        : m_BxLabel(label), m_BxTarget(target), m_BxParam(param)
    {};

    //! Default destructor.
    virtual ~CBiblExpander(void) {};

    //! set up object based on label, target, and/or parameter strings; default implementation does nothing
    virtual void compile(void) {};
    //@}

public:
    //------------------------------------------------------------
    ///\name API
    //@{
    //! String form of this expander. Default is m_BxLabel + " " + m_BxTarget + " " + m_BxParam
    virtual std::string configString(void) const;

    //! Expand a single term \a term to a set of terms \a dst ; default just calls expand(const set<string>&, set<string>&) for temporary singleton source-set
    virtual void expand(const std::string& src, std::set<std::string>& dst);

    //! Expand a set of terms \a src to a set of terms \a dst ; must be overridden by subclass
    virtual void expand(const std::set<std::string>& src, std::set<std::string>& dst);
    //@}
};

//======================================================================
/*! BxTermWrapper : bibliographic expander wrapping term
  \brief
  Abstract API for bibliographic metadata-expansion modules
*/
class BxTermWrapper : public CBiblExpander {
public:
    //! underlying CTermExpander
    CTermExpander *m_BxTx;

public:
    //! parses term-expander args as "CLASS PARAM...", uses term-expander label = bibl-expander label
    BxTermWrapper(const std::string& label=std::string("NoLabel"), const std::string& target=std::string("NoTarget"), const std::string& param=std::string(""));
    virtual ~BxTermWrapper(void);
    virtual void compile(void);
    virtual void expand(const std::set<std::string>& src, std::set<std::string>& dst);
}; 

#endif /* DDC_BIBL_EXPANDER_H */
