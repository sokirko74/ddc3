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
#include "../common/util_classes.h"
#include "../common/MorphXmlToken.h"
class TiXmlDocument;
class CRusCorpXmlFile{
public:
    FILE*               m_OutFile;
    string              m_SentenceStr;
    TiXmlDocument*      m_CurrSentXml;
    vector<CXmlToken>   m_CurrSentTokens;
    

    CRusCorpXmlFile();
    ~CRusCorpXmlFile();
    bool ReadNextSentence  (FILE* fp, bool PrintUnparsed);
    bool CreateGraTable();
    bool PrintDisambiguatedXmlNodes();
    bool WriteGramXml();
};


