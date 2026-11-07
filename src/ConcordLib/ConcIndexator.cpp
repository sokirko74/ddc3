#include "StdConc.h"
#include "DwdsThesaurus.h"
#include "ConcIndexator.h"
#include "DocumentIterator.h"
#include <deque>

using namespace std;

//===========================================
// globals

const uint32_t DefaultMaxTokenCountInOnePeriod = 5000000;

const uint32_t DefaultMaxInputLoadIndexSize    =  400000;


//===========================================
//================== Common functions =======
//===========================================

// Here is the definition of a token
//! Russian "jo" -> "je" (U+0451 -> U+0435, U+0401 -> U+0415) in utf8; formerly done by graphan (m_bConvertRussianJo2Je)
static void ReplaceRussianJo(std::string& s) {
    for (size_t i = 0; i + 1 < s.size(); i++) {
        if ((BYTE)s[i] == 0xD1 && (BYTE)s[i+1] == 0x91) { s[i] = (char)0xD0; s[i+1] = (char)0xB5; }
        else if ((BYTE)s[i] == 0xD0 && (BYTE)s[i+1] == 0x81) { s[i+1] = (char)0x95; }
    }
}

bool IsWord(const CGraphmatFile& piGraphmat, long GraLine) {
    return piGraphmat.HasDescr(GraLine, OLLE)
        || piGraphmat.HasDescr(GraLine, ORLE);
};

bool IsDigit(const CGraphmatFile& piGraphmat, long GraLine) {
    return piGraphmat.HasDescr(GraLine, ODigits)
        || piGraphmat.HasDescr(GraLine, ONumChar);
};

bool IsSentenceEnd(const CGraphmatFile& piGraphmat, long GraLine) {
    return piGraphmat.HasDescr(GraLine, OSentEnd);
}



CConcIndexator::CConcIndexator() {
    InitDefaultOptions();
    m_pDwdsThesaurus = 0;

};


CConcIndexator::~CConcIndexator() {
};

//  graphematical definition of a token
bool CConcIndexator::IsDWDSToken(long GraLine) const {
    return IsSentenceEnd(Graphmat, GraLine)
        || IsWord(Graphmat, GraLine)
        || IsDigit(Graphmat, GraLine)
        || (
            m_bIndexPunctuation
            && Graphmat.HasDescr(GraLine, OPun)
            );
}

void CConcIndexator::InitGraphan()  {
    //  first we should init properties, for example, language,
    //  because  loading dictionaries of graphan depends upon the language
    Graphmat.m_Language = m_Language;
    Graphmat.m_bUseParagraphTagToDivide = m_bUseParagraphTagToDivide;
    Graphmat.m_bEmptyLineIsSentenceDelim = m_bEmptyLineIsSentenceDelim;
    Graphmat.m_bUseIndention = m_bUseIndention;
    Graphmat.m_bKeepUnknownChars = true;   //-- e.g. Greek words in a Russian text are indexed, see GetTokenUtf8()
    try {
        Graphmat.LoadDicts(m_Language);
    }
    catch (std::exception& e) {
        throw CDDCExpc(Format("Graphan::LoadDicts failed! Error: %s", e.what()));
    }
};




