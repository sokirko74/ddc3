//-*- Mode: C++; c-basic-offset:4; -*-
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2014 by Bryan Jurish
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
    DWORD	m_HitNo;	///< subcorpus-local hit-number for context queries ; hit count for count-queries
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
	return Format("{HostNo=%d,HitNo=%d,SortKey=%s}", m_HostNo, m_HitNo, jsonStr(m_SortKeyStr).c_str());
    };
};

//======================================================================
/** parsed get_first_hits response */
struct CFirstHitsQueryResult  {
    DWORD			m_AllHitsCount;
    DWORD			m_AllRelevantDocsCount; 
    string			m_HitsDistributionStr;
    string			m_RelevantDocsDistributionStr;
    int				m_InternalError;
    HitSortOrderEnum		m_SortOrder;		//< hit sort order (-1:descending, 0:none, 1:ascending, 2:ascending_counts); formerly bool m_bSort
    NetworkErrorsEnum		m_NetworkError;
    string			m_ErrorStr;
    vector<CHitToSort>  	m_Hits;
    vector<SOCKET>		m_Sockets;
    
    bool HasErrors() const
    {
	return (m_NetworkError != neSuccess )  || (m_InternalError != errNone);
    };

    /** close any previously opened sockets */
    void CloseSockets();

    /** collect counts by sort-key, only makes sense if m_SortOrder==hsoAscendingCounts ; also modified m_AllHitsCount */
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
/** DDC leaf server node, formerly CDDCCorpusListenHost */
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
    virtual void handle__status(string &Result, bool verbose=false);

    /** request handler: info: required (leaf|branch) */
    virtual void handle__info(string &Result, bool verbose=false);

    /** request handler: reload: required (leaf|branch) */
    virtual void handle__reload(string &Result);

    /** request handler: clear_cache: required (leaf|branch) */
    virtual void handle__clear_cache(string &Result);

public:
    //--------------------------------------------------------------
    // local methods

    /** pass request to each subcorpus host and fetch results into a JSON array */
    string  GetSubcorpusJsonArray(const string &request, int timeout = 10);

    /** top-level guts for handle__run_query() */
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

