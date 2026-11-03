//
// Created by sokirko on 12.10.19.
//

#include "BiblIndex.h"
#include "../tinyxml/xpath_static.h"



bool CheckXPath(string XPath, string &ErrStr) {
    ErrStr = "";
    if (XPath.empty()) {
        ErrStr = "Empty XPath";
        return false;
    };
    if (XPath[XPath.length() - 1] == '/') {
        ErrStr = "XPath should not end with '/'";
        return false;
    };
    return true;
};

CBiblIndex::CBiblIndex() {
    m_bMemoryMap = false;
}

void CBiblIndex::FreeBiblIndices() {
    for (FreeBiblStringMap::iterator it = m_FreeBiblIndices.begin(); it != m_FreeBiblIndices.end(); it++) {
        delete it->second;
    };
    m_FreeBiblIndices.clear();
};

void CBiblIndex::FreeBiblExpanders() {
    for (BiblExpanderMap::iterator it = m_BiblExpanders.begin(); it != m_BiblExpanders.end(); it++) {
        if (it->second) delete it->second;
    }
    m_BiblExpanders.clear();
};


void CBiblIndex::SetPath(string ProjectFileName) {
    m_Path = ProjectFileName;
    m_RegexOpts = RML_RE::Options(true, NULL); //-- default

};

bool CBiblIndex::RegisterTextAreas(string fields, string &ErrorStr) {
    m_TextAreas.clear();
    StringTokenizer lines(fields.c_str(), "\n\r");
    while (lines()) {
        string OneField = lines.val();
        Trim(OneField);
        if (OneField.empty()) continue;
        StringTokenizer tok(OneField.c_str(), " \t");
        if (!tok()) {
            ErrorStr = "Error! Bad syntax in free bibliographical attribute description";
            return false;
        };
        string FieldName = tok.val();
        RmlMakeLower(FieldName, morphEnglish);
        if (FieldName != TextAreaOptionFieldName) {
            ErrorStr = "Error! Bad syntax in text area attribute description";
            return false;
        };

        if (!tok()) {
            ErrorStr = "Error! Bad syntax in text area attribute description";
            return false;
        };
        CTextArea TextArea;
        TextArea.m_TextAreaName = tok.val();
        // reading xpath
        if (!tok()) {
            ErrorStr = "Error! Bad syntax in text area attribute description";
            return false;
        };
        TextArea.m_Xpath = tok.val();
        if (!CheckXPath(TextArea.m_Xpath, ErrorStr)) {
            ErrorStr += " for TextArea XPath";
            return false;
        };


        m_TextAreas.push_back(TextArea);
    }


    return true;
}


