#include "StdConc.h"
#include "ConcordLib/ConcIndexator.h"
#include "ConcordLib/IndexSetForLoadingStage.h"
#include "ConcordAlgorithm.h"

using namespace std;







bool    CStringIndexSet::ConvertLoadIndexToWorkingIndex ()
{

    FILE* main_fp = fopen(m_MainOccurTempFileName.c_str(), "rb");   
    if (!main_fp) return false;
        
    string OccursFileName = GetOccursFileName();
    FILE* res_fp = fopen(OccursFileName.c_str(), "wb");
    if (!res_fp ) 
    {
        fclose (main_fp);
        return false;
    };
    assert( m_Index.empty() );
    m_Index.clear();
    m_EndPeriodOffsets.clear();
    const CTokenNo EndTokenNo = m_pParent->GetSearchPeriod(m_pParent->GetSearchPeriodsCount() - 1);
        
    CItemIndexForLoading M;
    if (!M.InitOccurs())
        return false;

    size_t CurrPositionInResFile = 0;
    while (!feof(main_fp))
    {
        if (!M.ReadFromTemporalFile(main_fp))
        {
            // the last index
            break;
        }
        if (!AddOneIndexItem(M,res_fp,CurrPositionInResFile, EndTokenNo))
        {
            fclose (main_fp);
            fclose(res_fp);
            return false;
        };
    };

    M.FreeOccurs();
    fclose(main_fp);
    fclose(res_fp);

        

    return  WritePeriodsDivision();
};


bool CStringIndexSet::WriteToFile(bool bAfterLoading)
{
    if (bAfterLoading) 
        if (!ConvertLoadIndexToWorkingIndex()) 
            return false;

    if (m_bUseItemStorage)
    {
        if (!ConvertTempStorageToPersistent())
            return false;
        OpenStorageFile();
    };

    DeleteTempFiles();

    m_Index.ensureVec();
    if (!WriteVector(GetOccHdrFileName().c_str(), m_Index.m_vec)) return false;

    m_StringBuffer.ensureVec();
    if (!WriteVector(GetFileNameForInfos().c_str(), m_StringBuffer.m_vec)) return false;

    EnsureSuffixIndex();
    m_rIndex.ensureVec();
    if (!WriteVector(GetSuffixFileName().c_str(), m_rIndex.m_vec)) return false;

    return true;
};
