#ifndef DDC_QFILTER_H
#define DDC_QFILTER_H

#include "ConcHolder.h"

class CQueryCompiler;       //-- forward decl
class CQueryOptions;        //-- forward decl
class CQCountKeyExprList;   //-- forward decl, for CQFPrune
class CQCount;              //-- forward decl, for CQFPrune

//======================================================================
// CQFilter

//! class for global query filters aka "query operators"
class CQFilter : public ddcObject {
public:
    //------------------------------------------------------------
    //!\name CQFilter API
    //@{
    //! Default constructor
    CQFilter()
    {};

    //! Default destructor (empty)
    virtual ~CQFilter() {};
    
    //! Run fast (un)satisfiability checks for filter before Compile() is called.  Default just returns true.
    virtual bool CheckSatisfiable(CQueryCompiler *compiler, CQueryOptions *options);

    //! apply the filter to the given compiler
    virtual bool Compile(CQueryCompiler *compiler, CQueryOptions *options);

    //! clone this filter
    virtual CQFilter* Clone()
    { return new CQFilter(*this); };

    //! sort-type for this filter (if any)
    virtual HitSortEnum FilterType() const
    { return NoSort; };
    //@}

    //------------------------------------------------------------
    //!\name ddcObject API
    //@{
    //! convert filter to a canonical string
    virtual std::string toString(void) { return std::string("#FILTER[?]"); };
    virtual std::string jsonClass(void) { return "CQFilter"; };
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
            const std::string &arg0=std::string(""),
            const std::string &arg1=std::string(""),
            const std::string &arg2=std::string("")
        );

    CQFSort(HitSortEnum   ftype,
            const std::string &arg0,
            int           arg1i,
            int           arg2i
        );

    virtual ~CQFSort() {};

    virtual CQFilter* Clone()
    { return (CQFilter*)new CQFSort(*this); };

    virtual HitSortEnum FilterType() const
    { return m_Filter.m_FilterType; };

    //! swap lower- and upper-bounds if they not in logical order
    void SortBounds(void);

    //! compile the filter.  Default implementation just pushes m_Filter onto options->m_Filters
    virtual bool Compile(CQueryCompiler *compiler, CQueryOptions *options);

    //! compilation utility: return a valid bibliographic attribute for \a attrName
    //!  + prefers \a attrName if that is a valid attribute name
    //!  + otherwise uses compiler->m_pHolder->m_pConcordance->m_Bibl.m_DefaultAttrName if non-empty and a valid attribute name
    //!  + otherwise returns an empty string
    std::string ResolveAttributeName(CQueryCompiler *compiler, const std::string& attrName, bool allowBiblExpander=false);

    //! compilation & satisfiability-check utility: return constant bibliographic index for \a attrName (if it is one), or NULL
    CFreeBiblIndex *GetBiblConstant(CQueryCompiler *compiler, const std::string &attrName, bool allowBiblExpander=true);

    //-- ddcObject API & utilities
    //! stringification utility: quoted strign for arg, or empty string
    std::string argString(const std::string &arg) const;
    virtual std::string toString(void);
    virtual std::string jsonClass(void) { return "CQFSort"; };
    virtual std::string jsonMinMax(void);
    virtual std::string jsonType(void);
    virtual std::string jsonData(void) { return (this->jsonType()+","+this->jsonMinMax()); };
};

//======================================================================
// CQFRankSort

class CQFRankSort : public CQFSort {
public:
    CQFRankSort(HitSortEnum ftype=GreaterByRank)
        : CQFSort(ftype)
    {};
    virtual ~CQFRankSort() {};

    virtual CQFilter* Clone()
    { return (CQFilter*)new CQFRankSort(*this); };

    virtual std::string jsonClass(void) { return "CQFRankSort"; };
    virtual std::string jsonData(void) { return this->jsonType(); };
};

//======================================================================
// CQFDateSort

class CQFDateSort : public CQFSort {
public:
    CQFDateSort(HitSortEnum ftype=LessByDate, const std::string &lb=std::string(""), const std::string &ub=std::string(""))
        : CQFSort(ftype,std::string(""),lb,ub)
    {};
    virtual ~CQFDateSort() {};

