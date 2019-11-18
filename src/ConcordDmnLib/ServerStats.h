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
#ifndef DDC_SERVER_STATS_H
#define DDC_SERVER_STATS_H

#include "../CommonLib/ddcTime.h"
#include <set>

//==============================================================================

/** default delays for CDDCServerStats exponential moving averages */
//#define DDC_SERVER_EMA_DELAYS 60,300,900  /* load-average style: 1,5,15 minutes*/
#define DDC_SERVER_EMA_DELAYS 300,900,3600  /* long window: 5,15,60 minutes */

/** generic class for tracking server statistics */
struct CDDCServerStats
{
    //--------------------------------------------------------------
    // Counters

    /** number of served requests */
    size_t m_nRequests; 

    /** number of serverd QUERY requests (run_query or get_first_hits only) */
    size_t m_nQueries;

    /** number of serverd EXXPAND requests (expand_terms only) */
    size_t m_nExpand;

    /** number of errors */
    size_t m_nErrors;

    /** number of slow requests */
    size_t m_nSlow;

    /** average query times over fixed interval (exponential moving averages at 5,15,60 minutes) */
    DDCTimeAvg m_qTimes;

    /** average expansion times over fixed interval (exponential moving averages at 5,15,60 minutes) */
    DDCTimeAvg m_xTimes;

    //--------------------------------------------------------------
    // Constructors etc.

    /** default constructor */
    CDDCServerStats()
        : m_nRequests(0), m_nQueries(0), m_nExpand(0), m_nErrors(0), m_nSlow(0), m_qTimes(DDC_SERVER_EMA_DELAYS), m_xTimes(DDC_SERVER_EMA_DELAYS)
    {};

    /** copy constructor */
    CDDCServerStats(const CDDCServerStats& x)
        : m_nRequests(x.m_nRequests), m_nQueries(x.m_nQueries), m_nExpand(x.m_nExpand), m_nErrors(x.m_nErrors), m_nSlow(x.m_nSlow), m_qTimes(x.m_qTimes), m_xTimes(x.m_xTimes)
    {};

    /** reset to zero */
    inline void clear()
    {
        m_nRequests = 0;
        m_nQueries = 0;
        m_nExpand = 0;
        m_nErrors = 0;
        m_nSlow = 0;
        m_qTimes.reset();
        m_xTimes.reset();
    };

    //--------------------------------------------------------------
    // Operators

    /** add counters to calling object */
    CDDCServerStats& operator+=(const CDDCServerStats& x);

    /** constructive addition */
    inline CDDCServerStats operator+(const CDDCServerStats &x) const
    { return CDDCServerStats(*this) += x; };
};


#endif /* DDC_SERVER_STATS_H */

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
