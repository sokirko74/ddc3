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

#include "QCount.h"
#include "QueryCompiler.h"
#include "ConcHolder.h"

//#define DEBUG_NCOUNT 1
//#undef DEBUG_NCOUNT

//==============================================================================
// Sorting utility structures

//==============================================================================
//! comparison operator for hits on CHit::m_FileNo (for std::sort)
struct IsLessByFileNo {
    IsLessByFileNo() {};

    bool operator()(const CHit &h1, const CHit &h2) const { return h1.m_FileNo < h2.m_FileNo; };
};

//==============================================================================
//! comparison operator for hits on CHit::m_BreakNo (for std::sort)
struct IsLessByBreakNo {
    IsLessByBreakNo() {};

    bool operator()(const CHit &h1, const CHit &h2) const { return h1.m_BreakNo < h2.m_BreakNo; };
};


//==============================================================================
//! direct comparison operator for hits on CHit::m_SortKey.i (for std::sort)
struct HitLessByCountValue {
    bool operator()(const CHit &a, const CHit &b) const {
        return a.m_Value.m_Count < b.m_Value.m_Count;
    };
};

//==============================================================================
// Hit size utilities

//----------------------------------------------------------------------
/** get initial occurrence number of \a Hit */
static inline DWORD HitOccurrenceStart(const CHit &Hit, const CConcHolder *holder) {
    DWORD hitno = &Hit - &*(holder->m_Hits.begin());
    return (hitno == 0 ? 0 : holder->m_Hits[hitno - 1].m_HighlightOccurrenceEnd);
};

//----------------------------------------------------------------------
/** get first occurence offset after \a Hit (upper bound) */
static inline DWORD HitOccurrenceEnd(const CHit &Hit, const CConcHolder *holder) {
    //return Hit.m_HighlightOccurrenceEnd;
    const vector<CTokenNo> &occurrences = holder->m_HighlightOccurs;
    return Hit.m_HighlightOccurrenceEnd >= occurrences.size() ? occurrences.size() : Hit.m_HighlightOccurrenceEnd;
};


//==============================================================================
// CQCountKeyExpr

//----------------------------------------------------------------------
bool CQCountKeyExpr::Compile(CQueryCompiler *compiler) {
    SetCompiler(compiler);
    return true;
}

//----------------------------------------------------------------------
string &CQCountKeyExpr::Evaluate(const CHit &Hit) {
    throw CExpc(errRuntime,
                Format("abstract method CQCountKeyExpr::Evaluate() called for class %s", typeid(*this).name()));
};

//==============================================================================
// CQCountKeyExpr ...

//----------------------------------------------------------------------
string &CQCountKeyExprFileId::Evaluate(const CHit &Hit) {
    if (Hit.m_FileNo != m_CurFile) {
        sprintf(buf, "%d", Hit.m_FileNo);
        m_CurKey = buf;
        m_CurFile = Hit.m_FileNo;
    }
    return m_CurKey;
}

//----------------------------------------------------------------------
bool CQCountKeyExprIndexed::Compile(CQueryCompiler *compiler) {
    CQCountKeyExpr::Compile(compiler);
    assert(compiler->m_pHolder != NULL);
    assert(compiler->m_pHolder->m_pConcordance != NULL);
    m_pConcordance = compiler->m_pHolder->m_pConcordance;
    return true;
}

//----------------------------------------------------------------------
string &CQCountKeyExprFileName::Evaluate(const CHit &Hit) {
    if (Hit.m_FileNo != m_CurFile) {
        m_CurKey = m_pConcordance->GetShortFilename(Hit.m_FileNo);
        m_CurFile = Hit.m_FileNo;
    }
    return m_CurKey;
}

//----------------------------------------------------------------------
bool CQCountKeyExprDate::Compile(CQueryCompiler *compiler) {
    CQCountKeyExprIndexed::Compile(compiler);
    m_pDates = &(m_pConcordance->m_BiblIndex.GetDates());
    return true;
}

//----------------------------------------------------------------------
string &CQCountKeyExprDate::Evaluate(const CHit &Hit) {
    if (Hit.m_FileNo != m_CurFile) {
        int2date((*m_pDates)[Hit.m_FileNo], &m_year, &m_month, &m_day);
        sprintf(buf, "%u-%02u-%02u", m_year, m_month, m_day);
        m_CurKey = buf;
        m_CurFile = Hit.m_FileNo;
    }
    return m_CurKey;
}

//----------------------------------------------------------------------
bool CQCountKeyExprDateSlice::Compile(CQueryCompiler *compiler) {
    CQCountKeyExprDate::Compile(compiler);
    if (!m_slice) m_slice = 1; //-- avoid divide-by-zero errors
    return true;
}

//----------------------------------------------------------------------
string &CQCountKeyExprDateSlice::Evaluate(const CHit &Hit) {
    if (Hit.m_FileNo != m_CurFile) {
        int2date((*m_pDates)[Hit.m_FileNo], &m_year, NULL, NULL);
        m_year /= m_slice;
        sprintf(buf, "%u", m_slice * m_year);
        m_CurKey = buf;
        m_CurFile = Hit.m_FileNo;
    }
    return m_CurKey;
}

