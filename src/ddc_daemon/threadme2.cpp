//-*- Mode: C++; c-basic-offset: 4; -*-
//
#include "threadme.h"
#include "../ConcordDmnLib/ServerThread.h"

//#undef HAVE_PTHREAD //-- test

//-- suppress gcc warnings of the form "ignoring return value of `fread', declared with attribute warn_unused_result [-Wunused-result]"
#pragma GCC diagnostic ignored "-Wunused-result"

const char *prog = "threadme2";

const ProtocolDensityEnum logLevel = pdHeavyDensity;
//const ProtocolDensityEnum logLevel = pdMediumDensity;
//const ProtocolDensityEnum logLevel = pdWeakDensity;

//======================================================================
// constants & params

#if USE_PTHREAD
  bool MyUseThreads = true;
#else
  bool MyUseThreads = false;
#endif

size_t MyNWorkers = 4;
size_t MyMaxQueueSize = DDC_DEFAULT_THREAD_QUEUE_SIZE;

//======================================================================
class TestServer : public CDDCServer
{
public:
    //--------------------------------------------------------------
    // local data
    int m_sleep;

public:
    //--------------------------------------------------------------
    // Constructors etc.
    TestServer(int sleep_seconds=0)
	: m_sleep(sleep_seconds)
    {
	m_pdProtocolDensity = logLevel;
	m_bLogRequests=true;
	m_bLogFinish=true;
	m_noLogCommands.clear();
    };

    //--------------------------------------------------------------
    virtual ~TestServer()
    {};

    //--------------------------------------------------------------
    // DDCServer API: client threads

    //! create a local copy of this object (and any subordinate data) for use by a per-client thread
    //! \li default just wraps copy constructor and InitLocal() method
    virtual CDDCServer *WorkerClone(void) const
    { return (CDDCServer*)new TestServer(); };

    //! create a local copy of this object (and any subordinate data) for use by a per-client thread
    virtual void WorkerCloneInit(const CDDCServer *Parent)
    {
	CDDCServer::WorkerCloneInit(Parent);
	m_sleep = ((const TestServer*)Parent)->m_sleep;
    };


    //--------------------------------------------------------------
    // DDCServer API: request handlers
    virtual void handle__status(string &Result, int timeout=10, bool verbose=false)
    {
	sleep(m_sleep);
	Result = Format("(v)status response (timeout=%d; verbose=%d; slept=%d; nreqs=%zd)", timeout, verbose, m_sleep, m_nRequests);
    };

    virtual void handle__info(string &Result, int timeout=10, bool verbose=false)
    {
	sleep(m_sleep);
	Result = Format("info response (timeout=%d; verbose=%d; slept=%d; nreqs=%zd)", timeout, verbose, m_sleep, m_nRequests);
    };
};



//======================================================================
// MAIN
int main(int argc, char **argv)
{
    ddcInitGlobal();
    ddc_thread_init(prog);
    concord_daemon_log_files=false;
    concord_daemon_log_stderr=true;

    TestServer srv;
    if (argc <= 1) {
	fprintf(stderr, "Usage: %s PORT [SLEEP=0] [NWORKERS=%zu] [QSIZE=%zu]\n", prog, MyNWorkers, MyMaxQueueSize);
	exit(1);
    }
    int port = strtol(argv[1], NULL, 0);
    if (argc > 2)
	srv.m_sleep = strtol(argv[2], NULL, 0);
    if (argc > 3)
	MyNWorkers = strtoul(argv[3], NULL, 0);
    if (argc > 4)
	MyMaxQueueSize = strtoul(argv[4], NULL, 0);

    srv.Init(prog, "0.0.0.0", port);
    srv.m_nWorkers = MyNWorkers;
    srv.m_ThreadQueueSize = MyMaxQueueSize;

    concord_daemon_log(Format("%s: starting server on %s:%d, sleep=%d", prog, srv.HostAddr().c_str(), srv.Port(), srv.m_sleep));
    srv.RunThread();

    fprintf(stderr, "%s: exiting normally.\n");
    return 0;
}





