//-*- Mode: C++; c-basic-offset:8;-*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2016 by Bryan Jurish
//
//  This file is part of DDC (formerly in string_socket.cpp)
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
#include "CHost.h"
#include "../common/util_classes.h"
#include "../common/DDCInternalError.h"
#include <string.h>
#include <errno.h>


//======================================================================
// CHost

//--------------------------------------------------------------
CHost::CHost()
{
	m_bExpectMore = false;
	m_bRespond   = true;
	m_bLogFinish = false;
	m_ListenSocket = -1;
	m_Port = -1;
	m_maxReceiveBytes = 0;
};


//--------------------------------------------------------------
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
				m_HostAddr = Item;
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

	if (m_HostAddr.empty() || m_Port==-1) return false;

	return true;
};

//--------------------------------------------------------------
bool CHost::Init (const string &CorpusName, const string& HostAddr, int Port, const string& LocalPath)
{
	m_CorpusName = CorpusName;
	m_HostAddr   = HostAddr;
	m_Port       = Port;
	m_LocalPath  = LocalPath;
	if (m_HostAddr.empty() || m_Port==-1) return false;
	return true;
};

//--------------------------------------------------------------
int	CHost::CreateAndConnectSocket(string& strError) const
{
	int l_socket = create_socket(m_HostAddr.c_str(), m_Port, false, strError);
	//fprintf (stderr, "create_and_connect %s:%i resulted in %i\n", HostAddr, Port, l_socket);
	return l_socket;
};

//--------------------------------------------------------------
bool CHost::GetRequest (SOCKET& rConnectedSocket, int TimeOut, string &Request)
{
	Request.clear();
	ddcLogTrace( Format("%s received a string (Timeout=%i) from %s", m_CorpusName.c_str(), TimeOut, SocketPeer(rConnectedSocket).c_str()) );

	NetworkErrorsEnum Res = ReceiveString(rConnectedSocket, Request, TimeOut, m_maxReceiveBytes);
						
	if (Res != neSuccess)
	{
		//ClientError(0, Format("Error [%d]: %s", Res, GetNetworkErrorString(Res).c_str()), rConnectedSocket); //-- doesn't work well...
		ddcLogError( Format("Error: Cannot receive string from %s (error: %s)", SocketPeer(rConnectedSocket).c_str(), GetNetworkErrorString(Res).c_str()) );
		m_bExpectMore = false;
		this->Close(rConnectedSocket);
		return false;
	}


	ddcLogTrace( Format("%s recv \"%s\" from %s", m_CorpusName.c_str(), Request.c_str(), SocketPeer(rConnectedSocket).c_str()) );

	//string Result = ProcessSocketString(S, rConnectedSocket);
	//SendResponse(rConnectedSocket, Result);
	return true;
}

//--------------------------------------------------------------
void CHost::SendResponse(SOCKET& rConnectedSocket, const string& Result)
{
	// send the answer
	ddcLogTrace( Format("%s has finished processing for %s", m_CorpusName.c_str(), SocketPeer(rConnectedSocket).c_str()) );

	string ErrorStr;
	if (m_bRespond && !SendString(rConnectedSocket, Result.c_str(), Result.length(), ErrorStr)) {
		ddcLogError( Format("Error! Cannot send string to %s: %s", SocketPeer(rConnectedSocket).c_str(), ErrorStr.c_str()) );
		m_bExpectMore = false;
	}
	else if (m_bLogFinish || ddcLogLevel >= ddcLLTrace) {
		string rpeer = SocketPeer(rConnectedSocket);
		if (m_bRespond)
			ddcLog(Format("%s sent back the result to %s (%zd bytes)", m_CorpusName.c_str(), rpeer.c_str(), Result.size()));
		else
			ddcLog(Format("%s no response required for client %s", m_CorpusName.c_str(), rpeer.c_str()));
	}

	if (!m_bExpectMore && !this->Close(rConnectedSocket)) {
		ddcLogError(Format("%s failed to close socket for client %s", m_CorpusName.c_str(), SocketPeer(rConnectedSocket).c_str()));
	}
}