bool CBiblIndex::RegisterFreeBiblAttributes(string fields, string &ErrorStr) {
    FreeBiblIndices();
    m_OrigXPath = "";
    m_DateXPath = "";
    m_ScanXPath = "";
    m_StartPageXPath = "";


    StringTokenizer lines(fields.c_str(), "\n\r");
    while (lines()) {
        string OneField = lines.val();
        Trim(OneField);
        if (OneField.empty()) continue;
        StringTokenizer tok(OneField.c_str(), " \t");

        if (!tok()) {
            ErrorStr = "Error! Bad syntax in free bibliographical attribute description";
            return false;
        };

        if (tok.val() != FreeBiblAttribOptionFieldName) {
            ErrorStr = "Error! Bad syntax in free bibliographical attribute description";
            return false;
        };

        // reading name
        if (!tok()) {
            ErrorStr = "Error! Cannot read name of text area";
            return false;
        };


        string TypeStr = tok.val();
        bool isConstant = false;
        bool isAlias = false;
        if ((TypeStr == StringTypeStr) || (TypeStr == IntegerTypeStr)) {
            isConstant = false;
        } else if (TypeStr == StringConstantTypeStr) {
            isConstant = true;
        } else if (TypeStr == StringAliasTypeStr) {
            isAlias = true;
        } else {
            ErrorStr = Format(
                "Error! Bad type \"%s\" in free bibliographical filed type; known types are \"%s\", \"%s\", \"%s\", and \"%s\"",
                TypeStr.c_str(), IntegerTypeStr, StringTypeStr, StringConstantTypeStr, StringAliasTypeStr);
            return false;
        };


        bool bShowInHeader;
        if (!isAlias) {
            //-- reading show in header ("visibility" flag)
            if (!tok()) {
                ErrorStr = "Error! Bad syntax in free bibliographical attribute description : missing visibility flag";
                return false;
            }

            string ShowInHeaderStr = tok.val();
            if (ShowInHeaderStr == "0")
                bShowInHeader = false;
            else if (ShowInHeaderStr == "1")
                bShowInHeader = true;
            else {
                ErrorStr = "Error! the first column in a non-alias free bibliographical attribute description should be 0 or 1 (visibility flag)";
                return false;
            }
        }

        // reading name
        if (!tok()) {
            ErrorStr = "Error! Bad syntax in free bibliographical attribute description: missing attribute name";
            return false;
        }

        string Name = tok.val();
        string Xpath;
        if (isConstant) {
            Xpath = tok.get_rest_trim(); //-- trim leading & trailing whitespace from constants
        } else if (tok()) {
            Xpath = tok.val();
        }

        // check xpath (or value for constants)
        if (!isConstant && !isAlias && !CheckXPath(Xpath, ErrorStr)) {
            //-- just warn about dodgy-looking XPaths (fatal error prior to v2.0.29)
            ErrorMessage("WARNING", ErrorStr + Format(" for free bibliographical attribte `%s'", Name.c_str()));
            //return false;
        }

        //-- check for aliases
        if (isAlias) {
            if (Xpath.empty()) {
                ErrorStr = Format("Error! Bad syntax in free bibliographical alias `%s': missing target attribute name",
                                  Name.c_str());
                return false;
            }
            if (m_FreeBiblIndices.find(Name) != m_FreeBiblIndices.end()) {
                //-- new alias clobbers old physical field
                FreeBiblStringMap::iterator oldi = m_FreeBiblIndices.find(Name);
                delete oldi->second;
                m_FreeBiblIndices.erase(oldi);
                ddcLogDebug(Format("DEBUG: bibliographic attribute alias `%s' -> `%s' overrides physical attribute `%s'",
                                   Name.c_str(), Xpath.c_str(), Name.c_str()));
            }
            if (m_FreeBiblAlias.find(Name) != m_FreeBiblAlias.end()) {
                //-- new alias clobbers old alias
                ddcLogDebug(Format("DEBUG: multiple definitions for bibliographic alias `%s', using most recent",
                                   Name.c_str()));
            }

            m_FreeBiblAlias[Name] = Xpath;
            continue;
        }

        //-- hacks for built-in fields
        if (Name == "orig")
            m_OrigXPath = Xpath;
        else if (Name == "scan")
            m_ScanXPath = Xpath;
        else if (Name == "date")
            m_DateXPath = Xpath;
        else if (Name == "page")
            m_StartPageXPath = Xpath;
        else {
            if (m_FreeBiblIndices.find(Name) != m_FreeBiblIndices.end()) {
                //-- just warn about duplicate bibl fields and use the most recent definitition
                //   (prior to v2.0.29, multiple bibl fields with the same name caused a fatal error)
                FreeBiblStringMap::iterator oldi = m_FreeBiblIndices.find(Name);
                delete oldi->second;
                m_FreeBiblIndices.erase(oldi);
                ddcLogDebug(Format("DEBUG: multiple definitions for free bibliographic attribute `%s', using most recent",
                                   Name.c_str()));
            }
            if (m_FreeBiblAlias.find(Name) != m_FreeBiblAlias.end()) {
                //-- just warn about clobbering an existng alias
                ddcLogDebug(Format("DEBUG: physical free bibliographic attribute `%s' overrides alias `%s' -> `%s'",
                                   Name.c_str(), Name.c_str(), m_FreeBiblAlias[Name].c_str()));
                m_FreeBiblAlias.erase(Name);
            }

            CFreeBiblIndex *pIndex;
            if (TypeStr == StringTypeStr) {
                pIndex = new CFreeBiblStringIndex;
            } else if (TypeStr == StringConstantTypeStr) {
                pIndex = new CFreeBiblStringConstant(unescapeCString(Xpath));
                Xpath = "/..";
            } else if (TypeStr == IntegerTypeStr) {
                pIndex = new CFreeBiblIndex;
            } else {
                ErrorStr = Format("Error! Unknown type \"%s\" in the options file!", TypeStr.c_str());
                return false;
            }

            pIndex->m_Name = Name;
            pIndex->m_Xpath = Xpath;
            pIndex->m_bShowInHeader = bShowInHeader;
            pIndex->m_pRegexOpts = &m_RegexOpts;
            m_FreeBiblIndices[Name] = pIndex;
        };
    };

    m_FreeBiblNameToPosition.clear();
    size_t i = 0;
    for (FreeBiblStringMap::const_iterator it = m_FreeBiblIndices.begin(); it != m_FreeBiblIndices.end(); it++) {
        m_FreeBiblNameToPosition[it->first] = i;
        ++i;
    }
    assert (m_FreeBiblIndices.size() == m_FreeBiblNameToPosition.size());

    return true;
};

