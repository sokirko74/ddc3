#ifndef DDC_CONC_SESSION_H
#define DDC_CONC_SESSION_H

#include "ConcIndexatorInvoker.h"
#include "QueryResult.h"
#include "NavHint.h"
#include "../CommonLib/ddcRandom.h"

//==============================================================================
// Typedefs & Forward Declarations

//! save trigger for ConcordPattern application
typedef bool (*SaveTriggerType) (const std::string&,uint32_t LParam);

class  CConcSessionContext; //-- forward decl
class  CQueryCompiler;      //-- forward decl
class  CQuery;              //-- forward decl

//==============================================================================
// Classes & Structs 

//----------------------------------------------------------------------
/**
 * \brief class for a single (thread-local) DDC query session; formerly CConcHolder
 * \detail
 *   An instance of CConcSession is created for each thread querying a corpus.
 *   It contains  all user options for query processing
 *   such as m_ResultLimit (maximal number of hits to output)
 *   or m_QueryResultStr (the string representation of the query result).
 *
 *   As of v2.1.0, data to be shared between multiple threads (e.g. cache) lives in
 *   CConcSessionContext, which see for details.
 */
class CConcSession : public ConcIndexatorInvoker, public CQueryResult
{
public:
    //------------------------------------------------------
    //! \name Low-level data (formerly private)
    //@{
    //! shared session data (cache, etc.)
    CConcSessionContext*            m_pSessionContext;

    //! are we acting as a session master?  if false, m_pSessionContext will be freed on object destruction; default=true
    bool                            m_bSessionMaster;

    //! local worker-thread ID (default=0)
    size_t                          m_WorkerId;

    //! current query compiler, for compilation & evaluation of input queries.
    CQueryCompiler*                 m_pQueryCompiler;

    //! pseudo-random number generator
    DDCRandom *m_pRandom;

    //! how much time a query can be processed, by default unlimited (-1) 
    time_t                          m_QueryEndTime;

    //! a pointer to the current hits collection
    const ddcBreakVector*   m_pBreaks;

    //! the format of query result 
    DDCFormatTypeEnum               m_ResultFormat;
    //@}

public:
    //------------------------------------------------------
    //! \name High-level data

    //! initial random-state components for m_pRandom
    unsigned int m_RandomSeed;

    //! a cache for short occurrence lists which is used during iterating through \ref period_def "corpus periods"  and evaluating of the same query
    mutable CShortOccurCacheMap             m_ShortOccurCaches;

    //! the result of the query (its format depends  upon m_ResultFormat)
    std::string                                  m_QueryResultStr;

    //! most recent error message (if applicable)
    std::string                                  m_ErrorStr;

    /*! \brief
     * m_pConcordance is the main (and the only) pointer to corpus indices and break collections.
     * During the querying this pointer is used as a constant.
     * Class CConcSession's original name "CConcHolder" was chosen because the class "holds" this pointer.
     */
    CConcordance*                           m_pConcordance;

    //! actual logical offset (starting from zero) of the first returnable hit in m_Hits[] (~ StartHitNo)
    //! \li maintained by DDC (requested StartHitNo is passed in as EndHitNo rsp. StartHitNo rsp. Start)
    //! \li this is actually the number of computed hits which have been trimmed off the front of m_Hits[]
    //! \li alternate formulation: m_ResultOffset is the logical offset (original index) of m_Hits[0]
    size_t                                  m_ResultOffset;

    //! the maximal number of hits to be returned by the current query operation
    //! \li assumed to be set explicitly by user
    size_t                                  m_ResultLimit;

    //! minimum final sort-key of hits to be retrieved by GetAllHits()
    //! \li applied independently for each corpus period to save memory
    //! \li assumed to be set explicitly by user
    std::string                                  m_ResultMinKey;

    //! full request path leading to this session (used by CDDCLeafServer)
    std::string                                  m_RequestPath;

    //! The index of the current \ref period_def "subcorpora", which is now  being processed
    size_t                                  m_CurrentSearchPeriodNo;

    //! a delimiter which should be used between hits in m_QueryResultStr in the distributed model
    std::string                                  m_AdditionalHitDelimiter;

