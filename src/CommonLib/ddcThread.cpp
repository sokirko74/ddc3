//-*- Mode: C++; c-basic-offset: 4; -*-
//
//  DDC originally by Alexey Sokirko
//  This file by Bryan Jurish, adapted from https://vichargrave.github.io/articles/2012-12/java-style-thread-class-in-cpp
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

#include "../CommonLib/ddcThread.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

using namespace std;

//======================================================================
// ddcThread: Constructors etc

//--------------------------------------------------------------
ddcThread::~ddcThread()
{
    if (m_running) {
	if (!m_detached)
	    pthread_detach(m_tid);
        pthread_cancel(m_tid);
    }
}


//======================================================================
// ddcThread: Accessors

//--------------------------------------------------------------
std::string ddcThread::toString(void) const
{
    unsigned char *thrc = (unsigned char*)(void*)(&m_tid);
    string str;
    char tmp[3];
    str.reserve(2*sizeof(pthread_t)+2);
    str.append("0x");
    for (size_t i=0; i<sizeof(pthread_t); ++i) {
	sprintf(tmp, "%02x", (unsigned)(thrc[i]));
	str.append(tmp);
    }
    return str;
}

//======================================================================
// ddcThread: API

//--------------------------------------------------------------
// C-level wrapper for use with pthread_create()
static void* ddcThreadRun(void* ddc_thread)
{
    return ((ddcThread*)ddc_thread)->run();
}

//--------------------------------------------------------------
int ddcThread::start()
{
    //-- initialize thread attributes before calling pthread_create()
    this->init();

    int result = pthread_create(&m_tid, m_attr, ddcThreadRun, this);
    if (result == 0)
        m_running = 1;

    //-- destroy thread attributes if requested: they're no longer needed for this thread
    if (m_attr != NULL)
	pthread_attr_destroy(m_attr);
    
    return result;
}

//--------------------------------------------------------------
int ddcThread::join()
{
    int result = ENOTSUP; //-- "Operation not supported"
    if (m_running == 1) {
        result = pthread_join(m_tid, NULL);
        if (result == 0)
            m_detached = 1;
    }
    return result;
}

//--------------------------------------------------------------
int ddcThread::detach(bool force)
{
    int result = ENOTSUP;
    if (m_running && !m_detached) {
	result = pthread_detach(m_tid);
	if (result == 0)
	    m_detached = 1;
    }
    if (m_detached && force && m_running)
	m_running = 0; //-- force-detach underlying pthread_t
    return result;
}
