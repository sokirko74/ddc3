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
#include "ddcString.h"
#include "utilit.h"
#include <string.h>

using namespace std;

//======================================================================
// C Escapes

//--------------------------------------------------------------
string escapeCString(const std::string &s)
{
    string os("");
    os.reserve(s.size());

    for (string::const_iterator si=s.begin(); si!=s.end(); si++) {
        switch (*si) {
            case '\a': os.append("\\a"); break; //-- \x07: alert (bell)
            case '\b': os.append("\\b"); break; //-- \x08: backspace
            case '\t': os.append("\\t"); break; //-- \x09: tab
            case '\n': os.append("\\n"); break; //-- \x0a: newline
            case '\v': os.append("\\v"); break; //-- \x0b: vertical tab
            case '\f': os.append("\\f"); break; //-- \x0c: form feed
            case '\r': os.append("\\r"); break; //-- \x0d: carriage return
            case ' ':  os.append("\\x20"); break; //-- \x20: space
            case '\"':  os.append("\\\""); break; //-- double quotes
            case '\'':  os.append("\\\'"); break; //-- single quote
            case '\\':  os.append("\\\\"); break; //-- backslash
            default:
                if (((unsigned char)*si) < 0x20) {
                    //-- non-printing characters: use hex escapes
                    os.append(Format("\\x%0.2x", ((unsigned char)*si)));
                } else {
                    //-- literal
                    os.push_back(*si);
                }
                break;
        }
    }
    return os;
}

//--------------------------------------------------------------
string unescapeCString(const string &s)
{
    string os("");
    size_t si, sj, slen=s.size();
    int c;

    os.reserve(s.size());
    for (si=0, sj=s.find('\\',0); si < slen; si=sj+1, sj=s.find('\\',si)) {
        //-- copy: prefix
        os.append(s,si,sj-si);
        if (sj>=slen) break;

        //-- copy: backslash escape
        sj++;
        if (sj>=slen) { os.push_back('\\'); break; } //-- trailing unescaped backslash: leave in place
        switch (s[sj]) {
            case 'a': c = '\a'; break; //-- \x07: alert (bell)
            case 'b': c = '\b'; break; //-- \x08: backspace
            case 't': c = '\t'; break; //-- \x09: tab
            case 'n': c = '\n'; break; //-- \x0a: newline
            case 'v': c = '\v'; break; //-- \x0b: vertical tab
            case 'f': c = '\f'; break; //-- \x0c: form feed
            case 'r': c = '\r'; break; //-- \x0d: carriage return
            case 'x': {
                //-- hex escape \xNN
                if (sj+1 < slen) {
                    int clen=-1;
                    const char *ss=s.c_str()+sj+1;
                    sscanf(ss, "%2x%n", &c, &clen);
                    if (clen >0) {
                        sj += clen;
                        break;
                    }
                }
                //-- not enough characters in string to parse escape
                os.push_back('\\');
                c  = 'x';
                break;
            }
            case 'u': {
                //-- json-style 16-bit unicode escape \uXXXX : interpret as utf8
                if (sj+1 < slen) {
                    const char *ss=s.c_str()+sj+1;
                    int clen;
                    ucs4 ucval;
                    sscanf(ss, "%4x%n", &ucval, &clen);
                    u8_wc_toutf8(os, ucval);
                    sj += clen;
                } else {
                    //-- not enough characters in string to parse escape
                    os.push_back('\\');
                    os.push_back('u');
                }
                continue;
            }
            case 'U': {
                //-- json-style 32-bit unicode escape \UXXXXXXXX : interpret as utf8
                if (sj+1 < slen) {
                    const char *ss=s.c_str()+sj+1;
                    int clen;
                    ucs4 ucval;
                    sscanf(ss, "%8x%n", &ucval, &clen);
                    u8_wc_toutf8(os, ucval);
                    sj += clen;
                } else {
                    //-- not enough characters in string to parse escape
                    os.push_back('\\');
                    os.push_back('U');
                }
                continue;
            }
            default:
                if (s[sj] >= '0' && s[sj] < '8') {
                    //-- octal escape \NNN
                    assert(sj+1<slen);
                    int clen=-1;
                    const char *ss=s.c_str()+sj;
                    sscanf(ss, "%3o%n", &c, &clen);
                    assert(clen>=0);
                    sj += clen;
                } else {
                    c = s[sj];
                }
                break;
        }
        os.push_back((char)c);
    }

    return os;
}

