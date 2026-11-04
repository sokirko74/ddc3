#ifndef DDC_QCOUNT_H
#define DDC_QCOUNT_H

#include "../ConcordLib/Query.h"

//======================================================================
//typedef vector<string>        CQCountByList;

/** default count()-query sample size */
const size_t DDCDefaultCountSampleSize = (size_t)-1;

// workaround for "error: overriding ‘virtual std::invalid_argument::~std::invalid_argument() throw ()’" under g++-5.4.0 / ubuntu 16.04.6
#ifndef _GLIBCXX_USE_NOEXCEPT
# define _GLIBCXX_USE_NOEXCEPT
#endif

/*! exception type used for aligning count-keys */
class CQCountKeyBadOccurrence : public std::invalid_argument
{
public:
    CQCountKeyBadOccurrence(const std::string& what_arg)
        : std::invalid_argument(what_arg)
    {};
    virtual ~CQCountKeyBadOccurrence() _GLIBCXX_USE_NOEXCEPT {};
};

//==============================================================================
// Hit sizes

//==============================================================================
// CQCountKeyExpr and subclasses

//----------------------------------------------------------------------
/*! runtime count-key expression base class */
class CQCountKeyExpr : public CQuery
{
public:
    /** default constructor */
    CQCountKeyExpr(const std::string& label="")
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
    virtual std::string& Evaluate(const CHit &Hit);

    /** stringification (default returns m_Label) */
    virtual std::string toString() { return m_Label; };

    /** json stringification: class */
    std::string jsonClass() { return "CQCountKeyExpr"; };

    /** json stringification: data */
    std::string jsonData() { return "\"label\":" + jsonStr(m_Label); };
};

//----------------------------------------------------------------------
/*! count-key expression: constant */
class CQCountKeyExprConstant : public CQCountKeyExpr {
public:
    CQCountKeyExprConstant(const std::string &label="*") : CQCountKeyExpr(label) {};
    virtual ~CQCountKeyExprConstant() {};
    virtual std::string& Evaluate(const CHit &Hit) { return m_Label; };
    virtual std::string jsonClass() { return "CQCountKeyExprConstant"; };
    virtual std::string toString() { return std::string("@'") + escapeChars(m_Label,"\\'") + "'"; };
};

//----------------------------------------------------------------------
/*! count-key expression: metadata-attribute */
class CQCountKeyExprMeta : public CQCountKeyExpr {
public:
    //! last file-number evaluated
    uint32_t  m_CurFile;

    //! last key generated
    std::string m_CurKey;

public:
    CQCountKeyExprMeta(const std::string &label="*") : CQCountKeyExpr(label), m_CurFile(-1), m_CurKey("") {};
    virtual ~CQCountKeyExprMeta() {};
};

//----------------------------------------------------------------------
/*! count-key expression: fileid (aka docid) */
class CQCountKeyExprFileId : public CQCountKeyExprMeta {
private:
    char buf[16];
public:
    CQCountKeyExprFileId(const std::string &label="fileid") : CQCountKeyExprMeta(label) {};
    virtual ~CQCountKeyExprFileId() {};
    virtual std::string& Evaluate(const CHit &Hit);
    virtual std::string jsonClass() { return "CQCountKeyExprFileId"; };
};

//----------------------------------------------------------------------
/*! count-key expression: indexed */
class CQCountKeyExprIndexed : public CQCountKeyExprMeta {
public:
    class CConcordance* m_pConcordance;
public:
    CQCountKeyExprIndexed(const std::string &label="file") : CQCountKeyExprMeta(label) {};
    virtual ~CQCountKeyExprIndexed() {};
    virtual bool Compile(CQueryCompiler *compiler);
    virtual std::string jsonClass() { return "CQCountKeyExprIndexed"; };
};

//----------------------------------------------------------------------
/*! count-key expression: filename */
class CQCountKeyExprFileName : public CQCountKeyExprIndexed {
public:
    CQCountKeyExprFileName(const std::string &label="filename") : CQCountKeyExprIndexed(label) {};
    virtual ~CQCountKeyExprFileName() {};
    virtual std::string& Evaluate(const CHit &Hit);
    virtual std::string jsonClass() { return "CQCountKeyExprFileName"; };
};

