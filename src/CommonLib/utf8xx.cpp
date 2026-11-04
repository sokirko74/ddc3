/*
  Basic UTF-8 manipulation routines
  by Jeff Bezanson
  placed in the public domain Fall 2005

  This code is designed to provide the utilities you need to manipulate
  UTF-8 as an internal string encoding. These functions do not perform the
  error checking normally needed when handling UTF-8 data, so if you happen
  to be from the Unicode Consortium you will want to flay me alive.
  I do this because error checking can be performed at the boundaries (I/O),
  with these routines reserved for higher performance on data known to be
  valid.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#if 0
/* Tue, 23 Feb 2016 14:24:52 +0100
 * + disable from non-POSIX alloca.h (used by u8_vprintf(), u8_printf())
 */
#include <alloca.h>
#endif /*-- disable alloca.h dependency --*/

#include "utf8xx.h"

using namespace std;

static const u_int32_t offsetsFromUTF8[6] = {
    0x00000000UL, 0x00003080UL, 0x000E2080UL,
    0x03C82080UL, 0xFA082080UL, 0x82082080UL
};

static const char trailingBytesForUTF8[256] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
};

/** returns length of next utf-8 sequence */
int u8_seqlen(const utf8str &s, size_t i)
{
    return trailingBytesForUTF8[(unsigned int)(unsigned char)s[i]] + 1;
}

/* conversions without error checking
   only works for valid UTF-8, i.e. no 5- or 6-byte sequences
   srcsz = source size in bytes, or -1 if 0-terminated
   sz = dest size in # of wide characters

   returns # characters converted
   dest will always be L'\0'-terminated, even if there isn't enough room
   for all the characters.
   if sz = srcsz+1 (i.e. 4*srcsz+4 bytes), there will always be enough space.
*/
size_t u8_toucs(ucs4str &dst, const utf8str &src)
{
    size_t nc=0;
    for (utf8str::const_iterator si=src.begin(); si!=src.end(); si++,nc++) {
        ucs4 ch = 0;
        int nb = trailingBytesForUTF8[(unsigned char)*si];
        switch (nb) {
            /* these fall through deliberately */
            case 3: ch += (unsigned char)*si++; ch <<= 6;
            case 2: ch += (unsigned char)*si++; ch <<= 6;
            case 1: ch += (unsigned char)*si++; ch <<= 6;
            case 0: ch += (unsigned char)*si++;
        }
        ch -= offsetsFromUTF8[nb];
        dst.push_back(ch);
    }
    return nc;
}

/** convert UTF-8 byte string \c src to a new UCS-4 string */
ucs4str u8_toucs(const utf8str &src)
{
    ucs4str dest;
    dest.reserve(src.size());
    u8_toucs(dest,src);
    return dest;
}

/* returns # characters converted
   OLD: dest will only be '\0'-terminated if there is enough space. this is
   for consistency; imagine there are 2 bytes of space left, but the next
   character requires 3 bytes. in this case we could NUL-terminate, but in
   general we can't when there's insufficient space. therefore this function
   only NUL-terminates if all the characters fit, and there's space for
   the NUL as well.
   the destination string will never be bigger than the source string.
*/
size_t u8_toutf8(utf8str &dst, const ucs4str &src)
{
    size_t nc=0;
    for (ucs4str::const_iterator si=src.begin(); si != src.end(); si++,nc++) {
        ucs4 ch = *si;
        if (ch < 0x80) {
            dst.push_back((char)ch);
        }
        else if (ch < 0x800) {
            dst.push_back((ch>>6) | 0xC0);
            dst.push_back((ch & 0x3F) | 0x80);
        }
        else if (ch < 0x10000) {
            dst.push_back((ch>>12) | 0xE0);
            dst.push_back(((ch>>6) & 0x3F) | 0x80);
            dst.push_back((ch & 0x3F) | 0x80);
        }
        else if (ch < 0x110000) {
            dst.push_back((ch>>18) | 0xF0);
            dst.push_back(((ch>>12) & 0x3F) | 0x80);
            dst.push_back(((ch>>6) & 0x3F) | 0x80);
            dst.push_back((ch & 0x3F) | 0x80);
        }
    }
    return nc;
}

