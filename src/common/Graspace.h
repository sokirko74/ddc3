
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

#ifndef graspace_h
 #define graspace_h

   #include "utilit.h"

   #define   SEOLN        (unsigned char) '´'
   #define   SSpace       (unsigned char) 'Å'
   #define   STab         '\x10'

   inline bool is_gra_space (int c)
    { return c==SEOLN || c == SSpace || c == STab;}

   // max length of the token
   const size_t CriticalTokenLength = 255;

   // length of the token and its graphematical descriptors 
   const size_t CriticalGraphemLineLength = CriticalTokenLength*2;

#endif
