//*-*- Mode: C++ -*-*/
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2020 by Bryan Jurish
//
//  This file is part of DDC (formerly CConcHolder.cpp)
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
#include "ConcCommon.h"
#include "ConcSession.h"
#include "ConcSessionContext.h"
#include "QueryCompiler.h"
#include "ConcXml.h"
#include "math.h"
#include "../CommonLib/ddcString.h"


using namespace std;

//==============================================================================
const time_t TheEndOfTheWorld = 0xffffffff;

#ifdef DETECT_MEMORY_LEAK
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

//==============================================================================
//#define DEBUG_HIT_TRIM 1
#undef DEBUG_HIT_TRIM

#if DEBUG_HIT_TRIM
# define HIT_TRIM_DEBUG(x) x
#else
# define HIT_TRIM_DEBUG(x)
#endif

//==============================================================================
//#define DEBUG_HIT_SORT 1
#undef DEBUG_HIT_SORT

#if DEBUG_HIT_SORT
# define HIT_SORT_DEBUG(x) x
#else
# define HIT_SORT_DEBUG(x)
#endif

static void dumpHits(const std::string &Label, const vector<CHit> &Hits) {
    for (size_t hi = 0; hi < Hits.size(); hi++) {
        const CHit &h = Hits[hi];
        fprintf(stderr,
                "%s[%zd] = {m_BreakNo=%u, m_HighlightOccurrenceEnd=%u, m_SortKey={%d,%s}, m_FileNo=%u, m_DebugRankNo=%zu}\n",
                Label.c_str(), hi,
                h.m_BreakNo, h.m_HighlightOccurrenceEnd, h.m_SortKey.i, jsonStr(h.m_SortKey.s).c_str(), h.m_FileNo,
                h.m_Value.m_DebugRankNo
            );
    }
}

static void dumpHitIndex(const std::string &IndexLabel, const vector<size_t> &HitIndex, const std::string &Label,
                         const vector<CHit> &Hits) {
    for (size_t hii = 0; hii < HitIndex.size(); hii++) {
        size_t hi = HitIndex[hii];
        const CHit &h = Hits[hi];
        fprintf(stderr,
                "%s[%zd] = %s[%zd] = {m_BreakNo=%u, m_HighlightOccurrenceEnd=%u, m_SortKey={%d,%s}, m_FileNo=%u, m_DebugRankNo=%zu}\n",
                IndexLabel.c_str(), hii,
                Label.c_str(), hi,
                h.m_BreakNo, h.m_HighlightOccurrenceEnd, h.m_SortKey.i, jsonStr(h.m_SortKey.s).c_str(), h.m_FileNo,
                h.m_Value.m_DebugRankNo
            );
    }
}

//==============================================================================
//! indirect comparison operator for hits on CHit::m_SortKey.i (for std::sort); replaces IsLessByHitOrderId .
//! \li true string-based sorting occurs only at distributed server level
struct IsLessByHitSortKey {
    const vector<CHit> &m_Base;

    IsLessByHitSortKey(const vector<CHit> &Base)
        : m_Base(Base) {};

    bool operator()(size_t i1, size_t i2) const {
        return m_Base[i1].m_SortKey.i < m_Base[i2].m_SortKey.i;
    };
};

//==============================================================================
//! indirect comparison operator for hits on CHit::m_SortKey.s (for std::sort); replaces IsLessByHitOrderId .
//! \li true string-based sorting occurs only at distributed server level
struct IsLessByHitSortKeyStr {
    const vector<CHit> &m_Base;

    IsLessByHitSortKeyStr(const vector<CHit> &Base)
        : m_Base(Base) {};

    bool operator()(size_t i1, size_t i2) const {
        return m_Base[i1].m_SortKey.s < m_Base[i2].m_SortKey.s;
    };
};

//==============================================================================
// cannot create cross-platform heterogenious predicate lower_bound:
// http://groups.google.com/group/comp.std.c++/browse_thread/thread/151b0210b6266c2f?hl=en&lr=&safe=off&ic=1&seekm=MPG.143ab91a14f21268989743%40news.supernews.com
// that's why we are to create i
template<class IndexIterator>
IndexIterator
my_lower_bound(IndexIterator First, IndexIterator Last, const CHitSortKey &Key, const vector<CHit> &Base) {
    size_t Count = Last - First;

    while (Count > 0) {
        // divide and conquer, find half that contains answer
        IndexIterator Mid = First;
        size_t Step = Count / 2;
        std::advance(Mid, Step);
        if (Base[*Mid].m_SortKey.i < Key.i) //-- use integer comparisons only here!
        {
            First = ++Mid;
            Count -= Step + 1;
        } else
            Count = Step;
    }
    return First;
}

//==============================================================================
template<class IndexIterator>
IndexIterator
my_upper_bound(IndexIterator First, IndexIterator Last, const CHitSortKey &Key, const vector<CHit> &Base) {
    size_t Count = Last - First;

    while (Count > 0) {
        // divide and conquer, find half that contains answer
        IndexIterator Mid = First;
        size_t Step = Count / 2;
        std::advance(Mid, Step);
        if (Base[*Mid].m_SortKey.i <= Key.i) //-- use integer comparisons only here!
        {
            First = ++Mid;
            Count -= Step + 1;
        } else
            Count = Step;
    }
    return First;
}


void DeleteEOLN(string &txt) {
    for (int i = 0; i < txt.length(); i++) {
        if (txt[i] == '\n')
            txt[i] = ' ';

        if (txt[i] == '\r')
            txt[i] = ' ';

        if (txt.substr(i, 4) == "</p>")
            txt.erase(i, 4);
    };
};


void SpaceStartQuoteMarks(string &s) {
    bool bInQuoteMark = false;
    bool bInSingleQuoteMark = false;

    const int len = s.length();

    for (int i = len - 1; i > 0; i--) {
        if (s[i] == '"') {
            if (s[i + 1] == ' ')
                if (bInQuoteMark
                    || ((i > 0) && (s[i - 1] == ':'))
                    )
                    swap(s[i], s[i + 1]);

            bInQuoteMark = !bInQuoteMark;
        }

        if (s[i] == '\'') {
            if (bInSingleQuoteMark && (s[i + 1] == ' '))
                swap(s[i], s[i + 1]);

            bInSingleQuoteMark = !bInSingleQuoteMark;
        };
    };

    for (int i = 0; i < len - 1; i++) {
        if ((s[i] == '(') || (s[i] == '<') || (s[i] == '[')) {
            if (s[i + 1] == ' ')
                swap(s[i], s[i + 1]);
            i++;
        };
    };
    if ((len > 1)
        && (s[1] == ' ')
        && ((s[0] == '\'')
            || (s[0] == '"')
            )
        )
        swap(s[0], s[1]);


};

//==============================================================================
// CShortOccurCache

//----------------------------------------------------------------------
void CShortOccurCache::Clear() {
    ClearContainer(m_IndexItemNo2Occurrences);
    ClearContainer(m_OccurrencesBody);
}

//----------------------------------------------------------------------
size_t CShortOccurCache::AddNewIndexItemNoToCache(const CTokenNo *pStart, const CTokenNo *pEnd) {
    m_IndexItemNo2Occurrences.push_back(CDataReference(m_OccurrencesBody.size(), pEnd - pStart));;
    m_OccurrencesBody.insert(m_OccurrencesBody.end(), pStart, pEnd);
    return m_IndexItemNo2Occurrences.size() - 1;
}

//----------------------------------------------------------------------
const CTokenNo *CShortOccurCache::GetOccurrencesFromCache(const int CacheId, uint32_t &Length) const {
    const CDataReference &R = m_IndexItemNo2Occurrences[CacheId];
    Length = R.m_VectorLength;
    return &m_OccurrencesBody[R.m_VectorStartOffset];
}

bool CShortOccurCache::CouldContainMore() const {
    return m_OccurrencesBody.size() < MaxShortOccurCacheSize;
}

//==============================================================================
// CConcSession: constructors etc

//----------------------------------------------------------------------
CConcSession::CConcSession(CConcSessionContext *SessionContext) {
    if (SessionContext != NULL) {
        m_pSessionContext = SessionContext;
        m_bSessionMaster = false;
    } else {
        m_pSessionContext = new CConcSessionContext();
        m_bSessionMaster = true;
    }
    m_WorkerId = 0;
    m_ResultOffset = 0;
    m_ResultLimit = SIZE_MAX;
    m_ResultMinKey = "";
    m_RequestPath = "";
    m_pConcordance = 0;
    m_pBreaks = 0;
    m_ResultFormat = DDC_ResultText;
    m_QueryEndTime = TheEndOfTheWorld;
    m_pQueryCompiler = new CQueryCompiler(this);
    m_pRandom = new DDCRandom();
    m_RandomSeed = 0;
    m_bSortByString = false;
    m_bPrune = false;
    m_SortOrder = hsoNone;
}

//----------------------------------------------------------------------
CConcSession::~CConcSession() {
    if (m_bSessionMaster)
        delete m_pSessionContext;
    delete m_pRandom;
    delete m_pQueryCompiler;
}

//==============================================================================
// CConcSession: worker-thread and shared-context utilities


//----------------------------------------------------------------------
CConcSession *CConcSession::WorkerClone(size_t WorkerId) {
    LockSessionContext();
    CConcSession *clone = new CConcSession(m_pSessionContext);

    clone->m_WorkerId = WorkerId;
    //clone->m_pQueryCompiler = m_pQueryCompiler;

    clone->m_pRandom->set_seed(m_pRandom->m_seed);
    //clone->m_QueryEndTime = m_QueryEndTime;
    clone->m_pBreaks = m_pBreaks;
    //clone->m_ResultFormat = m_ResultFormat;
    clone->m_RandomSeed = m_RandomSeed;
    //clone->m_ShortOccurCaches = m_ShortOccurCaches;
    //clone->m_QueryResultStr = m_QueryResultStr;
    //clone->m_ErrorStr = m_ErrorStr;
    clone->m_pConcordance = m_pConcordance;                //!!!!!!!! hic sunt dracones !!!!!!!
    //clone->m_ResultOffset = m_ResultOffset;
    //clone->m_ResultLimit = m_ResultLimit;
    //clone->m_ResultMinKey = m_ResultMinKey;
    //clone->m_CurrentSearchPeriodNo = m_CurrentSearchPeriodNo;
    clone->m_AdditionalHitDelimiter = m_AdditionalHitDelimiter;
    UnlockSessionContext();

#if 0 //-- DEBUG
    concord_daemon_log(Format("CConcSession::WorkerClone(): this = %0.16p:{Ctx=%0.16p, Random=%0.16p, Index=%0.16p}",
                              this, this->m_pSessionContext, this->m_pRandom, this->m_pConcordance));
    concord_daemon_log(Format("CConcSession::WorkerClone(): clone= %0.16p:{Ctx=%0.16p, Random=%0.16p, Index=%0.16p}",
                              clone, clone->m_pSessionContext, clone->m_pRandom, clone->m_pConcordance));
#endif

    return clone;
}

//----------------------------------------------------------------------
void CConcSession::WorkerCloneFree() {
    //-- nothing here
    m_bSessionMaster = false;
}

//----------------------------------------------------------------------
int CConcSession::LockSessionContext() {
    return m_pSessionContext ? m_pSessionContext->lock() : 0;
}

//----------------------------------------------------------------------
int CConcSession::UnlockSessionContext() {
    return m_pSessionContext ? m_pSessionContext->unlock() : 0;
}

//----------------------------------------------------------------------
void CConcSession::ClearQueryCache() {
    if (m_pSessionContext)
        m_pSessionContext->CacheClear();
}

//----------------------------------------------------------------------
size_t CConcSession::CacheSize(void) const {
    return m_pSessionContext ? m_pSessionContext->CacheSize() : 0;
}


//==============================================================================
// CConcSession: API

//----------------------------------------------------------------------
void CConcSession::AddFileReference(const long posFile) {

    if (m_ResultFormat == DDC_ResultHTML) {
        m_QueryResultStr += "<P>";
        m_QueryResultStr += m_pConcordance->GetHtmlReference(posFile);
        m_QueryResultStr += "</P>";
    } else if (m_ResultFormat == DDC_ResultText) {
        m_QueryResultStr += m_pConcordance->GetShortFilename(posFile) + " ### ";
    } else if (m_ResultFormat == DDC_ResultTable) {

        // nothing to do!
    }

}

