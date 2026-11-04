//-*- Mode: C++ -*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2020 by Bryan Jurish
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
#include "string_socket.h"
#include "CHost.h"
#include "util_classes.h"
#include "DDCInternalError.h"

#include <string.h>
#include <errno.h>
#include <sys/un.h>
#include "ddcExpc.h"
#include "ddcLocale.h"
#include "ddcString.h"

using namespace std;

const int ddcSocketChunkSize = DDC_STATIC_BUFLEN;


//#define DDC_DEBUG_FDLEAK 1
#undef DDC_DEBUG_FDLEAK
#ifdef DDC_DEBUG_FDLEAK
# define FDDEBUG(x) x
#else
# define FDDEBUG(x)
#endif


//======================================================================
// CSocketAddr

//--------------------------------------------------------------
void CSocketAddr::Clear()
{
    m_Type = stUnknown;
    m_Addr.clear();
    m_Port = -1;
}

//--------------------------------------------------------------
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

//--------------------------------------------------------------
void CSocketAddr::ParseSocketAddr(const string& Str, bool parsePort)
{
    string s(Str);
    string lo = stolower(s);
    if (startswith(lo,"tcp://")) {
        m_Type = stINET;
        m_Addr = s.substr(6);
    }
    else if (startswith(lo,"tcp:")) {
        m_Type = stINET;
        m_Addr = s.substr(4);
    }
    else if (startswith(lo,"inet://")) {
        m_Type = stINET;
        m_Addr = s.substr(7);
    }
    else if (startswith(lo,"inet:")) {
        m_Type = stINET;
        m_Addr = s.substr(5);
    }
    else if (startswith(lo, "unix://")) {
        m_Type = stUNIX;
        m_Addr = s.substr(7);
    }
    else if (startswith(lo, "unix:")) {
        m_Type = stUNIX;
        m_Addr = s.substr(5);
    }
    else if (startswith(Str,"/")) {
        m_Type = stUNIX;
        m_Addr = s;
    }
    else {
        //-- default: INET
        m_Type = stINET;
        m_Addr = s;
    }

    //-- parse port
    if (parsePort)
        ParseAddrPort();
}

//--------------------------------------------------------------
void CSocketAddr::ParseAddrPort()
{
    TrimRight(m_Addr);
    size_t pi = m_Addr.find_last_of(" \t\r\n:");
    if (pi > 0 && pi < (m_Addr.size()-1)) {
        m_Port = strtol(m_Addr.substr(pi+1).c_str(), NULL, 0);
        m_Addr.erase(pi);
        TrimRight(m_Addr);
    }
}

//--------------------------------------------------------------
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
// Utilities

//----------------------------------------------------------------------
bool CloseSocket(int l_socket, bool linger, int timeout)
{
    bool bResult;
    if (l_socket == -1) return true;
    if (linger) {
        //-- optionally force SO_LINGER socket option (e.g. timeout=0 for immediate termination via RST; avoid TCP TIME_WAIT)
        struct linger sock_linger;
        sock_linger.l_onoff = (linger ? 1 : 0);
        sock_linger.l_linger = timeout;
        setsockopt(l_socket, SOL_SOCKET, SO_LINGER, (void*)&sock_linger, sizeof(struct linger));
    }
    bResult =  close(l_socket) == 0;
    FDDEBUG(fprintf (stderr, "FDDEBUG: CloseSocket(%u) returned %s\n", (uint)l_socket, (bResult? "true" : "false"));)
        return bResult;
};

//----------------------------------------------------------------------
bool CloseSocketRef(SOCKET& rConnectedSocket, bool linger, int timeout)
{
    if (rConnectedSocket == -1) return true;
#ifdef DDC_DEBUG_FDLEAK
    ddcLogTrace(Format("closing socket descriptor #%i (linger=%s, timeout=%i)", rConnectedSocket, (linger ? "true" : "false"), timeout));
#endif
    bool rc = CloseSocket(rConnectedSocket, linger, timeout);
    rConnectedSocket = -1;
    return rc;
};

//----------------------------------------------------------------------
const int FLAGS = 0;

