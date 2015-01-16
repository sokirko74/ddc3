//-*- Mode: C++; c-basic-offset: 8; -*-
//
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
#include "../common/util_classes.h"
#include "../common/DwdsThesaurus.h"
#include "../common/ddcString.h"
#include "ConcIndexator.h"

const int DefaultKwicContextSize = 4;

// LC_CTYPE_UTF8_DEFAULT : default LC_CTYPE to use for Utf8 mode if no utf8 locale is detected
const char *LC_CTYPE_UTF8_DEFAULT = "en_US.UTF-8";

//-- option-parsing utility for boolean options
bool StringToBool(const string &s, bool onempty=true)
{
	if (s.empty()) return onempty;
	string ls = stolower(s);
	return (ls!="no" && ls!="n" && ls!="false" && ls!="off" && ls!="disabled" && ls!="0");
}

//-- boolean value reporting
const char *BoolToString(bool b)
{
	return b ? "true" : "false";
}

void CConcIndexator::InitDefaultOptions()
{
   	m_Path = "#empty_path";
	m_bUseParagraphTagToDivide = false;
	m_bEmptyLineIsSentenceDelim = true;
	m_bUseIndention = true;
	m_bIndexMorphPatterns = false;
	m_bUseDwdsThesaurus = false;
	m_UserMaxTokenCountInOnePeriod = 0;
	m_bUserMaxTokenCountInOnePeriod = false;
	m_bIndexPunctuation = true;
	m_bResumeOnIndexErrors = false;
	m_bQueryOnlyFiles = false;
	m_bDisableDefaultQueryLexicalExpansion = false;
	m_bUseDwdsThesaurus = false;
	m_bIndexChunks = false;
	m_bCaseSensitive = true;
	m_bOutputBibliographyOfHits = false;
	m_bDwdsCorpusInterface = false;
	m_bGutenbergInterface = false;
	m_bNoContextOperator = false;
	m_IndexType = DWDS_Index;
	m_bArchiveIndex = false;

	m_Language = morphUnknown;
	m_bShowNumberOfRelevantDocuments = false;
	//
	m_HtmlHighlighting.m_FirstOpener = "<STRONG><FONT COLOR=red>";
	m_HtmlHighlighting.m_FirstCloser = "</FONT></STRONG>";
	m_HtmlHighlighting.m_RestOpener = "<STRONG><FONT COLOR=red>";
	m_HtmlHighlighting.m_RestCloser = "</FONT></STRONG>";
	//
	m_TextHighlighting.m_FirstOpener = "&&";
	m_TextHighlighting.m_FirstCloser = "&&";
	m_TextHighlighting.m_RestOpener = "_&";
	m_TextHighlighting.m_RestCloser = "&_";
	//
	m_TableHighlighting.m_FirstOpener = "&&";
	m_TableHighlighting.m_FirstCloser = "&&";
	m_TableHighlighting.m_RestOpener = "_&";
	m_TableHighlighting.m_RestCloser = "&_";
	//
	m_LeftKwicContextSize = DefaultKwicContextSize;
	m_RightKwicContextSize = DefaultKwicContextSize;
	m_NumberOfKwicLinesInSnippets = 10;
	m_TfIdfRank = 0.3;
	m_NearRank = 0.3;
	m_PositionRank = 0.3;
	m_InterpDelimiter = "#";
	m_TokenDelimiter = "";
	m_Utf8 = false;
	m_bAllowUnsafeQueries = false;
	m_bAllowCountByTokenAttributes = true;
	m_bLemmaQueryUsesMorphPattern = true;
	m_Timestamp = 0;
	m_MaxCachedHitsCount = 512;
	m_MaxQueryCacheSize = 512;
	m_Txd.clear();
	m_OpDefaultIndexNames.clear();
	m_ServerInfo.clear();
	m_Bibl.m_DefaultAttrName = "";
}

const char* CConcIndexator::GetIndexTypeStr () const
{
	switch (m_IndexType)
	{
		case DWDS_Index:  return "DWDS_Index";
		case MorphXML_Index:  return "MorphXML_Index";
		case Free_Index:  return "Free_Index";
	};
	assert (false);
	return "unknown";
};

