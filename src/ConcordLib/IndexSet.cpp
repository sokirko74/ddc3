//-*- Mode: C++; c-basic-offset: 8;-*-
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
#include "IndexSet.h"
#include "ConcIndexator.h"

//#define DDC_DEBUG_UNION 1

#ifdef DDC_DEBUG_UNION
# define udebug(msg) ddcLogDebug(x)
# define utrace(msg) ddcLogTrace(x)
#else
# define udebug(msg)
# define utrace(msg)
#endif

//==============================================
//================== CStringIndexSet ==========
//===============================================

CStringIndexSet::CStringIndexSet(const CStringIndexator* pParent)
  : CIndexSetForQueryingStage(pParent)
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



ddcVecFile<CIndexItem>::const_iterator CStringIndexSet::GetTypeIndexIdLowerBoundIter(const string& ValueStr) const
{
	LessIndexString1<CIndexItem,char*> Less(&m_StringBuffer.m_data);
	return lower_bound (m_Index.begin(), m_Index.end(), ValueStr.c_str(), Less);
};

ddcVecFile<CIndexItem>::const_iterator CStringIndexSet::GetTypeIndexIdUpperBoundIter(const string& ValueStr) const
{
	LessIndexString1<CIndexItem,char*> Less(&m_StringBuffer.m_data);
	return upper_bound (m_Index.begin(), m_Index.end(), ValueStr.c_str(), Less);
};

DWORD CStringIndexSet::GetTypeIndexIdLowerBound(const string& ValueStr)	const
{
	return GetTypeIndexIdLowerBoundIter(ValueStr) - m_Index.begin();
};

DWORD CStringIndexSet::GetTypeIndexId(const string& ValueStr)	const
{
	ddcVecFile<CIndexItem>::const_iterator it = GetTypeIndexIdLowerBoundIter(ValueStr);
	if (it != m_Index.end() && (!strcmp(GetIndexItemStr(*it),ValueStr.c_str())))
		return it - m_Index.begin();
	return DWORD_MAX;
}

void CStringIndexSet::QueryTokenList (const string& WordForm, vector<DWORD>& MatchWords)	const
{
	ddcVecFile<CIndexItem>::const_iterator it = GetTypeIndexIdLowerBoundIter(WordForm);

	if (MatchWords.size() > m_pParent->m_MaxRegExpExpansionSize)
		throw CExpc("too many expansions for query word `%s' (MaxRegExpExpansionSize=%zd)", WordForm.c_str(), m_pParent->m_MaxRegExpExpansionSize);

	if ( (it != m_Index.end()) && (!strcmp(GetIndexItemStr(*it),WordForm.c_str())) )
		MatchWords.push_back( it -  m_Index.begin() );
};

struct LessByPrefixIndex {
	const char*       m_pBuffer;

	LessByPrefixIndex(const char* pBuffer)
		: m_pBuffer(pBuffer)
	{};

	//! direct string-comparison (by prefix)
	inline bool operator()(const char *A, const char *B) const
	{
		while (*A && *B && *A==*B) { ++A; ++B; }
		return (*A && *A < *B);
	};


	//! less-than operator (for suffix-indices lower_bound())
	inline bool operator()(const CIndexItem& Ref, const char* Val) const
	{ return operator()(m_pBuffer+Ref.GetIndexItemOffset(), Val); };

	//! less-than operator (for suffix-indices upper_bound())
	inline bool operator()(const char* Val, const CIndexItem& Ref) const
	{ return operator()(Val, m_pBuffer+Ref.GetIndexItemOffset()); };
};

void CStringIndexSet::QueryTokenListWithRightTruncation (const string& Prefix, vector<DWORD>& MatchWords) const
{
	LessByPrefixIndex Less(m_StringBuffer.m_data);
	ddcVecFile<CIndexItem>::const_iterator lb = lower_bound(m_Index.begin(), m_Index.end(), Prefix.c_str(), Less);
	ddcVecFile<CIndexItem>::const_iterator ub = upper_bound(lb,              m_Index.end(), Prefix.c_str(), Less);
	if ( (ub-lb) > m_pParent->m_MaxRegExpExpansionSize )
		throw CExpc("too many expansions for query prefix `%s' (MaxRegExpExpansionSize=%zd)", Prefix.c_str(), m_pParent->m_MaxRegExpExpansionSize);

	size_t offset=lb-m_Index.begin(), count=(ub-lb), moffset=MatchWords.size();
	MatchWords.insert(MatchWords.end(), count, offset);
	for (size_t ii=0; moffset < MatchWords.size(); ++moffset, ++ii) {
		MatchWords[moffset] += ii;
	}
};

