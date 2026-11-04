#include "Bibliography.h"
#include "ConcCommon.h"
#include "../CommonLib/ddcLog.h"
#include "nlp_base/graphan/GraphanLib/graline.h"
#include "../CommonLib/ddcTime.h"   // date2int(), int2date()

using namespace std;

CBibliography::CBibliography() {
    m_StartPageInfo = UnknownPageNumber;
}

void CBibliography::CleanBibliography() {
    m_OrigBibl = "";
    m_ScanBibl = "";
    m_DateStr = "";
    m_StartPageInfo = UnknownPageNumber;
    m_BiblAttribs.clear();
};

void CBibliography::ReadFromString(const string &S) {
    CleanBibliography();

    size_t start = S.find("<orig>");
    size_t end = S.find("</orig>");
    if ((start != -1) && (end != -1)) {
        m_OrigBibl = S.substr(start + 6, end - start - 6);
        Trim(m_OrigBibl);
    };

    start = S.find("<scan>");
    end = S.find("</scan>");
    if ((start != -1) && (end != -1)) {
        m_ScanBibl = S.substr(start + 6, end - start - 6);
        Trim(m_ScanBibl);
    };

    start = S.find("<date>");
    end = S.find("</date>");
    if ((start != -1) && (end != -1)) {
        m_DateStr = S.substr(start + 6, end - start - 6);
        Trim(m_DateStr);
    };


};

string CBibliography::WriteToString() const {
    string Result;
    if (!m_OrigBibl.empty()) Result += "<orig> " + m_OrigBibl + "</orig>\n";
    if (!m_DateStr.empty()) Result += "<date> " + m_DateStr + "</date>\n";
    if (!m_ScanBibl.empty()) Result += "<scan> " + m_ScanBibl + "</scan>\n";
    return Result;
};

bool CBibliography::ConvertDateToInt(int &Result) const
{
    if (m_DateStr.empty())
        return false; //-- sanity check: no empty dates

    signed   int year=0;
    unsigned int month=1,day=1;
    const char *s=m_DateStr.c_str();
    char *tail;

    year = strtol(s, &tail, 10);
    if (year < -32768 || year > 32767) return false; //-- sanity check: year-part is 16-bit signed

    while (tail && *tail=='-') ++tail;
    if (tail && *tail)
        month = strtoul((s=tail), &tail, 10);

    while (tail && *tail=='-') ++tail;
    if (tail && *tail)
        day = strtoul((s=tail), &tail, 10);

    Result = date2int(year, month, day);
    return true;
};


// auto-truncate a single bibliography string (convenience class method)
inline static void SanitizeBiblString(std::string& val, const char *label)
{
    if (TrimTruncate(val,MaxBiblStringLen))
        ddcLogWarn(Format("Warning: truncating value for bibl attribute `%s' to max=%zi bytes", label, MaxBiblStringLen));
};

void CBibliography::Sanitize(bool sanitizeFree)
{
    SanitizeBiblString(m_OrigBibl,"orig");
    SanitizeBiblString(m_ScanBibl,"scan");
    SanitizeBiblString(m_DateStr, "date");
    if (sanitizeFree) {
        //-- probably best not to do this here, since free bibl attributes are auto-truncated by
        for (size_t i=0; i < m_BiblAttribs.size(); ++i) {
            if (TrimTruncate(m_BiblAttribs[i],MaxBiblStringLen))
                ddcLogWarn(Format("Warning: truncating value for free bibl field #%zi to max=%zi bytes", i, MaxBiblStringLen));
        }
    }
};