    //@}

        
    //------------------------------------------------------
    //! \name Low-level API (formerly private)

    //! add a reference to FileNo according to m_ResultFormat
    void    AddFileReference(const long FileNo);
    //! add bibliographical information about Hit to m_QueryResultStr
    void    ShowBibliographyForTextOrHtml(const CHit& Hit, uint32_t PageNumber);
    //! add bibliographical information about Hit to m_QueryResultStr under TableFormat
    bool    ShowBibliographyForTable(uint32_t PageNumber, const CHit& Hit, const std::vector<COutputToken>& Tokens);
    //! add hit string built by  Hit to to m_QueryResultStr
    bool    GenerateOneHitString(uint32_t PageNumber, const CHit& Hit, const std::vector<COutputToken>& Tokens);
    //! json: add hit string built by  Hit to to m_QueryResultStr
    bool    GenerateOneHitStringJson(uint32_t PageNumber, const CHit& Hit, const std::vector<COutputToken>& Tokens);
    //! add hit strings [StartBreakNo,  EndBreakNo) without highlighting to m_QueryResultStr
    bool    GetContext(int  StartBreakNo, int  EndBreakNo, const uint32_t CurrFileNo, const bool bConvertASCIIToHtmlSymbols, std::string& Result) const;
    //! append json hit strings [StartBreakNo,  EndBreakNo) without highlighting to js
    bool    GetContextJson(int  StartBreakNo, int  EndBreakNo, const uint32_t CurrFileNo, std::string& js) const;

    //! evaluate query on the corpus and initialize slots from CQueryResult
    //! \li backwards-compatible version assuming Query was already have been parsed
    DDCErrorEnum GetAllHits(const std::string &Query, size_t Start, size_t Limit);

    //! evaluate query on the corpus and initialize slots from CQueryResult, given a pre-parsed query
    //! \li CQuery* version added in ddc-2.0.23
    //! \li Start parameter added in ddc-2.1.9
    //! \li may populate m_ErrorStr
    //! \li may modify m_ResultOffset
    DDCErrorEnum    GetAllHits(CQuery *QueryRoot, size_t Start, size_t Limit);

    //! check if CountQuery is a count(*) query suitable for use with GetUniversalCounts()
    bool IsUniversalCountQuery(CQuery *QueryRoot) const;

    //! checks if Query  si already in the cache, and if true, it returns its hit results from the cache
    bool    TryToGetFromCache(const std::string &Query,  uint32_t& EndHitNo);

    //! stores Query  to the cache
    void    SaveToCache(const std::string& Query,  std::vector<size_t>::const_iterator start, std::vector<size_t>::const_iterator end);

    //! sets hit type, initializing m_pBreaks
    void    SetHitType();

    //! creates snippets, concatenating contexts of  found words
    bool    GetFileSnippets(const int HitNo, std::vector<COutputToken>& Tokens)  const;
    //! saves current found hits using SaveTrigger, this function is only called from GetOccurrences
    bool    SaveOccurrences(const std::vector<uint32_t>& ChunkLengths,  int ContextSize, const std::vector<CTokenNo>& Occurrences,  const std::vector<CHit>& Hits, SaveTriggerType SaveTrigger,uint32_t LParam); 
    //! initializes Tokens with words of hit BreakNo
    bool    GetTokensFromStorageByBreak(size_t IndexNo, size_t BreakNo, std::vector<COutputToken>& Tokens) const;
    //! initializes CHit::m_FileNo for each hit of Hits
    void InitFileReferences(std::vector<CHit>&   Hits) const;

    //! initializes CHit::m_SortKey for each in m_pQueryCompiler->m_pQueryTree->m_Hits.
    //! Also sets m_bSortDescending=Filter.isDescending(), m_bSortByString, m_bPrune appropriately
    void    InitSortKeyForHits(const CQuery *pQuery, const CDDCFilterWithBounds& Filter, std::vector<size_t>& PeriodHitsIndex);
    void    InitSortByRank(const CQuery *pQuery) const;
    void    InitSortBySize(const CQuery *pQuery) const;
    void    InitSortByRandom(const CQuery *pQuery) const;
    void    InitSortByContext(const CQuery *pQuery, const CDDCFilterWithBounds& Filter) const;

