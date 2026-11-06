#ifndef DDC_TIME_H
#define DDC_TIME_H

#include "CommonLib/ddcConfig.h"
#include <time.h>
#include <cstdint>
#include <string>
#include <map>
#include <vector>

//======================================================================
// constants

/* number of bytes to allocate for date-string buffers */
extern const size_t DDCDateBufferSize;

/* number of bytes to allocate for time-string buffers */
extern const size_t DDCTimeBufferSize;

//======================================================================
// DDCTime : 1-second resolution clock
struct DDCTimeUnix
{
    //----------------------------------------------------------------------
    // Data
    /* time value (low-resolution: 1 second) */
    time_t m_t;

    //----------------------------------------------------------------------
    // constructors etc

    /* default constructor */
    DDCTimeUnix()
    {};

    /* default constructor given time_t */
    DDCTimeUnix(const time_t time_)
    { Set(time_); };

    /* copy constructor */
    DDCTimeUnix(const DDCTimeUnix& X)
        : m_t(X.m_t)
    {};

    /* default destructor */
    virtual ~DDCTimeUnix()
    {};

    /* constructor: current time */
    inline static DDCTimeUnix Now()
    {
        DDCTimeUnix t;
        t.Set();
        return t;
    };

    /* set this object to current time */
    inline void Set()
    { time(&m_t); };

    /* assignment operator (from time_t) */
    inline void Set(const time_t time_)
    { m_t = time_; };

    /* assignment operator (from DDCTimeUnix object) */
    inline void Set(const DDCTimeUnix& t)
    { Set(t.m_t); };

    //----------------------------------------------------------------------
    // API

    /* get low-resultion time_t time */
    inline time_t Time() const
    { return m_t; };

    /* get (low-resolution) calendar time; adapted from old RmlGetCurrentTime() */
    struct tm CalendarTime() const;

    /* get time and date strings in ISO-8601 format (YYYY-MM-DD HH:MM:SS) to char* buffers
     *  - either of DateStr or TimeStr may be passed as NULL
     *  DateBuf: output buffer of at least DDCDateBufferSize bytes, or NULL
     *  TimeBuf: output buffer of at least DDCTimeBufferSize bytes, or NULL
     */
    virtual void DateTime(char* DateBuf, char* TimeBuf) const;

    /* get date string in ISO-8601 format (YYYY-MM-DD) */
    inline std::string DateStr() const
    {
        char DateBuf[DDCDateBufferSize];
        this->DateTime(DateBuf, NULL);
        return std::string(DateBuf);
    };

    /* get time string in 24-hour HH:MM:SS format */
    inline std::string TimeStr() const
    {
        char TimeBuf[DDCTimeBufferSize];
        this->DateTime(NULL,TimeBuf);
        return std::string(TimeBuf);
    };

    /* get elapsed time since t0, double resolution */
    double Elapsed(const DDCTimeUnix& t0) const;
};

//======================================================================
// DDCTimeHiRes : nanosecond-resolution clock
#ifdef HAVE_CLOCK_GETTIME
struct DDCTimeHiRes : public DDCTimeUnix
{
    //----------------------------------------------------------------------
    // Data
    /* time value (high-resolution: 1 nanosecond) */
    struct timespec m_ts;

    //----------------------------------------------------------------------
    // constructors etc

    /* default constructor */
    DDCTimeHiRes()
    {};

    /* default constructor given struct timespec */
    DDCTimeHiRes(const struct timespec &ts_)
    { Set(ts_); };

    /* copy constructor */
    DDCTimeHiRes(const DDCTimeHiRes& t)
    { Set(t.m_ts); };

    /* copy constructor from DDCTimeUnix */
    DDCTimeHiRes(const DDCTimeUnix& t)
    { Set(t.m_t); };

    /* default destructor */
    virtual ~DDCTimeHiRes()
    {};

    /* constructor: current time */
    inline static DDCTimeHiRes Now()
    {
        DDCTimeHiRes t;
        t.Set();
        return t;
    };
    
    /* set this object to current time */
    inline void Set()
    {
        clock_gettime(CLOCK_REALTIME, &m_ts);
        DDCTimeUnix::Set(m_ts.tv_sec);
    };

    /* assignment operator (from time_t) */
    inline void Set(const time_t time_)
    {
        DDCTimeUnix::Set(time_);
        m_ts.tv_sec  = time_;
        m_ts.tv_nsec = 0;
    };

    /* assignment operator (from struct timespec) */
    inline void Set(const struct timespec &ts_)
    {
        m_t  = ts_.tv_sec;
        m_ts = ts_;
    };

    /* assignment operator (from DDCTimeUnix object) */
    inline void Set(const DDCTimeUnix& t)
    { Set(t.m_t); };

    /* assignment operator */
    inline void Set(const DDCTimeHiRes& t)
    { *this = t; };

    //----------------------------------------------------------------------
    // API

    /* inherited: get low-resultion time_t time */
    //time_t Time() const;

    /* inherited: get (low-resolution) calendar time; adapted from old RmlGetCurrentTime() */
    //struct tm CalendarTime() const;

    /* get time and date strings in ISO-8601 format (YYYY-MM-DD HH:MM:SS) to char* buffers
     *  - either of DateStr or TimeStr may be passed as NULL
     *  DateBuf: output buffer of at least DDCDateBufferSize bytes, or NULL
     *  TimeBuf: output buffer of at least DDCTimeBufferSize bytes, or NULL
     */
    virtual void DateTime(char* DateBuf, char* TimeBuf) const;

    /* inherited: get date string in ISO-8601 format (YYYY-MM-DD) */
    //inline std::string DateStr() const