bool CConcIndexator::SaveCorpusFileList() const {
    string ConFile = GetFileNameForCorpusFileNames(); //-- *._con
    FILE *cfp = fopen(ConFile.c_str(), "wb");
    if (!cfp) return false;

    string ListFile = ConFile + "_files";
    FILE *lfp = fopen(ListFile.c_str(), "wb");
    if (!lfp) return false;

    string OffsetsFile = ConFile + "_idx";
    FILE *ofp = fopen(OffsetsFile.c_str(), "wb");
    if (!ofp) return false;

    string PrefixFile = ConFile + "_prefix";
    FILE *pfp = fopen(PrefixFile.c_str(), "wb");
    if (!pfp) return false;

    //-- *._con (v2.1.13): VERSION_INFO ""
    std::string vmin_str = DDCVersionMinW.str();
    fprintf(cfp, "%s / min-compat %s\n", DDCVersionStr.c_str(), vmin_str.c_str());
    fclose(cfp);

    //-- *._con_prefix (v2.1.13)
    std::string prefix_str = GetCommonFilePrefix();
    fprintf(pfp, "%s\n", prefix_str.c_str());
    fclose(pfp);

    //-- *._con_files, *._con_idx (v2.1.13)
    size_t cnt = m_CorpusFiles.size();
    for (ddcCorpusList<>::IdT i = 0; i < cnt; i++) {
        ddcCorpusList<>::OffT pos = (ddcCorpusList<>::OffT)ftell64(lfp);
        fwrite(&pos, sizeof(ddcCorpusList<>::OffT), 1, ofp);
        fprintf(lfp, "%s\n", m_CorpusFiles[i].c_str());
    }
    fclose(ofp);
    fclose(lfp);

    return true;
}

bool CConcIndexator::SaveMaskedFileIds() const {
    //-- ugly temporary so we can use WriteVector()
    vector<CFileNo> maskedVec(m_MaskedFiles.begin(), m_MaskedFiles.end());
    return WriteVector(GetFileNameForMaskedFileIds(), maskedVec);
}

void CConcIndexator::DestroyIndex() {
    AssertHasPath();

    if (!RemoveHitBordersFileAndClear(m_Path))
        throw CDDCExpc("RemoveHitBordersFileAndClear failed, cannot destroy index, this corpus is possibly already used");

    if (!DestroyIndices())
        throw CDDCExpc("DestroyIndices failed, cannot destroy index, this corpus is possibly already used");

    if (FileExists(GetSearchPeriodsFileName().c_str()))
        if (remove(GetSearchPeriodsFileName().c_str()))
            throw CDDCExpc("remove(GetSearchPeriodsFileName failed");

    if (FileExists(GetFileNameForCorpusFileNames().c_str()))
        if (remove(GetFileNameForCorpusFileNames().c_str()))
            throw CDDCExpc("remove GetFileNameForCorpusFileNames failed");

    m_CorpusFiles.clear();

    if (FileExists(GetFileNameForMaskedFiles().c_str()))
        if (remove(GetFileNameForMaskedFiles().c_str()))
            throw CDDCExpc("remove GetFileNameForMaskedFiles failed");
    ;
    if (FileExists(GetFileNameForMaskedFileIds().c_str()))
        if (remove(GetFileNameForMaskedFileIds().c_str()))
            throw CDDCExpc("remove GetFileNameForMaskedFileIds failed");
    m_MaskedFiles.clear();
};

uint32_t CConcIndexator::GetMaxTokenCountInOnePeriod() const {
    if (m_UserMaxTokenCountInOnePeriod != 0)
        return m_UserMaxTokenCountInOnePeriod;
    else
        return DefaultMaxTokenCountInOnePeriod;
};

uint32_t CConcIndexator::GetMaxInputLoadIndexSize() const {
    if (m_UserMaxInputLoadIndexSize != 0)
        return m_UserMaxInputLoadIndexSize;
    else
        return DefaultMaxInputLoadIndexSize;
};

// a page break for the graphematics; a page number that is not a number (e.g. "iv") is unknown
static string PageBreakForGraphan(const char* number) {
    return '\n' + string(1, PageBreakMarker)
        + (isdigit((BYTE)number[0]) ? string(number, strspn(number, "0123456789")) : std::to_string(UnknownPageNumber))
        + '\n';
}

