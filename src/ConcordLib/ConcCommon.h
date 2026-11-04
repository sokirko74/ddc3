#ifndef __ConcCommon_H_
#define __ConcCommon_H_

/*! \file ConcCommon.h
  \brief A file for globally defined constants and classes.
*/



#include "morph_dict/common/utilit.h"
#include "../CommonLib/ddcUtil.h"
#include "../CommonLib/ddcLog.h"
#include "list"
#include "limits.h"


#include "../GraphanLib/GraphmatFile.h"
#include "../CommonLib/ddcIconv.h"
#include "../CommonLib/ptrholder.h"
#include "morph_dict/lemmatizer_base_lib/Lemmatizers.h"
#include "morph_dict/agramtab/EngGramTab.h"
#include "morph_dict/agramtab/RusGramTab.h"
#include "morph_dict/agramtab/GerGramTab.h"
#include "../CommonLib/DDC_common.h"
#include "../CommonLib/ddcObject.h"
#include "../tinyxml/tinyxml.h"

#include "../ConcordLib/CCurl.h"
#include "../CommonLib/ddcLocale.h"

//! global intialization
inline void ddcInitGlobal(void) {
    ddcInitLocale();
    ddcInitCurl();
}

//! a globally defined delimeter, which is used to delimit fields in one record (the first field is always a token)
const char globalFieldDelimeter = '\t';
//! a globally defined xml-tag, which is used to separate records if CConcIndexator::m_IndexType is Free_Index
const std::string PredefinedTableLineTag = "l";
//! a globally defined index name for chunks
const std::string ChunkIndexName = "chunk";
//! a globally defined break collection name for \ref corpus_file_def "corpus files"
const std::string PredefinedFileBreakName = "file";
//! a globally defined break collection name for \ref text areas
const std::string PredefinedTextAreaBreakName = "textarea";

//! integer type CTokenNo is used to  refer an index of a token in the corpus
typedef uint32_t CTokenNo;

//! integer type CFileNo is used to refer to a single document (file) in the corpus
typedef uint32_t CFileNo;

//!  MaxShortOccurCacheSize is the upper bound  of  CShortOccurCache::m_Data.size() It is introduced to restrict memory usage.
const size_t MaxShortOccurCacheSize = 1000000;

//! maximum length of string sort-keys passed from subcorpus servers to distributed server, including terminating NUL
//! (see CConcHolder::GetHitIds() and CDDCServerListenHost::GetFirstHitsFromCorpora())
#define DDC_SORTKEY_MAXLEN 256

const size_t MaxBiblStringLen = 20000;

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
    //map<CTokenNo, CDataReference> m_IndexItemNo2Occurrences;
    std::vector <CDataReference> m_IndexItemNo2Occurrences;

    //!this vector contains all occurrences for this cache
    std::vector<CTokenNo>                        m_OccurrencesBody;
public:
    void                            Clear();
    size_t                          AddNewIndexItemNoToCache(const CTokenNo* pStart, const CTokenNo* pEnd );
    const CTokenNo*                 GetOccurrencesFromCache(const int CacheId, uint32_t& Length) const;
    bool                            CouldContainMore() const;

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
    //! sort by central context (ascending) 
    LessByMiddleContext = 9,
    //! sort by match context (descending) 
    GreaterByMiddleContext = 10,
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
    //! sort by count()-key (ascending)
    LessByCountKey = 16,
    //! sort by count()-key (descending)
    GreaterByCountKey = 17,
    //! sort by count()-value (ascending)
    LessByCountValue = 18,
    //! sort by count()-value (descending)
    GreaterByCountValue = 19,
    //! sort by #prune[]-key (ascending)
    LessByPruneKey = 20,
    //! sort by #prune[]-key (descending)
    GreaterByPruneKey = 21,
    //! end-of-enum sentinel
    HitSortsCount = 22
};

inline bool IsPruneFilterType(HitSortEnum e)
{ return e==LessByPruneKey || e==GreaterByPruneKey; }

/*! symbolic hit sort order constants */
enum HitSortOrderEnum {
    hsoDescending = -1,
    hsoNone = 0,
    hsoAscending = 1,
    hsoAscendingCountKeys = 2,
    hsoDescendingCountKeys = 3,
    hsoAscendingCountValues = 4,
    hsoDescendingCountValues =  5
};

inline bool IsNullSort(HitSortOrderEnum e)
{ return e==hsoNone; }

inline bool IsCountSort(HitSortOrderEnum e)
{ return e >= hsoAscendingCountKeys && e <= hsoDescendingCountValues; }

inline bool IsCountKeySort(HitSortOrderEnum e)
{ return e==hsoAscendingCountKeys || e==hsoDescendingCountKeys; }

inline bool IsCountValueSort(HitSortOrderEnum e)
{ return e==hsoAscendingCountValues || e==hsoDescendingCountValues; }

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
    "LessByMiddleContext",
    "GreaterByMiddleContext",
    "LessByLeftContext",
    "GreaterByLeftContext",
    "LessByRightContext",
    "GreaterByRightContext",
    "RandomSort",
    "LessByCountKey",
    "GreaterByCountKey",
    "LessByCountValue",
    "GreaterByCountValue",
    "LessByPruneKey",
    "GreaterByPruneKey"
};

