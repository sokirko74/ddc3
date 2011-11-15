//-*- Mode: C++; c-basic-offset: 8; -*-
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
// QNode.h: interface for the CQNode class.
//
//////////////////////////////////////////////////////////////////////

#ifndef QUERY_NODE_H
#define QUERY_NODE_H

#include "ConcHolder.h"

extern const size_t MaxDistanceForNear;

//----------------------------------------------------------------------
/*! \brief
  CQueryNode is an abstract class for any node in a query parse tree. A parse tree is built by 
  YACC during CQueryCompiler::ParseQuery. This class contains all members 
  which are common to atomic and operation nodes.

  moo: this class looks like it \b should be an abstract representation of query
  \b without any direct dependence on an actual index instance (e.g. ConcHolder
  or ConcIndexator) until evaluation time, but that doesn't appear to be the case.
  Attempting to re-build a more modular abstract query representation in Query.(cpp|h).
*/
class CQueryNode  
{
public:
	//! true if this node is a description of one token or a sequence of adjacent tokens
	bool m_bAtomic;  

	//! is the node negated?
	bool m_bNegated;

	//! the string from which this node was created
	string m_Source;

	//! all occurrences of this node in the current \ref period_def "subcorpus", which should be highlighted
	vector<CTokenNo> m_Occurrences;

	//! should DDC uses m_OccurrenceNodeIndices (m_OccurrenceNodeIndices is necessary only for #less_by_rank)
	bool m_bUseNodeIndices;

	//! query node indices for each occurrence (the origin for each occurrence)
	vector<BYTE> m_OccurrenceNodeIndices;

	//! should DDC use m_OccurrenceTokenIdxs (used for #left or #right query operators)
	bool m_bUseTokenIdxs;

	//! token idxs for each occurrence (used for #left or #right query operators)
	vector<DWORD> m_OccurrenceTokenIdxs;

	//! all hits of this node in the current \ref period_def "subcorpora"
	vector<CHit> m_Hits;

	//! a reference to the parent holder (moo: should be unused until evaluation time, but isn't!)
	const CConcHolder* m_pHolder;

	//! the division of m_Occurrences by chunks , so m_ChunkLengths[0]+m_ChunkLengths[1]... = m_Occurrences.size()
	vector<size_t> m_ChunkLengths;

	//! ???
	vector<int> m_CacheIds;


	//! Constructor
	CQueryNode(bool bUseNodeIndices=false, bool bUseTokenIdxs=false, const CConcHolder *holder=NULL)
		: m_bAtomic(false),
		  m_bNegated(false),
		  m_bUseNodeIndices(bUseNodeIndices),
		  m_bUseTokenIdxs(bUseTokenIdxs),
		  m_pHolder(holder)
	{};

	//! Destructor
	virtual ~CQueryNode();

	//! ?
	virtual void Evaluate();	

	//! ?
	virtual void EvaluateWithoutHits();	

	//! set m_bNegated
	void SetNegation(bool Value);

	//! get m_bNegated
	bool GetNegation() const;

	//! ?
	void AddOccurrences(const CQueryNode& FromNode, int start, int end);

	//! ?
	void ClearAndReserveOccurrences(int size);

	//! ?
	void SwapOccurrences(CQueryNode& Node);

	//! convert occurrences to hits  using m_pHolder->GetBreaks()
	void ConvertOccurrencesToHits (bool bUniqueHits);

	//! convert occurrences to hits for pattern query construction (like "mother likes father")
	void ConvertOccurrencesToHitsForPatterns (bool bUniqueHits);

	//! set  m_pHolder
	void SetHolder(const CConcHolder* pHolder);

	//! ?
	virtual size_t GetNodeFrequenceByNodeIndex(size_t NodeIndex) const;
};

//----------------------------------------------------------------------
/*!
  An abtsract class for binary logical operations on nodes (and, or). It contains instances of three major 
  logical operation (union, intersection and difference) which were slightly modified to deal with 
  CQueryNode::m_Hits and CQueryNode::m_Occurrences simultaneously.
*/
class CQueryBinaryOperationNode : public CQueryNode 
{
	//! add the hit list of "NodeFrom" to the back of "First"
	void hits_add(const CQueryNode& NodeFrom, vector<CHit>::const_iterator First);

public:
	//! the first operation member
	CQueryNode*	m_pChild1;  

	//! the second operation member
	CQueryNode*	m_pChild2;  

public:
	CQueryBinaryOperationNode() : m_pChild1(NULL), m_pChild2(NULL)
	{};

	CQueryBinaryOperationNode(CQueryNode *dtr1, CQueryNode *dtr2)
		: CQueryNode(false,false), m_pChild1(dtr1), m_pChild2(dtr2)
	{};