struct LessBySuffixIndex {
	const char*       m_pBuffer;
	const CIndexItem* m_pIndex;
	
	LessBySuffixIndex(const char* pBuffer=NULL, const CIndexItem* pIndex=NULL)
		: m_pBuffer(pBuffer), m_pIndex(pIndex)
	{};

	//! direct string-comparison (A<B) (by suffix)
	inline bool less(const char *A, const char *B) const
	{
		const char *a=(A+strlen(A)-1), *b=(B+strlen(B)-1);
		for ( ; a>=A && b >= B && *a && *b; --a,--b ) {
			if      (*a < *b) return true;
			else if (*a > *b) return false;
		}
		return false;
	};

	//! less-than operator (for suffix-indices lower_bound())
	inline bool operator()(const DWORD ItemId, const char* Val) const
	{ return less(m_pBuffer+m_pIndex[ItemId].GetIndexItemOffset(), Val); };

	//! less-than operator (for suffix-indices upper_bound())
	inline bool operator()(const char* Val, const DWORD ItemId) const
	{ return less(Val, m_pBuffer+m_pIndex[ItemId].GetIndexItemOffset()); };

	//! less-than operator (for suffix-index creation)
	inline bool operator()(const DWORD ItemIdA, const DWORD ItemIdB) const
	{
		string A(m_pBuffer+m_pIndex[ItemIdA].GetIndexItemOffset()),
		       B(m_pBuffer+m_pIndex[ItemIdB].GetIndexItemOffset());
		reverse(A.begin(),A.end());
		reverse(B.begin(),B.end());
		return A < B;
	};
};

void CStringIndexSet::QueryTokenListWithLeftTruncation (const string& Suffix, vector<DWORD>& MatchWords)	const
{
	if (!m_rIndex)
		throw CExpc("ERROR: CStringIndexSet::QueryTokenListWithLeftTruncation() called but no suffix index is defined");
	//fprintf(stderr, "DEBUG: QueryTokenListWithLeftTruncation(%s)\n", Suffix.c_str());

	//-- LessBySuffixIndex: v2.1.21/1d-index,cstr+strlen
	LessBySuffixIndex Less(m_StringBuffer.m_data, m_Index.m_data);
	CSuffixIndex::const_iterator lb = lower_bound(m_rIndex.begin(), m_rIndex.end(), Suffix.c_str(), Less);
	CSuffixIndex::const_iterator ub = upper_bound(lb,               m_rIndex.end(), Suffix.c_str(), Less);
	if ( (ub-lb) > m_pParent->m_MaxRegExpExpansionSize )
		throw CExpc("too many expansions for query suffix `%s' (MaxRegExpExpansionSize=%zd)", Suffix.c_str(), m_pParent->m_MaxRegExpExpansionSize);

	MatchWords.insert(MatchWords.end(), lb, ub);
};


void CStringIndexSet::QueryTokenListUsingRegExp (RML_RE &RegExp, vector<DWORD>& MatchWords, bool negated, bool ignore_diacritics) const
{
	size_t Count = m_Index.size();
	if (!ignore_diacritics) {
		//-- honor diacritics (usual case)
		for( size_t i=0; i<Count; i++ ) {
			const char* str =  GetIndexItemStr(m_Index[i]);
			bool  ismatch = RegExp.PartialMatch(str);
			if ( negated ? (!ismatch) : ismatch ) {
				if (MatchWords.size() > m_pParent->m_MaxRegExpExpansionSize)
					throw CExpc("too many expansions for regex /%s/ (MaxRegExpExpansionSize=%zd)",
						    RegExp.pattern().c_str(), m_pParent->m_MaxRegExpExpansionSize);
				MatchWords.push_back( i );
			}
		}
	} else {
		//-- honor diacritics (iconv hack)
		ddcIconv iconv("UTF-8", "ASCII//TRANSLIT");
		string tmp;
		for( size_t i=0; i<Count; i++ ) {
			const char* str = GetIndexItemStr(m_Index[i]);
			iconv.convert(str, strlen(str), tmp);
			bool  ismatch = RegExp.PartialMatch(tmp);
			if ( negated ? (!ismatch) : ismatch ) {
				if (MatchWords.size() > m_pParent->m_MaxRegExpExpansionSize)
					throw CExpc("too many expansions for regex /%s/d (MaxRegExpExpansionSize=%zd)",
						    RegExp.pattern().c_str(), m_pParent->m_MaxRegExpExpansionSize);
				MatchWords.push_back( i );
			}
		}
	}
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
	m_StringBuffer.open(GetFileNameForInfos(), m_pParent->m_bMemoryMap);

	if (m_bUseItemStorage)
		if (!OpenStorageFile())
			return false;

	return true;
};

