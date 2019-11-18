/*-*- Mode: C++ -*-*/
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2018 by Bryan Jurish
//
//  This file is part of DDC.
// 
//  DDC is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
// 
//  DDC is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
// 
//  You should have received a copy of the GNU Lesser General Public License
//  along with DDC.  If not, see <http://www.gnu.org/licenses/>.
//
#include "ConcXml.h"
#include "../tinyxml/xpath_static.h"
#include "../CommonLib/bserialize.h"
#include "../CommonLib/ddcString.h"
#include <typeinfo>    //-- for typeid()


string &DeleteEoln(string &s) {
    for (size_t i = 0; i < s.length(); i++)
        if ((s[i] == '\n')
            || (s[i] == '\r')
            )
            s[i] = ' ';

    return s;
};




string ReadXmlField(const TiXmlDocument &pDoc, string XPath) {
    string ErrStr;
    TinyXPath::xpath_processor xp_proc(pDoc.RootElement(), XPath.c_str());
    TinyXPath::expression_result er_res = xp_proc.er_compute_xpath();
    if (xp_proc.e_error != TinyXPath::xpath_processor::e_no_error)
        // not present in this dociment
        return "";

    string Result;
    switch (er_res.e_type) {
        case TinyXPath::e_bool:
            Result = (er_res.o_get_bool() ? "1" : "0");
            break;

        case TinyXPath::e_string:
            Result = er_res.cp_get_string();
            break;

        case TinyXPath::e_int:
            Result = Format("%d", er_res.i_get_int());
            break;

        case TinyXPath::e_double:
            Result = Format("%g", er_res.d_get_double());
            break;

        case TinyXPath::e_node_set: {
            TinyXPath::node_set *pSet = er_res.nsp_get_node_set();
            size_t Count = pSet->u_get_nb_node_in_set();
            for (size_t u_node = 0; u_node < Count; u_node++) {
                string s;
                const TiXmlBase *pBase = pSet->XBp_get_base_in_set(u_node);
                if (pSet->o_is_attrib(u_node)) {
                    const TiXmlAttribute *node = pSet->XAp_get_attribute_in_set(u_node);
                    s = node->Value();
                } else {
                    const TiXmlNode *node = pSet->XNp_get_node_in_set(u_node);
                    for (TiXmlNode *child = node->FirstChild(); child; child = child->NextSibling())
                        if (child->Type() == TiXmlNode::TEXT) {
                            string q = child->Value();
                            Trim(q);
                            s += q;
                        };
                }
                Result += s;
                if (u_node + 1 < Count)
                    Result += ":";
            }
        }
            break;

        case TinyXPath::e_invalid:
        default:
            ErrorMessage(Format("Error: Unknown or invalid return type for XPath `%s'", XPath.c_str()));
            break;
    }

    DeleteEoln(Result);
    return Result;
};

//=============================================
CConcXml::CConcXml() : CBiblIndex() {
    m_BodyFileToBuild = 0;
};

CConcXml::~CConcXml() {
    if (m_BodyFileToBuild) {
        fclose(m_BodyFileToBuild);
    }
    FreeBiblIndices();
    FreeBiblExpanders();
};


bool CConcXml::Start(string ProjectFileName) {
    SetPath(ProjectFileName);

    if (m_BodyFileToBuild) fclose(m_BodyFileToBuild);
    m_BodyFileToBuildSize = 0;
    m_EndOffsetsInBiblFile.clear();
    m_Dates.clear();

    for (FreeBiblStringMap::iterator it = m_FreeBiblIndices.begin(); it != m_FreeBiblIndices.end(); it++) {
        it->second->clear();
    };


    m_BodyFileToBuild = fopen(GetBiblFileName().c_str(), "wb");
    if (!m_BodyFileToBuild) {
        fprintf(stderr, "cannot write to  file  %s\n", GetBiblFileName().c_str());
        return false;
    };

    return true;
};


bool CConcXml::AddIndexItem(const CBibliography &Bibliography) {
    {
        string BiblStr = Bibliography.WriteToString();
        fprintf(m_BodyFileToBuild, "%s", BiblStr.c_str());
        m_BodyFileToBuildSize += BiblStr.length();
    }



    // saving free bibliographical attributes
    {
        int BiblAttribNo = 0;
        assert (Bibliography.m_BiblAttribs.size() == m_FreeBiblIndices.size());
        for (FreeBiblStringMap::iterator it = m_FreeBiblIndices.begin();
             it != m_FreeBiblIndices.end(); it++, BiblAttribNo++)
            it->second->RegisterBiblStringItemId(Bibliography.m_BiblAttribs[BiblAttribNo]);
    }

    m_EndOffsetsInBiblFile.m_vec.push_back(m_BodyFileToBuildSize);

    {
        int Date;
        Bibliography.ConvertDateToInt(Date);
        m_Dates.m_vec.push_back(Date);
    };


    return true;
};

