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
// ==========  Copyright by Alexey Sokirko, Bryan Jurish (2011)

#ifndef __RUSGRAMTAB_H_
#define __RUSGRAMTAB_H_


#include "agramtab_.h"       
#include "rus_consts.h"       

/////////////////////////////////////////////////////////////////////////////

const unsigned int  StartUp =  0xC0E0; //\xc0\xe0\xa0
const unsigned int  EndUp = 0x10000;  //\xff\xff
const unsigned int MaxGrmCount  = EndUp -StartUp; // // 16159  (16 \xca\xe1) 
const BYTE rPartOfSpeechCount = 22;
// \xed\xe5 \xe4\xee\xeb\xe6\xed\xee \xe1\xfb\xf2\xfc \xef\xf0\xee\xe1\xe5\xeb\xee\xe2 \xec\xe5\xe6\xe4\xf3 \xf1\xeb\xee\xe2\xe0\xec\xe8 
const char rPartOfSpeeches[rPartOfSpeechCount][20] = 
{       "\xd1",  // 0
        "\xcf", // 1
        "\xc3", // 2
        "\xcc\xd1", // 3
        "\xcc\xd1-\xcf", // 4
        "\xcc\xd1-\xcf\xd0\xc5\xc4\xca", // 5
        "\xd7\xc8\xd1\xcb", // 6
        "\xd7\xc8\xd1\xcb-\xcf", // 7
        "\xcd", // 8
        "\xcf\xd0\xc5\xc4\xca", //9 
        "\xcf\xd0\xc5\xc4\xcb", // 10
        "\xcf\xce\xd1\xcb", // 11
        "\xd1\xce\xde\xc7", // 12
        "\xcc\xc5\xc6\xc4", // 13
        "\xc2\xc2\xce\xc4\xcd",// 14
        "\xd4\xd0\xc0\xc7", // 15
        "\xd7\xc0\xd1\xd2", // 16
        "\xca\xd0_\xcf\xd0\xc8\xcb",  // 17
        "\xcf\xd0\xc8\xd7\xc0\xd1\xd2\xc8\xc5", //18
        "\xc4\xc5\xc5\xcf\xd0\xc8\xd7\xc0\xd1\xd2\xc8\xc5", //19
        "\xca\xd0_\xcf\xd0\xc8\xd7\xc0\xd1\xd2\xc8\xc5", // 20
        "\xc8\xcd\xd4\xc8\xcd\xc8\xd2\xc8\xc2"  //21
};

const short GrammemsCount = 52;
const char Grammems[GrammemsCount][10] = { 
    // 0..1
    "\xec\xed","\xe5\xe4",
    // 2..8
    "\xe8\xec","\xf0\xe4","\xe4\xf2","\xe2\xed","\xf2\xe2","\xef\xf0","\xe7\xe2",
    // \xf0\xee\xe4 9-12
    "\xec\xf0","\xe6\xf0","\xf1\xf0","\xec\xf0-\xe6\xf0",
    // 13..15
    "\xed\xf1\xf2","\xe1\xf3\xe4","\xef\xf0\xf8",
    // 16..18
    "1\xeb","2\xeb","3\xeb", 
    // 19
    "\xef\xe2\xeb",
    // 20..21
    "\xee\xe4","\xed\xee",      
    // 22
    "\xf1\xf0\xe0\xe2\xed",
    // 23..24
    "\xf1\xe2","\xed\xf1",      
    // 25..26
    "\xed\xef","\xef\xe5",
    // 27..28
    "\xe4\xf1\xf2","\xf1\xf2\xf0",
    // 29-31
    "0", "\xe0\xe1\xe1\xf0", "\xee\xf2\xf7",
    // 32-33
    "\xeb\xee\xea", "\xee\xf0\xe3",
    // 34-35
    "\xea\xe0\xf7", "\xe4\xf4\xf1\xf2",
    // 36-37 (\xed\xe0\xf0\xe5\xf7\xe8\xff)
    "\xe2\xee\xef\xf0", "\xf3\xea\xe0\xe7\xe0\xf2",
    // 38..39
    "\xe8\xec\xff","\xf4\xe0\xec",
    // 40
    "\xe1\xe5\xe7\xeb",
    // 41,42
    "\xe6\xe0\xf0\xe3", "\xee\xef\xf7",
    // 43,44,45
    "\xf0\xe0\xe7\xe3", "\xef\xf0\xe8\xf2\xff\xe6", "\xe0\xf0\xf5",
    // \xe4\xeb\xff \xe2\xf2\xee\xf0\xee\xe3\xee \xf0\xee\xe4\xe8\xf2\xe5\xeb\xfc\xed\xee\xe3\xee \xe8 \xe2\xf2\xee\xf0\xee\xe3\xee \xef\xf0\xe5\xe4\xeb\xee\xe6\xed\xee\xe3\xee
    "2",
    "\xef\xee\xfd\xf2", "\xef\xf0\xee\xf4",
    "\xef\xf0\xe5\xe2", "\xef\xee\xeb\xee\xe6"
};




