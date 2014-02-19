//-*- Mode: C++; c-basic-offset: 8; -*-
/*! \mainpage Dialing DDWS Concordance  (DDC)
	DDC is a tool for linguists to search for a particular construction 
	in a given corpus.  A corpus is defined by a list \ref source_file_def "source files",
	which should be before indexed. The index and query process is governed by file of options. 
*/


#ifndef ConcIndexator_h
#define ConcIndexator_h

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "../ConcordLib/ConcCommon.h"
#include "../ConcordLib/Bibliography.h"
#include "../ConcordLib/StringIndexator.h"
#include "../ConcordLib/HitBorder.h"
#include "../ConcordLib/TermExpander.h"


struct CHighlightTags 
{
	//! true, if members were initialized from string (via CHighlightTags::ReadFromString)
	bool			m_bWasReadFromString;
	//! the start tag which should highlight the first found occurrence in a hit
	string			m_FirstOpener;
	//! the end tag which should highlight the first found occurrence in a hit
	string			m_FirstCloser;
	//! the start tag which should highlight the next found occurrences in a hit (except the first occurrence)
	string			m_RestOpener;
	//! the end tag which should highlight the next found occurrences in a hit (except the first occurrence)
	string			m_RestCloser;
	CHighlightTags();
	bool		ReadFromString(const string& s);
	string		ToString() const;
};


/*!
	CSourceFileHolder holds the list of source files 
*/

class CSourceFileHolder
{
	//! \ref source_file_def "Source files"
	vector<string>					m_SourceFiles;
	bool							m_bModifiedListOfFiles;

public:
	CSourceFileHolder();
	//! Saves the list of  \ref source_file_def "source files" to file *.con 
	bool	SaveSourceFileList(string FileName);

	//! Deletes a \ref source_file_def "source file"
	void	DeleteSourceFile(long ItemNo);

	//! Adds a \ref source_file_def "source file"
	void	AddSourceFile(const char* FileName);

	//! deletes all \ref source_file_def source files
	void DeleteAllSourceFiles();

	//! get the number of source files
	size_t	GetSourceFilesCount()  const;

	//! get the source file by the index
	string  GetSourceFile(size_t FileNo)  const;

	void AddSourceFilesFrom(const CSourceFileHolder& X);

	bool ReadSourceFileList(string FileName);

	//! finds a  \ref source_file_def "source file" which does not  exist, if there is no such file, returns -1
	int FoundNotExistedFile	( ) const;

	
	bool IsModified	( ) const;

};


class CDwdsThesaurus;
/*!
	CConcIndexator is the central class of DDC technology.  The most of its  slots come from the 
	two parent classes:CStringIndexator (indexing tokens and its properties) and CHitBorders (indexing corpus divisions)
	This class also contains a list of \ref corpus_file_def "corpus files" and some
	indexing  and querying options.
*/
class CConcIndexator : public CStringIndexator, public CHitBorders, public CSourceFileHolder
{
	/*! \brief  enum DDCIndexTypeEnum contains index types. Each index type determines DDC indices and
	  break collections. 
	*/
	enum DDCIndexTypeEnum {
		/*! \brief  A type for corpus without annotations, which are written for each word. Fr example the input text can be 
		a plain text. DDC always builds a token index and a file break collection for this index type.
		Optionally DDC can build "Thes" index, "Morph" index and a sentence collection.
		*/
		DWDS_Index, 
		/*! \brief  A type for xml-texts, if their words have predefined and written annotations.  
		DDC always builds a token index and a "MorphPattern" index. It also creates a file and a  sentence break collection
		*/
		MorphXML_Index, 
		/*! \brief  This index type is free and therefore it should be defined in the options file (fields "Indices" and "HitBorders"). The corpus
		should consists of xml-files with a bibliographical header and a body (text). 
		The text is written in CWB format (http://www.ims.uni-stuttgart.de/projekte/CorpusWorkbench/CWBTutorial/cwb-tutorial.pdf).
		The original CWB format was changed in the following way.  Instead of line breaks 
		which are used to delimit records in the input file, DDC uses a special tag CConcCommon.h::PredefinedTableLineTag.
		This is done because line breaks are not preserved by the XML-parser.
		*/
		Free_Index
	};

	//! a table of character properties for regular expressions which depend on CConcIndexator::m_Language
	vector<BYTE>					m_PcreCharacterTables;

