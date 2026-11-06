#ifndef  StringIndexator_h
#define  StringIndexator_h

#include "../ConcordLib/IndexSet.h"

/* \page index_set_def Index Set Definition
  An index set consists of the list of strings (which are also called "index items") and corresponding 
  lists of their occurrences in the corpus, for example:
  mother -> 1, 100, 457 
  mothered -> 5006
  mothering -> 2, 120, 147
  ...
  A string to index can contain any char except \\0.  All strings of one index set are stored in a 
  special file (see CIndexSetForQueryingStage::GetFileNameForInfos() ). 

  An index set has two names: the short one and the long one (see class CStringIndexSet). 
  These names can be used interchangeably in queries. 

  Optionally one index set can have a storage_def "storage". 
        
  Regarding occurrences, DDC distinguishes  three types of occurrence lists: 
  - singleton (which is always in the memory);
  - long_listdef "short lists";
  - long_listdef "long lists";
          
*/

/* \page storage_def Index Storage Definition
  An index storage is a sequence of integers X1...XN, where N is the number of tokens in 
  the corpus. Each Xi points to an indexed string, for example for the token index it points to a token.
  The order of X1...XN is just the same as        it was in the input corpus. For example using 
  Token index storage DDC can reproduce the whole corpus word by word. By default the first index of the corpus has an index storage,
  for the other indices this option is switched off (see CIndexSetForLoadingStage::m_bUseItemStorage).
*/


/* \page corpus_file_def Corpus File Definition 
  A list of corpus files (CConcIndexator::m_CorpusFiles) is built upon a list of 
  source_file_def "source files" extracting everything from all source archives. 
  So if a source list doesn't contain archives then the lists of corpus files and source files are
  identical, otherwise it contains also files from archives, which are prefixed by the name of the archive .
  For each corpus file DDC maintains a file break_def "break", quick bibliographical information 
  (class CBiblIndex) and full bibliographical information (class CBibliography).
*/

/* \page source_file_def Source File Definition 
  Generally a source file is a file, from which DDC reads information to index.  A list of source files is the first input  
  parameter for the indexing process (CConcIndexatorInvoker::BuildIndex).  The second parameter  is a file of 
  options.  Source files are used only during the indexing, and they can be removed afterwards.  The current version supports
  the following types of source files:
  - 1. Plain text (UTF-8), extension *.txt.
  - 2. Html text (UTF-8), extension *.html, *.htm.
  - 3. Xml text, extension *.xml.  
  Any of them can be gzip-compressed (*.xml.gz etc.); compressed tar files (*.tar.gz) are not supported.
        
  If a source file is an xml file then DDC extracts some bibliographical information from it (class CBibliography) and stores it as an additional index,
  otherwise the bibliographical index  is empty. For parsing DDC uses pugixml (https://pugixml.org)  
  A source file can be also a tar archive.  
  All source files of one DDC index are stored in CConcIndexator::m_SourceFiles .
*/

/* \page long_listdef Long/Short Occurrence list definition 
  A list of occurrences is called "long" if its length is more than OccurBufferSize, otherwise it is 
  called a "short" one. 
*/
/* \page perdiv_def Period division for long occurrence lists 
        
  For each long_listdef "long list" DDC stores so called period division, which is a list of 
  integers X[1],X[2], ..X[M], where M is the number of period_def "corpus periods". 
  All occurrences from X[i-1] until X[i] belongs to corpus period i. Generally, using this period division 
  one can quickly get the sublist of occurrences which belongs to the same corpus period. All period divisions
  are written in CIndexSetForQueryingStage::m_EndPeriodOffsets .
*/




/* \page period_def Corpus period definition
  A "corpus period",  "internal subcorpus" or a "search period" is a break_def "break", which is introduced to restrict 
  the memory usage.  Corpus period always  coincides with a file break. The size of one 
  corpus period is 5000000 by default and can be determined manualy using field "UserMaxTokenCountInOnePeriod"
  in the options file.  While evaluating a query DDC deals only with one corpus period at a time, so 
  DDC applies the input query to each corpus period, and then concatenates the results.  
  Corpus periods  are also used in storing perdiv_def "period divisions"

  see CStringIndexator::m_SearchPeriods
*/

//const char ddc_archive_stub[] = "ddc_archive_stub";
const char ddc_archive_stub[] = "";

struct CTokenIndexator {
    std::vector<CStringIndexSet*> ColumnMap;
    std::vector<CStringIndexSet*> AbsentIndices;
    CTokenNo CorpusEndTokenNo;
};

/*
  CStringIndexator contains a set of all token indices and period_def "corpus periods". 
  It contains also the main path to the project file.
*/
class CStringIndexator {
        
protected:
        
    // period_def "search periods" of the corpus  
    std::vector<CTokenNo>        m_SearchPeriods;

