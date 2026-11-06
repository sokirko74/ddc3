#include "ConcIndexatorInvoker.h"
#include "DwdsThesaurus.h"
#include "DocumentIterator.h"
#include "CommonLib/ddcFile.h"


using namespace std;

ConcIndexatorInvoker::ConcIndexatorInvoker() {
    m_bStoppedByUser = false;
    m_bStdout = false;
    m_CurrentSourceFileNo = 0;
    m_SourceFilesNumber = 0;
    // profiling takes 3 percent of working time, if we trust
    // DevPartner or gprof, that's why by dGefault it should be switched off.
    m_Profiler.m_bTimeSpanHolderEnabled = false;
    m_bOnlyReindexMorphology = false;
    m_bSkipInitialFileChecking = false;
};

void ConcIndexatorInvoker::SetCurrMessage(string Message) const {
    m_CurrMessage = Message;
    if (m_bStdout) {
        ddcLogInfo(m_CurrMessage);
    };
};

string ConcIndexatorInvoker::GetTimeStatisticsFileName(string Path) const {
    return MakeFName(Path, "_time_statistics");
};

string ConcIndexatorInvoker::GetErrorLogFileName(string Path) const {
    return MakeFName(Path, "_error_log");
};




void ConcIndexatorInvoker::WriteTimeStatistics(const CConcIndexator &Indexator, uint32_t MaxTokenCountInOnePeriod) const {
    try {
        double AllClocksCount = m_Profiler.EndTimer("Indexing");

        FILE *fp = fopen(GetTimeStatisticsFileName(Indexator.m_Path).c_str(), "w");
        if (!fp) {
            ddcLogError("Cannot write time statistics to file!");
        } else {
            fprintf(fp, "%s", m_Profiler.GetStrRepresentation(AllClocksCount).c_str());
            int AllSeconds = (int) (AllClocksCount / CLOCKS_PER_SEC);
            int u = (AllSeconds > 0) ? (int) ((m_CorpusEndTokenNo) / AllSeconds) : 0;
            fprintf(fp, "Speed (Tokens per second) = %i\n", u);
            fprintf(fp, "MaxTokenCountInOnePeriod = %u (tokens in one subcorpus)\n", MaxTokenCountInOnePeriod);
            fprintf(fp, "Count of subcorpora = %zi\n", Indexator.GetSearchPeriodsCount());
            fprintf(fp, "Count of running tokens  = %u\n", m_CorpusEndTokenNo);

            fclose(fp);
        };
    }
    catch (...) {
        SetCurrMessage("An exception occurred while saving time_statistsics files");
    }
};

void ConcIndexatorInvoker::FinalizeIndex(CConcIndexator &Indexator, uint32_t MaxTokenCountInOnePeriod) const {

    if (!Indexator.SaveCorpusFileList()) {
        throw CDDCExpc(Format("Cannot save corpus file list %s\n", Indexator.GetFileNameForCorpusFileNames().c_str()));
    };

    if (m_CorpusEndTokenNo >= CIndexItem::GetMaximalNumberOfRunningTokens()) {
        throw CDDCExpc(Format("Error! Number of running tokens cannot be more than ",
                           CIndexItem::GetMaximalNumberOfRunningTokens()));
    };

    m_Profiler.StartTimer("Final Save to Disc", 1);

    Indexator.BordersEndIndexing(Indexator.m_Path);
    if (!Indexator.LoadHitBorders(Indexator.m_Path)) throw CDDCExpc ("LoadHitBorders failed");
    assert (Indexator.GetCorpusEndTokenNo() == m_CorpusEndTokenNo);
    Indexator.CalculateSearchPeriods(MaxTokenCountInOnePeriod);

    SetCurrMessage(Format("Tokens Count = %i\n", m_CorpusEndTokenNo));

    if (!Indexator.AddInputLoadIndexToMemoryLoadIndex()) throw CDDCExpc ("AddInputLoadIndexToMemoryLoadIndex failed");
    if (!Indexator.SaveMemoryLoadIndex()) {
        throw CDDCExpc("Cannot save memory indices to disk; probably no space left on device!");
    }
    if (!Indexator.AddMemoryLoadIndexToMainLoadIndex()) throw CDDCExpc ("AddMemoryLoadIndexToMainLoadIndex failed");
    if (!Indexator.FinalSaveAllIndices(true)) throw CDDCExpc ("FinalSaveAllIndices failed");;
    SetCurrMessage("finished final saving");
    Indexator.NormalEndIndexing();
    SetCurrMessage("finished deleting temp. files");
    m_Profiler.EndTimer("Final Save to Disc");

    m_Profiler.StartTimer("CreateMorphIndex", 1);
    if (Indexator.m_bIndexMorphPatterns && !Indexator.CreateMorphIndexWrapper()) {
        throw CDDCExpc("Error! Cannot create morph index!");
    }
    m_Profiler.EndTimer("CreateMorphIndex");

    SetCurrMessage("");

    remove(GetErrorLogFileName(Indexator.m_Path).c_str());
    if (Indexator.m_bResumeOnIndexErrors && !m_ErrorCorpusFiles.empty()) {
        FILE *fp = fopen(GetErrorLogFileName(Indexator.m_Path).c_str(), "w");
        if (fp) {
            for (size_t i = 0; i < m_ErrorCorpusFiles.size(); i++)
                fprintf(fp, "%s\n", m_ErrorCorpusFiles[i].c_str());
            fclose(fp);
        }
        SetCurrMessage(Format("%i error(s) were written into %s", m_ErrorCorpusFiles.size(),
                              GetErrorLogFileName(Indexator.m_Path).c_str()));
    };
};