//----------------------------------------------------------------------
void CConcSession::ShowBibliographyForTextOrHtml(const CHit &Hit, uint32_t PageNumber) {
    // nothing to do for DDC_ResultTable!
    assert (m_ResultFormat != DDC_ResultTable);

    CBibliography B = m_pConcordance->m_BiblIndex.GetFullBibliographyOfHit(Hit.m_FileNo);

    string BiblStr;
    /*
      if <sourcedesc id="scan"> exists then
      - take <bibl>...</bibl>
      - take <date id="first"> in <sourcedesc id="orig">
      else take <bibl>...</bibl> in <sourcedesc id="orig">
    */
    if (m_pConcordance->IsGutenbergInterface()) {
        int dummy, birth, death;
        string Date = B.m_DateStr;
        if (sscanf(B.m_DateStr.c_str(), "%i.%i.%i-%i.%i.%i", &dummy, &dummy, &birth, &dummy, &dummy, &death) == 6)
            Date = Format("(%i-%i)", birth, death);
        BiblStr = B.m_OrigBibl + " " + Date;
        BiblStr += string(" [") + m_pConcordance->GetShortFilename(Hit.m_FileNo) + "]";

    } else if (!B.m_ScanBibl.empty()) {
        BiblStr = B.m_ScanBibl;
        if (!B.m_DateStr.empty()) {
            string Date = B.m_DateStr;
            int year, month, date;
            if (sscanf(B.m_DateStr.c_str(), "%i-%i-%i", &year, &month, &date) == 3)
                Date = Format("%i", year);
            BiblStr += " [" + Date + "]";
        };
    } else
        BiblStr = B.m_OrigBibl;

    if (BiblStr.empty())
        BiblStr = m_pConcordance->GetShortFilename(Hit.m_FileNo);

    if (BiblStr.empty())
        BiblStr = m_pConcordance->m_CorpusFiles[Hit.m_FileNo];

    // ======== special DWDS preprocessing of page numbers
    if (m_pConcordance->IsDwdsCorpusInterface()) {
        int i = BiblStr.rfind("S.");
        if (i != string::npos) {

            //if <bibl>...</bibl> ends with "S. {CARD}" then omit page generation

            for (i += 2; i < BiblStr.length(); i++)
                if ((BiblStr[i] != ' ')
                    && !isdigit((BYTE) BiblStr[i])
                    )
                    break;

            if (i == BiblStr.length())
                PageNumber = UnknownPageNumber;

        };
    };
    // ======== end of special DWDS preprocessing


    if (m_ResultFormat == DDC_ResultHTML) {
        m_QueryResultStr += "<br> <b>";
        m_QueryResultStr += BiblStr;
        if (PageNumber != UnknownPageNumber)
            m_QueryResultStr += Format(" Page %u", PageNumber);
        m_QueryResultStr += " ";
        m_QueryResultStr += m_pConcordance->m_BiblIndex.GetVisibleFreeHeaderBiblAttributes(Hit.m_FileNo, " ");
        m_QueryResultStr += "</b>";
        m_QueryResultStr += "<br>";

    } else if (m_ResultFormat == DDC_ResultText) {
        m_QueryResultStr += BiblStr;
        m_QueryResultStr += " ### ";
        if (PageNumber != UnknownPageNumber)
            m_QueryResultStr += Format("%u", PageNumber);
        else
            m_QueryResultStr += Format("-1");
        m_QueryResultStr += " ### ";
        m_QueryResultStr += B.m_DateStr;
        m_QueryResultStr += m_pConcordance->m_BiblIndex.GetVisibleFreeHeaderBiblAttributes(Hit.m_FileNo, " ### ");
        m_QueryResultStr += " ### ";

        //-- rank stuff / text
        if (m_pQueryCompiler->m_pQuery->m_Options->m_bDebugRank) {
            const char *DebugInfo = (const char *) (void *) (&m_DebugInfo[0]) + Hit.m_Value.m_DebugRankNo;
            m_QueryResultStr += Format(" %s ### ", DebugInfo);
        }

#if 0 /*-- incompatible with v1.x --*/
        //-- index list / text
        for (vector<size_t>::const_iterator fi = m_pConcordance->m_IndicesToShow.begin(); fi != m_pConcordance->m_IndicesToShow.end(); fi++) {
            const CStringIndexSet& I = *m_pConcordance->m_Indices[*fi];
            m_QueryResultStr.push_back(' ');
            m_QueryResultStr += I.m_ShortName;
        }
        m_QueryResultStr += " ### ";
#endif
    }

};


string BuildHtmlHitStrWithHighlighting(const vector<COutputToken> &Tokens, bool bConvertASCIIToHtmlSymbols,
                                       const CHighlightTags &HighlightTags, bool bUseAnchorSpan,
                                       const string &tokenDelimiter = "") {

    // ===============  creating string ======================
    string HitStr;
    const char StartHighl = 1;
    const char EndHighl = 2;

    for (int i = 0; i < Tokens.size(); i++) {
        HitStr += tokenDelimiter;

        if ((i > 0)
            && (!ispunct((BYTE) Tokens[i].m_TokenStr[0])
                || (Tokens[i].m_TokenStr == "-")
                )

            )
            HitStr += " ";

        if (bUseAnchorSpan && !Tokens[i].m_InterpStr.empty())
            HitStr += "<span title=\"" + Tokens[i].m_InterpStr + "\">";

        if (Tokens[i].m_Highlight)
            HitStr += StartHighl;

        // ===============  convert to html if it needs ======================
        if (bConvertASCIIToHtmlSymbols)
            HitStr += ConvertASCIIToHtmlSymbols(Tokens[i].m_TokenStr);
        else
            HitStr += Tokens[i].m_TokenStr;

        if (!bUseAnchorSpan && !Tokens[i].m_InterpStr.empty())
            HitStr += Tokens[i].m_InterpStr;

        if (Tokens[i].m_Highlight)
            HitStr += EndHighl;

        if (bUseAnchorSpan && !Tokens[i].m_InterpStr.empty())
            HitStr += "</span>";

    }

    // ===============  spacing quotes ======================
    SpaceStartQuoteMarks(HitStr);

    // ===============  convert to html if it needs ======================
    //if (bConvertASCIIToHtmlSymbols && !bUseAnchorSpan)
    //HitStr = ConvertASCIIToHtmlSymbols(HitStr);

    Trim(HitStr);

    // ===============  replace StartHighl and  EndHighl with the given arguments======================
    int CountOfHiglightedWords = 0;
    string Result;
    for (size_t i = 0; i < HitStr.length(); i++)
        if (HitStr[i] == StartHighl)
            Result += (CountOfHiglightedWords == 0) ? HighlightTags.m_FirstOpener : HighlightTags.m_RestOpener;
        else if (HitStr[i] == EndHighl) {
            Result += (CountOfHiglightedWords == 0) ? HighlightTags.m_FirstCloser : HighlightTags.m_RestCloser;
            CountOfHiglightedWords++;
        } else
            Result += HitStr[i];


    return Result;
}


//----------------------------------------------------------------------
// moo: BuildJsonContextString(): adapted from BuildHtmlHitStrWithHighlighting()
//   + returns a JSON array of token structures
//#define  JSON_USE_DDC_SPACING
#undef   JSON_USE_DDC_SPACING
#undef   JSON_USE_HASH
#undef   JSON_SHORT_FILENAMES
//#define DDC_JSON_DEEP_CONTEXT  //-- defined by configure option --(enable|disable)-json-complex-context

//#define DEBUG_HIT_JSON 1
#undef DEBUG_HIT_JSON

string CConcSession::BuildJsonContextString(const vector<COutputToken> &Tokens, bool doHighlight) const {
    //==================================================
    // create hit string
    bool utf8 = m_pConcordance->m_Utf8;
    char hlbuf[32];
    string js("");

    for (int i = 0; i < Tokens.size(); i++) {
        if (doHighlight) {
            //-- highlighting (full info) mode: only for hit "body"
            vector<string> fields = m_pConcordance->GetTokenFields(Tokens[i]);

            if (i > 0) {
                js.push_back(',');
#ifdef JSON_USE_DDC_SPACING
                //-- old-style punctuation-sensitive spacing
                if (!ispunct((BYTE)Tokens[i].m_TokenStr[0]) || (Tokens[i].m_TokenStr == "-"))
                    fields[0].insert(0, 1, ' ');
#endif // defined(JSON_USE_DDC_SPACING)
            }

#ifdef JSON_USE_HASH
            //-- return each token as a json hash
            js.push_back('{');
            for (size_t fi=0; fi < fields.size(); fi++) {
                const CStringIndexSet& I = *m_pConcordance->m_Indices[m_pConcordance->m_IndicesToShow[fi]];
                if (fi>0) js.push_back(',');
                js.append(jsonStr(I.m_ShortName, utf8));
                js.push_back(':');
                js.append(jsonStr(fields[fi], utf8));
            }
            js += ",\"hl_\":";
            if (Tokens[i].m_Highlight) {
                sprintf(hlbuf, "%u", Tokens[i].m_Highlight);
                js.append(hlbuf);
            } else {
                js.push_back('0');
            }
            js.push_back('}');

#else // !defined(JSON_USE_HASH)

            //-- return each token as a json array (with 0th elt ~ highlighting flag)
            js.push_back('[');
            if (Tokens[i].m_Highlight) {
                sprintf(hlbuf, "%u", Tokens[i].m_Highlight);
                js.append(hlbuf);
            } else {
                js.push_back('0');
            }
            js.push_back(',');
            for (vector<string>::const_iterator fi = fields.begin(); fi != fields.end(); fi++) {
                if (fi != fields.begin()) js.push_back(',');
                js += jsonStr(*fi, utf8);
            }
            js.push_back(']');
#endif // defined(JSON_HASH)
        } else {
            //-- non-highlighting mode
            string wtxt = Tokens[i].m_TokenStr;
            if (i > 0) {
                js.push_back(',');
#ifdef JSON_USE_DDC_SPACING
                //-- old-style punctuation-sensitive spacing
                if (!ispunct((BYTE)Tokens[i].m_TokenStr[0]) || (Tokens[i].m_TokenStr == "-"))
                    wtxt.insert(0, 1, ' ');
#endif // defined(JSON_USE_DDC_SPACING)
            }
            js += jsonStr(wtxt, utf8);
        }
    }

    return js;
}


//----------------------------------------------------------------------
bool CConcSession::GetContext(int StartBreakNo, int EndBreakNo, const uint32_t CurrFileNo,
                              const bool bConvertASCIIToHtmlSymbols, string &Result) const {
    Result = "";
    if (m_pQueryCompiler->m_pQuery->m_Options->m_HitTypeStr == PredefinedFileBreakName) return true;

    if (StartBreakNo == EndBreakNo) {
        Result = "";
        return true;
    };

    Result = "    ";
    const uint32_t FileStartTokenNo = m_pConcordance->GetFileStartTokenNo(CurrFileNo);
    const uint32_t FileEndTokenNo = m_pConcordance->GetFileBreaks()[CurrFileNo];
    const ddcBreakVector &Breaks = GetBreaks();
    for (int BreakNo = StartBreakNo; BreakNo < EndBreakNo; BreakNo++) {
        if (BreakNo < 0) continue;
        if (BreakNo >= Breaks.size()) continue;
        const CTokenNo &B = Breaks[BreakNo];
        if ((B > FileStartTokenNo)
            && (B <= FileEndTokenNo)
            ) {

            assert (!m_pConcordance->m_IndicesToShow.empty());
            vector<COutputToken> Tokens;
            if (!GetTokensFromStorageByBreak(m_pConcordance->m_IndicesToShow[0], BreakNo, Tokens)) {
                ErrorMessage(Format("Cannot get sentence: BreakNo=%i,BreakEndTokenNo=%i,  FileNo=%i\n", BreakNo, B,
                                    CurrFileNo));
                return false;
            };


            string Hit = BuildHtmlHitStrWithHighlighting(Tokens, bConvertASCIIToHtmlSymbols, CHighlightTags(), false,
                                                         m_pConcordance->m_TokenDelimiter);
            if (m_ResultFormat == DDC_ResultTable)
                Hit = "<s>" + Hit + "</s>";
            Result += Hit + "    ";
        };
    };
    return true;
}

//----------------------------------------------------------------------
bool CConcSession::GetContextJson(int StartBreakNo, int EndBreakNo, const uint32_t CurrFileNo, string &js) const {
    js.clear();
    if (m_pQueryCompiler->m_pQuery->m_Options->m_HitTypeStr == PredefinedFileBreakName)
        return true;

    if (StartBreakNo == EndBreakNo)
        return true;

    const uint32_t FileStartTokenNo = m_pConcordance->GetFileStartTokenNo(CurrFileNo);
    const uint32_t FileEndTokenNo = m_pConcordance->GetFileBreaks()[CurrFileNo];
    const ddcBreakVector &Breaks = GetBreaks();
    for (int BreakNo = StartBreakNo; BreakNo < EndBreakNo; BreakNo++) {
        if (BreakNo < 0) continue;
        if (BreakNo >= Breaks.size()) continue;

        const CTokenNo &B = Breaks[BreakNo];
        if ((B > FileStartTokenNo) && (B <= FileEndTokenNo)) {
            assert (!m_pConcordance->m_IndicesToShow.empty());
            vector<COutputToken> Tokens;

#ifdef DDC_JSON_DEEP_CONTEXT
            //-- complex output tokens; copy+paste+edit from CConcSession::GenerateHitStrings()
            assert (!m_pConcordance->m_IndicesToShow.empty());
            for (size_t ixno=0; ixno < m_pConcordance->m_IndicesToShow.size(); ++ixno) {
                vector<COutputToken> ixTokens;
                if (!GetTokensFromStorageByBreak(m_pConcordance->m_IndicesToShow[ixno], BreakNo, ixTokens)) {
                    throw CDDCExpc(errOther, Format("CConcSession::GetContextJson(): could not get index items for IndexNo=%i, BreakNo=%i\n",
                                                 m_pConcordance->m_IndicesToShow[ixno], BreakNo));
                    return false;
                }
                if (ixno==0) {
                    Tokens.swap(ixTokens);
                } else {
                    assert(Tokens.size()==ixTokens.size());
                    for (size_t toki=0; toki < Tokens.size(); ++toki) {
                        if (!ixTokens[toki].m_TokenStr.empty())
                            Tokens[toki].m_InterpStr += m_pConcordance->m_InterpDelimiter + ixTokens[toki].m_TokenStr;
                    }
                }
            }
            if (!js.empty()) js.push_back(',');
            js += BuildJsonContextString(Tokens, true);
#else //!defined(DDC_JSON_DEEP_CONTEXT)
            if (!GetTokensFromStorageByBreak(m_pConcordance->m_IndicesToShow[0], BreakNo, Tokens)) {
                ErrorMessage(Format("Cannot get sentence: BreakNo=%i,BreakEndTokenNo=%i,  FileNo=%i\n", BreakNo, B,
                                    CurrFileNo));
                return false;
            }
            if (!js.empty()) js.push_back(',');
            js += BuildJsonContextString(Tokens, false);
#endif //defined(DDC_JSON_DEEP_CONTEXT)
        };
    };
    return true;
}


