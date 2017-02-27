//-*- Mode: C++; c-basic-offset:4; -*-
//
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

#include "BranchServer.h"
#include "../CommonLib/ddcString.h"
#include "../CommonLib/ddcTime.h"
#include "../ConcordLib/QueryCompiler.h"

//#define DEBUG_SERVER_THREADS 1
#undef DEBUG_SERVER_THREADS

//==============================================================================
// CFirstHitsQueryResult

//----------------------------------------------------------------------
void CFirstHitsQueryResult::Clear()
{
    m_AllHitsCount = 0;
    m_AllRelevantDocsCount = 0;
    m_HitsDistributionStr.clear();
    m_RelevantDocsDistributionStr.clear();
    m_SortOrder = hsoNone;
    m_InternalError = errNone;
    m_NetworkError = neSuccess;
    ClearVector(m_Hits);
    m_Sockets.clear();
}

//----------------------------------------------------------------------
void CFirstHitsQueryResult::CloseSockets()
{
    for (size_t j=0; j<m_Sockets.size(); j++) {
	if (m_Sockets[j] != -1) {
	    string ErrorStr;
	    SendString(m_Sockets[j], "ddc_close_socket", 16, ErrorStr);
	    CloseSocket(m_Sockets[j]);
	}
	m_Sockets[j] = -1;
    }
}

//----------------------------------------------------------------------
void CFirstHitsQueryResult::CollectCounts()
{
    assert(IsCountSort(m_SortOrder));
    vector<CHitToSort> newHits;
    newHits.reserve(m_Hits.size());

    CHitToSort *cur=NULL;
    for (vector<CHitToSort>::iterator hi=m_Hits.begin(); hi != m_Hits.end(); hi++) {
	if (cur && cur->m_SortKeyStr == hi->m_SortKeyStr) {
	    cur->m_HitNo += hi->m_HitNo;
	    --m_AllHitsCount;
	} else {
	    newHits.push_back(CHitToSort());
	    cur = &(newHits.back());
	    cur->steal(*hi);
	}
    }
    m_Hits.swap(newHits);

    //-- v2.0.36: we might need to re-sort hits
    switch (m_SortOrder) {
    case hsoDescendingCountKeys:
	reverse(m_Hits.begin(), m_Hits.end());
	break;
    case hsoAscendingCountValues:
	stable_sort(m_Hits.begin(), m_Hits.end(), LessByHitNo());
	break;
    case hsoDescendingCountValues:
	stable_sort(m_Hits.rbegin(), m_Hits.rend(), LessByHitNo());
	break;
    case hsoAscendingCountKeys:
    default:
	break;
    }
}

//==============================================================================
// CDDCBranchServer: constructors etc

//----------------------------------------------------------------------
CDDCBranchServer::CDDCBranchServer()
{
    m_maxReceiveBytes = DDC_STATIC_BUFLEN;
    m_bLogRequests    = true;
    if (ddcLogLevel >= ddcLLDebug) {
	m_bLogFinish = true;
    } else {
	m_bLogFinish = false;
	m_noLogCommands.insert("version");
	m_noLogCommands.insert("status");
	m_noLogCommands.insert("vstatus");
	m_noLogCommands.insert("info");
	m_noLogCommands.insert("vinfo");
	m_noLogCommands.insert("get_hit_strings");
    }
};

//----------------------------------------------------------------------
void CDDCBranchServer::Shutdown()
{
    ddcLogInfo(Format("shutting down branch server %s", m_CorpusName.c_str()));
    for (int i=0; i < m_Hosts.size(); i++) {
	m_Hosts[i].StopAcceptingThread();
    }
    StopAcceptingThread();
};

//==============================================================================
// CDDCBranchServer: client threads

//----------------------------------------------------------------------
void CDDCBranchServer::WorkerCloneInit(const CDDCServer *Parent, size_t WorkerId)
{
    CDDCServer::WorkerCloneInit(Parent,WorkerId);

    CDDCBranchServer *parent = (CDDCBranchServer*)Parent;
    m_Hosts = parent->m_Hosts;
}

//----------------------------------------------------------------------
void CDDCBranchServer::WorkerCloneFree(void)
{
    CDDCServer::WorkerCloneFree();
}


//==============================================================================
// CRunQueryData

//----------------------------------------------------------------------
void CRunQueryData::Init(const string & _Query, const string& _ResultFormat, int _Start, int _Limit, int _TimeOut, string *_pErrorStr)
{
    Clear();
    sQuery = _Query;
    sResultFormat = _ResultFormat;
    StartHitNo = _Start;
    ResultLimit = _Limit;
    TimeOut = _TimeOut;
    pErrorStr = _pErrorStr;

    Trim(sQuery);
    Trim(sResultFormat);
}
			 
//----------------------------------------------------------------------
void CRunQueryData::Clear()
{
    ClearString(sQuery);
    sResultFormat.clear();
    StartHitNo = 0;
    ResultLimit = 10;
    TimeOut = 10;
    iInternalError = (int)errNone;
    iNetworkError  = (int)neSuccess;
    EndHitNo = 0;
    HitsCount = 0;
    RelevantDocsCount = 0;
    ClearVector(PossibleHosts);
    HitDistrib.clear();
    DocDistrib.clear();
    HitsKey = "hits_";
    ClearString(ResponseBody);
    pErrorStr = NULL;
}

