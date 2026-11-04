//-*- Mode: C++ -*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2019 by Bryan Jurish
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
#include "StdConc.h"
#include "Concordance.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "../CommonLib/ddcFile.h"


using namespace std;

string GetIndexItemSetByVectorString(const vector<string> &TokenProperties, bool bRegexp) {
    string Result;
    if (bRegexp)
        Result = ".*";

    size_t cnt = TokenProperties.size();
    for (size_t i = 0; i < cnt; i++) {
        Result += '@';
        Result += TokenProperties[i];
        Result += '@';
        if (bRegexp)
            Result += MorphAnnotationsDelimRegExp;
    };

    return Result;
};


//==============================================================
//=======================  CHighlightTags ======================
//==============================================================


CSourceFileHolder::CSourceFileHolder() {
    m_bModifiedListOfFiles = false;
}

bool CSourceFileHolder::SaveSourceFileList(string FileName) {
    FILE *fp = fopen(FileName.c_str(), "wb");
    if (!fp) return false;
    for (long i = 0; i < m_SourceFiles.size(); i++)
        fprintf(fp, "%s\n", m_SourceFiles[i].c_str());
    fclose(fp);

    m_bModifiedListOfFiles = false;
    return true;
}

void CSourceFileHolder::ReadSourceFileList(string FileName) {
    FILE *fp = fopen(FileName.c_str(), "rb");
    if (!fp) {
        throw CDDCExpc(Format("could not open %s\n", FileName.c_str()));
    }

    char s[1024];
    m_SourceFiles.clear();
    while (fgets(s, 1024, fp)) {
        string q = s;
        Trim(q);
        if (q.empty()) continue;
        //-- moo: interpret relative document filenames in .con file wrt the directory containing .con file itself
        string qr = RelativeFileName(FileName, q);
        m_SourceFiles.push_back(qr);
    };
    fclose(fp);
}


void CSourceFileHolder::AddSourceFile(const char *FileName) {
    m_SourceFiles.push_back(FileName);
    m_bModifiedListOfFiles = true;
}

void CSourceFileHolder::AddSourceFilesFrom(const CSourceFileHolder &X) {
    m_SourceFiles.insert(m_SourceFiles.end(), X.m_SourceFiles.begin(), X.m_SourceFiles.end());
    m_bModifiedListOfFiles = true;
}

bool CSourceFileHolder::IsModified() const {
    return m_bModifiedListOfFiles;
};

void CSourceFileHolder::DeleteSourceFile(long ItemNo) {
    m_SourceFiles.erase(m_SourceFiles.begin() + ItemNo);
    m_bModifiedListOfFiles = true;
};

void CSourceFileHolder::DeleteAllSourceFiles() {
    m_SourceFiles.clear();
    m_bModifiedListOfFiles = true;
};

size_t CSourceFileHolder::GetSourceFilesCount() const {
    return m_SourceFiles.size();
};

string CSourceFileHolder::GetSourceFile(size_t FileNo) const {
    return m_SourceFiles[FileNo];
};

// found a file of the corpus which does not  exist, if not return -1
int CSourceFileHolder::FoundNotExistedFile() const {
    for (int i = 0; i < m_SourceFiles.size(); i++)
        if (access(m_SourceFiles[i].c_str(), 04) != 0)
            return i;

    return -1;
};


//==============================================================
//=======================  CHighlightTags ======================
//==============================================================
CHighlightTags::CHighlightTags() {
    m_bWasReadFromString = false;
};

bool CHighlightTags::ReadFromString(const string &s) {
    string q = s;
    StringTokenizer tok(Trim(q).c_str(), ";");
    vector<string> tokens;
    while (tok()) {
        string l = tok.val();
        Trim(l);
        tokens.push_back(l);
    };
    if (tokens.size() != 4)
        return false;
    m_FirstOpener = unescapeCString(tokens[0]);
    m_FirstCloser = unescapeCString(tokens[1]);
    m_RestOpener = unescapeCString(tokens[2]);
    m_RestCloser = unescapeCString(tokens[3]);
    m_bWasReadFromString = true;
    return true;
}

