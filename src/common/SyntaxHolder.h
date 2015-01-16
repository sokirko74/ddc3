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
#ifndef SyntaxHolder_H
#define SyntaxHolder_H

#include "utilit.h"
#include "MorphologyHolder.h"
#include "../SynCommonLib/SentencesCollection.h"
#include "../MAPostLib/PostMorphInterface.h" 


class CSyntaxHolder : public  CMorphologyHolder
{
public:
	CSentencesCollection			m_Synan;
	CPostMorphInteface*				m_pPostMorph;


	CSyntaxHolder();
	~CSyntaxHolder();

	bool LoadSyntax(MorphLanguageEnum langua);
	bool GetSentencesFromSynAn(string str, bool bFile);
	
	string  GetClauseTypeDescr(const CClause& C, int ClauseTypeNo) const;
};

#endif
