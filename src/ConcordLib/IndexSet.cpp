//-*- Mode: C++; c-basic-offset: 8;-*-
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
#include "ConcIndexator.h"

//==============================================
//================== CStringIndexSet ==========
//===============================================

CStringIndexSet::CStringIndexSet(const CStringIndexator* pParent) : CIndexSetForQueryingStage(pParent), 
m_BigramsIndex(pParent)
{
	assert (pParent != 0);
	m_StorageFile = 0;
};


void CStringIndexSet::InitIndexSet(string Name, string ShortName, bool bCreateItemStorage, bool bCompress)
{
	m_Name = Name;
	m_ShortName	= ShortName;
	m_bUseItemStorage = bCreateItemStorage;
	m_bCompressOccurrences = bCompress;
};


CStringIndexSet::~CStringIndexSet()
{
	CloseStorageFile();
    
};

string CStringIndexSet::GetName() const
{
	return m_Name;
};





void CStringIndexSet::QueryTokenList (const string& WordForm, vector<DWORD>& MatchWords)	const
{
	LessIndexString1<CIndexItem> Less(&m_StringBuffer);

	vector<CIndexItem>::const_iterator it = lower_bound (m_Index.begin(), m_Index.end(), WordForm.c_str(), Less);
	
	if (MatchWords.size() > m_pParent->m_MaxRegExpExpansionSize)
			return;

	if (   
				( it != m_Index.end() )
			&&	( !strcmp(GetIndexItemStr(*it),WordForm.c_str())   )
		)
		MatchWords.push_back( it -  m_Index.begin() );
};


void CStringIndexSet::QueryTokenListWithRightTruncation (const string& WordForm, vector<DWORD>& MatchWords)	const
{
	LessIndexString1<CIndexItem> Less(&m_StringBuffer);
	int len =  WordForm.length();
	vector<CIndexItem>::const_iterator it = lower_bound (m_Index.begin(), m_Index.end(), WordForm.c_str(), Less);

	while ( 		( it != m_Index.end() )
			&&	( !strncmp(GetIndexItemStr(*it),WordForm.c_str(), len)   )
			)
	{
		if (MatchWords.size() > m_pParent->m_MaxRegExpExpansionSize)
			break;

		MatchWords.push_back( it -  m_Index.begin() );

		it++;
	};
};

void CStringIndexSet::QueryTokenListUsingRegExp (RML_RE &RegExp, vector<DWORD>& MatchWords, bool negated)	const
{
	size_t Count = m_Index.size();
	for( size_t i=0; i<Count; i++ )
	{
		const char* str =  GetIndexItemStr(m_Index[i]);
		bool  ismatch = RegExp.PartialMatch(str);

		if ( negated ? (!ismatch) : ismatch )
		{
			if (MatchWords.size() > m_pParent->m_MaxRegExpExpansionSize)
				break;

			MatchWords.push_back( i );
		};
	};
};

void CStringIndexSet::QueryTokenListUniversal(vector<DWORD>& MatchWords) const
{
	DWORD Count = (DWORD)m_Index.size();
	MatchWords.reserve(MatchWords.size()+Count);
	for (DWORD i=0; i < Count; ++i) {
		MatchWords.push_back(i);
	}
};


bool	CStringIndexSet::ReadFromTheDisk()
{
	LoadIndexSet();
	ReadVector(GetFileNameForInfos().c_str(), m_StringBuffer);

	if (m_bUseItemStorage)
		if (!OpenStorageFile())
			return false;

   	if (UseBigrams())
    {
        if (!m_BigramsIndex.LoadIndexSet())
			return false;
    }

	return true;
};

bool	CStringIndexSet::DestroyIndexSet()
{
	if (!CIndexSetForQueryingStage::DestroyIndexSet ()) return false;

	ClearVector(m_StringBuffer);
	if (FileExists(GetStorageFileName().c_str()))
	{
		CloseStorageFile();
		if (remove(GetStorageFileName().c_str()))
			return false;
	};

    if (UseBigrams())
        if (!m_BigramsIndex.DestroyIndexSet())
            return false;

	return true; 
};


string	CStringIndexSet::GetStorageFileName() const
{
	assert (m_pParent->m_Path != "#empty_path");
	return MakeFName(m_pParent->m_Path, "_storage_"+GetName());
};

