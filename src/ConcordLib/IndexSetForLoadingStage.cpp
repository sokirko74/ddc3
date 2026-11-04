#include "StdConc.h"
#include "../ConcordLib/IndexSetForLoadingStage.h"
#include "../ConcordLib/ConcIndexator.h"
#include "../CommonLib/ddcFile.h"


using namespace std;


//===========================================================
// globals
bool ddcEnableAnonymousTokens = false;


//===========================================================
//                    class CItemIndexForLoading
//==========================================================

//! initializes vector of  occurrences
bool CItemIndexForLoading::InitOccurs() 
{
    m_pCurrOccurs = new vector<CTokenNo>;
    if (!m_pCurrOccurs)
    {
        fprintf(stderr, "cannot allocate new vector of occurrences in CItemIndexForLoading::InitOccurs\n");
        return false;
    }
    return true;
};

//! deletes vector of  occurrences
void CItemIndexForLoading::FreeOccurs() 
{
    try 
    {
        assert (m_pCurrOccurs);
        delete m_pCurrOccurs;
        m_pCurrOccurs = 0;
    }
    catch (...)
    {
        fprintf (stderr, "Exception in CItemIndexForLoading::FreeOccurs\n");
        throw;
    }
};

//! writes vector of  occurrences to a file
bool CItemIndexForLoading::WriteOccurrences(FILE* fp) const 
{
    return WriteVectorInner(fp, *m_pCurrOccurs);
};

//! checks the order of  occurrences
bool CItemIndexForLoading::CheckOccurrences(CTokenNo EndTokenNo) const 
{
    size_t Count = m_pCurrOccurs->size();

    if (Count == 0) 
    {
        // the set of occurrences can be empty if 
        // all occurrences are masked with "-#"
        return true;
    }

    for (size_t i = 0; i+1 < Count; i++) {
        if ((*m_pCurrOccurs)[i] >= (*m_pCurrOccurs)[i+1]) {
            ErrorMessage(Format("ERROR: CheckOccurrences(): occurrences are not sorted (occ[%i]=%i >= %i=occ[%i])\n",
                                i, (*m_pCurrOccurs)[i], (*m_pCurrOccurs)[i+1], i+1));
            return false;
        }
    }

    if ((*m_pCurrOccurs).back() >= EndTokenNo) {
        ErrorMessage(Format("ERROR: CheckOccurrences(): final occurrence exceeds EndTokenNo (occs[%i]=%i >= %i=EndTokenNo)\n",
                            m_pCurrOccurs->size()-1, m_pCurrOccurs->back(), EndTokenNo));
        return false;
    }
        
    return true;
};

//! clears vector of  occurrences to a file
void CItemIndexForLoading::ClearOccurrences() 
{
    ClearVector(*m_pCurrOccurs);
};



//! read vector of  occurrences from a temporal file 
bool CItemIndexForLoading::ReadFromTemporalFile (FILE* fp)
{
    // reads m_IndexItemOffset
    if ( fread(&m_IndexItemOffset,  sizeof(m_IndexItemOffset),1, fp) != 1) 
        return false;;

    // reads the number  of  occurrences 
    size_t OccCount;
    if ( fread(&OccCount, sizeof(size_t), 1, fp) != 1) 
        throw CDDCExpc("Exception in CItemIndexForLoading::ReadFromTemporalFile: offset %llu\n", (unsigned long long)ftell64(fp));

    m_pCurrOccurs->clear();


    // reads occurrences  themselves
    ReadVectorInner(fp, *m_pCurrOccurs, OccCount); // if ReadVectorInner cannot read  OccCount items, then it throws an exception

    return true;
};

