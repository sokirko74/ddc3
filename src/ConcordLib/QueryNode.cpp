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
//-*- MOde: C++; c-basic-offset: 8; -*-
// QNode.cpp: implementation of the CQNode class.
//
//////////////////////////////////////////////////////////////////////

#include "StdConc.h"
#include "QueryNode.h"
#include "../common/DwdsThesaurus.h"
#include "../common/util_classes.h"
#include "../common/utilit.h"
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
	ClearVector(m_OccurrenceTokenIdxs);
};

size_t CQueryNode::GetNodeFrequenceByNodeIndex(size_t NodeIndex) const
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

void	CQueryNode::Evaluate() 
{
	throw  CExpc (errParseError, "not implemented!");
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
	m_Occurrences.insert(m_Occurrences.end(), FromNode.m_Occurrences.begin() + start,  FromNode.m_Occurrences.begin() + end);

	if (m_bUseNodeIndices)
		m_OccurrenceNodeIndices.insert(m_OccurrenceNodeIndices.end(), FromNode.m_OccurrenceNodeIndices.begin() + start,  FromNode.m_OccurrenceNodeIndices.begin() + end);

    if (m_bUseTokenIdxs)
        m_OccurrenceTokenIdxs.insert(m_OccurrenceTokenIdxs.end(), FromNode.m_OccurrenceTokenIdxs.begin() + start,  FromNode.m_OccurrenceTokenIdxs.begin() + end);
        
		
}

void	CQueryNode::ClearAndReserveOccurrences(int size)
{
	m_Occurrences.clear();
	m_Occurrences.reserve(size);

	m_OccurrenceNodeIndices.clear();
	if (m_bUseNodeIndices)
		m_OccurrenceNodeIndices.reserve(size);
    
	    
	m_OccurrenceTokenIdxs.clear();
	if (m_bUseTokenIdxs)
		m_OccurrenceTokenIdxs.reserve(size);
}

void	CQueryNode::SwapOccurrences(CQueryNode& Node)
{
	Node.m_Occurrences.swap(m_Occurrences);
	Node.m_OccurrenceNodeIndices.swap(m_OccurrenceNodeIndices);
	Node.m_OccurrenceTokenIdxs.swap(m_OccurrenceTokenIdxs);
}

void CQueryNode::SetHolder(const CConcHolder*	pHolder)
{
	m_pHolder = pHolder;
	m_bUseNodeIndices = m_pHolder->HasRankOrderOperator();
	m_bUseTokenIdxs = (m_pHolder->GetBigramsToOrder()  != bdDontUseBigrams);
}

void CQueryNode::ConvertOccurrencesToHits (bool bUniqueHits)
{
	const vector<CTokenNo>& Breaks = m_pHolder->GetBreaks();
	int TextAreasCount = m_pHolder->m_pIndexator->m_Bibl.GetTextAreasCount();
	int TextAreaNo = m_pHolder->GetTextArea();
	bool bTextAreaNo =  TextAreaNo != UnknownTextAreaNo;
	m_Hits.clear();
	m_Hits.reserve(GetOccurrencesSize());

	int cnt = GetOccurrencesSize();

	bool bLongSequence = GetOccurrencesSize()*5 > Breaks.size() ;
	vector<CTokenNo>::const_iterator break_it = Breaks.begin();

    CQueryNode NewNode (m_bUseNodeIndices, m_bUseTokenIdxs);
	if (bTextAreaNo)
		NewNode.ClearAndReserveOccurrences(GetOccurrencesSize());


	for (int i = 0;  i < cnt; i++)
	{
		CTokenNo Occurrence = m_Occurrences[i];

		if (!bLongSequence)
		{
			break_it = lower_bound (break_it, Breaks.end(), Occurrence);
			assert (break_it != Breaks.end());
			if (*break_it == m_Occurrences[i])
				break_it++;
		}
		else
		{
			// optimization for the very long sequence of m_Occurrences, lower_bound is too slow
			while(m_Occurrences[i] >= *break_it) break_it++;
		};

		
		DWORD BreakNo = break_it - Breaks.begin();
		if (bTextAreaNo)
			if ( BreakNo%TextAreasCount != TextAreaNo ) // if it is the right text area
				continue;
			else
				NewNode.AddOccurrences(*this, i, i+1);
				


		if (	m_Hits.empty() 
			|| ( m_Hits.back().m_BreakNo != BreakNo)
			|| !bUniqueHits
		   )
   		{
			CHit H(BreakNo);
			H.m_BreakNo = BreakNo;
			H.m_HighlightOccurrenceEnd = i+1;
			m_Hits.push_back(H);
		}
		else
			m_Hits.back().m_HighlightOccurrenceEnd = i+1;

	};

	if (bTextAreaNo)
		SwapOccurrences(NewNode);
		
};




