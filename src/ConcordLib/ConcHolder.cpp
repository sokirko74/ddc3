//*-*- Mode: C++; c-basic-offset: 8; -*-*/
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
#include "ConcHolder.h"
#include "QueryCompiler.h"
#include "Bibliography.h"
#include "math.h"
#include "ddcString.h"


//==============================================================================
const time_t TheEndOfTheWorld = 0xffffffff;

#ifdef DETECT_MEMORY_LEAK
	#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
	#endif
#endif

//==============================================================================
//! indirect comparison operator for hits on CHit::m_SortKey.i (for std::sort); replaces IsLessByHitOrderId .
//! \li true string-based sorting occurs only at distributed server level
struct IsLessByHitSortKey
{
	const vector<CHit>& m_Base;	

	IsLessByHitSortKey(const vector<CHit>& Base)
		: m_Base (Base)
	{};

	bool operator() (size_t i1,  size_t i2) const 
	{
		return m_Base[i1].m_SortKey.i < m_Base[i2].m_SortKey.i;
	};
};

//==============================================================================
//! comparison operator for hits on CHit::m_FileNo (for std::sort)
struct IsLessByFileNo
{
	IsLessByFileNo()
	{};

	bool operator() (const CHit &h1, const CHit &h2) const 
	{ return h1.m_FileNo < h2.m_FileNo; };
};


//==============================================================================
//! direct comparison operator for hits on CHit::m_SortKey.i (for std::sort)
struct HitLessByCountValue {
	bool operator() (const CHit &a, const CHit &b) const
	{
		return a.m_Value.m_Count < b.m_Value.m_Count;
	};
};


//==============================================================================
// cannot create cross-platform heterogenious predicate lower_bound:
// http://groups.google.com/group/comp.std.c++/browse_thread/thread/151b0210b6266c2f?hl=en&lr=&safe=off&ic=1&seekm=MPG.143ab91a14f21268989743%40news.supernews.com
// that's why we are to create i
template <class IndexIterator>
IndexIterator my_lower_bound(IndexIterator First, IndexIterator Last, const CHitSortKey& Key, const vector<CHit>& Base)
{	
	size_t Count =  Last-First;
	
	while (Count > 0)
	{	
		// divide and conquer, find half that contains answer
		IndexIterator Mid = First;
		size_t Step = Count / 2;
		std::advance(Mid, Step);
		if (Base[*Mid].m_SortKey.i < Key.i) //-- use integer comparisons only here!
		{
			First = ++Mid;
			Count -= Step + 1;
		}
		else
			Count = Step;
	}
	return First;
}



void DeleteEOLN(string& txt)
{
	for( int i=0; i<txt.length(); i++ )
	{
		if (txt[i] == '\n')
			txt[i] = ' ';

		if (txt[i] == '\r')
			txt[i] = ' ';

		if (txt.substr(i,4) ==  "</p>")
			txt.erase(i,4);
	};
};



void  SpaceStartQuoteMarks (string& s)
{
	bool  bInQuoteMark=false;
	bool  bInSingleQuoteMark=false;

	const int len = s.length();

	for (int i=len-1; i>0; i--)
	{
		if (s[i] == '"')
		{
			if (s[i+1] == ' ')
			if (		bInQuoteMark 
					|| ( (i>0) && (s[i-1] == ':'))
				)
				swap(s[i], s[i+1]);

			bInQuoteMark = !bInQuoteMark;
		}

		if (s[i] == '\'')
		{
			if ( bInSingleQuoteMark && (s[i+1] == ' '))
				swap(s[i], s[i+1]);

			bInSingleQuoteMark = !bInSingleQuoteMark;
		};
	};

	for (int i=0; i<len-1; i++)
	{
		if ( (s[i] == '(') || (s[i] == '<') || (s[i] == '['))
		{
			if (s[i+1] == ' ')
				swap(s[i], s[i+1]);
			i++;
		};
	};
	if (		(len >  1) 
			&&	(s[1] == ' ')
			&&	(		(s[0] == '\'') 
					||	(s[0] == '"') 
				)
		)
		swap(s[0], s[1]);



};

//======================================================
void CShortOccurCache::Clear()
{
	m_IndexItemNo2Occurrences.clear();
	m_OccurrencesBody.clear();
}

size_t CShortOccurCache::AddNewIndexItemNoToCache(const CTokenNo* pStart, const CTokenNo* pEnd )
{
	m_IndexItemNo2Occurrences.push_back(CDataReference (m_OccurrencesBody.size(), pEnd-pStart));;
	m_OccurrencesBody.insert(m_OccurrencesBody.end(), pStart, pEnd);				
	return m_IndexItemNo2Occurrences.size() - 1;
}

const CTokenNo*	CShortOccurCache::GetOccurrencesFromCache(const int CacheId, DWORD& Length) const
{
	const CDataReference& R 	=  m_IndexItemNo2Occurrences[CacheId];
	Length = R.m_VectorLength;
	return &m_OccurrencesBody[R.m_VectorStartOffset];
}
bool				CShortOccurCache::CouldContainMore() const
{
	return m_OccurrencesBody.size()<MaxShortOccurCacheSize;
}

//======================================================
CConcHolder::CConcHolder ()
{
	m_ResultLimit = 0xffffffff;
	m_pIndexator = 0;
	m_pBreaks = 0;
	m_ResultFormat = DDC_ResultText;
	m_QueryEndTime	 = TheEndOfTheWorld;
	m_pQueryCompiler = new CQueryCompiler(this);
	m_pRandom    = new DDCRandom();
	m_RandomSeed = 0;
	m_bSortByString  = false;
	m_SortOrder = hsoNone;
};

CConcHolder::~CConcHolder()
{
	delete m_pRandom;
	delete m_pQueryCompiler;
};


void CConcHolder::AddFileReference(const long posFile)
{

	if (m_ResultFormat == DDC_ResultHTML)
	{
		m_QueryResultStr += "<P>";
		m_QueryResultStr += m_pIndexator->GetHtmlReference(posFile);
		m_QueryResultStr += "</P>";
	}
	else
	if (m_ResultFormat == DDC_ResultText)
	{
		m_QueryResultStr += m_pIndexator->GetShortFilename(posFile)+ " ### ";
	}
	else
	if (m_ResultFormat == DDC_ResultTable)
	{

		// nothing to do!
	}

};


void CConcHolder::ShowBibliographyForTextOrHtml(const CHit& Hit, DWORD PageNumber)
{
	// nothing to do for DDC_ResultTable!
	assert (m_ResultFormat != DDC_ResultTable);

	CBibliography B = m_pIndexator->m_Bibl.GetFullBibliographyOfHit(Hit.m_FileNo);

	string BiblStr;
	/*
		if <sourcedesc id="scan"> exists then 
			- take <bibl>...</bibl>
			- take <date id="first"> in <sourcedesc id="orig">
		else take <bibl>...</bibl> in <sourcedesc id="orig">
	*/
	if (m_pIndexator->IsGutenbergInterface() )
	{
		int dummy, birth, death;
		string Date = B.m_DateStr;
		if (sscanf(B.m_DateStr.c_str(),"%i.%i.%i-%i.%i.%i", &dummy, &dummy, &birth,&dummy, &dummy, &death)  == 6)
			Date = Format("(%i-%i)", birth, death);
		BiblStr = B.m_OrigBibl + " " + Date;
		BiblStr += string(" [") + m_pIndexator->GetShortFilename(Hit.m_FileNo)+"]";
		
	}
	else
	if (!B.m_ScanBibl.empty())
	{
		BiblStr = B.m_ScanBibl;
		if (!B.m_DateStr.empty())
		{
			string Date = B.m_DateStr;
			int year, month, date;
			if (sscanf(B.m_DateStr.c_str(),"%i-%i-%i", &year, &month, &date)  == 3)
				Date = Format("%i", year);
			BiblStr += " ["+ Date +"]";
		};
	}
	else
		BiblStr = B.m_OrigBibl;

	if (BiblStr.empty())
		BiblStr = m_pIndexator->GetShortFilename(Hit.m_FileNo);

	if (BiblStr.empty())
		BiblStr = m_pIndexator->m_CorpusFiles[Hit.m_FileNo];

	// ======== special DWDS preprocessing of page numbers
	if ( m_pIndexator->IsDwdsCorpusInterface() )
	{
		int i = BiblStr.rfind("S.");
		if (i != string::npos)
		{
			
			//if <bibl>...</bibl> ends with "S. {CARD}" then omit page generation

			for (i+=2;i < BiblStr.length(); i++)
				if (		(BiblStr[i] != ' ')
						&&	!isdigit((BYTE)BiblStr[i])
					)
					break;

			if (i == BiblStr.length())
				PageNumber = UnknownPageNumber;

		};
	};
	// ======== end of special DWDS preprocessing


	if (m_ResultFormat == DDC_ResultHTML)
	{
		m_QueryResultStr += "<br> <b>"; 
		m_QueryResultStr +=  BiblStr;
		if (PageNumber != UnknownPageNumber)
			m_QueryResultStr +=  Format(" Page %u", PageNumber);
		m_QueryResultStr += " ";
		m_QueryResultStr += m_pIndexator->m_Bibl.GetVisibleFreeHeaderBiblAttributes(Hit.m_FileNo, " ");
		m_QueryResultStr += "</b>";
		m_QueryResultStr +=  "<br>";

	}
	else
	if (m_ResultFormat == DDC_ResultText)
	{
		m_QueryResultStr +=   BiblStr;
		m_QueryResultStr += " ### ";
		if (PageNumber != UnknownPageNumber)
			m_QueryResultStr +=  Format("%u", PageNumber);
		else
			m_QueryResultStr +=  Format("-1");
		m_QueryResultStr += " ### ";
		m_QueryResultStr += B.m_DateStr;
		m_QueryResultStr += m_pIndexator->m_Bibl.GetVisibleFreeHeaderBiblAttributes(Hit.m_FileNo, " ### ");
		m_QueryResultStr += " ### ";

		//-- rank stuff / text
		if (m_pQueryCompiler->m_pQuery->m_Options->m_bDebugRank) {
			const char* DebugInfo = (const char*)(void*)(&m_DebugInfo[0]) + Hit.m_Value.m_DebugRankNo;
			m_QueryResultStr += Format(" %s ### ",DebugInfo);
		}

#if 0 /*-- incompatible with v1.x --*/
		//-- index list / text
		for (vector<size_t>::const_iterator fi = m_pIndexator->m_IndicesToShow.begin(); fi != m_pIndexator->m_IndicesToShow.end(); fi++) {
			const CStringIndexSet& I = *m_pIndexator->m_Indices[*fi];
			m_QueryResultStr.push_back(' ');
			m_QueryResultStr += I.m_ShortName;
		}
		m_QueryResultStr += " ### ";
#endif
	}
	
};



string BuildHtmlHitStrWithHighlighting (const vector<COutputToken>& Tokens, bool bConvertASCIIToHtmlSymbols,const CHighlightTags& HighlightTags, bool bUseAnchorSpan, const string &tokenDelimiter="")
{

	// ===============  creating string ======================
	string HitStr;
	const char StartHighl = 1;
	const char EndHighl = 2;

	for (int i=0; i< Tokens.size(); i++)
	{
		HitStr += tokenDelimiter;

		if	(		(i>0)
				&&	(		!ispunct((BYTE)Tokens[i].m_TokenStr[0])
						||	( Tokens[i].m_TokenStr == "-" )
					)
				
			)
			HitStr += " ";

		if (bUseAnchorSpan && !Tokens[i].m_InterpStr.empty())
			HitStr += "<span title=\"" + Tokens[i].m_InterpStr +"\">";

		if (Tokens[i].m_Highlight)
			HitStr += StartHighl;

		// ===============  convert to html if it needs ======================
		if (bConvertASCIIToHtmlSymbols)
			HitStr += ConvertASCIIToHtmlSymbols(Tokens[i].m_TokenStr);
		else
			HitStr += Tokens[i].m_TokenStr;

		if (!bUseAnchorSpan && !Tokens[i].m_InterpStr.empty())
			HitStr += Tokens[i].m_InterpStr;

		if (Tokens[i].m_Highlight)
			HitStr += EndHighl;

		if (bUseAnchorSpan && !Tokens[i].m_InterpStr.empty())
			HitStr += "</span>";

	}

	// ===============  spacing quotes ======================
	SpaceStartQuoteMarks(HitStr);

	// ===============  convert to html if it needs ======================
	//if (bConvertASCIIToHtmlSymbols && !bUseAnchorSpan)
		//HitStr = ConvertASCIIToHtmlSymbols(HitStr);

	Trim(HitStr);

	// ===============  replace StartHighl and  EndHighl with the given arguments======================
	int CountOfHiglightedWords = 0; 
	string Result;
	for (size_t i=0; i<HitStr.length(); i++)
		if (HitStr[i] == StartHighl)
			Result += (CountOfHiglightedWords == 0) ? HighlightTags.m_FirstOpener : HighlightTags.m_RestOpener;
		else
			if (HitStr[i] == EndHighl)
			{
				Result += (CountOfHiglightedWords == 0) ? HighlightTags.m_FirstCloser : HighlightTags.m_RestCloser;
				CountOfHiglightedWords++;
			}
			else
				Result += HitStr[i];

	

	return Result;
};