/*! symbolic names for HitSortEnum, for stringification */
static const char *HitSortEnumStrings[HitSortsCount] = {
    "no_sort",
    "asc_by_date",
    "desc_by_date",
    "asc_by_size",
    "desc_by_size",
    "asc",
    "desc",
    "asc_by_rank",
    "desc_by_rank",
    "asc_middle",
    "desc_middle",
    "asc_left",
    "desc_left",
    "asc_right",
    "desc_right",
    "random",
    "asc_by_key",
    "desc_by_key",
    "asc_by_count",
    "desc_by_count",
    "prune_asc",
    "prune_desc"
};


class CFreeBiblIndexInterface {
public:
    virtual ~CFreeBiblIndexInterface()
    {};
    
    virtual std::string GetStringValue(uint32_t FileNo) const = 0;

    //! for key-based pruning (v2.1.9): map a single value-string to its value-id
    //! \li default implementation just calls hex2int(Value)
    virtual uint32_t GetIntegerLowerBound(const std::string &Value) const = 0;
};

/*! type for hit sort-keys and/or result filtering;
 *  new in v2.0.19
 */
struct CHitSortKey {
    //! primary integer sort key; formerly CHit::m_OrderId, CDDCFilterWithBounds.m_LevelStart|m_LevelEnd
    int     i;

    //! secondary sort key, new for v2.0.19
    std::string  s;

    //! default constructor
    CHitSortKey(int i_=0) : i(i_)
    {};

    //! constructor given integer and string
    CHitSortKey(int i_, const std::string& s_) : i(i_), s(s_)
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
    inline void assign(int i_, const std::string &s_)
    { i=i_; s=s_; };

    //! assignment to std::pair
    inline void operator= (const std::pair<int,std::string>& p)
    { i=p.first; s=p.second; };

    //! assignment to integer, alias for assign(i,"")
    inline void operator= (int i_)
    { i=i_; s.clear(); };

    //! assignment to string, alias for assign(0,s)
    inline void operator= (const std::string &s_)
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
    HitSortEnum             m_FilterType;

    //! the name of the free bibliographical field for bibliographic filters (#asc[FIELD], #desc[FIELD], #has[FIELD]),  or the name of a token field for context-sort filters (#left, #right, etc)
    //! \note formerly m_AttrName
    std::string                  m_AttrName;

    //! \li true if DDC should use CDDCFilterWithBounds::m_SatisfiedValues
    //! \li false if DDC should use range defined by CDDCFilterWithBounds::m_LevelStart and CDDCFilterWithBounds::m_LevelEnd slots
    //! (formerly m_bRegExp)
    bool                    m_bSet;

    //! true iff this is a negated filter
    bool                    m_bNegated; 

    //! match-id of reference token for context-sort operators (default=0:any)
    int m_ContextMatchId;

    //!  offset from matched token for context-sort operators
    int m_ContextOffset;

    //!  the lower bound of the filter (by default (INT_MIN,"")), valid only if m_bSet==false; formerly int m_LevelStart
    CHitSortKey m_KeyLo;

    //!  the upper bound of the filter (by default (INT_MAX,"")), valid only if m_bSet==false; formerly int m_LevelEnd
    CHitSortKey m_KeyHi;

    //!  the possible (integer) values for this bibliographical field,  valid only if m_bSet==true
    std::set<int> m_SatisfiedValues;

    //! pointer to the CConcXml::CFreeBiblIndex responsible for populating this filter (only after compile)
    const CFreeBiblIndexInterface* m_BiblIndex;

    //! pointer to parent CQFilter (if any)
    class CQFilter * m_Parent;

    inline void clear()
    {
        m_SatisfiedValues.clear();
    };

    //! returns integer sort order as a HitSortOrderEnum (-1:descending, 0:none, 1:ascending, 2:count_keys, 3:count_values)
    inline HitSortOrderEnum SortOrder() const {
        switch (m_FilterType) {
            case GreaterByDate:
            case GreaterByRank:
            case GreaterBySize:
            case GreaterByFreeBiblField:
            case GreaterByMiddleContext:
            case GreaterByLeftContext:
            case GreaterByRightContext:
            case GreaterByCountKey:
            case GreaterByCountValue:
            case GreaterByPruneKey:
                return hsoDescending;
            case NoSort:
                return hsoNone;
            default:
                return hsoAscending;
        };
    };