void GetTextFromXMLRecursive(const pugi::xml_node &parent, string &Result) {
    if (parent.type() == pugi::node_pcdata || parent.type() == pugi::node_cdata) {
        if (Result.empty())
            Result += PageBreakForGraphan(std::to_string(UnknownPageNumber).c_str());

        // control characters (forbidden in XML 1.0, but pugixml lets "&#2;" through) would be read
        // by the graphematics as markup inserted by DDC, e.g. TextAreaEndMarker
        size_t start = Result.length();
        Result += parent.value();
        for (size_t i = start; i < Result.length(); i++)
            if ((BYTE)Result[i] < 0x09)
                Result[i] = ' ';
    } else if (parent.type() == pugi::node_element) {
        string type = parent.name();
        Trim(type);

        if (type == "pb") {
            if (!parent.attribute("n")) {
                throw CDDCExpc("Cannot parse page break element");
            };
            Result += PageBreakForGraphan(parent.attribute("n").value());
        } else {
            for (pugi::xml_node child = parent.first_child(); child; child = child.next_sibling()) {
                GetTextFromXMLRecursive(child, Result);
            };
        };
        if (type == "p")
            Result += "\n</p>\n";
    } else if (parent.type() == pugi::node_comment || parent.type() == pugi::node_pi) {
        // skipping comments and processing instructions
    } else {
        throw CDDCExpc((Format("Unknown xml-node:%s. Some parts of file cannot be parsed!", parent.name())));
    };
};

// read the input xml that is in CWB-format (corpus work bench format)
void GetCWBFormattedStringRecursive(const pugi::xml_node &parent, string &Result) {
    if (parent.type() == pugi::node_pcdata || parent.type() == pugi::node_cdata) {
        Result += parent.value() + string("\n");
    } else if (parent.type() == pugi::node_element) {
        string type = parent.name();
        Trim(type);
        bool bNotLineBreak = (type != PredefinedTableLineTag);
        if (type == "pb") {
            if (parent.attribute("n")) {
                Result += Format("<pb %s>\n", parent.attribute("n").value());
                return;
            } else {
                throw CDDCExpc("bad page break");
            };
        } else if (bNotLineBreak)
            Result += Format("\n<%s>\n", type.c_str());


        for (pugi::xml_node child = parent.first_child(); child; child = child.next_sibling()) {
            GetCWBFormattedStringRecursive(child, Result);
        };

        if (bNotLineBreak)
            Result += Format("\n</%s>\n", type.c_str());

    } else if (parent.type() == pugi::node_comment || parent.type() == pugi::node_pi) {
        //-- moo: skip comments in document body
        ;
    } else {
        throw CDDCExpc(Format("Unknown xml-node:%s. Some parts of file cannot be parsed!", parent.name()));
    };
};


void
CConcIndexator::LoadXmlFile(string FileName, const char *pFileBuffer, CBibliography &Bibl) {
    if (m_BiblIndex.GetTextAreasCount() == 0) {
        throw CDDCExpc(Format("Error! Cannot index xml files, since no text areas defined in the options file!"));
    }

    pugi::xml_document doc;

    m_BiblIndex.LoadXmlAndReadBibliography(doc, pFileBuffer, Bibl);

    vector<pugi::xml_node> TextAreas;
    m_BiblIndex.GetTextAreaElements(doc, TextAreas);

    string AllTexts;
    for (size_t TextAreaNo = 0; TextAreaNo < TextAreas.size(); TextAreaNo++) {
        pugi::xml_node body = TextAreas[TextAreaNo];

        string SourceText;

        if (Bibl.m_StartPageInfo != UnknownPageNumber)
            SourceText = PageBreakForGraphan(std::to_string(Bibl.m_StartPageInfo).c_str());

        try {
            GetTextFromXMLRecursive(body, SourceText);
        }
        catch (const CExpc& e) {
            throw CDDCExpc (Format("Cannot get text from file %s, error=%s", FileName.c_str(), e.what()));
        };

        AllTexts += SourceText;
        AllTexts += '\n';
        AllTexts += TextAreaEndMarker;  // not "</textarea>": it can occur in a text (e.g. a book about HTML)
        AllTexts += "\n\n";
    }

    if (!IsValidUtf8(AllTexts))
        throw CDDCExpc(Format("file %s is not valid UTF-8 (ddc accepts only UTF-8)", FileName.c_str()));
    Graphmat.LoadStringToGraphan(AllTexts);

};

bool IsXmlFile(const string &fileName) {
    const string FileName = StripGzExtension(fileName);
    return (FileName.length() > 4)
        && ((FileName.substr(FileName.length() - 4) == ".xml")
            || (FileName.substr(FileName.length() - 4) == ".XML")
            );
};



