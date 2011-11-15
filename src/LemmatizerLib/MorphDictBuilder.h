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

#ifndef MorphDictBuilder_h
#define MorphDictBuilder_h


#include "MorphDict.h"
#include "MorphAutomBuilder.h"

#include "../MorphWizardLib/wizard.h"


class CMorphDictBuilder : public CMorphDict
{


	// m_ModelInfo[i][j] is a word which should be written into CTrieNodeBuild::m_Info
	//  where i is the index of MorphoWizard::m_FlexiaModels
	//  and j is a the index of CFlexiaModel::m_Flexia
	vector< vector <bool> >		m_ModelInfo;
	vector< DwordVector >	m_PrefixSets;

	
	void				ClearRegister();
	
	
	bool				CheckFlexiaGramInfo(const MorphoWizard& Wizard) const;
	bool				GeneratePrefixes(const MorphoWizard& Wizard);

	//  debug functions 
	bool				CheckRegister() const;
	
	CMorphAutomatBuilder*	GetFormBuilder() {return (CMorphAutomatBuilder*)m_pFormAutomat; };
	
	
	
public:
	CMorphDictBuilder(MorphLanguageEnum Language);
	~CMorphDictBuilder();

	bool	CreateAutomat(const MorphoWizard& Wizard);
	bool	GenerateLemmas(const MorphoWizard& Wizard);
	bool	GenerateUnitedFlexModels(const MorphoWizard& Wizard);
	bool	GenPredictIdx(const MorphoWizard& wizard, int PostfixLength, int MinFreq, string path);
};




#endif
