#ifndef DDC_CONC_SESSION_CONTEXT_H
#define DDC_CONC_SESSION_CONTEXT_H

#include "ConcHolder.h"
#include "../CommonLib/ddcThread.h"
#include <deque>

//==============================================================================
/*
 * common session data, sharable by multiple worker threads
 * extracted from ddc-2.0.x CConcHolder; now CConcSession
 */
class CConcSessionContext : public ddcLockable
{
public:
    // hit results for the last MaxQueryCacheSize queries 
    std::map<std::string, CQueryResult>       m_QueryCache;

    // a deque for last MaxQueryCacheSize queries; m_Queries.last() is the last given query 
    std::deque<std::string>                   m_Queries;

public:
    //----------------------------------------------------------------------
    //  Constructors etc.
    //
    /* default constructor */
    CConcSessionContext()
    {};

    /* default destructor */
    ~CConcSessionContext()
    {};
    //

public:
    //----------------------------------------------------------------------
    //  API: caching
    //
    /* fetch cached result for Query if available
     *  - formerly CConcHolder::TryToGetFromCache()
     *  - implicitly handles locking
     *  Holder: session object / result set to populate
     *  Query: query string (cache key) to be fetched
     *  EndHitNo: on call, index of first hit to retrieve; on return index of last hit retrieved
     *  returns true on success, otherwise false
     */
    bool CacheGet(CConcHolder& Holder, const std::string &Query, uint32_t& EndHitNo);

    /* store a result for Query in the cache
     *  - formerly CConcHolder::SaveToCache()
     *  - implicitly handles locking
     *  Holder: session object / result set to store
     *  Query: query string (cache key) to be stored
     *  start: hit-index iterator wrt Holder.m_Hits[] of first hit to be stored
     *  end: hit-index iterator wrt Holder.m_Hits[] of first hit NOT to store
     */
    void CacheSet(CConcHolder& Holder, const std::string& Query, std::vector<size_t>::const_iterator start, std::vector<size_t>::const_iterator end);

    /* clear the query cache; implicitly handles locking */
    void CacheClear();

    /* get current cache size; implicitly handles locking */
    size_t CacheSize();
    //

    //----------------------------------------------------------------------
    // API: locking : now in ddcLockable base class
    //inline int lock();
    //inline int unlock();
};


#endif /* DDC_CONC_SESSION_CONTEXT_H */
