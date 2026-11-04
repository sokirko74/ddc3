#ifndef DDC_QUERY_RESULT_H
#define DDC_QUERY_RESULT_H

#include "ConcCommon.h"

//==============================================================================
// Typedefs

// type for count-query maps
typedef std::map<std::string,size_t> CCountMap;

//==============================================================================
// Class Definitions

//----------------------------------------------------------------------
/* CQueryResult: query results, possibly aggregated by "break"
 *
 *  
 *    Class CQueryResult contains all information about the first m_pConcordance->m_MaxCachedHitsCount hits for
 *    the input query. Other hits (beyond  m_pConcordance->m_MaxCachedHitsCount) are not stored but they can be
 *    retrieved on user's demand. 
 */
struct CQueryResult 
{
    // found hits (not more than m_pConcordance->m_MaxCachedHitsCount).
    std::vector<CHit>            m_Hits;

    // words that should be highlighted in hits; m_HighlightOccurs is the concatenation of CQueryNode::m_Occurrences for all period_def "subcorpora"
    std::vector<CTokenNo>        m_HighlightOccurs;

    // highlighting match-ids for m_HighlightOccurs
    std::vector<BYTE>            m_HighlightIds;

    // the number of all found hits (if m_AllHitsCount < m_pConcordance->m_MaxCachedHitsCount, then m_Hits.size() == m_AllHitsCount)
    size_t                  m_AllHitsCount;

    // the number of documents, where at least one hit is found
    size_t                  m_RelevantDocumentCount;

    // whether to sort by string-value
    bool                    m_bSortByString : 1;

    // whether primary sort is a prune-sort
    bool		    m_bPrune : 1;

    // hit sort order
    HitSortOrderEnum        m_SortOrder : 4;

    // ?
    mutable std::vector<BYTE>    m_DebugInfo;

    // clears CQueryResult fields
    void ClearQueryResults();

    // sort all hits by generic index-comparison function (comparison predicate reference)
    // see CQueryResultIndex<HitIndexLessThanT>::SortByIndex()
    // see CQueryResultIndex<HitIndexLessThanT>::Apply()
    template <typename HitIndexLessThanT>
    inline void SortResultsByIndex(HitIndexLessThanT& HitIndexLess);

    // sort hits by generic hit-comparison function (comparison predicate reference)
    // see CQueryResultIndex<HitIndexLessThanT>::SortByHit()
    // see CQueryResultIndex<HitIndexLessThanT>::Apply()
    template <typename HitLessThanT>
    inline void SortResultsByHit(HitLessThanT& HitLess);

    // sort all hits by generic index-comparison function (comparison predicate value)
    // see CQueryResultIndex<HitIndexLessThanT>::SortByIndex()
    // see CQueryResultIndex<HitIndexLessThanT>::Apply()
    template <typename HitIndexLessThanT>
    inline void SortResultsByIndexP(HitIndexLessThanT HitIndexLess)
    { SortResultsByIndex(HitIndexLess); };

    // sort hits by generic hit-comparison function (comparsion predicate value)
    // see CQueryResultIndex<HitIndexLessThanT>::SortByHit()
    // see CQueryResultIndex<HitIndexLessThanT>::Apply()
    template <typename HitLessThanT>
    inline void SortResultsByHitP(HitLessThanT HitLess)
    { SortResultsByHit(HitLess); };
};

//----------------------------------------------------------------------
/*
 * template for converting hit-comparison functions to index-comparisons for CQueryResult sorting
 */
template <typename HitLessThanT> struct CResultHitLess
{
    // result hit-set with respect to which comparisons will be executed
    const CQueryResult& m_Result;

    // hit comparison operator
    HitLessThanT&       m_HitLess;

    // default constructor
    CResultHitLess(const CQueryResult& Result, HitLessThanT& HitLess)
        : m_Result(Result), m_HitLess(HitLess)
    {};

    // indirection operator: defer hit-index comparisons to hit-comparisons
    inline bool operator() (size_t i1, size_t i2) const
    { return m_HitLess(m_Result.m_Hits[i1], m_Result.m_Hits[i2]); }
};