void CConcIndexator::CalculateSearchPeriods(uint32_t MaxTokenCountInOnePeriod) {
    if (GetFileBreaks().empty()) return;

    // Calculating Search Periods

    m_SearchPeriods.clear();

    CTokenNo StartTokenNo = 0;
    for (size_t i = 0; i < m_CorpusFiles.size(); i++) {
        CTokenNo FileStart = GetFileStartTokenNo(i);
        if (FileStart - StartTokenNo > MaxTokenCountInOnePeriod) {
            m_SearchPeriods.push_back(FileStart);
            StartTokenNo = FileStart;
        };
    };

    m_SearchPeriods.push_back(GetCorpusEndTokenNo());
};


void CConcIndexator::IndexOneTableTextArea(const string &Text, const CPageNumber &StartPageFromHeader,
                                           size_t &page_breaks_count, CIndexDocument* document) {
    StringTokenizer tok(Text.c_str(), "\r\n");
    deque<pair<string, CTokenNo> > start_chunk_tags_str_and_pos;
    StartTextAreaBorders();
    try {
        while (tok()) {
            string q = tok.val();
            Trim(q);
            if (q.empty()) {
                throw CDDCExpc("Empty lines in CWB format!");
            }
            size_t len = q.length();
            if ((len < 100)
                && (len > 2)
                && (q[0] == '<')
                && (q[len - 1] == '>')
                ) {
                if (q[1] != '/') {
                    string tag_name = q.substr(1, len - 2); // ge the tag name, for example "vp" from "</vp>"
                    if (tag_name.length() > 3 && (tag_name.substr(0, 3) == "pb ")) // page break
                    {
                        int page_number = atoi(tag_name.c_str() + 3);
                        if (page_number != 0) {
                            // add the first page break from the header, if it is not specified in the body
                            if (page_breaks_count == 0) {
                                // moo (v2.0.7, Thu, 28 Mar 2013 09:52:05 +0100): this should never happen any more
                                if ((document->CorpusEndTokenNo - StartPageFromHeader.m_StartTokenNo) > 0)
                                    AddPageBreak(StartPageFromHeader);
                            }

                            CPageNumber Page;
                            Page.m_PageNumber = page_number;
                            Page.m_StartTokenNo = document->CorpusEndTokenNo;
                            AddPageBreak(Page);
                            page_breaks_count++;
                        } else {
                            throw CDDCExpc( Format("bad page break (%s)", q.c_str()));
                        };
                    } else if (!IsRegisteredBreak(tag_name)) {
                        if (m_bIndexChunks)
                            start_chunk_tags_str_and_pos.push_back(make_pair(tag_name, document->CorpusEndTokenNo));
                    };


                } else // an end tag
                {

                    string tag_name = q.substr(2, len - 3); // ge the tag name, for example "vp" from "</vp>"
                    int BrCollec = GetBreakCollectionIndexByName(tag_name);
                    if (BrCollec != -1) {
                        AddBreakByIndex(BrCollec, document->CorpusEndTokenNo);
                    } else {
                        // if it is not a registered break

                        if (m_bIndexChunks) {
                            if (start_chunk_tags_str_and_pos.empty()
                                || (start_chunk_tags_str_and_pos.back().first != tag_name)
                                ) {
                                throw CDDCExpc(Format("Error! An end tag without a start tag is found (%s<>%s)",
                                                   start_chunk_tags_str_and_pos.back().first.c_str(), tag_name.c_str()));
                            }
                            if (document->CorpusEndTokenNo > 0) {
                                string tag = Format("%s,%i", start_chunk_tags_str_and_pos.back().first.c_str(),
                                                    document->CorpusEndTokenNo - start_chunk_tags_str_and_pos.back().second);
                                start_chunk_tags_str_and_pos.pop_back();
                                assert (m_pChunkIndex);
                                m_pChunkIndex->InsertToInputLoadIndex(tag.c_str(), tag.length(),
                                                                      vector<CTokenNo>(1, document->CorpusEndTokenNo - 1));
                            } else {
                                // An empty element at the beginning of the corpus is ignored;
                            }
                        }
                    }
                }

            } else {
                IndexOneToken(document, q.c_str(), m_bResumeOnIndexErrors);
                document->CorpusEndTokenNo++;
            }
        };
        EndTextAreaBorders(document->CorpusEndTokenNo);
    }
    catch (CExpc &err) {
        throw err;
    }
    catch (...) {
        throw CDDCExpc (Format("General exception while processing \"%s\"\n", tok.val()));
    };
}