utf8str u8_toutf8(const ucs4str &src)
{
    utf8str dst;
    dst.reserve(src.size());
    u8_toutf8(dst,src);
    return dst;
}

/*-- moo: get number of bytes required for representing a wide character \a ch in UTF-8 --*/
size_t u8_wc_len(ucs4 ch)
{
    if (ch < 0x80) return 1;
    if (ch < 0x800) return 2;
    if (ch < 0x10000) return 3;
    if (ch < 0x110000) return 4;
    return 0;  //-- bad char (?)
}

/*-- moo: get number of bytes required for representing a wide character string \a ws ch in UTF-8 --*/
size_t u8_ws_len(const ucs4str &src)
{
    size_t len=0;
    for (ucs4str::const_iterator si=src.begin(); si != src.end(); si++) {
        len += u8_wc_len(*si);
    }
    return len;
}

size_t u8_wc_toutf8(utf8str &dst, ucs4 ch)
{
    if (ch < 0x80) {
        dst.push_back((char)ch);
        return 1;
    }
    if (ch < 0x800) {
        dst.push_back((ch>>6) | 0xC0);
        dst.push_back((ch & 0x3F) | 0x80);
        return 2;
    }
    if (ch < 0x10000) {
        dst.push_back((ch>>12) | 0xE0);
        dst.push_back(((ch>>6) & 0x3F) | 0x80);
        dst.push_back((ch & 0x3F) | 0x80);
        return 3;
    }
    if (ch < 0x110000) {
        dst.push_back((ch>>18) | 0xF0);
        dst.push_back(((ch>>12) & 0x3F) | 0x80);
        dst.push_back(((ch>>6) & 0x3F) | 0x80);
        dst.push_back((ch & 0x3F) | 0x80);
        return 4;
    }
    return 0;
}

utf8str u8_wc_toutf8(ucs4 ch)
{
    utf8str dst;
    dst.reserve(u8_wc_len(ch));
    u8_wc_toutf8(dst,ch);
    return dst;
}

/* charnum => byte offset */
size_t u8_offset(const utf8str &s, int charnum)
{
    size_t offs=0;
    while (charnum > 0 && offs<s.size()) {
        (void)(isutf(s[++offs]) || isutf(s[++offs]) ||
               isutf(s[++offs]) || ++offs);
        charnum--;
    }
    return offs;
}

/* byte offset => charnum */
size_t u8_charnum(const utf8str &s, int offset)
{
    int charnum = 0, offs=0;

    while (offs < offset && offs < s.size()) {
        (void)(isutf(s[++offs]) || isutf(s[++offs]) ||
               isutf(s[++offs]) || ++offs);
        charnum++;
    }
    return charnum;
}

/* reads the next utf-8 sequence out of a string, updating an index */
ucs4 u8_nextchar(const utf8str &s, size_t *i)
{
    ucs4 ch = 0;
    int sz = 0;

    do {
        ch <<= 6;
        ch += (unsigned char)s[(*i)++];
        sz++;
    } while (*i<s.size() && !isutf(s[*i]));
    ch -= offsetsFromUTF8[sz-1];

    return ch;
}

/*-- moo: reads the next utf-8 sequence out of a string, updating an index, and not exceeding a given length */
ucs4 u8_nextcharn(const utf8str &s, size_t slen, size_t *i)
{
    ucs4 ch = 0;
    int sz = 0;

    do {
        ch <<= 6;
        ch += (unsigned char)s[(*i)++];
        sz++;
    } while (*i<slen && *i<s.size() && !isutf(s[*i]));
    ch -= offsetsFromUTF8[sz-1];

    return ch;
}

