//-*- Mode: C++ -*-
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2020 by Bryan Jurish
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
    std::string m_Source;

    //! all occurrences of this node in the current \ref period_def "subcorpus", which should be highlighted
    std::vector<CTokenNo> m_Occurrences;

    //! should DDC uses m_OccurrenceNodeIndices (m_OccurrenceNodeIndices is necessary only for #less_by_rank)
    bool m_bUseNodeIndices;

    //! query node indices for each occurrence (the origin for each occurrence)
    std::vector<BYTE> m_OccurrenceNodeIndices;

    //! should DDC use m_OccurrenceMatchIds to track match-ids?
    bool m_bUseMatchIds;

    //! match-ids for each occurrence in m_Occurrences (only if m_bUseMatchIds is true)
    std::vector<BYTE> m_OccurrenceMatchIds;

    //! all hits of this node in the current \ref period_def "subcorpora"
    std::vector<CHit> m_Hits;

    //! a reference to the parent holder (moo: should be unused until evaluation time, but isn't!)
    const CConcHolder* m_pHolder;

    //! the division of m_Occurrences by chunks , so m_ChunkLengths[0]+m_ChunkLengths[1]... = m_Occurrences.size() ;
    //! used by near() queries.
    std::vector<uint32_t> m_ChunkLengths;

    //! chunk offsets, used by CQuerySequenceNode queries; use EnsureChunkOffsets() to populate if required
    /// \li introduced in v2.1.19; still unused (should probably be used to allow binary-search seek for NEAR queries
    std::vector<uint32_t> m_ChunkOffsets;

    //! ???
    std::vector<int> m_CacheIds;


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

    //! insers a single occurrence FromNode.m_Occurrences[occ]
    inline void AddOccurrence(const CQueryNode& FromNode, int FromOcc)
    {
        m_Occurrences.push_back(FromNode.m_Occurrences[FromOcc]);
        if (m_bUseNodeIndices)
            m_OccurrenceNodeIndices.push_back(FromNode.m_OccurrenceNodeIndices[FromOcc]);
        if (m_bUseMatchIds)
            m_OccurrenceMatchIds.push_back(FromNode.m_OccurrenceMatchIds[FromOcc]);
    };

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

    //! ensure m_ChunkOffsets[] is populated
    void EnsureChunkOffsets();

    //! set  m_pHolder dependent properties m_bUseNodeIndices, m_bUseMatchIds
    void SetHolder(const CConcHolder* pHolder);

    //! return true iff this is a universal wildcard query (*); default returns false
    virtual bool IsUniversalWildcard() const;
        
    //! get occurrence count by query-node index; used by rank-sort operator. default implementation in CQueryNode just chokes.
    virtual size_t GetNodeFrequencyByNodeIndex(size_t NodeIndex) const;

    //! get the index of the first occurrence in m_Occurrences[] for hit number HitNo
    inline uint32_t HitOccurrencesBegin(uint32_t HitNo) const
    { return (HitNo == 0) ? 0 : m_Hits[HitNo-1].m_HighlightOccurrenceEnd; };

    //! get the index of the first occurrence in m_Occurrences[] after hit number HitNo
    inline uint32_t HitOccurrencesEnd(uint32_t HitNo) const
    { return m_Hits[HitNo].m_HighlightOccurrenceEnd >= m_Occurrences.size() ? m_Occurrences.size() : m_Hits[HitNo].m_HighlightOccurrenceEnd; };

    //! scan for first occurrence of match-id \a MatchId for hit \a HitNo in m_OccurrenceMatchIds[]; only valid if m_bUseMatchIds is true
    //! \returns least occurence-index \a i such that: occurrence \a i belongs to Hits[HitNo] and as match-id MatchId, or (DOWRD)-1 if none exists
    uint32_t GetFirstOccurrenceInHit(uint32_t HitNo, BYTE MatchId) const;

    //! scan for last occurrence of match-id \a MatchId for hit \a HitNo in m_OccurrenceMatchIds[]; only valid if m_bUseMatchIds is true
    //! \returns greatest occurence-index \a i such that: occurrence \a i belongs to Hits[HitNo] and as match-id MatchId, or (DWORD)-1 if none exists
    uint32_t GetLastOccurrenceInHit(uint32_t HitNo, BYTE MatchId) const;

    //! scan for middle-most occurrence of match-id \a MatchId for hit \a HitNo in m_OccurrenceMatchIds[]; only valid if m_bUseMatchIds is true
    //! \returns middle-most occurence-index \a i such that: occurrence \a i belongs to Hits[HitNo] and as match-id MatchId, or (DWORD)-1 if none exists
    uint32_t GetMiddleOccurrenceInHit(uint32_t HitNo, BYTE MatchId) const;

    //! get average size of gap between breaks in m_Hits[]; returned value is always >= 1
    inline uint32_t BreakStride() const
    { return m_Hits.empty() ? 1 : std::max((size_t)1, (m_Hits.back().m_BreakNo-m_Hits.front().m_BreakNo)/m_Hits.size()); };
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
    void hits_add(const CQueryNode& NodeFrom, std::vector<CHit>::const_iterator First);

