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
#include "StdConc.h"
#include "ConcCommon.h"
#include "ConcIndexator.h"


bool	CConcIndexator::IndexMorphXml	(string FileName, const char* pFileBuffer, CTokenNo& NewCorpusEndTokenNo,string& strError)
{
	vector<CXmlToken> GraTable;
	CBibliography Bibliography;
	if (!m_Bibl.ReadMorphXmlFileIntoGraTable(FileName, pFileBuffer, GraTable, strError, Bibliography))
		return  false;

	CTokenNo StartTokenNo = NewCorpusEndTokenNo; 


	string TextBuffer;
	size_t GraLinesCount = GraTable.size();

	int SentNo = 0;
	bool bTheFirstPageBreakIsFound = false;
	char OneIndexLine[2048];
	DWORD LastSentenceBreak = NewCorpusEndTokenNo;
	for (long GraLineNo = 0; GraLineNo<GraLinesCount; GraLineNo++)
	{
		const CXmlToken& W = GraTable[GraLineNo];
		TextBuffer += W.m_WordStr; 
		TextBuffer += " "; 

		strcpy(OneIndexLine, W.m_WordStr.c_str());
		size_t wordlen = W.m_WordStr.length();
		OneIndexLine[wordlen] = globalFieldDelimeter;
		
		bool bPageBreak =  (W.m_Type == "pb");
		if (!bPageBreak)
		{
			if (W.m_Annots.empty() )
			{
				OneIndexLine[wordlen+1] = 0;
				if (!IndexOneToken(OneIndexLine, NewCorpusEndTokenNo))
				{
					strError = string(" Cannot index ")+OneIndexLine;
					return false;
				};
			}
			else
			{
				vector<string> Props;
				vector<string> Lemmas; 				
				

				for (size_t i=0; i< W.m_Annots.size(); i++)
				{
					const CXmlMorphAnnot& A = W.m_Annots[i];
					vector<string> CurrProps;
					A.GetAsSetOfProperties(CurrProps);
					Props.insert(Props.end(), CurrProps.begin(), CurrProps.end() );
					CurrProps.push_back(MorphAnnotationsDelim);

					Lemmas.push_back(A.m_Lemma);
				};

				strcpy(OneIndexLine+wordlen+1,GetIndexItemSetByVectorString(Props, false).c_str());
				size_t l = strlen (OneIndexLine);
				OneIndexLine[l] = globalFieldDelimeter;;
				strcpy (OneIndexLine+l+1, GetIndexItemSetByVectorString(Lemmas, false).c_str());

				if (!IndexOneToken(OneIndexLine, NewCorpusEndTokenNo))
				{
					strError = string(" Cannot index ")+OneIndexLine;
					return false;
				};
			};
		
			NewCorpusEndTokenNo++;

		}

		if(	W.m_bLastInSentence )
		{
			AddBreakByName("s", NewCorpusEndTokenNo);
			LastSentenceBreak = NewCorpusEndTokenNo;
			SentNo++;
		};


		if ( bPageBreak || (GraLineNo == 0))
		{
			CPageNumber Page;
			Page.m_PageNumber = 0;
			if (bPageBreak)
				Page.m_PageNumber = atoi(W.m_WordStr.c_str());
			if (Page.m_PageNumber == 0)
				Page.m_PageNumber = UnknownPageNumber;
			Page.m_StartTokenNo = LastSentenceBreak;
			AddPageBreak(Page);
		}
	};

	if (NewCorpusEndTokenNo != StartTokenNo)
	{
		// if at least one token is found, then add a bibliographical record
		if (!m_Bibl.AddIndexItem(Bibliography))
		{
			strError = "Cannot index bibliography " + Bibliography.WriteToString();
			return false;
		}
	};


	return true;
};

