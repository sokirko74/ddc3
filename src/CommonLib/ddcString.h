#ifndef DDC_STRING_H
#define DDC_STRING_H

#include "ddcConfig.h"
#include "utf8xx.h"
#include <stdarg.h>
#include <stdio.h>
#include <string>
#include <cstdint>
#include <vector>

//----------------------------------------------------------------------
// C escapes
//

/* Encode C escapes into string; encodes byte-wise with \xNN escapes */
std::string escapeCString(const std::string &s);

/* Decode C escapes in string. Also supports json-style "\uXXXX" utf8-escapes */
std::string unescapeCString(const std::string &s);
//

//----------------------------------------------------------------------
// JSON escapes
//

/* Encode JSON escapes into string.
 *  - If assume_utf8 is true (default),
 *  leaves bytes with high-bit set alone; otherwise encodes them as \uXXXX escapes.
 *  - If add_quotes is true, the returned string will be wrapped in JSON-friendly double quotes ("")
 */
std::string escapeJsonString(const std::string &s, bool assume_utf8=true, bool add_quotes=false);

/* Decode all JSON escapes from a string. */
std::string unescapeJsonString(const std::string &s);

/* wrapper for escapeJsonString */
inline std::string jsonStr(const std::string &s, bool assume_utf8=true, bool add_quotes=true)
{
    return escapeJsonString(s,assume_utf8,add_quotes);
}

/* jsonStr(unsigned char) maps to unsigned int */
inline std::string jsonStr(unsigned char b)
{
    char buf[4];
    sprintf(buf,"%u",b);
    return std::string(buf);
};

/* jsonStr(char) maps to single-character string */
inline std::string jsonStr(char c)
{
    return jsonStr(std::string(&c,1));
};

template<class Container>
std::string jsonArray(const Container &values)
{
    std::string s("[");
    for (typename Container::const_iterator vi=values.begin(); vi != values.end(); vi++) {
        if (s.size() > 1) s.push_back(',');
        s += jsonStr(*vi);
    }
    s.push_back(']');
    return s;
};

//

//----------------------------------------------------------------------
// Percent escapes (URL-encoding) 
//

/* URL-encode the string s with %XX escapes */
std::string escapeUrlString(const std::string &s);

/* Unescape URL-encoding %XX of s */
std::string unescapeUrlString(const std::string &s);
//

//----------------------------------------------------------------------
// UTF-8 escapes
//

/* Decode \uXXXX escapes from a string to UTF-8 */
std::string unescapeUtf8String(const std::string &s);

//! true iff s is valid UTF-8 (all ddc input must be UTF-8)
bool IsValidUtf8(const char *s, size_t len);
inline bool IsValidUtf8(const std::string &s) { return IsValidUtf8(s.data(), s.size()); }
//

//----------------------------------------------------------------------
// Generic backslash escapes
//

/* Escape selected characters chars in a string s */
std::string escapeChars(const std::string &s, const std::string &chars);

/* generate a single-quoted string */
std::string sqString(const std::string &s);

/* quote a regex in slashes // */
std::string reString(const std::string &re);

/* escape regex operators .*+?\ etc */
std::string escapeRegex(const std::string &re);
//

//----------------------------------------------------------------------
// printf-style formatting
//

/* wrapper for vsnprintf() which returns a C++ string */
std::string Format( const char* format, ... );

/* wrapper for vsnprintf(), va_list version */
std::string vFormat( const char* format, va_list& args );

//

//----------------------------------------------------------------------
// system errors
//

/* wrapper for strerror_r() if available, otherwise wraps strerror() */
char* StrError(int ErrorNo);

//

//----------------------------------------------------------------------
// string splitting
//

//--------------------------------------------------------------
/*
 * old string tokenizer from ../CommonLib/util_classes.h, utilit.cpp, rsp. ../CommonLib/string_tokenizer.h
 * see also stringSplitE() from utilit.cpp
 */
//-- string splitting and hex keys (formerly in utilit.h)

// moo: convenience wrapper for string-to-vector tokenization using StringTokenizer (no empty tokens)
std::vector<std::string> stringSplit(const char *s, const char *delims);

// moo: split a string using std::string() methods only, allowing empty tokens
// - appends token-strings to argument tokens
// - tokens is not implicitly cleared
void stringSplitE(const std::string& s, const std::string& delims, std::vector<std::string>& tokens);

// moo: stringSplitE() variant returning token-vector
std::vector<std::string> stringSplitE(const std::string& s, const std::string& delims);

// moo: int-to-hexidecimal string encoding; encoding preserves sort order (for subcorpus->server communications)
extern std::string int2hex(int32_t i);

// moo: int-to-hexidecimal string deccoding; ; encoding preserves sort order
extern int32_t hex2int(const std::string& s);

//-- StringTokenizer lives in nlp_base
#include "nlp_base/common/util_classes.h"



//--------------------------------------------------------------
/* pseudo-replacement for StringTokenizer (from utilit.h) which allows empty tokens
 * see also stringSplitE() from utilit.cpp
 */
class StringSplitter {
public:
    const std::string *srcp;      // source string (reference)
    const std::string *delimp;    // delimiter characters (reference)
    size_t begi;                  // start position of current token (string::npos after initilization)
    size_t endi;                  // end position of current token

public:

    /* constructor; positions at first available token */
    inline StringSplitter(const std::string& src, const std::string& delims)
        : srcp(&src), delimp(&delims)
    {
        begin();
    };

    /* position iterators to first token */
    inline void begin()
    {
        begi = 0;
        endi = srcp->find_first_of(*delimp, begi);
    };

    /* returns true iff the iterators point to a valid token */
    inline bool valid() const
    { return begi != std::string::npos; };

    /* cast-to-bool: wrapper for valid() */
    inline operator bool() const
    { return valid(); };

    /* get current token substring - should only be called if valid() is true */
    inline std::string current() const
    { return endi==std::string::npos ? srcp->substr(begi) : srcp->substr(begi,endi-begi); };

    /* dereference operator wraps current() */
    inline std::string operator*() const
    { return current(); };
  
    /* increment to next available token */
    inline void next()
    {
        begi = endi==std::string::npos ? endi : (endi+1);
        endi = begi==std::string::npos ? begi : srcp->find_first_of(*delimp,begi);
    };

    /* increment operator wraps next() */
    inline StringSplitter& operator++()
    {
        next();
        return *this;
    };
};

//----------------------------------------------------------------------
// string trimming
//

/* constructive variant of Trim() from utilit.(h|cpp): trims leading and trailing whitespace from argument, returns new trimmed string */
std::string TrimSafe(const std::string &str);

/* truncate string str to maxLen bytes if str.size() > max
 * returns true iff string was actually truncated
 */
inline bool TrimTruncate(std::string &str, size_t max)
{
    if (str.size() > max) {
        str.erase(max);
        return true;
    }
    return false;
};

/* verbose auto-truncation: logs a warning "LABEL ILABEL truncated to max=MAX bytes" on truncation */
void TrimTruncateV(std::string &str, size_t max, const char *label=NULL);

//

//----------------------------------------------------------------------
// bool parsing
//

/* option-parsing utility for boolean options */
bool StringToBool(const std::string &s, bool onempty=true);

/* boolean value reporting for options */
const char *BoolToString(bool b);

//


#endif /* DDC_STRING_H */
