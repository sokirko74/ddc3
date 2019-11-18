//-*- Mode: C++ -*-
//
//  Copyright 2018-2019 by Bryan Jurish
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

#include "ddcConfig.h"

#endif

#include "bserialize.h"
#include "utilit.h"
#include "ddcLog.h"
#include "ddcThread.h"
#include <string>
#include <stdexcept>
#include <algorithm>

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#if HAVE_SYS_STAT_H

#include <sys/stat.h> /* fstat */

#endif

#if HAVE_SYS_MMAN_H

#include <sys/mman.h> /* mmap */

#endif

//======================================================================
// ddcMMap
/** convenience wrapper for mapping entire files into virtual memory using mmap() */
template<typename T=char>
class ddcMMap {
public:
    //----------------------------------------------------------
    // data
    std::string m_file;    ///< underlying filename
    size_t m_nbytes;  ///< number of bytes mapped
    T *m_data;    ///< file data

public:
    //----------------------------------------------------------
    // constructors etc.

    /// default constructor
    ddcMMap()
        : m_nbytes(0), m_data(NULL) {};

    ddcMMap(const std::string &filename, int mode = O_RDONLY)
        : m_nbytes(0), m_data(NULL) { open(filename, mode); };

    /// default destructor calls close()
    ~ddcMMap() { close(); };

public:
    //----------------------------------------------------------
    // accessors

    /// returns the name of the currently mapped file, if any
    inline const std::string &filename() const { return m_file; };

    /// returns number of bytes mapped, or 0
    inline size_t nbytes() const { return m_nbytes; };

    /// returns a pointer to the mmap()ed file data, or NULL
    inline T *data() const { return m_data; };

public:
    //----------------------------------------------------------
    // high-level properties

    /// returns the number of objects of type T mapped, or 0
    inline size_t size() const { return m_nbytes / sizeof(T); };

    /// STL-esque wrapper for (nbytes()==0)
    inline bool empty() const { return m_nbytes == 0; };

    /// returns true iff m_data is non-NULL
    inline bool opened() const { return m_data != NULL; };

public:
    //----------------------------------------------------------
    // typecast operators

    /// implicit typecast to bool
    inline operator bool() const { return opened(); };

    /// implicit typecast to T*
    inline operator T *() const { return m_data; };

    /// indexing operator
    inline T &operator[](size_t idx) const { return m_data[idx]; };

public:
    //----------------------------------------------------------
    // guts

    /// map a named file \a filename
    ddcMMap &open(const std::string &filename, int mode = O_RDONLY) {
        if (opened()) close();
        //ddcLogTrace("ddcMMap::open("+filename+")");
        m_file = filename;

        //-- open the file (temporarily)
        int mmfd = ::open(filename.c_str(), mode);
        if (mmfd == -1)
            throw std::invalid_argument(
                Format("ddcMMap::open(): open failed for '%s': %s", filename.c_str(), strerror(errno)));

        //-- get total file size
        struct stat statbuf;
        if (fstat(mmfd, &statbuf) != 0)
            throw std::runtime_error(
                Format("ddcMMap::open(): fstat() failed for file '%s': %s", filename.c_str(), strerror(errno)));
        m_nbytes = statbuf.st_size;

        if (m_nbytes > 0) {
#if DDC_ENABLE_MMAP
            //-- get mmap protection flags
            int mmprot = 0;
            switch (mode) {
                case O_RDONLY:
                    mmprot = PROT_READ;
                    break;
                case O_WRONLY:
                    mmprot = PROT_WRITE;
                    break;
                case O_RDWR:
                    mmprot = (PROT_READ | PROT_WRITE);
                    break;
                default:
                    throw std::invalid_argument(Format("ddcMMap::open(): unknown open mode '%d'", mode));
            }

            //-- underlying mmap call
            m_data = (T *) mmap(NULL, m_nbytes, mmprot, MAP_SHARED, mmfd, 0);
            if (m_data == MAP_FAILED)
                throw std::runtime_error(
                    Format("ddcMMap::open(): mmap() failed for file '%s': %s", filename.c_str(), strerror(errno)));

#else // !DDC_HAVE_MMAP

            ddcLogWarn("ddcMMap::open(): Warning: mmap support unavailable, loading into resident memory");

            m_data = (T*)malloc(m_nbytes);
            if (m_data == NULL)
                throw std::runtime_error(Format("ddcMap::open(): failed to allocate memory for file '%s'", filename.c_str()));
            if (read(mmfd, m_data, m_nbytes) != m_nbytes)
                throw std::runtime_error(Format("ddcMap::open(): failed read data for file '%s'", filename.c_str()));

#endif // DDC_HAVE_MMAP
        }

        //-- we can now safely close the fd
        if (::close(mmfd) != 0)
            throw std::runtime_error(
                Format("ddcMMap::open(): close() failed for file '%s': %s", filename.c_str(), strerror(errno)));

        return *this;
    };