// Return value: return true, if the input XML is valid and it fits the index structure
void CConcIndexator::IndexFreeIndex(CIndexDocument* document) {

    CBibliography Bibliography;

    pugi::xml_document doc;
    m_BiblIndex.LoadXmlAndReadBibliography(doc, &document->DocumentBuffer[0], Bibliography);

    vector<pugi::xml_node> TextAreas;
    m_BiblIndex.GetTextAreaElements(doc, TextAreas);

    CPageNumber StartPageFromHeader;
    StartPageFromHeader.m_PageNumber = Bibliography.m_StartPageInfo;
    StartPageFromHeader.m_StartTokenNo = document->CorpusEndTokenNo;
    size_t page_breaks_count = 0;

    //moo: add initial page break if requested
    if (StartPageFromHeader.m_PageNumber > 0 && StartPageFromHeader.m_PageNumber != UnknownPageNumber)
        AddPageBreak(StartPageFromHeader);

    //iterate through all text areas
    for (size_t TextAreaNo = 0; TextAreaNo < TextAreas.size(); TextAreaNo++) {
        pugi::xml_node textarea = TextAreas[TextAreaNo];
        string Text;
        // get text from xml
        GetCWBFormattedStringRecursive(textarea, Text);

        // index one text area
        IndexOneTableTextArea(Text, StartPageFromHeader, page_breaks_count, document);
    }

    if (document->CorpusEndTokenNo != StartPageFromHeader.m_StartTokenNo) {
        // if at least one token is found, then add a bibliographical record
        m_BiblIndex.AddIndexItem(Bibliography);
    };
};



void CConcIndexator::LoadFileIntoGraphan(string FileName, const char *pFileBuffer,
                                         CBibliography &Bibl) {
    Bibl.CleanBibliography();
    try {
        if (IsXmlFile(FileName)) {
            LoadXmlFile(FileName, pFileBuffer, Bibl);
        } else {
            if (!IsValidUtf8(pFileBuffer, strlen(pFileBuffer)))
                throw CDDCExpc(Format("file %s is not valid UTF-8 (ddc accepts only UTF-8)", FileName.c_str()));
            Graphmat.LoadStringToGraphan(pFileBuffer);
            m_BiblIndex.SetFreeBiblAttribsEmpty(Bibl);
        };


    }
    catch (const CExpc& c) {
        throw CDDCExpc( Format("Exception %s in CConcIndexator::LoadFileIntoGraphan\n", c.what()));
    }
    catch (...) {
        throw CDDCExpc( "An exception occurred in CConcIndexator::LoadFileIntoGraphan while processing " + FileName);;
    }
}