//----------------------------------------------------------------------
bool CConcSession::ShowBibliographyForTable(uint32_t PageNumber, const CHit &Hit, const vector<COutputToken> &Tokens) {
    string KeyWords;
    for (int i = 0; i < Tokens.size(); i++)
        if (Tokens[i].m_Highlight
            && ((i == 0)
                || (find(Tokens.begin(), Tokens.begin() + i - 1, Tokens[i]) == Tokens.begin() + i - 1)
                )
            ) // print only unique keywords
            KeyWords += string("<orth>") + ConvertASCIIToHtmlSymbols(Tokens[i].m_TokenStr) + " </orth>";

    CBibliography B = m_pConcordance->m_BiblIndex.GetFullBibliographyOfHit(Hit.m_FileNo);
    string PageNumberStr = (PageNumber == UnknownPageNumber) ? "unknown" : Format("%u", PageNumber);


    m_QueryResultStr += (string("file") + globalTableItemsDelim + m_pConcordance->m_CorpusFiles[Hit.m_FileNo] +
                         globalTableItemsDelim
                         + string("scan") + globalTableItemsDelim + ConvertASCIIToHtmlSymbols(B.m_ScanBibl) +
                         globalTableItemsDelim
                         + string("orig") + globalTableItemsDelim + ConvertASCIIToHtmlSymbols(B.m_OrigBibl) +
                         globalTableItemsDelim
                         + string("page") + globalTableItemsDelim + PageNumberStr + globalTableItemsDelim
                         + string("date") + globalTableItemsDelim + ConvertASCIIToHtmlSymbols(B.m_DateStr) +
                         globalTableItemsDelim
                         + string("keyword") + globalTableItemsDelim + KeyWords);

    m_QueryResultStr +=
        m_pConcordance->m_BiblIndex.GetFreeHeaderBiblAttributesWithNames(Hit.m_FileNo, globalTableItemsDelim) +
        globalTableItemsDelim;

    //-- rank stuff / table
    if (HasRankOrderOperator()) {
        m_QueryResultStr +=
            string("rank") + globalTableItemsDelim + Format("%d", Hit.m_SortKey.i) + globalTableItemsDelim;
        if (m_pQueryCompiler->m_pQuery->m_Options->m_bDebugRank) {
            const char *DebugInfo = (const char *) (void *) (&m_DebugInfo[0]) + Hit.m_Value.m_DebugRankNo;
            m_QueryResultStr += string("rank_debug") + globalTableItemsDelim + DebugInfo + globalTableItemsDelim;
        }
    }

    //-- index list / table
    m_QueryResultStr += string("indices") + globalTableItemsDelim;
    for (vector<size_t>::const_iterator fi = m_pConcordance->m_IndicesToShow.begin();
         fi != m_pConcordance->m_IndicesToShow.end(); fi++) {
        const CStringIndexSet &I = *m_pConcordance->m_Indices[*fi];
        m_QueryResultStr.push_back(' ');
        m_QueryResultStr += I.m_ShortName;
    }
    m_QueryResultStr += globalTableItemsDelim;

    return true;
}


//----------------------------------------------------------------------
bool CConcSession::GenerateOneHitString(uint32_t PageNumber, const CHit &Hit, const vector<COutputToken> &Tokens) {
    if (m_ResultFormat == DDC_ResultJson)
        return GenerateOneHitStringJson(PageNumber, Hit, Tokens);

    bool bConvASCIIToHtml = m_ResultFormat != DDC_ResultText;

    // ===========   generate hit header   ===================
    if (m_ResultFormat == DDC_ResultDocIds) {
        m_QueryResultStr += Format("%u", Hit.m_FileNo);
    } else if (m_ResultFormat == DDC_ResultTable)
        ShowBibliographyForTable(PageNumber, Hit, Tokens);
    else if (m_pQueryCompiler->m_pQuery->m_Options->m_bEnableBibliography && m_pConcordance->OutputBibliographyOfHits())
        ShowBibliographyForTextOrHtml(Hit, PageNumber);
    else
        AddFileReference(Hit.m_FileNo);

    //-- rank stuff / html
    if (m_ResultFormat == DDC_ResultHTML && HasRankOrderOperator()) {
        if (!m_pQueryCompiler->m_pQuery->m_Options->m_bDebugRank) {
            m_QueryResultStr += Format("<i>Rank = %i</i><br>",
                                       Hit.m_SortKey.i > 0 ? Hit.m_SortKey.i : -Hit.m_SortKey.i);
        } else {
            const char *DebugInfo = (const char *) (void *) (&m_DebugInfo[0]) + Hit.m_Value.m_DebugRankNo;
            m_QueryResultStr += Format("<i>%s</i><br>", DebugInfo);
        }
    }

    // =============  add left hit context   ==================
    {

        string LeftContext;
        if (!GetContext((int) Hit.m_BreakNo - (int) m_pQueryCompiler->m_pQuery->m_Options->m_ContextSentencesCount,
                        Hit.m_BreakNo, Hit.m_FileNo, bConvASCIIToHtml, LeftContext)) {
            ErrorMessage("Error while getting the left-hand context");
            return false;
        };
        m_QueryResultStr += LeftContext;
    }



    // ===========   generate hit body ====================

    switch (m_ResultFormat) {
        case DDC_ResultHTML:
            m_QueryResultStr += BuildHtmlHitStrWithHighlighting(Tokens, bConvASCIIToHtml,
                                                                m_pConcordance->m_HtmlHighlighting, true,
                                                                m_pConcordance->m_TokenDelimiter);
            break;
        case DDC_ResultText:
            m_QueryResultStr += BuildHtmlHitStrWithHighlighting(Tokens, bConvASCIIToHtml,
                                                                m_pConcordance->m_TextHighlighting, false,
                                                                m_pConcordance->m_TokenDelimiter);
            break;
        case DDC_ResultTable:
            //m_QueryResultStr += "<s part=\"m\">"+ BuildHtmlHitStrWithHighlighting(Tokens,bConvASCIIToHtml, CHighlightTags(), false, m_pConcordance->m_TokenDelimiter) + "</s>";
            m_QueryResultStr += "<s part=\"m\">" + BuildHtmlHitStrWithHighlighting(Tokens, bConvASCIIToHtml,
                                                                                   m_pConcordance->m_TableHighlighting,
                                                                                   false,
                                                                                   m_pConcordance->m_TokenDelimiter) +
                "</s>";
            break;
        case DDC_ResultDocIds :
            break; // no hit body

        case DDC_ResultJson:
        default:
            // unhandled
            break;
    };

    // =============   add right hit context  =================
    {
        string RightContext;
        if (!GetContext(Hit.m_BreakNo + 1,
                        Hit.m_BreakNo + m_pQueryCompiler->m_pQuery->m_Options->m_ContextSentencesCount + 1,
                        Hit.m_FileNo, bConvASCIIToHtml, RightContext)) {
            ErrorMessage("Error while  getting the right-hand context");
            return false;
        };
        m_QueryResultStr += RightContext;
    };

    return true;

}


//----------------------------------------------------------------------
bool CConcSession::GenerateOneHitStringJson(uint32_t PageNumber, const CHit &Hit, const vector<COutputToken> &Tokens) {
    bool utf8 = m_pConcordance->m_Utf8;

    //==================================================
    // hit header
    // + adapted from: ShowBibliographyForTable(PageNumber, Hit, Tokens)
    CBibliography B = m_pConcordance->m_BiblIndex.GetFullBibliographyOfHit(Hit.m_FileNo);
    string pageStr = (PageNumber == UnknownPageNumber) ? "null" : Format("%u", PageNumber);
    string hitStr = string("{");

    //==================================================
    // hit debugging
#ifdef DEBUG_HIT_JSON
    hitStr        += (string("\"debug_\":{")
                      + "\"project_\":" + jsonStr(m_pConcordance->m_Path)
                      + ",\"worker_\":" + Format("%zu", m_WorkerId)
                      + ",\"breakno_\":" + Format("%u",  (uint)Hit.m_BreakNo)
                      + ",\"breakstart_\":" + Format("%u",  (uint)(Hit.m_BreakNo==0 ? 0 : GetBreaks()[Hit.m_BreakNo-1]))
                      + ",\"highlight_\":" + Format("%u",(uint)Hit.m_HighlightOccurrenceEnd)
                      + ",\"fileno_\":" + Format("%u",   (uint)Hit.m_FileNo)
                      + ",\"key_\":[" + Format("%d", Hit.m_SortKey.i) + "," + jsonStr(Hit.m_SortKey.s, utf8) + "]"
                      + "},");
#endif

    //==================================================
    // hit node
    hitStr += string("\"node_\":") + jsonStr(m_RequestPath) + ',';

    //==================================================
    // hit metadata
    hitStr += (string("\"meta_\":{")
#if JSON_SHORT_FILENAMES
               + "\"file_\":" + jsonStr(m_pConcordance->GetShortFilename(Hit.m_FileNo), utf8)
#else
               + "\"file_\":" + jsonStr(m_pConcordance->m_CorpusFiles[Hit.m_FileNo], utf8)
#endif // JSON_SHORT_FILENAMES
               + ",\"scan_\":" + jsonStr(B.m_ScanBibl, utf8)
               + ",\"orig_\":" + jsonStr(B.m_OrigBibl, utf8)
               + ",\"date_\":" + jsonStr(B.m_DateStr, utf8)
               + ",\"page_\":" + pageStr
        );
    if (m_pQueryCompiler->m_pQuery->m_Options->m_bEnableBibliography && m_pConcordance->OutputBibliographyOfHits()) {
        string freeBiblAttr = m_pConcordance->m_BiblIndex.GetFreeHeaderBiblAttributesJson(Hit.m_FileNo, utf8);
        if (!freeBiblAttr.empty()) {
            hitStr += "," + freeBiblAttr;
        }
    }

    if (HasRankOrderOperator()) {
        hitStr += Format(",\"rank_\":%d", Hit.m_SortKey.i);
        if (m_pQueryCompiler->m_pQuery->m_Options->m_bDebugRank) {
            const char *DebugInfo = (const char *) (void *) (&m_DebugInfo[0]) + Hit.m_Value.m_DebugRankNo;
            hitStr += ",\"rank_debug_\":" + jsonStr(DebugInfo, utf8);
        }
    }

#ifndef JSON_USE_HASH
    //-- json tokens are returned as arrays: return the indedx-list to be nice
    hitStr += ",\"indices_\":[";
    const vector<size_t> &ishow = m_pConcordance->m_IndicesToShow;
    for (size_t ii = 0; ii < ishow.size(); ii++) {
        if (ii != 0) hitStr.push_back(',');
        hitStr += jsonStr(m_pConcordance->m_Indices[ishow[ii]]->m_ShortName, utf8);
    }
    hitStr.push_back(']');
#endif

    //==================================================
    // hit context

    hitStr += "},\"ctx_\":[";

    //------------------------------------------
    // hit context: left
    {
        string LeftContext;
        if (!GetContextJson((int) Hit.m_BreakNo - (int) m_pQueryCompiler->m_pQuery->m_Options->m_ContextSentencesCount,
                            Hit.m_BreakNo, Hit.m_FileNo, LeftContext)) {
            ErrorMessage("Error while getting the left-hand context");
            return false;
        }
        hitStr += "[" + LeftContext + "],";
    }


    //------------------------------------------
    // hit context: center (aka "body")
    hitStr += "[" + BuildJsonContextString(Tokens, true) + "],";

    //------------------------------------------
    // hit context: right
    {
        string RightContext;
        if (!GetContextJson(Hit.m_BreakNo + 1,
                            Hit.m_BreakNo + m_pQueryCompiler->m_pQuery->m_Options->m_ContextSentencesCount + 1,
                            Hit.m_FileNo, RightContext)) {
            ErrorMessage("Error while  getting the right-hand context");
            return false;
        }
        hitStr += "[" + RightContext + "]";
    }
    hitStr += "]}";

    //-- append hit to m_QueryResultStr
    m_QueryResultStr += hitStr;

    return true;
}


//----------------------------------------------------------------------
bool CConcSession::GetTokensFromStorageByBreak(size_t IndexNo, size_t BreakNo, vector<COutputToken> &Tokens) const {
    Tokens.clear();

    uint32_t StartTokenNo = (BreakNo == 0) ? 0 : GetBreaks()[BreakNo - 1];
    uint32_t EndTokenNo = GetBreaks()[BreakNo];
    if (IndexNo > m_pConcordance->m_Indices.size()) return false;
    const CStringIndexSet &I = *m_pConcordance->m_Indices[IndexNo];
    if (!I.GetTokensFromStorage(StartTokenNo, EndTokenNo, Tokens))
        throw CDDCExpc(errReadSourceFile,
                    "CConcSession::GetTokensFromStorageByBreak(): cannot read $%s storage data for break #%i",
                    I.m_Name.c_str(), BreakNo);
    return true;
}


