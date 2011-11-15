//  Copyright 2011 by Bryan Jurish
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

#ifndef  IndexSet_h
#define  IndexSet_h

#include "../ConcordLib/IndexSetForLoadingStage.h"
#include "../ConcordLib/IndexSetForQueryingStage.h"
#include "../ConcordLib/ConcBigrams.h"
#include "../PCRE/pcre_rml.h"

/*!  COutputToken  contains information about one token of an output hit and its properties.
*/ 
struct COutputToken 
{
	//! the token itself
	string	m_TokenStr;
	//! the interpretation of the token 
	string	m_InterpStr;
	//! should DDC highlight this token in the output hit 
	bool	m_bHighlight;

	COutputToken () {
		m_bHighlight = false; 
	};

	COutputToken(string WordStr, bool bHighlight)
	{
		m_TokenStr = WordStr;
		m_bHighlight = bHighlight;
	};

	bool operator == (const COutputToken& X)const 
	{
		return m_TokenStr == X.m_TokenStr;
	};
};



class CStringIndexator;


/*! Class CStringIndexSet  is the upmost implementation of one \ref index_set_def "index set". The
	main functions deals with the searching of strings in index and with the retrieving its occurrences.
	On the other hand, this class is an inheritor of CIndexSetForLoadingStage and CIndexSetForQueryingStage, and 
	therefore it provides a connection between them during the load phase (for example CStringIndexSet::ConvertLoadIndexToWorkingIndex).
*/
class CStringIndexSet  :	public CIndexSetForLoadingStage, public CIndexSetForQueryingStage
{
	//! a file for \ref storage_def "index storage"
	FILE*	m_StorageFile;
    

    

	//!		convert a temporal index set to the work index 
	bool	ConvertLoadIndexToWorkingIndex ();
	//!		return file name for storage
	string	GetStorageFileName() const;
    //!		return file name for left bigrams
	string	GetLeftBigramsFileName() const;
	//!		make concatenation of two storages
	bool	CreateUnionTokenStorage(const CStringIndexSet& I1, const CStringIndexSet& I2, const map<DWORD, DWORD>& First2Result, const map<DWORD, DWORD>& Second2Result);
	//!		save one part of token storage to the common file (called from CreateUnionTokenStorage)
    bool	SaveOnePartOfUnionTokenStorage(FILE * res_fp, const map<DWORD, DWORD>& Old2New) const;
	//!     open \ref storage_def "storage" file
	bool	OpenStorageFile();
	//!     close \ref storage_def "storage" file
	void	CloseStorageFile();
	//! return m_Name (an implementation of pure member CIndexSetForLoadingStage::GetName )
	string	GetName() const;
	//! converts temporary \ref storage_def "index storage" to persistent one (replacing a reference to  m_StringBuffer by a index item no)
	bool	ConvertTempStorageToPersistent();
    bool    DumpBigramsOfOneDirection ( BigramDirectionEnum bigram_direc ) const;

public:
    
	//! the main name of the index set, for example "Token", "MorphPattern", "Thes", "Chunk"...
	string	m_Name;

	//! a short name of the index set,  for example "m", "w", "t", "c"
	string	m_ShortName;

	CIndexSetForBigrams   m_BigramsIndex;

    //! this function returns an string(which was indexed by DDC) by an instance of CIndexItem or CItemIndexForLoading
	template<class T>
	const char* GetIndexItemStr(const T& W) const 
	{
		return &m_StringBuffer[0] + W.GetIndexItemOffset();
	};

	CStringIndexSet(const CStringIndexator* pParent);
	~CStringIndexSet();

	//! initialize all class slots
	void	InitIndexSet(string Name, string ShortName,  bool bCreateItemStorage, bool bCompress);
	//! read index from the disk
	bool	ReadFromTheDisk();
	//! clear all vectors of the index and removes index files
	bool	DestroyIndexSet();
	//! write index to file
	bool	WriteToFile(bool bAfterLoading);
	//! build union of two indices , throws CExpc if failes
	void	UnionIndexSet(const CStringIndexSet& I1, const CStringIndexSet& I2, const CTokenNo EndToken1, const CTokenNo EndToken2);
	//! return sequence of tokens(strings) [start_offset,  end_offset] 
	bool	GetTokensFromStorage(const size_t start_offset,  const size_t end_offset, vector<COutputToken>& Tokens) const;
	//! find all occurrences of index items  in \ref period_def "subcorpora" PeriodNo, using cache pCaches
	void	FindOccurrences (const vector<DWORD>& IndexItems, const size_t PeriodNo, vector<CTokenNo>& occurrences, CMyTimeSpanHolder& Profilerp, CShortOccurCacheMap* pCaches, vector<int>& CacheIds)	const;
	//! find all occurrences of index items in \ref period_def "subcorpora" PeriodNo, using cache pCaches (if occurrences are written by chunks)
	void	FindChunkOccurrences (const vector<DWORD>& IndexItems, vector<CTokenNo>& occurrences, vector<size_t>& ChunkLengths, size_t PeriodNo, CMyTimeSpanHolder& Profilerp, CShortOccurCacheMap* pCaches, vector<int>& CacheIds)	const;
	//! search for a string "WordForm", and add it to "MatchWords", if it is found
	void	QueryTokenList (const string& WordForm, vector<DWORD>& MatchWords)	const;
	//! search for all strings, which start from  "WordForm", and add them to "MatchWords"
	void	QueryTokenListWithRightTruncation (const string& WordForm, vector<DWORD>& MatchWords)	const;
	//! search for all index items, which satisfy regular expession "RegExp", and add them to "MatchWords"
	void	QueryTokenListUsingRegExp (RML_RE &RegExp, vector<DWORD>& MatchWords)	const;
	//! print the string representation of the whole \ref storage_def "storage" to stdout
	bool	DumpStorage() const;
	//! print bigrams
	bool	DumpBigrams() const;
};




#endif
