#include "StdGraph.h"
#include "GraphmatFile.h"

#include <assert.h>
#include <stdlib.h>

#include "Consent.h"


using namespace std;

bool  CConSent :: IsSoft()   const
{
    return m_HardGraphEndNo == 0;
};



bool CConSent :: InitBasicInformation ()
{
    m_HardGraphEndNo  = m_GraFile->BSoft(m_EndNo);
    assert (m_HardGraphEndNo > 0 );

    if (IsSoft()) 
        m_GraLineNoToMark  = m_EndNo;
    else
        m_GraLineNoToMark = m_GraFile->HasDescr (m_HardGraphEndNo,OPun) ? m_HardGraphEndNo : m_GraFile->BSpace(m_EndNo);

    return true;
}
