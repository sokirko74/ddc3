//-*- Mode: C++ -*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2020 by Bryan Jurish
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

//==============================================================================
// debugging

//#define DEBUG_SERVER_THREADS 1
#undef DEBUG_SERVER_THREADS

#define DEEP_HINTS 1

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
    m_DtrEnds.clear();
    m_Sockets.clear();
    m_Offset = 0;
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
CDDCBranchServer::CDDCBranchServer(bool master)
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
        m_noLogCommands.insert("get_first_hits");
        m_noLogCommands.insert("get_hit_strings");
        m_noLogCommands.insert("ddc_close_socket");
    }

    //-- initialize navigation cache (master only; capacity will typically be overridden by server options)
    if (master) {
        m_pNavCache = new NavHintCache(DDC_DEFAULT_NAV_HINT_CACHE_CAPACITY);
    } else {
        m_pNavCache = NULL;
    }
    m_NavCacheStep = DDC_DEFAULT_NAV_HINT_CACHE_STEP;

    m_bHitStringsParallel = false;
};

//----------------------------------------------------------------------
CDDCBranchServer::~CDDCBranchServer()
{
    if (m_pNavCache) delete m_pNavCache;
};

//----------------------------------------------------------------------
void CDDCBranchServer::SetOptions(const CDDCServerOptions &Options)
{
    CDDCServer::SetOptions(Options);
    if (m_pNavCache) {
        ddcLogInfo(Format("setting branch navigation cache capacity = %zd", Options.m_NavCacheSize));
        m_pNavCache->reserve(Options.m_NavCacheSize);
    }
    m_NavCacheStep = Options.m_NavCacheStep;
    m_bHitStringsParallel = Options.m_bHitStringsParallel;
};

//----------------------------------------------------------------------
void CDDCBranchServer::Shutdown()
{
    ddcLogInfo(Format("shutting down branch server %s", m_CorpusName.c_str()));
    for (size_t i=0; i < m_Hosts.size(); i++) {
        m_Hosts[i].CloseListenSocket();
    }
    CloseListenSocket();
};

//==============================================================================
// CDDCBranchServer: client threads

//----------------------------------------------------------------------
void CDDCBranchServer::WorkerCloneInit(const CDDCServer *Parent, size_t WorkerId)
{
    CDDCServer::WorkerCloneInit(Parent,WorkerId);

    CDDCBranchServer *parent = (CDDCBranchServer*)Parent;
    m_Hosts = parent->m_Hosts;
    m_pNavCache = parent->m_pNavCache;
    m_bHitStringsParallel = parent->m_bHitStringsParallel;
}

//----------------------------------------------------------------------
void CDDCBranchServer::WorkerCloneFree(void)
{
    m_pNavCache = NULL;
    CDDCServer::WorkerCloneFree();
}

//==============================================================================
// CHostSubcorpora

//----------------------------------------------------------------------
void CSelectedHosts::Clear()
{
    ClearVector(m_vec);
    ClearContainer(m_map);
}

//----------------------------------------------------------------------
void CSelectedHosts::Insert(DWORD HostId, const string& SubPath)
{
    if (SubPath.empty()) {
        Insert(HostId,"*");
        return;
    }

    if (m_map.find(HostId) == m_map.end())
        m_vec.push_back(HostId);
    m_map[HostId].insert(SubPath);
}

//----------------------------------------------------------------------
void CSelectedHosts::InsertAll(DWORD nDtrs, const string &SubPath)
{
    m_vec.clear();
    m_vec.reserve(nDtrs);
    for (DWORD di=0; di<nDtrs; ++di) {
        Insert(di, SubPath);
    }
}

//----------------------------------------------------------------------
string CSelectedHosts::DtrPaths(DWORD HostId) const
{
    string paths;
    MapT::const_iterator mapi = m_map.find(HostId);
    if (mapi == m_map.end())
        return paths;

    paths.push_back(':');
    for (set<string>::const_iterator pi=mapi->second.begin(); pi != mapi->second.end(); ++pi) {
        if (*pi == "*") {
            paths.clear();
            break;
        }
        if (pi != mapi->second.begin()) paths.push_back(',');
        paths += sqString(*pi);
    }
    if (paths.size()==1)
        paths.clear();
    return paths;
}

//----------------------------------------------------------------------
string CSelectedHosts::toString() const
{
    string s("{\n");
    s += " \"m_vec\":[";
    for (VecT::const_iterator vi=m_vec.begin(); vi != m_vec.end(); ++vi) {
        if (vi != m_vec.begin()) s += ", ";
        s += Format("%d", *vi);
    }
    s += "],\n";

    s += " \"m_map\":{\n";
    for (MapT::const_iterator mi=m_map.begin(); mi != m_map.end(); ++mi) {
        if (mi != m_map.begin()) s += ",\n\t";
        s += Format("%d:[", mi->first);
        for (set<string>::const_iterator mvi=mi->second.begin(); mvi!=mi->second.end(); ++mvi) {
            if (mvi != mi->second.begin()) s += ", ";
            s += jsonStr(*mvi);
        }
        s += "]";
    }
    s += " }\n";
    
    s += "}\n";
    return s;
}


//==============================================================================
// CRunQueryData

//----------------------------------------------------------------------
void CRunQueryData::Init(const string & _Query, const string& _ResultFormat, size_t _Start, size_t _Limit, int _TimeOut, string *_pErrorStr, const NavHint& _Hint)
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

    navKey.assign(sQuery,StartHitNo);
    navHint = _Hint;
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
    SelectedHosts.Clear();
    HitDistrib.clear();
    DocDistrib.clear();
    HitsKey = "hits_";
    ClearString(ResponseBody);
    pErrorStr = NULL;
    navKey.clear();
    navHint.clear();
}

