//-*- Mode: C++;  coding: raw-text; -*-
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
#include "utilit.h"
#include "ddcLocale.h"
#include "ddcTime.h"
#include "util_classes.h"
#include "bserialize.h"
#include "DDCInternalError.h"
#include <time.h>
#include <errno.h>

//  for mkdir
#include <sys/stat.h>

//-- for stat() and mtime
#ifdef HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif

#ifdef HAVE_SYS_STAT_H
# include <sys/stat.h>
#endif

//-- for opendir()
#include <dirent.h>

using namespace std;

//-- suppress gcc warnings of the form "ignoring return value of `fread', declared with attribute warn_unused_result [-Wunused-result]"
#pragma GCC diagnostic ignored "-Wunused-result"


const uint16_t fWordDelim = 1;
const uint16_t RusUpper = 2;
const uint16_t RusLower = 4;
const uint16_t GerUpper = 8;
const uint16_t GerLower = 16;
const uint16_t EngUpper = 32;
const uint16_t EngLower = 64;
const uint16_t OpnBrck = 128;
const uint16_t ClsBrck = 256;
const uint16_t UpRomDigits = 512;
const uint16_t LwRomDigits = 1024;
const uint16_t LatinVowel = 2048;
const uint16_t RussianVowel = 4096;
const uint16_t URL_CHAR = 8192;