string CHighlightTags::ToString() const {
    return Format("%s;%s;%s;%s",
                  escapeCString(m_FirstOpener).c_str(),
                  escapeCString(m_FirstCloser).c_str(),
                  escapeCString(m_RestOpener).c_str(),
                  escapeCString(m_RestCloser).c_str());
};

//==============================================================
//=======================  CConcordance ======================
//==============================================================


CConcordance::CConcordance() {
    InitDefaultOptions();
};


CConcordance::~CConcordance() {
};


void CConcordance::AssertHasPath() const {
    assert(m_Path != "#empty_path");
    if (m_Path == "#empty_path") {
        ErrorMessage("Uninitialized path");
        throw CDDCExpc(errNonePath, "Exception: Uninitialized path for index files");
    };
};


string CConcordance::GetFileNameForCorpusFileNames() const {
    return MakeFName(m_Path, "_con");
};

string CConcordance::GetFileNameForMaskedFiles() const {
    return MakeFName(m_Path, "_masked");
};

string CConcordance::GetFileNameForMaskedFileIds() const {
    return MakeFName(m_Path, "_masked_ids");
};


vector<string> CConcordance::GetTokenFields(const COutputToken &tok) {
    vector<string> fields(m_IndicesToShow.size());
    size_t fi, i0, i1, dsize = m_InterpDelimiter.size();
    const string &istr = tok.m_InterpStr;

    fields[0] = tok.m_TokenStr;
    for (fi = 1, i0 = dsize; fi < fields.size() && i0 < tok.m_InterpStr.size(); fi++, i0 = i1 + dsize) {
        i1 = istr.find(m_InterpDelimiter, i0);
        fields[fi].assign(istr, i0, i1 - i0);
        if (i1 >= istr.size()) break;
    }

    return fields;
};


string CConcordance::GetCommonFilePrefix() const {
    string CommonFilePrefix = "";
    for (size_t fi = 0; fi < m_CorpusFiles.size(); ++fi) {
        string f = m_CorpusFiles[fi];
        if (fi == 0) {
            CommonFilePrefix = f;
        } else {
            int i = 0;
            for (; i < min(f.length(), CommonFilePrefix.length()) && f[i] == CommonFilePrefix[i]; ++i);
            CommonFilePrefix.erase(i);
        }
    }
    return CommonFilePrefix;
};


void CConcordance::LoadCorpusFiles() {
    m_CorpusFiles.clear();
    string ConFile = GetFileNameForCorpusFileNames();

    //-- open raw corpus-file list
    m_CorpusFiles.open(ConFile, ConFile + "_files", ConFile + "_idx", m_bMemoryMap);
    ddc_format_version_check(m_CorpusFiles.VersionString().c_str(), ConFile.c_str());

    //-- get shared filename prefix (*._con_prefix)
    string PrefixFile = ConFile + "_prefix";
    if (FileExists(PrefixFile)) {
        LoadFileToString(PrefixFile, m_CommonFilePrefix, true);
        Trim(m_CommonFilePrefix);
    } else {
        ddcLogWarn("WARNING: CConcordance::LoadCorpusFiles(): shared prefix file '" + PrefixFile +
                   "' not found: please upgrade your index!");
        m_CommonFilePrefix = GetCommonFilePrefix();
    }

    UpdateTimestamp(ConFile.c_str());
};

void CConcordance::LoadMaskedFiles() {
    m_MaskedFiles.clear();

    //-- masked files: strings: CORPUS._masked
    string maskedFile = GetFileNameForMaskedFiles();
    FILE *fp = fopen(maskedFile.c_str(), "rb");
    if (fp) {
        char s[1024];
        while (fgets(s, 1024, fp)) {
            string file = s;
            Trim(file);
            if (file.empty()) continue;
            ddcCorpusList<>::IdT fileid = m_CorpusFiles.rfind(file); //-- mask LAST occurrence
            if (fileid == m_CorpusFiles.NO_ID) {
                ddcLogWarn(Format("CConcordance::LoadMaskedFiles(): %s in %s is not a corpus file name", file.c_str(),
                                  GetFileNameForMaskedFiles().c_str()));
                continue; //-- just skip
            }
            m_MaskedFiles.insert(fileid);
        }
        fclose(fp);
        ddcLogDebug(Format("blacklisted %zd file(s) from %s", m_MaskedFiles.size(), maskedFile.c_str()));
    }

    //-- masked files: binary IDs: CORPUS._masked_ids
    string maskedBinFile = GetFileNameForMaskedFileIds();
    if (FileExists(maskedBinFile)) {
        ddcVecFile<CFileNo> maskedBinVec;
        maskedBinVec.open(maskedBinFile, m_bMemoryMap);
        m_MaskedFiles.insert(maskedBinVec.begin(), maskedBinVec.end());
        ddcLogDebug(Format("blacklisted %zd file(s) from %s", maskedBinVec.size(), maskedBinFile.c_str()));
    }

};