//======================================================================
// JSON Escapes

//--------------------------------------------------------------
extern std::string escapeJsonString(const std::string &s, bool assume_utf8, bool add_quotes)
{
    std::string js;
    js.reserve(s.size()+2);
    if (add_quotes) js.push_back('"');

    for (std::string::const_iterator si=s.begin(); si!=s.end(); si++) {
        switch (*si) {
            case '\b': js.append("\\b"); break;
            case '\t': js.append("\\t"); break;
            case '\n': js.append("\\n"); break;
            case '\f': js.append("\\f"); break;
            case '\r': js.append("\\r"); break;
            case '"':  js.append("\\\""); break;
            case '\\': js.append("\\\\"); break;
            default:
                if ( ((unsigned char)*si) <= 0x1f || (!assume_utf8 && ((unsigned char)*si) >= 0x80)) {
                    js.append(Format("\\u%0.4x", (unsigned char)*si));
                } else {
                    js.push_back(*si);
                }
                break;
        }
    }

    if (add_quotes) js.push_back('"');
    return js;
}

//--------------------------------------------------------------
string unescapeJsonString(const string &s)
{
    string os("");
    size_t si, sj, slen=s.size();
    int c;

    os.reserve(s.size());
    for (si=0, sj=s.find('\\',0); si < slen; si=sj+1, sj=s.find('\\',si)) {
        //-- copy: prefix
        os.append(s,si,sj-si);
        if (sj>=slen) break;

        //-- copy: backslash escape
        sj++;
        if (sj>=slen) { os.push_back('\\'); break; } //-- trailing unescaped backslash: leave in place
        switch (s[sj]) {
            case 'b': c = '\b'; break; //-- \x08: backspace
            case 't': c = '\t'; break; //-- \x09: tab
            case 'n': c = '\n'; break; //-- \x0a: newline
            case 'f': c = '\f'; break; //-- \x0c: form feed
            case 'r': c = '\r'; break; //-- \x0d: carriage return
            case 'u': {
                //-- json-style unicode escape \uXXXX : interpret as utf8
                assert(sj+1<slen);
                const char *ss=s.c_str()+sj+1;
                int clen;
                ucs4 ucval;
                sscanf(ss, "%4x%n", &ucval, &clen);
                u8_wc_toutf8(os, ucval);
                sj += clen;
                continue;
            }
            case 'U': {
                //-- fcs-style 32-bit unicode escape \UXXXXXXXX : interpret as utf8
                assert(sj+1<slen);
                const char *ss=s.c_str()+sj+1;
                int clen;
                ucs4 ucval;
                sscanf(ss, "%8x%n", &ucval, &clen);
                u8_wc_toutf8(os, ucval);
                sj += clen;
                continue;
            }
      
            default:
                c = s[sj];
                break;
        }
        os.push_back((char)c);
    }

    return os;
}

//======================================================================
// URL Escapes

//--------------------------------------------------------------
string escapeUrlString(const string &s)
{
    string os("");
    char   buf[4];

    os.reserve(s.size());
    for (string::const_iterator si=s.begin(); si != s.end(); si++) {
        if ((*si >= 'a' && *si <= 'z') 
            || (*si >= 'A' && *si <= 'Z')
            || (*si >= '0' && *si <= '9')
            || *si == '-'
            || *si == '_'
            || *si == '.'
            || *si == '~')
        {
            os.push_back(*si);
            continue;
        }
        snprintf(buf, 4, "%%%02X", ((unsigned char)*si));
        os.append(buf);
    }

    return os;
}