uint32_t size_to_lsb(uint32_t sz)
{
    unsigned char buf[4] = {0,0,0,0};
    buf[0] =  sz      & 0xff;
    buf[1] = (sz>> 8) & 0xff;
    buf[2] = (sz>>16) & 0xff;
    buf[3] = (sz>>24) & 0xff;
    return *((uint32_t*)buf);
}

//----------------------------------------------------------------------
uint32_t lsb_to_size(uint32_t sz_lsb)
{
    unsigned char *buf = ((unsigned char*)&sz_lsb);
    uint32_t      sz   = buf[0] | (buf[1]<<8) | (buf[2]<<16) | (buf[3]<<24);
    return sz;
}

//----------------------------------------------------------------------
inline bool send_buffer(int client_fd, const char* Buffer,int Length, string& Error)
{
    int count;
    count = send(client_fd, Buffer, Length, MSG_NOSIGNAL);
    if (count == -1)
    {
        int err = errno;
        Error = Format("%s; errno=%i", StrError(err), err);
        return false;
    }       

    Error = "";
    return true;
};


//======================================================================
// generic socket utilities

//----------------------------------------------------------------------
void SocketPeer(SOCKET sock, string& PeerIP, int& PeerPort)
{
    socklen_t len = sizeof(sockaddr);
    struct sockaddr addr;

    PeerIP.clear();
    PeerPort = 0;

    if (getpeername(sock, (struct sockaddr*)&addr, &len)==0) {
        if (addr.sa_family == AF_UNIX) {
            struct ucred cred;
            socklen_t cred_len = sizeof(struct ucred);
            getsockopt(sock, AF_UNIX, SO_PEERCRED, &cred, &cred_len);
            PeerPort = cred.pid;
            PeerIP   = Format("PID %d", PeerPort);
        }
        else if (addr.sa_family == AF_INET) {
            char ipstr[INET_ADDRSTRLEN];
            struct sockaddr_in *s = (struct sockaddr_in *)&addr;
            PeerPort = ntohs(s->sin_port);
            inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof(ipstr));
            PeerIP = ipstr;
        }
#if 0
        //-- handle IPv6
        else { // AF_INET6
            char ipstr[INET6_ADDRSTRLEN];
            struct sockaddr_in6 *s = (struct sockaddr_in6 *)&addr;
            PeerPort = ntohs(s->sin6_port);
            inet_ntop(AF_INET6, &s->sin6_addr, ipstr, sizeof(ipstr));
            PeerIP = ipstr;
        }
#endif
    }
    if (PeerIP.empty()) {
        //-- something went wrong
        PeerIP   = "???";
        PeerPort = 0;
    }
}

//----------------------------------------------------------------------
string SocketPeer(SOCKET sock)
{
    string PeerAddr;
    int    PeerPort;
    SocketPeer(sock, PeerAddr, PeerPort);
    return PeerAddr;
}


//----------------------------------------------------------------------
bool SendString (int client_fd, const char* Str, uint32_t  PacketLength, string& ErrorStr)
{
    try {
        uint32_t PacketLength_lsb = size_to_lsb(PacketLength);
        if (!send_buffer(client_fd, (const char*)&PacketLength_lsb, sizeof(PacketLength_lsb), ErrorStr) )
            return false;

        return send_buffer(client_fd, Str, (int)PacketLength, ErrorStr);
    }
    catch (...)
    {
        return false;
    };
};

//----------------------------------------------------------------------
bool SendString (int client_fd, const std::string &str, string& ErrorStr)
{
    uint32_t    len  = str.size();
    const char *data = str.data();
    return SendString(client_fd, data, len, ErrorStr);
}

//----------------------------------------------------------------------
NetworkErrorsEnum receive_buffer(int client_fd, char* Buffer,int Length, int& have_read, int TimeOut)
{
    fd_set fds;
    struct timeval timeout;
    timeout.tv_sec = (TimeOut == -1) ? 1000: TimeOut;
    timeout.tv_usec = 0;
        

    FD_ZERO(&fds);
    FD_SET(client_fd,&fds);

    if (!select(FD_SETSIZE, &fds,NULL,NULL, &timeout))
        return neTimeout;
                
    if (!FD_ISSET(client_fd,&fds))
        throw CDDCExpc(errOther, "FD_ISSET() failed for client socket after select(): %s", StrError(errno));

    have_read = recv (client_fd, Buffer, Length, MSG_NOSIGNAL);

    if (have_read <= 0)
        throw CDDCExpc(errOther, "receive_buffer() failed: expected %d byte(s) from recv(), but got only %d: %s", Length, have_read, StrError(errno));

    return neSuccess;
};


