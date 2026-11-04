/* -*- Mode: C++ -*- */
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2019 by Bryan Jurish
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

#include "ddcMMap.h"
#include "utilit.h"

using namespace std;

//======================================================================
// ddcFileOrMmap


//--------------------------------------------------------------
void ddcFileOrMMap::Open (bool useMemoryMap, const std::string &filename)
{
    m_UseMemoryMap = useMemoryMap;
    if (m_UseMemoryMap) {
        m_mmap.open(filename);
    }
    else {
        lock();
        m_File  = fopen(filename.c_str(), "rb");
        unlock();
        if (!m_File)
            throw std::runtime_error(Format("cannot  open file '%s': %s", filename.c_str(), strerror(errno)));
    }
}

//--------------------------------------------------------------
void ddcFileOrMMap::Close()
{
    if (m_File != 0) {
        lock();
        fclose(m_File);
        unlock();
        m_File = 0;
    } else {
        m_mmap.close();
    }
};

//--------------------------------------------------------------
bool ddcFileOrMMap::ReadFromFile(file_off_t start, size_t nbytes, BYTE* buffer) const
{
    if (!m_File) return false;
    lock();
    try {
        if (!fseek64(m_File, start, SEEK_SET)) {
            unlock();
            return false;
        }
        if (fread(buffer, 1, nbytes, m_File) != nbytes) {
            unlock();
            return false;
        }
    }
    catch (...) {
        unlock();
        throw;
    }

    unlock();
    return true;
}

//--------------------------------------------------------------
bool ddcFileOrMMap::ReadBuffer(file_off_t offset, size_t nbytes, BYTE* buffer) const {
    if (m_mmap) {
        memcpy(buffer, m_mmap.m_data + offset, nbytes);
        return true;
    }
    else  {
        // the default
        return ReadFromFile(offset, nbytes, buffer);
    }
}

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