	//! Enables using "<p>" tag as a paragraph delimiter
	bool							m_bUseParagraphTagToDivide;
	//! if m_bEmptyLineIsSentenceDelim is on, every empty line in the input file  is considered to be the end of the sentence.
	bool							m_bEmptyLineIsSentenceDelim;
	//! if m_bUseIndention is on, the  program tries to find paragraphs using indentions 
	bool							m_bUseIndention;
	//! if m_bDwdsCorpusInterface is on, the program outputs results in DWDS format
	bool							m_bDwdsCorpusInterface;
	//! if m_bGutenbergInterface is on, the program outputs results in a format of Gutenberg project
	bool							m_bGutenbergInterface;
	//! should  we switch off context operator (#Cntxt) due copyright
	bool							m_bNoContextOperator;
	//!	The maximal number of occurrences in one \ref period_def "subcorpora" (defined by user)
	DWORD							m_UserMaxTokenCountInOnePeriod;	
	bool							m_bUserMaxTokenCountInOnePeriod;
	//! Enables indexing and querying using  DWDS Thesaurus
	bool							m_bUseDwdsThesaurus;
	//! Should we show bibliography of the hits instead of filename
	bool							m_bOutputBibliographyOfHits;
	//! Enables  indexing all punctuation marks 
	bool							m_bIndexPunctuation;	
	//!  the type of index
	DDCIndexTypeEnum				m_IndexType;

	string							m_InternetPathPrefix;
	string							m_LocalPathPrefix;
	string							m_CommonFilePrefix;


	bool	IndexTextOrHtmlFile	(	CGraphmatFile* piGraphmat, string FileName, const char* pFileBuffer, const CDwdsThesaurus* pDwdsThesaurus,  CTokenNo& NewCorpusEndTokenNo,string& strError); 
	bool	IndexMorphXml	(string FileName, const char* pFileBuffer, CTokenNo& NewCorpusEndTokenNo, string& strError); 
	bool	IndexTable(string FileName, const char* pFileBuffer, 	CTokenNo& NewCorpusEndTokenNo,	string& strError);
	bool	IndexOneTableTextArea(const string& Text, const CPageNumber& StartPageFromHeader, size_t& page_breaks_count, CTokenNo& NewCorpusEndTokenNo,	string& strError);

	void	AssertHasPath() const;
	string	GetBiblIndexFileName() const;
	string	GetBiblFileName() const;
	

	//! saves options to a string 
	string SaveOptionsToString()  const;
	//! loads options from a string 
	bool	LoadOptionsFromString(string Options);
	//!  graphematical definition of a token for DWDSIndex
	bool	IsDWDSToken (const CGraphmatFile*	piGraphmat, long GraLine)	 const;
	//! checks if X has the same option 
	bool	HasEqualOptions(const CConcIndexator&  X) const;

	//! return a string representation of index type
	const char* GetIndexTypeStr () const;
	//! read the index type from a string
	bool		ReadIndexTypeFromStr (const string& s);
	bool		LoadXmlFile(string FileName, const char* pFileBuffer, CGraphmatFile* piGraphmat, CBibliography& Bibl, string& strError);
	bool		LoadFileIntoGraphan(string FileName,  const char* pFileBuffer,	CGraphmatFile* piGraphmat, CBibliography& Bibl, string& strError);
    void        InitDefaultOptions();
public:
	//! the language of the corpus
	MorphLanguageEnum				m_Language;
	//! Enables the index  of morph patterns 
	bool							m_bIndexMorphPatterns;
	//! Enables indexing and querying using  chunks
	bool							m_bIndexChunks;
	//! if true, then the default search is case sensitive
	bool							m_bCaseSensitive;
	//! if true, then DDC always calculates the number of documents, where at lease one hit is found
	bool							m_bShowNumberOfRelevantDocuments;
	//! prohibits sentence break collection  under DWDS_Index or MorphXML_Index
	bool							m_bQueryOnlyFiles;
	//! sets that index should be archived  under DWDS_Index or MorphXML_Index
	bool							m_bArchiveIndex;
	//! if true, CConcIndexatorInvoker skips source documents with errors 
	bool						    m_bResumeOnIndexErrors;
	//! \ref corpus_file_def "Corpus files"
	vector<string>					m_CorpusFiles;
	//! masked (deleted corpus files)
	set<size_t>					    m_MaskedFiles;
	//!  a member which holds a index for bibliographical information
	CConcXml						m_Bibl;

