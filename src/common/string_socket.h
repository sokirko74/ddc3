//  Copyright 2011 by Bryan Jurish
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



#include "../common/utilit.h"

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
	neInternalError = 9
};


enum ProtocolDensityEnum {
	pdWeakDensity = 0,
	pdMediumDensity = 1,
	pdHeavyDensity = 2,
};

#define SOCKET int
#ifdef WIN32
	struct sockaddr_in;
#endif


class CHost  
{
protected:
	string					m_HostName;
	int					m_Port;
	SOCKET					m_ListenSocket;
	bool					m_bDoubleMessage;
	string					m_LocalPath;
	ProtocolDensityEnum			m_pdProtocolDensity;

	void AnswerByRequest (SOCKET rConnectedSocket, const struct sockaddr_in* client_addr, int TimeOut, bool& bCloseSocket );

protected:
	virtual string	ProcessSocketString(const string& S, SOCKET rConnectedSocket);

	//! \li logs and sends an error messaage to the client
	//! \li \c code should be nonzero to indicate a 'real' error
	//! \li implicitly closes \c clientSocket if !=-1
	virtual void	ClientError(int code=-1, const string& msg="", SOCKET clientSocket=-1);

public:
	
	string				m_CorpusName;
	void				(*m_LogFunction)(const string&);
	

	CHost(bool bDoubleMessage, ProtocolDensityEnum pdProtocolDensity);
	bool			ReadFromString (string S);
	void			CreateListener();
	void			CopyAddressParametersFrom(const CHost& X);
	void			StopAcceptingThread();
	void			RunThread();
	int			CreateAndConnectSocket(string& strError) const;
	string			GetAddressStr() const;
	const string&		GetLocalPathOfIndex() const;
};

extern string GetNetworkErrorString(const NetworkErrorsEnum& t);

/* moo / ddc-2.0.0: packet length arguments sent over sockets are ALWAYS 32-bit unsigned integers in little-endian order
 *  + big-endian ("network") order or fixed-width ASCII decimal would make more sense, but would break too much existing client code
 */
extern uint32_t size_to_lsb(uint32_t sz);
extern uint32_t lsb_to_size(uint32_t sz_lsb);

extern bool SendString (int client_fd, const char* Str, uint32_t StrLen, string& ErrorStr);
extern bool SendString (int client_fd, const std::string &str, string& ErrorStr);
extern NetworkErrorsEnum ReceiveString (int  client_fd, string& Result, int TimeOut);
extern bool SetSocketReceiveBuffer(int socket_fd, int BufferSize);
extern bool SetSocketSendBuffer(int socket_fd, int BufferSize);
extern bool SocketInitialize(bool bReadFromLocalFile);
extern bool SocketDeinitialize();
extern bool	LoadHosts (string Path, vector<CHost>& Hosts);
bool CloseSocket(int l_socket);

	
#endif