//----------------------------------------------------------------------
bool CConcSession::GetFileSnippets(const int HitNo, vector<COutputToken> &ResultTokens) const {
    const size_t ContextSize = 4;
    ResultTokens.clear();

    const int BreakNo = m_Hits[HitNo].m_BreakNo;

    uint32_t StartTokenNo = (BreakNo == 0) ? 0 : GetBreaks()[BreakNo - 1];
    uint32_t EndTokenNo = GetBreaks()[BreakNo];

    vector<CTokenNo> positions;
    {
        vector<CTokenNo>::const_iterator start = (HitNo != 0) ? m_HighlightOccurs.begin() +
            m_Hits[HitNo - 1].m_HighlightOccurrenceEnd
            : m_HighlightOccurs.begin();
        vector<CTokenNo>::const_iterator end = m_HighlightOccurs.begin() + m_Hits[HitNo].m_HighlightOccurrenceEnd;
        positions.insert(positions.begin(), start, end);
        sort(positions.begin(), positions.end());
    }

    set<CTokenNo> DifferentTokens;
    {
        vector<COutputToken> TempTokens;
        set<string> DifferentWords;
        uint32_t CurrentStarter = StartTokenNo;
        set<CTokenNo> OtherKwicTokens;

        for (vector<CTokenNo>::const_iterator i = positions.begin(); i < positions.end(); i++) {
            CTokenNo pos = *i;
            if (CurrentStarter > pos) continue;
            if (!m_pConcordance->GetTokenIndex()->GetTokensFromStorage(pos, pos + 1, TempTokens))
                throw CDDCExpc(errReadSourceFile, "CConcSession::GetFileSnippets(): cannot read data for break #%i",
                            BreakNo);
            if (DifferentWords.insert(TempTokens[0].m_TokenStr).second) {
                DifferentTokens.insert(pos);
                // output only the first ten kwic-lines
                if (DifferentTokens.size() == m_pConcordance->m_NumberOfKwicLinesInSnippets)
                    break;
            } else
                OtherKwicTokens.insert(pos);


            // the snippets should be disjoint
            CurrentStarter = min(pos + m_pConcordance->m_RightKwicContextSize + 1, EndTokenNo);
        };

        if (DifferentTokens.size() < m_pConcordance->m_NumberOfKwicLinesInSnippets) {
            for (set<CTokenNo>::const_iterator pos_it = OtherKwicTokens.begin();
                 pos_it != OtherKwicTokens.end(); pos_it++) {
                DifferentTokens.insert(*pos_it);
                if (DifferentTokens.size() == m_pConcordance->m_NumberOfKwicLinesInSnippets)
                    break;
            }
        }


    }


    for (set<CTokenNo>::const_iterator pos_it = DifferentTokens.begin(); pos_it != DifferentTokens.end(); pos_it++) {
        CTokenNo pos = *pos_it;
        int start_kwic_line = max(
            ((m_pConcordance->m_LeftKwicContextSize >= pos) ? 0 : pos - m_pConcordance->m_LeftKwicContextSize),
            StartTokenNo);
        int end_kwic_line = min(pos + m_pConcordance->m_RightKwicContextSize + 1, EndTokenNo);
        vector<COutputToken> CurrTokens;
        if (!m_pConcordance->GetTokenIndex()->GetTokensFromStorage(start_kwic_line, end_kwic_line, CurrTokens))
            throw CDDCExpc(errReadSourceFile, "CConcSession::GetFileSnippets(): cannot read kwic data for break #%i",
                        BreakNo);

        for (size_t i = 0; i < end_kwic_line - start_kwic_line; i++) {
            CurrTokens[i].m_Highlight = binary_search(positions.begin(), positions.end(), start_kwic_line + i) ? 1 : 0;
            ResultTokens.push_back(CurrTokens[i]);
        };
        ResultTokens.push_back(COutputToken("...", false));
    };

    return true;
}

//----------------------------------------------------------------------
DDCErrorEnum CConcSession::GenerateHitStrings(const int StartHitNo, bool UseAdditionalHitDelimiter) {
    assert(m_pQueryCompiler != NULL);
    if (m_pQueryCompiler->m_pQuery == NULL)
        throw CDDCExpc(errRuntime, "CConcSession::GenerateHitStrings(): no compiled query available!");

    if (IsCountSort(m_SortOrder))
        return GenerateCountStrings(StartHitNo, UseAdditionalHitDelimiter);

    DwordVector PageBreaks;

    m_pConcordance->ConvertHitsToPageBreaks(m_Hits.begin(), m_Hits.end(), GetBreaks(), PageBreaks);
    m_QueryResultStr = "";
    m_ErrorStr = "";

    if (StartHitNo < m_ResultOffset)
        throw CDDCExpc("GenerateHitStrings(): m_ResultOffset=%zd exceeds requested StartHitNo=%d", StartHitNo, m_ResultOffset);

    int beg = StartHitNo - m_ResultOffset;
    int end = GetOffsetHint(StartHitNo) - m_ResultOffset;
    for (uint32_t HitNo = beg; HitNo < end; HitNo++) {
        const int BreakNo = m_Hits[HitNo].m_BreakNo;

        if (m_ResultFormat == DDC_ResultJson && HitNo == beg)
            m_QueryResultStr.push_back('[');

        vector<COutputToken> Tokens;
        if (m_pQueryCompiler->m_pQuery->m_Options->m_HitTypeStr == PredefinedFileBreakName) {
            if (!GetFileSnippets(HitNo, Tokens))
                return errReadSourceFile;
        } else {
            assert (!m_pConcordance->m_IndicesToShow.empty());
            if (!GetTokensFromStorageByBreak(m_pConcordance->m_IndicesToShow[0], BreakNo, Tokens))
                return errReadSourceFile;

            // next indices add to anchors, starting from the second index ()
            for (size_t indno = 1; indno < m_pConcordance->m_IndicesToShow.size(); indno++) {
                vector<COutputToken> Interps;
                if (!GetTokensFromStorageByBreak(m_pConcordance->m_IndicesToShow[indno], BreakNo, Interps))
                    throw CDDCExpc(errReadSourceFile,
                                "CConcSession::GenerateHitStrings(): cannot get sentence: IndexNo=%u, BreakNo=%i",
                                m_pConcordance->m_IndicesToShow[indno], BreakNo);
                assert (Interps.size() == Tokens.size());
                for (size_t tkn_no = 0; tkn_no < Interps.size(); tkn_no++) {
                    //if (Interps[tkn_no].m_TokenStr == ddc_archive_stub)
                    if (!Interps[tkn_no].m_TokenStr.empty()) {
                        if (m_ResultFormat != DDC_ResultHTML)
                            Tokens[tkn_no].m_InterpStr +=
                                m_pConcordance->m_InterpDelimiter + Interps[tkn_no].m_TokenStr;
                        else
                            Tokens[tkn_no].m_InterpStr += Interps[tkn_no].m_TokenStr + " ";
                        //else
                        //  Tokens[tkn_no].m_InterpStr +=  m_pConcordance->m_InterpDelimiter;
                    }
                }
            }


            size_t start_occ = (HitNo == 0) ? 0 : m_Hits[HitNo - 1].m_HighlightOccurrenceEnd;
            size_t end_occ = m_Hits[HitNo].m_HighlightOccurrenceEnd;
            vector<CTokenNo>::const_iterator start = m_HighlightOccurs.begin() + start_occ;
            vector<CTokenNo>::const_iterator end = m_HighlightOccurs.begin() + end_occ;
            const uint32_t StartHitTokenNo = (BreakNo == 0) ? 0 : GetBreaks()[BreakNo - 1];
            const bool bUseMatchIds = !m_HighlightIds.empty();

            for (long line = 0; line < Tokens.size(); line++) {
                vector<CTokenNo>::const_iterator found = find(start, end, StartHitTokenNo + line);
                if (found != end)
                    Tokens[line].m_Highlight = (bUseMatchIds ? m_HighlightIds[start_occ + (found - start)] : 1);
            }
        }

        const uint32_t &PageNumber = m_pConcordance->GetPageNumber(PageBreaks[HitNo]);

        if (!GenerateOneHitString(PageNumber, m_Hits[HitNo], Tokens))
            return errReadSourceFile;

        if (m_ResultFormat == DDC_ResultHTML) {
            m_QueryResultStr += "<BR>";
        } else if (m_ResultFormat == DDC_ResultJson) {
            m_QueryResultStr.push_back(HitNo < end - 1 ? ',' : ']');
            m_QueryResultStr.push_back('\n');
        } else {
            m_QueryResultStr.push_back('\n');
        }

        if (UseAdditionalHitDelimiter)
            m_QueryResultStr += m_AdditionalHitDelimiter;
    };

    return errNone;
}

//----------------------------------------------------------------------
DDCErrorEnum CConcSession::GenerateCountStrings(const int StartHitNo, bool UseAdditionalHitDelimiter) {
    assert(m_pQueryCompiler != NULL);
    assert(m_pQueryCompiler->m_pQuery != NULL);

    m_QueryResultStr = "";
    m_ErrorStr = "";

    if (m_ResultFormat == DDC_ResultJson)
        m_QueryResultStr.push_back('[');

    int beg = StartHitNo - m_ResultOffset;
    int end = min(m_Hits.size(), StartHitNo - m_ResultOffset + m_ResultLimit);

    HIT_SORT_DEBUG(
        ddcLogDebug(Format("GenerateCountStrings() called: StartHitNo=%zd ; ResultOffset=%zd ; nHits=%zd ; end=%zd",
                           StartHitNo, m_ResultOffset, m_Hits.size(), end));
        dumpHits("DEBUG[generateCountStrings]: m_Hits", m_Hits);
        );

    for (uint32_t HitNo = beg; HitNo < end; HitNo++) {
        GenerateCountString(m_QueryResultStr, m_ResultFormat, m_Hits[HitNo]);
        if (m_ResultFormat == DDC_ResultJson) {
            m_QueryResultStr.push_back(HitNo < end - 1 ? ',' : ']');
            m_QueryResultStr.push_back('\n');
        }

        if (UseAdditionalHitDelimiter)
            m_QueryResultStr += m_AdditionalHitDelimiter;
    }

    return errNone;
}

//----------------------------------------------------------------------
void CConcSession::DecorateQueryResults(const string &FormatStr, string &QueryResultStr) {
    if (GetResultFormatByString(FormatStr) == DDC_ResultHTML)
        QueryResultStr = "<HTML> <BODY>\n" + QueryResultStr + "\n</BODY></HTML>";
}

//----------------------------------------------------------------------
/*
 * DDC_FILEREF_BINSEARCH_COEF
 *  + heuristic for approximating number of linear-search ops per binary-search visitation (empirically set to 8)
 *    - for binary-vs-linear dispatch in CConcSession::InitFileReferences()
 *    - based on v2.1.19 CQueryNode::ConvertOccurrencesToHits() optimizations
 *    - inspired by Alexey Sokirko's HitsCount-dispatch optimization in delwin branch r1294
 *  + if undefined, lower_bound() is called for each hit
 *  + benchmarks (zeit01@plato, tested with ddc_simple -HitIds -ProfileRun $iters "$query")
 *    - avg 63% faster than always-use-binsearch strategy
 *    - <1% slower for VLF items ($l=@Kaffeeklastch), up to 1.5x faster for VHF items ($l=@diese)
 */
#define DDC_FILEREF_BINSEARCH_COEF 8

void CConcSession::InitFileReferences(vector<CHit> &Hits) const {
    const ddcBreakVector &Breaks = GetBreaks();
    const ddcBreakVector &FileBreaks = m_pConcordance->GetFileBreaks();
    size_t HitsCount = Hits.size();

#ifdef DDC_FILEREF_BINSEARCH_COEF
    //-- binary-vs-linear dispatch
    uint32_t breakStride = VectorStride(Breaks);     //-- average number of tokens per break-unit in Breaks[]
    uint32_t fileStride  = VectorStride(FileBreaks); //-- average number of tokens per file-unit in FileBreaks[]
    ddcBreakVector::const_iterator
        fbi=FileBreaks.begin(),
        fbi_end=FileBreaks.end();

    for (size_t HitNo=0; HitNo < HitsCount; ++HitNo) {
        CHit &H = Hits[HitNo];

        // seek distance (tokens): d=(Breaks[H.m_BreakNo] - *fbi)
        // expected number of linear-increment ops: d/fileStride
        // expected number of binary-search    ops: log2u32(fbi_end-fbi)
        const CTokenNo &brk = Breaks[H.m_BreakNo];
        if (brk > *fbi && (brk - *fbi)/fileStride > DDC_FILEREF_BINSEARCH_COEF*log2u32(fbi_end-fbi)) {
            fbi = lower_bound(fbi, fbi_end, brk);
        } else {
            while (fbi != fbi_end && brk > *fbi) ++fbi;
        }

        H.m_FileNo  = fbi - FileBreaks.begin();
        H.m_SortKey = H.m_BreakNo;  // no sort
    }

#else // !defined(DDC_FILEREF_BINSEARCH_COEF)
    //-- always use binsearch
    ddcBreakVector::const_iterator fbi=FileBreaks.begin();
    for (size_t HitNo = 0; HitNo < HitsCount; ++HitNo) {
        CHit &H     = Hits[HitNo];
        fbi         = lower_bound(fbi, FileBreaks.end(), Breaks[H.m_BreakNo]);
        H.m_FileNo  = fbi - FileBreaks.begin();
        H.m_SortKey = H.m_BreakNo;  // no sort
    }
#endif
}