	//! highlighting tags for CConcHolder::m_ResultFormat == DDC_ResultHTML
	CHighlightTags					m_HtmlHighlighting; 

	//! highlighting delimeters for CConcHolder::m_ResultFormat == DDC_ResultText
	CHighlightTags					m_TextHighlighting; 

	//! highlighting delimeters for CConcHolder::m_ResultFormat == DDC_ResultTable
	CHighlightTags					m_TableHighlighting; 

	//! if true, then no default lexical expansion fo querz words occurs 
	bool							m_bDisableDefaultQueryLexicalExpansion; 
	//! the size of the left context of the highlighted  words in document search 
	int								m_LeftKwicContextSize;
	//! the size of the right context of the highlighted  words in document search 
	int								m_RightKwicContextSize;
	//! the maximal number of kwic lines in file   snippets
	int								m_NumberOfKwicLinesInSnippets;
	//! the parameter for TfIdf ranking
	double							m_TfIdfRank;
	//! the parameter for Near ranking
	double							m_NearRank;
	//! the parameter for Position ranking
	double							m_PositionRank;
	//! delimiter to use between token index fields in output
	string							m_InterpDelimiter;
	//! delimiter to use between tokens in output
	string							m_TokenDelimiter;

	//! whether to assume indexed data is utf8 encoded (default=no)
	bool							m_Utf8;

	//! potentially unsafe queries will throw an exception unless this is true (default=false)
	bool m_AllowUnsafeQueries;

	//! indices to show for Free_Index
	vector<size_t>					m_IndicesToShow;

	//! moo: timestamp of project *._con file
	time_t m_Timestamp;

	//! term expansion dispatcher; should define at least an entry for "default"
	TxDispatcher m_Txd;

	CConcIndexator();
	~CConcIndexator();

	
	/*
	//! return tables of character properties for regular expressions for the current m_Language
	//const vector<BYTE>& GetRegExpTables() const { if (m_Utf8) return NULL; return m_PcreCharacterTables; };
	const BYTE* GetRegexTables() const { if (m_Utf8) return NULL; return m_PcreCharacterTables.data(); };

	//! return default pcre regex options
	const pcrecpp::RE_Options GetRegexOptions() const { if (m_Utf8) return pcrecpp::UTF8(); return pcrecpp::RE_Options(); }
	*/
	//! return default pcre regex options
	RML_RE::Options GetRegexOptions() const
	{
		if (m_Utf8)
			return RML_RE::Options(pcrecpp::UTF8(), NULL);
		else
			return RML_RE::Options(pcrecpp::RE_Options(), m_PcreCharacterTables.data());
	};

	//! return true, if DDC outputs results in DWDS format
	bool IsDwdsCorpusInterface() const { return m_bDwdsCorpusInterface; };
	//! return true, if DDC outputs results in Gutenberg project format
	bool IsGutenbergInterface() const { return m_bGutenbergInterface; };
	//! return true, if query context operator (#Cntxt) is switched off 
	bool HasContextOperator() const { return !m_bNoContextOperator; };
	//! return true, if DWDS thesaurus is enabled (index "Thes")
	bool UseDwdsThesaurus() const { return m_bUseDwdsThesaurus; };
	//! return true, if DDC should output bibliographical information  for hits instead of \ref corpus_file_def "corpus file names"
	bool OutputBibliographyOfHits() const { return m_bOutputBibliographyOfHits; };
	//! get an HTML formatted reference to a \ref corpus_file_def "corpus file" 
	string GetHtmlReference(size_t posFile) const;
	//! get a reference to a \ref corpus_file_def "corpus file" without the common left prefix 
	string GetShortFilename(size_t posFile) const;
	//! get file name for storing \ref corpus_file_def "corpus file" names
	string	GetFileNameForCorpusFileNames() const;
    //! get file name for masked files
    string	GetFileNameForMaskedFiles() const;

    //! parse a delimited token into fields by splitting on m_InterpDelimiter
    vector<string> GetTokenFields(const COutputToken &tok);
    
	

	//! initializes graphematics using current options
	void	InitGraphanProperties (CGraphmatFile* piGraphmat) const;
	//! true, when the corpus index was stored to the disk
	bool	WasIndexed() const;


	//! load list of \ref source_file_def "source files" and parses option file (*.opt)
	bool	LoadSourceFilesAndOptions(string FileName);

