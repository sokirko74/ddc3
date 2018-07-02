//-*- Mode: C++; c-basic-offset: 8; -*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2018 by Bryan Jurish
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
#include "ConcCommon.h"
#include "ConcIndexator.h"
#include "sys/stat.h"
#include "time.h"
#include "limits.h"
#include "ConcordAlgorithm.h"
#include "../tinyxml/tinyxml.h"
#include "../RmlTar/RmlTar.h"
#include "../GraphanLib/HTMLConv.h"
#include "../CommonLib/ddcString.h"
#include "../CommonLib/ddcThread.h"

#ifdef DETECT_MEMORY_LEAK
	#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
	#endif
#endif




//===========================================
//================== Common functions =======
//===========================================


bool bEnglishMorph = false;
bool bRussianMorph = false;
bool bGermanMorph = false;
CLemmatizerEnglish* engLemmatizer = 0;
CLemmatizerRussian* rusLemmatizer = 0;
CLemmatizerGerman* gerLemmatizer = 0;

CEngGramTab* engGramTab = 0;
CRusGramTab*  rusGramTab = 0;
CGerGramTab*  gerGramTab = 0;

//! global mutex for non-thread-safe curl operations (global init, lru-cached proxy)
pthread_mutex_t ddcMorphMutex = PTHREAD_MUTEX_INITIALIZER;

template <class  T, class Y>
void InitMorphologySystem(T*& Lemmatizer, Y*& Gramtab)
{
	Lemmatizer = new T;
	if (!Lemmatizer)
		return;

	pthread_mutex_lock(&ddcMorphMutex);
	try {
		string l = GetStringByLanguage(Lemmatizer->GetLanguage());
		ddcLogDebug("   dictionary");
		string strError;
		if (!Lemmatizer->LoadDictionariesRegistry(strError)) {
			ddcLogError(Format("Cannot load %s  morphological dictionary: %s", l.c_str(), strError.c_str()));
			delete Lemmatizer;
			Lemmatizer = 0;
		}

		ddcLogDebug("   gramtab");
		Gramtab = new Y;
		if (!Gramtab) {
			pthread_mutex_unlock(&ddcMorphMutex);
			return;
		}
		if (!Gramtab->LoadFromRegistry()) {
			ddcLogError(Format("Cannot load %s  gramtab", l.c_str()) );
			delete Gramtab;
			Gramtab = 0;
		}
	}
	catch (...) {
		pthread_mutex_unlock(&ddcMorphMutex);
		throw;
	}

	pthread_mutex_unlock(&ddcMorphMutex);
};


const CLemmatizer* GetLemmatizerByLanguage (MorphLanguageEnum Langua)
{
	if  (Langua == morphEnglish)
	{
		if (!bEnglishMorph) 
		{
			InitMorphologySystem(engLemmatizer, engGramTab);
			bEnglishMorph = true;
		};
		return engLemmatizer;

	}
	else
		if  (Langua == morphRussian)
		{
			if (!bRussianMorph) 
			{
				InitMorphologySystem(rusLemmatizer, rusGramTab);
				bRussianMorph = true;
			};
			return rusLemmatizer;
		}
		else
			if  (Langua == morphGerman)
			{
				if (!bGermanMorph) 
				{
					InitMorphologySystem(gerLemmatizer, gerGramTab);
					bGermanMorph = true;
				};
				return gerLemmatizer;
			}
			else
			   return 0;

};


const CAgramtab* GetGramtabByLanguage (MorphLanguageEnum Langua)
{
		if  (Langua == morphEnglish)
		{
			if (!bEnglishMorph) 
			{
				InitMorphologySystem(engLemmatizer, engGramTab);
				bEnglishMorph = true;
			};
			return engGramTab;
		}
		else
			if  (Langua == morphRussian)
			{
				if (!bRussianMorph) 
				{
					InitMorphologySystem(rusLemmatizer, rusGramTab);
					bRussianMorph = true;
				};
				return rusGramTab;
			}
			else
			 if  (Langua == morphGerman)
				{
					if (!bGermanMorph) 
					{
						InitMorphologySystem(gerLemmatizer, gerGramTab);
						bGermanMorph = true;
					};
					return gerGramTab;
				}
			 else
			    return 0;
};



bool InitConcordDicts()
{
	try
	{	
		bRussianMorph = true;
		ddcLogInfo("loading Russian morphology");
		InitMorphologySystem(rusLemmatizer, rusGramTab);

		bEnglishMorph = true;
		ddcLogInfo("loading English morphology");
		InitMorphologySystem(engLemmatizer, engGramTab);

		bGermanMorph = true;
		ddcLogInfo("loading German morphology");
		InitMorphologySystem(gerLemmatizer, gerGramTab);

		return true;
	}
	catch (CExpc c)
	{
		fprintf (stderr, "Exception %s \n",c.m_strCause.c_str());
		return false;
	}
	catch (...)
	{
		return false;
	}

}

void FreeConcordDicts()
{
	if (rusLemmatizer) delete rusLemmatizer;
	if (engLemmatizer) delete engLemmatizer;
	if (gerLemmatizer) delete gerLemmatizer;
	if (rusGramTab) delete rusGramTab;
	if (engGramTab) delete engGramTab;
	if (gerGramTab) delete gerGramTab;
	
	
};



// Here is the definition of a token
inline bool IsWord (const CGraphmatFile*	piGraphmat, long GraLine)	 
{
	return		piGraphmat->HasDescr(GraLine, OLLE)
		||	piGraphmat->HasDescr(GraLine, ORLE);
};

inline bool IsDigit (const CGraphmatFile*	piGraphmat, long GraLine)	 
{
	return		piGraphmat->HasDescr(GraLine, ODigits)
		||	piGraphmat->HasDescr(GraLine, ONumChar);
};

inline bool IsSentenceEnd (const CGraphmatFile*	piGraphmat, long GraLine)	 
{
	return	piGraphmat->HasDescr(GraLine,OSentEnd) ;
}




vector<string> GetGramInfosFromWord(const char* GraLine, MorphLanguageEnum Langua, bool bCapital)
{

	const CLemmatizer* Lemmatizer = GetLemmatizerByLanguage(Langua);
	if (!Lemmatizer) return vector<string>();

	const CAgramtab* A = GetGramtabByLanguage(Langua);

	char SrcCodesBuffer[2000];
	
	Lemmatizer->GetAllAncodesQuick((BYTE*)GraLine, bCapital,  (BYTE*)SrcCodesBuffer, true);

	size_t len = strlen(SrcCodesBuffer);
	vector<string> Result;
	QWORD CommonGrammems = 0;
	bool bReadCommonGrammems = false;
	for (size_t i=0; i < len; i+=2)
	{
		if (!bReadCommonGrammems)
		{
			if (SrcCodesBuffer[i] == '?')
				CommonGrammems = 0;
			else
				A->GetGrammems(SrcCodesBuffer+i, CommonGrammems);
			bReadCommonGrammems = true;
			continue;
		};
		if (SrcCodesBuffer[i] == ';')
		{
			i--;
			bReadCommonGrammems = false;
			continue;
		};

		int ResultSavedSize = Result.size();
		{
			BYTE pos = A->GetPartOfSpeech(SrcCodesBuffer+i);
			// all nouns in German are uppercase
			if (Langua == morphGerman)
				if (!bCapital)
					if ( (pos == gSUB) || (pos == gEIG) )
						continue;

			if (pos != UnknownPartOfSpeech)
				Result.push_back(A->GetPartOfSpeechStr(pos));
		};
		
		QWORD Grammems;
		A->GetGrammems(SrcCodesBuffer+i, Grammems);

		size_t GrammemsCount = A->GetGrammemsCount();
		for (int k = 0; k <GrammemsCount; k++)
			if (_QM(k) & (Grammems|CommonGrammems))
				Result.push_back(A->GetGrammemStr(k));

		sort(Result.begin()+ResultSavedSize, Result.end());

		Result.push_back(MorphAnnotationsDelim);
	}

	
	return Result;
};
//==============================================================
//=======================  CHighlightTags ======================
//==============================================================


CSourceFileHolder::CSourceFileHolder() 
{
	m_bModifiedListOfFiles = false;
}

bool CSourceFileHolder::SaveSourceFileList(string FileName)
{
	FILE* fp = fopen(FileName.c_str(), "wb");
	if (!fp) return false;
	for (long i=0;i < m_SourceFiles.size(); i++)
		fprintf(fp, "%s\n",m_SourceFiles[i].c_str());
	fclose(fp);

	m_bModifiedListOfFiles  = false;
	return true;
}

bool CSourceFileHolder::ReadSourceFileList(string FileName)
{
	FILE* fp = fopen(FileName.c_str(), "rb");
	if (!fp) 
	{
	    fprintf (stderr, "could not open %s\n", FileName.c_str());
	    return false;
    	}

	char s[1024];
	m_SourceFiles.clear();
	while (fgets(s,1024,fp))
	{
		string q = s;
		Trim(q);
		if (q.empty()) continue;
		//-- moo: interpret relative document filenames in .con file wrt the directory containing .con file itself
		string qr = RelativeFileName(FileName,q);
		m_SourceFiles.push_back(qr);
	};
	fclose(fp);

	return true;
}



void CSourceFileHolder::AddSourceFile(const char* FileName)
{
	m_SourceFiles.push_back(FileName);
	m_bModifiedListOfFiles = true;
}

void CSourceFileHolder::AddSourceFilesFrom(const CSourceFileHolder& X)
{
	m_SourceFiles.insert(m_SourceFiles.end(), X.m_SourceFiles.begin(),X.m_SourceFiles.end());
	m_bModifiedListOfFiles = true;
}

bool CSourceFileHolder::IsModified	( ) const
{
	return m_bModifiedListOfFiles;
};

void CSourceFileHolder::DeleteSourceFile(long ItemNo) 
{
	m_SourceFiles.erase(m_SourceFiles.begin()+ItemNo);
	m_bModifiedListOfFiles = true;
};

void CSourceFileHolder::DeleteAllSourceFiles() 
{
	m_SourceFiles.clear();
	m_bModifiedListOfFiles = true;
};

size_t CSourceFileHolder::GetSourceFilesCount()  const 
{
	return m_SourceFiles.size();
};

string  CSourceFileHolder::GetSourceFile(size_t FileNo)  const
{
	return m_SourceFiles[FileNo];
};

