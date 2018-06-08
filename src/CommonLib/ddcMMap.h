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
struct ddcMMap
{
    std::string  m_file;    ///< underlying filename
    size_t       m_nbytes;  ///< number of bytes mapped
    T           *m_data;    ///< file data

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

    //----------------------------------------------------------
    // typecast operators

    /// implicit typecast to bool
    inline operator bool() const
    { return opened(); };
    
    /// implicit typecast to T*
    inline operator T*() const
    { return m_data; };

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
    
};

//======================================================================
// ddcVecFile<T>
/** slurp or map an array of <T> to memory.
 *  uses either and ReadVector(...,vector<T>) ("slurp") or ddcMMap<T> ("mmap")
 */
template<typename T>
struct ddcVecFile
{
    string     m_file;     ///< data source filename
    ddcMMap<T> m_map;      ///< data (mmap)
    vector<T>  m_vec;      ///< data (slurp)
    T         *m_data;     ///< data (pointer to m_mmap or m_vec data)
    
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
    // accessors

    /// returns the name of the currently mapped file, if any
    inline const std::string& filename() const
    { return m_file; };

    /// returns a pointer to the mmap()ed file data, or NULL
    inline T* data() const
    { return m_data; };

    //----------------------------------------------------------
    // high-level properties

    /// returns the number of objects of type T in this vector, or 0
    inline size_t size() const
    { return m_map ? m_map.size() : m_vec.size(); };
    
    /// STL-esque wrapper for (nbytes()==0)
    inline bool empty() const
    { return m_map ? m_map.empty() : m_vec.empty(); };

    /// returns true iff m_data is non-NULL
    inline bool opened() const 
    { return m_map ? m_map.opened() : !m_file.empty(); };

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

    /// used by indexing routines
    inline void push_back(const T& value)
    {
	ensureVec();
	m_vec.push_back(value);
    };
  
    //----------------------------------------------------------
    // STL-esque iterators
    /// returns true iff m_data is non-NULL

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
	m_file = filename;
	if (useMMap) {
	    //-- mmap mode
	    ddcLogTrace("ddcVecFile[mmap]::open("+m_file+")");
	    m_map.open(filename, O_RDONLY);
	    m_data = m_map.m_data;
	} else {
	    //-- vector mode
	    ddcLogTrace("ddcVecFile[slurp]::open("+m_file+")");
	    ReadVector(filename, m_vec);
	    m_data = &(m_vec[0]);
	}
	return *this;
    };

    /// unmap current file (if any)
    void close()
    {
	m_map.close();
	ClearVector(m_vec);
	ClearString(m_file);
	m_data = NULL;
    };


    /// force vector-implementation
    void ensureVec()
    {
	if (m_map) {
	    ClearVector(m_vec);
	    m_vec.reserve(size());
	    m_vec.insert(m_vec.begin(), m_map.m_data, m_map.m_data+m_map.size());
	    m_map.close();
	    m_data = &(m_vec[0]);
	}
    };

};

//======================================================================
// ddcVec2dFile<T>
/**
 * slurp or map an array-of-arrays of <T> to memory
 * uses either and ReadVector(...,vector<T>) ("slurp") or ddcMMap<T> ("mmap")
 */
template<typename T>
struct ddcVec2dFile : public ddcVecFile<T>
{
    //----------------------------------------------------------
    // typedefs
    typedef ddcVecFile<T>               VecFileT;
    typedef typename VecFileT::iterator row_iterator;

    //----------------------------------------------------------
    // data
    size_t m_ncols;  ///< number of "columns" in the file

    //----------------------------------------------------------
    // constructors etc.
    ddcVec2dFile()
	: m_ncols(0)
    {};

    ddcVec2dFile(const std::string& filename, size_t ncols, bool useMMap=false)
	: m_ncols(ncols)
    { open(filename,ncols,useMMap); };

    ~ddcVec2dFile()
    { close(); };

    inline void clear()
    { close(); };

    //----------------------------------------------------------
    // access

    /// size() wraps nrows
    inline size_t nelts() const
    { return VecFileT::size(); };

    inline size_t nrows() const
    { return nelts() / m_ncols; };

    inline size_t ncols() const
    { return m_ncols; };
   
    /// size() wraps nrows
    inline size_t size() const
    { return nrows(); };

    /// indexing operator
    inline T* operator[](size_t rowi) const
    { return &VecFileT::m_data[rowi*m_ncols]; };

    /// 2d indexing operator
    inline T& at(size_t rowi, size_t coli) const
    { return VecFileT::m_data[rowi*m_ncols + coli]; };
    
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

	const ddcVec2dFile<T>* m_obj;
	IT*                    m_cur;

	iteratorT(const ddcVec2dFile<T> *obj, IT *cur)
	    : m_obj(obj), m_cur(cur)
	{};
	iteratorT(const iteratorT& i)
	    : m_obj(i.m_obj), m_cur(i.m_cur)
	{};

	//-- utils
	inline IT*    beg_() const { return m_obj->VecFileT::begin(); };
	inline IT*    end_() const { return m_obj->VecFileT::end(); };
	inline size_t ncols_() const { return m_obj->m_ncols; };
	inline ptrdiff_t pos_() const { return m_cur - beg_(); };
	inline ptrdiff_t rowi_() const { return pos_() / ncols_(); };
	inline ptrdiff_t coli_() const { return pos_() % ncols_(); };

