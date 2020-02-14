//
// Created by sokirko on 10.10.19.
//

#include "FreeBiblIndex.h"


CFreeBiblIndex::CFreeBiblIndex() {}

CFreeBiblIndex::~CFreeBiblIndex() {}

void CFreeBiblIndex::clear() {
    m_bShowInHeader = false;
    m_ValuesForEachFile.clear();
}

string CFreeBiblIndex::GetStringValue(DWORD FileNo) const {
    return Format("%i", (int) m_ValuesForEachFile[FileNo]);
}

int CFreeBiblIndex::GetIntegerValue(DWORD FileNo) const {
    return m_ValuesForEachFile[FileNo];
}


void CFreeBiblIndex::ReadFromDisk(string Path, DWORD FileBreaksSize, bool useMMap) {
    m_ValuesForEachFile.open(GetIndexFileName(Path), useMMap);


    if (m_ValuesForEachFile.size() != FileBreaksSize) {
        throw CExpc(
            Format("The number of corpus files (%zi) should be equal to the number of bibliographical records (%zi; index name = %s)",
                   FileBreaksSize, m_ValuesForEachFile.size(), m_Name.c_str()));
    };
}

string CFreeBiblIndex::GetDescriptionStr() const {
    return Format("%s %s %i %s %s",
                  FreeBiblAttribOptionFieldName.c_str(), this->GetTypeStr().c_str(),
                  m_bShowInHeader ? 1 : 0, m_Name.c_str(), this->GetXpathStr().c_str());
}

string CFreeBiblIndex::GetIndexFileName(string Path) const {
    return MakeFName(Path, string("_bibl_") + m_Name + "_integers");
}

void CFreeBiblIndex::CreateUnion(const string &Path, const vector<const CFreeBiblIndex *> &Indices,
                                 const vector<size_t> &FileCounts) {
    m_ValuesForEachFile.clear();
    m_ValuesForEachFile.ensureVec();
    for (size_t i = 0; i < Indices.size(); ++i) {
        if (Indices[i] != NULL) {
            m_ValuesForEachFile.m_vec.insert(m_ValuesForEachFile.m_vec.end(), Indices[i]->m_ValuesForEachFile.begin(),
                                             Indices[i]->m_ValuesForEachFile.end());
        } else {
            m_ValuesForEachFile.m_vec.resize(m_ValuesForEachFile.m_vec.size() + FileCounts[i], 0);
        }
    }
    m_ValuesForEachFile.ensureData();
    m_ValuesForEachFile.save(GetIndexFileName(Path));
}

void CFreeBiblIndex::CreatePartitions(vector<CFreeBiblIndex *> &Parts, const vector<string> &Paths,
                                      const vector<DWORD> &EndFileNo) const {
    assert(Parts.size() == Paths.size());
    assert(Parts.size() == EndFileNo.size());
    for (size_t i = 0; i < Parts.size(); ++i) {
        Parts[i]->m_ValuesForEachFile.clear();
        Parts[i]->m_ValuesForEachFile.ensureVec();
        Parts[i]->m_ValuesForEachFile.m_vec.assign(m_ValuesForEachFile.begin() + (i == 0 ? 0 : EndFileNo[i - 1]),
                                                   m_ValuesForEachFile.begin() + EndFileNo[i]);
        Parts[i]->m_ValuesForEachFile.ensureData();
        Parts[i]->m_ValuesForEachFile.save(Parts[i]->GetIndexFileName(Paths[i]));
    }
}


bool CFreeBiblIndex::GetFilterBounds(CDDCFilterWithBounds &Filter, const string &LoValue,
                                     const string &HiValue) const {
    Filter.m_bSet = false;
    Filter.m_KeyLo = LoValue.empty() ? INT_MIN : atoi(LoValue.c_str());
    Filter.m_KeyHi = HiValue.empty() ? INT_MAX : atoi(HiValue.c_str());
    Filter.m_BiblIndex = this;
    return true;
}

