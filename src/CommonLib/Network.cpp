#include "Network.h"
#include "ddcExpc.h"
#include "ddcString.h"
#include "DDCInternalError.h"
#include "ddcLocale.h"

#include "nlp_base/contrib/httplib/httplib.h"

using namespace std;

//======================================================================
// CSocketAddr

void CSocketAddr::Clear()
{
    m_Type = stUnknown;
    m_Addr.clear();
    m_Port = -1;
}

bool CSocketAddr::IsValid() const
{
    switch (m_Type) {
        case stINET:
            return !m_Addr.empty() && m_Port != -1;
        case stUNIX:
            return !m_Addr.empty();
        default:
            return false;
    }
}

void CSocketAddr::ParseSocketAddr(const string& Str, bool parsePort)
{
    static const struct { const char* prefix; SocketTypeEnum type; } schemes[] = {
        {"tcp://", stINET}, {"tcp:", stINET}, {"inet://", stINET}, {"inet:", stINET},
        {"unix://", stUNIX}, {"unix:", stUNIX},
    };
    string lo = stolower(Str);
    m_Type = stUnknown;
    for (const auto& s : schemes) {
        if (startswith(lo, s.prefix)) {
            m_Type = s.type;
            m_Addr = Str.substr(strlen(s.prefix));
            break;
        }
    }
    if (m_Type == stUnknown) {
        m_Type = startswith(Str, "/") ? stUNIX : stINET;
        m_Addr = Str;
    }
    if (parsePort && m_Type == stINET)
        ParseAddrPort();
}

void CSocketAddr::ParseAddrPort()
{
    TrimRight(m_Addr);
    size_t pi = m_Addr.find_last_of(" \t\r\n:");
    if (pi != string::npos && pi > 0 && pi < (m_Addr.size()-1)) {
        m_Port = strtol(m_Addr.substr(pi+1).c_str(), NULL, 0);
        m_Addr.erase(pi);
        TrimRight(m_Addr);
    }
}

string CSocketAddr::toString() const
{
    switch (m_Type) {
        case stINET:
            return Format("inet://%s:%i", m_Addr.c_str(), m_Port);
        case stUNIX:
            return string("unix://") + m_Addr;
        default:
            return Format("null://%s:%i", m_Addr.c_str(), m_Port);
    }
}

//======================================================================
// CRequest

bool CRequest::Has(const string& name) const
{
    for (const auto& p : Params)
        if (p.first == name) return true;
    return false;
}

const string& CRequest::Get(const string& name) const
{
    for (const auto& p : Params)
        if (p.first == name) return p.second;
    throw CDDCExpc(errParseError, Format("%s: parameter `%s' is missing", Command.c_str(), name.c_str()));
}

string CRequest::Get(const string& name, const string& deflt) const
{
    return Has(name) ? Get(name) : deflt;
}

long CRequest::GetInt(const string& name) const
{
    const string& s = Get(name);
    char* end = nullptr;
    long v = strtol(s.c_str(), &end, 0);
    if (s.empty() || *end != 0)
        throw CDDCExpc(errParseError, Format("%s: parameter `%s' is not an integer: `%s'", Command.c_str(), name.c_str(), s.c_str()));
    return v;
}

long CRequest::GetInt(const string& name, long deflt) const
{
    return Has(name) ? GetInt(name) : deflt;
}

string CRequest::toString() const
{
    string s = Command;
    for (const auto& p : Params) {
        s += ' ';
        s += p.first;
        s += '=';
        s += p.second;
    }
    return s;
}

//======================================================================
// CHttpConnection

struct CHttpConnection::Impl {
    CSocketAddr Addr;
    std::unique_ptr<httplib::Client> Client;
};

CHttpConnection::CHttpConnection(const CSocketAddr& addr) : m_Impl(new Impl)
{
    m_Impl->Addr = addr;
}

CHttpConnection::~CHttpConnection() = default;

void CHttpConnection::Close()
{
    if (m_Impl->Client) m_Impl->Client->stop();
    m_Impl->Client.reset();
}

static NetworkErrorsEnum HttpErrorToNetworkError(httplib::Error e)
{
    switch (e) {
        case httplib::Error::Connection:
        case httplib::Error::BindIPAddress:
        case httplib::Error::ProxyConnection:
            return neCouldNotOpenSocket;
        case httplib::Error::Write:
            return neCouldNotSendData;
        case httplib::Error::Read:
            return neCouldNotReceiveData;
        case httplib::Error::ConnectionTimeout:
            return neTimeout;
        default:
            return neNetworkError;
    }
}

NetworkErrorsEnum CHttpConnection::Request(const string& command, const RequestParams& params, int timeout,
                                           string& Result, string& errorStr)
{
    Result.clear();
    errorStr.clear();
    const CSocketAddr& addr = m_Impl->Addr;
    if (!addr.IsValid()) {
        errorStr = "invalid address " + addr.toString();
        return neCouldNotOpenSocket;
    }
    if (timeout <= 0) timeout = 10;
    if (!m_Impl->Client) {
        if (addr.m_Type == stUNIX) {
            m_Impl->Client.reset(new httplib::Client(addr.m_Addr, 80));
            m_Impl->Client->set_address_family(AF_UNIX);
        } else {
            m_Impl->Client.reset(new httplib::Client(addr.m_Addr, addr.m_Port));
        }
        m_Impl->Client->set_keep_alive(true);
        m_Impl->Client->set_tcp_nodelay(true);   // no Nagle: the body of a POST waits for the ACK of the headers otherwise
    }
    httplib::Client& cli = *m_Impl->Client;
    cli.set_connection_timeout(timeout, 0);
    cli.set_read_timeout(timeout, 0);
    cli.set_write_timeout(timeout, 0);

    httplib::Params form;
    for (const auto& p : params)
        form.emplace(p.first, p.second);
    auto res = cli.Post("/" + command, form);
    if (!res) {
        errorStr = Format("%s: %s", addr.toString().c_str(), httplib::to_string(res.error()).c_str());
        Close();
        return HttpErrorToNetworkError(res.error());
    }
    if (res->status != httplib::StatusCode::OK_200) {
        errorStr = Format("%s: http status %i: %s", addr.toString().c_str(), res->status, res->body.c_str());
        Result = res->body;
        return neProtocolError;
    }
    Result = std::move(res->body);
    return neSuccess;
}

NetworkErrorsEnum HttpRequest(const CSocketAddr& addr, const string& command, const RequestParams& params,
                              int timeout, string& Result, string& errorStr)
{
    CHttpConnection conn(addr);
    return conn.Request(command, params, timeout, Result, errorStr);
}

//======================================================================
string GetNetworkErrorString(const NetworkErrorsEnum& t)
{
    switch (t) {
        case neSuccess: return "No error";
        case neNetworkError: return "General network error";
        case neTimeout: return "Timeout elapsed";
        case neProtocolError: return "Protocol error";
        case neSubcorpusNotFound: return "Unknown subcorpus";
        case neInternalReadAccessError: return "Internal index access error";
        case neCouldNotOpenSocket: return "Could not connect";
        case neCouldNotSendData: return "Could not send a request";
        case neCouldNotReceiveData: return "Could not receive a response";
        case neInternalError: return "Internal error";
        case neRequestTooLarge: return "Request too large";
        default: break;
    };
    return "Unknown error code";
};
