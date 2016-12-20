//-*- Mode: C++; c-basic-offset:4;-*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2016 by Bryan Jurish
//
//  This file is part of DDC
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
#ifndef DDC_TIME_H
#define DDC_TIME_H

#include "../common/ddcConfig.h"
#include <time.h>
#include <string>

//======================================================================
// constants

/** number of bytes to allocate for date-string buffers */
extern const size_t DDCDateBufferSize;

/** number of bytes to allocate for time-string buffers */
extern const size_t DDCTimeBufferSize;

//======================================================================
struct DDCTime
{
    //----------------------------------------------------------------------
    // Data
#if DDC_USE_HIRES_CLOCK
    /** time value (high-resolution: 1 nanosecond) */
    struct timespec m_ts;
#else
    /** time value (low-resolution: 1 second) */
    time_t m_t;
#endif

    //----------------------------------------------------------------------
    // constructors etc

    /** default constructor */
    DDCTime()
    {};

    /** default destructor */
    ~DDCTime()
    {};

    /** constructor: current time */
    inline static DDCTime Now()
    {
	DDCTime t;
	t.Set();
	return t;
    };

    /** set this object to current time */
    inline void Set()
    {
#if DDC_USE_HIRES_CLOCK
	clock_gettime(CLOCK_REALTIME, &m_ts);
#else
	time(&m_t);	
#endif
    };

    /** assignment operator */
    inline void Set(const DDCTime& t)
    { *this = t; };

    //----------------------------------------------------------------------
    // API

    /** get low-resultion time_t time */
    inline time_t Time() const
    {
#if DDC_USE_HIRES_CLOCK
	return m_ts.tv_sec;
#else
	return m_t;
#endif
    };

    /** get (low-resolution) calendar time; adapted from old RmlGetCurrentTime() */
    struct tm CalendarTime() const;

    /** get time and date strings in ISO-8601 format (YYYY-MM-DD HH:MM:SS) to char* buffers
     *  \li either of DateStr or TimeStr may be passed as NULL
     *  \param DateBuf output buffer of at least DDCDateBufferSize bytes, or NULL
     *  \param TimeBuf output buffer of at least DDCTimeBufferSize bytes, or NULL
     */
    void DateTime(char* DateBuf, char* TimeBuf) const;

    /** get date string in ISO-8601 format (YYYY-MM-DD) */
    inline std::string DateStr() const
    {
	char DateBuf[DDCDateBufferSize];
	DateTime(DateBuf, NULL);
	return std::string(DateBuf);
    };

    /** get time string in 24-hour HH:MM:SS format */
    std::string TimeStr() const
    {
	char TimeBuf[DDCTimeBufferSize];
	DateTime(NULL,TimeBuf);
	return std::string(TimeBuf);
    };

    /** get elapsed time since \a t0, double resolution */
    double Elapsed(const DDCTime& t0) const;
};


//======================================================================
// Functions

	
#endif /* DDC_TIME_H */