//----------------------------------------------------------------------
void CRunQueryData::toString(string &Response, size_t WorkerId, const DDCVersionT& vCompat)
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
                    + (vCompat >= DDCVersionT(2,1,9)
                       ? (string(",\"hint_\":") + jsonStr(navHint.toString()))
                       : "")
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
void CDDCBranchServer::handle__get_first_hits(string &Result, const char *Query, int TimeOut, size_t ResultLimit, const NavHint& Hint)
{
    CRunQueryData &runq = m_QueryData;
    CFirstHitsQueryResult& FHResult = m_FHResult;
    runq.Init(Query, "", Hint.m_Offset, ResultLimit, TimeOut, &m_ErrorStr, Hint);

    NetworkErrorsEnum rc = RunGetFirstHits();
    CheckFirstHitsResult(rc);
    
    //-- adapted from CDDCLeafServer::handle__get_first_hits(), CConcSession::GetHitIds()
    Result = Format ("%i %zi %zi %zi %i", FHResult.m_InternalError, runq.EndHitNo, FHResult.m_AllHitsCount, FHResult.m_AllRelevantDocsCount, FHResult.m_SortOrder);
    char buf[32];
    size_t beg = FHResult.PhysicalOffset(runq.StartHitNo);
    size_t end = FHResult.PhysicalMax(runq.StartHitNo+runq.ResultLimit);

    if (IsCountSort(FHResult.m_SortOrder)) {
        //-- count-query requires special formatting, but can return immediately (respecting m_Offset)
        for (size_t phi=beg; phi < end; ++phi) {
            const CHitToSort &h = FHResult.m_Hits[phi];
            sprintf(buf, "\t%zd -0 ", h.m_HitNo); //-- hi->m_HitNo is really the hit-count
            Result += buf;
            Result += h.m_SortKeyStr;
        }
        m_bExpectMore = false;
    }
    else {
        //-- context query: just return hit keys (respecting m_Offset)
        for (size_t phi=beg; phi < end; ++phi) {
            const CHitToSort &h = FHResult.m_Hits[phi];
            sprintf(buf, "\t%zd -0 ", FHResult.LogicalOffset(phi));
            Result += buf;
            Result += FHResult.m_Hits[phi].m_SortKeyStr;
        }
        m_bExpectMore = true;
    }

    return;
}