// found a file of the corpus which does not  exist, if not return -1
int CSourceFileHolder::FoundNotExistedFile	( ) const
{
	for (int i =0; i<m_SourceFiles.size();i++)
		if (access (m_SourceFiles[i].c_str(), 04) != 0)
			return i;

	return -1;
};



//==============================================================
//=======================  CHighlightTags ======================
//==============================================================
CHighlightTags::CHighlightTags()
{
	m_bWasReadFromString = false;
};

bool		CHighlightTags::ReadFromString(const string& s)
{
	string q = s; 
	StringTokenizer tok(Trim(q).c_str(), ";");
	vector<string> tokens;
	while (tok())
	{
		string l = tok.val();
		Trim(l);
		tokens.push_back(l);
	};
	if (tokens.size() != 4) 
		return false;
	m_FirstOpener = unescapeCString(tokens[0]);
	m_FirstCloser = unescapeCString(tokens[1]);
	m_RestOpener = unescapeCString(tokens[2]);
	m_RestCloser = unescapeCString(tokens[3]);
	m_bWasReadFromString = true; 
	return true;
}

string CHighlightTags::ToString() const
{
	return Format("%s;%s;%s;%s", 
		      escapeCString(m_FirstOpener).c_str(),
		      escapeCString(m_FirstCloser).c_str(),
		      escapeCString(m_RestOpener).c_str(),
		      escapeCString(m_RestCloser).c_str());
};

//==============================================================
//=======================  CConcIndexator ======================
//==============================================================


CConcIndexator::CConcIndexator()  
{
    InitDefaultOptions();
};


CConcIndexator::~CConcIndexator()
{
};


string CConcIndexator::GetIndexItemSetByVectorString (const vector<string>& TokenProperties, bool bRegexp )
{
	string Result;
	if (bRegexp) 
		Result = ".*";

	size_t cnt = TokenProperties.size();
	for (size_t i=0;i <cnt; i++)
		{
			Result += '@';
			Result += TokenProperties[i];
			Result += '@';
			if (bRegexp) 
				Result += MorphAnnotationsDelimRegExp;
		};

	return Result;
};


void CConcIndexator::AssertHasPath() const
{
	assert(m_Path != "#empty_path");
	if (m_Path == "#empty_path")
	{
		ErrorMessage("Uninitialized path");
		throw CExpc(errNonePath, "Exception: Uninitialized path for index files");
	};
};

//!  graphematical definition of a token
bool	CConcIndexator::IsDWDSToken (const CGraphmatFile*	piGraphmat, long GraLine)	 const 
{
	return		IsSentenceEnd(piGraphmat, GraLine) 
			||	IsWord(piGraphmat, GraLine)
			||	IsDigit(piGraphmat, GraLine)
			||	(
							m_bIndexPunctuation
						&&	piGraphmat->HasDescr(GraLine, OPun) 
				)
			;
}






bool	CConcIndexator::WasIndexed() const
{
	if (m_Path.empty()) return false;
	return access(GetSearchPeriodsFileName().c_str(), 04) == 0;
};

void CConcIndexator::InitGraphanProperties (CGraphmatFile* piGraphmat) const
{
	piGraphmat->m_Language = m_Language;
	piGraphmat->m_bUseParagraphTagToDivide = m_bUseParagraphTagToDivide;
	piGraphmat->m_bEmptyLineIsSentenceDelim = m_bEmptyLineIsSentenceDelim;
	piGraphmat->m_bUseIndention = m_bUseIndention;
	piGraphmat->m_bConvertRussianJo2Je = true;
	piGraphmat->m_bFilterUnprintableSymbols = false;
};




string CConcIndexator::GetFileNameForCorpusFileNames() const 
{
	return MakeFName(m_Path, "_con");
};
string CConcIndexator::GetFileNameForMaskedFiles() const 
{
	return MakeFName(m_Path, "_masked");
};

vector<string> CConcIndexator::GetTokenFields(const COutputToken &tok)
{
    vector<string> fields(m_IndicesToShow.size());
    size_t fi, i0, i1, dsize=m_InterpDelimiter.size();
    const string &istr = tok.m_InterpStr;

    fields[0] = tok.m_TokenStr;
    for (fi=1, i0=dsize; fi < fields.size() && i0 < tok.m_InterpStr.size(); fi++, i0=i1+dsize) {
	i1=istr.find(m_InterpDelimiter, i0); 
	fields[fi].assign(istr, i0, i1-i0);
	if (i1>=istr.size()) break;
    }

    return fields;
};



bool CConcIndexator::SaveCorpusFileList() const
{
	string ConFile = GetFileNameForCorpusFileNames();
	FILE* cfp = fopen(ConFile.c_str(), "wb");
	if (!cfp) return false;

	string ListFile = ConFile + "_files";
	FILE *lfp = fopen(ListFile.c_str(), "wb");
	if (!lfp) return false;

	string OffsetsFile = ConFile + "_idx";
	FILE *ofp = fopen(OffsetsFile.c_str(), "wb");
	if (!ofp) return false;

	string PrefixFile = ConFile + "_prefix";
	FILE *pfp = fopen(PrefixFile.c_str(), "wb");
	if (!pfp) return false;

	//-- *._con (v2.1.13): VERSION_INFO "\n"
	std::string vmin_str = DDCVersionMinW.str();
	fprintf(cfp, "%s / min-compat %s\n", DDCVersionStr.c_str(), vmin_str.c_str());
	fclose(cfp);

	//-- *._con_prefix (v2.1.13)
	std::string prefix_str = GetCommonFilePrefix();
	fprintf(pfp, "%s\n", prefix_str.c_str());
	fclose(pfp);

	//-- *._con_files, *._con_idx (v2.1.13)
	size_t cnt = m_CorpusFiles.size();
	for (ddcCorpusList<>::IdT i=0; i< cnt; i++) {
		ddcCorpusList<>::OffT pos = ftell(lfp);
		fwrite(&pos, sizeof(ddcCorpusList<>::OffT), 1, ofp);
		fprintf(lfp, "%s\n",m_CorpusFiles[i].c_str());
	}
	fclose(ofp);
	fclose(lfp);

	return true;
}


string CConcIndexator::GetCommonFilePrefix() const
{
	string CommonFilePrefix = "";
	for (size_t fi=0; fi < m_CorpusFiles.size(); ++fi) {
		string f = m_CorpusFiles[fi];
		if (fi==0) {
			CommonFilePrefix = f;
		} else {
			int i=0;
			for (; i<min(f.length(), CommonFilePrefix.length()) && f[i]==CommonFilePrefix[i]; ++i) ;
			CommonFilePrefix.erase(i);
		}
	}
	return CommonFilePrefix;
};


bool CConcIndexator::LoadCorpusFiles()
{
	m_CorpusFiles.clear();
	string ConFile = GetFileNameForCorpusFileNames();

	//-- open raw corpus-file list
	try {
		m_CorpusFiles.open(ConFile, ConFile+"_files", ConFile+"_idx", m_bMemoryMap);
		ddc_format_version_check(m_CorpusFiles.VersionString().c_str(), ConFile.c_str());
	}
	catch (CExpc &e) {
		ErrorMessage (Format("Exception[%d]: %s", e.code(), e.what()));
		return false;
	}
	catch (exception &e) {
		ErrorMessage (Format("Exception: %s", e.what()));
		return false;
	}

	//-- get shared filename prefix (*._con_prefix)
	string PrefixFile = ConFile+"_prefix";
	if (FileExists(PrefixFile)) {
		LoadFileToString(PrefixFile, m_CommonFilePrefix, true);
	} else {
		ddcLogWarn("WARNING: CConcIndexator::LoadCorpusFiles(): shared prefix file '"+PrefixFile+"' not found: please upgrade your index!");
		m_CommonFilePrefix = GetCommonFilePrefix();
	}

	UpdateTimestamp(ConFile.c_str());
	return true;
};

bool CConcIndexator::LoadMaskedFiles()
{
	m_MaskedFiles.clear();
	// reading corpus files from *.con file
	FILE* fp = fopen(GetFileNameForMaskedFiles().c_str(), "rb");
	if (!fp) return true;
	char s[1024];
	while (fgets(s,1024,fp)) {
		string file = s;
		Trim(file);
		if (file.empty()) continue;
		ddcCorpusList<>::IdT fileid = m_CorpusFiles.find(file);
		if (fileid == m_CorpusFiles.NO_ID) {
			ddcLogWarn( Format("CConcIndexator::LoadMaskedFiles(): %s in %s is not a corpus file name", file.c_str(), GetFileNameForMaskedFiles().c_str()) );
			return false;
		}
		m_MaskedFiles.insert(fileid);
	}
	fclose(fp);
	return true;
};


bool CConcIndexator::LoadSourceFilesAndOptions(string FileName)
{
	m_LocalPathPrefix = "";
	m_InternetPathPrefix = "";

	m_Path = FileName;

	m_bUserMaxTokenCountInOnePeriod = false;

	// reading options  from *.opt file
	string PathFile = MakeFName(FileName, "opt");
	string AllOptions;
	if (LoadFileToString(PathFile, AllOptions))
	{
		if (!LoadOptionsFromString(AllOptions)) 
			return false;
	}
	else
        {
	    ddcLogWarn( Format("CConcIndexator::LoadSourceFilesAndOptions(): Warning: cannot find file %s", PathFile.c_str()) );
	}

	SetPath(FileName);

	// reading source files
	if (!ReadSourceFileList(FileName))
		return false;

	UpdateTimestamp(FileName.c_str());

	return true;
};



bool	CConcIndexator::DestroyIndex()
{	
	AssertHasPath();

	if (!RemoveHitBordersFileAndClear(m_Path))
		return false;

	if (!DestroyIndices())
		return false;

	if (FileExists(GetSearchPeriodsFileName().c_str()))
		if (remove(GetSearchPeriodsFileName().c_str()))
			return false;

	if (FileExists(GetFileNameForCorpusFileNames().c_str()))
		if (remove(GetFileNameForCorpusFileNames().c_str()))
			return false;
	m_CorpusFiles.clear();

	if (FileExists(GetFileNameForMaskedFiles().c_str()))
		if (remove(GetFileNameForMaskedFiles().c_str()))
			return false;
	m_MaskedFiles.clear();

	return true;

};







