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

#ifndef __iconv_h
#define __iconv_h

#include <iconv.h>
#include "utilit.h"

class tIConv {
    iconv_t ConversionHandle;

  public:
    tIConv(const string &to, const string &from);
    ~tIConv();
    string convert(const char *data, size_t size) const;
    string convert(const string &str);
    void reset();
};

extern string WinToUtf8(const string& s);
extern string WinToUtf8(const char *data, size_t size);
extern string Utf8ToWin(const string& s);
extern string Utf8ToWin(const char *data, size_t size);





#endif

