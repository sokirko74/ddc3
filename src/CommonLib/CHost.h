#ifndef _DDC_CHOST_H
#define _DDC_CHOST_H

#include "nlp_base/common/utilit.h"
#include "ddcUtil.h"
#include "Network.h"

#include <memory>

namespace httplib {
    class Server;
}

//======================================================================
/* a host: a node name and a socket address (tcp or UNIX)
 *  - for servers: an http server (cpp-httplib) listening on the address
 *  - for clients: the address to connect to (see CHttpConnection)
 */
class CHost
{
    /* the http server; shared_ptr since hosts are copied (worker clones, vectors) */
    std::shared_ptr<httplib::Server> m_HttpServer;
    bool            m_bListen;
protected:
    CSocketAddr     m_SockAddr;     // socket address (tcp or UNIX)
    bool            m_bExpectMore;  // whether the current session expects more requests (set by request handlers)
    bool            m_bLogFinish;   // whether to log the sent responses
    std::string     m_LocalPath;    // path to local project-file (ddc_local_corpora.cfg) or label of parent branch node (ddc_server.cfg)
    uint32_t        m_maxReceiveBytes; // maximum request length (default=0: no limit)
    mode_t          m_UnixSocketPerms; // permissions mask for unix socket (default=0: OS-default = 0777&~umask())

    bool            CheckValidAddr() const;
    void            StopListening ();

    /* number of worker threads of the http server (default 1); override */
    virtual size_t  WorkerCount() const { return 1; };

    /* maximum number of queued connections (0: no limit); override */
    virtual size_t  MaxQueuedConnections() const { return 0; };

public:
    std::string     m_CorpusName;	// full node label, including optional "server:" prefix
    std::string	    m_ShortName;	// short node label, without optional "server:" prefix

    CHost();
    virtual ~CHost();

    bool                    ReadFromString (std::string S);

    /* bind the http server to m_SockAddr and start serving in a new thread */
    virtual void            CreateListener();
    void                    CopyAddressParametersFrom(const CHost& X);

    /* stop the http server (and remove the UNIX socket file) */
    bool                    CloseListenSocket(int timeout=0);

    /* serve requests; called in the listener thread, returns when the server is stopped */
    virtual void            RunThread();

    std::string             GetAddressStr() const;
    const std::string&      GetLocalPathOfIndex() const;
    inline const CSocketAddr& SocketAddr() const { return m_SockAddr; };
    inline const std::string& HostAddr() const { return m_SockAddr.m_Addr; };
    inline const int        Port() const { return m_SockAddr.m_Port; };

    /* initialize static host parameters, in lieu of reading from file */
    bool InitEmbedded(const CHost&);

    /* initialize m_ShortName from m_CorpusName */
    void InitShortName();

    bool IsListening () const {return m_bListen; };

public:
    /* handle one request; called by the http server worker threads (concurrently if WorkerCount() > 1)
     *  - returns the response body
     *  - throws CExpc on unknown commands or bad parameters (http status 400)
     */
    virtual std::string HandleRequest(const CRequest& Request);
};

//======================================================================
// load a DDC server config file
extern bool LoadHosts (std::string Path, std::vector<CHost>& Hosts);

#endif /* DDC_CHOST_H */