//----------------------------------------------------------------------
struct COccurrenceAndQueryNodeIndex {
    CTokenNo m_TokenNo;
    BYTE m_NodeIndex;

    COccurrenceAndQueryNodeIndex(CTokenNo TokenNo, BYTE NodeIndex) {
        m_TokenNo = TokenNo;
        m_NodeIndex = NodeIndex;
    }

    bool operator<(const COccurrenceAndQueryNodeIndex &X) const {
        return m_TokenNo < X.m_TokenNo;
    }
};

//----------------------------------------------------------------------
struct CHitRank {
    // the begining of the most representative passage
    size_t m_PassageStart;
    // the end of the most representative passage
    size_t m_PassageEnd;
    // the frequences of all query items indexed by Node Index for the current hit
    vector<size_t> m_QueryNodeFreqs;
    // the frequences of all query items indexed by Node Index for the whole collection
    vector<double> m_IDFs;
};

//----------------------------------------------------------------------
// OccurrenceAndQueryNodeIndex is the array of all occurrences for this seacrh period.
//  start_pos is  the starting point in  OccurrenceAndQueryNodeIndex of occurrences for the current hit.
//  end_pos is  the end point in  OccurrenceAndQueryNodeIndex of occurrences for the current hit.
// GetHitRankLen returns a CHitRank structure.
void GetHitRankLen(vector<COccurrenceAndQueryNodeIndex> &OccurrenceAndQueryNodeIndex, int start_pos, int end_pos,
                   CHitRank &Result) {
    sort(OccurrenceAndQueryNodeIndex.begin() + start_pos, OccurrenceAndQueryNodeIndex.begin() + end_pos);

    // PrevPositionOfNode[i] - the index of the prev node of the same type
    vector<CTokenNo> PrevPositionOfNode(end_pos - start_pos, UINT32_MAX);
    CTokenNo iFirstIndex = UINT32_MAX; // iFirstIndex is  the first element of the passage

    size_t QueryNodesCount = Result.m_QueryNodeFreqs.size();
    fill(Result.m_QueryNodeFreqs.begin(), Result.m_QueryNodeFreqs.end(), 0);

    {    // get PrevPositionOfNode and iFirstIndex
        vector<CTokenNo> PrevNodes(QueryNodesCount, UINT32_MAX);
        for (size_t i = start_pos; i < end_pos; i++) {
            // take the previous node of the same type (of the same Node Index)
            CTokenNo &PrevNode = PrevNodes[OccurrenceAndQueryNodeIndex[i].m_NodeIndex];
            if (PrevNode != UINT32_MAX) // it is not the first node of this type
                PrevPositionOfNode[i - start_pos] = PrevNode; // set the previous node
            PrevNode = i - start_pos;

            // increment frequence
            Result.m_QueryNodeFreqs[OccurrenceAndQueryNodeIndex[i].m_NodeIndex]++;
        }
        for (size_t i = 0; i < PrevNodes.size(); i++)
            if (PrevNodes[i] != UINT32_MAX) // PrevNodes[i] == DWORD_MAX, then this query node is not found for this hit
                iFirstIndex = min(iFirstIndex, OccurrenceAndQueryNodeIndex[PrevNodes[i] + start_pos].m_TokenNo);
    }

    size_t MinPassageLen = UINT32_MAX;
    for (size_t i = end_pos - 1; i >= start_pos; i--) {
        size_t len = OccurrenceAndQueryNodeIndex[i].m_TokenNo - iFirstIndex;
        if (len <= MinPassageLen) // the closer to the beginning, the better, that's why here we use <= (not  <)
        {

            MinPassageLen = len;
            Result.m_PassageStart = iFirstIndex;
            Result.m_PassageEnd = OccurrenceAndQueryNodeIndex[i].m_TokenNo + 1;
        }
        CTokenNo PrevNode = PrevPositionOfNode[i - start_pos];
        if (PrevNode == UINT32_MAX)
            break;
        if (OccurrenceAndQueryNodeIndex[PrevNode + start_pos].m_TokenNo < iFirstIndex)
            iFirstIndex = OccurrenceAndQueryNodeIndex[PrevNode + start_pos].m_TokenNo;
    }

}

//----------------------------------------------------------------------
void CConcSession::InitSortByRank(const CQuery *pQuery) const {
    const ddcBreakVector &Breaks = GetBreaks();
    vector<CHit> &Hits = pQuery->m_Node->m_Hits;
    const bool bShowDebugRank = pQuery->m_Options->m_bDebugRank;
    size_t HitsCount = Hits.size();
    CHitRank HitRank;
    size_t NodeIndicesCount = m_pQueryCompiler->GetNodeIndicesCount();
    HitRank.m_QueryNodeFreqs.resize(NodeIndicesCount);

    // initializing idf for all query items
    for (size_t i = 0; i < NodeIndicesCount; i++) {
        double cf = pQuery->m_Node->GetNodeFrequencyByNodeIndex(i);
        double c = (double) Breaks.size();
        // we have no document frequence, that's why we use collection frequence, which can be more than "c".
        if (cf > c)
            cf = c;
        // calculating augmemented inverde document frequence
        HitRank.m_IDFs.push_back(log((c + 0.5) / cf) / log(c + 1));
    }


    vector<COccurrenceAndQueryNodeIndex> OccurrenceAndQueryNodeIndex;
    {
        const vector<BYTE> &NodeIndices = pQuery->m_Node->m_OccurrenceNodeIndices;
        const vector<CTokenNo> &Occurrences = pQuery->m_Node->m_Occurrences;
        assert (Occurrences.size() == NodeIndices.size());
        size_t Count = Occurrences.size();
        OccurrenceAndQueryNodeIndex.reserve(Count);
        for (size_t i = 0; i < Count; i++)
            OccurrenceAndQueryNodeIndex.push_back(COccurrenceAndQueryNodeIndex(Occurrences[i], NodeIndices[i]));

    }
    double AverageHitLength = m_pConcordance->GetCorpusEndTokenNo() / Breaks.size();

    if (m_pConcordance->m_BiblIndex.IsRegisteredBiblField("PageRank"))
        m_pConcordance->m_BiblIndex.InitSortByBiblIntegerField("PageRank", pQuery->m_Node->m_Hits);
    else
        for (size_t HitNo = 0; HitNo < HitsCount; HitNo++)
            Hits[HitNo].m_SortKey = 0;

    for (size_t HitNo = 0; HitNo < HitsCount; HitNo++) {
        CHit &H = Hits[HitNo];
        uint32_t StartTokenNo = (H.m_BreakNo == 0) ? 0 : GetBreaks()[H.m_BreakNo - 1];
        int start_occur = (HitNo == 0) ? 0 : Hits[HitNo - 1].m_HighlightOccurrenceEnd;
        int end_occur = Hits[HitNo].m_HighlightOccurrenceEnd;
        GetHitRankLen(OccurrenceAndQueryNodeIndex, start_occur, end_occur, HitRank);
        double HitSize = (H.m_BreakNo == 0) ? Breaks[H.m_BreakNo] : Breaks[H.m_BreakNo] - Breaks[H.m_BreakNo - 1];
        double tfidf = 0;
        for (size_t i = 0; i < NodeIndicesCount; i++) {
            double freq_l = HitRank.m_QueryNodeFreqs[0];
            // calculating augmemented term frequence
            double tf_l = freq_l / (freq_l + 0.5 + 1.5 * HitSize / AverageHitLength);
            const double beta = 0.4;
            double tfidf_l = beta + (1 - beta) * tf_l * HitRank.m_IDFs[i];
            tfidf += tfidf_l;
        }
        tfidf = m_pConcordance->m_TfIdfRank * tfidf / (double) NodeIndicesCount;
        double near_rank = m_pConcordance->m_NearRank /
            ((double) (HitRank.m_PassageEnd - HitRank.m_PassageStart) / (double) NodeIndicesCount);
        int pos_from_the_hit_beginning = HitRank.m_PassageStart - StartTokenNo + 1;
        double position_rank = m_pConcordance->m_PositionRank / (double) pos_from_the_hit_beginning;
        double rank = (tfidf + near_rank + position_rank) / 3;
        int SortKey = H.m_SortKey.i + (int) (rank * (double) 1000);
        if (bShowDebugRank) {
            H.m_Value.m_DebugRankNo = m_DebugInfo.size();
            string DebugInfo = Format("Rank=%i (tfidf=%05f near=%05f pos=%05f(%i) PR=%i)",
                                      SortKey, tfidf, near_rank, position_rank,
                                      pos_from_the_hit_beginning, H.m_SortKey.i);
            for (size_t c = 0; c < DebugInfo.size(); c++)
                m_DebugInfo.push_back(DebugInfo[c]);
            m_DebugInfo.push_back(0);
        }
        H.m_SortKey = SortKey; // H.m_SortKey contains already page rank
    }
}

//----------------------------------------------------------------------
void CConcSession::InitSortBySize(const CQuery *pQuery) const {
    const ddcBreakVector &Breaks = GetBreaks();
    size_t HitsCount = pQuery->m_Node->m_Hits.size();
    for (size_t HitNo = 0; HitNo < HitsCount; HitNo++) {
        CHit &H = pQuery->m_Node->m_Hits[HitNo];
        uint32_t BreakNo = H.m_BreakNo;
        H.m_SortKey = (BreakNo == 0) ? Breaks[BreakNo] : Breaks[BreakNo] - Breaks[BreakNo - 1];
    }
}

//----------------------------------------------------------------------
void CConcSession::InitSortByRandom(const CQuery *pQuery) const {
    size_t HitsCount = pQuery->m_Node->m_Hits.size();
    for (size_t HitNo = 0; HitNo < HitsCount; HitNo++) {
        CHit &H = pQuery->m_Node->m_Hits[HitNo];
        //unsigned short ostate0=m_pRandom->m_state[0], ostate1=m_pRandom->m_state[1], ostate2=m_pRandom->m_state[2]; //-- DEBUG RANDOM
        H.m_SortKey = m_pRandom->random_n();
        //concord_daemon_log( Format("InitSortByRandom: RandomSeed=%d, state=[%d,%d,%d]; HitNo=%u, SortKey.i=%d", m_RandomSeed, ostate0,ostate1,ostate2, HitNo, H.m_SortKey.i) ); //-- DEBUG RANDOM
    }
}

//----------------------------------------------------------------------
void CConcSession::InitSortByContext(const CQuery *pQuery, const CDDCFilterWithBounds &F) const {
    CStringIndexSet *pIdx = (F.m_AttrName.empty()
                             ? m_pConcordance->GetTokenIndex()
                             : m_pConcordance->GetIndexByAlias(F.m_AttrName));
    CQueryNode *qnod = pQuery->m_Node;
    vector<CHit> &Hits = qnod->m_Hits;
    uint32_t HitsCount = qnod->m_Hits.size();
    const ddcBreakVector &Breaks = GetBreaks();
    const vector<BYTE> &occur_ids = qnod->m_OccurrenceMatchIds;

    if (!pIdx)
        throw CDDCExpc(errOther,
                    Format("CConcSession::InitSortByContext(): Error: could not find index `%s' for context sort",
                           F.m_AttrName.c_str()));

    for (uint32_t HitNo = 0; HitNo < HitsCount; HitNo++) {
        CHit &H = Hits[HitNo];
        uint32_t StartTokenNo = (H.m_BreakNo == 0) ? 0 : Breaks[H.m_BreakNo - 1];
        uint32_t EndTokenNo = Breaks[H.m_BreakNo];

        //-- get context anchor occurrence-index occur_i
        uint32_t occur_i;
        if (qnod->m_bUseMatchIds && F.m_ContextMatchId != 0) {
            //-- get occur_i: WITH match-ids
            switch (F.m_FilterType) {
                case LessByLeftContext:
                case GreaterByLeftContext:
                    //-- #left : stick to FIRST id-matching token in each hit
                    occur_i = qnod->GetFirstOccurrenceInHit(HitNo, F.m_ContextMatchId);
                    break;

                case LessByRightContext:
                case GreaterByRightContext:
                    //-- #right : stick to FINAL id-matching token in each hit
                    occur_i = qnod->GetLastOccurrenceInHit(HitNo, F.m_ContextMatchId);
                    break;

                case LessByMiddleContext:
                case GreaterByMiddleContext:
                default:
                    //-- #middle : stick to MIDDLE id-matching token in each hit
                    occur_i = qnod->GetMiddleOccurrenceInHit(HitNo, F.m_ContextMatchId);
                    break;
            }
        } else {
            //-- get occur_i: WITHOUT match-ids
            switch (F.m_FilterType) {
                case LessByLeftContext:
                case GreaterByLeftContext:
                    //-- #left : stick to FIRST match-token in each hit
                    occur_i = (HitNo == 0) ? 0 : Hits[HitNo - 1].m_HighlightOccurrenceEnd;
                    break;

                case LessByRightContext:
                case GreaterByRightContext:
                    //-- #right : stick to FINAL match-token in each hit
                    occur_i = H.m_HighlightOccurrenceEnd - 1;
                    break;

                case LessByMiddleContext:
                case GreaterByMiddleContext:
                default:
                    //-- #middle : stick to MIDDLE match-token of each hit
                {
                    uint32_t occur_li = occur_i = (HitNo == 0) ? 0 : Hits[HitNo - 1].m_HighlightOccurrenceEnd;
                    uint32_t occur_ri = H.m_HighlightOccurrenceEnd - 1;
                    occur_i = occur_li + (occur_ri - occur_li) / 2;
                }
                break;
            }
        }

        //-- assign sort key
        CTokenNo keyId = (occur_i >= qnod->m_Occurrences.size() ? EndTokenNo : (qnod->m_Occurrences[occur_i] +
                                                                                F.m_ContextOffset));
        if (keyId >= StartTokenNo && keyId < EndTokenNo &&
            (H.m_SortKey.i = pIdx->GetTokenIndexId(keyId)) != UINT32_MAX) {
            //-- usual case: within target break and with a valid item id
            H.m_SortKey.s = pIdx->GetIndexItemStr(pIdx->m_Index[H.m_SortKey.i]);
        } else {
            //-- break-overflow (EOS etc) or invalid key item: treat as empty sort-key
            H.m_SortKey = INT_MIN;
        }
    }
}

