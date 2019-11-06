//-*- Mode: C++ -*-
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2018 by Bryan Jurish
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

#include "../CommonLib/utilit.h"
#include "../CommonLib/ddcString.h"
#include "../CommonLib/ddcConfig.h"
#include "../CommonLib/ddcThread.h"
#include "LRUCache.h"
#include <pthread.h>

#ifdef HAVE_LIBCURL

 #include <curl/curl.h>
 typedef CURL* CurlHandle;
 typedef struct curl_sockaddr struct_curl_sockaddr;

#else /* !HAVE_LIBCURL */

 //! dummy typedef for missing libcurl
 typedef void* CurlHandle;
 typedef int curlsocktype;
 typedef void struct_curl_sockaddr;

 #define CURL_ERROR_SIZE 64

#endif /* HAVE_LIBCURL */

//======================================================================
// Globals

#if HAVE_PTHREAD
//! global mutex for non-thread-safe curl operations (global init, lru-cached proxy)
extern pthread_mutex_t ddcCurlMutex;
#endif

//! sentinel to determine whether curl_global_init() has been called
extern int ddcCurlInitialized;

//! \brief curl response cache, maps URLs to responses
typedef ddcLRUCache<std::string,std::string> CCurlCache;

//! global curl response cache to avoid TCP retransmissions due to multiple subcorpora
//! converging on a single shared expander
extern CCurlCache ddcCurlCache;

//! global initialization function (multiple calls should be safe)
extern void ddcInitCurl(void);


//======================================================================
//! \brief CCurl: abstract term expander using libcurl
class CCurl : public ddcLockable {
public:
  //! curl response content handler callback type; should return the number of bytes actually taken care of (== size*n on success)
  typedef size_t (*CurlWriteDataCallback) (char *ptr, size_t size, size_t n, void *userdata);

  //! curl response header callback type; should return the number of bytes actually taken care of (== size*n on success)
  typedef size_t (*CurlWriteHeaderCallback) (void *ptr, size_t size, size_t n, void *userdata);

  //! curl open socket callback type, should return the socket fd
  typedef curl_socket_t (*CurlOpenSocketCallback) (void *clientp, curlsocktype purpose, struct_curl_sockaddr *address);

  //! curl socket option callback type
  typedef int (*CurlSocketOptionCallback) (void *clientp, curl_socket_t curlfd, curlsocktype purpose);

public:
  //! curl handle
  CurlHandle m_Curl;

  //! current url (maybe UNIX-socket URL)
  string m_Url;

  //! current request URL (passed to libcurl)
  string m_RequestUrl;

  //! unix socket path (override)
  string m_UnixSocketPath;

  //! current timeout (seconds; default=60)
  long m_Timeout;

  //! maximum number of redirects (-1:no limit, 0:none)
  long m_Redirects;

  //! local curl error buffer
  char m_CurlErr[CURL_ERROR_SIZE];

  //! response content buffer (used by default write callback)
  string m_Response;

  //! response headers (used by default header callback)
  vector<string> m_Headers;

public:
  //! constructor implicitly calls url(url)
  CCurl(const string &url_=string(""), long timeout_=60, long redirects_=10);

  //! destructor implicitly frees m_Curl
  ~CCurl(void);

  //! prepare for another perform(): clears m_CurlErr, m_Response, and m_Headers
  void reset(void);

  //! Get response for request in m_Curl: wrapper for curl_easy_perform
  //! \li Returns false on error and populates m_CurlErr if the default callbacks are used
  //! \li implicitly calls reset()
  bool perform(void);

  //! Wrapper for perform() which uses a CCurlCache to guarantee that at most 1 query
  //! is sent per process and url.  Really only useful in conjunction with the default
  //! callbacks or something custom which populates m_Response with the data to be cached.
  //! \li implicitly calls reset()
  //! \li may call perform()
  //! \li on completion, cache should have an entry for the current m_Url
  bool perform_cached(CCurlCache *cache=&ddcCurlCache);

  //! Set default options: 
  bool SetDefaultOptions();

  //--------
  //! get current URL
  inline const string& url(void) const
  { return m_Url; };

  //! set current URL (sets m_Url, calls requestUrl(URL) and unixSocketPath(PATH)); auto-detects UNIX socket URLs of the form:
  //!  - "http:/path/to/unix/socket//uri/path"        (perl LWP::Protocol::http::SocketUnixAlt style)
  //!  - "unix:/path/to/unix/socket|http:///uri/path" (apache mod_proxy style)
  //!  - "http+unix:/path/to/unix/socket//uri/path"   (native)
  //!  - "http+unix:/path/to/unix/socket|/uri/path"   (native)
  void url(const string &url);

  //! guts for parsing unix socket URLs, called by url(url)
  //! \param[in]  url         user-specified URL to parse
  //! \param[out] unixPath    parsed unix socket path (empty on failure)
  //! \param[out] requestUrl  parsed request URL (empty on failure)
  //! \returns true iff a unix socket URL was detected, in which case unixPath is empty and requestUrl==url
  static bool parseUnixSocketUrl(const string& url, string& unixPath, string& requestUrl);
  
  //--------
  //! get low-level curl request URL
  inline const string& requestUrl(void) const
  { return m_RequestUrl; };

  //! set low-level curl request URL (wraps CURLOPT_URL)
  void requestUrl(const string& url);

  //--------
  //! get low-level unix socket path
  inline const string& unixSocketPath(void) const
  { return m_UnixSocketPath; };

  //! set unix socket path (m_UnixSocketPath); calls setUnixSocketPath()
  void unixSocketPath(const string& path);

  //--------
  //! get current timeout (seconds)
  inline long timeout(void) const
  { return m_Timeout; };

  //! set timeout (seconds)
  void timeout(long seconds);

  //--------
  //! get maximum number of redirects (-1: no limit)
  inline long redirects(void)
  { return m_Redirects; };

  //! set maximum number of redirects (-1: no limit, 0: disabled)
  void redirects(long redirects_);

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

  //--------
  //! setup UNIX socket callbacks for m_UnixSocketPath (for libcurl < 7.40.0)
  void setUnixSocketCallbacks(void);

  //! open UNIX socket callback (CURLOPT_UNIX_SOCKET_PATH emulation)
  static curl_socket_t cbOpenUnixSocket_(void *clientp, curlsocktype purpose, struct_curl_sockaddr *address);

  //! setsockopt wrapper for UNIX sockets (CURLOPT_UNIX_SOCKET_PATH emulation)
  static int cbUnixSocketOption_(void *clientp, curl_socket_t curlfd, curlsocktype purpose);

};

#endif /* DDC_CURL_H */


/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-default-style: "linux"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