const uint16_t ASCII[256] = {
    /*null (nul)*/                                     fWordDelim,
    /*start of heading (soh)*/                         fWordDelim,
    /*start of text (stx)*/                            fWordDelim,
    /*end of text (etx)*/                              fWordDelim,
    /*end of transmission (eot)*/                      fWordDelim,
    /*enquiry (enq)*/                                  fWordDelim,
    /*acknowledge (ack)*/                              fWordDelim,
    /*bell (bel)*/                                     fWordDelim,
    /*backspace (bs)*/                                 fWordDelim,
    /*character tabulation (ht)*/                      fWordDelim,
    /*line feed (lf)*/                                 fWordDelim,
    /*line tabulation (vt)*/                           fWordDelim,
    /*form feed (ff)*/                                 fWordDelim,
    /*carriage return (cr)*/                           fWordDelim,
    /*shift out (so)*/                                 fWordDelim,
    /*shift in (si)*/                                  fWordDelim,
    /*datalink escape (dle)*/                          fWordDelim,
    /*device control one (dc1)*/                       fWordDelim,
    /*device control two (dc2)*/                       fWordDelim,
    /*device control three (dc3)*/                     fWordDelim,
    /*device control four (dc4)*/                      fWordDelim,
    /*negative acknowledge (nak)*/                     fWordDelim,
    /*syncronous idle (syn)*/                          fWordDelim,
    /*end of transmission block (etb)*/                fWordDelim,
    /*cancel (can)*/                                   fWordDelim,
    /*end of medium (em)*/                             fWordDelim,
    /*substitute (sub)*/                               fWordDelim,
    /*escape (esc)*/                                   fWordDelim,
    /*file separator (is4)*/                           fWordDelim,
    /*group separator (is3)*/                          fWordDelim,
    /*record separator (is2)*/                         fWordDelim,
    /*unit separator (is1)*/                           fWordDelim,
    /*space ' '*/                                      fWordDelim,
    /*exclamation mark '!'*/                           fWordDelim|URL_CHAR,
    /*quotation mark '"'*/                             fWordDelim,
    /*number sign '#'*/                                fWordDelim,
    /*dollar sign '$'*/                                fWordDelim|URL_CHAR,
    /*percent sign '%'*/                               fWordDelim|URL_CHAR,
    /*ampersand '&'*/                                  fWordDelim|URL_CHAR,
    /*apostrophe '''*/                                 fWordDelim|RusUpper|RusLower, // \xc3\x83\xc2\xb2\xc3\x83\xc2\xa2\xc3\x83\xc2\xa5\xc3\x83\xc2\xb0\xc3\x83\xc2\xa4\xc3\x83\xc2\xbb\xc3\x83\xc2\xa9 \xc3\x83\xc2\xa7\xc3\x83\xc2\xad\xc3\x83\xc2\xa0\xc3\x83\xc2\xaa \xc3\x83\xc2\xa2 \xc3\x83\xc2\xa2\xc3\x83\xc2\xa8\xc3\x83\xc2\xa4\xc3\x83\xc2\xa5 \xc3\x83\xc2\xa0\xc3\x83\xc2\xaf\xc3\x83\xc2\xae\xc3\x83\xc2\xb1\xc3\x83\xc2\xb2\xc3\x83\xc2\xb0\xc3\x83\xc2\xae\xc3\x83\xc2\xb4\xc3\x83\xc2\xa0
    /*left parenthesis '('*/                           fWordDelim|OpnBrck|URL_CHAR,
    /*right parenthesis ')'*/                          fWordDelim|ClsBrck|URL_CHAR,
    /*asterisk '*'*/                                   fWordDelim|URL_CHAR,
    /*plus sign '+'*/                                  fWordDelim|URL_CHAR,
    /*comma ','*/                                      fWordDelim|URL_CHAR,
    /*hyphen-minus '-'*/                               fWordDelim|URL_CHAR,
    /*full stop '.'*/                                  fWordDelim|URL_CHAR,
    /*solidus '/'*/                                    fWordDelim|URL_CHAR,
    /*digit zero '0'*/                                 URL_CHAR,
    /*digit one '1'*/                                  URL_CHAR,
    /*digit two '2'*/                                  URL_CHAR,
    /*digit three '3'*/                                URL_CHAR,
    /*digit four '4'*/                                 URL_CHAR,
    /*digit five '5'*/                                 URL_CHAR,
    /*digit six '6'*/                                  URL_CHAR,
    /*digit seven '7'*/                                URL_CHAR,
    /*digit eight '8'*/                                URL_CHAR,
    /*digit nine '9'*/                                 URL_CHAR,
    /*colon ':'*/                                      fWordDelim|URL_CHAR,
    /*semicolon ';'*/                                  fWordDelim|URL_CHAR,
    /*less-than sign '<'*/                             fWordDelim|OpnBrck,
    /*equals sign '='*/                                fWordDelim|URL_CHAR,
    /*greater-than sign '>'*/                          fWordDelim|ClsBrck,
    /*question mark '?'*/                              fWordDelim|URL_CHAR,
    /*commercial at '@'*/                              fWordDelim|URL_CHAR,
    /*latin capital letter a 'A'*/                     GerUpper|EngUpper|LatinVowel,
    /*latin capital letter b 'B'*/                     GerUpper|EngUpper,
    /*latin capital letter c 'C'*/                     GerUpper|EngUpper,
    /*latin capital letter d 'D'*/                     GerUpper|EngUpper,
    /*latin capital letter e 'E'*/                     GerUpper|EngUpper|LatinVowel,
    /*latin capital letter f 'F'*/                     GerUpper|EngUpper,
    /*latin capital letter g 'G'*/                     GerUpper|EngUpper,
    /*latin capital letter h 'H'*/                     GerUpper|EngUpper,
    /*latin capital letter i 'I'*/                     GerUpper|EngUpper|UpRomDigits|LatinVowel,
    /*latin capital letter j 'J'*/                     GerUpper|EngUpper,
    /*latin capital letter k 'K'*/                     GerUpper|EngUpper,
    /*latin capital letter l 'L'*/                     GerUpper|EngUpper|UpRomDigits,
    /*latin capital letter m 'M'*/                     GerUpper|EngUpper,
    /*latin capital letter n 'N'*/                     GerUpper|EngUpper,
    /*latin capital letter o 'O'*/                     GerUpper|EngUpper|LatinVowel,
    /*latin capital letter p 'P'*/                     GerUpper|EngUpper,
    /*latin capital letter q 'Q'*/                     GerUpper|EngUpper,
    /*latin capital letter r 'R'*/                     GerUpper|EngUpper,
    /*latin capital letter s 'S'*/                     GerUpper|EngUpper,
    /*latin capital letter t 'T'*/                     GerUpper|EngUpper,
    /*latin capital letter u 'U'*/                     GerUpper|EngUpper|LatinVowel,
    /*latin capital letter v 'V'*/                     GerUpper|EngUpper|UpRomDigits,
    /*latin capital letter w 'W'*/                     GerUpper|EngUpper,
    /*latin capital letter x 'X'*/                     GerUpper|EngUpper|UpRomDigits,
    /*latin capital letter y 'Y'*/                     GerUpper|EngUpper,
    /*latin capital letter z 'Z'*/                     GerUpper|EngUpper,
    /*left square bracket '['*/                        fWordDelim|OpnBrck,
    /*reverse solidus '\'*/                            fWordDelim,
    /*right square bracket ']'*/                       fWordDelim|ClsBrck,
    /*circumflex accent '^'*/                          fWordDelim,
    /*low line '_'*/                                   fWordDelim,
    /*grave accent '`'*/                               fWordDelim,
    /*latin small letter a 'a'*/                       GerLower|EngLower|LatinVowel|URL_CHAR,
    /*latin small letter b 'b'*/                       GerLower|EngLower|URL_CHAR,
    /*latin small letter c 'c'*/                       GerLower|EngLower|URL_CHAR,
    /*latin small letter d 'd'*/                       GerLower|EngLower|URL_CHAR,
    /*latin small letter e 'e'*/                       GerLower|EngLower|LatinVowel|URL_CHAR,
    /*latin small letter f 'f'*/                       GerLower|EngLower|URL_CHAR,
    /*latin small letter g 'g'*/                       GerLower|EngLower|URL_CHAR,
    /*latin small letter h 'h'*/                       GerLower|EngLower|URL_CHAR,
    /*latin small letter i 'i'*/                       GerLower|EngLower|LwRomDigits|LatinVowel|URL_CHAR,
    /*latin small letter j 'j'*/                       GerLower|EngLower|URL_CHAR,
    /*latin small letter k 'k'*/                       GerLower|EngLower|URL_CHAR,
    /*latin small letter l 'l'*/                       GerLower|EngLower|LwRomDigits|URL_CHAR,
    /*latin small letter m 'm'*/                       GerLower|EngLower|URL_CHAR,
    /*latin small letter n 'n'*/                       GerLower|EngLower|URL_CHAR,
    /*latin small letter o 'o'*/                       GerLower|EngLower|LatinVowel|URL_CHAR,
    /*latin small letter p 'p'*/                       GerLower|EngLower|URL_CHAR,
    /*latin small letter q 'q'*/                       GerLower|EngLower|URL_CHAR,
    /*latin small letter r 'r'*/                       GerLower|EngLower|URL_CHAR,
    /*latin small letter s 's'*/                       GerLower|EngLower|URL_CHAR,
    /*latin small letter t 't'*/                       GerLower|EngLower|URL_CHAR,
    /*latin small letter u 'u'*/                       GerLower|EngLower|LatinVowel|URL_CHAR,
    /*latin small letter v 'v'*/                       GerLower|EngLower|LwRomDigits|URL_CHAR,
    /*latin small letter w 'w'*/                       GerLower|EngLower|URL_CHAR,
    /*latin small letter x 'x'*/                       GerLower|EngLower|LwRomDigits|URL_CHAR,
    /*latin small letter y 'y'*/                       GerLower|EngLower|URL_CHAR,
    /*latin small letter z 'z'*/                       GerLower|EngLower|URL_CHAR,
    /*left curly bracket '{'*/                         fWordDelim|OpnBrck,
    /*vertical line '|'*/                              fWordDelim,
    /*right curly bracket '}'*/                        fWordDelim|ClsBrck,
    /*tilde '~'*/                                      fWordDelim,
    /*delete ''*/                                     0,
    /*padding character (pad) '_'*/                    fWordDelim,
    /*high octet preset (hop) '_'*/                    0,
    /*break permitted here (bph) '''*/                 0,
    /*no break here (nbh) '_'*/                        fWordDelim,
    /*index (ind) '"'*/                                0,
    /*next line (nel) ':'*/                            fWordDelim,
    /*start of selected area (ssa) '+'*/               fWordDelim,
    /*end of selected area (esa) '+'*/                 fWordDelim,
    /*character tabulation set (hts) '_'*/             fWordDelim,
    /*character tabulation with justification (htj) '%'*/ fWordDelim,
    /*line tabulation set (vts) '_'*/                  0,
    /*partial line forward (pld) '<'*/                 fWordDelim,
    /*partial line backward (plu) '_'*/                fWordDelim,
    /*reverse line feed (ri) '_'*/                     fWordDelim,
    /*single-shift two (ss2) '_'*/                     fWordDelim,
    /*single-shift three (ss3) '_'*/                   fWordDelim,
    /*device control string (dcs) '_'*/                fWordDelim,
    /*private use one (pu1) '''*/                      fWordDelim,
    /*private use two (pu2) '''*/                      fWordDelim,
    /*set transmit state (sts) '"'*/                   fWordDelim,
    /*cancel character (cch) '"'*/                     fWordDelim,
    /*message waiting (mw) ''*/                       fWordDelim,
    /*start of guarded area (spa) '-'*/                fWordDelim,
    /*end of guarded area (epa) '-'*/                  fWordDelim,
    /*start of string (sos) '_'*/                      fWordDelim,
    /*single graphic character introducer (sgci) 'T'*/ fWordDelim,
    /*single character introducer (sci) '_'*/          fWordDelim,
    /*control sequence introducer (csi) '>'*/          fWordDelim,
    /*string terminator (st) '_'*/                     fWordDelim,
    /*operating system command (osc) '_'*/             fWordDelim,
    /*privacy message (pm) '_'*/                       fWordDelim,
    /*application program command (apc) '_'*/          fWordDelim,
    /*no-break space \xa0 */                             fWordDelim,
    /*inverted exclamation mark \xa1 */                  fWordDelim,
    /*cent sign '\xa2'*/                                  fWordDelim,
    /*pound sign '\xa3' */                                 fWordDelim,
    /*currency sign '\xa4'*/                              fWordDelim,
    /*yen sign '\xa5'*/                                   fWordDelim,
    /*broken bar '\xa6'*/                                 fWordDelim,
    /*section sign '\xa7'*/                               fWordDelim,
    /*diaeresis '\xa8' */                                  fWordDelim|RusUpper|RussianVowel,
    /*copyright sign '\xa9'*/                             fWordDelim,
    /*feminine ordinal indicator '\xaa' */                 fWordDelim,
    /*left pointing double angle quotation mark '<<'*/  fWordDelim,
    /*not sign '\xac'*/                                   fWordDelim,
    /*soft hyphen '-'*/                                fWordDelim,
    /*registered sign 'R'*/                            fWordDelim,
    /*macron '\xaf'*/                                     fWordDelim,
    /*degree sign '\xb0'*/                                fWordDelim,
    /*plus-minus sign '+'*/                            fWordDelim,
    /*superscript two '_'*/                            fWordDelim,
    /*superscript three '_'*/                          fWordDelim,
    /*acute '_'*/                                      fWordDelim,
    /*micro sign '\xf7'*/                                 fWordDelim|GerLower|GerUpper,
    /*pilcrow sign '\xb6'*/                               fWordDelim,
    /*middle dot '\xb7'*/                                 fWordDelim,
    /*cedilla '\xb7'*/                                    RusLower|RussianVowel,
    /*superscript one '\xb9'*/                            fWordDelim,
    /*masculine ordinal indicator '\xba'*/                fWordDelim,
    /*right pointing double angle quotation mark '>'*/ fWordDelim,
    /*vulgar fraction one quarter '_'*/                fWordDelim,
    /*vulgar fraction one half '_'*/                   fWordDelim,
    /*vulgar fraction three quarters '_'*/             fWordDelim,
    /*inverted question mark '\xbf'*/                     fWordDelim,
    /*latin capital letter a with grave '\xc0'*/          RusUpper|RussianVowel,
    /*latin capital letter a with acute '\xc1'*/          RusUpper,
    /*latin capital letter a with circumflex '\xc2'*/     RusUpper|GerUpper|EngUpper|LatinVowel,
    /*latin capital letter a with tilde '\xc3'*/          RusUpper,
    /*latin capital letter a with diaeresis '\xc4'*/      RusUpper|GerUpper|LatinVowel,
    /*latin capital letter a with ring above '\xc5'*/     RusUpper|RussianVowel,
    /*latin capital ligature ae '\xc6'*/                  RusUpper,
    /*latin capital letter c with cedilla '\xc7'*/        RusUpper|GerUpper|EngUpper,
    /*latin capital letter e with grave '\xc8'*/          RusUpper|GerUpper|EngUpper|LatinVowel|RussianVowel,
    /*latin capital letter e with acute '\xc9'*/          RusUpper|GerUpper|EngUpper|LatinVowel,
    /*latin capital letter e with circumflex '\xca'*/     RusUpper|GerUpper|EngUpper|LatinVowel,
    /*latin capital letter e with diaeresis '\xcb'*/      RusUpper,
    /*latin capital letter i with grave '\xcc'*/          RusUpper,
    /*latin capital letter i with acute '\xcd'*/          RusUpper,
    /*latin capital letter i with circumflex '\xce'*/     RusUpper|RussianVowel,
    /*latin capital letter i with diaeresis '\xcf'*/      RusUpper,
    /*latin capital letter eth (icelandic) '\xd0'*/       RusUpper,
    /*latin capital letter n with tilde '\xd1'*/          RusUpper|GerUpper|EngUpper,
    /*latin capital letter o with grave '\xd2'*/          RusUpper,
    /*latin capital letter o with acute '\xd3'*/          RusUpper|RussianVowel,
    /*latin capital letter o with circumflex '\xd4'*/     RusUpper|GerUpper|EngUpper|LatinVowel,
    /*latin capital letter o with tilde '\xd5'*/          RusUpper,
    /*latin capital letter o with diaeresis '\xd6'*/      RusUpper|GerUpper|EngUpper|LatinVowel,
    /*multiplication sign '\xd7'*/                        RusUpper,
    /*latin capital letter o with stroke '\xd8'*/         RusUpper|UpRomDigits,
    /*latin capital letter u with grave '\xd9'*/          RusUpper,
    /*latin capital letter u with acute '\xda'*/          RusUpper,
    /*latin capital letter u with circumflex '\xdb'*/     RusUpper|GerUpper|EngUpper|LatinVowel|RussianVowel,
    /*latin capital letter u with diaeresis '\xdc'*/      RusUpper|GerUpper|LatinVowel,
    /*latin capital letter y with acute '\xdd'*/          RusUpper|RussianVowel,
    /*latin capital letter thorn (icelandic) '\xde'*/     RusUpper|RussianVowel,
    /*latin small letter sharp s (german) '\xdf'*/        RusUpper|GerLower|GerUpper|RussianVowel,
    /*latin small letter a with grave '\xe0'*/            RusLower|RussianVowel,
    /*latin small letter a with acute '\xe1'*/            RusLower,
    /*latin small letter a with circumflex '\xe2'*/       RusLower|GerLower|EngLower|LatinVowel,
    /*latin small letter a with tilde '\xe3'*/            RusLower,
    /*latin small letter a with diaeresis '\xe4'*/        RusLower|GerLower|LatinVowel,
    /*latin small letter a with ring above '\xe5'*/       RusLower|RussianVowel,
    /*latin small ligature ae '\xe6'*/                    RusLower,
    /*latin small letter c with cedilla '\xe7'*/          RusLower|GerLower|EngLower,
    /*latin small letter e with grave '\xe8'*/            RusLower|GerLower|EngLower|LatinVowel|RussianVowel,
    /*latin small letter e with acute '\xe9'*/            RusLower|GerLower|EngLower|LatinVowel,
    /*latin small letter e with circumflex '\xea'*/       RusLower|GerLower|EngLower|LatinVowel,
    /*latin small letter e with diaeresis '\xeb'*/        RusLower,
    /*latin small letter i with grave '\xec'*/            RusLower,
    /*latin small letter i with acute '\xed'*/            RusLower,
    /*latin small letter i with circumflex '\xee'*/       RusLower|RussianVowel,
    /*latin small letter i with diaeresis '\xef'*/        RusLower,
    /*latin small letter eth (icelandic) '\xf0'*/         RusLower,
    /*latin small letter n with tilde '\xf1'*/            RusLower|GerLower|EngLower,
    /*latin small letter o with grave '\xf2'*/            RusLower,
    /*latin small letter o with acute '\xf3'*/            RusLower|RussianVowel,
    /*latin small letter o with circumflex '\xf4'*/       RusLower|GerLower|EngLower|LatinVowel,
    /*latin small letter o with tilde '\xf5'*/            RusLower,
    /*latin small letter o with diaeresis '\xf6'*/        RusLower|GerLower|EngLower|LatinVowel,
    /*division sign '\xf7'*/                              RusLower,
    /*latin small letter o with stroke '\xf8'*/           RusLower,
    /*latin small letter u with grave '\xf9'*/            RusLower,
    /*latin small letter u with acute '\xfa'*/            RusLower,
    /*latin small letter u with circumflex '\xfb'*/       RusLower|GerLower|EngLower|LatinVowel|RussianVowel,
    /*latin small letter u with diaeresis '\xfc'*/        RusLower|GerLower|LatinVowel,
    /*latin small letter y with acute '\xfd'*/            RusLower|RussianVowel,
    /*latin small letter thorn (icelandic) '\xfe'*/       RusLower|RussianVowel,
    /*latin small letter y with diaeresis  '\xff'*/       RusLower|RussianVowel
};





























