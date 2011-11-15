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
#ifndef _ConcBigrams_h
#define _ConcBigrams_h

#include "IndexSetForQueryingStage.h"

struct  CSecondWord 
{
	// pointer to CStringIndexSet::m_StringBuffer and flags;
    DWORD               m_TheOnlyOccur : 1;
    DWORD               m_EndOfSentenceFlag : 1;
    DWORD               m_Distance : 2;
    DWORD				m_StartOccur: 28 ;

    DWORD				m_SecondWordId;
	// upper bound offset of occurrences in CIndexSetForQueryingStage::m_OccursFp
	DWORD				m_EndOccurOffset;

    void InitWithZeros()
    {
        m_TheOnlyOccur = 0;
        m_EndOfSentenceFlag = 0;
        m_Distance = 0;
        m_StartOccur = 0;
        m_EndOccurOffset = 0;
        m_SecondWordId = 0;
        
    }
    DWORD PackFlagsToDWORD () const
    {
        return  (m_TheOnlyOccur << 31) | (m_EndOfSentenceFlag  << 30)  | (m_Distance << 28) | m_StartOccur;
    }
    void InitFlagsFromDWORD (const DWORD & v)
    {
        m_TheOnlyOccur      =   v >> 31 ;
        m_EndOfSentenceFlag =   v >> 30;
        m_Distance          =   v >> 28 ;
        m_StartOccur        =  (v << 4) >> 4;
    }

};

class CIndexBigram
{
    void             CloseFiles();    

public:
    string m_Path ;
    vector<DWORD>    m_FirstWords;
    FILE*            m_SecondWordFile;

     CIndexBigram(string Path);
    ~CIndexBigram();
    string	         GetSecondWordFileName() const;
    string	         GetFirstWordFileName() const;
    bool             LoadBigrams();
    bool             RemoveFiles();
    size_t           ReadSecondWords(size_t FirstWord, vector<CSecondWord>& SecondWords) const;
    


    
};

class CIndexSetForBigrams : public CIndexSetForQueryingStage
{
   	//!     


    void	WriteBigramAndItsOccurs (CSecondWord& I, const DWORD BigramId, CItemIndexForLoading& M, FILE* res_fp, size_t& CurrPositionInResFile, FILE* second_word_fp);
    bool	CreateRightBigrams(string TempRightBigramsFileName);
    string           GetRightToLeftPerdiv() const;
    map<DWORD, DWORD> m_RightToLeftPerdivIds;
 public:
    CIndexBigram m_LeftBigrams;
    CIndexBigram m_RightBigrams;
    
    
    

   	//! the temp index(used only for bigrams) 
    CIndexSetForBigrams(const CStringIndexator*		pParent);
	virtual ~CIndexSetForBigrams();
    string GetName() const;
	//! destroy index set and remove index files
	bool	DestroyIndexSet ();

	bool    LoadIndexSet();

    //! convert temporary left bigrams file to persistent (left and right)
    bool	ConvertTempBigramsToPersistent(string TempBigramsFileName, const vector<CIndexItem>& MainTokenIndex);

    //! the same as FindOccurrences, but save the idx of token to the second part of the occurrences's items
    void    FindOccurrencesForBigrams (const BigramDirectionEnum bigr_direc, const vector<DWORD>& IndexItems, const size_t PeriodNo, vector<pair<CTokenNo,DWORD> >& occurrences,  CShortOccurCacheMap* pCaches, vector<int>& CacheIds)	const;
    //! read all occurrences of IndexItemN
    void    ReadAllOccurrences (size_t IndexItemNo, const CSecondWord& I, vector<CTokenNo>& Occurs) const;


};

#endif