//----------------------------------------------------------------------
NetworkErrorsEnum ReceiveString(int  client_fd, string& Result, int TimeOut, uint32_t maxPacketLength)
{

    try {
        uint32_t PacketLength, PacketLength_lsb;
        int have_read;

        NetworkErrorsEnum Res = receive_buffer (client_fd, (char*)&PacketLength_lsb, sizeof(PacketLength_lsb), have_read, TimeOut);
        if (Res != neSuccess )
        {
            return Res;
        }


        PacketLength  = lsb_to_size(PacketLength_lsb);
        if (maxPacketLength>0 && PacketLength > maxPacketLength)
            return neRequestTooLarge; //-- whoa!
        Result.clear();
        Result.reserve(PacketLength);

        //-- iterative chunked recv
        const int buffer_len = ddcSocketChunkSize;
        char buffer[buffer_len];
        int n_remaining=PacketLength;

        while (n_remaining > 0)
        {
            int to_read = n_remaining < buffer_len ? n_remaining : buffer_len;
                        
            Res = receive_buffer (client_fd, (char*)buffer, to_read, have_read, TimeOut);
            if (Res != neSuccess)
                return Res;

            n_remaining -= have_read;
            Result.append(buffer,have_read);
        };
        return neSuccess;
    }
    catch (...)
    {
        throw;
        //return neCouldNotReceiveData;
    };
};

//----------------------------------------------------------------------
SOCKET create_socket(const CSocketAddr& Addr, bool bBind, mode_t bindPerms, string& strError)
{
    switch (Addr.m_Type) {
        case stUNIX:
            return create_unix_socket(Addr.m_Addr, bBind, bindPerms, strError);
        case stINET:
            return create_inet_socket(Addr.m_Addr.c_str(), Addr.m_Port, bBind, strError);
        default:
            throw CDDCExpc("ERROR: create_socket(): unknown socket type");
    }
    return -1;
}

