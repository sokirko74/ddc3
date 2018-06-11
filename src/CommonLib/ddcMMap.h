//-*- Mode: C++; c-basic-offset:4;-*-
//
//  Copyright 2018 by Bryan Jurish
//
//  This file is part of DDC.
//  DDC originally by Alexey Sokirko
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
#ifndef DDC_MMAP_H
#define DDC_MMAP_H

#ifdef HAVE_CONFIG_H
#include "../common/ddcConfig.h"
#endif
#include "../common/bserialize.h"
#include "../CommonLib/utilit.h"
#include "../CommonLib/ddcLog.h"

#include <string>
#include <stdexcept>
#include <algorithm>

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h> /* fstat */
#include <sys/mman.h> /* mmap */

//======================================================================
// ddcMMap
/** convenience wrapper for mapping entire files into virtual memory using mmap() */
template<typename T=char>
class ddcMMap
{
public:
    //----------------------------------------------------------
    // data
    std::string  m_file;    ///< underlying filename
    size_t       m_nbytes;  ///< number of bytes mapped
    T           *m_data;    ///< file data

public:
    //----------------------------------------------------------
    // constructors etc.

    /// default constructor
    ddcMMap()
	: m_nbytes(0), m_data(NULL)
    {};

    ddcMMap(const std::string& filename, int mode=O_RDONLY)
	: m_nbytes(0), m_data(NULL)
    { open(filename,mode); };

    /// default destructor calls close()
    ~ddcMMap()
    { close(); };

public:
    //----------------------------------------------------------
    // accessors

    /// returns the name of the currently mapped file, if any
    inline const std::string& filename() const
    { return m_file; };

    /// returns number of bytes mapped, or 0
    inline size_t nbytes() const
    { return m_nbytes; };

    /// returns a pointer to the mmap()ed file data, or NULL
    inline T* data() const
    { return m_data; };

public:
    //----------------------------------------------------------
    // high-level properties

    /// returns the number of objects of type T mapped, or 0
    inline size_t size() const
    { return m_nbytes / sizeof(T); };
    
    /// STL-esque wrapper for (nbytes()==0)
    inline bool empty() const
    { return m_nbytes==0; };

    /// returns true iff m_data is non-NULL
    inline bool opened() const
    { return m_data != NULL; };

public:
    //----------------------------------------------------------
    // typecast operators

    /// implicit typecast to bool
    inline operator bool() const
    { return opened(); };
    
    /// implicit typecast to T*
    inline operator T*() const
    { return m_data; };

    /// indexing operator
    inline T& operator[](size_t idx) const
    { return m_data[idx]; };

public:
    //----------------------------------------------------------
    // guts

    /// map a named file \a filename
    ddcMMap& open(const std::string& filename, int mode=O_RDONLY)
    {
	if (opened()) close();
	//ddcLogTrace("ddcMMap::open("+filename+")");
	m_file = filename;

	//-- open the file (temporarily)
	int mmfd = ::open(filename.c_str(), mode);
	if (mmfd == -1)
	    throw std::invalid_argument(Format("ddcMMap::open(): open failed for '%s': %s", filename.c_str(), strerror(errno)));

	//-- get total file size
	struct stat statbuf;
	if (fstat(mmfd, &statbuf) != 0)
	    throw std::runtime_error(Format("ddcMMap::open(): fstat() failed for file '%s': %s", filename.c_str(), strerror(errno)));
	m_nbytes = statbuf.st_size;

	//-- get mmap protection flags
	int mmprot = 0;
	switch (mode) {
	case O_RDONLY: mmprot = PROT_READ; break;
	case O_WRONLY: mmprot = PROT_WRITE; break;
	case O_RDWR:   mmprot = (PROT_READ|PROT_WRITE); break;
	default:
	    throw std::invalid_argument(Format("ddcMMap::open(): unknown open mode '%d'",mode));
	}

	//-- underlying mmap call
	m_data = (T*)mmap(NULL, m_nbytes, mmprot, MAP_SHARED, mmfd, 0);
	if (m_data == MAP_FAILED)
	    throw std::runtime_error(Format("ddcMMap::open(): mmap() failed for file '%s': %s", filename.c_str(), strerror(errno)));

	//-- we can now safely close the fd
	if (::close(mmfd) != 0)
	    throw std::runtime_error(Format("ddcMMap::open(): close() failed for file '%s': %s", filename.c_str(), strerror(errno)));
	
	return *this;
    };

