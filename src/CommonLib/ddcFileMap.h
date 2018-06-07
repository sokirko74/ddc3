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
#ifndef DDC_FILE_MAP_H
#define DDC_FILE_MAP_H

#ifdef HAVE_CONFIG_H
#include "../common/ddcConfig.h"
#endif

#include <string>
#include <stdexcept>

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h> /* fstat */
#include <sys/mman.h> /* mmap */

//======================================================================
// ddcFileMap
/// convenience wrapper for mapping entire files into virtual memory using mmap()
template<typename T=void>
struct ddcFileMap
{
    std::string  m_file;  ///< underlying filename
    size_t       m_size;  ///< number of bytes mapped
    T           *m_data;  ///< file data

    //----------------------------------------------------------
    // constructors etc.

    /// default constructor
    ddcFileMap()
	: m_size(0), m_data(NULL)
    {};

    ddcFileMap(const std::string& filename, int mode=O_RDONLY)
	: m_size(0), m_data(NULL)
    { open(filename,mode); };

    /// default destructor calls close()
    ~ddcFileMap()
    { close(); };

    //----------------------------------------------------------
    // accessors

    /// returns the name of the currently mapped file, if any
    inline const std::string& filename() const
    { return m_file; };

    /// returns number of bytes mapped, or 0
    inline size_t mmSize() const
    { return m_size; };

    /// returns a pointer to the mmap()ed file data, or NULL
    inline T* data() const
    { return m_data; };

    /// STL-esque wrapper for (size()==0)
    inline bool empty() const
    { return m_size==0; };

    /// returns the number of objects of type T mapped, or 0
    inline size_t size() const
    { return m_size / sizeof(T); };

    //----------------------------------------------------------
    // STL-esque iterators

    typedef T*       iterator;
    typedef const T* const_iterator;

    inline iterator begin() const { return m_data; };
    inline iterator end()   const { return m_data+m_size; };

    //----------------------------------------------------------
    // typecast operators

    /// implicit typecast to bool
    inline operator bool() const
    { return m_data != NULL; };
    
    /// implicit typecast to T*
    inline operator T*() const
    { return m_data; };

    //----------------------------------------------------------
    // guts

    /// map a named file \a filename
    ddcFileMap& open(const std::string& filename, int mode=O_RDONLY)
    {
	if (m_data != NULL) close();
	m_file = filename;

	//-- open the file (temporarily)
	int mmfd = ::open(filename.c_str(), mode);
	if (mmfd == -1)
	    throw std::invalid_argument(Format("ddcFileMap::open(): open failed for '%s': %s", filename.c_str(), strerror(errno)));

	//-- get total file size
	struct stat statbuf;
	if (fstat(mmfd, &statbuf) != 0)
	    throw std::runtime_error(Format("ddcFileMap::open(): fstat() failed for file '%s': %s", filename.c_str(), strerror(errno)));
	m_size = statbuf.st_size;

	//-- get mmap protection flags
	int mmprot = 0;
	switch (mode) {
	case O_RDONLY: mmprot = PROT_READ; break;
	case O_WRONLY: mmprot = PROT_WRITE; break;
	case O_RDWR:   mmprot = (PROT_READ|PROT_WRITE); break;
	default:
	    throw std::invalid_argument(Format("ddcFileMap::open(): unknown open mode '%d'",mode));
	}

	//-- underlying mmap call
	m_data = (T*)mmap(NULL, m_size, mmprot, MAP_SHARED, mmfd, 0);
	if (m_data == MAP_FAILED)
	    throw std::runtime_error(Format("ddcFileMap::open(): mmap() failed for file '%s': %s", filename.c_str(), strerror(errno)));

	//-- we can now safely close the fd
	if (::close(mmfd) != 0)
	    throw std::runtime_error(Format("ddcFileMap::open(): close() failed for file '%s': %s", filename.c_str(), strerror(errno)));
	
	return *this;
    };

    /// unmap current file (if any)
    void close()
    {
	if (m_data != NULL) {
	    if (munmap(m_data, m_size) != 0)
		throw std::runtime_error(Format("ddcFileMap::close(): munmap() failed for file '%s': %s", m_file.c_str(), strerror(errno)));
	}
	m_file.clear();
	m_data = NULL;
	m_size = 0;
    };
    
};


	
#endif /* DDC_FILE_MAP_H */