DWORD CConcIndexator::GetMaxTokenCountInOnePeriod() const
{
	if (m_bUserMaxTokenCountInOnePeriod)
		return m_UserMaxTokenCountInOnePeriod;
	else
		return 5000000;
};

bool	GetTextFromXMLRecursive(TiXmlNode* parent, string& Result)
{
	if (parent->Type() == TiXmlNode::TEXT)
	{
		if ( Result.empty() )
			Result += Format("\n<pb %u>\n",UnknownPageNumber);

		Result += parent->Value();
	}
	else
		if (parent->Type() == TiXmlNode::ELEMENT)
		{
			string type = parent->Value();
			Trim(type);

			if (type == "pb")
			{
				const char* pb_str = ((TiXmlElement*)parent)->Attribute("n");
				if (!pb_str) 
				{
					ErrorMessage ("Cannot parse page break element");
					return false;
				};
				Result += Format("\n<pb %s>\n",pb_str);
			}
			else
			{
				for (TiXmlNode* child = parent->FirstChild();  child;  child = child->NextSibling())
				{
					if (!GetTextFromXMLRecursive(child, Result)) 
						return false;
				};
			};
			if (type == "p")
				Result += "\n</p>\n";
		}
		else
		if (parent->Type() == TiXmlNode::COMMENT)
		{
			// skipping comments
		}
		else
		{
			ErrorMessage (Format("Unknown xml-node:%s. Some parts of file cannot be parsed!", parent->Value()));
			return false;
		};

	return true;
};

// read the input xml that is in CWB-format (corpus work bench format)
bool	GetCWBFormattedStringRecursive(const TiXmlNode* parent, string& Result)
{
	if (parent->Type() == TiXmlNode::TEXT)
	{
		Result += parent->Value()+string("\n");
	}
	else
		if (parent->Type() == TiXmlNode::ELEMENT)
		{
			string type = parent->Value();
			Trim(type);
			bool bNotLineBreak = (type != PredefinedTableLineTag);
			if (type == "pb")
			{
				const char*	page_number = parent->ToElement()->Attribute("n");
				if (page_number)
				{
					Result += Format("<pb %s>\n", page_number);
					return true;
				}
				else
				{
					ErrorMessage("bad page break");						
					return false;
				};
			}
			else
				if (bNotLineBreak)
					Result += Format("\n<%s>\n", type.c_str());




			for (TiXmlNode* child = parent->FirstChild();  child;  child = child->NextSibling())
			{
				string R;
				if (!GetCWBFormattedStringRecursive(child, Result)) 
					return false;
			};

			if (bNotLineBreak)
				Result += Format("\n</%s>\n", type.c_str());
			
		}
		else
		{
			ErrorMessage (Format("Unknown xml-node:%s. Some parts of file cannot be parsed!", parent->Value()));
			return false;
		};

	return true;
};


bool	CConcIndexator::LoadXmlFile(string FileName, const char* pFileBuffer, CGraphmatFile* piGraphmat, CBibliography& Bibl, string& strError)
{
	if (m_Bibl.GetTextAreasCount() == 0)
	{
		strError = Format("Error! Cannot index xml files, since no text areas defined in the options file!");
		return false;
	}

	TiXmlDocument doc( FileName.c_str() );
	
	if (!m_Bibl.LoadXmlAndReadBibliography(doc, pFileBuffer, Bibl, strError)) 
		return false;

	vector<TiXmlElement*> TextAreas;
	if (!m_Bibl.GetTextAreaElements(doc, TextAreas, strError))
		return false;

	string AllTexts;
	for (size_t TextAreaNo = 0; TextAreaNo< TextAreas.size(); TextAreaNo++)
	{
		TiXmlElement* body = TextAreas[TextAreaNo];

		string SourceText;

		if (Bibl.m_StartPageInfo != UnknownPageNumber)
			SourceText = Format("\n<pb %u>\n",Bibl.m_StartPageInfo);
	
		if (!GetTextFromXMLRecursive(body, SourceText)) 
		{
			ErrorMessage (Format("Cannot get text from file %s", FileName.c_str()));
			return false;
		};

		AllTexts += SourceText;
		AllTexts += "</textarea>\n\n";
	}

	bool bResult = piGraphmat->LoadStringToGraphan(AllTexts);
	if (!bResult)
		ErrorMessage (Format("piGraphmat->LoadStringToGraphan failed for file %s, Error:%s", FileName.c_str(), piGraphmat->GetLastError().c_str() ));

	return bResult;
};

bool IsXmlFile(const string& FileName)
{
	return				(FileName.length() > 4)
				&&	(		(FileName.substr(FileName.length()-4) == ".xml")
						||	(FileName.substr(FileName.length()-4) == ".XML")
					);
};

bool IsTarFile(const string& FileName)
{
	return				(FileName.length() > 4)
				&&	(		(FileName.substr(FileName.length()-4) == ".tar")
						||	(FileName.substr(FileName.length()-4) == ".TAR")
					);
};





void CConcIndexator::CalculateSearchPeriods	(DWORD MaxTokenCountInOnePeriod )
{
	if (GetFileBreaks().empty()) return;

	// Calculating Search Periods
	
	m_SearchPeriods.clear();

	CTokenNo StartTokenNo = 0;
	for (size_t i=0; i < m_CorpusFiles.size(); i++)
	{
		CTokenNo  FileStart = GetFileStartTokenNo(i);
		if (FileStart - StartTokenNo > MaxTokenCountInOnePeriod)
		{
			m_SearchPeriods.push_back(FileStart);
			StartTokenNo = FileStart;
		};
	};

	m_SearchPeriods.push_back(GetCorpusEndTokenNo());
};


bool	CConcIndexator::IndexOneTableTextArea(const string& Text, const CPageNumber& StartPageFromHeader, size_t& page_breaks_count, CTokenNo& NewCorpusEndTokenNo,	string& strError)
{
	StringTokenizer tok(Text.c_str(), "\r\n");
	deque<pair<string,CTokenNo> >	start_chunk_tags_str_and_pos;
	StartTextAreaBorders();
	try {
		while (tok())
		{
			string q = tok.val();
			Trim(q);
			if (q.empty()) 
			{
				strError = "Empty lines in CWB format!";
				return false;
			}
			size_t len = q.length();
			if	(		(len < 100)
					&&	(len > 2)
					&&	(q[0] == '<') 
					&&	(q[len-1] == '>') 
				)
			{
				if (q[1] != '/')
				{
					string tag_name = q.substr(1,len-2); // ge the tag name, for example "vp" from "</vp>"
					if (tag_name.length() > 3 && (tag_name.substr(0,3) == "pb ")) // page break
					{
						int page_number = atoi(tag_name.c_str() + 3);
						if (page_number != 0)
						{
							// add the first page break from the header, if it is not specified in the body
							if (page_breaks_count == 0) {
								// moo (v2.0.7, Thu, 28 Mar 2013 09:52:05 +0100): this should never happen any more
								if ( (NewCorpusEndTokenNo - StartPageFromHeader.m_StartTokenNo) > 0)
									AddPageBreak(StartPageFromHeader);
							}

							CPageNumber Page;
							Page.m_PageNumber = page_number;
							Page.m_StartTokenNo = NewCorpusEndTokenNo;
							AddPageBreak(Page);
							page_breaks_count++;
						}
						else
						{
							strError = Format("bad page break (%s)",  q.c_str());						
							return false;
						};
					}
					else
						if ( !IsRegisteredBreak(tag_name) ) 
						{
							if (m_bIndexChunks)
								start_chunk_tags_str_and_pos.push_back(make_pair(tag_name, NewCorpusEndTokenNo));
						};


				}
				else // an end tag
				{

					string tag_name = q.substr(2,len-3); // ge the tag name, for example "vp" from "</vp>"
					int BrCollec = GetBreakCollectionIndexByName(tag_name);
					if (BrCollec != -1) {
						AddBreakByIndex(BrCollec, NewCorpusEndTokenNo);
					}
					else  {
					    // if it is not a registered break
                        
						if (m_bIndexChunks)
						{
							if (		start_chunk_tags_str_and_pos.empty() 
									||	(start_chunk_tags_str_and_pos.back().first != tag_name)
								)
							{
								strError  = Format("Error! An end tag without a start tag is found (%s<>%s)",
													start_chunk_tags_str_and_pos.back().first.c_str(), tag_name.c_str() ); 
								return false;
							}
							if (NewCorpusEndTokenNo > 0)
							{
								string tag = Format("%s,%i",start_chunk_tags_str_and_pos.back().first.c_str(), 
															NewCorpusEndTokenNo-start_chunk_tags_str_and_pos.back().second);
								start_chunk_tags_str_and_pos.pop_back();
								assert (m_pChunkIndex);
								m_pChunkIndex->InsertToInputLoadIndex(tag.c_str(),tag.length(), vector<CTokenNo>(1, NewCorpusEndTokenNo-1) );
							}
							else
							{
								// An empty element at the beginning of the corpus is ignored; 
							}
						}
					}
				}

			}
			else
			{
				if ( !IndexOneToken(q.c_str(), NewCorpusEndTokenNo))
				{
					strError = Format("Cannot index line: %s ", q.c_str());
					return false;
				};
				
				NewCorpusEndTokenNo++;
			}
		};
		if (!EndTextAreaBorders(NewCorpusEndTokenNo))
		{
			strError = Format("Cannot add end text area breaks");
			return false;
		};
	}
	catch (CExpc c)
	{
		strError = Format("Exception %s while processing \"%s\"\n", c.m_strCause.c_str(), tok.val());
		return false;
	}
	catch (...)
	{
		strError = Format("Exception while processing \"%s\"\n", tok.val());
		return false;
	};
	return true;
}

