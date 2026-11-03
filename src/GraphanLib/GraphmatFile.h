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
// ==========  Dialing Graphematical Module (www.aot.ru)
// ==========  Copyright by Alexey Sokirko (1996-2001), Bryan Jurish (2011)

#ifndef __GRAPHMATFILE_H_
#define __GRAPHMATFILE_H_

#include "UnitHolder.h"

class CGraphanDicts;
class CDictionary;

class CGraphmatFile  : public CUnitHolder
{
    std::string                                  m_LastError;
        


    // Analyzing
    bool            IsKey(size_t LB, size_t HB, size_t& GraLast) const;
    bool            FindKeySequence (const char* title, size_t i,size_t HB, size_t& GraLast)  const;
    bool                DealBullet (size_t i, size_t HB);
    bool            DealAsteriskBullet (size_t LB, size_t HB);
    int                     DealBulletsWithTwoBrackets (size_t StartPos, size_t EndPos);
    bool            DealEnglishStyleFIO (size_t StartPos, size_t EndPos);
    bool            DealAbbrev (size_t  StartPos, size_t EndPos);
    size_t          FindOborotto (size_t i, size_t HB, short& OborotNo, std::vector<WORD>& OborortIds) const;
    void            DealOborotto(size_t  HB);
    int                     DealReferences (size_t i,size_t HB);
    void            DealModifierKey (size_t LB, size_t HB);
    void            DealSimpleKey (size_t LB, size_t HB);
    void            DealKeySequence(size_t LB, size_t  HB);
    void            DealGermanDividedCompounds(size_t LB, size_t  HB);
    void            DealExtensionsAndLocalFileNames(size_t LB, size_t  HB);
    int                     HasIndention  (size_t LB, size_t HB);
    int                     CountEndL  (size_t LB, size_t HB);
    int                     CountSpaces  (size_t LB, size_t HB);
    int                     DealFIO (size_t i,size_t HB);
    int                     DealShortFIO(size_t i, size_t HB);
    void            DealNames (size_t LB, size_t  HB);
    bool            DealSentBreaker ();
    void            InitNonContextDescriptors (CGraLine& L);
    bool            GraphmatMain ();
    int                     InitContextDescriptors (size_t LB, size_t HB);                  
    void            MacSynHierarchy ();

        


public:
    const CGraphanDicts*    m_pDicts;
    bool                                    m_bConvertRussianJo2Je;

    size_t                                  m_MinParOfs;
    size_t                                  m_MaxParOfs;
    size_t                                  m_TabSize;
    // file for graphematical table
    std::string                                  m_GraOutputFile;
    // Ќужно ли запускать делилку на предложени€.
    bool                                    m_bSentBreaker;
    // нужно ли конвертировать латиницу в кириллицу внутри русского слова, если это возможно
    // (исправление ошибок)
    bool                                    m_bForceToRus;

    // пуста€ строка €вл€етс€ разделителем абазцев и предложений
    bool                                    m_bEmptyLineIsSentenceDelim;

    // использовать таг </p> дл€ разделени€ на параграфы
    bool                                    m_bUseParagraphTagToDivide;

    // использовать красную строку дл€ разделени€ на параграфы
    bool                                    m_bUseIndention;

    bool                                    m_bFilterUnprintableSymbols;

    bool                                    m_bRecognizeShortFIOs;
    // max length of sentence
    size_t                                  m_MaxSentenceLength;
        

    CGraphmatFile();
    ~CGraphmatFile();
        
    // processing 
    bool            LoadDicts();
    bool            LoadStringToGraphan(const std::string& szBuffer);
    const std::string&   GetLastError() const;
        
    //  browsing results 
        
    void                            GetGraphematicalLine (char* line, size_t NumLine) const;

    void                            WriteGraphMat (const char* FName) const;

        


        
};


#endif //__GRAPHMATFILE_H_

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
