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

#include "LeafServer.h"
#include "../CommonLib/ddcString.h"

//==============================================================================
// CDDCLeafServer: constructors etc

//----------------------------------------------------------------------
void CDDCLeafServer::Shutdown()
{
    ddcLogInfo(Format("shutting down leaf server %s", m_CorpusName.c_str()));
    StopAcceptingThread();
};

//==============================================================================
// CDDCLeafServer: client threads

//----------------------------------------------------------------------
void CDDCLeafServer::WorkerCloneInit(const CDDCServer *Parent, size_t WorkerId)
{
    CDDCServer::WorkerCloneInit(Parent, WorkerId);

    CDDCLeafServer *parent = (CDDCLeafServer*)Parent;
    m_pHolder = parent->m_pHolder->WorkerClone(WorkerId);
}

//----------------------------------------------------------------------
void CDDCLeafServer::WorkerCloneFree(void)
{
    m_pHolder->WorkerCloneFree();
    CDDCServer::WorkerCloneFree();
}

//==============================================================================
// CDDCLeafServer: CHost API: overrides

//----------------------------------------------------------------------
bool CDDCLeafServer::Close(SOCKET& rConnectedSocket, bool linger, int timeout)
{
    bool rc = CHost::Close(rConnectedSocket, linger, timeout);
    if (m_pHolder) {
	//-- clear local intermediate query results: don't hog memory after expensive (often failed) queries
	m_pHolder->ClearQuery();
	m_pHolder->ClearQueryResults();
	m_pHolder->m_ShortOccurCaches.clear();
    }
    return rc;
}


//==============================================================================
// CDDCLeafServer: DDCServer API: request handlers

//----------------------------------------------------------------------
void CDDCLeafServer::handle__get_first_hits(string &Result, const char *Query, int TimeOut, size_t ResultLimit, const NavHint& Hint)
{
    assert(m_pHolder != NULL);
    m_pHolder->SetTimeOut(TimeOut);
    m_pHolder->m_ResultLimit  = ResultLimit;
    m_pHolder->m_ResultMinKey = Hint.m_SortKey;

    NAVCACHE_DEBUG( ddcLogDebug(Format("DEBUG: get_first_hits: got Hint=%s", Hint.toJson().c_str())) );

    DWORD EndHitNo = Hint.m_Offset;
    int Error      = m_pHolder->GetHits(Query, EndHitNo);
    if (Error != errNone)
	throw CExpc(Error, m_pHolder->m_ErrorStr.empty() ? GetDDCErrorString((DDCErrorEnum)Error) : m_pHolder->m_ErrorStr); //-- error
    Result  = Format ("%i %i %i %i %i", Error, EndHitNo, m_pHolder->m_AllHitsCount, m_pHolder->m_RelevantDocumentCount, m_pHolder->HitSortOrder());
    Result += m_pHolder->GetHitIds();

    NAVCACHE_DEBUG( ddcLogTrace(Format("get_first_hits[HintOffset=%d]: %s", Hint.m_Offset, Result.c_str())) );
    
    if (IsCountSort(m_pHolder->HitSortOrder()))
	m_bExpectMore = false;
    else
	m_bExpectMore = true;
}

//----------------------------------------------------------------------
void CDDCLeafServer::handle__get_hit_strings(string &Result, const char *ResultType, size_t StartHitNo, size_t ResultLimit)
{
    assert(m_pHolder != NULL);
    m_pHolder->SetResultFormat(ResultType);
    m_pHolder->m_ResultLimit = ResultLimit;

    int  Error = m_pHolder->GenerateHitStrings(StartHitNo);
    if (Error != errNone)
	throw CExpc(Error, m_pHolder->m_ErrorStr.empty() ? GetDDCErrorString((DDCErrorEnum)Error) : m_pHolder->m_ErrorStr); //-- error

    //-- no error
    if (m_pHolder->m_QueryResultStr.empty()) {
	if (m_pHolder->GetResultFormatStr() == "html")
	    if (m_pHolder->m_ResultLimit > 0)
		m_pHolder->m_QueryResultStr = "no entries found";
    }
    if (m_VersionCompat < DDCVersionT(2,1,9)) {
	//-- compat <  v2.1.9: suppress local offset hint
	Result = Format("%i", Error);
    } else {
	//-- compat >= v2.1.9: include local offset hint
	Result = Format("%i %zd\n", Error, m_pHolder->GetOffsetHint(StartHitNo));
    }
    Result.push_back('\x01');
    
    Result += m_pHolder->m_QueryResultStr;
    m_pHolder->m_QueryResultStr= "";

    m_bExpectMore = false;
}

