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
#ifndef _string_socket_h
#define _string_socket_h

#include "../CommonLib/utilit.h"
#include "../CommonLib/ddcLog.h"

//  include headers for processes and sockets
#ifdef WIN32
	#include <winsock2.h>
	#include <Ws2tcpip.h>
	#include <process.h>
#else
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
#endif

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

#define SOCKET int
#ifdef WIN32
	struct sockaddr_in;
#endif

//======================================================================
// Constants

// default socket chunk size (for recv() loops)
extern const int ddcSocketChunkSize;

//======================================================================
// Utilities

/* moo / ddc-2.0.0: packet length arguments sent over sockets are ALWAYS 32-bit unsigned integers in little-endian order
 *  + big-endian ("network") order or fixed-width ASCII decimal would make more sense, but would break too much existing client code
 */
extern uint32_t size_to_lsb(uint32_t sz);
extern uint32_t lsb_to_size(uint32_t sz_lsb);

extern bool fd_is_valid(int fd);
extern SOCKET create_socket (const char* HostAddr, int Port, bool bBind, string& strError);
extern void flush_socket (SOCKET sock);
extern bool SocketInitialize(bool bReadFromLocalFile);
extern bool SocketDeinitialize();
/** close a socket; if \a linger is true, SO_LINGER option will be set for \a timeout second(s) */
extern bool CloseSocket(int l_socket, bool linger=false, int timeout=5);
extern string GetNetworkErrorString(const NetworkErrorsEnum& t);

//-- generic socket protocol utilities (pure-functions, used by ddc_daemon via CHost and ddc_search)
extern void SocketPeer(SOCKET sock, string& PeerAddr, int& PeerPort);
extern string SocketPeer(SOCKET sock);
extern string SocketPeerP(SOCKET sock);
extern bool SendString (int client_fd, const char* Str, uint32_t StrLen, string& ErrorStr);
extern bool SendString (int client_fd, const std::string &str, string& ErrorStr);
extern NetworkErrorsEnum receive_buffer(int client_fd, char* Buffer,int Length, int& have_read, int TimeOut);
extern NetworkErrorsEnum ReceiveString (int  client_fd, string& Result, int TimeOut, uint32_t maxPacketLength=0);

//-- set system-level socket buffer sizes (UNUSED)
extern bool SetSocketReceiveBuffer(int socket_fd, int BufferSize);
extern bool SetSocketSendBuffer(int socket_fd, int BufferSize);
	
#endif