//----------------------------------------------------------------------
void CConcSession::InitSortKeyForHits(const CQuery *pQuery, const CDDCFilterWithBounds &Filter, vector<size_t>& PeriodHitsIndex) {
    assert (Filter.m_FilterType != HitSortsCount);

    //-- defaults
    m_bSortByString = false;
    m_bPrune    = false;
    m_SortOrder = Filter.SortOrder();

    //-- guts
    switch (Filter.m_FilterType) {
        case GreaterByDate:
        case LessByDate:
            m_pConcordance->m_BiblIndex.InitSortByDate(pQuery->m_Node->m_Hits);
            break;

        case GreaterByRank:
        case LessByRank:
            InitSortByRank(pQuery);
            break;

        case LessByMiddleContext:
        case GreaterByMiddleContext:
        case LessByLeftContext:
        case GreaterByLeftContext:
        case LessByRightContext:
        case GreaterByRightContext:
            InitSortByContext(pQuery, Filter);
            m_bSortByString = true;
            break;

        case GreaterBySize:
        case LessBySize:
            InitSortBySize(pQuery);
            break;

        case NoSort: // NoSort is used for filtering, must be ascending
        case GreaterByFreeBiblField:
        case LessByFreeBiblField:
            m_pConcordance->m_BiblIndex.InitSortByBiblIntegerField(Filter.m_AttrName, pQuery->m_Node->m_Hits);
            m_bSortByString = (m_pConcordance->m_BiblIndex.GetBiblFieldTypeId(Filter.m_AttrName) == cfbiString
                               ||
                               m_pConcordance->m_BiblIndex.GetBiblFieldTypeId(Filter.m_AttrName) == cfbiStringConstant);
            break;

        case RandomSort:
            InitSortByRandom(pQuery);
            break;

        case GreaterByPruneKey:
        case LessByPruneKey:
            assert(Filter.m_Parent != NULL);
            ((CQFPrune*)Filter.m_Parent)->PruneHitsIndex(pQuery, PeriodHitsIndex);
            m_bSortByString = true;
            m_bPrune = true;
            break;

        default: break; //-- unhandled
    };
}

//----------------------------------------------------------------------
void CConcSession::SortKeyLB(CHitSortKey &Key, const CDDCFilterWithBounds &Filter) {
    Key.i = INT_MIN;

    //-- guts
    switch (Filter.m_FilterType) {
        case LessByMiddleContext:
        case GreaterByMiddleContext:
        case LessByLeftContext:
        case GreaterByLeftContext:
        case LessByRightContext:
        case GreaterByRightContext: {
            CStringIndexSet *pIdx = (Filter.m_AttrName.empty()
                                     ? m_pConcordance->GetTokenIndex()
                                     : m_pConcordance->GetIndexByAlias(Filter.m_AttrName));
            if (!pIdx)
                throw CDDCExpc(errOther,
                            Format("CConcSession::SortKeyLB(): could not find index `%s' for context-key pruning",
                                   Filter.m_AttrName.c_str()));

            Key.i = pIdx->GetTypeIndexIdLowerBound(Key.s);
            break;
        }

        case NoSort: // NoSort is used for filtering, must be ascending (but shouldn't happen here)
        case GreaterByFreeBiblField:
        case LessByFreeBiblField: {
            if (Filter.m_BiblIndex == NULL) {
                //-- should never happen
                ddcLogWarn(
                    Format("WARNING: Filter.m_BiblIndex undefined: cannot get value-ID for key `%s' via filter %s[%s]",
                           Key.s.c_str(),
                           HitSortEnumStrings[Filter.m_FilterType],
                           Filter.m_AttrName.c_str()));
            } else {
                Key.i = Filter.m_BiblIndex->GetIntegerLowerBound(Key.s);
            }
            break;
        }

        case LessByPruneKey:
        case GreaterByPruneKey:
            //-- just use string key
            break;

        default:
            Key.i = hex2int(Key.s);
            break;
    };
}


//==============================================================================

//----------------------------------------------------------------------
DDCErrorEnum CConcSession::GetAllHits(const string &Query, size_t Start, size_t Limit) {
    return GetAllHits(m_pQueryCompiler->m_pQuery, Start, Limit);
}


//----------------------------------------------------------------------
DDCErrorEnum CConcSession::GetAllHits(CQuery *QueryRoot, size_t Start, size_t Limit) {
    assert(QueryRoot != NULL);
    m_bStoppedByUser = false;
    ClearContainer(m_ShortOccurCaches);
    ClearQueryResults();

    //-- check for count-queries
    CQuery *qRoot = QueryRoot;
    CQCount *qCount = NULL;
    size_t qLimit = Limit;
    if (IsUniversalCountQuery(QueryRoot)) {
        //-- count(*) query: do memory-optimized computation
        ((CQCount *) QueryRoot)->CountUniversal(*this, Limit);
        return errNone;
    } else if (typeid(*QueryRoot) == typeid(CQCount)) {
        //-- count() query: remember count-node but evaluate (all) daughter hits
        qCount = (CQCount *) QueryRoot;
        qRoot = qCount->m_dtr;
        qLimit = qCount->m_sample;
        qCount->m_CountSample = 0;

        //-- count() query: by breaks: acquire subquery hits in #SEPARATE mode!
        assert(qCount->m_Options != NULL);
        assert(qRoot->m_Options != NULL);
        qCount->m_Options->m_bSeparateHits = qRoot->m_Options->m_bSeparateHits;
        if (!qCount->CanCountByFile() && !qCount->m_Options->m_bSeparateHits) {
            qRoot->m_Options->m_bSeparateHits = true;
        }
    }
    CQueryNode *qNode = qRoot->m_Node;
    CQueryOptions *qOpts = qRoot->m_Options;
    vector<CHit> &qHits = qNode->m_Hits;

    bool bUseMatchIds = qNode->m_bUseMatchIds;
    size_t CountOfPeriods = m_pConcordance->GetSearchPeriodsCount();
    time_t last_time;
    DDCErrorEnum rc = errNone;
    CHitSortKey minKey(INT_MIN, m_ResultMinKey);

    if (m_QueryEndTime != TheEndOfTheWorld)
        time(&last_time);

    vector<bool> bFilesUses(m_pConcordance->m_CorpusFiles.size(), false);


    for (m_CurrentSearchPeriodNo = 0; m_CurrentSearchPeriodNo < CountOfPeriods; m_CurrentSearchPeriodNo++) {
        //ddcLogWarn(Format("CConcSession::GetAllHits(): period %i / %i", m_CurrentSearchPeriodNo, CountOfPeriods));
        m_pQueryCompiler->Evaluate(qRoot);
        InitFileReferences(qHits);

        vector<size_t> PeriodHitsIndex;
        if (m_pConcordance->m_MaskedFiles.empty()) {
            for (size_t i = 0; i < qHits.size(); i++)
                PeriodHitsIndex.push_back(i);
        } else {
            for (size_t i = 0; i < qHits.size(); i++)
                if (m_pConcordance->m_MaskedFiles.find(qHits[i].m_FileNo) == m_pConcordance->m_MaskedFiles.end())
                    PeriodHitsIndex.push_back(i);
        }

        m_SortOrder = hsoNone; //-- no sort
        for (size_t FilterNo = 0; FilterNo < qOpts->m_Filters.size(); FilterNo++) {
            const CDDCFilterWithBounds &F = qOpts->m_Filters[FilterNo];
            //ddcLogDebug(Format("[period=%d] evaluating filter of type %s ; SortOrder=%d", m_CurrentSearchPeriodNo, HitSortEnumStrings[F.m_FilterType], m_SortOrder));

            //-- init Hits::m_SortKey (always initialized in raw ascending order)
            InitSortKeyForHits(qRoot, F, PeriodHitsIndex);

            size_t hits_start, hits_end;
            if (F.IsPruneFilter()) {
                //-- prune sort
                hits_start = 0;
                hits_end = PeriodHitsIndex.size();
            } else if (m_SortOrder >= 0) {
                //-- ascending sort (also run for NoSort, since #has_field[] filters need bounds-checking)
                stable_sort(PeriodHitsIndex.begin(), PeriodHitsIndex.end(), IsLessByHitSortKey(qHits));
                hits_start = my_lower_bound(PeriodHitsIndex.begin(), PeriodHitsIndex.end(), F.m_KeyLo, qHits) - PeriodHitsIndex.begin();
                hits_end   = my_lower_bound(PeriodHitsIndex.begin(), PeriodHitsIndex.end(), F.m_KeyHi, qHits) - PeriodHitsIndex.begin();
            } else if (m_SortOrder < 0) {
                //-- descending sort
                stable_sort(PeriodHitsIndex.rbegin(), PeriodHitsIndex.rend(), IsLessByHitSortKey(qHits));
                hits_start = my_lower_bound(PeriodHitsIndex.rbegin(), PeriodHitsIndex.rend(), F.m_KeyHi, qHits) - PeriodHitsIndex.rbegin();
                hits_end   = my_lower_bound(PeriodHitsIndex.rbegin(), PeriodHitsIndex.rend(), F.m_KeyLo, qHits) - PeriodHitsIndex.rbegin();
                hits_start = PeriodHitsIndex.size() - hits_start;
                hits_end   = PeriodHitsIndex.size() - hits_end;
            } else {
                //-- no sort
                hits_start = 0;
                hits_end = PeriodHitsIndex.size();
            }

#if DEBUG_HIT_SORT //-- DEBUG
            fprintf(stderr, "DEBUG[pre-trim,period=%d/%d,filter=%s(%s),order=%d]: KeyLo={%d,%s}, KeyHi={%d,%s}, hits_start=%zd, hits_end=%zd\n",
                    m_CurrentSearchPeriodNo, CountOfPeriods,
                    HitSortEnumNames[F.m_FilterType], F.m_AttrName.c_str(), m_SortOrder,
                    F.m_KeyLo.i, jsonStr(F.m_KeyLo.s).c_str(),
                    F.m_KeyHi.i, jsonStr(F.m_KeyHi.s).c_str(),
                    hits_start, hits_end);
            dumpHitIndex("DEBUG: periodHits", PeriodHitsIndex, "qHits", qHits);
#endif //-- DEBUG

            if (hits_end < hits_start) hits_start = hits_end;
            PeriodHitsIndex.erase(PeriodHitsIndex.begin() + hits_end, PeriodHitsIndex.end());
            PeriodHitsIndex.erase(PeriodHitsIndex.begin(), PeriodHitsIndex.begin() + hits_start);

            if (F.m_bSet) {
                // we have to intersect F.m_SatisfiedValues with qHits using integer sort-key m_CHit::m_SortKey.i
                vector<size_t>::const_iterator hits_start_i = PeriodHitsIndex.begin();
                vector<size_t>::const_iterator hits_end_i = PeriodHitsIndex.end();
                set<int>::const_iterator val_start_i = F.m_SatisfiedValues.begin();
                set<int>::const_iterator val_end_i = F.m_SatisfiedValues.end();
                vector<size_t> NewHitsIndex;

                assert(F.SortOrder() >= 0); //-- parallel traversal intersection only works for ascending sort!
                while (hits_start_i != hits_end_i && val_start_i != val_end_i) {
                    int i1 = qHits[*hits_start_i].m_SortKey.i;
                    int i2 = *val_start_i;

                    if (i1 < i2)
                        hits_start_i++;
                    else if (i2 < i1)
                        val_start_i++;
                    else {
                        NewHitsIndex.push_back(*hits_start_i);
                        hits_start_i++;
                    }
                }
                NewHitsIndex.swap(PeriodHitsIndex);
            }
        }

        //-- keep track of total number of hits we've processed
        m_AllHitsCount += PeriodHitsIndex.size();

        //-- calculate m_RelevantDocumentCount if required
        if (m_pConcordance->m_bShowNumberOfRelevantDocuments) {
            size_t Count = PeriodHitsIndex.size();
            for (size_t i = 0; i < Count; i++) {
                uint32_t FileNo = qHits[PeriodHitsIndex[i]].m_FileNo;
                if (!bFilesUses[FileNo]) {
                    bFilesUses[FileNo] = true;
                    m_RelevantDocumentCount++;
                }
            }
        }

        //-- trim-front: trimming from *front* of period-local hits (v2.1.9: save memory for high-offset result pages)
        //   + non-count queries only
        //   + non-pruned queries only
        //   + only meaningful for Start > 0
        size_t TrimFrontOffset = 0; //-- for trim-front, period-local
        if (!qCount && !m_bPrune && Start > 0) {
            if (m_SortOrder == hsoNone && Start > m_ResultOffset) {
                //-- trim-front: offset-based (no sort operators)
                TrimFrontOffset = min(Start - m_ResultOffset, PeriodHitsIndex.size());
                PeriodHitsIndex.erase(PeriodHitsIndex.begin(), PeriodHitsIndex.begin() + TrimFrontOffset);
                m_ResultOffset += TrimFrontOffset;
                HIT_TRIM_DEBUG(ddcLogDebug(
                                   Format("TRIM-FRONT[period=%zd/%zd,ResultOffset=%zd,Start=%zd]: trimmed %zd/%zd initial hit(s)",
                                          m_CurrentSearchPeriodNo, CountOfPeriods, m_ResultOffset, Start,
                                          TrimFrontOffset, TrimFrontOffset + PeriodHitsIndex.size()))
                    );
            } else if (m_SortOrder != hsoNone && !m_ResultMinKey.empty() && !qOpts->m_Filters.empty()) {
                //-- trim-front: sortkey-based (nontrivial sort operators)
                SortKeyLB(minKey, qOpts->m_Filters.back());
                if (m_SortOrder > 0) {
                    //-- ascending sort
                    TrimFrontOffset = my_lower_bound(PeriodHitsIndex.begin(), PeriodHitsIndex.end(), minKey, qHits) -
                        PeriodHitsIndex.begin();
                } else if (m_SortOrder < 0) {
                    //-- descending sort
                    TrimFrontOffset = my_upper_bound(PeriodHitsIndex.rbegin(), PeriodHitsIndex.rend(), minKey, qHits) -
                        PeriodHitsIndex.rbegin();
                    TrimFrontOffset = PeriodHitsIndex.size() - TrimFrontOffset;
                }

                m_ResultOffset += TrimFrontOffset;
                PeriodHitsIndex.erase(PeriodHitsIndex.begin(), PeriodHitsIndex.begin() + TrimFrontOffset);
                HIT_TRIM_DEBUG(ddcLogDebug(
                                   Format("TRIM-FRONT[period=%zd/%zd,ResultOffset=%zd,minKey=%d=`%s']: trimmed %zd/%zd initial hit(s)",
                                          m_CurrentSearchPeriodNo, CountOfPeriods, m_ResultOffset, minKey.i, minKey.s.c_str(),
                                          TrimFrontOffset, (TrimFrontOffset + PeriodHitsIndex.size())))
                    );
            }
        }

        //-- trim-back: trimming from *back* of period-local hits (v2.1.9: save more memory for high-offset result pages)
        // + we add at most PeriodLimit hits to the global m_Hits[] array per corpus-period ("trim-back")
        size_t PeriodLimit;
        if (m_SortOrder == hsoNone) {
            //-- trim-back: offset-based (no sort operators: we can consider all hits already computed by this or previous period-iterations)
            PeriodLimit = qLimit - min(qLimit, m_ResultOffset + m_Hits.size());
        } else {
            //-- trim-back: nontrivial sort (use m_ResultOffset to ignore all and only front-trimmed hits: we know they're all < ResultMinKey)
            PeriodLimit = qLimit - min(qLimit, m_ResultOffset);
        }

        //-- add period-local hits to m_Hits and highlight occurrences
        // + we ought to merge-sort here e.g. with std::inplace_merge()
        //   *but* we also need to keep m_HighlightOccurs[] aligned with m_Hits[]
        // + current solution is full post-retrieval re-sort in calling method CConcSession::GetHits()
        // + a native post-retrieval k-way merge with a min-heap would be even better, but would be a PITA
        size_t PeriodCount = min(PeriodLimit, PeriodHitsIndex.size());
        HIT_TRIM_DEBUG(ddcLogDebug(
                           Format("TRIM-BACK[period=%zd/%zd,qLimit=%zd,ResultOffset=%zd,TrimFrontOffset=%zd,PeriodLimit=%zd,PeriodCount=%zd]: trimming %zd/%zd final hit(s)",
                                  m_CurrentSearchPeriodNo, CountOfPeriods, qLimit, m_ResultOffset, TrimFrontOffset, PeriodLimit,
                                  PeriodCount,
                                  PeriodHitsIndex.size() - PeriodCount, PeriodHitsIndex.size()
                               )));
        for (size_t i = 0; i < PeriodCount; i++) {
            size_t HitNo = PeriodHitsIndex[i];
            const CHit &H = qHits[HitNo];

            int start_index = (HitNo == 0) ? 0 : qHits[HitNo - 1].m_HighlightOccurrenceEnd;
            m_HighlightOccurs.insert(m_HighlightOccurs.end(),
                                     qNode->m_Occurrences.begin() + start_index,
                                     qNode->m_Occurrences.begin() + H.m_HighlightOccurrenceEnd
                );
            if (bUseMatchIds)
                m_HighlightIds.insert(m_HighlightIds.end(),
                                      qNode->m_OccurrenceMatchIds.begin() + start_index,
                                      qNode->m_OccurrenceMatchIds.begin() + H.m_HighlightOccurrenceEnd
                    );
            m_Hits.push_back(H);
            m_Hits.back().m_HighlightOccurrenceEnd = m_HighlightOccurs.size();
        }


        //-- inexpensive hack to check that m_HighlightOccurrs[] and m_Hits[] are aligned 1:1
        assert (m_Hits.empty() || m_Hits.back().m_HighlightOccurrenceEnd == m_HighlightOccurs.size());

        // compute period-local counts
        if (qCount != NULL)
            qCount->CountLocal(*this, Limit);

        // check for user interrupt
        if (m_bStoppedByUser) break;

        //  checking timeout, if it was specified
        if (m_QueryEndTime != TheEndOfTheWorld) {
            if (m_CurrentSearchPeriodNo + 1 < CountOfPeriods) { // if it is not the last cycle
                time_t curr_time;
                time(&curr_time);
                if ((curr_time - last_time + curr_time) > m_QueryEndTime) { // if cannot process next cycle
                    concord_daemon_log(Format("timeout elapsed after %g second(s)", difftime(curr_time, last_time)));
                    rc = errTimeoutElapsed;
                    break;
                }
                //printf ("one period time=%i, left time =%i\n", curr_time-last_time, m_QueryEndTime - curr_time);
                last_time = curr_time;
            }
        }
    } //  cycle for corpus periods

    // encode count() query results as hits
    if (qCount != NULL && rc == errNone)
        qCount->ConvertCountsToHits(*this, Limit);

    //  we cannot call here CleanParser, because we would use later some slots of  m_pQueryCompiler
    //  but  we should delete the parse tree itself in order to free meemory
    //  + moo: this won't work in v2.0.23 because we still need query filters in m_pQueryCompiler->m_pQuery->m_Filters
    //         it's called implicitly by CQueryCompiler::CleanParser(), i.e. before the next parse
    //m_pQueryCompiler->DeleteTree();

    return rc;
}