//----------------------------------------------------------------------
void CDDCLeafServer::handle__run_query(string &Result, const char *CorpusName, const char *Query, const char *ResultType, size_t StartHitNo, size_t ResultLimit, int TimeOut, const NavHint& Hint)
{
    assert(m_pHolder != NULL);
    m_pHolder->SetTimeOut(TimeOut);
    m_pHolder->SetResultFormat(ResultType);
    m_pHolder->m_ResultLimit = ResultLimit;
    m_pHolder->m_ResultMinKey = Hint.m_SortKey;

    NAVCACHE_DEBUG( ddcLogDebug(Format("DEBUG: run_query[Start=%d,Limit=%d]: got Hint=%s", StartHitNo, ResultLimit, Hint.toJson().c_str())) );

    //-- RunQueryData
    CRunQueryData runq(Query, ResultType, StartHitNo, ResultLimit, TimeOut, &m_pHolder->m_ErrorStr);
    runq.navHint.update(Hint.m_SortKey, min((size_t)StartHitNo, Hint.m_Offset), 0);
    runq.EndHitNo = StartHitNo;
    NAVCACHE_DEBUG( ddcLogDebug(Format("DEBUG: run_query[Start=%d,Limit=%d]: init Hint=%s", StartHitNo, ResultLimit, runq.navHint.toJson().c_str())) );
    
    //-- get_first_hits
    DWORD EndHitNo = runq.EndHitNo;
    int Error = m_pHolder->GetHits(Query, EndHitNo);
    runq.EndHitNo = EndHitNo;
    if (Error != errNone)
	throw CExpc(Error, m_pHolder->m_ErrorStr.empty() ? GetDDCErrorString((DDCErrorEnum)Error) : m_pHolder->m_ErrorStr); //-- error
    runq.HitsCount = m_pHolder->m_AllHitsCount;
    runq.HitDistrib = Format("=%d", runq.HitsCount);
    if (IsCountSort(m_pHolder->HitSortOrder()))
	runq.HitDistrib += Format("~%d", runq.HitsCount);
    runq.RelevantDocsCount = m_pHolder->m_RelevantDocumentCount;
    runq.DocDistrib = Format("=%d", runq.RelevantDocsCount);

    //-- get_hit_strings
    Error = m_pHolder->GenerateHitStrings(StartHitNo, false);
    if (Error != errNone)
	throw CExpc(Error, m_pHolder->m_ErrorStr.empty() ? GetDDCErrorString((DDCErrorEnum)Error) : m_pHolder->m_ErrorStr); //-- error
    if (m_pHolder->m_QueryResultStr.empty()) {
	if (m_pHolder->GetResultFormatStr() == "html")
	    if (m_pHolder->m_ResultLimit > 0)
		m_pHolder->m_QueryResultStr = "no entries found";
    }

    //-- (re)format
    runq.EndHitNo = min((size_t)StartHitNo+(size_t)ResultLimit, m_pHolder->m_Hits.size());
    DDCFormatTypeEnum ResultTypeE = CConcSession::GetResultFormatByString(runq.sResultFormat);
    if (ResultTypeE == DDC_ResultText) {
	runq.ResponseBody += (string("Corpora Distribution:") + runq.HitDistrib + ";\n"
			      + string("Relevant Documents Distribution:") + runq.DocDistrib + ";\n");
    }

    if (IsCountSort(m_pHolder->HitSortOrder())) {
	GetHitCounts(runq, ResultTypeE);
	runq.navHint.clear();
    } else {
	GetHitContexts(runq, ResultTypeE);
	runq.navHint.update(m_pHolder->GetSortKeyHint(StartHitNo), m_pHolder->GetOffsetHint(StartHitNo), 0);
    }
    m_pHolder->m_QueryResultStr = "";

    NAVCACHE_DEBUG( ddcLogDebug(Format("DEBUG: run_query[Start=%d,Limit=%d]: final Hint=%s", StartHitNo, ResultLimit, runq.navHint.toJson().c_str())) );
    runq.toString(Result, m_WorkerId, m_VersionCompat);
    m_bExpectMore = false;
}