    /// unmap current file (if any)
    void close() {
        if (m_data != NULL) {
            //ddcLogTrace("ddcMMap::close("+m_file+")");
#if DDC_ENABLE_MMAP
            if (munmap(m_data, m_nbytes) != 0)
                throw std::runtime_error(
                    Format("ddcMMap::close(): munmap() failed for file '%s': %s", m_file.c_str(), strerror(errno)));
#else
            free(m_data);
#endif
        }
        ClearString(m_file);
        m_data = NULL;
        m_nbytes = 0;
    };

public:
    //----------------------------------------------------------
    // STL-style iterators

    typedef T *iterator;
    typedef const T *const_iterator;

    inline iterator begin() const { return m_data; };

    inline iterator end() const { return m_data + size(); };
};


//======================================================================
// ddcVecFile<T>
/** slurp or mmap an array of <T> to memory.
 *  uses either ReadVector(...,vector<T>) ("slurp") or ddcMMap<T> ("mmap")
 */
template<typename T>
class ddcVecFile {
public:
    typedef ddcMMap<T> MMapT;
    typedef vector<T> VecT;
    typedef T EltT;

public:
    string m_file;      ///< filename (if any)
    ddcMMap<T> m_mmap;      ///< data (mmap)
    vector<T> m_vec;       ///< data (slurp)
    T *m_data;      ///< data (pointer to m_mmap or m_vec data)

    //----------------------------------------------------------
    // constructors etc.

    /// default constructor
    ddcVecFile()
        : m_data(NULL) {};

    /// construct and open
    ddcVecFile(const std::string &filename, bool useMMap = false)
        : m_data(NULL) { open(filename, useMMap); };

    /// default destructor calls close()
    ~ddcVecFile() { close(); };

    /// clear() method wraps close()
    inline void clear() { close(); };

    //----------------------------------------------------------
    // accessors & high-level properties

    /// returns filename of last open(), or NULL
    inline const string &filename() const { return m_file; };

    /// returns a pointer to the mmap()ed file data, or NULL
    inline T *data() const { return m_data; };

    /// returns the number of objects of type T in this vector, or 0
    inline size_t size() const { return m_mmap ? m_mmap.size() : m_vec.size(); };

    /// STL-esque wrapper
    inline bool empty() const { return m_mmap ? m_mmap.empty() : m_vec.empty(); };

    /// returns true iff m_data is non-NULL
    inline bool opened() const { return (m_data != NULL); };

    //----------------------------------------------------------
    // typecasts and operators

    /// implicit typecast to bool
    inline operator bool() const { return opened(); };

    /// implicit typecast to T*
    inline operator T *() const { return m_data; };

    /// indexing operator
    inline T &operator[](size_t idx) const { return m_data[idx]; };

    //----------------------------------------------------------
    // high-level manipulation

    /// simulate vector::push_back(): used by indexing routines
    inline void push_back(const T &value) {
        ensureVec();
        m_vec.push_back(value);
    };

    //----------------------------------------------------------
    // STL-esque iterators

    typedef T *iterator;
    typedef const T *const_iterator;

    inline iterator begin() { return m_data; };

    inline iterator end() { return m_data + size(); };

    inline const_iterator begin() const { return m_data; };

    inline const_iterator end() const { return m_data + size(); };

    //----------------------------------------------------------
    // guts

    /// map a named file \a filename
    ddcVecFile &open(const std::string &filename, bool useMMap = false) {
        if (opened()) close();
        if (useMMap) {
            //-- mmap mode
            ddcLogTrace("ddcVecFile[mmap]::open(" + filename + ")");
            m_mmap.open(filename, O_RDONLY);
            m_data = m_mmap.m_data;
        } else {
            //-- slurp mode
            ddcLogTrace("ddcVecFile[slurp]::open(" + filename + ")");
            ReadVector(filename, m_vec);
            m_data = &(m_vec[0]);
        }
        m_file = filename;
        return *this;
    };

    /// unmap current file (if any)
    void close() {
        m_mmap.close();
        ClearVector(m_vec);
        m_data = NULL;
    };


