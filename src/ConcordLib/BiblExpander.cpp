#include "BiblExpander.h"
#include "ConcCommon.h"
#include "CommonLib/ddcString.h"
#include <stdlib.h>
#include <wctype.h>
#include "CommonLib/ddcExpc.h"

using namespace std;

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
    throw CDDCExpc(errOther,"abstract method CBiblExpander::expand() called for expander `%s'", m_BxLabel.c_str());
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
        throw CDDCExpc(errOther,"BxTermWrapper::expand() called with no underlying CTermExpander for expander `%s'", m_BxLabel.c_str());

    m_BxTx->expand(src,dst);
}