//! write vector of  occurrences to a temporal file 
void CItemIndexForLoading::WriteToTemporalFile (FILE* fp) const
{
    if (fwrite(&m_IndexItemOffset, sizeof(m_IndexItemOffset), 1 , fp) != 1) 
        throw CDDCExpc ("Exception in CItemIndexForLoading::WriteToTemporalFile(1)");

    size_t OccCount;
    OccCount = m_pCurrOccurs->size();
    if (fwrite(&OccCount, sizeof(size_t), 1, fp) != 1) 
        throw CDDCExpc ("Exception in CItemIndexForLoading::WriteToTemporalFile(2)");

    if (!WriteVectorInner(fp, *m_pCurrOccurs)) 
        throw CDDCExpc ("Exception in CItemIndexForLoading::WriteToTemporalFile while writing %i tokens", m_pCurrOccurs->size());
};


//===========================================================
//                    class CIndexSetForLoadingStage
//==========================================================

CIndexSetForLoadingStage::CIndexSetForLoadingStage ():
    m_LoadLess2(&m_StringBuffer.m_vec), m_LoadLess1(&m_StringBuffer.m_vec)
{
    m_bUseItemStorage= false;
    m_TempStorageFile = 0;
};




bool CIndexSetForLoadingStage::CreateTempFiles(string Path)
{
    m_MainOccurTempFileName = MakeFName(Path, "tmp_main_"+GetName());

    FILE* fp =  fopen (m_MainOccurTempFileName.c_str(), "wb");
    if (!fp) return false;
    fclose( fp );

    m_CurrOccurTempFileName = MakeFName(Path, "tmp_curr_"+GetName());
    fp =  fopen (m_CurrOccurTempFileName.c_str(), "wb");
    if (!fp) return false;
    fclose( fp );
        
    if (m_bUseItemStorage)
    {
        m_TempStorageFileName = MakeFName(Path, "tmp_storage_"+GetName());
        m_TempStorageFile = fopen( m_TempStorageFileName.c_str(), "wb");
        if (!m_TempStorageFile) return false;
    };

    return true;
};



bool CIndexSetForLoadingStage::DeleteTempFiles ()
{
    bool bResult =      RemoveWithPrint(m_MainOccurTempFileName)
        &&  RemoveWithPrint(m_CurrOccurTempFileName);

        
    if (m_bUseItemStorage)
    {
        if (m_TempStorageFile)
            fclose (m_TempStorageFile);
        m_TempStorageFile = 0;

        bResult |= RemoveWithPrint(m_TempStorageFileName);
    };

    // clear all load indices
    for (int j = 0; j < 256; j++)
    {
        for (int i = 0; i < m_MemoryLoadIndexHash[j].size(); i++)
            m_MemoryLoadIndexHash[j][i].FreeOccurs();

        m_MemoryLoadIndexHash[j].clear();
    };

                
    return bResult;
};





CIndexSetForLoadingStage::~CIndexSetForLoadingStage ()
{
    DeleteTempFiles();
};



size_t CIndexSetForLoadingStage::GetMemoryLoadIndexItemsCount() const
{
    size_t Result = 0;

    for (int i = 0; i < 256; i++)
        Result += m_MemoryLoadIndexHash[i].size();

    return Result;
};

template<class T>
bool    WriteLoadIndexToTempFileAndClear(FILE* fp, vector<T>& V)
{
    size_t count = V.size();
    for (int i=0; i < count; i++)
    {
        V[i].WriteToTemporalFile(fp);
        V[i].ClearOccurrences();
    };
    return true;
};

bool    CIndexSetForLoadingStage::SaveMemoryLoadIndex()
{
    FILE* fp = 0;
    try {
        fp = fopen(m_CurrOccurTempFileName.c_str(), "wb");
        if (!fp) return false;

        for (int i = 0; i < 256; i++)
        {
            if (!WriteLoadIndexToTempFileAndClear(fp, m_MemoryLoadIndexHash[i]))
            {

                fclose(fp);
                return false;
            }
        }

        fclose(fp);
        return true;
    }
    catch (CExpc c)
    {
        fprintf (stderr, "Exception %s in CIndexSetForLoadingStage::SaveMemoryLoadIndex; Index name=%s\n", c.what(), GetName().c_str());
        return false;
    }
    catch(...)
    {
        fprintf (stderr, "Exception in CIndexSetForLoadingStage::SaveMemoryLoadIndex; Index name=%s\n",GetName().c_str());
        if (!fp) fclose (fp);
        return false;
    }
};

