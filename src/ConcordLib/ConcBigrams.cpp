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
#include "StdConc.h"
#include "IndexSet.h"
#include "StringIndexator.h"
#include "TempBigrams.h"
#include "ConcBigrams.h"
#include "../common/SortWithTempFiles.h"

inline size_t get_size_in_bytes (const CSecondWord& t)
{
    return sizeof (t.m_EndOccurOffset) 
        + sizeof(DWORD)  // flags
        + sizeof (t.m_SecondWordId);
};

inline size_t save_to_bytes(const CSecondWord& i, BYTE* buf)
{
    {
        const DWORD d = i.PackFlagsToDWORD();
        buf += save_to_bytes(d, buf);
    }
    buf += save_to_bytes(i.m_SecondWordId, buf);
	buf += save_to_bytes(i.m_EndOccurOffset, buf);
	return get_size_in_bytes(i);
}

inline size_t restore_from_bytes(CSecondWord& i, const BYTE* buf)
{
    {
	    DWORD d;
        buf += restore_from_bytes(d, buf);
        i.InitFlagsFromDWORD(d);
    }

    buf += restore_from_bytes(i.m_SecondWordId, buf);
	buf += restore_from_bytes(i.m_EndOccurOffset, buf);
	return get_size_in_bytes(i);
}
//=====================================================

CIndexBigram::CIndexBigram(string Path)
{
    m_Path = Path;
    m_SecondWordFile = 0;
}

void CIndexBigram::CloseFiles()
{
    if (m_SecondWordFile != 0)
        fclose (m_SecondWordFile);
    m_SecondWordFile = 0;
}

CIndexBigram::~CIndexBigram()
{
    CloseFiles();
}

string CIndexBigram::GetSecondWordFileName() const
{
    return m_Path+"_sec_wrd_";
}


string	         CIndexBigram::GetFirstWordFileName() const
{
    return m_Path+"_first_wrd_";
}


bool             CIndexBigram::LoadBigrams()
{
    CloseFiles();
    m_SecondWordFile = fopen(GetSecondWordFileName().c_str(), "rb");
    if (! m_SecondWordFile )
    {
        fprintf (stderr, "cannot open %s\n", GetSecondWordFileName().c_str());
        return false;
    }
    ReadVector(GetFirstWordFileName().c_str(), m_FirstWords);;
    return true;
}

bool             CIndexBigram::RemoveFiles()
{
    CloseFiles();
    return RemoveWithPrint(GetSecondWordFileName()) &&  RemoveWithPrint(GetFirstWordFileName());
}

size_t  CIndexBigram::ReadSecondWords(size_t FirstWord, vector<CSecondWord>& SecondWords) const
{
    const size_t Start = (FirstWord == 0) ? 0 : m_FirstWords[ FirstWord - 1 ];
    const size_t End = m_FirstWords[ FirstWord ];
    //  Start is the first CSecondWord 
    //  End is the end the sequence of  CSecondWord's 

    SecondWords.clear();
    FSeek(m_SecondWordFile, (QWORD)Start*(QWORD)GetSizeInBytes<CSecondWord>(), SEEK_SET);
    ReadVectorInner(m_SecondWordFile, SecondWords, End-Start);
    return Start;
}


//=====================================================
CIndexSetForBigrams::CIndexSetForBigrams(const CStringIndexator* pParent) : 
    CIndexSetForQueryingStage (pParent),
    m_LeftBigrams(MakeFName(pParent->m_Path, "")  + "_left"),
    m_RightBigrams(MakeFName(pParent->m_Path,"") + "_right")
{
    m_bCompressOccurrences = false;

};


 string CIndexSetForBigrams::GetRightToLeftPerdiv() const
{
    return MakeFName(m_pParent->m_Path, "_left_to_right");
}

CIndexSetForBigrams::~CIndexSetForBigrams()
{
};

string CIndexSetForBigrams::GetName() const
{
	return "bigrams";
};



bool CIndexSetForBigrams::DestroyIndexSet() 
{
    if (!CIndexSetForQueryingStage::DestroyIndexSet()) return false;

    RemoveWithPrint( GetRightToLeftPerdiv() );

    return      m_LeftBigrams.RemoveFiles()
            &&  m_RightBigrams.RemoveFiles();
;
    
}



