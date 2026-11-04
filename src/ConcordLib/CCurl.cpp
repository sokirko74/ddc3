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
#define CURLOPT_FOLLOWLOCATION -1
#define CURLOPT_MAXREDIRS -1
#define CURLOPT_UNIX_SOCKET_PATH -1
#define CURLOPT_POSTREDIR -1
#define CURL_REDIR_POST_ALL -1
#define CURL_SOCKOPT_ALREADY_CONNECTED -1
#define CURLE_OK -1
#define curl_easy_setopt(handle,opt,val)
#define curl_easy_perform(handle) -1
#define curl_easy_cleanup(handle) -1
#endif /* HAVE_LIBCURL */

#ifndef CURL_REDIR_POST_ALL
# define CURL_REDIR_POST_ALL -1L
#endif

//-- sanity check for UNIX socket emulation
#if !defined(DDC_HAVE_CURL_UNIX_SUPPORT) && !defined(DDC_ENABLE_CURL_UNIX_SOCKETS)
# ifdef DDC_ENABLE_CURL_UNIX_URLS
#  warning implicit parsing of UNIX URLs disabled (neither DDC_HAVE_CURL_UNIX_SUPPORT nor DDC_ENABLE_CURL_UNIX_SOCKETS are defined)
# endif
# undef DDC_ENABLE_CURL_UNIX_URLS
#endif

#ifdef DDC_HAVE_UNIX_SOCKET_HEADERS
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/un.h>
#include "../CommonLib/ddcExpc.h"
#include "../CommonLib/DDCInternalError.h"
#endif