bool CIndexSetForLoadingStage::FindIndexItemInVector (const char* Item, vector<CItemIndexForLoading>::iterator& it, vector<CItemIndexForLoading>& V)
{
    it = lower_bound(V.begin(), V.end(),Item, m_LoadLess1);
    return          (it != V.end())
        && m_LoadLess1.are_equal(*it, Item);
};

//! finds an item in the swap index set, if it is not found, finds the item in the file index  set
bool CIndexSetForLoadingStage::FindIndexItem (const char* Item, vector<CItemIndexForLoading>::iterator& it)
{
    int HashNo = GetHashNo(Item);
    if (FindIndexItemInVector(Item, it, m_MemoryLoadIndexHash[HashNo]))
        return true;

    return FindIndexItemInVector(Item, it, m_InputLoadIndexHash[HashNo]);

};



bool    CIndexSetForLoadingStage::AddToMemoryLoadIndexAndClear(vector<CItemIndexForLoading>& Body, vector<CItemIndexForLoading>& FileIndexSet)
{
    size_t i = 0;

    // special check
    size_t cnt = FileIndexSet.size();
    for (; i+1 < cnt; i++)
        if (!m_LoadLess2(FileIndexSet[i], FileIndexSet[i+1]) )
        {
            fprintf (stderr,"An error occurred in function %s::AddToMemoryLoadIndexAndClear (order error:FileIndexSet is not sorted)\n", GetName().c_str());
                        
            //fprintf (stderr,"FileIndexSet[%i] = %s\n", i, GetIndexItemStr(FileIndexSet[i]) );
            //fprintf (stderr,"FileIndexSet[%i] = %s\n", i+1, GetIndexItemStr(FileIndexSet[i+1]) );
            return false;
        };
    // special check

    vector<CItemIndexForLoading>                    Result;
    Result.resize(FileIndexSet.size() + Body.size());
    vector<CItemIndexForLoading>::const_iterator it =  set_union(Body.begin(), Body.end(), FileIndexSet.begin(),FileIndexSet.end(), Result.begin(), m_LoadLess2);
    Result.resize( it - Result.begin());
        
    { // checking 
                
        int debug1 = Result.size();
        int debug2 = FileIndexSet.size() + Body.size();
        if ( Result.size() != FileIndexSet.size() + Body.size())
        {
            fprintf (stderr,"An error occurred in function %s::AddToMemoryLoadIndexAndClear (order error)\n", GetName().c_str());
            return false;
        };
        assert (Result.size() == (FileIndexSet.size() + Body.size()) );
    }
        
    Body =  Result;

    // special check
    cnt = Body.size();
    for (i = 0; i+1 < cnt; i++)
        if (!m_LoadLess2(Body[i], Body[i+1]) )
        {
            fprintf (stderr,"An error occurred in function %s::AddToMemoryLoadIndexAndClear (order error:Body is not sorted)\n", GetName().c_str());
            return false;
        };
    // special check

    FileIndexSet.clear();
    return true;
};

bool    CIndexSetForLoadingStage::AddInputLoadIndexToMemoryLoadIndex()
{
    try 
    {
        for (int i = 0; i < 256; i++)
            if (!AddToMemoryLoadIndexAndClear(m_MemoryLoadIndexHash[i], m_InputLoadIndexHash[i]))
                return false;
    }
    catch (...)
    {
        fprintf (stderr, "Exception in CStringIndexator::AddInputLoadIndexToMemoryLoadIndex; Index Name=%s\n", GetName().c_str());
        return false;
    }

    return true;
};