public:
    //! the first operation member
    CQueryNode*     m_pChild1;  

    //! the second operation member
    CQueryNode*     m_pChild2;  

public:
    CQueryBinaryOperationNode() : m_pChild1(NULL), m_pChild2(NULL)
    {};

    CQueryBinaryOperationNode(CQueryNode *dtr1, CQueryNode *dtr2)
        : CQueryNode(false), m_pChild1(dtr1), m_pChild2(dtr2)
    {};

    void Create(const CConcHolder*  pHolder, CQueryNode* child1, CQueryNode* child2, std::string Operation);

    virtual ~CQueryBinaryOperationNode();

    //! push a single hit onto m_Hits[]
    //! \li expects occurrences to already have been added; sets new hit's m_HighlightOccurrenceEnd=m_Occurrences.size()
    //! \li for use by hits_and_positions_intersection() etc.
    inline void pushHit(uint32_t BreakNo)
    {
        CHit H(BreakNo);
        H.m_HighlightOccurrenceEnd = m_Occurrences.size();
        m_Hits.push_back(H);
    };

    //! assign hit occurrences and positions from another node
    //! \note how does this differ from SwapOccurrences() + m_OccurrenceNodeIndices.assign() + m_OccurrenceMatchIds.assign() + ... ?
    void hits_and_positions_assign(const CQueryNode &NodeFrom);

    //! hijack hit occurrences and positions from another node
    void hits_and_positions_swap(CQueryNode &NodeFrom);
        
    //! a modified version of std::union which unites simultaneously  two pairs of vectors
    //! \note now implicitly evalutes child nodes (v2.0.45 2016-09-05 moocow)
    void hits_and_positions_union(bool bSeparateHits=false);

    //! a modified version of std::intersection which simultaneously  deals  with two pairs of vectors
    //! \note now implicitly evalutes child nodes (v2.0.45 2016-09-05 moocow)
    void hits_and_positions_intersection(bool bSeparateHits=false);

    //! a modified version of std::difference which simultaneously  deals  with two pairs of vectors
    //! \note now implicitly evalutes child nodes (v2.0.45 2016-09-05 moocow)
    void hits_and_positions_difference(bool bSeparateHits=false);

    //! get occurrence count by query-node index; used by rank-sort operator.
    size_t GetNodeFrequencyByNodeIndex(size_t NodeIndex) const;
};

//----------------------------------------------------------------------
//! CQueryAndOperation implements the hit intersection or "and" operator: for example, "Mother&&father" 
class CQueryAndOperation        : public CQueryBinaryOperationNode  
{
public:
    CQueryAndOperation();
    virtual ~CQueryAndOperation() {};
    void Evaluate(bool bSeparateHits=false);
};

//----------------------------------------------------------------------
//! CQueryOrOperation implements the hit union or "or" operator: for example, "Mother||father" 
class CQueryOrOperation : public CQueryBinaryOperationNode 
{
public:
    CQueryOrOperation();
    virtual ~CQueryOrOperation() {};
    void Evaluate(bool bSeparateHits=false);
};

//----------------------------------------------------------------------
//! CQueryTokenNode is a class which corresponds to one token or it's singular property (for example lemma)
class CQueryTokenNode : public CQueryNode
{
public:
    //!  find index items  in the index which is called m_IndexName
    std::vector<uint32_t> m_IndexItems;

    //! the name of index or break collection on which this node is built (see  CQueryChunkNode and  CQueryTokenNode nodes)
    std::string m_IndexName;

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
    CStringIndexSet* GetIndex(const CConcHolder* pHolder, const std::string &IndexName);