//----------------------------------------------------------------------
void CRunQueryData::toString(string &Response, size_t WorkerId)
{
    if (CConcSession::GetResultFormatByString(sResultFormat) == DDC_ResultJson) {
	Response = (string("{")
		    + Format("\"istatus_\":%i", iInternalError)
		    + Format(",\"nstatus_\":%i", iNetworkError)
		    
		    /*-- moo: this formatting works, but doesn't do anything useful (bogus error code 32 for parse error?)*/
		    /*
		      + "\"istatus_\":" + jsonStr(Format("%i %s", InternalError, GetDDCErrorString((DDCErrorEnum)InternalError).c_str()))
		      + ",\"nstatus_\":" + jsonStr(Format("%i %s", iNetworkError, GetNetworkErrorString((NetworkErrorsEnum)iNetworkError).c_str()))
		    */
		    + (!pErrorStr || pErrorStr->empty() ? "" : (string(",\"error_\":") + jsonStr(*pErrorStr)))

		    + Format(",\"end_\":%i", EndHitNo)
		    + Format(",\"nhits_\":%i", HitsCount)
		    + Format(",\"ndocs_\":%i", RelevantDocsCount)
		    + ",\"dhits_\":" + jsonStr(HitDistrib)
		    + ",\"ddocs_\":" + jsonStr(DocDistrib)
#if DEBUG_SERVER_THREADS
		    + ",\"worker_\":" + Format("%zu", WorkerId)
#endif
		    + ",\"" + HitsKey + "\":[\n" + ResponseBody
		    + "\n]}");
    }
    else if (!pErrorStr || pErrorStr->empty()) {
	//-- normal, error-free result
	Response = ResponseBody + Format("\x01 %i %i %i %i %i", iInternalError, iNetworkError, EndHitNo, HitsCount, RelevantDocsCount);
    }
    else {
	//-- errors
	Response = Format("\x01 %i %i %i %i %i", iInternalError, iNetworkError, EndHitNo, HitsCount, RelevantDocsCount) + "\n" + *pErrorStr + "\n";
    }
}

//==============================================================================
// CDDCLeafServer: CHost API: overrides

//----------------------------------------------------------------------
bool CDDCBranchServer::Close(SOCKET& rConnectedSocket, bool linger, int timeout)
{
    //ddcLogTrace(Format("CDDCBranchServer::Close(): socket=%d:%s, linger=%d, timeout=%d", rConnectedSocket, SocketPeerP(rConnectedSocket).c_str(), (int)linger, timeout));
    
    //-- clear local intermediate query results: don't hog memory (or sockets) after expensive (often failed) queries
    m_FHResult.CloseSockets();
    m_FHResult.Clear();
    m_QueryData.Clear();

    return CHost::Close(rConnectedSocket, linger, timeout);
}

//----------------------------------------------------------------------
bool CDDCBranchServer::CloseDtr(SOCKET& rConnectedSocket, bool linger, int timeout)
{
    if (rConnectedSocket != -1) {
	string ErrorStr;
	SendString(rConnectedSocket, "ddc_close_socket", 16, ErrorStr);
    }
    return CHost::Close(rConnectedSocket, linger, timeout);
}


//==============================================================================
// CDDCBranchServer: handlers

//----------------------------------------------------------------------
void CDDCBranchServer::handle__get_first_hits(string &Result, const char *Query, int TimeOut, int ResultLimit)
{
    CRunQueryData &runq = m_QueryData;
    CFirstHitsQueryResult& FHResult = m_FHResult;
    runq.Init(Query, "", 0, ResultLimit, TimeOut, &m_ErrorStr);

    NetworkErrorsEnum rc = RunGetFirstHits();
    if (FHResult.m_InternalError != errNone)
	throw CExpc(FHResult.m_InternalError);
    else if (rc != neSuccess)
	throw CExpc(errRuntime, GetNetworkErrorString(rc));
    
    //-- adapted from CDDCLeafServer::handle__get_first_hits(), CConcSession::GetHitIds()
    Result = Format ("%i %i %i %i %i", FHResult.m_InternalError, runq.EndHitNo, FHResult.m_AllHitsCount, FHResult.m_AllRelevantDocsCount, FHResult.m_SortOrder);
    if (IsCountSort(FHResult.m_SortOrder)) {
	//-- count-query requires special formatting, but can return immediately
	for (vector<CHitToSort>::const_iterator hi=FHResult.m_Hits.begin(); hi != FHResult.m_Hits.end(); ++hi) {
	    Result += Format("\t%zd -0 ", hi->m_HitNo); //-- hi->m_HitNo is really the hit-count
	    Result += hi->m_SortKeyStr;
	}
	m_bExpectMore = false;
    }
    else {
	//-- context query: just return hit keys
        for (size_t i=0; i < FHResult.m_Hits.size(); ++i) {
	    Result += Format("\t%zd -0 ", i);
	    Result += FHResult.m_Hits[i].m_SortKeyStr;
	}
	m_bExpectMore = true;
    }

    return;
}

