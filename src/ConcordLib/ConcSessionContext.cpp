//*-*- Mode: C++; c-basic-offset: 8; -*-*/
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2016 by Bryan Jurish
//
//  This file is part of DDC (formerly part of ConcHolder.cpp)
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

#include "ConcSessionContext.h"

//#define DEBUG_CACHE
#undef DEBUG_CACHE

#ifdef DEBUG_CACHE
# define CACHEDEBUG(code)   code
# define CACHEDEBUGLOG(str) concord_daemon_log(str)
#else
# define CACHEDEBUG(code)
# define CACHEDEBUGLOG(str)
#endif


//==============================================================================
// Constructors etc.

//==============================================================================
// API: caching

//----------------------------------------------------------------------
bool CConcSessionContext::CacheGet(CConcHolder& Holder, const string &Query, DWORD& EndHitNo)
{
	lock();
	try {
		CACHEDEBUG(concord_daemon_log(Format("CConcSessionContext::CacheGet() : Query=%s, End=%d, CacheSize=%zi", jsonStr(Query).c_str(), EndHitNo, m_Queries.size())));

		map<string, CQueryResult>::const_iterator it = m_QueryCache.find(Query);
		// if the query is not the cache then we're done
		if (it == m_QueryCache.end()) {
			CACHEDEBUGLOG( Format("CConcSessionContext::CacheGet() --> not found") );
			unlock();
			return false;
		}

		const CQueryResult& CacheItem = it->second;
		CACHEDEBUGLOG( Format("CConcSessionContext::CacheGet() --> found --> nHits=%zd ; HitUB=%zd ; MaxCachedHitsCount=%zd", CacheItem.m_AllHitsCount, EndHitNo+Holder.m_ResultLimit, Holder.m_pIndexator->m_MaxCachedHitsCount) );

		// if one asks hits, which were beyond the storage limits of the cache
		if (min(CacheItem.m_AllHitsCount,EndHitNo+Holder.m_ResultLimit) > Holder.m_pIndexator->m_MaxCachedHitsCount) {
			CACHEDEBUGLOG( Format("CConcSessionContext::CacheGet() --> min(nHits,HitUB)=%zd > MaxCachedHitsCount=%zd : must re-evaluate", min(CacheItem.m_AllHitsCount,EndHitNo+Holder.m_ResultLimit), Holder.m_pIndexator->m_MaxCachedHitsCount) );
			unlock();
			return false;
		}
		
		Holder.ClearQueryResults();
	
		// copy [EndHitNo...EndHitNo+Holder.m_ResultLimit) hits from the cache to Holder fields m_Hits, m_HighlightOccurs, and m_HighlightIds
		size_t End = min (EndHitNo+Holder.m_ResultLimit, CacheItem.m_Hits.size());
		for (; EndHitNo < End; EndHitNo++) {
			Holder.m_Hits.push_back(CacheItem.m_Hits[EndHitNo]);
			int start = (EndHitNo == 0) ? 0 : CacheItem.m_Hits[EndHitNo-1].m_HighlightOccurrenceEnd;
			Holder.m_HighlightOccurs.insert(Holder.m_HighlightOccurs.end(),
							CacheItem.m_HighlightOccurs.begin()+start,
							CacheItem.m_HighlightOccurs.begin()+CacheItem.m_Hits[EndHitNo].m_HighlightOccurrenceEnd);
		
			if (!CacheItem.m_HighlightIds.empty())
				Holder.m_HighlightIds.insert(Holder.m_HighlightIds.end(),
							     CacheItem.m_HighlightIds.begin()+start,
							     CacheItem.m_HighlightIds.begin()+CacheItem.m_Hits[EndHitNo].m_HighlightOccurrenceEnd);

			Holder.m_Hits.back().m_HighlightOccurrenceEnd = Holder.m_HighlightOccurs.size();
		}

		//-- copy administrative result data
		Holder.m_DebugInfo = CacheItem.m_DebugInfo;
		Holder.m_AllHitsCount = CacheItem.m_AllHitsCount;
		Holder.m_RelevantDocumentCount = CacheItem.m_RelevantDocumentCount;
		Holder.m_SortOrder = CacheItem.m_SortOrder;
		Holder.m_bSortByString = CacheItem.m_bSortByString;
	}
	catch (...) {
		unlock();
		throw;
	}

	unlock();
	return true;
};