//----------------------------------------------------------------------
bool CQCountKeyExprBibl::Compile(CQueryCompiler *compiler) {
    CQCountKeyExprIndexed::Compile(compiler);
    m_Bibl = m_pConcordance->m_BiblIndex.GetFreeBiblIndexConst(m_Label);
    if (m_Bibl == NULL)
        throw CExpc(errRuntime,
                    Format("CQCountKeyExprBibl()::Compile(): cannot use unknown bibliographic attribute `%s' as count-key",
                           m_Label.c_str()));
    return true;
}

//----------------------------------------------------------------------
string &CQCountKeyExprBibl::Evaluate(const CHit &Hit) {
    if (m_CurFile != Hit.m_FileNo) {
        m_CurKey = m_Bibl->GetStringValue(Hit.m_FileNo);
        m_CurFile = Hit.m_FileNo;
    }
    return m_CurKey;
};

//==============================================================================
// CQCountKeyExprRegex

//----------------------------------------------------------------------
CQCountKeyExprRegex::~CQCountKeyExprRegex() {
    if (m_Src) delete m_Src;
    if (m_Regex) delete m_Regex;
}

//----------------------------------------------------------------------
ddcObjectList CQCountKeyExprRegex::Children() const {
    ddcObjectList kids(CQuery::Children());
    if (m_Src) kids.push_back(m_Src);
    return kids;
}

//----------------------------------------------------------------------
void CQCountKeyExprRegex::DisownChildren() {
    CQuery::DisownChildren();
    m_Src = NULL;
}

//----------------------------------------------------------------------
bool CQCountKeyExprRegex::Compile(CQueryCompiler *compiler) {
    if (!m_Src || !m_Src->Compile(compiler)) return false;
    CQCountKeyExprIndexed::Compile(compiler);
    m_Regex = new RML_RE(m_Pattern, m_pConcordance->GetRegexOptions());
    //m_Pcre  = m_Regex->Compile(RML_RE::UNANCHORED);
    isGlobal = (m_Modifiers.find('g') != m_Modifiers.npos);
    return true;
}

//----------------------------------------------------------------------
string &CQCountKeyExprRegex::Evaluate(const CHit &Hit) {
    if (!m_Src->CanCountByFile() || Hit.m_FileNo != m_CurFile)
        EvaluateRegex(Hit, m_Src->Evaluate(Hit));
    return m_CurKey;
}

//----------------------------------------------------------------------
string CQCountKeyExprRegex::toString() {
    return string("(") + m_Src->toString() + " ~ s/" + m_Pattern + "/" + m_Replacement + "/" + m_Modifiers + ")";
}

//----------------------------------------------------------------------
string CQCountKeyExprRegex::jsonData() {
    return "\"Src\":" + m_Src->toJson() + ",\"Pattern\":" + jsonStr(m_Pattern) + ",\"Replacement\":" +
           jsonStr(m_Replacement) + ",\"Modifiers\":" + jsonStr(m_Modifiers);
}

//==============================================================================
// CQCountKeyExprToken

//----------------------------------------------------------------------
bool CQCountKeyExprToken::Compile(CQueryCompiler *compiler) {
    CQCountKeyExprIndexed::Compile(compiler);

    /* sanity check */
    if (!compiler->m_pHolder->m_pConcordance->m_bAllowCountByTokenAttributes)
        throw CExpc(errParseError, "counting by token attribute `%s' disabled", this->toString().c_str());

    /* get index */
    if (m_IndexName.empty())
        m_IndexName = "Token";

    m_pIndex = compiler->m_pHolder->m_pConcordance->GetIndexByAlias(m_IndexName);
    if (!m_pIndex)
        throw CExpc(errParseError, "CQCountKeyExprToken::Compile(): unknown index `%s'", m_IndexName.c_str());

    return true;
}

