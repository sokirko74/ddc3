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
// QNode.cpp: implementation of the CQNode class.
//
//////////////////////////////////////////////////////////////////////

#include "StdConc.h"
#include "QueryNode.h"
#include "Query.h"
#include "../common/DwdsThesaurus.h"
#include "../common/util_classes.h"
#include "../CommonLib/utilit.h"
#include "../PCRE/pcre_rml.h"

extern CDwdsThesaurus* pDwdsThesaurus;

#ifdef DETECT_MEMORY_LEAK
	#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
	#endif
#endif

//#pragma intrinsic(memcpy, memcmp, memset, strlen,strcpy)


const size_t MaxDistanceForNear = 32;
#define GetOccurrencesSize() m_Occurrences.size()  

//======================== CQueryNode =====================

CQueryNode::~CQueryNode()
{
	ClearVector(m_Occurrences);
	ClearVector(m_OccurrenceNodeIndices);
	ClearVector(m_OccurrenceMatchIds);
	/*
	ClearVector(m_Hits);
	ClearVector(m_ChunkLengths);
	ClearVector(m_ChunkOffsets);
	ClearVector(m_CacheIds);
	*/
};

size_t CQueryNode::GetNodeFrequencyByNodeIndex(size_t NodeIndex) const
{
	assert (false);
	return 0;
}

/*
	EvaluateWithoutHits is the first stage of  the evaluation of one query.
	The main task it to build CQueryNode::m_Occurrences, which is written by chunks,
	sorted by the first item of a chunk. 

*/
void	CQueryNode::EvaluateWithoutHits() 
{
};	

void	CQueryNode::Evaluate(bool bSeparateHits)
{
	throw  CExpc (errParseError, "not implemented!");
};	

void	CQueryNode::EnsureChunkOffsets()
{
	if (m_ChunkOffsets.empty()) {
		m_ChunkOffsets.resize(m_ChunkLengths.size());
		DWORD offset=0;
		for (size_t i=0; i < m_ChunkLengths.size(); ++i) {
			m_ChunkOffsets[i] = offset;
			offset += m_ChunkLengths[i];
		}
	}
};

void	CQueryNode::SetNegation(bool Value)
{
	m_bNegated = Value;
}
bool	CQueryNode::GetNegation() const
{
	return m_bNegated;
};


void	CQueryNode::AddOccurrences(const CQueryNode& FromNode, int start, int end)
{
	m_Occurrences.insert(m_Occurrences.end(), FromNode.m_Occurrences.begin()+start,  FromNode.m_Occurrences.begin()+end);

	if (m_bUseNodeIndices)
		m_OccurrenceNodeIndices.insert(m_OccurrenceNodeIndices.end(), FromNode.m_OccurrenceNodeIndices.begin()+start,  FromNode.m_OccurrenceNodeIndices.begin()+end);

	if (m_bUseMatchIds)
		m_OccurrenceMatchIds.insert(m_OccurrenceMatchIds.end(), FromNode.m_OccurrenceMatchIds.begin()+start,  FromNode.m_OccurrenceMatchIds.begin()+end);
}

void	CQueryNode::AddOccurrences2(const CQueryNode& FromNode1, int start1, int end1,
				    const CQueryNode& FromNode2, int start2, int end2)
{
	if (!m_bUseNodeIndices && !m_bUseMatchIds) {
		//-- no node-indices or match-ids : just append to m_Occurrences[] and sort appended data
		size_t occsize0 = m_Occurrences.size();
		AddOccurrences(FromNode1, start1, end1);
		AddOccurrences(FromNode2, start2, end2);
		sort(m_Occurrences.begin()+occsize0, m_Occurrences.end());
	}
	else {
		//-- node-indices or match-ids in use: assume source nodes are sorted and append
		int i1, i2;
		m_Occurrences.reserve(m_Occurrences.size() + (end1-start1) + (end2-start2));
		for (i1=start1, i2=start2; i1 < end1 || i2 < end2; ) {
			const CQueryNode *pnod;
			int *pi;
			if (i1 < end1 && (i2 >= end2 || FromNode1.m_Occurrences[i1] <= FromNode2.m_Occurrences[i2])) {
				pnod = &FromNode1;
				pi   = &i1;
			} else {
				pnod = &FromNode2;
				pi   = &i2;
			}
			m_Occurrences.push_back(pnod->m_Occurrences[*pi]);
			if (m_bUseNodeIndices)
				m_OccurrenceNodeIndices.push_back(pnod->m_OccurrenceNodeIndices[*pi]);
			if (m_bUseMatchIds)
				m_OccurrenceMatchIds.push_back(pnod->m_OccurrenceMatchIds[*pi]);
			++(*pi);
		}
	}
}

void	CQueryNode::AddOccurrences3(const CQueryNode& FromNode1, int start1, int end1,
				    const CQueryNode& FromNode2, int start2, int end2,
				    const CQueryNode& FromNode3, int start3, int end3)
{
	if (!m_bUseNodeIndices && !m_bUseMatchIds) {
		//-- no node-indices or match-ids : just append to m_Occurrences[] and sort appended data
		size_t occsize0 = m_Occurrences.size();
		AddOccurrences(FromNode1, start1, end1);
		AddOccurrences(FromNode2, start2, end2);
		AddOccurrences(FromNode3, start3, end3);
		sort(m_Occurrences.begin()+occsize0, m_Occurrences.end());
	}
	else {
		//-- node-indices or match-ids in use: assume source nodes are sorted and append
		int i1, i2, i3;
		m_Occurrences.reserve(m_Occurrences.size() + (end1-start1) + (end2-start2) + (end3-start3));
		for (i1=start1, i2=start2, i3=start3; i1 < end1 || i2 < end2 || i3 < end3; ) {
			const CQueryNode *pnod;
			int *pi;
			if (i1 < end1
			    && (i2 >= end2 || FromNode1.m_Occurrences[i1] <= FromNode2.m_Occurrences[i2])
			    && (i3 >= end3 || FromNode1.m_Occurrences[i1] <= FromNode3.m_Occurrences[i3])) {
				pnod = &FromNode1;
				pi   = &i1;
			}
			else if (i2 < end2
				 && (i1 >= end1 || FromNode2.m_Occurrences[i2] <  FromNode1.m_Occurrences[i1])
				 && (i3 >= end3 || FromNode2.m_Occurrences[i2] <= FromNode3.m_Occurrences[i3])) {
				pnod = &FromNode2;
				pi   = &i2;
			}
			else {
				pnod = &FromNode3;
				pi   = &i3;
			}
			m_Occurrences.push_back(pnod->m_Occurrences[*pi]);
			if (m_bUseNodeIndices)
				m_OccurrenceNodeIndices.push_back(pnod->m_OccurrenceNodeIndices[*pi]);
			if (m_bUseMatchIds)
				m_OccurrenceMatchIds.push_back(pnod->m_OccurrenceMatchIds[*pi]);
			++(*pi);
		}
	}
}

void	CQueryNode::ClearAndReserveOccurrences(int size)
{
	m_Occurrences.clear();
	m_Occurrences.reserve(size);

	m_OccurrenceNodeIndices.clear();
	m_OccurrenceMatchIds.clear();
	if (m_bUseNodeIndices)
		m_OccurrenceNodeIndices.reserve(size);
	if (m_bUseMatchIds)
		m_OccurrenceMatchIds.reserve(size);
}

void	CQueryNode::SwapOccurrences(CQueryNode& Node, bool swapChunkLengths)
{
	Node.m_Occurrences.swap(m_Occurrences);
	Node.m_OccurrenceNodeIndices.swap(m_OccurrenceNodeIndices);
	Node.m_OccurrenceMatchIds.swap(m_OccurrenceMatchIds);
	if (swapChunkLengths) Node.m_ChunkLengths.swap(m_ChunkLengths);
}

bool CQueryNode::IsUniversalWildcard() const
{
	return false;
}

void CQueryNode::SetHolder(const CConcHolder*	pHolder)
{
	m_pHolder = pHolder;
	m_bUseNodeIndices = m_pHolder->HasRankOrderOperator();
	m_bUseMatchIds    = m_pHolder->HasMatchIdOperator();
}

/**
 * DDC_GETBREAK_LB_MIN
 *  + minimum number of tokens between "current" token and "current" break for which we'll use std::lower_bound()
 *    to find the next "current" break in CQueryNode::ConvertOccurrencesToHits(); otherwise linear search will be used
 *  + std::lower_bound() will never be used for break-increment if this is undefined
 *  + notes: LEMMA@QUERIES_PER_SEC
 */
//#undef DDC_GETBREAK_LB_MIN         /* Haus@246.202 , sein@26.129 */
//#define DDC_GETBREAK_LB_MIN 65536  /* Haus@589.553 , sein@26.008 */
#define DDC_GETBREAK_LB_MIN 16384  /* Haus@606.531 , sein@26.244 */
//#define DDC_GETBREAK_LB_MIN 4096   /* Haus@632.487 , sein@26.025 */
//#define DDC_GETBREAK_LB_MIN 1024   /* Haus@478.542 , sein@25.954 */
//#define DDC_GETBREAK_LB_MIN 0      /* Haus@552.938 , sein@23.047 */

void CQueryNode::ConvertOccurrencesToHits (bool bSeparateHits)
{
	const ddcBreakVector& Breaks = m_pHolder->GetBreaks();
	int TextAreasCount = m_pHolder->m_pIndexator->m_Bibl.GetTextAreasCount();
	int TextAreaNo = m_pHolder->GetTextArea();
	bool bTextAreaNo =  TextAreaNo != UnknownTextAreaNo;
	size_t cnt = GetOccurrencesSize();
	m_Hits.clear();
	m_Hits.reserve(cnt);

	ddcBreakVector::const_iterator
		break_it  = Breaks.begin(),
		break_end = Breaks.end();

	//ddcLogWarn(Format("ConvertOccurrencesToHits(%s): bLongSequence = %d", m_Source.c_str(), (bLongSequence ? 1 : 0)));

	CQueryNode NewNode(m_bUseNodeIndices, m_bUseMatchIds);
	if (bTextAreaNo)
		NewNode.ClearAndReserveOccurrences(GetOccurrencesSize());


	DWORD BreakNo;
	for (size_t i= 0;  i < cnt; i++)
	{
#ifdef DDC_GETBREAK_LB_MIN
		if ((m_Occurrences[i] - *break_it) >= DDC_GETBREAK_LB_MIN) {
			break_it = lower_bound (break_it, break_end, m_Occurrences[i]);
			//assert (break_it != Breaks.end());
			while (*break_it == m_Occurrences[i]) //-- avoid bogus empty breaks (pathological indices)
				break_it++;
		}
		else
#endif // DDC_GETBREAK_LB_MIN
		{
			// optimization for the very long sequence of m_Occurrences, lower_bound is too slow
			while (m_Occurrences[i] >= *break_it) ++break_it;
		}

		
		BreakNo = break_it - Breaks.begin();
		if (bTextAreaNo)
			if ( BreakNo%TextAreasCount != TextAreaNo ) // if it is the right text area
				continue;
			else
				NewNode.AddOccurrences(*this, i, i+1);
				


		if (	bSeparateHits
			|| m_Hits.empty() 
			|| ( m_Hits.back().m_BreakNo != BreakNo)
		   )
   		{
			CHit H(BreakNo);
			H.m_HighlightOccurrenceEnd = i+1;
			m_Hits.push_back(H);
		}
		else
			m_Hits.back().m_HighlightOccurrenceEnd = i+1;

	};

	if (bTextAreaNo)
		SwapOccurrences(NewNode, true);
		
};


void CQueryNode::ConvertOccurrencesToHitsForPatterns (bool bSeparateHits)	
{
	const ddcBreakVector& Breaks = m_pHolder->GetBreaks();
	m_Hits.clear();
	int TextAreasCount = m_pHolder->m_pIndexator->m_Bibl.GetTextAreasCount();
	int TextAreaNo = m_pHolder->GetTextArea();
	bool bTextAreaNo =  TextAreaNo != UnknownTextAreaNo;

	m_Hits.reserve(m_ChunkLengths.size());

	size_t cnt = GetOccurrencesSize();

	CQueryNode NewNode(m_bUseNodeIndices, m_bUseMatchIds);
	NewNode.ClearAndReserveOccurrences(cnt);
	NewNode.m_ChunkLengths.reserve(m_ChunkLengths.size());
	size_t InputStarter = 0;
	size_t NewOccurrencesCount = 0;

	ddcBreakVector::const_iterator break_it=Breaks.begin();
	bool bLongSequence = m_ChunkLengths.size()*5 > Breaks.size() ;
	
	size_t ChunkNo = 0;
	for (size_t i=0;  i < cnt; i += m_ChunkLengths[ChunkNo], ChunkNo++ )
	{
		DWORD ItemsCount = m_ChunkLengths[ChunkNo];

		if (!bLongSequence)
		{
			break_it = lower_bound (break_it, (ddcBreakVector::const_iterator)Breaks.end(), m_Occurrences[i]);
			assert (break_it != Breaks.end());
			while (*break_it == m_Occurrences[i])  //-- avoid bogus empty breaks (pathological indices)
				break_it++; // then Break is the first position of the next break
		}
		else
		{
			while(m_Occurrences[i] >= *break_it) break_it++;
		}

		DWORD break_start = (break_it==Breaks.begin() ? 0 : *(break_it-1));
		if (m_Occurrences[i] < break_start || m_Occurrences[i + ItemsCount - 1] >= *break_it)
		{
			 //this period of m_Occurrences should be ignored since 
			 // it belongs two or more breaks simultaneously
			continue;
		};

		DWORD BreakNo = break_it - Breaks.begin();
		if (bTextAreaNo) {
			if ( BreakNo%TextAreasCount != TextAreaNo ) {
				continue;
			}
		}

		NewNode.AddOccurrences(*this, i, i+ItemsCount);
		NewNode.m_ChunkLengths.push_back(ItemsCount);
		NewOccurrencesCount += ItemsCount;

		if (	bSeparateHits
			|| m_Hits.empty() 
			|| ( m_Hits.back().m_BreakNo != BreakNo)
		   )
   		{
			CHit H(BreakNo);
			H.m_HighlightOccurrenceEnd = NewOccurrencesCount;
			m_Hits.push_back(H);
		}
		else
		{
			m_Hits.back().m_HighlightOccurrenceEnd += ItemsCount;
			assert (m_Hits.back().m_HighlightOccurrenceEnd == NewOccurrencesCount); 
		};
		
	}

	SwapOccurrences(NewNode, true);
};