//----------------------------------------------------------------------
/*! count-key expression: date: full */
class CQCountKeyExprDate : public CQCountKeyExprIndexed
{
public:
    const ddcDateVector *m_pDates;
      signed int         m_year;
    unsigned int         m_month;
    unsigned int         m_day;
    char                 buf[16];

public:
    CQCountKeyExprDate(const std::string &label="date") : CQCountKeyExprIndexed(label), m_pDates(NULL) {};
    virtual ~CQCountKeyExprDate() {};
    virtual bool Compile(CQueryCompiler *compiler);
    virtual std::string& Evaluate(const CHit &Hit);
    virtual std::string jsonClass() { return "CQCountKeyExprDate"; };
};

//----------------------------------------------------------------------
/*! count-key expr: date: slice (by year) */
class CQCountKeyExprDateSlice : public CQCountKeyExprDate
{
public:
    unsigned int m_slice;
public:
    CQCountKeyExprDateSlice(const std::string &label="date", int slice=1) : CQCountKeyExprDate(label), m_slice(slice) {};
    virtual ~CQCountKeyExprDateSlice() {};
    virtual bool Compile(CQueryCompiler *compiler);
    virtual std::string& Evaluate(const CHit &Hit);
    virtual std::string toString() { return m_Label + Format("/%d",m_slice); };
    virtual std::string jsonClass() { return "CQCountKeyExprDateSlice"; };
    virtual std::string jsonData() { return CQCountKeyExprDate::jsonData() + Format(",\"slice\":%d",m_slice); };
};

//----------------------------------------------------------------------
/*! count-key expr: bibl string */
class CQCountKeyExprBibl : public CQCountKeyExprIndexed
{
public:
    const CFreeBiblIndexInterface *m_Bibl;
public:
    CQCountKeyExprBibl(const std::string &attrName="") : CQCountKeyExprIndexed(attrName) {};
    virtual ~CQCountKeyExprBibl() {};
    virtual bool Compile(CQueryCompiler *compiler);
    virtual std::string& Evaluate(const CHit &Hit);
    virtual std::string jsonClass() { return "CQCountKeyExprBibl"; };
    virtual std::string toString() { return std::string("'") + escapeChars(m_Label,"\\'") + "'"; };
};

//----------------------------------------------------------------------
/*! count-key expr: regular expression replacement */
class CQCountKeyExprRegex : public CQCountKeyExprIndexed
{
public:
    CQCountKeyExpr *m_Src;
    std::string      m_Pattern;
    std::string      m_Replacement;
    std::string      m_Modifiers;
    bool        isGlobal;
    RML_RE     *m_Regex;

public:
    CQCountKeyExprRegex(CQCountKeyExpr *src, const std::string& pattern, const std::string &replacement, const std::string& modifiers=std::string(""))
        : CQCountKeyExprIndexed("regex"), m_Src(src), m_Pattern(pattern), m_Replacement(replacement), m_Modifiers(modifiers), isGlobal(false), m_Regex(NULL) {};
    virtual ~CQCountKeyExprRegex();
    virtual void DisownChildren();
    virtual bool CanCountByFile() const { return m_Src->CanCountByFile(); };
    virtual bool Compile(CQueryCompiler *compiler);
    virtual std::string& Evaluate(const CHit &Hit);
    inline void EvaluateRegex(const CHit &Hit, const std::string& srcKey)
    {
        m_CurKey = srcKey;
        if (isGlobal)
            m_Regex->GlobalReplace(m_Replacement, &m_CurKey);
        else
            m_Regex->Replace(m_Replacement, &m_CurKey);
        m_CurFile = Hit.m_FileNo;
    };
  
    //-- ddcObject API
    virtual ddcObjectList Children() const;
    virtual std::string toString();
    virtual std::string jsonClass() { return "CQCountKeyExprRegex"; };
    virtual std::string jsonData();
};

//----------------------------------------------------------------------
/*! count-key expression: context (token) attribute */
class CQCountKeyExprToken : public CQCountKeyExprIndexed
{
public:
    //! name of token index attribute
    std::string m_IndexName;

    //! match-id of anchor token (0 for any)
    BYTE   m_MatchId;

    //! offset of reference token
    int    m_Offset;