// Return value: return true, if the input XML is valid and it fits the index structure
bool	CConcIndexator::IndexTable(string FileName, const char* pFileBuffer, 	CTokenNo& NewCorpusEndTokenNo,	string& strError)
{

	
	CBibliography Bibliography;
		
	TiXmlDocument doc( FileName.c_str() );
	if (!m_Bibl.LoadXmlAndReadBibliography(doc, pFileBuffer, Bibliography, strError)) return false;

	vector<TiXmlElement*> TextAreas;
	if (!m_Bibl.GetTextAreaElements(doc, TextAreas, strError))
	{	
		return false;
	}

	CPageNumber StartPageFromHeader;
	StartPageFromHeader.m_PageNumber = Bibliography.m_StartPageInfo;
	StartPageFromHeader.m_StartTokenNo = NewCorpusEndTokenNo;
	size_t page_breaks_count = 0;

	//moo: add initial page break if requested
	if (StartPageFromHeader.m_PageNumber > 0 && StartPageFromHeader.m_PageNumber != UnknownPageNumber)
		AddPageBreak(StartPageFromHeader);
	
	//iterate through all text areas 
	for (size_t TextAreaNo = 0; TextAreaNo< TextAreas.size(); TextAreaNo++)
	{
		TiXmlElement* textarea = TextAreas[TextAreaNo];
		string Text;
		// get text from xml
		if (!GetCWBFormattedStringRecursive(textarea,  Text))
			return false;

		// index one text area
		if (!IndexOneTableTextArea(Text, StartPageFromHeader, page_breaks_count, NewCorpusEndTokenNo, strError))
			return false;
	}
	
	if (NewCorpusEndTokenNo != StartPageFromHeader.m_StartTokenNo)
	{
		// if at least one token is found, then add a bibliographical record
		if (!m_Bibl.AddIndexItem(Bibliography))
			return false;
	};
	
	return true;
};

bool	CConcIndexator::LoadFileIntoGraphan(string FileName,  const char* pFileBuffer,	CGraphmatFile* piGraphmat, CBibliography& Bibl, string& strError)
{
	Bibl.CleanBibliography();
	try
	{
		if	(IsXmlFile(FileName))
		{
			if (!LoadXmlFile(FileName, pFileBuffer, piGraphmat, Bibl, strError)) 
			{
				strError += "\nCConcIndexator::LoadXmlFile has crushed!";
				return false;
			}
		}
		else
		{
			if (!piGraphmat->LoadStringToGraphan(pFileBuffer)) 
			{
				if (!piGraphmat->GetLastError().empty())
					strError = piGraphmat->GetLastError();
				else
					strError = "CGraphmat::LoadStringToGraphan has crushed! ";
				return false;
			}
			m_Bibl.SetFreeBiblAttribsEmpty(Bibl);
		};
		

	}
	catch (CExpc c)
	{
		strError = Format("Exception %s in CConcIndexator::LoadFileIntoGraphan\n", c.m_strCause.c_str());
		return false;
	}
	catch(...)
	{
		strError = "CConcIndexator::LoadFileIntoGraphan has crushed! (general exception)";
		ErrorMessage ("An exception occurred in CConcIndexator::LoadFileIntoGraphan while processing " + FileName);
		return false;
	}

	return true;
}



bool	CConcIndexator::IndexTextOrHtmlFile(
					    CGraphmatFile* piGraphmat, 
					    string FileName, 
					    const char* pFileBuffer,
					    const CDwdsThesaurus* pDwdsThesaurus,
					    CTokenNo& NewCorpusEndTokenNo,
					    string& strError)
{
	CBibliography Bibl;
	if (!LoadFileIntoGraphan(FileName, pFileBuffer, piGraphmat, Bibl, strError))
	{
		if (strError.empty())
			strError = "CConcIndexator::LoadFileIntoGraphan has crushed!";
		return false;
	}

	long GraLinesCount = piGraphmat->GetTokensCount();
	if (GraLinesCount <= 1)  
	{
		// the file is empty
		return true;
	};


	CTokenNo StartTokenNo = NewCorpusEndTokenNo; 
	CTokenNo CurrSentenceBreak = NewCorpusEndTokenNo;

	size_t FileTokensCount = 0;
	int SentNo = 0;
	char OneIndexLine[5000];
	bool bTheFirstPageBreakIsFound = false;
	
	int TextAreaNo = 0;
	int TextAreasCount = m_Bibl.GetTextAreasCount();
	size_t TextAreaStarter = DWORD_MAX;
	int SentenceBreakCollection = GetBreakCollectionIndexByName("s");
	if ((SentenceBreakCollection == -1) && !m_bQueryOnlyFiles) {
		strError = "could not find sentence collection";
		return false;
	}

	for (long GraLineNo = 1; GraLineNo<GraLinesCount; GraLineNo++)
	{
		bool bSentenceEnd = false;
		bool bToken = IsDWDSToken(piGraphmat, GraLineNo);
		if	( bToken )
		{
 			BYTE TokenLen = piGraphmat->GetUnits()[GraLineNo].GetTokenLength();
			if (TokenLen == 0)
			{
				strError = Format("Fatal error: An empty word is found!\nGraph.Word No %i from %i \n", GraLineNo, GraLinesCount);
				return false;
			};

			const char* Token  = piGraphmat->GetUnits()[GraLineNo].GetToken();
			if ((BYTE)Token[0] == globalFieldDelimeter)
			{
				strError = Format("Error! An input word(LineNo=%i) cannot contain symbol \"%c\"(%i) \n", GraLineNo, (int)globalFieldDelimeter, (unsigned int)globalFieldDelimeter);
				return false;
			};

			strncpy(OneIndexLine, Token, TokenLen);
			OneIndexLine[TokenLen] = globalFieldDelimeter;
			OneIndexLine[TokenLen+1] = 0;

			
			if (m_bUseDwdsThesaurus 
			    &&  (piGraphmat->HasDescr(GraLineNo, OUp)
				 ||  piGraphmat->HasDescr(GraLineNo, OUpLw))
			    ) {
				const char* UpperToken  = piGraphmat->GetUppercaseToken(GraLineNo);
				OneIndexLine[TokenLen+1] = globalFieldDelimeter;
				strcpy(OneIndexLine + TokenLen +  2, pDwdsThesaurus->GetAllThesInterpetations(UpperToken).c_str());
			}

			IndexOneToken(OneIndexLine, NewCorpusEndTokenNo);

                
			// if m_bQueryOnlyFiles then no sentence break collection
			if ( !m_bQueryOnlyFiles && IsSentenceEnd(piGraphmat, GraLineNo) )
			{

				// "1" is for this token
				CurrSentenceBreak = NewCorpusEndTokenNo+1;
				AddBreakByIndex(SentenceBreakCollection, CurrSentenceBreak);

				SentNo++;
				bSentenceEnd = true;
			};
		} // IsDWDSToken == true

		if (piGraphmat->GetUnits()[GraLineNo].IsTextAreaEnd() || TextAreaStarter == NewCorpusEndTokenNo)
		{
			AddBreakByName(PredefinedTextAreaBreakName, NewCorpusEndTokenNo);
			TextAreaNo++;
		}


		if	(		(bToken && (FileTokensCount == 0) && !bTheFirstPageBreakIsFound) 
				||	piGraphmat->GetUnits()[GraLineNo].IsPageBreak()
			)
		{
			bTheFirstPageBreakIsFound = true;
			CPageNumber Page;
			Page.m_PageNumber = piGraphmat->GetPageNumber(GraLineNo);
			//If we have read end of sentence and after it we have read a page break, and
			//there is no  tokens between this end of sentence and  this page break, then we should
			//shift this page break backward to the end of sentence. Otherwise the first sentence of the  next
			//page will be considered as a sentence from the previous  page.
			//For example we have
			//    <pb 13> Sentence1 <end-of-sentence> <pb 14> Sentence2.
			//Sentence2 starts when Sentence1 terminates, then a page break occurs inside(!) of Sentence2,
			//and it means that Sentence2 starts at page 13 and terminates at page 14. That is not true and 
			//we fix this problem.
			

			if	(		bSentenceEnd
					||	(SentNo == 0)
				)
				Page.m_StartTokenNo = NewCorpusEndTokenNo; // normal case
			else
				Page.m_StartTokenNo = CurrSentenceBreak; //  shifting page break to the last end of sentence
				
			AddPageBreak(Page);
		};

		if (bToken)
		{
			NewCorpusEndTokenNo++;

			FileTokensCount++;
		};
	};

       // write the last sentence if it contains at least one token
       if (!m_bQueryOnlyFiles )
	if (CurrSentenceBreak < NewCorpusEndTokenNo)
	{	
        fprintf (stderr,"The last end of sentence is not found, graphematics should be refactored :)\n");
		CurrSentenceBreak = NewCorpusEndTokenNo;
		AddBreakByIndex(SentenceBreakCollection, NewCorpusEndTokenNo);
		SentNo++;

	};

	if (NewCorpusEndTokenNo != StartTokenNo)
	{
		// if at least one token is found, then add a bibliographical record
		m_Bibl.AddIndexItem(Bibl);
	};

	if ( TextAreaNo != TextAreasCount )
	{
		strError = Format("Some text areas are not present in this document\n");
		return false;
	}
	piGraphmat->FreeTable();
	return true;
};

string CConcIndexator::GetShortFilename(size_t posFile) const 
{
	return m_CorpusFiles[posFile].substr(m_CommonFilePrefix.length());
};




string CConcIndexator::GetHtmlReference(size_t posFile) const 
{
	string CorpusFileName = m_CorpusFiles[posFile];
	string ShortFileName  = CorpusFileName.substr(0, m_LocalPathPrefix.length());
	string InterfaceFileName, HtmlRefFileName;
	
	if (ShortFileName == m_LocalPathPrefix)
	{
		InterfaceFileName = ShortFileName;
		HtmlRefFileName = "http://"+m_InternetPathPrefix + InterfaceFileName;
	}
	else
	{
		HtmlRefFileName = InterfaceFileName = CorpusFileName;
	};

	return Format("<a href=\"%s\">%s</a>", HtmlRefFileName.c_str(),InterfaceFileName.c_str());
};



