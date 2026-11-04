#ifndef  IndexSet_h
#define  IndexSet_h

#include "../ConcordLib/IndexSetForLoadingStage.h"
#include "../ConcordLib/IndexSetForQueryingStage.h"
#include "../PCRE/pcre_rml.h"

/*!  COutputToken  contains information about one token of an output hit and its properties.
 */
struct COutputToken {
    //! the token itself
    std::string m_TokenStr;
    //! the interpretation of the token
    std::string m_InterpStr;
    //! how DDC should highlight this token in the output hit
    BYTE m_Highlight;

    COutputToken() : m_Highlight(0) {};

    COutputToken(std::string WordStr, BYTE Highlight) : m_TokenStr(WordStr), m_Highlight(Highlight) {};

    bool operator==(const COutputToken &X) const {
        return m_TokenStr == X.m_TokenStr;
    };
};


class CStringIndexator;


/*! Class CStringIndexSet  is the upmost implementation of one \ref index_set_def "index set". The
  main functions deals with the searching of strings in index and with the retrieving its occurrences.
  On the other hand, this class is an inheritor of CIndexSetForLoadingStage and CIndexSetForQueryingStage, and 
  therefore it provides a connection between them during the load phase (for example CStringIndexSet::ConvertLoadIndexToWorkingIndex).
*/
class CStringIndexSet : public CIndexSetForLoadingStage, public CIndexSetForQueryingStage {
    //! a file for \ref storage_def "index storage"
    ddcFileOrMMap m_StorageFile;


    //! convert a temporal index set to the work index
    bool ConvertLoadIndexToWorkingIndex();


    //! make concatenation of multiple storages (new)
    void CreateUnionTokenStorages(const std::vector<CStringIndexSet *> &IndexSets, const std::vector<size_t> &TokenCounts,
                                  const std::vector<std::vector<uint32_t> > &xlateItemId);

    //!     open \ref storage_def "storage" file
    void OpenStorageFile();


    //! return m_Name (an implementation of pure member CIndexSetForLoadingStage::GetName )
    std::string GetName() const;

    //! converts temporary \ref storage_def "index storage" to persistent one (replacing a reference to  m_StringBuffer by a index item no)
    bool ConvertTempStorageToPersistent();

public:

    //! the main name of the index set, for example "Token", "MorphPattern", "Thes", "Chunk"...
    std::string m_Name;

    //! a short name of the index set,  for example "m", "w", "t", "c"
    std::string m_ShortName;

    //! this function returns a string(which was indexed by DDC) by an instance of CIndexItem or CItemIndexForLoading
    template<class T>
    inline const char *GetIndexItemStr(const T &W) const {
        return m_StringBuffer.m_data + W.GetIndexItemOffset();
    };

    CStringIndexSet(const CStringIndexator *pParent);

    ~CStringIndexSet();

    //! return file name for storage
    std::string GetStorageFileName() const;

    //!     close \ref storage_def "storage" file
    void CloseStorageFile();

    //! initialize all class slots
    void InitIndexSet(std::string Name, std::string ShortName, bool bCreateItemStorage, bool bCompress);

    //! read index from the disk
    void ReadFromTheDisk();

    //! clear all vectors of the index and removes index files
    bool DestroyIndexSet();

    //! write index to file
    bool WriteToFile(bool bAfterLoading);

    //! build union of multiple indices , throws CExpc if fails (new)
    void UnionIndexSets(const std::vector<CStringIndexSet *> &IndexSets, const std::vector<size_t> &TokenCounts);

    //! partition this index into \a Paritions[] on \a EndTokenNo[] (exclusive)
    void CreateSplitPartitions(std::vector<CStringIndexSet *> &Partitions, const std::vector<CTokenNo> &EndTokenNo) const;

    //! ensure that m_rIndex is non-empty, populating it from m_Index if required (called during index compilation)
    void EnsureSuffixIndex();

    //! return sequence of tokens(strings) [start_offset,  end_offset]
    bool GetTokensFromStorage(const size_t start_offset, const size_t end_offset, std::vector<COutputToken> &Tokens) const;

