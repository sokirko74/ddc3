#ifndef _TEMPARTICLE_H_
#define _TEMPARTICLE_H_

#include "Ross.h"       // main symbols
#include "TextField.h"       // main symbols


class CTempArticle 
{
    std::string                                  m_ArticleStr;
public:
    char                                    m_EntryStr[EntryStrSize];
    BYTE                                    m_MeanNum;
    uint16_t                                    m_UnitNo;
    bool                                            m_ReadOnly;
    std::vector<CTextField>              m_Fields;
    CDictionary*                            m_pRoss;
        
    std::vector<TCortege10>              m_Corteges;
    std::string                          m_LastError;
    int                                             m_ErrorLine;
    CTempArticle();
        


    const TCortege10&       GetRossCortege (size_t i) const;
    size_t                          GetCortegesSize () const;
    const TCortege10&       GetCortege (size_t i)  const;
    std::string          ConstructFldName (BYTE FieldNo, BYTE LeafId, BYTE BracketLeafId);
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
    void            ReadFromDictionary(uint16_t UnitNo, bool ReadOnly);
    const std::string& GetArticleStr();
        
};

#endif