DWORD CQueryNode::GetFirstOccurrenceInHit(DWORD HitNo, BYTE MatchId) const
{
	DWORD beg = HitOccurrencesBegin(HitNo);
	DWORD end = HitOccurrencesEnd(HitNo);
	for (DWORD i=beg; i < end; ++i) {
		if (m_OccurrenceMatchIds[i] == MatchId) return i;
	}
	return (DWORD)-1;
}

DWORD CQueryNode::GetLastOccurrenceInHit(DWORD HitNo, BYTE MatchId) const
{
	DWORD beg = HitOccurrencesBegin(HitNo);
	DWORD end = HitOccurrencesEnd(HitNo);
	for (DWORD i=end-1; i >= beg && i < end; --i) {
		if (m_OccurrenceMatchIds[i] == MatchId) return i;
	}
	return (DWORD)-1;
}

DWORD CQueryNode::GetMiddleOccurrenceInHit(DWORD HitNo, BYTE MatchId) const
{
	DWORD beg = HitOccurrencesBegin(HitNo);
	DWORD end = HitOccurrencesEnd(HitNo);
	DWORD width = (end-beg)/2;
	DWORD mid = beg + width;
	DWORD off, i;
	for (off=0; off <= width; ++off) {
		if      ((i=mid-off) >= beg && i < end && m_OccurrenceMatchIds[i]==MatchId) return i;
		else if ((i=mid+off) >= beg && i < end && m_OccurrenceMatchIds[i]==MatchId) return i;
	}
	return (DWORD)-1;
}

// ================== CQueryBinaryOperationNode ==================

CQueryBinaryOperationNode::~CQueryBinaryOperationNode()
{
	if (m_pChild1)
		delete m_pChild1;
	if (m_pChild2)
		delete m_pChild2;
}


void CQueryBinaryOperationNode::Create(const CConcHolder*	pHolder, CQueryNode* child1, CQueryNode* child2, string Operation)
{
	SetHolder(pHolder);
	m_pChild1 = child1;
	m_pChild2 = child2;
	m_Source = child1->m_Source + Operation + child2->m_Source;
}

size_t CQueryBinaryOperationNode::GetNodeFrequencyByNodeIndex(size_t NodeIndex) const
{
	size_t Result = 0;
	if (m_pChild1) Result += m_pChild1->GetNodeFrequencyByNodeIndex(NodeIndex);
	if (m_pChild2) Result += m_pChild2->GetNodeFrequencyByNodeIndex(NodeIndex);
	return Result;
}




// ================== CQueryAndOperation ==================
CQueryAndOperation::CQueryAndOperation()
{
};

void CQueryBinaryOperationNode::hits_add(const CQueryNode& NodeFrom, vector<CHit>::const_iterator _First) 
{
	size_t prev_end =  0;
	if (_First !=  NodeFrom.m_Hits.begin() )
		prev_end = (_First-1)->m_HighlightOccurrenceEnd;

	vector<CHit>::const_iterator _Last = NodeFrom.m_Hits.end();

	for (; _First != _Last; _First++)
	{
		{
			size_t end = _First->m_HighlightOccurrenceEnd;
			AddOccurrences(NodeFrom, prev_end, end);
			prev_end = end;
		}
		{
			CHit  H(_First->m_BreakNo);
			H.m_HighlightOccurrenceEnd = GetOccurrencesSize();
			m_Hits.push_back(H);
		}
	};
};

void CQueryBinaryOperationNode::hits_and_positions_assign(const CQueryNode& NodeFrom)
{
	ClearAndReserveOccurrences(NodeFrom.m_Occurrences.size());
	AddOccurrences(NodeFrom, 0, NodeFrom.m_Occurrences.size());
	m_Hits = NodeFrom.m_Hits;
}

void CQueryBinaryOperationNode::hits_and_positions_swap(CQueryNode& NodeFrom)
{
	SwapOccurrences(NodeFrom, true);
	m_Hits.swap(NodeFrom.m_Hits);
}

void CQueryBinaryOperationNode::hits_and_positions_union(bool bSeparateHits) 
{
	//-- wildcard "optimization"
	if (m_pChild1->IsUniversalWildcard()) {
		m_pChild1->Evaluate(bSeparateHits);
		hits_and_positions_swap(*m_pChild1);
		return;
	}
	if (m_pChild2->IsUniversalWildcard()) {
		m_pChild2->Evaluate(bSeparateHits);
		hits_and_positions_swap(*m_pChild2);
		return;
	}
	
	//-- sub-query evaluation
	m_pChild1->Evaluate(bSeparateHits);
	m_pChild2->Evaluate(bSeparateHits);

	//-- search guts
	vector<CHit>::const_iterator
		hit1i = m_pChild1->m_Hits.begin(),
		hit1j = m_pChild1->m_Hits.end(),
		hit2i = m_pChild2->m_Hits.begin(),
		hit2j = m_pChild2->m_Hits.end();
	m_Hits.clear();
	m_Hits.reserve( m_pChild1->m_Hits.size() + m_pChild2->m_Hits.size() );
	ClearAndReserveOccurrences( m_pChild1->GetOccurrencesSize() + m_pChild2->GetOccurrencesSize() );

	size_t occ1=0, occ2=0;
	for ( ; hit1i != hit1j && hit2i != hit2j; ) {
		if (hit1i->m_BreakNo < hit2i->m_BreakNo) {
			//-- child1 only
			AddOccurrences(*m_pChild1, occ1, hit1i->m_HighlightOccurrenceEnd);
			pushHit(hit1i->m_BreakNo);
			occ1 = hit1i->m_HighlightOccurrenceEnd;
			++hit1i;
		}
		else if (hit1i->m_BreakNo > hit2i->m_BreakNo) {
			//-- child2 only
			AddOccurrences(*m_pChild2, occ2, hit2i->m_HighlightOccurrenceEnd);
			pushHit(hit2i->m_BreakNo);
			occ2 = hit2i->m_HighlightOccurrenceEnd;
			++hit2i;
		}
		else if (!bSeparateHits) {
			//-- child1 + child2 (join-mode): join daughters' occurrences
			AddOccurrences2(*m_pChild1, occ1, hit1i->m_HighlightOccurrenceEnd,
					*m_pChild2, occ2, hit2i->m_HighlightOccurrenceEnd);
			pushHit(hit1i->m_BreakNo);

			occ1 = hit1i->m_HighlightOccurrenceEnd;
			occ2 = hit2i->m_HighlightOccurrenceEnd;
			++hit1i;
			++hit2i;
		}
		else {
			//-- child1 + child2 (separate-mode): insert daughter-occurrences independently
			DWORD brkno = hit1i->m_BreakNo;
			for ( ; hit1i != hit1j && hit1i->m_BreakNo==brkno; ++hit1i) {
				AddOccurrences(*m_pChild1, occ1, hit1i->m_HighlightOccurrenceEnd);
				pushHit(hit1i->m_BreakNo);
				occ1 = hit1i->m_HighlightOccurrenceEnd;
			}
			for ( ; hit2i != hit2j && hit2i->m_BreakNo==brkno; ++hit2i) {
				AddOccurrences(*m_pChild2, occ2, hit2i->m_HighlightOccurrenceEnd);
				pushHit(hit2i->m_BreakNo);
				occ2 = hit2i->m_HighlightOccurrenceEnd;
			}
		}
	}


	//-- add trailing un-matchable hits
	hits_add(*m_pChild1, hit1i);
	hits_add(*m_pChild2, hit2i);
}


// DDC_HIT_INTERSECTION_BINSEARCH : use binay search lower_bound() for CQueryBinaryOperationNode::hits_and_positions_intersection()
//  + ca. 5-10% faster complex queries ("@auf @der @Lauer" && $l=@sein)
#define DDC_HIT_INTERSECTION_BINSEARCH 1
//#undef DDC_HIT_INTERSECTION_BINSEARCH

//#define DDC_HIT_INTERSECTION_BINSEARCH_COEF 1
//#define DDC_HIT_INTERSECTION_BINSEARCH_COEF 2
//#define DDC_HIT_INTERSECTION_BINSEARCH_COEF 3
#define DDC_HIT_INTERSECTION_BINSEARCH_COEF 4
//#define DDC_HIT_INTERSECTION_BINSEARCH_COEF 6
//#define DDC_HIT_INTERSECTION_BINSEARCH_COEF 8

//#define BINSEARCH_DEBUG(x) x
#define BINSEARCH_DEBUG(x)

