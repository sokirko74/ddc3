//-*- Mode: C++; c-basic-offset:8;-*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2018 by Bryan Jurish
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
#include "IndexSetForQueryingStage.h"
#include "ConcordAlgorithm.h"
#include "StringIndexator.h"
#include <fcntl.h>

#ifdef DETECT_MEMORY_LEAK
	#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
	#endif
#endif

const size_t MaxCompressRatio = 5;
size_t AllBytesRead =  0;
//!  the size of the buffer, which is used to read occurrences from the disk
//const DWORD OccurBufferSize = 32;
const DWORD OccurBufferSize = 512;



CIndexSetForQueryingStage::CIndexSetForQueryingStage(const CStringIndexator* pParent)
{
	m_OccursFp = 0;
	m_pParent  = pParent;
	assert (m_pParent);
};

void CIndexSetForQueryingStage::CloseOccursFile()
{
	if (m_OccursFp)
	{
		fclose(m_OccursFp);
		m_OccursFp = 0;
	};
};

CIndexSetForQueryingStage::~CIndexSetForQueryingStage()
{
	CloseOccursFile();
};


void CIndexSetForQueryingStage::AssertHasPath() const
{
	assert(m_pParent->m_Path != "#empty_path");
	if (m_pParent->m_Path == "#empty_path")
	{
		ErrorMessage("Uninitialized path for index files");;
		throw CExpc(errNonePath, "Exception: Uninitialized path for index files");
	};

};

bool CIndexSetForQueryingStage::DestroyIndexSet( )
{	
	AssertHasPath();
	m_Index.clear();
	m_EndPeriodOffsets.clear();

	CloseOccursFile();

	if (FileExists(GetOccHdrFileName().c_str()))
		if (remove (GetOccHdrFileName().c_str() ) )
			return false;


	if (FileExists(GetOccursFileName().c_str() ))
		if (remove (GetOccursFileName().c_str() ))
			return false;

	if (FileExists(GetPeriodsDivisionFileName().c_str() ) )
		if (remove (GetPeriodsDivisionFileName().c_str()))
			return false;

	if (FileExists(GetFileNameForInfos().c_str()))
		if (remove (GetFileNameForInfos().c_str() ))
			return false;

	return true;
	
};



bool	CIndexSetForQueryingStage::LoadIndexSet(bool bLoadHeaderOfOccurrences)
{
	CloseOccursFile();
	m_OccursFp = fopen(GetOccursFileName().c_str(), "rb");
	if (!m_OccursFp) return false;
	// disable buffer for fread under Windows, under Linuc this setvbuf could only slow down the program
	#ifdef	WIN32
		setvbuf(m_OccursFp, 0, _IONBF, 0);
	#endif

    
	if (bLoadHeaderOfOccurrences)
		m_Index.open(GetOccHdrFileName(), m_pParent->m_bMemoryMap);

	if (!LoadPeriodDivision()) return false;
	return true;
}



void DearchiveOccurrences(const DWORD* in_start, const DWORD* in_end,  DWORD* out_start, DWORD& OutCount, bool bEnabled)
{
	if (!bEnabled)
	{
		OutCount = in_end - in_start;
		memcpy(out_start, in_start, OutCount*sizeof(DWORD));
	}
	else
	{
		DeconvertFromVariableInteger(in_start, in_end,  out_start, OutCount);
		//DearchiveSequence(in_start, in_end,  out_start, OutCount);
	}
};


void CIndexSetForQueryingStage::ReadOccurrences (CTokenNo* OutBuffer, file_off_t FilePosition, size_t Count) const
{
	lock();
	try {
		AllBytesRead +=  Count * sizeof(CTokenNo);
		if (!FSeek(m_OccursFp, FilePosition, SEEK_SET))
			throw CExpc(errReadOccurrenceFile, Format("Fatal error! Cannot seek to offset %i in occurrence file\n", FilePosition));

		if (fread(OutBuffer, sizeof(CTokenNo), Count, m_OccursFp) != Count)
			throw CExpc(errReadOccurrenceFile, Format("Fatal error! Cannot read from offset %i  %i dwords from  occurrence file\n", FilePosition, Count));
	}
	catch (...) {
		unlock();
		throw;
	}
	unlock();
};





/*
 AddLongOccursOccurs reads from m_OccursFp occurrences. Input parameters are:
	IndexItemNo - the index item, whose occurrences we are going to read
	Occurs - output vector of occurrences, we will add  occurrences to the end of this vector
	PeriodNo - the number of subcorpora in which we should read occurrences.
	Buffer - an auxiliary buffer in which we read tokens for the first time(We use this buffer for performance, 
			for simplicity it can be declared inside AddLongOccursOccurs)
*/