    /// unmap current file (if any)
    void close()
    {
	if (m_data != NULL) {
	    //ddcLogTrace("ddcMMap::close("+m_file+")");
	    if (munmap(m_data, m_nbytes) != 0)
		throw std::runtime_error(Format("ddcMMap::close(): munmap() failed for file '%s': %s", m_file.c_str(), strerror(errno)));
	}
	ClearString(m_file);
	m_data = NULL;
	m_nbytes = 0;
    };

public:
    //----------------------------------------------------------
    // STL-style iterators

    typedef T*       iterator;
    typedef const T* const_iterator;

    inline iterator begin() const { return m_data; };
    inline iterator end()   const { return m_data+size(); };
};

//======================================================================
// ddcVMMap
/** convenience wrapper for mapping fixed-width record-based files as char* */
class ddcVMMap : public ddcMMap<char>
{
public:
    //----------------------------------------------------------
    // typedefs
    typedef ddcMMap<char> MMapT;

public:
    //----------------------------------------------------------
    // data
    size_t   m_recsize;  ///< number of bytes per record

public:
    //----------------------------------------------------------
    // constructors etc.

    /// default constructor
    ddcVMMap()
	: m_recsize(0)
    {};

    ddcVMMap(const std::string& filename, size_t recsize, int mode=O_RDONLY)
	: m_recsize(0)
    { open(filename,recsize,mode); };

    /// default destructor calls close()
    ~ddcVMMap()
    { close(); };

public:
    //----------------------------------------------------------
    // accessors

    /// returns the size of a single record in bytes
    inline size_t recsize() const
    { return m_recsize; };

public:
    //----------------------------------------------------------
    // high-level properties

    /// override returns the number of records mapped
    inline size_t size() const
    { return MMapT::size() / recsize(); };

    /// STL-esque wrapper for (size()==0)
    inline bool empty() const
    { return size() == 0; };

public:
    //----------------------------------------------------------
    // typecast operators

    /// implicit typecast to bool
    inline operator bool() const
    { return opened(); };
    
    /// indexing operator (gets start of row)
    inline void* operator[](size_t idx) const
    { return (void*) (m_data + idx*m_recsize); };

public:
    //----------------------------------------------------------
    // guts

    /// map a named file \a filename
    ddcVMMap& open(const std::string& filename, size_t recsize, int mode=O_RDONLY)
    {
	MMapT::open(filename,mode);
	assert( (ddcMMap<char>::nbytes() % recsize) == 0);
	m_recsize = recsize;
	return *this;
    };

    /// unmap current file (if any)
    void close()
    {
	MMapT::close();
	m_recsize = 0;
    };

    //----------------------------------------------------------
    // iterators
    template <typename IT>
    struct iteratorT
    {
	typedef IT        value_type;
	typedef ptrdiff_t difference_type;
	typedef IT*       pointer;
	typedef IT&       reference;
	typedef std::random_access_iterator_tag iterator_category;

	const ddcVMMap* m_obj;
	IT*             m_cur;

	iteratorT(const ddcVMMap *obj, IT *cur)
	    : m_obj(obj), m_cur(cur)
	{};

	template <typename srcIteratorT> //-- for implicit const/non-const conversions
	iteratorT(const srcIteratorT& i)
	    : m_obj(i.m_obj), m_cur(i.m_cur)
	{};

	//-- utils
	inline IT*       beg_() const { return m_obj->MMapT::begin(); };
	inline IT*       end_() const { return m_obj->MMapT::end(); };
	inline size_t    recsize_() const { return m_obj->m_recsize; };

	//-- api
	iteratorT& operator=(const iteratorT& i)
	{ m_obj=i.m_obj; m_cur=i.m_cur; return *this; };

