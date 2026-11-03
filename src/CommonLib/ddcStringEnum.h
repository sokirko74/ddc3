//-*- Mode: C++ -*-
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
#ifndef DDC_STRING_ENUM_H
#define DDC_STRING_ENUM_H

#include "ddcMMap.h"
#include <limits>

//======================================================================
// ddcStringEnum
/** convenience wrapper for file-based integer<->string mappings */
template <typename OffT_=DWORD>
class ddcStringEnum
{
public:
    //----------------------------------------------------------
    // typedefs
    typedef OffT_  OffT; ///< typedef for offset values
    typedef DWORD  IdT;  ///< typedef for integer IDs

public:
    //----------------------------------------------------------
    // data
    ddcVecFile<char>  m_cdata;    ///< underlying character data
    ddcVecFile<OffT>  m_offsets;  ///< offsets in m_cdata[] of NUL-terminated item strings; associated strings must be sorted in lexicographic order
    std::vector<std::string>    m_strings;  ///< backwards-compatible vector<string> implementation, for read/write access

    size_t            m_bufsize;  ///< buffer size for fallback loading (default=20000: old value for MaxBiblStringLen from Bibliography.cpp)

public:
    //----------------------------------------------------------
    // constructors etc.

    /// default constructor
    ddcStringEnum()
        : m_bufsize(20000)
    {};

    /// construct and open
    ddcStringEnum(const std::string& cdataFile, const std::string& offsetsFile, const std::string& fallbackFile="", bool useMMap=false)
        : m_bufsize(20000)
    { open(cdataFile,offsetsFile,fallbackFile,useMMap); };

    /// default destructor calls close()
    ~ddcStringEnum()
    { close(); };

    /// clear() method wraps close()
    inline void clear()
    { close(); };

public:
    //----------------------------------------------------------
    // accessors & properties

    /// returns the number of enumerated strings
    inline size_t size() const
    { return m_offsets ? m_offsets.size() : m_strings.size(); };

    /// STL-esque wrapper
    inline bool empty() const
    { return m_offsets ? m_offsets.empty() : m_strings.empty(); };

    /// check whether the object is opened
    inline bool opened() const
    { return m_offsets.opened() || !m_strings.empty(); };

public:
    //----------------------------------------------------------
    // typecast operators

    /// implicit typecast to bool
    inline operator bool() const
    { return opened(); };
    
    /// indexing operator
    inline const char* operator[](size_t idx) const
    { return m_offsets ? (m_cdata.m_data+m_offsets.m_data[idx]) : m_strings[idx].c_str(); };

    //----------------------------------------------------------
    // read/write access (auto-demote)

    /// simulate vector::push_back(): used by indexing routines
    inline void push_back(const std::string& value)
    {
        ensureVec();
        m_strings.push_back(value);
    };

    /// populate \a v with an equivalent vector-implementation (for compile-time compatibility)
    void to_vector(std::vector<std::string>& v) const
    {
        ClearVector(v);
        v.reserve(size());
        if (m_offsets) {
            for (const OffT* oi=m_offsets.begin(); oi != m_offsets.end(); ++oi)
                v.push_back( m_cdata.m_data + *oi );
        } else {
            v = m_strings;
        }
    };
    
    /// force vector-implementation
    inline void ensureVec()
    {
        if (m_offsets) {
            ddcLogWarn(Format("WARNING: ddcStringEnum(\"%s\") demoting to std::vector<> implementation", m_cdata.filename().c_str()));
            to_vector(m_strings);
            m_offsets.close();
            m_cdata.close();
        }
    };

public:
    //----------------------------------------------------------
    // search


    /// constant returned by string-to-id search methods indicating no match was found
    //-- numeric_limits<>::max():
    // + g++ 5.4.0 (ubuntu 16.04.3 / kira) chokes on initialization via std::numeric_limits<IdT>::max() with:
    //   "error: a function call cannot appear in a constant-expression"
    // + we don't have IdT parameterized yet anyway (it's all 32-bit at this point), so we can just use DWORD_MAX
    //static const IdT NO_ID = std::numeric_limits<IdT>::max();
    static const IdT NO_ID = DWORD_MAX;

    /// comparison helper struct for string-to-id search
    struct IdKeyLess {
        const char *m_buf;

