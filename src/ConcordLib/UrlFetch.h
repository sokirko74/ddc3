#pragma once

/* http GET of a url (cpp-httplib) with a response cache; used by the Cab term expanders */

#include "LRUCache.h"
#include <string>

typedef ddcLRUCache<std::string,std::string> CUrlCache;

/* the global response cache (successful responses only) */
extern CUrlCache UrlCache;

/* split a UNIX socket url into the socket path and the request url; returns false for other urls
 *  - http+unix:/path/to/unix/socket//uri/path
 *  - http+unix:/path/to/unix/socket|uri/path
 *  - unix:/path/to/unix/socket|http:///uri/path
 *  - http:/path/to/unix/socket//uri/path
 */
extern bool ParseUnixSocketUrl(const std::string& url, std::string& unixPath, std::string& requestUrl);

/* GET url (http://HOST[:PORT]/PATH?QUERY or a UNIX socket url, see ParseUnixSocketUrl)
 *  - at most one request for an url at a time, successful responses are cached
 *  - returns false on errors (errorStr describes the error)
 */
extern bool FetchUrl(const std::string& url, int timeout, std::string& response, std::string& errorStr,
                     CUrlCache* cache=&UrlCache);
