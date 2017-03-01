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
    size_t m_Window;

    /** guts: underlying set of query times */
    std::set<CDDCQueryTime> m_tset;

    /** optimization: current number of entries in m_tset */
    size_t m_size;

    /** optimization: current total elapsed time over all entries in m_tset */
    double m_etotal;

    //----------------------------------------------------------------------
    // Constructors etc.

    /** default constructor given optional window size (default=10 minutes) */
    CDDCQueryTimeAvg(size_t window=600)
	: m_Window(window), m_size(0), m_etotal(0)
    {};

    /** clear the buffer */
    inline void clear()
    {
	m_tset.clear();
	m_size = 0;
	m_etotal = 0;
    };

    //----------------------------------------------------------------------
    // API

    /** get current set size */
    inline size_t size() const
    { return m_size; };

    /** get current average query time */
    inline double tAverage() const
    { return m_size==0 ? 0 : (m_etotal / m_size); };

    /** append statistics for a single query */
    inline void Append(const CDDCQueryTime &qt)
    {
	m_tset.insert(m_tset.end(), qt);
	++m_size;
	m_etotal += qt.m_elapsed;
    };
    
    /** append statistics for a single query with current end time */
    inline void Append(double elapsed)
    { Append(CDDCQueryTime(elapsed)); };

    /** append all times from a CDDCQueryTimeAvg object */
    void Append(const CDDCQueryTimeAvg &qta)
    {
	m_tset.insert(qta.m_tset.begin(), qta.m_tset.end());
	m_size   += qta.m_size;
	m_etotal += qta.m_etotal;
    };

    /** append time for a followup query to the most recent entry, or add a new entry if the set is empty */
    void AppendCurrent(double elapsed);

    /** operator+=() wraps Append() and Scrub() */
    inline CDDCQueryTimeAvg& operator+=(const CDDCQueryTimeAvg& x)
    {
	Append(x);
	Scrub();
	return *this;
    };

    /** remove stale results (older than current time minus window size) from m_tset */
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

    /** average query time over fixed interval */
    CDDCQueryTimeAvg m_qTimes;

    //--------------------------------------------------------------
    // Constructors etc.

    /** default constructor */
    CDDCServerStats(size_t qTimeWindow=600)
	: m_nRequests(0), m_nQueries(0), m_nErrors(0), m_nSlow(0), m_qTimes(qTimeWindow)
    {};

    /** copy constructor */
    CDDCServerStats(const CDDCServerStats& x)
	: m_nRequests(x.m_nRequests), m_nQueries(x.m_nQueries), m_nErrors(x.m_nErrors), m_nSlow(x.m_nSlow), m_qTimes(x.m_qTimes)
    {};

    /** reset to zero */
    inline void clear()
    {
	m_nRequests = 0;
	m_nQueries = 0;
	m_nErrors = 0;
	m_nSlow = 0;
	m_qTimes.clear();
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