bool CFreeBiblIndex::GetFilterValue(CDDCFilterWithBounds &Filter, const string &Value) const {
    Filter.m_bSet = false;
    Filter.m_KeyLo = atoi(Value.c_str());
    Filter.m_KeyHi = Filter.m_KeyLo.i + 1;
    Filter.m_BiblIndex = this;
    return true;
}

bool CFreeBiblIndex::GetFilterValues(CDDCFilterWithBounds &Filter, const string &Regex) const {
    throw CExpc(errLogic, "%s::GetFilterValues(): field `%s' doesn't support regular expressions", typeid(*this).name(),
                m_Name.c_str());
    return false;
}

bool CFreeBiblIndex::GetFilterValues(CDDCFilterWithBounds &Filter, const set<string> &Values) const {
    throw CExpc(errLogic, "%s::GetFilterValues(): field `%s' doesn't support set values", typeid(*this).name(),
                m_Name.c_str());
    return false;
}

bool CFreeBiblIndex::FileMatches(DWORD FileNo, const CDDCFilterWithBounds &Filter) const {
    // + 2019-08-15 moocow
    //   - val: cast to int so it jives with CHitSortKey::i (avoid signed/unsigned comparison)
    //   - should fixes bogus empty responses from e.g. "count(* #asc[author]) #by[textClass]"
    int val = this->GetIntegerValue(FileNo);
    return (Filter.m_bSet
            ? (Filter.m_SatisfiedValues.find(val) != Filter.m_SatisfiedValues.end())
            : ((val >= Filter.m_KeyLo.i) && (val < Filter.m_KeyHi.i))
        );
}

void CFreeBiblIndex::RegisterBiblStringItemId(const string &ValueStr) {
    int u = ValueStr.empty() ? 0 : atoi(ValueStr.c_str());
    m_ValuesForEachFile.push_back(u);
}


bool CFreeBiblIndex::DeleteBiblFiles(string Path) const {
    return remove(GetIndexFileName(Path).c_str()) == 0;
}


bool CFreeBiblIndex::ConvertAndSaveToDiskAfterIndexing(string Path) {
    m_ValuesForEachFile.ensureVec();
    return WriteVector(GetIndexFileName(Path), m_ValuesForEachFile.m_vec);
}

string CFreeBiblIndex::GetTypeStr() const {
    return IntegerTypeStr;
}

CFreeBiblIndexTypeId CFreeBiblIndex::GetTypeId() const {
    return cfbiInteger;
}

const string &CFreeBiblIndex::GetXpathStr() const {
    return m_Xpath;
}

DWORD CFreeBiblIndex::GetIntegerLowerBound(const string &Value) const {
    return Value.empty() ? 0 : hex2int(Value);
}

//=============================================

CFreeBiblStringIndex::CFreeBiblStringIndex() {

}

CFreeBiblStringIndex::~CFreeBiblStringIndex() {
};

void CFreeBiblStringIndex::clear() {
    CFreeBiblIndex::clear();
    m_BuildStringItemsMap.clear();
    m_BuildStringItemsSize = 0;
    m_ValuesE.clear();
};

string CFreeBiblStringIndex::GetStringValue(DWORD FileNo) const {
    return m_ValuesE[m_ValuesForEachFile[FileNo]];
};

string CFreeBiblStringIndex::GetStringFileName(string Path) const {
    return MakeFName(Path, string("_bibl_") + m_Name + "_strings");
};

bool CFreeBiblStringIndex::DeleteBiblFiles(string Path) const {
    return remove(GetStringFileName(Path).c_str()) == 0
        && CFreeBiblIndex::DeleteBiblFiles(Path);
};

void CFreeBiblStringIndex::ReadBiblStringItems(string FileName, bool useMMap) {
    m_ValuesE.open(FileName + "_values", FileName + "_idx", FileName, useMMap);
};

