//
// Created by sokirko on 10.10.19.
//

#ifndef PROJECT_BIBLIOGRAPHY_H
#define PROJECT_BIBLIOGRAPHY_H

#include "../CommonLib/utilit.h"

/*! CBibliography  contains bibliographical information about one \ref corpus_file_def "corpus file", this information
  is read from xml, xpathes are defined in options file.
*/
struct CBibliography {
    //! original bibliography
    string m_OrigBibl;
    //! scanned bibliography
    string m_ScanBibl;
    //! issue date
    string m_DateStr;
    //! starting page
    DWORD m_StartPageInfo;
    //! free bibbliographical attributes
    vector<string> m_BiblAttribs;


    CBibliography();

    //! set all members empty
    void CleanBibliography();

    //! read structure's members  from a string
    void ReadFromString(const string &S);

    //! write structure's members  to a string
    string WriteToString() const;

    //! convert m_DateStr to an integer
    bool ConvertDateToInt(int &Result) const;
};


#endif //PROJECT_BIBLIOGRAPHY_H

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
