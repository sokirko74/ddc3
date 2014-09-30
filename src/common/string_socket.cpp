//-*- Mode: C++; c-basic-offset:8;-*-
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2014 by Bryan Jurish
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
	#include <netdb.h>
	#include <stdio.h>
	#include <fcntl.h>
	#define SOCKET int
#endif


#ifdef WIN32
const int ddcSocketChunkSize = 1024;
#else
const int ddcSocketChunkSize = 4096;
#endif
const int ddcListenSocketBufferSize = 131072;



#include "string_socket.h"
#include "../common/util_classes.h"
#include "../common/DDCInternalError.h"
#include <errno.h>

#ifdef WIN32
	#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
	#endif
#endif




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


bool CloseSocket(int l_socket)
{
	bool bResult;
	#ifdef WIN32
			bResult = closesocket(l_socket) == 0;
	#else
			bResult =  close(l_socket) == 0;
	#endif
	//fprintf (stderr, "CloseSocket %i returned %s\n", l_socket, bResult? "true":"false");
	return bResult;
};


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

uint32_t lsb_to_size(uint32_t sz_lsb)
{
	unsigned char *buf = ((unsigned char*)&sz_lsb);
	uint32_t      sz   = buf[0] | (buf[1]<<8) | (buf[2]<<16) | (buf[3]<<24);
	return sz;
}

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
		Error = Format("%s; errno=%i", strerror(err), err);;
		return false;
	}	

	Error = "";
	return true;
};


//======================================================================
// generic socket utilities

bool SendString (int client_fd, const char* Str, uint32_t  PacketLength, string& ErrorStr)
{
	try {
		uint32_t PacketLength_lsb = size_to_lsb(PacketLength);
		if (!send_buffer(client_fd, (const char*)&PacketLength_lsb, sizeof(PacketLength_lsb), ErrorStr) )
			return false;

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
	}
	catch (...)
	{
		return false;
	};
};

bool SendString (int client_fd, const std::string &str, string& ErrorStr)
{
	uint32_t    len  = str.size();
	const char *data = str.data();
	return SendString(client_fd, data, len, ErrorStr);
}


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
		throw CExpc(errOther, "FD_ISSET() failed for client socket after select(): %s", client_fd, strerror(errno));

	#ifdef WIN32
	 have_read = recv (client_fd, Buffer, Length, 0);
	#else
	 have_read = recv (client_fd, Buffer, Length, MSG_NOSIGNAL);
	#endif
	
	 if (have_read <= 0)
		throw CExpc(errOther, "receive_buffer() failed: expected %d byte(s) from recv(), but got only %d: %s", Length, have_read, strerror(errno));

	return neSuccess;
};



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

		const int buffer_len = ddcSocketChunkSize;
		char buffer[buffer_len];
		uint32_t  AllRead = 0;

		while (AllRead < PacketLength)
		{
			int to_read = buffer_len;
			if (PacketLength - AllRead < buffer_len)
					to_read = PacketLength - AllRead;

			
			Res = receive_buffer (client_fd, (char*)buffer, to_read, have_read, TimeOut);
			if (Res != neSuccess )
					return Res;

			AllRead += have_read;
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

bool SetSocketReceiveBuffer(int socket_fd, int BufferSize)
{

	if (setsockopt( socket_fd, SOL_SOCKET, SO_RCVBUF, (void*)&BufferSize, sizeof(size_t) ))
		return false;

	return true;
}

bool SetSocketSendBuffer(int socket_fd, int BufferSize)
{
	if (setsockopt( socket_fd, SOL_SOCKET, SO_SNDBUF, (void*)&BufferSize, sizeof(size_t) ))
		return false;

	return true;
}


string GetBindErrorLinux (int ErrCode)
{
	for (size_t i=0; i < sizeof(errlist) / sizeof(errlist[0]); i++)
		if (errlist[i].errnum == ErrCode)
			return errlist[i].errstr;
	return Format("unknown socket error (bind returned %i): %s", ErrCode, strerror(errno));
};

bool fd_is_valid(int fd)
{
    return fcntl(fd, F_GETFD) != -1 || errno != EBADF;
}

SOCKET create_socket (const char* HostName, int Port, bool bBind, string& strError)
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
	error = getaddrinfo(HostName, Format("%i",Port).c_str(), &hints, &res0);
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
			cause = Format("Could not create socket: %s", strerror(errno));
			continue;
		} 
		int Res;
		errno = 0;

		if (bBind)
		{
			int flag = 1; 

			if (setsockopt( l_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&flag, sizeof(flag) ) != 0)
			{
				cause = Format("Socket Error! Could not set socket option SO_REUSEADDR: %s", strerror(errno));
				CloseSocket(l_socket);
				l_socket = -1;
				continue;
			};
			Res = bind(l_socket, res->ai_addr, res->ai_addrlen);
		}
		else
			Res = connect(l_socket, res->ai_addr, res->ai_addrlen);

		

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
			CloseSocket(l_socket);
			l_socket = -1;
			continue;
		} 
		break; /* okay we got one */ 
	}
	if (l_socket == -1)
	{
		strError = Format("%s for %s:%i\n", cause.c_str(), HostName, Port);
		throw CExpc(errRuntime, strError);
		/*NOTREACHED*/
	}
	freeaddrinfo(res0);

	return l_socket;
};


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