bool CFreeBiblStringIndex::WriteBiblStringItems(const vector<string> &Set, string FileName) const {
    string ValuesFile = FileName + "_values";
    FILE *vfp = fopen(ValuesFile.c_str(), "wb");
    if (!vfp) {
        ddcLogError(Format("CFreeBiblStringIndex::WriteBiblStringItems(): open failed for '%s': %s",
                           ValuesFile.c_str(), strerror(errno)));
        return false;
    }

    string IndexFile = FileName + "_idx";
    FILE *ifp = fopen(IndexFile.c_str(), "wb");
    if (!ifp) {
        ddcLogError(Format("CFreeBiblStringIndex::WriteBiblStringItems(): open failed for '%s': %s",
                           IndexFile.c_str(), strerror(errno)));
        return false;
    }

    for (size_t i = 0; i < Set.size(); i++) {
        ddcStringEnum<>::OffT pos = ftell(vfp);
        fwrite(&pos, sizeof(ddcStringEnum<>::OffT), 1, ifp);
        fwrite(Set[i].c_str(), 1, Set[i].size() + 1, vfp);
    }

    fclose(ifp);
    fclose(vfp);
    return true;
};

string CFreeBiblStringIndex::GetTypeStr() const {
    return StringTypeStr;
};

CFreeBiblIndexTypeId CFreeBiblStringIndex::GetTypeId() const {
    return cfbiString;
};


void CFreeBiblStringIndex::ReadFromDisk(string Path, DWORD FileBreaksSize, bool useMMap) {
    ReadBiblStringItems(GetStringFileName(Path), useMMap);
    CFreeBiblIndex::ReadFromDisk(Path, FileBreaksSize, useMMap);
}

void CFreeBiblStringIndex::CreateUnion(const string &Path, const vector<const CFreeBiblIndex *> &Indices,
                                       const vector<size_t> &FileCounts) {
    assert(Indices.size() == FileCounts.size());

    //-- cast arguments to CFreeBiblStringIndex
    vector<const CFreeBiblStringIndex *> sIndices(Indices.size());
    for (size_t i = 0; i < Indices.size(); ++i) {
        sIndices[i] = (const CFreeBiblStringIndex *) Indices[i];
    }

    //-- get set of all values (expensive)
    set<string> values;
    string s;
    for (size_t i = 0; i < sIndices.size(); ++i) {
        if (sIndices[i] == NULL) {
            if (values.find("") == values.end()) values.insert("");
            continue;
        }
        for (size_t j = 0; j < sIndices[i]->m_ValuesE.size(); ++j) {
            s = sIndices[i]->m_ValuesE[j];
            if (values.find(s) == values.end()) values.insert(s);
        }
    }
    ddcLogDebug(Format("found %zd value type(s) for attribute %s", values.size(), m_Name.c_str()));

    //-- populate m_ValuesE and build translation tables
    m_ValuesE.clear();
    m_ValuesE.ensureVec();
    vector<vector<DWORD> > xlateId(sIndices.size());
    for (size_t i = 0; i < sIndices.size(); ++i) {
        if (sIndices[i] != NULL) xlateId[i].resize(sIndices[i]->m_ValuesE.size());
    }
    for (set<string>::const_iterator si = values.begin(); si != values.end(); ++si) {
        m_ValuesE.m_strings.push_back(*si);
        for (size_t i = 0; i < sIndices.size(); ++i) {
            if (sIndices[i] == NULL) continue;
            DWORD oldId = sIndices[i]->m_ValuesE.find(*si);
            if (oldId != sIndices[i]->m_ValuesE.NO_ID)
                xlateId[i][oldId] = m_ValuesE.m_strings.size() - 1;
        }
    }
    WriteBiblStringItems(m_ValuesE.m_strings, GetStringFileName(Path));
    //CFreeBiblIndex::ConvertAndSaveToDiskAfterIndexing(Path);

    //-- write integers by file (a la CFreeBiblIndex::CreateUnion)
    m_ValuesForEachFile.clear();
    m_ValuesForEachFile.ensureVec();
    size_t voff = 0;
    for (size_t i = 0; i < sIndices.size(); ++i) {
        m_ValuesForEachFile.m_vec.resize(voff + FileCounts[i], 0);
        if (sIndices[i] == NULL) continue;
        for (size_t j = 0; j < sIndices[i]->m_ValuesForEachFile.size(); ++j)
            m_ValuesForEachFile.m_vec[voff + j] = xlateId[i][sIndices[i]->m_ValuesForEachFile[j]];
        voff += FileCounts[i];
    }
    m_ValuesForEachFile.ensureData();
    m_ValuesForEachFile.save(GetIndexFileName(Path));
};