//----------------------------------------------------------------------
bool CConcSession::IsUniversalCountQuery(CQuery *QueryRoot) const {
    return (typeid(*QueryRoot) == typeid(CQCount) && ((CQCount *) QueryRoot)->CanCountUniversal());
}

//----------------------------------------------------------------------
size_t CConcSession::GetOffsetHint(const size_t StartHitNo) const {
    return min(m_ResultOffset + m_Hits.size(), StartHitNo + m_ResultLimit);
}

//----------------------------------------------------------------------
string CConcSession::GetSortKeyHint(const size_t StartHitNo) const {
    if (IsCountSort(m_SortOrder))
        return string();

    size_t HitNo = GetOffsetHint(StartHitNo);
    HitNo -= min(HitNo, m_ResultOffset);
    if (HitNo == 0)
        return m_ResultMinKey; //-- we don't have any hits; propagate the last requested hint-key

    if (m_bSortByString)
        return m_Hits[HitNo - 1].m_SortKey.s;
    else
        return int2hex(m_Hits[HitNo - 1].m_SortKey.i);
}

//----------------------------------------------------------------------
string CConcSession::GetHitIds() const {
    if (IsCountSort(m_SortOrder))
        return GetCountIds();

    string Result;
    for (size_t i = 0; i < m_Hits.size(); i++) {
        const CHit &h = m_Hits[i];
        Result += Format("\t%i -0 ", i + m_ResultOffset); //-- HitId, OrderId (for ddc < v2.0.19)
        if (m_bSortByString) {
            //-- string-based sort
            Result.append(h.m_SortKey.s, 0, DDC_SORTKEY_MAXLEN - 1);
        } else {
            //-- integer-based sort
            Result += int2hex(m_Hits[i].m_SortKey.i);
        }
    }
    return Result;
}

//----------------------------------------------------------------------
string CConcSession::GetCountIds() const {
    string Result;
    for (vector<CHit>::const_iterator hi = m_Hits.begin(); hi != m_Hits.end(); ++hi) {
        //-- "HitId OrderId" for ddc < v2.0.19
        //-- "HitId    -0"   for ddc >=v2.0.19, context-queries
        //-- "HitCount -0"   for ddc >=v2.0.23, count-queries
        //-- for ddc >=v2.0.38: omit extraneous spaces from count-key ids
        Result += Format("\t%zi -0 ", hi->m_Value.m_Count);
        Result.append(hi->m_SortKey.s, 0, DDC_SORTKEY_MAXLEN - 1);
    }
    return Result;
}

//----------------------------------------------------------------------
bool CConcSession::TryToGetFromCache(const string &Query, uint32_t &EndHitNo) {
    return m_pSessionContext ? m_pSessionContext->CacheGet(*this, Query, EndHitNo) : false;
}

//----------------------------------------------------------------------
void CConcSession::SaveToCache(const string &Query, vector<size_t>::const_iterator start,
                               vector<size_t>::const_iterator end) {
    if (m_pSessionContext)
        m_pSessionContext->CacheSet(*this, Query, start, end);
}

//----------------------------------------------------------------------
DDCErrorEnum CConcSession::GetHits(const string &QueryStr, uint32_t &EndHitNo) {
    if (!m_pQueryCompiler->ParseQuery(QueryStr))
        return errParseError;

    m_pQueryCompiler->CheckSatisfiable(); //-- just flag compiler unsatisfiable queries

    if (!m_pQueryCompiler->Compile())
        return errParseError;
    
    return GetHits(m_pQueryCompiler->m_pQuery, EndHitNo, QueryStr);
}

//----------------------------------------------------------------------
DDCErrorEnum CConcSession::GetHits(CQuery *QueryRoot, uint32_t &EndHitNo) {
    string QueryStr = QueryRoot ? (QueryRoot->toString() + QueryRoot->optionsToString()) : string();
    return GetHits(QueryRoot, EndHitNo, QueryStr);
}