//-- moo: BuildJsonContextString(): adapted from BuildHtmlHitStrWithHighlighting()
//   + returns a JSON array of token structures
//#define  JSON_USE_DDC_SPACING
#undef   JSON_USE_DDC_SPACING
#undef   JSON_USE_HASH
#undef   JSON_SHORT_FILENAMES
string CConcHolder::BuildJsonContextString (const vector<COutputToken>& Tokens, bool doHighlight) const
{
    //==================================================
    // create hit string
    bool utf8 = m_pIndexator->m_Utf8;
    char hlbuf[32];
    string js("");

    for (int i=0; i< Tokens.size(); i++) {
	if (doHighlight) {
	    //-- highlighting (full info) mode: only for hit "body"
	    vector<string> fields = m_pIndexator->GetTokenFields(Tokens[i]);
	
	    if (i>0) {
		js.push_back(',');
#ifdef JSON_USE_DDC_SPACING
		//-- old-style punctuation-sensitive spacing
		if (!ispunct((BYTE)Tokens[i].m_TokenStr[0]) || (Tokens[i].m_TokenStr == "-"))
		    fields[0].insert(0, 1, ' ');
#endif // defined(JSON_USE_DDC_SPACING)
	    }
	
#ifdef JSON_USE_HASH
	    //-- return each token as a json hash
	    js.push_back('{');
	    for (size_t fi=0; fi < fields.size(); fi++) {
		const CStringIndexSet& I = *m_pIndexator->m_Indices[m_pIndexator->m_IndicesToShow[fi]];
		if (fi>0) js.push_back(',');
		js.append(jsonStr(I.m_ShortName, utf8));
		js.push_back(':');
		js.append(jsonStr(fields[fi], utf8));
	    }
	    js += ",\"hl_\":";
	    if (Tokens[i].m_Highlight) {
		    sprintf(hlbuf, "%u", Tokens[i].m_Highlight);
		    js.append(hlbuf);
	    } else {
		    js.push_back('0');
	    }
	    js.push_back('}');

#else // !defined(JSON_USE_HASH)

	    //-- return each token as a json array (with 0th elt ~ highlighting flag)
	    js.push_back('[');
	    if (Tokens[i].m_Highlight) {
		    sprintf(hlbuf, "%u", Tokens[i].m_Highlight);
		    js.append(hlbuf);
	    } else {
		    js.push_back('0');
	    }
	    js.push_back(',');
	    for (vector<string>::const_iterator fi=fields.begin(); fi != fields.end(); fi++) {
		if (fi != fields.begin()) js.push_back(',');
		js += jsonStr(*fi, utf8);
	    }
	    js.push_back(']');
#endif // defined(JSON_HASH)
	}
	else {
	    //-- non-highlighting mode
	    string wtxt = Tokens[i].m_TokenStr;
	    if (i>0) {
		js.push_back(',');
#ifdef JSON_USE_DDC_SPACING
		//-- old-style punctuation-sensitive spacing
		if (!ispunct((BYTE)Tokens[i].m_TokenStr[0]) || (Tokens[i].m_TokenStr == "-"))
		    wtxt.insert(0, 1, ' ');
#endif // defined(JSON_USE_DDC_SPACING)
	    }
	    js += jsonStr(wtxt, utf8);
	}
    }

    return js;
}



bool CConcHolder::GetContext(int  StartBreakNo, int  EndBreakNo, const DWORD CurrFileNo,  const bool bConvertASCIIToHtmlSymbols, string& Result) const
{
	Result = "";
	if (m_pQueryCompiler->m_pQuery->m_Options->m_HitTypeStr == PredefinedFileBreakName) return true;

	if (StartBreakNo == EndBreakNo) 
	{
		Result =  "";
		return true;
	};

	Result = "    ";
	const DWORD FileStartTokenNo =  m_pIndexator->GetFileStartTokenNo(CurrFileNo);
	const DWORD FileEndTokenNo =  m_pIndexator->GetFileBreaks()[CurrFileNo];
	const vector<CTokenNo>& Breaks = GetBreaks();
	for  (int BreakNo = StartBreakNo; BreakNo < EndBreakNo; BreakNo++)
	{
		if (BreakNo < 0) continue;
		if (BreakNo >= Breaks.size()) continue;
		const CTokenNo& B = Breaks[BreakNo];
		if	(  	    (B > FileStartTokenNo) 
				&&	(B <= FileEndTokenNo)
			)
		{
			
			assert (!m_pIndexator->m_IndicesToShow.empty());
			vector<COutputToken> Tokens;
			if (!GetTokensFromStorageByBreak(m_pIndexator->m_IndicesToShow[0], BreakNo, Tokens))
			{
				ErrorMessage(Format("Cannot get sentence: BreakNo=%i,BreakEndTokenNo=%i,  FileNo=%i\n", BreakNo, B, CurrFileNo));
				return false;
			};


			string Hit =  BuildHtmlHitStrWithHighlighting(Tokens, bConvertASCIIToHtmlSymbols, CHighlightTags(), false, m_pIndexator->m_TokenDelimiter);
			if (m_ResultFormat == DDC_ResultTable)
				Hit = "<s>"+Hit+"</s>";
			Result += Hit + "    ";
		};
	};
	return true;
};

bool CConcHolder::GetContextJson(int StartBreakNo, int EndBreakNo, const DWORD CurrFileNo, string& js) const
{
    js.clear();
    if (m_pQueryCompiler->m_pQuery->m_Options->m_HitTypeStr == PredefinedFileBreakName)
	return true;

    if (StartBreakNo == EndBreakNo) 
	return true;

    const DWORD FileStartTokenNo =  m_pIndexator->GetFileStartTokenNo(CurrFileNo);
    const DWORD FileEndTokenNo =  m_pIndexator->GetFileBreaks()[CurrFileNo];
    const vector<CTokenNo>& Breaks = GetBreaks();
    for  (int BreakNo = StartBreakNo; BreakNo < EndBreakNo; BreakNo++) {
	if (BreakNo < 0) continue;
	if (BreakNo >= Breaks.size()) continue;

	const CTokenNo& B = Breaks[BreakNo];
	if ((B > FileStartTokenNo) && (B <= FileEndTokenNo)) {
	    assert (!m_pIndexator->m_IndicesToShow.empty());
	    vector<COutputToken> Tokens;

	    if (!GetTokensFromStorageByBreak(m_pIndexator->m_IndicesToShow[0], BreakNo, Tokens)) {
		ErrorMessage(Format("Cannot get sentence: BreakNo=%i,BreakEndTokenNo=%i,  FileNo=%i\n", BreakNo, B, CurrFileNo));
		return false;
	    }

	    if (!js.empty()) js.push_back(',');
	    js += BuildJsonContextString(Tokens, false);
	};
    };
    return true;
};


bool CConcHolder::ShowBibliographyForTable(DWORD PageNumber, const CHit& Hit, const vector<COutputToken>& Tokens)
{
	string KeyWords;
	for (int i=0; i< Tokens.size(); i++)
		if (		Tokens[i].m_Highlight 
				&&	(		(i==0)
						||	(find(Tokens.begin(), Tokens.begin()+i-1,Tokens[i])== Tokens.begin()+i-1)
					)
			) // print only unique keywords 
			KeyWords += string("<orth>")+ConvertASCIIToHtmlSymbols(Tokens[i].m_TokenStr)+" </orth>";
		
	CBibliography B = m_pIndexator->m_Bibl.GetFullBibliographyOfHit(Hit.m_FileNo);
	string PageNumberStr = (PageNumber == UnknownPageNumber) ? "unknown" : Format("%u",PageNumber);
	

	m_QueryResultStr += (string("file") + globalTableItemsDelim + m_pIndexator->m_CorpusFiles[Hit.m_FileNo] + globalTableItemsDelim
			     + string("scan") + globalTableItemsDelim +  ConvertASCIIToHtmlSymbols(B.m_ScanBibl) + globalTableItemsDelim 
			     + string("orig") + globalTableItemsDelim +  ConvertASCIIToHtmlSymbols(B.m_OrigBibl) + globalTableItemsDelim 
			     + string("page") + globalTableItemsDelim +  PageNumberStr + globalTableItemsDelim 
			     + string("date") + globalTableItemsDelim +  ConvertASCIIToHtmlSymbols(B.m_DateStr) + globalTableItemsDelim
			     + string("keyword") + globalTableItemsDelim + KeyWords);

	m_QueryResultStr += m_pIndexator->m_Bibl.GetFreeHeaderBiblAttributesWithNames(Hit.m_FileNo, globalTableItemsDelim) + globalTableItemsDelim;

	//-- rank stuff / table
	if (HasRankOrderOperator()) {
		m_QueryResultStr += string("rank") + globalTableItemsDelim + Format("%d", Hit.m_SortKey.i) + globalTableItemsDelim;
		if (m_pQueryCompiler->m_pQuery->m_Options->m_bDebugRank) {
			const char* DebugInfo = (const char*)(void*)(&m_DebugInfo[0]) + Hit.m_Value.m_DebugRankNo;
			m_QueryResultStr += string("rank_debug") + globalTableItemsDelim + DebugInfo + globalTableItemsDelim;
		}
	}

	//-- index list / table
	m_QueryResultStr += string("indices") + globalTableItemsDelim;
	for (vector<size_t>::const_iterator fi = m_pIndexator->m_IndicesToShow.begin(); fi != m_pIndexator->m_IndicesToShow.end(); fi++) {
		const CStringIndexSet& I = *m_pIndexator->m_Indices[*fi];
		m_QueryResultStr.push_back(' ');
		m_QueryResultStr += I.m_ShortName;
	}
	m_QueryResultStr += globalTableItemsDelim;

	return true;
};




