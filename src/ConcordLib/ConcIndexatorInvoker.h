//
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
    DWORD m_CorpusEndTokenNo;
    vector<string> m_ErrorCorpusFiles;

    string GetTimeStatisticsFileName(string Path) const;

    string GetErrorLogFileName(string Path) const;

    void WriteTimeStatistics(const CConcIndexator &Indexator, DWORD MaxTokenCountInOnePeriod) const;

    void FinalizeIndex(CConcIndexator &Indexator, DWORD MaxTokenCountInOnePeriod) const;

    void BuildOnlyMorphIndex(string ProjectFile) const;

    void BuildIndexStart(string ProjectFile, CConcIndexator &indexator);

    void PrintProgress(DWORD saveCorpusEndTokenNo);

    void IndexFiles(CConcIndexator &Indexator);

    void SaveLoadIndexToDisk(CConcIndexator &Indexator);

    DWORD IndexFile(CConcIndexator &Indexator, CIndexDocument* document);

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
    mutable string m_CurrMessage;

    //! should  DDC  send all messages to stdout
    bool m_bStdout;

    //! the index of the currently processing \ref source_file_def "source file"
    int m_CurrentSourceFileNo;

    //! the number of files to index
    int m_SourceFilesNumber;

    //! the name of file
    string m_CurrentSourceFileName;

    //! a slot to gather profiling information  for loading stage
    mutable CMyTimeSpanHolder m_Profiler;


    ConcIndexatorInvoker();

    //! outputs a message to stdout or to GUI
    void SetCurrMessage(string Message) const;

    //! builds index files for project ProjectFile
    bool BuildIndex(string ProjectFile);
};



#endif //PROJECT_CCONCINDEXATORINVOKER_H

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