void CConcordance::LoadSourceFilesAndOptions(string FileName, bool reallyReadSourceFiles) {
    m_LocalPathPrefix = "";
    m_InternetPathPrefix = "";

    m_Path = FileName;

    // reading options  from *.opt file
    string PathFile = MakeFName(FileName, "opt");
    string AllOptions;
    if (LoadFileToString(PathFile, AllOptions)) {
        LoadOptionsFromString(AllOptions);
    } else {
        ddcLogWarn(
            Format("CConcordance::LoadSourceFilesAndOptions(): Warning: cannot find file %s", PathFile.c_str()));
    }

    SetPath(FileName);

    // reading source files
    // 2018-08-21 16:05:27+0200 moo: don't read source files for runtime query
    if (reallyReadSourceFiles) {
        ReadSourceFileList(FileName);
    };

    UpdateTimestamp(FileName.c_str());
};


bool CConcordance::GetAllOccurrences(vector<CTokenNo> &occurrences, size_t searchPeriodNo) const {
    CTokenNo PeriodBegin = (searchPeriodNo == 0) ? 0 : GetSearchPeriod(searchPeriodNo - 1);
    CTokenNo PeriodEnd = GetSearchPeriod(searchPeriodNo);

    occurrences.clear();
    occurrences.reserve(PeriodEnd - PeriodBegin);
    for (CTokenNo occ = PeriodBegin; occ < PeriodEnd; ++occ) {
        occurrences.push_back(occ);
    }

    return true;
}

//----------------------------------------------------------------------
bool CConcordance::GetOccurrencesByPosition(const string &BreakName, int anchor, vector<CTokenNo> &occurrences,
                                            size_t searchPeriodNo) const {
    const CHBreakCollection *bcol = GetBreakCollectionByName(BreakName);
    if (!bcol)
        throw CDDCExpc(errRuntime, "CConcordance::GetOccurrencesByPosition(): unknown break collection `%s'",
                    BreakName.c_str());

    CTokenNo PeriodBegin = (searchPeriodNo == 0) ? 0 : GetSearchPeriod(searchPeriodNo - 1);
    CTokenNo PeriodEnd = GetSearchPeriod(searchPeriodNo);
    ddcBreakVector::const_iterator bi = lower_bound(bcol->m_BreakOffsets.begin(), bcol->m_BreakOffsets.end(),
                                                    PeriodBegin);

    occurrences.clear();
    CTokenNo b0 = 0, i;
    if (anchor >= 0) {
        //-- non-negative anchor position: count from 0 @ start (left)
        for (; bi != bcol->m_BreakOffsets.end() && *bi < PeriodEnd; bi++) {
            //-- break segment from i=b0 .. i<*bi
            i = b0 + anchor;
            if (i < *bi) occurrences.push_back(i);
            b0 = *bi;
        }
        if (searchPeriodNo == GetSearchPeriodsCount() - 1 && bi != bcol->m_BreakOffsets.end() && *bi == PeriodEnd &&
            (i = (b0 + anchor)) < *bi) {
            //-- hack for final break of final search period
            occurrences.push_back(i);
        }
    } else {
        //-- negative anchor position: count from -1 @ end (right)
        anchor *= -1;
        for (; bi != bcol->m_BreakOffsets.end() && *bi < PeriodEnd; bi++) {
            //-- break segment from i=b0 .. i<*bi
            i = *bi - anchor;
            if (*bi >= anchor && i >= b0) occurrences.push_back(i);
            b0 = *bi;
        }
        if (searchPeriodNo == GetSearchPeriodsCount() - 1 && bi != bcol->m_BreakOffsets.end() && *bi == PeriodEnd &&
            (i = (b0 + anchor)) < *bi) {
            //-- hack for final break of final search period
            occurrences.push_back(i);
        }
    }

    return true;
}

