//-*- Mode: C++; c-basic-offset:8; -*-
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
// Corpora.cpp : Implementation of CCorpora

#include "../common/Graspace.h"
#include "../common/string_socket.h"
#include "../ConcordLib/ConcHolder.h"
#include "Corpora.h"
#include "Morphan.h"
#include "../common/util_classes.h"
#include "../common/ddcString.h"

#ifdef WIN32
	#include <process.h>  /* _beginthread, _endthread */
#else
#endif


/*
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
*/

#ifdef DETECT_MEMORY_LEAK
	#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
	#endif
#endif

const char* AdditionalHitDelimeter = "\x01";

class CDDCCorpusListenHost  : public CHost
{
public:
	CConcHolder*					m_pHolder;

	/** moo: timestamp of server initialization */
	time_t m_tStarted;

	/** moo: number of served requests */
	size_t m_nRequests;

	CDDCCorpusListenHost (bool bDoubleMessage, ProtocolDensityEnum pdProtocolDensity);
	virtual ~CDDCCorpusListenHost ();
	string	ProcessSocketString(const string& S, SOCKET rConnectedSocket);
	bool	LoadHolder();

	void ServerStatusJson(string &Result, bool verbose=false);
	void ServerInfoJson(string &Result);
};

struct CQueryStatistics 
{
	DwordVector		m_HitsEnds;
	DWORD			m_FreqCount;
};

struct CHitToSort 
{
	BYTE	m_HostNo;
	DWORD	m_HitNo;
	DWORD	m_OrderId;
	string	m_OrderStrId;

	inline bool operator < (const CHitToSort& X) const {
		if (m_OrderId != X.m_OrderId)
			return m_OrderId < X.m_OrderId;
		if (m_OrderStrId != X.m_OrderStrId)
			return m_OrderStrId < X.m_OrderStrId;
		return m_HitNo < X.m_HitNo;
	};
};


class CDDCServerListenHost  : public CHost
{
public:
	struct CFirstHitsQueryResult 
	{
		DWORD			m_AllHitsCount;
		DWORD			m_AllRelevantDocsCount; 
		string			m_HitsDistributionStr;
		string			m_RelevantDocsDistributionStr;
		int			m_InternalError;
		bool			m_bSort;
		NetworkErrorsEnum	m_NetworkError;
		string			m_ErrorStr;
		vector<CHitToSort>  	m_Hits;
		vector<SOCKET>		m_Sockets;

		bool HasErrors() const
		{
			return		(m_NetworkError != neSuccess ) 
					||	(m_InternalError != errNone);
		};

		void CloseSockets()
		{
			// closing sockets, which were opened before
			for (size_t j=0; j<m_Sockets.size(); j++) {
				if (m_Sockets[j] != -1)
					CloseSocket(m_Sockets[j]);
				m_Sockets[j] = -1;
			}
		};
	};

	map<string, CQueryStatistics>	m_QueryToStatis;
	vector<CHost>			m_Hosts;	
	string				m_QueryResultString;
	string				m_ErrorStr;  //-- subcorpus error
	int                             m_ReloadCorpusNo;
	CConcHolder*                    m_pReloadedCorpusHolder;

	/** moo: timestamp of server initialization */
	time_t m_tStarted;

	/** moo: number of served requests */
	size_t m_nRequests;


	CDDCServerListenHost (bool bDoubleMessage, ProtocolDensityEnum pdProtocolDensity);
	virtual ~CDDCServerListenHost ();

	/** callback string_socket.h CHost callback */
	string	ProcessSocketString(const string& S, SOCKET rConnectedSocket);

	void GetFirstHitsFromCorpora(const DwordVector& PossibleHosts,
				     const string Query,
				     const DWORD  ResultLimit,
				     const int    TimeOut,
				     CFirstHitsQueryResult& Result);

	NetworkErrorsEnum GetHitStringsFromOneCorpus(CHost& Host,
						     const string& ResultType,
						     DWORD StartHitNo,
						     DWORD ResultLimit,
						     int   TimeOut,
						     SOCKET& CorpusSocket,
						     int&    InternalError,
						     string& Result);

	/** distributed query evaluation guts */
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
					 string& DocDistrib);

	bool   ReadPossibleHosts(const string& InputQuery, string& CleanQuery, DwordVector& PossibleHosts) /*const*/;
	string ReloadCorpusProcessSignal(const string& Query); 
	void   ReplaceHolderIfNeeded();

	/** pass request to each subcorpus host and fetch results into a JSON array */
	string  GetSubcorpusJsonArray(const string &request, int timeout = 10);
};


// all sockets which are opened by this daemon 
vector<CDDCCorpusListenHost> LocalCorpora;

CDDCServerListenHost* pServer = 0;


CDDCCorpusListenHost::CDDCCorpusListenHost (bool bDoubleMessage, ProtocolDensityEnum pdProtocolDensity) : 
	CHost(bDoubleMessage, pdProtocolDensity)
{
	m_pHolder = 0;
	m_LogFunction = concord_daemon_log;
	m_tStarted = time(NULL);
	m_nRequests = 0;
};


