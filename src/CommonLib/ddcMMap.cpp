#include "ddcMMap.h"
#include "nlp_base/common/utilit.h"
#include "ddcUtil.h"

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