void CConcXml::DeleteFiles() {
    remove(GetBiblFileName().c_str());
    remove(GetBiblIndexFileName().c_str());
    remove(GetBiblDateIndexFileName().c_str());
    for (FreeBiblStringMap::iterator it = m_FreeBiblIndices.begin(); it != m_FreeBiblIndices.end(); it++) {
        it->second->DeleteBiblFiles(m_Path);
    };

};


void CConcXml::SetFreeBiblByName(const string &name, const string &value, CBibliography &result) const {
    map<string, size_t>::const_iterator it = m_FreeBiblNameToPosition.find(name);
    if (it == m_FreeBiblNameToPosition.end())
        throw CExpc(Format("Free bibliographical index \"%s\" is not registered", name.c_str()));
    result.m_BiblAttribs[it->second] = value;
}


void CConcXml::ExitWithoutSave() {
    if (m_BodyFileToBuild)
        fclose(m_BodyFileToBuild);
    m_BodyFileToBuild = 0;
    m_BodyFileToBuildSize = 0;
    DeleteFiles();
};

void CConcXml::FinalSaveBibliography() {
    fclose(m_BodyFileToBuild);
    m_BodyFileToBuild = 0;
    m_BodyFileToBuildSize = 0;

    for (FreeBiblStringMap::iterator bibl_it = m_FreeBiblIndices.begin(); bibl_it != m_FreeBiblIndices.end(); bibl_it++)
        if (!bibl_it->second->ConvertAndSaveToDiskAfterIndexing(m_Path))
            throw CExpc("ConvertAndSaveToDiskAfterIndexing failed");;

    string BiblIndexFileName = GetBiblIndexFileName();
    remove(BiblIndexFileName.c_str());
    if (FileExists(BiblIndexFileName.c_str())) {
        throw CExpc(Format("Cannot delete %s!\n", BiblIndexFileName.c_str()));
    };

    m_EndOffsetsInBiblFile.ensureVec();
    if (!WriteVector(BiblIndexFileName, m_EndOffsetsInBiblFile.m_vec))
        throw CExpc(
            Format("Cannot write index in CConcXml::FinalSaveBibliography, file %s!\n", BiblIndexFileName.c_str()));

    if (!FileExists(BiblIndexFileName.c_str())) {
        throw CExpc(Format("Cannot create %s!\n", BiblIndexFileName.c_str()));
    };

    {
        string DatesFName = GetBiblDateIndexFileName();
        remove(DatesFName.c_str());
        m_Dates.ensureVec();
        if (!WriteVector(DatesFName, m_Dates.m_vec))
            throw CExpc("WriteVector failed");
        if (!FileExists(DatesFName.c_str())) {
            throw CExpc(Format("Cannot create %s!\n", DatesFName.c_str()));
        };
    }
};