	inline iteratorT& operator++() { m_cur = min(m_cur+recsize_(), end_()); return *this; };
	inline iteratorT& operator--() { m_cur = max(m_cur-recsize_(), beg_()); return *this; };

	inline iteratorT& operator++(int) { iteratorT i(*this); ++i; return i; };
	inline iteratorT& operator--(int) { iteratorT i(*this); --i; return i; };

	inline IT& operator*() const { return *m_cur; };
	inline IT* operator->() const { return m_cur; };

	//-- generic pointer-dereference
	template <typename PtrT>
	inline operator PtrT*() const { return (PtrT*)(m_cur); };

	inline bool operator==(const iteratorT& i) { return m_cur == i.m_cur; };
	inline bool operator!=(const iteratorT& i) { return m_cur != i.m_cur; };
	inline bool operator< (const iteratorT& i) { return m_cur < i.m_cur; };
	inline bool operator> (const iteratorT& i) { return m_cur > i.m_cur; };
	inline bool operator<=(const iteratorT& i) { return m_cur <= i.m_cur; };
	inline bool operator>=(const iteratorT& i) { return m_cur >= i.m_cur; };

	inline iteratorT& operator+=(size_t n) { m_cur = min(m_cur+n*recsize_(), end_()); return *this; };
	inline iteratorT& operator-=(size_t n) { m_cur = max(m_cur-n*recsize_(), beg_()); return *this; };

	inline iteratorT  operator+(size_t n)  { iteratorT i(*this); i += n; return i; };
	inline iteratorT  operator-(size_t n)  { iteratorT i(*this); i -= n; return i; };

	inline ptrdiff_t operator-(const iteratorT& i) { return (m_cur - i.m_cur) / recsize_(); };
    };

    typedef iteratorT<char>       iterator;
    typedef iteratorT<const char> const_iterator;

    inline iterator begin() { return iterator(this, MMapT::begin()); };
    inline iterator end()   { return iterator(this, MMapT::end()); };

    inline const_iterator begin() const { return const_iterator(this, MMapT::begin()); };
    inline const_iterator end()   const { return const_iterator(this, MMapT::end()); };
};


//======================================================================
// ddcVecFile<T>
/** slurp or mmap an array of <T> to memory.
 *  uses either ReadVector(...,vector<T>) ("slurp") or ddcMMap<T> ("mmap")
 */
template<typename T>
class ddcVecFile
{
public:
    ddcMMap<T> m_mmap;      ///< data (mmap)
    vector<T>  m_vec;       ///< data (slurp)
    T         *m_data;      ///< data (pointer to m_mmap or m_vec data)
    
    //----------------------------------------------------------
    // constructors etc.

    /// default constructor
    ddcVecFile()
	: m_data(NULL)
    {};

    /// construct and open
    ddcVecFile(const std::string& filename, bool useMMap=false)
	: m_data(NULL)
    { open(filename,useMMap); };

    /// default destructor calls close()
    ~ddcVecFile()
    { close(); };

    /// clear() method wraps close()
    inline void clear()
    { close(); };

    //----------------------------------------------------------
    // accessors & high-level properties

    /// returns a pointer to the mmap()ed file data, or NULL
    inline T* data() const
    { return m_data; };

    /// returns the number of objects of type T in this vector, or 0
    inline size_t size() const
    { return m_mmap ? m_mmap.size() : m_vec.size(); };

    /// STL-esque wrapper
    inline bool empty() const
    { return m_mmap ? m_mmap.empty() : m_vec.empty(); };

    /// returns true iff m_data is non-NULL
    inline bool opened() const 
    { return (m_data != NULL); };

    //----------------------------------------------------------
    // typecasts and operators

    /// implicit typecast to bool
    inline operator bool() const
    { return opened(); };
    
    /// implicit typecast to T*
    inline operator T*() const
    { return m_data; };

    /// indexing operator
    inline T& operator[](size_t idx) const
    { return m_data[idx]; };

    //----------------------------------------------------------
    // high-level manipulation

    /// simulate vector::push_back(): used by indexing routines
    inline void push_back(const T& value)
    {
	ensureVec();
	m_vec.push_back(value);
    };
  