void CQueryBinaryOperationNode::hits_and_positions_intersection(bool bSeparateHits)
{
#if 0
	//-- wildcard optimization: NOT HERE, so we can find e.g. all sentence-collocates with (count(foo && *=2 #sep) #by[$l=2])
	if (m_pChild1->IsUniversalWildcard()) {
		m_pChild2->Evaluate(bSeparateHits);
		hits_and_positions_swap(*m_pChild2);
		return;
	}
	if (m_pChild2->IsUniversalWildcard()) {
		m_pChild1->Evaluate(bSeparateHits);
		hits_and_positions_swap(*m_pChild1);
		return;
	}
#endif
	
	//-- sub-query evaluation
	m_pChild1->Evaluate(bSeparateHits);
	m_pChild2->Evaluate(bSeparateHits);

	//-- search guts
	vector<CHit>::const_iterator
		hit1i = m_pChild1->m_Hits.begin(),
		hit1j = m_pChild1->m_Hits.end(),
		hit2i = m_pChild2->m_Hits.begin(),
		hit2j = m_pChild2->m_Hits.end();
	m_Hits.clear();
	m_Hits.reserve( min(m_pChild1->m_Hits.size(),m_pChild2->m_Hits.size()) );
	ClearAndReserveOccurrences( min(m_pChild1->GetOccurrencesSize(),m_pChild2->GetOccurrencesSize()) );

#if defined(DDC_HIT_INTERSECTION_BINSEARCH)
	BINSEARCH_DEBUG( printf("binsearch enabled\n") );
	
	CHitCompareByBreak CompareByBreak;
	//-- breakStride : average size of gap between breaks in m_pChildX (for binary-search vs batch-increment heuristics)
	DWORD breakStride1 = max((size_t)1, (m_pChild1->m_Hits.back().m_BreakNo-m_pChild1->m_Hits.front().m_BreakNo) / m_pChild1->m_Hits.size());
	DWORD breakStride2 = max((size_t)1, (m_pChild2->m_Hits.back().m_BreakNo-m_pChild1->m_Hits.front().m_BreakNo) / m_pChild2->m_Hits.size());
#else
	BINSEARCH_DEBUG( printf("binsearch disabled\n") );
#endif
	/* binsearch, zeit(+debug), queries/sec

	 -binsearch
	   @Lauer && $l=@sein	->  3.588 (n=51)
	   @Haus && @Garten	-> 94.269 (n=144)
	   @das && @Haus 	->  7.474 (n=3994)
	   @auf && @der 	->  1.100 (n=230251)

	 +binsearch
	   @Lauer && $l=@sein	->  3.894 (n=51)
	   @Haus && @Garten	-> 94.976 (n=144)
	   @das && @Haus 	->  7.636 (n=3994)
	   @auf && @der 	->  0.928 (n=230251)

	 +batch-iter
	   @Lauer && $l=@sein	->   3.674 (n=51)
	   @Haus && @Garten	->  97.387 (n=144)
	   @das && @Haus 	->   7.596 (n=3994)
	   @auf && @der 	->   1.095 (n=230251)

	 +binsearch/heuristic[coef=1]
	   @Lauer && $l=@sein	->  3.831 (n=51)
	   @Haus && @Garten	-> 96.604 (n=144)
	   @das && @Haus 	->  7.638 (n=3994)
	   @auf && @der 	->  1.077 (n=230251)

	 +binsearch/heuristic[coef=2]
	   @Lauer && $l=@sein	->  3.869 (n=51)
	   @Haus && @Garten	-> 97.480 (n=144)
	   @das && @Haus 	->  7.750 (n=3994)
	   @auf && @der 	->  1.085 (n=230251)

	 +binsearch/heuristic[coef=3]
	   @Lauer && $l=@sein	->  3.889 (n=51)
	   @Haus && @Garten	-> 97.640 (n=144)
	   @das && @Haus 	->  7.714 (n=3994)
	   @auf && @der 	->  1.090 (n=230251)

	 +binsearch/heuristic[coef=4]
	   @Lauer && $l=@sein	->  3.895 (n=51)
	   @Haus && @Garten	-> 97.878 (n=144)
	   @das && @Haus 	->  7.722 (n=3994)
	   @auf && @der 	->  1.089 (n=230251)

	 +binsearch/heuristic[coef=6]
	   @Lauer && $l=@sein	->  3.867 (n=51)
	   @Haus && @Garten	-> 97.866 (n=144)
	   @das && @Haus 	->  7.706 (n=3994)
	   @auf && @der 	->  1.089 (n=230251)

	 +binsearch/heuristic[coef=8]
	   @Lauer && $l=@sein	->  3.831 (n=51)
	   @Haus && @Garten	-> 96.170 (n=144)
	   @das && @Haus 	->  7.674 (n=3994)
	   @auf && @der 	->  1.095 (n=230251)

       ----
       binsearch, zeit(+opt), queries/sec [vs OLD]

         OLD
	   @Lauer && $l=@sein	->  16.315 (n=51)
	   @Haus && @Garten	-> 456.788 (n=144)
	   @das && @Haus 	->  33.763 (n=3994)
	   @auf && @der 	->   6.260 (n=230251)

	 -binsearch
	   @Lauer && $l=@sein	->  21.920 (n=51)	+26%
	   @Haus && @Garten	-> 448.561 (n=144)	- 2%
	   @das && @Haus 	->  43.677 (n=3994)	+23%
	   @auf && @der 	->   8.039 (n=230251)	+22%

	 +binsearch
	   @Lauer && $l=@sein	->  25.407 (n=51)	+36%
	   @Haus && @Garten	-> 424.070 (n=144)	- 8%
	   @das && @Haus 	->  45.305 (n=3994)	+25%
	   @auf && @der 	->   6.850 (n=230251)	+ 9%

	 +batch-iter
	   @Lauer && $l=@sein	->  21.543 (n=51)	+24%
	   @Haus && @Garten	-> 440.684 (n=144)	- 4%
	   @das && @Haus 	->  44.893 (n=3994)	+25%
	   @auf && @der 	->   7.477 (n=230251)	+16%

	 +binsearch/heuristic[coef=4]
	   @Lauer && $l=@sein	->   25.304 (n=51)	+36%
	   @Haus && @Garten	->  434.858 (n=144)	- 5%
	   @das && @Haus 	->   47.461 (n=3994)	+29%
	   @auf && @der 	->    8.068 (n=230251)	+22%

	 +...
	   @Lauer && $l=@sein	->   (n=51)
	   @Haus && @Garten	->  (n=144)
	   @das && @Haus 	->   (n=3994)
	   @auf && @der 	->   (n=230251)
	*/
	
	size_t occ1=0, occ2=0;
	while (hit1i != hit1j && hit2i != hit2j) {
#if defined(DDC_HIT_INTERSECTION_BINSEARCH)
# if 0
		//-- break-binsearch: impl dispatch: always-binsearch
		if (hit1i->m_BreakNo < hit2i->m_BreakNo) {
			hit1i = lower_bound(++hit1i, hit1j, hit2i->m_BreakNo, CompareByBreak);
		}
		else if (hit1i->m_BreakNo > hit2i->m_BreakNo) {
			hit2i = lower_bound(++hit2i, hit2j, hit1i->m_BreakNo, CompareByBreak);
		}
# elif 0
		// break-binsearch: impl dispatch: batch-increment
		if (hit1i->m_BreakNo < hit2i->m_BreakNo) {
			
			do { ++hit1i; } while (hit1i < hit1j && hit1i->m_BreakNo < hit2i->m_BreakNo);
		}
		else if (hit1i->m_BreakNo > hit2i->m_BreakNo) {
			
			do { ++hit2i; } while (hit2i < hit2j && hit2i->m_BreakNo < hit1i->m_BreakNo);
		}
#else
		// break-binsearch: impl dispatch: heuristic
		if (hit1i->m_BreakNo < hit2i->m_BreakNo) {
			// break distance: d=(hit2i->m_BreakNo-hit1->m_BreakNo)
			// expected number of increment ops: d/breakStride1
			// expected number of binsearch ops: log2u32(hit1i->m_Breaks.end()-hit1i)
			if ((hit2i->m_BreakNo-hit1i->m_BreakNo)/breakStride1 > DDC_HIT_INTERSECTION_BINSEARCH_COEF*log2u32(hit1j-hit1i)) {
				BINSEARCH_DEBUG( printf("binsearch:1\n") );
				hit1i = lower_bound(++hit1i, hit1j, hit2i->m_BreakNo, CompareByBreak);
			} else {
				BINSEARCH_DEBUG( printf("batch-incr:1\n") );
				do { ++hit1i; } while (hit1i < hit1j && hit1i->m_BreakNo < hit2i->m_BreakNo);
			}
		}
		else if (hit1i->m_BreakNo > hit2i->m_BreakNo) {
			if ((hit1i->m_BreakNo-hit2i->m_BreakNo)/breakStride2 > DDC_HIT_INTERSECTION_BINSEARCH_COEF*log2u32(hit2j-hit2i)) {
				BINSEARCH_DEBUG( printf("binsearch:2\n") );
				hit2i = lower_bound(++hit2i, hit2j, hit1i->m_BreakNo, CompareByBreak);
			} else {
				BINSEARCH_DEBUG( printf("batch-incr:2\n") );
				do { ++hit2i; } while (hit2i < hit2j && hit2i->m_BreakNo < hit1i->m_BreakNo);
			}
		}
# endif 	//--/break-binsearch: impl dispatch
#else // !defined(DDC_HIT_INTERSECTION_BINSEARCH)
		if (hit1i->m_BreakNo < hit2i->m_BreakNo) {
			++hit1i;
		}
		else if (hit1i->m_BreakNo > hit2i->m_BreakNo) {
			++hit2i;
		}
#endif // DDC_HIT_INTERSECTION_BINSEARCH
		else if (!bSeparateHits) {
			//-- found a match (join-mode): join daughters' occurrences
			occ1 = hit1i==m_pChild1->m_Hits.begin() ? 0 : (hit1i-1)->m_HighlightOccurrenceEnd;
			occ2 = hit2i==m_pChild2->m_Hits.begin() ? 0 : (hit2i-1)->m_HighlightOccurrenceEnd;
			AddOccurrences2(*m_pChild1, occ1, hit1i->m_HighlightOccurrenceEnd,
					*m_pChild2, occ2, hit2i->m_HighlightOccurrenceEnd);
			pushHit(hit1i->m_BreakNo);

			++hit1i;
			++hit2i;
		}
		else {
			//-- found a match (separate-mode): insert all combinations of daughters' occurrences
			occ1 = hit1i==m_pChild1->m_Hits.begin() ? 0 : (hit1i-1)->m_HighlightOccurrenceEnd;
			occ2 = hit2i==m_pChild2->m_Hits.begin() ? 0 : (hit2i-1)->m_HighlightOccurrenceEnd;
			
			DWORD brkno = hit1i->m_BreakNo;
			vector<CHit>::const_iterator resume_hit2i = hit2i;
			size_t resume_occ2 = occ2;

			for ( ; hit1i != hit1j && hit1i->m_BreakNo==brkno; ++hit1i) {
				for (hit2i=resume_hit2i, occ2=resume_occ2; hit2i != hit2j && hit2i->m_BreakNo==brkno; ++hit2i) {
					AddOccurrences2(*m_pChild1, occ1, hit1i->m_HighlightOccurrenceEnd,
							*m_pChild2, occ2, hit2i->m_HighlightOccurrenceEnd);
					pushHit(brkno);
					occ2 = hit2i->m_HighlightOccurrenceEnd;
				}
				occ1 = hit1i->m_HighlightOccurrenceEnd;
			}

		}
	}
}

void CQueryBinaryOperationNode::hits_and_positions_difference(bool bSeparateHits)
{
	//-- wildcard optimization
	if (m_pChild2->IsUniversalWildcard()) {
		// (b && !*) ==> \emptyset
		ClearAndReserveOccurrences(0);
		m_Hits.clear();
		return;
	}
	
	//-- sub-query evaluation
	m_pChild1->Evaluate(bSeparateHits);
	m_pChild2->Evaluate(bSeparateHits);

	//-- search guts
	vector<CHit>::const_iterator
		hit1i = m_pChild1->m_Hits.begin(),
		hit1j = m_pChild1->m_Hits.end(),
		hit2i = m_pChild2->m_Hits.begin(),
		hit2j = m_pChild2->m_Hits.end();
	m_Hits.clear();
	m_Hits.reserve(m_pChild1->m_Hits.size());
	ClearAndReserveOccurrences(m_pChild1->GetOccurrencesSize());

#if defined(DDC_HIT_INTERSECTION_BINSEARCH)	
	CHitCompareByBreak CompareByBreak;
	//-- breakStride : average size of gap between breaks in m_pChildX (for binary-search vs batch-increment heuristics)
	DWORD breakStride2 = max((size_t)1, (m_pChild2->m_Hits.back().m_BreakNo-m_pChild2->m_Hits.front().m_BreakNo) / m_pChild2->m_Hits.size());
#endif

	size_t occ1=0;
	while ( hit1i != hit1j && hit2i != hit2j ) {
		if (hit1i->m_BreakNo < hit2i->m_BreakNo) {
			//-- hit1 only: insert (hit1..lb(hit1|hit2))
			occ1  = hit1i==m_pChild1->m_Hits.begin() ? 0 : (hit1i-1)->m_HighlightOccurrenceEnd;
			AddOccurrences(*m_pChild1, occ1, hit1i->m_HighlightOccurrenceEnd);
			pushHit(hit1i->m_BreakNo);
			occ1 = hit1i->m_HighlightOccurrenceEnd;
			++hit1i;
		}
		else if (hit1i->m_BreakNo > hit2i->m_BreakNo) {
			//-- hit2 only: skip hit2
#if defined(DDC_HIT_INTERSECTION_BINSEARCH)
			if ((hit1i->m_BreakNo-hit2i->m_BreakNo)/breakStride2 > DDC_HIT_INTERSECTION_BINSEARCH_COEF*log2u32(hit2j-hit2i)) {
				hit2i = lower_bound(++hit2i, hit2j, hit1i->m_BreakNo, CompareByBreak);
			} else {
				do { ++hit2i; } while (hit2i < hit2j && hit2i->m_BreakNo < hit1i->m_BreakNo);
			}
#else // !defined(DDC_HIT_INTERSECTION_BINSEARCH)
			do { ++hit2i; } while (hit2i < hit2j && hit2i->m_BreakNo < hit1i->m_BreakNo);
#endif  // DDC_HIT_INTERSECTION_BINSEARCH
		}
		else if (!bSeparateHits) {
			//-- hit1 == hit2: skip it (join-mode)
			occ1 = hit1i->m_HighlightOccurrenceEnd;
			++hit1i;
			++hit2i;
		}
		else {
			//-- hit1 == hit2: skip all (separate-mode)
			DWORD brkno = hit1i->m_BreakNo;
			for ( ; hit1i != hit1j && hit1i->m_BreakNo==brkno; ++hit1i )
				occ1 = hit1i->m_HighlightOccurrenceEnd;
			for ( ; hit2i != hit2j && hit2i->m_BreakNo==brkno; ++hit2i )
				;
		}
	}

	//-- add trailing hits from child1
	hits_add(*m_pChild1, hit1i);	
}


void CQueryAndOperation::Evaluate(bool bSeparateHits)
{
	if (!m_pChild1->GetNegation() && !m_pChild2->GetNegation()) {
		// (a && b)
		hits_and_positions_intersection(bSeparateHits);
	}
	else if (m_pChild1->GetNegation() && m_pChild2->GetNegation()) {
		// (!a && !b) == !(a || b)
		hits_and_positions_union(bSeparateHits);
		SetNegation(true);
	}
	else if (!m_pChild1->GetNegation() && m_pChild2->GetNegation()) {
		// (a && !b)
		hits_and_positions_difference(bSeparateHits);
	}
	else { //(m_pChild1->GetNegation() && !m_pChild2->GetNegation())
		// (!a && b)
		swap(m_pChild1, m_pChild2);
		hits_and_positions_difference(bSeparateHits);
	}
};

//=============   CQueryOrOperation =====================
CQueryOrOperation::CQueryOrOperation()
{
};

void CQueryOrOperation::Evaluate(bool bSeparateHits)
{
	if (!m_pChild1->GetNegation() && !m_pChild2->GetNegation()) {
		// (a || b)
		hits_and_positions_union(bSeparateHits);
	}
	else if (m_pChild1->GetNegation() && m_pChild2->GetNegation()) {
		// (!a || !b) ==> !(a&&b)
		hits_and_positions_intersection(bSeparateHits);
		SetNegation(true);
	}
	else if (m_pChild1->GetNegation() != m_pChild2->GetNegation()) {
		// (a || !b), (!a || b) ==> ERROR
		assert(false);
	}	
};


// ================ CQueryTokenNode ==================