CDDCCorpusListenHost::~CDDCCorpusListenHost ()
{
	StopAcceptingThread();
};




bool SaveTrigger(const string& S, DWORD LParam)
{
	string ErrorStr;
	if (!SendString(LParam, S.c_str(), S.length(), ErrorStr))
	{
		concord_daemon_log(Format("cannot send a string for GetOccurrences: %s", ErrorStr.c_str()));
		return false;
	};
	return true;
};

bool  CDDCCorpusListenHost::LoadHolder() {
	assert (!m_pHolder);
	m_pHolder = new CConcHolder;
	m_LogFunction = concord_daemon_log;;

	m_pHolder->m_pIndexator = new CConcIndexator;
	concord_daemon_log ( Format ("Loading corpus indices for %s", GetLocalPathOfIndex().c_str()) );
	if (!m_pHolder->m_pIndexator->LoadProject(GetLocalPathOfIndex())) 
	{
		concord_daemon_log ( Format("Error! Cannot load project %s! ", GetLocalPathOfIndex().c_str()) );
		delete m_pHolder->m_pIndexator;
		delete  m_pHolder;
		m_pHolder = 0;
		return false;
	};
	concord_daemon_log ( "  init graphan " );
	m_pHolder->m_AdditionalHitDelimeter = AdditionalHitDelimeter;

	concord_daemon_log(Format("  init random: port=m_RandomSeed=%i", m_Port));
	m_pHolder->m_RandomSeed = m_Port;
	m_pHolder->SetRandomSeed();

	concord_daemon_log ( "  ok " );

	return true;
}

void CDDCCorpusListenHost::ServerStatusJson(string &Result, bool verbose)
{
	double uptime = difftime(time(NULL), m_tStarted);
	Result = (string("{\n\t")
		    + "\"name\":" + jsonStr(m_CorpusName) + ",\n\t"
		  + "\"version\":" + jsonStr(PACKAGE_VERSION) + ",\n\t"
		  + "\"host\":" + jsonStr(m_HostName) + ",\n\t"
		  + "\"port\":" + Format("%d", m_Port) + ",\n\t"
		  + "\"started\":" + jsonStr(timestampUTC(m_tStarted)) + ",\n\t"
		  + "\"uptime\":" + Format("%.0f", uptime) + ",\n\t"
		  + "\"nrequests\":" + Format("%zd", m_nRequests) + ",\n\t"
		  + "\"cachesize\":" + Format("%zd", m_pHolder->CacheSize()) + "\n\t"
		  + "}"
		  );
}

#undef DDC_VERBOSE_CORPUS_INFO
void CDDCCorpusListenHost::ServerInfoJson(string &Result)
{
	//-- info : corpus info
	CConcIndexator *ix = m_pHolder ? m_pHolder->m_pIndexator : NULL;
	string ProjectName = ix ? basename(MakeFName(ix->m_Path, "").c_str()) : "";

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
			   + "\"nfiles\":"  + Format("%zd", ix->GetSourceFilesCount()) + ",\n\t"
			   + "\"ntokens\":" + Format("%zd", ix->GetCorpusEndTokenNo()) + ",\n\t"
			   //
			   //-- options
			   + "\"lang\":" + jsonStr(GetStringByLanguage(ix->m_Language)) + ",\n\t"
			   + "\"utf8\":" + (ix->m_Utf8 ? '1' : '0') + ",\n\t"
			   + "\"caseSensitive\":" + (ix->m_bCaseSensitive ? '1' : '0') + ",\n\t"
			   + "\"contextOperator\":" + (ix->HasContextOperator() ? '1' : '0') + ",\n\t"
			   + "\"dwdsThesaurus\":" + (ix->UseDwdsThesaurus() ? '1' : '0') + ",\n\t"
			   + "\"interpDelimiter\":" + jsonStr(ix->m_InterpDelimiter) + ",\n\t"
			   + "\"tokenDelimiter\":" + jsonStr(ix->m_TokenDelimiter) + ",\n\t"
			   + "\"allowUnsafeQueries\":" + (ix->m_AllowUnsafeQueries ? '1' : '0') + ",\n\t"
			   + "\"indexPunctuation\":" + (ix->IndexPunctuation() ? '1' : '0') + ",\n\t"
			   + "\"indexMorphPatterns\":" + (ix->m_bIndexMorphPatterns ? '1' : '0') + ",\n\t"
			   + "\"indexChunks\":" + (ix->m_bIndexChunks ? '1' : '0') + ",\n\t"
			   );

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
			Result += (string(",\n\t\t{")
				   + "\"name\":" + jsonStr(fbi->m_Name) + ", "
#if DDC_VERBOSE_CORPUS_INFO
				   + "\"xpath\":" + jsonStr(fbi->m_Xpath) + ", "
#endif
				   + "\"visible\":" + (fbi->m_bShowInHeader ? '1' : '0') + ", "
				   + "\"size\":" + Format("%zd", fbi->size()) //-- bibl[i].size : number of breaks
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
				   + "\"bigrams\":" + Format("%d", sis->m_MaxBigramWindowSize) + ", "
				   + "\"size\":" + Format("%zd", sis->m_Index.size()) //+ ", " //-- indices[i].size : number of values (?)
				   //+ "\"bigramBorder\":" + Format("%d", sis->m_BigramBorder) + ", "
				   //+ "\"left\":" + Format("%zd", sis->m_BigramsIndex.m_LeftBigrams.m_FirstWords.size()) + ", "
				   //+ "\"right\":" + Format("%zd", sis->m_BigramsIndex.m_RightBigrams.m_FirstWords.size()) + ", "
				   + "}"
				   );
		}
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
		for (TxDispatcher::TxMap::const_iterator txi=ix->m_Txd.m_tx.begin(); txi != ix->m_Txd.m_tx.end(); ++i, ++txi) {
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
		Result += "]\n\t";
		//--/info.expanders
	}
	Result += "}";
	//-- /info
}

