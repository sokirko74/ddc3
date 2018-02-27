//-*- Mode: C++; c-basic-offset:2; -*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2018 by Bryan Jurish
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
#ifndef DDC_BRANCH_NAVCACHE_H
#define DDC_BRANCH_NAVCACHE_H

#include "../ConcordLib/ConcCommon.h"
#include "../ConcordLib/LRUCache.h"
#include "../CommonLib/ddcThread.h"

/** default BranchNavCache capacity */
#define DDC_DEFAULT_NAV_CACHE_CAPACITY 1024

//======================================================================
//! cache sort keys and subcorpus-wise offsets for faster "paging" through hits
class BranchNavCache : public ddcLockable
{
public:
  //------------------------------------------------------------
  // public typedefs

  //----------------------------------------------------
  //! paging cache: key
  struct KeyT {
    string m_QueryStr;    ///< original query string
    size_t m_HitNo;       ///< maximum hit number

    //! default constructor
    KeyT(const string& qstr="", const size_t hitno=0)
      : m_QueryStr(qstr), m_HitNo(hitno)
    {};

    //! comparison operator, for use with map<>
    //! \li wraps <code>m_QueryStr < X.m_QueryStr || m_HitNo > X.m_HitNo</code>
    //! \li m_HitNo comparison is reversed so we can use map<>::lower_bound()
    inline bool operator< (const KeyT &X) const
    { return m_QueryStr < X.m_QueryStr || m_HitNo > X.m_HitNo; };

    //! assignment operator
    inline KeyT& operator= (const KeyT &X)
    {
      m_QueryStr = X.m_QueryStr;
      m_HitNo    = X.m_HitNo;
      return *this;
    };
  };

  //----------------------------------------------------
  //! paging cache: value
  struct ValT
  {
    string         m_MinSortKey;  ///< minimum sort key
    vector<size_t> m_MinOffsets;  ///< minimum offsets per subcorpus

    //! default constructor
    //! \param nOffsets length of m_MinOffsets (number of subcorpora)
    ValT(size_t nOffsets=0)
      : m_MinOffsets(nOffsets,0)
    {};

    //! constructor given sort key and number of subocpora
    ValT(const string& minKey, size_t nOffsets=0)
      : m_MinSortKey(minKey), m_MinOffsets(nOffsets,0)
    {};


    //! constructor given sort key and offsets
    ValT(const string& minKey, const vector<size_t>& minOffsets)
      : m_MinSortKey(minKey), m_MinOffsets(minOffsets)
    {};  

    //! assignment operator
    inline ValT& operator= (const ValT &X)
    {
      m_MinSortKey = X.m_MinSortKey;
      m_MinOffsets = X.m_MinOffsets;
      return *this;
    };
  };

  //----------------------------------------------------
  //! typedef for underlying LRU cache object
  typedef ddcLRUCache<KeyT,ValT> CacheT;

public:
  //------------------------------------------------------------
  // public data
  CacheT m_Cache;  ///< underlying LRU cache

public:
  //------------------------------------------------------------
  // constructors etc.

  //! default constructor
  //! \li initializes m_Cache to use m_Mutex inherited from ddcLockable
  BranchNavCache(size_t capacity=DDC_DEFAULT_NAV_CACHE_CAPACITY)
    : m_Cache(capacity, &m_Mutex)
  {};

  //! default destructor (empty)
  ~BranchNavCache()
  {};

  //------------------------------------------------------------
  // API

  //----------------------------------------------------
  //! get lower bound for key \a key = (QueryStr,HitNo)
  //! \returns copy of lower bound for key if \a QueryStr matches, otherwise a default \a ValT for \a nSubs
  //! \li if a valid match is found, it is promoted to MRU position
  //! \li wraps operation in lock() + unlock()
  ValT lower_bound(const KeyT& key, size_t nSubs=0)
  {
    ValT val(nSubs);
    
    lock();
    try {
      CacheT::const_iterator ci = m_Cache.lower_bound(key);
      if (ci != m_Cache.end() && ci->first.m_QueryStr == key.m_QueryStr) {
	val = ci->second->second;
	m_Cache.promote(ci);
      }
    } catch (...) {
      unlock();
      throw;
    }

    //-- all done
    unlock();
    return val;
  };

  //----------------------------------------------------
  //! insert new entry for \a key = (QueryStr,HitNo)
  //! \li promotes new entry to MRU position
  //! \li implicitly wraps operation in lock() + unlock()
  inline void insert(const KeyT& key, const ValT& val)
  {
    lock();
    try {
      m_Cache.insert(key,val);
    } catch (...) {
      unlock();
      throw;
    }
    unlock();
  };

  //------------------------------------------------------------
  // convenience API

  //! wrapper for lower_bound(KeyT(QueryStr, HitNo))
  inline ValT lower_bound(const string& QueryStr, size_t HitNo)
  { return lower_bound(KeyT(QueryStr,HitNo)); };

  //! wrapper for insert(KeyT(QueryStr, HitNo), ValT(MinSortKey,MinOffsets))
  inline void insert(const string& QueryStr, size_t HitNo, const string& MinSortKey, const vector<size_t> MinOffsets)
  { insert(KeyT(QueryStr,HitNo), ValT(MinSortKey,MinOffsets)); };

};


#endif /* DDC_BRANCH_NAVCACHE_H */