    //! low-level: makes m_IndexItems unique
    void MakeUnique(void);

    //! create pattern for matching literal index values (`$INDEX=@STRING' queries)
    bool CreateStringPattern(const CConcHolder* pHolder, const std::string& IndexName, const std::string& Value);

    //! create pattern for matching literal index values (`$INDEX=/REGEX/' queries)
    bool CreateRegexPattern(const CConcHolder* pHolder, const std::string& IndexName, const std::string& Regex, bool negated=false);

    //! create pattern for matching literal index values (`$INDEX=@{VAL1,...}' queries)
    bool CreateSetPattern(const CConcHolder* pHolder, const std::string& IndexName, const std::set<std::string>& Values);

    //! create pattern for matching set-valued right-truncated (prefix-set) queries (`$INDEX={PREFIX,...}*')
    bool CreatePrefixSetPattern(const CConcHolder* pHolder, const std::string& IndexName, const std::set<std::string>& Prefixes);

    //! create pattern for matching simple right-truncated (prefix) queries (`$INDEX=PREFIX*')
    bool CreatePrefixPattern(const CConcHolder* pHolder, const std::string& IndexName, const std::string& Prefix);

    //! create pattern for matching set-valued left-truncated (suffix-set) queries (`$INDEX=*{SUFFIX,...}'): uses regex
    bool CreateSuffixSetPattern(const CConcHolder* pHolder, const std::string& IndexName, const std::set<std::string>& Suffixes);

    //! create pattern for matching set-valued left-truncated (suffix-set) queries (`$INDEX=*SUFFIX'): uses regex
    bool CreateSuffixPattern(const CConcHolder* pHolder, const std::string& IndexName, const std::string& Suffix);

    //! create pattern for matching set-valued substring (infix-set) queries (`$INDEX=*{INFIX,...}*'): uses regex
    bool CreateInfixSetPattern(const CConcHolder* pHolder, const std::string& IndexName, const std::set<std::string>& Infixes);

    //! create pattern for matching simple substring (infix) queries (`$INDEX=*INFIX*'): uses regex
    bool CreateInfixPattern(const CConcHolder* pHolder, const std::string& IndexName, const std::string& Infix);

    //! create universal-match set
    bool CreateUniversalPattern(const CConcHolder *pHolder, const std::string& SourceStr="*");

    //! create empty match-set
    bool CreateNullPattern(const CConcHolder *pHolder, const std::string& IndexName="Token");

    //! create lemma-match pattern (old)
    bool CreateLemmaPattern(const CConcHolder* pHolder, const std::string& Value);

    //! create pattern which is associated with "Thes" index (old)
    bool CreateThesPattern(const CConcHolder* pHolder, const std::string& IndexName, const std::string& src);

    //! create pattern which is associated with "MorphPattern" or "Lemma" index (old)
    bool CreateMorphAnnotationPattern(const CConcHolder* pHolder, const std::string& IndexName, const std::vector<std::string> &Items);

    //! create pattern which loads target values from the file \a FileName
    bool CreateFileList(const CConcHolder* pHolder, const std::string &IndexName, const std::string& FileName);

    //! create pattern which is associated with "Chunk" index 
    bool CreateChunkPattern(const CConcHolder* pHolder, const std::string& IndexName, const std::string& ChunkTypeStr);

    //! create an anchor pattern
    bool CreateAnchorPattern(const CConcHolder *pHolder, const std::string& BreakName, int anchor);

    //! generic regex query utility
    bool BuildRegExp(std::string RegExpStr, std::vector<uint32_t>& IndexItems, bool negated=false);

    void    EvaluateWithoutHits();
    void    Evaluate(bool bSeparateHits=false);
    size_t  GetNodeFrequencyByNodeIndex(size_t NodeIndex) const;

};


//----------------------------------------------------------------------
/*!
  \brief  CQuerySequenceNode is an implementation of sequence  operator, for example, "Mother and father".
  This class holds a sequence of nodes of type CQueryTokenNode (slot m_Items).
  Between m_Items[i]    and  m_Items[i+1] must be no more than m_Distances[i] tokens.
*/ 
class CQuerySequenceNode : public CQueryNode
{
public:
    std::vector<BYTE>                    m_DistanceOps;  
    std::vector<BYTE>                    m_Distances;    
    std::vector<CQueryTokenNode*>        m_Items;