        IdKeyLess(const char *buf)
            : m_buf(buf)
        {};
        IdKeyLess(const ddcStringEnum& se)
            : m_buf(se.m_cdata.m_data)
        {};

        
        inline bool operator()(const OffT off, const std::string& key)
        { return (m_buf+off) < key; };
        inline bool operator()(const std::string& key, const OffT off)
        { return key < (m_buf+off); };
    };

    /// returns id of lower-bound for \a key, or NO_ID if not found
    IdT lower_bound(const std::string& key) const
    {
        if (m_offsets) {
            //-- ddc-v2.1.12 version
            typename ddcVecFile<OffT>::const_iterator lb = std::lower_bound(m_offsets.begin(), m_offsets.end(), key, IdKeyLess(*this));
            if (lb != m_offsets.end()) return (lb - m_offsets.begin());
        } else {
            //-- backwards-compatible implementation using m_strings
            std::vector<std::string>::const_iterator lb = std::lower_bound(m_strings.begin(), m_strings.end(), key);
            if (lb != m_strings.end()) return (lb - m_strings.begin());
        }
        return NO_ID;
    };

    /// returns id of upper-bound for \a key, or NO_ID if not found
    inline IdT upper_bound(const std::string& key) const
    {
        if (m_offsets) {
            //-- ddc-v2.1.12 version
            typename ddcVecFile<OffT>::const_iterator ub = std::upper_bound(m_offsets.begin(), m_offsets.end(), key, IdKeyLess(*this));
            if (ub != m_offsets.end()) return (ub - m_offsets.begin());
        } else {
            //-- backwards-compatible implementation using m_strings
            std::vector<std::string>::const_iterator ub = std::upper_bound(m_strings.begin(), m_strings.end(), key);
            if (ub != m_strings.end()) return (ub - m_strings.begin());
        }
        return NO_ID;
    };

    /// returns id of \a key, or NO_ID if not found; wraps lower_bound()
    inline IdT find(const std::string& key) const
    {
        IdT lbid = lower_bound(key);
        return (lbid != NO_ID && operator[](lbid) == key) ? lbid : NO_ID;
    };
    
public:
    //----------------------------------------------------------
    // guts

    /// map a named file \a filename
    ddcStringEnum& open(const std::string& cdataFile, const std::string& offsetsFile, const std::string& fallbackFile, bool useMMap=false)
    {
        if (opened()) close();

        if (FileExists(cdataFile.c_str()) && FileExists(offsetsFile.c_str())) {
            m_cdata.open(cdataFile, useMMap);
            m_offsets.open(offsetsFile, useMMap);
            ddcLogDebug(Format("ddcStringEnum[%s]::open(): read %zi item(s) from %s + %s", (useMMap ? "mmap" : "slurp"), size(), cdataFile.c_str(), offsetsFile.c_str()));
        }
        else if (!fallbackFile.empty() && FileExists(fallbackFile.c_str())) {
            ddcLogWarn("WARNING: ddcStringEnum::open(): loading fallback file '"+fallbackFile+"' in slurp mode: please upgrade your index!");
            openCompat(fallbackFile);
            ddcLogDebug(Format("ddcStringEnum[compat]::open(): read %zi item(s) from %s", size(), fallbackFile.c_str()));
        } else {
            throw std::invalid_argument("ddcStringEnum::open(\""+cdataFile+"\",\""+offsetsFile+"\",\""+fallbackFile+"\"): no file(s) found!");
        }
        return *this;
    };

    /// open in compatibility-mode; lifted from CConcXml::CFreeBiblStringIndex::ReadBiblStringItems (vector<string>&  Set, string FileName)
    void openCompat(const std::string& filename)
    {
        if (opened()) close();

        FILE * fp = fopen(filename.c_str(), "rb");
        if (!fp)
            throw std::invalid_argument(Format("ddcStringEnum::openCompat(): open failed for '%s': %s'", filename.c_str(), strerror(errno)));
        
        char buf[m_bufsize+1];
        while (fgets(buf, m_bufsize, fp)) {
            std::string q(buf);
            Trim(q);
            m_strings.push_back(q);
        }

        fclose(fp);
    };

    /// unmap current file(s), if any
    void close()
    {
        m_cdata.close();
        m_offsets.close();
        ClearVector(m_strings);
    };

};



#endif /* DDC_STRING_ENUM_H */

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