CQueryTokenNode::CQueryTokenNode(int NodeIndex, BYTE MatchId)
	: CQueryNode(false,false)
{
	m_bAtomic = true;
	m_bChunk = false;
	m_bAnchor = false;
	m_bAny    = false;
	m_AnchorOffset = 0;
	m_NodeIndex = NodeIndex;
	m_MatchId      = (MatchId==0 ? DefaultMatchId : MatchId);
	m_bUseMatchIds = (m_MatchId > 0);
};

CQueryTokenNode::~CQueryTokenNode()
{
};

void CQueryTokenNode::SetMatchId(BYTE MatchId)
{
	m_MatchId      = (MatchId==0 ? DefaultMatchId : MatchId);
	m_bUseMatchIds = (MatchId > 0);
}

bool CQueryTokenNode::IsUniversalWildcard() const
{
	return m_bAny;
}

bool CQueryTokenNode::BuildRegExp(string RegExpStr, vector<DWORD>& IndexItems, bool negated)
{
	const CStringIndexSet*  IndexSet =  m_pHolder->m_pIndexator->GetIndexByAlias(m_IndexName);
	if (!IndexSet) return false;

	//-- check for & dispatch on "ignore diacritics" pseudo-modifier
	bool ignore_diacritics = false;
	string restr(RegExpStr);
	if (restr.size() >= 3 && restr[0]=='(' && restr[1]=='?') {
		size_t eom  = restr.find_first_of(":)",2);
		size_t dpos = 2;
		while (eom != restr.npos) {
			dpos = restr.find_first_of("d",dpos);
			if (dpos >= eom) break;
			ignore_diacritics = true;
			restr.erase(dpos,1);
			--eom;
		}
		if (ignore_diacritics) {
			//-- transliterate query regex too!
			ddcIconv iconv("UTF-8","ASCII//TRANSLIT");
			string tmp(restr);
			iconv.convert(tmp,restr);
		}
	}

	RML_RE re(restr, m_pHolder->m_pIndexator->GetRegexOptions());
	IndexSet->QueryTokenListUsingRegExp(re, IndexItems, negated, ignore_diacritics);
	return true;
};

bool CQueryTokenNode::CreateMorphAnnotationPattern(const CConcHolder* pHolder, const string& IndexName, const vector<string>& Items)
{
	SetHolder(pHolder);
	vector<string> m_Items(Items);
	sort(m_Items.begin(), m_Items.end());
	string RegExpStr = m_pHolder->m_pIndexator->GetIndexItemSetByVectorString(m_Items, true);

	m_Source.clear();
	for (vector<string>::const_iterator ii=m_Items.begin(); ii != m_Items.end(); ii++) {
		if (!m_Source.empty()) m_Source.push_back(';');
		m_Source += *ii;
	}

	m_IndexName = IndexName;
	m_IndexItems.clear();
	return BuildRegExp(RegExpStr, m_IndexItems);
}


bool CQueryTokenNode::CreateThesPattern(const CConcHolder* pHolder, const string& IndexName, const string& src)
{
	SetHolder(pHolder);
	m_Source = src;
	string s(src);
	RmlMakeUpper(s, pHolder->m_pIndexator->m_Language);	
	m_IndexName = IndexName;
	if (m_IndexName.empty()) m_IndexName = "Thes";
	m_IndexItems.clear();
	return BuildRegExp(":"+s+":", m_IndexItems);
}

bool	CQueryTokenNode::CreateChunkPattern(const CConcHolder* pHolder, const string& IndexName, const string& ChunkTypeStr)
{
	m_bChunk = true;
	m_bAnchor = false;
	m_bAtomic = true;
	SetHolder(pHolder);
	m_Source = ChunkTypeStr;
	if (!pHolder->m_pIndexator->m_pChunkIndex) return false;
	m_IndexName = IndexName;
	if (m_IndexName.empty()) m_IndexName = ChunkIndexName;
	return BuildRegExp(m_Source+",", m_IndexItems);
};

//--------------------------------------------------------------
bool	CQueryTokenNode::CreateAnchorPattern(const CConcHolder* pHolder, const string& BreakName, int anchorOffset)
{
  m_bChunk  = false;
  m_bAnchor = true;
  m_bAtomic = true;
  SetHolder(pHolder);
  m_IndexName = BreakName.empty() ? "s" : BreakName;
  m_AnchorOffset = anchorOffset;
  return true;  //-- occurrences are assigned directly to m_Occurrences[] by CQueryTokenNode::EvaluateWithoutHits()
};

size_t CQueryTokenNode::GetNodeFrequencyByNodeIndex(size_t NodeIndex) const
{
	if (m_NodeIndex == NodeIndex)
		return m_Occurrences.size();
	else
		return 0;
}


//--------------------------------------------------------------
CStringIndexSet* CQueryTokenNode::GetIndex(const CConcHolder* pHolder, const string &IndexName)
{
	SetHolder(pHolder);
	
	CStringIndexSet* pIndexSet;
	{
		string name = IndexName.empty() ? "Token" : IndexName;
		
		pIndexSet = pHolder->m_pIndexator->GetIndexByAlias(name);
		if (!pIndexSet)
			throw CExpc(errParseError,"GetIndex(): unknown index `%s'", IndexName.c_str());

		m_IndexName = pIndexSet->m_Name;
	};
	return pIndexSet;
}

//--------------------------------------------------------------
void CQueryTokenNode::MakeUnique(void)
{
	//-- (?) sort results in m_IndexItems (snagged from old CreateTokenPattern())
	sort(m_IndexItems.begin(),  m_IndexItems.end());
	vector<DWORD>::iterator endit = unique(m_IndexItems.begin(),  m_IndexItems.end());
	m_IndexItems.erase(endit,m_IndexItems.end());
}


//--------------------------------------------------------------
bool CQueryTokenNode::CreateStringPattern(const CConcHolder* pHolder, const string& IndexName, const string& Value)
{
	m_Source = string("$") + IndexName + "=@" + Value;
	CStringIndexSet* pIndexSet = GetIndex(pHolder,IndexName);

	m_IndexItems.clear();
	pIndexSet->QueryTokenList(Value, m_IndexItems);
	return true;
}

//--------------------------------------------------------------
bool CQueryTokenNode::CreateRegexPattern(const CConcHolder* pHolder, const string& IndexName, const string& Regex, bool negated)
{
	m_Source = string("$") + IndexName + "=/" + Regex + "/";
	CStringIndexSet* pIndexSet = GetIndex(pHolder,IndexName);
	if (Regex.empty())
		throw CExpc(errParseError,"Empty regular expression not allowed in query for index `%s'", IndexName.c_str());

	m_IndexItems.clear();
	return BuildRegExp(Regex, m_IndexItems, negated);
};

//--------------------------------------------------------------
bool CQueryTokenNode::CreateSetPattern(const CConcHolder* pHolder, const string& IndexName, const set<string>& Values)
{
	m_Source = string("$") + IndexName + "={...}";
	CStringIndexSet* pIndexSet = GetIndex(pHolder,IndexName);

	//-- query each item in the (pre-expanded) set individually
	m_IndexItems.clear();
	for (set<string>::const_iterator it = Values.begin(); it != Values.end(); it++) {
		pIndexSet->QueryTokenList(*it, m_IndexItems);
	}
	MakeUnique();
	return true;
};

//--------------------------------------------------------------
bool CQueryTokenNode::CreatePrefixSetPattern(const CConcHolder* pHolder, const string& IndexName, const set<string>& Prefixes)
{
	m_Source = string("$") + IndexName + "={...}*";
	CStringIndexSet* pIndexSet = GetIndex(pHolder,IndexName);

	m_IndexItems.clear();
	for (set<string>::const_iterator it = Prefixes.begin(); it != Prefixes.end(); it++) {
		pIndexSet->QueryTokenListWithRightTruncation(*it, m_IndexItems);
	}
	MakeUnique();
	return true;
};

//--------------------------------------------------------------
bool CQueryTokenNode::CreatePrefixPattern(const CConcHolder* pHolder, const string& IndexName, const string& Prefix)
{
	set<string> tmp;
	tmp.insert(Prefix);
	return CreatePrefixSetPattern(pHolder, IndexName, tmp);
}


//--------------------------------------------------------------
bool CQueryTokenNode::CreateSuffixSetPattern(const CConcHolder* pHolder, const string& IndexName, const set<string>& Suffixes)
{
	m_Source = string("$") + IndexName + "=*{...}";
	CStringIndexSet* pIndexSet = GetIndex(pHolder,IndexName);
	m_IndexItems.clear();
	string regex("(?:");
	for (set<string>::const_iterator it=Suffixes.begin(); it != Suffixes.end(); it++) {
		if (it != Suffixes.begin()) regex.push_back('|');
		regex += string("(?:\\Q") + *it + "\\E)";
	}
	regex += string(")$");
	return BuildRegExp(regex, m_IndexItems);
};

//--------------------------------------------------------------
bool CQueryTokenNode::CreateSuffixPattern(const CConcHolder* pHolder, const string& IndexName, const string& Suffix)
{
	set<string> tmp;
	tmp.insert(Suffix);
	return CreateSuffixSetPattern(pHolder, IndexName, tmp);
}

//--------------------------------------------------------------
bool CQueryTokenNode::CreateInfixSetPattern(const CConcHolder* pHolder, const string& IndexName, const set<string>& Infixes)
{
	m_Source = string("$") + IndexName + "=*{...}*";
	CStringIndexSet* pIndexSet = GetIndex(pHolder,IndexName);
	m_IndexItems.clear();
	string regex("(?:");
	for (set<string>::const_iterator it=Infixes.begin(); it != Infixes.end(); it++) {
		if (it != Infixes.begin()) regex.push_back('|');
		regex += string("(?:\\Q") + *it + "\\E)";
	}
	regex.push_back(')');
	return BuildRegExp(regex, m_IndexItems);
};

//--------------------------------------------------------------
bool CQueryTokenNode::CreateInfixPattern(const CConcHolder* pHolder, const string& IndexName, const string& Infix)
{
	set<string> tmp;
	tmp.insert(Infix);
	return CreateInfixSetPattern(pHolder, IndexName, tmp);
}

//--------------------------------------------------------------
bool CQueryTokenNode::CreateUniversalPattern(const CConcHolder* pHolder, const string& SourceStr)
{
  m_bChunk  = false;
  m_bAnchor = false;
  m_bAny    = true;
  m_bAtomic = true;
  m_Source    = SourceStr;
  m_IndexName.clear();
  SetHolder(pHolder);
  return true;  //-- occurrences are assigned directly to m_Occurrences[] by CQueryTokenNode::EvaluateWithoutHits()
};


//--------------------------------------------------------------
bool CQueryTokenNode::CreateLemmaPattern(const CConcHolder* pHolder, const string& Value)
{
	SetHolder(pHolder);
	m_Source = Value;
	m_IndexName = "Token";
	m_IndexItems.clear();

	string re = '^'+ Value.substr(1) + '@';
	RmlMakeLower(re, pHolder->m_pIndexator->m_Language);
	m_IndexName = "MorphAnnot";
	return BuildRegExp(re, m_IndexItems);
}


//--------------------------------------------------------------
bool CQueryTokenNode::CreateFileList(const CConcHolder* pHolder, const string &IndexName, const string& FileName)
{
	m_Source = string("$") + IndexName + "=<" + FileName;
	if (access(FileName.c_str(),R_OK) != 0) return false;

	set<string> values;
	{
		FILE* fp = fopen (FileName.c_str(),"r");
		if (!fp) return false;
		char buffer[1000];
		while (fgets(buffer,1000,fp)) {
			string s(buffer);
			Trim(s);
			if (!s.empty())
				values.insert(s);
		};
		fclose(fp);
	}
	return CreateSetPattern(pHolder, IndexName, values);
};



void CQueryTokenNode::EvaluateWithoutHits()
{
	ClearAndReserveOccurrences(5000);
	if (!m_bChunk && !m_bAnchor && !m_bAny) {
		const CStringIndexSet* pIndex  = m_pHolder->m_pIndexator->GetIndexByAlias(m_IndexName);
		pIndex->FindOccurrences(
					m_IndexItems, 
					m_pHolder->m_CurrentSearchPeriodNo, 
					m_Occurrences,
					m_pHolder->m_Profiler, 
					&m_pHolder->m_ShortOccurCaches,
					m_CacheIds
					);
		m_ChunkLengths.resize(GetOccurrencesSize(), 1);
	}
	else if (m_bAnchor) {
		//-- anchor query ($.=N)
		m_pHolder->m_pIndexator->GetOccurrencesByPosition(m_IndexName, m_AnchorOffset, m_Occurrences, m_pHolder->m_CurrentSearchPeriodNo);
		m_ChunkLengths.resize(GetOccurrencesSize(), 1); //-- near() queries use m_ChunkLengths[]
	}
	else if (m_bAny) {
		//-- universal query (*)
		m_pHolder->m_pIndexator->GetAllOccurrences(m_Occurrences, m_pHolder->m_CurrentSearchPeriodNo);
		m_ChunkLengths.resize(GetOccurrencesSize(), 1); //-- near() queries use m_ChunkLengths[]
	}
	else {
	  // chunk query
	  m_pHolder->m_pIndexator->m_pChunkIndex->FindChunkOccurrences(
								       m_IndexItems, 
								       m_Occurrences, 
								       m_ChunkLengths,
								       m_pHolder->m_CurrentSearchPeriodNo, 			
								       m_pHolder->m_Profiler, 
								       &m_pHolder->m_ShortOccurCaches,
								       m_CacheIds
								       );
	}

	if (m_bUseNodeIndices)
		m_OccurrenceNodeIndices.resize(m_Occurrences.size(), m_NodeIndex);
	if (m_bUseMatchIds)
		m_OccurrenceMatchIds.resize(m_Occurrences.size(), m_MatchId);
};



