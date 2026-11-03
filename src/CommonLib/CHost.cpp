//-*- Mode: C++ -*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2020 by Bryan Jurish
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
#include "util_classes.h"
#include "DDCInternalError.h"
#include <string.h>
#include <errno.h>

//======================================================================
// CHost

//--------------------------------------------------------------
CHost::CHost()
    : m_SockAddr()
{
    m_bExpectMore = false;
    m_bRespond   = true;
    m_bLogFinish = false;
    m_ListenSocket = -1;
    m_maxReceiveBytes = 0;
    m_bListen = false;
    m_UnixSocketPerms = 0;
};

//--------------------------------------------------------------
CHost::~CHost()
{
    if (m_bListen) {
        CloseListenSocket();
    }
}

//--------------------------------------------------------------
bool CHost::CheckValidAddr() const
{
    return m_SockAddr.IsValid();
}

//--------------------------------------------------------------
bool CHost::ReadFromString (string S)
{
    ddcStringTokenizer tok(S.c_str(), " \t\r\n");
    int ItemNo = 0;
    m_SockAddr.Clear();
    while (tok()) 
    {
        string Item = tok.val();
        if (ItemNo == 0) {
            m_CorpusName = Item;
            InitShortName();
        }
        else if (ItemNo == 1) {
            m_SockAddr.ParseSocketAddr(Item, false);
        }
        else if (ItemNo == 2) {
            m_SockAddr.m_Port = atoi(Item.c_str());
            m_LocalPath = tok.get_rest();
            Trim (m_LocalPath);
            break;
        }
        ItemNo++;
    };

    return CheckValidAddr();
};

//--------------------------------------------------------------
bool CHost::InitEmbedded (const CHost& host)
{
    CopyAddressParametersFrom(host);
    if (m_SockAddr.m_Type==stINET && m_SockAddr.m_Addr == "0.0.0.0") {
        m_SockAddr.m_Addr = "127.0.0.1"; //-- connect to localhost for embedded branch servers binding all inet interfaces
    }
    m_LocalPath  = "";
    return CheckValidAddr();
};

int CHost::CreateSocket(bool bBind, string& strError) const
{
    if (m_SockAddr.m_Type==stUNIX) {
        if (bBind && FileExists(m_SockAddr.m_Addr.c_str()))
            ddcLogWarn(Format("Warning: unix socket path %s already exists for %s", m_SockAddr.m_Addr.c_str(), m_CorpusName.c_str()));
        return create_unix_socket(m_SockAddr.m_Addr.c_str(), bBind, m_UnixSocketPerms, strError);
    }
    else {
        return  create_inet_socket(m_SockAddr.m_Addr.c_str(), m_SockAddr.m_Port, bBind, strError);
    }
}

//--------------------------------------------------------------
int     CHost::CreateAndConnectSocket(string& strError) const
{
    return CreateSocket(false, strError);
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
    catch (CExpc& e)        { ErrorStr = Format("Exception[%d]: %s", ddcExpcCode(e), e.what()); }
    catch (exception &e)    { ErrorStr = Format("Exception: %s", e.what()); }
    catch (...)             { ErrorStr = "Exception: (unhandled exception)"; }

    if (!ErrorStr.empty())
        this->HandleSocketError(rConnectedSocket, ErrorStr, "CHost::HandleClientConnection()");
}

void CHost::StopListening () {
    m_bListen = false;
    m_ListenSocket = -1;
};

//--------------------------------------------------------------
bool    CHost::CloseListenSocket(int timeout)
{
    m_bListen = false;
    if (m_ListenSocket == -1)
        return true;
    else
    {
        // I (=AS?) have tried to send a special closing message to m_ListenSocket,
        // which should have a special processing in AnswerByRequest,
        // but I failed to close a socket correctly, so I would like to do the following:
        // (even knowing that m_ListenSocket was created in a different thread)
        //
        // moo: set SO_LINGER timeout=0: close immediately
        bool result = this->Close(m_ListenSocket, true, timeout);
        if (!result) {
            ddcLogError( Format("cannot close listen socket on %s for %s", GetAddressStr().c_str(), m_CorpusName.c_str()) );
        }
        if (m_SockAddr.m_Type==stUNIX) {
            if (unlink(m_SockAddr.m_Addr.c_str()) == -1) {
                ddcLogWarn(Format("cannot remove unix domain socket %s for %s", m_SockAddr.m_Addr.c_str(), m_CorpusName.c_str()));
            }
        }
        assert (m_ListenSocket == -1);
        return result;
    };
};

