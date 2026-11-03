//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2015 by Bryan Jurish
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
#ifndef __DwdsThesaurus_H_
#define __DwdsThesaurus_H_

#include "../CommonLib/util_classes.h"


class CDwdsThesaurus 
{
    //  all possible supernodes of the thesaurus Adel, H...
    StringVector HyperTerms;
    // a buffer to store pathes from the leaf to the root
    std::vector<uint32_t> Pathes;

    // an index which points to vector Pathes
    // the count of PathEndIndex  is equal to the count of leaves in the thesaurus
    // Pathes[ PathEndIndex[i-1].... PathEndIndex[i] ]  is a path number i
    std::vector<uint32_t> PathEndIndex;

    // an index which points to vector Pathes
    std::vector<uint32_t> LeavesPathes;
    CShortStringHolder LeavesLemmas;

    DwordVector m_AllPathes;

public:
    bool    LoadDwdsThesaurus ();
    int             FindHyperTerm (const std::string& s) const;
    void    GetAllPathesWhichContainHyperTermNo (size_t HyperTermNo, DwordVector& sub_pathes) const;        
    bool    ReadPathFromString(const std::string& TextPath, std::vector<int>& HyperTermNos) const;
    void    GetAllPathesWhichStartFromThisSequence (const std::vector<int>& HyperTermNos, DwordVector& Result) const;
    void    GetAllLemmasWhosePathesStartFromThisSequence (const std::vector<int>& HyperTermNos, StringSet& Lemmas) const;
    std::string  GetAllThesInterpetations(const char* Lemma) const;
};

extern const CDwdsThesaurus* LoadDwdsThesaurus();
extern void FreeDwdsThesaurus(const CDwdsThesaurus*);

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
