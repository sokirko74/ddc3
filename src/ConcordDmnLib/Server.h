#ifndef DDC_SERVER_H
#define DDC_SERVER_H

#include "ServerOptions.h"
#include "ServerStats.h"
#include "../CommonLib/CHost.h"
#include "../ConcordLib/ConcHolder.h"
#include "../CommonLib/ddcThreadQueue.h"


//#define DEBUG_HIT_SORT
#ifdef DEBUG_HIT_SORT
# define HSDEBUG(s) ddcLog(s)
# define HIT_SORT_DEBUG(x) x
#else
# define HSDEBUG(s)
# define HIT_SORT_DEBUG(x)
#endif

//==============================================================================
/** abstract base class class for DDC server nodes */
class CDDCServer : public CHost
{
public:
    /** additional hit delimiter; overrides CConcHolder.m_AdditionalHitDelimiter , also used for branch server hit-tokenization; default is "\x01" */
    static const char *AdditionalHitDelimiter;

    /** maximum number of subcorpora per branch server */
    static const size_t MaxSubhostsSize = 256;

    /** compatibility mode */
    DDCVersionT m_VersionCompat;

    /** timestamp of server initialization */
    time_t m_tStarted;

    /** server-wide administrative statistics (number of requests, etc) */
    CDDCServerStats m_ServerStats;

    /** session-local administrative statistics */
    CDDCServerStats m_SessionStats;

    /* whether to log "normal" requests received in ProcessSocketString() */
    bool m_bLogRequests;

    /* set of request commands NOT to be logged (e.g. "status", "info", etc.) */
    std::set<std::string> m_noLogCommands;

    /* FQDN if available, otherwise symbolic hostname as returned by gethostname() */
    std::string m_FQHostName;

    /** number of client-thread workers for thread pool (default=0: serial mode) */
    size_t m_nWorkers;

    /** maximum number of pending client connections the thread-pool queue (min=1: use tcp queueing only; default=DDC_DEFAULT_THREAD_QUEUE_SIZE) */
    size_t m_ThreadQueueSize;

    /** upper-bound in seconds for "slow" queries
     *  \li any query taking longer than this will be logged
     *  \li set to zero or less to suppress slow-query log messages
     *  \li default=10
     */
    double m_SlowQueryTimeout;

    /** worker thread-id for worker clones */
    size_t m_WorkerId;

    /** client-thread pool (requires pthread) */
    class CDDCServerThreadPool *m_ThreadPool;

public:
    //--------------------------------------------------------------
    // Constructors etc.

    /** default constructor */
    CDDCServer();

    /** default destructor */
    virtual ~CDDCServer()
    { this->Shutdown(); };
    
    /** close any open socket(s) this server administers, called on termination signal */
    virtual void Shutdown(bool quiet=false);

    /** set server options */
    virtual void SetOptions(const CDDCServerOptions &Options);

public:
    //--------------------------------------------------------------
    // DDCServer API: client threads

    /** initialize the client-thread pool (requires pthread support) */
    virtual void StartClientThreads();

    /** create a minimal (uninitialized) copy of this object (and any subordinate data) for use by a worker thread
     *  \li WorkerCloneInit() will be called on the returned clone
     *  \li will be called on parent server to create a thread-local \a m_Server for each worker ::CDDCServerThread 
     *  \li derived classes should override both this method and WorkerCloneInit()
     *  \see WorkerCloneInit
     */
    virtual CDDCServer* WorkerClone(void) const
    { return new CDDCServer(); };

    /** initialize a newly created worker-clone (and any subordinate data)
     *  \li called on newly created worker-clone objects by default WorkerClone() implementation
     *  \li \b recommended for derived classes
     *  \param Parent parent server from which settings are to be cloned
     *  \param WorkerId local id of this worker-clone (== CDDCServerThread.m_ThreadId)
     */
    virtual void WorkerCloneInit(const CDDCServer *Parent, size_t WorkerId);

    /** perform local cleanup of a worker clone prior to deletion; default implementation just calls Shutdown() */
    virtual void WorkerCloneFree(void);

