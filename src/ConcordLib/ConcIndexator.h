//-*- Mode: C++ -*-

//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2020 by Bryan Jurish
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

/*! \mainpage Dialing DDWS Concordance  (DDC)
  DDC is a tool for linguists to search for a particular construction
  in a given corpus.  A corpus is defined by a list \ref source_file_def "source files",
  which should be before indexed. The index and query process is governed by file of options.
*/


#ifndef ConcIndexator_h
#define ConcIndexator_h


#include "TabFormatIndexator.h"

/// global default value (5000000) for CConcIndexator::m_UserMaxTokenCountInOnePeriod 
extern const uint32_t DefaultMaxTokenCountInOnePeriod;

/// global default value for (400000) CConcIndexator::m_UserMaxInputLoadIndexSize (must be <= DefaultMaxTokenCountInOnePeriod)
extern const uint32_t DefaultMaxInputLoadIndexSize;

/*!
  CConcIndexator is the class for corpus indexing.  The most of its  slots come from Concordance class.
*/
class CConcIndexator : public CTabFormatIndexator {

    //! graphmat (tokenization  parser)
    CGraphmatFile Graphmat;

    //! a reference to DWDS thesaurus if applicable
    const CDwdsThesaurus *m_pDwdsThesaurus;


    void IndexTextOrHtmlFile(CIndexDocument* document);

    void IndexMorphXml(CIndexDocument* document);

    void IndexFreeIndex(CIndexDocument* document);

    void IndexOneTableTextArea(const std::string &Text, const CPageNumber &StartPageFromHeader, size_t &page_breaks_count,
                               CIndexDocument* document);

    //!  graphematical definition of a token for DWDSIndex
    bool IsDWDSToken(long GraLine) const;

    void LoadXmlFile(std::string FileName, const char *pFileBuffer, CBibliography &Bibl);

    void LoadFileIntoGraphan(std::string FileName, const char *pFileBuffer, CBibliography &Bibl);


public:
    CConcIndexator();

    ~CConcIndexator();

    //! initializes graphematics using current options
    void InitGraphan() ;


    //! saves corpus file list  (*._con)
    bool SaveCorpusFileList() const;

    //! saves masked file-ids (*._masked_ids)
    bool SaveMaskedFileIds() const;

    //! begins indexing
    void StartIndexing();

    //! destroy all index files
    void DestroyIndex();

    //! finishes indexing (normal way)
    void NormalEndIndexing();

    //! terminates indexing (for exceptions)
    void TerminateIndexing();

    //!  index one file according to m_IndexType
    void IndexOneFile(CIndexDocument* document);

    //! rollback data buffered by an immediate preceding failed IndexOneFile()
    void RollbackIndexOneFile(CTokenNo startTrimTokenNo);

    //! finds all \ref period_def "subcorpora"
    void CalculateSearchPeriods(uint32_t MaxTokenCountInOnePeriod);

    //! creates new concordance as union of one or more concordances (new)
    bool CreateAsUnion(std::vector<CConcIndexator* > &X, bool inheritOptions = true);

    //! creates new concordance as union of one or more concordances (new, filename-based)
    bool CreateAsUnion(const std::vector<std::string> &Xfiles, bool inheritOptions = true);

    //! split project uniformly into sub-projects (new; sub-projects inherit parent options)
    bool SplitProject(std::vector<CConcIndexator*> &Subs) const;

    //! split project uniformly into sub-projects (guts, given sub-options as string)
    bool SplitProject(std::vector<CConcIndexator*> &Subs, const std::string &SubOptions) const;

    //! creates morphology index
    bool CreateMorphIndexWrapper();

    //! returns the size of one \ref period_def "subcorpus"
    uint32_t GetMaxTokenCountInOnePeriod() const;

    //! returns the max size of input index in tokens must be less than GetMaxTokenCountInOnePeriod()
    uint32_t GetMaxInputLoadIndexSize() const;

};


#endif 

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
