//-*- Mode: C++; c-basic-offset:4; -*-
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
#ifndef DDC_SERVER_H
#define DDC_SERVER_H

#include "../ConcordLib/ConcHolder.h"
#include "../common/string_socket.h"

#ifdef WIN32
	#include <process.h>  /* _beginthread, _endthread */
#else
#endif

//#define DEBUG_HIT_SORT
#ifdef DEBUG_HIT_SORT
# define HSDEBUG(s) m_LogFunction(s)
#else
# define HSDEBUG(s)
#endif


/** abstract base class class for DDC server nodes */
class CDDCServer : public CHost
{
public:
    //--------------------------------------------------------------
    // Administrivia

    /** moo: additional hit delimiter; overrides CConcHolder.m_AdditionalHitDelimiter , also used for branch server hit-tokenization; default is "\x01" */
    static const char *AdditionalHitDelimeter;

    /** moo: maximum number of subcorpora per branch server */
    static const size_t MaxSubhostsSize = 256;

    /** moo: timestamp of server initialization */
    time_t m_tStarted;
	
    /** moo: number of served requests */
    size_t m_nRequests;	

    /* moo: whether to log all requests received in ProcessSocketString() */
    bool m_bLogRequests;

public:
    //--------------------------------------------------------------
    // Constructors etc.

    /** default constructor */
    CDDCServer(bool bDoubleMessage=false, ProtocolDensityEnum pdProtocolDensity=pdWeakDensity)
	: CHost(bDoubleMessage, pdProtocolDensity), m_tStarted(0), m_nRequests(0), m_bLogRequests(false)
    {
	m_LogFunction = concord_daemon_log;
	m_tStarted = time(NULL);
    };

    /** default destructor */
    virtual ~CDDCServer()
    { StopAcceptingThread(); };

public:
    //--------------------------------------------------------------
    // string_socket API: socket handlers

    /** CHost API function maintains m_nRequests and calls appropriate handle__() methods */
    virtual string ProcessSocketString(const string& SocketInput, SOCKET rConnectedSocket);

public:
    //--------------------------------------------------------------
    // DDCServer API: request handlers: required

    /** request handler: get_first_hits: required (leaf) */
    virtual void handle__get_first_hits(string &Result, const char *Query, int TimeOut, int ResultLimit);

    /** request handler: get_hit_strings: required (leaf) */
    virtual void handle__get_hit_strings(string &Result, const char *ResultType, int StartHitNo, int ResultLimit);

    /** request handler: run_query: required (branch) */
    virtual void handle__run_query(string &Result, const char *CorpusName, const char *Query, const char *ResultType, int StartHitNo, int ResultLimit, int TimeOut);

    /** request handler: expand_terms: required (leaf|branch) */
    virtual void handle__expand_terms(string &Result, const string& pipeline, const string& terms, int timeout, const string &corpus);

    /** request handler: status: required (leaf|branch) */
    virtual void handle__status(string &Result, bool verbose=false);

    /** request handler: info: required (leaf|branch) */
    virtual void handle__info(string &Result, bool verbose=false);

    /** request handler: reload: required (leaf|branch) */
    virtual void handle__reload(string &Result);

    /** request handler: clear_cache: required (leaf|branch) */
    virtual void handle__clear_cache(string &Result);

public:
    //--------------------------------------------------------------
    // DDCServer API: request handlers: optional

    /** request handler: get_paradigm: optional (leaf|branch) */
    virtual void handle__get_paradigm(string &Result, const char *Word, int iLemmatizeOnly, int iLang);

    /** request handler: close_socket: optional (leaf|branch) */
    virtual void handle__close_socket(string &Result);

    /** request handler: close_socket: optional (leaf|branch) */
    virtual void handle__version(string &Result);

    /** request handler: vstatus: optional (leaf|branch): default wraps handle__status(Result,true) */
    virtual void handle__vstatus(string &Result);

    /** request handler: vinfo: optional (leaf|branch): default wraps handle__info(Result,true) */
    virtual void handle__vinfo(string &Result);

public:
    //--------------------------------------------------------------
    // DDCServer: utilities
    inline void method_not_implemented(const char *methodName)
    { throw CExpc(errRuntime, "DDCServer API method %s not implemented for object %s", methodName, typeid(*this).name()); };
};

#endif /* DDC_SERVER_H */