void    CIndexSetForLoadingStage::SortInputAndMemoryIndices()
{
    for (size_t j=0; j < 256; j++)
        for (size_t k=0; k < m_InputLoadIndexHash[j].size(); k++)
        {
            CItemIndexForLoading& Item = m_InputLoadIndexHash[j][k];
            sort(Item.GetOccurs()->begin(), Item.GetOccurs()->end());
            vector<CTokenNo>::iterator endit = unique(Item.GetOccurs()->begin(), Item.GetOccurs()->end());
            Item.GetOccurs()->erase(endit, Item.GetOccurs()->end());
        };

    for (size_t j=0; j < 256; j++)
        for (size_t k=0; k < m_MemoryLoadIndexHash[j].size(); k++)
        {
            CItemIndexForLoading& Item = m_MemoryLoadIndexHash[j][k];
            sort(Item.GetOccurs()->begin(), Item.GetOccurs()->end());
            vector<CTokenNo>::iterator endit = unique(Item.GetOccurs()->begin(), Item.GetOccurs()->end());
            Item.GetOccurs()->erase(endit, Item.GetOccurs()->end());
        };
};


bool    CIndexSetForLoadingStage::AddMemoryLoadIndexToMainLoadIndex()
{

    FILE* curr_fp = 0;
    FILE* main_fp = 0;
    FILE* res_fp = 0;
    int iteration = 0;
    try 
    {
        curr_fp = fopen(m_CurrOccurTempFileName.c_str(), "rb");
        if (!curr_fp) return false;

        main_fp = fopen(m_MainOccurTempFileName.c_str(), "rb");
        if (!main_fp) return  false; 

        string ResultFileName = MakeFName(m_MainOccurTempFileName, "tmp_result");
        res_fp = fopen(ResultFileName.c_str(), "wb");
        if (!res_fp ) return  false;

        CItemIndexForLoading C;
        if (!C.InitOccurs())
            return false;
        CItemIndexForLoading M;
        if (!M.InitOccurs())
            return false;


        C.ReadFromTemporalFile(curr_fp);
        M.ReadFromTemporalFile(main_fp);

        while (!feof(curr_fp)  && !feof(main_fp))
        {
            iteration++;
            if ( C.GetIndexItemOffset() == M.GetIndexItemOffset() )
            {
                if (            !M.GetOccurs()->empty()
                                &&      !C.GetOccurs()->empty()
                                &&      (M.GetOccurs()->back() >= *C.GetOccurs()->begin())
                    )
                {
                    // this place is used only if we create morphology index  ("--only-reindex-morph"  switch) 
                    vector<CTokenNo> R(C.GetOccurs()->size() + M.GetOccurs()->size());
                    vector<CTokenNo>::iterator end =  set_union(
                        C.GetOccurs()->begin(), C.GetOccurs()->end(),
                        M.GetOccurs()->begin(), M.GetOccurs()->end(), R.begin());
                    R.resize(end  - R.begin());
                    *M.GetOccurs() = R;

                }
                else
                    M.GetOccurs()->insert(M.GetOccurs()->end(), C.GetOccurs()->begin(), C.GetOccurs()->end());

                M.WriteToTemporalFile(res_fp);

                // next  items
                C.ReadFromTemporalFile(curr_fp);
                M.ReadFromTemporalFile(main_fp);
            }
            else
                if (m_LoadLess2(C, M) )
                {
                    C.WriteToTemporalFile(res_fp);
                    C.ReadFromTemporalFile(curr_fp);
                }
                else
                {
                    M.WriteToTemporalFile(res_fp);
                    M.ReadFromTemporalFile(main_fp);
                }
        };
                
        iteration = -1;
                
        if (!feof(curr_fp))
        {
            C.WriteToTemporalFile(res_fp);
            while (C.ReadFromTemporalFile(curr_fp))
            {
                iteration--;
                C.WriteToTemporalFile(res_fp);
            };
        }
        else
            if (!feof(main_fp))
            {
                M.WriteToTemporalFile(res_fp);
                while (M.ReadFromTemporalFile(main_fp))
                {
                    iteration--;
                    M.WriteToTemporalFile(res_fp);
                };
            };

        iteration = 91;
        C.FreeOccurs();
        M.FreeOccurs();

        fclose(curr_fp);
        fclose(main_fp);
        fclose(res_fp);

        iteration = 92;
        if (remove(m_MainOccurTempFileName.c_str()) != 0)
        {
            fprintf (stderr,"Cannot remove file %s\n", m_MainOccurTempFileName.c_str());
            return false;
        };

        iteration = 93;
        if (!RmlMoveFile(ResultFileName.c_str(), m_MainOccurTempFileName.c_str()) )
        {
            fprintf (stderr,"Cannot move file %s to %s\n", ResultFileName.c_str(), m_MainOccurTempFileName.c_str());
            return false;
        };

        return true;

    }
    catch (CExpc c) 
    {
        fprintf (stderr, "Exception %s in CIndexSetForLoadingStage::AddMemoryLoadIndexToMainLoadIndex; Index name=%s; iteration=%i\n",c.what(), GetName().c_str(), iteration);
    }
    catch (...) 
    {
        fprintf (stderr, "Exception in CIndexSetForLoadingStage::AddMemoryLoadIndexToMainLoadIndex; Index name=%s; iteration=%i\n",GetName().c_str(), iteration);
    }
    if (curr_fp) fclose(curr_fp);
    if (main_fp) fclose(main_fp);
    if (res_fp) fclose(res_fp);
    return false;

};