	//! load list of \ref corpus_file_def "corpus files" (*.con)
	bool	LoadCorpusFiles();

    //! load list of masked (deleted)\ref corpus_file_def 
	bool	LoadMaskedFiles();
    
	//! saves options to option file (*.opt)
	bool	SaveOptions(string FileName) const;

	//! saves corpus file list  (*._con)
	bool	SaveCorpusFileList() const;
	
	//! loads  everything
	bool	LoadProject(string FileName);

	//! update m_Timestamp to mtime of Filename if it is newer than the current m_Timestamp; \returns new m_Timestamp
	time_t UpdateTimestamp(const char *filename);

	//! dump loaded metadata to a stream (JSON)
	void DumpBibliography(FILE *f=stdout) const;

	//! dump file metadata to a string (JSON)
	string DumpFileBibliography(DWORD FileNo) const;

	// ==========================
	// ====== Indexing Stage
	// ==========================

	//! begins indexing 
	bool	StartIndexing();
	//! destroy all index files
	bool	DestroyIndex();
	//! finishes indexing (normal way)
	bool	NormalEndIndexing();
	//! terminates indexing (for exceptions)
	bool	TerminateIndexing();
	//!  index one file according to m_IndexType
	bool	IndexOneFile(CGraphmatFile* piGraphmat, string FileName, const char* pFileBuffer, const CDwdsThesaurus* pDwdsThesaurus,  CTokenNo& CorpusEndTokenNo,string& strError);
	//! finds all \ref period_def "subcorpora"
	void	CalculateSearchPeriods	(DWORD MaxTokenCountInOnePeriod);
	//! creates new concordance as unionof two concordances
	bool	CreateAsUnion(const CConcIndexator&  _X1, const CConcIndexator&  _X2);
	//! creates morphology index
	bool	CreateMorphIndex();
	//! returns the size of one \ref period_def "subcorpus"
	DWORD GetMaxTokenCountInOnePeriod() const;
	//! return a string representation of a set of token properties (in the format which is used in the index)
	string			GetIndexItemSetByVectorString (const vector<string>& TokenProperties, bool bRegexp );

};


//! CConcIndexatorInvoker is a class for invoking an  index process.
/*!
	This class was established to start, to stop and to monitor an indexing process. 
	To start it  a user should call function CConcIndexatorInvoker::BuildIndex. 
	To stop the process a user should set CConcIndexatorInvoker::m_bStoppedByUser to true.
*/
class CConcIndexatorInvoker
{
	string	GetTimeStatisticsFileName(string Path) const;
	string	GetErrorLogFileName(string Path) const;
	void	WriteTimeStatistics	(const CConcIndexator& Indexator, DWORD CorpusEndTokenNo, DWORD MaxTokenCountInOnePeriod) const;
	bool	FinalizeIndex	(CConcIndexator& Indexator, DWORD CorpusEndTokenNo, DWORD MaxTokenCountInOnePeriod) const;
	bool	BuildOnlyMorphIndex	(string ProjectFile) const;
public:
	//! if true, CConcIndexatorInvoker tries to stop indexing
	bool						    m_bStoppedByUser;
	//! if true, indexing is on
	bool							m_bCorporaProcessing;
	//! if true, then BuildIndex should only rebuild MorphPattern index
	bool							m_bOnlyReindexMorphology;
	//! if true, then there is no initial checking whether the \ref source_file_def "source files" exist 
	bool							m_bSkipInitialFileChecking;
	
	//! the last message from indexing process
	mutable string					m_CurrMessage;

	//! should  DDC  send all messages to stdout
	bool							m_bStdout;

	//! the index of the currently processing \ref source_file_def "source file"
	int								m_CurrentSourceFileNo;

	//! the number of files to index
	int								m_SourceFilesNumber;

	//! the name of file
	string							m_CurrentSourceFileName;

	//! a slot to gather profiling information  for loading stage
	mutable CMyTimeSpanHolder				m_Profiler;

	CConcIndexatorInvoker ();

	//! outputs a message to stdout or to GUI
	void	SetCurrMessage( string  Message) const;

	//! builds index files for project ProjectFile
	bool	BuildIndex(string ProjectFile);
};


//-- formerly "private" method from ad-hoc ConcordQuery.cpp moved here
extern void SortOccurrences (vector<CTokenNo>& occurrences, size_t SortChunkCount);

#endif 
