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
#include <numeric> //-- for std::accumulate

//======================================================================
/** default BranchNavCache capacity */
#define DDC_DEFAULT_NAV_CACHE_CAPACITY 512

//======================================================================
//! navigation hint-key for branch server get_first_hits() "paging" 
struct BranchNavKey {
  string m_QueryStr;    ///< original query string
  size_t m_HitNo;       ///< maximum logical (branch-level) hit number covered

  //! default constructor
  BranchNavKey(const string& qstr="", const size_t hitno=0)
    : m_QueryStr(qstr), m_HitNo(hitno)
  {};

  //! comparison operator, for use with map<>
  //! \li wraps <code>m_QueryStr < X.m_QueryStr || m_HitNo > X.m_HitNo</code>
  //! \li m_HitNo comparison is reversed so we can use map<>::lower_bound()
  inline bool operator< (const BranchNavKey &X) const
  { return m_QueryStr < X.m_QueryStr || m_HitNo > X.m_HitNo; };

  //! assignment operator
  inline BranchNavKey& operator= (const BranchNavKey &X)
  {
    m_QueryStr = X.m_QueryStr;
    m_HitNo    = X.m_HitNo;
    return *this;
  };

  //! debug: stringification
  string toString() const
  { return Format("{\"QueryStr\":%s,\"HitNo\":%zd}", jsonStr(m_QueryStr).c_str(), m_HitNo); };
   
};

//======================================================================
//! navigation hint for branch server get_first_hits() "paging" 
struct BranchNavHint {
  string         m_SortKey;  ///< maximum sort key from any subcorpus in branch result-set
  vector<size_t> m_Offsets;  ///< maximum offset for each subcorpus in branch result-set

  //! default constructor
  //! \param nOffsets length of m_MinOffsets (number of subcorpora)
  BranchNavHint(size_t nOffsets=0)
    : m_Offsets(nOffsets,0)
  {};

  //! constructor given sort key and number of subocpora
  BranchNavHint(const string& SortKey, size_t nOffsets=0)
    : m_SortKey(SortKey), m_Offsets(nOffsets,0)
  {};

  //! constructor given sort key and offsets
  BranchNavHint(const string& SortKey, const vector<size_t>& Offsets)
    : m_SortKey(SortKey), m_Offsets(Offsets)
  {};

  //! clear the hint
  inline void clear(size_t nOffsets=0)
  {
    m_SortKey.clear();
    m_Offsets.assign(nOffsets,0);
  };

  //! assignment operator
  inline BranchNavHint& operator= (const BranchNavHint &X)
  {
    m_SortKey = X.m_SortKey;
    m_Offsets = X.m_Offsets;
    return *this;
  };

  //! return total number of gobbled offsets (sum over m_Offsets)
  inline size_t OffsetTotal() const
  { return std::accumulate(m_Offsets.begin(), m_Offsets.end(), 0); };

  //! debug: stringification
  string toString() const
  {
    string s = Format("{\"SortKey\":%s, \"Offsets\":[", jsonStr(m_SortKey).c_str());
    for (vector<size_t>::const_iterator oi=m_Offsets.begin(); oi!=m_Offsets.end(); ++oi) {
      if (oi != m_Offsets.begin()) s.push_back(',');
      s += Format("%zd", *oi);
    }
    s += "]}";
    return s;
  };

};


//======================================================================
//! LRU cache for faster "paging" through daughter hits for a branch server
class BranchNavCache : public ddcLockable
{
public:
  //------------------------------------------------------------
  // public typedefs
  typedef BranchNavKey  KeyT; ///< navigation cache key type
  typedef BranchNavHint ValT; ///< navigation cache value type

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
  //! wraps lock(); m_Cache.size(); unlock()
  inline size_t size() const
  {
    size_t sz=0;
    lock();
    try {
      sz = m_Cache.size();
      unlock();
    } catch (...) {
      unlock();
      throw;
    }
    return sz;
  };

  //----------------------------------------------------
  //! wraps lock(); m_Cache.clear(); unlock()
  inline void clear()
  {
    lock();
    try {
      m_Cache.clear();
      unlock();
    } catch (...) {
      unlock();
      throw;
    }
  };

  //----------------------------------------------------
  //! get lower bound for key \a key = (QueryStr,HitNo)
  //! \returns true iff a match was found in cache, false otherwise
  //! \li copies lower-bound cached hint for key if \a QueryStr matches, otherwise clears hint
  //! \li if a valid match is found, it is promoted to MRU position
  //! \li wraps operation in lock() + unlock()
  //! \param val (output) hint to be extracted (data copied from cache)
  //! \param key (input) key to search for
  //! \param nSubs (input) number of subcorpora
  bool lower_bound(ValT& val, const KeyT& key, size_t nSubs=0)
  {
    bool found = false;
    val.clear(nSubs);
    
    lock();
    try {
      CacheT::const_iterator ci = m_Cache.lower_bound(key);
      if (ci != m_Cache.end() && ci->first.m_QueryStr == key.m_QueryStr) {
	val   = ci->second->second;
	found = true;
	m_Cache.promote(ci);
      }
    } catch (...) {
      unlock();
      throw;
    }

    //-- all done
    unlock();
    return found;
  };

  //----------------------------------------------------
  //! get lower bound for key \a key = (QueryStr,HitNo)
  //! \returns copy of lower-bound cached hint for key if \a QueryStr matches, otherwise an empty hint for nSubs
  inline ValT lower_bound(const KeyT& key, size_t nSubs=0)
  {
    ValT val(nSubs);
    lower_bound(val, key, nSubs);
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

  //! wrapper for insert(KeyT(QueryStr, HitNo), ValT(SortKey,Offsets))
  inline void insert(const string& QueryStr, size_t HitNo, const string& SortKey, const vector<size_t>& Offsets)
  { insert(KeyT(QueryStr,HitNo), ValT(SortKey,Offsets)); };

  //------------------------------------------------------------
  // debugging
  //! debug: stringification
  string toString() const
  {
    string s = (string("{\n")
		+ Format(" \"size\":%zd,\n", m_Cache.size())
		+ Format(" \"capacity\":%zd,\n", m_Cache.capacity())
		+ " \"data\":[");
    for (CacheT::ListT::const_iterator li=m_Cache.m_list.begin(); li != m_Cache.m_list.end(); ++li) {
      if (li != m_Cache.m_list.begin()) s.push_back(',');
      s += "\n  {\"key\":";
      s += li->first.toString();
      s += ", \"val\":";
      s += li->second.toString();
      s += "}";
    }
    s += "\n ]}";
    return s;
  };
};


#endif /* DDC_BRANCH_NAVCACHE_H */