//----------------------------------------------------------------------
string &CQCountKeyExprToken::Evaluate(const CHit &Hit) {
    const CConcHolder *holder = m_Compiler->m_pHolder;
    const vector<CTokenNo> &occurrences = holder->m_HighlightOccurs;
    const ddcBreakVector &breaks = holder->GetBreaks();
    const vector<BYTE> &matchids = holder->m_HighlightIds;

    //-- get context anchor occurrence-index occur_i
    DWORD occ = HitOccurrenceStart(Hit, holder);
    if (m_MatchId != 0) {
        DWORD occ_end = HitOccurrenceEnd(Hit, holder);
        for (; occ < occ_end && matchids[occ] != m_MatchId; ++occ);
        if (occ >= occ_end)
            occ = (DWORD) -1;
    }

    //-- formerly EvaluateOccurrence()
    try {
        //-- check for valid occurrence
        if (occ >= occurrences.size() || (m_MatchId != 0 && matchids[occ] != m_MatchId))
            throw CQCountKeyBadOccurrence("id-mismatch for occurrence in CQCountKeyExprToken::Evaluate()");

        //-- get break limits and token id
        DWORD StartTokenNo = (Hit.m_BreakNo == 0) ? 0 : breaks[Hit.m_BreakNo - 1];
        DWORD EndTokenNo = breaks[Hit.m_BreakNo];
        CTokenNo tok = occurrences[occ] + m_Offset;
        DWORD indexKey;

        if (tok >= StartTokenNo && tok < EndTokenNo && (indexKey = m_pIndex->GetTokenIndexId(tok)) != DWORD_MAX) {
            //-- usual case: within target break and with a valid item id
            m_CurKey = m_pIndex->GetIndexItemStr(m_pIndex->m_Index[indexKey]);
        } else {
            //-- break-overflow (EOS etc) or invalid key item: throw exception
            throw CQCountKeyBadOccurrence("bad occurrence in CQCountKeyExprToken::Evaluate()");
        }
    }
    catch (CQCountKeyBadOccurrence) {
        //-- break-overflow (EOS etc) or invalid key item: return empty count-key
        m_CurKey.clear();
    }

    return m_CurKey;
}

//----------------------------------------------------------------------
string CQCountKeyExprToken::toString() {
    string s("$");
    s += m_IndexName;
    if (m_MatchId != 0)
        s += Format(" =%hhu", m_MatchId);
    if (m_Offset != 0)
        s += Format(" %+d", m_Offset);
    return s;
}

//----------------------------------------------------------------------
string CQCountKeyExprToken::jsonData() {
    return string("\"IndexName\":") + jsonStr(m_IndexName) +
           Format(",\"MatchId\":%hhu,\"Offset\":%d", m_MatchId, m_Offset);
}


//==============================================================================
// CQCountKeyExprList


//----------------------------------------------------------------------
CQCountKeyExprList::~CQCountKeyExprList() {
    this->Clear();
}

//----------------------------------------------------------------------
void CQCountKeyExprList::Clear() {
    for (vector<CQCountKeyExpr *>::iterator xi = m_Exprs.begin(); xi != m_Exprs.end(); xi++) {
        if (*xi) delete *xi;
    }
    m_Exprs.clear();
};

//----------------------------------------------------------------------
ddcObjectList CQCountKeyExprList::Children() const {
    ddcObjectList kids(CQuery::Children());
    for (vector<CQCountKeyExpr *>::const_iterator xi = m_Exprs.begin(); xi != m_Exprs.end(); xi++) {
        if (*xi) kids.push_back((ddcObject *) (*xi));
    }
    return kids;
}

//----------------------------------------------------------------------
void CQCountKeyExprList::DisownChildren() {
    CQuery::DisownChildren();
    m_Exprs.clear();
}

//----------------------------------------------------------------------
bool CQCountKeyExprList::CanCountByFile() const {
    for (vector<CQCountKeyExpr *>::const_iterator xi = m_Exprs.begin(); xi != m_Exprs.end(); xi++) {
        if (*xi && !(*xi)->CanCountByFile()) return false;
    }
    return true;
}

//----------------------------------------------------------------------
BYTE CQCountKeyExprList::GetMatchId() const {
    BYTE matchId = 0;
    for (vector<CQCountKeyExpr *>::const_reverse_iterator xi = m_Exprs.rbegin(); xi != m_Exprs.rend(); xi++) {
        if (*xi && (matchId = (*xi)->GetMatchId()) != 0)
            break;
    }
    return matchId;
}

//----------------------------------------------------------------------
bool CQCountKeyExprList::Compile(CQueryCompiler *compiler) {
    SetCompiler(compiler);

    if (m_Exprs.empty()) {
        //-- sanity check: ensure at least 1 key field
        this->PushKey(new CQCountKeyExprConstant("*"));
    }

    bool rc = true;
    for (vector<CQCountKeyExpr *>::iterator xi = m_Exprs.begin(); rc && xi != m_Exprs.end(); xi++) {
        rc = rc && (*xi)->Compile(compiler);
    }

    return rc;
};

//----------------------------------------------------------------------
string &CQCountKeyExprList::Evaluate(const CHit &Hit) {
    m_Key.clear();
    for (vector<CQCountKeyExpr *>::iterator xi = m_Exprs.begin(); xi != m_Exprs.end(); xi++) {
        if (xi != m_Exprs.begin()) m_Key.push_back(globalCountKeyDelim);
        //m_Key.push_back(' ');  //-- this is nice for CConcHolder::GetHitIds() debugging, but ugly everywhere else: lose it!
        m_Key += (*xi)->Evaluate(Hit);
    }
    return m_Key;
};

//----------------------------------------------------------------------
string CQCountKeyExprList::toString() {
    string s("");
    for (vector<CQCountKeyExpr *>::iterator xi = m_Exprs.begin(); xi != m_Exprs.end(); xi++) {
        if (xi != m_Exprs.begin()) s.push_back(',');
        s += (*xi)->toString();
    }
    return s;
}