//----------------------------------------------------------------------
void CDDCBranchServer::handle__get_hit_strings(string &Result, const char *ResultType, int StartHitNo, int ResultLimit)
{
    CRunQueryData &runq = m_QueryData;
    CFirstHitsQueryResult& FHResult = m_FHResult;

    //-- sanity check(s)
    if (FHResult.m_HitsDistributionStr.empty())
	throw CExpc(errRuntime, "CDDCBranchServer::handle__get_hit_strings(): FHResult is uninitialized!");
    if (StartHitNo < runq.StartHitNo)
	throw CExpc(errRuntime, "CDDCBranchServer::handle__get_hit_strings(): requested StartHitNo=%i < cached=%i", StartHitNo, runq.StartHitNo);
    if (ResultLimit > runq.ResultLimit)
	throw CExpc(errRuntime, "CDDCBranchServer::handle__get_hit_strings(): requested ResultLimit=%i > cached=%i", ResultLimit, runq.ResultLimit);

    //-- guts
    runq.sResultFormat = ResultType;
    runq.StartHitNo    = StartHitNo;
    runq.ResultLimit   = ResultLimit;

    //-- re-trim FHResult hits (in case get_hit_strings is requesting fewer hits than get_first_hits did)
    if (runq.StartHitNo+runq.ResultLimit < FHResult.m_Hits.size())
	FHResult.m_Hits.erase(FHResult.m_Hits.begin()+runq.StartHitNo+runq.ResultLimit, FHResult.m_Hits.end());
    
    if (runq.StartHitNo < FHResult.m_Hits.size())
	FHResult.m_Hits.erase(FHResult.m_Hits.begin(), FHResult.m_Hits.begin()+runq.StartHitNo);
    else
	FHResult.m_Hits.clear();

    //-- get full string form of selected hits
    DDCFormatTypeEnum ResultTypeE = CConcSession::GetResultFormatByString(runq.sResultFormat);

    if (IsCountSort(FHResult.m_SortOrder)) {
	//-- count-query can generate strings immediately
	GetHitCounts(FHResult, ResultTypeE, runq.ResponseBody);
	runq.HitsCount = FHResult.m_AllHitsCount;
	FHResult.m_HitsDistributionStr.insert(FHResult.m_HitsDistributionStr.size()-2, Format("~%d", runq.HitsCount));
	runq.HitsKey = "counts_";
    } else {
	//-- context-query must retrieve full hit strings
	GetHitContexts(FHResult, runq.sResultFormat, ResultTypeE, runq.PossibleHosts, runq.iInternalError, runq.TimeOut, runq.ResponseBody);
	runq.HitsKey = "hits_";
    }

    //-- check for errors
    if (runq.iInternalError != (int)errNone)
	throw CExpc(runq.iInternalError);
    else if (runq.iNetworkError != (int)neSuccess)
	throw CExpc(errRuntime, GetNetworkErrorString((NetworkErrorsEnum)runq.iNetworkError));

    //-- format result
    if (ResultTypeE == DDC_ResultJson) {
	//-- JSON mode: munge in JSON syntax
	StringTokenizer tok(runq.ResponseBody.c_str(), "\n");
	Result.reserve(6+runq.ResponseBody.size()+FHResult.m_Hits.size());
	Result = "0\x01[";
	while (tok()) {
	    string s(tok.val());
	    size_t p0 = s.find ('{', 0);
	    size_t p1 = s.rfind('}', s.npos);
	    if (!s.empty() && p0!=s.npos && p1!=s.npos && p0<p1) {
		Result += s.substr(p0,p1-p0+1);
		Result.push_back(',');
		Result.push_back('\n');
		Result += CDDCServer::AdditionalHitDelimiter;
	    }
	}
	//-- replace final trailing comma
	size_t pn = Result.rfind(',', Result.npos);
	if (pn != Result.npos)
	    Result[pn] = ']';
    } else {
	//-- default: just append response body
	Result.reserve(4+runq.ResponseBody.size());
	Result = "0\x01";
	Result += runq.ResponseBody;
	Result.push_back('\x01');
	Result += CDDCServer::AdditionalHitDelimiter;
    }
    
    runq.HitDistrib = FHResult.m_HitsDistributionStr.substr(21,FHResult.m_HitsDistributionStr.size()-23);
    runq.DocDistrib = FHResult.m_RelevantDocsDistributionStr.substr(32,FHResult.m_RelevantDocsDistributionStr.size()-34);
    runq.EndHitNo   = runq.StartHitNo + FHResult.m_Hits.size();
    runq.iNetworkError = neSuccess;
    
    m_bExpectMore = false;
}

//----------------------------------------------------------------------
void CDDCBranchServer::handle__run_query(string &Result, const char *CorpusName, const char *Query, const char *ResultType, int StartHitNo, int ResultLimit, int TimeOut)
{
    CRunQueryData& runq = m_QueryData;
    runq.Init(Query, ResultType, StartHitNo, ResultLimit, TimeOut, &m_ErrorStr);
    
    if ( runq.sQuery.empty() )
	throw CExpc(errParseError, "CDDCBranchServer::handle__run_query(): cannot parse empty query string");

    m_ErrorStr.clear();

    try {
	RunDistributed();
    }
    catch (exception &e) {
	if (m_ErrorStr.empty()) m_ErrorStr = Format("Exception: %s", e.what());
    }

    //-- log errors
    if (!m_ErrorStr.empty()) {
	ddcLogError( Format("CDDCBranchServer::handle__run_query(): ERROR: %s", m_ErrorStr.c_str()) );
	++m_SessionStats.m_nErrors;
    }

    //-- generate response
    runq.toString(Result, m_WorkerId);
    m_bExpectMore = false;

    //-- cleanup
    m_QueryData.Clear();
    m_FHResult.Clear();
}


//----------------------------------------------------------------------
void CDDCBranchServer::handle__expand_terms(string &Result, const string& pipeline, const string& terms, int timeout, const string &corpus)
{
    //-- get expansion host
    CHost *h = NULL;
    if (corpus.empty()) {
	//-- no user-specified expansion host: use first host in m_Hosts
	h = &(m_Hosts[0]);
    } else {
	//-- user-specified expansion host: get matching name from m_Hosts
	for (vector<CHost>::iterator hi=m_Hosts.begin(); hi != m_Hosts.end(); hi++) {
	    if (hi->m_CorpusName == corpus) {
		h = &(*hi);
		break;
	    }
	}
	if (h==NULL)
	    throw CExpc(errParseError, "unknown host `%s' in `expand_terms' request", corpus.c_str());
    }

    //-- delegate the query to the user-specified host
    assert(h != NULL);
    string ErrorStr;
    int hsock = h->CreateAndConnectSocket(ErrorStr);
    try {
	if (!ErrorStr.empty() || hsock==-1)
	    throw CExpc(errOther, "could not connect to subcorpus `%s': %s", h->m_CorpusName.c_str(), ErrorStr.c_str());

	string hq = string("expand_terms \x01") + pipeline + "\x01" + terms + "\x01" + Format("%i", timeout);
	if (!SendString(hsock, hq, ErrorStr))
	    throw CExpc(errOther, "expand_terms faild for subcorpus `%s': %s", h->m_CorpusName.c_str(), ErrorStr.c_str());

	//-- read response directly into Result
	if (ReceiveString(hsock, Result, timeout) != neSuccess)
	    throw CExpc(errOther, "expand_terms failed to read a response from subcorpus `%s'", h->m_CorpusName.c_str());
    }
    catch (...) {
	this->CloseDtr(hsock);
	throw;
    }

    this->CloseDtr(hsock);
    m_bExpectMore = false;
}