// ================== IsSuperEqualChar \xef\xf0\xee\xe2\xe5\xf0\xff\xe5\xf2, \xf7\xf2\xee \xf1\xe8\xec\xe2\xee\xeb\xfb \xf0\xe0\xe2\xed\xfb \xf1 \xf2\xee\xf7\xed\xee\xf1\xf2\xfc\xfe \xe4\xee \xf0\xe5\xe3\xe8\xf1\xf2\xf0\xe0
//  \xe8 \xf1 \xf2\xee\xf7\xed\xee\xf1\xf2\xfc\xfe \xe4\xee "\xff\xe7\xfb\xea\xe0", m.\xe5. \xeb\xe0\xf2\xe8\xed\xf1\xea\xee\xe5 "a" \xe1\xf3\xe4\xe5\xf2 \xf0\xe0\xe2\xed\xee  \xf0\xf3\xf1\xf1\xea\xee\xec\xf3 "\xe0".










































//======================================================================
// moo: get memory statistics using /proc/PID/status (linux only)



//======================================================================
// working with registry 







//=======================           Morphology  =======================







//=================================================================
//===================  STRINGS =====================================
//=================================================================



//  =============  Punctuation Letters ======================

//====================================================
//============= ENGLISH                   ============
//====================================================

const BYTE  Ccedille = 199;
const BYTE  Egravis = 200;
const BYTE  Ezirkun = 202;
const BYTE  Azirkun = 194;
const BYTE  Ozirkun = 212;
const BYTE  Ntilda = 209;
const BYTE  Eakut = 201;
const BYTE  Uzirkun = 219;