//----------------------------------------------------------------------
DDCErrorEnum CConcSession::GetHits(CQuery *QueryRoot, uint32_t &EndHitNo, const string &QueryStr) {
    ClearQueryResults();
    if (!QueryRoot)
        return errParseError;

    SetHitType();

    try {
        size_t StartHitNo = EndHitNo; //-- EndHitNo as input parameter

        if (QueryRoot->m_Compiler && !QueryRoot->m_Compiler->m_bSatisfiable) {
            //-- unsatisfiable query : ignore
            ddcLogDebug(Format("unsatisfiable query detected: %s", QueryStr.c_str()));
            return errNone;
        }
        else if (!TryToGetFromCache(QueryStr, EndHitNo)) {
            //-- new query, cache-miss, or re-evaluation required (e.g. high-offset page request)
            DDCErrorEnum result = GetAllHits(QueryRoot, StartHitNo,
                                             max(StartHitNo + m_ResultLimit, m_pConcordance->m_MaxCachedHitsCount));
            if (result != errNone)
                return result;

            vector<size_t> HitsIndex;
            HitsIndex.reserve(m_Hits.size());
            for (size_t i = 0; i < m_Hits.size(); i++)
                HitsIndex.push_back(i);

            HIT_SORT_DEBUG(dumpHits(Format("DEBUG[pre-sort;order=%d]: m_Hits", m_SortOrder), m_Hits));

            //-- re-sort hits here, since they might be drawn from different corpus periods
            if (m_bPrune && m_SortOrder > 0) {
                //-- ascending prune-sort
                stable_sort(HitsIndex.begin(), HitsIndex.end(), IsLessByHitSortKeyStr(m_Hits));
            } else if (m_bPrune && m_SortOrder < 0) {
                //-- descending prune- sort
                stable_sort(HitsIndex.rbegin(), HitsIndex.rend(), IsLessByHitSortKeyStr(m_Hits));
            } else if (m_SortOrder > 0) {
                //-- ascending sort
                stable_sort(HitsIndex.begin(), HitsIndex.end(), IsLessByHitSortKey(m_Hits));
            } else if (m_SortOrder < 0) {
                //-- descending sort
                stable_sort(HitsIndex.rbegin(), HitsIndex.rend(), IsLessByHitSortKey(m_Hits));
            } else {
                //-- no sort
                ;
            }
            //HIT_SORT_DEBUG( dumpHitIndex("DEBUG[post-sort]: HitsIndex", HitsIndex, "m_Hits", m_Hits) );

            if (m_ResultOffset == 0) {
                //-- only cache results starting at offset 0 (i.e. not if we did any key-based pruning)
                SaveToCache(QueryStr, HitsIndex.begin(), HitsIndex.end());
            }

            //-- sanity check
            if (StartHitNo < m_ResultOffset)
                throw CDDCExpc(errRuntime, "StartHitNo=%zd not available (pre-pruning overtrimmed m_ResultOffset=%zd)",
                            StartHitNo, m_ResultOffset);

            //-- trim front of HitsIndex for non-trivial StartHitNo (this probably won't really help much except for bandwidth)
            if (StartHitNo > m_ResultOffset) {
                size_t nTrim = min(StartHitNo - m_ResultOffset, HitsIndex.size());
                HitsIndex.erase(HitsIndex.begin(), HitsIndex.begin() + nTrim);
                m_ResultOffset += nTrim;
                HIT_TRIM_DEBUG(ddcLogDebug(
                                   Format("TRIM-FRONT[final,ResultOffset=%zd,StartHitNo=%zd]: trimmed %zd/%zd initial hit(s)",
                                          m_ResultOffset, StartHitNo, nTrim, nTrim + HitsIndex.size()))
                    );

            }
            //HIT_SORT_DEBUG( dumpHitIndex(Format("DEBUG[post-trim;offset=%zd]: HitsIndex", m_ResultOffset), HitsIndex, "m_Hits", m_Hits) );

            size_t End = min((StartHitNo - m_ResultOffset + m_ResultLimit), HitsIndex.size());
            CQueryResultIndex(*this, HitsIndex).Apply(*this, (StartHitNo - m_ResultOffset), End);

            EndHitNo = m_ResultOffset + End; //-- update EndHitNo as output parameter
            //HIT_SORT_DEBUG( dumpHits(Format("DEBUG[GetHits/3]: m_Hits", m_ResultOffset), m_Hits) );
        }


        return errNone;

    }
    catch (CExpc &C) {
        m_ErrorStr = string("Error: ") + string(C.what());
        ErrorMessage(m_ErrorStr);
        ddcLogError(m_ErrorStr);
        throw;
        //return (DDCErrorEnum)ddcExpcCode(C)==errNone ? errRuntime : (DDCErrorEnum)ddcExpcCode(C);
    }
    catch (exception &e) {
        m_ErrorStr = string("Exception: ") + e.what();
        ErrorMessage(m_ErrorStr);
        ddcLogError(m_ErrorStr);
        throw;
        //return errRuntime;
    }
    catch (...) {
        m_ErrorStr = string("Unhandled exception");
        ErrorMessage(m_ErrorStr);
        ddcLogError(m_ErrorStr);
        throw;
        //return errOther;
    }

};

//----------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
DDCErrorEnum CConcSession::SimpleQuery(const string &Query, uint32_t &EndHitNo, uint32_t &HitsCount) {
    uint32_t StartHitNo = EndHitNo;
    try {
        DDCErrorEnum result = GetHits(Query, EndHitNo);
        if (result != errNone)
            return result;

        HitsCount = m_AllHitsCount;
        //HIT_SORT_DEBUG( dumpHits("DEBUG[SimpleQuery:pre-generate] m_Hits", m_Hits) );

        result = GenerateHitStrings(StartHitNo);
        if (result != errNone)
            return result;


        if (m_ResultFormat == DDC_ResultHTML) {
            if (m_pConcordance->m_bShowNumberOfRelevantDocuments)
                m_QueryResultStr =
                    Format("Occurrences %i - %i of %i in %i document(s)<br>", StartHitNo + 1, EndHitNo, HitsCount,
                           m_RelevantDocumentCount) + m_QueryResultStr;
            else
                m_QueryResultStr =
                    Format("Occurrences %i - %i of %i<br>", StartHitNo + 1, EndHitNo, HitsCount) + m_QueryResultStr;
        };

        DecorateQueryResults(GetResultFormatStr(), m_QueryResultStr);

        return errNone;

    }
    catch (CExpc &C) {
        m_ErrorStr = string("Error: ") + string(C.what());
        ErrorMessage(m_ErrorStr);
        ddcLogError(m_ErrorStr);
        throw;
        //return (DDCErrorEnum)ddcExpcCode(C);
    }

};


//----------------------------------------------------------------------
bool
CConcSession::SaveOccurrences(const vector<uint32_t> &ChunkLengths, int ContextSize, const vector<CTokenNo> &Occurrences,
                              const vector<CHit> &Hits, SaveTriggerType SaveTrigger, uint32_t LParam) {
    if (m_pConcordance->m_Indices.empty()) return false;
    assert (Hits.size() == ChunkLengths.size());

    {
        int len = 0;
        for (size_t i = 0; i < ChunkLengths.size(); i++)
            len += ChunkLengths[i];
        if (Occurrences.size() != len) {
            fprintf(stderr, "Fatal Error! Sum of all chunk lengths  is not equal to the number of all occurrences\n");
            return false;
        }
    }


    string Result;
    size_t PosOffset = 0;
    for (int HitNo = 0; HitNo < Hits.size(); HitNo++) {
        size_t ItemsCount = ChunkLengths[HitNo];
        const uint32_t BreakNo = Hits[HitNo].m_BreakNo;

        CTokenNo PositionStart = Occurrences[PosOffset];
        CTokenNo PositionEnd = Occurrences[PosOffset + ItemsCount - 1] + 1;
        string Postfix;
        if (ContextSize != -1) {
            const uint32_t StartHitTokenNo = (BreakNo == 0) ? 0 : GetBreaks()[BreakNo - 1];
            if (StartHitTokenNo + ContextSize <= PositionStart)
                PositionStart -= ContextSize;
            else {
                for (size_t i = 0; i < ContextSize - (PositionStart - StartHitTokenNo); i++)
                    Result += "\"*\";";
                PositionStart = StartHitTokenNo;
            };

            const CTokenNo &EndHitTokenNo = GetBreaks()[BreakNo];
            if (PositionEnd + ContextSize <= EndHitTokenNo)
                PositionEnd += ContextSize;
            else {
                for (size_t i = 0; i < ContextSize - (EndHitTokenNo - PositionEnd); i++)
                    Postfix += "\"*\";";
                PositionEnd = EndHitTokenNo;
            };
        };


        vector<COutputToken> Tokens;
        if (!m_pConcordance->GetTokenIndex()->GetTokensFromStorage(PositionStart, PositionEnd, Tokens)) {
            concord_daemon_log(Format("Error! Cannot read hit number %i \n", BreakNo));
            return false;
        };

        for (size_t i = 0; i < Tokens.size(); i++) {
            Result += "\"";
            Result += Tokens[i].m_TokenStr;
            Result += "\";";
        };
        Result += Postfix;
        Result += "\n";

        if (Result.length() > DDC_STATIC_BUFLEN) {
            if (!SaveTrigger(Result, LParam))
                return false;

            Result = "";
        };

        PosOffset += ItemsCount;

    };

    if (!Result.empty())
        if (!SaveTrigger(Result, LParam))
            return false;

    return true;
};


//----------------------------------------------------------------------
DDCErrorEnum
CConcSession::GetOccurrences(const string &Query, int ContextSize, SaveTriggerType SaveTrigger, uint32_t LParam) {
    try {
        if (!(m_pQueryCompiler->ParseQuery(Query) && m_pQueryCompiler->Compile()))
            return errParseError;

        SetHitType();

        if (!m_pQueryCompiler->m_pQuery->m_Node->m_bAtomic) {
            fprintf(stderr, "Error! The query is not a pattern!\n");
            return errParseError;
        };

        for (m_CurrentSearchPeriodNo = 0;
             m_CurrentSearchPeriodNo < m_pConcordance->GetSearchPeriodsCount(); m_CurrentSearchPeriodNo++) {
            CQueryNode *Node = (CQuerySequenceNode *) m_pQueryCompiler->m_pQuery->m_Node;
            Node->EvaluateWithoutHits();


            Node->ConvertOccurrencesToHitsForPatterns(false);
            if (!SaveOccurrences(Node->m_ChunkLengths, ContextSize, Node->m_Occurrences, Node->m_Hits, SaveTrigger,
                                 LParam)) {
                break;
            }

            if (m_bStdout)
                fprintf(stderr, " %zi/%zi             \r", m_CurrentSearchPeriodNo,
                        m_pConcordance->GetSearchPeriodsCount());
        };

        if (m_bStdout)
            fprintf(stderr, " %zi/%zi             \n", m_CurrentSearchPeriodNo,
                    m_pConcordance->GetSearchPeriodsCount());

        //m_pQueryCompiler->DeleteTree();

        return errNone;
    }
    catch (CExpc &C) {
        m_ErrorStr = string("Error: ") + string(C.what());
        ErrorMessage(m_ErrorStr);
        ddcLogError(m_ErrorStr);
        return (DDCErrorEnum) ddcExpcCode(C);
    }
};

//----------------------------------------------------------------------
DDCFormatTypeEnum CConcSession::GetResultFormatByString(const string &ResultTypeStr) {
    string q = ResultTypeStr;
    EngMakeUpper(q);
    if (q == "JSON") return DDC_ResultJson;
    else if (q == "HTML") return DDC_ResultHTML;
    else if (q == "DOCIDS") return DDC_ResultDocIds;
    else if (q == "TABLE") return DDC_ResultTable;
    else return DDC_ResultText;
}

//----------------------------------------------------------------------
void CConcSession::SetResultFormat(string ResultTypeStr) {
    m_ResultFormat = GetResultFormatByString(ResultTypeStr);
}

//----------------------------------------------------------------------
string CConcSession::GetResultFormatStr() const {
    switch (m_ResultFormat) {
        case DDC_ResultJson:
            return "json";
        case DDC_ResultHTML:
            return "html";
        case DDC_ResultTable:
            return "table";
        case DDC_ResultDocIds:
            return "docids";
        default:
            return "text";
    };
}


//----------------------------------------------------------------------
const ddcBreakVector &CConcSession::GetBreaks() const {
    assert (m_pBreaks != 0);
    return *m_pBreaks;
}

//----------------------------------------------------------------------
void CConcSession::SetHitType() {
    assert(m_pQueryCompiler != NULL);
    assert(m_pQueryCompiler->m_pQuery != NULL);
    string BreakName = m_pQueryCompiler->m_pQuery->m_Options->m_HitTypeStr;
    int TextAreaNo = m_pQueryCompiler->m_pQuery->m_Options->m_TextAreaNo;

    if (TextAreaNo != UnknownTextAreaNo)
        m_pBreaks = m_pConcordance->GetBreaksByName(PredefinedTextAreaBreakName);
    else
        m_pBreaks = m_pConcordance->GetBreaksByName(BreakName);
}

//----------------------------------------------------------------------
int CConcSession::GetTextArea() const {
    assert(m_pQueryCompiler != NULL);
    assert(m_pQueryCompiler->m_pQuery != NULL);
    return m_pQueryCompiler->m_pQuery->m_Options->m_TextAreaNo;
}

//----------------------------------------------------------------------
void CConcSession::ClearQueryResults() {
    CQueryResult::ClearQueryResults();
    ClearString(m_QueryResultStr);
    ClearString(m_ErrorStr);
    m_ResultOffset = 0;
}

//----------------------------------------------------------------------
HitSortOrderEnum CConcSession::HitSortOrder() const {
    return m_SortOrder;
}

//----------------------------------------------------------------------
void CConcSession::SetTimeOut(int TimeOut) {
    if (TimeOut != -1) {
        time_t t;
        time(&t);
        m_QueryEndTime = t + TimeOut;
    } else
        m_QueryEndTime = TheEndOfTheWorld;
}


//----------------------------------------------------------------------
void CConcSession::ClearQuery() {
    m_pQueryCompiler->CleanParser();
}

//----------------------------------------------------------------------
bool CConcSession::HasRankOrderOperator() const {
    for (size_t FilterNo = 0; FilterNo < m_pQueryCompiler->m_pQuery->m_Options->m_Filters.size(); FilterNo++) {
        const CDDCFilterWithBounds &F = m_pQueryCompiler->m_pQuery->m_Options->m_Filters[FilterNo];
        if ((F.m_FilterType == LessByRank) || (F.m_FilterType == GreaterByRank))
            return true;
    }
    return false;
}

//----------------------------------------------------------------------
bool CConcSession::HasMatchIdOperator() const {
    return m_pQueryCompiler->m_pQuery->HasMatchId();
}

//----------------------------------------------------------------------
string CConcSession::CanonicalQueryString(const string &Query) {
    ClearQueryResults();
    if (!m_pQueryCompiler || !m_pQueryCompiler->ParseQuery(Query)) {
        m_ErrorStr = "parse error";
        return string("");
    }
    return m_pQueryCompiler->QueryToString();
}

//----------------------------------------------------------------------
string CConcSession::JsonQueryString(const string &Query) {
    ClearQueryResults();
    if (!m_pQueryCompiler || !m_pQueryCompiler->ParseQuery(Query)) {
        m_ErrorStr = "parse error";
        return string("");
    }
    return m_pQueryCompiler->QueryToJson();
}

//----------------------------------------------------------------------
void CConcSession::SetRandomSeed(unsigned int seed1) const {
    m_pRandom->set_seed(m_RandomSeed + seed1);
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