bool  CConcIndexator::ReadIndexTypeFromStr (const string& s)
{
	if (s == "DWDS_Index") 
		m_IndexType =  DWDS_Index;
	else
	if (s == "MorphXML_Index") 
		m_IndexType =  MorphXML_Index;
	else
	if (s == "Free_Index") 
		m_IndexType =  Free_Index;
	else
		return false;

	return true;
};



bool CConcIndexator::LoadOptionsFromString(string Options)
{
	StringTokenizer lines (Options.c_str(), "\n\r");
	MorphLanguageEnum langua;
	string IndicesStr, HitTypesStr, FreeBiblDescr, TextAreasDescr;
	m_Language = morphUnknown;
	m_IndicesToShow.resize(1,0);

	while (lines())
	{
		char s[1024];
		strcpy(s, lines.val());
		
		StringTokenizer fields(s, " \t\r\n");
		if (!fields()) continue;
		string q = fields.val();
		string q_lower = q;
		RmlMakeLower(q_lower, morphEnglish);
		
		if (q == "#include" || q == "include")
		{
			q = fields.get_rest();
			Trim(q);
			if ((q.length() < 2) || (q[0] != '\"') || (q[q.length() -1] != '\"'))
			{
				fprintf (stderr, "bad syntax in opt-file : %s!\n", s);
				return false;
			};
			string AddOptions;

			//-- moo: interpret relative #include filenames wrt the directory containing the main .con file
			string IncFileName = q.substr(1,q.length()-2);
			string IncFileRelative = RelativeFileName(m_Path, IncFileName);
			if (!LoadFileToString(IncFileRelative, AddOptions))
			{
				fprintf (stderr, "cannot load file \"%s\"!\n", IncFileRelative.c_str());
				return false;
			};
			fprintf (stderr, "#include \"%s\"\n", IncFileName.c_str());
			Options = AddOptions+"\n"+lines.get_rest();
			lines.reinitialize(Options.c_str(), "\n\r");
		}
		else if (q.empty() || q[0]=='#') {
			//-- blank line or comment: ignore
			continue;
		}
		else if (q == "LocalPathPrefix")
		{
			q = fields.next_token();
			if (q.empty() )
			{
				fprintf (stderr, "bad syntax in opt-file : %s!\n", s);
				return false;
			};
			m_LocalPathPrefix = q;
		}
		else if (q == "InternetPathPrefix")
			{
				q = fields.next_token();
				if (q.empty() )
				{
					fprintf (stderr, "bad syntax in opt-file : %s!\n", s);
					return false;
				};

				m_InternetPathPrefix = q;
			}
		else if (GetLanguageByString(q, langua))
			{
				fprintf (stderr,"%s\n", GetStringByLanguage (langua).c_str());
				m_Language = langua;
			}
		else if (q == "CaseInsensitive")
			{
				m_bCaseSensitive = !StringToBool(fields.next_token());
				fprintf (stderr,"CaseInsensitive %s\n", BoolToString(m_bCaseSensitive));
			}
		else if (q == "HtmlHighlighting")
			{
				if (!m_HtmlHighlighting.ReadFromString(fields.get_rest()))
				{
					fprintf (stderr,"Cannot parse HtmlHighlighting field\n");
					return false;
				};
				fprintf (stderr,"HtmlHighlighting = \"%s\"\n", m_HtmlHighlighting.ToString().c_str());
			}
		else if (q == "TextHighlighting")
			{
				if (!m_TextHighlighting.ReadFromString(fields.get_rest()))
				{
					fprintf (stderr,"Cannot parse TextHighlighting field\n");
					return false;
				};
				fprintf (stderr,"TextHighlighting = \"%s\"\n", m_TextHighlighting.ToString().c_str());
			}
		else if (q == "TableHighlighting")
			{
				if (!m_TableHighlighting.ReadFromString(fields.get_rest()))
				{
					fprintf (stderr,"Cannot parse TableHighlighting field\n");
					return false;
				};
				fprintf (stderr,"TableHighlighting = \"%s\"\n", m_TableHighlighting.ToString().c_str());
			}
		else if (q == "ShowNumberOfRelevantDocuments")
			{
				m_bShowNumberOfRelevantDocuments = StringToBool(fields.next_token());
				fprintf (stderr,"ShowNumberOfRelevantDocuments %s\n", BoolToString(m_bShowNumberOfRelevantDocuments));
			}
		else if (q == FreeBiblAttribOptionFieldName)
			{
				FreeBiblDescr += string(s) + "\n";
			}
		else if (q_lower == TextAreaOptionFieldName)
			{
				TextAreasDescr += string(s) + "\n";
			}
		else if (q == "UseParagraphTagToDivide")
			{
				m_bUseParagraphTagToDivide = StringToBool(fields.next_token());
			}
		else if (q == "QueryOnlyFiles")
			{
				m_bQueryOnlyFiles = StringToBool(fields.next_token());
				fprintf (stderr,"QueryOnlyFiles %s\n", BoolToString(m_bQueryOnlyFiles));
			}
		else if (q == "NoContextOperator")
			{
				m_bNoContextOperator = StringToBool(fields.next_token());
				fprintf (stderr,"NoContextOperator %s\n", BoolToString(m_bNoContextOperator));
			}
			
		else if (q == "EmptyLineIsNotSentenceDelim")
			{
				m_bEmptyLineIsSentenceDelim = StringToBool(fields.next_token());
			}
		else if (q == "DontUseIndention")
			{
				m_bUseIndention = StringToBool(fields.next_token());
			}
		else if (q == "UseDwdsThesaurus")
			{
				m_bUseDwdsThesaurus = StringToBool(fields.next_token());
				fprintf (stderr,"UseDwdsThesaurus %s\n", BoolToString(m_bUseDwdsThesaurus));
			}
		else if (q == "MaxRegExpExpansionSize")
			{
				q = fields.next_token();
				if (!q.empty()) {
					m_MaxRegExpExpansionSize = atoi(q.c_str());
					fprintf (stderr,"MaxRegExpExpansionSize = %zi\n", m_MaxRegExpExpansionSize);
				}
			}
		else if (q == "MaxCachedHitsCount")
			{
				q = fields.next_token();
				if (!q.empty()) {
					m_MaxCachedHitsCount = atoi(q.c_str());
					fprintf(stderr, "MaxCachedHitsCount = %zi\n", m_MaxCachedHitsCount);
				}
			}
		else if (q == "MaxQueryCacheSize")
			{
				q = fields.next_token();
				if (!q.empty()) {
					m_MaxQueryCacheSize = atoi(q.c_str());
					fprintf(stderr, "MaxQueryCacheSize = %zi\n", m_MaxQueryCacheSize);
				}
			}
		else if (q == "RightKwicContextSize")
			{
				q = fields.next_token();
				if (!q.empty()) 
				{
					m_RightKwicContextSize = atoi(q.c_str());
					fprintf (stderr,"RightKwicContextSize = %i\n", m_RightKwicContextSize);
				}
				else
					return false;
			}
		else if (q == "LeftKwicContextSize")
			{
				q = fields.next_token();
				if (!q.empty()) 
				{
					m_LeftKwicContextSize = atoi(q.c_str());
					fprintf (stderr,"LeftKwicContextSize = %i\n", m_LeftKwicContextSize);
				}
				else
					return false;
			}
		else if (q == "NumberOfKwicLinesInSnippets")
			{
				q = fields.next_token();
				if (!q.empty()) 
				{
					m_NumberOfKwicLinesInSnippets = atoi(q.c_str());
					fprintf (stderr,"NumberOfKwicLinesInSnippets = %i\n", m_NumberOfKwicLinesInSnippets);
				}
				else
					return false;
			}
		else if (q == "TfIdfRank")
			{
				q = fields.next_token();
				if (!q.empty()) 
				{
					m_TfIdfRank = atof(q.c_str());
					fprintf (stderr,"TfIdfRank = %f\n", m_TfIdfRank);
				}
				else
					return false;
			}
		else if (q == "PositionRank")
			{
				q = fields.next_token();
				if (!q.empty()) 
				{
					m_PositionRank = atof(q.c_str());
					fprintf (stderr,"PositionRank = %f\n", m_PositionRank);
				}
				else
					return false;
			}
		else if (q == "InterpDelimiter" || q == "InterpDelimeter")
			{
				q = fields.next_token();
				if (q.empty())  
				{
					fprintf (stderr,"InterpDelimiter is not set!\n");
					return false;
				}
				m_InterpDelimiter = unescapeCString(q);
				fprintf (stderr,"InterpDelimiter = \"%s\"\n", m_InterpDelimiter.c_str());
			}
		else if (q == "TokenDelimiter" || q == "TokenDelimeter")
			{
				q = fields.next_token();
				if (q.empty())  
				{
					fprintf (stderr,"TokenDelimiter is not set!\n");
					return false;
				}
				m_TokenDelimiter = unescapeCString(q);
				fprintf (stderr,"TokenDelimiter = \"%s\"\n", m_TokenDelimiter.c_str());
			}
		else if (q == "Utf8")
			{
				m_Utf8 = StringToBool(fields.next_token());
			}
		else if (q == "AllowUnsafeQueries")
			{
				m_bAllowUnsafeQueries = StringToBool(fields.next_token());
				fprintf (stderr,"AllowUnsafeQueries %s\n", BoolToString(m_bAllowUnsafeQueries));
			}
		else if (q == "AllowCountByTokenAttributes")
			{
				m_bAllowCountByTokenAttributes = StringToBool(fields.next_token());
				fprintf (stderr,"AllowCountByTokenAttributes %s\n", BoolToString(m_bAllowCountByTokenAttributes));
			}
		else if (q == "LemmaQueryUsesMorphPattern")
			{
				m_bLemmaQueryUsesMorphPattern = StringToBool(fields.next_token());
				fprintf (stderr, "bLemmaQueryUsesMorphPattern %s\n", BoolToString(m_bLemmaQueryUsesMorphPattern));
			}
		else if (q == "IndicesToShow")
			{
				q = fields.next_token();
				if (q.empty())  return false;
				m_IndicesToShow.clear();
				while (!q.empty())
				{
					if (q == "0") 
					{
						fprintf (stderr,"Error! IndicesToShow must start from 1\n");
						return false;
					}
					int a = atoi(q.c_str());
					if (!a)
					{
						fprintf (stderr,"Error! Bad format of IndicesToShow, it must be a blank separated list of integers (started from 1!)!\n");
						return false;
					}
					for (size_t j=0; j<q.length(); j++)
						if (!isdigit((BYTE)q[j]))
						{
							fprintf (stderr,"Error! Bad format of IndicesToShow, it must be a blank separated list of integers (started from 1!)!\n");
							return false;
						}

					m_IndicesToShow.push_back(a-1);
					q = fields.next_token();
				}
				fprintf (stderr,"IndicesToShow is initialized with %zi values\n", m_IndicesToShow.size());
			}
		else if (q == "NearRank")
			{
				q = fields.next_token();
				if (!q.empty()) 
				{
					m_NearRank = atof(q.c_str());
					fprintf (stderr,"NearRank = %f\n", m_NearRank);
				}
				else
					return false;
			}
			
		else if (q == "IndexType")
			{
				q = fields.next_token();
				if (!ReadIndexTypeFromStr(q)) 
				{
					fprintf (stderr,"Unknown value for IndexType\n");
					return false;
				}
				fprintf (stderr,"IndexType %s\n", GetIndexTypeStr());
			}
		else if (q == "GutenbergInterface")
			{
				m_bGutenbergInterface = StringToBool(fields.next_token());
				fprintf (stderr,"GutenbergInterface %s\n", BoolToString(m_bGutenbergInterface));
			}
		else if (q == "DwdsCorpusInterface")
			{
				m_bDwdsCorpusInterface = StringToBool(fields.next_token());
				fprintf (stderr,"DwdsCorpusInterface %s\n", BoolToString(m_bDwdsCorpusInterface));
			}
		else if (q == "Bigrams")
			{
				fprintf(stderr, "WARNING: Bigrams declaration ignored for ddc >= v2.0.19: `Bigrams %s'\n", fields.get_rest());
			}
		else if (q == "Indices")
			{
				IndicesStr = fields.get_rest();
			}
		else if (q == "HitBorders")
			{
				HitTypesStr = fields.get_rest();
			}
		else if (q == "IndexPunctuation")
			{
				m_bIndexPunctuation = StringToBool(fields.next_token());
				fprintf (stderr,"IndexPunctuation %s\n", BoolToString(m_bIndexPunctuation));
			}
		else if (q == "ResumeOnIndexErrors")
			{
				m_bResumeOnIndexErrors = StringToBool(fields.next_token());
				fprintf (stderr,"ResumeOnIndexErrors %s\n", BoolToString(m_bResumeOnIndexErrors));
			}
		else if (q == "IndexMorphPatterns")
			{
				m_bIndexMorphPatterns = StringToBool(fields.next_token());
				fprintf (stderr,"IndexMorphPatterns %s\n", BoolToString(m_bIndexMorphPatterns));
			}
		else if (q == "DisableDefaultQueryLexicalExpansion")
			{
				m_bDisableDefaultQueryLexicalExpansion = StringToBool(fields.next_token());
				fprintf (stderr,"DisableDefaultQueryLexicalExpansion %s\n", BoolToString(m_bDisableDefaultQueryLexicalExpansion));
			}
		else if (q == "ArchiveIndex")
			{
				m_bArchiveIndex = StringToBool(fields.next_token());
				fprintf (stderr,"ArchiveIndex %s\n", BoolToString(m_bArchiveIndex));
			}
		else if (q == "OutputBibliographyOfHits")
			{
				m_bOutputBibliographyOfHits = StringToBool(fields.next_token());
				fprintf (stderr,"OutputBibliographyOfHits %s\n", BoolToString(m_bOutputBibliographyOfHits));
			}
		else if (q == "IndexChunks")
			{
				m_bIndexChunks = StringToBool(fields.next_token());
				fprintf (stderr,"IndexChunks %s\n", BoolToString(m_bIndexChunks));
			}
		else if (q == "UserMaxTokenCountInOnePeriod")
			{
				q = fields.next_token();
				if (!q.empty()) 
				{
					m_bUserMaxTokenCountInOnePeriod = true;
					m_UserMaxTokenCountInOnePeriod = atoi(q.c_str());
					

					fprintf (stderr,"UserMaxTokenCountInOnePeriod = %i\n", m_UserMaxTokenCountInOnePeriod);
					if (m_UserMaxTokenCountInOnePeriod == 0)
					{
						fprintf (stderr,"ERROR: UserMaxTokenCountInOnePeriod: must be >= 65000, but got `%s'!\n", q.c_str());
						return false;
					};
				};
				
			}
 		else if (q == "Expand") {
			//-- term expander
			string tx_spec(fields.get_rest());
			CTermExpander *tx = m_Txd.addExpander(tx_spec);
			if (tx==NULL) {
				fprintf(stderr, "ERROR: could not create term-expander for spec `%s'\n", tx_spec.c_str());
				return false;
			}
			tx->compile();
			fprintf(stderr, "Expand %s\n", tx->configString().c_str());
		}
		else if (q == "ExpandBibl") {
			//-- bibliographic expander
			string bx_spec(fields.get_rest());
			CBiblExpander *bx = m_Bibl.AddBiblExpander(bx_spec);
			if (bx==NULL) {
				fprintf(stderr, "ERROR: could not create bibliographic expander for spec `%s'\n", bx_spec.c_str());
				return false;
			}
			bx->compile();
			fprintf(stderr, "ExpandBibl %s\n", bx->configString().c_str());
		}
		else if (q == "DefaultQueryIndex") {
			string query_op   = fields.next_token();
			string index_name = fields.next_token();
			m_OpDefaultIndexNames[query_op] = index_name;
		}
		else if (q == "DefaultBibl") {
			m_Bibl.m_DefaultAttrName = fields.next_token();
			fprintf(stderr, "DefaultBibl %s\n", m_Bibl.m_DefaultAttrName.c_str());
		}
		else if (q == "ServerInfo") {
			string info_key = unescapeCString(fields.next_token());
			string info_val = fields.get_rest();
			m_ServerInfo[info_key] = make_pair(false,info_val);
		}
		else if (q == "ServerInfoFile") {
			string info_key = unescapeCString(fields.next_token());
			string info_val = unescapeCString(fields.get_rest());
			m_ServerInfo[info_key] = make_pair(true,info_val);
		}
		else
		{
			fprintf (stderr, "bad syntax in opt-file : %s!\n", q.c_str());
			return false;
		};
	};


	if (m_Language == morphUnknown)
	{
		ErrorMessage ("There is no language definition in the options file");
		return false;
	};

	//-- set utf-8 flag
	if (m_Utf8) {
		const char *lc_ctype = setlocale(LC_CTYPE,NULL);
		if (strstr(lc_ctype,"UTF-8")==NULL && strstr(lc_ctype,"utf8")==NULL) {
			//-- hack for locale-sensitive internal iconv conversions to/from wchar_t
			fprintf(stderr, "WARNING: Utf8 mode requested but LC_CTYPE `%s' doesn't seem to be a UTF-8 locale\n", lc_ctype);
			fprintf(stderr, "WARNING: attempting to set Utf8 LC_CTYPE=%s\n", LC_CTYPE_UTF8_DEFAULT);
			setlocale(LC_CTYPE,LC_CTYPE_UTF8_DEFAULT);
			lc_ctype = setlocale(LC_CTYPE,NULL);
		}
		fprintf (stderr,"Utf8 mode enabled (LC_CTYPE=%s)\n", lc_ctype);
	} else {
		fprintf (stderr,"Utf8 mode disabled\n");
	}

	//-- ensure default expanders exist
	m_Txd.ensureDefaultExpanders(langua,
				     (m_Utf8 ? morphGeneric : langua),
				     (!m_bDisableDefaultQueryLexicalExpansion),
				     (!m_bCaseSensitive));

	//-- (old-style) regex table generation
	RmlPcreMakeTables(m_PcreCharacterTables, m_Language);
	
	const char* ArchiveType = (m_bArchiveIndex) ? "archive" : "normal";
	
	switch (m_IndexType) 
	{
		case MorphXML_Index: 	IndicesStr = Format("[Token w %s];[MorphPattern m %s];[Lemma l %s]", 
									ArchiveType,
									ArchiveType,
									ArchiveType);
								break;

		case DWDS_Index:	IndicesStr = Format("[Token w %s];",ArchiveType);
							if (m_bIndexMorphPatterns)
								IndicesStr += Format("[MorphPattern m %s];",ArchiveType);
							if (m_bUseDwdsThesaurus)
								IndicesStr += Format("[Thes t %s];",ArchiveType);
							break;

		case Free_Index:	if ( IndicesStr.empty() )
							{
								fprintf (stderr, "Error! Cannot find an index definition in the options file.\n");
								return false;
							};
							break;
	};

	if (!RegisterStringIndices(IndicesStr))
	{
		fprintf (stderr," Cannot parse index definition: %s\n", IndicesStr.c_str());
		return false;
	};




	if (m_bIndexChunks)
		if (!RegisterChunkIndex())
		{
			fprintf (stderr, "cannot register predefined chunk index!\n");
			return false;
		};

	fprintf (stderr," indices = %s\n", GetIndicesString().c_str() );
	
	switch (m_IndexType) {
		case MorphXML_Index:	HitTypesStr = "[s:sentence:default]";
								break;

		case DWDS_Index:	if (!m_bQueryOnlyFiles)
								HitTypesStr = "[s:sentence:default]";
							break;

		case Free_Index:	if ( HitTypesStr.empty() )
							{
								fprintf (stderr, "Error! Cannot find a hit types definition in the options file.\n");
								return false;
							};
							break;
	};


	string ErrorStr;
	if (!m_Bibl.RegisterFreeBiblAttributes(FreeBiblDescr, ErrorStr))
	{
		ErrorMessage( Format("Cannot parse %s\n (%s)", FreeBiblDescr.c_str(), ErrorStr.c_str()) );
		return false;
	}
	fprintf (stderr,"%s", m_Bibl.GetFreeBibiAttributesDescr().c_str());

	if (!m_Bibl.m_DefaultAttrName.empty() && !m_Bibl.IsRegisteredBiblField(m_Bibl.m_DefaultAttrName)) {
		ErrorMessage(Format("DefaultBibl target field `%s' is undefined", m_Bibl.m_DefaultAttrName.c_str()));
		return false;
	}

	if (!m_Bibl.RegisterTextAreas(TextAreasDescr, ErrorStr))
	{
		ErrorMessage( Format("Cannot parse %s\n (%s)", TextAreasDescr.c_str(), ErrorStr.c_str()));
		return false;
	}
	fprintf (stderr,"%s", m_Bibl.GetTextAreasDescr().c_str());

	if (!RegisterBorderIndices(HitTypesStr.c_str()))
	{
		fprintf (stderr," Cannot parse %s\n", HitTypesStr.c_str());
		return false;
	};
	fprintf (stderr," HitBorders = %s\n", GetBorderIndicesString().c_str());

	for(size_t i=0; i < m_IndicesToShow.size(); i++)
	{
		if (m_IndicesToShow[i] >= m_Indices.size())
		{
			fprintf (stderr,"Error! index %zi specified in IndicesToShow is out of range\n", m_IndicesToShow[i]);
			return false;
		}
		if (!m_Indices[m_IndicesToShow[i]]->m_bUseItemStorage)
		{
			fprintf (stderr,"Error! index %zi has no storage\n", m_IndicesToShow[i]);
			return false;
		}
	}

	//-- propagate regex-related options to m_Bibl
	m_Bibl.SetRegexOptions(GetRegexOptions());

	//-- sanity check for m_OpDefaultIndexNames[query_op] = index_name;
	for (map<string,string>::iterator oni=m_OpDefaultIndexNames.begin(); oni != m_OpDefaultIndexNames.end(); ) {
		if (oni->first == "." && !GetBreakCollectionByName(oni->second)) {
			map<string,string>::iterator tmp = oni;
			fprintf(stderr, "WARNING: ignoring unknown default break collection `%s' for query operator `%s'\n", oni->second.c_str(), oni->first.c_str());
			++oni;
			m_OpDefaultIndexNames.erase(tmp);
		}
		else if (!GetIndexByNameOrShortName(oni->second)) {
			map<string,string>::iterator tmp = oni;
			fprintf(stderr, "WARNING: ignoring unknown default index `%s' for query operator `%s'\n", oni->second.c_str(), oni->first.c_str());
			++oni;
			m_OpDefaultIndexNames.erase(tmp);
		}
		else {
			++oni;
		}
	}


	return true;
};