//----------------------------------------------------------------------
string CQCountKeyExprList::jsonData() {
    string s("\"Exprs\":[");
    for (vector<CQCountKeyExpr *>::iterator xi = m_Exprs.begin(); xi != m_Exprs.end(); xi++) {
        if (xi != m_Exprs.begin()) s.push_back(',');
        s += (*xi)->toJson();
    }
    s.push_back(']');
    return s;
}

//======================================================================
// CQCount

//--------------------------------------------------------------
CQCount::~CQCount() {
    Clear(true);
}

//--------------------------------------------------------------
void CQCount::ClearNode() {
    if (m_dtr) m_dtr->ClearNode();
    if (m_keys) m_keys->ClearNode();
    CQuery::ClearNode();
}

//--------------------------------------------------------------
void CQCount::Clear(bool deep) {
    ClearNode();
    ClearOptions();
    m_Counts.clear();
    m_CountSample = 0;
    if (deep) {
        if (m_dtr) delete m_dtr;
        if (m_keys) delete m_keys;
    }
    m_dtr = NULL;
}

//--------------------------------------------------------------
ddcObjectList CQCount::Children() const {
    ddcObjectList kids(CQuery::Children());
    if (m_dtr) kids.push_back(m_dtr);
    if (m_keys) kids.push_back(m_keys);
    return kids;
}

//--------------------------------------------------------------
void CQCount::DisownChildren() {
    CQuery::DisownChildren();
    m_dtr = NULL;
    m_keys = NULL;
}

//--------------------------------------------------------------
BYTE CQCount::GetMatchId() const {
    BYTE matchId = 0;
    if (m_keys && (matchId = m_keys->GetMatchId()) != 0) return matchId;
    if (m_dtr && (matchId = m_dtr->GetMatchId()) != 0) return matchId;
    return matchId;
}

//--------------------------------------------------------------
bool CQCount::Compile(CQueryCompiler *compiler) {
    SetCompiler(compiler);

    //-- sanity check(s)
    if (!m_dtr)
        throw CExpc(errParseError, "no argument conditions specified for count-query `%s'", this->toString().c_str());

    //-- compile daughter(s)
    if (!m_dtr->CompileOptions(compiler) || !m_dtr->Compile(compiler))
        throw CExpc(errParseError, "could not compile sub-query `%s' for count-query", m_dtr->toString().c_str());

    //-- adopt daughter options if required (copy for count-by-break hack)
    if (!m_Options && m_dtr->m_Options) {
        m_Options = m_dtr->m_Options->Clone();
    }

    //-- adopt appropriate daughter options (for break-counting)
    if (m_Options && m_dtr->m_Options) {
        m_Options->m_HitTypeStr = m_dtr->m_Options->m_HitTypeStr;
    }

    //-- compile key expression(s)
    if (!m_keys) m_keys = new CQCountKeyExprList();
    if (!m_keys->Compile(compiler))
        throw CExpc(errParseError, "could not compile key expression(s) `%s' for count-query",
                    m_keys->toString().c_str());

    //-- reset temporaries
    m_Counts.clear();
    m_CountSample = 0;

    //-- child methods hook in here
    return true;
}

//--------------------------------------------------------------
void CQCount::Evaluate() {
    //-- sanity check(s)
    assert(m_dtr != NULL);
    assert(m_Compiler != NULL);
    assert(m_Compiler->m_pHolder != NULL);
    assert(m_Compiler->m_pHolder->m_pConcordance != NULL);
}

//--------------------------------------------------------------
bool CQCount::CanCountUniversal() {
    return (typeid(*m_dtr) == typeid(CQTokAny)
            && (!m_dtr->m_Options || m_dtr->m_Options->CanFilterByFile())
            && (!m_keys || m_keys->CanCountByFile()));
}

//--------------------------------------------------------------
bool CQCount::CanCountByFile() const {
    return (!m_keys || m_keys->CanCountByFile());
}