void ConcIndexatorInvoker::BuildOnlyMorphIndex(string ProjectFile) const {
    CConcIndexator Indexator;
    Indexator.LoadProject(ProjectFile);

    if (!Indexator.CreateMorphIndexWrapper()) {
        throw CDDCExpc("cannot index morphology index");
    }
    SetCurrMessage("reindexing was successful!\n");
};

void newhandler() {
    ddcLogError("Cannot allocate memory (newhandler is called); terminate the process...");
    throw bad_alloc();
    return;
}

void ConcIndexatorInvoker::BuildIndexStart(string ProjectFile, CConcIndexator& indexator)
{
    m_CorpusEndTokenNo = 0;
    indexator.LoadSourceFilesAndOptions(ProjectFile);

    m_SourceFilesNumber = indexator.GetSourceFilesCount();

    if (m_SourceFilesNumber == 0) {
        throw CDDCExpc("No files in the project!");
    };

    SetCurrMessage(Format("Files %i\n", m_SourceFilesNumber));
    if (!m_bSkipInitialFileChecking) {
        int FileNo = indexator.FoundNotExistedFile();
        if (FileNo != -1) {
            throw CDDCExpc(Format("File %s was not found or it is empty, cannot load the project\n",
                               indexator.GetSourceFile(FileNo).c_str()));
        };
    };


    indexator.DestroyIndex();
    indexator.StartIndexing();

    SetCurrMessage(Format("MaxTokenCountInOnePeriod = %i", indexator.GetMaxTokenCountInOnePeriod()));
    SetCurrMessage(Format("MaxInputLoadIndexSize = %i", indexator.GetMaxInputLoadIndexSize()));

    m_Profiler.ClearTimers();
    m_Profiler.StartTimer("Indexing", 0);
    time(&m_StartTime);
}

void ConcIndexatorInvoker::PrintProgress(uint32_t saveCorpusEndTokenNo)
{
    time_t speed_curr_time;
    time(&speed_curr_time);
    size_t dur = speed_curr_time - m_StartTime;
    size_t speed = (dur == 0) ? 0 : saveCorpusEndTokenNo / dur;
    SetCurrMessage(Format("File  %s", m_CurrentSourceFileName.c_str()));
    SetCurrMessage(Format("(%i from  %i)", m_CurrentSourceFileNo + 1, m_SourceFilesNumber));
    SetCurrMessage(Format("Processed tokens = %i;Speed(tokens per sec)=%u", saveCorpusEndTokenNo, speed));
}

