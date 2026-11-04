//-*- Mode: C++ -*-
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

//  Linux-only process utilities (ddc is Linux/POSIX only)

#ifndef ddcProcess_h
#define ddcProcess_h

#include "ddcConfig.h"      // HAVE_MALLOC_H, HAVE_MALLOC_TRIM
#include <cstring>
#include <sys/types.h>
#include <unistd.h>
#ifdef HAVE_MALLOC_H
# include <malloc.h>
#endif

//======================================================================
// moo: get memory statistics using /proc/PID/statm (linux only)

/** struct for reading /proc/PID/status; see proc(5) */
struct DDCProcessMemoryStatus
{
    size_t VmPeak;      //< Peak virtual memory size.
    size_t VmSize;      //< Virtual memory size.
    size_t VmLck;       //< Locked memory size (see mlock(3)).
    size_t VmPin;       //< Pinned memory size (since Linux 3.2).  These are pages that can't be moved because something needs to directly access physical memory.
    size_t VmHWM;       //< Peak resident set size ("high water mark").
    size_t VmRSS;       //< Resident set size.  Note that the value here is the sum of RssAnon, RssFile, and RssShmem.
    size_t VmData;      //< Size of data segment.
    size_t VmStk;       //< Size of stack segment.
    size_t VmExe;       //< Size of text (code) segment.
    size_t VmLib;       //< Shared library code size.
    size_t VmPTE;       //< Page table entries size (since Linux 2.6.10).
    size_t VmPMD;       //< Size of second-level page tables (since Linux 4.0).
    size_t VmSwap;      //< Swapped-out virtual memory size by anonymous private pages; shmem swap usage is not included (since Linux 2.6.34).
    size_t RssFile;     //< Size of resident file mappings.  (since Linux 4.5).
    size_t RssAnon;     //< Size of resident file mappings.  (since Linux 4.5).

    /** default constructor (no implicit fetch) */
    DDCProcessMemoryStatus(void)
        : VmSize(0), VmLck(0), VmPin(0), VmHWM(0), VmRSS(0), VmData(0), VmStk(0), VmExe(0), VmLib(0), VmPTE(0), VmPMD(0), VmSwap(0), RssFile(0), RssAnon(0)
    {};

    /** constructor given pid implicitly fetches data */
    DDCProcessMemoryStatus(pid_t pid)
    { fetch(pid); };

    inline void clear(void)
    { memset(this, 0, sizeof(DDCProcessMemoryStatus)); };
  
    /** fetch memory statistics for process PID */
    void fetch(pid_t pid);

    /** fetch memory statistics for current process */
    inline void fetch(void)
    { fetch(getpid()); };
};


/// return the number of open files for \a pid (linux only).
/// \li pid=0 maps to PID of current process)
size_t GetNumberOfOpenFiles(pid_t pid=0);

//-- agressive heap trimming
inline void TrimHeap()
{
#if HAVE_MALLOC_TRIM
    malloc_trim(0);
#endif
};

#endif
