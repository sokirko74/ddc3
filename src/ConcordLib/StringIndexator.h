//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2014 by Bryan Jurish
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
#ifndef  StringIndexator_h
#define  StringIndexator_h

#include "../ConcordLib/IndexSet.h"

/*! \page index_set_def Index Set Definition
	An index set consists of the list of strings (which are also called "index items") and corresponding 
	lists of their occurrences in the corpus, for example:\n\n
	mother -> 1, 100, 457 \n
	mothered -> 5006\n
	mothering -> 2, 120, 147\n
	...\n
	A string to index can contain any char except \\0.  All strings of one index set are stored in a 
	special file (see CIndexSetForQueryingStage::GetFileNameForInfos() ). \n

	An index set has two names: the short one and the long one (see class CStringIndexSet). \n
	These names can be used interchangeably in queries. \n

	Optionally one index set can have a \ref storage_def "storage". \n
	
	Regarding occurrences, DDC distinguishes  three types of occurrence lists: \n
	 - singleton (which is always in the memory);
	 - \ref long_listdef "short lists";
	 - \ref long_listdef "long lists";
	  
*/

/*! \page storage_def Index Storage Definition
	An index storage is a sequence of integers X1...XN, where N is the number of tokens in 
	the corpus. Each Xi points to an indexed string, for example for the token index it points to a token.
	The order of X1...XN is just the same as	it was in the input corpus. For example using 
	Token index storage DDC can reproduce the whole corpus word by word. By default the first index of the corpus has an index storage,
	for the other indices this option is switched off (see CIndexSetForLoadingStage::m_bUseItemStorage).
*/


/*! \page corpus_file_def Corpus File Definition 
	A list of corpus files (CConcIndexator::m_CorpusFiles) is built upon a list of 
	\ref source_file_def "source files" extracting everything from all source archives. 
	So if a source list doesn't contain archives then the lists of corpus files and source files are
	identical, otherwise it contains also files from archives, which are prefixed by the name of the archive .
	For each corpus file DDC maintains a file \ref break_def "break", quick bibliographical information 
	(class CBiblIndex) and full bibliographical information (class CBibliography).
*/

/*! \page source_file_def Source File Definition 
	Generally a source file is a file, from which DDC reads information to index.  A list of source files is the first input  
  parameter for the indexing process (CConcIndexatorInvoker::BuildIndex).  The second parameter  is a file of 
  options.  Source files are used only during the indexing, and they can be removed afterwards.  The current version supports
  the following types of source files:
	- 1. Plain text (Russian Win-1251, German ISO-8859-1), extension *.txt.
	- 2. Html text (Russian Win-1251, German ISO-8859-1), extension *.html, *.htm.
	- 3. Xml text, extension *.xml.  \n
	
  If a source file is an xml file then DDC extracts some bibliographical information from it (class CBibliography) and stores it as an additional index,
  otherwise the bibliographical index  is empty. For parsing DDC uses TinyXml project (http://sourceforge.net/projects/tinyxml  )  \n
  A source file can be also a tar archive.  \n
  All source files of one DDC index are stored in CConcIndexator::m_SourceFiles .\n
*/

/*! \page long_listdef Long/Short Occurrence list definition 
	A list of occurrences is called "long" if its length is more than OccurBufferSize, otherwise it is 
	called a "short" one. 
*/
/*! \page perdiv_def Period division for long occurrence lists 
	
  For each \ref long_listdef "long list" DDC stores so called \b period \b division, which is a list of 
  integers X[1],X[2], ..X[M], where M is the number of \ref period_def "corpus periods". 
  All occurrences from X[i-1] until X[i] belongs to corpus period i. Generally, using this period division 
  one can quickly get the sublist of occurrences which belongs to the same corpus period. All period divisions
  are written in CIndexSetForQueryingStage::m_EndPeriodOffsets .
*/




/*! \page period_def Corpus period definition
  A "corpus period",  "internal subcorpus" or a "search period" is a \ref break_def "break", which is introduced to restrict 
  the memory usage.  Corpus period always  coincides with a file break. The size of one 
  corpus period is 5000000 by default and can be determined manualy using field "UserMaxTokenCountInOnePeriod"
  in the options file.  While evaluating a query DDC deals only with one corpus period at a time, so 
  DDC applies the input query to each corpus period, and then concatenates the results.  
  Corpus periods  are also used in storing \ref perdiv_def "period divisions"

  \see CStringIndexator::m_SearchPeriods
*/

