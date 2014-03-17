//-*- Mode: C++; c-basic-offset: 8; -*-
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
#ifndef __ConcCommon_H_
#define __ConcCommon_H_

/*! \file ConcCommon.h
    \brief A file for globally defined constants and classes.
*/




#include "../common/utilit.h"
#include "list"
#include "limits.h"


#include "../GraphanLib/GraphmatFile.h"
#include "../LemmatizerLib/Lemmatizers.h"

#include "../AgramtabLib/EngGramTab.h"
#include "../AgramtabLib/RusGramTab.h"
#include "../AgramtabLib/GerGramTab.h"
#include "../common/DDC_common.h"
#include "../tinyxml/tinyxml.h"

#include "../ConcordLib/CCurl.h"

//! global intialization
inline void ddcInitGlobal(void) {
  ddcInitLocale();
  ddcInitCurl();
}

//! a globally defined delimeter, which is used to delimit fields in one record (the first field is always a token)
const char globalFieldDelimeter = '\t';
//! a globally defined xml-tag, which is used to separate records if CConcIndexator::m_IndexType is Free_Index
const string PredefinedTableLineTag = "l";
//! a globally defined index name for chunks
const string ChunkIndexName = "chunk";
//! a globally defined break collection name for \ref corpus_file_def "corpus files"
const string PredefinedFileBreakName = "file";
//! a globally defined break collection name for \ref text areas
const string PredefinedTextAreaBreakName = "textarea";

//! integer type CTokenNo is used to  refer an index of a token in the corpus
typedef	DWORD CTokenNo;

//!  MaxShortOccurCacheSize is the upper bound  of  CShortOccurCache::m_Data.size() It is introduced to restrict memory usage.
const size_t MaxShortOccurCacheSize = 1000000;

//! maximum length of string sort-keys passed from subcorpus servers to distributed server, including terminating NUL
//! (see CConcHolder::GetHitIds() and CDDCServerListenHost::GetFirstHitsFromCorpora())
#define DDC_SORTKEY_MAXLEN 256

/*!  CShortOccurCache  is a structure which holds all found occurrences indexed by an index item No,
 if the number of  occurrences for this index item is not greater than OccurBufferSize. This structure can take an advantage only if there are many \ref period_def "corpus periods",
 otherwise it can even slow the program. But if there are many \ref period_def "corpus periods", then having initialized
 this cache for  the first \ref period_def "period", the program can read from now on occurrences directly from the memory.
 CShortOccurCache is  used only for one query at a time, so it is cleared in the very beginning of CConcHolder::GetAllHits.
 
*/

class CShortOccurCache 
{
	//! the structure holds a pointer to a vector of occurrences and its size
	struct CDataReference 
	{
		// the start index of subvector in m_OccurrencesBody
		size_t m_VectorStartOffset;
		// the length of subvector in m_OccurrencesBody
		size_t m_VectorLength;


		CDataReference (size_t VectorStartOffset, size_t VectorLength)
		{
			m_VectorStartOffset = VectorStartOffset;
			m_VectorLength = VectorLength;
		};
	};
	//!this map contains a relation from index item No to the address of its occurrences
	//map<CTokenNo, CDataReference>	m_IndexItemNo2Occurrences;
	vector <CDataReference>	m_IndexItemNo2Occurrences;

	//!this vector contains all occurrences for this cache
	vector<CTokenNo>			m_OccurrencesBody;
public:
	void				Clear();
	size_t				AddNewIndexItemNoToCache(const CTokenNo* pStart, const CTokenNo* pEnd );
	const CTokenNo*			GetOccurrencesFromCache(const int CacheId, DWORD& Length) const;
	bool				CouldContainMore() const;

};