//----------------------------------------------------------------------
void CConcSessionContext::CacheSet(CConcHolder& Holder, const string& Query, vector<size_t>::const_iterator start, vector<size_t>::const_iterator end)
{
	if (Holder.m_pIndexator->m_MaxQueryCacheSize==0) return;

	lock();
	try {
		CACHEDEBUGLOG( Format("CConcSessionContext::CacheSet() : Query=%s, nItems=%zd, CacheSize=%zi", jsonStr(Query).c_str(), end-start, m_Queries.size()));

		if (m_QueryCache.find(Query) !=  m_QueryCache.end()) {
			// input query already cached: nothing to do
			CACHEDEBUGLOG( Format("CConcSessionContext::CacheSet() --> already present") );
			unlock();
			return;
		}

		// if the cache is full, then we should delete the oldest item
		if (m_Queries.size() >= Holder.m_pIndexator->m_MaxQueryCacheSize) {
			//  erasing  the first item from Query queue and from the Query cache
			map<string, CQueryResult>::iterator it = m_QueryCache.find(m_Queries.front());
			assert(it != m_QueryCache.end());
			CACHEDEBUGLOG( Format("CConcSessionContext::CacheSet() --> dropping stale cache-item %s", jsonStr(it->first).c_str()) );
			m_QueryCache.erase(it);
			m_Queries.erase(m_Queries.begin());
		}
		m_Queries.push_back(Query);
	
		//  creating a new query cache item
		CQueryResult I;
		I.m_AllHitsCount = Holder.m_AllHitsCount;
		I.m_RelevantDocumentCount = Holder.m_RelevantDocumentCount;
		I.m_SortOrder = Holder.m_SortOrder;
		I.m_bSortByString = Holder.m_bSortByString;
		size_t End  = min(Holder.m_pIndexator->m_MaxCachedHitsCount, (size_t)(end-start));
		for (size_t i=0; i < End; i++)
			{
				size_t HitNo = *start;
				start++;
				I.m_Hits.push_back(Holder.m_Hits[ HitNo ]);
				int start_index = (HitNo == 0) ? 0 : Holder.m_Hits[HitNo-1].m_HighlightOccurrenceEnd;
				I.m_HighlightOccurs.insert(I.m_HighlightOccurs.end(),
							   Holder.m_HighlightOccurs.begin()+start_index,
							   Holder.m_HighlightOccurs.begin()+Holder.m_Hits[HitNo].m_HighlightOccurrenceEnd);

				if (!Holder.m_HighlightIds.empty())
					I.m_HighlightIds.insert(I.m_HighlightIds.end(),
								Holder.m_HighlightIds.begin()+start_index,
								Holder.m_HighlightIds.begin()+Holder.m_Hits[HitNo].m_HighlightOccurrenceEnd);

				I.m_Hits.back().m_HighlightOccurrenceEnd = I.m_HighlightOccurs.size();
			}

		I.m_DebugInfo = Holder.m_DebugInfo;
		m_QueryCache[Query] = I;
		assert (m_Queries.size() == m_QueryCache.size());
	}
	catch (...) {
		unlock();
		throw;
	}
	
	unlock();
}

//----------------------------------------------------------------------
void CConcSessionContext::CacheClear()
{
	lock();
	m_QueryCache.clear();
	m_Queries.clear();
	unlock();
}

//----------------------------------------------------------------------
size_t CConcSessionContext::CacheSize()
{
	lock();
	size_t sz = m_QueryCache.size();
	unlock();
	return sz;
}
