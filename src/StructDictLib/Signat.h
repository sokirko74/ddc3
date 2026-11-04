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
// ==========  Dialing Structural Dictionary (www.aot.ru)
// ==========  Copyright by Alexey Sokirko (1998-2002), Bryan Jurish (2011)


#ifndef __SIGNAT_H_
#define __SIGNAT_H_


#include "morph_dict/common/utilit.h"
#include "../CommonLib/ddcUtil.h"

struct TSignatItem  {
    BYTE m_DomNo;
    bool m_IsMult;
    TSignatItem (BYTE DomNo, bool IsMult)
    {
        m_DomNo = DomNo;
        m_IsMult = IsMult;
    };
    TSignatItem ()
    {
        m_IsMult = false;
        m_DomNo = 0;
    };
};
const size_t MaxFormatNameLen = 254;
const size_t MaxFormatStrLen = 254;
struct CSignat 
{
    char   sFrmt[512];
    char   sFrmtWithotSpaces[512];
    std::vector<TSignatItem>  DomsWithDelims;  
    std::vector<BYTE>  Doms; 
   
    char   FormatStr[255];
    char   FormatName[255];
    int    SignatId;
    int    OrderNo;

    bool operator==(const CSignat& X) const
    {return     OrderNo == X.OrderNo; }

    bool operator<(const CSignat& X) const
    { return   (OrderNo < X.OrderNo); }

};




#endif //__SIGNAT_H_

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
