
#ifndef PROJECT_DOCUMENTITERATOR_H
#define PROJECT_DOCUMENTITERATOR_H

#include "ConcCommon.h"
#include "StringIndexator.h"

class TAR;
class CConcIndexator;
class CConcordance;

struct CIndexDocument : public CTokenIndexator {
    std::string CorpusFileName; // = document name
    std::vector<char> DocumentBuffer; // read to chars or
    std::vector<std::string> DocumentLines; // or to lines
    size_t DroppedLinesCount;

    bool IsEmpty() const;
    void Initialize(const CConcIndexator* parent);
    void ReplaceZeroCharWithSpace();
    void NormalizeDocumentBuffer();
    void DefaultColumnMap(const CConcIndexator* parent);
    void CustomColumnMap(const CConcordance* parent, std::vector<CStringIndexSet*>& columnMap);
};

class CDocumentIterator {
    const CConcIndexator* Parent;

    TAR *Tar;
    std::string ContainerPath;
    bool Finished;

    bool IsStdin;
    std::string LastReadCorpusFileName;
    FILE* TabFormatStream;
    void ReadTabFormatDocument(CIndexDocument& doc);

public:
    CDocumentIterator (const CConcIndexator* parent, const std::string& containerPath);
    bool NextDocument(CIndexDocument& doc);
};


#endif //PROJECT_DOCUMENTITERATOR_H
