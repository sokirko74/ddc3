//-*- Mode: C++ -*-
//
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
#ifndef DDC_STRING_H
#define DDC_STRING_H

#include "ddcConfig.h"
#include "utf8xx.h"
#include <stdarg.h>
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

//----------------------------------------------------------------------
//\name printf-style formatting
//@{

/** wrapper for vsnprintf() which returns a C++ string */
std::string Format( const char* format, ... );

/** wrapper for vsnprintf(), va_list version */
std::string vFormat( const char* format, va_list& args );

//@}

//----------------------------------------------------------------------
//\name system errors
//@{

/** wrapper for strerror_r() if available, otherwise wraps strerror() */
char* StrError(int ErrorNo);

//@}

//----------------------------------------------------------------------
//\name string splitting
//@{

//--------------------------------------------------------------
/**
 * old string tokenizer from ../CommonLib/util_classes.h, utilit.cpp, rsp. ../CommonLib/string_tokenizer.h
 * \detail see also stringSplitE() from utilit.cpp
 */
/**
   re-entrant replacement of strtok().

   Usage (C-strings):
   <code>
   char *text = "word, word2;word3"
   CStringTokenizer token(text, " ,;");
   const char *word;
   while((word = token())){
   // handle token here
   }
   </code>
*/
class StringTokenizer {
protected:
    char *text_ptr;
    char *text;
    int i;

    //-------------------------------------------------------
    std::string delims;
    inline bool is_delim(char ch) const
    { return delims.find_first_of(ch) != std::string::npos; }
  
    char *_val;

public:
    //-------------------------------------------------------
    // constructors etc.
    StringTokenizer(const char *_text, const char *_delims=" \t\r\n");

    ///! moo: constructor from std::string (implicitly calls c_str() on arguments)
    StringTokenizer(const std::string& _text, const std::string& _delims)
    { initialize(_text,_delims); };

    ~StringTokenizer();

    void initialize(const char *_text, const char *_delims=" \t\r\n");
    void reinitialize(const char *_text, const char *_delims=" \t\r\n");

    ///! moo: initialize from std::string (copies)
    void initialize(const std::string& _text, const std::string &_delims)
    { initialize(_text.c_str(), _delims.c_str()); };

    //-------------------------------------------------------
    // API
    const char * operator ()();
    std::string next_token();

    inline const char * get_rest () const
    { return text; };
  
    inline const char *val() const
    { return _val; };
  
    inline int count() const
    { return i; };
 
    inline bool has_next() const
    { return (*text) != '\0'; };

    //! moo: append all remaining tokens to a string vector (consumes the rest of the source string)
    void get_tokens(std::vector<std::string> &tokens);

    //! moo: get all remaining text as a single token, trimming any initial or trailing delimiters
    const char* get_rest_trim();
};


//--------------------------------------------------------------
/** pseudo-replacement for StringTokenizer (from utilit.h) which allows empty tokens
 * \detail see also stringSplitE() from utilit.cpp
 */
class StringSplitter {
public:
    const std::string *srcp;      ///< source string (reference)
    const std::string *delimp;    ///< delimiter characters (reference)
    size_t begi;                  ///< start position of current token (string::npos after initilization)
    size_t endi;                  ///< end position of current token

public:

    /** constructor; positions at first available token */
    inline StringSplitter(const std::string& src, const std::string& delims)
        : srcp(&src), delimp(&delims)
    {
        begin();
    };

    /** position iterators to first token */
    inline void begin()
    {
        begi = 0;
        endi = srcp->find_first_of(*delimp, begi);
    };

    /** returns true iff the iterators point to a valid token */
    inline bool valid() const
    { return begi != std::string::npos; };

    /** cast-to-bool: wrapper for valid() */
    inline operator bool() const
    { return valid(); };

    /** get current token substring - should only be called if valid() is true */
    inline std::string current() const
    { return endi==std::string::npos ? srcp->substr(begi) : srcp->substr(begi,endi-begi); };

    /** dereference operator wraps current() */
    inline std::string operator*() const
    { return current(); };
  
    /** increment to next available token */
    inline void next()
    {
        begi = endi==std::string::npos ? endi : (endi+1);
        endi = begi==std::string::npos ? begi : srcp->find_first_of(*delimp,begi);
    };

    /** increment operator wraps next() */
    inline StringSplitter& operator++()
    {
        next();
        return *this;
    };
};

//----------------------------------------------------------------------
//\name string trimming
//@{

/** constructive variant of Trim() from utilit.(h|cpp): trims leading and trailing whitespace from argument, returns new trimmed string */
std::string TrimSafe(const std::string &str);

//@}

//----------------------------------------------------------------------
//\name bool parsing
//@{

/** option-parsing utility for boolean options */
bool StringToBool(const std::string &s, bool onempty=true);

/** boolean value reporting for options */
const char *BoolToString(bool b);

//@}


#endif /* DDC_STRING_H */

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