void CQueryTokenNode::Evaluate(bool bSeparateHits)
{
	EvaluateWithoutHits();
	if (m_bChunk)
		ConvertOccurrencesToHitsForPatterns(bSeparateHits);
	else
		ConvertOccurrencesToHits(bSeparateHits);
};


// ========= CQuerySequenceNode ======================
CQuerySequenceNode::CQuerySequenceNode()
 : CQueryNode(false)
{
	m_bAtomic = true;
};

CQuerySequenceNode::~CQuerySequenceNode()
{
	for (int i = 0; i < m_Items.size(); i++)
		delete m_Items[i];

};

bool CQuerySequenceNode::AddDistance(const string& s, char op)
{
	if (s=="0") 
	{
		m_Distances.push_back(0);
		m_DistanceOps.push_back(op);
		return true;
	}
	int distance = atoi(s.c_str());
	if (distance == 0)
		return false;
	if (distance > MaxDistanceForNear)
		return false;
	m_Distances.push_back(distance);
	m_DistanceOps.push_back(op);
	return true;
};

size_t CQuerySequenceNode::GetNodeFrequencyByNodeIndex(size_t NodeIndex) const
{
	size_t Result = 0;
	for (int i = 0; i < m_Items.size(); i++)
		Result += m_Items[i]->GetNodeFrequencyByNodeIndex(NodeIndex);
	return Result;
}


bool	CQuerySequenceNode::Create(const CConcHolder* pHolder, const vector<const CQueryNode*>& SequenceObj, const vector<string>& DistanceStrings)
{
	if (SequenceObj.size() != DistanceStrings.size() + 1)
	{
		// internal parse error
		return false;
	};
	

	for (int i = 0; i < DistanceStrings.size(); i++)
		if (!AddDistance(DistanceStrings[i].c_str()))
			return false;

	for (int i = 0; i < SequenceObj.size(); i++)
	{
		CQueryTokenNode* it = (CQueryTokenNode*)(void*) (SequenceObj[i]);
		m_Items.push_back(it);
	};

	SetHolder(pHolder);

	return true;	
};

bool	CQuerySequenceNode::Create(const CConcHolder* pHolder, const vector<CQueryTokenNode*>& Items, const vector<BYTE>& Distances, const vector<BYTE>& DistanceOps)
{
  if (Items.size() != Distances.size() + 1 || Distances.size() != DistanceOps.size()) {
    // internal parse error
    return false;
  }

  m_DistanceOps = DistanceOps;
  m_Distances = Distances;
  m_Items     = Items;

  SetHolder(pHolder);
  return true;	
};


/*

zeit(debug) queries/sec:

OLD:
 "@auf @der @Lauer"	->  8.764 (n=80)
 "@auf @der" 		->  5.106 (n=35118)
 "@das @Haus"		-> 13.044 (n=1666)

NEW/simple[binseek=undef]
 "@auf @der @Lauer"	-> 14.328 (n=80)
 "@auf @der" 		->  5.902 (n=35118)
 "@das @Haus"		-> 45.720 (n=1666)

NEW/simple[binseek=0]
 "@auf @der @Lauer"	-> 17.179 (n=80)
 "@auf @der" 		->  2.317 (n=35118)
 "@das @Haus"		-> 42.067 (n=1666)

NEW/simple[binseek=1024]
 "@auf @der @Lauer"	-> 17.503 (n=80)
 "@auf @der" 		->  5.551 (n=35118)
 "@das @Haus"		-> 49.295 (n=1666)

NEW/simple[binseek=4096]
 "@auf @der @Lauer"	-> 17.742 (n=80)
 "@auf @der" 		->  5.624 (n=35118)
 "@das @Haus"		-> 48.699 (n=1666)

-----
SEEK-RESUME[+debug]

OLD[binseek=undef]:
 "@auf @der @Lauer"	->    8.977 (n=80)
 "@auf @der" 		->    5.170 (n=35118)
 "@das @Haus"		->   13.588 (n=1666)

NEW/seek-resume[binseek=undef]
 "@auf @der @Lauer"	->    15.316 (n=80)
 "@auf @der" 		->     5.270 (n=35118)
 "@das @Haus"		->    48.077 (n=1666)

NEW/seek-resume[binseek=1024]
 "@auf @der @Lauer"	->    19.273 (n=80)
 "@auf @der" 		->     5.015 (n=35118)
 "@das @Haus"		->    48.867 (n=1666)

NEW/simple-seek-resume[binseek=1024]
 "@auf @der @Lauer"	->    19.150 (n=80)
 "@auf @der" 		->     6.623 (n=35118)
 "@das @Haus"		->    54.382 (n=1666)


-----
SEEKALL[+debug] -- no joy

OLD[binseek=undef]:
 "@auf @der @Lauer"	->    8.977 (n=80)
 "@auf @der" 		->    5.170 (n=35118)
 "@das @Haus"		->   13.588 (n=1666)

NEW/seekall[binseek=undef]:
 "@auf @der @Lauer"	->    0.856 (n=80)
 "@auf @der" 		->    4.908 (n=35118)
 "@das @Haus"		->    2.073 (n=1666)

NEW/seekall[binseek=1024]:
 "@auf @der @Lauer"	->    0.853 (n=80)
 "@auf @der" 		->    4.678 (n=35118)
 "@das @Haus"		->    2.035 (n=1666)

-----
zeit(opt) queries/sec:

OLD:
 "@auf @der @Lauer"	->   50.395 (n=80)
 "@auf @der" 		->   32.660 (n=35118)
 "@das @Haus"		->  119.649 (n=1666)

NEW/simple[LB_MIN=1024]:
 "@auf @der @Lauer"	->   72.131 (n=80)
 "@auf @der" 		->   32.011 (n=35118)
 "@das @Haus"		->  281.152 (n=1666)

NEW/simple[LB_COEF=4]:
 "@auf @der @Lauer"	->  123.637 (n=80)	+ 59%
 "@auf @der" 		->   34.774 (n=35118)	+  6%
 "@das @Haus"		->  388.651 (n=1666)	+ 69%

 */

template<typename T>
struct ProductIterator {
	vector<T> m_size;
	vector<T> m_cur;

	ProductIterator()
	{};

	ProductIterator(size_t nitems)
		: m_size(nitems,1)
	{ reset(); };

	ProductIterator(const vector<T>& sizes)
	{ assign(sizes); };

	ProductIterator(const vector< vector<T> >& vecs)
	{ assign(vecs); };


	inline void assign(const vector<T>& sizes)
	{
		m_size = sizes;
		reset();
	};

	inline void assign(const vector< vector<T> >& vecs)
	{
		m_size.resize(vecs.size());
		for (T i=0; i < vecs.size(); ++i)
			m_size[i] = vecs[i].size();
		reset();
	};

	inline void reset()
	{ m_cur.assign(m_size.size(), 0); };

	inline bool valid() const
	{ return m_cur.back() < m_size.back(); };

	inline operator bool() const
	{ return valid(); };

	//-- see https://codereview.stackexchange.com/questions/122699/finding-a-cartesian-product-of-multiple-lists
	void operator++()
	{
		do {
			for (T j=0; j < m_cur.size(); ++j) {
				//-- reset the slot if it can't be incremented
				if (++m_cur[j] >= m_size[j]) {
					//-- stop when the last enumerator resets
					if (j == m_cur.size()-1) return;

					//-- turnover
					m_cur[j] = 0;
					continue;
				}

				//-- we incremented m_cur[j] without reset, so stop here
				return;
			}
		} while (true);
	};
};