bool CConcIndexator::CreateMorphIndex()
{
	if (!m_bIndexMorphPatterns)
		return true;

	fprintf(stderr,"CreateMorphIndex...\n");
	CStringIndexSet* pMorphIndexSet = GetIndexByAlias("MorphPattern");
	if (!pMorphIndexSet )
	{
		ErrorMessage ("Cannot find MorphPattern index");
		return false;
	};
	CStringIndexSet* pTokensIndexSet = GetIndexByAlias("Token");
	if (!pTokensIndexSet )
	{
		ErrorMessage ("Cannot find Token index");
		return false;
	};
	
	if (!pTokensIndexSet->LoadIndexSet()) // if the index was just created, then Token index is not loaded
	{
		ErrorMessage ("Cannot load Token index");
		return false;
	};

	if (!pMorphIndexSet->DestroyIndexSet())
	{
		ErrorMessage ("Cannot destroy morph. index set (some files cannot be deleted)");
		return false;
	};
	pMorphIndexSet->CreateTempFiles(m_Path);
	size_t CountOfTokens = pTokensIndexSet->m_Index.size();
	size_t OccursCount =0;
	const size_t MaxTokenCountInOnePeriod = GetMaxTokenCountInOnePeriod();

	for (size_t i = 0; i< CountOfTokens; i++)
	{
		if ( (i % 1000) == 0)
				fprintf(stderr, "%zi/%zi (%zi/%zi)             \r", i, CountOfTokens, OccursCount, 3*MaxTokenCountInOnePeriod);

		const char* sToken = pTokensIndexSet->GetIndexItemStr(pTokensIndexSet->m_Index[i]);
		if (CheckLanguage(sToken, m_Language)) 
		{
			vector<string> TokenProperties =  GetGramInfosFromWord(sToken, m_Language, is_upper_alpha((BYTE)sToken[0], m_Language));
			
			if (!TokenProperties.empty()) 
			{
					string GramInfoStr = GetIndexItemSetByVectorString(TokenProperties,false);
				
					vector<CTokenNo> occurrences;
					pTokensIndexSet->ReadAllOccurrences(i, occurrences);
					pMorphIndexSet->InsertToInputLoadIndex (GramInfoStr.c_str(), GramInfoStr.length(), occurrences);	
					OccursCount += occurrences.size();
			}
		}


		if	(		( OccursCount > 3*MaxTokenCountInOnePeriod)
				||	(i+1== CountOfTokens)
			)
		{
	
			pMorphIndexSet->SortInputAndMemoryIndices();
			
			if (!pMorphIndexSet->AddInputLoadIndexToMemoryLoadIndex())
			{
					fprintf (stderr, "AddInputLoadIndexToMemoryLoadIndex returned false in CConcIndexator::CreateMorphIndex\n");
					return false;
			};

			if (!pMorphIndexSet->SaveMemoryLoadIndex())
			{
					fprintf (stderr, "cannot save memory indices to disk; probably no space left on device\n");
					return false;
			};

			if (!pMorphIndexSet->AddMemoryLoadIndexToMainLoadIndex()) 
			{
				fprintf (stderr, "AddMemoryLoadIndexToMainLoadIndex returned false in CConcIndexator::CreateMorphIndex\n");
				return false;
			}
			OccursCount = 0;
		};
	};
	fprintf(stderr, "%zi/%zi                         \n", CountOfTokens, CountOfTokens);

	fprintf(stderr, "final writing morph index\n");
	if ( !pMorphIndexSet->WriteToFile(true) ) return false;

	fprintf(stderr,"done\n");
	return true;
};


bool	CConcIndexator::StartIndexing()
{
	if (!CStringIndexator::StartIndexing(m_Path)) return false;
	if (!CHitBorders::StartIndexing(m_Path)) return false;
	if (!m_Bibl.Start(m_Path))
	{
		fprintf (stderr, "Cannot start bibl indexator");
		return false;
	};
	return true;
};

bool	CConcIndexator::TerminateIndexing()
{
	if (!CStringIndexator::TerminateIndexing()) return false;
	if (!BordersEndIndexing(m_Path)) return false;
	m_Bibl.ExitWithoutSave();
	return true;

};

bool	CConcIndexator::NormalEndIndexing()
{
	if (!m_Bibl.FinalSaveBibliography())
	{
		fprintf(stderr, "Cannot terminate bibl indexator");
		return false;
	};
	return true;

};

bool	CConcIndexator::IndexOneFile(CGraphmatFile* piGraphmat, string FileName, const char* pFileBuffer, const CDwdsThesaurus* pDwdsThesaurus,  CTokenNo& CorpusEndTokenNo,string& strError)
{
	switch (m_IndexType) {
		case MorphXML_Index:	return IndexMorphXml(FileName, pFileBuffer, CorpusEndTokenNo, strError);
		case DWDS_Index:		return IndexTextOrHtmlFile(piGraphmat, FileName, pFileBuffer, pDwdsThesaurus, CorpusEndTokenNo, strError);
		case Free_Index:		return IndexTable(FileName, pFileBuffer, CorpusEndTokenNo, strError);
		default:  		assert(false);
						return false;
	}
};



//===============================================
//================== CConcIndexatorInvoker =======
//===============================================
CConcIndexatorInvoker::CConcIndexatorInvoker()
{
	m_bStoppedByUser = false;
	m_bStdout = false;
	m_bCorporaProcessing = false;
	m_CurrentSourceFileNo = 0;
	m_SourceFilesNumber = 0;
	// profiling takes 3 percent of working time, if we trust 
	// DevPartner or gprof, that's why by default it should be switched off.
	m_Profiler.m_bTimeSpanHolderEnabled = false;
	m_bOnlyReindexMorphology = false;
	m_bSkipInitialFileChecking = false;
};

void CConcIndexatorInvoker :: SetCurrMessage( string  Message)  const 
{
	m_CurrMessage = Message;
	if (m_bStdout)
	{
		fprintf (stderr, "%s\n", m_CurrMessage.c_str());
	};
};

string CConcIndexatorInvoker::GetTimeStatisticsFileName(string Path) const 
{
	return MakeFName(Path, "_time_statistics");
};

string CConcIndexatorInvoker::GetErrorLogFileName(string Path) const 
{
	return MakeFName(Path, "_error_log");
};



bool ReadSourceFile	(const string& SourceFileName, string& CorpusFileName, TAR* pTar, vector<char>& Buffer, bool& bError)
{
	bError = false;
	if (!pTar)
	{
		Buffer.clear();
		CorpusFileName = SourceFileName;
		ReadVector(SourceFileName,Buffer);
	}
	else
	{
		if (!tar_get_next_file(pTar, CorpusFileName, Buffer, bError))
			return false;

		CorpusFileName = SourceFileName+":"+CorpusFileName;
	};
	size_t len = Buffer.size();
	for (size_t i=0; i<len; i++)
		if (Buffer[i] == 0)
			Buffer[i] = ' ';

	int new_len = Buffer.size();
	for (int  i=new_len-1; i>=0 && isspace((BYTE)Buffer[i]); i--)
		Buffer.erase(Buffer.begin() +i);

	if (IsHtmlFile(SourceFileName) && !Buffer.empty() )
	{
		HTML html;
		string Plain = html.GetTextFromHTMLBuffer(&(Buffer[0]), Buffer.size());
		Buffer.clear();
		Buffer.insert(Buffer.end(), Plain.begin(), Plain.end());
	};

	Buffer.push_back(0);
	return true;
};


void CConcIndexatorInvoker::WriteTimeStatistics	(const CConcIndexator& Indexator, DWORD CorpusEndTokenNo, DWORD MaxTokenCountInOnePeriod) const 
{
	try
	{
		double AllClocksCount = m_Profiler.EndTimer("Indexing");

		FILE * fp  = fopen (GetTimeStatisticsFileName(Indexator.m_Path).c_str(), "w");
		if (!fp)
		{
			fprintf (stderr,"Cannot write time statistics to file!\n");
		}
		else
		{
			fprintf (fp, "%s", m_Profiler.GetStrRepresentation(AllClocksCount).c_str());	
			int AllSeconds = (int)(AllClocksCount/CLOCKS_PER_SEC);
			int u = (AllSeconds > 0) ? (int)((CorpusEndTokenNo)/AllSeconds) : 0;
			fprintf (fp, "Speed (Tokens per second) = %i\n",u);
			fprintf (fp, "MaxTokenCountInOnePeriod = %u (tokens in one subcorpus)\n",MaxTokenCountInOnePeriod);
			fprintf (fp, "Count of subcorpora = %zi\n",Indexator.GetSearchPeriodsCount());
			fprintf (fp, "Count of running tokens  = %u\n",CorpusEndTokenNo);
			
			fclose(fp);
		};
	}
	catch(...)
	{
		SetCurrMessage("An exception occurred while saving time_statistsics files");
	}
};

bool CConcIndexatorInvoker::FinalizeIndex	(CConcIndexator& Indexator, DWORD CorpusEndTokenNo, DWORD MaxTokenCountInOnePeriod) const 
{
	if (!Indexator.SaveCorpusFileList())
	{
		printf ("Cannot save corpus file list %s\n", Indexator.GetFileNameForCorpusFileNames().c_str());
		return false;
	};		

	if (CorpusEndTokenNo >= CIndexItem::GetMaximalNumberOfRunningTokens())
	{
		SetCurrMessage( Format ("Error! Number of running tokens cannot be more than ", CIndexItem::GetMaximalNumberOfRunningTokens()) );
		return false;
	};

	m_Profiler.StartTimer("Final Save to Disc",1);

	if (!Indexator.BordersEndIndexing(Indexator.m_Path)) return false;
	if (!Indexator.LoadHitBorders(Indexator.m_Path)) return false;
	assert (Indexator.GetCorpusEndTokenNo() == CorpusEndTokenNo);
	Indexator.CalculateSearchPeriods(MaxTokenCountInOnePeriod);

	SetCurrMessage(  Format("Tokens Count = %i\n", CorpusEndTokenNo)  );

	if (!Indexator.AddInputLoadIndexToMemoryLoadIndex()) return false;
	if (!Indexator.SaveMemoryLoadIndex())  
	{
		SetCurrMessage(  "Cannot save memory indices to disk; probably no space left on device!");
		return false;
	}
	if (!Indexator.AddMemoryLoadIndexToMainLoadIndex())  return false;;
	if (!Indexator.FinalSaveAllIndices(true)) return false;;
	SetCurrMessage("finished final saving");
	if (!Indexator.NormalEndIndexing()) return false;;
	SetCurrMessage("finished deleting temp. files");
	m_Profiler.EndTimer("Final Save to Disc");

	m_Profiler.StartTimer("CreateMorphIndex",1);
	if (!Indexator.CreateMorphIndex()) 
	{
		SetCurrMessage("Error! Cannot create morph index!");
		return false;;
	}
	m_Profiler.EndTimer("CreateMorphIndex");

	SetCurrMessage("");
	return  true;
};

