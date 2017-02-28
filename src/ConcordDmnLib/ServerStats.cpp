//-*- Mode: C++; c-basic-offset:4; -*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2017 by Bryan Jurish
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

#include "ServerStats.h"
using namespace std;

//==============================================================================
// CDDCQueryTimeAvg

#if 0
//----------------------------------------------------------------------
//-- on-the-fly moving average, without cached m_size, m_etotal
double CDDCQueryTimeAvg::tAverage() const
{
    double total = 0;
    size_t n = 0;
    CDDCQueryTime key;
    key.m_t -= m_Window;
    for (set<CDDCQueryTime>::const_iterator tsi=m_tset.lower_bound(key); tsi!=m_tset.end(); ++tsi) {
	total += tsi->m_elapsed;
	++n;
    }
    return total / n;
}
#endif

//----------------------------------------------------------------------
void CDDCQueryTimeAvg::Scrub(void)
{
    set<CDDCQueryTime>::iterator qti;
    time_t left;
    time(&left);
    left -= m_Window;
    for (qti=m_tset.begin(); qti!=m_tset.end() && qti->m_t < left; ++qti) {
	--m_size;
	m_etotal -= qti->m_elapsed;
    }
    m_tset.erase(m_tset.begin(), qti);
}

//----------------------------------------------------------------------
void CDDCQueryTimeAvg::AppendCurrent(double elapsed)
{
    if (!m_tset.empty()) {
	set<CDDCQueryTime>::iterator cur = m_tset.end();
	--cur;
	--m_size;
	m_etotal -= cur->m_elapsed;
	elapsed  += cur->m_elapsed;
	m_tset.erase(cur);
    }
    Append(elapsed);
}

//==============================================================================
// CDDCServerStats

//----------------------------------------------------------------------
CDDCServerStats& CDDCServerStats::operator+=(const CDDCServerStats& x)
{
    m_nRequests += x.m_nRequests;
    m_nQueries  += x.m_nQueries;
    m_nErrors   += x.m_nErrors;
    m_nSlow     += x.m_nSlow;
    m_qTimes    += x.m_qTimes;
    return *this;
}

