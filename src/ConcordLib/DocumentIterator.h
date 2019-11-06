//
// Created by sokirko on 05.10.19.
//

#ifndef PROJECT_DOCUMENTITERATOR_H
#define PROJECT_DOCUMENTITERATOR_H

#include "ConcCommon.h"
#include "StringIndexator.h"

class TAR;
class CConcIndexator;
class CConcordance;

struct CIndexDocument : public CTokenIndexator {
    string CorpusFileName; // = document name
    vector<char> DocumentBuffer; // read to chars or
    vector<string> DocumentLines; // or to lines

    bool IsEmpty() const;
    void Initialize(const CConcIndexator* parent);
    void ReplaceZeroCharWithSpace();
    void NormalizeDocumentBuffer();
    void DefaultColumnMap(const CConcIndexator* parent);
    void CustomColumnMap(const CConcordance* parent, vector<CStringIndexSet*>& columnMap);
};

class CDocumentIterator {
    const CConcIndexator* Parent;

    TAR *Tar;
    string ContainerPath;
    bool Finished;

    bool IsStdin;
    string LastReadCorpusFileName;
    FILE* TabFormatStream;
    void ReadTabFormatDocument(CIndexDocument& doc);

public:
    CDocumentIterator (const CConcIndexator* parent, const string& containerPath);
    bool NextDocument(CIndexDocument& doc);
};


#endif //PROJECT_DOCUMENTITERATOR_H

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-default-style: "linux"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
