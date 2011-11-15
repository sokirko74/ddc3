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
#include "iconv_cpp.h"
#include <errno.h>



static  tIConv  UTF82Win ("windows-1251", "utf-8");
static  tIConv  Win2UTF8("utf-8", "windows-1251");

tIConv::tIConv(const string &to, const string &from)
{
  ConversionHandle = iconv_open (to.c_str(), from.c_str());
  if (ConversionHandle == (iconv_t) -1)
  {
    if (errno == EINVAL)
      throw runtime_error( "could not instantiate this specific iconv table" );
    else
      throw runtime_error( "iconv_open error" );
  }
}




tIConv::~tIConv()
{
  if (iconv_close(ConversionHandle) != 0)
    perror ("iconv_close");
}




string tIConv::convert(const char *data, size_t size) const
{
  const char **inptr_const = &data;
  char **inptr = const_cast<char**>(&data);
  size_t inlength = size;

  string result;

  do
  {
    char outbuffer[ 2048 ];
    size_t outlength = sizeof(outbuffer);
    char *outptr = outbuffer;

#ifdef WIN32
    if (iconv(ConversionHandle, inptr_const, &inlength, &outptr, &outlength) == (size_t) -1)
      throw CExpc("Error during iconv conversion");
#else
    if (iconv(ConversionHandle, inptr, &inlength, &outptr, &outlength) == (size_t) -1)
      throw runtime_error("Error during iconv conversion");
#endif

    result += string(outbuffer, sizeof(outbuffer) - outlength);
  }
  while (inlength);
  return result;
}




string tIConv::convert(const string &str)
{
  return convert(const_cast< char * >(str.c_str()), str.size());
}




void tIConv::reset()
{
  if (iconv(ConversionHandle, NULL, NULL, NULL, NULL) == (size_t) -1)
    throw runtime_error("Error during iconv reset");
}


string WinToUtf8(const string& s)
{
    return  Win2UTF8.convert (s);
}

string WinToUtf8(const char *data, size_t size)
{
    return  Win2UTF8.convert (data, size);;
}

string Utf8ToWin(const string& s)
{
    return  UTF82Win.convert (s);
}

string Utf8ToWin(const char *data, size_t size)
{
    return  UTF82Win.convert (data, size);
}
