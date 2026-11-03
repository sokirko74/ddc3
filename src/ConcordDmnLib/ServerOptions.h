//-*- Mode: C++ -*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2018 by Bryan Jurish
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
#include "../CommonLib/ddcVersion.h"
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

    /** default log level (clobbers global ddcLogLevel if anything other than ddcLLUnknown) */
    DDCLogLevel m_LogLevel;

    /** upper-bound in seconds for "slow" queries (default=10); see CDDCServer::m_SlowQueryTimeout */
    double m_SlowQueryTimeout;

    /* OBSOLETE time window for mocing average query time (seconds, default=600: 10 minutes) */
    //size_t m_StatsWindow;
   
    //--------------------------------------------------------------
    // client threads & parallelization

    /** number of client-thread workers for thread pool (default=0: serial mode) */
    size_t m_nWorkers;

    /** maximum number of pending client connections the thread-pool queue (min=1: use tcp queueing only; default=DDC_DEFAULT_THREAD_QUEUE_SIZE) */
    size_t m_ThreadQueueSize;

    /** should branch server send "get_hit_strings" requests in parallel? (default=false) */
    bool m_bHitStringsParallel;

    //--------------------------------------------------------------
    // navigation cache

    /** size of navigation hint cache (branch servers only) */
    size_t m_NavCacheSize;

    /** minimum logical offset increment for navigation hint cache (branch servers only) */
    size_t m_NavCacheStep;

    //--------------------------------------------------------------
    // compatibility

    /** server compatibility mode */
    DDCVersionT m_VersionCompat;

    mode_t m_UnixSocketPerms;

public:
    //--------------------------------------------------------------
    // Constructors etc.

    /** default constructor */
    CDDCServerOptions();

public:
    //--------------------------------------------------------------
    // I/O

    /** load server-options file file RCFILE */
    void LoadFile(const std::string& Filename);

    /** set server-options from a monolithic string */
    void LoadString(const std::string& Options, const std::string& srcName="String");

    /** set server-options from a c++ vector */
    void LoadLines(const std::vector<std::string>& Lines, const std::string& srcName="Lines");

    /** set a single option value
     *  \param Option name of the option to set
     *  \param Value option value
     *  \param srcName name of source (for complaints)
     *  \param LineNo source line number
     *  \returns true on success, false for unknown options
     */
    bool Set(const std::string& Option, const std::string& Value="", const std::string& srcName="Option");

    /** convert to a string representation */
    std::string toString() const;
};

#endif /* DDC_SERVER_OPTIONS_H */

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
