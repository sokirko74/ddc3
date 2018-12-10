//-*- Mode: C++; c-basic-offset: 8; -*-
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
#ifndef IndexSetForQueryingStage_h
#define IndexSetForQueryingStage_h


#include "../common/bserialize.h"
#include "../CommonLib/ddcThread.h"
#include "../CommonLib/ddcMMap.h"

/////////////////////////////////////////////////////////////////////////////
// PeriodsDivisionMap : type for mappping an index item no to its \ref perdiv_def "period division"

//!  a type for mappping an index item no to its \ref perdiv_def "period division"
//typedef map<DWORD, vector<DWORD> > PeriodsDivisionMap__OLD
typedef ddcMapFile<DWORD,DWORD>       PeriodsDivisionMapT;
typedef PeriodsDivisionMapT::MapT     PeriodsDivisionMapR;  ///< low-level resident std::map<> implementation in PeriodsDivisionMap::m_map
typedef PeriodsDivisionMapT::RecFileT PeriodsDivisionMapV;  ///< low-level virtual mmap()-based implementation in PeriodsDivisionMap::m_rfile



/////////////////////////////////////////////////////////////////////////////
// Flags for CIndexItem::m_IndexItemOffsetAndFlags

const DWORD TheOnlyOccurIsInEndOccurNo = 1<<31;
/*-- 2018-08-15: EndOfSentenceForBigrams flag is obsolete --*/
//const DWORD EndOfSentenceForBigrams = 1<<30;
//const DWORD AllFlags = TheOnlyOccurIsInEndOccurNo  | EndOfSentenceForBigrams;
const DWORD AllFlags = TheOnlyOccurIsInEndOccurNo;

/*!
	CIndexItem contains basic information about one index item. In the strict sense one index item
	is a connection between an indexed string and its occurrences. More generally the term "index item"
	is used to refer also an indexed string.
*/
class CIndexItem 
{
	// pointer to CStringIndexSet::m_StringBuffer and flags;
	DWORD				m_IndexItemOffsetAndFlags;

	// upper bound offset of occurrences in CIndexSetForQueryingStage::m_OccursFp
	DWORD				m_EndOccurOffset;

public:
	//! return m_IndexItemOffsetAndFlags for serialization
	DWORD	GetIndexItemOffsetAndFlags() const
	{
		return m_IndexItemOffsetAndFlags;
	};
	//! set m_IndexItemOffsetAndFlags for serialization
	void	SetIndexItemOffsetAndFlags(DWORD Value) 
	{
		m_IndexItemOffsetAndFlags = Value;
	};

	static size_t GetMaximalNumberOfRunningTokens()
	{
		return ~0 & ~AllFlags; 
	};

	//! returns a reference of this index item to CStringIndexSet::m_StringBuffer
	DWORD	GetIndexItemOffset() const
	{
		return m_IndexItemOffsetAndFlags & ~AllFlags;
	};
	
	//! sets a reference  of this index item to CStringIndexSet::m_StringBuffer
	void	SetIndexItemOffset(DWORD Value) 
	{
        m_IndexItemOffsetAndFlags &= AllFlags;
		m_IndexItemOffsetAndFlags |= Value & ~AllFlags;
	};
	//! returns  flags of  this  index item
	DWORD	GetItemIndexFlags() const
	{
		return m_IndexItemOffsetAndFlags & AllFlags;
	};
	//! set flags of  this  index item
	void	AddItemIndexFlags(DWORD Value) 
	{
		m_IndexItemOffsetAndFlags |= Value & AllFlags;
	};
	//! return the upper bound offset of occurrences in CIndexSetForQueryingStage::m_OccursFp
	DWORD GetEndOccurOffset() const 
	{
		return m_EndOccurOffset;
	};
	//! set the upper bound offset of occurrences in CIndexSetForQueryingStage::m_OccursFp
	void SetEndOccurOffset(DWORD EndOccurOffset)  
	{
		m_EndOccurOffset = EndOccurOffset;
	};
    bool HasOneOccurrence () const 
    {
        return (m_IndexItemOffsetAndFlags & TheOnlyOccurIsInEndOccurNo) != 0;
    }
};

inline size_t get_size_in_bytes (const CIndexItem& t)
{
	return 8;
};

inline size_t save_to_bytes(const CIndexItem& i, BYTE* buf)
{
	buf += save_to_bytes(i.GetIndexItemOffsetAndFlags(), buf);
	buf += save_to_bytes(i.GetEndOccurOffset(), buf);
	return get_size_in_bytes(i);
}

inline size_t restore_from_bytes(CIndexItem& i, const BYTE* buf)
{
	DWORD d;

	buf += restore_from_bytes(d, buf);
	i.SetIndexItemOffsetAndFlags(d);

	buf += restore_from_bytes(d, buf);
	i.SetEndOccurOffset(d);

	return get_size_in_bytes(i);
}

/////////////////////////////////////////////////////////////////////////////
// suffix-index

