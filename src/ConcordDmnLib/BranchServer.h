#ifndef DDC_BRANCH_SERVER_H
#define DDC_BRANCH_SERVER_H

#include "ConcordDmnLib/Server.h"
#include "ConcordLib/QueryCompiler.h"

//======================================================================
/* single hit data in get_first_hits responses */
struct CHitToSort 
{
    BYTE        m_HostNo;       // subcorpus id
    size_t      m_HitNo;        // subcorpus-local hit-number for context queries OR hit count for count-queries
    std::string      m_SortKeyStr;   // hit sort-string

    CHitToSort(BYTE HostNo=0)
        : m_HostNo(HostNo)
    {};

    inline bool operator < (const CHitToSort& X) const {
        return m_SortKeyStr < X.m_SortKeyStr;
    };

    /* steal data from X */
    inline void steal(CHitToSort &X)
    {
        m_HostNo = X.m_HostNo;
        m_HitNo  = X.m_HitNo;
        m_SortKeyStr.swap(X.m_SortKeyStr);
    };

    /* string form of hit, for debugging messages */
    inline std::string debugStr(void) const
    {
        return Format("{HostNo=%d,HitNo=%zd,SortKey=%s}", m_HostNo, m_HitNo, jsonStr(m_SortKeyStr).c_str());
    };
};

//==============================================================================
/* direct comparison operator for sorting count-hits by m_HitNo (count) */
struct LessByHitNo {
    bool operator() (const CHitToSort &a, const CHitToSort &b) const
    { return a.m_HitNo < b.m_HitNo; };
};


//======================================================================
/* parsed get_first_hits response
 * 
 * - somewhat redundant with CRunQueryData
 * - can and should probably be merged with CRunQueryData
 */
struct CFirstHitsQueryResult  {
    size_t                      m_AllHitsCount;
    size_t                      m_AllRelevantDocsCount; 
    std::string                      m_HitsDistributionStr;
    std::string                      m_RelevantDocsDistributionStr;
    int                         m_InternalError;
    HitSortOrderEnum            m_SortOrder;            //< hit sort order; formerly bool m_bSort
    NetworkErrorsEnum           m_NetworkError;
    std::string                      m_ErrorStr;
    std::vector<CHitToSort>          m_Hits;
    std::vector<size_t>              m_DtrEnds;              //< EndHitNo components scanned from each immediate daughter subcorpus
    std::vector<std::shared_ptr<CHttpConnection> > m_Connections; //< keep-alive sessions with the selected daughters
    size_t                      m_Offset;               //< logical offset of m_Hits[0] (sum over number of front-trimmed hits for all subcorpora)
    
    /* destructor implicitly calls CloseConnections() */
    ~CFirstHitsQueryResult()
    {
        CloseConnections();
    };

    /* clear the object */
    void Clear();

    /* check whether this result raised any errors */
    inline bool HasErrors() const
    {
        return (m_NetworkError != neSuccess )  || (m_InternalError != errNone);
    };

    /* close any previously opened connections */
    void CloseConnections();

    /* collect counts by sort-key, only makes sense if m_SortOrder==hsoCounts ; also modifies m_AllHitsCount */
    void CollectCounts();

    /* prune hits by sort-key, only makes sense for #prune[]-sorts; also modifies m_AllHitsCount */
    void PruneHits(size_t PruneLimit);

    /* compute the number of hits we need to request to cover all physical hit-offsets (for a single host) in HostHits
     * - for prune-queries
     * - HostHitIds[] is a list of physical indices into m_Hits[]
     * - all hits in m_Hits[HostHitIds[]] should share the same m_HostNo
     * - hits m_Hits[HistHitIds[]] should be sorted by m_HitNo , but may contain gaps
     */
    size_t HostHitsLimit(const std::vector<size_t>& HostHitIds);

    /* convert a logical branch-level hit offset to a physical index in m_Hits[] (no boundary-checking, underflow possible) */
    inline size_t PhysicalOffset(size_t LogicalHitNo) const
    { return LogicalHitNo - m_Offset; };

    /* convert a physical offset in m_Hits[] to a logical branch-level hit offset (no boundary-checking, no underflow) */
    inline size_t LogicalOffset(size_t PhysicalHitNo) const
    { return PhysicalHitNo + m_Offset; };

    /* returns the logical upper bound hit offset for LogicalHitNo, with boundary-checking */
    inline size_t LogicalMax(size_t LogicalHitNo) const
    { return std::min(LogicalHitNo, LogicalOffset(m_Hits.size())); };