void CFreeBiblStringIndex::CreatePartitions(vector<CFreeBiblIndex *> &Parts, const vector<string> &Paths,
                                            const vector<DWORD> &EndFileNo) const {
    assert(Parts.size() == Paths.size());
    assert(Parts.size() == EndFileNo.size());

    for (size_t i = 0; i < Parts.size(); ++i) {
        ddcLogDebug(
            Format("CFreeBiblStringIndex::CreatePartitions(%s): creating partition #%zd", m_Name.c_str(),
                   i));
        CFreeBiblStringIndex *Part = (CFreeBiblStringIndex *) Parts[i];
        DWORD f_begin = (i == 0 ? 0 : EndFileNo[i - 1]);
        DWORD f_end = EndFileNo[i];

        //-- get item-set for this partition
        set<DWORD> PartItems;
        for (DWORD fi = f_begin; fi < f_end; ++fi) {
            DWORD itemId = m_ValuesForEachFile[fi];
            if (PartItems.find(itemId) == PartItems.end()) PartItems.insert(itemId);
        }

        //-- populate m_ValuesE, build translation table
        Part->m_ValuesE.clear();
        Part->m_ValuesE.ensureVec();
        vector<DWORD> xlateId(m_ValuesE.size(), DWORD_MAX); //-- [oldId] => newId_or_DWORD_MAX
        for (set<DWORD>::const_iterator itemi = PartItems.begin(); itemi != PartItems.end(); ++itemi) {
            xlateId[*itemi] = Part->m_ValuesE.m_strings.size();
            Part->m_ValuesE.m_strings.push_back(m_ValuesE[*itemi]);
        }
        ClearContainer(PartItems);
        Part->WriteBiblStringItems(Part->m_ValuesE.m_strings, Part->GetStringFileName(Paths[i]));

        //-- populate integers by file (a la CFreeBiblIndex::CreatePartitions())
        Part->m_ValuesForEachFile.clear();
        Part->m_ValuesForEachFile.ensureVec();
        Part->m_ValuesForEachFile.m_vec.assign(m_ValuesForEachFile.begin() + f_begin,
                                               m_ValuesForEachFile.begin() + f_end);
        for (vector<DWORD>::iterator vali = Part->m_ValuesForEachFile.m_vec.begin();
             vali != Part->m_ValuesForEachFile.m_vec.end(); ++vali)
            *vali = xlateId[*vali];
        Part->m_ValuesForEachFile.ensureData();
        Part->m_ValuesForEachFile.save(Part->GetIndexFileName(Paths[i]));
    }
};

bool CFreeBiblStringIndex::GetFilterBounds(CDDCFilterWithBounds &Filter, const string &LoValue,
                                           const string &HiValue) const {
    Filter.m_bSet = false;
    Filter.m_BiblIndex = this;

    //-- lower bound
    Filter.m_KeyLo.assign(INT_MIN, LoValue);
    if (!LoValue.empty()) {
        DWORD ilo = m_ValuesE.lower_bound(LoValue);
        Filter.m_KeyLo.i = (ilo != m_ValuesE.NO_ID ? ilo : INT_MAX);
    }

    //-- upper bound
    Filter.m_KeyHi.assign(INT_MAX, HiValue);
    if (!HiValue.empty()) {
        DWORD ihi = m_ValuesE.upper_bound(HiValue);
        Filter.m_KeyHi.i = (ihi != m_ValuesE.NO_ID ? ihi : m_ValuesE.size());
    }

    return true;
}

DWORD CFreeBiblStringIndex::GetIntegerLowerBound(const string &Value) const {
    if (Value.empty())
        return INT_MIN;

    DWORD ilo = m_ValuesE.lower_bound(Value);
    return (ilo != m_ValuesE.NO_ID ? ilo : INT_MAX);
}