    //! initialize a CHitSortKey integer lower-bound for its string key with respect to \a Filter
    //! \li basically the inverse of InitSortKeyForHits()
    //! \li used for m_ResultMinKey-based pruning
    //! \param Key (input/output)
    //!   \li on input, Key.s is a key-string as reported by GetHitIds()
    //!   \li on return on return, Key.i is a lower bound for \a Key.s with respect to \a Filter
    //! \param Filter (input) filter with respect to which key is to be initialized
    void SortKeyLB(CHitSortKey &key, const CDDCFilterWithBounds& Filter);
    //@}

public:
    //------------------------------------------------------
    //! \name Constructors etc.
    //@{

    /** Default constructor
     *  \param SessionContext shared context for this session;
     *         if unspecified or NULL, a new local CConcSessionContext will be created and freed when the
     *         CConcSession object itself is destroyed; otherwise, user is responsible for freeing
     *         SessionContext.
     */
    CConcSession(CConcSessionContext *SessionContext=NULL);

    /** Default destructor */
    ~CConcSession();
    //@}

    //------------------------------------------------------
    //! \name Worker-thread and ConcSessionContext utilities
    //@{

    /** create a minimal copy of this object for use by a worker thread */
    CConcSession* WorkerClone(size_t WorkerId);

    /** perform local cleanup of a worker clone prior to deletion */
    void WorkerCloneFree();

    /** lock session context */
    int LockSessionContext();

    /** unlock session context */
    int UnlockSessionContext();

    /** clears the shared query cache */
    void ClearQueryCache();

    /** return shared query cache size */
    size_t CacheSize(void) const;
    //@}

    //------------------------------------------------------
    //! \name High-level API (public)
    //@{
        
    //! GetBreaks returns  the vector of current \ref break_def "breaks" (by m_pBreaks). 
    const ddcBreakVector& GetBreaks() const;

    //! return the current format of hit
    DDCFormatTypeEnum       GetResultFormat() const { return m_ResultFormat; };

    //! return string representation of m_ResultFormat
    std::string                  GetResultFormatStr() const;

    //! set the current format of hit
    void                    SetResultFormat(std::string ResultTypeStr);

    /*! \brief Finds all occurrences of \b Query(only occurrences , not hits!), if \b Query is an atomic query (CQueryNode::m_bAtomic),  
      For each found  occurrence it calls SaveTrigger, which normally should save all occurrences to a file.
      This function is called in application ConcordPattern.
    */
    DDCErrorEnum            GetOccurrences(const std::string &Query, int ContextSize, SaveTriggerType SaveTrigger,uint32_t LParam);
                

    //! SimpleQuery finds hits by the given query. EndHitNo is used as an input/output parameter.
    /*! 
      Let H0...Hn be all hits which match the Query. Then EndHitNo must be 0<= EndHitNo<=n. 
      Let S be min (n, EndHitNo+m_ResultLimit-1).
      The function saves  hits  [EndHitNo, EndHitNo+1,... EndHitNo+s] to result strings.
      After this it makes EndHitNo equal to s+1.
      The function returns errNone, if there is no parse error in the  given query.

      (moo) put simply:
      - as an INPUT parameter, EndHitNo is the offset of the FIRST hit to return
      - as an OUTPUT parameter, EndHitNo is the offset of the offset of the first hit NOT returned (= upper bound; last hit returned + 1)
    */
    DDCErrorEnum    SimpleQuery(const std::string &Query, uint32_t& EndHitNo, uint32_t& HitsCount);

    //! GetHits does the same as SimpleQuery does, but without GenerateHitStrings()
    //! \li see SimpleQuery() for semantics of EndHitNo
    DDCErrorEnum    GetHits(const std::string &QueryStr, uint32_t& EndHitNo);

    //! GetHits() variant for pre-parsed queries, cache key is generated as QueryRoot->toString() + QueryRoot->optionsToString()
    //! \li see SimpleQuery() for semantics of EndHitNo
    DDCErrorEnum    GetHits(CQuery *QueryRoot,  uint32_t& EndHitNo);