bool CConcHolder::GenerateOneHitString(DWORD PageNumber, const CHit& Hit, const vector<COutputToken>& Tokens)
{
    if (m_ResultFormat == DDC_ResultJson)
	return GenerateOneHitStringJson(PageNumber, Hit, Tokens);

	bool bConvASCIIToHtml = m_ResultFormat != DDC_ResultText;
	
	// ===========   generate hit header   ===================
	if (m_ResultFormat == DDC_ResultDocIds)
	{
		m_QueryResultStr += Format("%u", Hit.m_FileNo);
	}
	else
	if (m_ResultFormat == DDC_ResultTable) 
		ShowBibliographyForTable(PageNumber, Hit, Tokens);
	else
		if ( m_pQueryCompiler->m_pQuery->m_Options->m_bEnableBibliography && m_pIndexator->OutputBibliographyOfHits() )
			ShowBibliographyForTextOrHtml(Hit, PageNumber);
		else
			AddFileReference(Hit.m_FileNo);

	//-- rank stuff / html
	if (m_ResultFormat==DDC_ResultHTML && HasRankOrderOperator()) {
		if (!m_pQueryCompiler->m_pQuery->m_Options->m_bDebugRank) {
			m_QueryResultStr += Format("<i>Rank = %i</i><br>", Hit.m_SortKey.i > 0 ? Hit.m_SortKey.i : -Hit.m_SortKey.i);
		} else {
			const char* DebugInfo = (const char*)(void*)(&m_DebugInfo[0]) + Hit.m_Value.m_DebugRankNo;
			m_QueryResultStr += Format("<i>%s</i><br>",DebugInfo);
		}
	}
	
	// =============  add left hit context   ==================
	{
		
		string LeftContext;
		if (!GetContext((int)Hit.m_BreakNo-(int)m_pQueryCompiler->m_pQuery->m_Options->m_ContextSentencesCount, Hit.m_BreakNo,  Hit.m_FileNo,  bConvASCIIToHtml, LeftContext )) 
		{
			ErrorMessage("Error while getting the left-hand context");
			return false;
		};
		m_QueryResultStr += LeftContext;
	}



	// ===========   generate hit body ====================
	
	switch (m_ResultFormat) {
	case DDC_ResultHTML: 
		m_QueryResultStr += BuildHtmlHitStrWithHighlighting(Tokens, bConvASCIIToHtml, m_pIndexator->m_HtmlHighlighting, true, m_pIndexator->m_TokenDelimiter);
		break;
	case DDC_ResultText:
		m_QueryResultStr += BuildHtmlHitStrWithHighlighting(Tokens, bConvASCIIToHtml, m_pIndexator->m_TextHighlighting, false, m_pIndexator->m_TokenDelimiter);
		break;
	case DDC_ResultTable:
		//m_QueryResultStr += "<s part=\"m\">"+ BuildHtmlHitStrWithHighlighting(Tokens,bConvASCIIToHtml, CHighlightTags(), false, m_pIndexator->m_TokenDelimiter) + "</s>";
		m_QueryResultStr += "<s part=\"m\">"+ BuildHtmlHitStrWithHighlighting(Tokens,bConvASCIIToHtml, m_pIndexator->m_TableHighlighting, false, m_pIndexator->m_TokenDelimiter) + "</s>";
		break;
	case DDC_ResultDocIds :
		break; // no hit body  
	};

	// =============   add right hit context  =================
	{
		string RightContext;
		if (!GetContext(Hit.m_BreakNo+1, Hit.m_BreakNo+m_pQueryCompiler->m_pQuery->m_Options->m_ContextSentencesCount+1, Hit.m_FileNo, bConvASCIIToHtml, RightContext )) 
		{
			ErrorMessage("Error while  getting the right-hand context");
			return false;
		};
		m_QueryResultStr += RightContext;
	};

	return true;

}

//==============================================================================

//#define DEBUG_HIT_JSON 1
//#undef DEBUG_HIT_JSON

bool CConcHolder::GenerateOneHitStringJson(DWORD PageNumber, const CHit& Hit, const vector<COutputToken>& Tokens)
{
    bool utf8 = m_pIndexator->m_Utf8;
	
    //==================================================
    // hit header
    // + adapted from: ShowBibliographyForTable(PageNumber, Hit, Tokens)
    CBibliography B = m_pIndexator->m_Bibl.GetFullBibliographyOfHit(Hit.m_FileNo);
    string pageStr = (PageNumber == UnknownPageNumber) ? "null" : Format("%u",PageNumber);
    string hitStr  = (string("{\"meta_\":{")

#if JSON_SHORT_FILENAMES
		      + "\"file_\":" + jsonStr(m_pIndexator->GetShortFilename(Hit.m_FileNo), utf8)
#else
		      + "\"file_\":" + jsonStr(m_pIndexator->m_CorpusFiles[Hit.m_FileNo], utf8)
#endif // JSON_SHORT_FILENAMES

		      + ",\"scan_\":" + jsonStr(B.m_ScanBibl, utf8)
		      + ",\"orig_\":" + jsonStr(B.m_OrigBibl, utf8)
		      + ",\"date_\":" + jsonStr(B.m_DateStr, utf8)
		      + ",\"page_\":" + pageStr
#ifdef DEBUG_HIT_JSON
		      + ",\"breakno_\":" + Format("%u",  (uint)Hit.m_BreakNo)
		      + ",\"highlight_\":" + Format("%u",(uint)Hit.m_HighlightOccurrenceEnd)
		      + ",\"fileno_\":" + Format("%u",   (uint)Hit.m_FileNo)
		      + ",\"breakstart_\":" + Format("%u",  (uint)(Hit.m_BreakNo==0 ? 0 : GetBreaks()[Hit.m_BreakNo-1]))
		      + ",\"key_\":[" + Format("%d", Hit.m_SortKey.i) + "," + jsonStr(Hit.m_SortKey.s, utf8) + "]"
#endif
		      );
    if (m_pIndexator->OutputBibliographyOfHits()) {
	hitStr += "," + m_pIndexator->m_Bibl.GetFreeHeaderBiblAttributesJson(Hit.m_FileNo, utf8);
    }

    if (HasRankOrderOperator()) {
	    hitStr += Format(",\"rank_\":%d", Hit.m_SortKey.i);
	    if (m_pQueryCompiler->m_pQuery->m_Options->m_bDebugRank) {
		    const char* DebugInfo = (const char*)(void*)(&m_DebugInfo[0]) + Hit.m_Value.m_DebugRankNo;
		    hitStr += ",\"rank_debug_\":" + jsonStr(DebugInfo, utf8);
	    }
    }

#ifndef JSON_USE_HASH
    //-- json tokens are returned as arrays: return the indedx-list to be nice
    hitStr += ",\"indices_\":[";
    const vector<size_t> &ishow = m_pIndexator->m_IndicesToShow;
    for (size_t ii=0; ii < ishow.size(); ii++) {
	    if (ii!=0) hitStr.push_back(',');
	    hitStr += jsonStr(m_pIndexator->m_Indices[ishow[ii]]->m_ShortName, utf8);
    }
    hitStr.push_back(']');
#endif

    //==================================================
    // hit context

    hitStr += "},\"ctx_\":[";

    //------------------------------------------
    // hit context: left
    {
	string LeftContext;
	if (!GetContextJson((int)Hit.m_BreakNo-(int)m_pQueryCompiler->m_pQuery->m_Options->m_ContextSentencesCount, Hit.m_BreakNo,  Hit.m_FileNo, LeftContext )) {
	    ErrorMessage("Error while getting the left-hand context");
	    return false;
	}
	hitStr += "[" + LeftContext + "],";
    }


    //------------------------------------------
    // hit context: center (aka "body")
    hitStr += "[" + BuildJsonContextString(Tokens,true) + "],";

    //------------------------------------------
    // hit context: right
    {
	string RightContext;
	if (!GetContextJson(Hit.m_BreakNo+1, Hit.m_BreakNo+m_pQueryCompiler->m_pQuery->m_Options->m_ContextSentencesCount+1, Hit.m_FileNo, RightContext ))  {
	    ErrorMessage("Error while  getting the right-hand context");
	    return false;
	}
	hitStr += "[" + RightContext + "]";
    }
    hitStr += "]}";

    //-- append hit to m_QueryResultStr
    m_QueryResultStr += hitStr;

    return true;
}



bool CConcHolder::GetTokensFromStorageByBreak(size_t IndexNo, size_t BreakNo, vector<COutputToken>& Tokens) const
{
	Tokens.clear();

	DWORD StartTokenNo = (BreakNo==0) ?  0: GetBreaks()[BreakNo-1];
	DWORD EndTokenNo = GetBreaks()[BreakNo];
	if (IndexNo > m_pIndexator->m_Indices.size()) return false;
	const CStringIndexSet& I = *m_pIndexator->m_Indices[IndexNo];
	if (!I.GetTokensFromStorage(StartTokenNo, EndTokenNo, Tokens)) 
	{
		concord_daemon_log(Format ("Error! Cannot read hit no %i \n",BreakNo));
		return false;
	};
	return true;
};


bool CConcHolder::GetFileSnippets(const int HitNo, vector<COutputToken>& ResultTokens)  const
{
	const size_t ContextSize = 4;
	ResultTokens.clear();

	const int BreakNo = m_Hits[HitNo].m_BreakNo; 

	DWORD StartTokenNo = (BreakNo==0) ?  0: GetBreaks()[BreakNo-1];
	DWORD EndTokenNo = GetBreaks()[BreakNo];

	vector<CTokenNo> positions;
	{
		vector<CTokenNo>::const_iterator start = (HitNo != 0) ? m_HighlightOccurs.begin()+m_Hits[HitNo-1].m_HighlightOccurrenceEnd : m_HighlightOccurs.begin();
		vector<CTokenNo>::const_iterator end = m_HighlightOccurs.begin()+m_Hits[HitNo].m_HighlightOccurrenceEnd;
		positions.insert(positions.begin(), start,end);
		sort(positions.begin(), positions.end());
	}

	set<CTokenNo> DifferentTokens;
	{
		vector<COutputToken> TempTokens;
		set<string> DifferentWords;
		DWORD CurrentStarter = StartTokenNo;
		set<CTokenNo> OtherKwicTokens;

		for (vector<CTokenNo>::const_iterator i=positions.begin(); i < positions.end(); i++)
		{
			CTokenNo  pos = *i;
			if (CurrentStarter > pos) continue;
			if (!m_pIndexator->GetTokenIndex()->GetTokensFromStorage(pos, pos+1, TempTokens)) 
			{
				concord_daemon_log(Format ("Error! Cannot read hit no %i \n",BreakNo));
				return false;
			}
			if (DifferentWords.insert(TempTokens[0].m_TokenStr).second)
			{
				DifferentTokens.insert(pos);
				// output only the first ten kwic-lines
				if (DifferentTokens.size() == m_pIndexator->m_NumberOfKwicLinesInSnippets)
					break;
			}
			else
				OtherKwicTokens.insert(pos);


			// the snippets should be disjoint  
			CurrentStarter = min (pos+m_pIndexator->m_RightKwicContextSize+1, EndTokenNo);
		};
		
		if (DifferentTokens.size() < m_pIndexator->m_NumberOfKwicLinesInSnippets)
		{
			for (set<CTokenNo>::const_iterator pos_it = OtherKwicTokens.begin(); pos_it != OtherKwicTokens.end(); pos_it++)
			{
				DifferentTokens.insert(*pos_it);
				if (DifferentTokens.size() == m_pIndexator->m_NumberOfKwicLinesInSnippets)
					break;
			}
		}
		

	}


	for (set<CTokenNo>::const_iterator pos_it = DifferentTokens.begin(); pos_it != DifferentTokens.end(); pos_it++)
	{
		CTokenNo  pos = *pos_it;
		int start_kwic_line = max ( ((m_pIndexator->m_LeftKwicContextSize>=pos)?0:pos-m_pIndexator->m_LeftKwicContextSize), StartTokenNo);
		int end_kwic_line = min (pos+m_pIndexator->m_RightKwicContextSize+1, EndTokenNo);
		vector<COutputToken> CurrTokens;
		if (!m_pIndexator->GetTokenIndex()->GetTokensFromStorage(start_kwic_line, end_kwic_line, CurrTokens)) 
		{
			concord_daemon_log(Format ("Error! Cannot read hit no %i \n",BreakNo));
			return false;
		};
		for (size_t i=0; i<end_kwic_line-start_kwic_line; i++)
		{
			CurrTokens[i].m_Highlight = binary_search(positions.begin(), positions.end(), start_kwic_line + i) ? 1 : 0;
			ResultTokens.push_back(CurrTokens[i]);
		};
		ResultTokens.push_back(COutputToken("...", false));
	};

	return true;
};