const BYTE  ccedille = 231;
const BYTE  egravis = 232;
const BYTE  ezirkun = 234;
const BYTE  azirkun = 226;
const BYTE  ozirkun = 244;
const BYTE  ntilda = 241;
const BYTE  eakut = 233;
const BYTE  uzirkun = 251;

 














//====================================================
//============= GERMAN                  ============
//====================================================
 









//====================================================
//============= RUSSIAN                  ============
//====================================================










//========================================= ===========
//============= General encoding functions ============
//====================================================

bool is_lower_vowel(BYTE x, MorphLanguageEnum Langua)
{
    switch (Langua)
    {
        case morphRussian : return is_russian_lower_vowel(x);
        case morphEnglish : return is_english_lower_vowel(x);
        case morphGerman : return is_german_lower_vowel(x);
        default: break;
    };
    assert (false);
    return false;
};





bool is_alpha (BYTE x, MorphLanguageEnum Langua)
{
    switch (Langua)
    {
        case morphRussian : return is_russian_alpha(x);
        case morphEnglish : return is_english_alpha(x);
        case morphGerman : return is_german_alpha(x);
        case morphGeneric : return is_generic_alpha(x);
        case morphURL : return is_URL_alpha(x);
        default: break;
    };
    assert (false);
    return false;
};