    //----------------------------------------------------------
    // STL-esque iterators

    typedef T*       iterator;
    typedef const T* const_iterator;

    inline iterator begin() const { return m_data; };
    inline iterator end()   const { return m_data+size(); };
    
    //----------------------------------------------------------
    // guts

    /// map a named file \a filename
    ddcVecFile& open(const std::string& filename, bool useMMap=false)
    {
	if (opened()) close();
	if (useMMap) {
	    //-- mmap mode
	    ddcLogTrace("ddcVecFile[mmap]::open("+filename+")");
	    m_mmap.open(filename, O_RDONLY);
	    m_data = m_mmap.m_data;
	} else {
	    //-- slurp mode
	    ddcLogTrace("ddcVecFile[slurp]::open("+filename+")");
	    ReadVector(filename, m_vec);
	    m_data = &(m_vec[0]);
	}
	return *this;
    };

    /// unmap current file (if any)
    void close()
    {
	m_mmap.close();
	ClearVector(m_vec);
	m_data = NULL;
    };


    /// force vector-implementation
    void ensureVec()
    {
	if (m_mmap) {
	    ClearVector(m_vec);
	    m_vec.reserve(size());
	    m_vec.insert(m_vec.begin(), m_mmap.m_data, m_mmap.m_data+m_mmap.size());
	    m_mmap.close();
	    m_data = &(m_vec[0]);
	}
    };

};


//======================================================================
// ddcVMapFile<KeyT,ValT>
/** slurp or mmap a map<KeyT,ValT> to memory; records should be stored as {KeyT,ValT[]} and sorted in ascending order by key */
template<typename KeyT, typename ValT>
class ddcVMapFile
{
public:
    //----------------------------------------------------------
    // typedefs
    typedef ddcVMMap                    VMapT;
    typedef vector<ValT>                VecT;
    typedef map<KeyT,VecT>              MapT;

    typedef KeyT 			key_type;
    typedef VecT	      	        mapped_type;
    typedef pair<KeyT,VecT>             value_type;

    struct RecordT {
	const KeyT*  m_key;
	ValT*        m_vals;

	RecordT()
	    : m_key(NULL), m_vals(NULL)
	{};
	
	RecordT(const KeyT& key_, ValT* vals_=NULL)
	{ assign(key_,vals_); };

	~RecordT()
	{};

	inline RecordT& assign(const KeyT& key_, ValT* vals_)
	{ m_key = &key_; m_vals = vals_; return *this; };

	inline RecordT& assign(const char *data)
	{ return assign( *((const KeyT*)data),  (ValT*)(data+sizeof(KeyT)) ); };

	inline RecordT& assign(const typename MapT::iterator& mapi)
	{ return assign(mapi->first, &(mapi->second[0])); };

	inline RecordT& assign(const typename MapT::const_iterator& mapi)
	{ return assign(mapi->first, (ValT*)&(mapi->second[0])); };

	inline bool operator<(const KeyT& key) const
	{ return *m_key < key; };

	inline const KeyT& key() const
	{ return *m_key; };

	inline const ValT* vals() const
	{ return m_vals; };

	inline ValT* vals()
	{ return m_vals; };
    };

public:
    //----------------------------------------------------------
    // data
    VMapT    m_vmap;            ///< data (mmap)
    MapT     m_map;             ///< data (slurp)
    size_t   m_vsize;           ///< number of elements per value-vector

public:
    //----------------------------------------------------------
    // constrcutors etc

    // default constructor
    ddcVMapFile()
	: m_vsize(0)
    {};

    /// construct and open
    ddcVMapFile(const std::string& filename, size_t vsize_, bool useMMap=false)
	: m_vsize(0)
    { open(filename,vsize_,useMMap); };

    /// default destructor calls close()
    ~ddcVMapFile()
    { close(); };
  
    /// clear() method wraps close()
    inline void clear()
    { close(); };

public:
    //----------------------------------------------------------
    // accessors & properties

    /// returns the number of bytes per record
    inline size_t recsize() const
    { return sizeof(KeyT) + m_vsize*sizeof(ValT); };