DDCErrorEnum CConcHolder::GenerateHitStrings(const int StartHitNo) 
{
	assert(m_pQueryCompiler!=NULL);
	assert(m_pQueryCompiler->m_pQuery!=NULL);
	if (m_SortOrder == hsoAscendingCounts)
		return GenerateCountStrings(StartHitNo);

	DwordVector PageBreaks;

	m_pIndexator->ConvertHitsToPageBreaks(m_Hits.begin(), m_Hits.end(), GetBreaks(), PageBreaks);

	m_QueryResultStr = "";

	int end = min (m_Hits.size(), StartHitNo + m_ResultLimit);
	for(DWORD EndHitNo = StartHitNo; EndHitNo<end; EndHitNo++ )
	{
		const int BreakNo = m_Hits[EndHitNo].m_BreakNo;

		if (m_ResultFormat == DDC_ResultJson && EndHitNo==StartHitNo)
			m_QueryResultStr.push_back('[');

		vector<COutputToken> Tokens;
		if (m_pQueryCompiler->m_pQuery->m_Options->m_HitTypeStr == PredefinedFileBreakName)
		{
			if (!GetFileSnippets(EndHitNo, Tokens))
				return errReadSourceFile;
		}
		else
		{
			assert (!m_pIndexator->m_IndicesToShow.empty());
			if (!GetTokensFromStorageByBreak(m_pIndexator->m_IndicesToShow[0], BreakNo, Tokens)) 
					return errReadSourceFile;

			// next indices add to anchors, starting from the second index ()
			for (size_t indno=1; indno< m_pIndexator->m_IndicesToShow.size(); indno++)
			{
				vector<COutputToken> Interps;
				if (!GetTokensFromStorageByBreak(m_pIndexator->m_IndicesToShow[indno], BreakNo, Interps))
				{
					ErrorMessage(Format("Cannot get sentence: IndexNo=%i, BreakNo=%i\n", m_pIndexator->m_IndicesToShow[indno], BreakNo));
					return errReadSourceFile;
				};
				assert ( Interps.size() == Tokens.size() );
				for (size_t tkn_no=0; tkn_no<Interps.size(); tkn_no++)
				{
					//if (Interps[tkn_no].m_TokenStr == ddc_archive_stub)
					if (!Interps[tkn_no].m_TokenStr.empty())
						if (m_ResultFormat != DDC_ResultHTML)
							Tokens[tkn_no].m_InterpStr +=  m_pIndexator->m_InterpDelimiter+Interps[tkn_no].m_TokenStr;
						else
							Tokens[tkn_no].m_InterpStr +=  Interps[tkn_no].m_TokenStr + " ";
					//else
					//	Tokens[tkn_no].m_InterpStr +=  m_pIndexator->m_InterpDelimiter;
											
				}
			}


			size_t start_occ = (EndHitNo == 0) ? 0 : m_Hits[EndHitNo-1].m_HighlightOccurrenceEnd;
			size_t end_occ   = m_Hits[EndHitNo].m_HighlightOccurrenceEnd;
			vector<CTokenNo>::const_iterator start = m_HighlightOccurs.begin() + start_occ;
			vector<CTokenNo>::const_iterator end   = m_HighlightOccurs.begin() + end_occ;
			const DWORD StartHitTokenNo = (BreakNo == 0) ? 0 : GetBreaks()[BreakNo-1];
			const bool  bUseMatchIds    = !m_HighlightIds.empty();

			for( long line=0; line<Tokens.size(); line++ )
			{
				vector<CTokenNo>::const_iterator found = find(start, end, StartHitTokenNo + line);
				if (found != end)
					Tokens[line].m_Highlight = (bUseMatchIds ? m_HighlightIds[start_occ + (found-start)] : 1);
			}
		}

		const DWORD& PageNumber = m_pIndexator->GetPageNumber(PageBreaks[EndHitNo]);
		
		if (!GenerateOneHitString(PageNumber, m_Hits[EndHitNo], Tokens))
			return errReadSourceFile;

		if (m_ResultFormat==DDC_ResultHTML) {
		    m_QueryResultStr += "<BR>";
		}
		else if (m_ResultFormat==DDC_ResultJson) {
		    m_QueryResultStr.push_back(EndHitNo < end-1 ? ',' : ']');
		    m_QueryResultStr.push_back('\n');
		}
		else {
		    m_QueryResultStr.push_back('\n');
		}
		m_QueryResultStr += m_AdditionalHitDelimeter;
	};

	return errNone;
};

DDCErrorEnum CConcHolder::GenerateCountStrings(const int StartHitNo) 
{
	assert(m_pQueryCompiler!=NULL);
	assert(m_pQueryCompiler->m_pQuery!=NULL);


	int end = min (m_Hits.size(), StartHitNo + m_ResultLimit);
	m_QueryResultStr = "";
	
	if (m_ResultFormat == DDC_ResultJson)
		m_QueryResultStr.push_back('[');

	for (DWORD EndHitNo = StartHitNo; EndHitNo<end; EndHitNo++ ) {
		GenerateCountString(m_QueryResultStr, m_ResultFormat, m_Hits[EndHitNo]);
		if (m_ResultFormat == DDC_ResultJson) {
			m_QueryResultStr.push_back(EndHitNo < end-1 ? ',' : ']');
			m_QueryResultStr.push_back('\n');
		}
		m_QueryResultStr += m_AdditionalHitDelimeter;
	}

	return errNone;
};

void CConcHolder::DecorateQueryResults(const string& FormatStr, string& QueryResultStr)
{
	if (GetResultFormatByString(FormatStr) == DDC_ResultHTML)
		QueryResultStr = "<HTML> <BODY>\n" +  QueryResultStr +  "\n</BODY></HTML>";
};

void CConcHolder::InitFileReferences(vector<CHit>&	Hits) const
{
	const vector<CTokenNo>& Breaks = GetBreaks();
	const vector<CTokenNo>& FileBreaks = m_pIndexator->GetFileBreaks();
	size_t HitsCount = Hits.size();
	for (size_t HitNo=0; HitNo< HitsCount; HitNo++)
	{
		CHit&  H = Hits[HitNo];
		const CTokenNo& Break = Breaks[H.m_BreakNo];
		vector<CTokenNo>::const_iterator it = lower_bound (FileBreaks.begin(), FileBreaks.end(), Break);
		assert (it <  FileBreaks.end());
		H.m_FileNo  = it - FileBreaks.begin();
		H.m_SortKey = H.m_BreakNo;  // no sort 
	};
};

struct COccurrenceAndQueryNodeIndex 
{
	CTokenNo m_TokenNo;
	BYTE m_NodeIndex;
	COccurrenceAndQueryNodeIndex (CTokenNo TokenNo,	BYTE NodeIndex)
	{
		m_TokenNo = TokenNo;
		m_NodeIndex = NodeIndex;
	}
	bool operator < (const COccurrenceAndQueryNodeIndex& X) const
	{	
		return m_TokenNo < X.m_TokenNo;
	}
};

struct CHitRank 
{
	// the begining of the most representative passage 
	size_t			m_PassageStart;
	// the end of the most representative passage 
	size_t			m_PassageEnd;
	// the frequences of all query items indexed by Node Index for the current hit
	vector<size_t>	m_QueryNodeFreqs;
	// the frequences of all query items indexed by Node Index for the whole collection
	vector<double>	m_IDFs;
};

// OccurrenceAndQueryNodeIndex is the array of all occurrences for this seacrh period.
//  start_pos is  the starting point in  OccurrenceAndQueryNodeIndex of occurrences for the current hit.
//  end_pos is  the end point in  OccurrenceAndQueryNodeIndex of occurrences for the current hit.
// GetHitRankLen returns a CHitRank structure.
void GetHitRankLen(vector<COccurrenceAndQueryNodeIndex >& OccurrenceAndQueryNodeIndex, int start_pos, int end_pos, CHitRank& Result) 
{
	sort (OccurrenceAndQueryNodeIndex.begin()+start_pos,  OccurrenceAndQueryNodeIndex.begin()+end_pos);

	// PrevPositionOfNode[i] - the index of the prev node of the same type
	vector<CTokenNo> PrevPositionOfNode(end_pos-start_pos, DWORD_MAX);
	CTokenNo iFirstIndex = DWORD_MAX; // iFirstIndex is  the first element of the passage

	size_t QueryNodesCount = Result.m_QueryNodeFreqs.size();
	fill(Result.m_QueryNodeFreqs.begin(), Result.m_QueryNodeFreqs.end(), 0);

	{	// get PrevPositionOfNode and iFirstIndex
		vector<CTokenNo> PrevNodes(QueryNodesCount, DWORD_MAX);
		for(size_t i=start_pos; i <  end_pos; i++)
		{
			// take the previous node of the same type (of the same Node Index)
			CTokenNo& PrevNode = PrevNodes[OccurrenceAndQueryNodeIndex[i].m_NodeIndex];
			if (PrevNode != DWORD_MAX) // it is not the first node of this type
				PrevPositionOfNode[i-start_pos] = PrevNode; // set the previous node
			PrevNode = i-start_pos;

			// increment frequence
			Result.m_QueryNodeFreqs[OccurrenceAndQueryNodeIndex[i].m_NodeIndex]++;
		}
		for(size_t i=0; i <  PrevNodes.size(); i++)
			if (PrevNodes[i] != DWORD_MAX) // PrevNodes[i] == DWORD_MAX, then this query node is not found for this hit
				iFirstIndex = min(iFirstIndex, OccurrenceAndQueryNodeIndex[PrevNodes[i]+start_pos].m_TokenNo);
	}

	size_t MinPassageLen = DWORD_MAX;
	for(size_t i=end_pos-1; i >= start_pos; i--)
	{
		size_t  len = OccurrenceAndQueryNodeIndex[i].m_TokenNo - iFirstIndex;
		if (len <= MinPassageLen) // the closer to the beginning, the better, that's why here we use <= (not  <)
		{

			MinPassageLen = len;
			Result.m_PassageStart = iFirstIndex;
			Result.m_PassageEnd = OccurrenceAndQueryNodeIndex[i].m_TokenNo+1;
		}
		CTokenNo PrevNode = PrevPositionOfNode[i-start_pos];
		if (PrevNode == DWORD_MAX) 
			break;
		if (OccurrenceAndQueryNodeIndex[PrevNode+start_pos].m_TokenNo < iFirstIndex )
			iFirstIndex = OccurrenceAndQueryNodeIndex[PrevNode+start_pos].m_TokenNo;
	}
	
}

void CConcHolder::InitSortByRank(const CQuery *pQuery) const
{
	const vector<CTokenNo>& Breaks = GetBreaks();
	vector<CHit>& Hits = pQuery->m_Node->m_Hits;
	const bool bShowDebugRank = pQuery->m_Options->m_bDebugRank;
	size_t HitsCount = Hits.size();
	CHitRank HitRank;
	size_t NodeIndicesCount = m_pQueryCompiler->GetNodeIndicesCount();
	HitRank.m_QueryNodeFreqs.resize(NodeIndicesCount);

	// initializing idf for all query items
	for (size_t i=0; i < NodeIndicesCount; i++)
	{
		double cf = pQuery->m_Node->GetNodeFrequencyByNodeIndex(i);
		double c = (double)Breaks.size();
		// we have no document frequence, that's why we use collection frequence, which can be more than "c".
		if (cf > c)
			cf = c;
		// calculating augmemented inverde document frequence
		HitRank.m_IDFs.push_back(  log ((c+0.5)/cf)/log (c+1) );
	}

	
	vector<COccurrenceAndQueryNodeIndex > OccurrenceAndQueryNodeIndex;	
	{
		const vector<BYTE>& NodeIndices = pQuery->m_Node->m_OccurrenceNodeIndices;
		const vector<CTokenNo>& Occurrences = pQuery->m_Node->m_Occurrences;
		assert (Occurrences.size() == NodeIndices.size());
		size_t  Count = Occurrences.size();
		OccurrenceAndQueryNodeIndex.reserve(Count);
		for (size_t i=0;  i < Count; i++)
			OccurrenceAndQueryNodeIndex.push_back( COccurrenceAndQueryNodeIndex(Occurrences[i], NodeIndices[i]) );
		
	}
	double AverageHitLength = m_pIndexator->GetCorpusEndTokenNo()/Breaks.size();

	if (m_pIndexator->m_Bibl.IsRegisteredBiblField("PageRank"))
		m_pIndexator->m_Bibl.InitSortByBiblIntegerField("PageRank", pQuery->m_Node->m_Hits);
	else
		for (size_t HitNo=0; HitNo< HitsCount; HitNo++)
			Hits[HitNo].m_SortKey = 0;
	
	for (size_t HitNo=0; HitNo< HitsCount; HitNo++)
	{
		CHit&  H = Hits[HitNo];
		DWORD StartTokenNo = (H.m_BreakNo==0) ?  0: GetBreaks()[H.m_BreakNo-1];
		int start_occur = (HitNo == 0) ? 0 : Hits[HitNo-1].m_HighlightOccurrenceEnd;
		int end_occur =  Hits[HitNo].m_HighlightOccurrenceEnd;
		GetHitRankLen(OccurrenceAndQueryNodeIndex, start_occur, end_occur, HitRank);
		double HitSize  = (H.m_BreakNo==0) ? Breaks[H.m_BreakNo] : Breaks[H.m_BreakNo] - Breaks[H.m_BreakNo-1];
		double tfidf = 0;
		for (size_t i=0; i < NodeIndicesCount; i++)
		{
			double  freq_l = HitRank.m_QueryNodeFreqs[0];
			// calculating augmemented term frequence
			double tf_l  =  freq_l/(freq_l + 0.5  + 1.5*HitSize/AverageHitLength);
			const double beta = 0.4;
			double tfidf_l = beta + (1-beta)*tf_l*HitRank.m_IDFs[i];
			tfidf += tfidf_l;
		}
		tfidf = m_pIndexator->m_TfIdfRank*tfidf/(double)NodeIndicesCount;
		double near_rank = m_pIndexator->m_NearRank		/ ( (double)(HitRank.m_PassageEnd - HitRank.m_PassageStart) / (double)NodeIndicesCount);
		int pos_from_the_hit_beginning = HitRank.m_PassageStart - StartTokenNo + 1;
		double position_rank = m_pIndexator->m_PositionRank	/(double)pos_from_the_hit_beginning;
		double rank =	(tfidf + near_rank + position_rank) / 3;
		int SortKey = H.m_SortKey.i+(int)(rank*(double)1000);
		if (bShowDebugRank)
		{
			H.m_Value.m_DebugRankNo = m_DebugInfo.size();
			string DebugInfo = Format("Rank=%i (tfidf=%05f near=%05f pos=%05f(%i) PR=%i)", 
							SortKey, tfidf, near_rank, position_rank, 
							pos_from_the_hit_beginning, H.m_SortKey.i);
			for (size_t c=0; c < DebugInfo.size(); c++)
				m_DebugInfo.push_back(DebugInfo[c]);
			m_DebugInfo.push_back(0);
		}
		H.m_SortKey = SortKey; // H.m_SortKey contains already page rank
	}
}

