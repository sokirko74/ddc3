#include "Server.h"
#include "Morphan.h"
#include "CommonLib/ddcTime.h"

#include <atomic>
#include <map>
#include <set>
#include <mutex>

#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif

#ifdef HAVE_NETDB_H
# include <netdb.h>
#endif

using namespace std;

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
      m_WorkerId(0)
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
void CDDCServer::WorkerCloneInit(const CDDCServer *Parent, size_t WorkerId)
{
    *this = *Parent;

    //-- local overrides
    this->m_WorkerId = WorkerId;
    StopListening();
}

//----------------------------------------------------------------------
void CDDCServer::WorkerCloneFree()
{
}

//----------------------------------------------------------------------
namespace {
    //-- the stats of the parent servers are updated by several worker threads
    std::mutex StatsMutex;
    std::atomic<size_t> NextWorkerId(1);

    struct WorkerCloneDeleter {
        void operator()(CDDCServer* clone) const {
            clone->WorkerCloneFree();
            delete clone;
        }
    };
    typedef std::unique_ptr<CDDCServer, WorkerCloneDeleter> WorkerClonePtr;

    //-- worker clones of the current thread, by parent server
    thread_local std::map<const CDDCServer*, WorkerClonePtr> ThreadClones;
}

//----------------------------------------------------------------------
string CDDCServer::HandleRequest(const CRequest& Request)
{
    static const std::set<string> Commands = {
        "get_first_hits", "get_hit_strings", "run_query", "expand_terms", "get_paradigm",
        "version", "status", "vstatus", "info", "vinfo", "reload", "clear_cache", "nodes",
    };
    if (Commands.find(Request.Command) == Commands.end())
        throw CDDCExpc(errParseError, Format("unknown command `%s'", Request.Command.c_str()));  //-- http status 400

    WorkerClonePtr& clone = ThreadClones[this];
    if (!clone) {
        size_t workerId = NextWorkerId++;
        clone.reset(this->WorkerClone());
        clone->WorkerCloneInit(this, workerId);
        ddc_thread_init(Format("%s#%zu", m_CorpusName.c_str(), workerId).c_str());
        ddcLogDebug(Format("started worker #%zu for server %s", workerId, m_CorpusName.c_str()));
    }
    {
        //-- adopt the parent stats, so that the status reports them accurately
        std::lock_guard<std::mutex> lock(StatsMutex);
        clone->m_ServerStats = m_ServerStats;
    }
    clone->m_SessionStats.clear();
    string Result = clone->ProcessRequest(Request);
    if (!clone->m_bExpectMore)
        clone->EndSession();
    {
        std::lock_guard<std::mutex> lock(StatsMutex);
        m_ServerStats += clone->m_SessionStats;
    }
    return Result;
}