bool CConcIndexatorInvoker::BuildOnlyMorphIndex	(string ProjectFile) const 
{
	CConcIndexator Indexator;
	if(!Indexator.LoadProject(ProjectFile))
	{
		SetCurrMessage(Format("cannot load index of project %s\n", ProjectFile.c_str()));
		return false;
	};
	if (!Indexator.CreateMorphIndex())
	{
		SetCurrMessage ("cannot index morphology index !\n");
		return false;
	}
	else
	{
		SetCurrMessage ("reindexing was successful!\n");
		return true;
	};
};

void  newhandler( )
{
   fprintf (stderr,"Cannot allocate memory (newhandler is called); terminate the process...\n");
   throw bad_alloc( );
   return;
}

bool CConcIndexatorInvoker::BuildIndex	(string ProjectFile)
{
	set_new_handler (newhandler);
    
    {  // set temp directory 
        char filename[2*_MAX_PATH];
        strcpy(filename,Format("TMP=%s", GetPathByFile(ProjectFile).c_str()).c_str());
        putenv(filename);
        fprintf (stderr, "temp directory: %s\n", getenv("TMP"));
    }

	if (m_bOnlyReindexMorphology)
		return BuildOnlyMorphIndex(ProjectFile);

	const size_t MaxInputIndexSize = 400000;
	CConcIndexator Indexator;

	if (!Indexator.LoadSourceFilesAndOptions(ProjectFile)) 
	{
		SetCurrMessage(Format("cannot load options or source files of project %s\n", ProjectFile.c_str()));
		return false;
	};

	m_SourceFilesNumber = Indexator.GetSourceFilesCount();

	if ( m_SourceFilesNumber == 0 ) 
	{
		SetCurrMessage("No files in the project!");
		return false;
	};

	SetCurrMessage(Format("Files %i\n", m_SourceFilesNumber) );
	if (!m_bSkipInitialFileChecking)
	{
		int FileNo = Indexator.FoundNotExistedFile();
		if (FileNo != -1)
		{
			ErrorMessage(Format("File %s was not found or it is empty, cannot load the project\n", Indexator.GetSourceFile(FileNo).c_str()) );
			return false;
		};
	};

	
	if (!Indexator.DestroyIndex())
	{
		fprintf (stderr,"Error! Cannot destroy index, this corpus is possibly already used!\n");
		ErrorMessage("Error! Cannot destroy index, this corpus is possibly already used");
		return false;
	};
	if (!Indexator.StartIndexing() )
	{
		fprintf (stderr,"Cannot create temp files in the catalog of the corpus!");
		return false;
	};
	

	// a reference to DWDS thesaurus if applicable
	const CDwdsThesaurus* pDwdsThesaurus = 0;
	if ( Indexator.UseDwdsThesaurus() )
		pDwdsThesaurus = LoadDwdsThesaurus();

	

	const DWORD MaxTokenCountInOnePeriod = Indexator.GetMaxTokenCountInOnePeriod();
	SetCurrMessage( Format ("MaxTokenCountInOnePeriod = %i", MaxTokenCountInOnePeriod));

	m_Profiler.ClearTimers();
	m_Profiler.StartTimer("Indexing", 0);

	CGraphmatFile*	piGraphmat = 0;
	bool bResult = false;

	CTokenNo CorpusEndTokenNo = 0;

	TiXmlBase::SetCondenseWhiteSpace(false);
	time_t speed_start_time;
	time (&speed_start_time);
	try
	{
		piGraphmat = new CGraphmatFile;
		if (!piGraphmat)
		{
			SetCurrMessage("Cannot load graphan");
			goto error_label;
		};
		//  first we should init properties, for example, language,
		//  because  loading dictionaries of graphan depends upon the language
		Indexator.InitGraphanProperties(piGraphmat);
		if (!piGraphmat->LoadDicts())
		{
			SetCurrMessage(Format("Graphan::LoadDicts failed! Error: %s",piGraphmat->GetLastError().c_str()));
			goto error_label;
		}
		assert(piGraphmat != NULL);
		
		size_t InputLoadIndexSize = 0;
		size_t MemoryLoadIndexSize = 0;
		vector<char> FileBuffer;
		vector<string> m_ErrorCorpusFiles;
		for (m_CurrentSourceFileNo = 0; m_CurrentSourceFileNo < m_SourceFilesNumber ; m_CurrentSourceFileNo++)
		{
			if (m_bStoppedByUser)
			{
				bResult =  true;
				goto error_label;
			};
			
			m_CurrentSourceFileName = Indexator.GetSourceFile(m_CurrentSourceFileNo);
			fprintf(stderr, "Indexing file `%s'\n", m_CurrentSourceFileName.c_str()); 
			TAR *pTar = 0;
			if (IsTarFile(m_CurrentSourceFileName))
			{
				tar_open(&pTar, m_CurrentSourceFileName.c_str());
				if (!pTar)
				{
					bResult =  false;
					SetCurrMessage( Format("Error! Cannot open %s", m_CurrentSourceFileName.c_str()));
					goto error_label;
				};
			};

			do // reading files in one tar-archive
			{
				DWORD SaveCorpusEndTokenNo = CorpusEndTokenNo;
				if ( InputLoadIndexSize > MaxInputIndexSize)
				{
					time_t speed_curr_time;
					time (&speed_curr_time);
					size_t dur = speed_curr_time-speed_start_time;
					size_t  speed  = SaveCorpusEndTokenNo/dur;
					SetCurrMessage( Format ("File  %s", m_CurrentSourceFileName.c_str()));
					SetCurrMessage( Format ("(%i from  %i)", m_CurrentSourceFileNo+1, m_SourceFilesNumber));
					SetCurrMessage( Format ("Processed tokens = %i;Speed(tokens per sec)=%u", SaveCorpusEndTokenNo, speed));
					m_Profiler.StartTimer("AddInputLoadIndexToMemoryLoadIndex",1);
					if (!Indexator.AddInputLoadIndexToMemoryLoadIndex()) 
					{
			
						SetCurrMessage( Format("Fatal error! Cannot AddInputLoadIndexToMemoryLoadIndex for %s", m_CurrentSourceFileName.c_str()));
						bResult =  false;
						goto error_label;
					};
					m_Profiler.EndTimer("AddInputLoadIndexToMemoryLoadIndex");

					MemoryLoadIndexSize += InputLoadIndexSize;
					InputLoadIndexSize = 0;
				};

				string strError;
				m_Profiler.StartTimer("Indexator.IndexOneFile", 1);
				string CorpusFileName;
				bool bError;
				if (!ReadSourceFile(m_CurrentSourceFileName, CorpusFileName, pTar, FileBuffer, bError))
				{
					assert (pTar);
					tar_close(pTar);
					pTar = 0;
					break;
				};

				if (bError)
				{
					SetCurrMessage( Format("Error! Cannot read %s", m_CurrentSourceFileName.c_str()));
					bResult =  false;
					goto error_label;
				};

				if ( FileBuffer.empty() )
				{
					string err = Format("skipping empty %s", CorpusFileName.c_str());
					SetCurrMessage( err );
					m_ErrorCorpusFiles.push_back(err);	
					continue;
				};

				if (!Indexator.IndexOneFile(piGraphmat, CorpusFileName, &(FileBuffer[0]), pDwdsThesaurus, CorpusEndTokenNo, strError))
				{
					string err = Format ("Error! %s; Indexator.IndexOneFile returned false (file %s)",
						strError.c_str(), 
						CorpusFileName.c_str());
					SetCurrMessage( err );
					if (!Indexator.m_bResumeOnIndexErrors)
					{
						bResult =  false;
						goto error_label;
					}
					else
					{
						m_ErrorCorpusFiles.push_back(err);	
						SetCurrMessage( Format("skipping %s", CorpusFileName.c_str()));
						continue;
					}
				};

				m_Profiler.EndTimer("Indexator.IndexOneFile");
				if (CorpusEndTokenNo == SaveCorpusEndTokenNo)
				{
					string err = Format("skipping empty %s", CorpusFileName.c_str());
					SetCurrMessage( err );
					m_ErrorCorpusFiles.push_back(err);	
					continue;
				};

				if (CorpusEndTokenNo >= CIndexItem::GetMaximalNumberOfRunningTokens())
				{
					bResult =  false;
					SetCurrMessage( Format ("Error! Number of running tokens cannot be more than ", CIndexItem::GetMaximalNumberOfRunningTokens()) );
					goto error_label;
				};


				InputLoadIndexSize += CorpusEndTokenNo-SaveCorpusEndTokenNo;

				if (m_bStoppedByUser)
				{
					bResult =  true;
					goto error_label;
				};
				

				// Setting File address
				Indexator.AddBreakByName(PredefinedFileBreakName, CorpusEndTokenNo);	
				Indexator.m_CorpusFiles.push_back(CorpusFileName);

				if (MemoryLoadIndexSize + InputLoadIndexSize > MaxTokenCountInOnePeriod)
				{
					SetCurrMessage( "Saving index to disk" );
					m_Profiler.StartTimer("AddInputLoadIndexToMemoryLoadIndex",1);
					if (!Indexator.AddInputLoadIndexToMemoryLoadIndex()) 
					{
						SetCurrMessage( Format("Fatal Error! Cannot AddInputLoadIndexToMemoryLoadIndex"));
						goto error_label;
					};
					m_Profiler.EndTimer("AddInputLoadIndexToMemoryLoadIndex");

					m_Profiler.StartTimer("Intermediate Save to Disc",1);

					if (!Indexator.SaveMemoryLoadIndex()) 
					{
						SetCurrMessage("Cannot save indices to disk; probably no space left on device!\n");
						goto error_label;
					};
					if (!Indexator.AddMemoryLoadIndexToMainLoadIndex()) 
					{
						SetCurrMessage("Fatal Error! Indexator.AddMemoryLoadIndexToMainLoadIndex returned false\n");
						goto error_label;
					};
					m_Profiler.EndTimer("Intermediate Save to Disc");
					
					MemoryLoadIndexSize = 0;
					InputLoadIndexSize = 0;


				};

			}	while  (pTar);
		
		}; //for each(m_SourceFilesNumber)

		if (CorpusEndTokenNo == 0)
		{
			SetCurrMessage("Cannot index empty corpus!");
			goto error_label;
		}

		if (!FinalizeIndex(Indexator, CorpusEndTokenNo, MaxTokenCountInOnePeriod))
		{
			SetCurrMessage("Cannot save index to disk, probably no space left!");
			goto error_label;
		};

		remove (GetErrorLogFileName(Indexator.m_Path).c_str());
		if (Indexator.m_bResumeOnIndexErrors && !m_ErrorCorpusFiles.empty())
		{
			FILE* fp = fopen (GetErrorLogFileName(Indexator.m_Path).c_str(), "w");
			if (fp)
			{
				for (size_t i=0; i < m_ErrorCorpusFiles.size(); i++)
					fprintf (fp, "%s\n", m_ErrorCorpusFiles[i].c_str());
				fclose(fp);
			}
			SetCurrMessage(Format("%i error(s) were written into %s", m_ErrorCorpusFiles.size(), GetErrorLogFileName(Indexator.m_Path).c_str()) );
		};
	}
	catch(CExpc e)
	{
		SetCurrMessage(e.m_strCause);
		goto error_label;
	}
	catch(...)
	{
		SetCurrMessage("An exception occurred");
		goto error_label;
	}

	WriteTimeStatistics(Indexator, CorpusEndTokenNo, MaxTokenCountInOnePeriod);

	m_bCorporaProcessing = false;	
	if (piGraphmat) delete piGraphmat;

	if (pDwdsThesaurus)
		FreeDwdsThesaurus(pDwdsThesaurus);
	return true;


error_label:
	if (piGraphmat) delete piGraphmat;
	if (!Indexator.TerminateIndexing())
	{
		SetCurrMessage("Cannot normally terminate indexing!");
	};
	m_bCorporaProcessing = false;
	Indexator.DestroyIndex();
	if (pDwdsThesaurus)
		FreeDwdsThesaurus(pDwdsThesaurus);
	return bResult;
	
};


