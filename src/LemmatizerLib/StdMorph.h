//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2014 by Bryan Jurish
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
#ifndef StdMorph_h
#define StdMorph_h

#include <stdio.h>
#include "../common/util_classes.h"


#include "../GraphanLib/GraphmatFile.h"       // main symbols
#include "../AgramtabLib/RusGramTab.h"
#include "../AgramtabLib/EngGramTab.h"
#include "../AgramtabLib/GerGramTab.h"
#include "../MorphWizardLib/wizard.h"



#define HOMOWEIGHT_BIN_PATH			"homoweight.bin"		
#define WORDWEIGHT_BIN_PATH			"wordweight.bin"		
#define PREDICT_BIN_PATH			"npredict.bin"
#define MORPH_MAIN_FILES			"morph.bin"
#define OPTIONS_FILE				"morph.options"

const DWORD ErrorParadigmId			= 0xffffffff;


#endif
