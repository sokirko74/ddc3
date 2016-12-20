//-*- Mode: C++; c-basic-offset:8;-*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2016 by Bryan Jurish
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
#include <string.h>
#include <errno.h>
#include "../CommonLib/string_socket.h"
#include "../CommonLib/CHost.h"
#include "../common/util_classes.h"
#include "../common/DDCInternalError.h"

#ifdef WIN32
const int ddcSocketChunkSize = 1024;
#else
const int ddcSocketChunkSize = 4096;
#endif

#ifdef WIN32
	#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
	#endif
#endif

//#define DDC_DEBUG_FDLEAK 1
#undef DDC_DEBUG_FDLEAK
#ifdef DDC_DEBUG_FDLEAK
# define FDDEBUG(x) x
#else
# define FDDEBUG(x)
#endif


//! DDC_SOCKET_SEND_MULTI : define this to enable old multiple-send() calls
#undef DDC_SOCKET_SEND_MULTI

struct ERROR_STRUCT
{     
	int     errnum;     
	const char*   errstr; 
} ;  
const char msg_no_error[19] =      "No error occurred!"; 
const char msg_unknown_error[14] = "Unknown error";  
const string DDCCloseSocketString =  "ddc_close_socket";

const ERROR_STRUCT errlist[] = {     
	{EINTR,           "Socket Error! EINTR - Interrupted"},     
	{EBADF, "Socket Error! EBADF - Bad file number"},                
	{EFAULT,   "Socket Error! EFAULT - Bad address"},               
	{EINVAL,          "Socket Error! EINVAL - Invalid argument"},               
	{EMFILE,          "Socket Error! EMFILE - Too many open files"},            
	{EACCES,  "Socket Error! The address is protected, and the user is not the super-user."} ,
	{EROFS , "Socket Error! The socket inode would reside on a read-only file system."},
	{EFAULT, "Socket Error! my_addr points outside the user's accessible address space. "},
	{ENAMETOOLONG, "Socket Error! my_addr is too long."}, 
	{ENOENT, "Socket Error! The file does not exist."},
	{ENOMEM, "Socket Error! Insufficient kernel memory was available." },
	{ENOTDIR, "Socket Error! A component of the path prefix is not a directory." },

#ifndef WIN32
	{ELOOP, "Too many symbolic links were encountered in resolving my_addr" },
	{ENOTSOCK, "Argument is a descriptor for a file, not a socket."}
#endif

};

