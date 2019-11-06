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
#ifndef __MorphXMLtoken_h
#define __MorphXMLtoken_h

#include "../CommonLib/utilit.h"

const string XmlPunctType = "pun";
const string XmlWordType = "w";
//! CXmlMorphAnnot holds one morphological interpretation, which is read from xml under CConcIndexator::m_IndexType == MorphXML_Index
struct  CXmlMorphAnnot
{
        //! lemma
        string                          m_Lemma;
        //! other morphological features
        string                          m_GrammemsStr;
    //! reference to xml node
        //! return the structure as a set of token properties
    void        GetAsSetOfProperties(vector<string>& Result)  const
    {
        Result.clear();

        StringTokenizer tok2(m_GrammemsStr.c_str(), " \t,|; ");
        while (tok2())
            Result.push_back(tok2.val());

        sort(Result.begin(), Result.end());

    };
};

//! CXmlToken holds a word and all ist  morphological interpretations (used under CConcIndexator::m_IndexType == MorphXML_Index)
struct CXmlToken 
{
        //! type of token (a word, a punctuation mark)
        string                                          m_Type;
        //! the string itself
        string                                          m_WordStr;
        //! all morphological annotations
        vector<CXmlMorphAnnot>          m_Annots;
        //! true if the token is last in the sentence
        bool                                            m_bLastInSentence;
    CXmlToken()
    {
        m_bLastInSentence = false;
    };
    ;
};
#endif


/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-default-style: "linux"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
