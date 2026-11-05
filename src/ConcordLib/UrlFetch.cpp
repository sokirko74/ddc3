#include "UrlFetch.h"
#include "nlp_base/common/utilit.h"
#include "nlp_base/contrib/httplib/httplib.h"

#include <algorithm>

using namespace std;

#if HAVE_PTHREAD
static pthread_mutex_t UrlCacheMutex = PTHREAD_MUTEX_INITIALIZER;
#endif

static const int UrlCacheCapacity = 1024;
CUrlCache UrlCache(UrlCacheCapacity, DDC_IFPTHREADELSE(&UrlCacheMutex,NULL));

//--------------------------------------------------------------
bool ParseUnixSocketUrl(const string& url, string& unixPath, string& requestUrl)
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
            unixPath = url.substr(i_pbegin,i_pend-i_pbegin);

            if (scheme.size() >= 5 && scheme.rfind("+unix")==scheme.size()-5) {
                //-- "http+unix:/path/to/unix/socket//uri/path", "http+unix:/path/to/unix/socket|uri/path"
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

            //-- host-less request urls
            size_t i_nohost = requestUrl.find(":///");
            if (i_nohost != string::npos)
                requestUrl.insert(i_nohost+3, "localhost");

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
/* split "http://HOST[:PORT]/PATH" into "http://HOST[:PORT]" and "/PATH" */
static bool SplitUrl(const string& url, string& schemeHostPort, string& path)
{
    size_t i = url.find("://");
    if (i == string::npos) return false;
    size_t j = url.find('/', i+3);
    schemeHostPort = url.substr(0, j);
    path = (j == string::npos) ? string("/") : url.substr(j);
    return true;
}

//--------------------------------------------------------------
static bool HttpGet(const string& url, int timeout, string& response, string& errorStr)
{
    string unixPath, requestUrl, schemeHostPort, path;
    bool isUnix = ParseUnixSocketUrl(url, unixPath, requestUrl);
    if (!SplitUrl(requestUrl, schemeHostPort, path)) {
        errorStr = "bad url " + url;
        return false;
    }
    std::unique_ptr<httplib::Client> cli;
    if (isUnix) {
        cli.reset(new httplib::Client(unixPath, 80));
        cli->set_address_family(AF_UNIX);
    } else {
        cli.reset(new httplib::Client(schemeHostPort));
    }
    if (!cli->is_valid()) {
        errorStr = "unsupported url " + url;
        return false;
    }
    cli->set_connection_timeout(timeout, 0);
    cli->set_read_timeout(timeout, 0);
    cli->set_write_timeout(timeout, 0);
    auto res = cli->Get(path);
    if (!res) {
        errorStr = httplib::to_string(res.error());
        return false;
    }
    if (res->status != httplib::StatusCode::OK_200) {
        errorStr = Format("http status %i", res->status);
        return false;
    }
    response = std::move(res->body);
    return true;
}

//--------------------------------------------------------------
bool FetchUrl(const string& url, int timeout, string& response, string& errorStr, CUrlCache* cache)
{
    response.clear();
    errorStr.clear();
    if (!cache)
        return HttpGet(url, timeout, response, errorStr);
    cache->lock();
    bool rc = true;
    CUrlCache::iterator cachei = cache->get(url);
    if (cachei != cache->end()) {
        response = cachei->second->second;
    } else {
        rc = HttpGet(url, timeout, response, errorStr);
        if (rc)
            cache->insert(url, response);
    }
    cache->unlock();
    return rc;
}