bool SocketDeinitialize()
{
	#ifdef WIN32
		WSACleanup ();
	#endif

	return true;
};

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

bool LoadHosts (string Path, vector<CHost>& Hosts)
{
	if (!FileExists(Path.c_str()))
	{
		fprintf (stderr, "LoadHosts() ERROR: cannot access file %s\n", Path.c_str());
		return false;
	};
	FILE * fp = fopen (Path.c_str(), "r");
	if (!fp) 
	{
		fprintf (stderr, "LoadHosts() ERROR: cannot open file %s\n", Path.c_str());
		return false;
	};
	char buffer[1024];
	int LineNo = 0;
	while (fgets(buffer, 1024, fp))
	{
		LineNo++;
		string Q = buffer;
		Trim(Q);
		if (Q.empty()) continue;
		if (Q[0] == '/') continue;
		CHost T(false, pdMediumDensity);
		if (!T.ReadFromString(Q)) 
		{
			fprintf (stderr, "LoadHosts ERROR: could not read line number %i\n", LineNo);
			fclose(fp);
			return false;
		};
		
		Hosts.push_back(T);
	};
	
	fclose(fp);

	return true;
};

CHost::CHost(bool bDoubleMessage, ProtocolDensityEnum pdProtocolDensity)
{
	m_LogFunction = 0;
	m_pdProtocolDensity = pdProtocolDensity;
	m_bDoubleMessage = bDoubleMessage;
	m_bExpectMore = false;
	m_ListenSocket = -1;
	m_Port = -1;
	m_maxReceiveBytes = 0;
};


bool CHost::ReadFromString (string S)
{
	StringTokenizer tok(S.c_str(), " \t\r\n");
	int ItemNo = 0;
	while (tok()) 
	{
			string Item = tok.val();
			if (ItemNo == 0)
				m_CorpusName = Item;
			else
			if (ItemNo == 1)
				m_HostName = Item;
			else
			if (ItemNo == 2)
			{
				m_Port = atoi(Item.c_str());
				m_LocalPath = tok.get_rest();
				Trim (m_LocalPath);
				break;
			};
			ItemNo++;
	};

	if (m_HostName.empty() || m_Port==-1) return false;

	return true;
};

int	CHost::CreateAndConnectSocket(string& strError) const
{
	int l_socket =  create_socket(m_HostName.c_str(), m_Port, false, strError);
	//fprintf (stderr, "create_and_connect %s:%i resulted in %i\n", HostName, Port, l_socket);
	return l_socket;
};


