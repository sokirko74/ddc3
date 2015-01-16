//-*- Mode: C++; c-basic-offset: 8; -*-
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2015 by Bryan Jurish
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

	//! should DDC use m_OccurrenceMatchIds to track match-ids?
	bool m_bUseMatchIds;

	//! match-ids for each occurrence in m_Occurrences (only if m_bUseMatchIds is true)
	vector<BYTE> m_OccurrenceMatchIds;

	//! all hits of this node in the current \ref period_def "subcorpora"
	vector<CHit> m_Hits;

	//! a reference to the parent holder (moo: should be unused until evaluation time, but isn't!)
	const CConcHolder* m_pHolder;

	//! the division of m_Occurrences by chunks , so m_ChunkLengths[0]+m_ChunkLengths[1]... = m_Occurrences.size() ;
	//! used by near() queries.
	vector<size_t> m_ChunkLengths;

	//! ???
	vector<int> m_CacheIds;


	//! Constructor
	CQueryNode(bool bUseNodeIndices=false, bool bUseMatchIds=false, const CConcHolder *holder=NULL)
		: m_bAtomic(false),
		  m_bNegated(false),
		  m_bUseNodeIndices(bUseNodeIndices),
		  m_bUseMatchIds(bUseMatchIds),
		  m_pHolder(holder)
	{};

	//! Destructor
	virtual ~CQueryNode();

	//! evaluate query node with respect to m_pHolder , populating m_Hits[] attributes m_BreakNo, m_HighlightOcurrencesEnd .
	//! If bSeparateHits is false (default), hits in m_Hits[] will by aggregated by m_BreakNo (i.e. at most one instance of any m_BreakNo value in m_Hits[])
	virtual void Evaluate(bool bSeparateHits=false);

	/** \brief initial-stage query evaluation
	 * \detail EvaluateWithoutHits is the first stage of the evaluation of one query.
	 * The main task it to build CQueryNode::m_Occurrences, which is written by chunks,
	 * sorted by the first item of a chunk. 
	 */
	virtual void EvaluateWithoutHits();

	//! set m_bNegated
	void SetNegation(bool Value);

	//! get m_bNegated
	bool GetNegation() const;

	//! inserts occurrences [FromNode.m_Occurrences.begin()+start,  FromNode.m_Occurrences.begin()+end) into m_Occurrences[] (and m_OccurrenceNodeIndices if appropriate)
	void AddOccurrences(const CQueryNode& FromNode, int start, int end);

	//! appends occurrences from both FromNode1 and FromNode2, maintaining sort-order and respecting both m_bUseNodeIndices and m_bUseMatchIds
	void AddOccurrences2(const CQueryNode& FromNode1, int start1, int end1,
			     const CQueryNode& FromNode2, int start2, int end2);

	//! appends occurrences from FromNode1, FromNode2, and FromNode3 maintaining sort-order and respecting both m_bUseNodeIndices and m_bUseMatchIds
	void AddOccurrences3(const CQueryNode& FromNode1, int start1, int end1,
			     const CQueryNode& FromNode2, int start2, int end2,
			     const CQueryNode& FromNode3, int start3, int end3);

	//! clears m_Occurrences[] and reserves at least \a size elements.
	//! Also clears and reserves m_OccurrenceNodeIndices[], m_OccurrenceMatchids[] just in case m_bUseNodeIndices rsp. m_bUseMatchIds is true.
	void ClearAndReserveOccurrences(int size);

	//! swaps m_Occurrences[], m_OccurrenceNodeIndices[], and m_OccurrenceMatchIds[] between caller object and Node
	void SwapOccurrences(CQueryNode& Node, bool swapChunkLengths=false);

	//! convert occurrences to hits  using m_pHolder->GetBreaks()
	void ConvertOccurrencesToHits (bool bSeparateHits);

	//! convert occurrences to hits for pattern query construction (like "mother likes father")
	void ConvertOccurrencesToHitsForPatterns (bool bSeparateHits);

	//! set  m_pHolder dependent properties m_bUseNodeIndices, m_bUseMatchIds
	void SetHolder(const CConcHolder* pHolder);

	//! return true iff this is a universal wildcard query (*); default returns false
	virtual bool IsUniversalWildcard() const;
	
	//! get occurrence count by query-node index; used by rank-sort operator. default implementation in CQueryNode just chokes.
	virtual size_t GetNodeFrequencyByNodeIndex(size_t NodeIndex) const;

	//! get the index of the first occurrence in m_Occurrences[] for hit number HitNo
	inline DWORD HitOccurrencesBegin(DWORD HitNo) const
	{ return (HitNo == 0) ? 0 : m_Hits[HitNo-1].m_HighlightOccurrenceEnd; };

	//! get the index of the first occurrence in m_Occurrences[] after hit number HitNo
	inline DWORD HitOccurrencesEnd(DWORD HitNo) const
	{ return m_Hits[HitNo].m_HighlightOccurrenceEnd >= m_Occurrences.size() ? m_Occurrences.size() : m_Hits[HitNo].m_HighlightOccurrenceEnd; };

	//! scan for first occurrence of match-id \a MatchId for hit \a HitNo in m_OccurrenceMatchIds[]; only valid if m_bUseMatchIds is true
	//! \returns least occurence-index \a i such that: occurrence \a i belongs to Hits[HitNo] and as match-id MatchId, or (DOWRD)-1 if none exists
	DWORD GetFirstOccurrenceInHit(DWORD HitNo, BYTE MatchId) const;

	//! scan for last occurrence of match-id \a MatchId for hit \a HitNo in m_OccurrenceMatchIds[]; only valid if m_bUseMatchIds is true
	//! \returns greatest occurence-index \a i such that: occurrence \a i belongs to Hits[HitNo] and as match-id MatchId, or (DWORD)-1 if none exists
	DWORD GetLastOccurrenceInHit(DWORD HitNo, BYTE MatchId) const;

	//! scan for middle-most occurrence of match-id \a MatchId for hit \a HitNo in m_OccurrenceMatchIds[]; only valid if m_bUseMatchIds is true
	//! \returns middle-most occurence-index \a i such that: occurrence \a i belongs to Hits[HitNo] and as match-id MatchId, or (DWORD)-1 if none exists
	DWORD GetMiddleOccurrenceInHit(DWORD HitNo, BYTE MatchId) const;
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
		: CQueryNode(false), m_pChild1(dtr1), m_pChild2(dtr2)
	{};

	void Create(const CConcHolder*	pHolder, CQueryNode* child1, CQueryNode* child2, string Operation);

	virtual ~CQueryBinaryOperationNode();

	//! assign hit occurrences and positions from another node
	void hits_and_positions_assign(const CQueryNode &NodeFrom);

	//! a modified version of std::union which unites simultaneously  two pairs of vectors
	void hits_and_positions_union();

	//! a modified version of std::intersection which simultaneously  deals  with two pairs of vectors
	void hits_and_positions_intersection();

	//! a modified version of std::difference which simultaneously  deals  with two pairs of vectors
	void hits_and_positions_difference();

	//! get occurrence count by query-node index; used by rank-sort operator.
	size_t GetNodeFrequencyByNodeIndex(size_t NodeIndex) const;
};