//----------------------------------------------------------------------
void CDDCLeafServer::handle__expand_terms(string &Result, const string& pipeline, const string& terms, int timeout, const string &corpus)
{
    assert(m_pHolder != NULL);
    vector<string> iterms_v = stringSplit(terms.c_str(), " \t\r\n");
    set<string>    iterms(iterms_v.begin(), iterms_v.end());

    m_pHolder->SetTimeOut(timeout);
    set<string> oterms;
    TxChain txc = m_pHolder->GetTxDispatcher()->getChain(pipeline);
    txc.expand(iterms,oterms);
    Result = Format("%i %i\n", errNone, oterms.size());
    for (set<string>::const_iterator oi=oterms.begin(); oi!=oterms.end(); oi++) {
	Result += *oi;
	Result.push_back('\t');
    }

    m_bExpectMore = false;
}

//----------------------------------------------------------------------
void CDDCLeafServer::handle__status(string &Result, int timeout, bool verbose)
{
    double uptime = difftime(time(NULL), m_tStarted);
    DDCProcessMemoryStatus pms(getpid());

    //-- synchronize moving-average query-time window (EMA decay)
    m_ServerStats.m_qTimes.Scrub();
    m_ServerStats.m_xTimes.Scrub();
    
    Result = (string("{\n\t")
	      + "\"name\":" + jsonStr(m_CorpusName) + ",\n\t"
	      + "\"version\":" + jsonStr(PACKAGE_VERSION) + ",\n\t"
	      + "\"compat\":" + jsonStr(m_VersionCompat.str()).c_str() + ",\n\t"
	      + "\"hostname\":" + jsonStr(m_FQHostName) + ",\n\t"
	      + "\"hostaddr\":" + jsonStr(m_HostAddr) + ",\n\t"
	      + "\"port\":" + Format("%d", m_Port) + ",\n\t"
	      + "\"started\":" + jsonStr(timestampUTC(m_tStarted)) + ",\n\t"
	      + "\"uptime\":" + Format("%.0f", uptime) + ",\n\t"
	      + "\"nrequests\":" + Format("%zd", m_ServerStats.m_nRequests) + ",\n\t"
	      + "\"nqueries\":" + Format("%zd", m_ServerStats.m_nQueries) + ",\n\t"
	      + "\"nexpand\":" + Format("%zd", m_ServerStats.m_nExpand) + ",\n\t"
	      + "\"nerrors\":" + Format("%zd", m_ServerStats.m_nErrors) + ",\n\t"
	      + "\"nslow\":" + Format("%zd", m_ServerStats.m_nSlow) + ",\n\t"
	      + "\"qtavg\":" + Format("%g", m_ServerStats.m_qTimes.Average()) + ",\n\t" //-- pseudo-compat
	      + "\"qtavgs\":" + m_ServerStats.m_qTimes.toJsonArray() + ",\n\t"
	      + "\"xtavg\":" + Format("%g", m_ServerStats.m_xTimes.Average()) + ",\n\t"	      
	      + "\"xtavgs\":" + m_ServerStats.m_xTimes.toJsonArray() + ",\n\t"
	      + "\"nworkers\":" + Format("%zd", m_nWorkers) + ",\n\t"
	      + "\"memkb\":" + Format("%zd", pms.VmRSS) + ",\n\t" //-- compat
	      + "\"vmem\":" + Format("{\"peak\":%zd,\"size\":%zd,\"hwm\":%zd,\"rss\":%zd,\"data\":%zd,\"stk\":%zd,\"exe\":%zd,\"lib\":%zd,\"swap\":%zd,\"file\":%zd,\"anon\":%zd}",
				     pms.VmPeak, pms.VmSize, pms.VmHWM, pms.VmRSS, pms.VmData, pms.VmStk, pms.VmExe, pms.VmLib, pms.VmSwap, pms.RssFile, pms.RssAnon) + ",\n\t"
	      + "\"cachesize\":" + Format("%zd", m_pHolder->CacheSize()) + ",\n\t"
	      + "\"curlcachesize\":" + Format("%zd", ddcCurlCache.size()) + "\n\t"
	      + "}"
	      );
    m_bExpectMore = false;
}

