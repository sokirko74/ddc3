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
// ==========  Dialing Posmorphological Module (www.aot.ru)
// ==========  Copyright by Alexey Sokirko (2003-2004), Bryan Jurish (2011)

#ifndef __PLMLINE_H_
#define __PLMLINE_H_

#include "../common/Graspace.h"
#include "../AgramtabLib/agramtab_.h"

enum MainTokenTypeEnum {RLE=0, LLE=1, NUM=2, NUM_CHAR=3, PUNCTUAT=4, ROMAN_NUM=5, OTHER_TOKEN_TYPE=6};

extern string TokenTypeToString(const MainTokenTypeEnum & t);
extern MainTokenTypeEnum StringToTokenType(const  string& t);

class CPlmLine {
	string	m_GramCodes;
	string	m_Word;
	string	m_UpperWord;
	char	m_MorphSign;
	string	m_CommonGramCode;

public:
	int		m_FilePosition;
	int		m_TokenLengthInFile;
	string m_GraphDescr;
	bool   m_bHomonym;
	
	string m_Lemma;
	
	string m_ParadigmId;
	string m_HomoWeight;
	MainTokenTypeEnum   m_TokenType;
	RegisterEnum	   m_Register;	
	bool	m_bToDelete;
	bool	m_bFirstUpperAlpha;
	bool	m_bQuoteMarks;	
	bool	m_bFI1;
	bool	m_bFI2;
	
	bool	m_bName;
	bool	m_bSent2;
	bool	m_bOborot1;
	bool	m_bOborot2;
	bool	m_bHyphenWord;
	bool	m_bMorphName;	
	bool	m_bMorphSurname;
	QWORD	m_Grammems;	
	BYTE	m_Pos;	


	CPlmLine ();

	bool    LoadPlmLineFromString (string Buffer, bool bStartLine, const CAgramtab* pRusGramTab);
	string  GetStr() const;
	void	DeleteDescr(const char* Descr);
	void	DeleteOb1();
	void	DeleteOb2();
	bool	HasGraDescr(const char* GraphDescr) const;
	void	SetGramCodes(const string& NewGramCodes, const CAgramtab* pRusGramTab);
	const string&	GetGramCodes() const { return m_GramCodes;};
	bool	IsPartOfNonSingleOborot() const;
	bool	IsFoundInMorphology() const;
	void	SetWord(string s);
	const string&  GetWord() const;
	const string&  GetUpperWord() const;
	const string&   GetCommonGramCode() const;
	void			SetMorphUnknown();
	void			SetMorph(char MorphSign, const string& CommonAncode, const DWORD& ParadigmId);
	
};





#endif
