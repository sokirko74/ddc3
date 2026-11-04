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
