//-*- Mode: C++; c-basic-offset:4; -*-
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
#ifndef DDC_SERVER_OPTIONS_H
#define DDC_SERVER_OPTIONS_H

#include "../CommonLib/string_socket.h"
#include "../CommonLib/utilit.h"

//==============================================================================
/** class for storing common server options (ddc_server.rc) */
class CDDCServerOptions
{
public:
    //--------------------------------------------------------------
    // logging

    /** upper-bound in seconds for "slow" queries (default=10); see CDDCServer::m_SlowQueryTimeout */
    double m_SlowQueryTimeout;
   
    //--------------------------------------------------------------
    // client threads

    /** number of client-thread workers for thread pool (default=0: serial mode) */
    size_t m_nWorkers;

    /** maximum number of pending client connections the thread-pool queue (min=1: use tcp queueing only; default=DDC_DEFAULT_THREAD_QUEUE_SIZE) */
    size_t m_ThreadQueueSize;

public:
    //--------------------------------------------------------------
    // Constructors etc.

    /** default constructor */
    CDDCServerOptions();

public:
    //--------------------------------------------------------------
    // I/O

    /** load server-options file file RCFILE */
    void LoadFile(const string& Filename);

    /** set server-options from a monolithic string */
    void LoadString(const string& Options, const string& srcName="String");

    /** set server-options from a c++ vector */
    void LoadLines(const vector<string>& Lines, const string& srcName="Lines");

    /** set a single option value
     *  \param Option name of the option to set
     *  \param Value option value
     *  \param srcName name of source (for complaints)
     *  \param LineNo source line number
     *  \returns true on success, false for unknown options
     */
    bool Set(const string& Option, const string& Value="", const string& srcName="Option");

    /** convert to a string representation */
    string toString() const;
};

#endif /* DDC_SERVER_OPTIONS_H */
