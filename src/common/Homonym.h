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
// ==========  Dialing Syntax Analysis (www.aot.ru)
// ==========  Copyright by Dmitry Pankratov, Igor Nozhov, Alexey Sokirko, Bryan Jurish (2011)

#ifndef homonym_h
 #define homonym_h

enum EGraPairType {Date, WebAddr, Oborot, Keyb,  GermanDividedCompound, UnknownPairType };



class CFormInfo;

#include "AncodePattern.h"

class CHomonym : public CAncodePattern
{
    
public:
	// morphology
	string	m_strLemma;

	// corpus frequence information
	long m_lFreqHom; 

	// Oborots
	int  m_OborotNo;
	bool m_bOborot1; 
	bool m_bOborot2; 
	bool m_bInOb;
	
	
	long m_lPradigmID;
	
	bool m_bSmallNumber;
	size_t  m_iCmpnLen;
	bool m_bCmplLem;	
		
	bool m_bRussianOdin;
	

	// a special slot to mark all homonyms which should be deleted by 
	// function CSynWord::DeleteMarkedHomonymsWithClauses
	bool m_bDelete;

	
	CHomonym(const	CAgramtab* pGramTab);
	
	
	bool operator<(const CHomonym& hom) const
	{
		return m_strLemma < hom.m_strLemma;	
	}

	bool	HasSetOfGrammemsExact(QWORD Grammems) const;
	bool	IsOb1() const;
	bool	IsOb2() const;
	bool	IsIsOb() const;
	bool	IsLemma(const char* lemma) const;
	bool	IsMorphNoun() const;
    bool	IsSynNoun() const;
	bool	IsLeftNounModifier() const;
	void	DeleteOborotMarks();

	bool	ProcessLemmaAndGrammems(const char* strLemma);
	void	SetLemma(string Lemma);
	string	GetGrammemsStr() const;
	
    void    SetMorphUnknown();
    void    SetHomonym(const CFormInfo* F);
    
	
	
};

#endif