string CBiblIndex::GetFreeBibiAttributesDescr() const {
    string Result;
    if (!m_OrigXPath.empty())
        Result += Format("%s string 1 orig %s\n", FreeBiblAttribOptionFieldName.c_str(), m_OrigXPath.c_str());
    if (!m_ScanXPath.empty())
        Result += Format("%s string 1 scan %s\n", FreeBiblAttribOptionFieldName.c_str(), m_ScanXPath.c_str());
    if (!m_DateXPath.empty())
        Result += Format("%s integer 1 date %s\n", FreeBiblAttribOptionFieldName.c_str(), m_DateXPath.c_str());

    if (!m_StartPageXPath.empty())
        Result += Format("%s string 1 page %s\n", FreeBiblAttribOptionFieldName.c_str(), m_StartPageXPath.c_str());


    for (FreeBiblStringMap::const_iterator it = m_FreeBiblIndices.begin(); it != m_FreeBiblIndices.end(); it++) {
        Result += it->second->GetDescriptionStr();
        Result += "\n";
    };
    for (FreeBiblAliasMap::const_iterator it = m_FreeBiblAlias.begin(); it != m_FreeBiblAlias.end(); it++) {
        Result += Format("Bibl alias %s %s\n", it->first.c_str(), it->second.c_str());
    };

    return Result;
};

string CBiblIndex::GetTextAreasDescr() const {
    string Result;
    for (size_t i = 0; i < m_TextAreas.size(); i++) {
        Result += Format("%s %s %s",
                         TextAreaOptionFieldName.c_str(),
                         m_TextAreas[i].m_TextAreaName.c_str(),
                         m_TextAreas[i].m_Xpath.c_str()
            );


        Result += "\n";
    }

    return Result;
}

string CBiblIndex::GetBiblIndexFileName() const {
    return MakeFName(m_Path, "_bibl_idx");
};

string CBiblIndex::GetBiblDateIndexFileName() const {
    return MakeFName(m_Path, "_bibl_date");
};

string CBiblIndex::GetBiblFileName() const {
    return MakeFName(m_Path, "_bibl");
};


void CBiblIndex::LoadBibl(string Path, size_t FileBreaksSize, bool useMMap) {
    SetPath(Path);
    m_bMemoryMap = useMMap;

    // reading Bibliographical files if they exist
    m_BiblBodyFile.Open(m_bMemoryMap, GetBiblFileName() );
    m_EndOffsetsInBiblFile.open(GetBiblIndexFileName(), useMMap);
    if (m_EndOffsetsInBiblFile.size() != FileBreaksSize) {
        string s = Format(
            "The number of corpus files should be equal to the number of bibliographical records in file `%s'",
            GetBiblIndexFileName().c_str());
        s += Format("\nnumber of corpus files = %zi", FileBreaksSize);
        s += Format("\nnumber of bibliographical records = %zi", m_EndOffsetsInBiblFile.size());
        throw CExpc(s);
    };

    m_Dates.open(GetBiblDateIndexFileName(), useMMap);
    if (m_Dates.size() != FileBreaksSize) {
        throw CExpc(Format("Corrupt bibliograpical index file for dates (%s)", GetBiblDateIndexFileName().c_str()));
    };

    for (FreeBiblStringMap::iterator bibl_it = m_FreeBiblIndices.begin(); bibl_it != m_FreeBiblIndices.end(); bibl_it++)
        bibl_it->second->ReadFromDisk(m_Path, FileBreaksSize, useMMap);
};