    //! gets index-local item-id of token number \a TokenNo
    //! \li basically a pared-down single-token version of GetTokensFromStorage()
    //! \li \returns integer \a ItemId such that <code>CIndexItem TokenItem = m_Index[ItemId]</code> is the indexed attribute for token number \a TokenNo,
    //!     or \a DWORD_MAX if an error occurs (e.g. no such token)
    uint32_t GetTokenIndexId(CTokenNo TokenNo) const;

    //! gets local m_Index iterator (lower-bound) for type \a ValueStr
    //! \li guts for  QueryTokenList(string& WordForm)
    //! \li really just a wrapper for lower_bound(m_Index.begin(), m_Index.end(), ValueStr.c_str(), LessIndexString1<CIndexItem>(&m_StringBuffer))
    //! \returns lower-bound iterator for \a ValueStr
    ddcVecFile<CIndexItem>::const_iterator GetTypeIndexIdLowerBoundIter(const std::string &ValueStr) const;

    //! gets local m_Index iterator (upper bound) for string type \a ValueStr
    //! \li guts for  QueryTokenList(string& WordForm)
    //! \li really just a wrapper for upper_bound(m_Index.begin(), m_Index.end(), ValueStr.c_str(), LessIndexString1<CIndexItem>(&m_StringBuffer))
    //! \returns upper-bound iterator for \a ValueStr
    ddcVecFile<CIndexItem>::const_iterator GetTypeIndexIdUpperBoundIter(const std::string &ValueStr) const;

    //! gets index-local item-id (lower bound) of string type \a ValueStr
    //! \li wrapper for GetTypeIndexIdLowerBoundIter(), returns item-id rather than iterator
    //! \returns lower-bound item-id for \a ValueStr
    uint32_t GetTypeIndexIdLowerBound(const std::string &ValueStr) const;

    //! gets index-local item-id of string type \a ValueStr, or DWORD_MAX if not in index
    uint32_t GetTypeIndexId(const std::string &ValueStr) const;

    //! populate bounds for context-sort operator
    bool GetContextBounds(CDDCFilterWithBounds &Filter, const std::string &LoValue, const std::string &HiValue) const;

    //! find all occurrences of index items  in \ref period_def "subcorpora" PeriodNo, using cache pCaches
    void FindOccurrences(const std::vector<uint32_t> &IndexItems, const size_t PeriodNo, std::vector<CTokenNo> &occurrences,
                         CShortOccurCacheMap *pCaches, std::vector<int> &CacheIds) const;

    //! find all occurrences of index items in \ref period_def "subcorpora" PeriodNo, using cache pCaches (if occurrences are written by chunks)
    void
    FindChunkOccurrences(const std::vector<uint32_t> &IndexItems, std::vector<CTokenNo> &occurrences, std::vector<uint32_t> &ChunkLengths,
                         size_t PeriodNo, CShortOccurCacheMap *pCaches, std::vector<int> &CacheIds) const;

    //! search for a string "WordForm", and add it to "MatchWords", if it is found
    void QueryTokenList(const std::string &WordForm, std::vector<uint32_t> &MatchWords) const;

    //! search for all strings, which begin with "Prefix", and add their IDs to "MatchWords"
    void QueryTokenListWithRightTruncation(const std::string &Prefix, std::vector<uint32_t> &MatchWords) const;

    //! search for all strings, which end with "Suffix", adding their IDs to "MatchWords" (requires m_rIndex, introduced in v2.1.21)
    void QueryTokenListWithLeftTruncation(const std::string &Suffix, std::vector<uint32_t> &MatchWords) const;

    //! search for all index items, which satisfy regular expession "RegExp", and add them to "MatchWords"
    void QueryTokenListUsingRegExp(RML_RE &RegExp, std::vector<uint32_t> &MatchWords, bool negated = false,
                                   bool ignore_diacritics = false) const;

    //! populate "MatchWords" with all index item indices
    void QueryTokenListUniversal(std::vector<uint32_t> &MatchWords) const;

    //! print the string representation of the whole \ref storage_def "storage" to stdout
    void DumpStorage(FILE *output) const;
};


#endif
