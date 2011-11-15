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


#ifndef __FIELD_H_
#define __FIELD_H_

#include "Signat.h"

const size_t FieldStrLen = 100;
struct  CField  
{
       int				FieldId;
       char				FieldStr[FieldStrLen];
	   vector<CSignat>	m_Signats;
       char				TypeRes;
       int				OrderId;
	   bool				IsApplicToActant;
	   CField& operator = (const CField& _F)
	   {
		   FieldId = _F.FieldId;
		   strcpy (FieldStr, _F.FieldStr);
		   TypeRes = _F.TypeRes;
		   OrderId = _F.OrderId;
		   IsApplicToActant = _F.IsApplicToActant;
           	   m_Signats =  _F.m_Signats; 
		   return *this;
	   };

};

#endif //__FIELD_H_