string CConcordance::GetIndicesToShowStr(bool Positional) const {
    if (m_IndicesToShow.size() < 1 || (m_IndicesToShow.size() == 1 && m_IndicesToShow[0] == 0))
        return string("");
    string Result("IndicesToShow");
    for (size_t i = 0; i < m_IndicesToShow.size(); ++i) {
        Result.push_back(' ');
        if (Positional) {
            Result += Format("%zi", i);
        } else {
            CStringIndexSet *idx = m_Indices[m_IndicesToShow[i]];
            Result.append(idx->m_Name);
        }
    }
    return Result;
}


string CConcordance::GetHtmlReference(size_t posFile) const {
    string CorpusFileName = m_CorpusFiles[posFile];
    string ShortFileName = CorpusFileName.substr(0, m_LocalPathPrefix.length());
    string InterfaceFileName, HtmlRefFileName;

    if (ShortFileName == m_LocalPathPrefix) {
        InterfaceFileName = ShortFileName;
        HtmlRefFileName = "http://" + m_InternetPathPrefix + InterfaceFileName;
    } else {
        HtmlRefFileName = InterfaceFileName = CorpusFileName;
    };

    return Format("<a href=\"%s\">%s</a>", HtmlRefFileName.c_str(), InterfaceFileName.c_str());
};

time_t CConcordance::UpdateTimestamp(const char *filename) {
    //-- modification time of the file (0 if it cannot be stat'ed); stat() exists on Windows too
    struct stat statbuf;
    if (stat(filename, &statbuf) == 0 && statbuf.st_mtime > m_Timestamp)
        m_Timestamp = statbuf.st_mtime;
    return m_Timestamp;
}

string CConcordance::GetShortFilename(size_t posFile) const {
    return m_CorpusFiles[posFile].substr(m_CommonFilePrefix.length());
};

void CConcordance::LoadProject(string FileName, bool includeSourceFiles) {
    try {
        LoadSourceFilesAndOptions(FileName, includeSourceFiles);
        LoadCorpusFiles();
        LoadMaskedFiles();

        AssertHasPath();
        LoadHitBorders(m_Path, m_bMemoryMap);
        ReadIndicesFromTheDisk();

        if (GetFileBreaks().size() != m_CorpusFiles.size()) {
            throw CDDCExpc(Format("The number of files in %s is not equal to the number of files in the index", FileName.c_str()));
        }

        m_BiblIndex.LoadBibl(FileName, GetFileBreaks().size(), m_bMemoryMap);
    } catch (exception& e) {
        throw CDDCExpc(Format("cannot load index of project %s: %s", FileName.c_str(), e.what()));
    }
}


//==============================================================================
// data dumping utils

//----------------------------------------------------------------------
void CConcordance::DumpBibliography(FILE *f) const {
    size_t nfiles = m_CorpusFiles.size();
    fputs("[\n", f);
    for (size_t fn = 0; fn < nfiles; ++fn) {
        string fs = DumpFileBibliography(fn);
        if (fn != 0) fputs(",\n", f);
        fputs(fs.c_str(), f);
    }
    fputs("\n]\n", f);
}

//----------------------------------------------------------------------
string CConcordance::DumpFileBibliography(uint32_t FileNo) const {
    CBibliography B = m_BiblIndex.GetFullBibliographyOfHit(FileNo);
    string fb = (string("{")
                 + "\"n_\":" + Format("%u", FileNo)
                 + ",\"file_\":" + jsonStr(m_CorpusFiles[FileNo], m_Utf8)
                 + ",\"masked_\":" + (m_MaskedFiles.find(FileNo) == m_MaskedFiles.end() ? "0" : "1")
                 + ",\"scan_\":" + jsonStr(B.m_ScanBibl, m_Utf8)
                 + ",\"orig_\":" + jsonStr(B.m_OrigBibl, m_Utf8)
                 + ",\"date_\":" + jsonStr(B.m_DateStr, m_Utf8)
                 + ",\"page_\":" + (B.m_StartPageInfo == UnknownPageNumber ? "null" : Format("%u", B.m_StartPageInfo))
                 + "," + m_BiblIndex.GetFreeHeaderBiblAttributesJson(FileNo, m_Utf8, true)
                 + "}");
    return fb;
}