    /// returns the number of elements per value-vector
    inline size_t vecsize() const
    { return m_vsize; };
    
    /// returns the number of records in this object
    inline size_t size() const
    { return m_vmap ? m_vmap.size() : m_map.size(); };

    /// STL-esque wrapper
    inline bool empty() const
    { return size()==0; };

    /// returns true iff object is opened (or non-empty)
    inline bool opened() const 
    { return m_vmap ? m_vmap.opened() : !m_map.empty(); };

    //----------------------------------------------------------
    // typecasts and operators

    /// implicit typecast to bool
    inline operator bool() const
    { return opened(); };

    /// indexing operator auto-demotes to slurp-mode
    inline VecT& operator[](const KeyT& key)
    {
	ensureMap();
	return m_map[key];
    };

public:
    //----------------------------------------------------------
    // iterators : n/a
    template<typename MMapIT, typename MapIT>
    struct iteratorT
    {
	//-- typedefs
	typedef RecordT             value_type;
	typedef ptrdiff_t           difference_type;
	typedef value_type*         pointer;
	typedef value_type&         reference;
	typedef std::bidirectional_iterator_tag iterator_category;

	//--- data
	const ddcVMapFile<KeyT,ValT>* m_obj;
	MMapIT                          m_vmi;
	MapIT                           m_mi;
	RecordT                         m_rec;

	//-- constructors etc
	iteratorT(const ddcVMapFile<KeyT,ValT> *obj, MMapIT mmi, const MapIT& mi)
	    : m_obj(obj), m_vmi(mmi), m_mi(mi)
	{};

	template <typename srcIteratorT> //-- for implicit const/non-const conversions
	iteratorT(const srcIteratorT& i)
	    : m_obj(i.m_obj), m_vmi(i.m_vmi), m_mi(i.m_mi)
	{};
	
	~iteratorT()
	{};

	//-- utilities
	inline void update_()
	{ if (m_obj->m_vmap) m_rec.assign(m_vmi); else m_rec.assign(m_mi); };

	template <typename srcIteratorT>
	inline iteratorT& operator=(const srcIteratorT& i)
	{ m_obj=i.m_obj; m_vmi=i.m_vmi; m_mi=i.m_mi; return *this; };

	inline iteratorT& operator++() { if (m_obj->m_vmap) ++m_vmi; else ++m_mi; return *this; };
	inline iteratorT& operator--() { if (m_obj->m_vmap) --m_vmi; else --m_mi; return *this; };

	inline iteratorT& operator++(int) { iteratorT i(*this); ++i; return i; };
	inline iteratorT& operator--(int) { iteratorT i(*this); --i; return i; };

	inline reference operator*()  { update_(); return  m_rec; };
	inline pointer   operator->() { update_(); return &m_rec; };

	inline bool operator==(const iteratorT& i) { return m_obj->m_vmap ? (m_vmi == i.m_vmi) : (m_mi == i.m_mi); };
	inline bool operator!=(const iteratorT& i) { return m_obj->m_vmap ? (m_vmi != i.m_vmi) : (m_mi != i.m_mi); };
	inline bool operator< (const iteratorT& i) { return m_obj->m_vmap ? (m_vmi <  i.m_vmi) : (m_mi <  i.m_mi); };
	inline bool operator> (const iteratorT& i) { return m_obj->m_vmap ? (m_vmi >  i.m_vmi) : (m_mi >  i.m_mi); };
	inline bool operator<=(const iteratorT& i) { return m_obj->m_vmap ? (m_vmi <= i.m_vmi) : (m_mi <= i.m_mi); };
	inline bool operator>=(const iteratorT& i) { return m_obj->m_vmap ? (m_vmi >= i.m_vmi) : (m_mi >= i.m_mi); };

	inline iteratorT& operator+=(size_t n) { if (m_obj->m_vmap) m_vmi += n; else m_mi += n; return *this; };
	inline iteratorT& operator-=(size_t n) { if (m_obj->m_vmap) m_vmi -= n; else m_mi -= n; return *this; };