    /// force vector-implementation
    void ensureVec() {
        if (m_mmap) {
            ddcLogWarn(
                Format("WARNING: ddcVecFile(\"%s\") demoting to std::vector<> implementation", filename().c_str()));
            ClearVector(m_vec);
            m_vec.reserve(size());
            m_vec.insert(m_vec.begin(), m_mmap.m_data, m_mmap.m_data + m_mmap.size());
            m_mmap.close();
            m_data = &(m_vec[0]); //-- always update this
        }
    };

    /// ensure data is a valid pointer
    inline void ensureData() {
        m_data = m_mmap ? m_mmap.m_data : &(m_vec[0]);
    };

    /// dump data to a FILE*
    void save(FILE *fp) const { save(fp, Format("<FILE=%p>", fp)); };

    /// dump to a named file
    void save(const string &FileName) const {
        FILE *fp = fopen(FileName.c_str(), "wb");
        if (!fp)
            throw CExpc("ddcVecFile<>::save(): open failed for file " + FileName);
        save(fp, FileName);
        if (fclose(fp) != 0)
            throw CExpc("ddcVecFile<>::save(): close failed for file " + FileName);
    };

    /// dump data to a FILE* with a symbolic name
    void save(FILE *fp, const string &name) const {
        if (!fp)
            throw CExpc("ddcVecFile<>::save(): invalid file pointer for " + name);
        const T *datap = m_mmap ? m_mmap.m_data : &(m_vec[0]);
        if (fwrite(datap, sizeof(T), (m_mmap ? m_mmap.size() : m_vec.size()), fp) != size())
            throw CExpc("ddcVecFile<>::save(): failed to write data to " + name);
    };

};

//======================================================================
// ddcRecFile
/** convenience wrapper for mapping arbitrary fixed-width record-based files as char* */
class ddcRecFile : public ddcVecFile<char> {
public:
    //----------------------------------------------------------
    // typedefs
    typedef ddcVecFile<char> VecFileT;
    typedef VecFileT::MMapT MMapT;
    typedef VecFileT::VecT VecT;

public:
    //----------------------------------------------------------
    // data
    size_t m_recsize;  ///< number of bytes per record

public:
    //----------------------------------------------------------
    // constructors etc.

    /// default constructor
    ddcRecFile()
        : m_recsize(0) {};

    ddcRecFile(const std::string &filename, size_t recsize, bool useMMap = false)
        : m_recsize(0) { open(filename, recsize, useMMap); };

    /// default destructor calls close()
    ~ddcRecFile() { close(); };

public:
    //----------------------------------------------------------
    // accessors

    /// returns the size of a single record in bytes
    inline size_t recsize() const { return m_recsize; };

public:
    //----------------------------------------------------------
    // high-level properties

    /// override returns the number of records mapped
    inline size_t size() const { return VecFileT::size() / recsize(); };

    /// STL-esque wrapper for (size()==0)
    inline bool empty() const { return size() == 0; };

public:
    //----------------------------------------------------------
    // typecast operators

    /// implicit typecast to bool
    inline operator bool() const { return opened(); };

    /// indexing operator (gets start of row)
    inline void *operator[](size_t idx) const { return (void *) (m_data + idx * m_recsize); };

public:
    //----------------------------------------------------------
    // guts

    /// map a named file \a filename
    ddcRecFile &open(const std::string &filename, size_t recsize, bool useMMap = false) {
        VecFileT::open(filename, useMMap);
        if ((VecFileT::size() % recsize) != 0)
            throw invalid_argument(
                Format("ddcRecFile::open(): error opening '%s': file size (%zd) is not a multiple of record size (%zd)",
                       filename.c_str(), VecFileT::size(), recsize));
        m_recsize = recsize;
        return *this;
    };

    /// unmap current file (if any)
    void close() {
        VecFileT::close();
        m_recsize = 0;
    };

    //----------------------------------------------------------
    // iterators
    template<typename ET>
    struct iteratorT {
        typedef ET value_type;
        typedef ptrdiff_t difference_type;
        typedef ET *pointer;
        typedef ET &reference;
        typedef std::random_access_iterator_tag iterator_category;

        const ddcRecFile *m_obj;
        ET *m_cur;

        iteratorT(const ddcRecFile *obj, ET *cur)
            : m_obj(obj), m_cur(cur) {};

        template<typename srcIteratorT>
        //-- for implicit const/non-const conversions
        iteratorT(const srcIteratorT &i)
            : m_obj(i.m_obj), m_cur(i.m_cur) {};