    /* get time string in 24-hour HH:MM:SS format */
    // inline std::string TimeStr() const

    /* get elapsed time since t0, double resolution */
    double Elapsed(const DDCTimeHiRes& t0) const;
};

#else /* !defined(HAVE_CLOCK_GETTIME) */

/* compatibility typedef; used if clock_gettime() is unavailable */
typedef struct DDCTimeUnix DDCTimeHiRes;

#endif /* defined(HAVE_CLOCK_GETTIME) */

#ifdef DDC_USE_HIRES_CLOCK
/* typedef for default time class (either DDCTimeUnix or DDCTimeHiRes) */
typedef struct DDCTimeHiRes DDCTime;
#else
/* typedef for default time class (either DDCTimeUnix or DDCTimeHiRes) */
typedef struct DDCTimeUnix DDCTime;
#endif

//======================================================================
// DDCTimeAvg : exponential moving average
struct DDCTimeAvg
{
    //----------------------------------------------------------------------
    // typedefs

    /* typedef for delay keys (in seconds) */
    typedef size_t DelayT;

    /* typedef for moving-average samples and values */
    typedef double ValueT;

    /* typedef for timestamps */
    typedef DDCTimeHiRes TimeT;

    /* typedef for delay-to-value map */
    typedef std::map<DelayT,ValueT> MapT;

    //----------------------------------------------------------------------
    // data
    
    /* maps decay delays to current moving average values
     *  - keys ~ delays: number(s) of seconds until the contribution of a sample falls below 1/e (default=[60 300 900] ~ 1,5,15 minutes)
     *  - values ~ currentmoving average values
     */
    MapT  m_map;

    /* timestamp of the current sample as returned by DDCTime::Now() */
    TimeT m_t;

    /* global sample total */
    ValueT m_total;

    /* global number of samples */
    size_t m_n;
    
    //----------------------------------------------------------------------
    // constructors etc.

    /* constructor given up to three delays and optional initial value */
    DDCTimeAvg(DelayT delay1=60, DelayT delay2=300, DelayT delay3=900, ValueT val=0)
        : m_total(0), m_n(0)
    {
        SetDelays(delay1,delay2,delay3,val);
        m_t.Set();
    };

    /* constructor given delays as vector and optional initial value */
    DDCTimeAvg(const std::vector<DelayT>& delays, ValueT val=0)
        : m_total(0), m_n(0)
    {
        SetDelays(delays,val);
        m_t.Set();
    };

    /* copy constructor */
    DDCTimeAvg(const DDCTimeAvg& X)
        : m_map(X.m_map), m_t(X.m_t), m_total(X.m_total), m_n(X.m_n)
    {};

    /* reset sample values to zero */
    void reset(ValueT val=0);

    /* clear all data */
    inline void clear()
    {
        m_map.clear();
        reset();
    };

    //----------------------------------------------------------------------
    // manipulation

    /* set delays, given vector of delay keys */
    void SetDelays(const std::vector<DelayT>& delays, ValueT val=0);

    /* convenience method for setting up to 3 delays (zero delay-values are ignored) */
    void SetDelays(DelayT delay1=60, DelayT delay2=300, DelayT delay3=900, ValueT val=0);

    /* set delays, given a map of delay-keys to moving-average values */
    inline void SetDelays(const MapT& delayMap)
    { m_map = delayMap; };

    /* append a new sample value with timestamp when
     * returns new moving-average value map
     */
    MapT& Append(ValueT sample, const TimeT& when, size_t n=1);

    /* append a new sample value with current timestamp
     * returns new moving-average
     */
    inline MapT& Append(ValueT sample=0)
    { return Append(sample, TimeT::Now()); };

    /* append a new sample to the total only */
    inline void AppendTotal(ValueT sample)
    { m_total += sample; };

    /* hack: add EMA data from another object
     * - used by CDDCServerStats to add session-local averages to server-global stats
     * - does nothing if x.m_n==0; otherwise actually calls Append(x.Total())
     */
    inline DDCTimeAvg& operator+=(const DDCTimeAvg& x)
    { if (x.m_n > 0) Append(x.Total()); return *this;};

    /* alias used by CDDCLeafServer::handle__status() to synchronize times: causes moving-averages to decay */
    inline void Scrub()
    { Append(0,TimeT::Now(),0); };

    //----------------------------------------------------------------------
    // access
    
    /* get most recent sample-values (undecayed) */
    inline const MapT& Values() const
    { return m_map; };

    /* get most recent sample timestamp */
    inline const TimeT& Time() const
    { return m_t; };

    /* get sample total */
    inline ValueT Total() const
    { return m_total; };

    /* get global average value */
    inline ValueT Average() const
    { return m_n==0 ? m_total : (m_total / (ValueT)m_n); };

    /* get highest-resolution average value; used by CDDCLeafServer::handle__status() for compatiblity reports */
    inline ValueT tAverage() const
    { return m_map.begin()->second; };

    /* get JSON-array string of averages in ascending order of delay key */
    std::string toJsonArray() const;

    /* get JSON-map string of averages in ascending order of delay key */
    std::string toJsonMap() const;
};




//======================================================================
// Functions

        
//======================================================================
// date/time helpers (formerly in utilit.h)

// ISO 8601 timestamp, UTC
extern std::string timestampUTC(time_t timeval);

// moo: date-to-int encoding (v2.2.4: use signed years)
extern uint32_t date2int(  signed int y, unsigned int m=1, unsigned int d=1);

// moo: int-to-date decoding (v2.2.4: use signed years)
extern void int2date(uint32_t i, signed int *y, unsigned int *m=NULL, unsigned int *d=NULL);

#endif /* DDC_TIME_H */