//==============================================================================
// moved from ad-hoc ConcordQuery.cpp

bool CConcIndexator::LoadProject(string FileName)
{
	if ( !LoadSourceFilesAndOptions(FileName) ) return false;
	if ( !LoadCorpusFiles() ) return false;
	if ( !LoadMaskedFiles() ) return false;
	
	AssertHasPath();
	LoadHitBorders(m_Path, m_bMemoryMap);
	ReadIndicesFromTheDisk();

	if (GetFileBreaks().size() !=  m_CorpusFiles.size()) {
		ErrorMessage (Format("The number of files in %s is not equal to the number of files in the index",FileName.c_str()));
		return false;
	}
	
	if (!m_Bibl.LoadBibl(FileName, GetFileBreaks().size(), m_bMemoryMap)) {
		return false;
	}

	return true;
}

time_t CConcIndexator::UpdateTimestamp(const char *filename)
{
    time_t mtime = FileMTime( filename );
    if (mtime > m_Timestamp)
	m_Timestamp = mtime;
    return m_Timestamp;
}


void SortOccurrences (vector<CTokenNo>& occurrences, size_t SortChunkCount)	
{
	int size = occurrences.size();
	if (	(size < 30)
		||	(SortChunkCount > 1000)
		||	(size/SortChunkCount <  3)
	   ) // if occurrences are very defragmented then use simple sort
		sort(occurrences.begin(), occurrences.end());
	else
	{
		// else use sort based on list unions
		DwordVector Borders;
		Borders.reserve( size );
		assert (size > 0);
		for (size_t i = 0; i< size-1; i++)
			if (occurrences[i] > occurrences[i+1])
				Borders.push_back(i+1);

		Borders.push_back(size);

		SortWithLists(occurrences, Borders);
	};
	
};

//==============================================================================
// anchor and universal query utils

//----------------------------------------------------------------------
bool CConcIndexator::GetAllOccurrences(vector<CTokenNo> &occurrences, size_t searchPeriodNo) const
{
	CTokenNo PeriodBegin = (searchPeriodNo == 0) ? 0 : GetSearchPeriod(searchPeriodNo-1);
	CTokenNo PeriodEnd   = GetSearchPeriod(searchPeriodNo);

	occurrences.clear();
	occurrences.reserve(PeriodEnd-PeriodBegin);
	for (CTokenNo occ=PeriodBegin; occ < PeriodEnd; ++occ) {
		occurrences.push_back(occ);
	}

	return true;
}

//----------------------------------------------------------------------
bool CConcIndexator::GetOccurrencesByPosition(const string& BreakName, int anchor, vector<CTokenNo>& occurrences, size_t searchPeriodNo) const
{
	const CHBreakCollection *bcol = GetBreakCollectionByName(BreakName);
	if (!bcol)
		throw CExpc(errRuntime, "CConcIndexator::GetOccurrencesByPosition(): unknown break collection `%s'", BreakName.c_str());

	CTokenNo PeriodBegin = (searchPeriodNo == 0) ? 0 : GetSearchPeriod(searchPeriodNo-1);
	CTokenNo PeriodEnd   = GetSearchPeriod(searchPeriodNo);
	ddcBreakVector::const_iterator bi = lower_bound(bcol->m_BreakOffsets.begin(), bcol->m_BreakOffsets.end(), PeriodBegin);

	occurrences.clear();
	CTokenNo b0=0, i;
	if (anchor >= 0) {
		//-- non-negative anchor position: count from 0 @ start (left)
		for ( ; bi != bcol->m_BreakOffsets.end() && *bi < PeriodEnd; bi++) {
			//-- break segment from i=b0 .. i<*bi
			i = b0 + anchor;
			if (i < *bi) occurrences.push_back(i);
			b0 = *bi;
		}
		if (searchPeriodNo == GetSearchPeriodsCount()-1 && bi != bcol->m_BreakOffsets.end() && *bi==PeriodEnd && (i=(b0+anchor)) < *bi) {
			//-- hack for final break of final search period
			occurrences.push_back(i);
		}
	}
	else {
		//-- negative anchor position: count from -1 @ end (right)
		anchor *= -1;
		for ( ; bi != bcol->m_BreakOffsets.end() && *bi < PeriodEnd; bi++) {
			//-- break segment from i=b0 .. i<*bi
			i = *bi - anchor;
			if (*bi >= anchor && i >= b0) occurrences.push_back(i);
			b0 = *bi;
		}
		if (searchPeriodNo == GetSearchPeriodsCount()-1 && bi != bcol->m_BreakOffsets.end() && *bi==PeriodEnd && (i=(b0+anchor)) < *bi) {
			//-- hack for final break of final search period
			occurrences.push_back(i);
		}
	}

	return true;
}



//==============================================================================
// data dumping utils

//----------------------------------------------------------------------
void CConcIndexator::DumpBibliography(FILE *f) const
{
    size_t nfiles=m_CorpusFiles.size();
    fputs("[\n",f);
    for (size_t fn=0; fn < nfiles; ++fn) {
	string fs = DumpFileBibliography(fn);
	if (fn != 0) fputs(",\n",f);
	fputs(fs.c_str(),f);
    }
    fputs("\n]\n",f);
}

//----------------------------------------------------------------------
string CConcIndexator::DumpFileBibliography(DWORD FileNo) const
{
    CBibliography B = m_Bibl.GetFullBibliographyOfHit(FileNo);
    string fb = (string("{")
		 + "\"n_\":" + Format("%u",FileNo)
		 +",\"file_\":" + jsonStr(m_CorpusFiles[FileNo],m_Utf8)
		 +",\"masked_\":" + (m_MaskedFiles.find(FileNo) == m_MaskedFiles.end() ? "0" : "1")
		 + ",\"scan_\":" + jsonStr(B.m_ScanBibl, m_Utf8)
		 + ",\"orig_\":" + jsonStr(B.m_OrigBibl, m_Utf8)
		 + ",\"date_\":" + jsonStr(B.m_DateStr, m_Utf8)
		 + ",\"page_\":" + (B.m_StartPageInfo==UnknownPageNumber ? "null" : Format("%u",B.m_StartPageInfo))
		 + "," + m_Bibl.GetFreeHeaderBiblAttributesJson(FileNo, m_Utf8)
		 + "}");
    return fb;
}

//----------------------------------------------------------------------
void CConcIndexator::DumpFileIndexJson(DWORD FileNo, FILE *f) const
{
	if (f==NULL) f=stdout;

	//-- dump: token range
	CTokenNo tok_min = FileNo==0 ? 0 : GetFileBreaks()[FileNo-1];
	CTokenNo tok_max = GetFileBreaks()[FileNo];
	fprintf(f, "{\n\t\"tokids\":{\"begin\":%d, \"end\":%d},\n", tok_min,tok_max);


	//-- dump: metadata
	fputs("\t\"meta\":",f);
	string fs = DumpFileBibliography(FileNo);
	fwrite(fs.data(), 1, fs.size(), f);
	fputs(",\n", f);

	//-- dump: free breaks
	fputs("\t\"breaks\":\[\n", f);
	for (vector<CBreakCollection>::const_iterator brki=m_Breaks.begin(); brki!=m_Breaks.end(); brki++) {
		if (brki != m_Breaks.begin()) fputs(",\n", f);
		fprintf(f, "\t\t\{\"shortname\":%s,\"longname\":%s,\"offsets\":\[\n", jsonStr(brki->m_ShortName,m_Utf8).c_str(), jsonStr(brki->m_LongName,m_Utf8).c_str());
		ddcBreakVector::const_iterator off0 = lower_bound(brki->m_BreakOffsets.begin(), brki->m_BreakOffsets.end(), tok_min);
		for (ddcBreakVector::const_iterator offi=off0; offi != brki->m_BreakOffsets.end() && *offi < tok_max; offi++) {
			if (offi != off0) fputc(',',f);
			fprintf(f,"%u", *offi);
		}
		fputs("\n\t\t]}",f);
	}
	fputs("\n\t],\n", f);

	//-- dump: page-breaks
	fputs("\t\"pages\":\{\n", f);
	ddcVecFile<CPageNumber>::const_iterator pb0 = GetTokenPageBreak(tok_min);
	for (ddcVecFile<CPageNumber>::const_iterator pbi = pb0; pbi != m_PageBreaks.end() && pbi->m_StartTokenNo < tok_max; pbi++) {
			if (pbi != pb0) fputc(',',f);
			fprintf(f,"\"%u\":%u", pbi->m_StartTokenNo, pbi->m_PageNumber);
	}
	fputs("\n\t},\n", f);


	//-- construct: tokens
	vector<COutputToken> tmptoks;
	tmptoks.reserve(tok_max-tok_min);

	fputs("\t\"indices\":\[\n", f);
	for (vector<CStringIndexSet*>::const_iterator ixi=m_Indices.begin(); ixi!=m_Indices.end(); ixi++) {
		if (ixi != m_Indices.begin()) fputs(",\n",f);
		fprintf(f, "\t\t{\"shortname\":%s,\"longname\":%s,\"values\":[\n", jsonStr((*ixi)->m_ShortName,m_Utf8).c_str(), jsonStr((*ixi)->m_Name,m_Utf8).c_str());
		if ((*ixi)->GetTokensFromStorage(tok_min, tok_max, tmptoks)) {
			for (vector<COutputToken>::const_iterator tmpi=tmptoks.begin(); tmpi!=tmptoks.end(); tmpi++) {
				if (tmpi != tmptoks.begin()) fputc(',',f);
				fputs(jsonStr(tmpi->m_TokenStr,m_Utf8).c_str(), f);
			}
			fputc('\n',f);
		}
		fputs("\t\t]}", f);
		tmptoks.clear();
	}
	fputs("\n\t]\n}\n", f);

	return;
}