CBibliography CBiblIndex::GetFullBibliographyOfHit(size_t FileNo) const {
    if (FileNo == m_EndOffsetsInBiblFile.size()) return CBibliography();
    file_off_t endBiblFileOffset = m_EndOffsetsInBiblFile[FileNo];
    file_off_t startBiblFileOffset = (FileNo == 0) ? 0 : m_EndOffsetsInBiblFile[FileNo - 1];
    assert (endBiblFileOffset >= startBiblFileOffset);
    size_t length = endBiblFileOffset - startBiblFileOffset;
    ArrayPtrHolder<BYTE> buffer(new BYTE[length]);
    if (!m_BiblBodyFile.ReadBuffer(startBiblFileOffset, length, buffer.Get())) {
        return CBibliography();
    }

    CBibliography B;
    B.ReadFromString(string((char*)buffer.Get(), length));
    return B;
};

void CBiblIndex::InitNoSort(vector<CHit> &Hits) const {
    size_t HitsCount = Hits.size();
    for (size_t HitNo = 0; HitNo < HitsCount; HitNo++) {
        CHit &H = Hits[HitNo];
        H.m_SortKey = HitNo;
    }
}

void CBiblIndex::InitSortByDate(vector<CHit> &Hits) const {
    size_t HitsCount = Hits.size();
    for (size_t HitNo = 0; HitNo < HitsCount; HitNo++) {
        CHit &H = Hits[HitNo];
        H.m_SortKey = m_Dates.empty() ? 0 : m_Dates[H.m_FileNo];
    }
}

void CBiblIndex::InitSortByBiblIntegerField(string FreeBiblAttribNameOrAlias, vector<CHit> &Hits) const {
    const CFreeBiblIndex *pFreeAttrib = 0;

    if (!FreeBiblAttribNameOrAlias.empty())
        pFreeAttrib = GetFreeBiblIndex(FreeBiblAttribNameOrAlias);
    if (pFreeAttrib == NULL)
        return InitNoSort(Hits);

    size_t HitsCount = Hits.size();
    for (size_t HitNo = 0; HitNo < HitsCount; HitNo++) {
        CHit &H = Hits[HitNo];
        H.m_SortKey.assign(pFreeAttrib->GetIntegerValue(H.m_FileNo),
                           pFreeAttrib->GetStringValue(H.m_FileNo)); //-- moo: maybe we can avoid string-copying here?
    }
}

void CBiblIndex::SetRegexOptions(const RML_RE::Options &opts) {
    m_RegexOpts = opts;
    for (FreeBiblStringMap::iterator mi = m_FreeBiblIndices.begin(); mi != m_FreeBiblIndices.end(); mi++) {
        mi->second->m_pRegexOpts = &m_RegexOpts;
    }
}

bool CBiblIndex::FileMatches(DWORD FileNo, const vector<CDDCFilterWithBounds> &Filters) const {
    for (vector<CDDCFilterWithBounds>::const_iterator fi = Filters.begin(); fi != Filters.end(); ++fi) {
        CFreeBiblIndex *fbi = (CFreeBiblIndex *) (fi->m_BiblIndex);
        if (fbi && !fbi->FileMatches(FileNo, *fi)) {
            //-- free bibl filter is tested with CFreeBiblIndex::FileMatches()
            return false;
        } else if (!fbi && (fi->m_FilterType == LessByDate || fi->m_FilterType == GreaterByDate)) {
            //-- date filter is tested manually...
            // + 2019-08-15 moocow
            //   - fdate: cast to int so it jives with CHitSortKey::i (avoid signed/unsigned comparison)
            //   - should fixes bogus empty responses from e.g. "count(* #asc_date) #by[textClass]"
            int fdate = m_Dates[FileNo];
            if (fdate < fi->m_KeyLo.i || fdate > fi->m_KeyHi.i)
                return false;
        } else { ; //-- other filter tyes are ignored
        }
    }
    return true;
}

