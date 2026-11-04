#include "ServerThread.h"

using namespace std;

//======================================================================
// CDDCServerThread

//--------------------------------------------------------------
CDDCServerThread::CDDCServerThread(CDDCServer* Parent, size_t ThreadId)
    : m_ThreadId(ThreadId), m_Parent(Parent), m_Client(-1)
{
    if (m_Parent) {
        m_Server = m_Parent->WorkerClone();
        m_Server->WorkerCloneInit(m_Parent,ThreadId);
    }
};

//--------------------------------------------------------------
CDDCServerThread::~CDDCServerThread()
{
    if (m_Server) {
        m_Server->WorkerCloneFree();
        delete m_Server;
    }
};

//--------------------------------------------------------------
void* CDDCServerThread::run(void)
{
    assert(m_Parent != NULL);
    assert(m_Parent->m_ThreadPool != NULL);
    assert(m_Server != NULL);

    //-- common initialization (thread label, worker-id)
    if (m_Label.empty())
        m_Label = Format("%s#%zu", m_Server->m_CorpusName.c_str(), m_ThreadId);
    ddc_thread_init(m_Label.c_str());

    //-- report
    ddcLogDebug( Format("starting worker thread #%zd for server %s", m_Server->m_WorkerId, m_Server->m_CorpusName.c_str()) );

    //-- thread-pool mode (persistent)
    for (;;) {
        m_Client = m_Parent->m_ThreadPool->m_Queue.remove();

        //-- adopt parent server-stats so we can report them accurately (moving average window may be out-of-sync)
        pthread_mutex_lock(&m_Parent->m_ThreadPool->m_mutex);
        m_Server->m_ServerStats = m_Parent->m_ServerStats;
        pthread_mutex_unlock(&m_Parent->m_ThreadPool->m_mutex);

        m_Server->HandleClientConnection(m_Client);

        //-- propagate session-stats back to parent
        pthread_mutex_lock(&m_Parent->m_ThreadPool->m_mutex);
        m_Parent->m_ServerStats += m_Server->m_SessionStats; 
        pthread_mutex_unlock(&m_Parent->m_ThreadPool->m_mutex);
    }
    //-- should never be reached
    ddcLogWarn("CDDCServerThread::run() exiting queue processing loop");

    return NULL;
};


//======================================================================
// CDDCServerThreadPool

//--------------------------------------------------------------
CDDCServerThreadPool::CDDCServerThreadPool(void)
{
    pthread_mutex_init(&m_mutex, NULL);
}

//--------------------------------------------------------------
CDDCServerThreadPool::~CDDCServerThreadPool()
{
    this->stop();
    pthread_mutex_destroy(&m_mutex);
}

//--------------------------------------------------------------
CDDCServerThreadPool::CDDCServerThreadPool(CDDCServer *Server, size_t nWorkers, size_t maxQueueSize)
{
    pthread_mutex_init(&m_mutex, NULL);
    this->start(Server, nWorkers, maxQueueSize);
}

//--------------------------------------------------------------
void CDDCServerThreadPool::start(CDDCServer *Server, size_t nWorkers, size_t maxQueueSize)
{
    assert(Server != NULL);
    
    //-- +pthread
    if (!m_Workers.empty())
        throw CDDCExpc( Format("CDDCServerThreadPool::start(): ERROR: thread-pool seems to be already running!") );

    if (nWorkers == 0)
        nWorkers = 1; //-- if we get here, we need at least 1 worker thread
   
    
    ddcLogInfo( Format("initializing thread pool with %zd worker(s), max %zu queued requests", nWorkers, maxQueueSize) );
    m_Queue.m_max_size = (maxQueueSize==0 ? 1 : maxQueueSize); //-- queue needs to hold at least 1 element
    m_Workers.resize(nWorkers);
    for (size_t i=0; i < nWorkers; ++i) {
        m_Workers[i] = new CDDCServerThread(Server,i+1);
        m_Workers[i]->start();
        m_Workers[i]->detach();
    }
}

//--------------------------------------------------------------
void CDDCServerThreadPool::stop()
{
    for (size_t i=0; i < m_Workers.size(); ++i) {
        if (m_Workers[i] != NULL) delete m_Workers[i];
    }
    m_Workers.clear();
}
