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
#ifndef ancode_pattern_h
#define ancode_pattern_h

class CAgramtab;
class CSyntaxOpt;
#include "../CommonLib/utilit.h"

class CAncodePattern 
{
    const	CAgramtab* m_pGramTab;
     void    ResetFlags();

public:
	QWORD			m_TypeGrammems;
	QWORD			m_iGrammems;
	char			m_LemSign;
	string			m_CommonGramCode;
	string			m_GramCodes;
	size_t			m_iPoses;
    bool            m_bUnkGramcodes;
			
	// all single preposition interpretations
	vector<int>		m_SimplePrepNos;

	CAncodePattern(const	CAgramtab* pGramTab);
    const	CAgramtab* GetGramTab() const;
	void	CopyAncodePattern(const CAncodePattern& X);
	bool	HasGrammem(BYTE gram) const;
	bool	HasPos(BYTE pos) const;
	string	GetGrammemsByAncodes() const;
	bool	ModifyGrammems(QWORD Grammems, size_t Poses=0xffffffff);
	bool	InitAncodePattern();
    void    SetMorphUnknown();
    bool    DeleteAncodesByGrammemIfCan(BYTE Grammem);
    string	GetPartOfSpeechStr() const;

};


#endif