CBiblExpander *CBiblIndex::AddBiblExpander(const string &spec) {
    const char *delims = " \t\r\n";
    StringTokenizer stok(spec.c_str(), delims);
    string s_label(""), s_target(""), s_cls(""), s_param("");
    CBiblExpander *bx = NULL;;

    if (stok.has_next()) s_label = stok.next_token();
    if (stok.has_next()) s_target = stok.next_token();
    if (stok.has_next()) s_cls = stok.next_token();
    if (stok.has_next()) s_param = stok.get_rest();

    //-- parse spec
    string cls(s_cls);
    Trim(cls);
    EngMakeLower(cls);
    if (cls.empty()) {
        throw CExpc(errLogic, "unknown BiblExpander class `%s'", s_cls.c_str());
    } else {
        //-- default: BxTermWrapper
        bx = new BxTermWrapper(s_label, s_target, s_cls + " " + s_param);

        //-- check for chains (not yet implemented)
        CTermExpander *tx = ((BxTermWrapper *) bx)->m_BxTx;
        if (tx && tx->m_Class == "Chain")
            throw CExpc(errLogic, "chained bibliographic expanders not yet supported for `%s'", s_label.c_str());
    }

    //-- sanity check(s)
    if (bx == NULL)
        throw CExpc(errRuntime, "could not create BiblExpander of class `%s'", s_cls.c_str());

    //-- check for existing expander
    BiblExpanderMap::iterator bi = m_BiblExpanders.find(s_label);
    if (bi != m_BiblExpanders.end()) {
        if (bi->second != NULL) delete bi->second;
        m_BiblExpanders.erase(bi);
    }

    //-- insert new expander
    m_BiblExpanders[s_label] = bx;

    return bx;
};

bool CBiblIndex::IsRegisteredBiblField(const string &FreeBiblAttribNameOrAlias) const {
    return !FreeBiblAttribNameOrAlias.empty() && GetFreeBiblIndex(FreeBiblAttribNameOrAlias) != NULL;
}

CFreeBiblIndexTypeId CBiblIndex::GetBiblFieldTypeId(const string &FreeBiblAttribName) const {
    const CFreeBiblIndex *fbi = FreeBiblAttribName.empty() ? NULL : GetFreeBiblIndex(FreeBiblAttribName);
    if (!fbi) return cfbiUnknown; //-- attribute not found
    return fbi->GetTypeId();
}

bool CBiblIndex::GetFilterBounds(CDDCFilterWithBounds &Filter, const string &LoValue, const string &HiValue) const {
    Filter.clear();
    //-- filter bounds: require physically indexed bibliographic field
    const CFreeBiblIndex *fbi = GetFreeBiblIndex(Filter.m_AttrName);
    if (!fbi) return false; //-- attribute not found
    return fbi->GetFilterBounds(Filter, LoValue, HiValue);
}

bool CBiblIndex::GetFilterValue(CDDCFilterWithBounds &Filter, const string &Value) const {
    Filter.clear();

    //-- bibliographic expander clobbers any indexed field with the same name
    BiblExpanderMap::const_iterator xit = m_BiblExpanders.find(Filter.m_AttrName);
    if (xit != m_BiblExpanders.end()) {
        set<string> xvalues;
        xit->second->expand(Value, xvalues);

        Filter.m_AttrName = xit->second->m_BxTarget;
        return GetFilterValues(Filter, xvalues);
    }

    //-- usual case: physically indexed bibliographic field or alias
    const CFreeBiblIndex *fbi = GetFreeBiblIndex(Filter.m_AttrName);
    if (!fbi) return false; //-- attribute not found
    return fbi->GetFilterValue(Filter, Value);
};

//-- initialize CDDCFilterWithBounds for a target regex
bool CBiblIndex::GetFilterValues(CDDCFilterWithBounds &Filter, const string &Regex) const {
    Filter.clear();
    const CFreeBiblIndex *fbi = GetFreeBiblIndex(Filter.m_AttrName);
    if (!fbi) return false; //-- attribute not found
    return fbi->GetFilterValues(Filter, Regex);;
};