void ConcIndexatorInvoker::SaveLoadIndexToDisk(CConcIndexator& Indexator) {
    SetCurrMessage("Saving index to disk");
    m_Profiler.StartTimer("AddInputLoadIndexToMemoryLoadIndex", 1);
    if (!Indexator.AddInputLoadIndexToMemoryLoadIndex()) {
        throw CDDCExpc(Format("Fatal Error! Cannot AddInputLoadIndexToMemoryLoadIndex"));
    };
    m_Profiler.EndTimer("AddInputLoadIndexToMemoryLoadIndex");

    m_Profiler.StartTimer("Intermediate Save to Disc", 1);

    if (!Indexator.SaveMemoryLoadIndex()) {
        throw CDDCExpc("Cannot save indices to disk; probably no space left on device!\n");
    };
    if (!Indexator.AddMemoryLoadIndexToMainLoadIndex()) {
        throw CDDCExpc("Fatal Error! Indexator.AddMemoryLoadIndexToMainLoadIndex returned false\n");
    };
    m_Profiler.EndTimer("Intermediate Save to Disc");
}

uint32_t ConcIndexatorInvoker::IndexFile(CConcIndexator& Indexator, CIndexDocument* document)
{
    string strError;
    m_Profiler.StartTimer("Indexator.IndexOneFile", 1);
    string CorpusFileName = document->CorpusFileName;

    if (document->IsEmpty()) {
        string err = Format("skipping empty %s", CorpusFileName.c_str());
        SetCurrMessage(err);
        m_ErrorCorpusFiles.push_back(err);
        return 0;
    };

    //Indexator.m_Indices[0]->PrintLoadIndexStats(stderr); //-- DEBUG
    uint32_t startFileTokenNo =  m_CorpusEndTokenNo;
    try {
        document->CorpusEndTokenNo = m_CorpusEndTokenNo;
        Indexator.IndexOneFile(document);
        m_CorpusEndTokenNo = document->CorpusEndTokenNo;
    }
    catch (CFatalExpc &e) {
        ddcLogError(Format("Error: failed to index file `%s': %s", CorpusFileName.c_str(), e.what()));
        throw;
    }
    catch (CExpc &e) {
        string err = Format("Indexator.IndexOneFile() failed for file %s: %s", CorpusFileName.c_str(), e.what());

        if (!Indexator.m_bResumeOnIndexErrors) {
            throw CDDCExpc(string("Error: ")+err);
        } else {
            ddcLogWarn(string("Warning: ")+err);
            m_ErrorCorpusFiles.push_back(err);

            SetCurrMessage(Format("skipping %s", CorpusFileName.c_str()));

            //-- trim discarded doc data from buffered index structures
            m_ErrorCorpusFiles.push_back(Format("Initiated rollback for file `%s' at CTokenNo=%u", CorpusFileName.c_str(), startFileTokenNo));
            Indexator.RollbackIndexOneFile(startFileTokenNo);
            
            return 0;
        }
    }
    catch (...) {
        throw;
    }

    m_Profiler.EndTimer("Indexator.IndexOneFile");

    uint32_t tokensCount = m_CorpusEndTokenNo - startFileTokenNo;
    if (tokensCount == 0) {
        string err = Format("skipping empty %s", CorpusFileName.c_str());
        SetCurrMessage(err);
        m_ErrorCorpusFiles.push_back(err);
        return 0;
    };

    if (m_CorpusEndTokenNo >= CIndexItem::GetMaximalNumberOfRunningTokens()) {
        throw CDDCExpc(Format("Error! Number of running tokens cannot be more than ",
                           CIndexItem::GetMaximalNumberOfRunningTokens()));
    };

    Indexator.m_CorpusFiles.push_back(CorpusFileName);
    Indexator.AddBreakByName(PredefinedFileBreakName, m_CorpusEndTokenNo);


    return tokensCount;
}

void ConcIndexatorInvoker::AddInputLoadIndexToMemoryLoadIndexWrapper(CConcIndexator& Indexator)
{
    PrintProgress(m_CorpusEndTokenNo);
    m_Profiler.StartTimer("AddInputLoadIndexToMemoryLoadIndex", 1);

    if (!Indexator.AddInputLoadIndexToMemoryLoadIndex()) {

        throw CDDCExpc(Format("Fatal error! Cannot AddInputLoadIndexToMemoryLoadIndex for %s",
                           m_CurrentSourceFileName.c_str()));

    };
    m_Profiler.EndTimer("AddInputLoadIndexToMemoryLoadIndex");

}