size_t CIndexSetForQueryingStage::GetStartOccurNo(size_t IndexNo) const
{
	if (IndexNo == 0) return 0;
	if (m_Index[IndexNo].HasOneOccurrence()) return DWORD_MAX;

	// we should  pass all index items  which are occurred only one time in corpora (they take no space in m_OccursFp)
	for (IndexNo--; IndexNo > 0; IndexNo--)
	{
		if ( ! m_Index[IndexNo].HasOneOccurrence() )
			return m_Index[IndexNo].GetEndOccurOffset();
	};

	assert (IndexNo == 0);

	if (m_Index[0].HasOneOccurrence() )
		return 0;
	else
		return m_Index[0].GetEndOccurOffset();

}

void  CIndexSetForQueryingStage::AddOccurs (size_t PeriodDevId, const bool bOneOccurrence, const size_t StartOccurNo, const size_t EndOccurNo, vector<CTokenNo>& Occurs,  size_t PeriodNo, COccurrBuffer& TempOccurrsBuffer, CShortOccurCache* pCacheByIndexSet, int& CacheId) const
{
  //fprintf(stderr, "DEBUG: AddOccurs(PeriodDevId=%u, bOne=%d, Start=%u, End=%u, PNo=%u)\n", PeriodDevId, bOneOccurrence, StartOccurNo, EndOccurNo, PeriodNo);
	
	const CTokenNo StartSearchPeriod = (PeriodNo == 0)? 0: m_pParent->GetSearchPeriod(PeriodNo-1);
	const CTokenNo EndSearchPeriod =  m_pParent->GetSearchPeriod(PeriodNo);
	//  if there is only one occurrence if this index item  in the corpora
	// then  we should get from IndexItem.m_EndOccurOffset
	if (bOneOccurrence )
	{
		
		CTokenNo T = EndOccurNo;
		if	(	(T >= StartSearchPeriod)	
			  &&(T < EndSearchPeriod)
			)
			Occurs.push_back(T);
	}
	else
	
    {
	const DWORD *Periods = m_EndPeriodOffsets.find(PeriodDevId);
        if (Periods != NULL)
        {
	    //fprintf(stderr, "DEBUG: AddOccurs(): per_dev_it != m_EndPeriodOffsets.end()\n");
            
	    //const vector<DWORD>& Periods = per_dev_it->second;
	    //-- moo: this assertion catches if we redefine & manually re-calculate search-period size WITHOUT re-indexing (Thu, 13 Nov 2015 09:57:03 +0100)
	    //   + UPDATE 2018-06-12 10:02:56+0200: we check this anymore here using mmap()-savvy implementation,
	    //     but consistency with m_pParent->GetSearchPeriodsCount() should be checked at load-time by ddcRecFile::open()
            //assert (Periods.size() == m_pParent->GetSearchPeriodsCount());

            const QWORD StartOfPeriod  = (PeriodNo == 0) ? StartOccurNo      : (QWORD)StartOccurNo + Periods[PeriodNo - 1];
            const QWORD PeriodSize     = (PeriodNo == 0) ? Periods[PeriodNo] : Periods[PeriodNo]   - Periods[PeriodNo - 1];
            
            if  (PeriodSize == 0) return;

            // reading from the file
            DWORD DearchivedSize;
            TempOccurrsBuffer.resize(PeriodSize);

            ReadOccurrences(&TempOccurrsBuffer[0], StartOfPeriod*(QWORD)sizeof(CTokenNo), PeriodSize);

            // dearchiving 
            DWORD old_size =  Occurs.size();
            Occurs.resize(Occurs.size() + PeriodSize*MaxCompressRatio);
            DearchiveOccurrences(&TempOccurrsBuffer[0], &TempOccurrsBuffer[0]+TempOccurrsBuffer.size(),  &Occurs[0] + old_size, DearchivedSize, m_bCompressOccurrences);

            // adjusting the size  of  Occurs, since we have reserved  too much space   (MaxCountToRead*3)
            Occurs.resize(old_size + DearchivedSize);

        }

        else //  if no period division of this token, then read all occurrences from all periods
	    {
	      //fprintf(stderr, "DEBUG: AddOccurs(): per_dev_it == m_EndPeriodOffsets.end()\n");
		    
		    QWORD End  = EndOccurNo;
		    DWORD MaxCountToRead = EndOccurNo-StartOccurNo;

		    const CTokenNo* pBuffer;
		    TempOccurrsBuffer.resize(MaxCountToRead);
    		
		    if (pCacheByIndexSet && CacheId != -1)
		    {
			    pBuffer = pCacheByIndexSet->GetOccurrencesFromCache(CacheId, MaxCountToRead);
		    }
		    else
		    {
			    ReadOccurrences(&TempOccurrsBuffer[0], (QWORD)StartOccurNo*(QWORD)sizeof(CTokenNo), MaxCountToRead);
			    pBuffer = &TempOccurrsBuffer[0];

			    //-- moo: this assertion is catching if we query 'sein' (Mon, 06 Jun 2011 14:14:51 +0200)
			    //   + appears to be a result of old index files from kaskade (64-bit problem ?!)
			    //   + possibly (?) solved by re-defining typedefs DWORD, WORD in ../CommonLib/utilit.h
			    //       typedef unsigned int	DWORD --> uint32_t
			    //	     typedef unsigned short	WORD  --> uint16_t
			    //fprintf(stderr, "DEBUG: MaxCountToRead=%u, OccurBufferSize=%u\n", MaxCountToRead, OccurBufferSize);
			    assert (MaxCountToRead <= OccurBufferSize);

			    // dearchiving the occurrences ( if !m_bCompressOccurrences then it is just a copy )
			    // if there is no period division, then there is no more than  OccurBufferSize occurrences 
			    // (see "if (OccurBufferSize >= OriginalTokenCount)" in BuildPeriodsDivisionAndCompress
			    CTokenNo NewBuffer[OccurBufferSize];

			    // MaxCountToRead is going to be changed, if the index is archived  
			    // it will contain the real number of poistions for this  IndexItemNo
			    DearchiveOccurrences(pBuffer, pBuffer  + MaxCountToRead,  NewBuffer, MaxCountToRead, m_bCompressOccurrences);
			    pBuffer = NewBuffer;

			    if (pCacheByIndexSet && pCacheByIndexSet->CouldContainMore() )
			    {
				    //  inserting new cache item, if the cache is not too large
				    CacheId = pCacheByIndexSet->AddNewIndexItemNoToCache(pBuffer, pBuffer+MaxCountToRead);
			    };
		    }
    		
		    // finding start an end position of the search period 
		    const CTokenNo* start_it = lower_bound(pBuffer, pBuffer+MaxCountToRead,StartSearchPeriod);
		    const CTokenNo* end_it = lower_bound(start_it, pBuffer+MaxCountToRead,EndSearchPeriod);

		    // adding the found occurrences to the output vector
		    Occurs.insert(Occurs.end(), start_it, end_it);
	    }
    }

};


