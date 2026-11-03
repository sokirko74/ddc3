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
// ==========  Copyright by Alexey Sokirko (1996-2001), Bryan Jurish (2011)

#ifndef abbrev_h
#define abbrev_h

#include  "list"

const  size_t WordSize  = 50;
const  size_t AbbrevSize  = 200;

enum AbbrevItemTypeEnum  {abString, abNumber, abUpperCase, abAny};
struct  CAbbrevItem 
{
    AbbrevItemTypeEnum      m_Type;
    std::string                          m_ItemStr;
    bool operator == (const CAbbrevItem X) const;
    bool operator < (const CAbbrevItem X) const;

        
};
typedef std::list<CAbbrevItem> CAbbrev;




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