void CQueryNode::ConvertOccurrencesToHitsForPatterns (bool bUniqueHits)	
{
	const vector<CTokenNo>& Breaks = m_pHolder->GetBreaks();
	m_Hits.clear();
	int TextAreasCount = m_pHolder->m_pIndexator->m_Bibl.GetTextAreasCount();
	int TextAreaNo = m_pHolder->GetTextArea();
	bool bTextAreaNo =  TextAreaNo != UnknownTextAreaNo;

	m_Hits.reserve(m_ChunkLengths.size());

	int cnt = GetOccurrencesSize();

	CQueryNode NewNode(m_bUseNodeIndices, m_bUseTokenIdxs);
	NewNode.ClearAndReserveOccurrences(cnt);
	NewNode.m_ChunkLengths.reserve(m_ChunkLengths.size());
	size_t InputStarter = 0;
	size_t NewOccurrencesCount = 0;

	vector<CTokenNo>::const_iterator break_it = Breaks.begin();
	bool bLongSequence = m_ChunkLengths.size()*5 > Breaks.size() ;
	
	size_t ChunkNo = 0;
	int i = 0;
	for (;  i < cnt; i += m_ChunkLengths[ChunkNo], ChunkNo++)
	{
		size_t ItemsCount = m_ChunkLengths[ChunkNo];

		if (!bLongSequence)
		{
			break_it = lower_bound (break_it, Breaks.end(), m_Occurrences[i]);
			assert (break_it != Breaks.end());
			if (*break_it == m_Occurrences[i]) 
				break_it++; // then Break is the first position of the next break
		}
		else
		{
			while(m_Occurrences[i] >= *break_it) break_it++;
		}

		if (m_Occurrences[i + ItemsCount - 1] >= *break_it )
		{
			if ( i > InputStarter)
				NewNode.AddOccurrences(*this, InputStarter,  i);
			InputStarter = i + ItemsCount;
			 //this period of m_Occurrences should be ignored since 
			 // it belongs two or more breaks simultaneously
			continue;
		};

		DWORD BreakNo = break_it - Breaks.begin();
		if (bTextAreaNo)
			if ( BreakNo%TextAreasCount != TextAreaNo )
			{
				if ( i > InputStarter)
					NewNode.AddOccurrences(*this, InputStarter,  i);
				InputStarter = i + ItemsCount;

				continue;
			}
		
		NewNode.m_ChunkLengths.push_back(ItemsCount);
		NewOccurrencesCount += ItemsCount;
		

		if (	m_Hits.empty() 
			|| ( m_Hits.back().m_BreakNo != BreakNo)
			|| !bUniqueHits
		   )
   		{
			CHit H(BreakNo);
			H.m_BreakNo = BreakNo;
			H.m_HighlightOccurrenceEnd = NewOccurrencesCount;
			m_Hits.push_back(H);
		}
		else
		{
			m_Hits.back().m_HighlightOccurrenceEnd += ItemsCount;
			assert (m_Hits.back().m_HighlightOccurrenceEnd == NewOccurrencesCount); 
		};
		
	};
	if ( i > InputStarter)
		NewNode.AddOccurrences(*this, InputStarter,  i);

	SwapOccurrences(NewNode);
	NewNode.m_ChunkLengths.swap(m_ChunkLengths);
};




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