//----------------------------------------------------------------------
void CConcordance::DumpFileIndexJson(uint32_t FileNo, FILE *f) const {
    if (f == NULL) f = stdout;

    //-- dump: token range
    CTokenNo tok_min = FileNo == 0 ? 0 : GetFileBreaks()[FileNo - 1];
    CTokenNo tok_max = GetFileBreaks()[FileNo];
    fprintf(f, "{\n\t\"tokids\":{\"begin\":%d, \"end\":%d},\n", tok_min, tok_max);


    //-- dump: metadata
    fputs("\t\"meta\":", f);
    string fs = DumpFileBibliography(FileNo);
    fwrite(fs.data(), 1, fs.size(), f);
    fputs(",\n", f);

    //-- dump: free breaks
    fputs("\t\"breaks\":\[\n", f);
    for (vector<CBreakCollection>::const_iterator brki = m_Breaks.begin(); brki != m_Breaks.end(); brki++) {
        if (brki != m_Breaks.begin()) fputs(",\n", f);
        fprintf(f, "\t\t\{\"shortname\":%s,\"longname\":%s,\"offsets\":\[\n",
                jsonStr(brki->m_ShortName, m_Utf8).c_str(), jsonStr(brki->m_LongName, m_Utf8).c_str());
        ddcBreakVector::const_iterator off0 = lower_bound(brki->m_BreakOffsets.begin(), brki->m_BreakOffsets.end(),
                                                          tok_min);
        for (ddcBreakVector::const_iterator offi = off0;
             offi != brki->m_BreakOffsets.end() && *offi < tok_max; offi++) {
            if (offi != off0) fputc(',', f);
            fprintf(f, "%u", *offi);
        }
        fputs("\n\t\t]}", f);
    }
    fputs("\n\t],\n", f);

    //-- dump: page-breaks
    fputs("\t\"pages\":\{\n", f);
    ddcVecFile<CPageNumber>::const_iterator pb0 = GetTokenPageBreak(tok_min);
    for (ddcVecFile<CPageNumber>::const_iterator pbi = pb0;
         pbi != m_PageBreaks.end() && pbi->m_StartTokenNo < tok_max; pbi++) {
        if (pbi != pb0) fputc(',', f);
        fprintf(f, "\"%u\":%u", pbi->m_StartTokenNo, pbi->m_PageNumber);
    }
    fputs("\n\t},\n", f);


    //-- construct: tokens
    vector<COutputToken> tmptoks;
    tmptoks.reserve(tok_max - tok_min);

    fputs("\t\"indices\":\[\n", f);
    for (vector<CStringIndexSet *>::const_iterator ixi = m_Indices.begin(); ixi != m_Indices.end(); ixi++) {
        if (ixi != m_Indices.begin()) fputs(",\n", f);
        fprintf(f, "\t\t{\"shortname\":%s,\"longname\":%s,\"values\":[\n", jsonStr((*ixi)->m_ShortName, m_Utf8).c_str(),
                jsonStr((*ixi)->m_Name, m_Utf8).c_str());
        if ((*ixi)->GetTokensFromStorage(tok_min, tok_max, tmptoks)) {
            for (vector<COutputToken>::const_iterator tmpi = tmptoks.begin(); tmpi != tmptoks.end(); tmpi++) {
                if (tmpi != tmptoks.begin()) fputc(',', f);
                fputs(jsonStr(tmpi->m_TokenStr, m_Utf8).c_str(), f);
            }
            fputc('\n', f);
        }
        fputs("\t\t]}", f);
        tmptoks.clear();
    }
    fputs("\n\t]\n}\n", f);

    return;
}