    //! GetHits() guts: pre-parsed QueryRoot and given string cache-key QueryStr
    //! \li see SimpleQuery() for semantics of EndHitNo
    //! \li may set m_ResultOffset and trim m_Hits[] accordingly (ddc >= v2.1.9)
    DDCErrorEnum    GetHits(CQuery *QueryRoot,  uint32_t& EndHitNo, const std::string &QueryStr);

    //! initializes m_QueryResultStr using current m_Hits and m_HighlightOccurs (for context-queries)
    //! \li respects m_ResultOffset (generates strings for m_Hits[StartHitNo-m_ResultOffset .. StartHitNo-m_ResultOffset+m_ResultLimit-1])
    //! \param StartHitNo logical offset of 1st hit
    DDCErrorEnum    GenerateHitStrings(const int StartHitNo, bool UseAdditionalHitDelimiter=true);

    //! initializes m_QueryResultStr using current m_Hits (for count-queries)
    //! \li respects m_ResultOffset (generates strings for m_Hits[StartHitNo-m_ResultOffset .. StartHitNo-m_ResultOffset+m_ResultLimit-1])
    //! \param StartHitNo logical offset of 1st count-hit
    DDCErrorEnum    GenerateCountStrings(const int StartHitNo, bool UseAdditionalHitDelimiter=true);

    //! get offset-hint appropriate for next page (after GenerateHitStrings()); used by CDDCLeafServer
    size_t GetOffsetHint(const size_t StartHitNo) const;

    //! get sortkey-hint appropriate for next page (after GenerateHitStrings()); used by CDDCLeafServer
    std::string GetSortKeyHint(const size_t StartHitNo) const;

    //! stores sort-keys (CHit::m_SortKey) of current m_Hits to a string
    //! \li adds m_ResultOffset to reported (logical) hit offsets
    std::string GetHitIds()  const;

    //! GetHidIds() variant for count-queries; returns count-IDs of all hits in m_Hits[]
    //! \li m_ResultOffset is not relevant here, since hit offsets are not reported
    std::string GetCountIds()  const;

    //! get logical hit sort order; replaces HitsShouldBeSorted()
    HitSortOrderEnum HitSortOrder() const;

    //! sets timeout for query processing
    void SetTimeOut(int TimeOut);

    //! clears the current parsed query (if any)
    void ClearQuery();

    //! return the text area to be be searched
    int GetTextArea() const;

    //! clears CQueryResult fields, also m_ErrorStr and m_ResultOffset
    void ClearQueryResults();

    //! converts a string to a FormatTypeEnum
    static DDCFormatTypeEnum GetResultFormatByString(const std::string& ResultTypeStr );

    //! adds header and footer to QueryResultStr according to format ResultTypeStr
    static void DecorateQueryResults(const std::string& ResultTypeStr, std::string& QueryResultString);

    //! return true, if the input query contains #less_by_rank or #greater_by_rank
    //! moo: sick, bad, ugly, and wrong!
    bool HasRankOrderOperator() const;

    //! return true iff the input query contains a match-id operator (=ID)
    //! moo: sicker, badder, uglier, and wronger!
    bool HasMatchIdOperator() const;

    //! return the length of break prefix, where DDC should search (#within[sentence, 10])
    int GetBreakStarterLength() const;

    //! moo: build a json context string by parsing delimited token data
    std::string BuildJsonContextString (const std::vector<COutputToken>& Tokens, bool doHighlight=true) const;

    //! moo: return a canonical representation of the query string \c Query (implicitly parses)
    std::string CanonicalQueryString(const std::string &Query);

    //! moo: return a JSONr epresentation of the query string \c Query (implicitly parses)
    std::string JsonQueryString(const std::string &Query);

    //! moo: set internal random seed to m_RandomSeed+seed1
    void SetRandomSeed(unsigned int seed1=0) const;

    //! moo: get term-expansion dispatcher for this object (wrapper for &m_pConcordance.m_Txd)
    inline TxDispatcher* GetTxDispatcher() const
    { return &(m_pConcordance->m_Txd); };
    //@}
};



#endif