void CQuerySequenceNode::EvaluateWithoutHits()
{	
	int ItemsCount = m_Items.size();
	if (ItemsCount==1) {
		//-- special handling for singleton sequences
		m_Items[0]->EvaluateWithoutHits();
		AddOccurrences(*m_Items[0], 0, m_Items[0]->m_Occurrences.size()-1);
		return;
	}

	//-- evaluate non-trivial sub-queries and find the one with the smallest result-set (mini)
	vector<CQTokenOccurrenceIterator> iters(ItemsCount);
	vector<bool> ibind(ItemsCount);   //-- bind[i]==true iff m_Items[i] is a bound iterator
	size_t mini=(size_t)-1;           //-- index of item with smallest result-set
	for (size_t i=0; i < ItemsCount; ++i) {
		if (m_Items[i]->IsUniversalWildcard() && (mini != (size_t)-1 || i < (ItemsCount-1))) {
			ibind[i] = true;
			continue;
		}
		m_Items[i]->EvaluateWithoutHits();
		iters[i] = m_Items[i];
		ibind[i] = false;
		if (mini==(size_t)-1 || m_Items[i]->GetOccurrencesSize() < m_Items[mini]->GetOccurrencesSize())
			mini = i;
	}

	//-- bind wildcard iterators: left-to-right
	for (int i=mini+1; i < ItemsCount; ++i) {
		if (!ibind[i]) continue;
		int di=m_Distances[i-1], dmax=MaxDistanceForNear;
		switch (m_DistanceOps[i-1]) {
		default:
		case '<': iters[i].bind(m_Items[i], iters[i-1], 1,    1+di);   break;
		case '>': iters[i].bind(m_Items[i], iters[i-1], 1+di, 1+dmax); break;
		case '=': iters[i].bind(m_Items[i], iters[i-1], 1+di, 1+di);   break;
		}
	}
	//-- bind wildcard iterators: right-to-left
	for (int i=mini-1; i >= 0; --i) {
		if (!ibind[i]) continue;
		int di=m_Distances[i], dmax=MaxDistanceForNear;
		switch (m_DistanceOps[i]) {
		default:
		case '<': iters[i].bind(m_Items[i], iters[i+1], -1-di,   -1);    break;
		case '>': iters[i].bind(m_Items[i], iters[i+1], -1-dmax, -1-di); break;
		case '=': iters[i].bind(m_Items[i], iters[i+1], -1-di,   -1-di); break;
		}
	}


	//-- build minimum- and maximum-distance arrays
	//  + (min|max)Distance[i] is (min|max)imum distance between iters[i] and iters[i+1]
	//  + distances here are actual token-id differences (DDC "A #0 B" --> minDistance[0]=1)
	vector<DWORD> minDistance(m_Distances.size());
	vector<DWORD> maxDistance(m_Distances.size());
	bool bSimplePhrase = true;
	for (int i=0; i < m_Distances.size(); ++i) {
		switch (m_DistanceOps[i]) {
		default:
		case '<':
			minDistance[i] = 1;
			maxDistance[i] = m_Distances[i]+1;
			break;
		case '=':
			minDistance[i] = m_Distances[i]+1;
			maxDistance[i] = m_Distances[i]+1;
			break;
		case '>':
			minDistance[i] = m_Distances[i]+1;
			maxDistance[i] = MaxDistanceForNear;
			break;
		}
		maxDistance[i] = min(maxDistance[i], (DWORD)MaxDistanceForNear);
		if (minDistance[i] != 1 || maxDistance[i] != 1)
			bSimplePhrase = false;
	}

	//-- allocate local occurrences
	ClearAndReserveOccurrences(ItemsCount*m_Items[mini]->GetOccurrencesSize());

	if (false/*DEBUG*/ && bSimplePhrase) {
		//---- PHRASE-SIMPLE: optimized evaluation for "simple" phrases (only immediate successors, no skip-operators)
		size_t i,j;
		while ( iters[0].valid() ) {
			//-- check for hit
			for (i=1; i < ItemsCount; ++i) {
				CTokenNo nxt = iters[i-1].tmin()+1;
				iters[i].seek( nxt );
				if ( !iters[i].valid() || iters[i].tmin() != nxt ) break;
			}
			if (i==ItemsCount) {
				//-- found __exactly__ one complete sequence-match: save it by adding complete path represented by iters[]
				for (j=0; j < ItemsCount; ++j) {
					//resume[j] = iters[j];
					AddOccurrence(*m_Items[j], iters[j].cur);
					++iters[j];
				}
			}
			else if (!iters[i].valid()) {
				//-- no more items[i]: we can stop looking
				break;
			}
			else {
				//-- failed to find a match for iters[i]
				iters[0].seek( iters[i].tmin() - i );
			}
		}
	}
	else {
		//---- PHRASE-COMPLEX: hairy evaluation for "complex" phrases (non-trivial skip-operators)

#if 0 //-- PHRASE-COMPLEX: dispatch: new/seekall
		//fprintf(stderr, "PHRASE-COMPLEX: new/seekall\n");

		//-- allocate sub-occurrence buffers
		vector< vector<DWORD> > ItemOccs(ItemsCount);
		for (size_t i=0; i < ItemsCount; ++i)
			ItemOccs[i].reserve(MaxDistanceForNear);
		ItemOccs[0].resize(1);

		ProductIterator<DWORD> ItemOccIter(ItemsCount);

		size_t i,j;
		while ( iters[0].valid() ) {
			//-- check for hits
			for (i=1; i < ItemsCount; ++i) {
				iters[i].seekAll( iters[i-1].tmin()+minDistance[i-1], iters[i-1].tmin()+maxDistance[i-1], ItemOccs[i] );
				if (ItemOccs[i].empty()) break;
			}
			if (i==ItemsCount) {
				//-- found __at_least_one__ complete sequence-match: add __all__ complete matches
				ItemOccs[0][0] = iters[0].cur;
				for (ItemOccIter.assign(ItemOccs); ItemOccIter.valid(); ++ItemOccIter) {
					for (j=0; j < ItemsCount; ++j)
						AddOccurrence(*m_Items[j], ItemOccs[j][ItemOccIter.m_cur[j]]);
				}
				++iters[0];
			}
			else {
				//-- failed to find a match for iters[i] : backtrack
				for (j=i; j > 0; --j) {
					if (iters[j].valid()) {
						CTokenNo seekprev = iters[j].tmin() - min(iters[j].tmin(), maxDistance[j-1]);
						if (seekprev > iters[j-1].tmin()) iters[j-1].seek( seekprev );
					}
					else {
						iters[j-1].invalidate();
					}
				}
			}
		}

#elif 1
		//fprintf(stderr, "PHRASE-COMPLEX: new/seek-resume\n");

		// resume[] stores previous iteration value (resume positions) for iters[]
		vector<CQTokenOccurrenceIterator> resume(iters);

		// depth-first search  from iters[0]
		while ( iters[0].valid() ) {
			if (iters[0].cur > 0 && iters[0].tmin() == iters[0].tmax_prev()) continue; //-- ignore duplicates in iters[0]

			// i is the level of depth-first search
			size_t i = 1;
			while (i > 0) {
				//-- get token-id of the previous sequence-item
				CTokenNo tprev = iters[i-1].tmin();

				//-- advance iters[i] to first occurrence after iters[i-1]
				//for (iters[i]=resume[i]; iters[i].valid() && iters[i].tmin() <= tprev; ++iters[i]) ;
				resume[i].seek(tprev + minDistance[i-1]);
				iters[i] = resume[i];
				if (!iters[i].valid())
					goto seqdone;

				//-- attempt to find an iterator-position fulfilling the distance-constraints starting from iters[i]
				bool found=false;
				for ( ; iters[i].valid() && iters[i].tmin()-tprev <= maxDistance[i-1]; ++iters[i]) {
					if (iters[i].cur > 0 && iters[i].tmin()==iters[i].tmax_prev()) continue; //-- avoid duplicates in iters[i]

					//-- a suitable position has been found for iters[i]
					if ((i+1)==ItemsCount) {
						//-- found a complete sequence-match: save it by adding complete path represented by iters[]
						for (size_t j=0; j < ItemsCount; ++j)
							AddOccurrences(*m_Items[j], iters[j].cur, iters[j].cur+1);
					}
					else {
						//-- we've got a good match in iters[i]; continue by searching iters[i+1]
						found = true;
						break;
					}
				}

				if (found) {
					//-- found sub-query match in iters[i]; continue by trying to match iters[i+1]
					++i;
				} else {
					//-- no sub-query match iters[i] found: back up
					CTokenNo seekprev = resume[i].tmin() - min(resume[i].tmin(), maxDistance[i-1]);
					--i;
					if (seekprev > resume[i].tmin())
						resume[i].seek(seekprev);
					else
						++resume[i];
				}
			}
			// after this iteration iters[1]...iters[ItemsCount-1] are non-matches;
			// we are waiting  for the next value of iters[0]
			// resume[1] ... resume[ItemCount-1] were possibly updated 
			// resume[i] is a lower bound for possible continuations of resume[i-1],

			//-- update iters[0]
			iters[0] = resume[0];
			/*
			if (resume[0].cur > iters[0].cur)
				iters[0] = resume[0];
			else
				++iters[0];
			*/
		}
		
#else  //-- PHRASE-COMPLEX: dispatch: old
		//fprintf(stderr, "PHRASE-COMPLEX: old\n");

		// resume[] stores previous iteration value (resume positions) for iters[]
		vector<CQTokenOccurrenceIterator> resume(iters);

		// depth-first search  from iters[0]
		for ( ; iters[0].valid(); ++iters[0] ) {
			if (iters[0].cur > 0 && iters[0].tmin() == iters[0].tmax_prev()) continue; //-- ignore duplicates in iters[0]

			// i is the level of depth-first search
			size_t i = 1;
			while (i > 0) {
				//-- get token-id of the previous sequence-item
				CTokenNo tprev = iters[i-1].tmin();

				//-- advance iters[i] to first occurrence after iters[i-1]
				//for (iters[i]=resume[i]; iters[i].valid() && iters[i].tmin() <= tprev; ++iters[i]) ;
				resume[i].seek(tprev+1);
				iters[i] = resume[i];
				if (!iters[i].valid())
					goto seqdone;

				//-- attempt to find an iterator-position fulfilling the distance conditions starting from iters[i]
				bool found=false;
				for ( ; iters[i].valid(); ++iters[i]) {
					if (iters[i].cur > 0 && iters[i].tmin()==iters[i].tmax_prev()) continue; //-- avoid duplicates in iters[i]

					//-- check for distance-constraint violations
					DWORD CurDistance = iters[i].tmin() - tprev;
					if (CurDistance < minDistance[i-1])
						//-- minimum distance not yet reached: increment current iterator and keep searching
						continue;
					else if (CurDistance > maxDistance[i-1])
						//-- max distance exceeded
						break;
					else {
						//-- a suitable position has been found for iters[i]
						if ((i+1)==ItemsCount) {
							//-- found a complete sequence-match: save it by adding complete path represented by iters[]
							for (size_t j=0; j < ItemsCount; ++j)
								AddOccurrences(*m_Items[j], iters[j].cur, iters[j].cur+1);
						}
						else {
							//-- we've got a good match in iters[i]; continue by searching iters[i+1]
							found = true;
							break;
						}
					}
				}

				if (found) {
					//-- found sub-query match in iters[i]; continue by trying to match iters[i+1]
					++i;
				} else {
					//-- no sub-query match iters[i] found: back up
					--i;
					++resume[i];
				}
			}
			// after this iteration iters[1]...iters[ItemsCount-1] are non-matches;
			// we are waiting  for the next value of iters[0]
			// resume[1] ... resume[ItemCount-1] were possibly updated 
			// resume[i] is a lower bound for possible continuations of resume[i-1],
		}
#endif // PHRASE-COMPLEX: dispatch
	
	}
 seqdone:
	//fprintf(stderr, "CQSeq: added %zd total occurrences\n", m_Occurrences.size());

	// this procedure produces list of occurrences are stored by chunks, and sorted by the first item. 
	// The length of chunk is equal to the length of the  pattern,
	// Each chunk is a found occurrence of the pattern.
	m_ChunkLengths.resize(GetOccurrencesSize()/m_Items.size(), m_Items.size());
};

void CQuerySequenceNode::Evaluate(bool bSeparateHits)
{
	EvaluateWithoutHits();
	ConvertOccurrencesToHitsForPatterns(bSeparateHits);
};

//======================== CQueryNearNode =========================


CQueryNearNode::CQueryNearNode()
	: CQueryNode(false)
{
	m_pChild1 = NULL;
	m_pChild2 = NULL;
	m_pChild3 = NULL;
};

CQueryNearNode::~CQueryNearNode()
{
	if (m_pChild1) delete m_pChild1;
	if (m_pChild2) delete m_pChild2;
	if (m_pChild3) delete m_pChild3;
};

size_t CQueryNearNode::GetNodeFrequencyByNodeIndex(size_t NodeIndex) const
{
	size_t Result = 0;
	if (m_pChild1) Result += m_pChild1->GetNodeFrequencyByNodeIndex(NodeIndex);
	if (m_pChild2) Result += m_pChild2->GetNodeFrequencyByNodeIndex(NodeIndex);
	if (m_pChild3) Result += m_pChild3->GetNodeFrequencyByNodeIndex(NodeIndex);
	return Result;
}

bool CQueryNearNode::Create(const CConcHolder* pHolder, BYTE distance, CQueryNode* child1, CQueryNode* child2, CQueryNode* child3)
{
	if (distance > MaxDistanceForNear)
	  throw CExpc(errParseError, "distance #%d too large (max=%d) in near query", distance, MaxDistanceForNear);
	m_Distance = distance;

	if (!child1 || !child1->m_bAtomic)
		throw CExpc(errParseError, "child1 not atomic in near query");
	if (!child2 || !child2->m_bAtomic)
		throw CExpc(errParseError, "child2 not atomic in near query");
	if (child3 && !child3->m_bAtomic)
		throw CExpc(errParseError, "child3 not atomic in near query");

	m_pChild1 = child1;
	m_pChild2 = child2;
	m_pChild3 = child3;

	if (m_Source.empty()) {
		m_Source = string("NEAR(") + m_pChild1->m_Source + "," + m_pChild2->m_Source + ",";
		if (child3!=NULL) m_Source += m_pChild3->m_Source + ",";
		m_Source += Format("%d", m_Distance);
	}

	SetHolder(pHolder);
	return  true;
}

//--------------------------------------------------------------
void CQueryNearNode::FindOccurrences2()
{
	CTokenNo MaxDistance = m_Distance+1;
	CQOccurrenceIterator item1, item2;
	bool bind1=false, bind2=false; //-- whether item1 rsp. item2 is a bound iterator representing a universal wildcard (*)

	m_ChunkLengths.clear();

	//-- wildcard optimization (allowing at most 1 bound sub-query)
	if (m_pChild1->IsUniversalWildcard())
		bind1 = true;
	else if (m_pChild2->IsUniversalWildcard())
		bind2 = true;

	//-- sub-query evaluation (non-bound sub-queries)
	if (!bind1) {
		m_pChild1->EvaluateWithoutHits();
		item1.assign(m_pChild1);
	}
	if (!bind2) {
		m_pChild2->EvaluateWithoutHits();
		item2.assign(m_pChild2);
	}

	//-- sub-query pseudo-evaluation (bound sub-queries); local result-set allocation
	//   + also reserve local result-set m_Occurrences[] etc
	if (bind1) {
		item1.bind((CQueryTokenNode*)m_pChild1, item2, -MaxDistance, MaxDistance);
		ClearAndReserveOccurrences(item1.cnt);
	}
	else if (bind2) {
		item2.bind((CQueryTokenNode*)m_pChild2, item1, -MaxDistance, MaxDistance);
		ClearAndReserveOccurrences(item2.cnt);
	}
	else {
		//-- ensure that the sub-query with the smallest result-set is used for the outer search loop
		if (item2.cnt < item1.cnt)
			swap(item1, item2);
		ClearAndReserveOccurrences(item1.cnt*2);
	}

	//-- search guts
	for ( ; item1.valid() && item2.valid(); ++item1 ) {

		//-- advance item2 until (item1.tmin() <= item2.tmax()+MaxDistance)
		for ( ; item2.valid() && item1.tmin() > item2.tmax() + MaxDistance; ++item2 )
			;

		//-- find all item2 occurences s.t. (item1.tmax()+MaxDistance >= item2.tmin())
		CQOccurrenceIterator resume2(item2);
		for ( ; item2.valid() && item1.tmax()+MaxDistance >= item2.tmin(); ++item2 ) {
			if (item1==item2) continue; //-- near() sub-matches must be disjoint
			size_t size1 = item1.chunksize();
			size_t size2 = item2.chunksize();
			AddOccurrences2(*item1.node, item1.cur, item1.cur+size1,
					*item2.node, item2.cur, item2.cur+size2);
			m_ChunkLengths.push_back(size1+size2);
		}

		//-- update positions
		item2 = resume2;
	}
}