string	CStringIndexSet::GetLeftBigramsFileName() const
{
	assert (m_pParent->m_Path != "#empty_path");
	return MakeFName(m_pParent->m_Path, "_left_"+GetName());
};




bool	CStringIndexSet::SaveOnePartOfUnionTokenStorage(FILE * out_fp, const map<DWORD, DWORD>& Old2New) const
{
	DWORD Old;
	FSeek(m_StorageFile, 0, SEEK_SET);

	while (fread(&Old, sizeof(DWORD), 1, m_StorageFile) == 1)
	{
		map<DWORD,DWORD>::const_iterator it = Old2New.find(Old);
		if (it == Old2New.end()) 
		{
			return false;
		}
		if (fwrite(&(it->second), 4, 1, out_fp) != 1) 
		{
			return false;
		};
	};
	return true;
};

bool	CStringIndexSet::CreateUnionTokenStorage(
	const CStringIndexSet& First, 
	const CStringIndexSet& Second,
	const map<DWORD, DWORD>& First2Result, 
	const map<DWORD, DWORD>& Second2Result)
{
	assert  (First.m_bUseItemStorage);
	assert  (Second.m_bUseItemStorage);
	CloseStorageFile();

	{
		FILE * out_fp = fopen(GetStorageFileName().c_str(), "wb");
		if (!out_fp) return false;
		if (!First.SaveOnePartOfUnionTokenStorage(out_fp, First2Result)) return true;
		if (!Second.SaveOnePartOfUnionTokenStorage(out_fp, Second2Result)) return true;
		fclose (out_fp);
	}

	return OpenStorageFile();
};





void	CStringIndexSet::UnionIndexSet(const CStringIndexSet& First, const CStringIndexSet& Second, const CTokenNo EndToken1, const CTokenNo EndToken2)
{
    if ( (QWORD)EndToken1 + (QWORD)EndToken2 > (QWORD)CIndexItem::GetMaximalNumberOfRunningTokens() )
        throw CExpc("The number of running rokens of the result index cannot be more than %u\n", CIndexItem::GetMaximalNumberOfRunningTokens());

    if (First.m_Index.empty() && Second.m_Index.empty()) return;

	LessIndexString2<CIndexItem> Pred (&First.m_StringBuffer,&Second.m_StringBuffer);
	m_Index.clear();
	vector<CIndexItem>::const_iterator i1 = First.m_Index.begin();
	vector<CIndexItem>::const_iterator i2 = Second.m_Index.begin();


	FILE* res_fp = fopen(GetOccursFileName().c_str(), "wb");
	if (!res_fp ) 
        throw CExpc ("cannot open file %s to write occurrences", GetOccursFileName().c_str());

	CItemIndexForLoading M;
	if (!M.InitOccurs()) 
        throw CExpc ("cannot init occurrences buffer");

	size_t CurrPositionInResFile = 0;
	int DebugAction = 0;
	bool FirstIsLarger = First.m_Index.size()> Second.m_Index.size();
	size_t Count = (FirstIsLarger) ? First.m_Index.size() : Second.m_Index.size();
	size_t Curr = 0;
	
	map<DWORD, DWORD> First2Result, Second2Result;

	while	(		(i1 !=  First.m_Index.end()) 
				||	(i2 !=  Second.m_Index.end()) 
			)
	{
		size_t pos1 =  i1-First.m_Index.begin();
		size_t pos2 =  i2-Second.m_Index.begin();
		Curr = (FirstIsLarger) ? pos1 : pos2;

		if (!(Curr%1000))
			fprintf (stderr, "%i/%i\r", Curr, Count);
		const char* IndexItemStr1 = First.GetIndexItemStr(*i1);
		const char* IndexItemStr2 = Second.GetIndexItemStr(*i2);

		//  setting the pointer to data
		M.SetIndexItemOffset(m_StringBuffer.size());
		size_t AddDeltaIndex;

		if	(		(i2 ==  Second.m_Index.end())
				||	(	
							(i1 !=  First.m_Index.end())
						&& Pred(*i1, *i2)	
					)
			)
		{
			// adding data to buffer			
			AddItemStrToBuffer(IndexItemStr1, strlen(IndexItemStr1));

			// reading occurrences
			First.ReadAllOccurrences(pos1, *M.GetOccurs());
			AddDeltaIndex = M.GetOccursSize();

			First2Result[pos1] = m_Index.size();

			i1++;
			

			//DebugAction = 1;
		}
		else
			if	(		(i1 ==  First.m_Index.end())	
					||	(		(i2 !=  Second.m_Index.end())
							&&	Pred.Greater(*i1, *i2)	
						)
				)
			{
				AddItemStrToBuffer(IndexItemStr2, strlen(IndexItemStr2));

				// reading occurrences
				Second.ReadAllOccurrences(pos2, *M.GetOccurs());
				AddDeltaIndex = 0;				
				Second2Result[pos2] = m_Index.size();
				i2++;
				//DebugAction = 2;
			}
			else
			{
				First2Result[pos1] = Second2Result[pos2] = m_Index.size();
				First.ReadAllOccurrences(pos1, *M.GetOccurs());
				AddDeltaIndex = M.GetOccursSize();
				vector<CTokenNo> Q;
				Second.ReadAllOccurrences(pos2, Q);
				
				M.GetOccurs()->insert(M.GetOccurs()->end(), Q.begin(), Q.end());
				
				AddItemStrToBuffer(IndexItemStr1, strlen(IndexItemStr1));
				i1++;
				i2++;
				//DebugAction = 3;
			};
		//printf ("DebugAction = %i\n", DebugAction);

		// adding delta to the occurrences  from the second corpus 
		for (size_t  i = AddDeltaIndex; i < M.GetOccursSize();  i++)
			(*M.GetOccurs())[i] += EndToken1;

		// writing data  and add IndexItem to Result.m_Index
		if (!AddOneIndexItem(M, res_fp, CurrPositionInResFile, EndToken1+EndToken2))
            throw CExpc ("position in the first index =%i,position in the second index =%i\n", i1-First.m_Index.begin(), i2-Second.m_Index.begin());

		
	};
	fprintf (stderr, "%i/%i\n", Curr, Count);
	M.FreeOccurs();
	fclose(res_fp);
	if (!WritePeriodsDivision()) 
        throw CExpc ("cannot write period division");

	if (m_bUseItemStorage)
		if (!CreateUnionTokenStorage(First, Second, First2Result, Second2Result))
			throw CExpc ("cannot merge item storages");


};