bool CConcXml::UnionBibliographies(const vector<const CConcXml *> &Bibls) {
    string logname("CConcXml::UnionBibliographies()");

    //-- populate: m_EndOffsetsInBiblFile (*._bibl_idx)
    ddcLogInfo(logname + ": populating " + GetBiblIndexFileName());
    m_EndOffsetsInBiblFile.clear();
    m_EndOffsetsInBiblFile.ensureVec();
    file_off_t boffset = 0;
    size_t eobfi = 0;
    for (size_t bi = 0; bi < Bibls.size(); ++bi) {
        m_EndOffsetsInBiblFile.m_vec.insert(m_EndOffsetsInBiblFile.m_vec.end(),
                                            Bibls[bi]->m_EndOffsetsInBiblFile.begin(),
                                            Bibls[bi]->m_EndOffsetsInBiblFile.end());
        for (; eobfi < m_EndOffsetsInBiblFile.m_vec.size(); ++eobfi)
            m_EndOffsetsInBiblFile.m_vec[eobfi] += boffset;
        if (!m_EndOffsetsInBiblFile.m_vec.empty())
            boffset = m_EndOffsetsInBiblFile.m_vec.back();
    }
    m_EndOffsetsInBiblFile.ensureData();
    m_EndOffsetsInBiblFile.save(GetBiblIndexFileName());

    //-- populate: bibl file (*._bibl)
    ddcLogInfo(logname + ": populating " + GetBiblFileName());
    if (FileExists(GetBiblFileName())) remove(GetBiblFileName().c_str());
    for (size_t bi = 0; bi < Bibls.size(); ++bi) {
        if (FileExists(Bibls[bi]->GetBiblFileName()))
            FileAppend(Bibls[bi]->GetBiblFileName(), GetBiblFileName());
    }

    //-- sanity check: *._bibl <-> *._bibl_idx
    if (FileExists(GetBiblFileName()) && FileSize(GetBiblFileName()) != boffset)
        throw CExpc(Format("%s: Error: bibl index size mismatch (*._bibl_idx ~ %zd != %zd ~ *._bibl)",
                           logname.c_str(), (size_t) boffset, FileSize(GetBiblFileName())));

    //-- populate: *._bibl_date
    ddcLogInfo(logname + ": populating " + GetBiblDateIndexFileName());
    m_Dates.clear();
    m_Dates.ensureVec();
    for (size_t bi = 0; bi < Bibls.size(); ++bi) {
        m_Dates.m_vec.insert(m_Dates.m_vec.end(), Bibls[bi]->m_Dates.begin(), Bibls[bi]->m_Dates.end());
    }
    m_Dates.save(GetBiblDateIndexFileName());

    //-- populate: free bibl attributes
    vector<size_t> FileCounts(Bibls.size());
    for (size_t bi = 0; bi < Bibls.size(); ++bi)
        FileCounts[bi] = Bibls[bi]->m_Dates.size();
    for (FreeBiblStringMap::iterator fbi = m_FreeBiblIndices.begin(); fbi != m_FreeBiblIndices.end(); ++fbi) {
        const string &name = fbi->first;
        CFreeBiblIndex *fbx = fbi->second;
        ddcLogInfo(logname + ": populating free bibl index " + name);

        //-- get sub-indices
        vector<const CFreeBiblIndex *> bixs(Bibls.size());
        for (size_t bi = 0; bi < Bibls.size(); ++bi) {
            bixs[bi] = Bibls[bi]->GetFreeBiblIndex(name);
            if (bixs[bi] == NULL)
                ddcLogWarn(
                    logname + ": Warning: no free bibl index '" + name + "' in sub-project '" + Bibls[bi]->m_Path +
                    "' - using default values");
        }
        fbx->CreateUnion(m_Path, bixs, FileCounts);
    }


    return true;
};