    //! add a distance to m_Distances, return false if the value is too large
    //! \deprecated
    bool AddDistance(const std::string& s, char op='<');
        
public:
        
    CQuerySequenceNode();
    virtual ~CQuerySequenceNode();

    //! create the node during yacc parsing
    //! \deprecated in favor of second form  Create(const CConcHolder* pHolder, const vector<const CQueryTokenNode*>& Items, const vector<BYTE>& Distances);
    bool    Create(const CConcHolder* pHolder, const std::vector<const CQueryNode*>& SequenceObj, const std::vector<std::string>& DistanceStrings);

    //! moo: create the node after initial parsing (compile-time)
    bool    Create(const CConcHolder* pHolder, const std::vector<CQueryTokenNode*>& Items, const std::vector<BYTE>& Distances, const std::vector<BYTE>& DistanceOps);

    void    EvaluateWithoutHits();
    void    Evaluate(bool bSeparateHits=false);
    size_t  GetNodeFrequencyByNodeIndex(size_t NodeIndex) const;
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
    CQueryNode*             m_pChild1;  

    //!  the second  child  
    CQueryNode*             m_pChild2;  

    //!  the third  child (may be NULL)
    CQueryNode*             m_pChild3;   

    //!  the distance between the first child and the second child
    BYTE                    m_Distance;

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
  \brief CQueryWithNode is a class which is used to search a node which simultaneously has two properties, namely       m_pChild1 and  m_pChild2.
  (implementation of "with"  operator: for example, Mother with [NOUN] )
*/ 
class CQueryWithNode : public CQueryBinaryOperationNode
{
public:
    BYTE m_MatchId;

public:
    CQueryWithNode();
    virtual ~CQueryWithNode() {};

    //! create the node during yacc parsing
    bool Create(const CConcHolder*  pHolder, CQueryNode* child1, CQueryNode* child2, BYTE matchId=0);

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
    virtual ~CQueryWithoutNode() {};

    //! create the node during yacc parsing
    bool Create(const CConcHolder*  pHolder, CQueryNode* child1, CQueryNode* child2, BYTE matchId=0);

    void EvaluateWithoutHits();
};

//----------------------------------------------------------------------
/*!
  \brief CQueryWithorNode: (EXPR1 withor EXPR2) behaves like (EXPR1 || EXPR2) under token-identity
*/ 
class CQueryWithorNode : public CQueryWithNode
{
public:
    CQueryWithorNode()
    {};
    virtual ~CQueryWithorNode() {};

    //! create the node during yacc parsing
    bool Create(const CConcHolder*  pHolder, CQueryNode* child1, CQueryNode* child2, BYTE matchId=0);

    void EvaluateWithoutHits();
};

//----------------------------------------------------------------------


/*!
 * \brief CQOccurrenceIterator (formerly CQNearEvalItem) is used to iterate over query occurrences; used by near() queries
 *  + used by near()-queries, appropriate for iterating over single- or multi-token query nodes
 *    (respects node->m_ChunkLengths)
 */
struct CQOccurrenceIterator {
    CQueryNode *node; //!< (sub)query node
    int cnt;          //!< limit for  node->m_Occurrences[]
    int cur;          //!< index into node->m_Occurrences[]
    uint32_t chpos;      //!< index into node->m_ChunkLengths[] (match occurrence)

    /** default constructor */
    CQOccurrenceIterator(CQueryNode *node_=NULL)
    { assign(node_); };

    /** copy constructor */
    CQOccurrenceIterator(const CQOccurrenceIterator &b)
    { operator=(b); };

    virtual ~CQOccurrenceIterator() {};

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

    /** invalidate iterator */
    inline void invalidate()
    { cur = cnt; };

    /** bool typecast just wraps valid() */
    inline operator bool() const
    { return valid(); };

    /** get size of current occurrence-chunk; assumes iterator is valid */
    inline size_t chunksize() const
    {  return node->m_ChunkLengths[chpos]; };

    /* get token-id for occurrence-id \a occ */
    inline CTokenNo tocc(uint32_t occ) const
    { return node->m_Occurrences[occ]; };
        
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

