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

#include "BranchServer.h"
#include "../common/ddcString.h"
#include "../ConcordLib/QueryCompiler.h"

//==============================================================================
// CFirstHitsQueryResult

//----------------------------------------------------------------------
void CFirstHitsQueryResult::CloseSockets()
{
    for (size_t j=0; j<m_Sockets.size(); j++) {
	    if (m_Sockets[j] != -1)
		CloseSocket(m_Sockets[j]);
	    m_Sockets[j] = -1;
	}
}

//----------------------------------------------------------------------
void CFirstHitsQueryResult::CollectCounts()
{
    assert(m_SortOrder == hsoAscendingCounts);
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
}

//==============================================================================
// CDDCBranchServer

//----------------------------------------------------------------------
CDDCBranchServer::CDDCBranchServer(bool bDoubleMessage, ProtocolDensityEnum pdProtocolDensity)
 : CDDCServer(bDoubleMessage, pdProtocolDensity)
{
    m_maxReceiveBytes = DDC_STATIC_BUFLEN;
};

//==============================================================================
// CDDCBranchServer: handlers

//----------------------------------------------------------------------
//void CDDCBranchServer::handle__get_first_hits(string &Result, const char *Query, int TimeOut, int ResultLimit)

//----------------------------------------------------------------------
//void CDDCBranchServer::handle__get_hit_strings(string &Result, const char *ResultType, int StartHitNo, int ResultLimit)

//----------------------------------------------------------------------
void CDDCBranchServer::handle__run_query(string &Result, const char *CorpusName, const char *Query, const char *ResultType, int StartHitNo, int ResultLimit, int TimeOut)
{
    int InternalError;
    int iNetworkError;
    DWORD EndHitNo, HitsCount, RelevantDocsCount;
    string strResultType(ResultType);
    string strQuery(Query);
    Trim(strResultType);
    Trim(strQuery);
    if ( strQuery.empty() )
	throw CExpc(errParseError, "CDDCBranchServer::handle__run_query(): cannot parse empty query string");

    string ResultString;
    string HitDistrib;
    string DocDistrib;
    string HitsKey;
    m_ErrorStr.clear();
    iNetworkError = RunDistributed(strQuery, strResultType, StartHitNo, ResultLimit,
				   InternalError, EndHitNo, HitsCount, TimeOut,
				   ResultString, RelevantDocsCount, HitDistrib, DocDistrib, HitsKey);

    if (CConcHolder::GetResultFormatByString(strResultType) == DDC_ResultJson) {
	Result = (string("{")
		  + Format("\"istatus_\":%i", InternalError)
		  + Format(",\"nstatus_\":%i", iNetworkError)

		  /*-- moo: this formatting works, but doesn't do anything useful (bogus error code 32 for parse error?)*/
		  /*
		    + "\"istatus_\":" + jsonStr(Format("%i %s", InternalError, GetDDCErrorString((DDCErrorEnum)InternalError).c_str()))
		    + ",\"nstatus_\":" + jsonStr(Format("%i %s", iNetworkError, GetNetworkErrorString((NetworkErrorsEnum)iNetworkError).c_str()))
		  */
		  + (m_ErrorStr.empty() ? "" : (string(",\"error_\":") + jsonStr(m_ErrorStr)))

		  + Format(",\"end_\":%i", EndHitNo)
		  + Format(",\"nhits_\":%i", HitsCount)
		  + Format(",\"ndocs_\":%i", RelevantDocsCount)
		  + ",\"dhits_\":" + jsonStr(HitDistrib)
		  + ",\"ddocs_\":" + jsonStr(DocDistrib)
		  + ",\"" + HitsKey + "\":[\n" + ResultString
		  + "\n]}");
    }
    else if (m_ErrorStr.empty()) {
	//-- normal, error-free result
	Result = ResultString + Format("\x01 %i %i %i %i %i", InternalError, iNetworkError, EndHitNo, HitsCount, RelevantDocsCount);
    }
    else {
	//-- errors
	Result = Format("\x01 %i %i %i %i %i", InternalError, iNetworkError, EndHitNo, HitsCount, RelevantDocsCount) + "\n" + m_ErrorStr + "\n";
	m_LogFunction( Format("CDDCBranchServer::handle__run_query(): ERROR: %s", m_ErrorStr.c_str()) );
    }

    m_bExpectMore = false;
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
    if (!ErrorStr.empty() || hsock==-1) {
	CloseSocket(hsock);
	throw CExpc(errOther, "could not connect to subcorpus `%s': %s", h->m_CorpusName.c_str(), ErrorStr.c_str());
    }

    string hq = string("expand_terms \x01") + pipeline + "\x01" + terms + "\x01" + Format("%i", timeout);
    if (!SendString(hsock, hq, ErrorStr)) {
	CloseSocket(hsock);
	throw CExpc(errOther, "expand_terms faild for subcorpus `%s': %s", h->m_CorpusName.c_str(), ErrorStr.c_str());
    }

    //-- read response directly into Result
    if (ReceiveString(hsock, Result, timeout) != neSuccess) {
	CloseSocket(hsock);
	throw CExpc(errOther, "expand_terms failed to read a response from subcorpus `%s'", h->m_CorpusName.c_str());
    }

#if 0
    //-- ddc annoyingly complains unless each subcorpus socket gets doubled messages: why?!
    string tmp;
    SendString(hsock, "ddc_close_socket", ErrorStr);
    ReceiveString(hsock, tmp, timeout);
#endif
    CloseSocket(hsock);

    m_bExpectMore = false;
}