void CConcIndexator::IndexTextOrHtmlFile(CIndexDocument* document) {
    CBibliography Bibl;
    LoadFileIntoGraphan(document->CorpusFileName, &document->DocumentBuffer[0], Bibl);

    long GraLinesCount = Graphmat.GetTokensCount();
    if (GraLinesCount == 0) {
        // the file is empty
        return;
    };


    CTokenNo StartTokenNo = document->CorpusEndTokenNo;
    CTokenNo CurrSentenceBreak = document->CorpusEndTokenNo;

    size_t FileTokensCount = 0;
    int SentNo = 0;
    char OneIndexLine[5000];
    bool bTheFirstPageBreakIsFound = false;

    int TextAreaNo = 0;
    int TextAreasCount = m_BiblIndex.GetTextAreasCount();
    int SentenceBreakCollection = GetBreakCollectionIndexByName("s");
    if ((SentenceBreakCollection == -1) && !m_bQueryOnlyFiles) {
        throw CDDCExpc("could not find sentence collection");
    }

    // check it before anything of the document is added to the index (a rollback after a failed
    // document trims only the token occurrences, not the breaks and the bibliography)
    {
        int TextAreaEnds = 0;
        for (long GraLineNo = 0; GraLineNo < GraLinesCount; GraLineNo++)
            if (Graphmat.GetUnits()[GraLineNo].IsTextAreaEnd())
                TextAreaEnds++;
        if (TextAreaEnds != TextAreasCount)
            throw CDDCExpc(Format("Some text areas are not present in this document (%i of %i)",
                                  TextAreaEnds, TextAreasCount));
    }

    for (long GraLineNo = 0; GraLineNo < GraLinesCount; GraLineNo++) {
        bool bSentenceEnd = false;
        bool bToken = IsDWDSToken(GraLineNo);
        if (bToken) {
            //-- the index stores utf8 tokens (graphan works with single-byte strings inside)
            std::string Token = Graphmat.GetTokenUtf8(GraLineNo);
            if (m_Language == morphRussian)
                ReplaceRussianJo(Token);
            size_t TokenLen = Token.length();
            if (TokenLen == 0) {
                throw CDDCExpc(Format("Fatal error: An empty word is found!\nGraph.Word No %i from %i \n", GraLineNo,
                                   GraLinesCount));
            };

            if ((BYTE) Token[0] == globalFieldDelimeter) {
                throw CDDCExpc(Format("Error! An input word(LineNo=%i) cannot contain symbol \"%c\"(%i) \n", GraLineNo,
                                   (int) globalFieldDelimeter, (unsigned int) globalFieldDelimeter));
            };

            if (TokenLen + 2 >= sizeof(OneIndexLine))
                throw CDDCExpc(Format("Error! Token is too long (LineNo=%i)", GraLineNo));
            memcpy(OneIndexLine, Token.c_str(), TokenLen);
            OneIndexLine[TokenLen] = globalFieldDelimeter;
            OneIndexLine[TokenLen + 1] = 0;


            if (m_bUseDwdsThesaurus
                && (Graphmat.HasDescr(GraLineNo, OUp)
                    || Graphmat.HasDescr(GraLineNo, OUpLw))
                ) {
                std::string UpperToken = Graphmat.GetUnits()[GraLineNo].GetTokenUpperUtf8();
                OneIndexLine[TokenLen + 1] = globalFieldDelimeter;
                strcpy(OneIndexLine + TokenLen + 2, m_pDwdsThesaurus->GetAllThesInterpetations(UpperToken.c_str()).c_str());
            }

            IndexOneToken(document, OneIndexLine, m_bResumeOnIndexErrors);


            // if m_bQueryOnlyFiles then no sentence break collection
            if (!m_bQueryOnlyFiles && IsSentenceEnd(Graphmat, GraLineNo)) {

                // "1" is for this token
                CurrSentenceBreak = document->CorpusEndTokenNo + 1;
                AddBreakByIndex(SentenceBreakCollection, CurrSentenceBreak);

                SentNo++;
                bSentenceEnd = true;
            };
        } // IsDWDSToken == true

        if (Graphmat.GetUnits()[GraLineNo].IsTextAreaEnd()) {
            AddBreakByName(PredefinedTextAreaBreakName, document->CorpusEndTokenNo);
            TextAreaNo++;
        }


        if ((bToken && (FileTokensCount == 0) && !bTheFirstPageBreakIsFound)
            || Graphmat.GetUnits()[GraLineNo].IsPageBreak()
            ) {
            bTheFirstPageBreakIsFound = true;
            CPageNumber Page;
            Page.m_PageNumber = Graphmat.GetPageNumber(GraLineNo);
            //If we have read end of sentence and after it we have read a page break, and
            //there is no  tokens between this end of sentence and  this page break, then we should
            //shift this page break backward to the end of sentence. Otherwise the first sentence of the  next
            //page will be considered as a sentence from the previous  page.
            //For example we have
            //    <pb 13> Sentence1 <end-of-sentence> <pb 14> Sentence2.
            //Sentence2 starts when Sentence1 terminates, then a page break occurs inside(!) of Sentence2,
            //and it means that Sentence2 starts at page 13 and terminates at page 14. That is not true and
            //we fix this problem.


            if (bSentenceEnd
                || (SentNo == 0)
                )
                Page.m_StartTokenNo = document->CorpusEndTokenNo; // normal case
            else
                Page.m_StartTokenNo = CurrSentenceBreak; //  shifting page break to the last end of sentence

            AddPageBreak(Page);
        };

        if (bToken) {
            document->CorpusEndTokenNo++;

            FileTokensCount++;
        };
    };

    // write the last sentence if it contains at least one token
    if (!m_bQueryOnlyFiles)
        if (CurrSentenceBreak < document->CorpusEndTokenNo) {
            ddcLogError("The last end of sentence is not found, graphematics should be refactored :)");
            CurrSentenceBreak = document->CorpusEndTokenNo;
            AddBreakByIndex(SentenceBreakCollection, document->CorpusEndTokenNo);
            SentNo++;

        };

    if (document->CorpusEndTokenNo != StartTokenNo) {
        // if at least one token is found, then add a bibliographical record
        m_BiblIndex.AddIndexItem(Bibl);
    };

    if (TextAreaNo != TextAreasCount)
        throw CDDCExpc("internal error: the number of text areas changed while indexing");
    Graphmat.FreeTable();
};

