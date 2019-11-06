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
// ==========  Dialing Graphematical Module (www.aot.ru)
// ==========  Copyright by Alexey Sokirko  and Andrey Kalinin(1996-2001), Bryan Jurish (2011)

#ifndef  HTMLConv_h
#define HTMLConv_h


#include "../CommonLib/utilit.h"

class HTML 
{
public:
                bool    m_bCollectOffsets;

                HTML()
                {
                        m_bCollectOffsets = false;
                };
                string GetTextFromHtmlFile(string FileName);
                string GetTextFromHTMLBuffer(const char* Buffer, size_t BufferLen);
                unsigned long getOffset(unsigned long off);

private:
      bool checkTag(const string& str, const char* tag);
      void addOffset(unsigned long);
      
      struct offset_range
      {
                unsigned long low;
                unsigned long high;
                offset_range(unsigned long l = 0L, unsigned long h = 0L) : low(l), high(h){};
      };

      vector<offset_range> offsets;
};


#endif

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-default-style: "linux"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