//----------------------------------------------------------------------
void CDDCBranchServer::handle__status(string &Result, bool verbose)
{
    //-- status or vstatus : distributed server status
    double uptime = difftime(time(NULL), m_tStarted);

    Result = (string("{\n")
	      + "\"name\":" + jsonStr(m_CorpusName) + ",\n"
	      + "\"version\":" + jsonStr(PACKAGE_VERSION) + ",\n"
	      + "\"host\":" + jsonStr(m_HostName) + ",\n"
	      + "\"port\":" + Format("%d", m_Port) + ",\n"
	      + "\"started\":" + jsonStr(timestampUTC(m_tStarted)) + ",\n"
	      + "\"uptime\":" + Format("%.0f", uptime) + ",\n"
	      + "\"nrequests\":" + Format("%zd", m_nRequests) + ",\n"
	      + "\"corpora\":"
	      );

    if (verbose) {
	//-- vstatus: get subcorpus status
	Result += GetSubcorpusJsonArray("vstatus");
    } else {
	//-- status: just get subcorpus names
	for (size_t i=0; i < m_Hosts.size(); ++i) {
	    Result += (i==0 ? '[' : ',');
	    Result += jsonStr(m_Hosts[i].m_CorpusName);
	}
	Result += "]\n";
    }
    Result += "}\n";

    m_bExpectMore = false;
}

//----------------------------------------------------------------------
void CDDCBranchServer::handle__info(string &Result, bool verbose)
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
void CDDCBranchServer::handle__reload(string &Result)
{
    Result = string("{") + jsonStr(m_CorpusName) + ":" + GetSubcorpusJsonArray("reload") + "}";
    m_bExpectMore = false;
}