	void Create(const CConcHolder*	pHolder, CQueryNode* child1, CQueryNode* child2, string Operation);

	virtual ~CQueryBinaryOperationNode();

	//! a modified version of std::union which unites simultaneously  two pairs of vectors
	void hits_and_positions_union();

	//! a modified version of std::intersection which simultaneously  deals  with two pairs of vectors
	void hits_and_positions_intersection();

	//! a modified version of std::difference which simultaneously  deals  with two pairs of vectors
	void hits_and_positions_difference();

	size_t GetNodeFrequenceByNodeIndex(size_t NodeIndex) const;
};

//----------------------------------------------------------------------
//! CQueryAndOperation implements the hit intersection or "and" operator: for example, "Mother&&father" 
class CQueryAndOperation	: public CQueryBinaryOperationNode  
{
public:
	CQueryAndOperation();
	void Evaluate();
};

//----------------------------------------------------------------------
//! CQueryOrOperation implements the hit union or "or" operator: for example, "Mother||father" 
class CQueryOrOperation	: public CQueryBinaryOperationNode 
{
public:
	CQueryOrOperation();
	void Evaluate();
};

//----------------------------------------------------------------------
//! CQueryTokenNode is a class which corresponds to one token or it's singular property (for example lemma)
class CQueryTokenNode : public CQueryNode
{
public:
	//!  find index items  in the index which is called m_IndexName
	vector<DWORD> m_IndexItems;

	//! the name  of index, on which this node is built (see  CQueryChunkNode and  CQueryTokenNode nodes)
	string m_IndexName;

	//! true, if it is a chunk (NP, VP and so on)
	bool m_bChunk;

public:
	// a unique index of the node in query tree
	BYTE m_NodeIndex;
	
	CQueryTokenNode(int NodeIndex);
	virtual ~CQueryTokenNode();

	//! low-level: populates m_IndexName and returns appropriate index; throws exception if no appropriate index is found
	CStringIndexSet* GetIndex(const CConcHolder* pHolder, const string &IndexName);

	//! low-level: makes m_IndexItems unique
	void MakeUnique(void);

	//! create pattern for matching literal index values (`$INDEX=@STRING' queries)
	bool CreateStringPattern(const CConcHolder* pHolder, const string& IndexName, const string& Value);

	//! create pattern for matching literal index values (`$INDEX=/REGEX/' queries)
	bool CreateRegexPattern(const CConcHolder* pHolder, const string& IndexName, const string& Regex);

	//! create pattern for matching literal index values (`$INDEX=@{VAL1,...}' queries)
	bool CreateSetPattern(const CConcHolder* pHolder, const string& IndexName, const set<string>& Values);

	//! create pattern for matching set-valued right-truncated (prefix-set) queries (`$INDEX={PREFIX,...}*')
	bool CreatePrefixSetPattern(const CConcHolder* pHolder, const string& IndexName, const set<string>& Prefixes);

	//! create pattern for matching simple right-truncated (prefix) queries (`$INDEX=PREFIX*')
	bool CreatePrefixPattern(const CConcHolder* pHolder, const string& IndexName, const string& Prefix);

	//! create pattern for matching set-valued left-truncated (suffix-set) queries (`$INDEX=*{SUFFIX,...}'): uses regex
	bool CreateSuffixSetPattern(const CConcHolder* pHolder, const string& IndexName, const set<string>& Suffixes);

	//! create pattern for matching set-valued left-truncated (suffix-set) queries (`$INDEX=*SUFFIX'): uses regex
	bool CreateSuffixPattern(const CConcHolder* pHolder, const string& IndexName, const string& Suffix);

	//! create pattern for matching set-valued substring (infix-set) queries (`$INDEX=*{INFIX,...}*'): uses regex
	bool CreateInfixSetPattern(const CConcHolder* pHolder, const string& IndexName, const set<string>& Infixes);

	//! create pattern for matching simple substring (infix) queries (`$INDEX=*INFIX*'): uses regex
	bool CreateInfixPattern(const CConcHolder* pHolder, const string& IndexName, const string& Infix);


	//! create lemma-match pattern (old)
	bool CreateLemmaPattern(const CConcHolder* pHolder, const string& Value);

	//! create pattern which is associated with "Thes" index (old)
	bool CreateThesPattern(const CConcHolder* pHolder, const string& IndexName, const string& src);

	//! create pattern which is associated with "MorphPattern" or "Lemma" index (old)
	bool CreateMorphAnnotationPattern(const CConcHolder* pHolder, const string& IndexName, const vector<string> &Items);

	//! create pattern which loads target values from the file \a FileName
	bool CreateFileList(const CConcHolder* pHolder, const string &IndexName, const string& FileName);