string CDDCCorpusListenHost::ProcessSocketString(const string& InputSocket, SOCKET rConnectedSocket) 
{
	//-- moo: first, get command part of input string
	int eocpos = InputSocket.find_first_of(" \t\r\n\x00\x01\x02");
	string cmd(InputSocket,0,eocpos);
	if (eocpos==InputSocket.npos) eocpos=InputSocket.size();
	//fprintf(stderr, "CorpusListenHost: cmd=(%s)\n", cmd.c_str()); //-- DEBUG
	string Result;

	if (cmd == "get_hit_strings") {
		DWORD  StartHitNo;
		char sResultType[100];
		//sResultType\x01StartHitNo ResultLimit

		int CountItems = sscanf (InputSocket.c_str(), "get_hit_strings %[^\x01]\x01%i %i", sResultType,  &StartHitNo,&m_pHolder->m_ResultLimit);
		try {
			if (CountItems != 3)
				throw CExpc(errParseError, "CDDCCorpusListenHost(get_hit_strings): cannot parse socket input");
			m_pHolder->SetResultFormat(sResultType);
			int  Error = m_pHolder->GenerateHitStrings(StartHitNo);

			if (Error != errNone) throw CExpc(Error); //-- error

			//-- no error
			if (m_pHolder->m_QueryResultStr.empty()) {
				if (m_pHolder->GetResultFormatStr() == "html")
					if (m_pHolder->m_ResultLimit > 0)
						m_pHolder->m_QueryResultStr = "no entries found";
			}
			Result = Format ("%i\x01", Error);
			Result += m_pHolder->m_QueryResultStr;
			m_pHolder->m_QueryResultStr= "";
		}
		catch (CExpc& e) {
			Result = Format("%i\x01\n%s", e.code(), e.what());
		}
		catch (exception& e) {
			Result = Format("%i\x01\n%s", -1, e.what());
		}
	}
	else if (cmd == "get_first_hits") {
		// getting hits
		DWORD  EndHitNo = 0;
		int	TimeOut;
		char sQuery[DDC_STATIC_BUFLEN];
		const char* strInputSocket = InputSocket.c_str();
	
		int CountItems = sscanf (strInputSocket, "get_first_hits %[^\x01]\x01 %i %i", sQuery, &TimeOut,&m_pHolder->m_ResultLimit);
		try {
			if (CountItems != 3)
				throw CExpc(errParseError, "CDDCCorpusListenHost(get_first_hits): cannot parse socket input");
			m_pHolder->SetTimeOut(TimeOut);
			int Error = m_pHolder->GetHits(sQuery, EndHitNo);
			if (Error != errNone) throw CExpc(Error); //-- error

			Result = Format ("%i %i %i %i %i", Error, EndHitNo, m_pHolder->m_AllHitsCount, m_pHolder->m_RelevantDocumentCount, (m_pHolder->HitsShouldBeSorted()?1:0));
			Result += m_pHolder->GetHitIds();
		}
		catch (CExpc& e) {
			Result = Format("%i 0 0 0 0\n%s", e.code(), e.what());
		}
		catch (exception& e) {
			Result = Format("%i 0 0 0 0\n%s", -1, e.what());
		}
	}
	else if (cmd == "expand_terms") {
		//-- expand_terms \x01 PIPELINE \x01 TERMS \x01 TIMEOUT [\x01...]";
		vector<string> qv = stringSplit(InputSocket.c_str(), "\x01");
		try {
			//-- parse query
			if (qv.size() < 4)
				throw CExpc(errParseError, "could not parse expand_terms request");
			string &cspec = qv[1];
			vector<string> iterms_v = stringSplit(qv[2].c_str(), " \t\r\n");
			set<string>    iterms(iterms_v.begin(), iterms_v.end());
			int timeout = atoi(qv[3].c_str());

			//-- guts
			m_pHolder->SetTimeOut(timeout);
			set<string> oterms;
			TxChain txc = m_pHolder->m_pIndexator->m_Txd.getChain(cspec);
			txc.expand(iterms,oterms);
			Result = Format("%i %i\n", errNone, oterms.size());
			for (set<string>::const_iterator oi=oterms.begin(); oi!=oterms.end(); oi++) {
				Result += *oi;
				Result.push_back('\t');
			}
		}
		catch (CExpc& e) {
			Result = Format("%i 0\n%s", e.code(), e.what());
		}
		catch (exception& e) {
			Result = Format("%i 0\n%s", -1, e.what());
		}
	}
	else if (cmd == "version") {
		//-- version : subcorpus server version
		Result = PACKAGE_VERSION ;
	}
	else if (cmd == "status") {
		//-- status : subcorpus server status
		ServerStatusJson(Result, false);
	}
	else if (cmd == "vstatus") {
		//-- status : subcorpus server status (verbose)
		ServerStatusJson(Result, true);
	}
	else if (cmd == "info" || cmd == "vinfo") {
		//-- info : corpus info
		ServerInfoJson(Result);
	}
	else {
		Result = Format("%i 0\nunknown command `%s'", errParseError, cmd.c_str());
		concord_daemon_log( Format("CDDCCorpusListenHost Error: unknown command \"%s\"", cmd.c_str()) );
	}

	++m_nRequests;
	return Result;
};




