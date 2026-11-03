//-*- Mode: C++ -*-
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
#ifndef DDC_NAV_HINT_H
#define DDC_NAV_HINT_H

#include "../ConcordLib/ConcCommon.h"
#include "../ConcordLib/LRUCache.h"
#include "../CommonLib/ddcThread.h"
#include <numeric> //-- for std::accumulate

//======================================================================

/** default NavHintCache capacity */
#define DDC_DEFAULT_NAV_HINT_CACHE_CAPACITY 1024

/** default NavHintCache step size (used by ServerOptions, BranchServer) */
#define DDC_DEFAULT_NAV_HINT_CACHE_STEP 1000

//------------------------------------------------------
//#define DEBUG_NAVCACHE 1
#undef DEBUG_NAVCACHE
#ifdef DEBUG_NAVCACHE
# define NAVCACHE_DEBUG(x) x
#else
# define NAVCACHE_DEBUG(x)
#endif

//------------------------------------------------------
//#define TRACE_NAVCACHE 1
#undef TRACE_NAVCACHE
#ifdef TRACE_NAVCACHE
# define NAVCACHE_TRACE(x) x
#else
# define NAVCACHE_TRACE(x)
#endif

//======================================================================
//! navigation hint-key for branch server get_first_hits() "paging" 
struct NavHintKey {
    std::string m_QueryStr;    ///< original query string
    size_t m_HitNo;       ///< maximum logical hit number covered w.r.t. local corpus

    //! default constructor
    NavHintKey(const std::string& qstr="", const size_t hitno=0)
        : m_QueryStr(qstr), m_HitNo(hitno)
    {};

    //! clear the object
    inline void clear()
    {
        ClearString(m_QueryStr);
        m_HitNo = 0;
    };

    //! comparison operator, for use with map<>
    //! \li wraps <code>m_QueryStr < X.m_QueryStr || m_HitNo > X.m_HitNo</code>
    //! \li m_HitNo comparison is reversed so we can use map<>::lower_bound()
    inline bool operator< (const NavHintKey &X) const
    {
        return (m_QueryStr < X.m_QueryStr ? true                    //-- QueryStr is primary sort-key
                : (m_QueryStr==X.m_QueryStr ? (m_HitNo > X.m_HitNo) //-- ... only compare HitNo if QueryStr matches (otherwise map<> chokes)
                   : false));                                       //-- ... QueryStr>X.QueryStr
    };

    //! equality operator (for debugging)
    inline bool operator== (const NavHintKey &X) const
    { return m_HitNo == X.m_HitNo && m_QueryStr == X.m_QueryStr; };

    //! verbose assignment
    inline void assign(const std::string& qstr, const size_t hitno=0)
    {
        m_QueryStr = qstr;
        m_HitNo    = hitno;
    };
  
    //! assignment operator
    inline NavHintKey& operator= (const NavHintKey &X)
    {
        assign(X.m_QueryStr, X.m_HitNo);
        return *this;
    };

    //! debug: native stringification
    inline std::string toString() const
    { return Format("%zd %s", m_HitNo, m_QueryStr.c_str()); };

    //! debug: native decoding from string
    void fromString(const char *s);
  
    //! debug: JSON stringification
    std::string toJson() const;
};


//======================================================================
//! navigation hint with respect to local subcorpus tree, for get_first_hits "paging"
struct NavHint {
    std::string         m_SortKey;  ///< minimum sort key from this node or any subcorpus
    size_t         m_Offset;   ///< minimum offset for local corpus node
    std::vector<std::string> m_DtrHints; ///< offset hints for immediate daughter subcorpora

    //! default constructor
    //! \param nDtrs number of immediate subcorpora
    NavHint(size_t nDtrs=0)
        : m_SortKey(""), m_Offset(0), m_DtrHints(nDtrs,"")
    {};

    //! constructor given local offset and number of daughters
    NavHint(size_t Offset, size_t nDtrs)
        : m_SortKey(""), m_Offset(Offset), m_DtrHints(nDtrs,"")
    {};

    //! constructor given sort key, offset, and number of subcorpora
    NavHint(const std::string& SortKey, size_t Offset, size_t nDtrs)
        : m_SortKey(SortKey), m_Offset(Offset), m_DtrHints(nDtrs,"")
    {};

    //! full constructor
    NavHint(const std::string& SortKey, size_t Offset, const std::vector<std::string> DtrHints)
        : m_SortKey(SortKey), m_Offset(Offset), m_DtrHints(DtrHints)
    {};

    //! constructor from string
    NavHint(const std::string& HintStr)
    { fromString(HintStr); };

    //! clear the hint
    inline void clear(size_t nDtrs=0)
    {
        m_SortKey.clear();
        m_Offset = 0;
        m_DtrHints.assign(nDtrs,"");
    };

    //! returns true iff this is an empty hint
    inline bool empty() const
    { return m_SortKey.empty() && m_Offset==0; };

    //! get sum of daughter offsets
    size_t OffsetTotal() const;

    //! convenience wrapper: set local offset to sum of daughter offsets
    inline void UpdateOffset()
    { m_Offset = OffsetTotal(); };

    //! get hint-string for daughter number DtrNo
    inline const char* DtrHint(size_t DtrNo) const
    { return (DtrNo < m_DtrHints.size() ? m_DtrHints[DtrNo].c_str() : ""); };
  
