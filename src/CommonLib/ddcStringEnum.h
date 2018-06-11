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
#ifndef DDC_STRING_ENUM_H
#define DDC_STRING_ENUM_H

#include "../CommonLib/ddcMMap.h"

//======================================================================
// ddcMMap
/** convenience wrapper for integer->string mappings */
template <typename OffT=DWORD>
class ddcStringEnum
{
public:
    //----------------------------------------------------------
    // data
    ddcVecFile<char>  m_cdata;    ///< underlying character data
    ddcVecFile<OffT>  m_offsets;  ///< offsets in m_cdata[] of NUL-terminated item strings
    vector<string>    m_strings;  ///< backwards-compatible vector<string> implementation, for read/write access

    size_t            m_bufsize;  ///< buffer size for fallback (default is old value for MaxBiblStringLen from Bibliography.cpp)

public:
    //----------------------------------------------------------
    // constructors etc.

    /// default constructor
    ddcStringEnum()
	: m_bufsize(20000)
    {};

    /// construct and open
    ddcStringEnum(const string& cdataFile, const string& offsetsFile, const string& fallbackFile="", bool useMMap=false)
	: m_bufsize(20000)
    { open(cdataFile,offsetsFile,fallbackFile,useMMap); };

    /// default destructor calls close()
    ~ddcStringEnum()
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

public:
    //----------------------------------------------------------
    // TODO: search

    static const DWORD NOKEY = DWORD_MAX;

    DWORD lower_bound(const string& str)
    { throw runtime_error("not yet implemented"); };

    DWORD upper_bound(const string& str)
    { throw runtime_error("not yet implemented"); };

public:
    //----------------------------------------------------------
    // guts

    /// map a named file \a filename
    ddcStringEnum& open(const string& cdataFile, const string& offsetsFile, const string& fallbackFile, bool useMMap=false)
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
	    throw invalid_argument("ddcStrtringEnum::open(\""+cdataFile+"\",\""+offsetsFile+"\",\""+fallbackFile+"\"): no file(s) found!");
	}
	return *this;
    };

    /// open in compatibility-mode; lifted from CConcXml::CFreeBiblStringIndex::ReadBiblStringItems (vector<string>&  Set, string FileName)
    void openCompat(const string& filename)
    {
	if (opened()) close();

	FILE * fp = fopen(filename.c_str(), "rb");
	if (!fp)
	    throw invalid_argument(Format("ddcStringEnum::openCompat(): open failed for '%s': %s'", filename.c_str(), strerror(errno)));
	
	char buf[m_bufsize+1];
	while (fgets(buf, m_bufsize, fp)) {
	    string q(buf);
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