string& EngMakeUpper (string& word)
{
    return RegisterConverter(word, word.length(), is_english_lower, etoupper);
}

string& EngMakeLower (string& word)
{
    return RegisterConverter(word, word.length(), is_english_upper, etolower);
}




typedef bool (*SymbolCheckerFunc) (BYTE);

template<class T>
bool CheckLanguage(const T& src, size_t Length, MorphLanguageEnum langua)
{
    SymbolCheckerFunc SymbolChecker = 0;

    switch (langua) {
        case morphRussian : SymbolChecker =  is_russian_alpha; break;
        case morphGerman : SymbolChecker =  is_german_alpha; break;
        case morphEnglish : SymbolChecker =  is_english_alpha; break;
        case morphDigits : SymbolChecker =  is_arab_digit; break;
        default: break;
    };
    if (!SymbolChecker) return false;

    for( size_t i = 0 ; i < Length; i++ )
        if ( !SymbolChecker( (BYTE)src[i] )  )
            if ( (BYTE)src[i] != '-') 
                return false;
    return true;
};

bool IsRussian (const char *word) 
{
    return CheckLanguage(word, strlen(word), morphRussian);
}

bool CheckLanguage (const char *word, MorphLanguageEnum langua)
{
    return CheckLanguage(word, strlen(word), langua);
};






