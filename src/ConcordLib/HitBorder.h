#ifndef HitBorder_h
#define HitBorder_h

#include "CommonLib/ddcMMap.h"

/* \page break_def Corpus break definition 
  A "break" is a border between two adjacent sentences, paragraphs, files or other text chunks.
  Generally, a break of a type t  is an integer end offset of a token chunk in the corpus.
  Type  t  can be sentence, a clause, a file etc. The ordered concatenation of all chunks of 
  type t is the corpus itself, so it means that there is no intersection between these chunks and no uncovered parts. 
  One break collection of type t has short and long names.
  All break collections are stored in CHitBorders::m_Breaks indexed by their short names.
  see CHitBorders
*/

/* \page pb_def Page break definition
  A "page break" is a break_def break, which additionally  contains an integer page number
  see CPageNumber.
*/


/* typedef for user-defined break-vectors */
typedef ddcVecFile<CTokenNo> ddcBreakVector;

/* CPageNumber is a structure that holds a page number and the index of token, from which this page starts
 */
struct CPageNumber {
    // the starting position (in tokens) of the beginning of the page
    CTokenNo m_StartTokenNo;
    // the page number itself (as it was mentioned in the source text)
    uint32_t m_PageNumber;

    CPageNumber(CTokenNo StartTokenNo = 0, uint32_t PageNumber = 0)
        : m_StartTokenNo(StartTokenNo), m_PageNumber(PageNumber) {};

    inline bool operator<(const CPageNumber &X) const {
        return ((m_StartTokenNo < X.m_StartTokenNo)
                || (m_StartTokenNo == X.m_StartTokenNo && m_PageNumber < X.m_PageNumber));
    };
};


/*
  Class  CHitBorders contains all break_def "break" collections and all 
  pb_def "page breaks".
*/
class CHitBorders {
public:
    /*
      CBreakCollectionDescr is a structure that holds properties of a collection of break_def "breaks" of one type.
    */
    struct CBreakCollection {
        //  short name  of this break collection
        std::string m_ShortName;
        //  long name  of this break collection
        std::string m_LongName;

        // a file for temporally storing break_def "breaks" during indexing
        mutable FILE *m_FileForIndexing;

        // the breaks themselves
        ddcBreakVector m_BreakOffsets;

        CBreakCollection(const std::string &ShortName, const std::string &LongName);

        // returns the file name for a break collection
        std::string GetBreakFileName(std::string Path) const;

        void ReadFromDisk(std::string Path, bool useMMap = false);

        bool ClearAll(std::string Path);

        void CloseFileForIndexing();

        // for new union: append breaks
        void AppendBreaks(const ddcBreakVector &From, CTokenNo Offset = 0);

        // for new union: save to file
        void SaveToFile(const std::string &FileName);
    };

protected:
    // all breaks
    std::vector<CBreakCollection> m_Breaks;

    // the map from CBreakCollection.m_ShortName to the index in m_Breaks
    std::map<std::string, int> m_ShortName2BreakCollection;

    // the map from CBreakCollection.m_LongName to the index in m_Breaks
    std::map<std::string, int> m_LongName2BreakCollection;

    // a quick reference to file break_def "breaks" (which are also stored in m_Breaks)
    int m_FileBreakCollectionNo;
    // The name of the default break collection (written in the options file)
    std::string m_DefaultBreakName;

    //  page number collection
    ddcVecFile<CPageNumber> m_PageBreaks;


    // returns the file name for page breaks
    std::string GetPageBreaksFileName(std::string Path) const;

    // returns the short name of a break collection by the long or the short name
    std::string GetShortNameByName(const std::string &BreakName) const;

    //
    std::vector<uint32_t> m_LastTextAreaBreaks;

protected:
    //    opens for writing all CBreakCollectionDescr::m_FileForIndexing from  m_Breaks
    bool StartIndexing(std::string Path);

    //    deletes all break_def "break"  files
    bool RemoveHitBordersFileAndClear(std::string Path);

    //    adds one page break
    void AddPageBreak(const CPageNumber &P);

    //    save page break file
    void SavePageBreaks(const std::string &ProjectPath);

    int RegisterBreak(std::string ShortName, std::string LongName);

    int EnsureRegisteredBreak(std::string ShortName, std::string LongName);

    int GetBreakCollectionIndexByName(std::string ShortName) const;

    void AddBreakByIndex(uint32_t BreakCollectionNo, const CTokenNo &B);

public:
    // moo: get break collection by long or short name
    const CBreakCollection *GetBreakCollectionByName(const std::string &Name) const;


    // moo: get break collection map (dangerous)
    const std::vector<CBreakCollection> &GetBreaks(void) const { return m_Breaks; };

public:

    CHitBorders();

    //return the string representation of break collection descriptions
    std::string GetBorderIndicesString() const;

    // returns the short name of the last valid break collection (long or short) in Within
    // - if no valid break collection is found, returns m_DefaultBreakName
    // - replaces old ProcessHitTypeStrInQueryStr(string& Query)
    std::string WithinBreakName(const std::vector<std::string> &Within) const;

    //returns a break collection by a short name
    const ddcBreakVector *GetBreaksByName(const std::string &ShortName) const;

    //returns the value of the last file break_def "break" (which should be equal to the last value of any break collection)
    CTokenNo GetCorpusEndTokenNo() const;

    //quick reference to file break_def "breaks"
    const ddcBreakVector &GetFileBreaks() const;

    //returns the start position of corpus_file_def "corpus file" <i>FileNo</i>
    CTokenNo GetFileStartTokenNo(size_t FileNo) const;

    //returns m_PageBreaks[No].m_PageNumber (see CPageNumber)
    uint32_t GetPageNumber(size_t No) const;

    //returns true if a short name is found in  m_Breaks
    bool IsRegisteredBreak(const std::string &ShortName) const;

    //creates empty elements of m_Breaks by its string descriptions
    void RegisterBorderIndices(const char *IndicesStr);

    //load break collections from the disk
    bool LoadHitBorders(std::string Path, bool useMMap = false);

    // converts hits to page breaks, which contains this breaks
    void ConvertHitsToPageBreaks(std::vector<CHit>::const_iterator hits_begin, std::vector<CHit>::const_iterator hits_end,
                                 const ddcBreakVector &Breaks, DwordVector &PageBreaks) const;

    // get page break for a given token number as an interator into m_PageBreaks
    ddcVecFile<CPageNumber>::const_iterator GetTokenPageBreak(CTokenNo tok) const;

    // adds one break to a collection identified by a short name (during indexing)
    void AddBreakByName(const std::string &ShortName, const CTokenNo &B);

    //   closes all CBreakCollectionDescr::m_FileForIndexing from  m_Breaks (during indexing)
    void BordersEndIndexing(std::string Path);

    //   must be called before indexing each text area in order to create at least on break in each text area
    void StartTextAreaBorders();

    //   must be called after indexing each text area in order to create at least on break in each text area
    void EndTextAreaBorders(uint32_t TextAreaEndTokenNo);

};

// useful alias
typedef struct CHitBorders::CBreakCollection CHBreakCollection;


#endif