bool CIndexSetForBigrams::LoadIndexSet()
{
    if (!m_LeftBigrams.LoadBigrams() || !m_RightBigrams.LoadBigrams())
        return false;

    {
        if (!FileExists(GetRightToLeftPerdiv().c_str()))
        {
            fprintf (stderr, "cannot open file %s\n", GetRightToLeftPerdiv().c_str());
            return false;
        }
        vector<pair<DWORD,DWORD> > v;
        ReadVector(GetRightToLeftPerdiv().c_str(), v);
        for (size_t i=0; i < v.size(); i++)
            m_RightToLeftPerdivIds[ v[i].first ]  = v[i].second;
    }

    return CIndexSetForQueryingStage::LoadIndexSet(false); // do not read m_Index from the file, only open m_OccursFp and read period devisions
};




bool ConvertBufferOffsetToTokenId(const char* filename, const vector<CIndexItem>& MainTokenIndex)
{
    map<DWORD,DWORD> BufferOffset2TokenNo;
    assert (!MainTokenIndex.empty());
 	for (size_t i=0; i < MainTokenIndex.size(); i++)
		BufferOffset2TokenNo[MainTokenIndex[i].GetIndexItemOffset()] = i;

    size_t Count = FileSize(filename)/GetSizeInBytes<CTempBigram>();
    FILE * in_fp = 0;
    FILE * out_fp = 0;
    string TmpName = CreateTempFileName();
    bool bRes = true;
    try 
    {
        in_fp = fopen(filename, "rb");
        if (!in_fp) 
            throw CExpc ("cannot read file %s\n", filename);

        out_fp = fopen(TmpName.c_str(), "wb");
        if (!out_fp) 
            throw CExpc ("cannot create file %s\n",TmpName.c_str());

        for (size_t i=0; i < Count; i++)
        {
            CTempBigram B;
            if (!BinaryReadItem(in_fp, B))
                throw CExpc ("cannot read file %s\n", filename);
            if (B.m_LeftTokenId != DWORD_MAX)
            {
                map<DWORD,DWORD>::const_iterator it = BufferOffset2TokenNo.find(B.m_LeftTokenId);
                if (it == BufferOffset2TokenNo.end()) 
                    throw CExpc ("cannot map buffer offset %i to token no\n",B.m_LeftTokenId);
                B.m_LeftTokenId = it->second;
            }
            if (B.m_RightTokenId != DWORD_MAX)
            {
                map<DWORD,DWORD>::const_iterator it = BufferOffset2TokenNo.find(B.m_RightTokenId);
                if (it == BufferOffset2TokenNo.end()) 
                    throw CExpc ("cannot map buffer offset %i to token no\n",B.m_RightTokenId);
                B.m_RightTokenId = it->second;
            }
            if (!BinaryWriteItem(out_fp, B))
                throw CExpc ("cannot write to  %s \n",TmpName.c_str());
        }

    }
    catch (CExpc c)
    {
        fprintf (stderr, "Error in ConvertBufferOffsetToTokenId: %s", c.m_strCause.c_str());
        bRes = false;
    }
    if (in_fp) fclose (in_fp);
    if (out_fp) fclose (out_fp);

    if (bRes)
    {
        remove(filename);
        if (!RmlMoveFile(TmpName.c_str(), filename))
        {
            fprintf (stderr, "cannot move file %s to file %s\n", TmpName.c_str(), filename);
            return false;
        }
        return true;
    }
    else
    {
        remove (TmpName.c_str());
        return false;
    }
 }



void	CIndexSetForBigrams::WriteBigramAndItsOccurs (CSecondWord& I, const DWORD BigramId, CItemIndexForLoading& M, FILE* res_fp, size_t& CurrPositionInResFile, FILE* second_word_fp)
{

	if (M.GetOccursSize() == 1)
	{
        I.m_EndOccurOffset =  (*M.GetOccurs())[0];
        I.m_TheOnlyOccur = 1;
	}
	else
	{
        if (!BuildPeriodsDivisionAndCompress(BigramId, *M.GetOccurs() ) )
            throw CExpc ("Cannot build periods division for BigramId=%i",BigramId);

        CurrPositionInResFile += M.GetOccursSize();
        I.m_EndOccurOffset = CurrPositionInResFile ;
		if (!M.WriteOccurrences(res_fp)) 
            throw CExpc ("Cannot write occurences");
        I.m_StartOccur = M.GetOccursSize();
	};

    M.ClearOccurrences();
    if (   !BinaryWriteItem(second_word_fp, I) )
        throw CExpc ("Cannot write scond words of bigrsms BigramId=%i",BigramId);

};


