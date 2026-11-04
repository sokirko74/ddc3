#include "ddcVersion.h"
#include "nlp_base/common/utilit.h"
#include "ddcUtil.h"
#include "ddcExpc.h"
#include "ddcString.h"

using namespace std;

//--------------------------------------------------------------
const char *DDCVersionString()
{
    return PACKAGE_VERSION;
}

//--------------------------------------------------------------
void ddc_parse_format_version(const char *s, DDCVersionT &version, DDCVersionT &version_min)
{
    vector<string> toks = stringSplit(s," \t\r\n");
    version.clear();
    version_min.clear();
    for (int i=0; i < toks.size()-1; i++) {
        if (toks[i]=="Version")           version.fromString(toks[++i]);
        else if (toks[i]=="Format")       version.fromString(toks[++i]);
        else if (toks[i]=="min-compat")   version_min.fromString(toks[++i]);
    }
    if (version_min.empty()) { version_min = version; }
    return;
}

//--------------------------------------------------------------
void ddc_format_version_check(const char *s, const char *label)
{
    DDCVersionT version, version_min;
    if (label==NULL) label=s;
    ddc_parse_format_version(s,version,version_min);
    //std::string sv_str=version.str(), svmin_str=version_min.str(), ddcv_str=DDCVersion.str(), ddcvmin_str=DDCVersionMinR.str();
    if (version.empty() && version_min.empty())
        throw CDDCExpc(errLogic,
                    std::string("could not parse format version from `") + label + "'");
    if (version < DDCVersionMinR)
        throw CDDCExpc(errLogic,
                    std::string(label) + ": format version "+version.str()+" is obsolete (need format >= v" + DDCVersionMinR.str() + ")");
    if (DDCVersion < version_min)
        throw CDDCExpc(errLogic,
                    std::string(label) + ": DDC v"+DDCVersion.str()+" is too old to read format (need at least DDC v"+version_min.str()+")");
}