//==========================================================
//========  CDDCServerListenHost  ==========================
//==========================================================

CDDCServerListenHost::CDDCServerListenHost (bool bDoubleMessage, ProtocolDensityEnum pdProtocolDensity) : 
CHost(bDoubleMessage, pdProtocolDensity)
{
	m_LogFunction = concord_daemon_log;
	m_ReloadCorpusNo = -1;
	m_pReloadedCorpusHolder = 0;
	m_maxReceiveBytes = DDC_STATIC_BUFLEN;
	m_tStarted = time(NULL);
	m_nRequests = 0;
};


CDDCServerListenHost::~CDDCServerListenHost ()
{
	StopAcceptingThread();
};

#ifdef WIN32
	void  _cdecl ReloadCorpus( void* pParam )
#else
	void*   ReloadCorpus( void* pParam )
#endif
{
    CDDCServerListenHost* pServer = (CDDCServerListenHost* )pParam;
    const CDDCCorpusListenHost& OldH = LocalCorpora[pServer->m_ReloadCorpusNo];
    CDDCCorpusListenHost C(false, pdWeakDensity);
    C.CopyAddressParametersFrom(OldH);
    if (!C.LoadHolder()){
        concord_daemon_log ( Format("cannot reload %s!", C.GetLocalPathOfIndex().c_str()));
    }
    concord_daemon_log ( Format("reload %s successfully!", C.GetLocalPathOfIndex().c_str()));
    pServer->m_pReloadedCorpusHolder = C.m_pHolder;
}

string CDDCServerListenHost::ReloadCorpusProcessSignal(const string& Query) 
{
    char subcorpus[256];
    int CountItems = sscanf (Query.c_str(), "reload %s", subcorpus);
    if (CountItems != 1) return  "";
    int corpus_no = -1;
    if (isdigit(subcorpus[0]) ) {
        corpus_no = atoi(subcorpus);
    }
    else {
       for (int i=0; i < LocalCorpora.size(); i++)
           if (LocalCorpora[i].m_CorpusName == subcorpus) {
               corpus_no = i;
               break;
           }
    }
    if (corpus_no >= LocalCorpora.size())  {
        concord_daemon_log ( Format("bad corpus name %s!",  subcorpus));
        return "bad corpus name";
    }
    if (m_ReloadCorpusNo != -1) 
        return "already reloading, wait a little bit";

    m_ReloadCorpusNo = corpus_no;
    m_pReloadedCorpusHolder = 0;

	#ifdef WIN32
		_beginthread( ReloadCorpus, 0, (void*)this );
	#else
		pthread_t aThread;
		pthread_create(&aThread, NULL, ReloadCorpus, (void*)this);
		ddc_thread_init(subcorpus);
	#endif


    
    
    return "ok";
}


void CDDCServerListenHost::ReplaceHolderIfNeeded() 
{
    if (m_ReloadCorpusNo != -1 && m_pReloadedCorpusHolder != 0) 
    {
        delete LocalCorpora[m_ReloadCorpusNo].m_pHolder->m_pIndexator;
        delete LocalCorpora[m_ReloadCorpusNo].m_pHolder;
        LocalCorpora[m_ReloadCorpusNo].m_pHolder = m_pReloadedCorpusHolder;
        concord_daemon_log(Format("%s was replaced", LocalCorpora[m_ReloadCorpusNo].m_CorpusName.c_str()));
        m_pReloadedCorpusHolder = 0;
        m_ReloadCorpusNo = -1;
     
    }
}

