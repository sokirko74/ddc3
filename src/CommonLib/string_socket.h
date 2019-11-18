//-*- Mode: C++ -*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2019 by Bryan Jurish
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
#ifndef _string_socket_h
#define _string_socket_h

#include "utilit.h"
#include "ddcLog.h"

#include <pthread.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <stdio.h>
#include <fcntl.h>
#define SOCKET int

//-- debugging
//#define DDC_DEBUG_FDLEAK 1
#undef DDC_DEBUG_FDLEAK

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

/// enum for socket schemes
enum SocketTypeEnum {
    stUnknown = 0,
    stTCP = 1,
    stUNIX = 2
};

#define SOCKET int
#ifdef WIN32
struct sockaddr_in;
#endif

//======================================================================
// Constants

// default socket chunk size (for recv() loops)
extern const int ddcSocketChunkSize;

//======================================================================
// Constants

/** wrapper structure for abstract socket address parameters */
struct CSocketAddr
{
    SocketTypeEnum m_Type;	///< socket domain
    string         m_Addr;	///< unix:filesystem path, tcp:host address
    int            m_Port;      ///< unix:filler, tcp:port number

    /** default constructor */
    CSocketAddr(SocketTypeEnum sockType=stUnknown, const string& sockAddr="", int sockPort=-1)
        : m_Type(sockType), m_Addr(sockAddr), m_Port(sockPort)
    {};

    /** copy constructor */
    CSocketAddr(const CSocketAddr &X)
        : m_Type(X.m_Type), m_Addr(X.m_Addr), m_Port(X.m_Port)
    {};

    /** constructor from string */
    CSocketAddr(const string& Str, bool parsePort=true)
        : m_Type(stUnknown), m_Addr(), m_Port(-1)
    { ParseSocketAddr(Str, parsePort); };

    /** assignment operator */
    CSocketAddr& operator=(const CSocketAddr& X)
    {
        m_Type = X.m_Type;
        m_Addr = X.m_Addr;
        m_Port = X.m_Port;
        return *this;
    }

    /** clear address parameters */
    void Clear();

    /** does this address look kosher? */
    bool IsValid() const;

    /** implicit cast-to-bool wraps IsValid() */
    inline operator bool() const
    { return IsValid(); };

    /** parse m_Type and m_Addr from \a Str.
     *  Implicitly calls ParseSocketPort() if \a parsePort is true.
     *  Supported notation:
     *  \li ADDR - TCP socket on ADDR
     *  \li tcp://ADDR_PORT - TCP socket on ADDR, with explicit scheme
     *  \li /PATH - UNIX socket on absolute path /PATH
     *  \li unix://PATH - UNIX socket on PATH
     *  \li unix:PATH - ditto
     */
    void ParseSocketAddr(const string& Str, bool parsePort=true);

    /** extract \a m_Port from \a m_Addr.  Supported notation:
     *  \li ADDR:PORT - TCP socket on ADDR:PORT
     *  \li ADDR PORT - same
     */
    void ParseAddrPort();

    /** return a URL-style string representation of this address */
    string toString() const;
};


//======================================================================
// Utilities

/* moo / ddc-2.0.0: packet length arguments sent over sockets are ALWAYS 32-bit unsigned integers in little-endian order
 *  + big-endian ("network") order or fixed-width ASCII decimal would make more sense, but would break too much existing client code
 */
extern uint32_t size_to_lsb(uint32_t sz);
extern uint32_t lsb_to_size(uint32_t sz_lsb);

extern SOCKET create_socket (const CSocketAddr& Addr, bool bBind, mode_t bindPerms, string& strError); //-- generic
extern SOCKET create_tcp_socket (const char* HostAddr, int Port, bool bBind, string& strError); 
extern SOCKET create_unix_socket(const string& socket_path,  bool bBind, mode_t bindPerms, string& strError);
extern SOCKET create_socket(const char* HostAddr, int Port, bool bBind, string& strError);  //-- compatibility wrapper for create_tcp_socket() 

extern void flush_socket (SOCKET sock);
extern bool SocketInitialize(bool bReadFromLocalFile);
extern bool SocketDeinitialize();

/** close a socket; if \a linger is true, SO_LINGER option will be set for \a timeout second(s) */
extern bool CloseSocket(int l_socket, bool linger=false, int timeout=5);

/** wrapper for CloseSocket() on a reference */
extern bool CloseSocketRef(SOCKET& rConnectedSocket, bool linger=false, int timeout=5);

extern string GetNetworkErrorString(const NetworkErrorsEnum& t);

//-- generic socket protocol utilities (pure-functions, used by ddc_daemon via CHost and ddc_search)
extern void SocketPeer(SOCKET sock, string& PeerAddr, int& PeerPort);
extern string SocketPeer(SOCKET sock);
extern bool SendString (int client_fd, const char* Str, uint32_t StrLen, string& ErrorStr);
extern bool SendString (int client_fd, const std::string &str, string& ErrorStr);
extern NetworkErrorsEnum receive_buffer(int client_fd, char* Buffer,int Length, int& have_read, int TimeOut);
extern NetworkErrorsEnum ReceiveString (int  client_fd, string& Result, int TimeOut, uint32_t maxPacketLength=0);


#endif

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