    /* returns the physical upper bound hit offset LogicalHitNo, with boundary-checking */
    inline size_t PhysicalMax(size_t LogicalHitNo) const
    { return PhysicalOffset(LogicalMax(LogicalHitNo)); };

    /* returns the number of items in m_Hits[] logical range [StartHitNo,StartHitNo+ResultLimit), with boundary-checking */
    inline size_t LogicalSize(size_t StartHitNo, size_t ResultLimit) const
    { return LogicalMax(StartHitNo+ResultLimit) - LogicalMax(StartHitNo); };

};

//======================================================================
/* CDDCBranchServer statistics [UNUSED?] */
struct CQueryStatistics 
{
    DwordVector m_HitsEnds;
    uint32_t       m_FreqCount;
};

//======================================================================

/* struct for mapping immediate subcorpus host-IDs to selected sub-subcorpora
 *  - replaces CRunQueryData::PossibleHosts
 *  - sub-path "*" indicates all daughter-corpora
 *  TODO: TODO allow sub-path "**" indicating all descendendant corpora for CSelectedHosts (BranchServer)
 */
struct CSelectedHosts
{
    typedef std::vector<uint32_t>            VecT;
    typedef std::map<uint32_t, std::set<std::string> > MapT;

    VecT m_vec;  // Host-IDs of selected daughter(s); empty for all daughters
    MapT m_map;  // sub-paths relative to each selected daugther, keyed by Host-ID

    CSelectedHosts()
    {};

    ~CSelectedHosts()
    {};

    inline size_t size() const
    { return m_vec.size(); };

    inline void resize(size_t sz)
    { m_vec.resize(sz); };

    void Clear();

    // select sub-path "HostId/SubPath" (empty SubPath is treated as "*")
    void Insert(uint32_t HostId, const std::string& SubPath);

    // alias for Insert(HostId,"*"): select all sub-paths for HostId
    inline void Insert(uint32_t HostId)
    { Insert(HostId,"*"); };

    // alias for Insert(0 <= HostId < nDtrs, SubPath)
    void InsertAll(uint32_t nDtrs, const std::string &SubPath);
    
    // returns a string suitable for use in query
    std::string DtrPaths(uint32_t HostId) const;

    // debug: convert to string
    std::string toString() const;
};


//======================================================================
/* DDC branch server 'run_query' paramter & intermediate result-type */
class CRunQueryData {
public:
    std::string sQuery;                      // query string
    std::string sResultFormat;               // result format (string)
    size_t StartHitNo;                  // first hit to return
    size_t ResultLimit;                 // max number of hits to return
    int TimeOut;                        // query timeout (seconds)
    int iInternalError;                 // internal error code
    int iNetworkError;                  // network error code
    size_t EndHitNo;                    // final hit number returned
    size_t HitsCount;                   // total number of hits
    size_t RelevantDocsCount;           // ?
    //DwordVector PossibleHosts;          ///< indices of selected immediate subcorpora
    CSelectedHosts SelectedHosts;       // maps immediate subcorpora to selected sub-subcorpora
    std::string HitDistrib;                  // ?
    std::string DocDistrib;                  // ?
    std::string HitsKey;                     // key for response body data (json only)
    std::string ResponseBody;                // response body data
    std::string *pErrorStr;                  // error string pointer (empty or NULL for success)
    std::string     ReqPath;                 // request path (>=v2.2.8)
    NavHintKey navKey;                  // navigation hint key
    NavHint    navHint;                 // user- or cache-supplied navigation hint
    CQueryCompiler *pQCompiler;		// query compiler for parsing input queries (parsed query is pQCompiler->m_pQuery)
   
public:
    /* constructor */
    CRunQueryData(const std::string & _Query="", const std::string& _ResultFormat="JSON", size_t _Start=0, size_t _Limit=10, int _TimeOut=10, std::string *_pErrorStr=NULL);

    /* destructor */
    virtual ~CRunQueryData();

    /* (re-)initialize with parameters */
    void Init(const std::string & _Query="", const std::string& _ResultFormat="JSON", size_t _Start=0, size_t _Limit=10, int _TimeOut=10, std::string *_pErrorStr=NULL, const std::string& _ReqPath="", const NavHint& _Hint=NavHint());

    /* clear object */
    void Clear();

    /* convenience method for accessing compiled query */
    inline CQuery* Query() const
    { return pQCompiler->m_pQuery; };

    /* convenience method for accessing compiled query */
    inline CQueryOptions* QueryOptions() const
    { return Query()->m_Options; };

    /* is this a prune-query? */
    inline bool IsPruneQuery() const
    { return QueryOptions()->IsPruneFilter(); };

