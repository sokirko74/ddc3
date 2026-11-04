#ifndef DDC_LRUCACHE_H
#define DDC_LRUCACHE_H

#include "../CommonLib/ddcConfig.h"
#include <list>
#include <map>

#ifdef HAVE_PTHREAD
# include <pthread.h>
# define DDC_IFPTHREAD(x) x
# define DDC_IFPTHREADELSE(x,y) x
#else
# define DDC_IFPTHREAD(x)
# define DDC_IFPTHREADELSE(x,y) y
#endif

//======================================================================
// Globals

//! default cache capacity
#define DDC_DEFAULT_LRU_CACHE_CAPACITY 1024

//======================================================================
//! \brief generic least-recently-used cache template
template<class Key, class Val>
class ddcLRUCache {
public:
    //------------------------------------------------------------
    // public typedefs

    //! key type
    typedef Key KeyT;

    //! value type
    typedef Val ValT;

#if HAVE_PTHREAD
    //! mutex type (pthreads enabled)
    typedef pthread_mutex_t* MutexT;
#else
    //! mutex type (dummy, no pthreads)
    typedef void* MutexT;
#endif

    //! elementary data item: (key,val) pair
    typedef std::pair<KeyT,ValT> ItemT;

    //! list of (key,val) pairs, position indicates recency of use (most recent first)
    typedef std::list<ItemT> ListT;

    //! maps keys to lru-list iterators, used to check key existence
    typedef std::map<KeyT, typename ListT::iterator> MapT;

    //! iterator wraps MapT::iterator (~ pair< KeyT, pair<KeyT,ValT>* > *)
    typedef typename MapT::iterator iterator;

    //! const_iterator wraps MapT::const_iterator
    typedef typename MapT::const_iterator const_iterator;

public:
    //------------------------------------------------------------
    // pseudo-private data (public just in case you Know What You're Doing)

    //! maximum number of cached items
    size_t m_capacity;

    //! current number of cached items
    size_t m_size;

    //! list of (key,val) pairs, position indicates recency of use (most recent first)
    ListT m_list;

    //! maps keys to m_list iterators, used to check key existence
    MapT  m_map;

    //! mutex pointer to use for lock() and unlock() methods
    MutexT m_mutex;

public:
    //------------------------------------------------------------
    // public methods: constructors etc

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //! default constructor
    ddcLRUCache(size_t capacity=DDC_DEFAULT_LRU_CACHE_CAPACITY, MutexT mutex=NULL)
        : m_capacity(capacity),
          m_size(0),
          m_mutex(mutex)
    {};

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //! clear all cached items (no implicit locks)
    void clear()
    {
        m_map.clear();
        m_list.clear();
        m_size = 0;
    };

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //! drop least recently used cache items until size <= capacity
    void clean()
    {
        while (m_size > m_capacity) {
            const ItemT &lru_item = m_list.back();
            m_map.erase(lru_item.first);
            m_list.pop_back();
            --m_size;
        }
    };

    //------------------------------------------------------------
    // public methods: basic accessors

    //! get mutex pointer
    inline MutexT mutex() const
    { return m_mutex; };

    //! set mutex pointer
    inline MutexT mutex(MutexT mut)
    { return m_mutex=mut; };

    //! get number of currently cached items
    inline size_t size() const
    { return m_size; };

    //! get cache capacity
    inline size_t capacity() const
    { return m_capacity; };

    //! update cache capacity; implicitly calls clean()
    inline size_t reserve(size_t cap)
    {
        m_capacity=cap;
        clean();
        return m_capacity;
    };

    //------------------------------------------------------------
    // public methods: locking

    //! lock the cache mutex, if any
    inline void lock()
    { DDC_IFPTHREAD(if (m_mutex) pthread_mutex_lock(m_mutex)); };

    //! unlock cache mutex
    inline void unlock()
    { DDC_IFPTHREAD(if (m_mutex) pthread_mutex_unlock(m_mutex)); };

    //------------------------------------------------------------
    // public methods: map iterators

    inline iterator begin()               { return m_map.begin(); };
    inline iterator end()                 { return m_map.end(); };
    inline const_iterator begin() const   { return m_map.begin(); };
    inline const_iterator end()   const   { return m_map.end(); };

    //------------------------------------------------------------
    // public methods: lookup (no implicit locking; use must call lock() and unlock() if and when appropriate)

    //! find cached item; returns end() if not found, does NOT update the MRU-list (non-const)
    inline iterator find(const KeyT &key)
    { return m_map.find(key); };

    //! find lower bound for cache key; does NOT update the MRU-list (non-const)
    inline iterator lower_bound(const KeyT &key)
    { return m_map.lower_bound(key); };

    //! find upper bound for cache key; does NOT update the MRU-list (non-const)
    inline iterator upper_bound(const KeyT &key)
    { return m_map.upper_bound(key); };
  
    //! find cached item; returns end() if not found; does NOT update the MRU-list (const version)
    inline const_iterator find(const KeyT &key) const
    { return m_map.find(key); };

    //! find lower bound for cache key; does NOT update the MRU-list (const version)
    inline const_iterator lower_bound(const KeyT &key) const
    { return m_map.lower_bound(key); };

    //! find upper bound for cache key; does NOT update the MRU-list (const version)
    inline const_iterator upper_bound(const KeyT &key) const
    { return m_map.upper_bound(key); };

    //! get cached item, promoting it to MRU position if already exists; return end() if key is not found
    inline iterator get(const KeyT &key)
    {
        iterator mapi = m_map.find(key);
        if (mapi != m_map.end() && mapi->second != m_list.begin())
            promote(mapi);
        return mapi;
    };

    //! promote an existing item to the most-recently-used position
    void promote(const_iterator &it)
    { if (it->second != m_list.begin()) m_list.splice(m_list.begin(), m_list, it->second); };

    //! promote an existing item to the most-recently-used position
    void promote(iterator &it)
    { if (it->second != m_list.begin()) m_list.splice(m_list.begin(), m_list, it->second); };

    //! insert a new cache item, or promote an existing item if present.
    //! \li implicitly calls clean().
    //! \li prior to v2.1.11 returned an iterator to the newly inserted item
    //! \li as of v2.1.11, no iterator is returned, since it might be invalid if capacity==0
    void insert(const KeyT &key, const ValT &val)
    {
        iterator mapi = get(key);
        if (mapi != m_map.end()) {
            //-- update existing item (it's already been promoted by get() if it exists)
            mapi->second->second = val;
        }
        else if (m_capacity > 0) {
            //-- insert new item (only if we're not just going to delete it again)
            m_list.push_front(std::make_pair(key,val));
            m_map.insert(std::make_pair(key, m_list.begin()));
            ++m_size;
            clean();
        }
        //-- sanity check: FAILS for NavHintCache on v2.1.10 due to bogus NavHintKey::operator<()
        //assert(m_size==m_list.size() && m_size==m_map.size());
    };

};


#endif /* DDC_LRUCACHE_H */