//--------------------------------------------------------------
void CQCount::CountUniversal(CQueryResult &Result, size_t Limit) {
    //-- sanity checks
    this->Evaluate();

    //-- common variables
    CQuery *qRoot = m_dtr;
    CQCountKeyExprList *keys = m_keys;
    m_CountSample = 0;

    //-- count(* ...) query: do memory-optimized computation
    CConcordance *ix = m_Compiler->m_pHolder->m_pConcordance;
    const ddcBreakVector &fbreaks = ix->GetFileBreaks();
    const CMaskedFileSet &fmasked = ix->m_MaskedFiles;
    CMaskedFileSet::const_iterator fmaski = fmasked.begin();
    DWORD nfiles = ix->GetCorpusFilesCount();
    CHit hit;
    string key;
    size_t n;

    assert(nfiles <= fbreaks.size()); //-- sanity check

    if (qRoot->m_Options->m_bSeparateHits) {
        //-- count(* #sep): count tokens
        CTokenNo fw_begin = 0, fw_end;
        for (CFileNo f = 0; f < nfiles && m_CountSample < m_sample; ++f, fw_begin = fw_end) {
            fw_end = fbreaks[f];
            if (fmaski != fmasked.end() && f == *fmaski) {
                //-- don't count tokens in masked files
                ++fmaski;
                continue;
            }
            if (ix->m_BiblIndex.FileMatches(f, qRoot->m_Options->m_Filters)) {
                hit.m_FileNo = f;
                key = keys->Evaluate(hit);
                n = (fw_end - fw_begin);
                m_Counts[key] += n;
                m_CountSample += n;
            }
        }
    } else {
        //-- count(* #join): count selected breaks
        const CHitBorders::CBreakCollection *sbreaks = ix->GetBreakCollectionByName(qRoot->m_Options->m_HitTypeStr);
        CFileNo f = 0, n = 1;
        CTokenNo fw_end = fbreaks[f];
        for (ddcBreakVector::const_iterator bi = sbreaks->m_BreakOffsets.begin();
             bi != sbreaks->m_BreakOffsets.end() && m_CountSample < m_sample; ++bi, ++n) {
            if (*bi >= fw_end) {
                //-- new file
                if (fmaski != fmasked.end() && f == *fmaski) {
                    ++fmaski;
                } else if (n > 0 && ix->m_BiblIndex.FileMatches(f, qRoot->m_Options->m_Filters)) {
                    hit.m_FileNo = f;
                    key = keys->Evaluate(hit);
                    m_Counts[key] += n;
                    m_CountSample += n;
                }
                do {
                    ++f;
                    fw_end = fbreaks[f];
                } while (*bi >= fw_end);
                n = 0;
            }
        }
    }

    this->ConvertCountsToHits(Result, Limit);
}

//--------------------------------------------------------------
void CQCount::CountLocal(CQueryResult &Result, size_t Limit) {
    //-- sanity checks
    this->Evaluate();

    //-- common variables
    //CConcHolder      *holder = (CConcHolder*)m_Compiler->m_pHolder;
    CQuery *qRoot = m_dtr;
    CQCountKeyExprList *keys = m_keys;

    //-- counting guts
    if (keys->CanCountByFile()) {
        //-- counting guts: file-level
#if DEBUG_NCOUNT
        fprintf(stderr, "DEBUG_NCOUNT: count-by-file\n");
#endif
        bool isWithinFile = (qRoot->m_Options->m_HitTypeStr == PredefinedFileBreakName);
        DWORD f = (DWORD) -1;
        size_t n = 0;
        string key;

        //-- ensure m_Hits are sorted by file-id
        if (qRoot->m_Options && !qRoot->m_Options->IsTrivialFilter())
            sort(Result.m_Hits.begin(), Result.m_Hits.end(), IsLessByFileNo());

        for (vector<CHit>::const_iterator hi = Result.m_Hits.begin();
             hi != Result.m_Hits.end() && m_CountSample < m_sample; ++hi, ++n) {
            if (hi->m_FileNo != f) {
                //-- next file
                if (n > 0) {
                    m_Counts[key] += (isWithinFile ? 1 : n);
                    m_CountSample += (isWithinFile ? 1 : n);
                }
                n = 0;
                f = hi->m_FileNo;
                key = keys->Evaluate(*hi);
            }
        }
        if (n > 0) {
            m_Counts[key] += (isWithinFile ? 1 : n);
            m_CountSample += (isWithinFile ? 1 : n);
        }
    } else if (m_Options ? m_Options->m_bSeparateHits : qRoot->m_Options->m_bSeparateHits) {
        //-- counting guts: token-level
#if DEBUG_NCOUNT
        fprintf(stderr, "DEBUG_NCOUNT: count-by-token\n");
#endif
        for (vector<CHit>::const_iterator hi = Result.m_Hits.begin();
             hi != Result.m_Hits.end() && m_CountSample < m_sample; ++hi, ++m_CountSample) {
            string &key = keys->Evaluate(*hi);
            ++m_Counts[key];
        }
    } else {
        //-- counting guts: break-level
        //  + this code assumes m_dtr hits are populated with bSeparateHits=true !
#if DEBUG_NCOUNT
        fprintf(stderr, "DEBUG_NCOUNT: count-by-break\n");
#endif
        CConcHolder *holder = (CConcHolder *) m_Compiler->m_pHolder;
        set<string> bkeys;
        vector<CHit>::const_iterator hi, hj;

        //-- ensure m_Hits are sorted by break-id
        if (qRoot->m_Options && !qRoot->m_Options->IsTrivialFilter())
            Result.SortResultsByHitP(IsLessByBreakNo());

        for (hi = Result.m_Hits.begin();
             hi != Result.m_Hits.end() && m_CountSample < m_sample; hi = hj, ++m_CountSample) {
            //-- get set of all break keys
            for (hj = hi; hj != Result.m_Hits.end() && hj->m_BreakNo == hi->m_BreakNo; ++hj) {
                try {
                    bkeys.insert(keys->Evaluate(*hj));
                }
                catch (CQCountKeyBadOccurrence) {
                    continue;
                }
            }

            //-- increment counts for all instantiated keys
            for (set<string>::const_iterator bki = bkeys.begin(); bki != bkeys.end(); ++bki) {
                ++m_Counts[*bki];
            }
            bkeys.clear();
        }
    }

    //-- cleanup period-local count-daughter data
    Result.m_Hits.clear();
    Result.m_HighlightOccurs.clear();
    Result.m_HighlightIds.clear();
    Result.m_AllHitsCount = 0;
    Result.m_DebugInfo.clear();
}