//----------------------------------------------------------------------
void CConcIndexator::DumpFileIndexTabs(DWORD FileNo, FILE *f) const
{
	if (f==NULL) f=stdout;

	//-- dump: token range
	const char *cmt = "%%$DDC";
	CTokenNo tok_min = FileNo==0 ? 0 : GetFileBreaks()[FileNo-1];
	CTokenNo tok_max = GetFileBreaks()[FileNo];
	fprintf(f, "%s:tokid.begin=%u\n", cmt, (uint)tok_min);
	fprintf(f, "%s:tokid.end=%u\n",   cmt, (uint)tok_max);

	//-- dump: metadata: built-in
	CBibliography B = m_Bibl.GetFullBibliographyOfHit(FileNo);
	fprintf(f, "%s:meta.n_=%u\n", cmt, (uint)FileNo);
	fprintf(f, "%s:meta.file_=%s\n", cmt, jsonStr(m_CorpusFiles[FileNo],m_Utf8,false).c_str());
	fprintf(f, "%s:meta.masked_=%d\n", cmt, (m_MaskedFiles.find(FileNo) == m_MaskedFiles.end() ? 0 : 1));
	fprintf(f, "%s:meta.scan_=%s\n", cmt, jsonStr(B.m_ScanBibl,m_Utf8,false).c_str());
	fprintf(f, "%s:meta.orig_=%s\n", cmt, jsonStr(B.m_OrigBibl,m_Utf8,false).c_str());
	fprintf(f, "%s:meta.date_=%s\n", cmt, jsonStr(B.m_DateStr,m_Utf8,false).c_str());
	fprintf(f, "%s:meta.page_=%ld\n", cmt, (B.m_StartPageInfo==UnknownPageNumber ? -1L : (long int)B.m_StartPageInfo));
	fputs(m_Bibl.GetFreeHeaderBiblAttributesTabsDump(FileNo,m_Utf8).c_str(), f);

	//-- intialize: page-breaks
	ddcVecFile<CPageNumber>::const_iterator pb = GetTokenPageBreak(tok_min);

	//-- initialize: free-breaks
	vector<size_t> breaknos(m_Breaks.size(), 0);
	vector<size_t> breakstart(m_Breaks.size(), 0);
	size_t defaultBreakId = 0;
	for (size_t brkid=0; brkid < m_Breaks.size(); ++brkid) {
		const CBreakCollection &breaks = m_Breaks[brkid];
		breaknos[brkid]   = lower_bound(breaks.m_BreakOffsets.begin(), breaks.m_BreakOffsets.end(), tok_min) - breaks.m_BreakOffsets.begin();
		breakstart[brkid] = breaknos[brkid]==0 ? 0 : breaks.m_BreakOffsets[breaknos[brkid]-1];
		if (breaks.m_ShortName==m_DefaultBreakName || breaks.m_LongName==m_DefaultBreakName)
			defaultBreakId = brkid;
	}

	//-- construct tokens & dump index attributes
	vector<vector<COutputToken> > tokattrs;
	tokattrs.resize(m_Indices.size());
	size_t ixno, tixno;
	for (ixno=0, tixno=0; ixno < m_Indices.size(); ++ixno) {
		const CStringIndexSet *ix = m_Indices[ixno];
		if (!ix->m_bUseItemStorage) continue;
		fprintf(f, "%s:index[%zi]=%s %s\n", cmt, tixno, jsonStr(ix->m_Name,m_Utf8,false).c_str(), jsonStr(ix->m_ShortName,m_Utf8,false).c_str());
		tokattrs[tixno].reserve(tok_max-tok_min);
		ix->GetTokensFromStorage(tok_min, tok_max, tokattrs[tixno]);
		++tixno;
	}
	tokattrs.resize(tixno);

	//-- iterate over tokens
	for (CTokenNo tokid=tok_min; tokid!=tok_max; ++tokid) {
		//-- check for page-breaks
		for ( ; pb != m_PageBreaks.end() && pb->m_StartTokenNo <= tokid; ++pb) {
			fprintf(f, "%s:PAGE=%u\n", cmt, (uint)pb->m_PageNumber);
		}

		//-- check for free-breaks
		for (size_t brkid=0; brkid < m_Breaks.size(); ++brkid) {
			const CBreakCollection &breaks = m_Breaks[brkid];
			for ( ; breakstart[brkid] <= tokid && breaknos[brkid] < breaks.m_BreakOffsets.size(); ++breaknos[brkid]) {
				size_t breakno = breaknos[brkid];
				if (brkid==defaultBreakId && tokid > tok_min) fputc('\n',f);
				fprintf(f, "%s:BREAK.%s[%zu]=%u\n", cmt, breaks.m_ShortName.c_str(), breakno, (uint)(breaks.m_BreakOffsets[breakno]));
				breakstart[brkid] = breaks.m_BreakOffsets[breaknos[brkid]];
			}
		}

		//-- dump current token
		for (size_t tixno=0; tixno < tokattrs.size(); ++tixno) {
			if (tixno!=0) fputc('\t',f);
			fputs(tokattrs[tixno][tokid-tok_min].m_TokenStr.c_str(), f);
		}
		fputc('\n', f);
	}
	fputc('\n', f);

	return;
}

//----------------------------------------------------------------------
void CConcIndexator::DumpIndex(const char *dirname, CIndexDumpFormat fmt) const
{
	const char *file_ext = "";
	if (fmt==idfJson) {
		file_ext = "json";
	} else if (fmt==idfTabs) {
		file_ext = "tabs";
	} else {
		throw CExpc(errRuntime, "CConcIndexator::DumpIndex(): index dump-format %u", (uint)fmt);
	}
	size_t nfiles=m_CorpusFiles.size();
	for (size_t fn=0; fn < nfiles; ++fn) {
		string dumpfile = Format("%s/%d.%s", dirname, fn, file_ext);
		FILE  *dumpfh   = fopen(dumpfile.c_str(), "wb");
		if (!dumpfh)
			throw CExpc(errRuntime, "Error: open failed for dump file '%s': %s", dumpfile.c_str(), StrError(errno));
		fprintf(stderr, "dumping %s ~ %s\n", dumpfile.c_str(), m_CorpusFiles[fn].c_str());
		switch (fmt) {
		case idfJson: DumpFileIndexJson(fn, dumpfh); break;
		case idfTabs: DumpFileIndexTabs(fn, dumpfh); break;
		default: break;
		}
		fclose(dumpfh);
	}
}

//----------------------------------------------------------------------
void CConcIndexator::RegisterIndicesToShow(const string& IndexListStr)
{
	StringTokenizer tok(IndexListStr.c_str(), " \t\r\n,;");
	m_IndicesToShow.clear();

	while (tok()) {
		string s    = tok.val();
		size_t ipos = (size_t)-1;
		if (s.empty()) continue;

		CStringIndexSet *idx = GetIndexByAlias(s);
		if (idx != NULL) {
			//-- known alias: convert to position
			for (size_t i=0; i < m_Indices.size(); ++i) {
				if (m_Indices[i] == idx) {
					ipos = i;
					break;
				}
			}
			assert(ipos >= 0);
			assert(ipos < m_Indices.size());
		}
		else if (s.find_first_not_of("+-0123456789") == string::npos) {
			//-- decimal integer: convert to size_t
			ipos = strtoul(s.c_str(),NULL,0);
			if (ipos < 1)
				throw CExpc("minimum positional index value for IndicesToShow is 1 (one)");
			else if (ipos > m_Indices.size()) 
				throw CExpc(Format("positional index `%zi' in IndicesToShow out of bounds (max=%zi)", ipos, m_Indices.size()));
			--ipos; //-- convert to zero-based indces
		}
		else {
			//-- unknown: oops
			throw CExpc(Format("unknown index label `%s' in IndicesToShow", s.c_str()));
		}

		m_IndicesToShow.push_back(ipos);
	}
	
	//-- sanity check: always show at least 1 index (default=initial index)
	if (m_IndicesToShow.empty())
		m_IndicesToShow.push_back(0);

	//-- global sanity checks
	for (size_t i=0; i < m_IndicesToShow.size(); ++i) {
		if (!m_Indices[m_IndicesToShow[i]]->m_bUseItemStorage)
			throw CExpc("index #%zi (%s) in IndicesToShow has no storage class", i, m_Indices[m_IndicesToShow[i]]->m_Name.c_str());
	}
}

//----------------------------------------------------------------------
string CConcIndexator::GetIndicesToShowStr(bool Positional) const
{
	if (m_IndicesToShow.size() < 1 || (m_IndicesToShow.size() == 1 && m_IndicesToShow[0] == 0))
		return string("");
	string Result("IndicesToShow");
	for (size_t i=0; i < m_IndicesToShow.size(); ++i) {
		Result.push_back(' ');
		if (Positional) {
			Result += Format("%zi", i);
		} else {
			CStringIndexSet* idx = m_Indices[m_IndicesToShow[i]];
			Result.append(idx->m_Name);
		}
	}
	return Result;
}


// Local Variables:
// mode: c++
// c-basic-offset: 8
// End:

