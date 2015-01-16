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

// CCOMSyntaxHolder is a class which is created to work with Dialing Shallow Syntax
// via COM-interfaces. The main methods of the class are the following:
// 1. 	BOOL LoadSyntax(MorphLanguageEnum langua) - loading all dictionaries 
// of the syntax system into the memory for the  given language
// 2. 	BOOL GetSentencesFromSynAn(string str)  - building a syntax structure for 
//    the given text ("str")

 
#ifndef COMSyntaxHolder
#define COMSyntaxHolder

#include "utilit.h"
#include <comdef.h>
#include <atlbase.h>
#import "../../bin/Lemmatizer.tlb"
#import "../../bin/MAPost.tlb"
#import "../../bin/Agramtab.tlb"
#import "../../bin/Graphan.tlb"
#import "../../bin/Synan.tlb"

class CCOMSyntaxHolder
{
public:
	MorphLanguageEnum				m_CurrentLanguage;

	GRAPHANLib::IGraphmatFilePtr	m_piGraphan;
	LEMMATIZERLib::ILemmatizerPtr	m_piLemmatizer;
	AGRAMTABLib::IGramTabPtr		m_pGramTab;
	MAPOSTLib::IMAPostPtr m_piMAPost;
	SYNANLib::ISentencesCollectionPtr		m_piSentCollection;
	LEMMATIZERLib::IPLMLineCollectionPtr	m_piAfterMorphPlmLines;
	LEMMATIZERLib::IPLMLineCollectionPtr	m_piBeforeSyntaxPlmLines;

	CCOMSyntaxHolder();
	~CCOMSyntaxHolder();
	BOOL LoadSyntax(MorphLanguageEnum langua);
	
	void DeleteProcessors();
	BOOL LoadSyntaxModule(MorphLanguageEnum langua);

	BOOL BuildBeforeSyntax(string str, BOOL bFile, BOOL bWriteIntermFiles, BOOL bSaveIntermResults);
	BOOL BuildSyntax(BOOL bSaveIntermResults);
	BOOL GetSentencesFromSynAn(string str, BOOL bFile, BOOL bWriteIntermFiles, BOOL bSaveIntermResults);
	
	
	
};
extern string  GetClauseTypeDescr(MorphLanguageEnum	Language, const SYNANLib::IClausePtr& piClause, int ClauseRootNo);
#endif