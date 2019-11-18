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
// ==========  Copyright by Alexey Sokirko, Dmitry Pankratov, Bryan Jurish (2011)

#ifndef __SYNANLib_LIBRARY_DEFINED__
#ifndef __AGRAMTABLib_LIBRARY_DEFINED__

#ifndef rus_consts_h
#define rus_consts_h



enum rPartOfSpeeches 
{
    NOUN  = 0, 
    ADJ_FULL = 1, 
    VERB = 2, 
    PRONOUN = 3, 
    PRONOUN_P = 4, 
    PRONOUN_PREDK = 5,
    NUMERAL  = 6, 
    NUMERAL_P = 7, 
    ADV = 8, 
    PREDK  = 9, 
    PREP = 10,
    POSL = 11,
    CONJ = 12,
    INTERJ = 13,
    INP = 14,
    PHRASE = 15,
    PARTICLE = 16,
    ADJ_SHORT = 17,
    PARTICIPLE = 18,
    ADVERB_PARTICIPLE = 19,
    PARTICIPLE_SHORT = 20,
    INFINITIVE = 21,
};

 

enum rGrammems {
    rPlural     = 0,
    rSingular   = 1,
    rAllNumbers = (1<<rSingular) | (1<<rPlural),

    rNominativ  = 2,
    rGenitiv    = 3,
    rDativ      = 4,
    rAccusativ  = 5,
    rInstrumentalis = 6,
    rLocativ    = 7,
    rVocativ    = 8,
    rAllCases   = (1<<rNominativ) | (1<<rGenitiv) | (1<<rDativ) | (1<<rAccusativ) | (1<<rInstrumentalis) | (1<<rVocativ) | (1<<rLocativ),

    rMasculinum = 9,
    rFeminum    = 10,
    rNeutrum    = 11,
    rMascFem    = 12,
    rAllGenders   = (1<<rMasculinum) | (1<<rFeminum) | (1<<rNeutrum),


    rPresentTense = 13,
    rFutureTense = 14,
    rPastTense = 15,
    rAllTimes   = (1<<rPresentTense) | (1<<rFutureTense) | (1<<rPastTense),

    rFirstPerson = 16,
    rSecondPerson = 17,
    rThirdPerson = 18,
    rAllPersons = (1 << rFirstPerson) | (1 << rSecondPerson) | (1 << rThirdPerson),

    rImperative = 19,

    rAnimative = 20,
    rNonAnimative = 21,
    rAllAnimative   = (1<<rAnimative) | (1<<rNonAnimative),

    rComparative = 22,

    rPerfective = 23,
    rNonPerfective = 24,

    rNonTransitive = 25,
    rTransitive = 26,

    rActiveVoice = 27,
    rPassiveVoice = 28,


    rIndeclinable = 29,
    rInitialism = 30,

    rPatronymic = 31,

    rToponym = 32,
    rOrganisation = 33,

    rQualitative = 34,
    rDeFactoSingTantum = 35,

    rInterrogative = 36,
    rDemonstrative = 37,

    rName      = 38,
    rSurName       = 39,
    rImpersonal = 40,
    rSlang = 41,
    rMisprint = 42,
    rColloquial = 43,
    rPossessive = 44,
    rArchaism = 45,
    rSecondCase = 46,
    rPoetry = 47,
    rProfession = 48,
    rSuperlative = 49,
    rPositive = 50
};




typedef enum {
    VERB_PERS_T=0,
    ADVERB_PARTICIPLE_T=1, 
    PARTICIPLE_SHORT_T=2,   
    ADJ_SHORT_T=3,
    PREDK_T=4, 
    PARTICIPLE_T=5, 
    INFINITIVE_T=6, 
    INP_T=7, 
    DASH_T=8,
    UNDETACHED_ADJ_PATIC=9,
    COMPARATIVE_T=10,
    COPUL_T=11
} rClauseTypeEnum ;


#endif


#endif
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
