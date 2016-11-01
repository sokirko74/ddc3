//-*- Mode: C++; c-basic-offset:4; -*-
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
/** parsed get_first_hits response */
struct CFirstHitsQueryResult  {
    DWORD			m_AllHitsCount;
    DWORD			m_AllRelevantDocsCount; 
    string			m_HitsDistributionStr;
    string			m_RelevantDocsDistributionStr;
    int				m_InternalError;
    HitSortOrderEnum		m_SortOrder;		//< hit sort order; formerly bool m_bSort
    NetworkErrorsEnum		m_NetworkError;
    string			m_ErrorStr;
    vector<CHitToSort>  	m_Hits;
    vector<SOCKET>		m_Sockets;

    /** destructor implicitly calls CloseSockets() */
    ~CFirstHitsQueryResult()
    {
	CloseSockets();  //-- fix mantis bug #718?
    };

    /** check whether this result raised any errors */
    bool HasErrors() const
    {
	return (m_NetworkError != neSuccess )  || (m_InternalError != errNone);
    };

    /** close any previously opened sockets */
    void CloseSockets();

    /** collect counts by sort-key, only makes sense if m_SortOrder==hsoCounts ; also modifies m_AllHitsCount */
    void CollectCounts();
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
    int StartHitNo;			///< first hit to return
    int ResultLimit;			///< max number of hits to return
    int TimeOut;			///< query timeout (seconds)
    int iInternalError;			///< internal error code
    int iNetworkError;  		///< network error code
    DWORD EndHitNo;			///< final hit number returned
    DWORD HitsCount;			///< total number of hits
    DWORD RelevantDocsCount;		///<
    string HitDistrib;			///<
    string DocDistrib;			///<
    string HitsKey;			///< key for response body data (json only)
    string ResponseBody;		///< response body data
    string *pErrorStr;			///< error string pointer (empty or NULL for success)

public:
    /** constructor */
    CRunQueryData(const string & _Query="", const string& _ResultFormat="JSON", int _Start=0, int _Limit=10, int _TimeOut=10, string *_pErrorStr=NULL)
	: sQuery(_Query), sResultFormat(_ResultFormat), StartHitNo(_Start), ResultLimit(_Limit), TimeOut(_TimeOut),
	  iInternalError(errNone), iNetworkError(neSuccess), EndHitNo(0), HitsCount(0), RelevantDocsCount(0), HitDistrib(""), DocDistrib(""),
	  HitsKey("hits_"), ResponseBody(""),
	  pErrorStr(_pErrorStr)
    {
	Trim(sQuery);
	Trim(sResultFormat);
    };

    /** populate response string \a Response */
    void toString(string &Response);
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

public:
    //--------------------------------------------------------------
    // Constructors etc.

    /** default constructor */
    CDDCBranchServer(bool bDoubleMessage=false, ProtocolDensityEnum pdProtocolDensity=pdWeakDensity);

    /** default destructor */
    virtual ~CDDCBranchServer()
    {};

    /** close any open socket(s) this server administers, called on termination signal */
    virtual void Shutdown();

public:
    //--------------------------------------------------------------
    // DDCServer API: request handlers: required

    /* request handler: get_first_hits: required (leaf) */
    //virtual void handle__get_first_hits(string &Result, const char *Query, int TimeOut, int ResultLimit);

    /* request handler: get_hit_strings: required (leaf) */
    //virtual void handle__get_hit_strings(string &Result, const char *ResultType, int StartHitNo, int ResultLimit);

    /* request handler: run_query: required (branch) */
    virtual void handle__run_query(string &Result, const char *CorpusName, const char *Query, const char *ResultType, int StartHitNo, int ResultLimit, int TimeOut);

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

public:
    //--------------------------------------------------------------
    // local methods

    /** pass request to each subcorpus host and fetch results into a JSON array */
    string  GetSubcorpusJsonArray(const string &request, int timeout=10);

    /** new top-level guts for handle__run_query() */
    void RunDistributed(CRunQueryData &runq);
    
    /** backwards-compatible guts for handle__run_query() */
    NetworkErrorsEnum RunDistributed(string Query,
				     const string& ResultType,
				     DWORD StartHitNo,
				     DWORD ResultLimit,
				     int&  iInternalError,
				     DWORD&  EndHitNo,
				     DWORD&  HitsCount,
				     int     TimeOut,
				     string& ResultString,
				     DWORD&  RelevantDocsCount,
				     string& HitDistrib,
				     string& DocDistrib,
				     string& HitsKey);

    /** mid-level guts for handle__run_query() , context-queries only */
    NetworkErrorsEnum GetHitContexts(CFirstHitsQueryResult& FHResult,
				     const string& ResultType,
				     DDCFormatTypeEnum ResultTypeE,
				     DwordVector& PossibleHosts,
				     int&  InternalError,
				     int     TimeOut,
				     string& ResultString
				     );

    /** mid-level guts for handle__run_query() , count-queries only */
    NetworkErrorsEnum GetHitCounts(CFirstHitsQueryResult& FHResult, DDCFormatTypeEnum ResultTypeE, string& ResultString);

    /** guts for handle__run_query() phase 1 */
    void GetFirstHitsFromCorpora(const DwordVector& PossibleHosts,
				 const string Query,
				 const DWORD  ResultLimit,
				 const int    TimeOut,
				 CFirstHitsQueryResult& Result);

    /** guts for handle__run_query() phase 2 */
    NetworkErrorsEnum GetHitStringsFromOneCorpus(CHost& Host,
						 const string& ResultType,
						 DWORD StartHitNo,
						 DWORD ResultLimit,
						 int   TimeOut,
						 SOCKET& CorpusSocket,
						 int&    InternalError,
						 string& Result);

    /** heuristically extract user-specified subcorpora from ":CORPORA" clause of InputQuery, called by RunDistributed()
     * \li returns false only when a network error occurs
     * \todo fixme : have this method actually parse the query to avoid ":"-scanning errors
     */
    bool   ReadPossibleHosts(const string& InputQuery, string& CleanQuery, DwordVector& PossibleHosts) /*const*/;
};

/** compatibility typedef for ddc < v2.0.23 */
typedef CDDCBranchServer CDDCServerListenHost;

#endif /* DDC_BRANCH_SERVER_H */