//----------------------------------------------------------------------
//! CQueryAndOperation implements the hit intersection or "and" operator: for example, "Mother&&father" 
class CQueryAndOperation	: public CQueryBinaryOperationNode  
{
public:
	CQueryAndOperation();
	void Evaluate(bool bSeparateHits=false);
};

//----------------------------------------------------------------------
//! CQueryOrOperation implements the hit union or "or" operator: for example, "Mother||father" 
class CQueryOrOperation	: public CQueryBinaryOperationNode 
{
public:
	CQueryOrOperation();
	void Evaluate(bool bSeparateHits=false);
};

//----------------------------------------------------------------------
//! CQueryTokenNode is a class which corresponds to one token or it's singular property (for example lemma)
class CQueryTokenNode : public CQueryNode
{
public:
	//!  find index items  in the index which is called m_IndexName
	vector<DWORD> m_IndexItems;

	//! the name of index or break collection on which this node is built (see  CQueryChunkNode and  CQueryTokenNode nodes)
	string m_IndexName;

	//! true, if it is a chunk (NP, VP and so on)
	bool m_bChunk;

	//! true iff this is an anchor query
	bool m_bAnchor;

	//! true iff this is a "universal wildcard" query
	bool m_bAny;

	//! integer offset for break-anchor ($.) queries
	int m_AnchorOffset;

public:
	//! a unique index of the node in query tree (used by rank-sort operator)
	BYTE m_NodeIndex;

	//! user-specified match-id (0 specifies default behavior, which is to use highlight-id=255)
	BYTE m_MatchId;
	
