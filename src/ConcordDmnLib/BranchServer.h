//-*- Mode: C++; c-basic-offset:4; -*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2018 by Bryan Jurish
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
#ifndef DDC_BRANCH_SERVER_H
#define DDC_BRANCH_SERVER_H

#include "../ConcordDmnLib/Server.h"

//======================================================================
/** single hit data in get_first_hits responses */
struct CHitToSort 
{
    BYTE	m_HostNo;	///< subcorpus id
    size_t	m_HitNo;	///< subcorpus-local hit-number for context queries OR hit count for count-queries
    string	m_SortKeyStr;	///< hit sort-string

    CHitToSort(BYTE HostNo=0)
	: m_HostNo(HostNo)
    {};

    inline bool operator < (const CHitToSort& X) const {
	return m_SortKeyStr < X.m_SortKeyStr;
    };

    /** steal data from X */
    inline void steal(CHitToSort &X)
    {
	m_HostNo = X.m_HostNo;
	m_HitNo  = X.m_HitNo;
	m_SortKeyStr.swap(X.m_SortKeyStr);
    };

    /** string form of hit, for debugging messages */
    inline string debugStr(void) const
    {
	return Format("{HostNo=%d,HitNo=%zd,SortKey=%s}", m_HostNo, m_HitNo, jsonStr(m_SortKeyStr).c_str());
    };
};

//==============================================================================
/** direct comparison operator for sorting count-hits by m_HitNo (count) */
struct LessByHitNo {
	bool operator() (const CHitToSort &a, const CHitToSort &b) const
	{ return a.m_HitNo < b.m_HitNo; };
};


//======================================================================
/** \brief parsed get_first_hits response
 * \detail
 * \li somewhat redundant with CRunQueryData
 * \li can and should probably be merged with CRunQueryData
 */
struct CFirstHitsQueryResult  {
    size_t			m_AllHitsCount;
    size_t			m_AllRelevantDocsCount; 
    string			m_HitsDistributionStr;
    string			m_RelevantDocsDistributionStr;
    int				m_InternalError;
    HitSortOrderEnum		m_SortOrder;		//< hit sort order; formerly bool m_bSort
    NetworkErrorsEnum		m_NetworkError;
    string			m_ErrorStr;
    vector<CHitToSort>  	m_Hits;
    vector<size_t>		m_DtrEnds;		//< EndHitNo components scanned from each immediate daughter subcorpus
    vector<SOCKET>		m_Sockets;
    size_t                      m_Offset;            	//< logical offset of m_Hits[0] (sum over number of front-trimmed hits for all subcorpora)
    
    /** destructor implicitly calls CloseSockets() */
    ~CFirstHitsQueryResult()
    {
	CloseSockets();  //-- fix mantis bug #718?
    };

    /** clear the object */
    void Clear();

    /** check whether this result raised any errors */
    inline bool HasErrors() const
    {
	return (m_NetworkError != neSuccess )  || (m_InternalError != errNone);
    };

    /** close any previously opened sockets */
    void CloseSockets();

    /** collect counts by sort-key, only makes sense if m_SortOrder==hsoCounts ; also modifies m_AllHitsCount */
    void CollectCounts();

    /** convert a logical branch-level hit offset to a physical index in m_Hits[] (no boundary-checking, underflow possible) */
    inline size_t PhysicalOffset(size_t LogicalHitNo) const
    { return LogicalHitNo - m_Offset; };

    /** convert a physical offset in m_Hits[] to a logical branch-level hit offset (no boundary-checking, no underflow) */
    inline size_t LogicalOffset(size_t PhysicalHitNo) const
    { return PhysicalHitNo + m_Offset; };

    /** returns the logical upper bound hit offset for LogicalHitNo, with boundary-checking */
    inline size_t LogicalMax(size_t LogicalHitNo) const
    { return min(LogicalHitNo, LogicalOffset(m_Hits.size())); };

    /** returns the physical upper bound hit offset LogicalHitNo, with boundary-checking */
    inline size_t PhysicalMax(size_t LogicalHitNo) const
    { return PhysicalOffset(LogicalMax(LogicalHitNo)); };

    /** returns the number of items in m_Hits[] logical range [StartHitNo,StartHitNo+ResultLimit), with boundary-checking */
    inline size_t LogicalSize(size_t StartHitNo, size_t ResultLimit) const
    { return LogicalMax(StartHitNo+ResultLimit) - LogicalMax(StartHitNo); };

};

//======================================================================
/** CDDCBranchServer statistics [UNUSED?] */
struct CQueryStatistics 
{
    DwordVector	m_HitsEnds;
    DWORD	m_FreqCount;
};