//----------------------------------------------------------------------
void CDDCBranchServer::handle__get_hit_strings(string &Result, const char *ResultType, size_t StartHitNo, size_t ResultLimit)
{
    CRunQueryData &runq = m_QueryData;
    CFirstHitsQueryResult& FHResult = m_FHResult;

    //-- sanity check(s)
    if (FHResult.m_HitsDistributionStr.empty())
        throw CExpc(errRuntime, "CDDCBranchServer::handle__get_hit_strings(): FHResult is uninitialized!");
    if (StartHitNo < runq.StartHitNo)
        throw CExpc(errRuntime, "CDDCBranchServer::handle__get_hit_strings(): requested StartHitNo=%zi < cached=%zi", StartHitNo, runq.StartHitNo);
    if (ResultLimit > runq.ResultLimit)
        throw CExpc(errRuntime, "CDDCBranchServer::handle__get_hit_strings(): requested ResultLimit=%zd > cached=%zi", ResultLimit, runq.ResultLimit);
    if (StartHitNo > runq.StartHitNo+runq.ResultLimit) {
        //-- oops: someone a start-offset beyond what we can legitimately return: massage it (as LeafServer does)
        StartHitNo = runq.StartHitNo+runq.ResultLimit;
    }
    if (StartHitNo+ResultLimit > runq.StartHitNo+runq.ResultLimit) {
        //-- oops: someone requested more hits than we can legitimately return: massage it (as LeafServer does)
        ResultLimit  = runq.StartHitNo+runq.ResultLimit - StartHitNo;
    }

    //-- guts
    runq.sResultFormat = ResultType;
    runq.StartHitNo    = StartHitNo;
    runq.ResultLimit   = ResultLimit;

    //-- get full string form of selected hits
    DDCFormatTypeEnum ResultTypeE = CConcSession::GetResultFormatByString(runq.sResultFormat);

    if (IsCountSort(FHResult.m_SortOrder)) {
        //-- count-query can generate strings immediately
        GetHitCounts(FHResult, ResultTypeE, runq.ResponseBody);
        runq.HitsCount = FHResult.m_AllHitsCount;
        FHResult.m_HitsDistributionStr.insert(FHResult.m_HitsDistributionStr.size()-2, Format("~%d", runq.HitsCount));
        runq.HitsKey = "counts_";
        runq.navHint.clear();
    } else {
        //-- context-query must retrieve full hit strings (side-effect: updates runq.navKey, runq.navHint)
        GetHitContexts(FHResult, runq.sResultFormat, ResultTypeE, runq.SelectedHosts, runq.iInternalError, runq.TimeOut, runq.ResponseBody);
        runq.HitsKey = "hits_";
    }

    //-- check for errors
    if (runq.iInternalError != (int)errNone) {
        if (!m_ErrorStr.empty())
            throw CExpc(runq.iInternalError,m_ErrorStr);
        else
            throw CExpc(runq.iInternalError);
    } else if (runq.iNetworkError != (int)neSuccess) {
        throw CExpc(errRuntime, GetNetworkErrorString((NetworkErrorsEnum)runq.iNetworkError));
    }

    //-- format result
    if (ResultTypeE == DDC_ResultJson) {
        //-- JSON mode: munge in JSON syntax
        StringTokenizer tok(runq.ResponseBody.c_str(), "\n");
        Result.reserve(6+runq.ResponseBody.size()+FHResult.LogicalSize(runq.StartHitNo, runq.ResultLimit));

        Result = "0";
        if (m_VersionCompat >= DDCVersionT(2,1,9)) {
            //-- compat >= v2.1.9: include local offset hint for next page
            Result.push_back(' ');
            Result += runq.navHint.toString(false);
            Result.push_back('\n');
        }
        Result += "\x01[";

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
    runq.EndHitNo   = FHResult.LogicalMax(runq.StartHitNo + runq.ResultLimit);
    runq.iNetworkError = neSuccess;

    UpdateNavCache();
    m_bExpectMore = false;
}

//----------------------------------------------------------------------
void CDDCBranchServer::handle__run_query(string &Result, const char *CorpusName, const char *Query, const char *ResultType, size_t StartHitNo, size_t ResultLimit, int TimeOut, const NavHint &Hint)
{
    CRunQueryData& runq = m_QueryData;
    runq.Init(Query, ResultType, StartHitNo, ResultLimit, TimeOut, &m_ErrorStr, Hint);
    
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
    pid_t  pid = getpid();
    DDCProcessMemoryStatus pms(pid);
    size_t nfd = GetNumberOfOpenFiles(pid);

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

    //-- synchronize moving-average query-time window (EMA decay)
    m_ServerStats.m_qTimes.Scrub();
    m_ServerStats.m_xTimes.Scrub();

    Result = (string("{\n")
              + "\"name\":" + jsonStr(m_CorpusName) + ",\n"
              + "\"version\":" + jsonStr(PACKAGE_VERSION) + ",\n"
              + "\"compat\":" + jsonStr(m_VersionCompat.str()).c_str() + ",\n"
              + "\"hostname\":" + jsonStr(m_FQHostName) + ",\n"
              + "\"hostaddr\":" + jsonStr(m_SockAddr.m_Addr) + ",\n"
              + "\"port\":" + Format("%d", m_SockAddr.m_Port) + ",\n"
              + "\"sockaddr\":" + jsonStr(GetAddressStr()) + ",\n"              
              + "\"started\":" + jsonStr(timestampUTC(m_tStarted)) + ",\n"
              + "\"uptime\":" + Format("%.0f", uptime) + ",\n"
              + "\"nrequests\":" + Format("%zd", m_ServerStats.m_nRequests) + ",\n"
              + "\"nqueries\":" + Format("%zd", m_ServerStats.m_nQueries) + ",\n"
              + "\"nexpand\":" + Format("%zd", m_ServerStats.m_nExpand) + ",\n"       
              + "\"nerrors\":" + Format("%zd", m_ServerStats.m_nErrors) + ",\n"
              + "\"nslow\":" + Format("%zd", m_ServerStats.m_nSlow) + ",\n"
              + "\"qtavg\":" + Format("%g", m_ServerStats.m_qTimes.Average()) + ",\n" //-- pseudo-compat
              + "\"qtavgs\":" + m_ServerStats.m_qTimes.toJsonArray() + ",\n"
              + "\"xtavg\":" + Format("%g", m_ServerStats.m_xTimes.Average()) + ",\n" //-- pseudo-compat
              + "\"xtavgs\":" + m_ServerStats.m_xTimes.toJsonArray() + ",\n"
              + "\"nworkers\":" + Format("%zd", m_nWorkers) + ",\n"
              + "\"hitstrings\":\"" + (m_bHitStringsParallel ? "parallel" : "serial") + "\",\n"
              + "\"navcachesize\":" + Format("%zd", (m_pNavCache ? m_pNavCache->size() : 0)) + ",\n"
              + "\"navcachestep\":" + Format("%zd", m_NavCacheStep) + ",\n"
              + "\"memkb\":" + Format("%zd", pms.VmRSS) + ",\n" //-- compat           
              + "\"vmem\":" + Format("{\"peak\":%zd,\"size\":%zd,\"hwm\":%zd,\"rss\":%zd,\"data\":%zd,\"stk\":%zd,\"exe\":%zd,\"lib\":%zd,\"swap\":%zd,\"file\":%zd,\"anon\":%zd}",
                                     pms.VmPeak, pms.VmSize, pms.VmHWM, pms.VmRSS, pms.VmData, pms.VmStk, pms.VmExe, pms.VmLib, pms.VmSwap, pms.RssFile, pms.RssAnon) + ",\n"
              + "\"nfd\":" + Format("%zd", nfd) + ",\n"
#ifdef DEBUG_NAVCACHE
              + "\"navcache\":" + (m_pNavCache ? m_pNavCache->toJson() : "null") + ",\n"
#endif
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

    if (m_pNavCache) m_pNavCache->clear();

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
    DDCTimeHiRes t0 = DDCTimeHiRes::Now();
    
    //-- get hit sort-keys and trim to selected range
    NetworkErrorsEnum rc = RunGetFirstHits(); //-- runq.navHint should already have been initialized
    CheckFirstHitsResult(rc);
    
    //-- check timeout
    if  (runq.TimeOut >= 0) {
        double elapsed  = DDCTimeHiRes::Now().Elapsed(t0);
        if (elapsed >= runq.TimeOut) {
            // AS: if the previous steps took all time we add 10 seconds in order to retrieve at least some results 
            runq.TimeOut = 10;
        } else {
            // moo: timeout not yet expired; adjust it using clunky integer resolution
            runq.TimeOut -= (elapsed+0.5);
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
        runq.navHint.clear();
    } else {
        //-- context-query must retrieve full hit strings (and update runq.navKey, runq.navHint)
        GetHitContexts(FHResult, runq.sResultFormat, ResultTypeE, runq.SelectedHosts, runq.iInternalError, runq.TimeOut, runq.ResponseBody);
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
    runq.EndHitNo   = FHResult.LogicalMax(runq.StartHitNo + runq.ResultLimit);

    UpdateNavCache();
    runq.iNetworkError = neSuccess;
}


//----------------------------------------------------------------------
NetworkErrorsEnum CDDCBranchServer::RunDistributed(string Query,
                                                   const string& ResultType,
                                                   size_t StartHitNo,
                                                   size_t ResultLimit,
                                                   int&  InternalError,
                                                   size_t&  EndHitNo,
                                                   size_t&  HitsCount,
                                                   int     TimeOut,
                                                   string& ResultString,
                                                   size_t&  RelevantDocsCount,
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
    // SelectedHosts maps Host-IDs to selected sub-subcpora
    if (!ReadSelectedHosts(runq.sQuery, CleanQuery, runq.SelectedHosts)) {
        runq.iNetworkError = neSubcorpusNotFound;
        return (NetworkErrorsEnum)runq.iNetworkError;
    }
    //ddcLogTrace("DEBUG: SelectedHosts = " + runq.SelectedHosts.toString());

    runq.EndHitNo = 0;
    runq.HitsCount = 0;
    runq.ResponseBody = "";
    FHResult.Clear();

    //-- get cached navigation hint if available and not supplied by user
    if (runq.navHint.empty() && m_pNavCache) {
        m_pNavCache->lower_bound(runq.navHint, runq.navKey, false);     //-- navigation hint: from cache (NOT auto-promoted here)
    }
    NAVCACHE_DEBUG(ddcLogDebug(Format("initialized runq.navHint=%s", runq.navHint.toJson().c_str())));

    //-- read first StartHitNo+ResultLimit hits from each host and store them to FHResult.m_Hits
    GetFirstHitsFromCorpora(runq.SelectedHosts, CleanQuery, runq.StartHitNo, runq.ResultLimit, runq.TimeOut, FHResult);
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
    if (runq.SelectedHosts.size() > 1) {
        if (FHResult.m_SortOrder < 0) {
            //-- sort: descending
            stable_sort (FHResult.m_Hits.rbegin(), FHResult.m_Hits.rend());
        }
        else if (FHResult.m_SortOrder > 0) {
            //-- sort: ascending or counts
            stable_sort (FHResult.m_Hits.begin(), FHResult.m_Hits.end());
        }
    }

    //-- count-query: aggregate by sort-keys (pre-trim)
    if (IsCountSort(FHResult.m_SortOrder)) {
        FHResult.CollectCounts();
    }

    HIT_SORT_DEBUG(
        for (vector<CHitToSort>::const_iterator hi=FHResult.m_Hits.begin(); hi != FHResult.m_Hits.end(); ++hi) {
            concord_daemon_log( Format("DEBUG[post-sort:order=%d]: hit[%d] = %s", FHResult.m_SortOrder, hi-FHResult.m_Hits.begin(), hi->debugStr().c_str()) );
        });
    
    //-- sanity check
    if (FHResult.m_Offset > runq.StartHitNo)
        throw CExpc("navigation cache error: daughters over-pruned (FHResult.Offset=%zd > StartHitNo=%i)", FHResult.m_Offset, runq.StartHitNo);

#ifdef DEBUG_HIT_SORT
    for (size_t physi=FHResult.PhysicalOffset(runq.StartHitNo); physi < FHResult.PhysicalMax(runq.StartHitNo+runq.ResultLimit); ++physi) {
        const CHitToSort &h = FHResult.m_Hits[physi];
        concord_daemon_log( Format("DEBUG[pseudo-trim]: hit[%zd~%zd] = %s", physi,FHResult.LogicalOffset(physi), h.debugStr().c_str()) );
    }
#endif

    //-- update runq.EndHitNo for get_first_hits requests
    runq.EndHitNo = FHResult.LogicalMax(runq.StartHitNo+runq.ResultLimit);
    
    return (NetworkErrorsEnum)runq.iNetworkError;
}

//----------------------------------------------------------------------
void CDDCBranchServer::CheckFirstHitsResult(NetworkErrorsEnum networkError)
{
    CFirstHitsQueryResult& FHResult = m_FHResult;

    if (FHResult.m_InternalError != errNone) {
        if (!m_ErrorStr.empty())
            throw CExpc(FHResult.m_InternalError, m_ErrorStr);
        else if (!FHResult.m_ErrorStr.empty())
            throw CExpc(FHResult.m_InternalError, FHResult.m_ErrorStr);
        else
            throw CExpc(FHResult.m_InternalError);
    }
    else if (FHResult.m_NetworkError != neSuccess) {
        throw CExpc(errRuntime, GetNetworkErrorString(FHResult.m_NetworkError));
    }
    else if (networkError != neSuccess) {
        throw CExpc(errRuntime, GetNetworkErrorString(networkError));
    }
}

//----------------------------------------------------------------------
NetworkErrorsEnum CDDCBranchServer::GetHitCounts(CFirstHitsQueryResult& FHResult, DDCFormatTypeEnum ResultTypeE, string& ResultString)
{
    if (ResultTypeE == DDC_ResultHTML) {
        ResultString += "<TABLE>\n";
    }

    const CRunQueryData& runq = m_QueryData;
    size_t beg = FHResult.PhysicalOffset(runq.StartHitNo);
    size_t end = FHResult.PhysicalMax(runq.StartHitNo+runq.ResultLimit);
    for (size_t phi=beg; phi < end; ++phi) {
        const CHitToSort &h = FHResult.m_Hits[phi];
        GenerateCountString(ResultString, ResultTypeE, h.m_SortKeyStr, h.m_HitNo);
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
void CDDCBranchServer::UpdateNavCache()
{
    CRunQueryData &runq = m_QueryData;
    CFirstHitsQueryResult& FHResult = m_FHResult;

    //-- update nav cache
    if (m_pNavCache && !IsCountSort(FHResult.m_SortOrder) && runq.SelectedHosts.size()==m_Hosts.size()) {

        //-- minimize cache turnover: check for cached hint within m_NavCacheStep range
        //   (if we've got one close enough, we don't need to insert a new hint)
        NavHint cacheHint(m_Hosts.size());
        m_pNavCache->lower_bound(cacheHint, runq.navKey, true);
        if ((runq.navHint.m_Offset - cacheHint.m_Offset) >= m_NavCacheStep) {
            //-- no cached hint, or the offset increment exceeds m_NavCacheStep: really update the cache
            m_pNavCache->insert(runq.navKey, runq.navHint);
        }
    }
    NAVCACHE_DEBUG(
        //ddcLogDebug(Format("NAVCACHE: FHR.Offset=%zd ; FHR.nHits=%zd", FHResult.m_Offset, FHResult.m_Hits.size()));
        ddcLogDebug(Format("NAVCACHE: update Key=%s => Hint=%s", runq.navKey.toJson().c_str(), runq.navHint.toJson().c_str()));
        ddcLogDebug(string("NAVCACHE: cache=") + m_pNavCache->toJson());
        );
}

//----------------------------------------------------------------------
NetworkErrorsEnum CDDCBranchServer::SendGetHitStringsRequest(BYTE SelectedHostNo, const vector< vector<size_t> >& SortedHits, const vector<size_t>& FirstOffsets, const string& ResultType)
{
    BYTE HostNo              = m_QueryData.SelectedHosts.m_vec[SelectedHostNo];
    SOCKET&     CorpusSocket = m_FHResult.m_Sockets[SelectedHostNo];
    const vector<size_t>& V  = SortedHits[HostNo];
    size_t FirstHitNo        = (V.empty()) ? FirstOffsets[HostNo] : m_FHResult.m_Hits[V[0]].m_HitNo;
    string ErrorStr;

    if (CorpusSocket == -1)
        return neNetworkError;

    string Req = Format ("get_hit_strings %s\x01%zi %zi",  ResultType.c_str(), FirstHitNo,  V.size());
    if (!SendString(CorpusSocket, Req, ErrorStr))  {
        ErrorMessage(Format("cannot send a string to socket %s : %s", m_Hosts[HostNo].GetAddressStr().c_str(), ErrorStr.c_str() ));
        if (!this->CloseDtr(CorpusSocket))
            ErrorMessage (Format("cannot close socket %s", m_Hosts[HostNo].GetAddressStr().c_str()));

        return neCouldNotSendData;
    }
    return neSuccess;
};

//----------------------------------------------------------------------
NetworkErrorsEnum CDDCBranchServer::GetHitContexts(CFirstHitsQueryResult& FHResult,
                                                   const string& ResultType,
                                                   DDCFormatTypeEnum ResultTypeE,
                                                   CSelectedHosts& SelectedHosts,
                                                   int&    InternalError,
                                                   int     TimeOut,
                                                   string& ResultString
    )
{
    CRunQueryData &runq   = m_QueryData;
    
    // create map from HostNo to  Hits, SortedHits[i] contains all physical offsets of hits to return from host i in the correct order
    vector< vector<size_t> > SortedHits(m_Hosts.size());
    size_t beg = FHResult.PhysicalOffset(runq.StartHitNo);
    size_t end = FHResult.PhysicalMax(runq.StartHitNo+runq.ResultLimit);
    for (size_t i=beg; i < end; ++i)
        SortedHits[FHResult.m_Hits[i].m_HostNo].push_back(i);

    //-- hint-scan: scan for correct get_hit_strings offsets
    vector<size_t> FirstOffsets(m_Hosts.size(),SIZE_MAX);
    size_t nFirstOffsets = 0;
    //-- hint-scan: branch-level result set (easy answer)
    for (size_t i=0; i < SelectedHosts.size(); i++) {
        if (SortedHits[i].empty()) continue;
        FirstOffsets[i] = FHResult.m_Hits[SortedHits[i][0]].m_HitNo;
        ++nFirstOffsets;
    }
    //-- hint-scan: back-trimmed hits
    if (nFirstOffsets < SelectedHosts.size()) {
        for (size_t phi=end; phi < FHResult.m_Hits.size(); ++phi) {
            const CHitToSort &h = FHResult.m_Hits[phi];
            if (FirstOffsets[h.m_HostNo] != SIZE_MAX) continue;
            FirstOffsets[h.m_HostNo] = h.m_HitNo;
            if (++nFirstOffsets >= SelectedHosts.size()) break;
        }
    }
    //-- hint-scan: other (front-trimmed or no-hits)
    if (nFirstOffsets < SelectedHosts.size()) {
        for (size_t i=0; i < SelectedHosts.size(); i++) {
            if (FirstOffsets[i] != SIZE_MAX) continue;
            FirstOffsets[i] = FHResult.m_DtrEnds[i];
        }
    }
   

    // navHint caching
    runq.navKey.m_HitNo   = min(FHResult.LogicalOffset(end), FHResult.m_AllHitsCount);
    runq.navHint.m_Offset = runq.navKey.m_HitNo;
    runq.navHint.m_DtrHints.assign(m_Hosts.size(), "");
    if (beg < end)
        runq.navHint.m_SortKey = FHResult.m_Hits[end-1].m_SortKeyStr;
    NAVCACHE_DEBUG( ddcLogDebug(Format("GetHitContexts(): FHR.LEnd=%zd FHR.Count=%zd --> navKey.HitNo=%zd", FHResult.LogicalOffset(end), FHResult.m_AllHitsCount, runq.navKey.m_HitNo)) );

    // get strings from the hosts: paralell mode
    if (m_bHitStringsParallel) {
        NetworkErrorsEnum reqrc;
        for (size_t i=0; i < SelectedHosts.size(); ++i) {
            if ((reqrc=SendGetHitStringsRequest(i, SortedHits, FirstOffsets, ResultType)) != neSuccess)
                return reqrc;
        }
    }

    //-- get_hit_strings: serial mode / read responses
    //   Results[HostNo] - contains all hit strings in the right order
    vector<vector<string> > Results(m_Hosts.size());
    for (size_t i=0; i<SelectedHosts.size(); i++) {
        BYTE HostNo = SelectedHosts.m_vec[i]; 
        const vector<size_t>&  V = SortedHits[HostNo];

        if (!m_bHitStringsParallel) {
            //-- serial mode: send request
            NetworkErrorsEnum reqrc = SendGetHitStringsRequest(i, SortedHits, FirstOffsets, ResultType);
            if (reqrc != neSuccess) return reqrc;
        }
        
        string S, dtrHint;
        size_t FirstHitNo = (V.empty()) ? FirstOffsets[HostNo] : FHResult.m_Hits[V[0]].m_HitNo;
        InternalError = errNone;
        NetworkErrorsEnum Res = GetHitStringsFromOneCorpus
            (m_Hosts[HostNo], ResultType, FirstHitNo, V.size(), TimeOut,FHResult.m_Sockets[i], InternalError, S, dtrHint);
        //-- should we be checking for (Res != neSuccess) here?

        NAVCACHE_DEBUG(ddcLogDebug(Format("GetHitContexts[host=%d]: Hint=`%s'", HostNo, dtrHint.c_str())));
        if (!dtrHint.empty()) runq.navHint.m_DtrHints[HostNo].swap(dtrHint);
            
        if (FHResult.HasErrors()) {
            FHResult.CloseSockets();
            m_ErrorStr = FHResult.m_ErrorStr;
            return FHResult.m_NetworkError==neSuccess ? neInternalError : FHResult.m_NetworkError;
        }
        else if (InternalError != errNone) {
            FHResult.CloseSockets();
            m_ErrorStr = string("[") + m_Hosts[HostNo].m_CorpusName + "] ";
            size_t p = S.find_first_not_of("\x1\x2 \t\r\n");
            if (p != S.npos) {
                m_ErrorStr += S.substr(p);
            } else {
                m_ErrorStr += GetDDCErrorString((DDCErrorEnum)InternalError);
            }
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

    //-- populate ResultString
    for (size_t i=beg; i < end; i++) {
        BYTE HostNo = FHResult.m_Hits[i].m_HostNo;
        const vector<size_t>&  V = SortedHits[HostNo];
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
void CDDCBranchServer::GetFirstHitsFromCorpora(const CSelectedHosts& SelectedHosts,
                                               const string Query,
                                               const size_t  StartHitNo,
                                               const size_t  ResultLimit,
                                               const int    TimeOut,
                                               CFirstHitsQueryResult& Result)
{
    CRunQueryData &runq = m_QueryData; //-- for navigation hints
        
    Result.m_Sockets.resize(SelectedHosts.size(),-1);
    Result.m_AllHitsCount = 0;
    Result.m_AllRelevantDocsCount = 0;
    Result.m_NetworkError = neSuccess;
    Result.m_InternalError = errNone;
    Result.m_SortOrder = hsoNone;
    Result.m_ErrorStr = "";

    //-- nav-hints
    bool compat_ge_v2_1_9 = (m_VersionCompat >= DDCVersionT(2,1,9)); //-- can we use v2.1.9 get_first_hits syntax?
    const NavHint& Hint   = runq.navHint;
    size_t HintOffset     = Hint.OffsetTotal();
    if (StartHitNo < HintOffset)
        throw CExpc("bizarre hint OffsetTotal=%zd exceeds requested StartHitNo=%d", HintOffset, StartHitNo);
    NAVCACHE_DEBUG(ddcLogDebug(Format("-> got HintOffset=%zd", HintOffset)));

    //-- daughter-relative paths placeholder \x01
    size_t qPathPos = Query.rfind('\x01');

    for (size_t i=0; i<SelectedHosts.size(); i++)   
    {
        BYTE HostNo = SelectedHosts.m_vec[i];
        CHost& Host = m_Hosts[HostNo];
        string strError;
        Result.m_Sockets[i] = Host.CreateAndConnectSocket(strError);
        if (Result.m_Sockets[i] == -1)
        {
            Result.m_NetworkError = neCouldNotOpenSocket;
            return;
        };

        string dtrQuery(Query);
        if (qPathPos != string::npos)
            dtrQuery.replace(qPathPos,1, SelectedHosts.DtrPaths(HostNo));

        const char *dtrHintStr = Hint.DtrHint(HostNo);
        string Req;
        if (compat_ge_v2_1_9) {
            //-- compat >= v2.1.9: use NavCache hints for get_first_hits requests to daughter subcorpora
            char *dtrHintTail;
            size_t dtrStart = strtoul(dtrHintStr,&dtrHintTail,0);
            size_t dtrLimit = StartHitNo + ResultLimit - HintOffset;
            //size_t dtrLimit = ResultLimit + (StartHitNo-min((size_t)StartHitNo,dtrStart));
            //size_t dtrLimit = ResultLimit - min((size_t)ResultLimit,max(dtrStart,HintOffset));
            Req = Format("get_first_hits %s\x01%i %zi %zd%s %s",
                         dtrQuery.c_str(), TimeOut, dtrLimit, dtrStart,dtrHintTail, Hint.m_SortKey.c_str());
        } else {
            //-- compat <  v2.1.9: use old get_first_hits syntax (highway-painting algorithm)
            Req = Format ("get_first_hits %s\x01%i %i", dtrQuery.c_str(), TimeOut,  StartHitNo+ResultLimit);
        }
                    
        string ErrorStr;
        if (!SendString(Result.m_Sockets[i], Req.c_str(), Req.length(), ErrorStr)) 
        {
            ErrorMessage (Format("cannot send a string to socket %s : %s", Host.GetAddressStr().c_str(), ErrorStr.c_str() ));
            Result.m_NetworkError = neCouldNotSendData;
            return;
        };
    };

    Result.m_DtrEnds.assign(m_Hosts.size(), 0);
    vector<size_t>  HitsDistribution(m_Hosts.size(), 0);
    vector<size_t>  RelevantDocsDistribution(m_Hosts.size(), 0);
    for (size_t i=0; i<SelectedHosts.size(); i++)   
    {
        BYTE HostNo = SelectedHosts.m_vec[i];
        CHost& Host = m_Hosts[HostNo];

        string S;
        Result.m_NetworkError = ReceiveString(Result.m_Sockets[i], S, TimeOut);
        if (Result.m_NetworkError != neSuccess)
        {
            concord_daemon_log ( " Cannot receive a result string from a client  " );
            return;
        };

        size_t  CorpusHitsCount,RelevantDocumentsCount, EndHitNo;
        int iInternalError, iSort;

        if(sscanf(S.c_str(), "%i %zi %zi %zi %i", &iInternalError, &EndHitNo, &CorpusHitsCount, &RelevantDocumentsCount, &iSort) != 5)
        {
            Result.m_NetworkError = neProtocolError;
            Result.m_ErrorStr     = string("[") + Host.m_CorpusName + "] " + GetNetworkErrorString(Result.m_NetworkError);
            return;
        }
        Result.m_InternalError = (DDCErrorEnum)iInternalError;
        Result.m_AllHitsCount += CorpusHitsCount;
        HitsDistribution[HostNo] = CorpusHitsCount;
        Result.m_AllRelevantDocsCount += RelevantDocumentsCount;
        RelevantDocsDistribution[HostNo] = RelevantDocumentsCount;
        Result.m_SortOrder = (HitSortOrderEnum)iSort;
        Result.m_DtrEnds[HostNo] = EndHitNo;
        //#ifdef DDC_COUNT_KEY_COMPAT
        //-- hack for transition to v2.0.38; see DDC_COUNT_KEY_COMPAT definition in ConcCommon.h
        //   + also needed for v2.1.4 fixes
        bool isCountResult = IsCountSort(Result.m_SortOrder);
        //#endif

        HSDEBUG( Format("DEBUG[status:%s]=\"%s\" --> iSort=%d", Host.m_CorpusName.c_str(), S.c_str(), iSort) );

        if (Result.m_InternalError != errNone) {
            //-- sub-corpus error: look for error message
            size_t p = S.find('\n');
            Result.m_ErrorStr = string("[") + Host.m_CorpusName + "] ";
            if (p != S.npos) {
                Result.m_ErrorStr += S.substr(p+1);
            } else {
                Result.m_ErrorStr += GetDDCErrorString((DDCErrorEnum)Result.m_InternalError);
            }
            Result.m_NetworkError = neInternalError;
            return;
        }

        //-- reserve space in hit sort-key vector (this actually doesn't seem to help against memory-bloat --moocow 2018-01-10 10:23:29+0100)
        //Result.m_Hits.reserve( Result.m_Hits.size() + (CorpusHitsCount < ResultLimit ? CorpusHitsCount : ResultLimit) );
                
        //-- read sort keys for merging sorted results (v2.0.19: always use string-sort for results)            
        size_t f = S.find("\t");
        size_t subcorpusHitOffset = Result.m_Hits.size();
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
                    if (isCountResult && SortKeyBuf[0]=='\002')
                        HS.m_SortKeyStr = &(SortKeyBuf[1]); //-- suppress empty initial sort-key fields for ddc-2.1.4
                    else
                        HS.m_SortKeyStr = SortKeyBuf;
                }

                Result.m_Hits.push_back(HS);
                HSDEBUG( Format("DEBUG[<%s]: hit = %s", Host.m_CorpusName.c_str(), Result.m_Hits.back().debugStr().c_str()) );
            }
        }

        //-- update logical result offset of m_Hits[]
        //   + 2018-06-13: only for ResultLimit>0 (mantis bug #27397)
        if (!isCountResult && ResultLimit>0) {
            Result.m_Offset += (subcorpusHitOffset < Result.m_Hits.size()    //-- we added at least 1 hit from this subcorpus
                                ? Result.m_Hits[subcorpusHitOffset].m_HitNo  //   : logical subcorpus-offset of 1st hit returned by this subcorpus
                                : CorpusHitsCount);                          //   : we added no hits from this corpus
            NAVCACHE_DEBUG( ddcLogDebug(Format("DEBUG[<%s]: nHostHits=%zd; Result.Offset=%zd",
                                               Host.m_CorpusName.c_str(), Result.m_Hits.size()-subcorpusHitOffset, Result.m_Offset)) );
        }
    }

    // collecting hits distribution in the right order for all possible corpus threads
    // the previous cycle was only for "possible" host (=user-defined corpus threads)
    Result.m_HitsDistributionStr = "Corpora Distribution:";
    Result.m_RelevantDocsDistributionStr = "Relevant Documents Distribution:";
    for (size_t i=0; i< HitsDistribution.size();  i++)
    {
        Result.m_HitsDistributionStr += Format("%i",HitsDistribution[i]);
        Result.m_RelevantDocsDistributionStr += Format("%zi",RelevantDocsDistribution[i]);

        if (i+1 == HitsDistribution.size())
        {
            Result.m_HitsDistributionStr += Format("=%zi;\n",Result.m_AllHitsCount);
            Result.m_RelevantDocsDistributionStr += Format("=%zi;\n",Result.m_AllRelevantDocsCount);
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
                                                               size_t StartHitNo,
                                                               size_t ResultLimit,
                                                               int   TimeOut,
                                                               SOCKET& CorpusSocket,
                                                               int&    InternalError,
                                                               string& Result,
                                                               string& ResultHint)
{
    string ErrorStr;
    if (CorpusSocket == -1)
        return neNetworkError;

    string S;
    NetworkErrorsEnum Res = ReceiveString(CorpusSocket, S, TimeOut);
    if (!this->CloseDtr(CorpusSocket))
        ErrorMessage (Format("cannot close socket %s", Host.GetAddressStr().c_str()));

    if (Res  != neSuccess)
    {
        concord_daemon_log ( "cannot receive a result string from a client" );
        return Res;
    };

    //InternalError OffsetHint? Result      
    size_t dataPos = S.find('\x01');
    if ( (dataPos == string::npos) || (dataPos == 0) ) 
    {
        return neProtocolError;
    };

    if (ResultLimit > 0)
        Result.assign(S, dataPos, string::npos);
    else
        Result.clear();

    S.erase(dataPos, S.length() - dataPos);
    int iInternalError, hintPos;
    if(sscanf(S.c_str(), "%i%n", &iInternalError, &hintPos) != 1)
    {
        return neProtocolError;
    };
    InternalError = (DDCErrorEnum)iInternalError;

    //-- parse hint
    ResultHint.clear();
    if (hintPos < dataPos) {
        ResultHint.assign(S, hintPos, dataPos-hintPos);
        Trim(ResultHint);
    }
        

    return neSuccess;
}

//----------------------------------------------------------------------
size_t CDDCBranchServer::FindHostID(const string& CorpusName) const
{
    size_t hi=0;
    for (; hi < m_Hosts.size() && m_Hosts[hi].m_CorpusName != CorpusName; ++hi)
        ;
    return hi;
}

//----------------------------------------------------------------------
void CDDCBranchServer::ParseCorpusPath(const string& CorpusPath, string& Dtr, string& Rest)
{
    Dtr.clear();
    Rest.clear();

   
    size_t i = CorpusPath.find_first_not_of('/');
    if (i == string::npos) return;

    size_t j = CorpusPath.find('/',i+1);
    if (j == string::npos) {
        Dtr = CorpusPath.substr(i);
        return;
    }

    Dtr = CorpusPath.substr(i,j-i);
    j   = CorpusPath.find_first_not_of('/',j+1);
    if (j == string::npos) return;

    Rest = CorpusPath.substr(j);
}

//----------------------------------------------------------------------
bool CDDCBranchServer::ReadSelectedHosts(const string& InputQuery, string& CleanQuery, CSelectedHosts& SelectedHosts)
{
    SelectedHosts.m_vec.reserve(m_Hosts.size());
    CleanQuery = InputQuery;

    //-- scan backwards for ":CORPUS_LIST"
    size_t Beg;
    for (Beg=InputQuery.rfind(':'); Beg != string::npos; Beg=InputQuery.rfind(':',Beg-1)) {
        if (Beg==0 || isspace(InputQuery[Beg-1])) break;
    }
    if (Beg==string::npos || InputQuery[Beg] != ':') {
        //-- no corpus list found in input query: pass to all hosts
        SelectedHosts.InsertAll(m_Hosts.size(), "*");
        return true;
    }

    //-- find end of corpus list: scan forward from Beg for next whitespace character
    size_t End = InputQuery.find_first_of(" \t\r\n",Beg+1);
    CleanQuery.replace(Beg,End-Beg, "\x01");
    Trim(CleanQuery);

    //-- read subcorpus labels from selected corpus-list substring
    string s = InputQuery.substr(Beg+1, End-(Beg+1));
    Trim(s);
    if (s.empty()) {
        //-- empty subcorpus list found in input query: pass to all hosts
        SelectedHosts.InsertAll(m_Hosts.size(),"*");
        return true;
    }
    StringTokenizer tok(s.c_str(),", ");
    while (tok()) {
        string CorpusPath = tok.val();
        //-- hack for single-quoted paths
        if (CorpusPath.size()>=2 && CorpusPath[0]=='\'' && CorpusPath[CorpusPath.size()-1]=='\'') {
            //-- hack for single-quoted subcorpus paths
            CorpusPath.erase(CorpusPath.size()-1,1);
            CorpusPath.erase(0,1);
        }

        string DtrName, DtrPath;        
        ParseCorpusPath(CorpusPath, DtrName,DtrPath);
        DtrName = unescapeCString(DtrName);

        if (DtrName == "*") {
            SelectedHosts.InsertAll(m_Hosts.size(), DtrPath);
        }
        else {
            size_t DtrId = FindHostID(DtrName);
            if (DtrId == m_Hosts.size()) {
                ddcLogWarn(Format("ignoring unknown subcorpus `%s' for path `%s'", DtrName.c_str(), CorpusPath.c_str()));
                //m_ErrorStr = Format("subcorpus `%s' not found for corpus path `%s'", DtrName.c_str(), CorpusPath.c_str());
                //return false;
            } else {
                SelectedHosts.Insert(DtrId, DtrPath);
            }
        }
    }
    
    if (SelectedHosts.size() >= MaxSubhostsSize) {
        m_ErrorStr = Format("requested subcorpus set too large (%u >= %u)", SelectedHosts.size(), MaxSubhostsSize);
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

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
