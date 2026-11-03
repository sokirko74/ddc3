//
// Created by sokirko on 05.10.19.
//

#include "TabFormatIndexator.h"
#include "DocumentIterator.h"

const string COMMENT_STARTER = "%%";
const string CMD_STARTER = "%%$DDC:";
const string META_STARTER = "%%$DDC:meta.";
const string BREAK_STARTER = "%%$DDC:BREAK.";
const string META_FILE_DELIMITER = "%%$DDC:meta.file_";
const string INDEX_FIELD_STARTER = "%%$DDC:index";
const string BIBL_SCAN = "%%$DDC:meta.scan_";
const string BIBL_ORIG = "%%$DDC:meta.orig_";
const string BIBL_DATE = "%%$DDC:meta.date_";
const string BIBL_PAGE = "%%$DDC:meta.page_";
const string META_N = "%%$DDC:meta.n_";
const string TOKID_STARTER = "%%$DDC:tokid."; //-- ignored
const string PAGE_BREAK = "%%$DDC:PAGE";

const char EQU_CHAR = '=';

struct CTabFormattedMetaParams {
    vector<CStringIndexSet*> FoundDocColumnDeclarations;
    CBibliography Bibl;
};


void CTabFormatIndexator::AddColumnMap (const string& field, const string& value,  CTabFormattedMetaParams* params) {
    {
        int indexInBrackets;
        size_t afterBrackets = field.find('[');
        if (afterBrackets == string::npos || afterBrackets + 1 == field.size())
            throw CDDCExpc(Format("bad format at line starting with %s", field.c_str()));
        indexInBrackets = atoi (field.c_str() + afterBrackets + 1);
        if (indexInBrackets != params->FoundDocColumnDeclarations.size()) {
            throw CDDCExpc(Format("Bad order in index declaration %s ", field.c_str()));
        }
    }
    string indexName;
    {
        int i = value.find(' ');
        indexName = value.substr(0, i);
    }
    CStringIndexSet* indexSet = GetIndexByNameOrShortName(indexName);
    if (!indexSet) throw CDDCExpc(Format("Cannot find index %s in opt file", value.c_str()));
    params->FoundDocColumnDeclarations.push_back(indexSet);
}

void CTabFormatIndexator::ProcessBreakRecord (CIndexDocument* document, const string& line, CTabFormattedMetaParams* params) {
    int equDelim = line.find(EQU_CHAR);
    string field = (equDelim == -1) ? line : line.substr(0, equDelim);
    //  ignore  numbers in breaks
    string breakName = field.substr(BREAK_STARTER.length());
    int bracketIndex = breakName.find('[');
    if (bracketIndex != -1) {
        breakName.erase(bracketIndex);
    }
    if (breakName != PredefinedFileBreakName) {
        AddBreakByName(breakName, document->CorpusEndTokenNo);
    }
}

void CTabFormatIndexator::ProcessMetaField (CIndexDocument* document, const string& line, CTabFormattedMetaParams* params) {
    int equDelim = line.find(EQU_CHAR);

    if (equDelim == -1) {
        throw CDDCExpc(Format("In line %s cannot find '%c' ", line.c_str(), EQU_CHAR));
    }
    string field = line.substr(0, equDelim);
    string value =  line.substr(equDelim + 1);
    Trim(value);

    // todo inheritance from the previous file
    if (StartsWith(field, INDEX_FIELD_STARTER)) {
        AddColumnMap(field, value, params);
    }
    else if (field == BIBL_SCAN) {
        params->Bibl.m_ScanBibl = value;
    }
    else if (field == BIBL_ORIG) {
        params->Bibl.m_OrigBibl = value;
    }
    else if (field == BIBL_DATE) {
        params->Bibl.m_DateStr = value;
    }
    else if (field == BIBL_PAGE) {
        params->Bibl.m_StartPageInfo = atoi(value.c_str());
    }
    else if (field == PAGE_BREAK) {
        CPageNumber p;
        p.m_PageNumber = atoi (value.c_str());
        if (p.m_PageNumber  == 0) {
            throw CDDCExpc(Format("In line %s cannot parse page number (0 is not allowed) ", line.c_str()));
        }
        p.m_StartTokenNo = document->CorpusEndTokenNo;
        AddPageBreak(p);
    }
    else if (field == META_N) {
        // nothing to store
    }
    else if (StartsWith(field, TOKID_STARTER)) {
        // ignored
    }
    else if (StartsWith(field, BREAK_STARTER)) {
        // if with '=', then ignore value
        string breakName = field.substr(BREAK_STARTER.length());
        AddBreakByName(breakName, document->CorpusEndTokenNo);
    }
    else if (StartsWith(field, META_STARTER)) {
        // free bibl index
        string indexName = field.substr(META_STARTER.length());
        m_BiblIndex.SetFreeBiblByName(indexName, value, params->Bibl);
    }
    else {
        // unrecognized "%%DDC:" instruction: ignored
        ddcLogTrace("ignoring unrecognized instruction `"+line+"'");
        ++document->DroppedLinesCount;
    }

}

void CTabFormatIndexator::ProcessToken (CIndexDocument* document, const string& line) {
    IndexOneToken(document, line.c_str(), m_bResumeOnIndexErrors);
    document->CorpusEndTokenNo ++;
}

string ReadTabFormatDocumentName(const string& line) {
    if (StartsWith(line, META_FILE_DELIMITER)) {
        int index = line.find(EQU_CHAR);
        if (index == string::npos) throw CDDCExpc(Format("bad format at line %s", line.c_str()));
        string s = line.substr(index  + 1);
        Trim(s);
        return s;
    }
    return "";
}


void CTabFormatIndexator::IndexTabFormat(CIndexDocument* document) {
    if (PrevBibl.Get() == 0) {
        PrevBibl.Reset(new  CBibliography());
        PrevBibl.Get()->CleanBibliography();
        m_BiblIndex.SetFreeBiblAttribsEmpty(*PrevBibl.Get());
    }
    CTabFormattedMetaParams params;
    params.Bibl = *PrevBibl.Get(); // inherit all attributes from the previous document

    bool inDocumentHeader = true;
    for (size_t i = 0; i < document->DocumentLines.size(); ++i) {
        string& line  = document->DocumentLines[i];
        Trim(line);
        if (line.empty()) continue;
        if (StartsWith(line, BREAK_STARTER)) {
            if (!inDocumentHeader) {
                ProcessBreakRecord(document, line, &params);
            }
        }
        else if (StartsWith(line, CMD_STARTER)) {
            ProcessMetaField(document, line, &params);
        }
        else if (StartsWith(line, COMMENT_STARTER)) {
            //-- other comment: ignore
        }
        else {
            if (inDocumentHeader) {
                if (!params.FoundDocColumnDeclarations.empty()) {
                    document->CustomColumnMap(this, params.FoundDocColumnDeclarations);
                }
            }
            ProcessToken(document, line);
            inDocumentHeader = false;
        }
    }
    m_BiblIndex.AddIndexItem(params.Bibl);
    *PrevBibl.Get() = params.Bibl;
    EndTextAreaBorders(document->CorpusEndTokenNo);
    if (document->DroppedLinesCount > 0) {
        ddcLogDebug(Format("ignored %i line(s) in document %s",
                           document->DroppedLinesCount, document->CorpusFileName.c_str()));
    }
};

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
