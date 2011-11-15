/* -*- Mode: C++ -*- */
//  Copyright 2011 by Bryan Jurish
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

#endif //_DDC_LOCALE_H

