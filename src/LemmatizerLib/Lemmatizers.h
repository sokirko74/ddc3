//-*- Mode: C++ -*-*/
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
// ==========  Dialing Lemmatizer (www.aot.ru)
// ==========  Copyright by Alexey Sokirko, Andrey Putrin, Bryan Jurish (2011)

#ifndef __LEMMATIZERS_H_
#define __LEMMATIZERS_H_

#pragma warning (disable : 4786)

#include "MorphDict.h"
#include "Paradigm.h"
#include "Statistic.h"
#include "Predict.h"
#include "../CommonLib/ddcIconv.h"

#pragma warning (disable : 4250)

class CGraphmatFile;


class CLemmatizer  : public CMorphDict
{
protected:
    string                          m_Registry;
        
    // Postfixes-particles, that do not change the meaning 
    set<string>             m_HyphenPostfixes;
    // productive prefixes
    set<string>                 m_HyphenPrefixes;

    CStatistic                      m_Statistic;
    CPredictBase            m_Predict;
    set<string>                     m_PrefixesSet;


    virtual void                    FilterSrc(string& src) const = 0;

    string                                  GetRegistryString()  const      {return m_Registry;     };
    string                                  GetPath()  const;
    void                                    ReadOptions(string FileName);
                
        
    bool                                    LemmatizeWord(string& InputWordStr, const bool cap, const bool predict, vector<CAutomAnnotationInner>& results, bool bGetLemmaInfos) const;
    void                                    AssignWeightIfNeed(vector<CAutomAnnotationInner>& FindResults) const;

    // prediction by suffix
    bool                                    CheckAbbreviation(string InputWordStr,vector<CAutomAnnotationInner>& FindResults, bool is_cap) const;
    CAutomAnnotationInner   ConvertPredictTupleToAnnot(const CPredictTuple& input) const;
    void                                    PredictByDataBase(string InputWordStr,  vector<CAutomAnnotationInner>&  results,bool is_cap) const;
    bool                                    IsPrefix(const string& Prefix) const;


public:
    bool                                    m_bLoaded;
    bool                                    m_bMaximalPrediction;
    bool                                    m_bUseStatistic;
    bool                                    m_bAllowRussianJo;


public:
    //-- BEGIN moo: character set hacks
    std::string                             m_enc_int;     ///< internal encoding (default=""=none)
    std::string                             m_enc_ext;     ///< external encoding (default=""=none)
    ddcIconv                               *m_ic_ext2int;  ///< iconv converter from user encoding to morph-internal encoding
    ddcIconv                               *m_ic_int2ext;  ///< iconv converter from morph-internal encoding to user encoding
    //-- END moo
        
        
    CLemmatizer(MorphLanguageEnum Language);
    virtual ~CLemmatizer();

    //  basic methods
    MorphLanguageEnum GetLanguage()  const {return m_pFormAutomat->m_Language; };
    const CStatistic& GetStatistic() const;
    bool    CheckABC(const string& WordForm) const;
    bool    IsHyphenPostfix(const string& Postfix) const;
    bool    IsHyphenPrefix(const string& Prefix) const;


    //-- moo: character set hacks
    bool initIconv(const string &enc_internal="", const string &enc_external="UTF8");
    inline std::string recode_ext2int(const std::string s_ext) const { return m_ic_ext2int==NULL ? s_ext : m_ic_ext2int->convert(s_ext); }
    inline std::string recode_int2ext(const std::string s_int) const { return m_ic_int2ext==NULL ? s_int : m_ic_int2ext->convert(s_int); }

        
    //  loading
    bool    LoadDictionariesRegistry(string& strError) ;

    //  main interfaces
    bool    CreateParadigmCollection(bool bNorm, string& WordStr, bool capital, bool bUsePrediction, vector<CFormInfo>& Result) const;
    void    GetAllAncodesQuick(const BYTE* WordForm, bool capital, BYTE* OutBuffer, bool bUsePrediction) const;
    bool    GetAllAncodesAndLemmasQuick(string& InputWordStr, bool capital, char* OutBuffer, size_t MaxBufferSize, bool bUsePrediction) const;
};





/////////////////////////////////////////////////////////////////////////////
class CLemmatizerRussian : public CLemmatizer
{
public:
    CLemmatizerRussian();
    virtual ~CLemmatizerRussian() {};
    void FilterSrc(string& src) const;
};


class  CLemmatizerEnglish : public CLemmatizer
{
    void FilterSrc(string& src) const;
public:
    CLemmatizerEnglish();
    virtual ~CLemmatizerEnglish() {};
        
};



/////////////////////////////////////////////////////////////////////////////

class  CLemmatizerGerman: public CLemmatizer
{
    void FilterSrc(string& src) const;
public:
    CLemmatizerGerman();
    virtual ~CLemmatizerGerman() {};
        
};





#endif //__LEMMATIZERS_H_

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