size_t CQueryBinaryOperationNode::GetNodeFrequenceByNodeIndex(size_t NodeIndex) const
{
	size_t Result = 0;
	if (m_pChild1) Result += m_pChild1->GetNodeFrequenceByNodeIndex(NodeIndex);
	if (m_pChild2) Result += m_pChild2->GetNodeFrequenceByNodeIndex(NodeIndex);
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

void CQueryBinaryOperationNode::hits_and_positions_union() 
{	
	vector<CHit>::const_iterator _First1 = m_pChild1->m_Hits.begin();
	vector<CHit>::const_iterator _Last1 = m_pChild1->m_Hits.end();
	vector<CHit>::const_iterator _First2 = m_pChild2->m_Hits.begin();
	vector<CHit>::const_iterator _Last2 = m_pChild2->m_Hits.end();
	m_Hits.clear();
	m_Hits.reserve(m_pChild1->m_Hits.size() + m_pChild2->m_Hits.size());
	ClearAndReserveOccurrences(m_pChild1->GetOccurrencesSize() + m_pChild2->GetOccurrencesSize());
	

	size_t  prev_end1 = 0;
	size_t  prev_end2 = 0;
	for (; _First1 != _Last1 && _First2 != _Last2; )
		if (_First1->m_BreakNo < _First2->m_BreakNo)
		{
			
			AddOccurrences(*m_pChild1, prev_end1, _First1->m_HighlightOccurrenceEnd);
			prev_end1 = _First1->m_HighlightOccurrenceEnd;

			{
				CHit  H(_First1->m_BreakNo);
				H.m_HighlightOccurrenceEnd = GetOccurrencesSize();
				m_Hits.push_back(H);
			}
			_First1++;
		}
		else 
		if (_First2->m_BreakNo < _First1->m_BreakNo)
		{
			AddOccurrences (*m_pChild2, prev_end2,  _First2->m_HighlightOccurrenceEnd);
			prev_end2 = _First2->m_HighlightOccurrenceEnd;
			{
				CHit  H(_First2->m_BreakNo);
				H.m_HighlightOccurrenceEnd = GetOccurrencesSize();
				m_Hits.push_back(H);
			}
			_First2++;
		}
		else
		{
			{	// inserting highlight occurrences from the first and the second child
				AddOccurrences(*m_pChild1, prev_end1, _First1->m_HighlightOccurrenceEnd);
				AddOccurrences(*m_pChild2, prev_end2, _First2->m_HighlightOccurrenceEnd);
				{
					CHit  H(_First1->m_BreakNo);
					H.m_HighlightOccurrenceEnd = GetOccurrencesSize();
					m_Hits.push_back(H);
				}
				prev_end1 = _First1->m_HighlightOccurrenceEnd;
				prev_end2 = _First2->m_HighlightOccurrenceEnd;
			}

			_First1++;
			_First2++;
		};

	hits_add(*m_pChild1, _First1);
	hits_add(*m_pChild2, _First2);
}


void CQueryBinaryOperationNode::hits_and_positions_intersection() 
{	
	vector<CHit>::const_iterator _First1 = m_pChild1->m_Hits.begin();
	vector<CHit>::const_iterator _Last1 = m_pChild1->m_Hits.end();
	vector<CHit>::const_iterator _First2 = m_pChild2->m_Hits.begin();
	vector<CHit>::const_iterator _Last2 = m_pChild2->m_Hits.end();
	m_Hits.clear();
	m_Hits.reserve(min(m_pChild1->m_Hits.size(),m_pChild2->m_Hits.size()) );
	ClearAndReserveOccurrences( min(m_pChild1->GetOccurrencesSize(),m_pChild2->GetOccurrencesSize()));

	size_t  prev_end1 = 0;
	size_t  prev_end2 = 0;
	for (; _First1 != _Last1 && _First2 != _Last2; )
		if (_First1->m_BreakNo < _First2->m_BreakNo)
		{
			prev_end1 = _First1->m_HighlightOccurrenceEnd;
			_First1++;
		}
		else 
		if (_First2->m_BreakNo < _First1->m_BreakNo)
		{
			prev_end2 = _First2->m_HighlightOccurrenceEnd;
			_First2++;
			
		}
		else
		{

			{	// inserting highlight occurrences from the first and the second child
				AddOccurrences(*m_pChild1, prev_end1, _First1->m_HighlightOccurrenceEnd);
				AddOccurrences(*m_pChild2, prev_end2, _First2->m_HighlightOccurrenceEnd);
				{
					CHit  H (_First1->m_BreakNo);
					H.m_HighlightOccurrenceEnd = GetOccurrencesSize();
					m_Hits.push_back(H);
				}
				prev_end1 = _First1->m_HighlightOccurrenceEnd;
				prev_end2 = _First2->m_HighlightOccurrenceEnd;
			}


			_First1++;
			_First2++;
		};

}

void CQueryBinaryOperationNode::hits_and_positions_difference() 
{	
	vector<CHit>::const_iterator _First1 = m_pChild1->m_Hits.begin();
	vector<CHit>::const_iterator _Last1 = m_pChild1->m_Hits.end();
	vector<CHit>::const_iterator _First2 = m_pChild2->m_Hits.begin();
	vector<CHit>::const_iterator _Last2 = m_pChild2->m_Hits.end();
	m_Hits.clear();
	m_Hits.reserve(min(m_pChild1->m_Hits.size(),m_pChild2->m_Hits.size()) );
	ClearAndReserveOccurrences( min(m_pChild1->GetOccurrencesSize(), m_pChild2->GetOccurrencesSize()) );

	size_t  prev_end1 = 0;
	for (; _First1 != _Last1 && _First2 != _Last2; )
		if (_First1->m_BreakNo < _First2->m_BreakNo)
		{
			AddOccurrences(*m_pChild1, prev_end1, _First1->m_HighlightOccurrenceEnd);
			prev_end1 = _First1->m_HighlightOccurrenceEnd;

			{
				CHit  H (_First1->m_BreakNo);
				H.m_HighlightOccurrenceEnd = GetOccurrencesSize();
				m_Hits.push_back(H);
			}
			_First1++;
		}
		else 
		if (_First2->m_BreakNo < _First1->m_BreakNo)
		{
			_First2++;
		}
		else
		{
			prev_end1 = _First1->m_HighlightOccurrenceEnd;
			_First1++;
			_First2++;
		};

	hits_add(*m_pChild1, _First1);
}


void CQueryAndOperation::Evaluate()
{
	m_pChild1->Evaluate();
	m_pChild2->Evaluate();

	

	if (!m_pChild1->GetNegation() && !m_pChild2->GetNegation())
	{
		hits_and_positions_intersection ();
	}
	else
	if (m_pChild1->GetNegation() && m_pChild2->GetNegation())
	{
		// !a && !b == !(a||b)
		hits_and_positions_union ();
		SetNegation(true);
	}
	else
	if (!m_pChild1->GetNegation() && m_pChild2->GetNegation())
	{
		hits_and_positions_difference ();
	}
	else //(m_pChild1->GetNegation() && !m_pChild2->GetNegation())
	{
		hits_and_positions_difference ();
	}
	
};

//=============   CQueryOrOperation =====================
CQueryOrOperation::CQueryOrOperation()
{
};

void CQueryOrOperation::Evaluate()
{
	m_pChild1->Evaluate();
	m_pChild2->Evaluate();

	
	

	if (!m_pChild1->GetNegation() && !m_pChild2->GetNegation())
	{
		hits_and_positions_union ();
	}
	else
	if (m_pChild1->GetNegation() && m_pChild2->GetNegation())
	{
		// !a || !b ==> !(a&&b)
		hits_and_positions_intersection ();
		SetNegation(true);
	}
	else
	if (m_pChild1->GetNegation() != m_pChild2->GetNegation())
	{
		assert (false);
	}

	
};


// ================ CQueryTokenNode ==================

CQueryTokenNode::CQueryTokenNode(int NodeIndex):CQueryNode(false, false)
{
	m_bAtomic = true;
	m_bChunk = false;
	m_bAnchor = false;
	m_NodeIndex = NodeIndex;
};

CQueryTokenNode::~CQueryTokenNode()
{
};


bool CQueryTokenNode::BuildRegExp(string RegExpStr, vector<DWORD>& IndexItems, bool negated)
{
	RML_RE re(RegExpStr, m_pHolder->m_pIndexator->GetRegexOptions());
	
	const CStringIndexSet*  IndexSet =  m_pHolder->m_pIndexator->GetIndexByName(m_IndexName);
	if (!IndexSet) return false;
	IndexSet->QueryTokenListUsingRegExp(re, IndexItems, negated);
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
bool	CQueryTokenNode::CreateAnchorPattern(const CConcHolder* pHolder, const string& BreakName, int anchor)
{
  m_bChunk  = false;
  m_bAnchor = true;
  m_bAtomic = true;
  SetHolder(pHolder);
  m_IndexName = BreakName.empty() ? "s" : BreakName;

  //-- assign occurrences directly to m_IndexItems
  m_IndexItems.clear();
  return pHolder->m_pIndexator->GetOccurrencesByPosition(m_IndexName, anchor, m_IndexItems);
};

size_t CQueryTokenNode::GetNodeFrequenceByNodeIndex(size_t NodeIndex) const
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
		
		pIndexSet = pHolder->m_pIndexator->GetIndexByNameOrShortName(name);
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
	m_Source = string("$") + IndexName + "=" + Value;
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
bool CQueryTokenNode::CreateUniversalPattern(const CConcHolder* pHolder, const string& IndexName)
{
  CStringIndexSet* pIndexSet = GetIndex(pHolder,IndexName);
  m_IndexItems.clear();
  pIndexSet->QueryTokenListUniversal(m_IndexItems);
  return true;
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
	if (!m_bChunk && !m_bAnchor) {
		const CStringIndexSet* pIndex  = m_pHolder->m_pIndexator->GetIndexByName(m_IndexName);
		BigramDirectionEnum bigr_direc =  m_pHolder->GetBigramsToOrder();

		if ( bigr_direc != bdDontUseBigrams   &&  pIndex->UseBigrams()) {
			assert (m_bUseTokenIdxs);
			vector< pair<CTokenNo,DWORD> > OccurAndTokenIds;
			pIndex->m_BigramsIndex.FindOccurrencesForBigrams(
									 bigr_direc,
									 m_IndexItems, 
									 m_pHolder->m_CurrentSearchPeriodNo, 
									 OccurAndTokenIds,
									 &m_pHolder->m_ShortOccurCaches,
									 m_CacheIds
									 );

			for (size_t i =0; i < OccurAndTokenIds.size(); i++) {
				m_Occurrences.push_back(OccurAndTokenIds[i].first);
				//const string& SecomdTokenStr  = pIndex->GetIndexItemStr( pIndex->m_Index[ OccurAndTokenIds[i].second] );
				//m_OccurrenceTokenIdxs.push_back(HashValue( SecomdTokenStr ));
				m_OccurrenceTokenIdxs.push_back( OccurAndTokenIds[i].second  );
			}

			/*
			  vector<size_t> debug; 
			  for (size_t i =0; i < pIndex->m_Index.size(); i++) {
				  const string& SecomdTokenStr  = pIndex->GetIndexItemStr( pIndex->m_Index[ i ]  );
				  int hv =  HashValue( SecomdTokenStr );
				  debug.push_back(hv);
			  }
			*/
		}
		else {
			pIndex->FindOccurrences(
						m_IndexItems, 
						m_pHolder->m_CurrentSearchPeriodNo, 
						m_Occurrences,
						m_pHolder->m_Profiler, 
						&m_pHolder->m_ShortOccurCaches,
						m_CacheIds
						);
		}
		m_ChunkLengths.resize(GetOccurrencesSize(), 1);
	}
	else if (m_bAnchor) {
	  // anchor query
	  m_Occurrences.assign(m_IndexItems.begin(), m_IndexItems.end());
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
};



void CQueryTokenNode::Evaluate()
{
	EvaluateWithoutHits();
	if (m_bChunk)
		ConvertOccurrencesToHitsForPatterns(true);
	else
		ConvertOccurrencesToHits (true);
};


// ========= CQuerySequenceNode ======================
CQuerySequenceNode::CQuerySequenceNode():CQueryNode(false, false)
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

size_t CQuerySequenceNode::GetNodeFrequenceByNodeIndex(size_t NodeIndex) const
{
	size_t Result = 0;
	for (int i = 0; i < m_Items.size(); i++)
		Result += m_Items[i]->GetNodeFrequenceByNodeIndex(NodeIndex);
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

void CQuerySequenceNode::EvaluateWithoutHits()
{	
	
	size_t MinOccurSize = DWORD_MAX;
	//  first get occurrences for each child
	int ItemsCount = m_Items.size();
	for (size_t i = 0; i < ItemsCount; i++)
	{
		m_Items[i]->EvaluateWithoutHits();
		MinOccurSize = min (m_Items[i]->GetOccurrencesSize(), MinOccurSize);
	}

	ClearAndReserveOccurrences(MinOccurSize*ItemsCount);

	if (ItemsCount==1) {
		//-- moo: special handling for singleton sequences
		AddOccurrences(*m_Items[0], 0, m_Items[0]->m_Occurrences.size()-1);
		return;
	}

	DwordVector S;	
	S.resize(ItemsCount, 0);

	// Path is currently observed path from an item of the first  list to an item of the last list
	// for each i > 0, 
	//  if Path[i] != -1, then
	//   : (m_Items[i]->m_Occurrences[Path[i]] - m_Items[i-1]->m_Occurrences[Path[i-1]]) <= m_Distances[i-1] if m_DistanceOps[i-1]=='<' (default)
	//   : (m_Items[i]->m_Occurrences[Path[i]] - m_Items[i-1]->m_Occurrences[Path[i-1]]) >= m_Distances[i-1] if m_DistanceOps[i-1]=='>'
	//   : (m_Items[i]->m_Occurrences[Path[i]] - m_Items[i-1]->m_Occurrences[Path[i-1]]) == m_Distances[i-1] if m_DistanceOps[i-1]=='='

	int* Path = new int[ItemsCount];	
	for (size_t i=0; i<ItemsCount; i++) Path[i] = -1;


	// depth-first search  from Path[0] 
	size_t Occur0Count = m_Items[0]->GetOccurrencesSize();
	for (Path[0] = 0; Path[0] < Occur0Count; Path[0]++)
	{
		if (Path[0]>0) // ignoring this line if it has the same value
			if (m_Items[0]->m_Occurrences[Path[0]-1] ==  m_Items[0]->m_Occurrences[Path[0]])
				continue;

		// i is the level of depth-first search
		size_t i = 1;
		while (i > 0)
		{
			// take the previos token no
			CTokenNo T = m_Items[i-1]->m_Occurrences[Path[i-1]];

			// get the number of postions in the current column
			size_t OccurCount = m_Items[i]->GetOccurrencesSize();

			// if we are for the first time  on this  level, then  Path[i]!= -1
			if (Path[i] == -1)
			{
				// position  S[i] and  Path[i] on the  first child after T
				for (Path[i]=S[i]; Path[i] < OccurCount; Path[i]++)
					if (m_Items[i]->m_Occurrences[Path[i]] >  T)
						break;
				S[i] = Path[i]; // save the starting position of Path[i] 
			}
			else
				Path[i]++; // get the next position in this column and try if it suits

			BYTE Distance   = m_Distances[i-1] + 1; // get the possible distance
			BYTE DistanceOp = m_DistanceOps[i-1];   // get distance constraint operator
			bool bPositionIsFound = false;

			// searching for the position, which is inside the distance, starting from Path[i]
			for (; Path[i] < OccurCount; Path[i]++)
			{
			  if (Path[i]>0) // ignoring equal occurrences
			    if (m_Items[i]->m_Occurrences[Path[i]-1] ==  m_Items[i]->m_Occurrences[Path[i]])
			      continue;

			  //-- check for distance-constraint violations
			  DWORD CurDistance = m_Items[i]->m_Occurrences[Path[i]] - T;
			  if (CurDistance < Distance && (DistanceOp=='=' || DistanceOp=='>'))
			    //-- minimum distance not yet reached
			    continue; 
			  else if (CurDistance > Distance && (DistanceOp=='=' || DistanceOp=='<'))
			    //-- max distance exceeded
			    break;
			  else if (CurDistance > MaxDistanceForNear)
			    //-- global max distance exceeded
			    break;
			  else
			    //-- a suitable position has been found
			    if (i+1 == ItemsCount) // if it is the end  of pattern then save this occurrence
			    {
			      // adding current path from Path[0] to Path[ItemsCount-1] to occurrences
			      for (int j=0; j < ItemsCount; j++)
				AddOccurrences(*m_Items[j], Path[j], Path[j]+1);
			    }
			    else
			    {
			      // Path[i] is a current node we should search for a child of Path[i]
			      // it means we should go to the  next level (i+1)
			      bPositionIsFound = true;
			      break;
			    };
			};

			if (bPositionIsFound)
			  i++; // going to depth 
			else
			{
			  // leaving this level, clearing Path[i] 
			  Path[i] = -1;
			  i--;
			};
		};
		// after this iteration Path[1]...Path[ItemsCount-1] must be -1
		// we are waiting  for the next value of Path[0]
		// S[1] ... S[ItemCount-1] were updated 
		// S[i] is a lower bound of a possible children of S[i-1], 
	};
	delete Path;

	// this procedure produces list of occurrences are stored by chunks, and sorted by the first item. 
	// The length of chunk is equal to the length of the  pattern,
	// Each chunk is a found occurrence of the pattern.
	m_ChunkLengths.resize(GetOccurrencesSize()/m_Items.size(), m_Items.size());
};

void CQuerySequenceNode::Evaluate()
{
	EvaluateWithoutHits();
	ConvertOccurrencesToHitsForPatterns(true);
};

//======================== CQueryNearNode =========================


CQueryNearNode::CQueryNearNode():CQueryNode(false, false)
{
	m_pChild1 = 0;
	m_pChild2 = 0;
	m_pMiddleChild = 0;
};

CQueryNearNode::~CQueryNearNode()
{
	if (m_pChild1) delete m_pChild1;
	if (m_pChild2) delete m_pChild2;
	if (m_pMiddleChild) delete m_pMiddleChild;
};

size_t CQueryNearNode::GetNodeFrequenceByNodeIndex(size_t NodeIndex) const
{
	size_t Result = 0;
	if (m_pChild1) Result += m_pChild1->GetNodeFrequenceByNodeIndex(NodeIndex);
	if (m_pChild2) Result += m_pChild2->GetNodeFrequenceByNodeIndex(NodeIndex);
	if (m_pMiddleChild) Result += m_pMiddleChild->GetNodeFrequenceByNodeIndex(NodeIndex);
	return Result;
}


bool CQueryNearNode::ReadDistanceFromString(const string& s)
{
	if (s=="0")
	{
		m_Distance = 0;
		return true;
	}

	int distance = atoi(s.c_str());
	if (distance == 0)
		return false;
	if (distance > MaxDistanceForNear)
		return false;
	m_Distance = distance;
	return true;
};

bool CQueryNearNode::Create(const CConcHolder* pHolder, const string& distance_str, CQueryNode* child1, CQueryNode* child2, CQueryNode* child3)
{
	if (!ReadDistanceFromString(distance_str)) return false;

	if (!child1->m_bAtomic) return false;
	if (!child2->m_bAtomic) return false;
	if (child3 != 0)
		if (!child3->m_bAtomic) return false;

	if (!child3)
	{
		m_pChild1 = child1;
		m_pChild2 = child2;
	}
	else
	{
		m_pChild1 = child1;
		m_pMiddleChild = child2;
		m_pChild2 = child3;
	};
	SetHolder(pHolder);
	return  true;
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

	if (!child3) {
		m_pChild1 = child1;
		m_pChild2 = child2;
	}
	else {
		m_pChild1 = child1;
		m_pMiddleChild = child2;
		m_pChild2 = child3;
	}

	SetHolder(pHolder);
	return  true;
}


void CQueryNearNode::Evaluate()
{
	m_ChunkLengths.clear();
	m_pChild1->EvaluateWithoutHits();
	m_pChild2->EvaluateWithoutHits();

	if (m_pMiddleChild) 
	{
		m_pMiddleChild->EvaluateWithoutHits();
	};

	int cnt1 = m_pChild1->GetOccurrencesSize();
	int cnt2 = m_pChild2->GetOccurrencesSize();
	int cnt_middle = 0;
	if (m_pMiddleChild) 
		cnt_middle = m_pMiddleChild->GetOccurrencesSize();
	if (cnt1 < cnt2)
	{
		swap(m_pChild1, m_pChild2);
		swap(cnt1, cnt2);
	}

	// Start2 is a index in m_pChild2->m_Occurrences
	int Start2 = 0;

	// Start3 is a index in m_pChild3->m_Occurrences
	int Start_middle = 0;

	ClearAndReserveOccurrences(min(m_pChild1->GetOccurrencesSize(),  m_pChild2->GetOccurrencesSize())*2);
	size_t  pos1 = 0, pos2=0, pos_middle = 0; 
	size_t PatternSize2, PatternSize1, PatternSizeMiddle=0;
	const bool bMiddleChild  = m_pMiddleChild != 0;
	for (int i = 0; i < cnt1; i+=m_pChild1->m_ChunkLengths[pos1], pos1++)
	{
		CTokenNo  T  = m_pChild1->m_Occurrences[i];

		for (; Start2 < cnt2; Start2 += m_pChild2->m_ChunkLengths[pos2], pos2++)
			if ( T <= m_pChild2->m_Occurrences[Start2+m_pChild2->m_ChunkLengths[pos2]-1] + m_Distance+1) 
				break;

		

		// T is the position of the last word in chunk from the first list
		PatternSize1 = m_pChild1->m_ChunkLengths[pos1];
		T  = m_pChild1->m_Occurrences[i + PatternSize1 - 1];

	
		size_t _pos2 = pos2;
		for (int k = Start2; k < cnt2; k+=m_pChild2->m_ChunkLengths[_pos2++])
			if ( T + m_Distance+1 < m_pChild2->m_Occurrences[k]) 
				  //  == " if m_pChild2->m_Occurrences[k] is outside [T-m_Distance, T+m_Distance] then break"
				break;
			else
			{
				PatternSize2 = m_pChild2->m_ChunkLengths[_pos2];

				if (T < m_pChild2->m_Occurrences[k])
				{
					if (bMiddleChild)
					{
						bool bCheckMiddle = false;
						for (; Start_middle < cnt_middle; Start_middle+=m_pMiddleChild->m_ChunkLengths[pos_middle++])
							if ( m_pMiddleChild->m_Occurrences[Start_middle] > T) 
							{
								bCheckMiddle = (m_pMiddleChild->m_Occurrences[Start_middle] < m_pChild2->m_Occurrences[k]);
								break;
							};
						if (!bCheckMiddle)
							continue;
					};
					

					// adding chunk from the first vector
					AddOccurrences(*m_pChild1, i, i+PatternSize1);

					if (bMiddleChild)
					{
						PatternSizeMiddle = m_pMiddleChild->m_ChunkLengths[pos_middle];
						AddOccurrences(*m_pMiddleChild,  Start_middle, Start_middle+PatternSizeMiddle);
					};

					// adding chunk from the second vector
					AddOccurrences(*m_pChild2, k, k+PatternSize2);

					m_ChunkLengths.push_back(PatternSize1+PatternSizeMiddle+PatternSize2);

				}
				else
				if (T > m_pChild2->m_Occurrences[k])
				{
					if (bMiddleChild)
					{
						bool bCheckMiddle = false;
						for (; Start_middle < cnt_middle; Start_middle+=m_pMiddleChild->m_ChunkLengths[pos_middle++])
							if ( m_pMiddleChild->m_Occurrences[Start_middle] > m_pChild2->m_Occurrences[k]) 
							{
								bCheckMiddle = (m_pMiddleChild->m_Occurrences[Start_middle] < T);
								break;
							};
						if (!bCheckMiddle)
							continue;
					};

					// adding chunk from the second vector
					AddOccurrences(*m_pChild2, k, k+PatternSize2);

					if (bMiddleChild)
					{
						PatternSizeMiddle = m_pMiddleChild->m_ChunkLengths[pos_middle];
						AddOccurrences(*m_pMiddleChild, Start_middle, Start_middle+PatternSizeMiddle);
					};

					// adding chunk from the first vector
					AddOccurrences(*m_pChild1, i, i+PatternSize1);

					m_ChunkLengths.push_back(PatternSize1+PatternSizeMiddle+PatternSize2);
				};
			};

		// if the middle child is finished than stop processing
		if (bMiddleChild)
			if (Start_middle == cnt_middle)
				break;

	};

	ConvertOccurrencesToHitsForPatterns(true);

};


CQueryWithNode::CQueryWithNode()
{
	m_bAtomic = true;
};

bool CQueryWithNode::Create(const CConcHolder*	pHolder, CQueryNode* child1, CQueryNode* child2)
{
	CQueryBinaryOperationNode::Create(pHolder, child1, child2, string(" with ") );
	return true;
};



void CQueryWithNode::OccurIntersectionWithTokenIds()
{	
    bool bFirstIsNotEmpty = !m_pChild1->m_OccurrenceTokenIdxs.empty();
    const vector<DWORD>& contexts =   bFirstIsNotEmpty ?  m_pChild1->m_OccurrenceTokenIdxs : m_pChild2->m_OccurrenceTokenIdxs;
    assert ( !contexts.empty() );
    size_t i1 = 0;
    size_t i2 = 0;
    size_t cnt1 = m_pChild1->GetOccurrencesSize();
    size_t cnt2 = m_pChild2->GetOccurrencesSize();
    
    m_OccurrenceTokenIdxs.clear();
    m_Occurrences.clear();

	while(i1 < cnt1 && i2 < cnt2)
    {
        if (m_pChild1->m_Occurrences[i1] < m_pChild2->m_Occurrences[i2])
			i1++;
		else if (m_pChild2->m_Occurrences[i2] < m_pChild1->m_Occurrences[i1])
			i2++;
		else
        {
            m_Occurrences.push_back(m_pChild1->m_Occurrences[i1]);
            m_OccurrenceTokenIdxs.push_back(contexts[bFirstIsNotEmpty ? i1 : i2]);
			i1++;
            i2++;
        }
    }
	
}


void CQueryWithNode::EvaluateWithoutHits()
{
	((CQueryTokenNode*)m_pChild1)->EvaluateWithoutHits();
	((CQueryTokenNode*)m_pChild2)->EvaluateWithoutHits();

    if (!m_pChild1->m_OccurrenceTokenIdxs.empty() || !m_pChild2->m_OccurrenceTokenIdxs.empty())
        OccurIntersectionWithTokenIds();
    else
    {
	    m_Occurrences.resize( m_pChild1->GetOccurrencesSize() + m_pChild2->GetOccurrencesSize() );

	    vector<CTokenNo>::iterator it = set_intersection (m_pChild1->m_Occurrences.begin(), m_pChild1->m_Occurrences.end(),
				       m_pChild2->m_Occurrences.begin(), m_pChild2->m_Occurrences.end(),
				       m_Occurrences.begin());

	    m_Occurrences.resize(it - m_Occurrences.begin());
    }

	if (m_bUseNodeIndices)
		m_OccurrenceNodeIndices.resize(m_Occurrences.size(), ((CQueryTokenNode*)m_pChild1)->m_NodeIndex);


	m_ChunkLengths.resize(GetOccurrencesSize(), 1);

};

void CQueryWithNode::Evaluate()
{
	EvaluateWithoutHits();
	ConvertOccurrencesToHits (true);
};



