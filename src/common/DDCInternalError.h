//-*- Mode: C++; c-basic-offset:8;-*-
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
#ifndef DDC_internal_error_h
#define DDC_internal_error_h


enum DDCErrorEnum
{       
	errNone = 0,
	errReadOccurrenceFile	= 1,
	errProcessMorphology	= 2,
	errNonePath		= 3,
	errParseError		= 4,
	errReadSourceFile	= 5,
	errTimeoutElapsed	= 6,
	errRuntime		= 7,
	errLogic		= 8,
	errOther		= 9
};


inline const char* GetDDCErrorString(DDCErrorEnum ErrorCode)
{
	switch (ErrorCode) {
		case errNone: return "No error";
		case errReadOccurrenceFile: return "cannot read an index file";
		case errProcessMorphology: return "an exception in morphology";
		case errNonePath: return "bad path for index files";
		case errParseError: return "cannot parse the input query";
		case errReadSourceFile: return "cannot read a source file";
		case errTimeoutElapsed: return "timeout elapsed";
		case errRuntime: return "runtime error";
		case errLogic: return "logic error";
		case errOther: return "other error";
		default: break;
	}
	return "Unknown error code";
}

#endif