/*!  HitSortEnum
This enum defines the types of all possible orders which can be apllied to an output hit set. 
*/
enum HitSortEnum {
	//! no sort operators, only filtering (used by #has_field[])
	NoSort = 0,
	//! sort by the issue date (ascending) 
	LessByDate = 1,
	//! sort by the issue date (descending)
	GreaterByDate = 2,
	//! sort by the size of the hit in tokens (ascending) 
	LessBySize = 3,
	//! sort by the size of the hit in tokens (descending) 
	GreaterBySize = 4,
	//! sort by a free bibliographical field (ascending) 
	LessByFreeBiblField = 5,
	//! sort by a free bibliographical field (descending) 
	GreaterByFreeBiblField = 6,
	//! sort by document (ascending) 
	LessByRank = 7,
	//! sort by document rank (descending) 
	GreaterByRank = 8,
	//! sort by match context (ascending) 
	LessByContext = 9,
	//! sort by match context (descending) 
	GreaterByContext = 10,
	//! sort by left context (ascending) 
	LessByLeftContext = 11,
	//! sort by left context (descending) 
	GreaterByLeftContext = 12,
	//! sort by right context (ascending) 
	LessByRightContext = 13,
	//! sort by right context (descending) 
	GreaterByRightContext = 14,
	//! sort by random key
	RandomSort = 15,
	//! end-of-enum sentinel
	HitSortsCount = 16
};

/*! symbolic hit sort order constants */
enum HitSortOrderEnum {
	hsoDescending = -1,
	hsoNone = 0,
	hsoAscending = 1
};

/*! symbolic names for HitSortEnum, for debugging */
static const char *HitSortEnumNames[HitSortsCount] =
	{
	"NoSort",
	"LessByDate",
	"GreaterByDate",
	"LessBySize",
	"GreaterBySize",
	"LessByFreeBiblField",
	"GreaterByFreeBiblField",
	"LessByRank",
	"GreaterByRank",
	"LessByContext",
	"GreaterByContext",
	"LesaByLeftContext",
	"GreaterByLeftContext",
	"LesaByRightContext",
	"GreaterByRightContext",
	"RandomSort"
	};

/*! type for hit sort-keys and/or result filtering;
 *  new in v2.0.19
 */
struct CHitSortKey {
	//! primary integer sort key; formerly CHit::m_OrderId, CDDCFilterWithBounds.m_LevelStart|m_LevelEnd
	int	i;

	//! secondary sort key, new for v2.0.19
	string	s;

	//! default constructor
	CHitSortKey(int i_=0) : i(i_)
	{};

	//! constructor given integer and string
	CHitSortKey(int i_, const string& s_) : i(i_), s(s_)
	{};

	//! clear key
	inline void clear()
	{ i=0; s.clear(); };

	//! less-than comparison operator; as for std::pair<i,s>
	inline bool operator< (const CHitSortKey &x) const
	{ return (i < x.i) || (i==x.i && s < x.s); };

	//! greater-than comparison operator
	inline bool operator> (const CHitSortKey &x) const
	{ return (i > x.i) || (i==x.i && s > x.s); };

	//! assignment given integer
	inline void assign(int i_)
	{ i=i_; s.clear(); };

	//! assignment given integer + string
	inline void assign(int i_, const string &s_)
	{ i=i_; s=s_; };

	//! assignment to std::pair
	inline void operator= (const std::pair<int,string>& p)
	{ i=p.first; s=p.second; };

	//! assignment to integer, alias for assign(i,"")
	inline void operator= (int i_)
	{ i=i_; s.clear(); };

	//! assignment to string, alias for assign(0,s)
	inline void operator= (const string &s_)
	{ i=0; s=s_; };
};

/*! This structure describes a filter which can be applied to the result hit set. For example, for 
filter operator "#less_by_size[5,10]" the slots would have the following values: \n
	- m_FilterType =  LessBySize \n
	- m_LevelStart =  5 \n
	- m_LevelEnd =  10+1 \n

*/
struct CDDCFilterWithBounds 
{
	//!  the type of the filter
	HitSortEnum		m_FilterType;

	//! the name of the free bibliographical field for bibliographic filters (#asc[FIELD], #desc[FIELD], #has[FIELD]),  or the name of a token field for context-sort filters (#left, #right, etc)
	//! \note formerly m_AttrName
	string			m_AttrName;