char* RmlMakeUpper (char *word, MorphLanguageEnum langua)
{
    if (!word) return word;
    if (langua==morphGeneric) {
        string s = stoupper(string(word));
        strncpy(word, s.c_str(), s.size());
    }
    return GerEngRusMakeUpperTemplate(word, langua, strlen(word));
};      


string& RmlMakeLower (string& word, MorphLanguageEnum langua)
{
    if (word.length() == 0) return word;
    if (langua==morphGeneric) {
        word = stolower(word);
        return word;
    }
    else if (langua == morphGerman)
        return RegisterConverter(word, word.length(), is_german_upper, gtolower);
    else
        return EngRusMakeLower(word);
};      


string&  EngRusMakeUpper (string& word)
{
    size_t len = word.length();
    for( size_t i = 0 ; i < len; i++ )
        if ( is_russian_lower((BYTE)word[i]) )
            word[i] = rtoupper ((BYTE)word[i]);
        else
            word[i] = etoupper ((BYTE) word[i]);

    return word;
}



char*  EngRusMakeUpper (char* word)
{
    if (word == 0) return 0;
    size_t len =  strlen(word);

    for( size_t i = 0 ; i < len; i++ )

        if ( is_russian_lower((BYTE)word[i]) )
            word[i] = rtoupper ((BYTE)word[i]);
        else
            if ( is_english_lower((BYTE)word[i]) )
                word[i] = etoupper ((BYTE) word[i]);
                

    return word;
}






