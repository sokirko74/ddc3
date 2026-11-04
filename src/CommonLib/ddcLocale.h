/*--------------------------------------------------------------------------
 * File: ddcLocale.h
 * Author: Bryan Jurish <jurish@uni-potsdam.de>
 * Description: locale interface
 *--------------------------------------------------------------------------*/

/**
   \file ddcLocale.h
   \brief locale functions
*/

#ifndef _DDC_LOCALE_H
#define _DDC_LOCALE_H

#include <locale.h>
#include <string>
#include "morph_dict/common/utilit.h"   // MorphLanguageEnum, RmlMakeUpper()

//! sentinel indicating whether current process has initialized the locale
extern bool ddcLocaleInitialized;

//! initialize the locale from current environment if not already initialized
extern void ddcInitLocale(void);

//! convert a std::string in current locale's character set to a std::wstring
//! (requires setlocale(LC_CTYPE,"whatever"))
std::wstring string2wstring(const std::string &src);

//! convert a std::wstring to a std::string in current locale's character set
//! (requires setlocale(LC_CTYPE,"whatever"))
std::string wstring2string(const std::wstring &src);

//! convert a std::wstring to upper-case 
std::wstring wstoupper(const std::wstring &ws);

//! convert a std::wstring to lower-case 
std::wstring wstolower(const std::wstring &ws);

//! convert a std::string to upper-case according to current locale (implicit conversion to and from wstring)
std::string stoupper(const std::string &s);

//! convert a std::string to lower-case according to current locale (implicit conversion to and from string)
std::string stolower(const std::string &s);

//! ddc case conversion of a word in the corpus language:
//!  morphGeneric -> stoupper()/stolower() (current locale, e.g. utf8),
//!  otherwise -> morph_dict RmlMakeUpper()/RmlMakeLower() (single-byte cp1251/cp1252)
std::string& ddcMakeUpper(std::string& word, MorphLanguageEnum langua);
std::string& ddcMakeLower(std::string& word, MorphLanguageEnum langua);
//! in-place variant for a 0-terminated buffer (the result must not be longer than the input)
char* ddcMakeUpper(char* word, MorphLanguageEnum langua);

#endif //_DDC_LOCALE_H