void CIndexSetForQueryingStage::ReadAllOccurrences (size_t IndexItemNo, vector<CTokenNo>& Occurs) const
{
	Occurs.clear();
	COccurrBuffer TempBuffer;
	int CacheId;
	for (size_t i=0; i < m_pParent->GetSearchPeriodsCount(); i++)
	{
		CacheId = -1;
		AddOccurs(IndexItemNo, 
            m_Index[IndexItemNo].HasOneOccurrence(), 
            GetStartOccurNo(IndexItemNo), 
            m_Index[IndexItemNo].GetEndOccurOffset(), 
            Occurs, 
            i, 
            TempBuffer, 
            0, 
            CacheId);
	};
};




string CIndexSetForQueryingStage::GetOccHdrFileName() const
{
	AssertHasPath();
	return MakeFName(m_pParent->m_Path,"_occ_hdr_")  + GetName();
};



string CIndexSetForQueryingStage::GetOccursFileName() const
{
	AssertHasPath();
	return MakeFName(m_pParent->m_Path,"_occurs_")  + GetName();
};
string	CIndexSetForQueryingStage::GetPeriodsDivisionFileName () const
{
	AssertHasPath();
	return  MakeFName(m_pParent->m_Path,"_perdiv") + GetName();
};
string	CIndexSetForQueryingStage::GetFileNameForInfos() const
{
	AssertHasPath();
	return MakeFName(m_pParent->m_Path,string("_") + GetName() );
};

file_off_t	CIndexSetForQueryingStage::GetOccurrsFileSize() const
{
	AssertHasPath();
	return FileSize(GetOccursFileName().c_str());
};