//----------------------------------------------------------------------
bool CloseSocket(int l_socket, bool linger, int timeout)
{
	bool bResult;
	if (l_socket == -1) return true;
#ifdef WIN32
	bResult = closesocket(l_socket) == 0;
#else
	if (linger) {
		//-- optionally force SO_LINGER socket option (e.g. timeout=0 for immediate termination via RST; avoid TCP TIME_WAIT)
		struct linger sock_linger;
		sock_linger.l_onoff = (linger ? 1 : 0);
		sock_linger.l_linger = timeout;
		setsockopt(l_socket, SOL_SOCKET, SO_LINGER, (void*)&sock_linger, sizeof(struct linger));
	}
	bResult =  close(l_socket) == 0;
#endif
	FDDEBUG(fprintf (stderr, "FDDEBUG: CloseSocket(%u) returned %s\n", (uint)l_socket, (bResult? "true" : "false"));)
	return bResult;
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
	#ifdef WIN32
		count = send(client_fd, Buffer, Length, 0);
	#else
		count = send(client_fd, Buffer, Length, MSG_NOSIGNAL);
	#endif
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
		if (addr.sa_family == AF_INET) {
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
string SocketPeerP(SOCKET sock)
{
	string PeerAddr;
	int    PeerPort;
	SocketPeer(sock, PeerAddr, PeerPort);
	return Format("%s:%d", PeerAddr.c_str(), PeerPort);
}

//----------------------------------------------------------------------
bool SendString (int client_fd, const char* Str, uint32_t  PacketLength, string& ErrorStr)
{
	try {
		uint32_t PacketLength_lsb = size_to_lsb(PacketLength);
		if (!send_buffer(client_fd, (const char*)&PacketLength_lsb, sizeof(PacketLength_lsb), ErrorStr) )
			return false;

#ifdef DDC_SOCKET_SEND_MULTI
		//-- iterative chunked send
		const int buffer_len = ddcSocketChunkSize;
		if (PacketLength <= buffer_len)
		{
			if (!send_buffer(client_fd, Str, (int)PacketLength, ErrorStr))
				return false;
		}
		else
		{
			int i = 0;
			for (; i< PacketLength/buffer_len;  i++)
			{
				if (!send_buffer(client_fd, (Str + i*buffer_len), buffer_len, ErrorStr))
				{
					return false;
				}
			};

			uint32_t rest=PacketLength % buffer_len;
			if (!send_buffer(client_fd, (Str + i*buffer_len), (int)rest, ErrorStr))
			{
				return false;
			}
		};
		return true;
#else
		//-- single send() call; let libc+kernel handle chunking
		return send_buffer(client_fd, Str, (int)PacketLength, ErrorStr);
#endif
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
		throw CExpc(errOther, "FD_ISSET() failed for client socket after select(): %s", StrError(errno));

	#ifdef WIN32
	 have_read = recv (client_fd, Buffer, Length, 0);
	#else
	 have_read = recv (client_fd, Buffer, Length, MSG_NOSIGNAL);
	#endif
	
	 if (have_read <= 0)
		 throw CExpc(errOther, "receive_buffer() failed: expected %d byte(s) from recv(), but got only %d: %s", Length, have_read, StrError(errno));

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
bool SetSocketReceiveBuffer(int socket_fd, int BufferSize)
{

	if (setsockopt( socket_fd, SOL_SOCKET, SO_RCVBUF, (void*)&BufferSize, sizeof(size_t) ))
		return false;

	return true;
}

//----------------------------------------------------------------------
bool SetSocketSendBuffer(int socket_fd, int BufferSize)
{
	if (setsockopt( socket_fd, SOL_SOCKET, SO_SNDBUF, (void*)&BufferSize, sizeof(size_t) ))
		return false;

	return true;
}


//----------------------------------------------------------------------
string GetBindErrorLinux (int ErrCode)
{
	for (size_t i=0; i < sizeof(errlist) / sizeof(errlist[0]); i++)
		if (errlist[i].errnum == ErrCode)
			return errlist[i].errstr;
	return Format("unknown socket error (bind returned %i): %s", ErrCode, StrError(errno));
};

//----------------------------------------------------------------------
bool fd_is_valid(int fd)
{
    return fcntl(fd, F_GETFD) != -1 || errno != EBADF;
}

//----------------------------------------------------------------------
SOCKET create_socket (const char* HostAddr, int Port, bool bBind, string& strError)
{
	strError = "";
	struct addrinfo hints, *res, *res0; 
	int error;
	SOCKET l_socket;
	

	memset(&hints, 0, sizeof(hints));
	if (bBind)
		hints.ai_flags = AI_PASSIVE;
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	error = getaddrinfo(HostAddr, Format("%i",Port).c_str(), &hints, &res0);
	if (error) {
		strError = Format("Socket Error! %s", gai_strerror(error)); /*NOTREACHED*/
		throw CExpc(errRuntime, strError);
	}
	l_socket = -1;
	string cause  = "no addresses";
	for (res = res0; res; res = res->ai_next) 
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
				#ifdef WIN32
					cause = GetBindErrorWindows(WSAGetLastError());
				#else
					cause = GetBindErrorLinux(errno);
				#endif
			}
			else
				cause = "Could not connect";
			CloseSocket(l_socket, true, 0);
			l_socket = -1;
			continue;
		} 
		break; /* okay we got one */ 
	}
	if (l_socket == -1)
	{
		strError = Format("%s for %s:%i\n", cause.c_str(), HostAddr, Port);
		throw CExpc(errRuntime, strError);
		/*NOTREACHED*/
	}
	else {
		//-- setup socket options (TCP_NODELAY : disable Nagle's algorithm / force immediate send())
		int flag=1;
		setsockopt(l_socket, IPPROTO_TCP, TCP_NODELAY, (char *)&flag, sizeof(int));
	}
 	freeaddrinfo(res0);

	FDDEBUG(fprintf(stderr, "DEBUG: create_socket(host=%s, port=%d, bind=%d) --> %u\n", HostAddr, Port, (bBind ? 1 : 0), (uint)l_socket);)
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
	#ifdef WIN32
		WORD    wVersionRequested;
		WSADATA wsaData;
		int     err;
		wVersionRequested = MAKEWORD(1,1);
		err = WSAStartup(wVersionRequested,&wsaData);
		if (err != 0) {
			//MessageBox(NULL, "Service could invoke WSAStartup()", "Concordance Socket", MB_OK);
			return false;
		}
	#endif
	
	return true;
};

//----------------------------------------------------------------------
bool SocketDeinitialize()
{
	#ifdef WIN32
		WSACleanup ();
	#endif

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