    /* populate response string Response */
    void toString(std::string &Response, size_t WorkerId=0, const DDCVersionT& vCompat=DDCVersion);

};

//======================================================================
/* utility typedef for CDDCBranchServer::m_HostMap */
typedef std::map<std::string,size_t> CHostIdMap;

//======================================================================
/* DDC branch server node, formerly CDDCCorpusListenHost */
class CDDCBranchServer : public CDDCServer
{
public:

public:
    //--------------------------------------------------------------
    // local data
    std::map<std::string, CQueryStatistics>       m_QueryToStatis; //-- unused?
    std::vector<CHost>                       m_Hosts;
    CHostIdMap				m_HostMap;       // maps short daughter labels (without "server:" prefix) to m_Hosts[] offsets
    std::string                              m_QueryResultString;
    std::string                              m_ErrorStr;     //-- subcorpus error

    //-- low-level data
    CFirstHitsQueryResult               m_FHResult;   //< first-hits result
    CRunQueryData                       m_QueryData;  //< run-query data
    NavHintCache                        *m_pNavCache; //< navigation hint cache (shared over multiple worker threads)
    size_t                              m_NavCacheStep; //-- minimum offset increment for update of navigation hint cache

    bool m_bHitStringsParallel; // send get_hit_strings requests in parallel?

public:
    //--------------------------------------------------------------
    // Constructors etc.

    /* default constructor
     * master: true (default) iff this is to be a "master" object (i.e. not a worker clone)
     */
    CDDCBranchServer(bool master=true);

    /* default destructor */
    virtual ~CDDCBranchServer();

    /* close any open socket(s) this server administers, called on termination signal */
    virtual void Shutdown();

    /* set server options (override handles option m_NavCacheSize) */
    virtual void SetOptions(const CDDCServerOptions &Options);

public:
    //--------------------------------------------------------------
    // DDCServer API: client threads

    /* create a minimal copy of this object (and any subordinate data) for use by a worker thread
     *  - override creates a CDDCBranchServer as non-master
     */
    virtual CDDCServer *WorkerClone(void) const
    { return (CDDCServer*)new CDDCBranchServer(false); };

    /* initialize a newly created worker-clone (and any subordinate data) */
    virtual void WorkerCloneInit(const CDDCServer *Parent, size_t WorkerId);

    /* perform local cleanup of a worker clone prior to deletion */
    virtual void WorkerCloneFree(void);

public:
    //--------------------------------------------------------------
    // CDDCServer API: overrides
    /* end of a session: cleanup/close of m_FHResult and m_QueryData */
    virtual void EndSession() override;

public:
    //--------------------------------------------------------------
    // DDCServer API: request handlers: required

    /* request handler: get_first_hits: required (leaf) */
    virtual void handle__get_first_hits(std::string &Result, const char *Query, int TimeOut, size_t ResultLimit, const std::string& ReqPath, const NavHint& Hint);

    /* request handler: get_hit_strings: required (leaf) */
    virtual void handle__get_hit_strings(std::string &Result, const char *ResultType, size_t StartHitNo, size_t ResultLimit);

    /* request handler: run_query: required (branch) */
    virtual void handle__run_query(std::string &Result, const char *CorpusName, const char *Query, const char *ResultType, size_t StartHitNo, size_t ResultLimit, int TimeOut, const std::string& ReqPath, const NavHint& Hint);

    /* request handler: expand_terms: required (leaf|branch) */
    virtual void handle__expand_terms(std::string &Result, const std::string& pipeline, const std::string& terms, int timeout, const std::string &corpus);

    /* request handler: status: required (leaf|branch) */
    virtual void handle__status(std::string &Result, int timeout=10, bool verbose=false);

    /* request handler: info: required (leaf|branch) */
    virtual void handle__info(std::string &Result, int timeout=10, bool verbose=false);

    /* request handler: reload: required (leaf|branch) */
    virtual void handle__reload(std::string &Result, int depth=0);

    /* request handler: clear_cache: required (leaf|branch) */
    virtual void handle__clear_cache(std::string &Result, int depth=0);

    /* request handler: nodes: required (leaf|branch; since v2.2.8) */
    virtual void handle__nodes(std::string &Result, int depth=-1);

    /* request handler: ddc_close_socket: required (leaf|branch) */

public:
    //--------------------------------------------------------------
    // local methods

    /* initialize m_HostMap[] from m_Hosts[] */
    void InitHostMap();

    /* send a request to each daughter (in parallel), fetch the json results (or json error objects) */
    void GetSubcorpusJsonStrings(std::vector<std::string>& Results, const std::string &command, const RequestParams& params, int timeout=10);