	CQueryTokenNode(int NodeIndex, BYTE MatchId=0);
	virtual ~CQueryTokenNode();

	//! compilation utility: set match-id
	void SetMatchId(BYTE MatchId);

	//! return true iff this is a universal wildcard query (*); override returns m_bAny
	virtual bool IsUniversalWildcard() const;

	//! low-level: populates m_IndexName and returns appropriate index; throws exception if no appropriate index is found
	CStringIndexSet* GetIndex(const CConcHolder* pHolder, const string &IndexName);

	//! low-level: makes m_IndexItems unique
	void MakeUnique(void);

	//! create pattern for matching literal index values (`$INDEX=@STRING' queries)
	bool CreateStringPattern(const CConcHolder* pHolder, const string& IndexName, const string& Value);

	//! create pattern for matching literal index values (`$INDEX=/REGEX/' queries)
	bool CreateRegexPattern(const CConcHolder* pHolder, const string& IndexName, const string& Regex, bool negated=false);

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

	//! create universal-match set
	bool CreateUniversalPattern(const CConcHolder *pHolder, const string& SourceStr="*");

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

	//! create an anchor pattern
	bool CreateAnchorPattern(const CConcHolder *pHolder, const string& BreakName, int anchor);

	//! generic regex query utility
	bool BuildRegExp(string RegExpStr, vector<DWORD>& IndexItems, bool negated=false);

	void	EvaluateWithoutHits();
	void	Evaluate(bool bSeparateHits=false);
	size_t	GetNodeFrequencyByNodeIndex(size_t NodeIndex) const;

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
	vector<BYTE>			m_DistanceOps;	
	vector<BYTE>			m_Distances;	
	vector<CQueryTokenNode*>	m_Items;

	//! add a distance to m_Distances, return false if the value is too large
	//! \deprecated
	bool AddDistance(const string& s, char op='<');
	
public:
	
	CQuerySequenceNode();
	virtual ~CQuerySequenceNode();

	//! create the node during yacc parsing
	//! \deprecated in favor of second form  Create(const CConcHolder* pHolder, const vector<const CQueryTokenNode*>& Items, const vector<BYTE>& Distances);
	bool	Create(const CConcHolder* pHolder, const vector<const CQueryNode*>& SequenceObj, const vector<string>& DistanceStrings);

	//! moo: create the node after initial parsing (compile-time)
	bool	Create(const CConcHolder* pHolder, const vector<CQueryTokenNode*>& Items, const vector<BYTE>& Distances, const vector<BYTE>& DistanceOps);

	void	EvaluateWithoutHits();
	void	Evaluate(bool bSeparateHits=false);
	size_t	GetNodeFrequencyByNodeIndex(size_t NodeIndex) const;
};

//----------------------------------------------------------------------
/*!
  \brief CQueryNearNode is a class which is used to search two or three
  child nodes, which are inside some text period of length CQueryNearNode::m_Distance ,
  i.e. an implementation of "near" operator NEAR(a,b,2) and NEAR(a,b,c, 2).
  Note that for the 3-subquery form NEAR(a,b,c, n), n specifies the maximum number
  of tokens between ANY PAIR of subqueries (a,b), (b,c), or (a,c).
*/ 
class CQueryNearNode : public CQueryNode 
{
public:
	//!  the first child 
	CQueryNode*		m_pChild1;  

	//!  the second  child  
	CQueryNode*		m_pChild2;  

	//!  the third  child (may be NULL)
	CQueryNode*		m_pChild3;   

	//!  the distance between the first child and the second child
	BYTE			m_Distance;

public:
	CQueryNearNode();
	virtual ~CQueryNearNode();

	//! create the node after yacc parsing (compile-time)
	bool Create(const CConcHolder* pHolder, BYTE distance, CQueryNode* child1, CQueryNode* child2, CQueryNode* child3 = NULL);

	void FindOccurrences2();
	void FindOccurrences3();
	void Evaluate(bool bSeparateHits=false);
	size_t GetNodeFrequencyByNodeIndex(size_t NodeIndex) const;
};

//----------------------------------------------------------------------
/*!
  \brief CQueryWithNode is a class which is used to search a node which simultaneously has two properties, namely 	m_pChild1 and  m_pChild2.
  (implementation of "with"  operator: for example, Mother with [NOUN] )
*/ 
class CQueryWithNode : public CQueryBinaryOperationNode
{
public:
	CQueryWithNode();