//--------------------------------------------------------------
string  CHost::ProcessSocketString(const string& S, SOCKET& rConnectedSocket) 
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
    return CloseSocketRef(rConnectedSocket, linger, timeout);
}

//--------------------------------------------------------------
void   CHost::RunThread()
{
    string ErrorStr;
    m_ListenSocket = CreateSocket(true, ErrorStr);
    if (m_ListenSocket == -1)
    {
        ddcLogError("CHost::RunThread(): ERROR: "+ErrorStr);
        StopListening();
        return;
    };

    // set maximal length of pending queue to 5 
    int listen_val = listen(m_ListenSocket, 5);
    if (listen_val == -1) {
        ddcLogError(Format("CHost::RunThread(): ERROR: listen() failed: %s", StrError(errno)));
        CloseListenSocket();
    }

    ddcLogInfo( Format("CHost on %s waiting for accept", GetAddressStr().c_str()) );
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
        catch (CExpc& e)        { HandleSocketError(rConnectedSocket, Format("Exception[%d]: %s", ddcExpcCode(e), e.what())); }
        catch (exception &e)    { HandleSocketError(rConnectedSocket, Format("Exception: %s", e.what())); }
        catch (...)             { HandleSocketError(rConnectedSocket, "Exception: (unhandled exception)"); }
    }

    if (m_ListenSocket != -1)
    {
        ddcLogInfo(Format("closing listen socket on %s for %s", GetAddressStr().c_str(), m_CorpusName.c_str()));
        if (!CloseListenSocket(1)) {
            ddcLogError( Format("cannot close listen socket on %s for %s", GetAddressStr().c_str(), m_CorpusName.c_str()) );
        }
    };

};

//--------------------------------------------------------------
static void* ListenerThread( void* pParam )
{
    CHost* pHost = (CHost* )pParam;
    try {
        ddc_thread_init(pHost->m_CorpusName.c_str());


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
        

    return NULL;
};

//--------------------------------------------------------------
void CHost::CreateListener() 
{
    m_bListen = true;
    ddcLogInfo( Format ("Create Listener %s (%s)", m_CorpusName.c_str(), GetAddressStr().c_str()) );
    pthread_t aThread;
    pthread_create(&aThread, NULL, ListenerThread, (void*)this);

};

//--------------------------------------------------------------
string  CHost::GetAddressStr() const
{
    return m_SockAddr.toString();
};

//--------------------------------------------------------------
const string&   CHost::GetLocalPathOfIndex() const
{
    return m_LocalPath;
};

//--------------------------------------------------------------
void CHost::InitShortName()
{
    if (m_CorpusName.find("server:")==0) {
        m_ShortName = m_CorpusName.substr(7);
    } else {
        m_ShortName = m_CorpusName;
    }
};

//--------------------------------------------------------------
void CHost::CopyAddressParametersFrom(const CHost& X)
{
    m_SockAddr = X.m_SockAddr;
    m_LocalPath = X.m_LocalPath;
    m_CorpusName = X.m_CorpusName;
    m_ShortName = X.m_ShortName;
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

        //-- ignore comments and blank lines
        if (Q.empty()) continue;
        if (Q.find("//")==0) continue;
        if (Q.find("#")==0)  continue;
        CHost T;
        if (!T.ReadFromString(Q)) 
        {
            fprintf (stderr, "LoadHosts ERROR: could not parse file %s line number %i: %s\n", Path.c_str(), LineNo, buffer);
            fclose(fp);
            return false;
        };
                
        Hosts.push_back(T);
    };
        
    fclose(fp);

    return true;
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