void CQueryNearNode::FindOccurrences3()
{
	CTokenNo MaxDistance = m_Distance+1;
	CQOccurrenceIterator item1, item2, item3;
	bool bind1=false, bind2=false, bind3=false; //-- whether itemX is a bound iterator representing a universal wildcard (*)

	m_ChunkLengths.clear();

	//-- wildcard optimization (allowing at most 2 bound sub-queries)
	if (m_pChild1->IsUniversalWildcard()) {
		bind1 = true;
		if (m_pChild2->IsUniversalWildcard())
			bind2 = true;
		else if (m_pChild3->IsUniversalWildcard())
			bind3 = true;
	}
	else {
		bind2 = m_pChild2->IsUniversalWildcard();
		bind3 = m_pChild3->IsUniversalWildcard();
	}

	//-- sub-query evaluation (non-bound sub-queries)
	if (!bind1) {
		m_pChild1->EvaluateWithoutHits();
		item1.assign(m_pChild1);
	}
	if (!bind2) {
		m_pChild2->EvaluateWithoutHits();
		item2.assign(m_pChild2);
	}
	if (!bind3) {
		m_pChild3->EvaluateWithoutHits();
		item3.assign(m_pChild3);
	}

	//-- sub-query pseudo-evaluation (bound sub-queries); local result-set allocation
	if (bind1 && bind2) {
		item1.bind((CQueryTokenNode*)m_pChild1, item3, -MaxDistance, MaxDistance);
		item2.bind((CQueryTokenNode*)m_pChild2, item3, -MaxDistance, MaxDistance);
		ClearAndReserveOccurrences(item1.cnt);
	}
	else if (bind1 && bind3) {
		item1.bind((CQueryTokenNode*)m_pChild1, item2, -MaxDistance, MaxDistance);
		item3.bind((CQueryTokenNode*)m_pChild3, item2, -MaxDistance, MaxDistance);
		ClearAndReserveOccurrences(item1.cnt);
	}
	else if (bind2 && bind3) {
		item2.bind((CQueryTokenNode*)m_pChild2, item1, -MaxDistance, MaxDistance);
		item3.bind((CQueryTokenNode*)m_pChild3, item1, -MaxDistance, MaxDistance);
		ClearAndReserveOccurrences(item2.cnt);
	}
	else if (bind1) {
		item1.bind((CQueryTokenNode*)m_pChild1, (item2.cnt <= item3.cnt ? item2 : item3), -MaxDistance, MaxDistance);
		ClearAndReserveOccurrences(item1.cnt);
	}
	else if (bind2) {
		item2.bind((CQueryTokenNode*)m_pChild2, (item1.cnt <= item3.cnt ? item1 : item3), -MaxDistance, MaxDistance);
		ClearAndReserveOccurrences(item2.cnt);
	}
	else if (bind3) {
		item3.bind((CQueryTokenNode*)m_pChild3, (item1.cnt <= item2.cnt ? item1 : item2), -MaxDistance, MaxDistance);
		ClearAndReserveOccurrences(item3.cnt);
	}
	else {
		ClearAndReserveOccurrences(min(min(item1.cnt,item2.cnt),item3.cnt)*3);
	}

	//-- ensure that the sub-query with the smallest result-set is used for the outer search loop
	//   + bound queries are ok to use here, since they set their 'cnt' property on bind()
	if (item2.cnt < item1.cnt) {
		swap(item1, item2);
		swap(bind1, bind2);
	}
	if (item3.cnt < item1.cnt) {
		swap(item1, item3);
		swap(bind1, bind3);
	}
	if (item3.cnt < item2.cnt) {
		swap(item2, item3);
		swap(bind2, bind3);
	}

	//-- search guts
	for ( ; item1.valid() && item2.valid() && item3.valid(); ++item1 ) {

		//-- advance item2 until (item1.tmin() <= item2.tmax()+MaxDistance)
		for ( ; item2.valid() && item1.tmin() > item2.tmax() + MaxDistance; ++item2 ) ;

		//-- find all item2 occurences s.t. (item1.tmax()+MaxDistance >= item2.tmin())
		CQOccurrenceIterator resume2(item2);
		for ( ; item2.valid() && item3.valid() && item1.tmax()+MaxDistance >= item2.tmin(); ++item2 ) {
			if (item1==item2) continue; //-- near() sub-matches must be disjoint
			CTokenNo max_begin = max(item1.tmin(), item2.tmin());
			CTokenNo min_end   = min(item1.tmax(), item2.tmax());

			//-- advance item3 until (max_begin <= item3.tmax()+MaxDistance)
			for ( ; item3.valid() && max_begin > item3.tmax() + MaxDistance; ++item3 ) ;

			//-- find all item3 occurences s.t. (min_end+MaxDistance >= item3.tmin())
			CQOccurrenceIterator resume3(item3);
			for ( ; item3.valid() && min_end+MaxDistance >= item3.tmin(); ++item3 ) {
				if (item1==item3 || item2==item3) continue; //-- near() sub-matches must be disjoint
				size_t size1 = item1.chunksize();
				size_t size2 = item2.chunksize();
				size_t size3 = item3.chunksize();
				AddOccurrences3(*item1.node, item1.cur, item1.cur+size1,
						*item2.node, item2.cur, item2.cur+size2,
						*item3.node, item3.cur, item3.cur+size3);
				m_ChunkLengths.push_back(size1+size2+size3);
			}

			//-- update item3 position
			item3 = resume3;
		}

		//-- update item2 position
		item2 = resume2;
	}
}

void CQueryNearNode::Evaluate(bool bSeparateHits)
{
	if (m_pChild3)
		FindOccurrences3();
	else
		FindOccurrences2();
	ConvertOccurrencesToHitsForPatterns(bSeparateHits);
};

//======================== CQueryWithNode =========================

CQueryWithNode::CQueryWithNode()
{
	m_bAtomic = true;
	m_MatchId = 0;
};

bool CQueryWithNode::Create(const CConcHolder*	pHolder, CQueryNode* child1, CQueryNode* child2, BYTE matchId)
{
	CQueryBinaryOperationNode::Create(pHolder, child1, child2, string(" with ") );
	m_MatchId = matchId;
	return true;
};


/* with times (zeit01,+opt)

OLD
 @Haus with $l=@Haus	(n=11121)	355.954
 @Haus with $p=@NN	(n=11116)	  9.156
 @das  with $p=@ART	(n=393473)	 10.612

NEW/set-intersection
 @Haus with $l=@Haus	(n=11121)	363.168		+ 2%
 @Haus with $p=@NN	(n=11116)	  9.091		- 1%
 @das  with $p=@ART	(n=393473)	 11.918		+11%

NEW/-seek
 @Haus with $l=@Haus	(n=11121)	364.219
 @Haus with $p=@NN	(n=11116)	  8.046
 @das  with $p=@ART	(n=393473)	 10.812

NEW/+seek[LB_MIN=undef]
 @Haus with $l=@Haus	(n=11121)	359.041
 @Haus with $p=@NN	(n=11116)	  9.765
 @das  with $p=@ART	(n=393473)	 11.652

NEW/+seek[LB_MIN=0]
 @Haus with $l=@Haus	(n=11121)	343.584
 @Haus with $p=@NN	(n=11116)	 10.266
 @das  with $p=@ART	(n=393473)	  9.935

NEW/+seek[LB_MIN=1024]
 @Haus with $l=@Haus	(n=11121)	341.618
 @Haus with $p=@NN	(n=11116)	 10.282
 @das  with $p=@ART	(n=393473)	 11.345

NEW/+seek[LB_COEF=1]
 @Haus with $l=@Haus	(n=11121)	342.050		- 4%
 @Haus with $p=@NN	(n=11116)	 10.203		+10%
 @das  with $p=@ART	(n=393473)	 10.432		- 2%

NEW/+seek[LB_COEF=2]
 @Haus with $l=@Haus	(n=11121)	358.173		+ 1%
 @Haus with $p=@NN	(n=11116)	 10.244		+11%
 @das  with $p=@ART	(n=393473)	 11.007		+ 4%

NEW/+seek[LB_COEF=4]
 @Haus with $l=@Haus	(n=11121)	354.836		- 0%
 @Haus with $p=@NN	(n=11116)	 10.277		+11%
 @das  with $p=@ART	(n=393473)	 11.147		+ 5%

----> WINNER: NEW/+seek+reorder[LB_COEF=4]
 @Haus with $l=@Haus	(n=11121)	385.201		+ 8%
 @Haus with $p=@NN	(n=11116)	 10.393		+12%
 @das  with $p=@ART	(n=393473)	 12.939		+18%

NEW/+seek[LB_COEF=8]
 @Haus with $l=@Haus	(n=11121)	353.008		- 1%
 @Haus with $p=@NN	(n=11116)	 10.278		+11%
 @das  with $p=@ART	(n=393473)	 11.082		+ 4%

...
 @Haus with $l=@Haus	(n=11121)	0
 @Haus with $p=@NN	(n=11116)	0
 @das  with $p=@ART	(n=393473)	0

*/

void CQueryWithNode::EvaluateWithoutHits()
{
	CQueryTokenNode *child1 = (CQueryTokenNode*)m_pChild1;
	CQueryTokenNode *child2 = (CQueryTokenNode*)m_pChild2;

	//-- wildcard optimization
	if (child1->IsUniversalWildcard()) {
		child2->EvaluateWithoutHits();
		SwapOccurrences(*m_pChild2, true);
#if 0 /* Thu, 02 Jun 2016 13:17:08 +0200: this looks pretty useless */
		if (m_bUseNodeIndices)
			m_OccurrenceNodeIndices.assign(m_OccurrenceNodeIndices.size(), child1->m_NodeIndex);
#endif
		if (m_bUseMatchIds && m_MatchId)
			m_OccurrenceMatchIds.assign(m_OccurrenceMatchIds.size(), m_MatchId);
		return;
	}
	else if (child2->IsUniversalWildcard()) {
		child1->EvaluateWithoutHits();
		SwapOccurrences(*m_pChild1, true);
		if (m_bUseMatchIds && m_MatchId)
			m_OccurrenceMatchIds.assign(m_OccurrenceMatchIds.size(), m_MatchId);
		return;
	}

	//-- evaluation guts
	child1->EvaluateWithoutHits();
	child2->EvaluateWithoutHits();

#if 0 /* DEBUG: use set-intersection -- new implementation is actually faster without this clause! */
	if (!m_bUseNodeIndices && !m_bUseMatchIds) {
		//-- no node-indices or match-ids : just append to m_Occurrences[] and sort appended data
		//printf("WITH:intersect\n");
		m_Occurrences.resize( min(child1->GetOccurrencesSize(), child2->GetOccurrencesSize()) );
		vector<CTokenNo>::iterator it = set_intersection(child1->m_Occurrences.begin(), child1->m_Occurrences.end(),
								 child2->m_Occurrences.begin(), child2->m_Occurrences.end(),
								 m_Occurrences.begin());
		m_Occurrences.resize(it - m_Occurrences.begin());
	}
	else
#endif
	{
		//-- node-indices and/or match-ids in use: manual intersection via linear scan needed to preserve them
		ClearAndReserveOccurrences( min(child1->GetOccurrencesSize(), child2->GetOccurrencesSize()) );
#if 1
		//-- WITH:new[+seek]
		//printf("WITH:new[+seek]\n");
		CQTokenOccurrenceIterator iter1(child1), iter2(child2);
		while ( iter1.valid() && iter2.valid() ) {
			if (iter1.tmin() < iter2.tmin()) {
				iter1.seek(iter2.tmin());
			}
			else if (iter2.tmin() > iter1.tmin()) {
				iter2.seek(iter1.tmin());
			}
			else /*if (iter1.tmin() == iter2.tmin())*/ {
				//-- occ1 == occ2: add occ1
				m_Occurrences.push_back(child1->m_Occurrences[iter1.cur]);
				if (m_bUseNodeIndices)
					m_OccurrenceNodeIndices.push_back(child1->m_OccurrenceNodeIndices[iter1.cur]);
				if (m_bUseMatchIds)
					m_OccurrenceMatchIds.push_back(child2->m_OccurrenceMatchIds[iter2.cur]!=DefaultMatchId
								       ? child2->m_OccurrenceMatchIds[iter2.cur]
								       : child1->m_OccurrenceMatchIds[iter1.cur]);
				++iter1;
				++iter2;
			}
		}
		
#else
		//-- WITH:old
		//printf("WITH:old\n");
		size_t i1,i2;
		for (i1=0, i2=0; i1 < child1->GetOccurrencesSize() && i2 < child2->GetOccurrencesSize(); ) {
			if (child1->m_Occurrences[i1] == child2->m_Occurrences[i2]) {
				//-- occ1 == occ2: add occ1
				m_Occurrences.push_back(child1->m_Occurrences[i1]);
				if (m_bUseNodeIndices)
					m_OccurrenceNodeIndices.push_back(child1->m_OccurrenceNodeIndices[i1]);
				if (m_bUseMatchIds)
					m_OccurrenceMatchIds.push_back(child2->m_OccurrenceMatchIds[i2]!=DefaultMatchId
								       ? child2->m_OccurrenceMatchIds[i2]
								       : child1->m_OccurrenceMatchIds[i1]);
				++i1;
				++i2;
			}
			else if (child1->m_Occurrences[i1] < child2->m_Occurrences[i2])  {
				++i1;
			}
			else if (child1->m_Occurrences[i1] > child2->m_Occurrences[i2])  {
				++i2;
			}
		}
#endif
		//-- clobber match-ids
		if (m_bUseMatchIds && m_MatchId)
			m_OccurrenceMatchIds.assign(m_OccurrenceMatchIds.size(), m_MatchId);
	}

	m_ChunkLengths.resize(GetOccurrencesSize(), 1);
};

void CQueryWithNode::Evaluate(bool bSeparateHits)
{
	EvaluateWithoutHits();
	ConvertOccurrencesToHits(bSeparateHits);
};

//======================== CQueryWithoutNode =========================

bool CQueryWithoutNode::Create(const CConcHolder* pHolder, CQueryNode* child1, CQueryNode* child2, BYTE matchId)
{
	CQueryBinaryOperationNode::Create(pHolder, child1, child2, string(" without ") );
	m_MatchId = matchId;
	return true;
};


