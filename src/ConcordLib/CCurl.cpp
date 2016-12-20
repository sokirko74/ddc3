//-*- Mode: C++; c-basic-offset: 2; -*-
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2015 by Bryan Jurish
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

#include "CCurl.h"

//======================================================================
// macros

#ifndef HAVE_LIBCURL
#define CURL_GLOBAL_ALL -1
#define curl_global_init(which) -1
#define curl_easy_init() NULL
#define CURLOPT_URL -1
#define CURLOPT_TIMEOUT -1
#define CURLOPT_WRITEFUNCTION -1
#define CURLOPT_WRITEDATA -1
#define CURLOPT_HEADERFUNCTION -1
#define CURLOPT_HEADERDATA -1
#define CURLOPT_ERRORBUFFER -1
#define CURLOPT_FORBID_REUSE -1
#define CURLOPT_VERBOSE -1
#define CURLOPT_NOSIGNAL -1
#define CURLOPT_FAILONERR -1
#define curl_easy_setopt(handle,opt,val)
#define curl_easy_perform(handle) -1
#define curl_easy_cleanup(handle) -1
#endif /* HAVE_LIBCURL */

//======================================================================
// Globals

#if HAVE_PTHREAD
 pthread_mutex_t ddcCurlMutex = PTHREAD_MUTEX_INITIALIZER;
#endif

static const int ddcCurlCacheCapacity = 1024;
CCurlCache ddcCurlCache(ddcCurlCacheCapacity, DDC_IFPTHREADELSE(&ddcCurlMutex,NULL));

int ddcCurlInitialized = 0;

void ddcInitCurl(void) {
  //if (ddcCurlInitialized) return;
  DDC_IFPTHREAD(pthread_mutex_lock(&ddcCurlMutex));
  if (!ddcCurlInitialized) {
    curl_global_init(CURL_GLOBAL_ALL);
    ddcCurlInitialized = 1;
  }
  DDC_IFPTHREAD(pthread_mutex_unlock(&ddcCurlMutex));
}


//======================================================================
// CCurl

//--------------------------------------------------------------
CCurl::CCurl(const string &url_, long timeout_)
  : m_Curl(NULL)
{
  ddcInitCurl();
  m_Curl = curl_easy_init();
  curl_easy_setopt(m_Curl, CURLOPT_ERRORBUFFER, m_CurlErr);
  reset();
  url(url_);
  timeout(timeout_);
};

//--------------------------------------------------------------
CCurl::~CCurl(void)
{
  if (m_Curl) curl_easy_cleanup(m_Curl);
}

//--------------------------------------------------------------
void CCurl::reset(void)
{
  m_CurlErr[0] = '\0';
  m_Response.clear();
  m_Headers.clear();
}

//--------------------------------------------------------------
bool CCurl::perform(void)
{
  reset();
  int rc = curl_easy_perform(m_Curl);
  if (rc==0) return true;
#ifndef HAVE_LIBCURL
  strcpy(m_CurlErr, "CCurl::perform() called but libcurl support disabled!");
#endif
  return false;
}

//--------------------------------------------------------------
bool CCurl::perform_cached(CCurlCache *cache)
{
  int rc = 0;
  CCurlCache::iterator cachei;
  reset();

  cache->lock();
  cachei = cache->get(m_Url);
  if (cachei != cache->end()) {
    m_Response = cachei->second->second;
  }
  else {
    rc = curl_easy_perform(m_Curl);
    if (rc==0) {
      //-- only cache successful responses (avoid perpetuating mantis bug #701)
      cache->insert(m_Url, m_Response);
    }
  }
  cache->unlock();

  return (rc==0);
}


//--------------------------------------------------------------
void CCurl::url(const string& url)
{
  m_Url = url;
  curl_easy_setopt(m_Curl, CURLOPT_URL, (url.empty() ? NULL : url.c_str()));
}

//--------------------------------------------------------------
void CCurl::timeout(long seconds)
{
  m_Timeout = seconds;
  curl_easy_setopt(m_Curl, CURLOPT_TIMEOUT, seconds);
}

//--------------------------------------------------------------
void CCurl::forbidReuse(int flag)
{ curl_easy_setopt(m_Curl, CURLOPT_FORBID_REUSE, flag); }

void CCurl::noSignal(int flag)
{ curl_easy_setopt(m_Curl, CURLOPT_NOSIGNAL, flag); }

void CCurl::failOnError(int flag)
{ curl_easy_setopt(m_Curl, CURLOPT_FAILONERROR, flag); }

void CCurl::verbose(int flag)
{ curl_easy_setopt(m_Curl, CURLOPT_VERBOSE, flag); }

//--------------------------------------------------------------
void CCurl::setDataCallback(CurlWriteDataCallback handler, void *data)
{
  curl_easy_setopt(m_Curl, CURLOPT_WRITEFUNCTION, handler);
  curl_easy_setopt(m_Curl, CURLOPT_WRITEDATA,     data);
}

//--------------------------------------------------------------
void CCurl::setHeaderCallback(CurlWriteHeaderCallback handler, void *data)
{
  curl_easy_setopt(m_Curl, CURLOPT_HEADERFUNCTION, handler);
  curl_easy_setopt(m_Curl, CURLOPT_HEADERDATA,     data);
}

//--------------------------------------------------------------
size_t CCurl::cbWriteData_(char *ptr, size_t size, size_t n, string *bufp)
{
  if (!bufp) return size*n; //-- dummy clause for NULL data
  size_t size0 = bufp->size();
  bufp->append(ptr, size*n);
  return bufp->size()-size0;
}

//--------------------------------------------------------------
size_t CCurl::cbWriteHeader_(void *ptr, size_t size, size_t n, vector<string> *bufvp)
{
  if (!bufvp) return size*n; //-- dummy clause for NULL data
  bufvp->push_back(string());
  bufvp->back().assign((char*)ptr,size*n);
  return bufvp->back().size();
}



