//-*- Mode: C++ -*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2016 by Bryan Jurish
//
//  This file is part of DDC (fomerly defined in string_socket.h)
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
#ifndef _DDC_CHOST_H
#define _DDC_CHOST_H

#include "utilit.h"
#include "string_socket.h"

//======================================================================
/** \brief generic socket host wrapper class
 *  \detail irritatingly also used for client connections
 */
class CHost  
{
protected:
        string                                  m_HostAddr;     ///< string representation of address to bind or connect to
        int                                             m_Port;
        string                                  m_SocketPath; // for unix domain socket
        SOCKET                                  m_ListenSocket;
        bool                                    m_bExpectMore;  ///< moo: whether to expect more requests from current client
        bool                                    m_bRespond;     ///< moo: whether current request has a real (possibly empty) response
        bool                                    m_bLogFinish;   ///< moo: whether to log connection completion
        string                                  m_LocalPath;    ///< path to local project-file (ddc_local_corpora.cfg) or label of parent branch node (ddc_server.cfg)
        uint32_t                                m_maxReceiveBytes; ///< maximum receivable packet length (default=0: no limit)

        int                     CreateSocket(bool bBind, string& strError) const;
        bool                    IsUnixDomainSocket() const;
        bool                    CheckValid() const;
public:
        //ProtocolDensityEnum           m_pdProtocolDensity;
        string                          m_CorpusName;
        
        CHost();
        bool                    ReadFromString (string S);

        /** top-level call to start accept-process-respond loop; run in main thread */
        virtual void            CreateListener();
        void                    CopyAddressParametersFrom(const CHost& X);
        void                    StopAcceptingThread();

        /** main accept - process - respond loop; called in its own thread */
        virtual void            RunThread();
        
        int                     CreateAndConnectSocket(string& strError) const;
        string                  GetAddressStr() const;
        const string&           GetLocalPathOfIndex() const;

        inline const string&    HostAddr() const { return m_HostAddr; };
        inline const int        Port() const { return m_Port; };

        /** initialize static host parameters, in lieu of reading from file */
        bool InitEmbedded(const CHost&);

public:
        /** read request string from a connected socket; handles low-level errors
         * \param rConnectedSocket socket from which to read
         * \param TimeOut timeout in seconds for low-level read operations
         * \param Request holds request on return
         * \returns true on success
         */
        bool GetRequest   (SOCKET& rConnectedSocket, int TimeOut, string &Request);

        /** send a response string to a connected socket; handles low-level errors
         * \li closes socket unless \a m_bExpectMore is true
         * \param rConnectedSocket socket to which response is to be sent
         * \param Result response string to be sent (without size prefix)
         */
        void SendResponse (SOCKET& rConnectedSocket, const string& Result);

        /** handle a socket-level error for a client connection, no response sent to client */
        void HandleSocketError(SOCKET& rConnectedSocket, const string& ErrorStr="ERROR", const string& Where="CHost::HandleSocketError()");

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
         * \li default implementation just wraps CloseSocket(rConnectedSocket,linger,timeout)
         * \returns true on success, false otherwise
         */
        virtual bool Close(SOCKET& rConnectedSocket, bool linger=false, int timeout=5);

        /** guts for request handling; override in subclasses */
        virtual string  ProcessSocketString(const string& S, SOCKET& rConnectedSocket);

        /** close a client connection in case of error, for use by derived classes
         * \li logs and sends an error messaage to the client
         * \li \c code should be nonzero to indicate a 'real' error
         * \li implicitly closes \c clientSocket if !=-1 (default)
         */
        virtual void    ClientError(int code=-1, const string& msg="");
        virtual void    ClientError(int code,    const string& msg, SOCKET& clientSocket);

};

//======================================================================
// load a DDC server config file
extern bool LoadHosts (string Path, vector<CHost>& Hosts);

        
#endif /* DDC_CHOST_H */

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-default-style: "linux"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