bool CStringIndexSet::GetTokensFromStorage(const size_t start_offset,  const size_t end_offset, vector<COutputToken>& Tokens) const
{
	if (!m_bUseItemStorage) return false;
	size_t count  = end_offset-start_offset;
	Tokens.resize(count);
	if (count == 0) return true;
	file_off_t read_offset =  (QWORD)start_offset*(QWORD)sizeof(DWORD);
	
	if (!FSeek (m_StorageFile, read_offset, SEEK_SET)) return false;
	for (size_t i=0; i < count; i++)
	{
		DWORD u;
		if (fread(&(u),sizeof(u), 1, m_StorageFile) != 1) return false;
		if (u > m_Index.size()) return false;
		Tokens[i].m_TokenStr  = GetIndexItemStr(m_Index[u]);
		Tokens[i].m_bHighlight  = false;
	};
	return true;
};

bool CStringIndexSet::DumpStorage() const
{
	if (!m_bUseItemStorage) 
	{
		fprintf(stderr, "Error! This index has no item storage!\n");
		return false;
	};
	if (!m_StorageFile) return false;
	if (!FSeek (m_StorageFile, 0, SEEK_SET)) return false;
	DWORD u;
	while (fread(&u,sizeof(u), 1, m_StorageFile) == 1)
	{
		printf ("%s\n", GetIndexItemStr(m_Index[u]));
	};
	return  true;
};