void CConcHolder::InitSortBySize(const CQuery *pQuery) const
{
	const vector<CTokenNo>& Breaks = GetBreaks();
	size_t HitsCount = pQuery->m_Node->m_Hits.size();
	for (size_t HitNo=0; HitNo< HitsCount; HitNo++)
	{
		CHit&  H = pQuery->m_Node->m_Hits[HitNo];
		DWORD BreakNo = H.m_BreakNo;
		H.m_SortKey = (BreakNo==0) ? Breaks[BreakNo] : Breaks[BreakNo] - Breaks[BreakNo-1];
	}
}

void CConcHolder::InitSortByRandom(const CQuery *pQuery) const
{
	size_t HitsCount = pQuery->m_Node->m_Hits.size();
	for (size_t HitNo=0; HitNo< HitsCount; HitNo++)
	{
		CHit&  H = pQuery->m_Node->m_Hits[HitNo];
		//unsigned short ostate0=m_pRandom->m_state[0], ostate1=m_pRandom->m_state[1], ostate2=m_pRandom->m_state[2]; //-- DEBUG RANDOM
		H.m_SortKey = m_pRandom->random_n();
		//concord_daemon_log( Format("InitSortByRandom: RandomSeed=%d, state=[%d,%d,%d]; HitNo=%u, SortKey.i=%d", m_RandomSeed, ostate0,ostate1,ostate2, HitNo, H.m_SortKey.i) ); //-- DEBUG RANDOM
	}
}

void CConcHolder::InitSortByContext(const CQuery *pQuery, const CDDCFilterWithBounds& F) const
{
	CStringIndexSet* pIdx = (F.m_AttrName.empty()
				 ? m_pIndexator->GetTokenIndex()
				 : m_pIndexator->GetIndexByNameOrShortName(F.m_AttrName));
	CQueryNode   *qnod = pQuery->m_Node;
	vector<CHit>& Hits = qnod->m_Hits;
	DWORD HitsCount = qnod->m_Hits.size();
	const vector<CTokenNo>& Breaks = GetBreaks();
	const vector<BYTE> &occur_ids = qnod->m_OccurrenceMatchIds;

	if (!pIdx)
		throw CExpc(errOther, Format("CConcHolder::InitSortByContext(): Error: could not find index `%s' for context sort", F.m_AttrName.c_str()));

	for (DWORD HitNo=0; HitNo< HitsCount; HitNo++) {
		CHit& H = Hits[HitNo];
		DWORD StartTokenNo = (H.m_BreakNo==0) ?  0 : Breaks[H.m_BreakNo-1];
		DWORD EndTokenNo   = Breaks[H.m_BreakNo];

		//-- get context anchor occurrence-index occur_i
		DWORD occur_i;
		if (qnod->m_bUseMatchIds && F.m_ContextMatchId!=0) {
			//-- get occur_i: WITH match-ids
			switch (F.m_FilterType) {
			case LessByLeftContext:
			case GreaterByLeftContext:
				//-- #left : stick to FIRST id-matching token in each hit
				occur_i = qnod->GetFirstOccurrenceInHit(HitNo, F.m_ContextMatchId);
				break;

			case LessByRightContext:
			case GreaterByRightContext:
				//-- #right : stick to FINAL id-matching token in each hit
				occur_i = qnod->GetLastOccurrenceInHit(HitNo, F.m_ContextMatchId);
				break;

			case LessByMiddleContext:
			case GreaterByMiddleContext:
			default:
				//-- #middle : stick to MIDDLE id-matching token in each hit
				occur_i = qnod->GetMiddleOccurrenceInHit(HitNo, F.m_ContextMatchId);
				break;
			}
		}
		else {
			//-- get occur_i: WITHOUT match-ids
			switch (F.m_FilterType) {
			case LessByLeftContext:
			case GreaterByLeftContext:
				//-- #left : stick to FIRST match-token in each hit
				occur_i = (HitNo == 0) ? 0 : Hits[HitNo-1].m_HighlightOccurrenceEnd;
				break;

			case LessByRightContext:
			case GreaterByRightContext:
				//-- #right : stick to FINAL match-token in each hit
				occur_i = H.m_HighlightOccurrenceEnd - 1;
				break;

			case LessByMiddleContext:
			case GreaterByMiddleContext:
			default:
				//-- #middle : stick to MIDDLE match-token of each hit
				{
					DWORD occur_li = occur_i = (HitNo == 0) ? 0 : Hits[HitNo-1].m_HighlightOccurrenceEnd;
					DWORD occur_ri = H.m_HighlightOccurrenceEnd - 1;
					occur_i = occur_li + (occur_ri-occur_li)/2;
				}
				break;
			}
		}

		//-- assign sort key
		CTokenNo keyId = (occur_i >= qnod->m_Occurrences.size() ? EndTokenNo : (qnod->m_Occurrences[occur_i] + F.m_ContextOffset));
		if (keyId >= StartTokenNo && keyId < EndTokenNo && (H.m_SortKey.i=pIdx->GetTokenIndexId(keyId)) != DWORD_MAX) {
			//-- usual case: within target break and with a valid item id
			H.m_SortKey.s = pIdx->GetIndexItemStr( pIdx->m_Index[H.m_SortKey.i] );
		} else {
			//-- break-overflow (EOS etc) or invalid key item: treat as empty sort-key
			H.m_SortKey = INT_MIN;
		}
	}
}


void CConcHolder::InitSortKeyForHits(const CQuery *pQuery, const CDDCFilterWithBounds& Filter)
{
	assert (Filter.m_FilterType != HitSortsCount);

	//-- defaults
	m_bSortByString = false;
	m_SortOrder     = Filter.SortOrder();

	//-- guts
	switch (Filter.m_FilterType)
	{
	case GreaterByDate:
	case LessByDate:
		m_pIndexator->m_Bibl.InitSortByDate(pQuery->m_Node->m_Hits);
		break;

	case GreaterByRank:
	case LessByRank:
		InitSortByRank(pQuery);
		break;

	case LessByMiddleContext:
	case GreaterByMiddleContext:
	case LessByLeftContext:
	case GreaterByLeftContext:
	case LessByRightContext:
	case GreaterByRightContext:
		InitSortByContext(pQuery,Filter);
		m_bSortByString = true;
		break;

	case GreaterBySize:
	case LessBySize:
		InitSortBySize(pQuery);
		break;

	case NoSort: // NoSort is used for filtering, must be ascending
	case GreaterByFreeBiblField:
	case LessByFreeBiblField:	
		m_pIndexator->m_Bibl.InitSortByBiblIntegerField(Filter.m_AttrName, pQuery->m_Node->m_Hits);
		m_bSortByString = (m_pIndexator->m_Bibl.GetBiblFieldTypeId(Filter.m_AttrName) == cfbiString);
		break;

	case RandomSort:
		InitSortByRandom(pQuery);
		break;
	};
}

//==============================================================================
//#define DEBUG_HIT_SORT 1
#undef DEBUG_HIT_SORT

//==============================================================================

DDCErrorEnum CConcHolder::GetAllHits(const string &Query, size_t Limit) 
{
	return GetAllHits(m_pQueryCompiler->m_pQuery, Limit);
}