void CompressOccurrences(const vector<DWORD>& In,  vector<DWORD>& Out, bool bEnabled)
{
	if (!bEnabled)
		Out = In;
	else
	{
		ConvertToVariableInteger(In, Out);
	}
};


void	CompressPortion (vector<DWORD>& Archive, const vector<DWORD>& Body, DWORD Start, DWORD End, bool bArchiveOccurrences)
{
	vector<CTokenNo> NewPortion;
	NewPortion.insert(NewPortion.begin(), Body.begin()+Start, Body.begin()+End);
	vector<CTokenNo> ArchivedNewPortion;
	CompressOccurrences(NewPortion, ArchivedNewPortion, bArchiveOccurrences);
	Archive.insert(Archive.end(), ArchivedNewPortion.begin(), ArchivedNewPortion.end());
};



/*
	this procedure  archives the sequence of occurrences (IndexItem.m_pOccurs)
	and calculates the borders between the search periods for this sequence

	For example,  let sequence of occurrences be a = "1 34 45 46 89"   and the search periods be "20 50 90"
	then  a should  be divided into 3 periods according to  the search periods i.e.
	" 1 | 34 45 46 | 89 |". These three  borders  should be saved to m_EndPeriodOffsets.
*/
bool	CIndexSetForQueryingStage::BuildPeriodsDivisionAndCompress (const DWORD PerDivId, vector<CTokenNo>& InputTokens )
{
	if (m_pParent->GetSearchPeriodsCount() == 0)
	{
		fprintf (stderr, "Error! There are no search periods\n");
		return false;
	}
    size_t OriginalTokenCount = InputTokens.size();

	vector<CTokenNo> ResultArchive;

	// only archiving if it is necessary
	if (OccurBufferSize >= OriginalTokenCount) 
	{
		// the number of occurrences is too small for building  period division
        CompressPortion(ResultArchive, InputTokens, 0, InputTokens.size(), m_bCompressOccurrences);

		// writing back to IndexItem archived version of occurrences
		InputTokens = ResultArchive;
		return true;
	};

	vector<DWORD> EndOffsets;
	EndOffsets.resize(m_pParent->GetSearchPeriodsCount());
	
	size_t CurrentPeriod = 0;
	
	size_t PrevStart = 0;
	size_t j = 0;
	for (; j<OriginalTokenCount; j++)
		while (InputTokens[j] >= m_pParent->GetSearchPeriod(CurrentPeriod) )
			{
				// check the current search period
				if (CurrentPeriod >= m_pParent->GetSearchPeriodsCount())
				{
					// if we are here, it means that some j (*IndexItem.GetOccurs())[j]
					// is greater than the upper bound of the last search period
					fprintf (stderr, "Error while writing occurrences periods for \"%s\": CurrentPeriod >= m_pParent->m_pSearchPeriods.size()\n", GetName().c_str());
					fprintf (stderr, "CurrentPeriod = %zi\n", CurrentPeriod);
					fprintf (stderr, "m_pParent->m_pSearchPeriods.size() = %zi\n", m_pParent->GetSearchPeriodsCount());
					fprintf (stderr, "Occurrence =%i, Number of occurrences = %zi\n",InputTokens[j], OriginalTokenCount);
					for (size_t p = 0; p < m_pParent->GetSearchPeriodsCount(); p++)
						fprintf (stderr, "CurrentPeriod = %zi, EndTokenNo = %u\n", p, m_pParent->GetSearchPeriod(p));

					return false;
				};

				if (j > PrevStart)
					CompressPortion(ResultArchive, InputTokens, PrevStart, j, m_bCompressOccurrences);
				else
				{
					//no occurrences in the search period
				}

				PrevStart = j;

				EndOffsets[CurrentPeriod] = ResultArchive.size();
				
				CurrentPeriod++;
				
			};


	// writing the last search period, if there are some occurrences 
	if (j > PrevStart)
	{
		// check the current search period
		if (CurrentPeriod >= m_pParent->GetSearchPeriodsCount())
		{
			// if we are here, it means that some j (*IndexItem.GetOccurs())[j]
			// is greater than the upper bound of the last search period
			fprintf (stderr, "Error while writing occurrences periods for \"%s\": CurrentPeriod >= m_pParent->m_pSearchPeriods.size()\n", GetName().c_str());
			fprintf (stderr, "CurrentPeriod = %zi\n", CurrentPeriod);
			fprintf (stderr, "m_pParent->m_pSearchPeriods.size() = %zi\n", m_pParent->GetSearchPeriodsCount());
			fprintf (stderr, "Occurrence =%u, Number of occurrences = %zi\n",InputTokens[j], OriginalTokenCount);
			for (size_t p = 0; p < m_pParent->GetSearchPeriodsCount(); p++)
				fprintf (stderr, "CurrentPeriod = %zi, EndTokenNo = %u\n", p, m_pParent->GetSearchPeriod(p));
			return false;
		};

		CompressPortion(ResultArchive, InputTokens, PrevStart, j, m_bCompressOccurrences);
	}
	else
	{
		//no occurrences in the last search period
	}

    // the rest of search periods
	for(; CurrentPeriod < m_pParent->GetSearchPeriodsCount(); CurrentPeriod++)
		EndOffsets[CurrentPeriod]	 = ResultArchive.size();

	assert (EndOffsets.size() == m_pParent->GetSearchPeriodsCount());

	m_EndPeriodOffsets.ensureMap();
	if ( m_EndPeriodOffsets.m_map.find (PerDivId) != m_EndPeriodOffsets.m_map.end() ) {
		fprintf (stderr, "token id %i fo period division is not unique, index name = %s\n", PerDivId, GetName().c_str() );
		return false;
	}

	m_EndPeriodOffsets.m_map[PerDivId] = EndOffsets;


	// writing back to IndexItem archived version of occurrences
	InputTokens = ResultArchive;

	return true;
};