const int rClauseTypesCount = 12;
const char rClauseTypes [rClauseTypesCount][30] = 
{
    "\xc3\xcb_\xcb\xc8\xd7\xcd", 
    "\xc4\xcf\xd0",
    "\xca\xd0_\xcf\xd0\xd7",
    "\xca\xd0_\xcf\xd0\xc8\xcb",
    "\xcf\xd0\xc5\xc4\xca",
    "\xcf\xd0\xd7",   
    "\xc8\xcd\xd4",  
    "\xc2\xc2\xce\xc4",
    "\xd2\xc8\xd0\xc5",
    "\xcd\xd1\xce",
    "\xd1\xd0\xc0\xc2\xcd",
    "\xca\xce\xcf\xd3\xcb"
};




class CRusGramTab : public CAgramtab{
public:
    CAgramtabLine*  Lines[MaxGrmCount];
    CRusGramTab();
    ~CRusGramTab();

    BYTE                        GetPartOfSpeechesCount () const;
    const char*             GetPartOfSpeechStr(BYTE i) const;
    size_t                  GetGrammemsCount()  const;
    const char*             GetGrammemStr(size_t i) const;
    size_t                  GetMaxGrmCount() const;
    CAgramtabLine*&                 GetLine(size_t LineNo);
    const CAgramtabLine*    GetLine(size_t LineNo) const;
    size_t          s2i(const char * s )  const;
    string          i2s(WORD i) const;

    bool                ProcessPOSAndGrammems (const char* tab_str, BYTE& PartOfSpeech,  QWORD& grammems) const;
    const char* GetRegistryString() const;

    bool GleicheCase(const char* gram_code_noun, const char* gram_code_adj) const;
    bool GleicheCaseNumber(const char* gram_code1, const char* gram_code2) const;
    QWORD GleicheGenderNumberCase(const char* common_gram_code_noun, const char* gram_code_noun, const char* gram_code_adj) const;

    bool GleicheGenderNumber(const char* gram_code1, const char* gram_code2) const;
    bool GleicheSubjectPredicate(const char* gram_code1, const char* gram_code2) const;
    long GetClauseTypeByName(const char* TypeName) const;

    const char* GetClauseNameByType(long type) const;
    const size_t GetClauseTypesCount() const;

    bool IsStrongClauseRoot(const DWORD Poses) const;
    bool is_month (const char* lemma) const;
    bool is_small_number (const char* lemma) const;
    bool IsMorphNoun (size_t Poses)  const;
    bool is_morph_adj (size_t poses) const;
    bool is_morph_participle (size_t poses) const;
    bool is_morph_pronoun (size_t poses) const;
    bool is_morph_pronoun_adjective(size_t poses) const;
    bool is_left_noun_modifier  (size_t poses, QWORD grammems) const;
    bool is_numeral (size_t poses) const;
    bool is_verb_form (size_t poses) const;
    bool is_infinitive(size_t poses) const;
    bool is_morph_predk(size_t poses) const;
    bool is_morph_adv(size_t poses) const;
    bool is_morph_article(size_t poses) const;
    bool is_morph_personal_pronoun (size_t poses, QWORD grammems) const;
    bool IsSimpleParticle(const char* lemma, size_t poses) const;
    bool IsSynNoun(size_t Poses, const char* Lemma) const;
    bool IsStandardParamAbbr (const char* WordStrUpper) const;
        
};

extern bool GenderNumberCaseRussian (const CAgramtabLine* l1, const CAgramtabLine* l2);
extern bool FiniteFormCoordRussian (const CAgramtabLine* l1, const CAgramtabLine* l2);

#endif //__RUSGRAMTAB_H_

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