//----------------------------------------------------------------------
SOCKET create_unix_socket(const string& socket_path,  bool bBind, mode_t bindPerms, string& strError)
{
    SOCKET l_socket = -1;
    if (bBind) {
        if (unlink(socket_path.c_str()) != 0) {
            if (errno != ENOENT)
                throw CDDCExpc(Format("failed to remove stale UNIX socket %s: %s\n",
                                   socket_path.c_str(), StrError(errno)));
        } else {
            ddcLogWarn("removed stale UNIX socket "+socket_path);
        }
    }

    l_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if ( l_socket  == -1) {
        strError = Format("Could not create UNIX socket %s: %s", socket_path.c_str(), StrError(errno));
        throw CDDCExpc(errRuntime, strError);
    }
    sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socket_path.c_str(), socket_path.length());
    if (bBind) {
        //server
        if (bind(l_socket, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
            strError = Format("bind() failed for UNIX socket %s: %s", socket_path.c_str(), StrError(errno));
            CloseSocketRef(l_socket, true, 0);
        }
        else if (bindPerms != 0) {
            //-- force user-specified socket permissions (default = 0777 & ~umask())
            if (chmod(socket_path.c_str(), bindPerms) != 0) {
                ddcLogWarn(Format("failed to set permissions mask=%04o for UNIX socket %s: %s",
                                  bindPerms, socket_path.c_str(), StrError(errno)));
            }
        }

    }
    else {
        //client
        if (connect(l_socket, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
            strError = Format("Could not connect to UNIX socket %s: %s", socket_path.c_str(), StrError(errno));
            CloseSocketRef(l_socket, true, 0);
        }
    }

    //-- sanity check
    if (l_socket == -1) {
        if (strError.empty())
            strError = Format("error for UNIX socket %s: %s\n", socket_path.c_str(), StrError(errno));
        throw CDDCExpc(errRuntime, strError);
    }
    
    return l_socket;
}

//----------------------------------------------------------------------
SOCKET create_socket (const char* HostAddr, int Port, bool bBind, string& strError)
{ return create_inet_socket(HostAddr, Port, bBind, strError); }

SOCKET create_inet_socket (const char* HostAddr, int Port, bool bBind, string& strError)
{
    strError = "";
    addrinfo hints, *res0;
    SOCKET l_socket = -1;
    memset(&hints, 0, sizeof(hints));
    if (bBind)
        hints.ai_flags = AI_PASSIVE;
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    int error = getaddrinfo(HostAddr, Format("%i",Port).c_str(), &hints, &res0);
    if (error) {
        strError = Format("Socket Error! %s", gai_strerror(error)); /*NOTREACHED*/
        throw CDDCExpc(errRuntime, strError);
    }
    string cause  = "no addresses";
    for (addrinfo* res = res0; res; res = res->ai_next)
    { 
        l_socket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (l_socket < 0) 
        {
            cause = Format("Could not create socket: %s", StrError(errno));
            continue;
        } 
        int Res;
        errno = 0;

        if (bBind)
        {
            int flag = 1; 

            if ( setsockopt(l_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&flag, sizeof(flag)) != 0 )
            {
                cause = Format("Socket Error! Could not set socket option SO_REUSEADDR: %s", StrError(errno));
                CloseSocket(l_socket, true, 0);
                l_socket = -1;
                continue;
            };

            Res = bind(l_socket, res->ai_addr, res->ai_addrlen);
        }
        else {
            //-- set SO_LINGER for immediate termination for client sockets
            struct linger sock_linger = {1,0};
            setsockopt(l_socket, SOL_SOCKET, SO_LINGER, (void*)&sock_linger, sizeof(struct linger));
                        
            Res = connect(l_socket, res->ai_addr, res->ai_addrlen);
        }

                

        if (Res < 0) 
        {
            if (bBind)
            {
                cause = StrError(errno);
            }
            else
                cause = "Could not connect";
            CloseSocketRef(l_socket, true, 0);
            continue;
        } 
        break; /* okay we got one */ 
    }
    if (l_socket == -1)
    {
        strError = Format("%s for %s:%i\n", cause.c_str(), HostAddr, Port);
        throw CDDCExpc(errRuntime, strError);
        /*NOTREACHED*/
    }
    else {
        //-- setup socket options (TCP_NODELAY : disable Nagle's algorithm / force immediate send())
        int flag=1;
        setsockopt(l_socket, IPPROTO_TCP, TCP_NODELAY, (char *)&flag, sizeof(int));
    }
    freeaddrinfo(res0);

    FDDEBUG(fprintf(stderr, "DEBUG: create_socket(host=%s, port=%d, bind=%d) --> %u\n", HostAddr, Port, (bBind ? 1 : 0), (uint)l_socket));
    return l_socket;
};

//----------------------------------------------------------------------
void flush_socket(SOCKET sock)
{
    // explicitly flush a socket by (temporarily) enabling the TCP_NODELAY option
    // - see discussion at http://stackoverflow.com/questions/6835216/how-to-push-i-e-flush-data-sent-to-a-tcp-stream
    socklen_t flaglen = sizeof(int);
    int oldflag, flag=1;
    getsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&oldflag, &flaglen);
    if (oldflag) return;
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&flag,     flaglen);
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&oldflag,  flaglen);
};


//----------------------------------------------------------------------
bool SocketInitialize(bool bReadFromLocalFile)
{

    return true;
};

//----------------------------------------------------------------------
bool SocketDeinitialize()
{
    return true;
};

//----------------------------------------------------------------------
string GetNetworkErrorString(const NetworkErrorsEnum& t)
{
    switch (t) {
        case neSuccess: return "No error";
        case neNetworkError: return "General network error";
        case neTimeout: return "Timeout elapsed";
        case neProtocolError: return "Different protocols are used";
        case neSubcorpusNotFound: return "Unknown subcorpus";
        case neInternalReadAccessError: return "Internal index access error";
        case neCouldNotOpenSocket: return "Could not open some socket";
        case neCouldNotSendData: return "Could not send data to a socket";
        case neCouldNotReceiveData: return "Could not receive data to a socket";
        case neInternalError: return "Internal error";
        case neRequestTooLarge: return "Request too large";
        default: break;
    };
    return "Unknown error code";
};

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
