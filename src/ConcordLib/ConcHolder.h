/*-*- Mode: C++; c-basic-offset: 8; -*- */
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
#ifndef __CConcHolder_H_
#define __CConcHolder_H_


#include "ConcIndexator.h"
#include "ddcRandom.h"

//! save trigger for ConcordPattern application
typedef bool (*SaveTriggerType) (const string&,DWORD LParam);

class CQueryCompiler;


/*! \brief
	Class  CQueryResult contains all information about the first MaxCachedHitsCount hits for 
	the input query. 	Other hits (beyond  MaxCachedHitsCount) are not stored but 
	they can be retrieved on user's demand. 
*/

struct CQueryResult 
{
	//! found hits (not more than MaxCachedHitsCount). 
	vector<CHit>		m_Hits;
	//! words that should be highlighted in hits; m_HighlightOccurs is the concatenation of CQueryNode::m_Occurrences for all \ref period_def "subcorpora"
	vector<CTokenNo>	m_HighlightOccurs;
	//! the number of all found hits (if m_AllHitsCount < MaxCachedHitsCount, then m_Hits.size() == m_AllHitsCount)
	size_t				m_AllHitsCount;
	//! the number of documents, where at least one hit is found
	size_t				m_RelevantDocumentCount;

	mutable vector<BYTE>	m_DebugInfo;
	void				ClearQueryResults();

};




 
/*! Class  CConcHolder is created for querying a corpus. It contains  all user options  for the query process like  m_ResultLimit 
	(the maximal number of hits, which should be output) or m_QueryResultStr(the string representation of the query result).
*/
class CConcHolder : public CConcIndexatorInvoker, 
					public CQueryResult
{
public:
	/*! \brief FormatTypeEnum defines the format of output hits: 
	- DDC_ResultHTML -  output hits  should be written in HTML-format; the tags "<STRONG><FONT COLOR=red>"
						are used for highlighting.
	- DDC_ResultText -  output hits  should be written in plain-format; the string "&&" is used to select the first  highlighting position, "_"  for the following positions
						are used for higlighting.
	- DDC_ResultTable -  output hits  should be written in table-format; there is no highlighting in the string at all, instead of this highligted words are written after the string 
	- DDC_ResultJson -  output hits  should be written in json format
	*/
    enum FormatTypeEnum{DDC_ResultHTML, DDC_ResultText, DDC_ResultTable, DDC_ResultDocIds, DDC_ResultJson};

private:
	//! hit results for the last MaxQueryCacheSize queries 
	map<string, CQueryResult>	m_QueryCache;

	//! a deque for last MaxQueryCacheSize queries; m_Queries.last() is the last given query 
	deque<string>					m_Queries;

	//! current query compiler, for compilation & evaluation of input queries.
	CQueryCompiler*					m_pQueryCompiler;	

	//! pseudo-random number generator
	DDCRandom *m_pRandom;

	//! how much time a query can be processed, by default unlimited (-1) 
	time_t							m_QueryEndTime;

	//! a pointer to the current hits collection
	const vector<CTokenNo>*			m_pBreaks;

	//! the format of query result 
	FormatTypeEnum					m_ResultFormat;

	

	

	//! add a reference to FileNo according to m_ResultFormat
	void	AddFileReference(const long FileNo);
	//! add bibliographical information about Hit to m_QueryResultStr
	void	ShowBibliographyForTextOrHtml(const CHit& Hit, DWORD PageNumber);
	//! add bibliographical information about Hit to m_QueryResultStr under TableFormat
	bool	ShowBibliographyForTable(DWORD PageNumber, const CHit& Hit, const vector<COutputToken>& Tokens);
	//! add hit string built by  Hit to to m_QueryResultStr
	bool	GenerateOneHitString(DWORD PageNumber, const CHit& Hit, const vector<COutputToken>& Tokens);
	//! json: add hit string built by  Hit to to m_QueryResultStr
	bool	GenerateOneHitStringJson(DWORD PageNumber, const CHit& Hit, const vector<COutputToken>& Tokens);
	//! add hit strings [StartBreakNo,  EndBreakNo) without highlighting to m_QueryResultStr
	bool	GetContext(int  StartBreakNo, int  EndBreakNo, const DWORD CurrFileNo, const bool bConvertASCIIToHtmlSymbols, string& Result) const;
	//! append json hit strings [StartBreakNo,  EndBreakNo) without highlighting to js
	bool	GetContextJson(int  StartBreakNo, int  EndBreakNo, const DWORD CurrFileNo, string& js) const;

	//! run query to the corpus, initializes slots from CQueryResult
	DDCErrorEnum	GetAllHits(const string &Query, size_t Limit);

	//! checks if Query  si already in the cache, and if true, it returns its hit results from the cache
	bool	TryToGetFromCache(const string &Query,  DWORD& EndHitNo);

	//! stores Query  to the cache
	void	SaveToCache(const string& Query,  vector<size_t>::const_iterator start, vector<size_t>::const_iterator end);

	//! sets hit type, initializing m_pBreaks
	void	SetHitType();

	//! creates snippets, concatenating contexts of  found words
	bool	GetFileSnippets(const int HitNo, vector<COutputToken>& Tokens)  const;
	//! saves current found hits using SaveTrigger, this funciton is only called from GetOccurrences
	bool	SaveOccurrences(const vector<size_t>& ChunkLengths,  int ContextSize, const vector<CTokenNo>& Occurrences,  const vector<CHit>& Hits, SaveTriggerType SaveTrigger,DWORD LParam);	
	//! initializes Tokens with words of hit BreakNo
	bool	GetTokensFromStorageByBreak(size_t IndexNo, size_t BreakNo, vector<COutputToken>& Tokens) const;
	//! initializes CHit::m_FileNo for each hit of Hits
	void InitFileReferences(vector<CHit>&	Hits) const;
	//! initializes CHit::m_OrderId for each in m_pQueryCompiler->m_pQueryTree->m_Hits
	void	InitOrderIDForHits(const CDDCFilterWithBounds& Filter) const;
	void	InitLessByRank() const;
	void	InitGreaterByRank() const;
	void	InitLessBySize() const;
	void	InitGreaterBySize() const;
	void    InitLessByBigrams() const;
	void	InitRandomSort() const;

public:
	//! initial random-state components for m_pRandom
	unsigned int m_RandomSeed;

	//! a cache for short occurrence lists which is used during iterating through \ref period_def "corpus periods"  and evaluating of the same query
	mutable CShortOccurCacheMap		m_ShortOccurCaches;

	//! the result of the query (its format depends  upon m_ResultFormat)
	string							m_QueryResultStr;

	/*! \brief m_pIndexator is the main (and the only) pointer to corpus indices and break collections. 
	During the querying this pointer is used as a constant. Class CConcHolder  itself is called so because it "holds" this pointer.
	*/
	CConcIndexator*					m_pIndexator;		

	//! the maximal number of hits, which should be output to m_HtmlResult and to m_PlainResult.
	size_t							m_ResultLimit;
	

	//! The index of the current \ref period_def "subcorpora", which is now  being processed
	size_t							m_CurrentSearchPeriodNo;
	//! a delimeter which should be used between hits in m_QueryResultStr in the distributed model
	string							m_AdditionalHitDelimeter;

	CConcHolder();
	~CConcHolder();

	//! GetBreaks returns  the vector of current \ref break_def "breaks" (by m_pBreaks). 
	const vector<CTokenNo>&	GetBreaks	()  const;

	//! return the current format of hit
	FormatTypeEnum	GetResultFormat() const { return m_ResultFormat; };;
	//! return string representation of m_ResultFormat
	string				GetResultFormatStr() const;
	//! set the current format of hit
	void				SetResultFormat(string ResultTypeStr);

	/*! \brief Finds all occurrences of \b Query(only occurrences , not hits!), if \b Query is an atomic query (CQueryNode::m_bAtomic),  
	 For each found  occurrence it calls SaveTrigger, which normally should save all occurrences to a file.
	 This function is called in application ConcordPattern.
	 */
	DDCErrorEnum	GetOccurrences(const string &Query, int ContextSize, SaveTriggerType SaveTrigger,DWORD LParam);
		

	//! SimpleQuery finds hits by the given query. EndHitNo is used as an input/output parameter.
	/*! 
		Let H0...Hn be all hits which match the Query. Then EndHitNo must be 0<= EndHitNo<=n. 
		Let S be min (n, EndHitNo+m_ResultLimit-1).
		The function saves  hits  [EndHitNo, EndHitNo+1,... EndHitNo+s] to result strings.
		After this it makes EndHitNo equal to s+1.
		The function returns errNone, if there is no parse error in the  given query.
	*/
	DDCErrorEnum	SimpleQuery(const string &Query, DWORD& EndHitNo, DWORD& HitsCount);

	//! GetHits makes the same as SimpleQuery does, but without GenerateHitStrings.
	DDCErrorEnum	GetHits(const string &Query,  DWORD& EndHitNo);

	//! initializes m_QueryResultStr using current m_Hits and m_HighlightOccurs
	DDCErrorEnum	GenerateHitStrings(const int StartHitNo);

	//! stores order ids (CHit::m_OrderId) of current m_Hits to a string
	string			GetHitIds()  const;

	//! return true, if the resulting hits should be ordered somehow
	bool			HitsShouldBeSorted() const;

	//! sets timeout for query processing
	void			SetTimeOut(int TimeOut);

	//! clears the query cache
	void			ClearQueryCache();

	//! return the text area to be be searched
	int				GetTextArea() const;

	//! converts a string to a FormatTypeEnum
	static FormatTypeEnum GetResultFormatByString(const string& ResultTypeStr );

	//! adds header and footer to QueryResultStr according to format ResultTypeStr
	static void			DecorateQueryResults(const string& ResultTypeStr, string& QueryResultString);

	//! return true, if the input query contains #less_by_rank or #greater_by_rank
	//! moo: sick, bad, ugly, and wrong!
	bool				HasRankOrderOperator() const;
	//! return the length of break prefix, where DDC should search (#within[sentence, 10])
	int					GetBreakStarterLength() const;

	//! true, if #left or #right operator 
	BigramDirectionEnum     GetBigramsToOrder() const;

	//! moo: build a json context string by parsing delimited token data
	string BuildJsonContextString (const vector<COutputToken>& Tokens, bool doHighlight=true) const;

	//! moo: return a canonical representation of the query string \c Query (implicitly parses)
	string CanonicalQueryString(const string &Query);

	//! moo: set internal random seed to m_RandomSeed+seed1
	void SetRandomSeed(unsigned int seed1=0) const;
};


/*! \brief Class  CConcordance is a modification of CConcHolder, which automates handling of CConcHolder::m_pIndexator.
	CConcordance makes  all  necessary initialization steps in the constructor and the deinitialization steps in the destructor.
*/
class CConcordance : public CConcHolder
{
public:
	//! It shows us that the options were changed.
	bool m_bOptionsWereModified;
		
	CConcordance();
	virtual ~CConcordance();

	//! Loads indices from the disk in order to start querying 
	bool LoadProject(const char* FileName);

	//! Saves the list of  \ref source_file_def "source files" to file *.con 
	bool SaveProject(string FileName);
};



#endif