//--------------------------------------------------------------
void CQCount::ConvertCountsToHits(CQueryResult &Result, size_t Limit) {
    /*
    assert(m_Compiler != NULL);
    assert(m_Compiler->m_pHolder != NULL);
    CConcHolder  *holder = (CConcHolder*)m_Compiler->m_pHolder;
    */

    //-- count query: apply bounds
    switch (m_sort) {

        case LessByCountKey:
        case GreaterByCountKey:
            if (!m_lo.empty())
                m_Counts.erase(m_Counts.begin(), m_Counts.lower_bound(m_lo));
            if (!m_hi.empty())
                m_Counts.erase(m_Counts.upper_bound(m_hi), m_Counts.end());
            break;

        case LessByCountValue:
        case GreaterByCountValue: {
            size_t lb = m_lo.empty() ? 0 : strtoul(m_lo.c_str(), NULL, 0);
            size_t ub = m_hi.empty() ? ((size_t) -1) : strtoul(m_hi.c_str(), NULL, 0);
            CCountMap::iterator nxt;
            for (CCountMap::iterator ci = m_Counts.begin(); ci != m_Counts.end(); ci = nxt) {
                nxt = ci;
                ++nxt;
                if (ci->second < lb || ci->second > ub)
                    m_Counts.erase(ci);
            }
        }
            break;

        default:
            break;
    }

    //-- count query: setup m_Hits[]
    // + m_Hits[] for count()-queries encodes element CHit hit.m_Sortkey.s (count-key) and hit.m_Value.m_Count
    //   attributes; used to transport count()-query results in a backwards-compatible manner.
    size_t n = m_sort == NoSort || m_sort == LessByCountKey ? min(Limit, m_Counts.size()) : m_Counts.size();
    Result.m_Hits.clear();
    Result.m_Hits.resize(n);
    vector<CHit>::iterator hi = Result.m_Hits.begin();
    for (CCountMap::const_iterator ci = m_Counts.begin();
         ci != m_Counts.end() && hi != Result.m_Hits.end(); ++ci, ++hi) {
        hi->m_BreakNo = -1;
        hi->m_HighlightOccurrenceEnd = 0;
        hi->m_FileNo = -1;
        hi->m_Value.m_Count = ci->second;
        hi->m_SortKey = ci->first;
    }

    //-- count query: sort hits
    switch (m_sort) {
        case LessByCountValue:
            Result.m_SortOrder = hsoAscendingCountValues;
            stable_sort(Result.m_Hits.begin(), Result.m_Hits.end(), HitLessByCountValue());
            break;
        case GreaterByCountValue:
            Result.m_SortOrder = hsoDescendingCountValues;
            stable_sort(Result.m_Hits.rbegin(), Result.m_Hits.rend(), HitLessByCountValue());
            break;
        case GreaterByCountKey:
            Result.m_SortOrder = hsoDescendingCountKeys;
            reverse(Result.m_Hits.begin(), Result.m_Hits.end());
            break;
        case LessByCountKey:
        default:
            Result.m_SortOrder = hsoAscendingCountKeys;
            break;
    }

    //-- count query: trim hits (apply limit)
    if (Limit < Result.m_Hits.size())
        Result.m_Hits.resize(Limit);


    //-- count query: setup CQueryResult fields
    Result.m_HighlightOccurs.clear();
    Result.m_HighlightIds.clear();
    Result.m_AllHitsCount = m_Counts.size();
    Result.m_bSortByString = 1;
    Result.m_DebugInfo.clear();
}

//--------------------------------------------------------------
string CQCount::toString() {
    string qs("COUNT(" + m_dtr->toString() + m_dtr->optionsToString() + ")" + this->countOptionsToString());
    return qs;
}

//--------------------------------------------------------------
string CQCount::countOptionsToString() {
    string qs;
    if (m_keys && !m_keys->empty()) {
        qs += " #BY[" + m_keys->toString() + "]";
    }
    if (m_sample != DDCDefaultCountSampleSize)
        qs += Format(" #SAMPLE %zi", m_sample);
    if (m_sort != NoSort) {
        string sortstr(" #");
        sortstr += HitSortEnumStrings[m_sort];
        EngMakeUpper(sortstr);
        qs += sortstr;
        if (!m_lo.empty() || !m_hi.empty()) {
            qs.push_back('[');
            if (!m_lo.empty()) qs += sqString(m_lo);
            qs.push_back(',');
            if (!m_hi.empty()) qs += sqString(m_hi);
            qs.push_back(']');
        }
    }
    return qs;
}