//-- initialize CDDCFilterWithBounds for a set of target values
bool CBiblIndex::GetFilterValues(CDDCFilterWithBounds &Filter, const set<string> &Values) const {
    Filter.clear();

    //-- bibliographic expander clobbers any indexed field with the same name
    BiblExpanderMap::const_iterator xit = m_BiblExpanders.find(Filter.m_AttrName);
    if (xit != m_BiblExpanders.end()) {
        set<string> xvalues;
        xit->second->expand(Values, xvalues);

        Filter.m_AttrName = xit->second->m_BxTarget;
        return GetFilterValues(Filter, xvalues);
    }

    //-- usual case: physically indexed bibliographic field
    const CFreeBiblIndex *fbi = GetFreeBiblIndex(Filter.m_AttrName);
    if (!fbi) return false; //-- attribute not found
    return fbi->GetFilterValues(Filter, Values);;
};


void CBiblIndex::GetTextAreaElements(const TiXmlDocument &doc, vector<TiXmlElement *> &Result) const {
    Result.clear();

    for (size_t i = 0; i < m_TextAreas.size(); i++) {
        TiXmlNode *text = TinyXPath::XNp_xpath_node(doc.RootElement(), m_TextAreas[i].m_Xpath.c_str());
        if (!text) {
            throw CExpc(Format("Cannot find %s in the source document using XPath \"%s\"!",
                               m_TextAreas[i].m_TextAreaName.c_str(),
                               m_TextAreas[i].m_Xpath.c_str()));
        };
        Result.push_back(text->ToElement());
    }
};

size_t CBiblIndex::GetTextAreasCount() const {
    return m_TextAreas.size();
}

string CBiblIndex::GetVisibleFreeHeaderBiblAttributes(size_t FileNo, string Delim) const {
    string Result;
    for (FreeBiblStringMap::const_iterator bibl_it = m_FreeBiblIndices.begin();
         bibl_it != m_FreeBiblIndices.end(); bibl_it++) {
        const CFreeBiblIndex *I = bibl_it->second;
        if (I->m_bShowInHeader) {
            Result += Delim;
            Result += I->GetStringValue(FileNo);
        };
    };

    return Result;

};

string CBiblIndex::GetFreeHeaderBiblAttributesWithNames(size_t FileNo, char Delim) const {
    string Result;
    for (FreeBiblStringMap::const_iterator bibl_it = m_FreeBiblIndices.begin();
         bibl_it != m_FreeBiblIndices.end(); bibl_it++) {
        CFreeBiblIndex *I = bibl_it->second;
        if (I->m_bShowInHeader) {
            Result += Delim;
            Result += I->m_Name;
            Result += Delim;
            Result += I->GetStringValue(FileNo);
        };
    };
    return Result;
};

string CBiblIndex::GetFreeHeaderBiblAttributesJson(size_t FileNo, bool assume_utf8, bool include_invisible) const {
    string js("");
    for (FreeBiblStringMap::const_iterator bibl_it = m_FreeBiblIndices.begin();
         bibl_it != m_FreeBiblIndices.end(); bibl_it++) {
        CFreeBiblIndex *I = bibl_it->second;
        if (include_invisible || I->m_bShowInHeader) {
            if (!js.empty()) js.push_back(',');
            js.append(jsonStr(I->m_Name, assume_utf8));
            js.push_back(':');
            js.append(jsonStr(I->GetStringValue(FileNo), assume_utf8));
        }
    }
    return js;
}

string CBiblIndex::GetFreeHeaderBiblAttributesTabsDump(size_t FileNo, bool assume_utf8, bool include_invisible) const {
    string ts("");
    string prefix("%%$DDC:meta.");
    for (FreeBiblStringMap::const_iterator bibl_it = m_FreeBiblIndices.begin();
         bibl_it != m_FreeBiblIndices.end(); bibl_it++) {
        CFreeBiblIndex *I = bibl_it->second;
        if (include_invisible || I->m_bShowInHeader) {
            ts.append(prefix);
            ts.append(jsonStr(I->m_Name, assume_utf8, false));
            ts.push_back('=');
            ts.append(jsonStr(I->GetStringValue(FileNo), assume_utf8, false));
            ts.push_back('\n');
        }
    }
    return ts;
}


int CBiblIndex::GetTextAreaByName(const string &Name) const {
    for (int i = 0; i < m_TextAreas.size(); i++)
        if (m_TextAreas[i].m_TextAreaName == Name)
            return i;
    return UnknownTextAreaNo;
}