struct CTempBigram2
{
    DWORD m_LeftTokenId;
    DWORD m_LeftBigramOffset;
    CSecondWord m_SecondWord;
    bool operator < (const CTempBigram2& X) const 
    {
        if (m_LeftTokenId != X.m_LeftTokenId)
            return m_LeftTokenId < X.m_LeftTokenId;

        if (m_SecondWord.m_SecondWordId != X.m_SecondWord.m_SecondWordId)
            return m_SecondWord.m_SecondWordId < X.m_SecondWord.m_SecondWordId;

        return m_SecondWord.m_Distance < X.m_SecondWord.m_Distance;

    }
};

inline size_t get_size_in_bytes (const CTempBigram2& t)
{
	return      sizeof (t.m_LeftTokenId)
            +   sizeof (t.m_LeftBigramOffset)
            +   sizeof (t.m_SecondWord)
            ;
};

inline size_t save_to_bytes(const CTempBigram2& i, BYTE* buf)
{
    buf += save_to_bytes(i.m_LeftTokenId, buf);
    buf += save_to_bytes(i.m_LeftBigramOffset, buf);
    buf += save_to_bytes(i.m_SecondWord, buf);
	return get_size_in_bytes(i);
}

inline size_t restore_from_bytes(CTempBigram2& i, const BYTE* buf)
{
	buf += restore_from_bytes(i.m_LeftTokenId, buf);
    buf += restore_from_bytes(i.m_LeftBigramOffset, buf);
    buf += restore_from_bytes(i.m_SecondWord, buf);

	return get_size_in_bytes(i);
}





bool	CIndexSetForBigrams::CreateRightBigrams(string TempRightBigramsFileName)
{
    if (!SortWithFiles<CTempBigram2>(TempRightBigramsFileName))
               return false;
    bool bResult = true;    
    FILE * second_word_fp  = 0;
    FILE * TempBigramsFile = 0;
    vector< pair <DWORD,DWORD> >  Right2LeftOffsets;
    try 
    {
        TempBigramsFile = fopen(TempRightBigramsFileName.c_str(), "rb");
        if (!TempBigramsFile) 
            throw CExpc ("cannot reopen file %s", TempRightBigramsFileName.c_str());

        second_word_fp = fopen(m_RightBigrams.GetSecondWordFileName().c_str(), "wb");
	    if (!second_word_fp) 
             throw CExpc ("cannot write file %s", m_RightBigrams.GetSecondWordFileName().c_str());
        m_RightBigrams.m_FirstWords.clear();
        size_t Count = FileSize(TempRightBigramsFileName.c_str())/GetSizeInBytes<CTempBigram2>();
        DWORD LastFirstWord = DWORD_MAX;
        for (size_t  o=0; o < Count; o++) 
	    {
            CTempBigram2   TempBigram;
            if (!BinaryReadItem(TempBigramsFile, TempBigram))
                throw CExpc ("cannot read items from file %s", TempRightBigramsFileName.c_str());

            if (m_EndPeriodOffsets.find(TempBigram.m_LeftBigramOffset) != m_EndPeriodOffsets.end())
                Right2LeftOffsets.push_back(pair<DWORD,DWORD> (o, TempBigram.m_LeftBigramOffset));
            
            if (!BinaryWriteItem(second_word_fp, TempBigram.m_SecondWord))
                throw CExpc ("cannot write items to  file %s", m_RightBigrams.GetSecondWordFileName().c_str());


            if (o > 0)
                if ( LastFirstWord != TempBigram.m_LeftTokenId)
                    m_RightBigrams.m_FirstWords.push_back(o);

            LastFirstWord = TempBigram.m_LeftTokenId;
        }

        if (Count > 0)
            m_RightBigrams.m_FirstWords.push_back(Count);

        WriteVector(GetRightToLeftPerdiv().c_str(), Right2LeftOffsets);

        if (!WriteVector(m_RightBigrams.GetFirstWordFileName().c_str(), m_RightBigrams.m_FirstWords)) 
            throw CExpc ("Cannot write to file %s", m_RightBigrams.GetFirstWordFileName().c_str());

    }
    catch (CExpc c)
    {
        fprintf (stderr, "Error in CIndexSetForBigrams::CreateRightBigrams: %s", c.m_strCause.c_str());
        bResult = false;

    }

    if (second_word_fp)  fclose ( second_word_fp );

    if (TempBigramsFile)  fclose ( TempBigramsFile );

    RemoveWithPrint (TempRightBigramsFileName.c_str());

    

    
    return bResult;
}

