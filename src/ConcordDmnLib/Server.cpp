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

#include "Server.h"
#include "Morphan.h"

#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif

#ifdef HAVE_NETDB_H
# include <netdb.h>
#endif

//==============================================================================

const char *CDDCServer::AdditionalHitDelimeter = "\x01";

//----------------------------------------------------------------------
CDDCServer::CDDCServer(bool bDoubleMessage, ProtocolDensityEnum pdProtocolDensity)
    : CHost(bDoubleMessage, pdProtocolDensity),
      m_tStarted(0),
      m_nRequests(0),
      m_bLogRequests(false)
{
    m_LogFunction = concord_daemon_log;
    m_tStarted = time(NULL);

    //-- attempt to set m_FQHostName
#if HAVE_UNISTD_H
    char hostname[1024];
    memset(hostname,0,1024);
    gethostname(hostname, 1023);
# if HAVE_NETDB_H
    struct hostent *h = gethostbyname(hostname);
    m_FQHostName = h ? h->h_name : hostname;
# else
    m_FQHostName = hostname;
# endif
#else
    m_FQHostName = m_HostAddr;
#endif
};


//----------------------------------------------------------------------
//void errorString(

//----------------------------------------------------------------------
string CDDCServer::ProcessSocketString(const string& SocketInput, SOCKET& rConnectedSocket)
{
    string Result;
    try {
    	//-- moo: check for buffer overflow
	if (SocketInput.size() > DDC_STATIC_BUFLEN) {
	    string req(SocketInput.substr(0,DDC_STATIC_BUFLEN-3));
	    throw CExpc(errParseError, Format("input buffer size %zi exceeded by request \"%s...\"", DDC_STATIC_BUFLEN, req.c_str()));
	}
	
	//-- moo: parse input command
	int eocpos = SocketInput.find_first_of(" \t\r\n\x00\x01\x02");
	if (eocpos==SocketInput.npos) eocpos=SocketInput.size();
	string cmd(SocketInput,0,eocpos);
	//fprintf(stderr, "Server: cmd=(%s)\n", cmd.c_str()); //-- DEBUG
	//Result.reserve(DDC_STATIC_BUFLEN);

	//-- moo: maybe log request
	if (m_bLogRequests && m_noLogCommands.find(cmd)==m_noLogCommands.end())
	    m_LogFunction(Format("%s recv \"%s\"", m_CorpusName.c_str(), SocketInput.c_str()));

	//-- moo: command parsing and dispatch
	if (cmd == "get_first_hits") {
	    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	    // get_first_hits QUERY "\x01" TIMEOUT " " LIMIT  : get keys of first hits (leaf-node only)
	    try {
		int	TimeOut, ResultLimit;
		char sQuery[DDC_STATIC_BUFLEN];
		const char* SocketInputStr = SocketInput.c_str();
		int nItems = sscanf (SocketInputStr, "get_first_hits %[^\x01]\x01 %i %i", sQuery, &TimeOut, &ResultLimit);
		if (nItems != 3)
		    throw CExpc(errParseError, "CDDCServer::ProcessSocketString(): cannot parse `get_first_hits' request");
		this->handle__get_first_hits(Result, sQuery, TimeOut, ResultLimit);
	    }
	    catch (CExpc& e) {
		Result = Format("%i 0 0 0 0\n%s", e.code(), e.what());
	    }
	    catch (exception& e) {
		Result = Format("%i 0 0 0 0\n%s", -1, e.what());
	    }
	}
	else if (cmd == "get_hit_strings") {
	    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	    // get_hit_strings " " FORMAT "\x01" OFFSET " " LIMIT : get full hit strings (leaf only)
	    try {
		int StartHitNo, ResultLimit;
		char sResultType[128];
		int nItems = sscanf(SocketInput.c_str(), "get_hit_strings %[^\x01]\x01%i %i", sResultType, &StartHitNo, &ResultLimit);
		if (nItems != 3)
		    throw CExpc(errParseError, "CDDCServer::ProcessSocketString(): cannot parse `get_hit_strings' request");
		this->handle__get_hit_strings(Result, sResultType,StartHitNo,ResultLimit);
	    }
	    catch (CExpc& e) {
		Result = Format("%i\x01%s", e.code(), e.what());
	    }
	    catch (exception& e) {
		Result = Format("%i\x01%s", -1, e.what());
	    }
	}
	else if (cmd == "run_query") {
	    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	    // run_query " " CORPUS "\x01" QUERY "\x01" FORMAT "\x01" OFFSET " " LIMIT " " TIMEOUT : user query (branch-node only)
	    try {
		int StartHitNo, ResultLimit;
		int TimeOut;
		char sQuery[DDC_STATIC_BUFLEN];
		char sCorpusName[DDC_STATIC_BUFLEN]; //-- unused?
		char sResultType[DDC_STATIC_BUFLEN];
		int nItems = sscanf(SocketInput.c_str(), 
					"run_query %[^\x01]\x01%[^\x01]\x01%[^\x01]\x01%i %i %i", 
					sCorpusName, sQuery, sResultType, &StartHitNo, &ResultLimit, &TimeOut);
		if (nItems != 6)
		    throw CExpc(errParseError, "cannot parse `run_query` request");
		this->handle__run_query(Result, sCorpusName,sQuery,sResultType,StartHitNo,ResultLimit,TimeOut);
	    }
	    catch (CExpc &e) {
		Result = Format("\x01 %i %i %i %i %i\n%s", e.code(), 0, 0, 0, 0, e.what());
	    }
	    catch (exception &e) {
		Result = Format("\x01 %i %i %i %i %i\n%s", errOther, 0, 0, 0, 0, e.what());
	    }
	}
	else if (cmd == "expand_terms") {
	    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	    // expand_terms "\x01" PIPELINE "\x01" TERMS "\x01" TIMEOUT ["\x01" CORPUS] : term expansion (leaf|branch)
	    vector<string> qv = stringSplit(SocketInput.c_str(), "\x01");
	    if (qv.size() < 4)
		throw CExpc(errParseError, "could not parse `expand_terms' request");
	    else if (qv.size() < 5)
		qv.push_back("");
	    string &pipeline = qv[1];
	    string &terms    = qv[2];
	    int     timeout  = atoi(qv[3].c_str());
	    string &corpus   = qv[4];
	    this->handle__expand_terms(Result, pipeline,terms,timeout,corpus);
	}
	else if (cmd == "get_paradigm") {
	    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	    // get_paradigm " " WORD "\x01" LEMMATIZE_BOOL " " LANG_INT
	    char sWord[DDC_STATIC_BUFLEN];
	    int iLemmatizeOnly, iLang;
	    int nItems = sscanf(SocketInput.c_str(), "get_paradigm %[^\x01]\x01%i %i", sWord, &iLemmatizeOnly, &iLang);
	    if (nItems != 3)
		throw CExpc(errParseError, "cannot parse `get_paradigm` request");
	    this->handle__get_paradigm(Result, sWord,iLemmatizeOnly,iLang);
	}
	else if (cmd == "ddc_close_socket" || cmd == "close_socket" || cmd == "close") {
	    //--  close
	    this->handle__close_socket(Result, rConnectedSocket);
	}
	else if (cmd == "version") {
	    //-- version : server version
	    this->handle__version(Result);
	}
	else if (cmd == "status") {
	    //-- status : server status (brief)
	    this->handle__status(Result);
	}
	else if (cmd == "vstatus") {
	    //-- vstatus [TIMEOUT] : server status (verbose)
	    int timeout = strtol(SocketInput.substr(eocpos).c_str(),NULL,0);
	    this->handle__vstatus(Result, timeout);
	}
	else if (cmd == "info") {
	    //-- info [TIMEOUT]: sever info (brief)
	    int timeout = strtol(SocketInput.substr(eocpos).c_str(),NULL,0);
	    this->handle__info(Result, timeout);
	}
	else if (cmd == "vinfo") {
	    //-- vinfo [TIMEOUT]: sever info (verbose)
	    int timeout = strtol(SocketInput.substr(eocpos).c_str(),NULL,0);
	    this->handle__vinfo(Result, timeout);
	}
	else if (cmd == "reload") {
	    //-- reload [DEPTH]
	    int depth = strtol(SocketInput.substr(eocpos).c_str(),NULL,0);
	    this->handle__reload(Result, depth);
	}
	else if (cmd == "clear_cache") {
	    //-- clear_cache [DEPTH]
	    int depth = strtol(SocketInput.substr(eocpos).c_str(),NULL,0);
	    this->handle__clear_cache(Result, depth);
	}
	else {
	    //-- unknown request
	    throw CExpc(errParseError, Format("unknown command `%s'", cmd.c_str()));
	}
    }
    catch (CExpc &e) {
	m_LogFunction(Format("CDDCServer[%s]::ProcessSocketString(): Exception[%d]: %s", m_CorpusName.c_str(), e.code(), e.what()));
	if (Result.empty()) Result = Format("%i 0\n%s", e.code(), e.what());
    }
    catch (exception& e) {
	m_LogFunction(Format("CDDCServer[%s]::ProcessSocketString(): Exception: %s", m_CorpusName.c_str(), e.what()));
	if (Result.empty()) Result = Format("%i 0\n%s", -1, e.what());
    }

    ++m_nRequests;
    return Result;
}


