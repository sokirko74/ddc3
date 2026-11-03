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
// ==========  Dialing Graphematical Module (www.aot.ru)
// ==========  Copyright by Alexey Sokirko (1996-2001), Bryan Jurish (2011)

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

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
