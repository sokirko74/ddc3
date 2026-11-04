#ifndef _DDC_CHOST_H
#define _DDC_CHOST_H

#include "morph_dict/common/utilit.h"
#include "ddcUtil.h"
#include "string_socket.h"

//======================================================================
/** \brief generic socket host wrapper class
 *  \detail irritatingly also used for client connections
 */
class CHost  
{
    bool            m_bListen;
    SOCKET          m_ListenSocket;

protected:
    CSocketAddr     m_SockAddr;     ///< socket address (tcp or UNIX); formerly m_HostAddr, m_Port, m_SocketPath
    bool            m_bExpectMore;  ///< moo: whether to expect more requests from current client
    bool            m_bRespond;     ///< moo: whether current request has a real (possibly empty) response
    bool            m_bLogFinish;   ///< moo: whether to log connection completion
    std::string          m_LocalPath;    ///< path to local project-file (ddc_local_corpora.cfg) or label of parent branch node (ddc_server.cfg)
    uint32_t        m_maxReceiveBytes; ///< maximum receivable packet length (default=0: no limit)
    mode_t          m_UnixSocketPerms; ///< permissions mask for unix socket (defualt=0: OS-default = 0777&~umask())

    int             CreateSocket(bool bBind, std::string& strError) const;
    bool            CheckValidAddr() const;
    void            StopListening ();
public:
    std::string          m_CorpusName;	///< full node label, including optional "server:" prefix
    std::string	    m_ShortName;	///< short node label, without optional "server:" prefix
        
    CHost();
    virtual ~CHost();
    bool                    ReadFromString (std::string S);

    /** top-level call to start accept-process-respond loop; run in main thread */
    virtual void            CreateListener();
    void                    CopyAddressParametersFrom(const CHost& X);
    bool                    CloseListenSocket(int timeout=0);

    /** main accept - process - respond loop; called in its own thread */
    virtual void            RunThread();
        
    int                     CreateAndConnectSocket(std::string& strError) const;
    std::string                  GetAddressStr() const;
    const std::string&           GetLocalPathOfIndex() const;
    
    inline const CSocketAddr& SocketAddr() const { return m_SockAddr; };
    inline const std::string&    HostAddr() const { return m_SockAddr.m_Addr; };
    inline const int        Port() const { return m_SockAddr.m_Port; };

    

    /** initialize static host parameters, in lieu of reading from file */
    bool InitEmbedded(const CHost&);

    /** initialize m_ShortName from m_CorpusName */
    void InitShortName();

    bool IsListening () const {return m_bListen; };

public:
    /** read request string from a connected socket; handles low-level errors
     * \param rConnectedSocket socket from which to read
     * \param TimeOut timeout in seconds for low-level read operations
     * \param Request holds request on return
     * \returns true on success
     */
    bool GetRequest   (SOCKET& rConnectedSocket, int TimeOut, std::string &Request);

    /** send a response string to a connected socket; handles low-level errors
     * \li closes socket unless \a m_bExpectMore is true
     * \param rConnectedSocket socket to which response is to be sent
     * \param Result response string to be sent (without size prefix)
     */
    void SendResponse (SOCKET& rConnectedSocket, const std::string& Result);

    /** handle a socket-level error for a client connection, no response sent to client */
    void HandleSocketError(SOCKET& rConnectedSocket, const std::string& ErrorStr="ERROR", const std::string& Where="CHost::HandleSocketError()");

    /** handle a single client request (formerly AnswerByRequest())
     *  \li wraps a single iteration of GetRequest(), ProcessSocketString(), and SendResponse()
     *  \li should set \a m_bExpectMore if more requests from the client are to be
     *      handled by the same instance.
     */
    void HandleClientRequest(SOCKET& rConnectedSocket, int TimeOut);

    /** handle a new client connection (top-level)
     * \li must be public for use by C-level pthread callbacks
     * \li formerly hard-coded into RunThread()
     * \li call is wrapped in a try/catch block together with HandleSocketError() on exceptions
     */
    virtual void HandleClientConnection(SOCKET& rConnectedSocket);

public:
    /** shutdown connected socket and perform any local cleanup methods
     * \li default implementation just wraps CloseSocketRef(rConnectedSocket,linger,timeout)
     * \returns true on success, false otherwise
     */
    virtual bool Close(SOCKET& rConnectedSocket, bool linger=false, int timeout=5);

    /** guts for request handling; override in subclasses */
    virtual std::string  ProcessSocketString(const std::string& S, SOCKET& rConnectedSocket);

    /** close a client connection in case of error, for use by derived classes
     * \li logs and sends an error messaage to the client
     * \li \c code should be nonzero to indicate a 'real' error
     * \li implicitly closes \c clientSocket if !=-1 (default)
     */
    virtual void    ClientError(int code=-1, const std::string& msg="");
    virtual void    ClientError(int code,    const std::string& msg, SOCKET& clientSocket);

};

//======================================================================
// load a DDC server config file
extern bool LoadHosts (std::string Path, std::vector<CHost>& Hosts);

        
#endif /* DDC_CHOST_H */