//#define DDC_SUFFIX_INDEX_OFFSETS 1
#undef DDC_SUFFIX_INDEX_OFFSETS
#ifdef DDC_SUFFIX_INDEX_OFFSETS
 class CSuffixItem {
 public:
	 DWORD m_ItemId;  //-- index of item in m_Index
	 DWORD m_Offset;  //-- offset of terminating '\0' for this value in m_StringBuffer

 public:
	 CSuffixItem(DWORD ItemId=0, DWORD Offset=0)
		 : m_ItemId(ItemId), m_Offset(Offset)
	 {};
 };
 inline size_t get_size_in_bytes (const CSuffixItem& t)
 { return 8; };

 inline size_t save_to_bytes(const CSuffixItem& i, BYTE* buf)
 {
	buf += save_to_bytes(i.m_ItemId, buf);
	buf += save_to_bytes(i.m_Offset, buf);
	return get_size_in_bytes(i);
 };
 inline size_t restore_from_bytes(CSuffixItem& i, const BYTE* buf)
 {
	buf += restore_from_bytes(i.m_ItemId, buf);
	buf += restore_from_bytes(i.m_Offset, buf);
	return get_size_in_bytes(i);
 };


 typedef ddcVecFile<CSuffixItem> CSuffixIndex;
#else
 typedef ddcVecFile<DWORD> CSuffixIndex;
#endif


/////////////////////////////////////////////////////////////////////////////
// forward decls

class CStringIndexator; 
class CItemIndexForLoading;

/////////////////////////////////////////////////////////////////////////////
/*!	This class is  a part of CStringIndexSet class which is used only during querying.  It contains
the important serialization primitives.
*/
class CIndexSetForQueryingStage : public ddcLockable
{
	//! the main file of  occurrences 
	FILE*			m_OccursFp;
	
	
	//! close m_OccursFp
	void	CloseOccursFile();

	//! load all \ref perdiv_def "period divisions" to m_EndPeriodOffsets
	bool	LoadPeriodDivision();
	

protected:

	//!		return true, if the project path is initialized
	void	AssertHasPath() const;
	//!  a function for reading occurrences for one index item
	void	AddOccurs (size_t IndexItemNo, const bool bOneOccurrence, const size_t StartOccurNo, const size_t EndOccurNo, vector<CTokenNo>& Occurs, size_t PeriodNo, COccurrBuffer& OccursBuffer, CShortOccurCache* pCacheByIndexSet, int& CacheId) const;
	//!  return the file name  for the file occurrences
	string	GetOccursFileName() const;
	//!  return the name  of file for m_Index
	string	GetOccHdrFileName() const;
	//!  return the name  of file for m_rIndex (for suffix-queries)
	string	GetSuffixFileName() const;
	
	
	//!  return the name  of file for occurrences \ref perdiv_def "period division"
	string	GetPeriodsDivisionFileName () const;
	//!  return the name  of file for CIndexSetForLoadingStage::m_StringBuffer
	string	GetFileNameForInfos() const;
	//! return the size of the file for occurrences
	file_off_t	GetOccurrsFileSize() const;
	//!  get the offset of the first occurrence of index item no IndexNo in the file of occurrences(m_OccursFp)
	size_t	GetStartOccurNo(size_t IndexNo) const;
   	//!		build  a \ref perdiv_def "period division"  for one index item  
	bool	BuildPeriodsDivisionAndCompress (const DWORD TokenId, vector<CTokenNo>& InputTokens);
	//! write one index item to result file
	bool	AddOneIndexItem (CItemIndexForLoading& M, FILE* res_fp, size_t& CurrPositionInResFile, const CTokenNo EndTokeNo);
	//! write index item's \ref perdiv_def "period division"  to disk
	bool	WritePeriodsDivision ();


public:
	//! the main index(from strings to the ordered list of their occurrences) 
	ddcVecFile<CIndexItem>		m_Index;

	//! optional auxiliary index for suffix-queries; ItemIds lexicographically sorted by reverse string-value
	//ddcVecFile<DWORD>		m_rIndex; //-- 1d index
	CSuffixIndex			m_rIndex; //-- 2d index

	//! all corpus \ref perdiv_def "period divisions" for the long occurrence lists
	PeriodsDivisionMapT		m_EndPeriodOffsets;

	//! a pointer to the collection of indices, which contains a reference to this index
	const CStringIndexator*		m_pParent;

	//! if true, then the occurrences should be compresses (up to 30% for huge corpora)
	bool						m_bCompressOccurrences;


	CIndexSetForQueryingStage(const CStringIndexator*		pParent);
	~CIndexSetForQueryingStage();
	//! return the name of the index (CStringIndexSet::m_Name)
	virtual string GetName() const = 0;
	//! load index set from binaries
	bool	LoadIndexSet(bool bLoadHeaderOfOccurrences = true);
	//! destroy index set and remove index files
	bool	DestroyIndexSet ();
	//! reads all occurrences of IndexItemNo (this function can allocate much memory; it should be used carefully)
	void ReadAllOccurrences (size_t IndexItemNo, vector<CTokenNo>& Occurs) const;

	//! reads \a Count occurences starting at \a FilePosition from \a m_OccursFp into \a OutBuffer
	//! + ddc-v2.1.0: file-access (m_OccursFp); implicitly locks & unlocks the object
	void ReadOccurrences (CTokenNo* OutBuffer, file_off_t FilePosition, size_t Count) const;
};



#endif
