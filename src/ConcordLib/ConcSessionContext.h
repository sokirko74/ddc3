#ifndef DDC_CONC_SESSION_CONTEXT_H
#define DDC_CONC_SESSION_CONTEXT_H

#include "ConcHolder.h"
#include "../CommonLib/ddcThread.h"
#include <deque>

//==============================================================================
/**
 * \brief common session data, sharable by multiple worker threads
 * \detail extracted from ddc-2.0.x CConcHolder; now CConcSession
 */
class CConcSessionContext : public ddcLockable
{
public:
    //! hit results for the last MaxQueryCacheSize queries 
    std::map<std::string, CQueryResult>       m_QueryCache;

    //! a deque for last MaxQueryCacheSize queries; m_Queries.last() is the last given query 
    std::deque<std::string>                   m_Queries;

public:
    //----------------------------------------------------------------------
    // \name Constructors etc.
    //@{
    /** default constructor */
    CConcSessionContext()
    {};

    /** default destructor */
    ~CConcSessionContext()
    {};
    //@}

public:
    //----------------------------------------------------------------------
    // \name API: caching
    //@{
    /** fetch cached result for Query if available
     *  \li formerly CConcHolder::TryToGetFromCache()
     *  \li implicitly handles locking
     *  \param Holder session object / result set to populate
     *  \param Query query string (cache key) to be fetched
     *  \param EndHitNo on call, index of first hit to retrieve; on return index of last hit retrieved
     *  \returns true on success, otherwise false
     */
    bool CacheGet(CConcHolder& Holder, const std::string &Query, uint32_t& EndHitNo);

    /** store a result for \a Query in the cache
     *  \li formerly CConcHolder::SaveToCache()
     *  \li implicitly handles locking
     *  \param Holder session object / result set to store
     *  \param Query query string (cache key) to be stored
     *  \param start hit-index iterator wrt Holder.m_Hits[] of first hit to be stored
     *  \param end hit-index iterator wrt Holder.m_Hits[] of first hit NOT to store
     */
    void CacheSet(CConcHolder& Holder, const std::string& Query, std::vector<size_t>::const_iterator start, std::vector<size_t>::const_iterator end);

    /** clear the query cache; implicitly handles locking */
    void CacheClear();

    /** get current cache size; implicitly handles locking */
    size_t CacheSize();
    //@}

    //----------------------------------------------------------------------
    // API: locking : now in ddcLockable base class
    //inline int lock();
    //inline int unlock();
};


#endif /* DDC_CONC_SESSION_CONTEXT_H */
