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

#include "Server.h"
#include "ServerThread.h"
#include "Morphan.h"
#include "../CommonLib/ddcTime.h"

#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif

#ifdef HAVE_NETDB_H
# include <netdb.h>
#endif

//==============================================================================
// CDDCServer

const char *CDDCServer::AdditionalHitDelimiter = "\x01";

//----------------------------------------------------------------------
CDDCServer::CDDCServer()
    : m_VersionCompat(DDCVersionT::current()),
      m_tStarted(0),
      m_bLogRequests(false),
      m_nWorkers(0),
      m_ThreadQueueSize(DDC_DEFAULT_THREAD_QUEUE_SIZE),
      m_SlowQueryTimeout(10),
      m_WorkerId(0),
      m_ThreadPool(NULL)
{
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
void CDDCServer::Shutdown(bool quiet)
{
    if (m_ThreadPool) {
        if (!quiet)
            ddcLogInfo(Format("shutting down worker thread(s) for server %s", m_CorpusName.c_str()));
        m_ThreadPool->stop();
    }

    if (!quiet) {
        if (m_WorkerId) {
            ddcLogDebug(Format("shutting down worker thread #%zd for server %s", m_WorkerId, m_CorpusName.c_str()));
        } else {
            ddcLogDebug(Format("shutting down main thread for server %s", m_CorpusName.c_str()));
        }
    }
    CloseListenSocket();
};

//----------------------------------------------------------------------
void CDDCServer::SetOptions(const CDDCServerOptions &Options)
{
    if (Options.m_LogLevel > ddcLLUnknown)
        SetLogLevel(Options.m_LogLevel);
    m_VersionCompat = Options.m_VersionCompat;
    m_SlowQueryTimeout = Options.m_SlowQueryTimeout;
    //m_ServerStats.m_qTimes.m_Window = Options.m_StatsWindow;
    m_nWorkers = Options.m_nWorkers;
    m_ThreadQueueSize = Options.m_ThreadQueueSize;
    m_UnixSocketPerms = Options.m_UnixSocketPerms;

    if (m_VersionCompat > DDCVersionT::current()) {
        ddcLogWarn(Format("WARNING: requested VersionCompat (%s) is newer than current DDC (%s)", m_VersionCompat.str().c_str(), DDCVersionString()));
    }
    else if (m_VersionCompat < DDCVersionT::current()) {
        ddcLogInfo(Format("enabling compatibility mode ~ v%s", m_VersionCompat.str().c_str()));
    }
};

//----------------------------------------------------------------------
void CDDCServer::StartClientThreads()
{
    if (m_nWorkers == 0) {
        //-- serial mode
        if (m_ThreadPool) delete m_ThreadPool;
        m_ThreadPool = NULL;
        ddcLogInfo("client-threads disabled; running in serial mode");
    }
    else {
        //-- client-thread mode
        if (!m_ThreadPool)
            m_ThreadPool = new CDDCServerThreadPool();
        m_ThreadPool->start(this, m_nWorkers, m_ThreadQueueSize);
    }
}

//----------------------------------------------------------------------
void CDDCServer::WorkerCloneInit(const CDDCServer *Parent, size_t WorkerId)
{
    *this = *Parent;

    //-- local overrides
    this->m_WorkerId = WorkerId;
    StopListening();

    m_ThreadPool = NULL;
}

//----------------------------------------------------------------------
void CDDCServer::WorkerCloneFree()
{
}

//----------------------------------------------------------------------
void CDDCServer::RunThread()
{
    this->StartClientThreads();
    CHost::RunThread();
};

//----------------------------------------------------------------------
void CDDCServer::HandleClientConnection(SOCKET& rConnectedSocket)
{
    m_SessionStats.clear();
    if (UseClientThreads()) {
        //-- +pthread, client-thread mode
        m_ThreadPool->m_Queue.add(rConnectedSocket);
        ddcLogTrace(Format("queued thread-pool item for client %s", SocketPeer(rConnectedSocket).c_str()));
    }
    else {
        //-- serial mode or worker
        CHost::HandleClientConnection(rConnectedSocket);
        m_ServerStats += m_SessionStats;
    }
}

//----------------------------------------------------------------------
string CDDCServer::ProcessSocketString(const string& SocketInput, SOCKET& rConnectedSocket)
{
    string Result;
    bool isQueryRequest=false, isFollowupRequest=false, isExpandRequest=false;
    DDCTimeHiRes t_started = DDCTimeHiRes::Now();

    //-- initialize with default values
    m_bRespond    = true;
    m_bExpectMore = false;

    try {
        //-- moo: check for buffer overflow
        if (SocketInput.size() > DDC_STATIC_BUFLEN) {
            string req(SocketInput.substr(0,DDC_STATIC_BUFLEN-3));
            throw CExpc(errParseError, Format("input buffer size %zi exceeded by request \"%s...\"", DDC_STATIC_BUFLEN, req.c_str()));
        }
        
        //-- moo: parse input command
        size_t eocpos = SocketInput.find_first_of(" \t\r\n\x00\x01\x02");
        if (eocpos==SocketInput.npos) eocpos=SocketInput.size();
        string cmd(SocketInput,0,eocpos);

        //-- moo: maybe log request
        if (m_bLogRequests && m_noLogCommands.find(cmd)==m_noLogCommands.end()) {
            ddcLogInfo(Format("%s recv \"%s\"", m_CorpusName.c_str(), SocketInput.c_str()));
        } else if (ddcLogLevel >= ddcLLTrace) {
            ddcLogInfo(Format("%s recv \"%s\"", m_CorpusName.c_str(), SocketInput.c_str()));
        }

        //-- moo: command parsing and dispatch
        if (cmd == "get_first_hits") {
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // get_first_hits QUERY "\x01" TIMEOUT " " LIMIT              : get keys of hits [0,LIMIT)             (<  v2.1.9)
            // get_first_hits QUERY "\x01" TIMEOUT " " LIMIT  (" " HINT)? : get keys of hits [OFFSET,OFFSET+LIMIT) (>= v2.1.9)
            //                                                              where HINT = OFFSET ("(" DTR_OFFSETS ")")? (" " MINKEY)?
            ++m_SessionStats.m_nQueries;
            isQueryRequest = true;
            try {
                int TimeOut, StartPathPos;
                size_t ResultLimit, PathPos,HintPos;
                char sQuery[DDC_STATIC_BUFLEN];
                const char* SocketInputStr = SocketInput.c_str();

                //-- parse mandatory arguments (QUERY, TIMEOUT, LIMIT)
                int nItems = sscanf(SocketInputStr, "get_first_hits %[^\x01]\x01 %i %zi%n", sQuery, &TimeOut, &ResultLimit, &StartPathPos);
                if (nItems != 3) {
                    //-- unparseable
                    throw CExpc(errParseError, "CDDCServer::ProcessSocketString(): cannot parse `get_first_hits' request");
                }

                findPathHint(SocketInput, StartPathPos, PathPos, HintPos);
                this->handle__get_first_hits(Result, sQuery, TimeOut, ResultLimit,
                                             SocketInput.substr(PathPos,HintPos-PathPos),
                                             NavHint(SocketInput.substr(HintPos)));
            }
            catch (CExpc& e) {
                Result = Format("%i 0 0 0 0\n%s", (e.code()==errNone ? errOther : e.code()), e.what());
                ++m_SessionStats.m_nErrors;
            }
            catch (exception& e) {
                Result = Format("%i 0 0 0 0\n%s", -1, e.what());
                ++m_SessionStats.m_nErrors;
            }
        }
        else if (cmd == "get_hit_strings") {
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // get_hit_strings " " FORMAT "\x01" OFFSET " " LIMIT : get full hit strings
            isFollowupRequest = true;
            try {
                size_t StartHitNo, ResultLimit;
                char sResultType[128];
                int nItems = sscanf(SocketInput.c_str(), "get_hit_strings %[^\x01]\x01%zi %zi", sResultType, &StartHitNo, &ResultLimit);
                if (nItems != 3)
                    throw CExpc(errParseError, "CDDCServer::ProcessSocketString(): cannot parse `get_hit_strings' request");
                this->handle__get_hit_strings(Result, sResultType,StartHitNo,ResultLimit);
            }
            catch (CExpc& e) {
                Result = Format("%i\x01%s", (e.code()==errNone ? errOther : e.code()), e.what());
                ++m_SessionStats.m_nErrors;
            }
            catch (exception& e) {
                Result = Format("%i\x01%s", -1, e.what());
                ++m_SessionStats.m_nErrors;
            }
        }
        else if (cmd == "run_query") {
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // run_query " " CORPUS "\x01" QUERY "\x01" FORMAT "\x01" START " " LIMIT " " TIMEOUT             : full query           (<  v2.1.9)
            // run_query " " CORPUS "\x01" QUERY "\x01" FORMAT "\x01" START " " LIMIT " " TIMEOUT (" " HINT)? : full query with hint (>= v2.1.9)
            ++m_SessionStats.m_nQueries;
            isQueryRequest = true;
            try {
                size_t StartHitNo, ResultLimit, PathPos,HintPos;
                int TimeOut, StartPathPos;
                char sQuery[DDC_STATIC_BUFLEN];
                char sCorpusName[DDC_STATIC_BUFLEN]; //-- unused?
                char sResultType[DDC_STATIC_BUFLEN];
                const char* SocketInputStr = SocketInput.c_str();
                int nItems = sscanf(SocketInputStr,
                                    "run_query %[^\x01]\x01%[^\x01]\x01%[^\x01]\x01%zi %zi %i%n",
                                    sCorpusName, sQuery, sResultType, &StartHitNo, &ResultLimit, &TimeOut, &StartPathPos);
                if (nItems != 6)
                    throw CExpc(errParseError, "cannot parse `run_query` request");

                findPathHint(SocketInput, StartPathPos, PathPos, HintPos);
                this->handle__run_query(Result, sCorpusName,sQuery,sResultType,StartHitNo,ResultLimit,TimeOut,
                                        SocketInput.substr(PathPos,HintPos-PathPos),
                                        NavHint(SocketInput.substr(HintPos)));
            }
            catch (CExpc &e) {
                Result = Format("\x01 %i %i %i %i %i\n%s", e.code(), 0, 0, 0, 0, e.what());
                ++m_SessionStats.m_nErrors;
            }
            catch (exception &e) {
                Result = Format("\x01 %i %i %i %i %i\n%s", errOther, 0, 0, 0, 0, e.what());
                ++m_SessionStats.m_nErrors;
            }
        }
        else if (cmd == "expand_terms") {
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // expand_terms "\x01" PIPELINE "\x01" TERMS "\x01" TIMEOUT ["\x01" CORPUS] : term expansion (leaf|branch)
            ++m_SessionStats.m_nExpand;
            isExpandRequest = true;
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
            ++m_SessionStats.m_nExpand;
            isExpandRequest = true;
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
        else if (cmd == "nodes") {
            //-- nodes [DEPTH]
            int depth = (eocpos >= SocketInput.size()
                         ? -1
                         : strtol(SocketInput.substr(eocpos).c_str(),NULL,0));
            this->handle__nodes(Result, depth);
        }
        else {
            //-- unknown request
            throw CExpc(errParseError, Format("unknown command `%s'", cmd.c_str()));
        }
    }
    catch (CExpc &e) {
        ddcLogError(Format("CDDCServer[%s]::ProcessSocketString(): Exception[%d]: %s", m_CorpusName.c_str(), e.code(), e.what()));
        if (Result.empty()) Result = Format("%i 0\n%s", e.code(), e.what());
        ++m_SessionStats.m_nErrors;
    }
    catch (exception& e) {
        ddcLogError(Format("CDDCServer[%s]::ProcessSocketString(): Exception: %s", m_CorpusName.c_str(), e.what()));
        if (Result.empty()) Result = Format("%i 0\n%s", -1, e.what());
        ++m_SessionStats.m_nErrors;
    }

    //-- get query time
    double t_elapsed = DDCTimeHiRes::Now().Elapsed(t_started);
    if (isQueryRequest)
        m_SessionStats.m_qTimes.Append(t_elapsed);
    else if (isFollowupRequest)
        m_SessionStats.m_qTimes.AppendTotal(t_elapsed);
    else if (isExpandRequest)
        m_SessionStats.m_xTimes.Append(t_elapsed);
    
    //-- check for slow queries
    if (m_SlowQueryTimeout > 0 && t_elapsed > m_SlowQueryTimeout) {
        ddcLogWarn(Format("WARNING: slow request (%gs > %gs): %s", t_elapsed, m_SlowQueryTimeout, SocketInput.c_str()));
        ++m_SessionStats.m_nSlow;
    }

    ++m_SessionStats.m_nRequests;
    return Result;
}

//----------------------------------------------------------------------
void CDDCServer::handle__get_first_hits(string &Result, const char *Query, int TimeOut, size_t ResultLimit, const string& ReqPath, const NavHint& Hint)
{
    m_bExpectMore = true;
    method_not_implemented("handle__get_first_hits()");
}

//----------------------------------------------------------------------
void CDDCServer::handle__get_first_hits(string &Result, const char *Query, int TimeOut, size_t ResultLimit)
{
    this->handle__get_first_hits(Result,Query,TimeOut,ResultLimit,string(""),NavHint());
}

//----------------------------------------------------------------------
void CDDCServer::handle__get_hit_strings(string &Result, const char *ResultType, size_t StartHitNo, size_t ResultLimit)
{
    method_not_implemented("handle__get_hit_strings()");
}

//----------------------------------------------------------------------
void CDDCServer::handle__run_query(string &Result, const char *CorpusName, const char *Query, const char *ResultType, size_t StartHitNo, size_t ResultLimit, int TimeOut, const string& ReqPath, const NavHint& Hint)
{
    method_not_implemented("handle__run_query()");
}

//----------------------------------------------------------------------
void CDDCServer::handle__run_query(string &Result, const char *CorpusName, const char *Query, const char *ResultType, size_t StartHitNo, size_t ResultLimit, int TimeOut)
{
    this->handle__run_query(Result,CorpusName,Query,ResultType,StartHitNo,ResultLimit,TimeOut,string(""),NavHint());
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
    m_bRespond = false;
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

//----------------------------------------------------------------------
void CDDCServer::handle__nodes(string &Result, int depth)
{
    method_not_implemented("handle__nodes()");
}

//==============================================================================

//----------------------------------------------------------------------
size_t CDDCServer::residentMemorySize(void) const
{
    DDCProcessMemoryStatus pms(getpid());
    return pms.VmRSS;
}

//----------------------------------------------------------------------
size_t CDDCServer::totalMemorySize(void) const
{
    DDCProcessMemoryStatus pms(getpid());
    return pms.VmSize;
}

//----------------------------------------------------------------------
void CDDCServer::findPathHint(const string& ReqStr, size_t StartPos, size_t &PathPos, size_t &HintPos)
{
    //-- skip initial whitespace
    for (PathPos=StartPos; PathPos < ReqStr.size() && isspace(ReqStr[PathPos]); ++PathPos) ;

    //-- check whether path was specified (must begin with a non-digit and contain no whitespace)
    if (PathPos < ReqStr.size() && !isdigit(ReqStr[PathPos])) {
        for (HintPos=PathPos; HintPos < ReqStr.size() && !isspace(ReqStr[HintPos]); ++HintPos) ;
    } else {
        HintPos = PathPos;
    }
    
    return;
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
