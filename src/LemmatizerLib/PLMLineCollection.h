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
// ==========  Dialing Lemmatizer (www.aot.ru)
// ==========  Copyright by Alexey Sokirko, Andrey Putrin, Bryan Jurish (2011)

#ifndef __PLMLINECOLLECTION_H_
#define __PLMLINECOLLECTION_H_
#pragma warning (disable : 4786)

#include "../GraphanLib/GraphmatFile.h"       
#include "Lemmatizers.h"       



/////////////////////////////////////////////////////////////////////////////
// CPlmLineCollection

class CPlmLineCollection 
{
public:
	StringVector			m_Items;
	CLemmatizer*			m_pLemmatizer;

	CPlmLineCollection();
	~CPlmLineCollection();

	bool SaveToFile(string filename) const;
	bool ProcessPlmLines(const CGraphmatFile* piGraphmatFile);
	
};

inline bool CheckIfHomonymPlmLine(const char* strPlmLine)
{
	return( strPlmLine[0] == ' ') ;
}


#endif //__COMPLMLINECOLLECTION_H_
