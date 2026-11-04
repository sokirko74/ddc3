#ifndef PROJECT_TABFORMATINDEXATOR_H
#define PROJECT_TABFORMATINDEXATOR_H


#include "Concordance.h"

class CIndexDocument;
class CTabFormattedMetaParams;

class CTabFormatIndexator : public CConcordance {

    PtrHolder<CBibliography> PrevBibl;

    void AddColumnMap (const std::string& field, const std::string& value,  CTabFormattedMetaParams* params);

    void ProcessMetaField(CIndexDocument* document, const std::string &line, CTabFormattedMetaParams* params);

    void ProcessBreakRecord(CIndexDocument* document, const std::string &line, CTabFormattedMetaParams* params);

    void ProcessToken (CIndexDocument* document, const std::string& line);

protected:
    void IndexTabFormat(CIndexDocument* document);
public:

};
extern  std::string ReadTabFormatDocumentName(const std::string& line);


#endif //PROJECT_TABFORMATINDEXATOR_H