	//! create pattern which is associated with "Chunk" index 
	bool CreateChunkPattern(const CConcHolder* pHolder, const string& IndexName, const string& ChunkTypeStr);

	//! generic regex query utility
	bool BuildRegExp(string RegExpStr, vector<DWORD>& IndexItems);

	void	EvaluateWithoutHits();
	void	Evaluate();
	size_t	GetNodeFrequenceByNodeIndex(size_t NodeIndex) const;

};


//----------------------------------------------------------------------
/*!
  \brief  CQuerySequenceNode is an implementation of sequence  operator, for example, "Mother and father".
  This class holds a sequence of nodes of type CQueryTokenNode (slot m_Items).
  Between m_Items[i] 	and  m_Items[i+1] must be no more than m_Distances[i] tokens.
*/ 
class CQuerySequenceNode : public CQueryNode
{
public:
	vector<BYTE>			m_Distances;	
	vector<CQueryTokenNode*>	m_Items;

	//! add a distance to m_Distances, return false if the value is too large
	//! \deprecated
	bool AddDistance(const string& s);
	
public:
	
	CQuerySequenceNode();
	virtual ~CQuerySequenceNode();

	//! create the node during yacc parsing
	//! \deprecated in favor of second form  Create(const CConcHolder* pHolder, const vector<const CQueryTokenNode*>& Items, const vector<BYTE>& Distances);
	bool	Create(const CConcHolder* pHolder, const vector<const CQueryNode*>& SequenceObj, const vector<string>& DistanceStrings);

	//! moo: create the node after initial parsing (compile-time)
	bool	Create(const CConcHolder* pHolder, const vector<CQueryTokenNode*>& Items, const vector<BYTE>& Distances);

	void	EvaluateWithoutHits();
	void	Evaluate();
	size_t	GetNodeFrequenceByNodeIndex(size_t NodeIndex) const;
};

//----------------------------------------------------------------------
/*!
  \brief CQueryNearNode is a class which is used to search two or three 
  nodes, which are inside some text period of length CQueryNearNode::m_Distance. It other words
  it is an implementation of "near" operator: for example, NEAR(a,b,2).
*/ 
class CQueryNearNode : public CQueryNode 
{
public:
	//!  the first child 
	CQueryNode*		m_pChild1;  

	//!  the middle  child  (can be null)
	CQueryNode*		m_pMiddleChild;   

	//!  the second  child  
	CQueryNode*		m_pChild2;  

	//!  the distance between the first child and the second child
	BYTE			m_Distance;

	//! read the  text distance from a string, return false if it is to large
	//! \deprecated
	bool ReadDistanceFromString(const string& s);

public:
	CQueryNearNode();
	virtual ~CQueryNearNode();

	//! create the node during yacc parsing
	//! \deprecated in favor of Create(const CConcHolder* pHolder, BYTE distance, CQueryNode* child1, CQueryNode* child2, CQueryNode* child3 = NULL);
	bool Create(const CConcHolder* pHolder, const string& distance_str, CQueryNode* child1, CQueryNode* child2, CQueryNode* child3 = 0);

	//! create the node after yacc parsing (compile-time)
	bool Create(const CConcHolder* pHolder, BYTE distance, CQueryNode* child1, CQueryNode* child2, CQueryNode* child3 = NULL);

	void Evaluate();
	size_t GetNodeFrequenceByNodeIndex(size_t NodeIndex) const;
};

//----------------------------------------------------------------------
/*!
  \brief CQueryWithNode is a class which is used to search a node which simultaneously has two properties, namely 	m_pChild1 and  m_pChild2.
  (implementation of "with"  operator: for example, Mother with [NOUN] )
*/ 
class CQueryWithNode : public CQueryBinaryOperationNode
{
	void OccurIntersectionWithTokenIds();
public:
	CQueryWithNode();

	//! create the node during yacc parsing
	bool Create(const CConcHolder*	pHolder, CQueryNode* child1, CQueryNode* child2);

	void EvaluateWithoutHits();
	void Evaluate();
};

//----------------------------------------------------------------------
/** compute the set of types \c WordForms which may share a lemma with \c src in language \c Langua.
 *
 *  The underlying CLemmatizer should handle transcoding of user queries transparently, assuming you
 *  called CLemmatizer::initIconv() with the appropriate encoding arguments.
 *
 *  This is very ugly, and the entire morphology system needs an overhaul.
 *
 *  Formerly a hidden function in QueryNode.cpp.
 */
extern void GetWordForms (const MorphLanguageEnum Langua, const string& src, set<string>& WordForms);


#endif /* QUERY_NODE_H */
