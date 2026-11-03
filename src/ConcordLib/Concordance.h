//-*- Mode: C++ -*-

//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2019 by Bryan Jurish
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

/*! \mainpage Dialing DDWS Concordance  (DDC)
  DDC is a tool for linguists to search for a particular construction 
  in a given corpus.  A corpus is defined by a list \ref source_file_def "source files",
  which should be before indexed. The index and query process is governed by file of options. 
*/


#ifndef Concordance_h
#define Concordance_h


#include "ConcCommon.h"
#include "ConcXml.h"
#include "StringIndexator.h"
#include "HitBorder.h"
#include "TermExpander.h"
#include "../CommonLib/ddcCorpusList.h"


struct CHighlightTags {
    //! true, if members were initialized from string (via CHighlightTags::ReadFromString)
    bool m_bWasReadFromString;
    //! the start tag which should highlight the first found occurrence in a hit
    std::string m_FirstOpener;
    //! the end tag which should highlight the first found occurrence in a hit
    std::string m_FirstCloser;
    //! the start tag which should highlight the next found occurrences in a hit (except the first occurrence)
    std::string m_RestOpener;
    //! the end tag which should highlight the next found occurrences in a hit (except the first occurrence)
    std::string m_RestCloser;

    CHighlightTags();

    bool ReadFromString(const std::string &s);

    std::string ToString() const;
};


/*!
  CSourceFileHolder holds the list of source files 
*/

class CSourceFileHolder {
protected:
    //! \ref source_file_def "Source files"
    std::vector<std::string> m_SourceFiles;
    bool m_bModifiedListOfFiles;

public:
    CSourceFileHolder();

    //! Saves the list of  \ref source_file_def "source files" to file *.con
    bool SaveSourceFileList(std::string FileName);

    //! Deletes a \ref source_file_def "source file"
    void DeleteSourceFile(long ItemNo);

    //! Adds a \ref source_file_def "source file"
    void AddSourceFile(const char *FileName);

    //! deletes all \ref source_file_def source files
    void DeleteAllSourceFiles();

    //! get the number of source files
    //! \note this may greater than the actual number of file-breaks as indexed by the HitBorder class,
    //!  in particular if empty files were ignored during indexing.
    size_t GetSourceFilesCount() const;

    //! get the source file by the index
    std::string GetSourceFile(size_t FileNo) const;

    void AddSourceFilesFrom(const CSourceFileHolder &X);

    void ReadSourceFileList(std::string FileName);

    //! finds a  \ref source_file_def "source file" which does not  exist, if there is no such file, returns -1
    int FoundNotExistedFile() const;


    bool IsModified() const;

};


class CDwdsThesaurus;

/* CIndexDumpFormat : enum for index-dump formats */
typedef enum CIndexDumpFormatE {
    idfUnknown,
    idfJson,
    idfTabs,
    idfTabsStream
} CIndexDumpFormat;

/* CMaskedFileSet : type for CConcIndexator::m_MaskedFiles */
typedef std::set<CFileNo> CMaskedFileSet;

/*!
  CConcordance is the central class of DDC technology.  The most of its  slots come from the
  two parent classes:CStringIndexator (indexing tokens and its properties) and CHitBorders (indexing corpus divisions)
  This class also contains a list of \ref corpus_file_def "corpus files" and some
  indexing  and querying options.
*/
class CConcordance : public CStringIndexator, public CHitBorders, public CSourceFileHolder {


    //! a table of character properties for regular expressions which depend on CConcIndexator::m_Language
    std::vector<BYTE> m_PcreCharacterTables;

    //! if m_bDwdsCorpusInterface is on, the program outputs results in DWDS format
    bool m_bDwdsCorpusInterface;
    //! if m_bGutenbergInterface is on, the program outputs results in a format of Gutenberg project
    bool m_bGutenbergInterface;
    //! should  we switch off context operator (#Cntxt) due copyright
    bool m_bNoContextOperator;
    //! Should we show bibliography of the hits instead of filename
    bool m_bOutputBibliographyOfHits;

    std::string m_InternetPathPrefix;
    std::string m_LocalPathPrefix;
    std::string m_CommonFilePrefix;




    std::string GetBiblIndexFileName() const;

    std::string GetBiblFileName() const;



    //! checks if X has the same option
    bool HasEqualOptions(const CConcordance &X) const;

    //! return a string representation of index type
    const char *GetIndexTypeStr() const;

    //! read the index type from a string
    bool ReadIndexTypeFromStr(const std::string &s);