//--------------------------------------------------------------
void CHost::HandleSocketError(SOCKET& rConnectedSocket, const string& ErrorStr, const string& Where)
{
	string rpeer = SocketPeer(rConnectedSocket);
	ddcLogError( Format("%s: ERROR: %s", Where.c_str(), ErrorStr.c_str()) );
	ddcLogError( Format("closing connected socket %s", rpeer.c_str()) );
	if (!this->Close(rConnectedSocket))
		ddcLogError( Format("cannot close connected socket %s", rpeer.c_str()) );
}

//--------------------------------------------------------------
void CHost::HandleClientRequest(SOCKET& rConnectedSocket, int TimeOut)
{
	//-- ~ ddc < v2.1.0 AnswerByRequest()
	string Request;
	if (!GetRequest(rConnectedSocket, TimeOut, Request)) return;
	string Result = this->ProcessSocketString(Request, rConnectedSocket);
	this->SendResponse(rConnectedSocket, Result);
}


//--------------------------------------------------------------
void CHost::HandleClientConnection(SOCKET& rConnectedSocket)
{
	string ErrorStr;
	try {
		this->HandleClientRequest(rConnectedSocket,10);
		for (int i=0; i < 10 && m_bExpectMore; ++i) {
			this->HandleClientRequest(rConnectedSocket,30);
		}

		if (!this->Close(rConnectedSocket))
			ddcLogError( Format("cannot close socket %s", SocketPeer(rConnectedSocket).c_str())  );
	}
	catch (CExpc& e) 	{ ErrorStr = Format("Exception[%d]: %s", e.code(), e.what()); }
	catch (exception &e)	{ ErrorStr = Format("Exception: %s", e.what()); }
	catch (...)		{ ErrorStr = "Exception: (unhandled exception)"; }

	if (!ErrorStr.empty())
		this->HandleSocketError(rConnectedSocket, ErrorStr, "CHost::HandleClientConnection()");
}

//--------------------------------------------------------------
void	CHost::StopAcceptingThread() 
{
	if (m_ListenSocket == -1)
		return;
	else
	{
		// I (=AS?) have tried to send a special closing message to m_ListenSocket,
		// which should have a special processing in AnswerByRequest,
		// but I failed to close a socket correctly, so I would like to do the following:
		// (even knowing that m_ListenSocket was created in a different thread)
		//
		// moo: set SO_LINGER timeout=0: close immediately
		this->Close(m_ListenSocket, true, 0);
	};
};

//--------------------------------------------------------------
string	CHost::ProcessSocketString(const string& S, SOCKET& rConnectedSocket) 
{
	assert(false);
	return "";
};
/*
#ifndef socklen_t
	typedef size_t socklen_t;
#endif
*/

//--------------------------------------------------------------
void CHost::ClientError(int code, const string& msg)
{
	SOCKET dummySocket = -1;
	this->ClientError(code, msg, dummySocket);
}

//--------------------------------------------------------------
void CHost::ClientError(int code, const string& msg, SOCKET& clientSocket) 
{
	if (code != 0)
		ddcLogError( Format("Client error (%d): %s", code, msg.c_str()) );
	if (clientSocket != -1) {
		string send_error_tmp; //-- ignored here
		SendString(clientSocket, Format("ERROR (%d): %s", code, msg.c_str()), send_error_tmp);
		this->Close(clientSocket);
	}
}

//--------------------------------------------------------------
bool CHost::Close(SOCKET& rConnectedSocket, bool linger, int timeout)
{
	if (rConnectedSocket == -1) return true;
#ifdef DDC_DEBUG_FDLEAK
	ddcLogTrace(Format("closing socket descriptor #%i (linger=%s, timeout=%i)", rConnectedSocket, (linger ? "true" : "false"), timeout));
#endif
	bool rc = CloseSocket(rConnectedSocket, linger, timeout);
	rConnectedSocket = -1;
	return rc;
}

