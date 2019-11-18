//-*- Mode: C++ -*-
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

#include "ServerStats.h"
using namespace std;

//==============================================================================
// CDDCServerStats

//----------------------------------------------------------------------
CDDCServerStats& CDDCServerStats::operator+=(const CDDCServerStats& x)
{
    m_nRequests += x.m_nRequests;
    m_nQueries  += x.m_nQueries;
    m_nExpand   += x.m_nExpand;
    m_nErrors   += x.m_nErrors;
    m_nSlow     += x.m_nSlow;
    m_qTimes    += x.m_qTimes;
    m_xTimes    += x.m_xTimes;
    return *this;
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