    // register chunk index (chunks:NP, VP etc)    
    bool    RegisterChunkIndex();
    // return the file name for period_def "search periods"
    std::string  GetSearchPeriodsFileName() const;
    // call DestroyIndexSet for all registered indices
    bool    DestroyIndices();
    //  call ReadFromTheDisk for all registered indices
    void    ReadIndicesFromTheDisk();
    //  clear m_Indices
    void    ClearStringIndices();
    // index one token and its properies (delimited by CConcCommon.h::globalFieldDelimeter)
    void    IndexOneToken   (CTokenIndexator* document, const char* Line, bool tryFixErrors=true);

    // moo: truncate long columns in InputLine, storing result in Out
    // MaxLen: maximum length in bytes of Out, including terminating NUL byte
    // nCols: number of TAB-separated columns to write to Out ("globalFieldDelimeter" (sic))
    // InputLine: TAB-separated input token line string with length greater than or equal to MaxLen
    // Out: output string, should already be allocated with at least MaxLen bytes
    // 
    //   - called implicitly by IndexOneToken() encounters a too-long line if tryFixErrors is true
    //   - truncates only "greedy" columns (those using more than MaxLen/nCols bytes)
    //   - truncates each "greedy" column indepdently, proportionate to its "greediness" (the number of bytes by which its length exceeds MaxLen/nCols)
    void IndexTokenFixLongColumns(const size_t MaxLen, const size_t nCols, const char *InputLine, char *Out);

public:
    // typedef for index alias maps
    typedef std::map<std::string,std::string> IndexAliasMap;

    // typedef for index symbol table
    typedef std::map<std::string,CStringIndexSet*> IndexMap;
        
public:
    // where all indices are stored
    std::string                                  m_Path;

    // whether to directly mmap() index file data (default=false)
    bool                                    m_bMemoryMap;

    // the registered indices, by positional index
    std::vector<CStringIndexSet*>                m_Indices;

    // declared index aliases (FROM -> TO); not really used at runtime
    IndexAliasMap                           m_IndexAlias;

    // all registered indices, keyed by long-name, short-name, or label (LABEL -> INDEX)
    IndexMap                                m_IndexMap;

    // the maximal number of index items which can be included in an expansion set of one regular expression
    size_t                                  m_MaxRegExpExpansionSize;

    // a quick reference to a chunk index, if CConcIndexator::m_bIndexChunks       is on, otherwise null
    CStringIndexSet*                        m_pChunkIndex;

    CStringIndexator();
    ~CStringIndexator();

    // read index declarations  from a string and register  them
    bool RegisterStringIndices(const std::string& IndicesStr);

    // read index alias declarations from a string and register them; returns true iff all registrations were successful
    bool RegisterIndexAliases(const std::string& IndexAliasStr);

    // register a single index alias (low-level); returns true iff AliasTo resolves to a known index according to m_AliasMap
    bool RegisterIndexAlias(const std::string& AliasFrom, const std::string& AliasTo);

    // register a single index label or alias (lowest-level); if idx is NULL, any existing entry for AliasFrom will be deleted
    void RegisterIndexAlias(const std::string& AliasFrom, CStringIndexSet* idx);

    // set  the path to the indices
    void SetPath(std::string Path);
    // return all registered index declarations, in opt-file syntax
    std::string GetIndicesString() const;
    // return all registered index aliases, in opt-file syntax
    std::string GetIndexAliasString() const;
        
    // return the number of period_def "corpus periods"
    size_t  GetSearchPeriodsCount() const;
    // get a period_def "corpus period" by an index
    const CTokenNo&  GetSearchPeriod(size_t i) const { return m_SearchPeriods[i]; };

    // call CreateTempFiles for all registered indices
    bool    StartIndexing(std::string Path);
    // call DeleteTempFiles for all registered indices
    void    TerminateIndexing();
    // final saving all indices to disk (converting temp files to persistent)
    bool    FinalSaveAllIndices(bool bAfterLoading);
    // unites input index with memory index and clears input load index
    bool    AddInputLoadIndexToMemoryLoadIndex();
    // unites memory index with main index and clears  memory load index
    bool    AddMemoryLoadIndexToMainLoadIndex();
    // store memory load index on the disk
    bool    SaveMemoryLoadIndex();
    // return a pointer to the index by CStringIndexSet::m_Name (linear search)
    CStringIndexSet*  GetIndexByName(const std::string& Name);
    // return a pointer to the index by CStringIndexSet::m_Name or CStringIndexSet::m_ShortName (linear search)
    CStringIndexSet*  GetIndexByNameOrShortName(const std::string& Name);
    // return a pointer to the index by long-name, short-name, or alias (most abstract, uses m_IndexMap)
    CStringIndexSet*  GetIndexByAlias(const std::string &Alias) const;
    // return the first index that normally contains tokens themselves
    CStringIndexSet* GetTokenIndex();
    // return the first index that normally contains tokens themselves
    const CStringIndexSet* GetTokenIndex() const;

};





#endif