DDCErrorEnum CConcHolder::GetAllHits(CQuery *QueryRoot, size_t Limit) 
{
	assert(QueryRoot != NULL);
	m_bStoppedByUser = false;
	m_ShortOccurCaches.clear();
	ClearQueryResults();

	//-- check for count-queries
	CQuery  *qRoot=QueryRoot;
	CQCount *qCount=NULL;
	size_t qLimit = Limit;
	if (IsUniversalCountQuery(QueryRoot)) {
		//-- count(*) query: do memory-optimized computation
		return GetUniversalCounts(QueryRoot, Limit);
	}
	else if (typeid(*QueryRoot) == typeid(CQCount)) {
		//-- count() query: remember count-node but evaluate (all) daughter hits
		qCount = (CQCount*)QueryRoot;
		qRoot  = qCount->m_dtr;
		qLimit = qCount->m_sample;
		m_CountSample = 0;
	} 
	CQueryNode    *qNode = qRoot->m_Node;
	CQueryOptions *qOpts = qRoot->m_Options;
	vector<CHit>  &qHits = qNode->m_Hits;

	bool   bUseMatchIds   = qNode->m_bUseMatchIds;
	size_t CountOfPeriods = m_pIndexator->GetSearchPeriodsCount(); 
	time_t last_time;
	DDCErrorEnum rc = errNone;

	if (m_QueryEndTime != TheEndOfTheWorld)
			time(&last_time);

	vector<bool> bFilesUses(m_pIndexator->m_CorpusFiles.size(), false);
	

	for (m_CurrentSearchPeriodNo = 0;  m_CurrentSearchPeriodNo < CountOfPeriods; m_CurrentSearchPeriodNo++)
	{
		m_pQueryCompiler->Evaluate(qRoot);
		InitFileReferences(qHits);

		vector<size_t>		PeriodHitsIndex;
		if (m_pIndexator->m_MaskedFiles.empty()) {
			for (size_t i=0; i < qHits.size(); i++)
				PeriodHitsIndex.push_back(i);
		}
		else {
			for (size_t i=0; i < qHits.size(); i++)
				if (m_pIndexator->m_MaskedFiles.find(qHits[i].m_FileNo) == m_pIndexator->m_MaskedFiles.end())
					PeriodHitsIndex.push_back(i);
		}

		m_SortOrder = hsoNone; //-- no sort
		for (size_t FilterNo = 0; FilterNo < qOpts->m_Filters.size(); FilterNo++) {
			const CDDCFilterWithBounds& F = qOpts->m_Filters[FilterNo];

			//-- init Hits::m_SortKey (always initialized in raw ascending order)
			InitSortKeyForHits(qRoot,F);

			size_t hits_start, hits_end;
			if (m_SortOrder >= 0) {
				//-- ascending sort (also run for NoSort, since #has_field[] filters need bounds-checking)
				stable_sort(PeriodHitsIndex.begin(), PeriodHitsIndex.end(), IsLessByHitSortKey(qHits));
				hits_start = my_lower_bound(PeriodHitsIndex.begin(), PeriodHitsIndex.end(), F.m_KeyLo, qHits) - PeriodHitsIndex.begin();
				hits_end   = my_lower_bound(PeriodHitsIndex.begin(), PeriodHitsIndex.end(), F.m_KeyHi, qHits) - PeriodHitsIndex.begin();
			}
			else if (m_SortOrder < 0) {
				//-- descending sort
				stable_sort(PeriodHitsIndex.rbegin(), PeriodHitsIndex.rend(), IsLessByHitSortKey(qHits));
				hits_start = my_lower_bound(PeriodHitsIndex.rbegin(), PeriodHitsIndex.rend(), F.m_KeyHi, qHits) - PeriodHitsIndex.rbegin();
				hits_end   = my_lower_bound(PeriodHitsIndex.rbegin(), PeriodHitsIndex.rend(), F.m_KeyLo, qHits) - PeriodHitsIndex.rbegin();
				hits_start = PeriodHitsIndex.size()-hits_start;
				hits_end   = PeriodHitsIndex.size()-hits_end;
			}
			else {
				//-- no sort
				hits_start = 0;
				hits_end   = PeriodHitsIndex.size();
			}

#if DEBUG_HIT_SORT //-- DEBUG
			fprintf(stderr, "DEBUG[pre-trim,period=%d/%d,filter=%s(%s),order=%d]: KeyLo={%d,%s}, KeyHi={%d,%s}, hits_start=%zd, hits_end=%zd\n",
				m_CurrentSearchPeriodNo, CountOfPeriods,
				HitSortEnumNames[F.m_FilterType], F.m_AttrName.c_str(), m_SortOrder,
				F.m_KeyLo.i, jsonStr(F.m_KeyLo.s).c_str(),
				F.m_KeyHi.i, jsonStr(F.m_KeyHi.s).c_str(),
				hits_start, hits_end);
			for (size_t phi=0; phi < PeriodHitsIndex.size(); phi++) {
				const CHit &h=qHits[ PeriodHitsIndex[phi] ];
				fprintf(stderr, "DEBUG: periodHits[%zd] = qHits[%zd] = {m_BreakNo=%u, m_HighlightOccurrenceEnd=%u, m_SortKey={%d,%s}, m_FileNo=%u}\n",
					phi, PeriodHitsIndex[phi], h.m_BreakNo, h.m_HighlightOccurrenceEnd, h.m_SortKey.i, jsonStr(h.m_SortKey.s).c_str(), h.m_FileNo);
			}
#endif //-- DEBUG

			if (hits_end < hits_start) hits_start = hits_end;
			PeriodHitsIndex.erase(PeriodHitsIndex.begin()+hits_end, PeriodHitsIndex.end());
			PeriodHitsIndex.erase(PeriodHitsIndex.begin(), PeriodHitsIndex.begin()+hits_start);

			if (F.m_bSet) {
				// we have to intersect F.m_SatisfiedValues with qHits using integer sort-key m_CHit::m_SortKey.i
				vector<size_t>::const_iterator hits_start = PeriodHitsIndex.begin();
				vector<size_t>::const_iterator hits_end = PeriodHitsIndex.end();
				set<int>::const_iterator val_start = F.m_SatisfiedValues.begin();
				set<int>::const_iterator val_end = F.m_SatisfiedValues.end();
				vector<size_t> NewHitsIndex;

				assert( F.SortOrder() >= 0 ); //-- parallel traversal intersection only works for ascending sort!
				while (hits_start != hits_end && val_start != val_end) {
					int i1 = qHits[*hits_start].m_SortKey.i;
					int i2 = *val_start;
							
					if (i1 < i2)
						hits_start++;
					else if (i2 < i1)
						val_start++;
					else {
						NewHitsIndex.push_back(*hits_start);
						hits_start++;
					}
				}
				NewHitsIndex.swap(PeriodHitsIndex);
			}
		}

		m_AllHitsCount += PeriodHitsIndex.size();

		//-- add period-local hits to m_Hits and highlight occurrences
		// + we ought to merge-sort here e.g. with std::inplace_merge()
		//   *but* we also need to keep m_HighlightOccurs[] aligned with m_Hits[]
		// + current solution is full post-retrieval re-sort in calling method CConcHolder::GetHits()
		size_t Count = min(qLimit, PeriodHitsIndex.size());
		for (size_t i=0; i < Count; i++) {
			size_t  HitNo = PeriodHitsIndex[i];
			const CHit &H = qHits[ HitNo ];
				
			int start_index = (HitNo == 0) ? 0 : qHits[HitNo-1].m_HighlightOccurrenceEnd;
			m_HighlightOccurs.insert(m_HighlightOccurs.end(),
						 qNode->m_Occurrences.begin()+start_index,
						 qNode->m_Occurrences.begin()+H.m_HighlightOccurrenceEnd
						 );
			if (bUseMatchIds)
				m_HighlightIds.insert(m_HighlightIds.end(),
						      qNode->m_OccurrenceMatchIds.begin()+start_index,
						      qNode->m_OccurrenceMatchIds.begin()+H.m_HighlightOccurrenceEnd
						      );
			m_Hits.push_back(H);
			m_Hits.back().m_HighlightOccurrenceEnd = m_HighlightOccurs.size();
		}

		// calculate m_RelevantDocumentCount if it is necessary
		if (m_pIndexator->m_bShowNumberOfRelevantDocuments) {
			size_t Count = PeriodHitsIndex.size();
			for (size_t i=0; i <Count; i++) {
				DWORD FileNo = qHits[ PeriodHitsIndex[i] ].m_FileNo;
				if (!bFilesUses[ FileNo ]) {
					bFilesUses[ FileNo ] = true;
					m_RelevantDocumentCount++;
				}
			}
		}


		if (!m_Hits.empty()) {
			//-- inexpensive hack to check that m_HighlightOccurrs[] and m_Hits[] are aligned 1:1
			assert (m_Hits.back().m_HighlightOccurrenceEnd == m_HighlightOccurs.size());
		}

		// compute period-local counts
		if (qCount != NULL) {
			rc = GetPeriodCounts(qCount);
			if (rc != errNone) break;
		}
		
		// check for user interrupt
		if (m_bStoppedByUser) break;

		//  checking timeout, if it was specified
		if (m_QueryEndTime != TheEndOfTheWorld) {
			if (m_CurrentSearchPeriodNo+1 < CountOfPeriods) { // if it is not the last cycle
				time_t curr_time;
				time(&curr_time);
				if ((curr_time-last_time+curr_time) > m_QueryEndTime) { // if cannot process next cycle
					return errTimeoutElapsed;
				}
				//printf ("one period time=%i, left time =%i\n", curr_time-last_time, m_QueryEndTime - curr_time);
				last_time = curr_time;
			}
		}
	} //  cycle for corpus periods

	// encode count() query results as hits
	if (qCount != NULL) {
		rc = ConvertCountsToHits(qCount, Limit);
	}

	//  we cannot call here CleanParser, because we would use later some slots of  m_pQueryCompiler 
	//  but  we should delete the parse tree itself in order to free meemory
	//  + moo: this won't work in v2.0.23 because we still need query filters in m_pQueryCompiler->m_pQuery->m_Filters
	//         it's called implicitly by CQueryCompiler::CleanParser(), i.e. before the next parse
	//m_pQueryCompiler->DeleteTree();

	return rc;
};

bool CConcHolder::IsUniversalCountQuery(CQuery *QueryRoot) const
{
	if (typeid(*QueryRoot) != typeid(CQCount)) return false;
	CQCount *qCount = (CQCount*)QueryRoot;
	return (typeid(*qCount->m_dtr)==typeid(CQTokAny) && qCount->m_dtr->m_Options->CanFilterByFile() && qCount->m_keys.CanCountByFile());
};

DDCErrorEnum CConcHolder::GetUniversalCounts(CQuery *CountQueryRoot, size_t Limit)
{
	//-- sanity check(s)
	assert(CountQueryRoot != NULL);
	assert(IsUniversalCountQuery(CountQueryRoot));

	//-- common variables
	CQCount *qCount  = (CQCount*)CountQueryRoot;
	CQuery  *qRoot   = qCount->m_dtr;
	CQCountKeyExprList &keys = qCount->m_keys;
	m_CountSample = 0;

	//-- count(* ...) query: do memory-optimized computation
	CConcIndexator *ix = m_pIndexator;
	const vector<CTokenNo> &fbreaks = ix->GetFileBreaks();
	const set<size_t>      &fmasked = ix->m_MaskedFiles; 
	set<size_t>::const_iterator fmaski = fmasked.begin();
	DWORD nfiles = ix->GetCorpusFilesCount();
	CHit hit;
	string key;
	size_t n;

	assert(nfiles <= fbreaks.size()); //-- sanity check
		
	if (qRoot->m_Options->m_bSeparateHits) {
		//-- count(* #sep): count tokens
		CTokenNo fw_begin=0, fw_end;
		for (DWORD f=0; f<nfiles && m_CountSample < qCount->m_sample; ++f, fw_begin=fw_end) {
			fw_end = fbreaks[f];
			if (fmaski != fmasked.end() && f == *fmaski) {
				//-- don't count tokens in masked files
				++fmaski;
				continue;
			}
			if (ix->m_Bibl.FileMatches(f, qRoot->m_Options->m_Filters)) {
				hit.m_FileNo   = f;
				key            = keys.Evaluate(hit);
				n              = (fw_end - fw_begin);
				m_Counts[key] += n;
				m_CountSample += n;
			}
		}
	}
	else {
		//-- count(* #join): count selected breaks
		const CHitBorders::CBreakCollection *sbreaks = ix->GetBreakCollectionByName(qRoot->m_Options->m_HitTypeStr);
		DWORD    f=0, n=1;
		CTokenNo fw_end = fbreaks[f];
		for (vector<CTokenNo>::const_iterator bi=sbreaks->m_BreakOffsets.begin(); bi!=sbreaks->m_BreakOffsets.end() && m_CountSample<qCount->m_sample; ++bi,++n) {
			if (*bi >= fw_end) {
				//-- new file
				if (fmaski != fmasked.end() && f == *fmaski) {
					++fmaski;
				}
				else if (n>0 && ix->m_Bibl.FileMatches(f, qRoot->m_Options->m_Filters)) {
					hit.m_FileNo   = f;
					key            = keys.Evaluate(hit);
					m_Counts[key] += n;
					m_CountSample += n;
				}
				do {
					++f;
					fw_end = fbreaks[f];
				} while (*bi >= fw_end);
				n = 0;
			}
		}
	}

	return ConvertCountsToHits(qCount, Limit);
}

DDCErrorEnum CConcHolder::GetPeriodCounts(CQuery *CountQueryRoot)
{
	//-- sanity check(s)
	assert(CountQueryRoot != NULL);
	assert(typeid(*CountQueryRoot) == typeid(CQCount));

	//-- common variables
	CQCount *qCount  = (CQCount*)CountQueryRoot;
	CQuery  *qRoot   = qCount->m_dtr;
	CQCountKeyExprList &keys = qCount->m_keys;

	//-- counting guts
	if (keys.CanCountByFile()) {
		//-- counting guts: file-level
		bool isWithinFile = (qRoot->m_Options->m_HitTypeStr == PredefinedFileBreakName);
		DWORD  f = (DWORD)-1;
		size_t n = 0;
		string key;

		//-- ensure m_Hits are sorted by file-id
		if (qRoot->m_Options && !qRoot->m_Options->m_Filters.empty() && qRoot->m_Options->m_Filters.back().m_FilterType!=NoSort) 
			sort(m_Hits.begin(), m_Hits.end(), IsLessByFileNo());

		for (vector<CHit>::const_iterator hi=m_Hits.begin(); hi != m_Hits.end() && m_CountSample < qCount->m_sample; ++hi, ++n) {
			if (hi->m_FileNo != f) {
				//-- next file
				if (n>0) {
					m_Counts[key] += (isWithinFile ? 1 : n);
					m_CountSample += (isWithinFile ? 1 : n);
				}
				n   = 0;
				f   = hi->m_FileNo;
				key = keys.Evaluate(*hi);
			}
		}
		if (n>0) {
			m_Counts[key] += (isWithinFile ? 1 : n);
			m_CountSample += (isWithinFile ? 1 : n);
		}
	}
	else {
		//-- counting guts: token-level
		for (vector<CHit>::const_iterator hi=m_Hits.begin(); hi != m_Hits.end() && m_CountSample < qCount->m_sample; ++hi, ++m_CountSample) {
			string &key = keys.Evaluate(*hi);
			++m_Counts[key];
		}
	}

	//-- cleanup period-local count-daughter data
	m_Hits.clear();
	m_HighlightOccurs.clear();
	m_HighlightIds.clear();
	m_AllHitsCount = 0;

	return errNone;
}