//const char ddc_archive_stub[] = "ddc_archive_stub";
const char ddc_archive_stub[] = "";

/*!
	CStringIndexator contains a set of all token indices and \ref period_def "corpus periods". 
	It contains also the main path to the project file.
*/
class CStringIndexator {
	
protected:
	
	//! \ref period_def "search periods" of the corpus  
    vector<CTokenNo>	m_SearchPeriods;

	//! register chunk index (chunks:NP, VP etc)	
	bool	RegisterChunkIndex();
    //! return the file name for \ref period_def "search periods"
	string	GetSearchPeriodsFileName() const;
	//! call DestroyIndexSet for all registered indices
	bool	DestroyIndices();
	//!  call ReadFromTheDisk for all registered indices
	bool	ReadIndicesFromTheDisk();
	//!  clear m_Indices
	void	ClearStringIndices();
	//! index one token and its properies (delimited by CConcCommon.h::globalFieldDelimeter)
	bool	IndexOneToken	(const char* Line, const CTokenNo& TokenNo);

public:
	//! where all indices are stored
	string							m_Path;
	//! the registered indices
	vector<CStringIndexSet*>		m_Indices;
	//! the maximal number of index items which can be included in an expansion set of one regular expression
	size_t							m_MaxRegExpExpansionSize;
	//! a quick reference to a chunk index, if CConcIndexator::m_bIndexChunks	is on, otherwise null
	CStringIndexSet*				m_pChunkIndex;
	//! a quick reference to the left bigrams index 
	CStringIndexSet*				m_pLeftBigramsIndex;
	//! a quick reference to the right bigrams index 
	CStringIndexSet*				m_pRightBigramsIndex;
	

	CStringIndexator();
	~CStringIndexator();

	//! read index declarations  from a string and register  them
	bool RegisterStringIndices(string IndicesStr);
	//! set  the path to the indices
	void SetPath(string Path);
	//! return all registered index declarations
	string GetIndicesString() const;
	//! return a pointer to the index by CStringIndexSet::m_Name or CStringIndexSet::m_ShortName
	CStringIndexSet*  GetIndexByNameOrShortName(const string& Name);
	//! return the number of \ref period_def "corpus periods"
	size_t	GetSearchPeriodsCount() const;
	//! get a \ref period_def "corpus period" by an index
	const CTokenNo&  GetSearchPeriod(size_t i) const { return m_SearchPeriods[i]; };
	//! populates \a PeriodOccurrences with all and only those values from \a AllOccurrences which fall into search period \a searchPeriodNo : used by anchor queries
	void RestrictOccurrencesToSearchPeriod(const vector<CTokenNo> &AllOccurrences, vector<CTokenNo> &PeriodOccurrences, size_t searchPeriodNo) const;

	//! call CreateTempFiles for all registered indices
	bool	StartIndexing(string Path);
	//! call DeleteTempFiles for all registered indices
	bool	TerminateIndexing();
	//! final saving all indices to disk (converting temp files to persistent)
	bool	FinalSaveAllIndices(bool bAfterLoading);
	//! unites input index with memory index and clears input load index
	bool	AddInputLoadIndexToMemoryLoadIndex();
	//! unites memory index with main index and clears  memory load index
	bool	AddMemoryLoadIndexToMainLoadIndex();
	//! store memory load index on the disk
	bool	SaveMemoryLoadIndex();
	//! return a pointer to the index by CStringIndexSet::m_Name
	CStringIndexSet*  GetIndexByName(const string& Name);
    //! return the first index that normally contains tokens themselves
    CStringIndexSet* GetTokenIndex();
    //! return the first index that normally contains tokens themselves
    const CStringIndexSet* GetTokenIndex() const;
    //! add "Wi <eos>" bigrams for end of sentence
    void    ProcessBigramBorders (const int BreakCollectionNo, CTokenNo occurrence);
};





#endif