bool	CIndexSetForBigrams::ConvertTempBigramsToPersistent(string TempBigramsFileName , const vector<CIndexItem>& MainTokenIndex)
{
    
    // the main sort of the bigrams, should take much time
    
    if (!ConvertBufferOffsetToTokenId(TempBigramsFileName.c_str(), MainTokenIndex))
        return false;

    if (!SortWithFiles<CTempBigram>(TempBigramsFileName))
               return false;

    FILE * TempBigramsFile = 0;
    FILE * out_fp  = 0;
    FILE * second_word_fp  = 0;
    FILE*  right_bigrams_fp  = 0;
    string TempRightBigramsFileName;
    bool bResult = true;    
    try 
    {
        //  open bigrams that were already sorted
        TempBigramsFile = fopen(TempBigramsFileName.c_str(), "rb");
        if (!TempBigramsFile) 
            throw CExpc ("cannot reopen file %s", TempBigramsFileName.c_str());

        // out_fp contains the second word to occurrences corespondency 
        out_fp = fopen(GetOccursFileName().c_str(), "wb");
        if (!out_fp) 
            throw CExpc ("cannot write file %s", GetOccursFileName().c_str());


        // out_fp contains the map from the firs word to the second 
        second_word_fp = fopen(m_LeftBigrams.GetSecondWordFileName().c_str(), "wb");
	    if (!second_word_fp) 
             throw CExpc ("cannot write file %s", m_LeftBigrams.GetSecondWordFileName().c_str());

        assert (sizeof (CTokenNo) == sizeof (DWORD));

        TempRightBigramsFileName  = CreateTempFileName();
        right_bigrams_fp = fopen (TempRightBigramsFileName.c_str(), "wb");
	    if (!right_bigrams_fp) 
             throw CExpc ("cannot write file %s", TempRightBigramsFileName.c_str());

        
	    CItemIndexForLoading M;
	    if (!M.InitOccurs())
		    throw CExpc ("cannot init occurrence");

        size_t CurrPositionInResFile = 0;
        
        CTempBigram   TempBigramSave;
        TempBigramSave.InitUnknown();
        size_t CountDifferentBigrams = 0;;

        m_LeftBigrams.m_FirstWords.clear();

        
        size_t Count = FileSize(TempBigramsFileName.c_str())/GetSizeInBytes<CTempBigram>();

        for (size_t  o=0; o <= Count; o++) // Count+1 iteration 
	    {
            CTempBigram   TempBigram;
            if (o != Count)
                if (!BinaryReadItem(TempBigramsFile, TempBigram))
                    throw CExpc ("cannot read items from file %s", TempRightBigramsFileName.c_str());


            if (o > 0) // not the first iteration
            {

                if (      o == Count
                      ||  TempBigramSave.LessWithoutAddress(TempBigram) //  a new bigram 
                    )
                {
                    
                    assert (M.GetOccursSize() > 0);
            	    CSecondWord I;
                    I.InitWithZeros();
                    if (TempBigramSave.m_LeftTokenId == DWORD_MAX)
                        I.m_EndOfSentenceFlag = 1;
                    I.m_Distance = TempBigramSave.m_Distance;
                    I.m_SecondWordId = TempBigramSave.m_LeftTokenId;
                    


                 //   const char * first = (IndexItemOffset1save == DWORD_MAX) ? "<eos>" : GetIndexItemStr(MainTokenIndex[ IndexItemOffset1save ]);
                    WriteBigramAndItsOccurs(I, CountDifferentBigrams, M, out_fp, CurrPositionInResFile, second_word_fp );
                    
                    {
                        I.m_EndOfSentenceFlag = (TempBigramSave.m_RightTokenId == DWORD_MAX) ? 1 : 0;
                        I.m_SecondWordId = TempBigramSave.m_RightTokenId;
                        CTempBigram2 B2;
                        B2.m_LeftTokenId = TempBigramSave.m_LeftTokenId;
                        B2.m_SecondWord = I;
                        B2.m_LeftBigramOffset = CountDifferentBigrams;
                        if (!BinaryWriteItem(right_bigrams_fp, B2))
                         throw CExpc ("cannot write to temporal right bigrams file");
                    }
                    CountDifferentBigrams++;

                    if (o == Count || (TempBigramSave.m_RightTokenId != TempBigram.m_RightTokenId))
                        m_LeftBigrams.m_FirstWords.push_back(CountDifferentBigrams);

                }
            }

            M.GetOccurs()->push_back(TempBigram.m_RightTokenCorpusAddress);
            TempBigramSave = TempBigram;

	    }
        
        if (!WriteVector(m_LeftBigrams.GetFirstWordFileName().c_str(), m_LeftBigrams.m_FirstWords)) return false;

       
        M.FreeOccurs();
    }
    catch ( CExpc c)
    {
        fprintf (stderr, "Error in CIndexSetForBigrams::ConvertTempBigramsToPersistent: %s", c.m_strCause.c_str());
        if (!TempRightBigramsFileName.empty()) 
            remove (TempRightBigramsFileName.c_str());
        TempRightBigramsFileName = "";
        bResult = false;
    }

    if (right_bigrams_fp) fclose(right_bigrams_fp); 
	if (TempBigramsFile) fclose (TempBigramsFile);
	if (out_fp) fclose (out_fp);
    if (second_word_fp) fclose(second_word_fp);

    if (bResult)
	    return WritePeriodsDivision() && CreateRightBigrams(TempRightBigramsFileName);
    else
    {

        return false;
    }
};