DDCErrorEnum CConcHolder::ConvertCountsToHits(CQuery *CountQueryRoot, size_t Limit) 
{
	CQCount *qCount = (CQCount*)CountQueryRoot;
	size_t n = qCount->m_sort==NoSort || qCount->m_sort==LessByCountKey ? min(Limit, m_Counts.size()) : m_Counts.size();

	//-- count query: setup m_Hits[]
	// + m_Hits[] for count()-queries encodes element CHit hit.m_Sortkey.s (count-key) and hit.m_Value.m_Count
	//   attributes; used to transport count()-query results in a backwards-compatible manner.
	m_Hits.clear();
	m_Hits.resize(n);
	vector<CHit>::iterator hi = m_Hits.begin(); 
	for (CCountMap::const_iterator ci=m_Counts.begin(); ci != m_Counts.end() && hi != m_Hits.end(); ++ci, ++hi) {
		hi->m_BreakNo = -1;
		hi->m_HighlightOccurrenceEnd = 0;
		hi->m_FileNo  = -1;
		hi->m_Value.m_Count = ci->second;
		hi->m_SortKey = ci->first;
	}

	//-- count query: sort hits 
	switch (qCount->m_sort) {
	case LessByCountValue:
		stable_sort(m_Hits.begin(), m_Hits.end(), HitLessByCountValue()); break;
	case GreaterByCountValue:
		stable_sort(m_Hits.rbegin(), m_Hits.rend(), HitLessByCountValue()); break;
	case GreaterByCountKey:
		reverse(m_Hits.begin(), m_Hits.end()); break;
	case LessByCountKey:
	default:
		break;
	}

	//-- count query: trim hits (apply limit)
	if (Limit < m_Hits.size())
		m_Hits.resize(Limit);
	

	//-- count query: setup CQueryResult fields
	m_HighlightOccurs.clear();
	m_HighlightIds.clear();
	m_AllHitsCount  = m_Hits.size();
	m_bSortByString = 1;
	m_SortOrder     = hsoAscendingCounts;
	m_DebugInfo.clear();

	return errNone;
}

void	CQueryResult::ClearQueryResults()
{
	ClearVector(m_Hits);
	ClearVector(m_HighlightOccurs);
	ClearVector(m_HighlightIds);
	ClearVector(m_DebugInfo);
	m_AllHitsCount = 0;
	m_RelevantDocumentCount = 0;
	m_bSortByString = false;
	m_SortOrder = hsoNone;
}



string CConcHolder::GetHitIds()  const
{
	if (m_SortOrder == hsoAscendingCounts) return GetCountIds();

	string Result;
	for (size_t i=0; i < m_Hits.size(); i++) {
		const CHit &h = m_Hits[i];
		Result += Format("\t%i -0 ", i); //-- HitId, OrderId (for ddc < v2.0.19)
		if (m_bSortByString) {
			//-- string-based sort
			Result.append(h.m_SortKey.s, 0, DDC_SORTKEY_MAXLEN-1);
		}
		else {
			//-- integer-based sort
			Result += int2hex(m_Hits[i].m_SortKey.i);
		}
	}
	return Result;
};

string CConcHolder::GetCountIds()  const
{
	string Result;
	for (size_t i=0; i < m_Hits.size(); i++) {
		//-- "HitId OrderId" for ddc < v2.0.19
		//-- "HitId    -0"   for ddc >=v2.0.19, context-queries
		//-- "HitCount -0"   for ddc >=v2.0.23, count-queries
		const CHit &h = m_Hits[i];
		Result += Format("\t%zi -0%c", h.m_Value.m_Count, globalCountKeyDelim);
		Result.append(h.m_SortKey.s, 0, DDC_SORTKEY_MAXLEN-1);
	}
	return Result;
};

//#define DEBUG_CACHE
#undef DEBUG_CACHE
#ifdef DEBUG_CACHE
# define CACHEDEBUG(code) code
#else
# define CACHEDEBUG(code)
#endif

bool CConcHolder::TryToGetFromCache(const string &Query,  DWORD& EndHitNo)
{
	CACHEDEBUG(fprintf(stderr,"TryToGetFromCache() : Query=%s, EndHitNo=%d, CacheSize=%zi\n", jsonStr(Query).c_str(), EndHitNo, m_Queries.size()));

	map<string, CQueryResult>::const_iterator it = m_QueryCache.find(Query);
	// if the query is not the cache then exit
	if (it == m_QueryCache.end()) {
		CACHEDEBUG(fprintf(stderr,"TryToGetFromCache() --> not found\n"));
		return false;
	}

	CACHEDEBUG(fprintf(stderr,"TryToGetFromCache() --> found\n"));
	const CQueryResult& CacheItem = it->second;

	// if one asks hits, which were beyond the storage limits of the cache
	if (CacheItem.m_AllHitsCount > m_pIndexator->m_MaxCachedHitsCount) {
		CACHEDEBUG(fprintf(stderr,"TryToGetFromCache() --> nHits=%zd > MaxCachedHitsCount=%zd : must re-evaluate\n", CacheItem.m_AllHitsCount, m_pIndexator->m_MaxCachedHitsCount));
		if (EndHitNo+m_ResultLimit > m_pIndexator->m_MaxCachedHitsCount) return false;
	}

	ClearQueryResults();
	
	//  copying [EndHitNo...EndHitNo+m_ResultLimit) hits from the cache to  m_Hits,  m_HighlightOccurs,  and m_HighlightIds
	size_t End  = min (EndHitNo+m_ResultLimit, CacheItem.m_Hits.size());
	for (; EndHitNo < End; EndHitNo++)
	{
		m_Hits.push_back(CacheItem.m_Hits[EndHitNo]);
		int start = (EndHitNo == 0) ? 0 : CacheItem.m_Hits[EndHitNo-1].m_HighlightOccurrenceEnd;
		m_HighlightOccurs.insert(m_HighlightOccurs.end(), CacheItem.m_HighlightOccurs.begin()+start, CacheItem.m_HighlightOccurs.begin()+CacheItem.m_Hits[EndHitNo].m_HighlightOccurrenceEnd);
		if (!CacheItem.m_HighlightIds.empty())
			m_HighlightIds.insert(m_HighlightIds.end(), CacheItem.m_HighlightIds.begin()+start, CacheItem.m_HighlightIds.begin()+CacheItem.m_Hits[EndHitNo].m_HighlightOccurrenceEnd);
		m_Hits.back().m_HighlightOccurrenceEnd = m_HighlightOccurs.size();
	};
	m_DebugInfo = CacheItem.m_DebugInfo;
	m_AllHitsCount = CacheItem.m_AllHitsCount;
	m_RelevantDocumentCount = CacheItem.m_RelevantDocumentCount;
	m_SortOrder = CacheItem.m_SortOrder;
	m_bSortByString = CacheItem.m_bSortByString;
	return true;
};

// saving results to the cache
void  CConcHolder::SaveToCache(const string& Query, vector<size_t>::const_iterator start, vector<size_t>::const_iterator end)
{
	if (m_pIndexator->m_MaxQueryCacheSize==0) return;
	CACHEDEBUG(fprintf(stderr,"SaveToCache() : Query=%s, nItems=%zd, CacheSize=%zi\n", jsonStr(Query).c_str(), end-start, m_Queries.size()));

	if (m_QueryCache.find(Query) !=  m_QueryCache.end())
	{
		// it can be so that SaveToCache was called but the input query is already in the cache,
		// because the user now wants some hits after MaxCachedHitsCount 
		// so TryToGetFromCache has returned false, and now we are here
		CACHEDEBUG(fprintf(stderr,"SaveToCache() --> already present\n"));
		return;
	};

	// if the cache is full, then we should delete the oldest item
	if (m_Queries.size() >= m_pIndexator->m_MaxQueryCacheSize)
	{
		//  erasing  the first item from Query queue and from the Query cache
		map<string, CQueryResult>::iterator it = m_QueryCache.find(m_Queries.front());
		assert(it != m_QueryCache.end());
		CACHEDEBUG(fprintf(stderr,"SaveToCache() --> dropping stale cache-item %s\n", jsonStr(it->first).c_str()));
		m_QueryCache.erase(it);
		m_Queries.erase(m_Queries.begin());
	};
	m_Queries.push_back(Query);
	
	//  creating a new query cache item
	CQueryResult I;
	I.m_AllHitsCount = m_AllHitsCount;
	I.m_RelevantDocumentCount = m_RelevantDocumentCount;
	I.m_SortOrder = m_SortOrder;
	I.m_bSortByString = m_bSortByString;
	size_t End  = min (m_pIndexator->m_MaxCachedHitsCount, (size_t)(end-start));
	for (size_t i=0; i < End; i++)
	{
		size_t HitNo = *start;
		start++;
		I.m_Hits.push_back(m_Hits[ HitNo ]);
		int start_index = (HitNo == 0) ? 0 : m_Hits[HitNo-1].m_HighlightOccurrenceEnd;
		I.m_HighlightOccurs.insert(I.m_HighlightOccurs.end(), m_HighlightOccurs.begin()+start_index, m_HighlightOccurs.begin()+m_Hits[HitNo].m_HighlightOccurrenceEnd);
		if (!m_HighlightIds.empty())
			I.m_HighlightIds.insert(I.m_HighlightIds.end(), m_HighlightIds.begin()+start_index, m_HighlightIds.begin()+m_Hits[HitNo].m_HighlightOccurrenceEnd);
		I.m_Hits.back().m_HighlightOccurrenceEnd = I.m_HighlightOccurs.size();

	};
	I.m_DebugInfo = m_DebugInfo;
	m_QueryCache[Query] = I;
	assert (m_Queries.size() ==  m_QueryCache.size());
};