    //! dump file data to a file (tabs)
    void DumpFileIndexTabs(uint32_t FileNo, FILE *f) const;

protected:
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
        Free_Index,
        /*! \brief see http://odo.dwds.de/~moocow/software/ddc/ddc_tabs.html
         *
         */
        TabFormat_Index

    };
    //!  the type of index
    DDCIndexTypeEnum m_IndexType;
    //! Enables  indexing all punctuation marks
    bool m_bIndexPunctuation;
    //! Enables using "<p>" tag as a paragraph delimiter
    bool m_bUseParagraphTagToDivide;
    //! if m_bEmptyLineIsSentenceDelim is on, every empty line in the input file  is considered to be the end of the sentence.
    bool m_bEmptyLineIsSentenceDelim;
    //! if m_bUseIndention is on, the  program tries to find paragraphs using indentions
    bool m_bUseIndention;
    //! The maximal number of occurrences in one \ref period_def "subcorpora" (defined by user)
    uint32_t m_UserMaxTokenCountInOnePeriod;
    //! The maximal number of occurrences in the input load index,  by default 400000
    uint32_t m_UserMaxInputLoadIndexSize;
    //! Enables indexing and querying using  DWDS Thesaurus
    bool m_bUseDwdsThesaurus;

    void AssertHasPath() const;

    //! loads options from a string
    void LoadOptionsFromString(std::string Options);

    void InitDefaultOptions();
    //! saves options to a string
    std::string SaveOptionsToString() const;