//==============================================================================
// local methods

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
	DwordVector PossibleHosts;
	string CleanQuery;
	// read "possible" hosts (e.g. user-specified hosts from query), using query where these hosts can be specified
	// PossibleHosts is an index of m_Hosts
	if (!ReadPossibleHosts(Query, CleanQuery, PossibleHosts))
		return neSubcorpusNotFound;

	EndHitNo = 0;
	HitsCount = 0;
	ResultString = "";

	DDCFormatTypeEnum ResultTypeE = CConcHolder::GetResultFormatByString(ResultType);

	// 
	time_t start_get_hits, end_get_hits; 
	if  (TimeOut != -1)
		time(&start_get_hits);
	

	CFirstHitsQueryResult FHResult;
	// reading first StartHiNo+ResultLimit  hits from each host and storing them to Hits

	GetFirstHitsFromCorpora(PossibleHosts, CleanQuery, StartHitNo+ResultLimit, TimeOut, FHResult);
	HitsCount = FHResult.m_AllHitsCount;
	RelevantDocsCount = FHResult.m_AllRelevantDocsCount;
	InternalError = FHResult.m_InternalError;
	if (FHResult.HasErrors())
	{
		FHResult.CloseSockets();
		swap(m_ErrorStr, FHResult.m_ErrorStr);
		if (FHResult.m_InternalError != errNone)
			InternalError = FHResult.m_InternalError;
		return FHResult.m_NetworkError;
	}

	if  (TimeOut != -1)
	{
		time(&end_get_hits);
		TimeOut -= end_get_hits-start_get_hits;
		if (TimeOut < 0)
		{
			// if the provious steps took all time we add 10 seconds in order to 
			// receive at least some results 
			TimeOut = 10;
		};
	};

	// sorting and trimming: we need stable_sort() in order to ensure HitNo order is retained
	if (FHResult.m_SortOrder < 0) {
		//-- sort: descending
		stable_sort (FHResult.m_Hits.rbegin(), FHResult.m_Hits.rend());
	}
	else if (FHResult.m_SortOrder > 0) {
		//-- sort: ascending
		stable_sort (FHResult.m_Hits.begin(), FHResult.m_Hits.end());
	}

	// count-query: aggregate by sort-keys
	if (FHResult.m_SortOrder == hsoAscendingCounts) {
	    FHResult.CollectCounts();
	}

#ifdef DEBUG_HIT_SORT
	for (vector<CHitToSort>::const_iterator hi=FHResult.m_Hits.begin(); hi != FHResult.m_Hits.end(); ++hi) {
		concord_daemon_log( Format("DEBUG[post-sort:order=%d]: hit[%d] = %s", FHResult.m_SortOrder, hi-FHResult.m_Hits.begin(), hi->debugStr().c_str()) );
	}
#endif

	if (StartHitNo+ResultLimit < FHResult.m_Hits.size())
		FHResult.m_Hits.erase(FHResult.m_Hits.begin()+StartHitNo+ResultLimit, FHResult.m_Hits.end());

	if (StartHitNo < FHResult.m_Hits.size())
		FHResult.m_Hits.erase(FHResult.m_Hits.begin(), FHResult.m_Hits.begin()+StartHitNo);
	else
		FHResult.m_Hits.clear();

#ifdef DEBUG_HIT_SORT
	for (vector<CHitToSort>::const_iterator hi=FHResult.m_Hits.begin(); hi != FHResult.m_Hits.end(); ++hi) {
		concord_daemon_log( Format("DEBUG[post-trim]: hit[%d] = %s", hi-FHResult.m_Hits.begin(), hi->debugStr().c_str()) );
	}