	inline iteratorT  operator+(size_t n)  { iteratorT i(*this); i += n; return i; };
	inline iteratorT  operator-(size_t n)  { iteratorT i(*this); i -= n; return i; };

	inline ptrdiff_t operator-(const iteratorT& i) { return m_obj->m_vmap ? (m_vmi - i.m_vmi) : (m_mi - i.m_mi); };
    };

    typedef iteratorT< typename VMapT::iterator,       typename MapT::iterator >       iterator;
    typedef iteratorT< typename VMapT::const_iterator, typename MapT::const_iterator > const_iterator;

    inline iterator begin() { return iterator(this, m_vmap.begin(), m_map.begin()); };
    inline iterator end()   { return iterator(this, m_vmap.end(),   m_map.end()); };

    inline const_iterator begin() const { return const_iterator(this, m_vmap.begin(), m_map.begin()); };
    inline const_iterator end()   const { return const_iterator(this, m_vmap.end(),   m_map.end()); };

public:
    //----------------------------------------------------------
    // searching

    struct KeyLess {
	inline bool operator()(const RecordT &rec, const KeyT& key)
	{
	    //fprintf(stderr, "COMPARE(%d, %d)\n", rec.key(), key);
	    return rec.key() < key;
	};
    };

    
    /// simulate std::map::find()
    inline const_iterator find(const KeyT& key) const
    {
	if (m_vmap) {
	    const_iterator lb = lower_bound(begin(), end(), key, KeyLess());
	    return (lb != end() && lb->key() == key) ? lb : end();
	} else {
	    typename MapT::const_iterator lb = m_map.find(key);
	    return const_iterator(this, m_vmap.end(), lb);
	}
    };

    
public:
    //----------------------------------------------------------
    // guts
    ddcVMapFile& open(const std::string& filename, size_t vsize, bool useMMap=false)
    {
      if (opened()) close();
      m_vsize = vsize;
      if (useMMap) {
	//-- mmap mode
	ddcLogTrace("ddcVMapFile[mmap]::open("+filename+")");
	m_vmap.open(filename, sizeof(KeyT)+vsize*sizeof(ValT), O_RDONLY);
      } else {
	//-- slurp mode, adapted from CIndexSetForQueryingStage::LoadPeriodDevision()
	ddcLogTrace("ddcVMapFile[slurp]::open("+filename+")");
	FILE *fp = fopen(filename.c_str(), "rb");
	if (!fp)
	  throw invalid_argument(Format("ddcVMapFile::open(): open failed for '%s': %s",filename.c_str(),strerror(errno)));

	size_t fsize = FileSize(filename.c_str());
	size_t nrecs = fsize / recsize();
	assert((fsize % recsize()) == 0);

	for (size_t i=0; i < nrecs; ++i) {
	  KeyT key;
	  if (fread(&key,sizeof(KeyT),1,fp) != 1)
	    throw runtime_error(Format("ddcVMapFile::open(): failed to read key from %s: %s",filename.c_str(),strerror(errno)));
	  typename MapT::iterator it = m_map.insert(make_pair(key,VecT())).first;
	  it->second.reserve(m_vsize);
	  ReadVectorInner(fp, it->second, m_vsize);
	  if (it->second.size() != m_vsize)
	    throw runtime_error(Format("ddcVMapFile::open(): failed to read values from %s: %s",filename.c_str(),strerror(errno)));
	}
	fclose(fp);
      }
      return *this;
    };

    inline void close()
    {
      m_vmap.close();
      m_map.clear();
      m_vsize = 0;
    };

    /// force map-implementation
    void ensureMap()
    {
	if (m_vmap) {
	  m_map.clear();
	  for (const_iterator i=begin(); i != end(); ++i) {
	    const KeyT &key  = i->key();
	    const ValT *vals = i->vals();
	    typename MapT::iterator it = m_map.insert(make_pair(key,VecT())).first;
	    it->second.reserve(m_vsize);
	    it->second.assign(vals, vals+m_vsize);
	  }
	  m_vmap.close();
	}
    };
};



#endif /* DDC_MMAP_H */
