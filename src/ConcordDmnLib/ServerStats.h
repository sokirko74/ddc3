//-*- Mode: C++; c-basic-offset:4; -*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2017 by Bryan Jurish
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
/** generic struct representing query timing information (for average query time stats) */
struct CDDCQueryTime
{
    //----------------------------------------------------------------------
    // data

    /** absolute UNIX time at which query completion was registered */
    time_t m_t;

    /** total elapsed time while processing query (high-resolution if available) */
    double m_elapsed;

    //----------------------------------------------------------------------
    // Constructors etc.

    /** default constructor, given optional elapsed time */
    CDDCQueryTime(double elapsed=0)
    {
	time(&m_t);
	m_elapsed = elapsed;
    };
    
    /** constructor, given end-time and optional elapsed time */
    CDDCQueryTime(time_t t, double elapsed=0)
	: m_t(t), m_elapsed(elapsed)
    {};

    //----------------------------------------------------------------------
    // Operators

    /** less-than operator */
    inline bool operator<(const CDDCQueryTime &qt1) const
    {
	return (m_t < qt1.m_t ? true
		: (m_t==qt1.m_t ? (m_elapsed > qt1.m_elapsed)
		   : false));
    };

};

//==============================================================================
/** generic struct for tracking average query times over a fixed length time window */
struct CDDCQueryTimeAvg
{
    /** time interval over which to average (seconds) */
    time_t m_Window;

    /** guts: underlying set of query times */
    std::set<CDDCQueryTime> m_tset;

    /** running average: current number of queries in m_tset */
    size_t m_n;

    /** running average: current running average over m_tset */
    double m_etotal;

    //----------------------------------------------------------------------
    // Constructors etc.

    /** default constructor given optional window size (default=5minutes) */
    CDDCQueryTimeAvg(time_t window=300)
	: m_Window(window)
    { clear(); };

    /** clear the buffer */
    void clear()
    {
	m_tset.clear();
	m_n = 0;
	m_etotal = 0;
    };

    //----------------------------------------------------------------------
    // API

    /** get current average query time */
    inline double tAverage() const
    { return m_etotal / m_n; };

    /** append statistics for a single query */
    inline void Append(const CDDCQueryTime &qt)
    {
	m_tset.insert(m_tset.end(), qt);
	++m_n;
	m_etotal += qt.m_elapsed;
    };

    /** append statistics for a single query with current end time */
    inline void Append(double elapsed)
    { Append(CDDCQueryTime(elapsed)); };

    /** append all times from a CDDCQueryTimeAvg object */
    inline void Append(const CDDCQueryTimeAvg &qta)
    {
	m_tset.insert(qta.m_tset.begin(), qta.m_tset.end());
	m_n      += qta.m_n;
	m_etotal += qta.m_etotal;
    };

    /** scrub stale results (older than window) from m_tset */
    void Scrub(void);

};


//==============================================================================
/** generic class for tracking server statistics */
struct CDDCServerStats
{
    //--------------------------------------------------------------
    // Counters

    /** number of served requests */
    size_t m_nRequests;	

    /** number of serverd QUERY requests (run_query or get_first_hits only) */
    size_t m_nQueries;

    /** number of errors */
    size_t m_nErrors;

    /** number of slow requests */
    size_t m_nSlow;

    //--------------------------------------------------------------
    // Constructors etc.

    /** default constructor */
    CDDCServerStats()
	: m_nRequests(0), m_nQueries(0), m_nErrors(0), m_nSlow(0)
    {};

    /** copy constructor */
    CDDCServerStats(const CDDCServerStats& x)
	: m_nRequests(x.m_nRequests), m_nQueries(x.m_nQueries), m_nErrors(x.m_nErrors), m_nSlow(x.m_nSlow)
    {};

    /** reset to zero */
    inline void clear()
    {
	m_nRequests = 0;
	m_nQueries = 0;
	m_nErrors = 0;
	m_nSlow = 0;
    };

    //--------------------------------------------------------------
    // Operators

    /** add counters to calling object */
    CDDCServerStats& operator+=(const CDDCServerStats& x);

    /** subtract counters from calling object */
    CDDCServerStats& operator-=(const CDDCServerStats& x);

    /** constructive addition */
    inline CDDCServerStats operator+(const CDDCServerStats &x) const
    { return CDDCServerStats(*this) += x; };

    /** constructive subtraction */
    inline CDDCServerStats operator-(const CDDCServerStats &x) const
    { return CDDCServerStats(*this) -= x; };
};


#endif /* DDC_SERVER_STATS_H */