//----------------------------------------------------------------------
#undef DDC_VERBOSE_CORPUS_INFO
void CDDCLeafServer::handle__info(string &Result, int timeout, bool verbose)
{
	//-- info : corpus info
	CConcIndexator *ix = m_pHolder ? m_pHolder->m_pIndexator : NULL;
	string ProjectName = ix ? FileBasename(MakeFName(ix->m_Path, "")) : "";

	if (!ProjectName.empty()) ProjectName.erase(ProjectName.size()-1);
	Result = (string("{\n\t")
		  + "\"name\":" + jsonStr(m_CorpusName) + ",\n\t"
		  + "\"version\":" + jsonStr(PACKAGE_VERSION) + ",\n\t"
		  + "\"project\":" + (ix ? jsonStr(ProjectName) : "null") //+ ",\n\t"
		  );

	if (ix) {
		int i;

		//-- index required
		Result += (string(",\n\t")
			   + "\"indexed\":" + jsonStr(timestampUTC(ix->m_Timestamp)) + ",\n\t"
			   + "\"nfiles\":"  + Format("%zd", ix->GetCorpusFilesCount()) + ",\n\t"
			   + "\"nmasked\":"  + Format("%zd", ix->GetMaskedFilesCount()) + ",\n\t"
			   + "\"nsources\":"  + Format("%zd", ix->GetSourceFilesCount()) + ",\n\t"
			   + "\"ntokens\":" + Format("%zd", ix->GetCorpusEndTokenNo()) + ",\n\t"
			   //
			   //-- options
			   + "\"lang\":" + jsonStr(GetStringByLanguage(ix->m_Language)) + ",\n\t"
			   + "\"utf8\":" + (ix->m_Utf8 ? '1' : '0') + ",\n\t"
			   + "\"mmap\":" + (ix->m_bMemoryMap ? '1' : '0') + ",\n\t"
			   + "\"caseSensitive\":" + (ix->m_bCaseSensitive ? '1' : '0') + ",\n\t"
			   + "\"contextOperator\":" + (ix->HasContextOperator() ? '1' : '0') + ",\n\t"
			   + "\"dwdsThesaurus\":" + (ix->UseDwdsThesaurus() ? '1' : '0') + ",\n\t"
			   + "\"interpDelimiter\":" + jsonStr(ix->m_InterpDelimiter) + ",\n\t"
			   + "\"tokenDelimiter\":" + jsonStr(ix->m_TokenDelimiter) + ",\n\t"
			   + "\"allowUnsafeQueries\":" + (ix->m_bAllowUnsafeQueries ? '1' : '0') + ",\n\t"
			   + "\"allowCountByTokenAttributes\":" + (ix->m_bAllowCountByTokenAttributes ? '1' : '0') + ",\n\t"
			   + "\"indexPunctuation\":" + (ix->IndexPunctuation() ? '1' : '0') + ",\n\t"
			   + "\"indexMorphPatterns\":" + (ix->m_bIndexMorphPatterns ? '1' : '0') + ",\n\t"
			   + "\"indexChunks\":" + (ix->m_bIndexChunks ? '1' : '0') + ",\n\t"
			   );

		//-- info.periods
		Result += string("\"periods\":[");
		for (i=0; i < ix->GetSearchPeriodsCount(); i++) {
		    if (i!=0) Result += ",";
		    Result += Format("%u", ix->GetSearchPeriod(i));
		}
		Result += "],\n\t";

		//-- info.bibl
		Result += (string("\"bibl\":[")
			   + "\n\t\t{\"name\":\"orig\",\"builtin\":1},"
			   + "\n\t\t{\"name\":\"scan\",\"builtin\":1},"
			   + "\n\t\t{\"name\":\"date\",\"builtin\":1},"
			   + "\n\t\t{\"name\":\"page\",\"builtin\":1}"
			   );
		const CConcXml::FreeBiblStringMap& bmap = ix->m_Bibl.GetFreeBiblStringMap();
		i=0;
		for (CConcXml::FreeBiblStringMap::const_iterator bmi=bmap.begin(); bmi != bmap.end(); ++i, ++bmi) {
			const CConcXml::CFreeBiblIndex *fbi = bmi->second;
			const CFreeBiblIndexTypeId fbtyp = fbi->GetTypeId();
			Result += (string(",\n\t\t{")
				   + "\"name\":" + jsonStr(fbi->m_Name) + ", "
#if DDC_VERBOSE_CORPUS_INFO
				   + "\"xpath\":" + jsonStr(fbi->m_Xpath) + ", "
#endif
				   + "\"visible\":" + (fbi->m_bShowInHeader ? '1' : '0') + ", "
				   + "\"size\":" + Format("%zd", fbi->size()) //-- bibl[i].size : number of values (?)
				   );
			if (fbtyp==cfbiStringConstant) {
			    Result += string(", \"value\":") + jsonStr(fbi->GetXpathStr(),ix->m_Utf8);
			}
			Result += "}";
		}
		const CConcXml::FreeBiblAliasMap& bamap = ix->m_Bibl.GetFreeBiblAliasMap();
		for (CConcXml::FreeBiblAliasMap::const_iterator bai=bamap.begin(); bai!=bamap.end(); ++bai) {
		    Result += (string(",\n\t\t{")
			       + "\"alias\":" + jsonStr(bai->first) + ", "
			       + "\"ref\":" + jsonStr(bai->second)
			       + "}"
			       );
		}
		Result += "\n\t\t],\n\t";
		//-- /info.bibl

		//-- info.breaks
		Result += "\"breaks\":[";
		const vector<CHitBorders::CBreakCollection> &breaks = ix->GetBreaks();
		for (i=0; i < breaks.size(); ++i) {
			const CHitBorders::CBreakCollection &b = breaks[i];
			if (i != 0) Result += ',';
			Result += (string("\n\t\t{")
				   + "\"shortname\":" + jsonStr(b.m_ShortName) + ", "
				   + "\"longname\":" + jsonStr(b.m_LongName) + ", "
				   + "\"size\":" + Format("%zd", b.m_BreakOffsets.size()) //-- breaks[i].size : number of breaks
				   + "}"
				   );
		}
		Result += "\n\t\t],\n\t";
		//-- /info.breaks

		//-- info.indices
		Result += "\"indices\":[";
		for (i=0; i < ix->m_Indices.size(); ++i) {
			const CStringIndexSet* sis = ix->m_Indices[i];
			set<size_t> visibleIndices(ix->m_IndicesToShow.begin(), ix->m_IndicesToShow.end());
			//
			if (i != 0) Result += ',';
			//-- info.indices : verbose
			Result += (string("\n\t\t{")
				   + "\"shortname\":" + jsonStr(sis->m_ShortName) + ", "
				   + "\"longname\":" + jsonStr(sis->m_Name) + ", "
				   + "\"visible\":" + (visibleIndices.find(i)!=visibleIndices.end() ? '1' : '0') + ", "
				   //+ "\"bigrams\":" + Format("%d", sis->m_MaxBigramWindowSize) + ", "
				   //+ "\"bigrams\":" + Format("%d", -1) + ", "
				   + "\"size\":" + Format("%zd", sis->m_Index.size()) //+ ", " //-- indices[i].size : number of values (?)
				   //+ "\"bigramBorder\":" + Format("%d", sis->m_BigramBorder) + ", "
				   //+ "\"left\":" + Format("%zd", sis->m_BigramsIndex.m_LeftBigrams.m_FirstWords.size()) + ", "
				   //+ "\"right\":" + Format("%zd", sis->m_BigramsIndex.m_RightBigrams.m_FirstWords.size()) + ", "
				   + "}"
				   );
		}
		//---- info.indices: aliases
		for (CStringIndexator::IndexMap::const_iterator imi=ix->m_IndexMap.begin(); imi != ix->m_IndexMap.end(); ++imi) {
		    if (imi->second==NULL || imi->first == imi->second->m_Name || imi->first == imi->second->m_ShortName)
			continue;
		    if (i != 0) Result += ',';
		    Result += (string("\n\t\t{")
			       + "\"alias\":" + jsonStr(imi->first) + ", "
			       + "\"ref\":" + jsonStr(imi->second->m_Name)
			       + "}");
		    ++i;
		}
		//---- /info.indices: aliases
		Result += "\n\t\t],\n\t";
		//-- /info.indices

		//-- info.xbibl ~ ExpandBibl
		Result += "\"xbibl\":[";
		const CConcXml::BiblExpanderMap& xbmap = ix->m_Bibl.GetBiblExpanderMap();
		i=0;
		for (CConcXml::BiblExpanderMap::const_iterator bmi=xbmap.begin(); bmi != xbmap.end(); ++i, ++bmi) {
			const CBiblExpander *bx = bmi->second;
			if (i != 0) Result += ',';
#if DDC_VERBOSE_CORPUS_INFO
			//-- info.xbibl: verbose
			Result += (string("\n\t\t{")
				   + "\"label\":" + jsonStr(bx->m_BxLabel) + ", "
				   + "\"target\":" + jsonStr(bx->m_BxTarget) + ", "
				   + "\"param\":" + jsonStr(bx->m_BxParam)
				   + "}"
				   );
#else
			//-- info.xbibl: terse
			Result += jsonStr(bx->m_BxLabel);
#endif
		}
		Result += "],\n\t";
		//-- /info.xbibl

		//-- info.expanders ~ Expand
		Result += "\"expanders\":[";
		i=0;
		const TxDispatcher *txd = m_pHolder->GetTxDispatcher();
		for (TxDispatcher::TxMap::const_iterator txi=txd->m_tx.begin(); txi != txd->m_tx.end(); ++i, ++txi) {
			const CTermExpander* tx = txi->second;
			if (i != 0) Result += ", ";
#if DDC_VERBOSE_CORPUS_INFO
			//-- info.expanders : verbose
			Result += (string("\n\t\t{")
				   + "\"class\":" + jsonStr(tx->m_Class) + ", "
				   + "\"label\":" + jsonStr(tx->m_Label) + ", "
				   + "\"param\":" + jsonStr(tx->m_Param)
				   + "}"
				   );
#else
			Result += jsonStr(tx->m_Label);
#endif
		}
		Result += "],\n\t";
		//--/info.expanders

		//--info:opdefault
		Result += "\"opdefault\":{";
		i=0;
		for (map<string,string>::const_iterator oii=ix->m_OpDefaultIndexNames.begin(); oii!=ix->m_OpDefaultIndexNames.end(); ++oii, ++i) {
		    if (i != 0) Result.push_back(',');
		    Result += string("\n\t\t") + jsonStr(oii->first) + ":" + jsonStr(oii->second);
		}
		if (i != 0) Result += "\n\t\t";
		Result += "},\n\t";
		//--/info:opdefault

		//-- info.user
		Result += "\"user\":";
		if (!ix->m_ServerInfo.empty()) {
		    Result += "{";
		    for (map<string,pair<bool,string> >::const_iterator ii=ix->m_ServerInfo.begin(); ii!=ix->m_ServerInfo.end(); ++ii) {
			const string &ikey = ii->first;
			const pair<bool,string> &ival = ii->second;
			if (ii != ix->m_ServerInfo.begin()) Result.push_back(',');
			Result += string("\n\t\t") + jsonStr(ikey,ix->m_Utf8,true) + ":";
			if (ival.first) {
			    //-- user-supplied json file
			    string filename = RelativeFileName(ix->m_Path, ival.second);
			    //fprintf(stderr, "info file for key '%s'='%s' ; cwd=%s\n", ikey.c_str(), filename.c_str(), CurrentDirectory().c_str()); //-- DEBUG
			    if (!LoadFileToString(filename, Result, false)) {
				Result += string("null");
			    }
			} else {
			    //-- user-supplied json string
			    Result += ival.second;
			}
		    }
		    Result += (ix->m_ServerInfo.empty() ? "}" : "\n\t\t}");
		} else {
		    Result += "null";
		}
		Result += "\n\t";
	}
	Result += "}";
	//-- /info

	m_bExpectMore = false;
}

