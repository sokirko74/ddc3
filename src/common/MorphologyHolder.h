//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2014 by Bryan Jurish
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
#ifndef MorphologyHolder_H
#define MorphologyHolder_H

#include "utilit.h"
#include "../LemmatizerLib/PLMLineCollection.h"
#include "../GraphanLib/GraphmatFile.h"
#include "../AgramtabLib/RusGramTab.h"
#include "../AgramtabLib/GerGramTab.h"
#include "../AgramtabLib/EngGramTab.h"

class CMorphologyHolder
{
public:
	bool							m_bTimeStatis;
	MorphLanguageEnum				m_CurrentLanguage;
	CPlmLineCollection				m_PlmLines;
	CAgramtab*						m_pGramTab;
	CLemmatizer*					m_pLemmatizer;
	CGraphmatFile					m_Graphan;

	CMorphologyHolder();
	~CMorphologyHolder();

	bool GetMorphology(string str, bool bFile, int& CountOfWords);
	bool LoadGraphanAndLemmatizer(MorphLanguageEnum langua);
	void DeleteProcessors();
	DwordVector GetParadigmIdsByNormAndAncode(std::string &str, const std::string &code) const;
	void		string_to_ids(const char *str, DwordVector &ids, bool bNorm) const;
	std::string		id_to_string(long id) const;
	CFormInfo		id_to_paradigm(long id) const;
};



#endif