//--------------------------------------------------------------
string CQCount::jsonData() {
    string qs("\"Dtr\":" + m_dtr->toJson() + ",\"DtrOptions\":" + m_dtr->optionsToJson());
    if (m_keys && !m_keys->empty()) {
        qs += string(",\"Keys\":") + m_keys->toJson();
    }
    qs += Format(",\"Sample\":%zi", m_sample);
    qs += string(",\"Sort\":") + jsonStr(HitSortEnumNames[m_sort]);
    return qs;
}

//======================================================================
// CQKeys

//--------------------------------------------------------------
CQKeys::~CQKeys() {
    Clear(true);
}

//--------------------------------------------------------------
void CQKeys::ClearNode() {
    if (m_qCount) m_qCount->ClearNode();
    if (m_proxy) m_proxy->ClearNode();
    m_Node = NULL; //-- if defined at all, it should be == m_proxy->m_Node
    CQuery::ClearNode();
}

//--------------------------------------------------------------
void CQKeys::Clear(bool deep) {
    ClearNode();
    ClearOptions();
    if (deep) {
        if (m_qCount) delete m_qCount;
        if (m_proxy) {
            if (m_proxy->m_Options == m_Options)
                m_proxy->m_Options = NULL;
            delete m_proxy;
        }
    }
    m_qCount = NULL;
    m_proxy = NULL;
    m_dtrs.clear();
    //m_tuples.clear();
}

//--------------------------------------------------------------
ddcObjectList CQKeys::Children() const {
    ddcObjectList kids(CQuery::Children());
    if (m_qCount) kids.push_back(m_qCount);
    //if (m_proxy) kids.push_back(m_proxy);
    return kids;
}

//--------------------------------------------------------------
void CQKeys::DisownChildren() {
    CQuery::DisownChildren();
    m_qCount = NULL;
    m_proxy = NULL;
    m_dtrs.clear();
}

//--------------------------------------------------------------
//#define KEYSDEBUG(code) code
#define KEYSDEBUG(code)

bool CQKeys::Compile(CQueryCompiler *compiler) {
    SetCompiler(compiler);

    //-- sanity check(s)
    if (!m_qCount)
        throw CExpc(errParseError, "no underlying count-query for keys-query `%s'", this->toString().c_str());

    //-- compile count-subquerx
    if (!m_qCount->Compile(compiler))
        throw CExpc(errParseError, "could not compile count-query `%s' for keys-query `%s'",
                    m_qCount->toString().c_str(), this->toString().c_str());

    //-- set default index-names
    vector<CQCountKeyExpr *> &Exprs = m_qCount->m_keys->m_Exprs;
    string ixNone("-");
    if (m_IndexNames.empty()) {
        //-- set default index names
        m_IndexNames.reserve(Exprs.size());
        for (vector<CQCountKeyExpr *>::const_iterator xi = Exprs.begin(); xi != Exprs.end(); ++xi) {
            if (typeid(*(*xi)) == typeid(CQCountKeyExprToken))
                m_IndexNames.push_back(((CQCountKeyExprToken *) (*xi))->m_IndexName);
            else
                m_IndexNames.push_back(ixNone);
        }
    }
    if (m_IndexNames.empty())
        throw CExpc(errParseError, "can't handle empty index-tuple in keys-query `%s'", this->toString().c_str());

    //-- create attribute-wise value-set queries
    m_dtrs.clear();
    for (vector<string>::iterator ixi = m_IndexNames.begin(); ixi != m_IndexNames.end(); ++ixi) {
        if (ixi->empty())
            *ixi = ixNone;
        if ((*ixi) == ixNone)
            m_dtrs.push_back(NULL);
        else
            m_dtrs.push_back(new CQTokSet(*ixi));
    }

    KEYSDEBUG(fprintf(stderr, "[DEBUG:keys] %s\n", (this->toString() + this->optionsToString()).c_str()));

    //-- create joint proxy query
    m_proxy = NULL;
    for (vector<CQTokSet *>::iterator di = m_dtrs.begin(); di != m_dtrs.end(); ++di) {
        if (*di == NULL) continue;
        if (m_proxy == NULL)
            m_proxy = *di;
        else
            m_proxy = new CQWith(m_proxy, *di);
    }
    if (m_proxy == NULL)
        throw CExpc(errParseError, "no attributes proxied by keys-query `%s'", this->toString().c_str());

    //-- evaluate count subquery using CConcHolder::GetAllHits() (via public CConcHolder::GetHits())
    //   + this is annoying, but otherwise we're in a double-bind calling Evaluate() from CConcHolder::GetHits() in the period-loop,
    //     since GetAllHits() does the sorting and filtering and evaluation of count-query daughter node
    assert(compiler->m_pHolder);
    CConcHolder *holder = (CConcHolder *) compiler->m_pHolder;
    DWORD EndHitNo = 0;
    size_t ResultLimitTmp = holder->m_ResultLimit;
    holder->m_ResultLimit = m_CountLimit;
    if (holder->GetHits(m_qCount, EndHitNo) != errNone)
        throw CExpc(errParseError, "could not evaluate count-query `%s' for keys-query `%s'",
                    m_qCount->toString().c_str(), this->toString().c_str());

    //-- populate attribute-wise value sets
    //m_tuples.clear();
    vector<string> hvals;
    vector<string>::const_iterator vali;
    vector<CQTokSet *>::iterator dtri;
    string delims(1, globalCountKeyDelim);
    for (vector<CHit>::const_iterator hiti = holder->m_Hits.begin(); hiti != holder->m_Hits.end(); ++hiti) {
        hvals.clear();
        stringSplitE(hiti->m_SortKey.s, delims, hvals);
        //m_tuples.insert(hvals);
        for (vali = hvals.begin(), dtri = m_dtrs.begin(); vali != hvals.end() && dtri != m_dtrs.end(); ++vali, ++dtri) {
            if (*dtri == NULL) continue;
            (*dtri)->m_Values.insert(*vali);
        }
    }

    //-- restore holder & count-query data
    holder->ClearQueryResults();
    holder->m_ResultLimit = ResultLimitTmp;
    m_qCount->ClearNode();

    //-- setup proxy match-id(s)
    if (m_MatchId != 0)
        m_proxy->SetMatchId(m_MatchId);

    //-- compile proxy query
    if (!m_proxy->Compile(compiler))
        throw CExpc(errParseError, "could not compile subquery `%s' for keys-query `%s'", m_proxy->toString().c_str(),
                    this->toString().c_str());

    KEYSDEBUG(fprintf(stderr, "[DEBUG:keys:proxy] %s\n", (m_proxy->toString() + m_proxy->optionsToString()).c_str()));

    //-- setup proxy m_Node
    m_Node = m_proxy->m_Node;
    m_proxy->m_Options = m_Options;
    return true;
}

