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
//! a globally defined left bigrams index name 
const string LeftBigramsIndexName = "left";
//! a globally defined right bigrams index name 
const string RightBigramsIndexName = "right";
//! a globally defined break collection name for \ref corpus_file_def "corpus files"
const string PredefinedFileBreakName = "file";
//! a globally defined break collection name for \ref text areas
const string PredefinedTextAreaBreakName = "textarea";

//! integer type CTokenNo is used to  refer an index of a token in the corpus
typedef	DWORD CTokenNo;

//!  MaxShortOccurCacheSize is the upper bound  of  CShortOccurCache::m_Data.size() It is introduced to restrict memory usage.
const size_t MaxShortOccurCacheSize = 1000000;



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
	//! no sort operators, only filtering
	NoSort = 0,
	//! sort by the issue date(increasing) 
	LessByDate = 1,
	//! sort by the issue date (decreasing) 
	GreaterByDate = 2,
	//! sort by the size of the hit in tokens (increasing) 
	LessBySize = 3,
	//! sort by the size of the hit in tokens (decreasing) 
	GreaterBySize = 4,
	//! sort by a free bibliographical field(increasing) 
	LessByFreeBiblField = 5,
	//! sort by a free bibliographical field(decreasing) 
	GreaterByFreeBiblField = 6,
	//! sort by document  (increasing) 
	LessByRank = 7,
	//! sort by document rank (decreasing) 
	GreaterByRank = 8,
	//! sort by document rank (decreasing) 
	LessByLeftContext = 9,
	//! sort by document rank (decreasing) 
	LessByRightContext = 10,
	//! sort by random key
	RandomSort = 11,
	//! end-of-enum sentinel
	HitSortsCount = 12
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
	//!  the name of free bibliographical field 
	string			m_FreeBiblAttribName;

	//!  true, if DDC  should use CDDCFilterWithBounds::m_SatisfiedValues, false, if DDC should use CDDCFilterWithBounds::m_LevelStart and CDDCFilterWithBounds::m_LevelEnd slots
	bool			m_bRegExp;
	//!  the lower bound of the filter (by default INT_MIN), valid only m_bRegExp==false
	int				m_LevelStart;
	//!  the upper bound of the filter (by default INT_MAX), valid only m_bRegExp==false
	int				m_LevelEnd;
	//!  the possible values for this bibliographical field,  valid only m_bRegExp==true
	set<int>		m_SatisfiedValues;  

	CDDCFilterWithBounds() 
	{
		m_bRegExp = false;
		m_FilterType = HitSortsCount;
		m_LevelStart = INT_MIN;
		m_LevelEnd = INT_MAX; 
	}

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
	//! a value which is used to sort and to filter hits, which is calculated by an instance of CDDCFilterWithBounds
	int		m_OrderId;
	//! the index of \ref corpus_file_def "coprus file", where this hit is found, it is equal to  m_BreakNo if user searches within files
	DWORD	m_FileNo;
	//! the string which displays how the rank was calculated
	size_t	m_DebugRankNo;

	CHit(DWORD BreakNo) : m_BreakNo(BreakNo), m_OrderId(0) {};

	bool operator < (const CHit& X) const 
	{
		return  m_OrderId < X.m_OrderId;
	};
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

enum BigramDirectionEnum{
     bdDontUseBigrams,
     bdLeftBigram,
     bdRightBigram
};

#endif
