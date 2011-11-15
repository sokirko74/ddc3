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
// ==========  Copyright by Alexey Sokirko, Bryan Jurish (2011)

#ifndef __PARADIGM_H_
#define __PARADIGM_H_

#include  "../common/utilit.h"
#include  "MorphAutomat.h"

class CLemmatizer;


class CFormInfo 
{
	bool					m_bPrefixesWereCut;
	bool					m_bFlexiaWasCut;
    string                  m_UserPrefix;
	CAutomAnnotationInner m_InnerAnnot;
	const CLemmaInfoAndLemma& GetLemmaInfo() const;
	const CFlexiaModel& GetFlexiaModel() const;
	bool  IsValid() const;

public:
	const CLemmatizer*			m_pParent;
	string						m_InputWordBase;
	bool						m_bFound;

	
	CFormInfo();
	void	Create(const CLemmatizer*	pParent, const CAutomAnnotationInner& A, const string& InputWordForm, bool bFound);
	void	Copy(const CFormInfo& from);
	void	AttachLemmatizer(const CLemmatizer* parent);
	bool	SetParadigmId(DWORD newVal);

	DWORD	GetParadigmId() const;
	DWORD	GetCount () const;
	
	string	GetSrcNorm() const; 
	// returns the weight of a word form 
	int		GetHomonymWeightWithForm(WORD pos) const; 
	// returns the weight of this word 
	int		GetWordWeight() const;

	string	GetAncode(WORD pos) const;
	string	GetWordForm (WORD pos) const;
	string	GetSrcAncode() const;
	int		GetHomonymWeight() const;
	BYTE	GetAccentedVowel(WORD pos) const;
	BYTE	GetSrcAccentedVowel() const;
	string	GetCommonAncode() const;
	char	GetLemSign() const; 
	size_t	GetLemmaPrefixLength() const; 
    string  FormatAsInPlmLine() const;
    void    SetUserPrefix(const string& UserPrefix);
    void    SetUserUnknown();
};


#endif //__PARADIGM_H_