DDCErrorEnum CConcHolder::GetHits(const string &Query,  DWORD& EndHitNo) 
{
	ClearQueryResults();
	m_Counts.clear();

	if ( !(m_pQueryCompiler->ParseQuery(Query) && m_pQueryCompiler->Compile()) )
			return errParseError;

	SetHitType();

	try {
		if ( !TryToGetFromCache(Query, EndHitNo) )
		{
			// a new query occurs
			DDCErrorEnum result = GetAllHits(Query, max(EndHitNo+m_ResultLimit, m_pIndexator->m_MaxCachedHitsCount) );
			if (result != errNone) 
				return result;

			vector<size_t> HitsIndex;
			HitsIndex.reserve(m_Hits.size());
			for (size_t i=0; i < m_Hits.size(); i++)
				HitsIndex.push_back(i);

#if DEBUG_HIT_SORT //-- DEBUG
			for (size_t hi=0; hi < m_Hits.size(); hi++) {
				const CHit &h=m_Hits[hi];
				fprintf(stderr, "DEBUG[pre-sort;order=%d]: m_Hits[%u] = {m_BreakNo=%u, m_HighlightOccurrenceEnd=%u, m_SortKey={%d,%s}, m_FileNo=%u, m_DebugRankNo=%u}\n",
					m_SortOrder,
					hi, h.m_BreakNo, h.m_HighlightOccurrenceEnd, h.m_SortKey.i, jsonStr(h.m_SortKey.s).c_str(), h.m_FileNo, h.m_Value.m_DebugRankNo);
			}
#endif //-- DEBUG

			//-- re-sort hits here, since they might be drawn from different corpus periods
			if (m_SortOrder > 0) {
				//-- ascending sort
				stable_sort (HitsIndex.begin(), HitsIndex.end(), IsLessByHitSortKey(m_Hits));
			} else if (m_SortOrder < 0) {
				//-- descending sort
				stable_sort (HitsIndex.rbegin(), HitsIndex.rend(), IsLessByHitSortKey(m_Hits));
			} else {
				//-- no sort
				;
			}

			SaveToCache(Query, HitsIndex.begin(), HitsIndex.end() );
			{
				size_t  End = min (EndHitNo+m_ResultLimit, HitsIndex.size());
				vector<CHit>		NewHits;
				vector<CTokenNo>	NewHighlightOccurs;
				vector<BYTE>		NewHighlightIds;

				for (; EndHitNo < End; EndHitNo++)
				{
					size_t HitNo = HitsIndex[EndHitNo];

					NewHits.push_back(m_Hits[ HitNo ]);

					int start_index = (HitNo == 0) ? 0 : m_Hits[HitNo-1].m_HighlightOccurrenceEnd;
					NewHighlightOccurs.insert(NewHighlightOccurs.end(), m_HighlightOccurs.begin()+start_index, m_HighlightOccurs.begin()+m_Hits[HitNo].m_HighlightOccurrenceEnd);
					if (!m_HighlightIds.empty())
						NewHighlightIds.insert(NewHighlightIds.end(), m_HighlightIds.begin()+start_index, m_HighlightIds.begin()+m_Hits[HitNo].m_HighlightOccurrenceEnd);

					NewHits.back().m_HighlightOccurrenceEnd = NewHighlightOccurs.size();
				};
				m_Hits.swap(NewHits);
				m_HighlightOccurs.swap(NewHighlightOccurs);
				m_HighlightIds.swap(NewHighlightIds);
			}
		}
		
	
		return errNone;

	}
	catch (CExpc& C)
	{
		ErrorMessage (C.m_strCause);
		concord_daemon_log(C.m_strCause);
		return (DDCErrorEnum)C.m_ErrorCode;
	}


};


/////////////////////////////////////////////////////////////////////////////
DDCErrorEnum CConcHolder::SimpleQuery(const string &Query, DWORD& EndHitNo, DWORD& HitsCount) 
{
	DWORD SaveEndHitNo = EndHitNo;
	try {
		DDCErrorEnum result = GetHits(Query, EndHitNo);
		if (result != errNone)
			return result;

		HitsCount = m_AllHitsCount;

		result = GenerateHitStrings (0);
		if (result != errNone)
			return result;

		

		if (m_ResultFormat == DDC_ResultHTML)
		{
			if (m_pIndexator->m_bShowNumberOfRelevantDocuments)
				m_QueryResultStr = 	Format("Occurrences %i - %i of %i in %i document(s)<br>", SaveEndHitNo+1, EndHitNo, HitsCount, m_RelevantDocumentCount) + m_QueryResultStr;
			else
				m_QueryResultStr = 	Format("Occurrences %i - %i of %i<br>", SaveEndHitNo+1, EndHitNo, HitsCount) + m_QueryResultStr;
		};

		DecorateQueryResults(GetResultFormatStr(), m_QueryResultStr);

		return errNone;

	}
	catch (CExpc& C)
	{
		ErrorMessage (C.m_strCause);
		concord_daemon_log(C.m_strCause);
		return (DDCErrorEnum)C.m_ErrorCode;
	}

};


bool CConcHolder::SaveOccurrences(const vector<size_t>& ChunkLengths, int ContextSize, const vector<CTokenNo>& Occurrences,  const vector<CHit>& Hits,  SaveTriggerType SaveTrigger, DWORD LParam)
{
	if (m_pIndexator->m_Indices.empty()) return false;
	assert (Hits.size() == ChunkLengths.size());

	{
		int len = 0;
		for(size_t i=0; i < ChunkLengths.size(); i++)
			len += ChunkLengths[i];
		if (Occurrences.size() != len)
		{
			fprintf (stderr, "Fatal Error! Sum of all chunk lengths  is not equal to the number of all occurrences\n");
			return false;
		}
	}


	string Result;
	size_t PosOffset = 0;
	for ( int HitNo =  0; HitNo<Hits.size(); HitNo++ )
	{
		size_t ItemsCount = ChunkLengths[HitNo];
		const DWORD BreakNo = Hits[HitNo].m_BreakNo; 
		
		CTokenNo PositionStart = Occurrences[PosOffset];
		CTokenNo PositionEnd = Occurrences[PosOffset+ItemsCount-1]+1;
		string Postfix;
		if (ContextSize != -1)
		{
			const DWORD StartHitTokenNo = (BreakNo == 0) ? 0 : GetBreaks()[BreakNo-1];
			if (StartHitTokenNo+ContextSize <= PositionStart)
				PositionStart -= ContextSize;
			else
			{
				for (size_t i=0; i < ContextSize-(PositionStart-StartHitTokenNo); i++)
					Result += "\"*\";"; 
				PositionStart = StartHitTokenNo;
			};

			const CTokenNo& EndHitTokenNo = GetBreaks()[BreakNo];
			if (PositionEnd+ContextSize <= EndHitTokenNo)
				PositionEnd += ContextSize;
			else
			{
				for (size_t i=0; i < ContextSize-(EndHitTokenNo-PositionEnd); i++)
					Postfix += "\"*\";"; 
				PositionEnd = EndHitTokenNo;
			};
		};


		vector<COutputToken> Tokens;
		if (!m_pIndexator->GetTokenIndex()->GetTokensFromStorage(PositionStart, PositionEnd, Tokens)) 
		{
			concord_daemon_log(Format ("Error! Cannot read hit number %i \n",BreakNo));
			return false;
		};

		for (size_t i=0; i < Tokens.size(); i++)
		{
			Result += "\"";
			Result += Tokens[i].m_TokenStr;
			Result += "\";"; 
		};
		Result += Postfix;
		Result += "\n";

		if (Result.length() > 4096)
		{
			if (!SaveTrigger(Result, LParam))
				return false;

			Result = "";
		};

		PosOffset += ItemsCount;
			
	};

	if (!Result.empty())
		if (!SaveTrigger(Result, LParam))
			return false;
	
	return true;
};


DDCErrorEnum CConcHolder::GetOccurrences(const string &Query, int ContextSize,  SaveTriggerType SaveTrigger, DWORD LParam) 
{
    try {
		if ( !(m_pQueryCompiler->ParseQuery(Query) && m_pQueryCompiler->Compile()) )
				return errParseError;

		SetHitType();

		if	( !m_pQueryCompiler->m_pQuery->m_Node->m_bAtomic )
		{
			fprintf (stderr,"Error! The query is not a pattern!\n");
			return errParseError;
		};

		for (m_CurrentSearchPeriodNo = 0;  m_CurrentSearchPeriodNo < m_pIndexator->GetSearchPeriodsCount(); m_CurrentSearchPeriodNo++)
		{
			CQueryNode* Node = (CQuerySequenceNode*)m_pQueryCompiler->m_pQuery->m_Node;
			Node->EvaluateWithoutHits();

			
			Node->ConvertOccurrencesToHitsForPatterns (false);
			if (!SaveOccurrences(Node->m_ChunkLengths, ContextSize, Node->m_Occurrences, Node->m_Hits, SaveTrigger, LParam))
			{
				break;
			}

			if (m_bStdout)
				fprintf (stderr," %zi/%zi             \r", m_CurrentSearchPeriodNo, m_pIndexator->GetSearchPeriodsCount());
		};

		if (m_bStdout)
				fprintf (stderr," %zi/%zi             \n", m_CurrentSearchPeriodNo, m_pIndexator->GetSearchPeriodsCount());
		
		//m_pQueryCompiler->DeleteTree();

		return errNone;
	}
	catch (CExpc& C)
	{
		ErrorMessage (C.m_strCause);
		concord_daemon_log(C.m_strCause);
		return (DDCErrorEnum)C.m_ErrorCode;
	}
};

DDCFormatTypeEnum CConcHolder::GetResultFormatByString(const string& ResultTypeStr )
{
	string q = ResultTypeStr;
	EngMakeUpper(q);
	if (q == "JSON") return DDC_ResultJson;
	else if (q == "HTML") return DDC_ResultHTML;
	else if (q == "DOCIDS") return DDC_ResultDocIds;
	else if (q == "TABLE") return DDC_ResultTable;
	else return DDC_ResultText;
};

void CConcHolder::SetResultFormat(string ResultTypeStr)
{
	m_ResultFormat = GetResultFormatByString(ResultTypeStr);
};

string CConcHolder::GetResultFormatStr() const 
{
	switch (m_ResultFormat)  {
		case DDC_ResultJson: return "json";
		case DDC_ResultHTML: return "html";
		case DDC_ResultTable: return "table";
		case DDC_ResultDocIds: return "docids";
		default: return "text";
	};
};



const vector<CTokenNo>&	CConcHolder::GetBreaks	()  const
{
	assert (m_pBreaks != 0);
	return *m_pBreaks;
};

void	CConcHolder::SetHitType()
{
	assert(m_pQueryCompiler!=NULL);
	assert(m_pQueryCompiler->m_pQuery!=NULL);
	string BreakName = m_pQueryCompiler->m_pQuery->m_Options->m_HitTypeStr;
	int TextAreaNo = m_pQueryCompiler->m_pQuery->m_Options->m_TextAreaNo;

	if (TextAreaNo != UnknownTextAreaNo)
		m_pBreaks = m_pIndexator->GetBreaksByName(PredefinedTextAreaBreakName);
	else
		m_pBreaks = m_pIndexator->GetBreaksByName(BreakName);
}


int	CConcHolder::GetTextArea() const
{
	assert(m_pQueryCompiler!=NULL);
	assert(m_pQueryCompiler->m_pQuery!=NULL);
	return m_pQueryCompiler->m_pQuery->m_Options->m_TextAreaNo;
}


HitSortOrderEnum CConcHolder::HitSortOrder() const
{
	return m_SortOrder;
};

void CConcHolder::SetTimeOut(int TimeOut) 
{
	if (TimeOut != -1)
	{
		time_t t;
		time(&t);
		m_QueryEndTime = t+TimeOut;
	}
	else
		m_QueryEndTime = TheEndOfTheWorld;
};

void CConcHolder::ClearQueryCache() 
{
	m_QueryCache.clear();
	m_Queries.clear();
};

bool	CConcHolder::HasRankOrderOperator() const
{
	for (size_t FilterNo = 0; FilterNo < m_pQueryCompiler->m_pQuery->m_Options->m_Filters.size(); FilterNo++)
	{
		const CDDCFilterWithBounds& F = m_pQueryCompiler->m_pQuery->m_Options->m_Filters[FilterNo];
		if ( (F.m_FilterType == LessByRank) || (F.m_FilterType == GreaterByRank))
			return true;
	}
	return  false;
}

bool	CConcHolder::HasMatchIdOperator() const
{
	return m_pQueryCompiler->m_pQuery->HasMatchId();
}

string CConcHolder::CanonicalQueryString(const string &Query)
{
	ClearQueryResults();
	if ( !m_pQueryCompiler || !m_pQueryCompiler->ParseQuery(Query) )
		return string("");
	return m_pQueryCompiler->QueryToString();
}

string CConcHolder::JsonQueryString(const string &Query)
{
	ClearQueryResults();
	if ( !m_pQueryCompiler || !m_pQueryCompiler->ParseQuery(Query) )
		return string("");
	return m_pQueryCompiler->QueryToJson();
}

void CConcHolder::SetRandomSeed(unsigned int seed1) const
{
	m_pRandom->set_seed(m_RandomSeed+seed1);
}


//=============================================================
//==================  CConcordance ============================
//=============================================================

CConcordance::CConcordance() 
{
	m_pIndexator = new CConcIndexator;
	m_bOptionsWereModified = false;
	
}
CConcordance::~CConcordance() 
{
	delete m_pIndexator;
};

bool	CConcordance::LoadProject(const char* FileName)
{

	ClearQueryCache();

	if (!m_pIndexator->LoadProject (FileName))
		return false;
	
	return 	true;
}

bool CConcordance::SaveProject(string FileName)
{
	m_pIndexator->SetPath(FileName);

	if (!m_pIndexator->SaveSourceFileList(FileName))
		return false;;

	return true;
}