void CHost::AnswerByRequest (SOCKET rConnectedSocket, const struct sockaddr_in* client_addr, int TimeOut)
{
	string S;

	if (m_pdProtocolDensity  == pdHeavyDensity)
	{
		m_LogFunction(Format("%s received a string (Timeout=%i)", m_CorpusName.c_str(), TimeOut ));
	}
	NetworkErrorsEnum Res = ReceiveString(rConnectedSocket, S, TimeOut, m_maxReceiveBytes);
						
	if (Res != neSuccess)
	{
		//ClientError(0, Format("Error [%d]: %s", Res, GetNetworkErrorString(Res).c_str()), rConnectedSocket); //-- doesn't work well...
		m_LogFunction(Format("Error: Cannot receive string for corpus \"%s\" (error: %s)", m_CorpusName.c_str(), GetNetworkErrorString(Res).c_str()));
		m_bExpectMore = false;
		return;
	};


	if (m_pdProtocolDensity  == pdHeavyDensity)
	{
		const char* src_addr = inet_ntoa(client_addr->sin_addr);
		m_LogFunction(Format("%s recv \"%s\" from %s", m_CorpusName.c_str(), S.c_str(),src_addr ));
	}

	string Result = ProcessSocketString(S, rConnectedSocket);

	// send the answer
	if (m_pdProtocolDensity  == pdHeavyDensity)
	{
		m_LogFunction(Format("%s has finished processing", m_CorpusName.c_str() ));
	}

	string ErrorStr;
	if (!SendString(rConnectedSocket, Result.c_str(), Result.length(), ErrorStr))
	{
		m_LogFunction(Format("Error! Cannot send string: %s", ErrorStr.c_str()));
		m_bExpectMore = false;
	}
	else
	if (m_pdProtocolDensity  == pdHeavyDensity)
	{
		const char* src_addr = inet_ntoa(client_addr->sin_addr);
		m_LogFunction(Format("%s sent back the result to %s (%zd bytes)", m_CorpusName.c_str(), src_addr, Result.size() ));
	}

}

void	CHost::StopAcceptingThread() 
{
	if (m_ListenSocket == -1)
		return;
	else
	{
		// I have tried to send a special closing message to m_ListenSocket,
		// which should have a special processing in AnswerByRequest,
		// but I failed to close a socket correctly, so I would like to do the following:
		// (even knowing that m_ListenSocket was created in a different thread)

		int l = m_ListenSocket;
		m_ListenSocket = -1;
		CloseSocket(l);
		
	};
};

string	CHost::ProcessSocketString(const string& S, SOCKET rConnectedSocket) 
{
	assert(false);
	return "";
};
//#ifndef socklen_t
//	typedef size_t socklen_t;
//#endif

void CHost::ClientError(int code, const string& msg, SOCKET clientSocket) 
{
	if (code != 0)
		m_LogFunction( Format("Client error (%d): %s", code, msg.c_str()) );
	if (clientSocket != -1) {
		string send_error_tmp; //-- ignored here
		SendString(clientSocket, Format("ERROR (%d): %s", code, msg.c_str()), send_error_tmp);
		CloseSocket(clientSocket);
	}
}