    //! underlying index-set (post-compile())
    CStringIndexSet *m_pIndex;

public:
    CQCountKeyExprToken(const std::string &IndexName="Token", BYTE MatchId=0, int Offset=0)
        : CQCountKeyExprIndexed("token"), m_IndexName(IndexName), m_MatchId(MatchId), m_Offset(Offset), m_pIndex(NULL)
    {};
    virtual ~CQCountKeyExprToken() {};
    virtual BYTE GetMatchId() const { return m_MatchId; };
    virtual BYTE SetMatchId(BYTE matchId) { return m_MatchId = matchId; };
    virtual bool CanCountByFile() const { return false; };
    virtual bool Compile(CQueryCompiler *compiler);
    virtual std::string& Evaluate(const CHit &Hit);
    virtual std::string toString();
    virtual std::string jsonClass() { return "CQCountKeyExprToken"; };
    virtual std::string jsonData();
};

//----------------------------------------------------------------------
// count-key expr: list
class CQCountKeyExprList : public CQCountKeyExpr
{
public:
    /** underlying expression list */
    std::vector<CQCountKeyExpr*> m_Exprs;

    /** temporary key */
    std::string m_Key;

public:
    CQCountKeyExprList() : m_Key("") {};

    CQCountKeyExprList(const CQCountKeyExprList &src)
        : m_Exprs(src.m_Exprs), m_Key(src.m_Key)
    {};

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

    virtual BYTE GetMatchId() const;

    virtual bool Compile(CQueryCompiler *compiler);
    virtual std::string& Evaluate(const CHit &Hit);

    //-- ddcObject API
    virtual ddcObjectList Children() const;
    virtual void DisownChildren();
    virtual std::string toString();
    virtual std::string jsonClass() { return "CQCountKeyExprList"; };
    virtual std::string jsonData();

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

    //! maximum sort-key to return (empty for none)
    std::string m_lo;

    //! minimum sort-key to return (empty for none)
    std::string m_hi;

    //! list of count-bin metadata key expressions
    CQCountKeyExprList* m_keys;

    //! temporary for constructing count-query results
    CCountMap m_Counts;

    //! temporary for tracking count-query sample size
    size_t m_CountSample;

public:
    //! bison constructor
    CQCount(CQuery *dtr_=NULL, CQCountKeyExprList* keys_=NULL, size_t sample_=DDCDefaultCountSampleSize, HitSortEnum sort_=NoSort, std::string lb="", std::string ub="")
        : CQuery("count"),
          m_dtr(dtr_),
          m_sample(sample_),
          m_sort(sort_),
          m_keys(keys_),
          m_lo(lb),
          m_hi(ub),
          m_CountSample(0)
    {
        if (sample_==0) m_sample = DDCDefaultCountSampleSize;
    };

    //! Default destructor.
    virtual ~CQCount(void);

public:
    //! get local match-id: keys > dtr
    virtual BYTE GetMatchId() const;

    //! Compile index-dependent query properties
    bool CompileLocal(CQueryCompiler *compiler, bool compileDtr=true, bool compileKeys=true);

    //! Run optional unsatisfiability checks for query before Compile() is called.
    virtual bool CheckSatisfiable(CQueryCompiler *compiler);

    //! Compile index-dependent query properties
    virtual bool Compile(CQueryCompiler *compiler);

    //! evaluate query: top-level (sanity checks only)
    virtual void Evaluate();

    //! evaluation utility: returns true iff this is a count(*)-query; guts for CConcHolder::IsUniversalCountQuery()
    virtual bool CanCountUniversal();

    //! evaluation utility: returns true iff this query can count at file-level; wraps m_keys.canCountByFile()
    virtual bool CanCountByFile() const;
    
    //! evaluation guts: populate m_Counts with universal counts; formerly CConcHolder::GetUniversalCounts()
    //! \li should be called only once per query
    //! \li stores encoded results in Result
    //! \li implicitly calls ConvertCountsToHits()
    virtual void CountUniversal(CQueryResult &Result, size_t Limit);

    //! evaluation guts: extend m_Counts[] with counts for current search period; formerly CConcHolder::GetPeriodCounts()
    //! \li should be called once per subcorpus search period
    //! \li may (re-)sort Result.m_Hits 
    //! \li also clears local query-data in Result (expected to correspond to m_dtr query for current period)
    //! \li ConvertCountsToHits() still needs to be called after all search-periods have been counted
    virtual void CountLocal(CQueryResult &Result, size_t Limit);

