//-*- Mode: C++ -*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2019 by Bryan Jurish
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
#include "ddcTime.h"
#include "ddcString.h"
#include <string.h>
#include <stdio.h>
#include <cstdarg>
#include <math.h>

using namespace std;

//======================================================================
// constants

const size_t DDCDateBufferSize = 16;

#if HAVE_CLOCK_GETTIME
const size_t DDCTimeBufferSize = 32;
#else
const size_t DDCTimeBufferSize = 16;
#endif


//======================================================================
// DDCTimeUnix

//----------------------------------------------------------------------
struct tm DDCTimeUnix::CalendarTime() const
{
    time_t ltime = Time();
#ifdef	WIN32
    struct tm *today;
    today = localtime( &ltime );
    return *today;
#else
    //  we should  thread safe  variants
    struct tm today;
    localtime_r( &ltime, &today );
    return today;
#endif
}

//----------------------------------------------------------------------
void DDCTimeUnix::DateTime(char* DateBuf, char* TimeBuf) const
{
    struct tm tmTime = this->CalendarTime();

    if (DateBuf != NULL)
	strftime(DateBuf, DDCDateBufferSize, "%F", &tmTime);

    if (TimeBuf != NULL)
	strftime(TimeBuf, DDCTimeBufferSize, "%H:%M:%S", &tmTime);
}

//----------------------------------------------------------------------
double DDCTimeUnix::Elapsed(const DDCTimeUnix& t0) const
{
    return difftime(m_t, t0.m_t);
}


//======================================================================
// DDCTimeHiRes

#ifdef HAVE_CLOCK_GETTIME

//----------------------------------------------------------------------
void DDCTimeHiRes::DateTime(char* DateBuf, char* TimeBuf) const
{
    DDCTimeUnix::DateTime(DateBuf,TimeBuf);
    if (TimeBuf != NULL)
	snprintf(&TimeBuf[strlen(TimeBuf)], DDCTimeBufferSize, ".%09lu", m_ts.tv_nsec);
}

//----------------------------------------------------------------------
double DDCTimeHiRes::Elapsed(const DDCTimeHiRes& t0) const
{
    /* Perform the carry for the later subtraction by updating Y. */
    time_t  t0_tv_sec   = t0.m_ts.tv_sec;
    long    t0_tv_nsec  = t0.m_ts.tv_nsec;
    if (m_ts.tv_nsec < t0_tv_nsec) {
	long nsec = (t0_tv_nsec - m_ts.tv_nsec) / 1000000000 + 1;
	t0_tv_nsec -= 1000000000 * nsec;
	t0_tv_sec += nsec;
    }
    if (m_ts.tv_nsec - t0_tv_nsec > 1000000000) {
	long nsec = (m_ts.tv_nsec - t0_tv_nsec) / 1000000000;
	t0_tv_nsec += 1000000000 * nsec;
	t0_tv_sec -= nsec;
    }

    /* Compute the time remaining to wait. 'tv_nsec' is certainly positive. */
    double elapsed = (m_ts.tv_sec - t0_tv_sec) + ((double)(m_ts.tv_nsec - t0_tv_nsec) / (double)1000000000);
    if (m_ts.tv_sec < t0_tv_sec)
	elapsed *= -1;

    return elapsed;
}

#endif /* defined(HAVE_CLOCK_GETTIME) */

//======================================================================
// DDCTimeAvg

//----------------------------------------------------------------------
void DDCTimeAvg::reset(ValueT val)
{
    for (MapT::iterator mapi=m_map.begin(); mapi != m_map.end(); ++mapi)
	mapi->second = val;
    m_total = val;
    m_n     = (val==0 ? 0 : 1);
}

//----------------------------------------------------------------------
void DDCTimeAvg::SetDelays(const std::vector<DelayT>& delays, ValueT val)
{
    m_map.clear();
    for (std::vector<DelayT>::const_iterator ki=delays.begin(); ki != delays.end(); ++ki)
	m_map[*ki] = val;
}

//----------------------------------------------------------------------
void DDCTimeAvg::SetDelays(DelayT delay1, DelayT delay2, DelayT delay3, ValueT val)
{
    m_map.clear();
    if (delay1 > 0) m_map[delay1] = val;
    if (delay2 > 0) m_map[delay2] = val;
    if (delay3 > 0) m_map[delay3] = val;
}

//----------------------------------------------------------------------
DDCTimeAvg::MapT& DDCTimeAvg::Append(double sample, const TimeT& when, size_t n)
{
    double tdiff = when.Elapsed(m_t);
    for (MapT::iterator mapi=m_map.begin(); mapi != m_map.end(); ++mapi) {
	double alpha  = (tdiff <= 0 ? 0.5 : exp(-tdiff / (double)(mapi->first)));
	mapi->second  = (1-alpha)*sample + alpha*mapi->second;
    }
    m_t.Set(when);

    
    while ((SIZE_MAX - n) < m_n) {
	//-- avoid counter overflow: reduce by half
	m_total /= 2;
	m_n     /= 2;
    }
    m_total += sample;
    m_n     += n;

    return m_map;
}

//----------------------------------------------------------------------
string DDCTimeAvg::toJsonArray() const
{
    string buf("[");
    for (MapT::const_iterator mapi=m_map.begin(); mapi != m_map.end(); ++mapi) {
	if (mapi != m_map.begin()) buf.push_back(',');
	buf += Format("%g",mapi->second);
    }
    buf.push_back(']');
    return buf;
}

//----------------------------------------------------------------------
string DDCTimeAvg::toJsonMap() const
{
    string buf("{");
    for (MapT::const_iterator mapi=m_map.begin(); mapi != m_map.end(); ++mapi) {
	if (mapi != m_map.begin()) buf.push_back(',');
	buf += Format("\"%zd\":%g",mapi->first,mapi->second);
    }
    buf.push_back('}');
    return buf;
}

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-default-style: "linux"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