/* WITHOUT query-times (zeit01,+opt; queries/sec)

OLD
 %Haus != @Haus		(n=15740)	288.018
 @das  != $p=@ART	(n=161223)	 13.430
 @Liebe != $p=@NN	(n=174)		  9.552

new/set-intersection
 %Haus != @Haus		(n=15740)	301.187		+ 4%
 @das  != $p=@ART	(n=161223)	 14.363		- 1%
 @Liebe != $p=@NN	(n=174)		  9.953		+ 4%

new/+seek[LB_MIN=1024]
 %Haus != @Haus		(n=15740)	300.161		+ 4%
 @das  != $p=@ART	(n=161223)	 13.239		- 1%
 @Liebe != $p=@NN	(n=174)		 11.722		+19%

new/+seek[COEF=4]
 %Haus != @Haus		(n=15740)	297.584		+ 3%
 @das  != $p=@ART	(n=161223)	 14.440		+ 7%
 @Liebe != $p=@NN	(n=174)		 11.830		+19%

...
 %Haus != @Haus		(n=15740)	0
 @das  != $p=@ART	(n=161223)	0
 @Liebe != $p=@NN	(n=174)		0

*/

void CQueryWithoutNode::EvaluateWithoutHits()
{
	CQueryTokenNode* child1 = (CQueryTokenNode*)m_pChild1;
	CQueryTokenNode* child2 = (CQueryTokenNode*)m_pChild2;

	child1->EvaluateWithoutHits();
	child2->EvaluateWithoutHits();

#if 0 /* DEBUG: use set-intersection -- we're actually faster without it now */
	if (!m_bUseNodeIndices && !m_bUseMatchIds) {
		//-- no node-indices or match-ids : simple set-operation
		m_Occurrences.resize( child1->GetOccurrencesSize() );
		vector<CTokenNo>::iterator it = set_difference(child1->m_Occurrences.begin(), child1->m_Occurrences.end(),
							       child2->m_Occurrences.begin(), child2->m_Occurrences.end(),
							       m_Occurrences.begin());
		m_Occurrences.resize(it - m_Occurrences.begin());
	}
	else
#endif
        {
		ClearAndReserveOccurrences( child1->GetOccurrencesSize() );
#if 1
		//-- WITHOUT:new[+seek]
		CQTokenOccurrenceIterator iter1(child1), iter2(child2);
		while ( iter1.valid() && iter2.valid() ) {
			if (iter1.tmin() < iter2.tmin()) {
				//-- occ1 < occ2: add occ1
#if 0
				//-- batch add & incr
				DWORD start = iter1.cur;
				iter1.seek(iter2.tmin());
				AddOccurrences(*child1, start, (iter1.valid() ? iter1.cur : iter1.cnt));
#else
				//-- single add
				m_Occurrences.push_back(child1->m_Occurrences[iter1.cur]);
				if (m_bUseNodeIndices)
					m_OccurrenceNodeIndices.push_back(child1->m_OccurrenceNodeIndices[iter1.cur]);
				if (m_bUseMatchIds)
					m_OccurrenceMatchIds.push_back(child1->m_OccurrenceMatchIds[iter1.cur]);
				++iter1;
#endif
			}
			else if (iter1.tmin() == iter2.tmin()) {
				//-- occ1 == occ2: skip both
				++iter1;
				++iter2;
			}
			else /*if (iter1.tmin() > iter2.tmin())*/ {
				//-- occ1 > occ2 : skip occ2
				iter2.seek( iter1.tmin() );
			}
		}

		//-- append final occurrences
		if (iter1.valid())
			AddOccurrences(*child1, iter1.cur, iter1.cnt);

		//-- clobber match-ids
		if (m_bUseMatchIds && m_MatchId)
			m_OccurrenceMatchIds.assign(m_OccurrenceMatchIds.size(), m_MatchId);

#else
		//-- WITHOUT:old
		//-- node-indices and/or match-ids in use: linear scan needed to preserve them
		size_t i1,i2;
		for (i1=0, i2=0; i1 < child1->GetOccurrencesSize() && i2 < child2->GetOccurrencesSize(); ) {
			if (child1->m_Occurrences[i1] < child2->m_Occurrences[i2]) {
				//-- occ1 < occ2: add occ1
				m_Occurrences.push_back(child1->m_Occurrences[i1]);
				if (m_bUseNodeIndices)
					m_OccurrenceNodeIndices.push_back(child1->m_OccurrenceNodeIndices[i1]);
				if (m_bUseMatchIds)
					m_OccurrenceMatchIds.push_back(child1->m_OccurrenceMatchIds[i1]);
				++i1;
			}
			else if (child1->m_Occurrences[i1] == child2->m_Occurrences[i2]) {
				//-- occ1 == occ2: skip both
				++i1;
				++i2;
			}
			else  {
				//-- occ1 > occ2: skip occ2
				++i2;
			}
		}

		//-- append final occurrences
		if (i1 < child1->GetOccurrencesSize())
			AddOccurrences(*child1, i1, child1->GetOccurrencesSize());

		//-- clobber match-ids
		if (m_bUseMatchIds && m_MatchId)
			m_OccurrenceMatchIds.assign(m_OccurrenceMatchIds.size(), m_MatchId);
#endif
	}

	m_ChunkLengths.resize(GetOccurrencesSize(), 1);
};

//======================== CQueryWithorNode =========================

bool CQueryWithorNode::Create(const CConcHolder* pHolder, CQueryNode* child1, CQueryNode* child2, BYTE matchId)
{
	CQueryBinaryOperationNode::Create(pHolder, child1, child2, string(" withor ") );
	m_MatchId = matchId;
	return true;
};


void CQueryWithorNode::EvaluateWithoutHits()
{
	CQueryTokenNode *child1 = (CQueryTokenNode*)m_pChild1;
	CQueryTokenNode *child2 = (CQueryTokenNode*)m_pChild2;
	child1->EvaluateWithoutHits();
	child2->EvaluateWithoutHits();

#if 1 /* DEBUG: use set-intersection */
	if (!m_bUseNodeIndices && !m_bUseMatchIds) {
		//-- no node-indices or match-ids : just append to m_Occurrences[] and sort appended data
		m_Occurrences.resize( child1->GetOccurrencesSize() + child2->GetOccurrencesSize() );
		vector<CTokenNo>::iterator it = set_union(child1->m_Occurrences.begin(), child1->m_Occurrences.end(),
							  child2->m_Occurrences.begin(), child2->m_Occurrences.end(),
							  m_Occurrences.begin());
		m_Occurrences.resize(it - m_Occurrences.begin());
	}
	else
#endif
	{
		ClearAndReserveOccurrences( child1->GetOccurrencesSize() + child2->GetOccurrencesSize() );
#if 0
		//-- WITHOR:new
		CQTokenOccurrenceIterator iter1(child1), iter2(child2);
		while ( iter1.valid() && iter2.valid() ) {
			if (iter1.tmin() <= iter2.tmin()) {
				//-- occ1 <= occ2: add occ1
				m_Occurrences.push_back(child1->m_Occurrences[iter1.cur]);
				if (m_bUseNodeIndices)
					m_OccurrenceNodeIndices.push_back(child1->m_OccurrenceNodeIndices[iter1.cur]);
				if (m_bUseMatchIds)
					m_OccurrenceMatchIds.push_back(child1->m_OccurrenceMatchIds[iter1.cur]);
				++iter1;
				if (iter1.tmin() == iter2.tmin()) ++iter2;
			}
			else {
				//-- occ1 > occ2: add occ2
				m_Occurrences.push_back(child2->m_Occurrences[iter2.cur]);
				if (m_bUseNodeIndices)
					m_OccurrenceNodeIndices.push_back(child2->m_OccurrenceNodeIndices[iter2.cur]);
				if (m_bUseMatchIds)
					m_OccurrenceMatchIds.push_back(child2->m_OccurrenceMatchIds[iter2.cur]);
				++iter2;
			}

		}

		//-- append final occurrences
		if (iter1.valid()) AddOccurrences(*child1, iter1.cur, iter1.cnt);
		if (iter2.valid()) AddOccurrences(*child2, iter2.cur, iter2.cnt);

#else
		//-- WITHOR:old
		//-- node-indices and/or match-ids in use: manual union via linear scan needed to preserve them
		size_t i1,i2;
		for (i1=0, i2=0; i1 < child1->GetOccurrencesSize() && i2 < child2->GetOccurrencesSize(); ) {
			if (child1->m_Occurrences[i1] <= child2->m_Occurrences[i2]) {
				//-- occ1 <= occ2: add occ1
				m_Occurrences.push_back(child1->m_Occurrences[i1]);
				if (m_bUseNodeIndices)
					m_OccurrenceNodeIndices.push_back(child1->m_OccurrenceNodeIndices[i1]);
				if (m_bUseMatchIds)
					m_OccurrenceMatchIds.push_back(child1->m_OccurrenceMatchIds[i1]);
				if (child1->m_Occurrences[i1] == child2->m_Occurrences[i2]) ++i2;
				++i1;
			}
			else {
				//-- occ1 > occ2: add occ2
				m_Occurrences.push_back(child2->m_Occurrences[i2]);
				if (m_bUseNodeIndices)
					m_OccurrenceNodeIndices.push_back(child2->m_OccurrenceNodeIndices[i2]);
				if (m_bUseMatchIds)
					m_OccurrenceMatchIds.push_back(child2->m_OccurrenceMatchIds[i2]);
				++i2;
			}
		}

		//-- append final occurrences
		if (i1 < child1->GetOccurrencesSize())
			AddOccurrences(*child1, i1, child1->GetOccurrencesSize());
		if (i2 < child2->GetOccurrencesSize())
			AddOccurrences(*child2, i2, child2->GetOccurrencesSize());
#endif /* WITHOR:old */
		//-- clobber match-ids
		if (m_bUseMatchIds && m_MatchId)
			m_OccurrenceMatchIds.assign(m_OccurrenceMatchIds.size(), m_MatchId);
	}

	m_ChunkLengths.resize(GetOccurrencesSize(), 1);
};


//======================== CQOccurrenceIterator =========================

//--------------------------------------------------------------
void CQOccurrenceIterator::bind(CQueryTokenNode *node_, const CQOccurrenceIterator &src, int minOffset, int maxOffset)
{
	assert(node_ && node_->m_bAny);
	operator=(node_);

	cnt = (1+maxOffset-minOffset) * src.cnt;
	if (minOffset<=0 && maxOffset>=0) cnt -= src.cnt; //-- avoid dups: don't count zero-offsets
	node->ClearAndReserveOccurrences(cnt);

	CTokenNo last_tok = (CTokenNo)-1;
	for (vector<CTokenNo>::const_iterator occi=src.node->m_Occurrences.begin(); occi!=src.node->m_Occurrences.end(); ++occi) {
		for (int off=minOffset; off<=maxOffset; ++off) {
			CTokenNo tok = *occi + off;
			if (off==0 || (last_tok != (CTokenNo)-1 && last_tok >= tok)) continue; //-- avoid overlap
			node->m_Occurrences.push_back(tok);
			last_tok = tok;
		}
	}
	cnt = node->m_Occurrences.size();
	node->m_ChunkLengths.resize(cnt,1);
	if (node->m_bUseNodeIndices) {
		node->m_OccurrenceNodeIndices.resize(cnt,node_->m_NodeIndex);
	}
	if (node->m_bUseMatchIds) {
		node->m_OccurrenceMatchIds.resize(cnt,node_->m_MatchId);
	}
}

//--------------------------------------------------------------
bool CQOccurrenceIterator::operator==(const CQOccurrenceIterator &b) const
{
	CTokenNo i, len=chunksize();
	if (len != b.chunksize()) return false;
	for (i=0; i<len; ++i) {
		if (node->m_Occurrences[cur+i] != b.node->m_Occurrences[b.cur+i])
			return false;
	}
	return true;
};

//======================== CQTokenOccurrenceIterator =========================

//--------------------------------------------------------------
void CQTokenOccurrenceIterator::bind(CQueryTokenNode *node_, const CQTokenOccurrenceIterator &src, int minOffset, int maxOffset)
{
	assert(node_ && node_->m_bAny);
	operator=(node_);

	cnt = (1+maxOffset-minOffset) * src.cnt;
	if (minOffset<=0 && maxOffset>=0) cnt -= src.cnt; //-- avoid dups: don't count zero-offsets
	node->ClearAndReserveOccurrences(cnt);

	CTokenNo last_tok = (CTokenNo)-1;
	for (vector<CTokenNo>::const_iterator occi=src.node->m_Occurrences.begin(); occi!=src.node->m_Occurrences.end(); ++occi) {
		for (int off=minOffset; off<=maxOffset; ++off) {
			CTokenNo tok = *occi + off;
			if (off==0 || (last_tok != (CTokenNo)-1 && last_tok >= tok)) continue; //-- avoid overlap
			node->m_Occurrences.push_back(tok);
			last_tok = tok;
		}
	}
	cnt = node->m_Occurrences.size();
	//node->m_ChunkLengths.resize(cnt,1);
	if (node->m_bUseNodeIndices) {
		node->m_OccurrenceNodeIndices.resize(cnt,node_->m_NodeIndex);
	}
	if (node->m_bUseMatchIds) {
		node->m_OccurrenceMatchIds.resize(cnt,node_->m_MatchId);
	}
}

//--------------------------------------------------------------
void CQTokenOccurrenceIterator::seekAll(const CTokenNo TokMin, const CTokenNo TokMax, vector<DWORD>& occs)
{
	seek(TokMin);
	occs.clear();
	for (DWORD occ=cur; valid() && tocc(occ) <= TokMax; ++occ)
		occs.push_back(occ);
}
