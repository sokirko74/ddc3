#ifndef DDC_CORPUS_FILES_H
#define DDC_CORPUS_FILES_H

#include "ddcMMap.h"
#include "ddcVersion.h"
#include "ddcFile.h"

//======================================================================
// ddcCorpusList
/* high-level wrapper for corpus file lists (*._con) */
template <typename OffT_=uint32_t>
class ddcCorpusList
{
public:
    //----------------------------------------------------------
    // typedefs
    typedef OffT_  OffT; // typedef for offset values
    typedef uint32_t  IdT;  // typedef for integer IDs

public:
    //----------------------------------------------------------
    // data
    ddcVecFile<char>  m_cdata;    // underlying character data, including initial version string
    ddcVecFile<OffT>  m_offsets;  // offsets in m_cdata[] of ""-terminated filenames (in corpus order)
    std::vector<std::string>    m_strings;  // backwards-compatible vector<string> implementation, for read/write access
    std::string            m_verstr;   // version string (1st line of *._con file)

    size_t            m_bufsize;  // buffer size for fallback (default is old value for MaxBiblStringLen from Bibliography.cpp)

public:
    //----------------------------------------------------------
    // constructors etc.

    // default constructor
    ddcCorpusList()
        : m_bufsize(20000)
    {};

    // construct and open
    ddcCorpusList(const std::string& conFile, const std::string& cdataFile="", const std::string& offsetsFile="", bool useMMap=false)
        : m_bufsize(20000)
    { open(conFile,cdataFile,offsetsFile,useMMap); };

    // default destructor calls close()
    ~ddcCorpusList()
    { close(); };

    // clear() method wraps close()
    inline void clear()
    { close(); };

public:
    //----------------------------------------------------------
    // accessors & properties

    // returns the number of enumerated strings
    inline size_t size() const
    { return m_offsets ? m_offsets.size() : m_strings.size(); };

    // STL-esque wrapper
    inline bool empty() const
    { return m_offsets ? m_offsets.empty() : m_strings.empty(); };

    // check whether the object is opened
    inline bool opened() const
    { return m_offsets.opened() || !m_strings.empty(); };

    // version string
    const std::string& VersionString() const
    { return m_verstr; };

    // get start-offset of string by index (mmap variant only)
    inline OffT itemStartOffset(IdT idx) const
    { return m_offsets[idx]; };

    // get end-offset of string by index (mmap variant only)
    inline OffT itemEndOffset(IdT idx) const
    { return ((idx+1)>=size() ? m_cdata.size() : m_offsets[idx+1]) - 1; };

    // pseudo-indexing operator
    inline void itemGet(IdT idx, std::string& str) const
    {
        OffT i = itemStartOffset(idx);
        OffT j = itemEndOffset(idx);
        str.assign( &m_cdata[i], j-i );
    };


public:
    //----------------------------------------------------------
    // operators

    // implicit typecast to bool
    inline operator bool() const
    { return opened(); };

    // indexing operator (copies)
    inline std::string operator[](IdT idx) const
    {
        if (!m_offsets) return m_strings[idx];
        OffT i = itemStartOffset(idx);
        OffT j = itemEndOffset(idx);
        return std::string( &m_cdata[i], j-i );
    };

    //----------------------------------------------------------
    // read/write access (auto-demote)

    // simulate vector::push_back(): used by indexing routines
    inline void push_back(const std::string& value)
    {
        ensureVec();
        m_strings.push_back(value);
    };

    // populate v with an equivalent vector-implementation (for compile-time compatibility)
    void append_vector(std::vector<std::string>& v) const
    {
        v.reserve(v.size()+size());
        if (m_offsets) {
            for (IdT idx=0; idx < size(); ++idx)
                v.push_back(operator[](idx));
        } else {
            v.insert(v.end(), m_strings.begin(), m_strings.end());
        }
    };
    
