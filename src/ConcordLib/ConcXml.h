// //-*- Mode: C++ -*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2018 by Bryan Jurish
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
#ifndef __ConcXml_H_
#define __ConcXml_H_

#include "BiblIndex.h"

#include "../CommonLib/util_classes.h"
#include "../CommonLib/ddcThread.h"
#include "../CommonLib/ddcMMap.h"
#include "../CommonLib/ddcStringEnum.h"
#include <list>



/*!
  CConcXml is used for building bibliographical indices and working with xml.  
*/


class CConcXml : public CBiblIndex {
private:
    // File of Bibliographical references
    FILE *m_BodyFileToBuild;
    size_t m_BodyFileToBuildSize;

public:


public:
    CConcXml();

    ~CConcXml();

    void DeleteFiles();

    //! initialize building bibliography for corpus ProjectFileName
    bool Start(std::string ProjectFileName);

    //! add  one record Bibliography
    bool AddIndexItem(const CBibliography &Bibliography);

    //! save all indices and stop indexing bibliography
    void FinalSaveBibliography();

    //! stop indexing bibliography an removes index files
    void ExitWithoutSave();

    //! union of multiple (heterogeneous) bibliographies (new)
    bool UnionBibliographies(const std::vector<const CConcXml *> &Bibls);

    //! partition this object into multiple sub-objects (called by CConcIndexator::SplitProject())
    bool SplitBibliography(std::vector<CConcXml *> &Bibls, const std::vector<uint32_t> &EndFileNo) const;


    
    //! load xml file into TiXmlDocument& doc and load bibliographical fileds to CBibliography& Bibl
    void LoadXmlAndReadBibliography(TiXmlDocument &doc, const char *pFileBuffer, CBibliography &Bibl);

    //! load xml file under  MorphXML_Index into vector<CXmlToken>& GraTable
    void ReadMorphXmlFileIntoGraTable(std::string FileName, const char *pFileBuffer, std::vector<CXmlToken> &GraTable,
                                      CBibliography &Bibl);


    //! set all free bibliographical attributes to ""
    void SetFreeBiblAttribsEmpty(CBibliography &Bibl) const;


    void SetFreeBiblByName(const std::string &name, const std::string &value, CBibliography &result) const;


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