    /* send a request to each daughter, collect the results into a single JSON array */
    std::string GetSubcorpusJsonArray(const std::string &command, const RequestParams& params=RequestParams(), int timeout=10);

    /* new top-level guts for handle__run_query(); uses m_FHResult and m_QueryData */
    void RunDistributed();

    /* new top-level guts for handle__get_first_hits() and handle__run_query() phase 1; uses m_FHResult and m_QueryData */ 
    NetworkErrorsEnum RunGetFirstHits();

    /* error-message propagation for get_first_hits requests; uses m_FHResult and m_ErrorStr; assigns to m_ErrorStr if currently empty */
    void CheckFirstHitsResult(NetworkErrorsEnum networkError=neSuccess);

    /* new top-level guts for handle__get_hit_strings() and handle__run_query() phase 2; uses m_FHResult and m_QueryData */
    NetworkErrorsEnum RunGetHitStrings();

    /* backwards-compatible guts for handle__run_query() */
    NetworkErrorsEnum RunDistributed(std::string Query,
                                     const std::string& ResultType,
                                     size_t   StartHitNo,
                                     size_t   ResultLimit,
                                     int&     iInternalError,
                                     size_t&  EndHitNo,
                                     size_t&  HitsCount,
                                     int      TimeOut,
                                     std::string&  ResultString,
                                     size_t&  RelevantDocsCount,
                                     std::string&  HitDistrib,
                                     std::string&  DocDistrib,
                                     std::string&  HitsKey);

    /* mid-level: update the navigation cache from runq.navHint, runq.navKey if applicable */
    void UpdateNavCache();

    /* mid-level guts for handle__run_query() , context-queries only
     *  - updates runq.m_navKey and runq.m_navHint to point to the next available hit
     */
    NetworkErrorsEnum GetHitContexts(CFirstHitsQueryResult& FHResult,
                                     const std::string& ResultType,
                                     DDCFormatTypeEnum ResultTypeE,
                                     CSelectedHosts& SelectedHosts,
                                     int&    InternalError,
                                     int     TimeOut,
                                     std::string& ResultString
        );

    /* mid-level guts for handle__run_query() , count-queries only */
    NetworkErrorsEnum GetHitCounts(CFirstHitsQueryResult& FHResult, DDCFormatTypeEnum ResultTypeE, std::string& ResultString);

    /* old guts for handle__run_query() phase 1 */
    void GetFirstHitsFromCorpora(const CSelectedHosts& SelectedHosts,
                                 const std::string  Query,
                                 const size_t  StartHitNo,
                                 const size_t  ResultLimit,
                                 const int     TimeOut,
                                 CFirstHitsQueryResult& Result);

    /* parameters of a get_hit_strings request to a selected daughter */
    RequestParams GetHitStringsParams(BYTE SelectedHostNo,
                                      const std::vector< std::vector<size_t> >& SortedHits,
                                      const std::vector<size_t>& FirstOffsets,
                                      const std::string& ResultType);

    /* parse a get_hit_strings response S of a daughter */
    NetworkErrorsEnum ParseHitStringsResponse(const std::string& S,
                                              size_t ResultLimit,
                                              int&    InternalError,
                                              std::string& Result,
                                              std::string& ResultHint);

    /* heuristically extract user-specified subcorpora from ":CORPORA" clause of current query, called by RunDistributed()
     * - uses (parsed) input query from m_QueryData
     * - appends parsed daughter paths to m_QueryData.SelectedHosts (which is assumed to be empty when this method is called)
     * - returns false only when a network error occurs
     */
    bool   ReadSelectedHosts(std::string& CleanQuery);

    /* find Host-ID (index in m_Hosts[]) for a given CorpusName (short form, uses m_HostIdMap[])
     *  returns host-ID for CorpusName on success, otherwise m_Hosts.size()
     */
    size_t FindHostID(const std::string& CorpusName) const;

    /* find pointer to host in m_Hosts[] for a given CorpusName
     * returns pointer into m_Hosts[] for CorpusName on success, otherwise NULL
     */
    CHost* FindHost(const std::string& CorpusName);

    /* aligns user-request CorpusPath into shared (~runq.ReqPath), initial (immediate daughter), and non-initial (grandchildren etc.) components */
    void AlignCorpusPath(const std::string& UserPath, std::string& Dtr, std::string& Rest);
};

/* compatibility typedef for ddc < v2.0.23 */
typedef CDDCBranchServer CDDCServerListenHost;

#endif /* DDC_BRANCH_SERVER_H */