    // force vector-implementation
    inline void ensureVec()
    {
        if (m_offsets) {
            ddcLogWarn(Format("WARNING: ddcCorpusList(\"%s\") demoting to std::vector<> implementation", m_cdata.filename().c_str()));
            ClearVector(m_strings);
            append_vector(m_strings);
            m_offsets.close();
            m_cdata.close();
        }
    };

public:
    //----------------------------------------------------------
    // search

    // constant returned by string-to-id search methods indicating no match was found
    //-- re numeric_limits<>::max(): see NO_ID comments in ddcStringEnum.h
    //static const IdT NO_ID = std::numeric_limits<IdT>::max();
    static const IdT NO_ID = UINT32_MAX;

    // returns first id of key, or NO_ID if not found (linear search)
    inline IdT find(const std::string& key) const
    {
        if (m_offsets) {
            std::string tmp;
            for (IdT idx=0; idx < size(); ++idx) {
                itemGet(idx,tmp);
                if (tmp == key)
                    return idx;
            }
        }
        else {
            std::vector<std::string>::const_iterator it = std::find(m_strings.begin(), m_strings.end(), key);
            if (it != m_strings.end())
                return (it - m_strings.begin());
        }
        return NO_ID;
    };

    // returns last id of key, or NO_ID if not found (linear search)
    inline IdT rfind(const std::string& key) const
    {
        if (m_offsets) {
            if (empty()) return NO_ID;
            std::string tmp;
            IdT idx = size()-1;
            do {
                itemGet(idx,tmp);
                if (tmp == key)
                    return idx;
                --idx;
            } while (idx != 0);
        }
        else {
            std::vector<std::string>::const_reverse_iterator it = std::find(m_strings.rbegin(), m_strings.rend(), key);
            if (it != m_strings.rend())
                return (m_strings.size()-1) - (it - m_strings.rbegin());
        }
        return NO_ID;
    };
    
public:
    //----------------------------------------------------------
    // guts

    // map a named file filename
    ddcCorpusList& open(const std::string& conFile, const std::string& cdataFile="", const std::string& offsetsFile="", bool useMMap=false)
    {
        if (opened()) close();

        if (!cdataFile.empty() && !offsetsFile.empty() && FileExists(cdataFile) && FileExists(offsetsFile)) {
            openCompat(conFile,false);
            m_cdata.open(cdataFile, useMMap);
            m_offsets.open(offsetsFile, useMMap);
            ddcLogDebug(Format("ddcCorpusList[%s]::open(): read %zi item(s) from %s + %s", (useMMap ? "mmap" : "slurp"), size(), cdataFile.c_str(), offsetsFile.c_str()));
        }
        else {
            ddcLogWarn("WARNING: ddcCorpusList::open(): loading corpus list '"+conFile+"' in compatibility mode: please upgrade your index!");
            openCompat(conFile,true);
            ddcLogDebug(Format("ddcCorpusList[compat]::open(): read %zi item(s) from %s", size(), conFile.c_str()));
        }
        //ddc_format_version_check(m_verstr.c_str(), cdataFile.c_str());
        return *this;
    };

    // open in compatibility-mode; lifted from CConcIndexator::LoadCorpusFiles()
    void openCompat(const std::string& filename, bool slurpList=true)
    {
        if (opened()) close();

        FILE * fp = fopen(filename.c_str(), "rb");
        if (!fp)
            throw std::invalid_argument(Format("ddcCorpusList::openCompat(): open failed for '%s': %s'", filename.c_str(), strerror(errno)));

        char buf[m_bufsize+1];
        if (!fgets(buf, m_bufsize, fp))
            throw std::invalid_argument("ddcCorpusList::openCompat(): failed to read version information from '"+filename+"'");
        m_verstr = buf;
        Trim(m_verstr);

        if (slurpList) {
            std::string tmp;
            while (fgets(buf, m_bufsize, fp)) {
                tmp = buf;
                Trim(tmp);
                m_strings.push_back(tmp);
            }
        }

        fclose(fp);
    };

    // unmap current file(s), if any
    void close()
    {
        m_cdata.close();
        m_offsets.close();
        ClearVector(m_strings);
        ClearString(m_verstr);
    };

};


#endif /* DDC_STRING_ENUM_H */
