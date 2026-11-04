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

#include "ddcProcess.h"
#include <cstdio>
#include <cstdlib>
#include <dirent.h>

void DDCProcessMemoryStatus::fetch(pid_t pid)
{
    clear();
    
    char filename[64];
    sprintf(filename, "/proc/%d/status", pid);
    
    FILE *f = fopen(filename, "r");
    if (f==NULL) return;

    char buf[512];
    char *sep;
    while (fgets(buf, 512, f)) {
        if ( !(sep = strchr(buf, ':')) ) continue;
        *sep++ = '\0';
        if      (strcmp(buf,"VmPeak")==0) VmPeak = strtoul(sep,NULL,0);
        else if (strcmp(buf,"VmSize")==0) VmSize = strtoul(sep,NULL,0);
        else if (strcmp(buf,"VmLck")==0) VmLck = strtoul(sep,NULL,0);
        else if (strcmp(buf,"VmPin")==0) VmPin = strtoul(sep,NULL,0);
        else if (strcmp(buf,"VmHWM")==0) VmHWM = strtoul(sep,NULL,0);
        else if (strcmp(buf,"VmRSS")==0) VmRSS = strtoul(sep,NULL,0);
        else if (strcmp(buf,"VmData")==0) VmData = strtoul(sep,NULL,0);
        else if (strcmp(buf,"VmStk")==0) VmStk = strtoul(sep,NULL,0);
        else if (strcmp(buf,"VmExe")==0) VmExe = strtoul(sep,NULL,0);
        else if (strcmp(buf,"VmLib")==0) VmLib = strtoul(sep,NULL,0);
        else if (strcmp(buf,"VmPTE")==0) VmPTE = strtoul(sep,NULL,0);
        else if (strcmp(buf,"VmPMD")==0) VmPMD = strtoul(sep,NULL,0);
        else if (strcmp(buf,"VmSwap")==0) VmSwap = strtoul(sep,NULL,0);
        else if (strcmp(buf,"RssFile")==0) RssFile = strtoul(sep,NULL,0);
        else if (strcmp(buf,"RssAnon")==0) RssAnon = strtoul(sep,NULL,0);
    }

    fclose(f);
    return;
}

size_t GetNumberOfOpenFiles(pid_t pid)
{
    if (pid==0) pid = getpid();

    char fddir[64];
    DIR *d;
    sprintf(fddir, "/proc/%d/fd", pid);
    if (!(d=opendir(fddir))) {
        return 0; //-- no process matching pid, or non-linux
    }

    struct dirent *de;
    size_t n=0;
    while ( (de=readdir(d)) ) {
        if (strcmp(de->d_name,".")!=0 && strcmp(de->d_name,"..")!=0)
            ++n;
    }
    closedir(d);
    
    return n;
};
