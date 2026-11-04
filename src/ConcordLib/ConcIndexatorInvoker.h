// Created by sokirko on 04.10.19.
//

#ifndef CCONCINDEXATORINVOKER_H
#define CCONCINDEXATORINVOKER_H

#include "ConcIndexator.h"

class CDwdsThesaurus;

class CGraphmatFile;

class TAR;
//! CConcIndexatorInvoker is a class for invoking an  index process.
/*!
  This class was established to start, to stop and to monitor an indexing process.
  To start it  a user should call function CConcIndexatorInvoker::BuildIndex.
  To stop the process a user should set CConcIndexatorInvoker::m_bStoppedByUser to true.
*/
class ConcIndexatorInvoker {
    time_t m_StartTime;
    uint32_t m_CorpusEndTokenNo;
    std::vector<std::string> m_ErrorCorpusFiles;

    std::string GetTimeStatisticsFileName(std::string Path) const;

    std::string GetErrorLogFileName(std::string Path) const;

    void WriteTimeStatistics(const CConcIndexator &Indexator, uint32_t MaxTokenCountInOnePeriod) const;

    void FinalizeIndex(CConcIndexator &Indexator, uint32_t MaxTokenCountInOnePeriod) const;

    void BuildOnlyMorphIndex(std::string ProjectFile) const;

    void BuildIndexStart(std::string ProjectFile, CConcIndexator &indexator);

    void PrintProgress(uint32_t saveCorpusEndTokenNo);

    void IndexFiles(CConcIndexator &Indexator);

    void SaveLoadIndexToDisk(CConcIndexator &Indexator);

    uint32_t IndexFile(CConcIndexator &Indexator, CIndexDocument* document);

    void AddInputLoadIndexToMemoryLoadIndexWrapper(CConcIndexator &Indexator);

    void ProcessTarOrSingleFile(CConcIndexator &Indexator, size_t &InputLoadIndexSize, size_t &MemoryLoadIndexSize);

public:
    //! if true, CConcIndexatorInvoker tries to stop indexing
    bool m_bStoppedByUser;
    //! if true, then BuildIndex should only rebuild MorphPattern index
    bool m_bOnlyReindexMorphology;
    //! if true, then there is no initial checking whether the \ref source_file_def "source files" exist
    bool m_bSkipInitialFileChecking;

    //! the last message from indexing process
    mutable std::string m_CurrMessage;

    //! should  DDC  send all messages to stdout
    bool m_bStdout;

    //! the index of the currently processing \ref source_file_def "source file"
    int m_CurrentSourceFileNo;

    //! the number of files to index
    int m_SourceFilesNumber;

    //! the name of file
    std::string m_CurrentSourceFileName;

    //! a slot to gather profiling information  for loading stage
    mutable CMyTimeSpanHolder m_Profiler;


    ConcIndexatorInvoker();

    //! outputs a message to stdout or to GUI
    void SetCurrMessage(std::string Message) const;

    //! builds index files for project ProjectFile
    bool BuildIndex(std::string ProjectFile);
};



#endif //PROJECT_CCONCINDEXATORINVOKER_H
