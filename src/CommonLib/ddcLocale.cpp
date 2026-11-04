#include "ddcLocale.h"
#include <cstring>
#include "morph_dict/common/utilit.h"
#include "ddcUtil.h"
#include <wchar.h>
#include <wctype.h>
#include <limits.h>

using namespace std;

//--------------------------------------------------------------
bool ddcLocaleInitialized = false;

//--------------------------------------------------------------
void ddcInitLocale(void)
{
    if (!ddcLocaleInitialized) {
        setlocale(LC_ALL,""); //-- initialize locale from current environment
    }
    ddcLocaleInitialized = true;
}

//======================================================================
// Wide Character Strings

//--------------------------------------------------------------
std::wstring string2wstring(const std::string &src)
{
    ddcInitLocale(); //-- ensure locale has been initialized
    const char *srcp = src.data();
    size_t src_len = src.size();
    size_t c_len;
    mbstate_t state;
    memset(&state, '\0', sizeof(state)); //-- (re-)initialize conversion state
    std::wstring dst;
    wchar_t dst_c;
    dst.reserve(src_len);
    for (; src_len > 0; srcp += c_len, src_len -= c_len) {
        c_len = mbrtowc(&dst_c, srcp, src_len, &state);
        if (c_len == 0) {
            //-- NUL byte
            c_len = 1;
            dst_c = L'\0';
        }
        else if (c_len == (size_t)-2) {
            //-- conversion error: incomplete multibyte sequence
            fprintf(stderr,"string2wstring(): incomplete multibyte sequence starting with `%c'\n", src[src.size()-src_len]);
            dst.push_back((wchar_t)((unsigned char)*srcp));   //-- latin-1 hack: push raw byte value
            c_len = 1;
            continue;
        }
        else if (c_len == (size_t)-1) {
            //-- conversion error: invalid multibyte sequence
            fprintf(stderr,"string2wstring(): invalid multibyte sequence starting with `%c'\n", src[src.size()-src_len]);
            dst.push_back((wchar_t)((unsigned char)*srcp)); //-- latin-1 hack: push raw byte value
            c_len = 1;
            continue;
        }
        dst.push_back(dst_c);
    }
    return dst;
}

//--------------------------------------------------------------
std::string wstring2string(const std::wstring &src)
{
    ddcInitLocale(); //-- ensure locale has been initialized
    const wchar_t *srcp = src.data();
    size_t src_len = src.size();
    size_t c_len;
    mbstate_t state;
    memset(&state, '\0', sizeof(state)); //-- (re-)initialize conversion state
    std::string dst;
    dst.reserve(src_len);
    for (; src_len > 0; srcp++, src_len--) {
        char dst_buf[MB_LEN_MAX];
        c_len = wcrtomb(dst_buf, *srcp, &state);
        if (c_len == (size_t)-1) {
            //-- conversion error: *srcp is not a valid wide character: skip it
            fprintf(stderr,"wstring2string(): invalid wide character 0x%04x\n", (int)src[src.size()-src_len]);
            c_len = 1;
            continue;
        }
        dst.append(dst_buf,c_len);
    }
    return dst;
}

//--------------------------------------------------------------
std::wstring wstoupper(const std::wstring &ws)
{
    wstring dst;
    dst.reserve(ws.size());
    for (wstring::const_iterator wsi=ws.begin(); wsi!=ws.end(); wsi++) {
        dst.push_back(towupper(*wsi));
    }
    return dst;
}

//--------------------------------------------------------------
std::wstring wstolower(const std::wstring &ws)
{
    wstring dst;
    dst.reserve(ws.size());
    for (wstring::const_iterator wsi=ws.begin(); wsi!=ws.end(); wsi++) {
        dst.push_back(towlower(*wsi));
    }
    return dst;
}

//--------------------------------------------------------------
std::string stoupper(const std::string &s)
{
    return wstring2string(wstoupper(string2wstring(s)));
}

//--------------------------------------------------------------
std::string stolower(const std::string &s)
{
    return wstring2string(wstolower(string2wstring(s)));
}

//--------------------------------------------------------------
std::string& ddcMakeUpper(std::string& word, MorphLanguageEnum langua)
{
    if (langua == morphGeneric)
        word = stoupper(word);
    else
        RmlMakeUpper(word, langua);
    return word;
}

//--------------------------------------------------------------
char* ddcMakeUpper(char* word, MorphLanguageEnum langua)
{
    if (!word) return word;
    std::string s(word);
    ddcMakeUpper(s, langua);
    strncpy(word, s.c_str(), s.size());
    return word;
}

//--------------------------------------------------------------
std::string& ddcMakeLower(std::string& word, MorphLanguageEnum langua)
{
    if (langua == morphGeneric)
        word = stolower(word);
    else
        RmlMakeLower(word, langua);
    return word;
}