//======================================================================
/** DDC branch server 'run_query' paramter & intermediate result-type */
class CRunQueryData {
public:
    string sQuery; 			///< query string
    string sResultFormat;		///< result format (string)
    size_t StartHitNo;			///< first hit to return
    size_t ResultLimit;			///< max number of hits to return
    int TimeOut;			///< query timeout (seconds)
    int iInternalError;			///< internal error code
    int iNetworkError;  		///< network error code
    size_t EndHitNo;			///< final hit number returned
    size_t HitsCount;			///< total number of hits
    size_t RelevantDocsCount;		///< ?
    DwordVector PossibleHosts;		///< indices of selected immediate subcorpora
    string HitDistrib;			///< ?
    string DocDistrib;			///< ?
    string HitsKey;			///< key for response body data (json only)
    string ResponseBody;		///< response body data
    string *pErrorStr;			///< error string pointer (empty or NULL for success)
    NavHintKey navKey;			///< navigation hint key
    NavHint    navHint;               	///< user- or cache-supplied navigation hint
   
public:
    /** constructor */
    CRunQueryData(const string & _Query="", const string& _ResultFormat="JSON", size_t _Start=0, size_t _Limit=10, int _TimeOut=10, string *_pErrorStr=NULL)
	: sQuery(_Query), sResultFormat(_ResultFormat), StartHitNo(_Start), ResultLimit(_Limit), TimeOut(_TimeOut),
	  iInternalError(errNone), iNetworkError(neSuccess), EndHitNo(0), HitsCount(0), RelevantDocsCount(0), HitDistrib(""), DocDistrib(""),
	  HitsKey("hits_"), ResponseBody(""),
	  pErrorStr(_pErrorStr)
    {
	Trim(sQuery);
	Trim(sResultFormat);
    };

    /** (re-)initialize with parameters */
    void Init(const string & _Query="", const string& _ResultFormat="JSON", size_t _Start=0, size_t _Limit=10, int _TimeOut=10, string *_pErrorStr=NULL, const NavHint& _Hint=NavHint());

    /** clear object */
    void Clear();

    /** populate response string \a Response */
    void toString(string &Response, size_t WorkerId=0, const DDCVersionT& vCompat=DDCVersion);

};

//======================================================================
/** DDC branch server node, formerly CDDCCorpusListenHost */
class CDDCBranchServer : public CDDCServer
{
public:

public:
    //--------------------------------------------------------------
    // local data
    map<string, CQueryStatistics>	m_QueryToStatis; //-- unused?
    vector<CHost>			m_Hosts;	
    string				m_QueryResultString;
    string				m_ErrorStr;  //-- subcorpus error

    //-- low-level data
    CFirstHitsQueryResult 		m_FHResult;   //< first-hits result
    CRunQueryData			m_QueryData;  //< run-query data
    NavHintCache			*m_pNavCache; //< navigation hint cache (shared over multiple worker threads)
    
public:
    //--------------------------------------------------------------
    // Constructors etc.

    /** default constructor
     * \param master true (default) iff this is to be a "master" object (i.e. not a worker clone)
     */
    CDDCBranchServer(bool master=true);

    /** default destructor */
    virtual ~CDDCBranchServer();

    /** close any open socket(s) this server administers, called on termination signal */
    virtual void Shutdown();

    /** set server options (override handles option m_NavCacheSize) */
    virtual void SetOptions(const CDDCServerOptions &Options);

public:
    //--------------------------------------------------------------
    // DDCServer API: client threads

    /** create a minimal copy of this object (and any subordinate data) for use by a worker thread
     *  \li override creates a CDDCBranchServer as non-master
     */
    virtual CDDCServer *WorkerClone(void) const
    { return (CDDCServer*)new CDDCBranchServer(false); };

    /** initialize a newly created worker-clone (and any subordinate data) */
    virtual void WorkerCloneInit(const CDDCServer *Parent, size_t WorkerId);

    /** /** perform local cleanup of a worker clone prior to deletion */
    virtual void WorkerCloneFree(void);

public:
    //--------------------------------------------------------------
    // CHost API: overrides
    /** close connected socket, implies cleanup/close of m_FHResult and m_QueryData */
    virtual bool Close(SOCKET& rConnectedSocket, bool linger=false, int timeout=5);

    /** close a socket connected to a daugher subcorpus, NO implicit cleanup of m_FHResult and m_QueryData */
    virtual bool CloseDtr(SOCKET& rConnectedSocket, bool linger=false, int timeout=5);

public:
    //--------------------------------------------------------------
    // DDCServer API: request handlers: required

    /* request handler: get_first_hits: required (leaf) */
    virtual void handle__get_first_hits(string &Result, const char *Query, int TimeOut, size_t ResultLimit, const NavHint& Hint);

