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
#ifndef DDC_common_h
#define DDC_common_h

#include "ddcConfig.h" /*-- moo --*/
#include "../common/DDCInternalError.h"

const char globalTableItemsDelim = '\x2';

/** string global for human-readable version reporting (see also ddcVersion.h) */
const string DDCVersionStr = "Dialing DWDS Concordance (DDC), Version " PACKAGE_VERSION ;

#endif