//--------------------------------------------------------------
string unescapeUrlString(const string &s)
{
    string os("");
    size_t si, sj, slen=s.size();
    int c, clen;

    os.reserve(s.size());
    for (si=0, sj=s.find('%',0); si < slen; si=sj+1, sj=s.find('%',si)) {
        //-- copy: prefix
        os.append(s,si,sj-si);
        if (sj>=slen) break;

        sj++;
        if (sj>=slen) { os.push_back('%'); break; } //-- trailing unescaped percent sign: leave in place

        const char *ss=s.c_str()+sj;
        sscanf(ss, "%2x%n", &c, &clen);
        assert(clen>=0);
        os.push_back((char)c);
        sj += clen;
    }

    return os;
}

//======================================================================
// UTF-8 Escapes

//--------------------------------------------------------------
string unescapeUtf8String(const string &s)
{
    string os("");
    size_t si, sj, slen=s.size();

    os.reserve(s.size());
    for (si=0, sj=s.find('\\',0); si < slen; si=sj+1, sj=s.find('\\',si)) {
        //-- copy: prefix
        os.append(s,si,sj-si);
        if (sj>=slen) break;

        sj++;
        if (sj >= slen) {
            //-- trailing unescaped backslash: leave in place
            os.push_back('\\');
            break;
        }
        if (s[sj]=='u' && sj+1 < slen) {
            //-- json-style 16-bit unicode escape \uXXXX : interpret as utf8
            const char *ss=s.c_str()+sj+1;
            int  clen;
            ucs4 ucval;
            sscanf(ss, "%4x%n", &ucval, &clen);
            u8_wc_toutf8(os, ucval);
            sj += clen;
            continue;
        }
        if (s[sj]=='U' && sj+1 < slen) {
            //-- json-style 32-bit unicode escape \UXXXXXXXX : interpret as utf8
            const char *ss=s.c_str()+sj+1;
            int  clen;
            ucs4 ucval;
            sscanf(ss, "%8x%n", &ucval, &clen);
            u8_wc_toutf8(os, ucval);
            sj += clen;
            continue;
        }
   
        else {
            //-- some other backslash escape: leave it and the following character in place
            os.push_back('\\');
            os.push_back(s[sj]);
        }
    }

    return os;
}

//======================================================================
// Generic Backslash Escapes

//--------------------------------------------------------------
string escapeChars(const string &s, const string &chars)
{
    string os("");
    size_t si, sj, slen=s.size();

    os.reserve(s.size());
    for (si=0, sj=s.find_first_of(chars,si); si < slen; si=sj+1, sj=s.find_first_of(chars,si)) {
        //-- copy: prefix
        os.append(s,si,sj-si);
        if (sj>=slen) break;
        os.push_back('\\');
        os.push_back(s[sj]);
    }

    return os;
}

//--------------------------------------------------------------
string sqString(const std::string &s)
{
    return string("'") + escapeChars(s,"\\'") + "'";
}

//--------------------------------------------------------------
string reString(const std::string &re)
{
    return string("/") + escapeChars(re,"/") + "/";
}

//--------------------------------------------------------------
string escapeRegex(const std::string &re)
{
    return escapeChars(re,".*+?{}()\\");
}

//======================================================================
// printf-style formatting

//--------------------------------------------------------------
string Format( const char* format, ... )
{
    va_list arglst;
    const size_t  SmallBufferSize = DDC_STATIC_BUFLEN;
    char SmallBuffer[SmallBufferSize];

    va_start( arglst, format );
    int OutputLength = 1 + vsnprintf( SmallBuffer, SmallBufferSize, format, arglst) ;
    va_end( arglst );

    if ((OutputLength == 0) || (OutputLength < SmallBufferSize))
        return string(SmallBuffer,OutputLength-1);

    char * pBuffer = new char[OutputLength];
    if (!pBuffer)
        return string(SmallBuffer,SmallBufferSize);
    va_start( arglst, format );
    vsnprintf( pBuffer, OutputLength, format, arglst);
    va_end( arglst );
    string Result(pBuffer,OutputLength-1);
    delete pBuffer;
    return Result;
};


