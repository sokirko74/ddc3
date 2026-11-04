#ifndef __MorphXMLtoken_h
#define __MorphXMLtoken_h

#include "morph_dict/common/utilit.h"
#include "../CommonLib/ddcUtil.h"

const std::string XmlPunctType = "pun";
const std::string XmlWordType = "w";
// CXmlMorphAnnot holds one morphological interpretation, which is read from xml under CConcIndexator::m_IndexType == MorphXML_Index
struct  CXmlMorphAnnot
{
    // lemma
    std::string                          m_Lemma;
    // other morphological features
    std::string                          m_GrammemsStr;
    // reference to xml node
    // return the structure as a set of token properties
    void        GetAsSetOfProperties(std::vector<std::string>& Result)  const
    {
        Result.clear();

        StringTokenizer tok2(m_GrammemsStr.c_str(), " \t,|; ");
        while (tok2())
            Result.push_back(tok2.val());

        std::sort(Result.begin(), Result.end());

    };
};

// CXmlToken holds a word and all ist  morphological interpretations (used under CConcIndexator::m_IndexType == MorphXML_Index)
struct CXmlToken 
{
    // type of token (a word, a punctuation mark)
    std::string                                          m_Type;
    // the string itself
    std::string                                          m_WordStr;
    // all morphological annotations
    std::vector<CXmlMorphAnnot>          m_Annots;
    // true if the token is last in the sentence
    bool                                            m_bLastInSentence;
    CXmlToken()
    {
        m_bLastInSentence = false;
    };
    ;
};
#endif
