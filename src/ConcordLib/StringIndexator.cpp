#include "StdConc.h"
#include "ConcCommon.h"
#include "StringIndexator.h"


using namespace std;

CStringIndexator::CStringIndexator() {
    m_Path = "#empty_path";
    m_bMemoryMap = false;
    m_MaxRegExpExpansionSize = 1000000;
    m_pChunkIndex = NULL;
};

CStringIndexator::~CStringIndexator() {
    ClearStringIndices();

};

void CStringIndexator::SetPath(string Path) {
    m_Path = Path;
};

void CStringIndexator::ClearStringIndices() {
    for (size_t i = 0; i < m_Indices.size(); i++)
        delete m_Indices[i];
    m_Indices.clear();
};

bool CStringIndexator::RegisterChunkIndex() {
    if (GetIndexByAlias(ChunkIndexName))
        return false; // no one should use this name

    m_pChunkIndex = new CStringIndexSet(this);
    m_pChunkIndex->InitIndexSet(ChunkIndexName, ChunkIndexName, false, false);
    m_Indices.push_back(m_pChunkIndex);
    return true;
};

CStringIndexSet *CStringIndexator::GetTokenIndex() {
    return m_Indices[0];
}

const CStringIndexSet *CStringIndexator::GetTokenIndex() const {
    return m_Indices[0];
}

bool CStringIndexator::RegisterStringIndices(const string &IndicesStr) {
    ClearStringIndices();
    // to be done[name,short,archive]
    StringTokenizer tok(IndicesStr.c_str(), ";");
    while (tok()) {
        string Item = tok.val();
        Trim(Item);
        if ((Item.empty()) || (Item[0] != '[') || (Item[Item.length() - 1] != ']')) {
            ErrorMessage("A bad format of Indices Header !" + IndicesStr);
            return false;
        };
        Item = Item.substr(1, Item.length() - 2);
        StringTokenizer item_tok(Item.c_str(), " \t,");
        string Name = item_tok.next_token();
        string Short = item_tok.next_token();
        string CompressedStr = item_tok.next_token();
        string StorageStr = item_tok.next_token();
        if (Name.empty() || Short.empty() || CompressedStr.empty()) {
            ErrorMessage("A bad format of Indices Header !" + Item);
            return false;
        };

        bool bCompressed = true;

        if (CompressedStr == "archive")
            bCompressed = true;
        else if (CompressedStr == "normal")
            bCompressed = false;
        else {
            ErrorMessage("A bad format of Indices Header :" + Item);
            return false;
        };
        bool bStorage = m_Indices.empty();
        if (StorageStr != "") {
            if (StorageStr == "storage")
                bStorage = true;
            else if (StorageStr == "storage_omit")
                bStorage = false;
            else {
                ErrorMessage("A bad format of index header (storage specifier has wrong format) :" + Item);
                return false;
            }
        }

        if (GetIndexByAlias(Name)) {
            ErrorMessage("Error: multiple declarations of index name `%s'");
            ClearStringIndices();
            assert (false);
            return false;

        }

        CStringIndexSet *R = new CStringIndexSet(this);
        R->InitIndexSet(Name, Short, bStorage, bCompressed);
        m_Indices.push_back(R);

        //-- register alias
        RegisterIndexAlias(Name, R);
        RegisterIndexAlias(Short, R);
    };

    return true;
};

bool CStringIndexator::RegisterIndexAliases(const string &IndexAliasStr) {
    bool rc = true;
    StringTokenizer lines(IndexAliasStr.c_str(), "\n");
    while (lines()) {
        string Item = lines.val();
        Trim(Item);
        if (Item.empty()) continue;
        StringTokenizer fields(Item.c_str(), " \t\r\n");
        string AliasOp = fields.next_token();
        string AliasFrom = fields.next_token();
        string AliasTo = fields.next_token();
        if (AliasFrom.empty() || AliasTo.empty()) {
            ddcLogWarn(Format("Warning: failed to parse index alias declaraction `%s' - skipping", Item.c_str()));
            continue;
        }
        rc = (rc && RegisterIndexAlias(AliasFrom, AliasTo));
    }
    return rc;
}

bool CStringIndexator::RegisterIndexAlias(const string &AliasFrom, const string &AliasTo) {
    CStringIndexSet *idx = GetIndexByAlias(AliasTo);
    if (idx == NULL)
        ddcLogWarn(Format("Warning: cannot resolve target label `%s' for index alias `%s' -> `%s'",
                          AliasTo.c_str(), AliasFrom.c_str(), AliasTo.c_str()));
    m_IndexAlias[AliasFrom] = AliasTo; //-- remember alias topology, e.g. for GetIndexAliasString()
    RegisterIndexAlias(AliasFrom, idx);
    return true;
}

