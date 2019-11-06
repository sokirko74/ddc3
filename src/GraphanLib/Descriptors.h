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

#ifndef  Descriptors_h
#define Descriptors_h

#ifndef __GRAPHANLib_LIBRARY_DEFINED__

enum Descriptors 
{
         OBeg  = 0, 
         ORLE   = 1, 
         OLLE  = 2, 
         ODel  = 3, 
         OPun  = 4, 
         ODC   = 5, 
         ODSC = 6, 
         OElectAddr  = 7, 
         OUnk  = 8, 
         OSpc  = 9, 
         OHyp  = 10, 
         OEOLN = 11,  
         OEOP  = 12, 
         OPlu  = 13, 
         OUp   = 14, 
         OLw   = 15, 
         OUpLw = 16, 
         ONam  = 17, 
         OOpn  = 18, 
         OCls  = 19,
         ONil  = 20, 
         OBullet = 21, 
         OPar    = 22,
         ODUMMY = 23, 
         OLongDelimSeq = 24, 
         OParagraph = 25,


         CS_Undef   = 26, 
         CS_Simple  = 27, 
         CS_Quasi   = 28, 
         CS_Parent  = 29, 
         CS_Heading = 30, 
         CS_Explan  = 31, 
         CS_Doc     = 32, 


         OEXPR1    = 33, 
         OEXPR2    = 34,    
         OFAM1   = 35, 
         OFAM2   = 36, 
         ORef1      = 37, 
         ORef2      = 38, 
         OFile1 = 39, 
         OFile2 = 40,
         OAbbr1 = 41, 
         OAbbr2 = 42,
         OKey1 =  43, 
         OKey2 =  44,
         OGerDivComp1 =  45, 
         OGerDivComp2 =  46,
         OSentEnd  = 47,
};
#endif

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
