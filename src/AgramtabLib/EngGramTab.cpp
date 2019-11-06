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
#include "StdGramtab.h"
#include "EngGramTab.h"


CEngGramTab :: CEngGramTab()
{
	for (size_t i = 0; i<GetMaxGrmCount(); i++) 
	    GetLine(i) = NULL;

}

CEngGramTab :: ~CEngGramTab()
{
	int Num = 0;
	for (size_t i=0; i<GetMaxGrmCount(); i++) 
		if (GetLine(i) != NULL) 
		{
			delete GetLine(i);
			Num++;
		};
};





bool CEngGramTab::GleicheGenderNumber(const char* gram_code1, const char* gram_code2) const
{
	return  false;
}

bool CEngGramTab::GleicheSubjectPredicate(const char* gram_code1, const char* gram_code2) const
{
	return  false;
}


bool CEngGramTab::IsStrongClauseRoot(const DWORD Poses)  const
{
	return	false;
};


bool CEngGramTab::is_small_number (const char* lemma) const  
{
   return false;
}

bool CEngGramTab::is_month (const char* lemma) const
{
	return false;
};

bool CEngGramTab::IsMorphNoun (size_t Poses)  const
{
	return  false;
};

bool CEngGramTab::is_morph_adj (size_t poses) const
{
	return  false;
};

bool CEngGramTab::is_morph_participle (size_t poses) const
{
	return  false;
};
 
bool CEngGramTab::is_morph_pronoun (size_t poses) const
{
	return  false;
};

bool CEngGramTab::is_morph_pronoun_adjective(size_t poses) const
{
	return  false;
};

bool CEngGramTab::is_left_noun_modifier (size_t poses, QWORD grammems) const
{
	return     false;
}


bool CEngGramTab::is_numeral (size_t poses) const
{ 
	return  false;
};

bool CEngGramTab::is_verb_form (size_t poses) const
{
	return     false;
};



bool CEngGramTab::is_infinitive(size_t poses) const
{
	return false; 
}

bool CEngGramTab::is_morph_predk(size_t poses) const
{
	return false;
}

bool CEngGramTab::is_morph_adv(size_t poses) const
{
	return false; 
}

bool CEngGramTab::is_morph_personal_pronoun (size_t poses, QWORD grammems) const
{
	return		false;
};

bool CEngGramTab::IsSimpleParticle(const char* lemma, size_t poses) const
{
	return false;
}







bool CEngGramTab::IsSynNoun(size_t Poses, const char* Lemma) const
{
	return false;
};

bool CEngGramTab::IsStandardParamAbbr (const char* WordStrUpper) const
{
	return false;
};



bool CEngGramTab::GleicheCase(const char* gram_code_noun, const char* gram_code_adj) const
{
	return false;
};
bool CEngGramTab::GleicheCaseNumber(const char* gram_code1, const char* gram_code2) const
{
	return false;
};
QWORD CEngGramTab::GleicheGenderNumberCase(const char* common_gram_code_noun, const char* gram_code_noun, const char* gram_code_adj) const 
{
	return 0;
};

bool CEngGramTab::is_morph_article(size_t poses)  const 
{
	return false;
};


void TestMem1() 
{
	string Result;
	Result.append("test",2);
}

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-default-style: "linux"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