bool CFreeBiblStringIndex::GetFilterValue(CDDCFilterWithBounds &Filter, const string &Value) const {
    Filter.m_bSet = false;
    Filter.m_BiblIndex = this;

    if (Value.empty()) return true; //-- compatibility

    if (Filter.m_bNegated) {
        //-- negative filter condition (literal): generate regex
        return GetFilterValues(Filter, string("^") + escapeRegex(Value) + "$");
    }

    //-- positive filter condition (literal)
    DWORD id = m_ValuesE.find(Value);
    if (id == m_ValuesE.NO_ID) {
        Filter.m_KeyLo = 0;
        Filter.m_KeyHi = 0;
    } else {
        Filter.m_KeyLo.assign(id, Value);
        Filter.m_KeyHi.assign(Filter.m_KeyLo.i + 1, Value);
    }

    return true;
};

bool CFreeBiblStringIndex::GetFilterValues(CDDCFilterWithBounds &Filter, const string &Regex) const {
    RML_RE re(Regex, *m_pRegexOpts);
    size_t Count = m_ValuesE.size();

    //-- regex condition: positive or negative
    Filter.m_bSet = true;
    Filter.m_BiblIndex = this;
    for (size_t i = 0; i < Count; i++) {
        bool isMatch = re.PartialMatch(m_ValuesE[i]);
        if (Filter.m_bNegated ? (!isMatch) : isMatch)
            Filter.m_SatisfiedValues.insert(i);
    }

    //-- sanitize filter ranges (compatibility)
    if (Filter.m_SatisfiedValues.empty()) {
        Filter.m_KeyLo = 0;
        Filter.m_KeyHi = 0;
    } else {
        Filter.m_KeyLo.i = *Filter.m_SatisfiedValues.begin();
        Filter.m_KeyLo.s = m_ValuesE[Filter.m_KeyLo.i];

        Filter.m_KeyHi.i = *Filter.m_SatisfiedValues.rbegin();
        Filter.m_KeyHi.s = m_ValuesE[Filter.m_KeyHi.i];
        Filter.m_KeyHi.i++;
    }

    return true;
};

bool CFreeBiblStringIndex::GetFilterValues(CDDCFilterWithBounds &Filter, const set<string> &Values) const {
    Filter.m_bSet = true;
    Filter.m_BiblIndex = this;

    if (!Filter.m_bNegated) {
        //-- set-valued condition: positive: iterate over argument values (assume |Values| << |m_Values|)
        for (set<string>::const_iterator vali = Values.begin(); vali != Values.end(); ++vali) {
            DWORD it = m_ValuesE.find(*vali);
            if (it != m_ValuesE.NO_ID)
                Filter.m_SatisfiedValues.insert(it);
        }
    } else {
        //-- set-valued condition: negative: iterate over indexed values (expensive)
        size_t Count = m_ValuesE.size();
        for (size_t i = 0; i < Count; i++) {
            set<string>::const_iterator vali = Values.find(m_ValuesE[i]);
            if (vali == Values.end())
                Filter.m_SatisfiedValues.insert(i);
        }
    }

    //-- sanitize filter ranges (compatibility)
    if (Filter.m_SatisfiedValues.empty()) {
        Filter.m_KeyLo = 0;
        Filter.m_KeyHi = 0;
    } else {
        Filter.m_KeyLo.i = *Filter.m_SatisfiedValues.begin();
        Filter.m_KeyLo.s = m_ValuesE[Filter.m_KeyLo.i];

        Filter.m_KeyHi.i = *Filter.m_SatisfiedValues.rbegin();
        Filter.m_KeyHi.s = m_ValuesE[Filter.m_KeyHi.i];
        Filter.m_KeyHi.i++;
    }

    return true;
};


// DDC_FREE_BIBL_AUTOTRUNCATE
//  + if undefined, free bibl values > 20kB long cause a fatal error
//  + otherwise, such values will be implicitly truncated
//  + executive decision (moo + fw, 2020-01-22): use fatal error -> pass on to curators
//#define DDC_FREE_BIBL_AUTOTRUNCATE 1
//#undef DDC_FREE_BIBL_AUTOTRUNCATE