//----------------------------------------------------------------------
void CDDCBranchServer::handle__status(string &Result, int timeout, bool verbose)
{
    //-- status or vstatus : distributed server status
    double uptime = difftime(time(NULL), m_tStarted);

    string subResult;
    if (verbose) {
	//-- vstatus: get subcorpus status
	subResult = GetSubcorpusJsonArray("vstatus", timeout);
    } else {
	//-- status: just get subcorpus names
	for (size_t i=0; i < m_Hosts.size(); ++i) {
	    subResult += (i==0 ? '[' : ',');
	    subResult += jsonStr(m_Hosts[i].m_CorpusName);
	}
	subResult += "]\n";
    }

    Result = (string("{\n")
	      + "\"name\":" + jsonStr(m_CorpusName) + ",\n"
	      + "\"version\":" + jsonStr(PACKAGE_VERSION) + ",\n"
	      + "\"hostname\":" + jsonStr(m_FQHostName) + ",\n"
	      + "\"hostaddr\":" + jsonStr(m_HostAddr) + ",\n"
	      + "\"port\":" + Format("%d", m_Port) + ",\n"
	      + "\"started\":" + jsonStr(timestampUTC(m_tStarted)) + ",\n"
	      + "\"uptime\":" + Format("%.0f", uptime) + ",\n"
	      + "\"nrequests\":" + Format("%zd", m_ServerStats.m_nRequests) + ",\n"
	      + "\"nqueries\":" + Format("%zd", m_ServerStats.m_nQueries) + ",\n"
	      + "\"nerrors\":" + Format("%zd", m_ServerStats.m_nErrors) + ",\n"
	      + "\"nslow\":" + Format("%zd", m_ServerStats.m_nSlow) + ",\n"
	      + "\"nworkers\":" + Format("%zd", m_nWorkers) + ",\n"	      
	      + "\"memkb\":" + Format("%zd", this->residentMemorySize()) + ",\n"
	      + "\"corpora\":" + subResult + "}\n"
	      );
    m_bExpectMore = false;
}

//----------------------------------------------------------------------
void CDDCBranchServer::handle__info(string &Result, int timeout, bool verbose)
{
    //-- info : distributed (collected) corpus info
    Result = (string("{\n")
	      + "\"name\":" + jsonStr(m_CorpusName) + ",\n"
	      + "\"version\":" + jsonStr(PACKAGE_VERSION) + ",\n"
	      + "\"corpora\":" + GetSubcorpusJsonArray(verbose ? "vinfo" : "info")
	      + "}\n"
	      );
    m_bExpectMore = false;
}

//----------------------------------------------------------------------
void CDDCBranchServer::handle__reload(string &Result, int depth)
{
    Result = string("{") + jsonStr(m_CorpusName) + ":";
    if (depth != 0) {
	Result += GetSubcorpusJsonArray(Format("reload %d",depth-1));
    } else {
	Result.push_back('1');
    }
    Result.push_back('}');
    m_bExpectMore = false;
}

//----------------------------------------------------------------------
void CDDCBranchServer::handle__clear_cache(string &Result, int depth)
{
    ddcCurlCache.lock();
    ddcCurlCache.clear();
    ddcCurlCache.unlock();

    Result = string("{") + jsonStr(m_CorpusName) + ":";
    if (depth != 0) {
	Result += GetSubcorpusJsonArray(Format("clear_cache %d",depth-1));
    } else {
	Result.push_back('1');
    }
    Result.push_back('}');
    m_bExpectMore = false;
}

//----------------------------------------------------------------------
void CDDCBranchServer::handle__close_socket(string &Result, SOCKET &rConnectedSocket)
{
    m_bRespond = false;
    this->Close(rConnectedSocket);
}

//==============================================================================
// local methods

//----------------------------------------------------------------------
void CDDCBranchServer::RunDistributed()
{
    CRunQueryData &runq             = m_QueryData;
    CFirstHitsQueryResult& FHResult = m_FHResult;

    //-- timeout maintainence
    DDCTime t0 = DDCTime::Now();
    
    //-- get hit sort-keys and trim to selected range
    NetworkErrorsEnum rc = RunGetFirstHits();
    if (FHResult.m_InternalError != errNone)
	throw CExpc(FHResult.m_InternalError);
    else if (rc != neSuccess)
	throw CExpc(errRuntime, GetNetworkErrorString(rc));
    
    //-- check timeout
    if  (runq.TimeOut >= 0) {
	DDCTime t1    = DDCTime::Now();
	runq.TimeOut -= DDCTime::Now().Elapsed(t0);
	if (runq.TimeOut < 0) {
	    // AS: if the previous steps took all time we add 10 seconds in order to retrieve at least some results 
	    runq.TimeOut = 10;
	}
    }

    //-- get full string form of selected hits
    DDCFormatTypeEnum ResultTypeE = CConcSession::GetResultFormatByString(runq.sResultFormat);

    if (IsCountSort(FHResult.m_SortOrder)) {
	//-- count-query can generate strings immediately
	GetHitCounts(FHResult, ResultTypeE, runq.ResponseBody);
	runq.HitsCount = FHResult.m_AllHitsCount;
	FHResult.m_HitsDistributionStr.insert(FHResult.m_HitsDistributionStr.size()-2, Format("~%d", runq.HitsCount));
	runq.HitsKey = "counts_";
    } else {
	//-- context-query must retrieve full hit strings
	GetHitContexts(FHResult, runq.sResultFormat, ResultTypeE, runq.PossibleHosts, runq.iInternalError, runq.TimeOut, runq.ResponseBody);
	runq.HitsKey = "hits_";
    }

    CConcSession::DecorateQueryResults(runq.sResultFormat, runq.ResponseBody);
    if (ResultTypeE == DDC_ResultText) {
	// AS: we always write relevant document numbers (RelevantDocsDistributionStr) to output, 
	//     even though it is not specified in the option file of the corpus threads.
	//     The problem is, that daemon doesn't know anything about options files of their corpus threads.
	runq.ResponseBody = FHResult.m_HitsDistributionStr + FHResult.m_RelevantDocsDistributionStr + runq.ResponseBody;
    }
    runq.HitDistrib = FHResult.m_HitsDistributionStr.substr(21,FHResult.m_HitsDistributionStr.size()-23);
    runq.DocDistrib = FHResult.m_RelevantDocsDistributionStr.substr(32,FHResult.m_RelevantDocsDistributionStr.size()-34);
    runq.EndHitNo   = runq.StartHitNo + FHResult.m_Hits.size();
    
    runq.iNetworkError = neSuccess;
}