// processing input for one daemon
//  there are two possibilities:
//  1. "run_query" returns results for DDC
//  2. "get_paradigm" returns a paradigm from morphology 
string CDDCServerListenHost::ProcessSocketString(const string& InputSocket, SOCKET rConnectedSocket)
{
	ReplaceHolderIfNeeded();
	m_ErrorStr.clear();
	string Result;

	try {
		concord_daemon_log(Format("%s recv \"%s\"", m_CorpusName.c_str(), InputSocket.c_str()));

		//-- moo: check for buffer overflow
		if (InputSocket.size() > DDC_STATIC_BUFLEN) {
				Result = Format ("\x01 %i %i %i %i %i", errParseError, 0, 0, 0, 0) + "\ninput buffer size exceeded\n";
				throw CExpc(errParseError, Format("CDDCServerListenHost::ProcessSocketString(): input buffer size exceeded"));
		}

		//-- moo: first, get command part of input string
		int eocpos = InputSocket.find_first_of(" \t\r\n\x00\x01\x02");
		if (eocpos==InputSocket.npos) eocpos=InputSocket.size();
		string cmd(InputSocket,0,eocpos);
		//fprintf(stderr, "ServerListenHost: cmd=(%s)\n", cmd.c_str()); //-- DEBUG
		Result.reserve(DDC_STATIC_BUFLEN);

		if (cmd == "run_query") {
			DWORD StartHitNo, ResultLimit;
			int TimeOut;
			char sQuery[DDC_STATIC_BUFLEN];
			char sCorpusName[DDC_STATIC_BUFLEN];
			char sResultType[DDC_STATIC_BUFLEN];
			int CountItems = sscanf (InputSocket.c_str(), 
						 "run_query %[^\x01]\x01%[^\x01]\x01%[^\x01]\x01%i %i %i", 
						 sCorpusName, sQuery, sResultType, &StartHitNo, &ResultLimit, &TimeOut);
			if (CountItems != 6) {
				Result = Format ("\x01 %i %i %i %i %i", errParseError, 0, 0, 0, 0) + "\ncannot parse socket input\n";
				throw CExpc(errParseError, "CDDCServerListenHost::ProcessSocketString(): cannot parse socket input");
			}

			int InternalError;
			int iNetworkError;
			DWORD EndHitNo, HitsCount, RelevantDocsCount;
			string ResultType(sResultType);
			string strQuery(sQuery);
			Trim(ResultType);
			Trim(strQuery);
			if ( strQuery.empty() )
				throw CExpc(errParseError, "CDDCServerListenHost::ProcessSocketString(): cannot parse empty string in socket input");

			string ResultString;
			string HitDistrib;
			string DocDistrib;
			iNetworkError = RunDistributed(strQuery, ResultType, StartHitNo, ResultLimit,
						       InternalError, EndHitNo, HitsCount, TimeOut,
						       ResultString, RelevantDocsCount, HitDistrib, DocDistrib);

			if (CConcHolder::GetResultFormatByString(ResultType) == CConcHolder::DDC_ResultJson) {
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
					  + ",\"hits_\":[\n" + ResultString
					  + "\n]}");
			}
			else if (m_ErrorStr.empty()) {
				//-- normal, error-free result
				Result = ResultString + Format ("\x01 %i %i %i %i %i", InternalError, iNetworkError, EndHitNo, HitsCount, RelevantDocsCount);
			}
			else {
				//-- errors
				Result = Format ("\x01 %i %i %i %i %i", InternalError, iNetworkError, EndHitNo, HitsCount, RelevantDocsCount) + "\n" + m_ErrorStr + "\n";
				m_LogFunction( Format("CDDCServerListenHost::ProcessSocketString(): ERROR: %s", m_ErrorStr.c_str()) );
			}
		}
		else if (cmd == "expand_terms") {
			//-- expand_terms \x01 PIPELINE \x01 TERMS \x01 TIMEOUT [\x01 SUBCORPUS]
			vector<string> qv = stringSplit(InputSocket.c_str(), "\x01");
			if (qv.size() < 4)
				throw CExpc(errParseError, "could not parse expand_terms request");

			//-- get expansion host
			CHost *h=NULL;
			if (qv.size() < 5 || qv[4].empty()) {
				//-- no user-specified expansion host: use first host in m_Hosts
				h = &(m_Hosts[0]);
			} else {
				//-- user-specified expansion host: get matching name from m_Hosts
				string& subcorpus = qv[4];
				for (vector<CHost>::iterator hi=m_Hosts.begin(); hi != m_Hosts.end(); hi++) {
					if (hi->m_CorpusName == subcorpus) {
						h = &(*hi);
						break;
					}
				}
				if (h==NULL)
					throw CExpc(errParseError, "unknown host `%s' in expand_terms request", subcorpus.c_str());
			}

			//-- delegate the query to the user-specified host
			assert(h != NULL);
			string ErrorStr;
			int hsock = h->CreateAndConnectSocket(ErrorStr);
			if (!ErrorStr.empty() || hsock==-1) {
				CloseSocket(hsock);
				throw CExpc(errOther, "could not connect to subcorpus `%s': %s", h->m_CorpusName.c_str(), ErrorStr.c_str());
			}

			const string& hq = InputSocket;
			if (!SendString(hsock, hq, ErrorStr)) {
				CloseSocket(hsock);
				throw CExpc(errOther, "expand_terms faild for subcorpus `%s': %s", h->m_CorpusName.c_str(), ErrorStr.c_str());
			}

			//-- read response directly into Result
			int timeout = atoi(qv[3].c_str());
			if (ReceiveString(hsock, Result, timeout) != neSuccess) {
				CloseSocket(hsock);
				throw CExpc(errOther, "expand_terms failed to read a response from subcorpus `%s'", h->m_CorpusName.c_str());
			}

			//-- ddc annoyingly complains unless each subcorpus socket gets doubled messages: why?!
			string tmp;
			SendString(hsock, "ddc_close_socket", ErrorStr);
			ReceiveString(hsock, tmp, timeout);
			CloseSocket(hsock);
		}
		else if (cmd == "get_paradigm") {
			//-- get_paradigm WORD \x01 LEMMATIZE_BOOL LANG_INT
			char sWord[255];
			int iNurLemmatize, iLangua;
			int CountItems = sscanf (InputSocket.c_str(), "get_paradigm %[^\x01]\x01%i %i", sWord, &iNurLemmatize, &iLangua);
			if (CountItems != 3) {
				Result = ReloadCorpusProcessSignal(InputSocket);
				if (!Result.empty())
					return Result;
				concord_daemon_log("Error:Cannot parse socket input");
				return "";
			}
			int LemmasCount;
			Result = Lemmatize(sWord, (MorphLanguageEnum)iLangua, LemmasCount);
			if (!iNurLemmatize) {
				for (int i = 0; i < LemmasCount; i++) {
					Result += "\n";
					Result += GetParadigm(sWord, i, (MorphLanguageEnum)iLangua);
				}
			}
		}
		else if (cmd == "version") {
			//-- version : distributed server version
			Result = PACKAGE_VERSION;
		}
		else if (cmd == "status" || cmd == "vstatus") {
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

			if (cmd[0]=='v') {
				//-- vstatus: get subcorpus status
				Result += GetSubcorpusJsonArray("status");
			} else {
				//-- status: just get subcorpus names
				for (size_t i=0; i < m_Hosts.size(); ++i) {
					Result += (i==0 ? '[' : ',');
					Result += jsonStr(m_Hosts[i].m_CorpusName);
				}
				Result += "]\n";
			}

			Result += "}\n";
		}
		else if (cmd == "info") {
			//-- info : distributed (collected) corpus info
			Result = (string("{\n")
				  + "\"name\":" + jsonStr(m_CorpusName) + ",\n"
				  + "\"version\":" + jsonStr(PACKAGE_VERSION) + ",\n"
				  + "\"corpora\":" + GetSubcorpusJsonArray("info")
				  + "}\n"
				  );
		}
	}
	catch (CExpc &e) {
		concord_daemon_log(Format("CDDCServerListenHost::ProcessSocketString(): Exception[%d]: %s", e.code(), e.what()));
		if (Result.empty()) Result = Format("%i\x01\n%s", e.code(), e.what());
	}
	catch (exception& e) {
		concord_daemon_log(Format("CDDCServerListenHost::ProcessSocketString(): Exception: %s", e.what()));
		if (Result.empty()) Result = Format("-1\x01\n%s", e.what());
	}

	++m_nRequests;
	return Result;
};