//----------------------------------------------------------------------
void CDDCServer::handle__get_first_hits(string &Result, const char *Query, int TimeOut, int ResultLimit)
{
    method_not_implemented("handle__get_first_hits()");
}

//----------------------------------------------------------------------
void CDDCServer::handle__get_hit_strings(string &Result, const char *ResultType, int StartHitNo, int ResultLimit)
{
    method_not_implemented("handle__get_hit_strings()");
}

//----------------------------------------------------------------------
void CDDCServer::handle__run_query(string &Result, const char *CorpusName, const char *Query, const char *ResultType, int StartHitNo, int ResultLimit, int TimeOut)
{
    method_not_implemented("handle__run_query()");
}

//----------------------------------------------------------------------
void CDDCServer::handle__expand_terms(string &Result, const string& pipeline, const string& terms, int timeout, const string &corpus)
{
    method_not_implemented("handle__expand_terms()");
}

//----------------------------------------------------------------------
void CDDCServer::handle__get_paradigm(string &Result, const char *Word, int iLemmatizeOnly, int iLang)
{
    int LemmaCount;
    Result = Lemmatize(Word, (MorphLanguageEnum)iLang, LemmaCount);
    if (!iLemmatizeOnly) {
	for (int i = 0; i < LemmaCount; i++) {
	    Result += "\n";
	    Result += GetParadigm(Word, i, (MorphLanguageEnum)iLang);
	}
    }

}

