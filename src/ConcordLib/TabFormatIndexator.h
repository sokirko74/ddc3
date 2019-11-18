//
// Created by sokirko on 05.10.19.
//

#ifndef PROJECT_TABFORMATINDEXATOR_H
#define PROJECT_TABFORMATINDEXATOR_H


#include "Concordance.h"

class CIndexDocument;
class CTabFormattedMetaParams;

class CTabFormatIndexator : public CConcordance {

    PtrHolder<CBibliography> PrevBibl;

    void AddColumnMap (const string& field, const string& value,  CTabFormattedMetaParams* params);

    void ProcessMetaField(CIndexDocument* document, const string &line, CTabFormattedMetaParams* params);

    void ProcessBreakRecord(CIndexDocument* document, const string &line, CTabFormattedMetaParams* params);

    void ProcessToken (CIndexDocument* document, const string& line);

protected:
    void IndexTabFormat(CIndexDocument* document);
public:

};
extern  string ReadTabFormatDocumentName(const string& line);


#endif //PROJECT_TABFORMATINDEXATOR_H

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