//----------------------------------------------------------------------
NetworkErrorsEnum CDDCBranchServer::RunDistributed(string Query,
						   const string& ResultType,
						   DWORD StartHitNo,
						   DWORD ResultLimit,
						   int&  InternalError,
						   DWORD&  EndHitNo,
						   DWORD&  HitsCount,
						   int     TimeOut,
						   string& ResultString,
						   DWORD&  RelevantDocsCount,
						   string& HitDistrib,
						   string& DocDistrib,
						   string& HitsKey)
{
    CRunQueryData& runq = m_QueryData;
    runq.Init(Query, ResultType, StartHitNo, ResultLimit, TimeOut, &m_ErrorStr);

    RunDistributed();

    InternalError = runq.iInternalError;
    EndHitNo = runq.EndHitNo;
    HitsCount = runq.HitsCount;
    ResultString = runq.ResponseBody;
    RelevantDocsCount = runq.RelevantDocsCount;
    HitDistrib = runq.HitDistrib;
    DocDistrib = runq.DocDistrib;
    HitsKey = runq.HitsKey;
    return (NetworkErrorsEnum)runq.iNetworkError;
}

//----------------------------------------------------------------------
NetworkErrorsEnum CDDCBranchServer::RunGetFirstHits()
{
    CRunQueryData &runq             = m_QueryData;
    CFirstHitsQueryResult& FHResult = m_FHResult;

    string CleanQuery;
    // read "possible" hosts (e.g. user-specified hosts from query), using query where these hosts can be specified
    // PossibleHosts is an index of m_Hosts
    if (!ReadPossibleHosts(runq.sQuery, CleanQuery, runq.PossibleHosts)) {
	runq.iNetworkError = neSubcorpusNotFound;
	return (NetworkErrorsEnum)runq.iNetworkError;
    }

    runq.EndHitNo = 0;
    runq.HitsCount = 0;
    runq.ResponseBody = "";

    //-- readi first StartHiNo+ResultLimit hits from each host and store them to FHResult.m_Hits
    GetFirstHitsFromCorpora(runq.PossibleHosts, CleanQuery, runq.StartHitNo+runq.ResultLimit, runq.TimeOut, FHResult);
    runq.HitsCount = FHResult.m_AllHitsCount;
    runq.RelevantDocsCount = FHResult.m_AllRelevantDocsCount;
    runq.iInternalError = FHResult.m_InternalError;
    if (FHResult.HasErrors()) {
	FHResult.CloseSockets();
	swap(m_ErrorStr, FHResult.m_ErrorStr);
	if (FHResult.m_InternalError != errNone)
	    runq.iInternalError = FHResult.m_InternalError;
	runq.iNetworkError      = FHResult.m_NetworkError!=neSuccess ? FHResult.m_NetworkError : neInternalError;
	return (NetworkErrorsEnum)runq.iNetworkError;
    }

    //-- sorting and trimming: we need stable_sort() in order to ensure HitNo order is retained
    if (FHResult.m_SortOrder < 0) {
	//-- sort: descending
	stable_sort (FHResult.m_Hits.rbegin(), FHResult.m_Hits.rend());
    }
    else if (FHResult.m_SortOrder > 0) {
	//-- sort: ascending or counts
	stable_sort (FHResult.m_Hits.begin(), FHResult.m_Hits.end());
    }

    //-- count-query: aggregate by sort-keys
    if (IsCountSort(FHResult.m_SortOrder)) {
	FHResult.CollectCounts();
    }

#ifdef DEBUG_HIT_SORT
    for (vector<CHitToSort>::const_iterator hi=FHResult.m_Hits.begin(); hi != FHResult.m_Hits.end(); ++hi) {
	concord_daemon_log( Format("DEBUG[post-sort:order=%d]: hit[%d] = %s", FHResult.m_SortOrder, hi-FHResult.m_Hits.begin(), hi->debugStr().c_str()) );
    }
#endif

    //-- trim to requested hits
    if (runq.StartHitNo+runq.ResultLimit < FHResult.m_Hits.size())
	FHResult.m_Hits.erase(FHResult.m_Hits.begin()+runq.StartHitNo+runq.ResultLimit, FHResult.m_Hits.end());

    if (runq.StartHitNo < FHResult.m_Hits.size())
	FHResult.m_Hits.erase(FHResult.m_Hits.begin(), FHResult.m_Hits.begin()+runq.StartHitNo);
    else
	FHResult.m_Hits.clear();

#ifdef DEBUG_HIT_SORT
    for (vector<CHitToSort>::const_iterator hi=FHResult.m_Hits.begin(); hi != FHResult.m_Hits.end(); ++hi) {
	concord_daemon_log( Format("DEBUG[post-trim]: hit[%d] = %s", hi-FHResult.m_Hits.begin(), hi->debugStr().c_str()) );
    }
#endif

    return (NetworkErrorsEnum)runq.iNetworkError;
}

//----------------------------------------------------------------------
NetworkErrorsEnum CDDCBranchServer::GetHitCounts(CFirstHitsQueryResult& FHResult, DDCFormatTypeEnum ResultTypeE, string& ResultString)
{
    if (ResultTypeE == DDC_ResultHTML) {
	ResultString += "<TABLE>\n";
    }

    for (vector<CHitToSort>::const_iterator hi=FHResult.m_Hits.begin(); hi != FHResult.m_Hits.end(); hi++) {
	GenerateCountString(ResultString, ResultTypeE, hi->m_SortKeyStr, hi->m_HitNo);
	if (ResultTypeE == DDC_ResultJson) {
	    ResultString += ",\n";
	}
    }

    if (ResultTypeE == DDC_ResultJson && !FHResult.m_Hits.empty()) {
	ResultString.erase(ResultString.size()-2);
    }
    else if (ResultTypeE == DDC_ResultHTML) {
	ResultString += "</TABLE>";
    }

    FHResult.CloseSockets();
    return neSuccess;
}

