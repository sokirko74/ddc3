#include "CHost.h"
#include "util_classes.h"
#include "DDCInternalError.h"
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ddcExpc.h"
#include "ddcString.h"
#include "ddcThread.h"

#include "nlp_base/contrib/httplib/httplib.h"

using namespace std;

//======================================================================
// CHost

//--------------------------------------------------------------
CHost::CHost()
    : m_SockAddr()
{
    m_bExpectMore = false;
    m_bLogFinish = false;
    m_maxReceiveBytes = 0;
    m_bListen = false;
    m_UnixSocketPerms = 0;
};

//--------------------------------------------------------------
CHost::~CHost()
{
}

//--------------------------------------------------------------
bool CHost::CheckValidAddr() const
{
    return m_SockAddr.IsValid();
}

//--------------------------------------------------------------
bool CHost::ReadFromString (string S)
{
    StringTokenizer tok(S.c_str(), " \t\r\n");
    int ItemNo = 0;
    m_SockAddr.Clear();
    while (tok()) 
    {
        string Item = tok.val();
        if (ItemNo == 0) {
            m_CorpusName = Item;
            InitShortName();
        }
        else if (ItemNo == 1) {
            m_SockAddr.ParseSocketAddr(Item, false);
        }
        else if (ItemNo == 2) {
            m_SockAddr.m_Port = atoi(Item.c_str());
            m_LocalPath = tok.get_rest();
            Trim (m_LocalPath);
            break;
        }
        ItemNo++;
    };

    return CheckValidAddr();
};

//--------------------------------------------------------------
bool CHost::InitEmbedded (const CHost& host)
{
    CopyAddressParametersFrom(host);
    if (m_SockAddr.m_Type==stINET && m_SockAddr.m_Addr == "0.0.0.0") {
        m_SockAddr.m_Addr = "127.0.0.1"; //-- connect to localhost for embedded branch servers binding all inet interfaces
    }
    m_LocalPath  = "";
    return CheckValidAddr();
};

//--------------------------------------------------------------
void CHost::StopListening () {
    m_bListen = false;
    m_HttpServer.reset();
};

//--------------------------------------------------------------
bool CHost::CloseListenSocket(int timeout)
{
    m_bListen = false;
    if (!m_HttpServer)
        return true;
    m_HttpServer->stop();
    m_HttpServer.reset();
    if (m_SockAddr.m_Type==stUNIX) {
        if (unlink(m_SockAddr.m_Addr.c_str()) == -1 && errno != ENOENT) {
            ddcLogWarn(Format("cannot remove unix domain socket %s for %s", m_SockAddr.m_Addr.c_str(), m_CorpusName.c_str()));
        }
    }
    return true;
};

//--------------------------------------------------------------
string CHost::HandleRequest(const CRequest& Request)
{
    throw CDDCExpc(errParseError, Format("unknown command `%s'", Request.Command.c_str()));
};

//--------------------------------------------------------------
static CRequest MakeRequest(const httplib::Request& req)
{
    CRequest r;
    r.Command = req.path;
    while (!r.Command.empty() && r.Command[0] == '/')
        r.Command.erase(0, 1);
    for (const auto& p : req.params)
        r.Params.emplace_back(p.first, p.second);
    return r;
}

//--------------------------------------------------------------
void CHost::RunThread()
{
    std::shared_ptr<httplib::Server> server = m_HttpServer;
    if (!server) return;
    ddcLogInfo( Format("%s listening on %s", m_CorpusName.c_str(), GetAddressStr().c_str()) );
    if (!server->listen_after_bind()) {
        ddcLogError(Format("CHost::RunThread(): ERROR: http server on %s stopped with an error", GetAddressStr().c_str()));
    }
    m_bListen = false;
};

//--------------------------------------------------------------
static void* ListenerThread( void* pParam )
{
    CHost* pHost = (CHost* )pParam;
    try {
        ddc_thread_init(pHost->m_CorpusName.c_str());
        pHost->RunThread();
    }
    catch (exception &e) {
        ddcLogError(Format("ListenerThread[%s]: Exception: %s", pHost->GetAddressStr().c_str(), e.what()) );
    }
    catch (...) {
        ddcLogError( Format("ListenerThread[%s]: Exception: (unhandled exception)", pHost->GetAddressStr().c_str()) );
    }
    return NULL;
};