/* number of characters */
size_t u8_strlen(const utf8str &s)
{
    size_t count=0, i=0;
    while (u8_nextchar(s, &i) != 0)
        count++;
    return count;
}

void u8_inc(const utf8str &s, size_t *i)
{
    (void)(isutf(s[++(*i)]) || isutf(s[++(*i)]) ||
           isutf(s[++(*i)]) || ++(*i));
}

void u8_dec(const utf8str &s, size_t *i)
{
    (void)(isutf(s[--(*i)]) || isutf(s[--(*i)]) ||
           isutf(s[--(*i)]) || --(*i));
}

int octal_digit(char c)
{
    return (c >= '0' && c <= '7');
}

int hex_digit(char c)
{
    return ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'F') ||
            (c >= 'a' && c <= 'f'));
}

#ifdef UTF8XX_C_API

/* assumes that src points to the character after a backslash
   returns number of input characters processed */
int u8_read_escape_sequence(char *str, u_int32_t *dest)
{
    u_int32_t ch;
    char digs[9]="\0\0\0\0\0\0\0\0";
    int dno=0, i=1;

    ch = (u_int32_t)str[0];    /* take literal character */
    if (str[0] == 'n')
        ch = L'\n';
    else if (str[0] == 't')
        ch = L'\t';
    else if (str[0] == 'r')
        ch = L'\r';
    else if (str[0] == 'b')
        ch = L'\b';
    else if (str[0] == 'f')
        ch = L'\f';
    else if (str[0] == 'v')
        ch = L'\v';
    else if (str[0] == 'a')
        ch = L'\a';
    else if (octal_digit(str[0])) {
        i = 0;
        do {
            digs[dno++] = str[i++];
        } while (octal_digit(str[i]) && dno < 3);
        ch = strtol(digs, NULL, 8);
    }
    else if (str[0] == 'x') {
        while (hex_digit(str[i]) && dno < 2) {
            digs[dno++] = str[i++];
        }
        if (dno > 0)
            ch = strtol(digs, NULL, 16);
    }
    else if (str[0] == 'u') {
        while (hex_digit(str[i]) && dno < 4) {
            digs[dno++] = str[i++];
        }
        if (dno > 0)
            ch = strtol(digs, NULL, 16);
    }
    else if (str[0] == 'U') {
        while (hex_digit(str[i]) && dno < 8) {
            digs[dno++] = str[i++];
        }
        if (dno > 0)
            ch = strtol(digs, NULL, 16);
    }
    *dest = ch;

    return i;
}

/* convert a string with literal \uxxxx or \Uxxxxxxxx characters to UTF-8
   example: u8_unescape(mybuf, 256, "hello\\u220e")
   note the double backslash is needed if called on a C string literal */
int u8_unescape(char *buf, int sz, char *src)
{
    int c=0, amt;
    u_int32_t ch;
    char temp[4];

    while (*src && c < sz) {
        if (*src == '\\') {
            src++;
            amt = u8_read_escape_sequence(src, &ch);
        }
        else {
            ch = (u_int32_t)*src;
            amt = 1;
        }
        src += amt;
        amt = u8_wc_toutf8(temp, ch);
        if (amt > sz-c)
            break;
        memcpy(&buf[c], temp, amt);
        c += amt;
    }
    if (c < sz)
        buf[c] = '\0';
    return c;
}

