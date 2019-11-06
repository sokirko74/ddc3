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

#ifndef ger_consts_h
 #define ger_consts_h




enum gPartOfSpeeches 
{
          gART  = 0, 
          gADJ = 1, 
          gADV = 2, 
          gEIG = 3, 
          gSUB = 4, 
          gVER = 5,
          gPA1  = 6, 
          gPA2 = 7, 
          gPRONOMEN = 8, 
          gPRP = 9, 
          gKON = 10, 
          gNEG = 11, 
          gINJ = 12, 
          gZAL = 13,  
          gZUS = 14, 
          gPRO_BEG = 15,
          gZU_INFINITIV = 16
};


enum gGrammems {
// unknown 0..3
gNoaUnk = 0, 
gPredikBenutz = 1, 
gProUnk = 2,
gTmpUnk = 3,


// eigennamen 4..14
gNac=4,
gMou=5,
gCou=6,
gGeo=7,
gWasser=8,
gGeb=9,
gStd=10,
gLok=11,
gVor=12,  

//  reflexive Verben
gSichAcc=13,
gSichDat=14,



// verb clasess 15..18
gSchwach=15,
gNichtSchwach=16,
gModal=17,
gAuxiliar=18,


// verb forms 19..26
gKonj1=19,
gKonj2=20,
gPartizip1=21,
gPartizip2=22,
gZuVerbForm=23,
gImperativ=24,
gPraeteritum=25,
gPrasens=26,

//adjective 27..29
gGrundform=27,
gKomparativ=28,
gSuperlativ=29,

// konjunk 30..34
gProportionalKonjunktion=30,
gInfinitiv=31, // used also for verbs
gVergleichsKonjunktion=32,
gNebenordnende=33,
gUnterordnende=34,



//pronouns 35..41
gPersonal=35,
gDemonstrativ=36,
gInterrogativ=37,
gPossessiv=38,
gReflexiv=39,
gRinPronomen=40,
gAlgPronomen=41,

//adjective's articles 42.44
gAdjektiveOhneArtikel=42,
gAdjektiveMitUnbestimmte=43,
gAdjektiveMitBestimmte=44,



//persons 44..47
gErstePerson=45,
gZweitePerson=46,
gDrittePerson=47,  

//genus 48..50
gFeminin=48,
gMaskulin=49,
gNeutrum=50,



// number 51..52
gPlural=51,
gSingular=52,


//cases 53..56
gNominativ=53,
gGenitiv=54,
gDativ=55,
gAkkusativ=56,

// abbreviation
gAbbreviation=57,

//Einwohnerbezeichnung
gEinwohner=58,

//
gTransitiv=59,
gIntransitiv=60,
gImpersonal=61


};




typedef enum {
        VERBSATZ_T =0,
        PARTIZIPIALSATZ_T = 1,
        INFINITIVSATZ_T=2
} gClauseTypeEnum;


#endif


#endif

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