//----------------------------------------------------------------------
void CConcordance::DumpFileIndexTabs(uint32_t FileNo, FILE *f) const {
    //-- dump: token range
    const char *cmt = "%%$DDC";
    CTokenNo tok_min = FileNo == 0 ? 0 : GetFileBreaks()[FileNo - 1];
    CTokenNo tok_max = GetFileBreaks()[FileNo];

    fprintf(f, "%s:tokid.begin=%u\n", cmt, (uint) tok_min);
    fprintf(f, "%s:tokid.end=%u\n", cmt, (uint) tok_max);
    fprintf(f, "%s:meta.n_=%u\n", cmt, (uint) FileNo);

    //-- dump: metadata: built-in
    CBibliography B = m_BiblIndex.GetFullBibliographyOfHit(FileNo);
    fprintf(f, "%s:meta.file_=%s\n", cmt, jsonStr(m_CorpusFiles[FileNo], m_Utf8, false).c_str());
    fprintf(f, "%s:meta.scan_=%s\n", cmt, jsonStr(B.m_ScanBibl, m_Utf8, false).c_str());
    fprintf(f, "%s:meta.orig_=%s\n", cmt, jsonStr(B.m_OrigBibl, m_Utf8, false).c_str());
    fprintf(f, "%s:meta.date_=%s\n", cmt, jsonStr(B.m_DateStr, m_Utf8, false).c_str());
    fprintf(f, "%s:meta.page_=%ld\n", cmt,
            (B.m_StartPageInfo == UnknownPageNumber ? -1L : (long int) B.m_StartPageInfo));
    fputs(m_BiblIndex.GetFreeHeaderBiblAttributesTabsDump(FileNo, m_Utf8, true).c_str(), f);

    //-- intialize: page-breaks
    ddcVecFile<CPageNumber>::const_iterator pb = GetTokenPageBreak(tok_min);

    //-- initialize: free-breaks
    vector<size_t> breaknos(m_Breaks.size(), 0);
    size_t defaultBreakId = 0;
    for (size_t brkid = 0; brkid < m_Breaks.size(); ++brkid) {
        const CBreakCollection &breaks = m_Breaks[brkid];
        breaknos[brkid] = lower_bound(breaks.m_BreakOffsets.begin(), breaks.m_BreakOffsets.end(), tok_min) -
            breaks.m_BreakOffsets.begin();
        if (breaks.m_ShortName == m_DefaultBreakName || breaks.m_LongName == m_DefaultBreakName)
            defaultBreakId = brkid;
    }

    //-- construct tokens & dump index attributes
    vector<vector<COutputToken> > tokattrs;
    tokattrs.resize(m_Indices.size());
    size_t ixno, tixno;
    for (ixno = 0, tixno = 0; ixno < m_Indices.size(); ++ixno) {
        const CStringIndexSet *ix = m_Indices[ixno];
        if (!ix->m_bUseItemStorage) continue;
        fprintf(f, "%s:index[%zi]=%s %s\n", cmt, tixno, jsonStr(ix->m_Name, m_Utf8, false).c_str(),
                jsonStr(ix->m_ShortName, m_Utf8, false).c_str());
        tokattrs[tixno].reserve(tok_max - tok_min);
        ix->GetTokensFromStorage(tok_min, tok_max, tokattrs[tixno]);
        ++tixno;
    }
    tokattrs.resize(tixno);

    //-- iterate over tokens
    for (CTokenNo tokid = tok_min; tokid != tok_max; ++tokid) {
        //-- check for page-breaks
        for (; pb != m_PageBreaks.end() && pb->m_StartTokenNo <= tokid; ++pb) {
            fprintf(f, "%s:PAGE=%u\n", cmt, (uint) pb->m_PageNumber);
        }

        //-- check for free-breaks
        for (size_t brkid = 0; brkid < m_Breaks.size(); ++brkid) {
            const CBreakCollection &breaks = m_Breaks[brkid];
            if (tokid == 0) // articificial break
            {
                fprintf(f, "%s:BREAK.%s[-1]=0\n", cmt, breaks.m_ShortName.c_str());
            }
            else {
                size_t& breakNo = breaknos[brkid];
                while (     (breakNo < breaks.m_BreakOffsets.size())
                            &&   (breaks.m_BreakOffsets[breakNo] <= tokid) // in correct indices there must be '==' instead of '<='
                    ) {
                    if (brkid == defaultBreakId && tokid > tok_min) {
                        fputc('\n', f);
                    }
                    fprintf(f, "%s:BREAK.%s[%zu]=%u\n", cmt, breaks.m_ShortName.c_str(), breakNo,
                            (uint) (breaks.m_BreakOffsets[breakNo]));
                    ++breakNo;
                }
            }
        }

        //-- dump current token
        for (size_t tixno = 0; tixno < tokattrs.size(); ++tixno) {
            if (tixno != 0) fputc('\t', f);
            fputs(tokattrs[tixno][tokid - tok_min].m_TokenStr.c_str(), f);
        }
        fputc('\n', f);
    }
    fputc('\n', f);

}