int u8_escape_wchar(char *buf, int sz, u_int32_t ch)
{
    if (ch == L'\n')
        return snprintf(buf, sz, "\\n");
    else if (ch == L'\t')
        return snprintf(buf, sz, "\\t");
    else if (ch == L'\r')
        return snprintf(buf, sz, "\\r");
    else if (ch == L'\b')
        return snprintf(buf, sz, "\\b");
    else if (ch == L'\f')
        return snprintf(buf, sz, "\\f");
    else if (ch == L'\v')
        return snprintf(buf, sz, "\\v");
    else if (ch == L'\a')
        return snprintf(buf, sz, "\\a");
    else if (ch == L'\\')
        return snprintf(buf, sz, "\\\\");
    else if (ch < 32 || ch == 0x7f)
        return snprintf(buf, sz, "\\x%hhX", (unsigned char)ch);
    else if (ch > 0xFFFF)
        return snprintf(buf, sz, "\\U%.8X", (u_int32_t)ch);
    else if (ch >= 0x80 && ch <= 0xFFFF)
        return snprintf(buf, sz, "\\u%.4hX", (unsigned short)ch);

    return snprintf(buf, sz, "%c", (char)ch);
}

int u8_escape(char *buf, int sz, char *src, int escape_quotes)
{
    int c=0, i=0, amt;

    while (src[i] && c < sz) {
        if (escape_quotes && src[i] == '"') {
            amt = snprintf(buf, sz - c, "\\\"");
            i++;
        }
        else {
            amt = u8_escape_wchar(buf, sz - c, u8_nextchar(src, &i));
        }
        c += amt;
        buf += amt;
    }
    if (c < sz)
        *buf = '\0';
    return c;
}

char *u8_strchr(char *s, u_int32_t ch, int *charn)
{
    int i = 0, lasti=0;
    u_int32_t c;

    *charn = 0;
    while (s[i]) {
        c = u8_nextchar(s, &i);
        if (c == ch) {
            return &s[lasti];
        }
        lasti = i;
        (*charn)++;
    }
    return NULL;
}

char *u8_memchr(char *s, u_int32_t ch, size_t sz, int *charn)
{
    int i = 0, lasti=0;
    u_int32_t c;
    int csz;

    *charn = 0;
    while ((size_t)i < sz) {
        c = csz = 0;
        do {
            c <<= 6;
            c += (unsigned char)s[i++];
            csz++;
        } while ((size_t)i < sz && !isutf(s[i]));
        c -= offsetsFromUTF8[csz-1];

        if (c == ch) {
            return &s[lasti];
        }
        lasti = i;
        (*charn)++;
    }
    return NULL;
}

int u8_is_locale_utf8(char *locale)
{
    /* this code based on libutf8 */
    const char* cp = locale;

    for (; *cp != '\0' && *cp != '@' && *cp != '+' && *cp != ','; cp++) {
        if (*cp == '.') {
            const char* encoding = ++cp;
            for (; *cp != '\0' && *cp != '@' && *cp != '+' && *cp != ','; cp++)
                ;
            if ((cp-encoding == 5 && !strncmp(encoding, "UTF-8", 5))
                || (cp-encoding == 4 && !strncmp(encoding, "utf8", 4)))
                return 1; /* it's UTF-8 */
            break;
        }
    }
    return 0;
}

#if 0
/* Tue, 23 Feb 2016 14:24:52 +0100
 * + disable u8_vprintf() and u8_printf() since they rely on alloca() from non-POSIX alloca.h
 */
int u8_vprintf(char *fmt, va_list ap)
{
    int cnt, sz=0;
    char *buf;
    u_int32_t *wcs;

    sz = 512;
    buf = (char*)alloca(sz);
  try_print:
    cnt = vsnprintf(buf, sz, fmt, ap);
    if (cnt >= sz) {
        buf = (char*)alloca(cnt - sz + 1);
        sz = cnt + 1;
        goto try_print;
    }
    wcs = (u_int32_t*)alloca((cnt+1) * sizeof(u_int32_t));
    cnt = u8_toucs(wcs, cnt+1, buf, cnt);
    printf("%ls", (wchar_t*)wcs);
    return cnt;
}

int u8_printf(char *fmt, ...)
{
    int cnt;
    va_list args;

    va_start(args, fmt);

    cnt = u8_vprintf(fmt, args);

    va_end(args);
    return cnt;
}
#endif /*-- disable alloca()-dependent functions --*/

#endif /* UTF8XX_C_API */