//----------------------------------------------------------------------
void CDDCLeafServer::handle__reload(string &Result, int depth)
{
#if 0 /* BROKEN */
    CConcHolder *pHolder = NULL;
    if (!LoadHolder(&pHolder))
	throw CExpc(errOther, Format("reload failed for %s", GetLocalPathOfIndex().c_str()));
    if (m_pHolder) {
	if (m_pHolder->m_pIndexator) delete m_pHolder->m_pIndexator;
	delete m_pHolder;
    }
    m_pHolder = pHolder;
    Result = Format("{%s:1}", jsonStr(m_CorpusName).c_str());
#else
    Result = Format("{%s:null,\"error\":\"reload request handler broken\"}", jsonStr(m_CorpusName).c_str());
#endif
    m_bExpectMore = false;
}

//----------------------------------------------------------------------
void CDDCLeafServer::handle__clear_cache(string &Result, int depth)
{
    m_pHolder->ClearQueryCache();
    ddcCurlCache.lock();
    ddcCurlCache.clear();
    ddcCurlCache.unlock();
    Result = Format("{%s:1}", jsonStr(m_CorpusName).c_str());
    m_bExpectMore = false;
}

//==============================================================================
// CDDCLeafServer: local methods

//----------------------------------------------------------------------
bool CDDCLeafServer::LoadHolder(CConcHolder **ppHolder) {
    if (!ppHolder)
	ppHolder = &m_pHolder;

    assert (!*ppHolder);
    *ppHolder = new CConcHolder;

    (*ppHolder)->m_pIndexator = new CConcIndexator;
    ddcLogInfo( Format ("Loading corpus indices for %s (%s)", GetLocalPathOfIndex().c_str(), m_CorpusName.c_str()) );
    if (!(*ppHolder)->m_pIndexator->LoadProject(GetLocalPathOfIndex(), false)) {
	ddcLogError ( Format("Error! Cannot load project %s! ", GetLocalPathOfIndex().c_str()) );
	    delete (*ppHolder)->m_pIndexator;
	delete  (*ppHolder);
	(*ppHolder) = 0;
	return false;
    }

    ddcLogDebug("  init graphan ");
    (*ppHolder)->m_AdditionalHitDelimiter = CDDCServer::AdditionalHitDelimiter;

    ddcLogDebug(Format("  init random: port=m_RandomSeed=%i", m_Port));
    (*ppHolder)->m_RandomSeed = m_Port;
    (*ppHolder)->SetRandomSeed();

    ddcLogDebug(Format("Loaded corpus indices for %s (%s)", GetLocalPathOfIndex().c_str(), m_CorpusName.c_str()));
    return true;
}

