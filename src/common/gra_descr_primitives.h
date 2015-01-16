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
#include "utilit.h"
#include "gra_descr.h"
extern bool IsEndTextPeriodDescriptor (Descriptors d);
extern bool IsFirstMemberOfPairDesciptor(Descriptors d);
extern bool IsSecondMemberOfPairDesciptor(Descriptors d);
extern Descriptors GetSecondMemberByTheFirst(Descriptors d);
extern Descriptors GetFirstMemberByTheSecond(Descriptors d);
extern QWORD parse_gra_descriptors ( const char * s, string& unparsed);
extern const char* GetDescriptorStr(int DescriptorNo);
