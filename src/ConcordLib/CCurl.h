//-*- Mode: C++ -*-
//  Copyright 2011 by Bryan Jurish
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

#ifndef DDC_CURL_H
#define DDC_CURL_H

#include "../common/utilit.h"
#include "../common/ddcString.h"
#include "../common/ddcConfig.h"

#ifdef HAVE_LIBCURL

 #include <curl/curl.h>
 typedef CURL* CurlHandle;

#else /* !HAVE_LIBCURL */

 //! dummy typedef for missing libcurl
 typedef void* CurlHandle;

 #define CURL_ERROR_SIZE 64

#endif /* HAVE_LIBCURL */

//======================================================================
// Globals

//! sentinel to determine whether curl_global_init() has been called
extern int ddcCurlInitialized;

//! global initialization function (multiple calls should be safe)
extern void ddcInitCurl(void);

//======================================================================
//! \brief CCurl: abstract term expander using libcurl
class CCurl {
public:
  //! curl response content handler callback type; should return the number of bytes actually taken care of (== size*n on success)
  typedef size_t (*CurlWriteDataCallback) (char *ptr, size_t size, size_t n, void *userdata);

  //! curl response header callback type; should return the number of bytes actually taken care of (== size*n on success)
  typedef size_t (*CurlWriteHeaderCallback) (void *ptr, size_t size, size_t n, void *userdata);

public:
  //! curl handle
  CurlHandle m_Curl;

  //! current url
  string m_Url;

  //! current timeout (seconds; default=60)
  long m_Timeout;

  //! local curl error buffer
  char m_CurlErr[CURL_ERROR_SIZE];

  //! response content buffer (used by default write callback)
  string m_Response;

  //! response headers (used by default header callback)
  vector<string> m_Headers;

public:
  //! constructor implicitly calls url(url)
  CCurl(const string &url_=string(""), long timeout_=60);

  //! destructor implicitly frees m_Curl
  ~CCurl(void);

  //! prepare for another perform(): clears m_CurlErr, m_Response, and m_Headers
  void reset(void);

  //! Get response for request in m_Curl: wrapper for curl_easy_perform
  //! \li Returns false on error and populates m_CurlErr if the default callbacks are used
  //! \li implicitly calls reset()
  bool perform(void);

  //! Set default options: 
  bool SetDefaultOptions();

  //--------
  //! get current URL
  inline const string& url(void)
  { return m_Url; };

  //! set current URL (sets m_Url and wraps CURLOPT_URL)
  void url(const string &url);

  //--------
  //! get current timeout (seconds)
  inline long timeout(void)
  { return m_Timeout; };

  //! set timeout (seconds)
  void timeout(long seconds);

  //--------
  //! wrap CURLOPT_FORBID_REUSE: if true, a new connection will be established for each perform()
  void forbidReuse(int flag);

  //! wrap CURLOPT_NOSIGNAL: if true, prevents CURL from using signals; may be required for multi-threaded apps
  void noSignal(int flag);

  //! wrap CURLOPT_FAILONERR: if true, tells CURL to fail silently if the HTTP code returned is equal to or larger than 400
  void failOnError(int flag);

  //! wrap CURLOPT_VERBOSE (debug)
  void verbose(int flag);

  //--------
  //! set response data callback and data: wraps CURLOPT_WRITEFUNCTION, CURLOPT_WRITEDATA
  void setDataCallback(CurlWriteDataCallback handler=NULL, void *data=NULL);

  //! set default response data callback: catch all response data into m_Response
  inline void setDefaultDataCallback(void)
  { setDataCallback((CurlWriteDataCallback)cbWriteData_, (void*)&m_Response); };

  //--------
  //! set response header callback and data: wraps CURLOPT_HEADERFUNCTION, CURLOPT_HEADERDATA
  void setHeaderCallback(CurlWriteHeaderCallback handler=NULL, void *data=NULL);

  //! set default response data callback: catch all headers in m_Headers
  inline void setDefaultHeaderCallback(void)
  { setHeaderCallback((CurlWriteHeaderCallback)cbWriteHeader_, (void*)&m_Headers); };

  //--------
  //! default response data callback (cast to CurlWriteCallback for use with CURLOPT_WRITEFUNCTION)
  static size_t cbWriteData_(char *ptr, size_t size, size_t n, string *bufp);

  //--------
  //! default response header callback
  static size_t cbWriteHeader_(void *ptr, size_t size, size_t n, vector<string> *bufvp);
};

#endif /* DDC_CURL_H */

