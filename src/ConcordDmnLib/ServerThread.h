#ifndef DDC_SERVER_THREAD_H
#define DDC_SERVER_THREAD_H

#include "Server.h"
#include "../CommonLib/ddcThread.h"
#include "../CommonLib/ddcThreadQueue.h"

//======================================================================
// globals

/* default number of workers for client-threaded servers */
#define DDC_DEFAULT_THREAD_POOL_SIZE 4

//======================================================================
/* low-level class implementing a single CDDCServer per-client worker thread */
class CDDCServerThread : public ddcThread
{
public:
    //--------------------------------------------------------------
    // data

    /* worker-index */
    size_t      m_ThreadId;

    /* thread label "CORPUS#TID"; set on run() */
    std::string       m_Label;

    /* parent server (read-only) */
    CDDCServer  *m_Parent;

    /* thread-local server (worker copy) */
    CDDCServer  *m_Server;

    /* connected client socket */
    SOCKET       m_Client;

public:
    //--------------------------------------------------------------
    // methods

    /* default constructor; set ClientSocket=-1 for pool threads */
    CDDCServerThread(CDDCServer* Parent=NULL, size_t ThreadId=1);

    /* destructor calls m_Server->WorkerCloneFree() and deletes it */
    virtual ~CDDCServerThread();

    /* DDCThread API guts: process parent pool queue
     *  - requires valid m_Parent, m_Child
     */
    virtual void* run();
};


//======================================================================
/* high-level class used by CDDCServer for a per-client thread pool */
class CDDCServerThreadPool
{
public:
    /* item queue for thread-pool mode */
    ddcThreadQueue<SOCKET> m_Queue;

    /* worker threads for thread-pool mode */
    std::vector<CDDCServerThread*> m_Workers;

    /* pthread mutex for locking parent access */
    pthread_mutex_t m_mutex;

public:
    //--------------------------------------------------------------
    // Constructors etc.

    /* default constructor */
    CDDCServerThreadPool(void);

    /* wrapper for constructor and start() */
    CDDCServerThreadPool(CDDCServer *Server, size_t nWorkers=DDC_DEFAULT_THREAD_POOL_SIZE, size_t maxQueueSize=DDC_DEFAULT_THREAD_QUEUE_SIZE);

    /* default destructor */
    virtual ~CDDCServerThreadPool();

public:
    //--------------------------------------------------------------
    // API

    /* create and start worker nWorkers worker-threads
     *  - throws an exception if already started
     */
    virtual void start(CDDCServer *Server, size_t nWorkers=DDC_DEFAULT_THREAD_POOL_SIZE, size_t maxQueueSize=DDC_DEFAULT_THREAD_QUEUE_SIZE);

    /* terminate any worker threads and free up memory */
    virtual void stop(void);

    /* current number of worker thrads */
    inline size_t size(void) const
    { return m_Workers.size(); };

    /* wrapper for size()!=0 */
    inline bool started(void) const
    { return (size() != 0); };
};



#endif /* DDC_SERVER_THREAD_H */