bool CConcXml::SplitBibliography(vector<CConcXml *> &Bibls, const vector<DWORD> &EndFileNo) const {
    string logname("CConcXml::SplitBibliography()");
    assert(Bibls.size() == EndFileNo.size());

    //-- split: m_EndOffsetsInBiblFile (*._bibl_idx)
    ddcLogInfo(logname + ": splitting " + GetBiblIndexFileName());
    file_off_t boffset = 0;
    for (size_t i = 0; i < Bibls.size(); ++i) {
        Bibls[i]->m_EndOffsetsInBiblFile.clear();
        Bibls[i]->m_EndOffsetsInBiblFile.ensureVec();
        Bibls[i]->m_EndOffsetsInBiblFile.m_vec.insert(Bibls[i]->m_EndOffsetsInBiblFile.m_vec.end(),
                                                      m_EndOffsetsInBiblFile.begin() + (i == 0 ? 0 : EndFileNo[i - 1]),
                                                      m_EndOffsetsInBiblFile.begin() + EndFileNo[i]);
        for (vector<file_off_t>::iterator foi = Bibls[i]->m_EndOffsetsInBiblFile.m_vec.begin();
             foi != Bibls[i]->m_EndOffsetsInBiblFile.m_vec.end(); ++foi)
            *foi -= boffset;

        ddcLogTrace(logname + ": saving " + Bibls[i]->GetBiblIndexFileName());
        Bibls[i]->m_EndOffsetsInBiblFile.ensureData();
        Bibls[i]->m_EndOffsetsInBiblFile.save(Bibls[i]->GetBiblIndexFileName());

        boffset = m_EndOffsetsInBiblFile[EndFileNo[i] - 1];
    }

    //-- split: bibl file (*._bibl)
    ddcLogInfo(logname + ": splitting " + GetBiblFileName());
    FILE* mainBodyFile = fopen(GetBiblFileName().c_str(), "rb");
    try {
        for (size_t i = 0; i < Bibls.size(); ++i) {
            file_off_t bf_begin = (i == 0 ? 0 : m_EndOffsetsInBiblFile[EndFileNo[i - 1] - 1]);
            file_off_t bf_end = m_EndOffsetsInBiblFile[EndFileNo[i] - 1];

            FILE *bf_out = fopen(Bibls[i]->GetBiblFileName().c_str(), "wb");
            if (bf_out == NULL)
                throw CExpc(Format("%s: Error: open failed for partition #%zd bibl file: %s", logname.c_str(), i,
                                   strerror(errno)));
            if (!FSeek(mainBodyFile, bf_begin, SEEK_SET))
                throw CExpc(Format("%s: Error: seek failed for %s to position %zd", GetBiblFileName().c_str(),
                                   (size_t) bf_begin));

            FileAppendPartial(mainBodyFile, bf_out, bf_end - bf_begin);
            if (fclose(bf_out) != 0)
                throw CExpc(Format("%s: Error: close failed for partition #%zd bibl file: %s", logname.c_str(), i,
                                   strerror(errno)));

            //-- sanity check: *._bibl <-> *._bibl_idx
            if (FileSize(Bibls[i]->GetBiblFileName()) != Bibls[i]->m_EndOffsetsInBiblFile.m_vec.back())
                throw CExpc(
                    Format("%s: Error: bibl index size mismatch for patition #%zd (*._bibl_idx ~ %zd != %zd ~ *._bibl)",
                           logname.c_str(), i,
                           (size_t) Bibls[i]->m_EndOffsetsInBiblFile.m_vec.back(),
                           (size_t) FileSize(Bibls[i]->GetBiblFileName())));
        }
    }
    catch (exception& e) {
        fclose (mainBodyFile);
        throw;
    }

    //-- populate: *._bibl_date
    ddcLogInfo(logname + ": splitting " + GetBiblDateIndexFileName());
    for (size_t i = 0; i < Bibls.size(); ++i) {
        Bibls[i]->m_Dates.clear();
        Bibls[i]->m_Dates.ensureVec();
        Bibls[i]->m_Dates.m_vec.insert(Bibls[i]->m_Dates.m_vec.end(),
                                       m_Dates.begin() + (i == 0 ? 0 : EndFileNo[i - 1]),
                                       m_Dates.begin() + EndFileNo[i]);
        Bibls[i]->m_Dates.ensureData();
        Bibls[i]->m_Dates.save(Bibls[i]->GetBiblDateIndexFileName());
    }

    //-- populate: free bibl attributes
    for (FreeBiblStringMap::const_iterator fbi = m_FreeBiblIndices.begin(); fbi != m_FreeBiblIndices.end(); ++fbi) {
        const string &name = fbi->first;
        const CFreeBiblIndex *fbx = fbi->second;

        vector<CFreeBiblIndex *> parts(Bibls.size());
        vector<string> paths(Bibls.size());
        bool canSplitBibl = true;
        for (size_t i = 0; i < Bibls.size(); ++i) {
            if ((parts[i] = Bibls[i]->GetFreeBiblIndex(name)) == NULL) {
                ddcLogWarn(Format("%s: Warning: no free bibl index '%s' in partition #%zd - skipping", logname.c_str(),
                                  name.c_str(), i));
                canSplitBibl = false;
                break;
            }
            paths[i] = Bibls[i]->m_Path;
        }
        if (canSplitBibl) {
            ddcLogInfo(logname + ": splitting free bibl index " + name);
            fbx->CreatePartitions(parts, paths, EndFileNo);
        }
    }

    //-- all done
    return true;
};




void CConcXml::LoadXmlAndReadBibliography(TiXmlDocument &doc, const char *pFileBuffer, CBibliography &Bibl) {
    string Buffer = pFileBuffer;
    doc.Parse(Buffer.c_str());

    if (doc.Error()) {
        throw CExpc(Format("cannot open or parse Col=%i,  Row=%i, Error=%s", doc.ErrorCol(), doc.ErrorRow(),
                           doc.ErrorDesc()));
    };
    Bibl.CleanBibliography();

    if (!m_OrigXPath.empty())
        Bibl.m_OrigBibl = ReadXmlField(doc, m_OrigXPath);

    if (!m_ScanXPath.empty())
        Bibl.m_ScanBibl = ReadXmlField(doc, m_ScanXPath);

    if (!m_DateXPath.empty()) {
        Bibl.m_DateStr = ReadXmlField(doc, m_DateXPath);
        int Date;
        if (!Bibl.ConvertDateToInt(Date)) {
            if (Bibl.m_DateStr.empty())
                throw CExpc(Format("Empty date!", Bibl.m_DateStr.c_str()));
            else
                throw CExpc(Format("Bad date format (\"%s\")", Bibl.m_DateStr.c_str()));
        };
    }

    if (!m_StartPageXPath.empty()) {
        string page_str = ReadXmlField(doc, m_StartPageXPath);
        Bibl.m_StartPageInfo = UnknownPageNumber;
        if (!page_str.empty()) {
            int i = atoi(page_str.c_str());
            if (i != 0)
                Bibl.m_StartPageInfo = i;
        };

    }


    assert (Bibl.m_BiblAttribs.empty());
    for (FreeBiblStringMap::iterator bibl_it = m_FreeBiblIndices.begin();
         bibl_it != m_FreeBiblIndices.end(); bibl_it++) {
        const CFreeBiblIndex *pIndexItem = bibl_it->second;
        string q = ReadXmlField(doc, pIndexItem->m_Xpath);
        // push attributes in the same order as m_FreeBiblIndices is ordered
        Bibl.m_BiblAttribs.push_back(q);
    };

};