//----------------------------------------------------------------------
void CConcordance::DumpIndex(string dirname, CIndexDumpFormat fmt) const {
    const char *file_ext = "";
    if (fmt == idfJson) {
        file_ext = "json";
    } else if (fmt == idfTabs) {
        file_ext = "tabs";
    } else {
        throw CDDCExpc(errRuntime, "CConcordance::DumpIndex(): index dump-format %u", (uint) fmt);
    }
    size_t nfiles = m_CorpusFiles.size();
    for (size_t fn = 0; fn < nfiles; ++fn) {
        if (m_MaskedFiles.find(fn) != m_MaskedFiles.end()) continue;  //-- skip masked files
        string dumpfile = Format("%s/%d.%s", dirname.c_str(), fn, file_ext);
        FILE *dumpfh = fopen(dumpfile.c_str(), "wb");
        if (!dumpfh)
            throw CDDCExpc(errRuntime, "Error: open failed for dump file '%s': %s", dumpfile.c_str(), StrError(errno));
        fprintf(stderr, "dumping %s ~ %s\n", dumpfile.c_str(), m_CorpusFiles[fn].c_str());
        switch (fmt) {
            case idfJson:
                DumpFileIndexJson(fn, dumpfh);
                break;
            case idfTabs:
                DumpFileIndexTabs(fn, dumpfh);
                break;
            default:
                break;
        }
        fclose(dumpfh);
    }
}


void CConcordance::DumpIndexToSingleTabFile(FILE *outfp) const {
    size_t nfiles = m_CorpusFiles.size();
    for (size_t fn = 0; fn < nfiles; ++fn) {
        if (m_MaskedFiles.find(fn) != m_MaskedFiles.end()) continue;  //-- skip masked files
        DumpFileIndexTabs(fn, outfp);
    }
}

//----------------------------------------------------------------------
void CConcordance::RegisterIndicesToShow(const string &IndexListStr) {
    StringTokenizer tok(IndexListStr.c_str(), " \t\r\n,;");
    m_IndicesToShow.clear();

    while (tok()) {
        string s = tok.val();
        size_t ipos = (size_t) -1;
        if (s.empty()) continue;

        CStringIndexSet *idx = GetIndexByAlias(s);
        if (idx != NULL) {
            //-- known alias: convert to position
            for (size_t i = 0; i < m_Indices.size(); ++i) {
                if (m_Indices[i] == idx) {
                    ipos = i;
                    break;
                }
            }
            assert(ipos >= 0);
            assert(ipos < m_Indices.size());
        } else if (s.find_first_not_of("+-0123456789") == string::npos) {
            //-- decimal integer: convert to size_t
            ipos = strtoul(s.c_str(), NULL, 0);
            if (ipos < 1)
                throw CDDCExpc("minimum positional index value for IndicesToShow is 1 (one)");
            else if (ipos > m_Indices.size())
                throw CDDCExpc(Format("positional index `%zi' in IndicesToShow out of bounds (max=%zi)", ipos,
                                   m_Indices.size()));
            --ipos; //-- convert to zero-based indces
        } else {
            //-- unknown: oops
            throw CDDCExpc(Format("unknown index label `%s' in IndicesToShow", s.c_str()));
        }

        m_IndicesToShow.push_back(ipos);
    }

    //-- sanity check: always show at least 1 index (default=initial index)
    if (m_IndicesToShow.empty())
        m_IndicesToShow.push_back(0);

    //-- global sanity checks
    for (size_t i = 0; i < m_IndicesToShow.size(); ++i) {
        if (!m_Indices[m_IndicesToShow[i]]->m_bUseItemStorage)
            throw CDDCExpc("index #%zi (%s) in IndicesToShow has no storage class", i,
                        m_Indices[m_IndicesToShow[i]]->m_Name.c_str());
    }
}

//----------------------------------------------------------------------

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