        //-- utils
        inline ET *beg_() const { return m_obj->VecFileT::begin(); };

        inline ET *end_() const { return m_obj->VecFileT::end(); };

        inline size_t recsize_() const { return m_obj->m_recsize; };

        //-- utils for (key,val) pair files
        template<typename KeyT>
        inline const KeyT &key() const { return *((const KeyT *) m_cur); };

        template<typename KeyT, typename ValT>
        inline const ValT *val() const { return (const ValT *) (((const char *) m_cur) + sizeof(KeyT)); };

        //-- api
        iteratorT &operator=(const iteratorT &i) {
            m_obj = i.m_obj;
            m_cur = i.m_cur;
            return *this;
        };

        inline iteratorT &operator++() {
            m_cur = min(m_cur + recsize_(), end_());
            return *this;
        };

        inline iteratorT &operator--() {
            m_cur = max(m_cur - recsize_(), beg_());
            return *this;
        };

        inline iteratorT &operator++(int) {
            iteratorT i(*this);
            ++i;
            return i;
        };

        inline iteratorT &operator--(int) {
            iteratorT i(*this);
            --i;
            return i;
        };

        inline ET &operator*() const { return *m_cur; };

        inline ET *operator->() const { return m_cur; };

        //-- generic pointer-dereference
        template<typename PtrT>
        inline operator PtrT *() const { return (PtrT *) (m_cur); };

        inline bool operator==(const iteratorT &i) { return m_cur == i.m_cur; };

        inline bool operator!=(const iteratorT &i) { return m_cur != i.m_cur; };

        inline bool operator<(const iteratorT &i) { return m_cur < i.m_cur; };

        inline bool operator>(const iteratorT &i) { return m_cur > i.m_cur; };

        inline bool operator<=(const iteratorT &i) { return m_cur <= i.m_cur; };

        inline bool operator>=(const iteratorT &i) { return m_cur >= i.m_cur; };

        inline iteratorT &operator+=(size_t n) {
            m_cur = min(m_cur + n * recsize_(), end_());
            return *this;
        };

        inline iteratorT &operator-=(size_t n) {
            m_cur = max(m_cur - n * recsize_(), beg_());
            return *this;
        };

        inline iteratorT operator+(size_t n) {
            iteratorT i(*this);
            i += n;
            return i;
        };

        inline iteratorT operator-(size_t n) {
            iteratorT i(*this);
            i -= n;
            return i;
        };

        inline ptrdiff_t operator-(const iteratorT &i) { return (m_cur - i.m_cur) / recsize_(); };
    };

    typedef iteratorT<char> iterator;
    typedef iteratorT<const char> const_iterator;

    inline iterator begin() { return iterator(this, VecFileT::begin()); };

    inline iterator end() { return iterator(this, VecFileT::end()); };

    inline const_iterator begin() const { return const_iterator(this, VecFileT::begin()); };

    inline const_iterator end() const { return const_iterator(this, VecFileT::end()); };
};


//======================================================================
// ddcMapFile<KeyT,ValT>
/** simulate map<KeyT,ValT> using mmap, slurp, or demote.
 *  records should be stored as {KeyT,ValT[]} and sorted in ascending order by key
 */
template<typename KeyT, typename ValT>
class ddcMapFile {
public:
    //----------------------------------------------------------
    // typedefs
    typedef ddcRecFile RecFileT;
    typedef vector<ValT> VecT;
    typedef map<KeyT, VecT> MapT;

    typedef KeyT key_type;
    typedef VecT mapped_type;
    typedef pair<KeyT, VecT> value_type;

public:
    //----------------------------------------------------------
    // "private" data
    RecFileT m_rfile;           ///< data (read-only: mmap or slurp)
    MapT m_map;             ///< data (read/write: demoted)
    size_t m_vsize;           ///< number of elements per value-vector (constant)

public:
    //----------------------------------------------------------
    // constructors etc

    // default constructor
    ddcMapFile()
        : m_vsize(0) {};

    /// construct and open
    ddcMapFile(const std::string &filename, size_t vsize_, bool useMMap = false)
        : m_vsize(0) { open(filename, vsize_, useMMap); };

    /// default destructor calls close()
    ~ddcMapFile() { close(); };

    /// clear() method wraps close()
    inline void clear() { close(); };

public:
    //----------------------------------------------------------
    // accessors & properties

    /// returns the number of bytes per record
    inline size_t recsize() const { return sizeof(KeyT) + m_vsize * sizeof(ValT); };

