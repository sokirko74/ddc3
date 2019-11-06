//
// Created by sokirko on 10.10.19.
//

#include "Bibliography.h"
#include "../GraphanLib/graline.h"

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

bool CBibliography::ConvertDateToInt(int &Result) const {
    if (m_DateStr.empty())
        return false;
    int year, month, day;
    StringTokenizer tok(m_DateStr.c_str(), "-");
    if (!tok()) return false;
    year = atoi(tok.val());
    if (year > 0xffff) return false; //-- moo: year-part is 16-bit
    if (tok()) {
        //-- Mon, 17 Feb 2015 13:26:37 +0100 moocow: allow MM > 12, YYYY-MM dates, and YYYY-MM-DD with DD > 31
        month = atoi(tok.val());

        if (tok()) day = atoi(tok.val());
    } else {
        month = 1;
        day = 1;
    };
    Result = date2int(year, month, day);
    return true;
};

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-default-style: "linux"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
