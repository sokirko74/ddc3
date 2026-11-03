//*-*- Mode: C++ -*-*/
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2016 by Bryan Jurish
//
//  This file is part of DDC (formerly in ConcHolder.cpp)
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

#include "QueryResult.h"

using namespace std;

//==============================================================================
// CQueryResult

//----------------------------------------------------------------------
void    CQueryResult::ClearQueryResults()
{
    ClearVector(m_Hits);
    ClearVector(m_HighlightOccurs);
    ClearVector(m_HighlightIds);
    ClearVector(m_DebugInfo);
    m_AllHitsCount = 0;
    m_RelevantDocumentCount = 0;
    m_bSortByString = false;
    m_SortOrder = hsoNone;
}


//==============================================================================
// CQueryResultIndex

//----------------------------------------------------------------------
void CQueryResultIndex::Reset(void)
{
    if (m_pHitIndex==NULL) {
        m_pHitIndex = new vector<size_t>(m_Result.m_Hits.size());
        m_bLocalIndex = true;
    } else {
        m_pHitIndex->resize(m_Result.m_Hits.size());
    }
    for (size_t ii=0; ii < m_pHitIndex->size(); ++ii)
        (*m_pHitIndex)[ii] = ii;
};

//----------------------------------------------------------------------
void CQueryResultIndex::Apply(CQueryResult& Dst, size_t Begin, size_t End)
{
    //-- sanity checks
    End = min(End, size());
    if (Begin >= End) {
        Dst.m_Hits.clear();
        Dst.m_HighlightOccurs.clear();
        Dst.m_HighlightIds.clear();
        Dst.m_DebugInfo.clear();
        return;
    }
        
    //-- populate new temporary result structures
    vector<CHit>            NewHits;
    vector<CTokenNo>        NewHighlightOccurs;
    vector<BYTE>            NewHighlightIds;
    NewHits.reserve(End - Begin);
    if (NewHits.size() == m_Result.m_Hits.size()) {
        //-- full monty: go ahead and reserve everything
        NewHighlightOccurs.reserve(m_Result.m_HighlightOccurs.size());
        NewHighlightIds.reserve(m_Result.m_HighlightIds.size());
    }
                
    for (size_t ii=Begin; ii < End; ++ii) {
        size_t HitNo = (*m_pHitIndex)[ii];
        NewHits.push_back( m_Result.m_Hits[HitNo] );
                
        int occ_begin = (HitNo == 0) ? 0 : m_Result.m_Hits[HitNo-1].m_HighlightOccurrenceEnd;
        NewHighlightOccurs.insert(NewHighlightOccurs.end(),
                                  m_Result.m_HighlightOccurs.begin()+occ_begin,
                                  m_Result.m_HighlightOccurs.begin()+m_Result.m_Hits[HitNo].m_HighlightOccurrenceEnd);

        if (!m_Result.m_HighlightIds.empty())
            NewHighlightIds.insert(NewHighlightIds.end(),
                                   m_Result.m_HighlightIds.begin()+occ_begin,
                                   m_Result.m_HighlightIds.begin()+m_Result.m_Hits[HitNo].m_HighlightOccurrenceEnd);

        NewHits.back().m_HighlightOccurrenceEnd = NewHighlightOccurs.size();
    }

    //-- update sink object
    Dst.m_Hits.swap(NewHits);
    Dst.m_HighlightOccurs.swap(NewHighlightOccurs);
    Dst.m_HighlightIds.swap(NewHighlightIds);
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