    virtual CQFilter* Clone()
    { return (CQFilter*)new CQFDateSort(*this); };
  
    static int Str2Date(const std::string &datestr, int onEmpty=0);

    virtual bool Compile(CQueryCompiler *compiler, CQueryOptions *options);
    virtual std::string jsonClass(void) { return "CQFDateSort"; };
};

//======================================================================
// CQFSizeSort

class CQFSizeSort : public CQFSort {
public:
    CQFSizeSort(HitSortEnum ftype=LessBySize, const std::string &lb=std::string(""), const std::string &ub=std::string(""))
        : CQFSort(ftype,std::string(""),lb,ub)
    {};

    CQFSizeSort(HitSortEnum ftype=LessBySize, int lb=INT_MIN, int ub=INT_MAX);

    virtual ~CQFSizeSort() {};

    virtual CQFilter* Clone()
    { return (CQFilter*)new CQFSizeSort(*this); };

    virtual bool Compile(CQueryCompiler *compiler, CQueryOptions *options);
    virtual std::string jsonClass(void) { return "CQFSizeSort"; };
};

//======================================================================
// CQFRandomSort

class CQFRandomSort : public CQFSort {
public:
    CQFRandomSort(const std::string &seed0=std::string(""))
        : CQFSort(RandomSort,std::string(""),seed0)
    {};

    CQFRandomSort(int seed0);

    virtual ~CQFRandomSort() {};

    virtual CQFilter* Clone()
    { return (CQFilter*)new CQFRandomSort(*this); };

    virtual bool Compile(CQueryCompiler *compiler, CQueryOptions *options);
    virtual std::string jsonClass(void) { return "CQFRandomSort"; };
    virtual std::string jsonData(void) { return (this->jsonType()+",\"Seed\":"+jsonStr(m_arg1)); };
};

//======================================================================
// CQFBiblSort

//! m_arg0: field name, m_arg1: lower_bound, m_arg2: upper_bound
class CQFBiblSort : public CQFSort {
public:
    CQFBiblSort(HitSortEnum ftype=LessByFreeBiblField,
                const std::string &field=std::string(""),
                const std::string &lb=std::string(""),
                const std::string &ub=std::string(""))
        : CQFSort(ftype,field,lb,ub)
    {};

    virtual ~CQFBiblSort() {};

    virtual CQFilter* Clone()
    { return (CQFilter*)new CQFBiblSort(*this); };

    //! compile the filter.  requires reference to underlying CConcIndexator
    virtual bool Compile(CQueryCompiler *compiler, CQueryOptions *options);

    virtual std::string toString(void);
    virtual std::string jsonClass(void) { return "CQFBiblSort"; };
    virtual std::string jsonData(void);
    virtual std::string jsonMinMax(void);
};

//======================================================================
// CQFContextSort (formerly CQFBigramSort)

//! m_arg0: field name, m_arg1: lower_bound, m_arg2: upper_bound
class CQFContextSort : public CQFSort {
public:
    CQFContextSort(HitSortEnum ftype=LessByMiddleContext,
                   const std::string &field=std::string(""),
                   int matchid=0,
                   int offset=0,
                   const std::string &lb=std::string(""),
                   const std::string &ub=std::string(""))
        : CQFSort(ftype,field,lb,ub)
    {
        m_Filter.m_ContextMatchId = matchid;
        m_Filter.m_ContextOffset = offset;
    };

    virtual ~CQFContextSort() {};

    virtual CQFilter* Clone()
    { return (CQFilter*)new CQFContextSort(*this); };

    //! compile the filter
    virtual bool Compile(CQueryCompiler *compiler, CQueryOptions *options);

    virtual std::string toString(void);
    virtual std::string jsonClass(void) { return "CQFContextSort"; };
    virtual std::string jsonData(void);
};

//======================================================================
// CQFHasField (abstract)