    //! returns true iff this is a file-based filter (for optimized count(*) queries)
    inline bool IsFileFilter() const
    {
        switch (m_FilterType) {
            case NoSort:
            case LessByDate:
            case GreaterByDate:
                return true; //-- special handling in CConcXml::FileMatches()
            case LessByFreeBiblField:
            case GreaterByFreeBiblField:
                return true; //-- usual case of metadata-based filtering
            case LessByRank:
            case GreaterByRank:
            case RandomSort:
                return true; //-- non-filter operators are ignored
            case LessByPruneKey:
            case GreaterByPruneKey:
                //return !m_Parent || !((CQFPrune*)m_Parent)->m_keys || ((CQFPrune*)m_Parent)->m_keys->canCountByFile(); //-- not declared here
            case LessBySize:
            case GreaterBySize:
            case LessByMiddleContext:
            case GreaterByMiddleContext:
            case LessByLeftContext:
            case GreaterByLeftContext:
            case LessByRightContext:
            case GreaterByRightContext:
            default:
                return false; //-- not file-based
        }
    };

    //! returns true iff this is a trivial-sort filter (i.e. does not change original hit-sort order)
    inline bool IsTrivialFilter(void) const
    { return m_FilterType == NoSort; };

    //! returns true iff this is a pruning filter
    inline bool IsPruneFilter(void) const
    { return IsPruneFilterType(m_FilterType); };


    CDDCFilterWithBounds()
        : m_bSet(false),
          m_bNegated(false),
          m_FilterType(NoSort),
          m_ContextMatchId(0),
          m_ContextOffset(0),
          m_KeyLo(INT_MIN),
          m_KeyHi(INT_MAX),
          m_BiblIndex(NULL),
          m_Parent(NULL)
    {};
};

/*! CHit is a structure that holds one found hit and its properties. The calculation of its slots 
  starts in CQueryNode class  and its inheritors and proceeds  in CConcHolder class.
*/
struct CHit 
{
    //! the index of the \ref break_def "break", which this hit represents (in the break collection CConcHolder::GetBreaks)
    uint32_t   m_BreakNo;
    //! the end offset of token occurrences to be highlighted in CQueryNode::m_Occurrences and later in CConcHolder::m_HighlightOccurs
    uint32_t   m_HighlightOccurrenceEnd;
    //! the index of \ref corpus_file_def "coprus file", where this hit is found, it is equal to  m_BreakNo if user searches within files
    uint32_t   m_FileNo;

    union {
        //! the string which displays how the rank was calculated (for rank-sorted queries)
        size_t  m_DebugRankNo;

        //! count for this item (for count-queries)
        size_t  m_Count;
    } m_Value;

    //! key for sorting and/or filtering, which is calculated either by an instance of CDDCFilterWithBounds or by CConcHolder.
    //! formerly m_OrderId
    CHitSortKey m_SortKey;

    CHit(uint32_t BreakNo=0) : m_BreakNo(BreakNo), m_SortKey(0) { m_Value.m_Count=0; };
};

/*! \brief FormatTypeEnum defines the format of output hits:
  - DDC_ResultHTML -  output hits  should be written in HTML-format; the tags "<STRONG><FONT COLOR=red>" are used for highlighting.
  - DDC_ResultText -  output hits  should be written in plain-format; the string "&&" is used to select the first  highlighting position, "_"  for the following positions are used for higlighting.
  - DDC_ResultTable -  output hits  should be written in table-format; there is no highlighting in the string at all, instead of this highligted words are written after the string
  - DDC_ResultJson -  output hits  should be written in json format
*/
enum DDCFormatTypeEnum {
    DDC_ResultHTML,
    DDC_ResultText,
    DDC_ResultTable,
    DDC_ResultDocIds,
    DDC_ResultJson
};

//!  a type for index string to its occurrences
typedef std::map<std::string,CShortOccurCache> CShortOccurCacheMap;

//!  a type for holding occurrences during reading from the disk
typedef std::vector<CTokenNo> COccurrBuffer;

//! a delimiter between morphological annotations
const std::string MorphAnnotationsDelim = "#";
//! a regular expression, which passes everything within one morphological annotation
const std::string MorphAnnotationsDelimRegExp = "[^#]*";

//! initializes morphology dictionaries
extern bool InitConcordDicts();
//! deletes morphology dictionaries
extern void FreeConcordDicts();
//! return a morphology dictionary by a language indentifier
extern const CLemmatizer* GetLemmatizerByLanguage (MorphLanguageEnum Langua);
//! return a grammatical table  by a language indentifier
extern const CAgramtab* GetGramtabByLanguage (MorphLanguageEnum Langua);
//! recode a word from the user (corpus) encoding to the internal encoding of the morphology (and back);
//! identity except for German, see "Software\\Dialing\\Lemmatizer\\German\\ExtEncoding" in rml.ini
extern std::string MorphRecodeExt2Int (MorphLanguageEnum Langua, const std::string& s);
extern std::string MorphRecodeInt2Ext (MorphLanguageEnum Langua, const std::string& s);

//! compare hits by break-number (for query evaluation, e.g. CQueryBinaryOperationNode::hits_and_positions_intersection())
struct CHitCompareByBreak
{
    CHitCompareByBreak() {};

    inline bool operator()(const CHit& h, const uint32_t brkno) const
    { return h.m_BreakNo < brkno; };
};

//! return a string representation of a set of token properties (in the format which is used in the index)
std::string GetIndexItemSetByVectorString(const std::vector<std::string> &TokenProperties, bool bRegexp);

#endif