void CStringIndexator::RegisterIndexAlias(const string &AliasFrom, CStringIndexSet *idx) {
    CStringIndexSet *oldi = GetIndexByAlias(AliasFrom);
    if (oldi != NULL) {
        if (idx == NULL) {
            ddcLogWarn(Format("Warning: deleting index label `%s' (-> `%s')",
                              AliasFrom.c_str(), oldi->m_Name.c_str()));
        } else {
            ddcLogWarn(Format("Warning: overriding old target `%s' for index label `%s' (-> `%s')",
                              oldi->m_Name.c_str(), AliasFrom.c_str(), idx->m_Name.c_str()));
        }
        m_IndexMap.erase(AliasFrom);
    }
    if (idx != NULL)
        m_IndexMap[AliasFrom] = idx;
}


string CStringIndexator::GetIndicesString() const {
    string Result;
    for (size_t i = 0; i < m_Indices.size(); i++) {
        if (m_Indices[i]->m_Name != ChunkIndexName)
            Result += Format("[%s %s %s %s];",
                             m_Indices[i]->m_Name.c_str(),
                             m_Indices[i]->m_ShortName.c_str(),
                             (m_Indices[i]->m_bCompressOccurrences ? "archive" : "normal"),
                             (m_Indices[i]->m_bUseItemStorage ? "storage" : "storage_omit"));
    };
    Trim(Result);
    return Result;
};


string CStringIndexator::GetIndexAliasString() const {
    string Result;
    for (IndexAliasMap::const_iterator ai = m_IndexAlias.begin(); ai != m_IndexAlias.end(); ++ai)
        Result += string("IndexAlias ") + ai->first + " " + ai->second + "\n";
    return Result;
}


bool CStringIndexator::StartIndexing(string Path) {
    m_Path = Path;

    for (size_t i = 0; i < m_Indices.size(); i++)
        if (!m_Indices[i]->CreateTempFiles(Path))
            return false;


    return true;
};

void CStringIndexator::TerminateIndexing() {
    for (size_t i = 0; i < m_Indices.size(); i++)
        m_Indices[i]->DeleteTempFiles();
};


bool CStringIndexator::FinalSaveAllIndices(bool bAfterLoading) {
    for (size_t i = 0; i < m_Indices.size(); i++) {
        if (!m_Indices[i]->WriteToFile(bAfterLoading))
            return false;
    }

    if (!WriteVector(GetSearchPeriodsFileName().c_str(), m_SearchPeriods)) return false;

    return true;
};

void CStringIndexator::IndexTokenFixLongColumns(const size_t MaxLen, const size_t nCols, const char *InputLine, char *Out)
{
    //-- get column start & end positions
    //const char globalFieldDelimeter = '\t'; //-- ddc global constant
    char delims[2] = { globalFieldDelimeter, '\0' };
    vector<string> cols = stringSplit(InputLine, delims);  

    //-- force number of columns
    if (cols.size() != nCols)
        cols.resize(nCols);

    //-- get relative overflow
    size_t clmax  = (MaxLen-nCols) / nCols;
    double ldiff  = strlen(InputLine) - MaxLen + 1;
    vector<double> cldiff(nCols,0);
    double cldtotal = 0;
    for (int i=0; i < nCols; ++i) {
        cldiff[i] = (cols[i].length() >= clmax ? (cols[i].length() - clmax) : 0);
        cldtotal += cldiff[i];
    }

    //-- truncate columns independently, proportional to their relative overflow
    for (int i=0; i < nCols; ++i) {
        if (cldiff[i] == 0) continue;
        size_t clen  = cols[i].length();
        size_t ctrim = clen - ( cldiff[i]/cldtotal * ldiff + 0.5 );
        cols[i].resize(ctrim);
        if (cols[i].length() > 3) {
            cols[i].replace(cols[i].length()-3, 3, 3, '.');
        }
        ddcLogWarn(Format("Warning: truncated %zd suffix byte(s) from greedy column #%d -> \"%s\"", clen-ctrim, i, cols[i].c_str()));
    }

    //-- construct output string
    char *outp = Out;
    for (int i=0; i < nCols; ++i, ++outp) {
        strcpy(outp, cols[i].c_str());
        outp += cols[i].length();
        assert(outp < (Out+MaxLen));
        *outp = '\t';
    }
    *(--outp) = '\0';
}