//----------------------------------------------------------------------
void CDDCLeafServer::GetHitCounts(CRunQueryData &runq, DDCFormatTypeEnum ResultTypeE)
{
    runq.HitsKey = "counts_";
    string &ResultStr = runq.ResponseBody;

    if (ResultTypeE == DDC_ResultHTML) {
	ResultStr += "<HTML> <BODY>\n<TABLE>\n";
    }

    if (ResultTypeE == DDC_ResultJson) {
	size_t p0 = m_pHolder->m_QueryResultStr.find('[');
	size_t p1 = m_pHolder->m_QueryResultStr.rfind(']');
	if (p0 != string::npos && p1 != string::npos && p1 > p0)
	    ResultStr += m_pHolder->m_QueryResultStr.substr(p0+1, p1-(p0+1));
    } else {
	ResultStr += m_pHolder->m_QueryResultStr;
    }

    if (ResultTypeE == DDC_ResultHTML) {
	ResultStr += "</TABLE>\n</BODY></HTML>";
    }
}


//----------------------------------------------------------------------
void CDDCLeafServer::GetHitContexts(CRunQueryData &runq, DDCFormatTypeEnum ResultTypeE)
{
    runq.HitsKey = "hits_";
    string &ResultStr = runq.ResponseBody;
    
    if (ResultTypeE == DDC_ResultJson) {
	size_t p0 = m_pHolder->m_QueryResultStr.find('[');
	size_t p1 = m_pHolder->m_QueryResultStr.rfind(']');
	if (p0 != string::npos && p1 != string::npos && p1 > p0)
	    ResultStr += m_pHolder->m_QueryResultStr.substr(p0+1, p1-(p0+1));
    } else {
	ResultStr += m_pHolder->m_QueryResultStr;
    }
}