//-- maximum size of value-type string-buffer
//  + formerly hard-coded at 500MB
//  + should now be 2GB (2018-09-24 12:55:49+0200 moo)
#define MAX_STRINGBUFFER_SIZE (UINT32_MAX & (~AllFlags))

size_t CIndexSetForLoadingStage::AddItemStrToBuffer(const char* Str, size_t StrLen)
{
    //  including the last 0
    size_t buf_len = m_StringBuffer.size();
    if ((m_StringBuffer.size()+StrLen+1) >= MAX_STRINGBUFFER_SIZE)
    {
        throw CDDCExpc("index set(name = \"%s\") cannot contain more than %zd bytes of string type data", this->GetName().c_str(), MAX_STRINGBUFFER_SIZE);
    }

    for (long i=0; i <= StrLen; i++)
        m_StringBuffer.push_back(Str[i]);

    return buf_len;
};




int CIndexSetForLoadingStage::GetHashNo(const char* Str) const
{
    return (unsigned char)Str[0];
}


void CIndexSetForLoadingStage::InsertToInputLoadIndex(const char* Str, size_t StrLen, const vector<CTokenNo>& occurrences)
{
    const char AnonymousFlag[] = "-#";
    bool bHasAnonymousFlag = false;
    if (ddcEnableAnonymousTokens && !strncmp(Str,AnonymousFlag,2))
    {
        Str    += strlen(AnonymousFlag);
        StrLen -= strlen(AnonymousFlag);
        bHasAnonymousFlag = true;
    };

    vector<CItemIndexForLoading>::iterator it;
    uint32_t IndexItemOffset;

    if (!FindIndexItem(Str, it) )
    {
        // creating new index item
        CItemIndexForLoading word;
        if (!word.InitOccurs())
            throw CDDCExpc ("cannot allocate new vector of occurrences in CItemIndexForLoading::InitOccurs");

        if (!bHasAnonymousFlag)
            *word.GetOccurs() = occurrences;
        
        IndexItemOffset = AddItemStrToBuffer(Str, StrLen);
        word.SetIndexItemOffset(IndexItemOffset);
        m_InputLoadIndexHash[GetHashNo(Str)].insert(it, word);
    }
    else
    {
        // adding new occurrence to the existing index item
        if      (               (it->GetOccurs()->empty())
                                ||      (it->GetOccurs()->back() != occurrences[0])
            )

        {
            if (!bHasAnonymousFlag)
                it->GetOccurs()->insert(it->GetOccurs()->end(),  occurrences.begin(), occurrences.end());
        }
                        
        IndexItemOffset = it->GetIndexItemOffset();
    }

    if (m_bUseItemStorage) {
        if (fwrite(&IndexItemOffset,sizeof(uint32_t),1, m_TempStorageFile) != 1) 
            throw CDDCExpc ("Cannot write to temporary storage file");
    };
};