void CFreeBiblStringIndex::RegisterBiblStringItemId(const string &ValueStr) {
#ifndef DDC_FREE_BIBL_AUTOTRUNCATE
    if (ValueStr.length() > MaxBiblStringLen) {
        //-- v2.0.40: Mon, 07 Dec 2015 11:16:00 +0100 moocow: bail out here rather than creating a corrupt index
        throw CFatalExpc(Format("Value for bibl field `%s' is too long (%zi bytes > max=%zi bytes)",
                                m_Name.c_str(), ValueStr.length(), MaxBiblStringLen));
    }
#endif


    string BiblString(ValueStr);
    DWORD  BiblId = (DWORD)-1;
    for (size_t i = 0; i < BiblString.length(); i++)  // delete all \x1, since it is used as a delimeter
        if ((BYTE) BiblString[i] == 1)
            BiblString[i] = ' ';

    Trim(BiblString);

#ifdef DDC_FREE_BIBL_AUTOTRUNCATE
    if (TrimTruncate(BiblString,MaxBiblStringLen))
        ddcLogWarn(Format("Warning: truncating value for free bibl attribute `%s' to max=%zi bytes", m_Name.c_str(), MaxBiblStringLen));
#endif

    BuildStringItemsMapT::const_iterator it = m_BuildStringItemsMap.find(BiblString);
    if (it == m_BuildStringItemsMap.end()) {

        //-- sanity checks (v2.2.1, 2020-01-22: do NOT use CExpc here: it will corrupt the resulting index!)
        //   + thrown CExpc exceptions will be caught by ConcIndexatorInvoker::IndexFile() (~ line 213)
        //   + throwing CFatalExpc will cause immediate termination, but core dump won't point us here
        //   + calling ddcLogDie() will print error message and abort here (but won't tell us which input file was wonky)
        if (m_BuildStringItemsSize >= DWORD_MAX) {
            //-- v2.0.40: moo Mon, 07 Dec 2015 11:16:00 +0100 moocow: bail out here rather than creating a corrupt index
            throw CFatalExpc(Format("Too many values for bibl field `%s'. Cannot be more than %u\n", m_Name.c_str(), DWORD_MAX));
        }

        BiblId = m_BuildStringItemsSize++;
        m_BuildStringItemsMap[BiblString] = BiblId;
    } else {
        BiblId = it->second;
    }

    m_ValuesForEachFile.push_back(BiblId);
};


bool CFreeBiblStringIndex::ConvertAndSaveToDiskAfterIndexing(string m_Path) {
    fprintf(stderr, "sorting and saving index for %s\n", m_Name.c_str());
    { // converting
        vector<DWORD> Old2New(m_BuildStringItemsMap.size());
        size_t newId = 0;
        for (BuildStringItemsMapT::const_iterator mi=m_BuildStringItemsMap.begin(); mi != m_BuildStringItemsMap.end(); ++mi, ++newId) {
            Old2New[mi->second] = newId;
        }

        m_ValuesForEachFile.ensureVec();
        for (size_t i = 0; i < m_ValuesForEachFile.size(); i++)
            m_ValuesForEachFile.m_vec[i] = Old2New[m_ValuesForEachFile.m_vec[i]];
    }

    //-- save data (v2.1.12)
    string StringFileName = GetStringFileName(m_Path);
    string ValuesFile = StringFileName + "_values";
    string IndexFile = StringFileName + "_idx";

    FILE *vfp = fopen(ValuesFile.c_str(), "wb");
    if (!vfp) {
        ddcLogError(
            Format("CFreeBiblStringIndex::ConvertAndSaveToDiskAfterIndexing(): open failed for '%s': %s",
                   ValuesFile.c_str(), strerror(errno)));
        return false;
    }
    FILE *ifp = fopen(IndexFile.c_str(), "wb");
    if (!ifp) {
        ddcLogError(
            Format("CFreeBiblStringIndex::ConvertAndSaveToDiskAfterIndexing(): open failed for '%s': %s",
                   IndexFile.c_str(), strerror(errno)));
        return false;
    }

    fprintf(stderr, "Writing %zi items  to %s_*\n", m_BuildStringItemsMap.size(), StringFileName.c_str());

    bool rc = true;
    try {
        for (BuildStringItemsMapT::const_iterator it=m_BuildStringItemsMap.begin(); it != m_BuildStringItemsMap.end(); ++it) {
            const string &I = it->first;
            ddcStringEnum<>::OffT pos = ftell(vfp);

            if (fwrite(&pos, sizeof(ddcStringEnum<>::OffT), 1, ifp) != 1)
                throw runtime_error("failed to write offset data");
            if (fwrite(I.c_str(), 1, I.size() + 1, vfp) != I.size() + 1)
                throw runtime_error("failed to write string data");
        }
        CFreeBiblIndex::ConvertAndSaveToDiskAfterIndexing(m_Path);
        rc = true;
    }
    catch (exception &e) {
        fprintf(stderr, "CFreeBiblStringIndex::ConvertAndSaveToDiskAfterIndexing(): Exception: %s\n", e.what());
        rc = false;
    }
    catch (...) {
        fprintf(stderr, "CFreeBiblStringIndex::ConvertAndSaveToDiskAfterIndexing(): Exception: (unhandled exception)\n");
        rc = false;
    }

    fclose(vfp);
    fclose(ifp);
    return rc;
};