//----------------------------------------------------------------------
void CDDCServer::handle__close_socket(string &Result, SOCKET& rConnectedSocket)
{
    m_bExpectMore = false;
    m_bRespond    = false;
    this->Close(rConnectedSocket);
}

//----------------------------------------------------------------------
void CDDCServer::handle__version(string &Result)
{
    Result = PACKAGE_VERSION;
}

//----------------------------------------------------------------------
void CDDCServer::handle__status(string &Result, int timeout, bool verbose)
{
    method_not_implemented("handle__status");
}

//----------------------------------------------------------------------
void CDDCServer::handle__vstatus(string &Result, int timeout)
{
    this->handle__status(Result,timeout,true);
}

//----------------------------------------------------------------------
void CDDCServer::handle__info(string &Result, int timeout, bool verbose)
{
    method_not_implemented("handle__info()");
}

//----------------------------------------------------------------------
void CDDCServer::handle__vinfo(string &Result, int timeout)
{
    this->handle__info(Result,timeout,true);
}

//----------------------------------------------------------------------
void CDDCServer::handle__reload(string &Result, int depth)
{
    method_not_implemented("handle__reload()");
}

//----------------------------------------------------------------------
void CDDCServer::handle__clear_cache(string &Result, int depth)
{
    method_not_implemented("handle__clear_cache()");
}

//==============================================================================

//----------------------------------------------------------------------
size_t CDDCServer::residentMemorySize(void)
{
    DDCProcessMemoryStatus pms;
    pms.fetch();
    return pms.resident;
}
