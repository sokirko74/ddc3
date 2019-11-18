//-*- Mode: C++ -*-
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2013-2015 by Bryan Jurish
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

#include "BiblExpander.h"
#include "ConcCommon.h"
#include "../CommonLib/ddcString.h"
#include <stdlib.h>
#include <wctype.h>

//======================================================================
// CBiblExpander

//--------------------------------------------------------------
string CBiblExpander::configString(void) const
{
    return m_BxLabel + " " + m_BxTarget + " " + " " + m_BxParam;
}

//--------------------------------------------------------------
void CBiblExpander::expand(const string& src, set<string>& dst)
{
    set<string> ssrc;
    ssrc.insert(src);
    this->expand(ssrc,dst);
}

//--------------------------------------------------------------
void CBiblExpander::expand(const set<string>& src, set<string>& dst)
{
    throw CExpc(errOther,"abstract method CBiblExpander::expand() called for expander `%s'", m_BxLabel.c_str());
}

//======================================================================
// BxTermWrapper

//--------------------------------------------------------------
BxTermWrapper::BxTermWrapper(const string& label, const string& target, const string& param)
    : CBiblExpander(label,target,param), m_BxTx(NULL)
{
    const char *delims = " \t\r\n";
    StringTokenizer stok(param.c_str(), delims);
    string txclass("Id"), txparam("");

    if (stok.has_next()) txclass = stok.next_token();
    txparam = stok.get_rest();

    m_BxTx = newTermExpander(txclass, label, txparam);
};

//--------------------------------------------------------------
BxTermWrapper::~BxTermWrapper(void)
{
    if (m_BxTx) delete m_BxTx;
    m_BxTx = NULL;
}

//--------------------------------------------------------------
void BxTermWrapper::compile(void)
{
    if (m_BxTx) m_BxTx->compile();
}

//--------------------------------------------------------------
void BxTermWrapper::expand(const set<string>& src, set<string>& dst)
{
    if (!m_BxTx)
        throw CExpc(errOther,"BxTermWrapper::expand() called with no underlying CTermExpander for expander `%s'", m_BxLabel.c_str());

    m_BxTx->expand(src,dst);
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