using namespace std;

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
CCurl::CCurl(const string &url_, long timeout_, long redirects_)
    : m_Curl(NULL)
{
    ddcInitCurl();
    m_Curl = curl_easy_init();
    curl_easy_setopt(m_Curl, CURLOPT_ERRORBUFFER, m_CurlErr);
    reset();
    url(url_);
    timeout(timeout_);
    redirects(redirects_);
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
bool CCurl::parseUnixSocketUrl(const string& url, string& unixPath, string& requestUrl)
{
    bool rc = false;
    size_t i_colon = url.find(':');
    if (i_colon != string::npos) {
        string scheme = url.substr(0,i_colon);
    
        size_t i_vbar     = url.find('|', i_colon);
        size_t i_slashes1 = url.find("//",i_colon);
        size_t i_slashes2 = i_slashes1==string::npos ? i_slashes1 : url.find("//",i_slashes1+2);
        size_t i_pbegin   = (i_slashes1==i_colon+1 ? i_slashes1+2 : i_colon+1);
        size_t i_pend     = std::min((i_slashes1==i_colon+1 ? i_slashes2 : i_slashes1), i_vbar);

        if (i_pbegin < url.size() && i_pend < url.size()) {
            //-- url might have a valid unix socket path
            unixPath = url.substr(i_pbegin,i_pend-i_pbegin);

            if (scheme.size() >= 5 && scheme.rfind("+unix")==scheme.size()-5) {
                //-- "http+unix:/path/to/unix/socket//uri/path
                //-- "http+unix:/path/to/unix/socket|uri/path
                scheme.erase(scheme.size()-5);
                requestUrl = scheme + "://" + url.substr(i_pend+1);
                rc = true;
            }
            else if (scheme == "unix") {
                //-- "unix:/path/to/unix/socket|http:///uri/path"
                requestUrl = url.substr(i_pend+1);
                rc = true;
            }
            else if ((scheme=="http" || scheme=="https") && i_slashes1 != i_colon+1) {
                //-- "http:/path/to/unix/socket//uri/path"
                requestUrl = scheme + "://" + url.substr(i_slashes1+1);
                rc = true;
            }

            //-- detect and repair host-less request URLs (otherwise CURL drops leading request path element)
            size_t i_nohost = requestUrl.find(":///");
            if (i_nohost != string::npos)
                requestUrl.insert(i_nohost+3, "localhost");

            //-- sanity check: no empty unix socket path or request url
            rc = rc && !(unixPath.empty() || requestUrl.empty());
        }
    }
    if (!rc) {
        unixPath.clear();
        requestUrl = url;
    }
    return rc;
}

//--------------------------------------------------------------
void CCurl::url(const string& url)
{
    m_Url = url;
#if DDC_ENABLE_CURL_UNIX_URLS
    parseUnixSocketUrl(m_Url, m_UnixSocketPath, m_RequestUrl);
    unixSocketPath(m_UnixSocketPath);
    requestUrl(m_RequestUrl);
#else
    requestUrl(m_Url);
#endif
}

//--------------------------------------------------------------
void CCurl::requestUrl(const string& url)
{
    m_RequestUrl = url;
    curl_easy_setopt(m_Curl, CURLOPT_URL, (url.empty() ? NULL : url.c_str()));
}

//--------------------------------------------------------------
void CCurl::unixSocketPath(const string& path)
{
    m_UnixSocketPath = path;
    if (!path.empty())
        setUnixSocketCallbacks();
}


//--------------------------------------------------------------
void CCurl::timeout(long seconds)
{
    m_Timeout = seconds;
    curl_easy_setopt(m_Curl, CURLOPT_TIMEOUT, seconds);
}

//--------------------------------------------------------------
void CCurl::redirects(long redirects_)
{
    m_Redirects = redirects_;
    curl_easy_setopt(m_Curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(m_Curl, CURLOPT_MAXREDIRS, m_Redirects);
    curl_easy_setopt(m_Curl, CURLOPT_POSTREDIR, CURL_REDIR_POST_ALL);
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
void CCurl::setUnixSocketCallbacks(void)
{
#if defined(DDC_ENABLE_CURL_UNIX_SOCKETS)
    curl_easy_setopt(m_Curl, CURLOPT_TCP_NODELAY, 0);  
    curl_easy_setopt(m_Curl, CURLOPT_OPENSOCKETFUNCTION, (CurlOpenSocketCallback)cbOpenUnixSocket_);
    curl_easy_setopt(m_Curl, CURLOPT_SOCKOPTFUNCTION, (CurlSocketOptionCallback)cbUnixSocketOption_);
    curl_easy_setopt(m_Curl, CURLOPT_OPENSOCKETDATA, (void*)this);
#elif defined(DDC_HAVE_CURL_UNIX_SUPPORT)
    curl_easy_setopt(m_Curl, CURLOPT_UNIX_SOCKET_PATH, m_UnixSocketPath.c_str());
#else
    throw CDDCExpc(errOther, "CCurl::setUnixSocketCallbacks(): UNIX socket handlers disabled");
#endif
}

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

//--------------------------------------------------------------
curl_socket_t CCurl::cbOpenUnixSocket_(void *clientp, curlsocktype purpose, struct_curl_sockaddr *address)
{
#ifndef DDC_ENABLE_CURL_UNIX_SOCKETS
    return -1;
#else
    CCurl* ccurl = (CCurl*)clientp;
    curl_socket_t sockfd;
    struct sockaddr_un sun;

    sockfd = socket(PF_LOCAL, SOCK_STREAM, 0);
    if (sockfd < 0) return sockfd; //-- open failed

    memset(&sun,0,sizeof(sun));
    sun.sun_family = AF_LOCAL;
    strncpy(sun.sun_path, ccurl->m_UnixSocketPath.c_str(), sizeof(sun.sun_path)-1);

    if (connect(sockfd, (struct sockaddr *)&sun, sizeof(struct sockaddr_un)) < 0) {
        close(sockfd);
        return -1;
    }

    //fprintf(stderr, "DEBUG: CCurl::cbOpenUnixSocket_(): opened %s on fd #%d [addrlen=%zd]\n", ccurl->m_UnixSocketPath.c_str(), sockfd, address->addrlen);
  
    return sockfd;
#endif
}

//-------------------------------------------------------------- 
int CCurl::cbUnixSocketOption_(void *clientp, curl_socket_t curlfd, curlsocktype purpose)
{
#ifdef DDC_HAVE_CURL_ALREADY_CONNECTED
    /* This return code was added in libcurl 7.21.5 */
    return CURL_SOCKOPT_ALREADY_CONNECTED;
#else
    return CURLE_OK;
#endif
}