    /* seek iterator to the first occurrence greater-than-or-equal-to Tok */
    inline void seek(const CTokenNo Tok)
    {
        while (valid() && tmin() < Tok) operator++();
    };

    /* equality operator tests whether calling object and argument \a b point to exactly the same tokens */
    bool operator==(const CQOccurrenceIterator &b) const;
};

/**
 * DDC_OCCITER_LB_COEF
 *  + minimum coefficient for deciding between linear increment and lower_bound() on CQTokenOccurrenceIterator::seek()
//  + heuristic for approximating number of linear-search ops per binary-search visitation (empirically set to 4)
//  + speeds up phrase-, WITH-, and WITHOUT-queries by up to 69%,  e.g. ("@das @Haus")
//  + can hurt up to 5% for "very simple" &&-queries, e.g. (@Haus && @Garten)
*  + introduced in v2.1.19-pre1
*/
#define DDC_OCCITER_LB_COEF 4

/*!
 * \brief CQTokenOccurrenceIterator (formerly CQNearEvalItem) is used to iterate over query occurrences;
 *  + used by phrase ("") queries, appropriate for iterating over single-token query nodes
 *    (assumes all node->m_ChunkLengths[i]==1)
 *  + disregards chpos
 */
struct CQTokenOccurrenceIterator : public CQOccurrenceIterator
{
    uint32_t stride; ///< average number of tokens between occurrences in node
        
    /** default constructor */
    CQTokenOccurrenceIterator(CQueryNode *node_=NULL)
    { assign(node_); };

    /** copy constructor */
    CQTokenOccurrenceIterator(const CQTokenOccurrenceIterator &b)
    { operator=(b); };

    virtual ~CQTokenOccurrenceIterator() {};
    
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
    void bind(CQueryTokenNode *node_, const CQTokenOccurrenceIterator &src, int minOffset, int maxOffset);

    /** assignment operator */
    inline CQTokenOccurrenceIterator& operator=(const CQTokenOccurrenceIterator &b)
    {
        CQOccurrenceIterator::operator=(b);
        stride = b.stride;
        return *this;
    };


    /** node-assignment : inherited */
    inline void assign(CQueryNode *node_)
    {
        CQOccurrenceIterator::assign(node_);
        stride = node && cnt ? std::max((CTokenNo)1, (node->m_Occurrences.back()-node->m_Occurrences.front())/cnt) : 1;
    };

    /* node-assignment operator; wraps assign() */
    inline CQTokenOccurrenceIterator& operator=(CQueryTokenNode *node_)
    {
        assign((CQueryNode*)node_);
        return *this;
    };

    //-- inherited
    //inline bool valid() const
    //inline operator bool() const
        
    /** get size of current occurrence-chunk: override */
    inline size_t chunksize() const
    { return 1; };

    //-- inherited
    //inline CTokenNo tocc(DWORD occ) const

    //-- inherited
    inline CTokenNo tmin() const
    { return node->m_Occurrences[cur]; };

    /* get last token-id of current occurrence (inclusive); assumes iterator is valid: override just returns tmin() */
    inline CTokenNo tmax() const
    { return tmin(); };

    //-- inherited
    //inline CTokenNo tmax_prev() const

    /* increment operator updates the iterator to point to the next available occurrence, or to an invalid state if no such occurrence exists */
    inline void operator++()
    { 
        if (!valid()) return;
        ++cur;
    };

    /* seek iterator to the first occurrence greater-than-or-equal-to Tok */
    inline void seek(const CTokenNo Tok)
    {
        if (valid() && tmin() < Tok) {
            if ((Tok-tmin())/stride > DDC_OCCITER_LB_COEF*log2u32(cnt-cur)) {
                cur = std::lower_bound(node->m_Occurrences.begin()+cur, node->m_Occurrences.end(), Tok) - node->m_Occurrences.begin();
            } else {
                do { ++cur; } while (valid() && tmin() < Tok);
            }
        }
    };

    /* equality operator tests whether calling object and argument \a b point to exactly the same tokens : override */
    inline bool operator==(const CQTokenOccurrenceIterator &b) const
    {
        return node->m_Occurrences[cur] == b.node->m_Occurrences[b.cur];
    };
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
extern void GetWordForms (const MorphLanguageEnum Langua, const std::string& src, std::set<std::string>& WordForms);

#endif /* QUERY_NODE_H */

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