//----------------------------------------------------------------------
NetworkErrorsEnum CDDCBranchServer::GetHitContexts(CFirstHitsQueryResult& FHResult,
						   const string& ResultType,
						   DDCFormatTypeEnum ResultTypeE,
						   DwordVector& PossibleHosts,
						   int&    InternalError,
						   int     TimeOut,
						   string& ResultString
						   )
{
    // create map from HostNo to  Hits, SortedHits[i] contains all reference to hits from host i in the right order
    vector<int> SortedHits[MaxSubhostsSize];
    for (size_t i=0; i < FHResult.m_Hits.size(); i++)
	SortedHits[FHResult.m_Hits[i].m_HostNo].push_back(i);


    // get strings from the hosts:
    //   Results[HostNo] - contains all hit strings in the right order
    vector<string> Results[MaxSubhostsSize];
    for (int i=0; i<PossibleHosts.size(); i++)	{
	BYTE HostNo = PossibleHosts[i]; 

	const vector<int>&  V = SortedHits[HostNo];
	string S;
	size_t FirstHitNo = (V.empty()) ? 0 : FHResult.m_Hits[V[0]].m_HitNo;
	InternalError = errNone;
	NetworkErrorsEnum Res = GetHitStringsFromOneCorpus
	    (m_Hosts[HostNo], ResultType, FirstHitNo, V.size(), TimeOut,FHResult.m_Sockets[i], InternalError, S);


	if (FHResult.HasErrors()) {
	    FHResult.CloseSockets();
	    m_ErrorStr = FHResult.m_ErrorStr;
	    return FHResult.m_NetworkError==neSuccess ? neInternalError : FHResult.m_NetworkError;
	}
	else if (InternalError != errNone) {
	    FHResult.CloseSockets();
	    m_ErrorStr = S;
	    Trim(m_ErrorStr);
	    return neInternalError;
	}


	StringTokenizer tok(S.c_str(), CDDCServer::AdditionalHitDelimiter);
	while (tok()) {
	    Results[HostNo ].push_back(tok.val());
	    if (ResultTypeE == DDC_ResultJson) {
		//-- ugly beautification for json format: we have to take apart the json strings again
		string &s = Results[HostNo].back();
		size_t p = s.rfind('}',s.npos);
		if (!s.empty() && p < s.size()-1)
		    s.erase(p+1,s.npos);
		p = s.find('{',0);
		if (!s.empty() && p > 0)
		    s.erase(0,p);
	    }
	}

	if (Results[HostNo].size() != V.size())
	    {
		FHResult.CloseSockets();
		return neProtocolError;
	    };
    };

    // create m_QueryResultStr
    for (size_t i=0; i < FHResult.m_Hits.size(); i++) {
	BYTE HostNo = FHResult.m_Hits[i].m_HostNo;
	const vector<int>&  V = SortedHits[HostNo];
	if (V.empty()) continue;
	ResultString += Results[ HostNo ][ FHResult.m_Hits[i].m_HitNo - FHResult.m_Hits[V[0]].m_HitNo ];
	if (ResultTypeE == DDC_ResultJson) {
	    //-- add hit-separating comma for json format
	    ResultString += ",\n";
	}
    }

    if (ResultTypeE == DDC_ResultJson && !ResultString.empty()) {
	//-- trim final trailing comma
	ResultString.erase(ResultString.size()-2,1);
    }

    return neSuccess;	
}

