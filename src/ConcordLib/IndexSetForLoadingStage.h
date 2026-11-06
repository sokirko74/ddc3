#ifndef IndexSetForIndexingStage_h
#define IndexSetForIndexingStage_h


#include "DDCLessOperators.h"
#include "CommonLib/ddcMMap.h"

//===========================================================
// globals

/* global hack: set this to a true value to enable "masked" tokens
 *  (0 occurrences, in *_storage but not searchable) during corpus
 *  indexing.  Default was true prior to ddc v2.1.18.
 *  - 'anonymized' tokens are any beginning with the string "-#"
 *      (hard-coded in CIndexSetForLoadingStage::InsertToInputLoadIndex())
 */
extern bool ddcEnableAnonymousTokens;


//     CItemIndexForLoading holds all occurrences of one index item (token, morph. pattern...) on the index stage 
/*
  There are only two members: m_pCurrOccurs and m_IndexItemOffset.
  Member m_pCurrOccurs is a pointer to the vector of occurrences of an indexed string.
  We use here pointers because  we are going to create vector<CItemIndexForLoading>, and pointers can help us to avoid copying all occurrences each time when 
  an item is inserted to vector<CItemIndexForLoading>. 
  Member m_IndexItemOffset is  an reference to CIndexSetForLoadingStage::m_StringBuffer
*/
class CItemIndexForLoading
{ 
    // current vector of  occurrences 
    std::vector< CTokenNo >*     m_pCurrOccurs;

    // a reference to CStringIndexSet::m_StringBuffer 
    size_t                          m_IndexItemOffset;

public:

    // gets the reference to the index item 
    size_t  GetIndexItemOffset() const
    {
        return m_IndexItemOffset;
    };
    // sets the reference to the index item 
    void    SetIndexItemOffset(size_t Value) 
    {
        m_IndexItemOffset = Value;
    };

    // gets vector of occurrences
    std::vector<CTokenNo>* GetOccurs() 
    {
        assert (m_pCurrOccurs);
        return m_pCurrOccurs;
    };

    // gets vector of occurrences (const)
    const std::vector<CTokenNo>* GetOccurs() const 
    {
        assert (m_pCurrOccurs);
        return m_pCurrOccurs;
    };
    //  return the number of occurrences
    size_t GetOccursSize() const 
    {
        return  m_pCurrOccurs->size();
    };
    // initializes vector of  occurrences
    bool InitOccurs();

    // deletes vector of  occurrences
    void FreeOccurs();

    // writes vector of  occurrences to a file
    bool WriteOccurrences(FILE* fp) const;

    // checks the order of  occurrences
    bool CheckOccurrences(CTokenNo EndTokenNo) const;
        
    // clears vector of  occurrences to a file
    void ClearOccurrences();
        
    // read vector of  occurrences from a temporal file 
    bool ReadFromTemporalFile (FILE* fp);

    // write vector of  occurrences to a temporal file 
    void WriteToTemporalFile (FILE* fp) const;
};





// CIndexSetForLoadingStage is a part of DDC which is used only on the loading stage.
/*
  CIndexSetForLoadingStage contains temporary  file names and all load indices for one index_set_def "index set". 
  While indexing three indices are used:
  - main load index, 
  - memory load index,  
  - input load index.
  In fact these three indices contain information about one and the same index set, but on different stages: 
  - a main load index is always stored on the disk, and it is never loaded to the memory
  - a memory load index is a always in RAM
  - an input load index is used for one corpus_file_def "corpus file" or a sequence of short corpus files;  
  After having indexed one chunk of the input corpus DDC unites  the input index  with the memory index and clears the input index. 
  When the memory index is large enough DDC unites it also with the main index and clears the memory index.
  CIndexSetForLoadingStage holds a buffer, which contains all indexed strings delimited by "\\0" (m_StringBuffer). 
*/
class CIndexSetForLoadingStage
{
    //  a less operator for two buffer pointers  
    LessIndexString2<CItemIndexForLoading> m_LoadLess2;

    //  a less operator for a buffer pointer  and a const char*
    LessIndexString1<CItemIndexForLoading> m_LoadLess1;


    // a temporary file, where the memory index set is stored
    std::string  m_CurrOccurTempFileName;

    // return the name of the index (CStringIndexSet::m_Name) 
    virtual std::string GetName() const = 0;

    // memory index set (hashed by ASCII)
    std::vector<CItemIndexForLoading  >                  m_MemoryLoadIndexHash[256] ;

    // input memory index set   (hashed by ASCII)
    std::vector<CItemIndexForLoading  >                  m_InputLoadIndexHash[256] ;

    // find a string in vector "V", returning iterator "it", using  m_LoadLess1
    bool FindIndexItemInVector (const char* Item, std::vector<CItemIndexForLoading>::iterator& it, std::vector<CItemIndexForLoading>& V);

    // finds an item in the swap index set, if it is not found, finds the item in the file index  set
    bool FindIndexItem (const char* Item, std::vector<CItemIndexForLoading>::iterator& it);

    bool    AddToMemoryLoadIndexAndClear(std::vector<CItemIndexForLoading>& Body, std::vector<CItemIndexForLoading>& FileIndexSet);
    int     GetHashNo(const char* Str) const;

protected:
    // a temporal file for storage_def "index storage"
    FILE*           m_TempStorageFile;
    // a temporary file, where the storage_def "index storage" is stored
    std::string      m_TempStorageFileName;
    // a temporary file, where the main index is stored
    std::string  m_MainOccurTempFileName;

    // add a string to m_StringBuffer
    size_t                  AddItemStrToBuffer(const char* Str, size_t StrLen);


public:
    // if true, then the program creates and uses a storage_def "storage" for this index
    bool            m_bUseItemStorage;

    // a buffer for storing index strings (compile-time)
    ddcVecFile<char>   m_StringBuffer;


    CIndexSetForLoadingStage ();
    virtual ~CIndexSetForLoadingStage ();

    // creates temporary files  for indexing
    bool    CreateTempFiles (std::string Path);
    // deletes temporary files  after indexing
    bool    DeleteTempFiles();
    // gets the number  of items in memory load index 
    size_t  GetMemoryLoadIndexItemsCount() const;
    // saves memory index  
    bool    SaveMemoryLoadIndex();
    // add the input load index to the memory load index and clear the input load index 
    bool    AddInputLoadIndexToMemoryLoadIndex();
    // sort the input and the memory load indices
    void    SortInputAndMemoryIndices();
    // add the memory load index to the main load index and clear the memory load index 
    bool    AddMemoryLoadIndexToMainLoadIndex();
    // updates input or memory load index with one string
    void    InsertToInputLoadIndex(const char* Str, size_t StrLen, const std::vector<CTokenNo>& occurrences);

    // rolls back buffered index data starting at startTrimTokenNo
    void    RollbackLoadIndex(CTokenNo startTrimTokenNo);

    // debug: print input/memory load index stats
    void PrintLoadIndexStats(FILE *f=stderr) const;
};



#endif
