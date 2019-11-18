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


#ifndef __TEXTFIELD_H_
#define __TEXTFIELD_H_



struct CTextField  
{
    BYTE  FieldNo;
    BYTE  LeafId;
    BYTE  BracketLeafId;
    DWORD StartLine;
    DWORD EndLine;

    CTextField() {};
    CTextField (BYTE _FieldNo, BYTE _LeafId, BYTE _BracketLeafId)
    {
        LeafId = _LeafId;
        FieldNo = _FieldNo;
        BracketLeafId = _BracketLeafId;
    };

    bool operator==(const CTextField& X) const
    {
        return    (FieldNo == X.FieldNo)
            && (LeafId  == X.LeafId)
            && (BracketLeafId  == X.BracketLeafId);
    }

};


#endif //__TEXTFIELD_H_

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