/*
	return false only when a network error occurs
*/
const size_t MaxSubhostsSize = 256;
bool CDDCServerListenHost::ReadPossibleHosts(const string& InputQuery, string& CleanQuery, DwordVector& PossibleHosts) //const
{
	PossibleHosts.reserve(m_Hosts.size());
	int Starter;	
	for (Starter  = InputQuery.length()-1;   Starter >= 0; Starter--)
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


	assert (Starter != string::npos);

	string s = InputQuery.substr(Starter+1);
	Trim(s);
	if (s.empty()) return false;
	StringTokenizer tok(s.c_str(),", ");
	while (tok())
	{
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
	};
	CleanQuery = InputQuery.substr(0, Starter);
	if (PossibleHosts.size() >= MaxSubhostsSize)
	{
		m_ErrorStr = Format("requested subcorpus set too large (%u >= %u)", PossibleHosts.size(), MaxSubhostsSize);
		return false;
	};
	return true;
};


NetworkErrorsEnum CDDCServerListenHost::GetHitStringsFromOneCorpus(CHost& Host,  const string& ResultType,  
								   DWORD StartHitNo, DWORD ResultLimit, int TimeOut, SOCKET& CorpusSocket, int& InternalError, string& Result )
{
	if (CorpusSocket == -1)
	{
		return neNetworkError;
	};

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
		concord_daemon_log ( " Cannot receive a resulting string from a client  " );
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
};