    //! encode count()-query results from m_Counts[] to m_Compiler->m_pHolder->m_Hits[], using
    //! m_Hits[] element CHit hit.m_SortKey.s to transport count-key
    //! and hit.m_Value.m_Count to transport count results in a backwards-compatible manner.
    //! \li formerly CConcHolder::ConvertCountsToHits()
    virtual void ConvertCountsToHits(CQueryResult &Result, size_t Limit);

    //! \b DEBUG: return a canonical string form for this query
    virtual std::string toString();
    //virtual string optionsToString() { return ""; };
    virtual std::string countOptionsToString();

    virtual std::string jsonClass() { return "CQCount"; };
    virtual std::string jsonData();
    //virtual string optionsToJson() { return "null"; };

    //! wrapper for m_dtr->ClearNode()
    virtual void ClearNode();

    //! clear query contents.  if \c deep is true, propagates operation to daughters
    virtual void Clear(bool deep=true);

    //-- ddcObject API
    virtual ddcObjectList Children() const;
    virtual void DisownChildren();
};


//======================================================================
/*!
  \brief utility struct for iterating over hit occurrences
*/

//======================================================================
/*!
  \brief
  keys-query
*/
class CQKeys : public CQuery {
public:
    //! typedef for target value-tuples
    typedef std::set< std::vector<std::string> > StringTupleSet;
  
public:
    //! underlying count() query supplying keys
    CQCount *m_qCount;

    //! limit for m_qCount subquery
    size_t m_CountLimit;

    //! target index-tuple
    std::vector<std::string> m_IndexNames;

    //! match-id of anchor token (0 for any)
    BYTE   m_MatchId;

    //! pseudo-private: temporary sub-queries for each CQCountKeyExprToken key-expression in m_qCount->m_keys->m_Exprs
    std::vector<CQTokSet*> m_dtrs;

    //! pseudo-private: proxy query for join of independent attributes (WITH)
    CQuery *m_proxy;

    // pseudo-private: all value tuples
    //StringTupleSet m_tuples;

public:
    //! bison constructor
    CQKeys(CQCount *qCount=NULL, size_t CountLimit=DDCDefaultCountSampleSize)
        : CQuery("keys"), m_qCount(qCount), m_CountLimit(CountLimit), m_MatchId(0), m_proxy(NULL)
    {};

    //! bison constructor
    CQKeys(CQCount *qCount, size_t CountLimit, const std::vector<std::string>& IndexNames)
        : CQuery("keys"), m_qCount(qCount), m_CountLimit(CountLimit), m_IndexNames(IndexNames), m_MatchId(0), m_proxy(NULL)
    {};

    //! Default destructor.
    virtual ~CQKeys(void);

public:
    //! Compile index-dependent query properties
    virtual bool Compile(CQueryCompiler *compiler);

    //! evaluate query: top-level (sanity checks only)
    virtual void Evaluate();

    //! get nontrivial match-id: local > qCount
    virtual BYTE GetMatchId() const;

    //! Set match-id, returns new value
    virtual BYTE SetMatchId(BYTE matchId)
    { return m_MatchId = matchId; };

    //! \b DEBUG: return a canonical string form for this query
    virtual std::string toString();

    virtual std::string jsonClass() { return "CQKeys"; };
    virtual std::string jsonData();

    //! clears all daugher nodes
    virtual void ClearNode();

    //! clear query contents.  if \c deep is true, propagates operation to daughters
    virtual void Clear(bool deep=true);

    //-- ddcObject API
    virtual ddcObjectList Children() const;
    virtual void DisownChildren();
};


//======================================================================
// functions

/** generate a single count string from a (key,count)-pair */
void GenerateCountString(std::string &ResultStr, DDCFormatTypeEnum fmt, const std::string& key, size_t count);

/** generate a single count string from a CHit */
inline void GenerateCountString(std::string &ResultStr, DDCFormatTypeEnum fmt, const CHit &hit)
{ GenerateCountString(ResultStr, fmt, hit.m_SortKey.s, hit.m_Value.m_Count); };


#endif /* DDC_QCOUNT_H */