bool    CStringIndexSet::DumpBigramsOfOneDirection ( BigramDirectionEnum bigram_direc ) const
{
    const CIndexBigram& IndexBigrams = (bigram_direc == bdLeftBigram) ? m_BigramsIndex.m_LeftBigrams :  m_BigramsIndex.m_RightBigrams;
    if (IndexBigrams.m_FirstWords.size() != m_Index.size()+1)
        throw CExpc ("the number of the first words of bigrams should be the same as the number of the words in the main index plus one for <eos>");
    if (!m_bUseItemStorage)
        throw CExpc ("cannot dump bigrams without item storage");

    for (size_t  fw=0; fw < m_Index.size(); fw++)
    {
        const char* first_word =  GetIndexItemStr(m_Index[fw]);
        vector<CSecondWord>	    SecondWords;
        const size_t Start = IndexBigrams.ReadSecondWords(fw,  SecondWords);
        for( size_t sw=0; sw<SecondWords.size(); sw++ )
	    {
		    vector<CTokenNo> occurs;
            const CSecondWord& I =  SecondWords[sw];
            m_BigramsIndex.ReadAllOccurrences(sw+Start, I, occurs);
            if (occurs.empty())
                throw CExpc ("bigram occurrence list is empty (first word is \"%s\")", first_word);
            const char* second_word =  (I.m_EndOfSentenceFlag) ? "<eos>" : GetIndexItemStr(m_Index[I.m_SecondWordId]);
            printf ("%s %s %i ->", first_word, second_word, I.m_Distance);
            for (size_t on=0; on <  occurs.size(); on++)
            {
                size_t o;
                if (bigram_direc == bdLeftBigram) 
                    o = occurs[on];
                else
                    o = occurs[on] - (I.m_Distance+1) + I.m_EndOfSentenceFlag;

                printf (" %i", o);
            }
            printf ("\n");


        }


    }
    return true;
}

bool CStringIndexSet::DumpBigrams() const
{
    try {
        printf ("left bigrams:\n");
        DumpBigramsOfOneDirection (bdLeftBigram);
        printf ("right bigrams:\n");
        DumpBigramsOfOneDirection (bdRightBigram);
    }
    catch (CExpc c)
    {
        fprintf (stderr, "CStringIndexSet::DumpBigrams: %s\n", c.m_strCause.c_str());
        return false;
    }
    return true;
}


void CStringIndexSet::CloseStorageFile()
{
	if (m_StorageFile) 
	{
		fclose(m_StorageFile);
		m_StorageFile = 0;
	};
};

bool CStringIndexSet::OpenStorageFile()
{
	CloseStorageFile();
	m_StorageFile = fopen(GetStorageFileName().c_str(), "rb");
	return m_StorageFile != 0;
};



bool	CStringIndexSet::ConvertTempStorageToPersistent()
{
	assert (m_bUseItemStorage);

	// if the procedure is called from ConcordAdd, then 
	//  the persistent file should be already built and m_TempStorageFile is null, no other actions
	if (!m_TempStorageFile) return true;

	

	map<DWORD,DWORD> BufferOffset2TokenNo;
    assert (!m_Index.empty());
  	for (size_t i=0; i < m_Index.size(); i++)
		BufferOffset2TokenNo[m_Index[i].GetIndexItemOffset()] = i;

	
	
	if (m_TempStorageFile) fclose (m_TempStorageFile);
	m_TempStorageFile = fopen(m_TempStorageFileName.c_str(), "rb");
	FILE * out_fp = fopen(GetStorageFileName().c_str(), "wb");
	if (!out_fp) return false;
	DWORD BufferOffset;
	while (fread(&BufferOffset, 4, 1, m_TempStorageFile) == 1)
	{
		map<DWORD,DWORD>::const_iterator it = BufferOffset2TokenNo.find(BufferOffset);
		if (it == BufferOffset2TokenNo.end()) 
		{
			fclose (out_fp);
			return false;
		}
		if (fwrite(&(it->second), 4, 1, out_fp) != 1) 
		{
			fclose (out_fp);
			return false;
		};
	};

	fclose (m_TempStorageFile);
	m_TempStorageFile = 0;
	fclose (out_fp);
	return true;
};


//==============================================================================
// moved from ad-hoc ConcordQuery.cpp