void CDDCServerListenHost::GetFirstHitsFromCorpora(const DwordVector& PossibleHosts,
						   const string Query,  
						   const DWORD ResultLimit, 
						   const int TimeOut,
						   CFirstHitsQueryResult& Result)
{
	Result.m_Sockets.resize(PossibleHosts.size(),-1);
	Result.m_AllHitsCount = 0;
	Result.m_AllRelevantDocsCount = 0;
	Result.m_NetworkError = neSuccess;
	Result.m_InternalError = errNone;
	Result.m_bSort = false;
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
		Result.m_bSort = (iSort!=0);

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


		// reading order ids that  would be used to sort results
		int f = S.find("\t");
		if (f != string::npos)
		{
			StringTokenizer tok(S.c_str() + f +1,"\t");
            char Buffer [CriticalTokenLength +1];
			while (tok())
			{
				CHitToSort HS;
                const char* rest = tok.val();
				if(sscanf(rest, "%i %i %[^ ]", &HS.m_HitNo, &HS.m_OrderId, Buffer) != 3)
				{
					Result.m_NetworkError = neProtocolError;
					return;
				};
                if (strcmp(Buffer, "<empty>"))
                    HS.m_OrderStrId = Buffer;

				HS.m_HostNo = HostNo;
				Result.m_Hits.push_back(HS);
			};
		};
	};

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
};


