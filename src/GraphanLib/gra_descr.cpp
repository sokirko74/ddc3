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
#include "../CommonLib/util_classes.h"
#include "gra_descr.h"

const int ODesLen    = 9;                   /* the length of unit's descriptor */

const char DesArray[NumberOfGraphematicalDescriptors][ODesLen] = 
{
                     
    "BEG","RLE", "LLE","DEL","PUN",//the first position :  //0-4
    "DC", "DSC","EA","_UNK_", // 5-8
    //the second position :
    "SPC","HYP","EOLN","EOP", //9-12
    "PLP","AA", "aa", "Aa", // 13-16
    "NAM?", "OPN","CLS", // 17-19
    "EMSYM", "BUL", "INDENT", // 20-22
    "dummy", "#QUOTED", "PAR_SYM", // 23-25

    // macrosyntax
    "CS?","CS","QUA","CS_PRNT","HDNG","CS_AUX","DOC", // 26-32

    "SENT_END", //33
    "ROMAN", //34
    // pair descriptors : 
    // if d is the first descriptor, then it should be always even, and d+1 should  be the corresponding second descriptor
    "EXPR1","EXPR2", // 35-36
    "FAM1","FAM2", // 37-38
    "RE1",  "RE2", // 39-40
    "FILE1", "FILE2", // 41-42
    "ABB1", "ABB2", // 43-44
    "KEY1", "KEY2", // 45-46
    "GDC1", "GDC2", // 47-48  // German divided compounds

    // only pair descriptors!!!

};


const char* GetDescriptorStr(int DescriptorNo)
{
    assert (DescriptorNo < NumberOfGraphematicalDescriptors);
    return DesArray[DescriptorNo];
};

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