void CStringIndexSet::FindOccurrences (const vector<DWORD>& IndexItems, const size_t PeriodNo, vector<CTokenNo>& occurrences,  CMyTimeSpanHolder& Profiler, CShortOccurCacheMap* pCaches, vector<int>& CacheIds)	const
{
	vector<CTokenNo> TempBuffer;

	CShortOccurCache*  pCacheByIndexSet = 0;
	if (pCaches)
		pCacheByIndexSet = &(*pCaches)[GetName()]; 	

	size_t Count = IndexItems.size();

	if (CacheIds.empty())
		CacheIds.resize(Count, -1);

	assert (CacheIds.size() == Count);

	for( size_t i=0; i<Count; i++ )
	{
		const size_t IndexItemNo = IndexItems[i];
		const CIndexItem& I = m_Index[ IndexItemNo ];
		const char * _debug_view = GetIndexItemStr(I);	///<TODO: see if we can lose this -- moocow Fri, 29 Nov 2013 10:04:58 +0100
		AddOccurs(IndexItemNo, 
			  I.HasOneOccurrence(), 
			  GetStartOccurNo(IndexItemNo), 
			  I.GetEndOccurOffset(), 
			  occurrences, 
			  PeriodNo, 
			  TempBuffer, 
			  pCacheByIndexSet, 
			  CacheIds[i]);

	}

    SortOccurrences(occurrences, Count);

};





void CStringIndexSet::FindChunkOccurrences (const vector<DWORD>& IndexItems, vector<CTokenNo>& occurrences,  vector<size_t>& ChunkLengths, size_t PeriodNo, CMyTimeSpanHolder& Profiler, CShortOccurCacheMap* pCaches, vector<int>& CacheIds)	const
{
		
	vector<CTokenNo> TempBuffer;

	vector<pair<CTokenNo, size_t> > pos_and_lengths;

	size_t Count = IndexItems.size();

	CShortOccurCache*  pCacheByIndexSet = 0;
	if (pCaches)
		pCacheByIndexSet = &(*pCaches)[GetName()]; 	

	if (CacheIds.empty())
		CacheIds.resize(Count, -1);

	assert (CacheIds.size() == Count);


	for( size_t i=0; i<Count; i++ )	
	{
        size_t IndexItemNo  = IndexItems[i];
		int chunk_len;
		{
			const char * chunk_str = GetIndexItemStr(m_Index[ IndexItemNo ]);
			const char* offset = strchr(chunk_str, ',');
			if (offset == 0) 
			{
				assert (false);
				continue;
			};
			chunk_len = atoi(offset+1);
			if (chunk_len<=0) continue;
		};
		vector<CTokenNo> curr_positions;	
        
		AddOccurs(IndexItemNo , 
                  m_Index[ IndexItemNo  ].HasOneOccurrence(), 
                  GetStartOccurNo(IndexItemNo),
                  m_Index[ IndexItemNo  ].GetEndOccurOffset(), 
                  curr_positions, 
                  PeriodNo, 
                  TempBuffer, 
                  pCacheByIndexSet, 
                  CacheIds[i]);
		{
			vector<pair<CTokenNo, size_t> > curr_pos_and_lengths;
			for (size_t k=0; k < curr_positions.size(); k++)
				curr_pos_and_lengths.push_back(make_pair(curr_positions[k], chunk_len));

			//add curr_pos_and_lengths to pos_and_lengths
			vector<pair<CTokenNo, size_t> > new_pos_and_lengths;
			new_pos_and_lengths.resize(curr_pos_and_lengths.size() + pos_and_lengths.size());
			vector<pair<CTokenNo, size_t> >::iterator it = 
				set_union(curr_pos_and_lengths.begin(), curr_pos_and_lengths.end(), pos_and_lengths.begin(), pos_and_lengths.end(), new_pos_and_lengths.begin());
			new_pos_and_lengths.resize(it - new_pos_and_lengths.begin());
			new_pos_and_lengths.swap(pos_and_lengths);
		}
	};

	Count = pos_and_lengths.size();
	for (size_t i=0; i < Count; i++)
	{
		size_t l = pos_and_lengths[i].second;
		for (int k = 0; k<l; k++)
		{
			CTokenNo LastPositionOfChunk = pos_and_lengths[i].first;
			CTokenNo FirstPositionOfChunk = LastPositionOfChunk - l +1;
			occurrences.push_back(FirstPositionOfChunk+k);
		}
		ChunkLengths.push_back(l);
	};
	
};
