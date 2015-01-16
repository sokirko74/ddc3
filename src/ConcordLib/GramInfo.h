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
#ifndef  GramInfo_h
#define  GramInfo_h


//! CGramInfo represents one morphological pattern, for example "[SUB pl, sg]"
struct CGramInfo 
{
	//! the language of the pattern 
	MorphLanguageEnum	m_Language;
	//! the part of speech mask  (SUB, ART,ADJ...)
	DWORD				m_PartOfSpeechMask;
	//! morphological features (plu, sig, nom...)
	QWORD				m_Grammems;

	CGramInfo () {
		m_PartOfSpeechMask = 0;
	    m_Grammems = 0;;
		m_Language = morphUnknown;

	};
	CGramInfo (MorphLanguageEnum Language, DWORD PartOfSpeechMask, QWORD Grammems)
	{ 
		m_PartOfSpeechMask = PartOfSpeechMask;
	    m_Grammems = Grammems;
		m_Language = Language;

	};
	

};

#endif