void CConcXml::SetFreeBiblAttribsEmpty(CBibliography &Bibl) const {
    assert (Bibl.m_BiblAttribs.empty());
    for (size_t i = 0; i < m_FreeBiblIndices.size(); ++i)
    {
        Bibl.m_BiblAttribs.push_back("");
    }
};



void CConcXml::ReadMorphXmlFileIntoGraTable(string FileName, const char *pFileBuffer, vector<CXmlToken> &GraTable,
                                            CBibliography &Bibl) {

    TiXmlDocument doc(FileName.c_str());

    LoadXmlAndReadBibliography(doc, pFileBuffer, Bibl);

    vector<TiXmlElement *> TextAreas;
    GetTextAreaElements(doc, TextAreas);

    for (size_t TextAreaNo = 0; TextAreaNo < TextAreas.size(); TextAreaNo++) {
        TiXmlElement *text = TextAreas[TextAreaNo];

        size_t AllWordsCount = 0;
        string LastReadWord;
        try {
            for (TiXmlElement *sent = text->FirstChildElement("s"); sent; sent = sent->NextSiblingElement("s")) {
                size_t CountOfWord = 0;
                for (TiXmlElement *xml_word = sent->FirstChildElement(); xml_word; xml_word = xml_word->NextSiblingElement()) {

                    CXmlToken Word;
                    Word.m_Type = xml_word->Value();
                    Trim(Word.m_Type);
                    if (Word.m_Type == "pb") {
                        const char *q = xml_word->Attribute("n");
                        if (q) {
                            Word.m_WordStr = q;
                            GraTable.push_back(Word);
                            continue;
                        } else {
                            throw CExpc(Format("bad page break; cannot parse the input [WordNo=%i LastReadWord=%s]",
                                               AllWordsCount, LastReadWord.c_str()));
                        };
                    };

                    {
                        TiXmlNode *xml_word_str = xml_word->FirstChild();
                        if (!xml_word_str) {
                            throw CExpc(Format("cannot get the next word [WordNo=%i LastReadWord=%s]", AllWordsCount,
                                               LastReadWord.c_str()));
                        };
                        Word.m_WordStr = xml_word_str->Value();
                        Trim(Word.m_WordStr);
                    };
                    if (Word.m_WordStr.empty()) {
                        fprintf(stderr, "empty word after word WordNo=%zi WordStr=%s\n", AllWordsCount,
                                LastReadWord.c_str());
                        continue;
                    };


                    for (TiXmlElement *xml_annot = xml_word->FirstChildElement(
                             "ana"); xml_annot; xml_annot = xml_annot->NextSiblingElement("ana")) {
                        CXmlMorphAnnot A;

                        {
                            const char *q = xml_annot->Attribute("lex");
                            string s = q ? q : "";
                            for (int i = 0; i < s.length(); i++)
                                if ((s[i] != '`') && (s[i] != '*'))
                                    A.m_Lemma += s[i];
                        };

                        {
                            const char *s = xml_annot->Attribute("gr");
                            if (s)
                                A.m_GrammemsStr = s;
                        };
                        Word.m_Annots.push_back(A);
                    };
                    GraTable.push_back(Word);
                    CountOfWord++;
                    AllWordsCount++;
                    LastReadWord = Word.m_WordStr;
                };

                if (CountOfWord > 0) {
                    GraTable.back().m_bLastInSentence = true;
                };
            };
        }
        catch (...) {
            throw CExpc(Format("an exception while reading xml WordNo=%i LastReadWord=%s", AllWordsCount,
                               LastReadWord.c_str()));

        };
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