//----------------------------------------------------------------------
void CDDCBranchServer::GetFirstHitsFromCorpora(const DwordVector& PossibleHosts,
					       const string Query,
					       const DWORD  ResultLimit,
					       const int    TimeOut,
					       CFirstHitsQueryResult& Result)
{
	Result.m_Sockets.resize(PossibleHosts.size(),-1);
	Result.m_AllHitsCount = 0;
	Result.m_AllRelevantDocsCount = 0;
	Result.m_NetworkError = neSuccess;
	Result.m_InternalError = errNone;
	Result.m_SortOrder = hsoNone;
	Result.m_ErrorStr = "";
	
	for (int i=0; i<PossibleHosts.size(); i++)	
	{
		BYTE HostNo = PossibleHosts[i];
		CHost& Host = m_Hosts[HostNo];
		string strError;
		Result.m_Sockets[i] = Host.CreateAndConnectSocket(strError);
		if (Result.m_Sockets[i] == -1)
		{
			Result.m_NetworkError = neCouldNotOpenSocket;
			return;
		};
		string S = Format ("get_first_hits %s\x01%i %i", Query.c_str(), TimeOut,  ResultLimit);
		string ErrorStr;
		if (!SendString(Result.m_Sockets[i], S.c_str(), S.length(), ErrorStr)) 
		{
			ErrorMessage (Format("cannot send a string to socket %s : %s", Host.GetAddressStr().c_str(), ErrorStr.c_str() ));
			Result.m_NetworkError = neCouldNotSendData;
			return;
		};
	};

	vector<size_t>  HitsDistribution(m_Hosts.size(), 0);
	vector<size_t>  RelevantDocsDistribution(m_Hosts.size(), 0);
	for (int i=0; i<PossibleHosts.size(); i++)	
	{
		BYTE HostNo = PossibleHosts[i];
		CHost& Host = m_Hosts[HostNo];

		string S;
		Result.m_NetworkError = ReceiveString(Result.m_Sockets[i], S, TimeOut);
		if (Result.m_NetworkError != neSuccess)
		{
			concord_daemon_log ( " Cannot receive a result string from a client  " );
			return;
		};

		DWORD  CorpusHitsCount,RelevantDocumentsCount, EndHitNo;
		int iInternalError, iSort;

		if(sscanf(S.c_str(), "%i %i %i %i %i", &iInternalError, &EndHitNo, &CorpusHitsCount, &RelevantDocumentsCount, &iSort) != 5)
		{
			Result.m_NetworkError = neProtocolError;
			return;
		}
		Result.m_InternalError = (DDCErrorEnum)iInternalError;
		Result.m_AllHitsCount += CorpusHitsCount;
		HitsDistribution[HostNo] = CorpusHitsCount;
		Result.m_AllRelevantDocsCount += RelevantDocumentsCount;
		RelevantDocsDistribution[HostNo] = RelevantDocumentsCount;
		Result.m_SortOrder = (HitSortOrderEnum)iSort;
#ifdef DDC_COUNT_KEY_COMPAT
		//-- hack for transition to v2.0.38; see DDC_COUNT_KEY_COMPAT definition in ConcCommon.h
		bool isCountResult = IsCountSort(Result.m_SortOrder);
#endif

		HSDEBUG( Format("DEBUG[status:%s]=\"%s\" --> iSort=%d", Host.m_CorpusName.c_str(), S.c_str(), iSort) );

		if (Result.m_InternalError != errNone) {
			//-- sub-corpus error: look for error message
			size_t p = S.find('\n');
			if (p != S.npos) {
				Result.m_ErrorStr = S.substr(p+1);
			} else {
				Result.m_ErrorStr = "unknown error";
			}
			Result.m_NetworkError = neInternalError;
			return;
		}


		//-- read sort keys for merging sorted results (v2.0.19: always use string-sort for results)
		int f = S.find("\t");
		if (f != string::npos) {
			StringTokenizer tok(S.c_str() + f +1,"\t");
			char SortKeyBuf[ DDC_SORTKEY_MAXLEN ];
			while (tok()) {
				CHitToSort HS(HostNo);
				const char* rest = tok.val();
				int OrderId_IGNORED; //-- formerly integer sort-key Hit.m_OrderId sent by ddc < v2.0.19
				int nscanned = sscanf(rest, "%zi %i %[^\t]", &HS.m_HitNo, &OrderId_IGNORED, SortKeyBuf);

				if (nscanned < 2) {
					Result.m_NetworkError = neProtocolError;
					Result.m_ErrorStr = Format("could not parse get_first_hits result string #%zi from subcorpus `%s'",
								   Result.m_Hits.size(),
								   m_Hosts[HostNo].m_CorpusName.c_str());
					return;
				}
				else if (nscanned > 2 && strcmp(SortKeyBuf, "<empty>") != 0) {
#ifdef DDC_COUNT_KEY_COMPAT
				    //-- hack for transition to v2.0.38; see DDC_COUNT_KEY_COMPAT definition in ConcCommon.h
				    //   + trim bogus leading spaces from sort-keys from subcorpus server <=ddc v2.0.37
				    //   + it ought to be safe to leave this code in even after transition
				    if (isCountResult && SortKeyBuf[0]=='\002') {
					char *bi=SortKeyBuf, *bj=SortKeyBuf, *end=SortKeyBuf+DDC_SORTKEY_MAXLEN-1;
					for ( ; bi<end; ++bi, ++bj) {
					    *bj = *bi;
					    if (*bi=='\002' && *(bi+1)==' ')
						++bi;
					    else if (*bi=='\0')
						break;
					}
					if (bi==end) *bj = '\0';
				    }
#endif // DDC_COUNT_KEY_COMPAT
				    HS.m_SortKeyStr = SortKeyBuf;
				}

				Result.m_Hits.push_back(HS);
				HSDEBUG( Format("DEBUG[<%s]: hit = %s", Host.m_CorpusName.c_str(), Result.m_Hits.back().debugStr().c_str()) ); //-- debug
			}
		}
	}

	// collecting hits distribution in the right order for all possible corpus threads
	// the previous cycle was only for "possible" host (=user-defined corpus threads)
	Result.m_HitsDistributionStr = "Corpora Distribution:";
	Result.m_RelevantDocsDistributionStr = "Relevant Documents Distribution:";
	for (size_t i=0; i< HitsDistribution.size();  i++)
	{
		Result.m_HitsDistributionStr += Format("%i",HitsDistribution[i]);
		Result.m_RelevantDocsDistributionStr += Format("%i",RelevantDocsDistribution[i]);

		if (i+1 == HitsDistribution.size())
		{
			Result.m_HitsDistributionStr += Format("=%i;\n",Result.m_AllHitsCount);
			Result.m_RelevantDocsDistributionStr += Format("=%i;\n",Result.m_AllRelevantDocsCount);
		}
		else
		{
			Result.m_HitsDistributionStr += "+";
			Result.m_RelevantDocsDistributionStr += "+";
		};
	};
	
	Result.m_NetworkError = neSuccess;
}