void PrintLoadIndexHashStats(const vector<CItemIndexForLoading> *hash, const char *label, FILE *f) {
    size_t nbins=0, nitems=0, noccs=0, max_offset=0, max_occ=0;
    for (size_t j=0; j < 256; j++) {
        const vector<CItemIndexForLoading>& mv = hash[j];
        if (!mv.empty()) ++nbins;
        
        for (vector<CItemIndexForLoading>::const_iterator mvi=mv.begin(); mvi != mv.end(); ++mvi) {
            ++nitems;
            if (mvi->GetIndexItemOffset() > max_occ) max_occ = mvi->GetIndexItemOffset();

            const vector<CTokenNo>* occs = mvi->GetOccurs();
            if (!occs) continue;
            
            noccs += occs->size();
            for (vector<CTokenNo>::const_iterator mvio=occs->begin(); mvio!=occs->end(); ++mvio) {
                if (*mvio > max_occ) max_occ = *mvio;
            }
        }
    }

    //-- dump stats
    fprintf(f, "%s statistics: %zd bins; %zd items (max=%zd), %zd occs (max=%zd)\n",
            label, nbins, nitems, max_offset, noccs, max_occ);
}
void CIndexSetForLoadingStage::PrintLoadIndexStats(FILE *f) const {
    PrintLoadIndexHashStats(m_MemoryLoadIndexHash, "MemoryLoadIndexHash", f);
    PrintLoadIndexHashStats(m_InputLoadIndexHash,  "InputLoadIndexHash ", f);
};


void RollbackLoadIndexHash(vector<CItemIndexForLoading> *Hash, CTokenNo startTrimTokenNo)
{
    for (size_t j=0; j < 256; j++) {
        vector<CItemIndexForLoading>& mv = Hash[j];
        
        for (vector<CItemIndexForLoading>::iterator mvi=mv.begin(); mvi != mv.end(); ++mvi) {
            vector<CTokenNo> *occs = mvi->GetOccurs();
            vector<CTokenNo>::iterator it = lower_bound(occs->begin(), occs->end(), startTrimTokenNo);
            if (it != occs->end())
                occs->erase(it,occs->end());
        }
    }
}

void CIndexSetForLoadingStage::RollbackLoadIndex(CTokenNo startTrimTokenNo)
{
    RollbackLoadIndexHash(m_InputLoadIndexHash, startTrimTokenNo);
    RollbackLoadIndexHash(m_InputLoadIndexHash, startTrimTokenNo);
    
    if (m_bUseItemStorage) {
        off_t truncate_offset = ((off_t)startTrimTokenNo) * sizeof(uint32_t);
        fflush(m_TempStorageFile);
        if (ftruncate(fileno(m_TempStorageFile), ((off_t)startTrimTokenNo) * sizeof(uint32_t)) != 0)
            throw CDDCExpc(Format("failed to truncate temporary storage file '%s' during rollback", m_TempStorageFileName.c_str()));
        if (!fseek64(m_TempStorageFile, truncate_offset, SEEK_SET))
            throw CDDCExpc(Format("failed to re-seek to end of temporary storage file '%s' during rollback", m_TempStorageFileName.c_str()));
        //fprintf(stderr, "DEBUG/ROLLBACK: truncate_offset=%zd ; new_offset=%zd\n", truncate_offset, ftell64(m_TempStorageFile)); //-- DEBUG
    }
};
