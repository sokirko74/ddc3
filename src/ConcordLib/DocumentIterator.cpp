//
// Created by sokirko on 05.10.19.
//

#include "DocumentIterator.h"
#include "ConcCommon.h"
#include "ConcIndexator.h"

#include "../RmlTar/RmlTar.h"
#include "../GraphanLib/HTMLConv.h"
#include "../CommonLib/bserialize.h"


using namespace std;

bool CIndexDocument::IsEmpty() const {
    return DocumentLines.empty() && DocumentBuffer.empty();
}

void CIndexDocument::DefaultColumnMap(const CConcIndexator* parent) {
    AbsentIndices.clear();
    ColumnMap.resize(parent->m_Indices.size());
    for (size_t i=0; i < parent->m_Indices.size(); ++i) {
        ColumnMap[i] = parent->m_Indices[i]; // default mapping
    }

}

void CIndexDocument::CustomColumnMap(const CConcordance* parent, vector<CStringIndexSet*>& columnMap) {
    columnMap.swap(ColumnMap);
    for (size_t i=0; i < parent->m_Indices.size(); ++i) {
        if (find(ColumnMap.begin(), ColumnMap.end(), parent->m_Indices[i]) == ColumnMap.end()) {
            AbsentIndices.push_back(parent->m_Indices[i]);
        }
    }
}

void CIndexDocument::Initialize(const CConcIndexator* parent) {
    DocumentBuffer.clear();
    DocumentLines.clear();
    DefaultColumnMap(parent);
    DroppedLinesCount = 0;
}

void replaceZeroCharWithSpace(vector<char>& buffer) {
    for (size_t i = 0; i < buffer.size(); i++)
        if (buffer[i] == 0)
            buffer[i] = ' ';

    // trim  spaces
    while (buffer.size() > 0 && isspace((BYTE) buffer[buffer.size() - 1]))
        buffer.erase(buffer.begin() + buffer.size() - 1);

    // make buffer a null-terminated string
    buffer.push_back(0);
}

void CIndexDocument::NormalizeDocumentBuffer() {

    replaceZeroCharWithSpace(DocumentBuffer);
    if (IsHtmlFile(CorpusFileName) && !DocumentBuffer.empty()) {
        HTML html;
        string Plain = html.GetTextFromHTMLBuffer(&(DocumentBuffer[0]), DocumentBuffer.size());
        DocumentBuffer.clear();
        DocumentBuffer.insert(DocumentBuffer.end(), Plain.begin(), Plain.end());
        replaceZeroCharWithSpace(DocumentBuffer);
    };


}

bool IsTarFile(const string &FileName) {
    return (FileName.length() > 4)
        && ((FileName.substr(FileName.length() - 4) == ".tar")
            || (FileName.substr(FileName.length() - 4) == ".TAR")
            );
};

CDocumentIterator::CDocumentIterator(const CConcIndexator* parent, const string &containerPath) :
    Parent(parent),
    Tar(0),
    ContainerPath(containerPath),
    Finished(false),
    IsStdin(false),
    TabFormatStream(NULL)
{
    if (IsTarFile(containerPath)) {
        tar_open(&Tar, containerPath.c_str());
        if (!Tar) {
            throw CDDCExpc(Format("Error! Cannot open %s", containerPath.c_str()));
        };
    }
    else if (containerPath == "-"){
        IsStdin = true;
    }

};

extern string ReadTabFormatDocumentName(const string& line);
void CDocumentIterator::ReadTabFormatDocument(CIndexDocument& doc) {
    if (TabFormatStream == NULL) {
        assert (!IsTarFile(ContainerPath));
        TabFormatStream = IsStdin ? stdin : fopen(ContainerPath.c_str(), "rb");
        if (!TabFormatStream) throw CDDCExpc (Format("Cannot open file \"%s\"", ContainerPath.c_str()));
    }

    const size_t MaxTabFormatLine = MaxBiblStringLen  + 255; // 20000 + 250
    char buffer[MaxTabFormatLine];
    doc.CorpusFileName = LastReadCorpusFileName;
    while (fgets(buffer, MaxTabFormatLine, TabFormatStream)) {
        rtrim(buffer);
        string line  = buffer;
        string docName = ReadTabFormatDocumentName(line);
        if (!docName.empty()) {
            //-- log document boundaries (for streaming import)
            ddcLogDebug("reading document "+docName);

            if (LastReadCorpusFileName.empty()) {
                // initial document in stream
                doc.CorpusFileName = docName;
                LastReadCorpusFileName = docName;
            }
            else {
                // non-initial document in stream
                LastReadCorpusFileName = docName;
                return;
            }
        }
        else {
            doc.DocumentLines.push_back(line);
        }
    }
    fclose (TabFormatStream);
    Finished = true;
}

bool CDocumentIterator::NextDocument(CIndexDocument& doc) {
    if (Finished) {
        return false;
    }
    doc.Initialize(Parent);
    if (Parent->UseTabFormatForLoading()) {
        ReadTabFormatDocument(doc);
    }
    else  if (Tar) {
        if (!tar_get_next_file(Tar, doc.CorpusFileName, doc.DocumentBuffer)) {
            tar_close(Tar);
            Finished = true;
            return false; // end of container
        }
        doc.CorpusFileName = ContainerPath + ":" + doc.CorpusFileName;
    } else {
        doc.CorpusFileName = ContainerPath;
        ReadVector(doc.CorpusFileName, doc.DocumentBuffer);
        Finished = true;
    }
    doc.NormalizeDocumentBuffer();
    return true;
}

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
