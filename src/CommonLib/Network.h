#pragma once

/* network layer: socket addresses, requests and the http client (cpp-httplib)
 *
 * A request is an http GET or POST to /COMMAND with named parameters (url query
 * or application/x-www-form-urlencoded body); the response body is the result.
 * One keep-alive connection is one session: the requests of a connection are
 * served one after another by the same server worker (get_first_hits, then
 * get_hit_strings).
 */

#include "nlp_base/common/utilit.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

//======================================================================
// Types

enum NetworkErrorsEnum {
    neSuccess = 0,
    neNetworkError = 1,
    neTimeout = 2,
    neProtocolError = 3,
    neSubcorpusNotFound = 4,
    neInternalReadAccessError = 5,
    neCouldNotOpenSocket = 6,
    neCouldNotSendData = 7,
    neCouldNotReceiveData = 8,
    neInternalError = 9,
    neRequestTooLarge = 10
};

enum SocketTypeEnum {
    stUnknown = 0,
    stINET = 1,
    stUNIX = 2
};

extern std::string GetNetworkErrorString(const NetworkErrorsEnum& t);

//======================================================================
/* socket address (tcp or UNIX) */
struct CSocketAddr
{
    SocketTypeEnum m_Type = stUnknown;  // socket domain
    std::string    m_Addr;              // unix: filesystem path, tcp: host address
    int            m_Port = -1;         // unix: filler, tcp: port number

    CSocketAddr() = default;

    CSocketAddr(SocketTypeEnum sockType, const std::string& sockAddr="", int sockPort=-1)
        : m_Type(sockType), m_Addr(sockAddr), m_Port(sockPort)
    {};

    /* constructor from string */
    CSocketAddr(const std::string& Str, bool parsePort=true)
    { ParseSocketAddr(Str, parsePort); };

    void Clear();

    bool IsValid() const;

    inline operator bool() const
    { return IsValid(); };

    /* parse m_Type and m_Addr from Str (calls ParseAddrPort() if parsePort is true):
     *  - ADDR, tcp://ADDR, tcp:ADDR, inet://ADDR, inet:ADDR - tcp socket on ADDR
     *  - /PATH, unix://PATH, unix:PATH - UNIX socket on PATH
     */
    void ParseSocketAddr(const std::string& Str, bool parsePort=true);

    /* extract m_Port from m_Addr: ADDR:PORT or "ADDR PORT" */
    void ParseAddrPort();

    /* URL-style string representation */
    std::string toString() const;
};

//======================================================================
/* named request parameters, in the order they are sent */
typedef std::vector<std::pair<std::string, std::string> > RequestParams;

/* a parsed request: command (the url path without "/") and its parameters */
struct CRequest
{
    std::string   Command;
    RequestParams Params;

    bool Has(const std::string& name) const;

    /* throws CDDCExpc(errParseError) if the parameter is missing */
    const std::string& Get(const std::string& name) const;
    std::string Get(const std::string& name, const std::string& deflt) const;

    /* integer parameters; throws CDDCExpc(errParseError) if missing or not a number */
    long GetInt(const std::string& name) const;
    long GetInt(const std::string& name, long deflt) const;

    /* "COMMAND name=value ..." for the logs */
    std::string toString() const;
};

//======================================================================
/* an http client connection to a ddc server; keep-alive, so that several
 * requests of a session (get_first_hits, get_hit_strings) go to the same worker */
class CHttpConnection
{
    struct Impl;
    std::unique_ptr<Impl> m_Impl;
public:
    explicit CHttpConnection(const CSocketAddr& addr);
    ~CHttpConnection();
    CHttpConnection(const CHttpConnection&) = delete;
    CHttpConnection& operator=(const CHttpConnection&) = delete;

    /* POST /command with params; Result is the response body
     * timeout: seconds for connecting, sending and receiving (0: 10 seconds)
     * returns neSuccess or the error, errorStr describes the error */
    NetworkErrorsEnum Request(const std::string& command, const RequestParams& params, int timeout,
                              std::string& Result, std::string& errorStr);

    /* close the connection (ends the session on the server) */
    void Close();
};

/* a one-request connection */
extern NetworkErrorsEnum HttpRequest(const CSocketAddr& addr, const std::string& command, const RequestParams& params,
                                     int timeout, std::string& Result, std::string& errorStr);