    /** is this server configured and ready to use client threads?
     *  \li requires pthread support
     *  \li only meaningful for parent server after StartClientThreads()
     */
    inline bool UseClientThreads(void) const
    { return m_ThreadPool!=NULL; };

public:
    //--------------------------------------------------------------
    // CHost API: socket handlers

    /** CHost API: main accept - process - respond loop; called in its own thread
     *  \li override calls StartClientThreads() before calling inherited method
     */
    virtual void RunThread();

    /** CHost API: handle a new client connection (top-level): override */
    virtual void HandleClientConnection(SOCKET& rConnectedSocket);
    
    /** CHost API: maintains m_Stats and calls appropriate handle__() methods */
    virtual std::string ProcessSocketString(const std::string& SocketInput, SOCKET& rConnectedSocket);

public:
    //--------------------------------------------------------------
    // DDCServer API: request handlers: required

    /** request handler: get_first_hits: required (leaf) */
    virtual void handle__get_first_hits(std::string &Result, const char *Query, int TimeOut, size_t ResultLimit, const std::string& ReqPath, const NavHint& Hint);

    /** request handler: get_hit_strings: required (leaf) */
    virtual void handle__get_hit_strings(std::string &Result, const char *ResultType, size_t StartHitNo, size_t ResultLimit);

    /** request handler: run_query: required (branch) */
    virtual void handle__run_query(std::string &Result, const char *CorpusName, const char *Query, const char *ResultType, size_t StartHitNo, size_t ResultLimit, int TimeOut, const std::string& ReqPath, const NavHint& Hint);

    /** request handler: expand_terms: required (leaf|branch) */
    virtual void handle__expand_terms(std::string &Result, const std::string& pipeline, const std::string& terms, int timeout, const std::string &corpus);

    /** request handler: status: required (leaf|branch) */
    virtual void handle__status(std::string &Result, int timeout=10, bool verbose=false);

    /** request handler: info: required (leaf|branch) */
    virtual void handle__info(std::string &Result, int timeout=10, bool verbose=false);

    /** request handler: reload: required (leaf|branch) */
    virtual void handle__reload(std::string &Result, int depth=0);

    /** request handler: clear_cache: required (leaf|branch) */
    virtual void handle__clear_cache(std::string &Result, int depth=0);

    /** request handler: nodes: required (leaf|branch; since v2.2.8) */
    virtual void handle__nodes(std::string &Result, int depth=-1);

public:
    //--------------------------------------------------------------
    // DDCServer API: request handlers: optional

    /** request handler: get_first_hits, 3-argument form (no path or hint) */
    virtual void handle__get_first_hits(std::string &Result, const char *Query, int TimeOut, size_t ResultLimit);

    /** request handler: get_first_hits, 7-argument form (no path or hint) */
    virtual void handle__run_query(std::string &Result, const char *CorpusName, const char *Query, const char *ResultType, size_t StartHitNo, size_t ResultLimit, int TimeOut);

    /** request handler: get_paradigm: optional (leaf|branch) */
    virtual void handle__get_paradigm(std::string &Result, const char *Word, int iLemmatizeOnly, int iLang);

    /** request handler: close_socket: optional (leaf|branch) */
    virtual void handle__close_socket(std::string &Result, SOCKET &rConnectedSocket);

    /** request handler: close_socket: optional (leaf|branch) */
    virtual void handle__version(std::string &Result);

    /** request handler: vstatus: optional (leaf|branch): default wraps handle__status(Result,timeout,true) */
    virtual void handle__vstatus(std::string &Result, int timeout=10);

    /** request handler: vinfo: optional (leaf|branch): default wraps handle__info(Result,timeout,true) */
    virtual void handle__vinfo(std::string &Result, int timeout=10);

public:
    //--------------------------------------------------------------
    // DDCServer: utilities
    inline void method_not_implemented(const char *methodName)
    { throw CDDCExpc(errRuntime, "DDCServer API method %s not implemented for object %s", methodName, typeid(*this).name()); };
    
    /** find offsets of server-path and navigation hint from \a ReqStr starting at \a StartPos */
    void findPathHint(const std::string& ReqStr, size_t StartPos, size_t &PathPos, size_t &HintPos);
};

#endif /* DDC_SERVER_H */