//--------------------------------------------------------------
void CQKeys::Evaluate() {
    assert(m_proxy != NULL);
    m_proxy->Evaluate();
    m_Node = m_proxy->m_Node;
}

//--------------------------------------------------------------
BYTE CQKeys::GetMatchId() const {
    if (m_MatchId != 0) return m_MatchId;
    if (m_qCount) return m_qCount->GetMatchId();
}

//--------------------------------------------------------------
string CQKeys::toString() {
    string qs;
    if (!m_IndexNames.empty()) {
        qs += "$(";
        for (vector<string>::const_iterator ii = m_IndexNames.begin(); ii != m_IndexNames.end(); ++ii) {
            if (ii != m_IndexNames.begin()) qs.push_back(',');
            qs += *ii;
        }
        qs += ")=";
    }

    qs += "KEYS(";
    if (m_qCount) {
        if (m_qCount->m_dtr)
            qs += m_qCount->m_dtr->toString() + m_qCount->m_dtr->optionsToString();
        qs += m_qCount->countOptionsToString();
        if (m_CountLimit != DDCDefaultCountSampleSize)
            qs += Format(" #CLIMIT %zi", m_CountLimit);
    }
    qs.push_back(')');

    if (m_MatchId != 0)
        qs += Format(" =%u", m_MatchId);

    return qs;
}

//--------------------------------------------------------------
string CQKeys::jsonData() {
    string qs("\"IndexNames\":" + jsonArray(m_IndexNames)
              + ",\"QCount\":" + m_qCount->toJson()
    );
    if (m_CountLimit != DDCDefaultCountSampleSize)
        qs += Format(",\"CountLimit\":%zi", m_CountLimit);
    if (m_MatchId != 0)
        qs += Format(",\"MatchId\":%u", m_MatchId);
    return qs;
}

//======================================================================
// functions

void GenerateCountString(string &ResultStr, DDCFormatTypeEnum fmt, const string &key, size_t count) {
    string keysep(1, globalCountKeyDelim);
    StringSplitter keysplit(key, keysep);

    switch (fmt) {
        case DDC_ResultJson:
            //-- count strings, json format "[[COUNT, KEY0, KEY1, ... ], ..., [COUNT, KEY0, KEY1, ...]"
            ResultStr += Format("[%zi", count);
            for (; keysplit; ++keysplit) {
                ResultStr.push_back(',');
                ResultStr.append(jsonStr(*keysplit));
            }
            ResultStr.push_back(']');
            break;

        case DDC_ResultHTML:
            //-- count strings, html
            ResultStr += Format("<TR><TD>%zi</TD>", count);
            for (; keysplit; ++keysplit) {
                ResultStr += "<TD>" + ConvertASCIIToHtmlSymbols(*keysplit) + "</TD>";
            }
            ResultStr += "</TR>\n";
            break;


        case DDC_ResultText:
        case DDC_ResultTable:
        default:
            //-- count strings, text or table
            ResultStr += Format("%zi", count);
            for (; keysplit; ++keysplit) {
                ResultStr.push_back('\t');
                ResultStr += *keysplit;
            }
            ResultStr.push_back('\n');
            break;
    }
}

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-default-style: "linux"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
