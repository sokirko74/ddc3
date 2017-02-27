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

//----------------------------------------------------------------------
void CDDCQueryTimeAvg::Scrub(void)
{
    time_t t_now;
    set<CDDCQueryTime>::const_iterator tsi;

    time(&t_now);
    for (tsi=m_tset.begin(); tsi!=m_tset.end(); ++tsi) {
	if (difftime(t_now, tsi->m_t) <= m_Window) break;
	--m_n;
	m_etotal -= tsi->m_elapsed;
    }
    m_tset.erase(m_tset.begin(), tsi);
};

//==============================================================================
// CDDCServerStats

//----------------------------------------------------------------------
CDDCServerStats& CDDCServerStats::operator+=(const CDDCServerStats& x)
{
    m_nRequests += x.m_nRequests;
    m_nQueries  += x.m_nQueries;
    m_nErrors   += x.m_nErrors;
    m_nSlow     += x.m_nSlow;
    return *this;
}

//----------------------------------------------------------------------
CDDCServerStats& CDDCServerStats::operator-=(const CDDCServerStats& x)
{
    m_nRequests -= x.m_nRequests;
    m_nQueries  -= x.m_nQueries;
    m_nErrors   -= x.m_nErrors;
    m_nSlow     -= x.m_nSlow;
    return *this;
}