//----------------------------------------------------------------------
string CDDCServer::ProcessRequest(const CRequest& Request)
{
    string Result;
    bool isQueryRequest=false, isFollowupRequest=false, isExpandRequest=false;
    DDCTimeHiRes t_started = DDCTimeHiRes::Now();
    const string& cmd = Request.Command;

    m_bExpectMore = false;

    try {
        //-- maybe log request
        if ((m_bLogRequests && m_noLogCommands.find(cmd)==m_noLogCommands.end()) || ddcLogLevel >= ddcLLTrace) {
            ddcLogInfo(Format("%s recv \"%s\"", m_CorpusName.c_str(), Request.toString().c_str()));
        }

        //-- command parsing and dispatch
        if (cmd == "get_first_hits") {
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // get_first_hits query timeout limit [path] [hint] : get keys of hits [OFFSET,OFFSET+LIMIT)
            //   where hint = OFFSET ("(" DTR_OFFSETS ")")? (" " MINKEY)?
            ++m_SessionStats.m_nQueries;
            isQueryRequest = true;
            try {
                this->handle__get_first_hits(Result, Request.Get("query").c_str(),
                                             Request.GetInt("timeout"), Request.GetInt("limit"),
                                             Request.Get("path", ""), NavHint(Request.Get("hint", "")));
            }
            catch (CExpc& e) {
                Result = Format("%i 0 0 0 0\n%s", (ddcExpcCode(e)==errNone ? errOther : ddcExpcCode(e)), e.what());
                ++m_SessionStats.m_nErrors;
            }
            catch (exception& e) {
                Result = Format("%i 0 0 0 0\n%s", -1, e.what());
                ++m_SessionStats.m_nErrors;
            }
        }
        else if (cmd == "get_hit_strings") {
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // get_hit_strings format start limit : get full hit strings
            isFollowupRequest = true;
            try {
                this->handle__get_hit_strings(Result, Request.Get("format").c_str(),
                                              Request.GetInt("start"), Request.GetInt("limit"));
            }
            catch (CExpc& e) {
                Result = Format("%i\x01%s", (ddcExpcCode(e)==errNone ? errOther : ddcExpcCode(e)), e.what());
                ++m_SessionStats.m_nErrors;
            }
            catch (exception& e) {
                Result = Format("%i\x01%s", -1, e.what());
                ++m_SessionStats.m_nErrors;
            }
        }
        else if (cmd == "run_query") {
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // run_query corpus query format start limit timeout [path] [hint] : full query
            ++m_SessionStats.m_nQueries;
            isQueryRequest = true;
            try {
                this->handle__run_query(Result, Request.Get("corpus", "Distributed").c_str(), Request.Get("query").c_str(),
                                        Request.Get("format", "text").c_str(),
                                        Request.GetInt("start", 0), Request.GetInt("limit", 10), Request.GetInt("timeout", 10),
                                        Request.Get("path", ""), NavHint(Request.Get("hint", "")));
            }
            catch (CExpc &e) {
                Result = Format("\x01 %i %i %i %i %i\n%s", ddcExpcCode(e), 0, 0, 0, 0, e.what());
                ++m_SessionStats.m_nErrors;
            }
            catch (exception &e) {
                Result = Format("\x01 %i %i %i %i %i\n%s", errOther, 0, 0, 0, 0, e.what());
                ++m_SessionStats.m_nErrors;
            }
        }
        else if (cmd == "expand_terms") {
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // expand_terms pipeline terms [timeout] [corpus] : term expansion (leaf|branch)
            ++m_SessionStats.m_nExpand;
            isExpandRequest = true;
            this->handle__expand_terms(Result, Request.Get("pipeline"), Request.Get("terms"),
                                       Request.GetInt("timeout", 10), Request.Get("corpus", ""));
        }
        else if (cmd == "get_paradigm") {
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // get_paradigm word [lemmatize_only] lang
            ++m_SessionStats.m_nExpand;
            isExpandRequest = true;
            this->handle__get_paradigm(Result, Request.Get("word").c_str(), Request.GetInt("lemmatize_only", 0),
                                       Request.GetInt("lang"));
        }
        else if (cmd == "version") {
            this->handle__version(Result);
        }
        else if (cmd == "status") {
            this->handle__status(Result);
        }
        else if (cmd == "vstatus") {
            this->handle__vstatus(Result, Request.GetInt("timeout", 0));
        }
        else if (cmd == "info") {
            this->handle__info(Result, Request.GetInt("timeout", 0));
        }
        else if (cmd == "vinfo") {
            this->handle__vinfo(Result, Request.GetInt("timeout", 0));
        }
        else if (cmd == "reload") {
            this->handle__reload(Result, Request.GetInt("depth", 0));
        }
        else if (cmd == "clear_cache") {
            this->handle__clear_cache(Result, Request.GetInt("depth", 0));
        }
        else if (cmd == "nodes") {
            this->handle__nodes(Result, Request.GetInt("depth", -1));
        }
        else {
            throw CDDCExpc(errParseError, Format("unknown command `%s'", cmd.c_str()));
        }
    }
    catch (CExpc &e) {
        ddcLogError(Format("CDDCServer[%s]::ProcessRequest(): Exception[%d]: %s", m_CorpusName.c_str(), ddcExpcCode(e), e.what()));
        if (Result.empty()) Result = Format("%i 0\n%s", ddcExpcCode(e), e.what());
        ++m_SessionStats.m_nErrors;
    }
    catch (exception& e) {
        ddcLogError(Format("CDDCServer[%s]::ProcessRequest(): Exception: %s", m_CorpusName.c_str(), e.what()));
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
        ddcLogWarn(Format("WARNING: slow request (%gs > %gs): %s", t_elapsed, m_SlowQueryTimeout, Request.toString().c_str()));
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