public:
    //! the language of the corpus
    MorphLanguageEnum m_Language;
    //! Enables the index  of morph patterns
    bool m_bIndexMorphPatterns;
    //! Enables indexing and querying using  chunks
    bool m_bIndexChunks;
    //! if true, then the default search is case sensitive
    bool m_bCaseSensitive;
    //! if true, then DDC always calculates the number of documents, where at lease one hit is found
    bool m_bShowNumberOfRelevantDocuments;
    //! prohibits sentence break collection  under DWDS_Index or MorphXML_Index
    bool m_bQueryOnlyFiles;
    //! sets that index should be archived  under DWDS_Index or MorphXML_Index
    bool m_bArchiveIndex;
    //! if true, CConcIndexatorInvoker skips source documents with errors
    bool m_bResumeOnIndexErrors;

    //! \ref corpus_file_def "Corpus files"
    ddcCorpusList<> m_CorpusFiles;

    CMaskedFileSet m_MaskedFiles;

    //!  a member which holds a index for bibliographical information
    CConcXml m_BiblIndex;

    //! highlighting tags for CConcHolder::m_ResultFormat == DDC_ResultHTML
    CHighlightTags m_HtmlHighlighting;

    //! highlighting delimeters for CConcHolder::m_ResultFormat == DDC_ResultText
    CHighlightTags m_TextHighlighting;

    //! highlighting delimeters for CConcHolder::m_ResultFormat == DDC_ResultTable
    CHighlightTags m_TableHighlighting;

    //! if true, then no default lexical expansion fo querz words occurs
    bool m_bDisableDefaultQueryLexicalExpansion;
    //! the size of the left context of the highlighted  words in document search
    int m_LeftKwicContextSize;
    //! the size of the right context of the highlighted  words in document search
    int m_RightKwicContextSize;
    //! the maximal number of kwic lines in file   snippets
    int m_NumberOfKwicLinesInSnippets;
    //! the parameter for TfIdf ranking
    double m_TfIdfRank;
    //! the parameter for Near ranking
    double m_NearRank;
    //! the parameter for Position ranking
    double m_PositionRank;
    //! delimiter to use between token index fields in output
    std::string m_InterpDelimiter;
    //! delimiter to use between tokens in output
    std::string m_TokenDelimiter;

    //! whether to assume indexed data is utf8 encoded (default=no)
    bool m_Utf8;

    //! potentially unsafe queries will throw an exception unless this is true (default=false)
    bool m_bAllowUnsafeQueries;

    //! using any token attribute as a count-key will throw an exception unless this is true (default=true)
    bool m_bAllowCountByTokenAttributes;

    //! interpret "%foo" queries using MorphPattern? (default=true)
    bool m_bLemmaQueryUsesMorphPattern;

    //! indices to show for Free_Index
    std::vector<size_t> m_IndicesToShow;

    //! moo: timestamp of project *._con file
    time_t m_Timestamp;

    //! moo: maximum number of hits in a CConcHolder cache entry -- query results with more than MaxCachedHitsCount hits will not be cached (default=512)
    size_t m_MaxCachedHitsCount;

    //! moo: maximum number of queries to be cached by an associated CConcHolder (default=512)
    size_t m_MaxQueryCacheSize;

    //! term expansion dispatcher; should define at least an entry for "default"
    TxDispatcher m_Txd;

    /** \brief maps token-query operators to default index names; keys are as returned by CQToken::OperatorKey()
     * \detail
     * \li "_" ~ CQTokInfl (Token)
     * \li "@_" ~ CQTokExact (Token)
     * \li "%_" ~ CQTokLemma (Lemma)
     * \li "/_/" ~ CQTokRegex, CQTokSuffix, CQTokPrefix, CQTokInfix (Token)
     * \li "[_]" ~ CQTokMorph (MorphPattern)
     * \li ":{_}" ~ CQTokThes (Thes)
     * \li "^_" ~ CQTokChunk (Chunk)
     * \li "<_" ~ CQTokFile (Token)
     * \li "." ~ CQTokAnchor (sentence: should resolve to a break name rather than a token-level index name)
     * \li "*" ~ generic fallback (Token)
     */
    std::map<std::string, std::string> m_OpDefaultIndexNames;

    /** \brief maps symbolic keys to string constants to be included in corpus 'info' response as info.user.KEY=VAL
     * \detail
     * values are pairs (isFile,Value) s.t. Value is filename iff isFile is a true value, otherwise a literal value
     */
    std::map<std::string, std::pair<bool, std::string> > m_ServerInfo;

    CConcordance();

    ~CConcordance();

    //! wrapper for IndicesToShow option; now accepts integer position (min=1), long name, short name, or alias
    void RegisterIndicesToShow(const std::string &IndexListStr);

    //! get opt-style string declaration for IndicesToShow (empty if default)
    std::string GetIndicesToShowStr(bool Positional = false) const;

    //! return default pcre regex options
    RML_RE::Options GetRegexOptions() const {
        if (m_Utf8)
            return RML_RE::Options(true, NULL);
        else
            return RML_RE::Options(false, m_PcreCharacterTables.data());
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

    //! wrapper for m_bIndexPunctuation
    bool IndexPunctuation() const { return m_bIndexPunctuation; };

    //! get an HTML formatted reference to a \ref corpus_file_def "corpus file"
    std::string GetHtmlReference(size_t posFile) const;

    //! get a reference to a \ref corpus_file_def "corpus file" without the common left prefix
    std::string GetShortFilename(size_t posFile) const;

    //! get file name for storing \ref corpus_file_def "corpus file" names
    std::string GetFileNameForCorpusFileNames() const;

    //! get file name for masked files (strings)
    std::string GetFileNameForMaskedFiles() const;

    //! get file name for masked files (IDs, binary)
    std::string GetFileNameForMaskedFileIds() const;

    //! parse a delimited token into fields by splitting on m_InterpDelimiter
    std::vector<std::string> GetTokenFields(const COutputToken &tok);

    //! get the number of indexed corpus files
    inline size_t GetCorpusFilesCount() const { return m_CorpusFiles.size(); };

    //! get corpus file by index
    inline std::string GetCorpusFile(CFileNo FileNo) const { return m_CorpusFiles[FileNo]; };

    //! get count of masked files
    inline size_t GetMaskedFilesCount() const { return m_MaskedFiles.size(); };

    //! load list of \ref source_file_def "source files" and parses option file (*.opt)
    void LoadSourceFilesAndOptions(std::string FileName, bool reallyReadSourceFiles = true);

    //! load list of \ref corpus_file_def "corpus files" (*.con)
    void LoadCorpusFiles();

    //! (re-)compute common prefix of corpus files in m_CorpusFiles
    std::string GetCommonFilePrefix() const;

    //! load list of masked (deleted)\ref corpus_file_def
    void LoadMaskedFiles();

    //! loads options from a named file (calls LoadOptionsFromString())
    void LoadOptionsFromFile(const std::string &OptFile);

    //! loads  everything
    void LoadProject(std::string FileName, bool includeSourceFiles = true);

    //! update m_Timestamp to mtime of Filename if it is newer than the current m_Timestamp; \returns new m_Timestamp
    time_t UpdateTimestamp(const char *filename);

    //! dump loaded metadata to a stream (JSON)
    void DumpBibliography(FILE *f = stdout) const;

    //! dump file metadata to a string (JSON)
    std::string DumpFileBibliography(uint32_t FileNo) const;

    //! dump file data to a file (JSON)
    void DumpFileIndexJson(uint32_t FileNo, FILE *f = stdout) const;


    //! dump index data to a directory (format-dependent)
    void DumpIndex(std::string dirname, CIndexDumpFormat fmt = idfJson) const;

    //! dump index data to a single tab formatted file
    void DumpIndexToSingleTabFile(FILE *outfp) const;

    //! saves options to option file (*.opt)
    bool SaveOptions(std::string FileName) const;

    //! moo: get a vector of all occurrences in a given search period; used by universal wildcard (*) queries
    bool GetAllOccurrences(std::vector<CTokenNo> &occurrences, size_t searchPeriodNo) const;

    //! moo: search named break collection for matching positions, used by anchor queries
    bool GetOccurrencesByPosition(const std::string &BreakName, int anchor, std::vector<CTokenNo> &occurrences,
                                  size_t searchPeriodNo) const;
    bool UseTabFormatForLoading () const {return m_IndexType == TabFormat_Index;}
};


#endif 

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