//--------------------------------------------------------------
void   CHost::RunThread()
{
	string ErrorStr;
	m_ListenSocket = create_socket(m_HostAddr.c_str(), m_Port, true, ErrorStr);
	if (m_ListenSocket == -1)
	{
		ddcLogError(Format("%s [corpus name = %s] \n", ErrorStr.c_str(), m_CorpusName.c_str()));
		return;
	};

	// set maximal length of pending queue to 5 
	int listen_val = listen(m_ListenSocket, 5);
	if (listen_val == -1) {
		ddcLogError("Could not create the socket queue");
		this->Close(m_ListenSocket);
	}

	ddcLogInfo( Format("CHost on %s:%d waiting for accept", m_HostAddr.c_str(), m_Port) );
	size_t NumberOfSocketAccepts = 0;
	for (;;)
	{
		NumberOfSocketAccepts++;

		if (!(NumberOfSocketAccepts%100))
			ddcLogInfo(Format("QueryCount = %i", NumberOfSocketAccepts));

		struct sockaddr_in client_addr;
		socklen_t client_addr_len = sizeof(sockaddr_in);
		SOCKET rConnectedSocket = accept(m_ListenSocket, (struct sockaddr *)&client_addr, &client_addr_len);

		if (m_ListenSocket == -1)  // the thread  should be stopped
		{
			this->Close(rConnectedSocket);
			break;
		}

		if (rConnectedSocket == -1) 
		{
			this->HandleSocketError(rConnectedSocket, Format("could not get client socket: %s", StrError(errno)));
			continue;
		}
	

		//  if we have passed "accept", then Timeout can be very short
		//m_bExpectMore = m_bDoubleMessage;
		m_bRespond    = true;

		
		try {
			this->HandleClientConnection(rConnectedSocket); //-- formerly AnswerByRequest()
		}
		catch (CExpc& e) 	{ HandleSocketError(rConnectedSocket, Format("Exception[%d]: %s", e.code(), e.what())); }
		catch (exception &e)	{ HandleSocketError(rConnectedSocket, Format("Exception: %s", e.what())); }
		catch (...)		{ HandleSocketError(rConnectedSocket, "Exception: (unhandled exception)"); }
	}

	if (m_ListenSocket != -1)
	{
		ddcLogInfo(Format("closing listen socket on %s for %s", GetAddressStr().c_str(), m_CorpusName.c_str()));
		if (!this->Close(m_ListenSocket, true, 1))
			ddcLogError( Format("cannot close listen socket on %s for %s", GetAddressStr().c_str(), m_CorpusName.c_str()) );
	};

};

//--------------------------------------------------------------
#ifdef WIN32
	void  _cdecl ListenerThread( void* pParam )
#else
	static void* ListenerThread( void* pParam )
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
		ddcLogError("Service could invoke AfxSocketInit()");
    }
    catch (exception &e) {
	    ddcLogError(Format("ListenerThread[%s:%d]: Exception: %s", pHost->HostAddr().c_str(), pHost->Port(), e.what()) );
	    throw;
    }
    catch (...) {
	    ddcLogError( Format("ListenerThread[%s:%d]: Exception: (unhandled exception)", pHost->HostAddr().c_str(), pHost->Port()) );
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

//--------------------------------------------------------------
void CHost::CreateListener() 
{

	ddcLogInfo( Format ("Create Listener %s (%s)", m_CorpusName.c_str(), GetAddressStr().c_str()) );
	#ifdef WIN32
		_beginthread( ListenerThread, 0, (void*)this );
	#else
		pthread_t aThread;
		pthread_create(&aThread, NULL, ListenerThread, (void*)this);
	#endif

};

//--------------------------------------------------------------
string	CHost::GetAddressStr() const
{
	if (m_HostAddr.empty())
		return "(null)";
	else
		return Format("%s:%i", m_HostAddr.c_str(), m_Port);
};

//--------------------------------------------------------------
const string&	CHost::GetLocalPathOfIndex() const
{
	return m_LocalPath;
};

//--------------------------------------------------------------
void CHost::CopyAddressParametersFrom(const CHost& X)
{
	m_HostAddr = X.m_HostAddr;
	m_Port = X.m_Port;
	m_LocalPath = X.m_LocalPath;
	m_CorpusName = X.m_CorpusName;
};


//======================================================================
// global functions

//--------------------------------------------------------------
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
		CHost T;
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