//----------------------------------------------------------------------
NetworkErrorsEnum CDDCBranchServer::GetHitStringsFromOneCorpus(CHost& Host,
							       const string& ResultType,
							       DWORD StartHitNo,
							       DWORD ResultLimit,
							       int   TimeOut,
							       SOCKET& CorpusSocket,
							       int&    InternalError,
							       string& Result)
{
	string ErrorStr;
	if (CorpusSocket == -1)
		return neNetworkError;

	if (ResultLimit==0) {
	    //-- vacuous request; just close up the socket to avoid ~40ms turnaround (data from A. Barbaresi, tested kerncorpus@data)
	    this->CloseDtr(CorpusSocket);
	    InternalError = errNone;
	    Result.clear();
	    return neSuccess;
	}

	//Query\x01StartHitNo ResultLimit bGetText
	string S = Format ("get_hit_strings %s\x01%i %i",  ResultType.c_str(), StartHitNo,  ResultLimit);

	if (!SendString(CorpusSocket, S.c_str(), S.length(), ErrorStr)) 
	{
		ErrorMessage (Format("cannot send a string to socket %s : %s", Host.GetAddressStr().c_str(), ErrorStr.c_str() ));

		if (!this->CloseDtr(CorpusSocket))
			ErrorMessage (Format("cannot close socket %s", Host.GetAddressStr().c_str()));

		return neCouldNotSendData;
	};

	NetworkErrorsEnum Res = ReceiveString(CorpusSocket, S, TimeOut);
	if (!this->CloseDtr(CorpusSocket))
		ErrorMessage (Format("cannot close socket %s", Host.GetAddressStr().c_str()));

	if (Res  != neSuccess)
	{
		concord_daemon_log ( "cannot receive a result string from a client" );
		return Res;
	};

	//InternalError EndHitNo Result	
	int z = S.find('\x01');
	if ( (z == -1) || (z == 0) ) 
	{
		return neProtocolError;
	};

	Result = S.substr(z+1);
	S.erase(z, S.length() - z);
	int iInternalError;
	if(sscanf(S.c_str(), "%i", &iInternalError) != 1)
	{
		return neProtocolError;
	};
	InternalError = (DDCErrorEnum)iInternalError;

	return neSuccess;
}

//----------------------------------------------------------------------
bool CDDCBranchServer::ReadPossibleHosts(const string& InputQuery, string& CleanQuery, DwordVector& PossibleHosts)
{
    PossibleHosts.reserve(m_Hosts.size());
    int Starter;
    for (Starter  = InputQuery.length()-1;   Starter >= 0; Starter--) {
	if ((BYTE)InputQuery[Starter] == ':')
	    break;
	else if ((!is_english_alpha((BYTE)InputQuery[Starter]) && !strchr("_-1234567890,# \t", (BYTE)InputQuery[Starter]))
		 ||
		 (Starter == 0)) {
	    for (size_t i=0; i<m_Hosts.size(); i++)
		PossibleHosts.push_back(i);
	    CleanQuery = InputQuery;
	    return true;
	}
    }
    assert (Starter != string::npos);

    string s = InputQuery.substr(Starter+1);
    Trim(s);
    if (s.empty()) return false;
    StringTokenizer tok(s.c_str(),", ");
    while (tok()) {
	string CorpusName = tok.val();
	size_t j=0;
	for (; j<m_Hosts.size(); j++) {
	    if (m_Hosts[j].m_CorpusName == CorpusName)
		break;
	}
	if (j == m_Hosts.size()) {
	    m_ErrorStr = Format("subcorpus `%s' not found", CorpusName.c_str());
	    return false;
	}
	PossibleHosts.push_back(j);
    }

    CleanQuery = InputQuery.substr(0, Starter);
    if (PossibleHosts.size() >= MaxSubhostsSize) {
	m_ErrorStr = Format("requested subcorpus set too large (%u >= %u)", PossibleHosts.size(), MaxSubhostsSize);
	return false;
    }
    return true;
}


//----------------------------------------------------------------------
string CDDCBranchServer::GetSubcorpusJsonArray(const string& request, int timeout)
{
	vector<string> Results(m_Hosts.size());
	vector<SOCKET> Sockets(m_Hosts.size(), -1);
	size_t i;
	string errorStr;
	if (timeout==0) timeout=10; //-- default timeout

	//-- send requests
	for (i=0; i < m_Hosts.size(); ++i) {
		CHost &Host = m_Hosts[i];

		//-- open socket
		errorStr.clear();
		try {
		    SOCKET sock = Host.CreateAndConnectSocket(errorStr);
		    if (sock == -1 || !errorStr.empty()) {
			Results[i] = Format("{\"name\":%s,\"error\":\"could not open socket: %s\"}", jsonStr(Host.m_CorpusName).c_str(), jsonStr(errorStr, true, false).c_str());
			continue;
		    }

		    //-- send request
		    if (!SendString(sock, request, errorStr) || !errorStr.empty()) {
			this->CloseDtr(sock);
			Results[i] = Format("{\"name\":%s,\"error\":\"could not send to socket: %s\"}", jsonStr(Host.m_CorpusName).c_str(), jsonStr(errorStr, true, false).c_str());
			continue;
		    }

		    //-- store socket
		    Sockets[i] = sock;
		}
		catch (exception &e) {
		    Results[i] = Format("{\"name\":%s,\"error\":\"error sending to socket: %s\"}", jsonStr(Host.m_CorpusName).c_str(), jsonStr(e.what(), true, false).c_str());
		    continue;
		}
		catch (...) {
		    Results[i] = Format("{\"name\":%s,\"error\":\"error sending to socket\"}", jsonStr(Host.m_CorpusName).c_str());
		    continue;
		}

	}

	//-- read responses
	for (i=0; i < m_Hosts.size(); ++i) {
		if (Sockets[i] == -1 || !Results[i].empty())
			continue;

		//-- read response
		try {
		    if (ReceiveString(Sockets[i], Results[i], timeout) != neSuccess) {
			Results[i] = Format("{\"name\":%s,\"error\":\"failed to read response data from socket\"}", jsonStr(m_Hosts[i].m_CorpusName).c_str());
		    }
		}
		catch (exception &e) {
		    Results[i] = Format("{\"name\":%s,\"error\":\"error reading response data from socket: %s\"}", jsonStr(m_Hosts[i].m_CorpusName).c_str(), jsonStr(e.what(),true,false).c_str());
		}
		catch (...) {
		    Results[i] = Format("{\"name\":%s,\"error\":\"error reading response data from socket\"}", jsonStr(m_Hosts[i].m_CorpusName).c_str());
		}

		//-- close socket (forgetting this causes an fd-leak resulting in "Could not create socket: Too many open files for HOST:PORT" messages later)
		this->CloseDtr(Sockets[i]);
	}

	//-- build result
	string Result("[");
	for (i=0; i < m_Hosts.size(); ++i) {
		if (i!=0) Result += ',';
		Result += string("\n\t") + (Results[i].empty() ? "null" : Results[i]);
	}
	Result += "\n]";
	return Result;
}
