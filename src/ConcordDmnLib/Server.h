//-*- Mode: C++; c-basic-offset:4; -*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2017 by Bryan Jurish
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
#ifndef DDC_SERVER_H
#define DDC_SERVER_H

#include "ServerOptions.h"
#include "ServerStats.h"
#include "../CommonLib/CHost.h"
#include "../ConcordLib/ConcHolder.h"
#include "../common/ddcThreadQueue.h"

#ifdef WIN32
	#include <process.h>  /* _beginthread, _endthread */
#else
#endif

//#define DEBUG_HIT_SORT
#ifdef DEBUG_HIT_SORT
# define HSDEBUG(s) ddcLog(s)
#else
# define HSDEBUG(s)
#endif

//==============================================================================
/** abstract base class class for DDC server nodes */
class CDDCServer : public CHost
{
public:
    //--------------------------------------------------------------
    // Administrivia

    /** additional hit delimiter; overrides CConcHolder.m_AdditionalHitDelimiter , also used for branch server hit-tokenization; default is "\x01" */
    static const char *AdditionalHitDelimiter;

    /** maximum number of subcorpora per branch server */
    static const size_t MaxSubhostsSize = 256;

    /** timestamp of server initialization */
    time_t m_tStarted;

    /** server-wide administrative statistics (number of requests, etc) */
    CDDCServerStats m_ServerStats;

    /** session-local administrative statistics */
    CDDCServerStats m_SessionStats;

    /* whether to log "normal" requests received in ProcessSocketString() */
    bool m_bLogRequests;

    /* set of request commands NOT to be logged (e.g. "status", "info", etc.) */
    set<string> m_noLogCommands;

    /* FQDN if available, otherwise symbolic hostname as returned by gethostname() */
    string m_FQHostName;

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
    virtual string ProcessSocketString(const string& SocketInput, SOCKET& rConnectedSocket);

public:
    //--------------------------------------------------------------
    // DDCServer API: request handlers: required

    /** request handler: get_first_hits: required (leaf) */
    virtual void handle__get_first_hits(string &Result, const char *Query, int TimeOut, int ResultLimit);

    /** request handler: get_hit_strings: required (leaf) */
    virtual void handle__get_hit_strings(string &Result, const char *ResultType, int StartHitNo, int ResultLimit);

    /** request handler: run_query: required (branch) */
    virtual void handle__run_query(string &Result, const char *CorpusName, const char *Query, const char *ResultType, int StartHitNo, int ResultLimit, int TimeOut);

    /** request handler: expand_terms: required (leaf|branch) */
    virtual void handle__expand_terms(string &Result, const string& pipeline, const string& terms, int timeout, const string &corpus);

    /** request handler: status: required (leaf|branch) */
    virtual void handle__status(string &Result, int timeout=10, bool verbose=false);

    /** request handler: info: required (leaf|branch) */
    virtual void handle__info(string &Result, int timeout=10, bool verbose=false);

    /** request handler: reload: required (leaf|branch) */
    virtual void handle__reload(string &Result, int depth=0);

    /** request handler: clear_cache: required (leaf|branch) */
    virtual void handle__clear_cache(string &Result, int depth=0);

public:
    //--------------------------------------------------------------
    // DDCServer API: request handlers: optional

    /** request handler: get_paradigm: optional (leaf|branch) */
    virtual void handle__get_paradigm(string &Result, const char *Word, int iLemmatizeOnly, int iLang);

    /** request handler: close_socket: optional (leaf|branch) */
    virtual void handle__close_socket(string &Result, SOCKET &rConnectedSocket);

    /** request handler: close_socket: optional (leaf|branch) */
    virtual void handle__version(string &Result);

    /** request handler: vstatus: optional (leaf|branch): default wraps handle__status(Result,timeout,true) */
    virtual void handle__vstatus(string &Result, int timeout=10);

    /** request handler: vinfo: optional (leaf|branch): default wraps handle__info(Result,timeout,true) */
    virtual void handle__vinfo(string &Result, int timeout=10);

public:
    //--------------------------------------------------------------
    // DDCServer: utilities
    inline void method_not_implemented(const char *methodName)
    { throw CExpc(errRuntime, "DDCServer API method %s not implemented for object %s", methodName, typeid(*this).name()); };
    
    /** get resident memory size of server process in kb using /proc/self/statm */
    virtual size_t residentMemorySize(void);
};

#endif /* DDC_SERVER_H */