    //! get offset for daughter number DtrNo
    inline size_t DtrOffset(size_t DtrNo) const
    { return (DtrNo < m_DtrHints.size() ? strtoul(m_DtrHints[DtrNo].c_str(),NULL,0) : 0); };
  
    //! assignment operator
    inline NavHint& operator= (const NavHint &X)
    {
        m_SortKey  = X.m_SortKey;
        m_Offset   = X.m_Offset;
        m_DtrHints = X.m_DtrHints;
        return *this;
    };

    //! string assignment wraps fromString()
    inline NavHint& operator= (const std::string& S)
    {
        fromString(S);
        return *this;
    };

    //! assigns \a SortKey and \a Offset and resize \a DtrHints 
    inline void update(const std::string& SortKey, size_t Offset, size_t nDtrs)
    {
        m_SortKey = SortKey;
        m_Offset  = Offset;
        m_DtrHints.resize(nDtrs);
    };

    //! serialization: returns a string-form for this hint suitable for parsing with the fromString() method.
    //! \li returned string is of the form <code>OFFSET ("(" DTR_OFFSETS ")")? (" " SORTKEY)?</code>
    //! \li if the local node has no daughters, the daughter offset hint <code>DTR_OFFSETS</code> is omitted.
    //! \li if the local node is a branch-node, <code>$DTR_OFFSETS</code> is a "+"-separated list of subcorpus-wise daughter offset hints
    //!     of the form <code>DTR_OFFSET_1 "+" DTR_OFFSET_2 "+" ... "+" DTR_OFFSET_N</code>,
    //!     and each <code>DTR_OFFSET_i</code> item is a nested hint <code>DTR_OFFSET ("(" DTR_DTR_OFFSETS ")")?</code> appropriate for
    //!     the respective daughter subcorpus.
    //! \li if \a m_SortKey is empty, the <code>"\t" SORTKEY</code> suffix is omitted.
    std::string toString(bool includeSortKey=true) const;

    //! de-serialization: parses a string hint as returned by the toString() method, which see for details on the accepted syntax.
    void fromString(const std::string& Str);

    //! debug: JSON stringification
    std::string toJson() const;
};

//======================================================================
//! LRU cache for faster "paging" through daughter hits for a branch server
class NavHintCache : public ddcLockable
{
public:
    //------------------------------------------------------------
    // public typedefs
    typedef NavHintKey  KeyT; ///< navigation cache key type
    typedef NavHint ValT; ///< navigation cache value type

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
    NavHintCache(size_t capacity=DDC_DEFAULT_NAV_HINT_CACHE_CAPACITY)
        : m_Cache(capacity, &m_Mutex)
    {};

    //! default destructor (empty)
    ~NavHintCache()
    {};

    //------------------------------------------------------------
    // API

    //! wraps lock(); m_Cache.reserve(capacity_); unlock()
    inline void reserve(size_t capacity_)
    {
        lock();
        try {
            m_Cache.reserve(capacity_);
        } catch (...) {
            unlock();
            throw;
        }
        unlock();
    };
  
    //----------------------------------------------------
    //! wraps lock(); m_Cache.size(); unlock()
    inline size_t size() const
    {
        size_t sz=0;
        lock();
        try {
            sz = m_Cache.size();
        } catch (...) {
            unlock();
            throw;
        }
        unlock();
        return sz;
    };

    //----------------------------------------------------
    //! wraps lock(); m_Cache.clear(); unlock()
    inline void clear()
    {
        lock();
        try {
            m_Cache.clear();
        } catch (...) {
            unlock();
            throw;
        }
        unlock();
    };

    //----------------------------------------------------
    //! get lower bound for key \a key = (QueryStr,HitNo)
    //! \returns true iff a match was found in cache, false otherwise
    //! \li copies lower-bound cached hint for key if \a QueryStr matches, otherwise clears hint
    //! \li if a valid match is found, it is promoted to MRU position iff \a doPromote is true
    //! \li wraps operation in lock() + unlock()
    //! \param val (output) hint to be extracted (data copied from cache if found, otherwise an empty hint)
    //! \param key (input) key to search for
    //! \param doPromote (input) whether to implicitly promote match to MRU position
    bool lower_bound(ValT& val, const KeyT& key, bool doPromote=true);

    //----------------------------------------------------
    //! get lower bound for key \a key = (QueryStr,HitNo)
    //! \returns copy of lower-bound cached hint for key if \a QueryStr matches, otherwise an empty hint for nSubs
    inline ValT lower_bound(const KeyT& key, bool doPromote=true)
    {
        ValT val;
        lower_bound(val, key, doPromote);
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
            NAVCACHE_TRACE(ddcLogTrace(Format("NavCache::insert(\"%s\",\"%s\")", escapeCString(key.toString()).c_str(), escapeCString(val.toString()).c_str())));
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
    inline ValT lower_bound(const std::string& QueryStr, size_t HitNo)
    { return lower_bound(KeyT(QueryStr,HitNo)); };

    //! wrapper for insert(KeyT(QueryStr, HitNo), ValT(SortKey,Offset,DtrHints))
    inline void insert(const std::string& QueryStr, size_t HitNo, const std::string& SortKey, const size_t Offset, const std::vector<std::string>& DtrHints)
    { insert(KeyT(QueryStr,HitNo), ValT(SortKey,Offset,DtrHints)); };

    //------------------------------------------------------------
    // debugging
    //! debug: stringification
    std::string toJson() const;
};


#endif /* DDC_NAV_HINT_H */

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