void ConvertJO2Je(char* src) 
{
    ConvertJO2Je(src, strlen(src));
};













const string open_brackets = "{[(<";
const string close_brackets = "}])>";
const string all_brackets = open_brackets+close_brackets;




// \xe2\xfb\xe4\xe0\xe5\xf2 \xf1\xee\xee\xf2\xe2\xe5\xf2\xf1\xf2\xe2\xf3\xfe\xf9\xf3\xfe \xf1\xea\xee\xe1\xea\xf3 



// ============     CShortString and  CShortStringHolder =========================




















// ============     CMyTimeSpan and  CMyTimeSpanHolder =========================








//  finish timer "Name" and returns the elapsed time in ticks











//-- formerly in Bibliography.cpp
//#define _MAKEWORD(a, b)      ((WORD)(((BYTE)((a) & 0xff)) | ((WORD)((BYTE)((b) & 0xff))) << 8))
//#define _MAKELONG(a, b)      ((long)(((WORD)((a) & 0xffff)) | ((DWORD)((WORD)((b) & 0xffff))) << 16))








































string BuildRMLPath (const char* s)
{
    string path = s;
    size_t i = path.find("$RML");
    if (i != string::npos)
        path.replace(i, 4, GetRmlVariable());
    return path;
}

#ifdef CLION_DEBUG
//  to show windows-1251 strings in gdb
#include <codecvt>
#include <locale>


struct TRmlLocales {
    static const std::locale& Russian() {
        const char* enc = "ru_RU.cp1251";
        static std::locale* loc = new std::locale("ru_RU.cp1251");
        return *loc;
    }
};
static TRmlLocales RmlLocales;


char debug_buffer[10000];
char* _tou8(const char* str) {
    std::wstring wstr(strlen(str), U'\0');
    std::use_facet<std::ctype<wchar_t>>(RmlLocales.Russian()).widen(str, str + strlen(str), &wstr[0]);
    std::wstring_convert<std::codecvt_utf8<wchar_t>> cvt;
    std::string converted = cvt.to_bytes(wstr);
    strcpy(debug_buffer, converted.c_str());
    return debug_buffer;
}
#endif

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
