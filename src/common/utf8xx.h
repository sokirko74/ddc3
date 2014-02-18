//-*- Mode: C++; c-basic-offset: 4; -*-
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2014 by Bryan Jurish
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
#ifndef UTF8XX_H
#define UTF8XX_H

/*--moo--*/
/** \file
 * \brief Basic UTF-8 manipulation routines by Jeff Bezanson
 * \details
 * (from original utf8.c)
 *
 * Basic UTF-8 manipulation routines<br/>
 * by Jeff Bezanson<br/>
 * placed in the public domain Fall 2005
 *
 * This code is designed to provide the utilities you need to manipulate
 * UTF-8 as an internal string encoding. These functions do not perform the
 * error checking normally needed when handling UTF-8 data, so if you happen
 * to be from the Unicode Consortium you will want to flay me alive.
 * I do this because error checking can be performed at the boundaries (I/O),
 * with these routines reserved for higher performance on data known to be
 * valid.
 */
#include <stdint.h>
#include <string.h>
#include <assert.h>

#ifndef u_int32_t
# define u_int32_t uint32_t
#endif

#ifndef ucs4
 typedef u_int32_t ucs4;
#endif

#ifndef uchar
 typedef unsigned char uchar;
#endif

#define UTF8_MAXBYTES  4
#define UTF8_MAXBYTES1 5
/*--/moo--*/

#include <stdarg.h>

#include <string>
#include <vector>

/** is c the start of a utf8 sequence? */
#define isutf(c) (((c)&0xC0)!=0x80)

/** typedef for UCS-4 strings */
typedef std::vector<ucs4> ucs4str;

/** typedef for UTF-8 strings: use standard byte strings */
typedef std::string utf8str;

/** c++ifiy: returns length of utf-8 sequence beginning at position \c i of string \c s */
int u8_seqlen(const utf8str &s, size_t i);

/** convert UTF-8 byte string \c src to UCS-4 wide character string \c dst, without error checking.
 * Data is appended to \c dst.
 * \warning only works for valid UTF-8, i.e. no 5- or 6-byte sequences
 * \param dst = destination UCS-4 string
 * \param src = source UTF-8 byte string
 * \returns number of characters converted
 */
size_t u8_toucs(ucs4str &dst, const utf8str &src);

/** convience wrapper: UTF-8 string -> UCS-4 string */
ucs4str u8_toucs(const utf8str &src);

/** convert UCS-4 wide character string to UTF-8 byte string.
 * \param dst = destination UTF-8 string
 * \param src = source UCS-4 string
 * \returns number of characters converted
 */
size_t u8_toutf8(utf8str &dst, const ucs4str &src);

/** convenience wrapper: UCS-4 string -> UTF-8 string */
utf8str u8_toutf8(const ucs4str &src);

/** (moo) get number of bytes required for representing a wide character \a ch in UTF-8.
 *  Returns 0 on error.
 */
size_t u8_wc_len(ucs4 ch);

/** (moo) get number of bytes required for representing a wide character string \a ws in UTF-8 */
size_t u8_ws_len(const ucs4str &src);

/** append single UCS-4 character to a UTF-8 string
 * \param dst UTF-8 destination buffer
 * \param ch UCS-4 character to convert
 * \returns number of bytes written to \a dst (0 <= RETVAL <= UTF8_MAXBYTES)
 */
size_t u8_wc_toutf8(utf8str &dst, ucs4 ch);

/** convience wrapper: UCS-4 char -> UTF-8 string */
utf8str u8_wc_toutf8(ucs4 ch);


/** (logical) character number to (physical) byte offset */
size_t u8_offset(const utf8str &s, int charnum);

/** (physical) byte offset to (logical) character number */
size_t u8_charnum(const utf8str &s, int offset);
//int u8_charnum(char *s, int offset);

/** read and return next logical character, updating an index variable */
ucs4 u8_nextchar(const utf8str &s, size_t *i);

/** (moo): return next character, updating an index variable which may not exceed length \a slen */
ucs4 u8_nextcharn(const utf8str &s, size_t slen, size_t *i);

/** count the number of characters in a UTF-8 string */
size_t u8_strlen(const utf8str &s);

/** move to next character */
void u8_inc(const utf8str &s, size_t *i);

/** move to previous character */
void u8_dec(const utf8str &s, size_t *i);

#ifdef UTF8XX_C_API
//-- NOT YET CONVERTED TO C++ CONVENTIONS

/** assuming src points to the character after a backslash, read an
    escape sequence, storing the result in dest and returning the number of
    input characters processed */
int u8_read_escape_sequence(char *src, u_int32_t *dest);

/** given a wide character, convert it to an ASCII escape sequence stored in
   buf, where buf is "sz" bytes. returns the number of characters output. */
int u8_escape_wchar(char *buf, int sz, u_int32_t ch);

/** convert a string "src" containing escape sequences to UTF-8 */
int u8_unescape(char *buf, int sz, char *src);

/** convert UTF-8 "src" to ASCII with escape sequences.
   if escape_quotes is nonzero, quote characters will be preceded by
   backslashes as well. */
int u8_escape(char *buf, int sz, char *src, int escape_quotes);

/** utility predicates used by the above */
int octal_digit(char c);
int hex_digit(char c);

/** return a pointer to the first occurrence of ch in s, or NULL if not
   found. character index of found character returned in *charn. */
char *u8_strchr(char *s, u_int32_t ch, int *charn);

/** same as the above, but searches a buffer of a given size instead of
   a NUL-terminated string. */
char *u8_memchr(char *s, u_int32_t ch, size_t sz, int *charn);

int u8_is_locale_utf8(char *locale);

/** printf where the format string and arguments may be in UTF-8.
   you can avoid this function and just use ordinary printf() if the current
   locale is UTF-8. */
int u8_vprintf(char *fmt, va_list ap);
int u8_printf(char *fmt, ...);

#endif /* UTFXX_C_API */

#endif /* UTF8XX_H */

