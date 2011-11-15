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

#ifndef MorphAutomat_h
#define MorphAutomat_h

#include "../common/util_classes.h"

#if DDC_USE_UTF8
 const size_t MaxAlphabetSize = 182; //-- moo: bump this up to max byte size for pseudo-utf8 support
#else
 const size_t MaxAlphabetSize = 54;  //-- original ddc default
#endif


const size_t ChildrenCacheSize = 1000;

struct CMorphAutomNode 
{
	//  the highest bit of CMorphAutomNode::m_Data contains final/not final flag;
	//  the rest is an index to CMorphAutomat::m_Relations (an index 
	//   to the place where the first child is)
	DWORD							m_Data;

	DWORD	GetChildrenStart()  const
	{
		return m_Data&(0x80000000-1); 
	};
	bool	IsFinal()  const
	{
		return (m_Data&0x80000000) > 0; 
	};
	void	SetChildrenStart(DWORD v) 
	{
		m_Data = (0x80000000&m_Data)|v;  
	};
	void	SetFinal(bool v) 
	{
		if (v)
			m_Data |= 0x80000000;  
		else
			m_Data &= 0x80000000-1;  
	};

};

struct CMorphAutomRelation
{
	//  the highest byte of CMorphAutomRelation::m_Data contains relational char;
	//  the rest is an index to CMorphAutomat::m_Nodes 

	DWORD							m_Data;

	DWORD	GetChildNo()  const
	{
		return m_Data & 0xffffff; 
	};
	BYTE	GetRelationalChar()  const
	{
		return m_Data>>24; 
	};

	void	SetChildNo(DWORD v) 
	{
		m_Data = (0xff000000&m_Data)|v;  
	};

	void	SetRelationalChar(BYTE v) 
	{
		m_Data = (0xffffff&m_Data)| (v<<24);  
	};

};

struct CAutomAnnotationInner
{
	// these members are read from the automat
	WORD	m_ModelNo;
	WORD	m_ItemNo;
	WORD	m_PrefixNo;

	// these members are calculated later
	int		m_LemmaInfoNo;
	int		m_nWeight;

	DWORD GetParadigmId() const 
	{
		return (m_PrefixNo<<23) | m_LemmaInfoNo;  
	}
	void SplitParadigmId(DWORD value) 
	{
		m_PrefixNo = value>>23;
		m_LemmaInfoNo = value&0x7fffff;
	}
};
const size_t MinimalPredictionSuffix  = 3;
const BYTE MorphAnnotChar = '+';
class CABCEncoder 
{
public:

	MorphLanguageEnum			m_Language;
	const BYTE					m_AnnotChar;
	int							m_AlphabetSize;
	int							m_Alphabet2Code[256];					
	int							m_Code2Alphabet[MaxAlphabetSize];
	

	int							m_AlphabetSizeWithoutAnnotator;
	int							m_Alphabet2CodeWithoutAnnotator[256];					
	int							m_Code2AlphabetWithoutAnnotator[MaxAlphabetSize];

	bool	CheckABCWithAnnotator(const string& WordForm) const;
	bool	CheckABCWithoutAnnotator(const string& WordForm) const;
	string	EncodeIntToAlphabet(DWORD v) const;
	DWORD	DecodeFromAlphabet(const string& v) const;
	string	GetCriticalNounLetterPack() const;
	CABCEncoder(MorphLanguageEnum Language, BYTE AnnotChar);


};

class CMorphAutomat : public CABCEncoder
{
	
protected:
	
	CMorphAutomNode*				m_pNodes;
	size_t							m_NodesCount;

	CMorphAutomRelation*			m_pRelations;
	size_t							m_RelationsCount;

	vector<int>						m_ChildrenCache;
	

	
	void	DumpAllStringsRecursive(FILE* fp, int NodeNo, string CurrPath) const;
	void	BuildChildrenCache();
	void	GetAllMorphInterpsRecursive (int NodeNo, string& curr_path, vector<CAutomAnnotationInner>& Infos) const;
	int		FindStringAndPassAnnotChar (const string& Text, size_t TextPos) const;
	void	Clear();

public:
	
	CMorphAutomat(MorphLanguageEnum Language, BYTE AnnotChar);
	~CMorphAutomat();
	bool	Load(string GrammarFileName);
	bool	Save(string GrammarFileName) const;
	bool	DumpAllStrings(string FileName) const;
	void	GetInnerMorphInfos (const string& Text, size_t TextPos, vector<CAutomAnnotationInner>& Infos) const;
	const CMorphAutomRelation*  GetChildren(size_t NodeNo) const;
	int		NextNode(int NodeNo, BYTE Child) const;
	size_t	GetChildrenCount(size_t NodeNo)  const;
	const CMorphAutomNode& GetNode(int NodeNo) const { return m_pNodes[NodeNo];} ;
	DWORD	EncodeMorphAutomatInfo (size_t ModelNo, size_t ItemNo, size_t PrefixNo) const;
	void	DecodeMorphAutomatInfo (DWORD Info, size_t& ModelNo, size_t& ItemNo, size_t& PrefixNo) const;
	string	GetFirstResult (const string& Text) const;
	
};



#endif