class CQFHasField : public CQFSort {
public:
    //! is this a negated filter?
    bool m_Negated;

public:
    CQFHasField(const std::string &field, const std::string &val=std::string(""), bool isNegated=false)
        : CQFSort(NoSort, field, val, std::string("")), m_Negated(isNegated)
    {};

    virtual ~CQFHasField() {};

    virtual CQFilter* Clone()
    { return (CQFilter*)new CQFHasField(*this); };

    //! negate the filter condition
    virtual void Negate(void);

    //! compile the filter.  requires reference to underlying CConcIndexator.
    //! CQFHasField implementation just ensures that m_arg0, m_arg1 are non-empty, throwing a CExpc otherwise
    virtual bool Compile(CQueryCompiler *compiler, CQueryOptions *options);

    //! value string for stringification
    virtual std::string valueString(void);

    //! generic stringification; uses valueString()
    virtual std::string toString(void);

    virtual std::string jsonClass(void) { return "CQFHasField"; };
    virtual std::string jsonFieldValue(void) { return jsonStr(m_arg1); };
    virtual std::string jsonMinMax(void);
};


//======================================================================
// CQFHasFieldValue

class CQFHasFieldValue : public CQFHasField {
public:
    CQFHasFieldValue(const std::string &field, const std::string &val=std::string(""), bool isNegated=false)
        : CQFHasField(field, val, isNegated)
    {};

    virtual ~CQFHasFieldValue() {};

    virtual CQFilter* Clone()
    { return (CQFilter*)new CQFHasFieldValue(*this); };

    //! Run fast (un)satisfiability checks for filter before Compile() is called.  Default just returns true.
    virtual bool CheckSatisfiable(CQueryCompiler *compiler, CQueryOptions *options);
    
    //! compile the filter.  requires reference to underlying CConcIndexator
    virtual bool Compile(CQueryCompiler *compiler, CQueryOptions *options);
    virtual std::string jsonClass(void) { return "CQFHasFieldValue"; };
};

//======================================================================
// CQFHasFieldRegex

class CQFHasFieldRegex : public CQFHasField {
public:
    //! target regex (same as m_arg1 for direct regex filters; auto-generated for prefix-, suffix-, and infix-filters)
    std::string m_Regex;

public:
    CQFHasFieldRegex(const std::string &field, const std::string &val=std::string(""), bool isNegated=false)
        : CQFHasField(field, val, isNegated), m_Regex(val)
    {};

    virtual ~CQFHasFieldRegex() {};

    virtual CQFilter* Clone()
    { return (CQFilter*)new CQFHasFieldRegex(*this); };

    //! Run fast (un)satisfiability checks for filter before Compile() is called.  Default just returns true.
    virtual bool CheckSatisfiable(CQueryCompiler *compiler, CQueryOptions *options);

    //! compile the filter.  requires reference to underlying CConcIndexator
    virtual bool Compile(CQueryCompiler *compiler, CQueryOptions *options);

    virtual std::string valueString(void);
    virtual std::string jsonClass(void) { return "CQFHasFieldRegex"; };
};

//======================================================================
// CQFHasFieldPrefix

class CQFHasFieldPrefix : public CQFHasFieldRegex {
public:
    CQFHasFieldPrefix(const std::string &field, const std::string &val=std::string(""), bool isNegated=false)
        : CQFHasFieldRegex(field, val, isNegated)
    {
        m_Regex = std::string("^") + escapeRegex(val);
    };

    virtual ~CQFHasFieldPrefix() {};

    virtual CQFilter* Clone()
    { return (CQFilter*)new CQFHasFieldPrefix(*this); };
  
    virtual std::string valueString(void);
    virtual std::string jsonClass(void) { return "CQFHasFieldPrefix"; };
};

//======================================================================
// CQFHasFieldSuffix

class CQFHasFieldSuffix : public CQFHasFieldRegex {
public:
    CQFHasFieldSuffix(const std::string &field, const std::string &val=std::string(""), bool isNegated=false)
        : CQFHasFieldRegex(field, val, isNegated)
    {
        m_Regex = escapeRegex(val) + "$";
    };