string CConcIndexator::SaveOptionsToString()  const
{
	string Result;
	if (!m_LocalPathPrefix.empty())
		Result += Format("LocalPathPrefix %s\n", m_LocalPathPrefix.c_str());

	if (!m_InternetPathPrefix.empty())
		Result += Format("InternetPathPrefix %s\n", m_InternetPathPrefix.c_str());

	if (m_Language != morphUnknown)
		Result += GetStringByLanguage(m_Language)+"\n";


	if (!m_bCaseSensitive)
		Result += Format("CaseInsensitive\n");

	if (m_bShowNumberOfRelevantDocuments)
		Result += Format("ShowNumberOfRelevantDocuments\n");
	

	if (m_bUseParagraphTagToDivide)
		Result += Format("UseParagraphTagToDivide\n");
				
	if (!m_bEmptyLineIsSentenceDelim)
		Result += Format("EmptyLineIsNotSentenceDelim\n");

				
	if (!m_bUseIndention)
		Result += Format("DontUseIndention\n");
			
	if (m_bUseDwdsThesaurus)
		Result += Format("UseDwdsThesaurus\n");
			
	if (m_bIndexPunctuation)
		Result += Format("IndexPunctuation\n");

	if (m_bResumeOnIndexErrors)
		Result += Format("ResumeOnIndexErrors\n");
	

	if (m_bQueryOnlyFiles)
		Result += Format("QueryOnlyFiles\n");

	if (m_bDisableDefaultQueryLexicalExpansion)
		Result += Format("DisableDefaultQueryLexicalExpansion\n");

	if (m_LeftKwicContextSize != DefaultKwicContextSize)
		Result += Format("LeftKwicContextSize %i\n", m_LeftKwicContextSize);

	if (m_NumberOfKwicLinesInSnippets != 10)
		Result += Format("NumberOfKwicLinesInSnippets %i\n", m_NumberOfKwicLinesInSnippets);

	if (m_TfIdfRank != 0.3)
		Result += Format("TfIdfRank %f\n", m_TfIdfRank);
	if (m_NearRank != 0.3)
		Result += Format("NearRank %f\n", m_NearRank);
	if (m_PositionRank != 0.3)
		Result += Format("PositionRank %f\n", m_PositionRank);
	if (m_InterpDelimiter != "#")
	{
		Result += Format("InterpDelimiter  %s\n", m_InterpDelimiter.c_str()  );
		
	}
	if (m_IndicesToShow.size() > 1 || (m_IndicesToShow.size() == 1 &&  m_IndicesToShow[0] != 0))
	{
		string s = "IndicesToShow ";
		for(size_t i=0; i <m_IndicesToShow.size(); i++)
			s += Format("%i ",m_IndicesToShow[i]+1);
		Result += s+"\n";
	}

	if (m_RightKwicContextSize != DefaultKwicContextSize)
		Result += Format("RightKwicContextSize %i\n", m_RightKwicContextSize);

	if (m_bArchiveIndex)
		Result += Format("ArchiveIndex\n");
				
	if (m_bIndexMorphPatterns)
		Result += Format("IndexMorphPatterns\n");

	if (m_HtmlHighlighting.m_bWasReadFromString)
		Result += Format("HtmlHighlighting %s\n", m_HtmlHighlighting.ToString().c_str());

	if (m_TextHighlighting.m_bWasReadFromString)
		Result += Format("TextHighlighting %s\n", m_TextHighlighting.ToString().c_str());

	if (m_TableHighlighting.m_bWasReadFromString)
		Result += Format("TableHighlighting %s\n", m_TableHighlighting.ToString().c_str());

	Result += Format("IndexType %s\n", GetIndexTypeStr() );

	if (m_bOutputBibliographyOfHits)
		Result += Format("OutputBibliographyOfHits\n");

	if (m_bIndexChunks)
		Result += Format("IndexChunks\n");

	if (m_bUserMaxTokenCountInOnePeriod)
		Result += Format("UserMaxTokenCountInOnePeriod %i\n", m_UserMaxTokenCountInOnePeriod);			

	if (m_Utf8)
		Result += "Utf8\n";

	if (m_bAllowUnsafeQueries)
		Result += "AllowUnsafeQueries\n";

	if (m_bAllowCountByTokenAttributes)
		Result += "AllowCountByTokenAttributes\n";

	if (!m_Bibl.m_DefaultAttrName.empty())
		Result += Format("DefaultBibl %s\n", m_Bibl.m_DefaultAttrName.c_str());

	Result += m_Txd.configString("Expand ");

	Result += Format("MaxRegExpExpansionSize %i\n", m_MaxRegExpExpansionSize);
	Result += Format("MaxCachedHitsCount %zi\n", m_MaxCachedHitsCount);
	Result += Format("MaxQueryCacheSize %zi\n", m_MaxQueryCacheSize);

	if (m_bDwdsCorpusInterface)
		Result += Format("DwdsCorpusInterface\n");

    for (size_t i=0; i < m_Indices.size(); i++)

	if (m_bGutenbergInterface)
		Result += Format("GutenbergInterface\n");
	

	if (m_bNoContextOperator)
		Result += Format("NoContextOperator\n");

	string IndicesStr = GetIndicesString();
	if (!IndicesStr.empty())
		Result += "Indices " + IndicesStr + "\n";

	IndicesStr = GetBorderIndicesString();
	if (!IndicesStr.empty())
		Result += "HitBorders " + IndicesStr + "\n";
	
	Result += m_Bibl.GetFreeBibiAttributesDescr();

	return Result;
};

bool CConcIndexator::SaveOptions(string FileName) const
{
	string PathFile = MakeFName(FileName, "opt");
	FILE* fp = fopen(PathFile.c_str(), "w");
	if (!fp) return false;
	string s  = SaveOptionsToString();
	if (!s.empty())
		fprintf (fp,"%s", s.c_str());
	fclose(fp);
	return true;
};


bool	CConcIndexator::HasEqualOptions(const CConcIndexator&  X) const
{
	string s1  = SaveOptionsToString();
	string s2  = X.SaveOptionsToString();
	return s1 == s2;
};