void CStringIndexator::IndexOneToken(CTokenIndexator *document, const char *InputLine, bool tryFixErrors) {
    assert (!m_Indices.empty());

    size_t length = strlen(InputLine);
    if (length == 0) {
        throw CDDCExpc("Error! CStringIndexator::IndexOneToken cannot index empty lines");
    };

    const size_t MaxIndexLineLength = DDC_STATIC_BUFLEN;
    char Line[MaxIndexLineLength];

    if (length >= MaxIndexLineLength) {
        if (!tryFixErrors)
            throw CDDCExpc(Format("Error! Line \"%s\" is too long! It cannot be more than %zi chars", InputLine, MaxIndexLineLength));

        ddcLogWarn(Format("Warning: truncating greedy colums for input line \"%s\" (length=%zd > max=%zd)", InputLine, length, MaxIndexLineLength));
        IndexTokenFixLongColumns(MaxIndexLineLength, document->ColumnMap.size(), InputLine, Line);
        length = strlen(Line);
        //ddcLogWarn(Format("DEBUG: got truncated line of length %zd: %s\n", length, Line));
    } else {
        strcpy(Line, InputLine);
    }


    size_t columnNo = 0;
    vector<CTokenNo> occurrences(1, document->CorpusEndTokenNo);

    for (size_t start = 0; start < length; start++) {
        if (columnNo == document->ColumnMap.size()) {
            if (!tryFixErrors)
                throw CDDCExpc(Format("Too many columns at line at line \"%s\", starting at \"%s\"", Line, Line+start));
            ddcLogWarn(Format("Warning: ignoring extra column(s) in line \"%s\" starting at \"%s\"", Line, Line+start));
            break;
        };

        size_t end = start;
        for (; end < length && (Line[end] != globalFieldDelimeter); end++);
        int len = end - start;
        Line[end] = 0;

        document->ColumnMap[columnNo]->InsertToInputLoadIndex(Line + start, len, occurrences);


        columnNo++;
        start = end;
    };

    // DDC has to insert a stub to each indices with storages in order to maintain
    // so all storage files should be of the same size
    for (; columnNo < document->ColumnMap.size(); columnNo++) {
        CStringIndexSet *i = document->ColumnMap[columnNo];
        if (i->m_bUseItemStorage)
            i->InsertToInputLoadIndex(ddc_archive_stub, strlen(ddc_archive_stub), occurrences);
    }

    // DDC has to insert a stub to each indices with storages in order to maintain
    // so all storage files should be of the same size
    for (size_t i = 0; i < document->AbsentIndices.size(); i++) {
        CStringIndexSet *index = document->AbsentIndices[i];
        if (index->m_bUseItemStorage)
            index->InsertToInputLoadIndex(ddc_archive_stub, strlen(ddc_archive_stub), occurrences);
    }
};


bool CStringIndexator::AddInputLoadIndexToMemoryLoadIndex() {
    try {
        for (size_t i = 0; i < m_Indices.size(); i++)
            if (!m_Indices[i]->AddInputLoadIndexToMemoryLoadIndex())
                return false;

        return true;
    }
    catch (...) {
        fprintf(stderr, "exception in CStringIndexator::AddInputLoadIndexToMemoryLoadIndex\n");
        return false;
    }
};


bool CStringIndexator::AddMemoryLoadIndexToMainLoadIndex() {
    for (size_t i = 0; i < m_Indices.size(); i++)
        if (!m_Indices[i]->AddMemoryLoadIndexToMainLoadIndex())
            return false;

    return true;
};


bool CStringIndexator::SaveMemoryLoadIndex() {
    for (size_t i = 0; i < m_Indices.size(); i++)
        if (!m_Indices[i]->SaveMemoryLoadIndex())
            return false;

    return true;
};

CStringIndexSet *CStringIndexator::GetIndexByName(const string &Name) {
    for (size_t i = 0; i < m_Indices.size(); i++)
        if (m_Indices[i]->m_Name == Name) {
            return m_Indices[i];
        };
    return 0;
};

CStringIndexSet *CStringIndexator::GetIndexByNameOrShortName(const string &Name) {
    for (size_t i = 0; i < m_Indices.size(); i++)
        if ((m_Indices[i]->m_Name == Name)
            || (m_Indices[i]->m_ShortName == Name)
            ) {
            return m_Indices[i];
        };
    return 0;
};

CStringIndexSet *CStringIndexator::GetIndexByAlias(const string &Alias) const {
    IndexMap::const_iterator ai = m_IndexMap.find(Alias);
    if (ai != m_IndexMap.end())
        return ai->second;
    return NULL;
};


string CStringIndexator::GetSearchPeriodsFileName() const {
    return MakeFName(m_Path, "_periods");
};

void CStringIndexator::ReadIndicesFromTheDisk() {
    ReadVector(GetSearchPeriodsFileName().c_str(), m_SearchPeriods);

    for (size_t i = 0; i < m_Indices.size(); i++)
        m_Indices[i]->ReadFromTheDisk();
};

bool CStringIndexator::DestroyIndices() {
    for (size_t i = 0; i < m_Indices.size(); i++)
        if (!m_Indices[i]->DestroyIndexSet())
            return false;


    return true;
};


size_t CStringIndexator::GetSearchPeriodsCount() const {
    return m_SearchPeriods.size();
};