bool	CIndexSetForQueryingStage::AddOneIndexItem (CItemIndexForLoading& M, FILE* res_fp, size_t& CurrPositionInResFile, const CTokenNo EndTokeNo)
{
	CIndexItem I;
    I.SetIndexItemOffsetAndFlags(M.GetIndexItemOffset() | 0);
    

	if (!M.CheckOccurrences(EndTokeNo))
	{
		ErrorMessage(Format("CheckOccurrences failed!\n Index Name: %s\nCount of occurrences=%i\n IndexItemOffset=%i\n", 
			GetName().c_str(), 
			M.GetOccursSize(), 
			M.GetIndexItemOffset()
			
			));
		return false;
	};

	if (M.GetOccursSize() == 1)
	{
		I.SetEndOccurOffset( (*M.GetOccurs())[0] );
		I.AddItemIndexFlags ( TheOnlyOccurIsInEndOccurNo );
	}
	else
	{

        if (!BuildPeriodsDivisionAndCompress(m_Index.size(), *M.GetOccurs() ) )
		{
			return false;;
		};

		I.SetEndOccurOffset( CurrPositionInResFile + M.GetOccursSize() );
		CurrPositionInResFile += M.GetOccursSize();
		
		if (!M.WriteOccurrences(res_fp)) return false;
	};

	m_Index.push_back(I);
	return true;
};


bool	CIndexSetForQueryingStage::WritePeriodsDivision ()
{
	string FName = GetPeriodsDivisionFileName();
	FILE * fp = fopen (FName.c_str(), "wb");
	if (!fp) return false;
	size_t count = 0;
	m_EndPeriodOffsets.ensureMap();
	for (PeriodsDivisionMapR::const_iterator it = m_EndPeriodOffsets.m_map.begin(); it != m_EndPeriodOffsets.m_map.end();it++)
	{
		DWORD t = it->first;
		if (fwrite(&t,sizeof(t),1, fp) != 1)
		{
			fclose (fp);
			return false;
		}
		assert (it->second.size() == m_pParent->GetSearchPeriodsCount());
		if (!WriteVectorInner(fp, it->second))
		{
			fclose (fp);
			return false;
		}
		count++;
	};
	fclose(fp);
	printf ("To file %s %zi vectors were written \n", FName.c_str(), count);
	return true;

};

bool	CIndexSetForQueryingStage::LoadPeriodDivision()
{
	try {
		m_EndPeriodOffsets.open(GetPeriodsDivisionFileName(), m_pParent->GetSearchPeriodsCount(), m_pParent->m_bMemoryMap);
	}
	catch (CExpc &e) {
		fprintf (stderr, "Exception[%d] %s in CIndexSetForQueryingStage::LoadPeriodDivision: %s\n", e.code(), e.what());
		return false;
	}
	catch (exception &e) {
		fprintf (stderr, "Exception in CIndexSetForQueryingStage::LoadPeriodDivision(): %s\n", e.what());
		return false;
	}
	catch (...) {
		fprintf (stderr, "Exception in CIndexSetForQueryingStage::LoadPeriodDivision(): (unhandled exception)\n");
		return false;
	}
	return true;
};