void CIndexSetForBigrams::FindOccurrencesForBigrams (const BigramDirectionEnum bigr_direc, const vector<DWORD>& FirstWords, const size_t PeriodNo, vector<pair<CTokenNo,DWORD> >& occurrences,  CShortOccurCacheMap* pCaches, vector<int>& CacheIds)	const
{
    const CIndexBigram&  IB = (bigr_direc == bdLeftBigram) ? m_LeftBigrams : m_RightBigrams;

	vector<CTokenNo> TempBuffer;

	CShortOccurCache*  pCacheByIndexSet = 0;
	if (pCaches)
		pCacheByIndexSet = &(*pCaches)["bigrams"]; 	


	bool bFirstUseOfCache =  CacheIds.empty();
    size_t AllSecondWordsCount = 0; 
	for (size_t fw=0; fw < FirstWords.size(); fw++)
    {
        vector<CSecondWord>	    SecondWords;
        const size_t StartOfSecondWords = IB.ReadSecondWords(FirstWords[fw],  SecondWords);
    
	    for( size_t sw=0; sw<SecondWords.size(); sw++ )
	    {
		    vector<CTokenNo> curr_occur;
            const CSecondWord& I =  SecondWords[sw];

            if (bFirstUseOfCache)
                CacheIds.push_back( -1 );


            DWORD LeftBigramId = StartOfSecondWords+sw;
            if (bigr_direc == bdRightBigram)
            {
                const map<DWORD, DWORD>::const_iterator it = m_RightToLeftPerdivIds.find(LeftBigramId);
                if (it == m_RightToLeftPerdivIds.end())
                    LeftBigramId = DWORD_MAX;
                else
                    LeftBigramId = it->second;
            }

            AddOccurs(  LeftBigramId, 
                        I.m_TheOnlyOccur > 0, 
                        I.m_EndOccurOffset - I.m_StartOccur,
                        I.m_EndOccurOffset,
                        curr_occur, 
                        PeriodNo, 
                        TempBuffer, 
                        pCacheByIndexSet, CacheIds[AllSecondWordsCount]);

            for (size_t on=0; on < curr_occur.size(); on++)
            {
                CTokenNo o = curr_occur[on];
                if (bigr_direc == bdRightBigram) 
                    if (!I.m_EndOfSentenceFlag)
                        o -= (I.m_Distance+1);
                occurrences.push_back( pair<CTokenNo, DWORD> (o, I.m_SecondWordId) );
            }
            AllSecondWordsCount++;
	    }
    }

    sort(occurrences.begin(), occurrences.end());

};


void CIndexSetForBigrams::ReadAllOccurrences (size_t IndexItemNo, const CSecondWord& I, vector<CTokenNo>& Occurs) const
{
	Occurs.clear();
	COccurrBuffer TempBuffer;
	int CacheId;
	for (size_t i=0; i < m_pParent->GetSearchPeriodsCount(); i++)
	{
		CacheId = -1;
        AddOccurs(  IndexItemNo, 
            I.m_TheOnlyOccur > 0, 
            I.m_EndOccurOffset - I.m_StartOccur,
            I.m_EndOccurOffset,
            Occurs, 
            i, 
            TempBuffer, 
            0, CacheId);

	};
};