    virtual ~CQFHasFieldSuffix() {};

    virtual CQFilter* Clone()
    { return (CQFilter*)new CQFHasFieldSuffix(*this); };
  
    virtual std::string valueString(void);
    virtual std::string jsonClass(void) { return "CQFHasFieldSuffix"; };
};

//======================================================================
// CQFHasFieldInfix

class CQFHasFieldInfix : public CQFHasFieldRegex {
public:
    CQFHasFieldInfix(const std::string &field, const std::string &val=std::string(""), bool isNegated=false)
        : CQFHasFieldRegex(field, val, isNegated)
    {
        m_Regex = escapeRegex(val);
    };

    virtual ~CQFHasFieldInfix() {};

    virtual CQFilter* Clone()
    { return (CQFilter*)new CQFHasFieldInfix(*this); };
  
    virtual std::string valueString(void);
    virtual std::string jsonClass(void) { return "CQFHasFieldInfix"; };
};

//======================================================================
// CQFHasFieldSet

class CQFHasFieldSet : public CQFHasField {
public:
    //! original target strings string
    std::set<std::string> m_Values;

public:
    CQFHasFieldSet(const std::string &field, const std::set<std::string>& vals=std::set<std::string>(), bool isNegated=false)
        : CQFHasField(field, std::string("{}"), isNegated), m_Values(vals)
    {};

    virtual ~CQFHasFieldSet() {};

    virtual CQFilter* Clone()
    { return (CQFilter*)new CQFHasFieldSet(*this); };

    //! Run fast (un)satisfiability checks for filter before Compile() is called.  Default just returns true.
    virtual bool CheckSatisfiable(CQueryCompiler *compiler, CQueryOptions *options);

    //! compile the filter.  requires reference to underlying CConcIndexator
    virtual bool Compile(CQueryCompiler *compiler, CQueryOptions *options);

    //! utility for use by subclasses: comma-separated list of strings in \a values
    std::string SetValueString(const std::set<std::string> &values);

    //! wrapper for SetValueString(m_Values)
    inline std::string SetValueString(void)
    { return SetValueString(m_Values); };

    //! stringification virtual method
    virtual std::string valueString(void);

    virtual std::string jsonClass(void) { return "CQFHasFieldSet"; };
    virtual std::string jsonFieldValue(void);
};

//======================================================================
// CQFPrune

//! class for global query pruning filters
//! m_arg0 : pruning limit (maximum number of hits per key)
class CQFPrune : public CQFSort {
public:
    //! maximum number of hits per count-key
    size_t m_limit;

    //! list count-keys (externally allocated, freed here)
    CQCountKeyExprList *m_keys;

    //! underlying counts
    CCountMap m_Counts;

public:
    //------------------------------------------------------------
    //!\name CQFilter API
    //@{
    CQFPrune(HitSortEnum ftype=LessByPruneKey, size_t Limit=0, CQCountKeyExprList* Keys=NULL);

    //! Default destructor (empty)
    virtual ~CQFPrune();

    //! clone this filter (also clones m_keys)
    virtual CQFilter* Clone();

    //! apply the filter to the given compiler
    virtual bool Compile(CQueryCompiler *compiler, CQueryOptions *options);
    //@}

    //------------------------------------------------------------
    //!\name ddcObject API
    //@{
    //! convert filter to a canonical string
    virtual std::string toString(void);

    virtual std::string jsonClass(void) { return "CQFPrune"; };
    virtual std::string jsonData(void);

    virtual ddcObjectList Children() const;
    virtual void DisownChildren();
    //@}

    //------------------------------------------------------------
    //!\name CQFPrune local methods
    //@{
    //! apply pruning filter to \a PeriodHitsIndex, assigning hit sort-key strings as we go
    //! \li also assigns period-local key-ids (for use with navigation hints via ConcSession::SortKeyLB() etc)
    void PruneHitsIndex(const CQuery *qRoot, std::vector<size_t>& PeriodHitsIndex);
    //@}
};

#endif /* DDC_QFILTER_H */
