//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2015 by Bryan Jurish
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
#ifndef DDC_STRING_H
#define DDC_STRING_H

#include "ddcConfig.h"
#include "utf8xx.h"
#include <stdio.h>
#include <string>

//----------------------------------------------------------------------
//\name C escapes
//@{

/** Encode C escapes into string; encodes byte-wise with \xNN escapes */
std::string escapeCString(const std::string &s);

/** Decode C escapes in string. Also supports json-style "\uXXXX" utf8-escapes */
std::string unescapeCString(const std::string &s);
//@}

//----------------------------------------------------------------------
//\name JSON escapes
//@{

/** Encode JSON escapes into string.
 *  \li If \c assume_utf8 is true (default),
 *  leaves bytes with high-bit set alone; otherwise encodes them as \uXXXX escapes.
 *  \li If \c add_quotes is true, the returned string will be wrapped in JSON-friendly double quotes ("")
 */
std::string escapeJsonString(const std::string &s, bool assume_utf8=true, bool add_quotes=false);

/** Decode all JSON escapes from a string. */
std::string unescapeJsonString(const std::string &s);

/** wrapper for escapeJsonString */
inline std::string jsonStr(const std::string &s, bool assume_utf8=true, bool add_quotes=true)
{
  return escapeJsonString(s,assume_utf8,add_quotes);
}

/** jsonStr(unsigned char) maps to unsigned int */
inline std::string jsonStr(unsigned char b)
{
  char buf[4];
  sprintf(buf,"%u",b);
  return std::string(buf);
};

/** jsonStr(char) maps to single-character string */
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

//@}

//----------------------------------------------------------------------
//\name Percent escapes (URL-encoding) 
//@{

/** URL-encode the string s with %XX escapes */
std::string escapeUrlString(const std::string &s);

/** Unescape URL-encoding %XX of s */
std::string unescapeUrlString(const std::string &s);
//@}

//----------------------------------------------------------------------
//\name UTF-8 escapes
//@{

/** Decode \uXXXX escapes from a string to UTF-8 */
std::string unescapeUtf8String(const std::string &s);
//@}

//----------------------------------------------------------------------
//\name Generic backslash escapes
//@{

/** Escape selected characters \c chars in a string \c s */
std::string escapeChars(const std::string &s, const std::string &chars);

/** generate a single-quoted string */
std::string sqString(const std::string &s);

/** quote a regex in slashes // */
std::string reString(const std::string &re);

/** escape regex operators .*+?\ etc */
std::string escapeRegex(const std::string &re);
//@}

#endif /* DDC_STRING_H */