	//! create the node during yacc parsing
	bool Create(const CConcHolder*	pHolder, CQueryNode* child1, CQueryNode* child2);

	void EvaluateWithoutHits();
	void Evaluate(bool bSeparateHits=false);
};

//----------------------------------------------------------------------
/*!
  \brief CQueryWithoutNode: (EXPR1 without EXPR2) behaves like (EXPR1 WITH !EXPR2)
*/ 
class CQueryWithoutNode : public CQueryWithNode
{
public:
	CQueryWithoutNode()
	{};

	//! create the node during yacc parsing
	bool Create(const CConcHolder*	pHolder, CQueryNode* child1, CQueryNode* child2);

	void EvaluateWithoutHits();
};

//----------------------------------------------------------------------
/*!
  \brief CQOccurrenceIterator (formerly CQNearEvalItem) is used to iterate over query occurrences;
  used by near() and phrase ("") queries
 */
struct CQOccurrenceIterator {
	CQueryNode *node; //!< (sub)query node
	int cnt;	  //!< limit for  node->m_Occurrences[]
	int cur;	  //!< index into node->m_Occurrences[]
	size_t chpos;	  //!< index into node->m_ChunkLengths[] (match occurrence)

	/** default constructor */
	CQOccurrenceIterator(CQueryNode *node_=NULL)
	{ assign(node_); };

	/** copy constructor */
	CQOccurrenceIterator(const CQOccurrenceIterator &b)
	{ operator=(b); };

	/**
	 *  Create an iterator bound to the neighbors of \a src, used to avoid expensive EvaluateWithoutHits() for universal sub-queries as near() arguments.
	 *  Destructively alters \a node_->m_Occurrences[] (and associated vectors).
	 *  Generates a "bound" occurence in \a node_->m_Occurrences[] for each source-occurence <code>occi = src.node->m_Occurrences[i]</code>
	 *  and each offset \a off with <code>minOffset <= off <= maxOffset</code> representing token <code>*occi + off</code>, modulo <code>off==0</code>.
	 *  @param node_ universal wildcard node in which to create bound occurrences.
	 *  @param src source iterator to use for occurrence generation (should already have been populated by EvaluateWithoutHits())
	 *  @param minOffset minimum offset for bound occurrences wrt source-occurrence
	 *  @param maxOffset maximum offset for bound occurrences wrt source-occurrence (inclusive)
	 */
	void bind(CQueryTokenNode *node_, const CQOccurrenceIterator &src, int minOffset, int maxOffset);

	/** assignment operator */
	inline CQOccurrenceIterator& operator=(const CQOccurrenceIterator &b)
	{
		node = b.node;
		cnt = b.cnt;
		cur = b.cur;
		chpos = b.chpos;
		return *this;
	};

	/** node-assignment */
	inline void assign(CQueryNode *node_)
	{
		node  = node_;
		cnt   = 0;
		cur   = 0;
		chpos = 0;
		if (node) cnt = node->m_Occurrences.size();
	};

	/* node-assignment operator; wraps assign() */
	inline CQOccurrenceIterator& operator=(CQueryNode *node_)
	{
		assign(node_);
		return *this;
	};

	/** test whether iterator is valid */
	inline bool valid() const
	{ return cur < cnt; };

	/** bool typecast just wraps valid() */
	inline operator bool() const
	{ return valid(); };

	/** get size of current occurrence-chunk; assumes iterator is valid */
	inline size_t chunksize() const
	{  return node->m_ChunkLengths[chpos]; };

	/* get first token-id of current occurrence; assumes iterator is valid */
	inline CTokenNo tmin() const
	{ return node->m_Occurrences[cur]; };

	/* get last token-id of current occurrence (inclusive); assumes iterator is valid */
	inline CTokenNo tmax() const
	{ return node->m_Occurrences[cur + node->m_ChunkLengths[chpos] - 1]; };

	/* get last token-id of previous occurrence; assumes iterator is valid and cur>0 */
	inline CTokenNo tmax_prev() const
	{ return node->m_Occurrences[cur-1]; };

	/* increment operator updates the iterator to point to the next available occurrence, or to an invalid state if no such occurrence exists */
	inline void operator++()
	{ 
		if (!valid()) return;
		cur += node->m_ChunkLengths[chpos];
		chpos++;
	};

	/* equality operator tests whether calling object and argument \a b point to exactly the same tokens */
	bool operator==(const CQOccurrenceIterator &b) const;
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