void   CHost::RunThread()
{
	m_ListenSocket = -1;
	string strError;

	m_ListenSocket = create_socket(m_HostName.c_str(), m_Port, true, strError);
	if (m_ListenSocket == -1)
	{
		string s = Format("%s [corpus name = %s] \n", strError.c_str(), m_CorpusName.c_str());
		m_LogFunction (  s );
		return ;
	};

	SetSocketReceiveBuffer (m_ListenSocket, ddcListenSocketBufferSize);

	// set maximal length of pending queue to 5 
	int listen_val = listen(m_ListenSocket, 5);
	if (listen_val == -1) {
		m_LogFunction ("Could not create the socket queue");
		CloseSocket(m_ListenSocket);
		m_ListenSocket = -1;
	}

	m_LogFunction ( Format("CHost on %s:%d waiting for accept", m_HostName.c_str(), m_Port) );
	size_t NumberOfSocketAccepts = 0;
	for (;;)
	{
		strError.clear();
		NumberOfSocketAccepts++;

		if (!(NumberOfSocketAccepts%100))
			m_LogFunction (Format("QueryCount = %i", NumberOfSocketAccepts));

		
		struct sockaddr_in client_addr;
		socklen_t client_addr_len = sizeof(sockaddr_in);
		SOCKET rConnectedSocket = accept(m_ListenSocket, (struct sockaddr *)&client_addr, &client_addr_len);

		if (m_ListenSocket == -1)  // the thread  should be stopped
		{
			if (rConnectedSocket  != -1) 
				CloseSocket(rConnectedSocket);
			break;
		};

		if (rConnectedSocket == -1) 
		{
			m_LogFunction (Format("Error:Could not get client socket: %s", strerror(errno)));
			continue;
		}
	

		try
		{
			//  if we have passed "accept", then Timeout can be very short
			m_bExpectMore = m_bDoubleMessage;

			AnswerByRequest(rConnectedSocket, &client_addr, 10);
			for (int i=0; i<10 && m_bExpectMore; ++i) {
				AnswerByRequest(rConnectedSocket, &client_addr, 30);
			}

			if (!CloseSocket(rConnectedSocket))
				m_LogFunction ( Format("cannot close socket for %s", m_CorpusName.c_str())  );

		}
		catch (CExpc& e) {
		  strError = Format("Exception[%d]: %s", e.code(), e.what());
		}
		catch (exception &e) {
		  strError = Format("Exception: %s", e.what());
		}
		catch (...) {
		  strError = "Exception: (unhandled exception)";
		}

		if (!strError.empty()) {
			m_LogFunction( Format("%s: CHost::RunThread(): ERROR: %s", m_CorpusName.c_str(), strError.c_str()) );
			m_LogFunction( Format("closing connected socket for %s", m_CorpusName.c_str()) );
			if (!CloseSocket(rConnectedSocket))
				m_LogFunction( Format("cannot close connected socket for %s", m_CorpusName.c_str()) );
		}
	}

	if (m_ListenSocket != -1)
	{
		m_LogFunction(Format("close socket for %s %s", m_CorpusName.c_str(), GetAddressStr().c_str()));

		if (!CloseSocket(m_ListenSocket))
			m_LogFunction ( Format("cannot close socket for %s", m_CorpusName.c_str())  );
		else
			m_ListenSocket = -1;

	};

};

#ifdef WIN32
	void  _cdecl ListenerThread( void* pParam )
#else
	void*   ListenerThread( void* pParam )
#endif
{
	CHost* pHost = (CHost* )pParam;
    try {
	    ddc_thread_init(pHost->m_CorpusName.c_str());

	#ifdef WIN32
		CoInitialize(NULL);
	#endif

	if ( SocketInitialize(false) )
	{
		pHost->RunThread();	
		SocketDeinitialize();
	}
	else
		pHost->m_LogFunction("Service could invoke AfxSocketInit()");
    }
    catch (exception &e) {
	    pHost->m_LogFunction( Format("ListenerThread[%s:%d]: Exception: %s", pHost->HostName().c_str(), pHost->Port(), e.what()) );
	    throw;
    }
    catch (...) {
	    pHost->m_LogFunction( Format("ListenerThread[%s:%d]: Exception: (unhandled exception)", pHost->HostName().c_str(), pHost->Port()) );
	    throw;
    }
	

	#ifdef WIN32 
		CoUninitialize();
		_endthread(); 
		return;	
	#else 
		return NULL; 
	#endif

};

void CHost::CreateListener() 
{

	m_LogFunction( Format ("Create Listener %s (%s)", m_CorpusName.c_str(), GetAddressStr().c_str()) );
	#ifdef WIN32
		_beginthread( ListenerThread, 0, (void*)this );
	#else
		pthread_t aThread;
		pthread_create(&aThread, NULL, ListenerThread, (void*)this);
	#endif

};

string	CHost::GetAddressStr() const
{
	if (m_HostName.empty())
		return "(null)";
	else
		return Format("%s:%i", m_HostName.c_str(), m_Port);
};

const string&	CHost::GetLocalPathOfIndex() const
{
	return m_LocalPath;
};

void CHost::CopyAddressParametersFrom(const CHost& X)
{
	m_HostName = X.m_HostName;
	m_Port = X.m_Port;
	m_LocalPath = X.m_LocalPath;
	m_CorpusName = X.m_CorpusName;
};


