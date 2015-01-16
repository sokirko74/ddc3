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
#ifndef __rus_numerals
#define __rus_numerals

#include  "utilit.h"

struct CNumeralToNumber
{
	char				m_Cardinal[25]; // "‰‚‡"
	char				m_Ordinal[25]; // "‚ÚÓÓÈ"
	char				m_Adverb[25]; // "¬ƒ¬Œ≈Ã"
	char				m_CoollectiveNumber[25]; //  "ƒ¬Œ≈"
	char				m_RomanNumber[25]; // II
	double				m_Number; // 2
    bool                m_bNoun; // false
};

const size_t NumeralToNumberCount = 40;
extern const CNumeralToNumber NumeralToNumber[];

extern string IntToStr (double i);
extern string FindByNumber(QWORD Number);
extern int IsAdverbRule(const string& Lemma);
extern double GetCardinalNumeral(const string& word);
extern QWORD GetOrdinalNumeral(const string& word);
extern QWORD GetNounNumeral(const string& word);


#endif