//=============================================

CFreeBiblStringConstant::CFreeBiblStringConstant(const string &value) {
    setValue(value);
};

CFreeBiblStringConstant::~CFreeBiblStringConstant() {
};

void CFreeBiblStringConstant::setValue(const string &value) {
    clear();
    m_Value = value;
    m_ValuesE.ensureVec();
    m_ValuesE.m_strings.reserve(1);
    m_ValuesE.m_strings.push_back(m_Value);
}

void CFreeBiblStringConstant::clear() {
    CFreeBiblStringIndex::clear();
    ClearString(m_Value);
};

string CFreeBiblStringConstant::GetTypeStr() const {
    return StringConstantTypeStr;
};

CFreeBiblIndexTypeId CFreeBiblStringConstant::GetTypeId() const {
    return cfbiStringConstant;
};

const string &CFreeBiblStringConstant::GetXpathStr() const {
    return m_Value;
};


string CFreeBiblStringConstant::GetStringValue(DWORD FileNo) const {
    return m_Value;
};

int CFreeBiblStringConstant::GetIntegerValue(DWORD FileNo) const {
    return 0;
};

void CFreeBiblStringConstant::ReadFromDisk(string Path, DWORD FileBreaksSize, bool useMMap) {
    return;
};

bool CFreeBiblStringConstant::ConvertAndSaveToDiskAfterIndexing(string Path) {
    return true;
};

void CFreeBiblStringConstant::CreateUnion(const string &Path, const vector<const CFreeBiblIndex *> &Indices,
                                          const vector<size_t> &FileCounts) {
    size_t i = 0;
    bool gotValue = !m_Value.empty();
    for (; i < Indices.size(); ++i) {
        if (Indices[i] == NULL) continue;
        if (Indices[i]->GetTypeId() != cfbiStringConstant) {
            ddcLogWarn(
                "CFreeBiblStringConstant::CreateUnion(): Warning: cannot merge variable field into bibl constant " +
                m_Name);
            continue;
        }
        CFreeBiblStringConstant *cfb = (CFreeBiblStringConstant *) Indices[i];
        if (!gotValue) {
            setValue(cfb->m_Value);
            gotValue = true;
        } else if (cfb->m_Value != m_Value) {
            ddcLogWarn("CFreeBiblStringConstant::CreateUnion(): Warning: cannot merge distinct constants \"" +
                       m_Value + "\" != \"" + cfb->m_Value + "\" for attribute " + m_Name);
        }
    }
};

void CFreeBiblStringConstant::CreatePartitions(vector<CFreeBiblIndex *> &Parts, const vector<string> &Paths,
                                               const vector<DWORD> &EndFileNo) const {
    ddcLogDebug("CFreeBiblStringConstant::CreatePartitions(): ignoring bibl string constant " + m_Name);
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