NetworkErrorsEnum CDDCServerListenHost::RunDistributed(string Query, const string& ResultType, DWORD StartHitNo, 
						       DWORD ResultLimit, int& InternalError, DWORD& EndHitNo, DWORD& HitsCount, 
						       int TimeOut, string& ResultString,
						       DWORD& RelevantDocsCount,
						       string& HitDistrib, string& DocDistrib)
{
	DwordVector PossibleHosts;
	string CleanQuery;
	//  reading possible hosts, using query where these hosts can be specified
	// PossibleHosts is an index of m_Hosts
	if (!ReadPossibleHosts(Query, CleanQuery, PossibleHosts))
		return neSubcorpusNotFound;

	EndHitNo = 0;
	HitsCount = 0;
	ResultString = "";

	CConcHolder::FormatTypeEnum ResultTypeE = CConcHolder::GetResultFormatByString(ResultType);

	// 
	time_t start_get_hits, end_get_hits; 
	if  (TimeOut != -1)
		time(&start_get_hits);
	

	CFirstHitsQueryResult FHResult;
	// reading first StartHiNo+ResultLimit  hits from each host and storing them to Hits

	GetFirstHitsFromCorpora(PossibleHosts, CleanQuery, StartHitNo+ResultLimit, TimeOut, FHResult );
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

	// sorting and trimming
	if (FHResult.m_bSort)
		sort (FHResult.m_Hits.begin(), FHResult.m_Hits.end());

	if (StartHitNo+ResultLimit < FHResult.m_Hits.size())
		FHResult.m_Hits.erase(FHResult.m_Hits.begin()+StartHitNo+ResultLimit, FHResult.m_Hits.end());

	if (StartHitNo < FHResult.m_Hits.size())
		FHResult.m_Hits.erase(FHResult.m_Hits.begin(), FHResult.m_Hits.begin()+StartHitNo);
	else
		FHResult.m_Hits.clear();


	//  creating map from HostNo to  Hits, SortedHits[i] contains all reference to hits from host i
	// in the right order
	vector<int> SortedHits[MaxSubhostsSize];
	for (size_t i=0; i < FHResult.m_Hits.size(); i++)
		SortedHits[FHResult.m_Hits[i].m_HostNo].push_back(i);


	//  getting strings from the hosts:
	// Results[HostNo] - contains all hit strings in the right order
	vector<string> Results[MaxSubhostsSize];
	for (int i=0; i<PossibleHosts.size(); i++)	
	{
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


		StringTokenizer tok(S.c_str(), AdditionalHitDelimeter);
		while (tok()) {
			Results[HostNo ].push_back(tok.val());
			if (ResultTypeE == CConcHolder::DDC_ResultJson) {
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

	// Creating m_QueryResultStr
	for (size_t i=0; i < FHResult.m_Hits.size(); i++)
	{
		BYTE HostNo = FHResult.m_Hits[i].m_HostNo;
		const vector<int>&  V = SortedHits[HostNo];
		if (V.empty()) continue;
		ResultString += Results[ HostNo ][ FHResult.m_Hits[i].m_HitNo - FHResult.m_Hits[V[0]].m_HitNo];
		if (ResultTypeE == CConcHolder::DDC_ResultJson) {
		  //-- add hit-separating comma for json format
		  ResultString += ",\n";
		}
	};
	if (ResultTypeE == CConcHolder::DDC_ResultJson && !ResultString.empty()) {
	  //-- trim final trailing comma
	  ResultString.erase(ResultString.size()-2,1);
	}

	CConcHolder::DecorateQueryResults(ResultType, ResultString);

	if (ResultTypeE == CConcHolder::DDC_ResultText)
	{
		// we always write relevant document numbers (RelevantDocsDistributionStr) to output, 
		// even though it is not specified in the option file of the coprus threads.
		// The problem is, that daemon doesn't know anything about options files of their coprus threads.
		ResultString = FHResult.m_HitsDistributionStr + FHResult.m_RelevantDocsDistributionStr+ResultString;
	}
	HitDistrib = FHResult.m_HitsDistributionStr.substr(21,FHResult.m_HitsDistributionStr.size()-23);
	DocDistrib = FHResult.m_RelevantDocsDistributionStr.substr(32,FHResult.m_RelevantDocsDistributionStr.size()-34);

	EndHitNo = StartHitNo + FHResult.m_Hits.size();

	return neSuccess;	
};



//=====================================================================
//===========================   global functions  =====================
//=====================================================================


void LoadLocalCorpora (ProtocolDensityEnum ProtocolDensity, string ConfigFile)
{
	string Error;
	if (!IsRmlRegistered(Error)) 
	{
		concord_daemon_log ( Error  );
		return;
	};
	string IniPath = GetIniFilePath();

	{
		int ii = ConfigFile.find("$RML");
		if (ii != string::npos)
				ConfigFile.replace(ii, 4, IniPath);
	};

	concord_daemon_log ( Format ("Start loading corpora from %s", ConfigFile.c_str()) );
	vector<CHost> Hosts;
	LoadHosts(ConfigFile, Hosts);


	concord_daemon_log ( Format("  Found %i Hosts ", Hosts.size()) );
	LocalCorpora.clear();

	try {	
		for (int i = 0; i<Hosts.size(); i++) {
			CDDCCorpusListenHost H(true, ProtocolDensity);
			H.CopyAddressParametersFrom(Hosts[i]);
			if (!H.LoadHolder())
				throw CExpc(errOther, "LoadHolder() failed for host %d", i);
			LocalCorpora.push_back(H);
		}
		for (int i = 0; i<LocalCorpora.size(); i++) {
			CDDCCorpusListenHost& H = LocalCorpora[i];
			H.CreateListener();
		}
	}
	catch (CExpc     &e) { concord_daemon_log( Format("LoadLocalCorpora(): Exception[%d]: %s", e.code(), e.what()) ); throw; }
	catch (exception &e) { concord_daemon_log( Format("LoadLocalCorpora(): Exception: %s", e.what()) ); throw; }
	catch (...)          { concord_daemon_log( "LoadLocalCorpora(): Exception: unhandled exception" ); throw; }
};

void LoadDDCServer (ProtocolDensityEnum ProtocolDensity, string ServerConfigFile)
{
	string Error;
	if (!IsRmlRegistered(Error)) 
	{
		concord_daemon_log ( Error  );
		return;
	};
	string IniPath = GetIniFilePath();
	{
		int ii = ServerConfigFile.find("$RML");
		if (ii != string::npos)
				ServerConfigFile.replace(ii, 4, IniPath);
	};

	if (pServer)
		delete pServer;
	pServer = new CDDCServerListenHost(false, ProtocolDensity);
	if (!pServer)
	{
		concord_daemon_log ( "Error! cannot allocate memory for a server instance");
		return;
	};
	
	LoadHosts(ServerConfigFile, pServer->m_Hosts);
	if (pServer->m_Hosts.empty())
	{
		delete pServer;
		pServer = 0;
		return;
	};
	bool bServerIsFound = false;	
	for (int i = 0; i<pServer->m_Hosts.size(); i++)
	if (pServer->m_Hosts[i].m_CorpusName == "server")
	{
		pServer->CopyAddressParametersFrom(pServer->m_Hosts[i]);
		pServer->m_LogFunction = concord_daemon_log;;
		pServer->CreateListener();
		pServer->m_Hosts.erase(pServer->m_Hosts.begin() + i);
		bServerIsFound = true;
		break;
	}

	if (!bServerIsFound)
	{
		concord_daemon_log ( Format("Error! there is no server socket description in %s!", ServerConfigFile.c_str()));
		return;

	};
	if (pServer->m_Hosts.empty())
	{
		concord_daemon_log ( Format("Error! there is no ouptut server  sockets in %s!", ServerConfigFile.c_str()));
		return;

	};

};


void UnloadLocalCorporaAndServer ()
{
	for (int i =0 ;  i<LocalCorpora.size(); i++)
	{
		delete LocalCorpora[i].m_pHolder->m_pIndexator;
		delete LocalCorpora[i].m_pHolder;
	};

	LocalCorpora.clear();

	// stop server
	delete pServer;
	pServer = 0;
};



string CDDCServerListenHost::GetSubcorpusJsonArray(const string& request, int timeout)
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

		//-- send doubled messages to avoid ddc complaints of the form 'Cannot receive string for corpus "corpus2" (error: Could not receive data to a socket)'
		errorStr.clear();
		SendString(Sockets[i], "ddc_close_socket", errorStr);
	}

	//-- get responses for "ddc_close_socket" messages
	for (i=0; i < m_Hosts.size(); ++i) {
		if (Sockets[i] == -1) continue;

		errorStr.clear();
		ReceiveString(Sockets[i], errorStr, timeout);
		CloseSocket(Sockets[i]);
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

