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
// ==========  Dialing Structural Dictionary (www.aot.ru)
// ==========  Copyright by Alexey Sokirko (1998-2002), Bryan Jurish (2011)


#ifndef _TEMPARTICLE_H_
#define _TEMPARTICLE_H_

#include "Ross.h"       // main symbols
#include "TextField.h"       // main symbols


class CTempArticle 
{
    string                                  m_ArticleStr;
public:
    char                                    m_EntryStr[EntryStrSize];
    BYTE                                    m_MeanNum;
    WORD                                    m_UnitNo;
    bool                                            m_ReadOnly;
    vector<CTextField>              m_Fields;
    CDictionary*                            m_pRoss;
        
    vector<TCortege10>              m_Corteges;
    string                          m_LastError;
    int                                             m_ErrorLine;
    CTempArticle();
        


    const TCortege10&       GetRossCortege (size_t i) const;
    size_t                          GetCortegesSize () const;
    const TCortege10&       GetCortege (size_t i)  const;
    string          ConstructFldName (BYTE FieldNo, BYTE LeafId, BYTE BracketLeafId);
    bool            IsPartOf(const CTempArticle *Article, bool UseWildCards) const;
    int                     IntersectByFields(const CTempArticle *Article) const;
    bool            AddArticle(const CTempArticle *Article);
    bool            ArticleToText ();
    bool            AddCortegeToVector (CTextField& F);
    bool            CheckCortegeVector ();
    bool            SetArticleStr(const char * s);
    bool            MarkUp();
    bool            BuildCortegeList();
    bool            WriteToDictionary();
    void            ReadFromDictionary(WORD UnitNo, bool ReadOnly);
    const string& GetArticleStr();
        
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