//--------------------------------------------------------------
void CHost::CreateListener()
{
    ddcLogInfo( Format ("Create Listener %s (%s)", m_CorpusName.c_str(), GetAddressStr().c_str()) );
    auto server = std::make_shared<httplib::Server>();

    size_t nWorkers = WorkerCount();
    size_t maxQueued = MaxQueuedConnections();
    server->new_task_queue = [nWorkers, maxQueued] {
        return new httplib::ThreadPool(nWorkers == 0 ? 1 : nWorkers, maxQueued);
    };
    //-- a keep-alive connection is a session (get_first_hits, get_hit_strings, ...)
    server->set_tcp_nodelay(true);   // no Nagle: a response written in parts waits ~40-200 ms for a delayed ACK
    server->set_keep_alive_max_count(100);
    server->set_keep_alive_timeout(30);
    server->set_read_timeout(30, 0);
    if (m_maxReceiveBytes > 0)
        server->set_payload_max_length(m_maxReceiveBytes);

    auto handler = [this](const httplib::Request& req, httplib::Response& res) {
        CRequest request = MakeRequest(req);
        try {
            res.set_content(this->HandleRequest(request), "text/plain; charset=utf-8");
            if (m_bLogFinish || ddcLogLevel >= ddcLLTrace)
                ddcLogInfo(Format("%s sent back the result to %s (%zd bytes)", m_CorpusName.c_str(), req.remote_addr.c_str(), res.body.size()));
        }
        catch (CExpc& e) {
            ddcLogError(Format("%s: request `%s' from %s: Exception[%d]: %s", m_CorpusName.c_str(), request.toString().c_str(), req.remote_addr.c_str(), ddcExpcCode(e), e.what()));
            res.status = httplib::StatusCode::BadRequest_400;
            res.set_content(Format("%i 0\n%s", ddcExpcCode(e), e.what()), "text/plain; charset=utf-8");
        }
        catch (exception& e) {
            ddcLogError(Format("%s: request `%s' from %s: Exception: %s", m_CorpusName.c_str(), request.toString().c_str(), req.remote_addr.c_str(), e.what()));
            res.status = httplib::StatusCode::InternalServerError_500;
            res.set_content(Format("%i 0\n%s", -1, e.what()), "text/plain; charset=utf-8");
        }
    };
    server->Get(R"(/\w+)", handler);
    server->Post(R"(/\w+)", handler);

    bool bound;
    if (m_SockAddr.m_Type == stUNIX) {
        const string& path = m_SockAddr.m_Addr;
        if (unlink(path.c_str()) == 0)
            ddcLogWarn("removed stale UNIX socket " + path);
        server->set_address_family(AF_UNIX);
        bound = server->bind_to_port(path, 80);
        if (bound && m_UnixSocketPerms != 0 && chmod(path.c_str(), m_UnixSocketPerms) != 0) {
            ddcLogWarn(Format("failed to set permissions mask=%04o for UNIX socket %s: %s",
                              m_UnixSocketPerms, path.c_str(), StrError(errno)));
        }
    } else {
        bound = server->bind_to_port(m_SockAddr.m_Addr, m_SockAddr.m_Port);
    }
    if (!bound)
        throw CDDCExpc(errRuntime, Format("%s: cannot bind to %s: %s", m_CorpusName.c_str(), GetAddressStr().c_str(), StrError(errno)));

    m_HttpServer = server;
    m_bListen = true;
    pthread_t aThread;
    pthread_create(&aThread, NULL, ListenerThread, (void*)this);
    pthread_detach(aThread);
};

//--------------------------------------------------------------
string  CHost::GetAddressStr() const
{
    return m_SockAddr.toString();
};

//--------------------------------------------------------------
const string&   CHost::GetLocalPathOfIndex() const
{
    return m_LocalPath;
};

//--------------------------------------------------------------
void CHost::InitShortName()
{
    if (m_CorpusName.find("server:")==0) {
        m_ShortName = m_CorpusName.substr(7);
    } else {
        m_ShortName = m_CorpusName;
    }
};

//--------------------------------------------------------------
void CHost::CopyAddressParametersFrom(const CHost& X)
{
    m_SockAddr = X.m_SockAddr;
    m_LocalPath = X.m_LocalPath;
    m_CorpusName = X.m_CorpusName;
    m_ShortName = X.m_ShortName;
};


//======================================================================
// global functions

//--------------------------------------------------------------
bool LoadHosts (string Path, vector<CHost>& Hosts)
{
    if (!FileExists(Path.c_str()))
    {
        ddcLogError(Format("LoadHosts() ERROR: cannot access file %s", Path.c_str()));
        return false;
    };
    FILE * fp = fopen (Path.c_str(), "r");
    if (!fp) 
    {
        ddcLogError(Format("LoadHosts() ERROR: cannot open file %s", Path.c_str()));
        return false;
    };
    char buffer[1024];
    int LineNo = 0;
    while (fgets(buffer, 1024, fp))
    {
        LineNo++;
        string Q = buffer;
        Trim(Q);

        //-- ignore comments and blank lines
        if (Q.empty()) continue;
        if (Q.find("//")==0) continue;
        if (Q.find("#")==0)  continue;
        CHost T;
        if (!T.ReadFromString(Q)) 
        {
            ddcLogError(Format("LoadHosts ERROR: could not parse file %s line number %i: %s", Path.c_str(), LineNo, buffer));
            fclose(fp);
            return false;
        };
                
        Hosts.push_back(T);
    };
        
    fclose(fp);

    return true;
};