    /* request handler: get_hit_strings: required (leaf) */
    virtual void handle__get_hit_strings(string &Result, const char *ResultType, size_t StartHitNo, size_t ResultLimit);

    /* request handler: run_query: required (branch) */
    virtual void handle__run_query(string &Result, const char *CorpusName, const char *Query, const char *ResultType, size_t StartHitNo, size_t ResultLimit, int TimeOut, const NavHint& Hint);

    /** request handler: expand_terms: required (leaf|branch) */
    virtual void handle__expand_terms(string &Result, const string& pipeline, const string& terms, int timeout, const string &corpus);

    /** request handler: status: required (leaf|branch) */
    virtual void handle__status(string &Result, int timeout=10, bool verbose=false);

    /** request handler: info: required (leaf|branch) */
    virtual void handle__info(string &Result, int timeout=10, bool verbose=false);

    /** request handler: reload: required (leaf|branch) */
    virtual void handle__reload(string &Result, int depth=0);

    /** request handler: clear_cache: required (leaf|branch) */
    virtual void handle__clear_cache(string &Result, int depth=0);

    /** request handler: ddc_close_socket: required (leaf|branch) */
    virtual void handle__close_socket(string &Result, SOCKET &rConnectedSocket);

public:
    //--------------------------------------------------------------
    // local methods

    /** pass request to each subcorpus host and fetch results into a JSON array */
    string  GetSubcorpusJsonArray(const string &request, int timeout=10);

    /** new top-level guts for handle__run_query(); uses m_FHResult and m_QueryData */
    void RunDistributed();

    /** new top-level guts for handle__get_first_hits() and handle__run_query() phase 1; uses m_FHResult and m_QueryData */ 
    NetworkErrorsEnum RunGetFirstHits();

    /** error-message propagation for get_first_hits requests; uses m_FHResult and m_ErrorStr; assigns to m_ErrorStr if currently empty */
    void CheckFirstHitsResult(NetworkErrorsEnum networkError=neSuccess);

    /** new top-level guts for handle__get_hit_strings() and handle__run_query() phase 2; uses m_FHResult and m_QueryData */
    NetworkErrorsEnum RunGetHitStrings();

    /** backwards-compatible guts for handle__run_query() */
    NetworkErrorsEnum RunDistributed(string Query,
				     const string& ResultType,
				     size_t   StartHitNo,
				     size_t   ResultLimit,
				     int&     iInternalError,
				     size_t&  EndHitNo,
				     size_t&  HitsCount,
				     int      TimeOut,
				     string&  ResultString,
				     size_t&  RelevantDocsCount,
				     string&  HitDistrib,
				     string&  DocDistrib,
				     string&  HitsKey);

    /** mid-level: update the navigation cache from runq.navHint, runq.navKey if applicable */
    void UpdateNavCache();

    /** mid-level guts for handle__run_query() , context-queries only
     *  \li updates runq.m_navKey and runq.m_navHint to point to the next available hit
     */
    NetworkErrorsEnum GetHitContexts(CFirstHitsQueryResult& FHResult,
				     const string& ResultType,
				     DDCFormatTypeEnum ResultTypeE,
				     DwordVector& PossibleHosts,
				     int&    InternalError,
				     int     TimeOut,
				     string& ResultString
				     );

    /** mid-level guts for handle__run_query() , count-queries only */
    NetworkErrorsEnum GetHitCounts(CFirstHitsQueryResult& FHResult, DDCFormatTypeEnum ResultTypeE, string& ResultString);

    /** old guts for handle__run_query() phase 1 */
    void GetFirstHitsFromCorpora(const DwordVector& PossibleHosts,
				 const string  Query,
				 const size_t  StartHitNo,
				 const size_t  ResultLimit,
				 const int     TimeOut,
				 CFirstHitsQueryResult& Result);

    /** old guts for handle__run_query() phase 2 */
    NetworkErrorsEnum GetHitStringsFromOneCorpus(CHost& Host,
						 const string& ResultType,
						 size_t StartHitNo,
						 size_t ResultLimit,
						 int   TimeOut,
						 SOCKET& CorpusSocket,
						 int&    InternalError,
						 string& Result,
						 string& ResultHint);

    /** heuristically extract user-specified subcorpora from ":CORPORA" clause of InputQuery, called by RunDistributed()
     * \li returns false only when a network error occurs
     * \todo fixme : have this method actually parse the query to avoid ":"-scanning errors
     */
    bool   ReadPossibleHosts(const string& InputQuery, string& CleanQuery, DwordVector& PossibleHosts) /*const*/;
};

/** compatibility typedef for ddc < v2.0.23 */
typedef CDDCBranchServer CDDCServerListenHost;

#endif /* DDC_BRANCH_SERVER_H */