bool	CStringIndexSet::DestroyIndexSet()
{
	if (!CIndexSetForQueryingStage::DestroyIndexSet ()) return false;

	m_StringBuffer.close();

	if (FileExists(GetStorageFileName().c_str()))
	{
		CloseStorageFile();
		if (remove(GetStorageFileName().c_str()))
			return false;
	};

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



bool	CStringIndexSet::SaveOnePartOfUnionTokenStorage(FILE * out_fp, const vector<DWORD>& Old2New) const
{
	DWORD Old;
	FSeek(m_StorageFile, 0, SEEK_SET);

	while (fread(&Old, sizeof(DWORD), 1, m_StorageFile) == 1)
	{
		if (Old >= Old2New.size())
			return false;
		if (fwrite(&(Old2New[Old]), sizeof(DWORD), 1, out_fp) != 1) 
			return false;
	};
	return true;
};

bool	CStringIndexSet::CreateUnionTokenStorages(const vector<CStringIndexSet*>& IndexSets, const vector<size_t>& TokenCounts, const vector< vector<DWORD> >& xlateItemId)
{
	assert(IndexSets.size()==xlateItemId.size());
	CloseStorageFile();

	FILE * out_fp = fopen(GetStorageFileName().c_str(), "wb");
	if (!out_fp) return false;
	for (size_t ixi=0; ixi < IndexSets.size(); ++ixi) {
		if (IndexSets[ixi]==NULL || !IndexSets[ixi]->m_bUseItemStorage) {
			//-- dummy storage
			DWORD tmp = 0;
			for (size_t n=0; n < TokenCounts[ixi]; ++n)
				fwrite(&tmp, sizeof(DWORD), 1, out_fp);
		}
		else {
			//-- real storage
			IndexSets[ixi]->SaveOnePartOfUnionTokenStorage(out_fp, xlateItemId[ixi]);
		}
	}			
	fclose (out_fp);

	return OpenStorageFile();
};

void    CStringIndexSet::EnsureSuffixIndex()
{
	if (m_rIndex && m_rIndex.size()==m_Index.size()) return;

	//-- initialize index
	m_rIndex.ensureVec();
	m_rIndex.m_vec.resize(m_Index.size());
	for (DWORD i=0; i < m_rIndex.m_vec.size(); ++i)
		m_rIndex.m_vec[i] = i;

	//-- sort index by reverse value-string
	m_Index.ensureVec();
	m_StringBuffer.ensureVec();
	LessBySuffixIndex Less( m_StringBuffer.m_vec.data(), m_Index.m_vec.data() );
	stable_sort(m_rIndex.m_vec.begin(), m_rIndex.m_vec.end(), Less);
};


bool	CStringIndexSet::CreatePartitionStorage(vector<CStringIndexSet*>& Partitions, const vector<CTokenNo>& EndTokenNo, const vector< vector<DWORD> >& xlateItemId) const
{
	assert(Partitions.size() == EndTokenNo.size());
	assert(Partitions.size() == xlateItemId.size());
	size_t cur = 0;
	for (size_t i=0; i < Partitions.size(); ++i) {
		Partitions[i]->CloseStorageFile();
		FILE *fp = fopen(Partitions[i]->GetStorageFileName().c_str(), "wb");
		DWORD itemIdOld, itemIdNew;
		size_t StartTokenNo = cur;
		if (fp == NULL)
			throw CExpc("CStringIndexSet::CreatePartitionStorage(): Error: open failed for file "+Partitions[i]->GetStorageFileName());
		for ( ; cur < EndTokenNo[i]; ++cur) {
			if (fread(&itemIdOld, sizeof(DWORD), 1, m_StorageFile) != 1)
				throw CExpc(Format("CStringIndexSet::CreatePartitionStorage(): Error: failed to read token #%zd from storage file '%s'",
						   cur, GetStorageFileName().c_str()));
			itemIdNew = xlateItemId[i][itemIdOld];
			if (itemIdNew == DWORD_MAX)
				throw CExpc(Format("CStringIndexSet::CreatePartitionStorage(): Error: token #%zd target itemId==DWORD_MAX==%zd for source itemId=#%zd, partition %zd",
						   cur, itemIdNew, itemIdOld, i));
			if (fwrite(&itemIdNew, sizeof(DWORD), 1, fp) != 1)
				throw CExpc(Format("CStringIndexSet::CreatePartitionStorage(): Error: failed to write token #%zd to storage file '%s'",
						   (cur-StartTokenNo), Partitions[i]->GetStorageFileName().c_str()));
		}
		if (fclose(fp) != 0)
			throw CExpc("CStringIndexSet::CreatePartitionStorage(): Error: close failed for file "+Partitions[i]->GetStorageFileName());
	}
	return true;
}


void	CStringIndexSet::UnionIndexSets(const vector<CStringIndexSet*>& IndexSets, const vector<size_t>& TokenCounts)
{
	assert(IndexSets.size()==TokenCounts.size());
	m_Index.clear();
	m_StringBuffer.ensureVec();

	//-- phase 1: get list of all string values (expensive)
	set<string> ItemStrings;
	string s;
	for (size_t i=0; i < IndexSets.size(); ++i) {
		if (IndexSets[i]==NULL || (m_bUseItemStorage && !IndexSets[i]->m_bUseItemStorage)) {
			//-- force include empty string (it will get item-id 0)
			ItemStrings.insert("");
			if (IndexSets[i]==NULL) continue;
		}
		for (size_t ItemId=0; ItemId < IndexSets[i]->m_Index.size(); ++ItemId) {
			s = IndexSets[i]->GetIndexItemStr(IndexSets[i]->m_Index[ItemId]);
			if (ItemStrings.find(s) == ItemStrings.end())
				ItemStrings.insert(s);
		}
	}
	if (ItemStrings.size() >= DWORD_MAX)
		throw CExpc("CStringIndexSet::UnionIndexSets(): Error: vocabulary size (%zd) too large for index %s %s (max=%zd)",
			    ItemStrings.size(), m_Name.c_str(), m_ShortName.c_str(), (size_t)DWORD_MAX-1);
	ddcLogDebug(Format("found %zd value type(s) for attribute %s", ItemStrings.size(), m_Name.c_str()));

	//-- phase 2: adopt occurrences
	FILE *res_fp = fopen(GetOccursFileName().c_str(), "wb");
	if (!res_fp)
		throw CExpc("CStringIndexSet::UnionIndexSets(): cannot open occurrences file %s", GetOccursFileName().c_str());

	CItemIndexForLoading M;
	if (!M.InitOccurs()) 
		throw CExpc ("CStringIndexSet::UnionIndexSets(): cannot initialize occurrences buffer");
	size_t CurrPositionInResFile = 0;

	vector< vector<DWORD> > xlateItemId(IndexSets.size());
	for (size_t i=0; i < IndexSets.size(); ++i) {
		if (IndexSets[i] != NULL) xlateItemId[i].resize(IndexSets[i]->m_Index.size());
	}
	vector<CTokenNo> occurs;
	DWORD outId = 0;
	for (set<string>::const_iterator si=ItemStrings.begin(); si!=ItemStrings.end(); ++si, ++outId) {
		M.SetIndexItemOffset(m_StringBuffer.m_vec.size());
		M.GetOccurs()->clear();
		AddItemStrToBuffer(si->c_str(), si->size());
		//m_StringBuffer.ensureData();
		utrace(Format("adding type %zd=\"%s\"", M.GetIndexItemOffset(), si->c_str()));

		size_t offset = 0;
		for (size_t ixi=0; ixi < IndexSets.size(); ++ixi) {
			DWORD ixId = (IndexSets[ixi] != NULL ? IndexSets[ixi]->GetTypeIndexId(*si) : DWORD_MAX);
			if (ixId != DWORD_MAX) {
				//-- type is present in sub-index: adopt occurrences
				xlateItemId[ixi][ixId] = outId;
				IndexSets[ixi]->ReadAllOccurrences(ixId, occurs);
				for (vector<CTokenNo>::iterator occi=occurs.begin(); occi<occurs.end(); ++occi)
					*occi += offset;
				M.GetOccurs()->insert(M.GetOccurs()->end(), occurs.begin(), occurs.end());
				utrace(Format("-> found %zd occurrences from %s", occurs.size(), IndexSets[ixi]->GetOccursFileName().c_str()));
			}
			offset += TokenCounts[ixi];
		}
		//-- format the occurrences accordingly
		utrace(Format("-> found %zd total occurrences", M.GetOccurs()->size()));
		if (!AddOneIndexItem(M, res_fp, CurrPositionInResFile, offset))
			throw CExpc("CStringIndexSet::UnionIndexSets(): Error: failed to add index item for string '"+*si+"'");
	}

	//-- cleanup
	M.FreeOccurs();
	ItemStrings.clear();
	fclose(res_fp);

	//-- store string buffer (this is done by FinalSaveAllIndices)
	//m_StringBuffer.save(GetFileNameForInfos());

	//-- store index
	//m_Index.save(GetOccHdrFileName());

	//-- store "period division" map
	if (!WritePeriodsDivision())
		throw CExpc("CStringIndexSet::UnionIndexSets(): Error: failed to write period division");

	//-- merge storage files
	if (m_bUseItemStorage && !CreateUnionTokenStorages(IndexSets,TokenCounts,xlateItemId))
		throw CExpc("CStringIndexSet::UnionIndexSets(): Error: cannot create union storage file "+GetStorageFileName());
};

#undef DDC_DEBUG_SPLIT
void CStringIndexSet::CreatePartitions(vector<CStringIndexSet*>& Partitions, const vector<CTokenNo>& EndTokenNo) const
{
	string logname = "CStringIndexSet::CreatePartitions("+m_Name+")";

#ifdef DDC_DEBUG_SPLIT
	char debugfile[512];
	sprintf(debugfile,"CreatePartitions.%s.log", m_Name.c_str());
	FILE *fdebug = fopen(debugfile,"wb");
#endif
	
	//-- intialize: clear partitions
	ddcLogTrace(logname+": initialize");
	assert(Partitions.size() == EndTokenNo.size());
	vector<CItemIndexForLoading> M(Partitions.size());
	vector<FILE*> Mfp(Partitions.size());
	vector<size_t> Mpos(Partitions.size());
	vector< vector<DWORD> > xlateItemId(Partitions.size()); //-- [partition][oldId] -> newId_or_DWORD_MAX
	for (size_t i=0; i < Partitions.size(); ++i) {
		Partitions[i]->m_Index.clear();
		Partitions[i]->m_StringBuffer.ensureVec();

		if ( !M[i].InitOccurs() )
			throw CExpc(Format("CStringIndexSet::CreatePartitions(): cannot initialize occurrences buffer for partition #%zd", i));
		
		
		if ( !(Mfp[i] = fopen(Partitions[i]->GetOccursFileName().c_str(), "wb")) )
			throw CExpc("CStringIndexSet::CreatePartitions(): cannot open occurrences file "+Partitions[i]->GetOccursFileName());

		Mpos[i] = 0;
		xlateItemId[i].resize(m_Index.size(), DWORD_MAX);
	}

	//-- churn through value-types and split up occurrences
	ddcLogTrace(logname+": split occurrences");
	vector<CTokenNo> occurs;
	for (DWORD ItemId=0; ItemId < m_Index.size(); ++ItemId) {
		ReadAllOccurrences(ItemId, occurs);
		const char* ItemStr = GetIndexItemStr(m_Index[ItemId]);
		CTokenNo offset = 0;
		vector<CTokenNo>::const_iterator occi=occurs.begin(), occj, occ_end=occurs.end();
		bool occ_none = (occi==occ_end); //-- no occurrences: "anonymized" token, see mantis #31586
		for (size_t i=0; i < Partitions.size(); ++i) {
			M[i].GetOccurs()->clear();
			occi = lower_bound(occi, occ_end, offset);
			if ((occi != occ_end && *occi < EndTokenNo[i]) || occ_none) {
				//-- at least one occurrence in this partition OR no occurrences at all 
				occj = occ_none ? occ_end : lower_bound(occi, occ_end, EndTokenNo[i]);
				M[i].SetIndexItemOffset(Partitions[i]->m_StringBuffer.m_vec.size());
				Partitions[i]->AddItemStrToBuffer(ItemStr, strlen(ItemStr));
				xlateItemId[i][ItemId] = Partitions[i]->m_Index.size();
#ifdef DDC_DEBUG_SPLIT
				fprintf(fdebug,"XLATE[%zd]\t%zd\t%zd\n", i, ItemId, Partitions[i]->m_Index.size());
#endif

				M[i].GetOccurs()->insert(M[i].GetOccurs()->end(), occi, occj);
				for (vector<CTokenNo>::iterator mocci=M[i].GetOccurs()->begin(); mocci != M[i].GetOccurs()->end(); ++mocci)
					*mocci -= offset;
				
				//-- format occurrences
				if (!Partitions[i]->AddOneIndexItem(M[i], Mfp[i], Mpos[i], EndTokenNo[i]))
					throw CExpc(Format("CStringIndexSet::CreatePartitions(): Error: failed to add index item for string '%s', partition #%zd", ItemStr, i));

				//-- update
				occi   = occj;
			}
			offset = EndTokenNo[i];
		}
	}
#ifdef DDC_DEBUG_SPLIT
	fclose(fdebug);
#endif

	//-- cleanup
	ClearVector(occurs);
	for (size_t i=0; i < Partitions.size(); ++i) {
		M[i].FreeOccurs();
		if (Mfp[i] != NULL && fclose(Mfp[i]) != 0)
			throw CExpc("CStringIndexSet::CreatePartitions(): Error: failed to close occurrences file "+Partitions[i]->GetOccursFileName());
	}

	//-- store "period division" maps
	ddcLogTrace(logname+": store period divisions");
	for (size_t i=0; i < Partitions.size(); ++i) {
		if (!Partitions[i]->WritePeriodsDivision())
			throw CExpc(Format("CStringIndexSet::CreatePartitions(): Error: failed to write period division map for partition #%zd",i));
	}

	//-- split storage files
	ddcLogTrace(logname+": split storage");
	if (m_bUseItemStorage && Partitions[0]->m_bUseItemStorage && !CreatePartitionStorage(Partitions, EndTokenNo, xlateItemId))
		throw CExpc("CStringIndexSet::CreatePartitions(): Error: cannot split storage file "+GetStorageFileName());
};

bool CStringIndexSet::GetTokensFromStorage(const size_t start_offset,  const size_t end_offset, vector<COutputToken>& Tokens) const
{
	if (!m_bUseItemStorage) return false;
	size_t count  = end_offset-start_offset;
	Tokens.resize(count);
	if (count == 0) return true;
	file_off_t read_offset =  (QWORD)start_offset*(QWORD)sizeof(DWORD);

	lock();
	if (!FSeek (m_StorageFile, read_offset, SEEK_SET)) { unlock(); return false; }
	for (size_t i=0; i < count; i++)
	{
		DWORD u;
		if (fread(&(u),sizeof(u), 1, m_StorageFile) != 1) { unlock(); return false; }
		if (u > m_Index.size()) { unlock(); return false; }
		Tokens[i].m_TokenStr  = GetIndexItemStr(m_Index[u]);
		Tokens[i].m_Highlight = 0;
	};
	unlock();
	return true;
};

DWORD CStringIndexSet::GetTokenIndexId(CTokenNo TokenNo) const
{
	if (!m_bUseItemStorage) return DWORD_MAX;
	file_off_t read_offset =  (QWORD)TokenNo*(QWORD)sizeof(DWORD);
	DWORD u;
	
	lock();
	if (!FSeek(m_StorageFile, read_offset, SEEK_SET)) { unlock(); return DWORD_MAX; }
	if (fread(&(u),sizeof(u), 1, m_StorageFile) != 1) { unlock(); return DWORD_MAX; }
	if (u >= m_Index.size()) { unlock(); return DWORD_MAX; }
	unlock();

	return u;
};

bool CStringIndexSet::GetContextBounds(CDDCFilterWithBounds &Filter, const string& LoValue, const string& HiValue) const
{
	Filter.clear();
	Filter.m_bSet = false;

	//-- lower bound, based on CConcXml::CFreeBiblStringIndex::GetFilterBounds() from Bibliography.cpp
	Filter.m_KeyLo.assign(INT_MIN,LoValue);
	if (!LoValue.empty()) {
		ddcVecFile<CIndexItem>::const_iterator ilo = GetTypeIndexIdLowerBoundIter(LoValue);
		if ( ilo != m_Index.end() )
			Filter.m_KeyLo.i = ilo-m_Index.begin();
		else
			Filter.m_KeyLo.i = INT_MAX;
	}

	//-- upper bound
	Filter.m_KeyHi.assign(INT_MAX,HiValue);
	if (!HiValue.empty()) {
		ddcVecFile<CIndexItem>::const_iterator ihi = GetTypeIndexIdUpperBoundIter(HiValue);
		if ( ihi != m_Index.end() )
			Filter.m_KeyHi.i = ihi-m_Index.begin();
		else
			Filter.m_KeyHi.i = m_Index.size();
	}

	return true;
}

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

void CStringIndexSet::CloseStorageFile()
{
	lock();
	if (m_StorageFile) 
	{
		fclose(m_StorageFile);
		m_StorageFile = 0;
	};
	unlock();
};

bool CStringIndexSet::OpenStorageFile()
{
	CloseStorageFile();
	lock();
	m_StorageFile = fopen(GetStorageFileName().c_str(), "rb");
	unlock();
	return m_StorageFile != 0;
};



bool	CStringIndexSet::ConvertTempStorageToPersistent()
{
	assert (m_bUseItemStorage);

	// if the procedure is called from ConcordAdd, then 
	//  the persistent file should be already built and m_TempStorageFile is null, no other actions
	if (!m_TempStorageFile) return true;

	

	map<DWORD,DWORD> BufferOffset2TokenNo;

	m_Index.ensureVec();
	assert (!m_Index.empty());

  	for (size_t i=0; i < m_Index.m_vec.size(); i++)
		BufferOffset2TokenNo[m_Index.m_vec[i].GetIndexItemOffset()] = i;

	
	
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
		//const char * _debug_view = GetIndexItemStr(I);
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





void CStringIndexSet::FindChunkOccurrences (const vector<DWORD>& IndexItems, vector<CTokenNo>& occurrences,  vector<DWORD>& ChunkLengths, size_t PeriodNo, CMyTimeSpanHolder& Profiler, CShortOccurCacheMap* pCaches, vector<int>& CacheIds)	const
{
		
	vector<CTokenNo> TempBuffer;

	vector<pair<CTokenNo, DWORD> > pos_and_lengths;

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
			vector<pair<CTokenNo, DWORD> > curr_pos_and_lengths;
			for (size_t k=0; k < curr_positions.size(); k++)
				curr_pos_and_lengths.push_back(make_pair(curr_positions[k], chunk_len));

			//add curr_pos_and_lengths to pos_and_lengths
			vector<pair<CTokenNo, DWORD> > new_pos_and_lengths;
			new_pos_and_lengths.resize(curr_pos_and_lengths.size() + pos_and_lengths.size());
			vector<pair<CTokenNo, DWORD> >::iterator it = 
				set_union(curr_pos_and_lengths.begin(), curr_pos_and_lengths.end(), pos_and_lengths.begin(), pos_and_lengths.end(), new_pos_and_lengths.begin());
			new_pos_and_lengths.resize(it - new_pos_and_lengths.begin());
			new_pos_and_lengths.swap(pos_and_lengths);
		}
	};

	Count = pos_and_lengths.size();
	for (size_t i=0; i < Count; i++)
	{
		DWORD l = pos_and_lengths[i].second;
		for (int k = 0; k<l; k++)
		{
			CTokenNo LastPositionOfChunk = pos_and_lengths[i].first;
			CTokenNo FirstPositionOfChunk = LastPositionOfChunk - l +1;
			occurrences.push_back(FirstPositionOfChunk+k);
		}
		ChunkLengths.push_back(l);
	};
	
};
	