	//! \li true if DDC should use CDDCFilterWithBounds::m_SatisfiedValues
	//! \li false if DDC should use range defined by CDDCFilterWithBounds::m_LevelStart and CDDCFilterWithBounds::m_LevelEnd slots
	//! (formerly m_bRegExp)
	bool			m_bSet;
  	bool			m_bNegated;  ///< ... for negated filters

	//!  offset from matched token for context-sort operators
	int m_ContextOffset;

	//!  the lower bound of the filter (by default (INT_MIN,"")), valid only if m_bSet==false; formerly int m_LevelStart
	CHitSortKey m_KeyLo;

	//!  the upper bound of the filter (by default (INT_MAX,"")), valid only if m_bSet==false; formerly int m_LevelEnd
	CHitSortKey m_KeyHi;

	//!  the possible (integer) values for this bibliographical field,  valid only if m_bSet==true
	set<int> m_SatisfiedValues;  

	inline void clear()
	{
		m_SatisfiedValues.clear();
	};

	//! returns integer sort order as a HitSortOrderEnum (-1:descending, 0:none, 1:ascending)
	inline HitSortOrderEnum SortOrder() const {
		switch (m_FilterType) {
		case GreaterByDate:
		case GreaterByRank:
		case GreaterBySize:
		case GreaterByFreeBiblField:
		case GreaterByContext:
		case GreaterByLeftContext:
		case GreaterByRightContext:
			return hsoDescending;
		case NoSort:
			return hsoNone;
		default:
			return hsoAscending;
		};
	};

	CDDCFilterWithBounds()
		: m_bSet(false),
		  m_bNegated(false),
		  m_FilterType(NoSort),
		  m_ContextOffset(0),
		  m_KeyLo(INT_MIN),
		  m_KeyHi(INT_MAX)
	{};
};

/*! CHit is a structure that holds one found hit and its properties. The calculation of its slots 
starts in CQueryNode class  and its inheritors and proceeds  in CConcHolder class.
*/
struct CHit 
{
	//! the index of the \ref break_def "break", which this hit represents (in the break collection CConcHolder::GetBreaks)
	DWORD	m_BreakNo;
	//! the end offset of token occurrences to be highlighted in CQueryNode::m_Occurrences and later in CConcHolder::m_HighlightOccurs
	DWORD	m_HighlightOccurrenceEnd;
	//! the index of \ref corpus_file_def "coprus file", where this hit is found, it is equal to  m_BreakNo if user searches within files
	DWORD	m_FileNo;
	//! the string which displays how the rank was calculated
	size_t	m_DebugRankNo;

	//! key for sorting and/or filtering, which is calculated either by an instance of CDDCFilterWithBounds or by CConcHolder.
	//! formerly m_OrderId
	CHitSortKey m_SortKey;

	CHit(DWORD BreakNo) : m_BreakNo(BreakNo), m_SortKey(0) {};
};



//!  a type for mappping an index item no to its \ref perdiv_def "period division"
typedef map<DWORD, vector<DWORD> > PeriodsDivisionMap;

//!  a type for index string to its occurrences
typedef map<string,CShortOccurCache> CShortOccurCacheMap;

//!  a type for holding occurrences during reading from the disk
typedef vector<CTokenNo> COccurrBuffer;

//! a delimiter between morphological annotations
const string MorphAnnotationsDelim = "#";
//! a regular expression, which passes everything within one morphological annotation
const string MorphAnnotationsDelimRegExp = "[^#]*";

//! initializes morphology dictionaries
extern bool InitConcordDicts();
//! deletes morphology dictionaries
extern void FreeConcordDicts();
//! return a morphology dictionary by a language indentifier
extern const CLemmatizer* GetLemmatizerByLanguage (MorphLanguageEnum Langua);
//! return a grammatical table  by a language indentifier
extern const CAgramtab* GetGramtabByLanguage (MorphLanguageEnum Langua);
//! write a dump message  to a log file
extern void concord_daemon_log(const string&  t);

//! return a string representation of a DDC error
//extern const char* GetDDCErrorString(DDCErrorEnum ErrorCode);

//! bool: whether to output all log messages on stderr as well
extern bool concord_daemon_log_stderr;

#endif