void CConcIndexator::StartIndexing() {
    if (!CStringIndexator::StartIndexing(m_Path)) throw CDDCExpc("CStringIndexator::StartIndexing failed, possibly cannot create temp files in the catalog of the corpus!");
    if (!CHitBorders::StartIndexing(m_Path)) throw CDDCExpc("CHitBorders::StartIndexing failed, possibly cannot create temp files in the catalog of the corpus!");
    if (!m_BiblIndex.Start(m_Path)) {
        throw CDDCExpc("Cannot start bibl indexator");
    };
    InitGraphan();
    m_pDwdsThesaurus = 0;
    if (UseDwdsThesaurus())
        m_pDwdsThesaurus = LoadDwdsThesaurus();
};

void CConcIndexator::TerminateIndexing() {
    CStringIndexator::TerminateIndexing();
    BordersEndIndexing(m_Path);
    m_BiblIndex.ExitWithoutSave();
};

void CConcIndexator::NormalEndIndexing() {
    m_BiblIndex.FinalSaveBibliography();
    if (m_pDwdsThesaurus)
        FreeDwdsThesaurus(m_pDwdsThesaurus);
    m_pDwdsThesaurus = 0;
};

void CConcIndexator::IndexOneFile(CIndexDocument* document) {
    switch (m_IndexType) {
        case MorphXML_Index:
            return IndexMorphXml(document);
        case DWDS_Index:
            return IndexTextOrHtmlFile(document);
        case Free_Index:
            return IndexFreeIndex(document);
        case TabFormat_Index:
            return IndexTabFormat(document);
        default:
            assert(false);
    }
};

extern bool CreateMorphIndex(const CStringIndexator* indexator, string path, MorphLanguageEnum language, size_t maxTokenCountInOnePeriod);
bool CConcIndexator::CreateMorphIndexWrapper() {
    return ::CreateMorphIndex(this, m_Path, m_Language, GetMaxTokenCountInOnePeriod());
}

void CConcIndexator::RollbackIndexOneFile(CTokenNo startTrimTokenNo)
{
    ddcLogWarn(Format("Warning: rolling back buffered index data to token #%u\n", startTrimTokenNo));
    for (vector<CStringIndexSet*>::const_iterator ixi=m_Indices.begin(); ixi!=m_Indices.end(); ++ixi) {
        (*ixi)->RollbackLoadIndex(startTrimTokenNo);
    }
};
