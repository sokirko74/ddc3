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
    //  we should  thread safe  variants
    struct tm today;
    localtime_r( &ltime, &today );
    return today;
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


//======================================================================
// date/time helpers

string timestampUTC(time_t timeval)
{
    char buf[32];
    struct tm time_tm;
    gmtime_r(&timeval, &time_tm);
    strftime(buf, 32, "%FT%TZ", &time_tm);                  //--- ISO 8601 timestamp, UTC
    return string(buf);
}

uint32_t date2int(signed int y, unsigned int m, unsigned int d)
{
    return
        (((y&0xffff)<<16) | ((m&0xff)<<8) | ((d&0xff)<<0)); //-- ddc <= v2.0.8 compat (mostly, modulo signed years)
    //(((y&0xfffffe00)<<9) | ((m&0x0f)<<5) | ((d&0x1f)<<0));  //-- 32bit safe, decodable
    //($y*10000 + $m*100 + $d); //-- decimal intuitive (tough to decode)
}

void int2date(uint32_t i, signed int *y, unsigned int *m, unsigned int *d)
{
    //-- ddc <= v2.0.8 compat for years in range [0..32767] + new support for years [-32768..-1] as of ddc v2.2.4
    if (y) *y = ((int16_t)((i>>16)&0xffff));
    if (m) *m = ((uint8_t)((i>> 8)&0xff));
    if (d) *d = ((uint8_t)((i>> 0)&0xff));
}