int CBiblIndex::WithinTextArea(const vector<string> &Within) const {
    for (vector<string>::const_reverse_iterator wi = Within.rbegin(); wi != Within.rend(); wi++) {
        int TextAreaNo = GetTextAreaByName(*wi);
        if (TextAreaNo != UnknownTextAreaNo)
            return TextAreaNo;
    }
    return UnknownTextAreaNo;
}

#define MAX_ALIAS_REDIR 100

CFreeBiblIndex *CBiblIndex::GetFreeBiblIndex(const string &FreeBiblAttribNameOrAlias) const {
    string name(FreeBiblAttribNameOrAlias);
    FreeBiblAliasMap::const_iterator ai = m_FreeBiblAlias.find(name);
    for (size_t n = 0; ai != m_FreeBiblAlias.end(); ++n, ai = m_FreeBiblAlias.find(name)) {
        if (n >= MAX_ALIAS_REDIR)
            throw (CExpc(errRuntime, "too many alias redirections (%zi) for metadata label `%s'", n,
                         FreeBiblAttribNameOrAlias.c_str()));
        name = ai->second;
    }

    FreeBiblStringMap::const_iterator bi = m_FreeBiblIndices.find(name);
    if (bi == m_FreeBiblIndices.end()) return NULL; // attribute not found
    return bi->second;
}

CBiblExpander *CBiblIndex::GetBiblExpander(const string &ExpanderName) const {
    BiblExpanderMap::const_iterator xit = m_BiblExpanders.find(ExpanderName);
    if (xit == m_BiblExpanders.end()) return NULL; // expander not found
    return xit->second;
}

#undef DDC_VERBOSE_CORPUS_INFO

string CBiblIndex::FreeBiblMapToJson(bool useUtf) const {
    size_t i=0;
    string result;
    for (FreeBiblStringMap::const_iterator bmi=m_FreeBiblIndices.begin(); bmi != m_FreeBiblIndices.end(); ++i, ++bmi) {
        const CFreeBiblIndex *fbi = bmi->second;
        const CFreeBiblIndexTypeId fbtyp = fbi->GetTypeId();
        result += (string(",\n\t\t{")
                   + "\"name\":" + jsonStr(fbi->m_Name) + ", "
#if DDC_VERBOSE_CORPUS_INFO
                   + "\"xpath\":" + jsonStr(fbi->m_Xpath) + ", "
#endif
                   + "\"visible\":" + (fbi->m_bShowInHeader ? '1' : '0') + ", "
                   + "\"size\":" + Format("%zd", fbi->size()) //-- bibl[i].size : number of values (?)
            );
        if (fbtyp==cfbiStringConstant) {
            result += string(", \"value\":") + jsonStr(fbi->GetXpathStr(),useUtf);
        }
        result += "}";
    }
    return result;
}

string CBiblIndex::FreeBiblAliasMapToJson() const {
    string result;
    for (CBiblIndex::FreeBiblAliasMap::const_iterator bai=m_FreeBiblAlias.begin(); bai!=m_FreeBiblAlias.end(); ++bai) {
        result += (string(",\n\t\t{")
                   + "\"alias\":" + jsonStr(bai->first) + ", "
                   + "\"ref\":" + jsonStr(bai->second)
                   + "}"
            );
    }
    return result;


}


string CBiblIndex::BiblExpanderMapToJson() const {
    size_t i = 0;
    string result = "[";
    for (CBiblIndex::BiblExpanderMap::const_iterator bmi=m_BiblExpanders.begin(); bmi != m_BiblExpanders.end(); ++i, ++bmi) {
        const CBiblExpander *bx = bmi->second;
        if (i != 0) result += ',';
#if DDC_VERBOSE_CORPUS_INFO
        //-- info.xbibl: verbose
        result += (string("\n\t\t{")
                   + "\"label\":" + jsonStr(bx->m_BxLabel) + ", "
                   + "\"target\":" + jsonStr(bx->m_BxTarget) + ", "
                   + "\"param\":" + jsonStr(bx->m_BxParam)
                   + "}"
            );
#else
        //-- info.xbibl: terse
        result += jsonStr(bx->m_BxLabel);
#endif
    }
    result += "]";
    return result;
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
