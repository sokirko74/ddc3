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
// DDCTime : 1-second resolution clock
struct DDCTimeUnix
{
    //----------------------------------------------------------------------
    // Data
    /** time value (low-resolution: 1 second) */
    time_t m_t;

    //----------------------------------------------------------------------
    // constructors etc

    /** default constructor */
    DDCTimeUnix()
    {};

    /** default constructor given time_t */
    DDCTimeUnix(const time_t time_)
    { Set(time_); };

    /** default destructor */
    virtual ~DDCTimeUnix()
    {};

    /** constructor: current time */
    inline static DDCTimeUnix Now()
    {
	DDCTimeUnix t;
	t.Set();
	return t;
    };

    /** set this object to current time */
    inline void Set()
    { time(&m_t); };

    /** assignment operator (from time_t) */
    inline void Set(const time_t time_)
    { m_t = time_; };

    /** assignment operator (from DDCTimeUnix object) */
    inline void Set(const DDCTimeUnix& t)
    { Set(t.m_t); };


    //----------------------------------------------------------------------
    // API

    /** get low-resultion time_t time */
    inline time_t Time() const
    { return m_t; };

    /** get (low-resolution) calendar time; adapted from old RmlGetCurrentTime() */
    struct tm CalendarTime() const;

    /** get time and date strings in ISO-8601 format (YYYY-MM-DD HH:MM:SS) to char* buffers
     *  \li either of DateStr or TimeStr may be passed as NULL
     *  \param DateBuf output buffer of at least DDCDateBufferSize bytes, or NULL
     *  \param TimeBuf output buffer of at least DDCTimeBufferSize bytes, or NULL
     */
    virtual void DateTime(char* DateBuf, char* TimeBuf) const;

    /** get date string in ISO-8601 format (YYYY-MM-DD) */
    inline std::string DateStr() const
    {
	char DateBuf[DDCDateBufferSize];
	this->DateTime(DateBuf, NULL);
	return std::string(DateBuf);
    };

    /** get time string in 24-hour HH:MM:SS format */
    inline std::string TimeStr() const
    {
	char TimeBuf[DDCTimeBufferSize];
	this->DateTime(NULL,TimeBuf);
	return std::string(TimeBuf);
    };

    /** get elapsed time since \a t0, double resolution */
    double Elapsed(const DDCTimeUnix& t0) const;
};

//======================================================================
// DDCTimeHiRes : nanosecond-resolution clock
#ifdef HAVE_CLOCK_GETTIME
struct DDCTimeHiRes : public DDCTimeUnix
{
    //----------------------------------------------------------------------
    // Data
    /** time value (high-resolution: 1 nanosecond) */
    struct timespec m_ts;

    //----------------------------------------------------------------------
    // constructors etc

    /** default constructor */
    DDCTimeHiRes()
    {};

    /** default constructor given struct timespec */
    DDCTimeHiRes(const struct timespec &ts_)
    { Set(ts_); };
    
    /** default destructor */
    virtual ~DDCTimeHiRes()
    {};

    /** constructor: current time */
    inline static DDCTimeHiRes Now()
    {
	DDCTimeHiRes t;
	t.Set();
	return t;
    };
    
    /** set this object to current time */
    inline void Set()
    {
	clock_gettime(CLOCK_REALTIME, &m_ts);
	DDCTimeUnix::Set(m_ts.tv_sec);
    };

    /** assignment operator (from time_t) */
    inline void Set(const time_t time_)
    {
	DDCTimeUnix::Set(time_);
	m_ts.tv_sec  = time_;
	m_ts.tv_nsec = 0;
    };

    /** assignment operator (from struct timespec) */
    inline void Set(const struct timespec &ts_)
    {
	m_t  = ts_.tv_sec;
	m_ts = ts_;
    };

    /** assignment operator (from DDCTimeUnix object) */
    inline void Set(const DDCTimeUnix& t)
    { Set(t.m_t); };

    /** assignment operator */
    inline void Set(const DDCTimeHiRes& t)
    { *this = t; };

    //----------------------------------------------------------------------
    // API

    /* inherited: get low-resultion time_t time */
    //time_t Time() const;

    /* inherited: get (low-resolution) calendar time; adapted from old RmlGetCurrentTime() */
    //struct tm CalendarTime() const;

    /** get time and date strings in ISO-8601 format (YYYY-MM-DD HH:MM:SS) to char* buffers
     *  \li either of DateStr or TimeStr may be passed as NULL
     *  \param DateBuf output buffer of at least DDCDateBufferSize bytes, or NULL
     *  \param TimeBuf output buffer of at least DDCTimeBufferSize bytes, or NULL
     */
    virtual void DateTime(char* DateBuf, char* TimeBuf) const;

    /* inherited: get date string in ISO-8601 format (YYYY-MM-DD) */
    //inline std::string DateStr() const

    /** get time string in 24-hour HH:MM:SS format */
    // inline std::string TimeStr() const

    /** get elapsed time since \a t0, double resolution */
    double Elapsed(const DDCTimeHiRes& t0) const;
};

#else /* !defined(HAVE_CLOCK_GETTIME) */

/** compatibility typedef; used if clock_gettime() is unavailable */
typedef struct DDCTimeUnix DDCTimeHiRes;

#endif /* defined(HAVE_CLOCK_GETTIME) */

#ifdef DDC_USE_HIRES_CLOCK
/** typedef for default time class (either DDCTimeUnix or DDCTimeHiRes) */
typedef struct DDCTimeHiRes DDCTime;
#else
/** typedef for default time class (either DDCTimeUnix or DDCTimeHiRes) */
typedef struct DDCTimeUnix DDCTime;
#endif

//======================================================================
// Functions

	
#endif /* DDC_TIME_H */
