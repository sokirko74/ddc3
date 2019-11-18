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

#ifndef __AGRAMTABLib_LIBRARY_DEFINED__

#ifndef eng_consts_h
#define eng_consts_h


enum ePartOfSpeeches 
{
    eNOUN  = 0, 
    eADJ = 1, 
    eVERB = 2, 
    eVBE = 3, 
    eMOD = 4, 
    eNUMERAL = 5,
    eCONJ  = 6, 
    eINTERJ = 7, 
    ePREP = 8, 
    ePARTICLE = 9, 
    eART = 10, 
    eADV = 11, 
    ePN = 12, 
    eORDNUM = 13,  
    ePRON = 14,
    ePOSS = 15,
    ePN_ADJ = 16
};


enum eGrammems {
    eSingular = 0,
    ePlural = 1,
    eMasculinum = 2,
    eFeminum = 3,
    eAnimative = 4, 
    ePerfective = 5, 
    eNominative = 6, 
    eObjectCase = 7, 
    eNarrative = 8, 
    eGeographics = 9, 
    eProper = 10, 
    ePersonalPronoun = 11, 
    ePossessive = 12, 
    ePredicative = 13, 
    eUncountable = 14, 
    eReflexivePronoun = 15, 
    eDemonstrativePronoun = 16, 
    eMass = 17, 
    eComparativ  = 18, 
    eSupremum = 19,
    eFirstPerson = 20, 
    eSecondPerson = 21, 
    eThirdPerson = 22, 
    ePresentIndef = 23, 
    eInfinitive = 24,
    ePastIndef = 25,
    ePastParticiple = 26,
    eGerund = 27,
    eFuturum = 28,
    eConditional = 29,

    eApostropheS = 30,
    eApostrophe = 31,
    eNames = 32,
    eOrganisation = 33

};


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
