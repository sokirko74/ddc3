#ifndef PROJECT_BIBLIOGRAPHY_H
#define PROJECT_BIBLIOGRAPHY_H

#include "nlp_base/common/utilit.h"
#include "../CommonLib/ddcUtil.h"

/* CBibliography  contains bibliographical information about one corpus_file_def "corpus file", this information
  is read from xml, xpathes are defined in options file.
*/
struct CBibliography {
    // original bibliography
    std::string m_OrigBibl;
    // scanned bibliography
    std::string m_ScanBibl;
    // issue date
    std::string m_DateStr;
    // starting page
    uint32_t m_StartPageInfo;
    // free bibbliographical attributes
    std::vector<std::string> m_BiblAttribs;


    CBibliography();

    // set all members empty
    void CleanBibliography();

    // read structure's members  from a string
    void ReadFromString(const std::string &S);

    // write structure's members  to a string
    std::string WriteToString() const;

    // convert m_DateStr to an integer
    bool ConvertDateToInt(int &Result) const;

    // sanitize (auto-truncate) built-in attribute strings
    // free string values are auto-truncated by CFreeBiblStringIndex::RegisterBiblStringItemId()
    // sanitizeFree: : sanitize free bibl-attributes too?
    void Sanitize(bool sanitizeFree=false);
};


#endif //PROJECT_BIBLIOGRAPHY_H