    /// returns the number of elements per value-vector
    inline size_t vecsize() const { return m_vsize; };

    /// returns the number of records in this object
    inline size_t size() const { return m_rfile ? m_rfile.size() : m_map.size(); };

    /// STL-esque wrapper
    inline bool empty() const { return size() == 0; };

    /// returns true iff object is opened (or non-empty)
    inline bool opened() const { return m_rfile ? m_rfile.opened() : !m_map.empty(); };

    //----------------------------------------------------------
    // typecasts and operators

    /// implicit typecast to bool
    inline operator bool() const { return opened(); };

    /// indexing operator auto-demotes to slurp-mode
    inline VecT &operator[](const KeyT &key) {
        ensureMap();
        return m_map[key];
    };


public:
    //----------------------------------------------------------
    // STL-esque iterators (read-only mode)

    typedef RecFileT::iterator iterator;
    typedef RecFileT::const_iterator const_iterator;

    inline iterator begin() { return m_rfile.begin(); };

    inline iterator end() { return m_rfile.end(); };

    inline const_iterator begin() const { return m_rfile.begin(); };

    inline const_iterator end() const { return m_rfile.end(); };

    template<typename IterT>
    inline const KeyT &key(const IterT &it) const { return it.template key<KeyT>(); };

    template<typename IterT>
    inline const ValT *val(const IterT &it) const { return it.template val<KeyT, ValT>(); };

public:
    //----------------------------------------------------------
    // searching

    struct KeyLess {
        inline bool operator()(const char &ref, const KeyT &key) {
            const KeyT &refkey = *((const KeyT *) (&ref));
            //fprintf(stderr, "COMPARE(%d, %d)\n", refkey, key);
            return refkey < key;
        };
    };


    /// simulate std::map::find(), returns NULL on error
    inline const ValT *find(const KeyT &key_) const {
        if (m_rfile) {
            const_iterator lb = lower_bound(begin(), end(), key_, KeyLess());
            return (lb != end() && key(lb) == key_) ? val(lb) : NULL;
        } else {
            typename MapT::const_iterator lb = m_map.find(key_);
            return (lb != m_map.end() && lb->first == key_) ? &(lb->second[0]) : NULL;
        }
    };

public:
    //----------------------------------------------------------
    // guts
    ddcMapFile &open(const std::string &filename, size_t vsize, bool useMMap = false) {
        if (opened()) close();
        m_vsize = vsize;
        m_rfile.open(filename, recsize(), useMMap);
        return *this;
    };

    inline void close() {
        m_rfile.close();
        m_map.clear();
        m_vsize = 0;
    };

    /// force map-implementation
    void ensureMap() {
        if (m_rfile) {
            ddcLogWarn(Format("WARNING: ddcMapFile(\"%s\") demoting to std::map<> implementation",
                              m_rfile.filename().c_str()));
            m_map.clear();
            for (const_iterator i = begin(); i != end(); ++i) {
                const KeyT &key_ = key(i);
                const ValT *val_ = val(i);
                typename MapT::iterator it = m_map.insert(make_pair(key_, VecT())).first;
                it->second.reserve(m_vsize);
                it->second.assign(val_, val_ + m_vsize);
            }
            m_rfile.close();
        }
    };
};

class ddcFileOrMMap : public ddcLockable {
public:
    //----------------------------------------------------------
    // data
    bool m_UseMemoryMap;
    ddcMMap<char> m_mmap;
    FILE* m_File;

public:
    //----------------------------------------------------------
    // constructors etc.
    ddcFileOrMMap()
        : m_UseMemoryMap(false), m_mmap(), m_File(NULL)
    {};
 
    ~ddcFileOrMMap()
    { Close(); };

public:
    //----------------------------------------------------------
    // API

    /// check if file is currently mapped or opened
    inline bool opened() const
    { return m_mmap.opened() || m_File != NULL; };

    /// implicit cast-to-bool wraps opened()
    inline operator bool() const
    { return opened(); };

    /// open or memory-map \a filename
    void Open (bool useMemoryMap, const std::string &filename);

    /// close or un-map current file
    void Close();

    /// read \a nbytes of data at offset \a offset from file or memory-map into \a buffer
    bool ReadBuffer(file_off_t offset, size_t nbytes, BYTE* buffer) const;

public:
    //----------------------------------------------------------
    // low-level guts (use at your own risk)

    /// guts for ReadBuffer() on \a m_File
    bool ReadFromFile(file_off_t start, size_t nbytes, BYTE* buffer) const;
};

#endif /* DDC_MMAP_H */

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