//--------------------------------------------------------------
string vFormat( const char* format, va_list& args )
{
    const size_t  SmallBufferSize = DDC_STATIC_BUFLEN;
    char SmallBuffer[SmallBufferSize];

    va_list args1;
    va_copy(args1, args);
    int OutputLength = 1 + vsnprintf( SmallBuffer, SmallBufferSize, format, args);
    
    if ((OutputLength == 0) || (OutputLength < SmallBufferSize))
        return string(SmallBuffer,OutputLength-1);

    char * pBuffer = new char[OutputLength];
    if (!pBuffer)
        return string(SmallBuffer,SmallBufferSize);
    vsnprintf( pBuffer, OutputLength, format, args1);
    string Result(pBuffer,OutputLength-1);
    delete pBuffer;
    return Result;
}

//======================================================================
// system errors

char* StrError(int ErrorNo)
{
#if HAVE_STRERROR_R
    char buf[512];
    return strerror_r(ErrorNo, buf, 512);
#else
    return strerror(ErrorNo);
#endif
}

//======================================================================
// string tokenization

//--------------------------------------------------------------
void StringTokenizer::initialize(const char *_text, const char *_delims)
{
    delims = _delims;
    i = -1;
    size_t leng = strlen(_text);
    text_ptr = new char[leng+2];
    text = text_ptr;
    strcpy(text, _text);
    text[leng+1] = 0;
}

void StringTokenizer::reinitialize(const char *_text, const char *_delims)
{
    assert (text_ptr);
    delete[] text_ptr;
    initialize(_text, _delims);
}

//--------------------------------------------------------------
StringTokenizer::StringTokenizer(const char *_text, const char *_delims)
{
    initialize(_text, _delims);
}

//--------------------------------------------------------------
StringTokenizer::~StringTokenizer()
{
    delete[] text_ptr;
}

//--------------------------------------------------------------
const char * StringTokenizer::operator()()
{
    ++i;
    // skip delims
    while(*text && is_delim(*text))
        text++;

    if(*text == '\0')
        return NULL;

    char *ret_val = text;
    while(*text && !is_delim(*text))
        text++;
    *text++ = '\0';
    _val = ret_val;

    if (_val == NULL)
        throw CExpc ("Exception in StringTokenizer::operator ()");
  
    return ret_val;
}

//--------------------------------------------------------------
std::string StringTokenizer::next_token ()
{
    const char* s = operator()();
    if (s) 
        return s;
    else 
        return std::string();
}

//--------------------------------------------------------------
void StringTokenizer::get_tokens(std::vector<std::string> &tokens)
{
    while ( operator()() )
        tokens.push_back(_val);
}

//--------------------------------------------------------------
const char* StringTokenizer::get_rest_trim()
{
    char *s = text;
    while (*s && is_delim(*s)) ++s;
    int j = strlen(s) - 1;
    while (j >= 0 && (s[j]=='\0' || is_delim(s[j]))) --j;
    s[j+1] = '\0';
    return s;
}

//======================================================================
// string trimming

//--------------------------------------------------------------
std::string TrimSafe(const std::string &str)
{
    size_t i = str.find_first_not_of(" \t\r\n");
    size_t j = str.find_last_not_of(" \t\r\n");
    if (i >= j) return string();
    return str.substr(i, j-i+1);
}

//======================================================================
// string <-> bool

bool StringToBool(const std::string &s, bool onempty)
{
    if (s.empty()) return onempty;
    string ls = stolower(s);
    return (ls!="no" && ls!="n" && ls!="false" && ls!="off" && ls!="disabled" && ls!="0");
}

const char *BoolToString(bool b)
{
    return b ? "true" : "false";
}

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