        inline row_iterator rowbegin() const { return beg_() + rowi_()*ncols_(); };
        inline row_iterator rowend  () const { return rowbegin() + ncols_(); };

	//-- api
	iteratorT& operator=(const iteratorT& i)
	{ m_obj=i.m_obj; m_cur=i.m_cur; return *this; };

	inline iteratorT& operator++() { m_cur = min(m_cur+ncols_(), end_()); return *this; };
	inline iteratorT& operator--() { m_cur = max(m_cur-ncols_(), beg_()); return *this; };

	inline iteratorT& operator++(int) { iteratorT i(*this); ++i; return i; };
	inline iteratorT& operator--(int) { iteratorT i(*this); --i; return i; };

	inline IT& operator*() const { return *m_cur; };
	inline IT* operator->() const { return m_cur; };

	inline bool operator==(const iteratorT& i) { return m_cur == i.m_cur; };
	inline bool operator!=(const iteratorT& i) { return m_cur != i.m_cur; };
	inline bool operator< (const iteratorT& i) { return m_cur < i.m_cur; };
	inline bool operator> (const iteratorT& i) { return m_cur > i.m_cur; };
	inline bool operator<=(const iteratorT& i) { return m_cur <= i.m_cur; };
	inline bool operator>=(const iteratorT& i) { return m_cur >= i.m_cur; };

	inline iteratorT& operator+=(size_t n) { m_cur = min(m_cur+n*ncols_(), end_()); return *this; };
	inline iteratorT& operator-=(size_t n) { m_cur = max(m_cur-n*ncols_(), beg_()); return *this; };

	inline iteratorT  operator+(size_t n)  { iteratorT i(*this); i += n; return i; };
	inline iteratorT  operator-(size_t n)  { iteratorT i(*this); i -= n; return i; };

	inline ptrdiff_t operator-(const iteratorT& i) { return (m_cur - i.m_cur) / ncols_(); };
    };

    typedef iteratorT<      T> iterator;
    typedef iteratorT<const T> const_iterator;

    inline iterator begin() const { return iterator(this, VecFileT::begin()); };
    inline iterator end()   const { return iterator(this, VecFileT::end()); };

    inline row_iterator rowbegin(size_t rowi) const { return VecFileT::begin() + rowi*m_ncols; };
    inline row_iterator rowend  (size_t rowi) const { return rowbegin(0) + m_ncols; };

    //----------------------------------------------------------
    // guts
    ddcVec2dFile& open(const std::string& filename, size_t ncols, bool useMMap=false)
    {
	VecFileT::open(filename,useMMap);
	assert(ncols > 0);
	assert((VecFileT::size() % ncols) == 0);
	m_ncols = ncols;
	return *this;
    };

    inline void close()
    {
	VecFileT::close();
	m_ncols = 0;
    };
};

//======================================================================
// ddcVecMapFile<T>
/**
 * wrapper for ddcVec2dFile assuming single-object keys, data sorted in ascending order by key
 */
template<typename T>
struct ddcVecMapFile : public ddcVec2dFile<T>
{
    //----------------------------------------------------------
    // typedefs
    typedef          ddcVec2dFile<T>             Vec2dFileT;
    typedef typename Vec2dFileT::iterator        iterator;
    typedef typename Vec2dFileT::const_iterator  const_iterator;
    
    typedef          ddcVecFile<T>               VecFileT;
    typedef typename VecFileT::iterator          row_iterator;

    //----------------------------------------------------------
    // constructors etc.
    ddcVecMapFile()
    {};

    ddcVecMapFile(const std::string& filename, size_t ncols, bool useMMap=false)
    { open(filename,ncols,useMMap); };

    ~ddcVecMapFile()
    { close(); };

    inline void clear()
    { close(); };

    //----------------------------------------------------------
    // iterators

    inline iterator begin() const { return Vec2dFileT::begin(); };
    inline iterator end()   const { return Vec2dFileT::end(); };

    inline row_iterator rowbegin(size_t rowi) const { return Vec2dFileT::rowbegin(rowi); };
    inline row_iterator rowend  (size_t rowi) const { return Vec2dFileT::rowend(rowi); };
    
    //----------------------------------------------------------
    // searching

    struct KeyLessDebug
    {
	bool operator()(const T& a, const T& b) const
	{
	    fprintf(stderr, "\n COMPARE(%d,%d)", a,b);
	    return (a < b);
	};
    };
    
    /// simulate map::find()
    inline iterator find(const T& key) const
    {
	//KeyLessDebug less;
	iterator lb = lower_bound(begin(), end(), key);
	if (lb != end() && *lb==key) return lb;
	return end();
    };

    /// indexing operator gets values for key
    inline row_iterator operator[](size_t key) const
    { return find(key).rowbegin() + 1; };

    //----------------------------------------------------------
    // guts
    ddcVecMapFile& open(const std::string& filename, size_t ncols, bool useMMap=false)
    {
	Vec2dFileT::open(filename,ncols,useMMap);
	return *this;
    };

    inline void close()
    { Vec2dFileT::close(); };
};

	
#endif /* DDC_MMAP_H */