#endif

	if (FHResult.m_SortOrder == hsoAscendingCounts) {
	    //-- count-query can generate strings immediately
	    GetHitCounts(FHResult, ResultTypeE, ResultString);
	    HitsCount = FHResult.m_AllHitsCount;
	    FHResult.m_HitsDistributionStr.insert(FHResult.m_HitsDistributionStr.size()-2, Format("~%d", HitsCount));
	    HitsKey = "counts_";
	} else {
	    //-- context-query must retrieve full hit strings
	    GetHitContexts(FHResult, ResultType, ResultTypeE, PossibleHosts, InternalError, TimeOut, ResultString);
	    HitsKey = "hits_";
	}

	CConcHolder::DecorateQueryResults(ResultType, ResultString);
	if (ResultTypeE == DDC_ResultText) {
	    // we always write relevant document numbers (RelevantDocsDistributionStr) to output, 
	    // even though it is not specified in the option file of the coprus threads.
	    // The problem is, that daemon doesn't know anything about options files of their coprus threads.
	    ResultString = FHResult.m_HitsDistributionStr + FHResult.m_RelevantDocsDistributionStr + ResultString;
	}
	HitDistrib = FHResult.m_HitsDistributionStr.substr(21,FHResult.m_HitsDistributionStr.size()-23);
	DocDistrib = FHResult.m_RelevantDocsDistributionStr.substr(32,FHResult.m_RelevantDocsDistributionStr.size()-34);
	EndHitNo = StartHitNo + FHResult.m_Hits.size();

	return neSuccess;	
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
	int FirstHitNo = (V.empty()) ? 0 : FHResult.m_Hits[V[0]].m_HitNo;
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


	StringTokenizer tok(S.c_str(), CDDCServer::AdditionalHitDelimeter);
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
			concord_daemon_log ( " Cannot receive a resulting string from a client  " );
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
				int OrderId_IGNORED; //-- formerly integer sort-key Hit.m_OrderId sent by ddc < v2.0.19; used for count-queries by ddc >= v2.0.23
				int nscanned = sscanf(rest, "%i %i %[^\t]", &HS.m_HitNo, &OrderId_IGNORED, SortKeyBuf);

				if (nscanned < 2) {
					Result.m_NetworkError = neProtocolError;
					return;
				}
				else if (nscanned > 2 && strcmp(SortKeyBuf, "<empty>") != 0) {
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
	if (CorpusSocket == -1)
		return neNetworkError;

	//Query\x01StartHitNo ResultLimit bGetText
	string S = Format ("get_hit_strings %s\x01%i %i",  ResultType.c_str(), StartHitNo,  ResultLimit);

	string ErrorStr;
	if (!SendString(CorpusSocket, S.c_str(), S.length(), ErrorStr)) 
	{
		ErrorMessage (Format("cannot send a string to socket %s : %s", Host.GetAddressStr().c_str(), ErrorStr.c_str() ));

		if (!CloseSocket(CorpusSocket))
			ErrorMessage (Format("cannot close socket %s", Host.GetAddressStr().c_str()));
		CorpusSocket =-1;

		return neCouldNotSendData;
	};

	NetworkErrorsEnum Res = ReceiveString(CorpusSocket, S, TimeOut);
	if (!CloseSocket(CorpusSocket))
		ErrorMessage (Format("cannot close socket %s", Host.GetAddressStr().c_str()));
	CorpusSocket =-1;

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

	//-- send requests
	for (i=0; i < m_Hosts.size(); ++i) {
		CHost &Host = m_Hosts[i];

		//-- open socket
		errorStr.clear();
		SOCKET sock = Host.CreateAndConnectSocket(errorStr);
		if (sock == -1 || !errorStr.empty()) {
			Results[i] = Format("{\"name\":%s,\"error\":\"could not open socket: %s\"},", Host.m_CorpusName.c_str(), jsonStr(errorStr, true, false).c_str());
			continue;
		}

		//-- send request
		if (!SendString(sock, request, errorStr) || !errorStr.empty()) {
			CloseSocket(sock);
			Results[i] = Format("{\"name\":%s,\"error\":\"could not send to socket: %s\"},", Host.m_CorpusName.c_str(), jsonStr(errorStr, true, false).c_str());
			continue;
		}

		//-- store socket
		Sockets[i] = sock;
	}

	//-- read responses
	for (i=0; i < m_Hosts.size(); ++i) {
		if (Sockets[i] == -1 || !Results[i].empty())
			continue;

		//-- read response
		if (ReceiveString(Sockets[i], Results[i], timeout) != neSuccess) {
			CloseSocket(Sockets[i]);
			Sockets[i] = -1;
			Results[i] = Format("{\"name\":%s,\"error\":\"failed to read response data from socket\"},", m_Hosts[i].m_CorpusName.c_str());
			continue;
		}

#if 0
		//-- send doubled messages to avoid ddc complaints of the form 'Cannot receive string for corpus "corpus2" (error: Could not receive data to a socket)'
		errorStr.clear();
		SendString(Sockets[i], "ddc_close_socket", errorStr);
#endif
	}

#if 0
	//-- get responses for "ddc_close_socket" messages
	for (i=0; i < m_Hosts.size(); ++i) {
		if (Sockets[i] == -1) continue;

		errorStr.clear();
		ReceiveString(Sockets[i], errorStr, timeout);
		CloseSocket(Sockets[i]);
	}
#endif

	//-- build result
	string Result("[");
	for (i=0; i < m_Hosts.size(); ++i) {
		if (i!=0) Result += ',';
		Result += string("\n\t") + (Results[i].empty() ? "null" : Results[i]);
	}
	Result += "\n]";
	return Result;
}