void ConcIndexatorInvoker::ProcessTarOrSingleFile(CConcIndexator& Indexator, size_t& InputLoadIndexSize, size_t& MemoryLoadIndexSize)
{
    ddcLogDebug(Format("Indexing file `%s'", m_CurrentSourceFileName.c_str()));
    CDocumentIterator docIterator(&Indexator, m_CurrentSourceFileName);
    CIndexDocument document;


    while ( docIterator.NextDocument(document) )
    {
        if (InputLoadIndexSize > Indexator.GetMaxInputLoadIndexSize()) {
            AddInputLoadIndexToMemoryLoadIndexWrapper (Indexator);
            MemoryLoadIndexSize += InputLoadIndexSize;
            InputLoadIndexSize = 0;
        };
        uint32_t tokensCount = IndexFile(Indexator, &document);
        if (m_bStoppedByUser) {
            throw CDDCExpc("stopped by user");
        };
        if  (tokensCount > 0) {
            InputLoadIndexSize += tokensCount;
            if (MemoryLoadIndexSize + InputLoadIndexSize > Indexator.GetMaxTokenCountInOnePeriod()) {
                SaveLoadIndexToDisk(Indexator);
                MemoryLoadIndexSize = 0;
                InputLoadIndexSize = 0;
            };
        }
    };
}

void ConcIndexatorInvoker::IndexFiles(CConcIndexator& Indexator)
{
    size_t InputLoadIndexSize = 0;
    size_t MemoryLoadIndexSize = 0;
    m_ErrorCorpusFiles.clear();
    if (Indexator.GetMaxInputLoadIndexSize() > Indexator.GetMaxTokenCountInOnePeriod()) {
        throw CDDCExpc(Format("ConcIndexatorInvoker::IndexFiles(): can't handle MaxInputLoadIndexSize=%u > MaxTokenCountInOnePeriod=%u",
                           Indexator.GetMaxInputLoadIndexSize(), Indexator.GetMaxTokenCountInOnePeriod()));
    }

    for (m_CurrentSourceFileNo = 0; m_CurrentSourceFileNo < m_SourceFilesNumber; m_CurrentSourceFileNo++) {
        if (m_bStoppedByUser) {
            throw CDDCExpc("stopped by user");
        };

        m_CurrentSourceFileName = Indexator.GetSourceFile(m_CurrentSourceFileNo);

        ProcessTarOrSingleFile(Indexator, InputLoadIndexSize, MemoryLoadIndexSize);
    };

    if (m_CorpusEndTokenNo == 0) {
        throw CDDCExpc("Cannot index empty corpus!");
    }

    FinalizeIndex(Indexator, Indexator.GetMaxTokenCountInOnePeriod());
}

bool ConcIndexatorInvoker::BuildIndex(string ProjectFile) {
    set_new_handler(newhandler);

    {  // set temp directory 
        char filename[2 * _MAX_PATH];
        strcpy(filename, Format("TMP=%s", GetPathByFile(ProjectFile).c_str()).c_str());
        putenv(filename);
        ddcLogDebug(Format("using temporary directory `%s'", getenv("TMP")));
    }


    CConcIndexator Indexator;
    try {
        if (m_bOnlyReindexMorphology) {
            BuildOnlyMorphIndex(ProjectFile);
            return true;
        }

        BuildIndexStart(ProjectFile, Indexator);
    }
    catch (CExpc e) {
        SetCurrMessage(string(e.what()));
        return false;
    }


    try {
        IndexFiles(Indexator);
        WriteTimeStatistics(Indexator,  Indexator.GetMaxTokenCountInOnePeriod());
        return true;
    }
    catch (exception& e) {
        ddcLogError(Format("Error: exception while indexing `%s': %s", ProjectFile.c_str(), e.what()));
        SetCurrMessage(Format("An exception occurred: %s", e.what()));
        throw;
    }
    catch (...) {
        ddcLogError(Format("Error: unknown exception while indexing `%s'", ProjectFile.c_str()));
        SetCurrMessage("An unknown exception occurred");
        throw;
    }

    //-- 2020-01-22: never reached (keep temporary data for debugging if something went wrong)
    try {
        Indexator.TerminateIndexing();
        Indexator.DestroyIndex();
    }
    catch (CExpc e) {
        SetCurrMessage(Format("Cannot normally terminate indexing: %s", e.what()));
    }
    return m_bStoppedByUser;

};
