//*-*- Mode: C++ -*- */
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2016 by Bryan Jurish
//
//  This file is part of DDC (formerly in ConcHolder.h)
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
#ifndef DDC_CONC_SESSION_CONTEXT_H
#define DDC_CONC_SESSION_CONTEXT_H

#include "ConcHolder.h"
#include "../CommonLib/ddcThread.h"

//==============================================================================
/**
 * \brief common session data, sharable by multiple worker threads
 * \detail extracted from ddc-2.0.x CConcHolder; now CConcSession
 */
class CConcSessionContext : public ddcLockable
{
public:
    //! hit results for the last MaxQueryCacheSize queries 
    map<string, CQueryResult>       m_QueryCache;

    //! a deque for last MaxQueryCacheSize queries; m_Queries.last() is the last given query 
    deque<string>                   m_Queries;

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
    bool CacheGet(CConcHolder& Holder, const string &Query, DWORD& EndHitNo);

    /** store a result for \a Query in the cache
     *  \li formerly CConcHolder::SaveToCache()
     *  \li implicitly handles locking
     *  \param Holder session object / result set to store
     *  \param Query query string (cache key) to be stored
     *  \param start hit-index iterator wrt Holder.m_Hits[] of first hit to be stored
     *  \param end hit-index iterator wrt Holder.m_Hits[] of first hit NOT to store
     */
    void CacheSet(CConcHolder& Holder, const string& Query, vector<size_t>::const_iterator start, vector<size_t>::const_iterator end);

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

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