//----------------------------------------------------------------------
/*
 * temporary type for (re-)sorting CQueryResult hits
 */
struct CQueryResultIndex
{
    // result-set containing hits to be indexed/sorted
    const CQueryResult& m_Result;

    // hit index: elements are indices into m_Result.m_Hits, sorted in "logical" order
    std::vector<size_t>*     m_pHitIndex;

    // whether m_pHitIndex was created locally (if true, it will be destroyed with this object)
    bool                m_bLocalIndex;

    // Default constructor creates new trivial hit index
    CQueryResultIndex(const CQueryResult& Result)
        : m_Result(Result), m_pHitIndex(NULL), m_bLocalIndex(false)
    { Reset(); }

    // Constructor for an existing hit index pHitIndex (pointer version)
    // - caller is responsible for destroying pHitIndex when it is no longer needed
    CQueryResultIndex(const CQueryResult& Result, std::vector<size_t>* HitIndex)
        : m_Result(Result), m_pHitIndex(HitIndex), m_bLocalIndex(false)
    {};

    // Constructor for an existing hit index HitIndex (reference version)
    // - caller is responsible for destroying HitIndex when it is no longer needed
    CQueryResultIndex(const CQueryResult& Result, std::vector<size_t>& HitIndex)
        : m_Result(Result), m_pHitIndex(&HitIndex), m_bLocalIndex(false)
    {};

    // Destructor
    ~CQueryResultIndex(void)
    { if (m_bLocalIndex) delete m_pHitIndex; };

    // Resets the hit-index to the trivial sequence sort-order
    void Reset(void);

    // Wrapper for m_pHitIndex->size()
    inline size_t size(void) const
    { return m_pHitIndex==NULL ? 0 : m_pHitIndex->size(); };

    // sort hit-index by generic index-comparison function
    //  - HitIndexLessThanT must support an <code>operator() (size_t& a, size_t& b)</code>
    //       returning true iff <code>m_Result.m_Hits[a] < m_Result.m_Hits[b]</code>
    template <typename HitIndexLessThanT>
    inline void SortByIndex(HitIndexLessThanT& HitIndexLess)
    { std::stable_sort(m_pHitIndex->begin(), m_pHitIndex->end(), HitIndexLess); };

    // sort hits by generic hit-comparison function
    //  - HitLessThanT must support an <code>operator() (CHit& a, CHit& b)</code>
    //      returning true iff <code>a < b</code>
    template <typename HitLessThanT>
    inline void SortByHit(HitLessThanT& HitLess)
    {
        CResultHitLess<HitLessThanT> ResultLess(m_Result, HitLess);
        SortByIndex(ResultLess);
    };

    // copy selected source hits in index-order from m_pResult to Dst
    // - clobbers current contents of Dst
    // - only hits in index-range begin (inclusive) to end (exclusive) are copied
    // - End defaults to m_HitIndex.size()
    void Apply(CQueryResult &Dst, size_t Begin=0, size_t End=(size_t)-1);
};

//==============================================================================
// Template instantiations

//----------------------------------------------------------------------
// CQueryResult

//-- hit-sorting: result: by index: guts
template <typename HitIndexLessThanT>
inline void CQueryResult::SortResultsByIndex(HitIndexLessThanT& HitIndexLess)
{
    CQueryResultIndex ResultIndex(*this);
    ResultIndex.SortByIndex(HitIndexLess);
    ResultIndex.Apply(*this);
};

//-- hit-sorting: result: by hit: guts
template <typename HitLessThanT>
inline void CQueryResult::SortResultsByHit(HitLessThanT& HitLess)
{
    CQueryResultIndex ResultIndex(*this);
    ResultIndex.SortByHit(HitLess);
    ResultIndex.Apply(*this);
};



#endif /* DDC_QUERY_RESULT_H */
