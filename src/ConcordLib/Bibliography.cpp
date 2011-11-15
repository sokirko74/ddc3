/*-*- Mode: C++; c-basic-offset: 8; -*-*/
//  Copyright 2011 by Bryan Jurish
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
#include "Bibliography.h"
#include "../tinyxml/xpath_static.h"
#include "../common/bserialize.h"
#include "../common/ddcString.h"

const char IntegerTypeStr[] = "integer";
const char StringTypeStr[] = "string";
const size_t MaxBiblStringLen = 20000;

string& DeleteEoln (string& s)
{
	for (size_t i =0; i <s.length(); i++)
	if (		(s[i] == '\n') 
			||	(s[i] == '\r') 
		)
		s[i] = ' ';

	return s;
};


bool  CheckXPath (string XPath, string& ErrStr )
{
	ErrStr = "";
	if (XPath.empty() ) 
	{
		ErrStr = "Error! Empty  XPath!";
		return false;
	};
	if (XPath[0] != '/' ) 
	{
		ErrStr = "Error! XPath should start with '/' !";
		return false;
	};
	if (XPath[XPath.length() - 1] == '/' ) 
	{
		ErrStr = "Error! XPath should not terminate with '/' !";
		return false;
	};
	return true;
};


string ReadXmlField (const TiXmlDocument& pDoc, string XPath)
{
	string ErrStr;
	TinyXPath::xpath_processor xp_proc (pDoc.RootElement(), XPath.c_str());	
	TinyXPath::expression_result er_res = xp_proc.er_compute_xpath ();
	if (xp_proc.e_error != TinyXPath::xpath_processor::e_no_error)
		// not present in this dociment 
		return "";
	
	TinyXPath::node_set* pSet = er_res.nsp_get_node_set();
	string Result;
	size_t Count = pSet->u_get_nb_node_in_set();
	for (size_t u_node= 0; u_node < Count; u_node++)
	{
		string s;
		const TiXmlBase* pBase = pSet->XBp_get_base_in_set(u_node);
		if (pSet->o_is_attrib(u_node)  )
		{
			const TiXmlAttribute * node =  pSet->XAp_get_attribute_in_set(u_node);
			s = node->Value();
		}
		else
		{
			const TiXmlNode * node =  pSet->XNp_get_node_in_set(u_node);
			for (TiXmlNode* child = node->FirstChild();  child;  child = child->NextSibling())
			if (child -> Type () == TiXmlNode::TEXT)
			{
				string  q = child->Value();
				Trim(q);
				s += q;
			};
		}
		Result += s;
		if (u_node+1 < Count) 
				Result += ":";
	}
	
	DeleteEoln(Result);

	return Result;
};


CBibliography::CBibliography()
{
	m_StartPageInfo = UnknownPageNumber;
}
void CBibliography::CleanBibliography()
{
	m_OrigBibl = "";
	m_ScanBibl = "";
	m_DateStr = "";
	m_StartPageInfo = UnknownPageNumber;
	m_BiblAttribs.clear();
};


void CBibliography::ReadFromString(const string&  S)
{
	CleanBibliography();

	size_t start = S.find("<orig>");
	size_t end = S.find("</orig>");
	if ( (start != -1) && (end != -1))
	{
		m_OrigBibl = S.substr(start + 6, end - start - 6);
		Trim(m_OrigBibl);
	};

	start = S.find("<scan>");
	end = S.find("</scan>");
	if ( (start != -1) && (end != -1))
	{
		m_ScanBibl = S.substr(start + 6, end - start - 6);
		Trim(m_ScanBibl);
	};
	
	start = S.find("<date>");
	end = S.find("</date>");
	if ( (start != -1) && (end != -1))
	{
		m_DateStr = S.substr(start + 6, end - start - 6);
		Trim(m_DateStr);
	};


};

string CBibliography::WriteToString() const
{
	string Result;
	if (!m_OrigBibl.empty()) Result += "<orig> "+m_OrigBibl+"</orig>\n";
	if (!m_DateStr.empty()) Result += "<date> "+m_DateStr+"</date>\n";
	if (!m_ScanBibl.empty()) Result += "<scan> "+m_ScanBibl+"</scan>\n";
	return Result;
};

#define _MAKEWORD(a, b)      ((WORD)(((BYTE)((a) & 0xff)) | ((WORD)((BYTE)((b) & 0xff))) << 8))
#define _MAKELONG(a, b)      ((long)(((WORD)((a) & 0xffff)) | ((DWORD)((WORD)((b) & 0xffff))) << 16))

bool CBibliography::ConvertDateToInt(int& Result) const 
{
	if (m_DateStr.empty()) 
		return false;
	int  year, month, day;
	StringTokenizer tok(m_DateStr.c_str(),"-");
	if (!tok()) return false;
	year = atoi(tok.val());
	if (tok())
	{
		month = atoi(tok.val());
		if (month >  12) return false;

		if (!tok()) return false;
		day = atoi(tok.val());
		if (day >  31) return false;
	}
	else
	{
		month = 1;
		day = 1;
	};
	Result = _MAKELONG (_MAKEWORD(day,month), year);
	if (year > 30000) return false;
	return true;
};

//=============================================



//=============================================

CConcXml::CFreeBiblIndex::CFreeBiblIndex()
{

}
CConcXml::CFreeBiblIndex::~CFreeBiblIndex()
{
};
void	CConcXml::CFreeBiblIndex::clear()
{
	m_bShowInHeader = false;
	m_ValuesForEachFile.clear();
};

string CConcXml::CFreeBiblIndex::GetStringValue(DWORD FileNo ) const 
{
	return Format("%i", (int)m_ValuesForEachFile[FileNo]);
};

int CConcXml::CFreeBiblIndex::GetIntegerValue(DWORD FileNo ) const 
{
	return m_ValuesForEachFile[FileNo];
};



bool CConcXml::CFreeBiblIndex::ReadFromDisk (string Path,  DWORD FileBreaksSize) 
{
	ReadVector(GetIndexFileName(Path), m_ValuesForEachFile);

	if (m_ValuesForEachFile.size() != FileBreaksSize)
	{
		ErrorMessage (Format("The number of corpus files should be equal to the number of bibliographical records (index name = %s)",m_Name.c_str()));
		return false;
	};

	return true;
}

string  CConcXml::CFreeBiblIndex::GetDescriptionStr () const
{
	return Format ("%s %s %i %s %s", 
			FreeBiblAttribOptionFieldName.c_str(),  GetTypeStr().c_str(),
			m_bShowInHeader ? 1:0,  m_Name.c_str(),  m_Xpath.c_str());
};

string  CConcXml::CFreeBiblIndex::GetIndexFileName (string Path) const
{
	return MakeFName(Path, string("_bibl_")+m_Name+"_integers");
};

void CConcXml::CFreeBiblIndex::CreateUnion (string Path, const CFreeBiblIndex* pIndex1, const CFreeBiblIndex* pIndex2) 
{
	m_ValuesForEachFile = pIndex1->m_ValuesForEachFile;
	m_ValuesForEachFile.insert(m_ValuesForEachFile.end(),  pIndex2->m_ValuesForEachFile.begin(), pIndex2->m_ValuesForEachFile.end());
	WriteVector(GetIndexFileName(Path), m_ValuesForEachFile);
};

bool CConcXml::CFreeBiblIndex::GetValueForDDCFilter (const RML_RE::Options &RegexOpts, string Value, CDDCFilterWithBounds& Filter, bool isRegex) const
{
	Filter.m_LevelStart = atoi(Value.c_str());
	Filter.m_LevelEnd = Filter.m_LevelStart+1;
	return true;
};

bool CConcXml::CFreeBiblIndex::RegisterBiblStringItemId(const string& ValueStr)
{
	int u = ValueStr.empty() ? 0 : atoi(ValueStr.c_str());
	m_ValuesForEachFile.push_back(u);
	return true;
};


bool CConcXml::CFreeBiblIndex::DeleteBiblFiles (string Path) const 
{
	return		remove(GetIndexFileName(Path).c_str()) == 0;
};


bool CConcXml::CFreeBiblIndex::ConvertAndSaveToDiskAfterIndexing (string Path) 
{
	return WriteVector(GetIndexFileName(Path), m_ValuesForEachFile);
};

string CConcXml::CFreeBiblIndex::GetTypeStr() const
{
	return IntegerTypeStr;
};




//=============================================

CConcXml::CFreeBiblStringIndex::CFreeBiblStringIndex()
{

}
CConcXml::CFreeBiblStringIndex::~CFreeBiblStringIndex()
{
};

void	CConcXml::CFreeBiblStringIndex::clear()
{
	CFreeBiblIndex::clear();
	m_BuildStringItems.clear();
	m_Values.clear();
};

string CConcXml::CFreeBiblStringIndex::GetStringValue(DWORD FileNo ) const 
{
	return m_Values[m_ValuesForEachFile[FileNo]];
};

string  CConcXml::CFreeBiblStringIndex::GetStringFileName (string Path) const 
{
	return MakeFName(Path, string("_bibl_")+m_Name+"_strings");
};

bool CConcXml::CFreeBiblStringIndex::DeleteBiblFiles (string Path) const
{
	return		remove(GetStringFileName(Path).c_str()) == 0
			&&	CFreeBiblIndex::DeleteBiblFiles(Path);
};

bool CConcXml::CFreeBiblStringIndex::ReadBiblStringItems (vector<string>&  Set, string FileName) const
{
	Set.clear();

	FILE * fp = fopen(FileName.c_str(), "rb");
	if (!fp) 
	{
		fprintf(stderr, "Warning:Cannot read file %s\n", FileName.c_str());
		return false;
	};
	char buffer[MaxBiblStringLen+1];
	while (fgets(buffer, MaxBiblStringLen, fp))
	{
		string q = buffer;
		Trim(q);
		Set.push_back(q);
	};

	fprintf(stderr, "Read  %i items  from %s\n", Set.size(), FileName.c_str());
	fclose (fp);
	return true;
};

bool CConcXml::CFreeBiblStringIndex::WriteBiblStringItems (const vector<string>&  Set, string FileName) const
{
	FILE * fp = fopen(FileName.c_str(), "wb");
	if (!fp) 
	{
		fprintf(stderr, "Warning:Cannot write file %s\n", FileName.c_str());
		return false;
	};
	for (size_t i=0; i< Set.size(); i++)
		fprintf(fp, "%s\n",Set[i].c_str());

	fclose (fp);
	return true;
};

string CConcXml::CFreeBiblStringIndex::GetTypeStr() const
{
	return StringTypeStr;
};



bool CConcXml::CFreeBiblStringIndex::ReadFromDisk (string Path, DWORD FileBreaksSize) 
{
	if (!ReadBiblStringItems(m_Values, GetStringFileName(Path)))
			return false;
	return CFreeBiblIndex::ReadFromDisk(Path, FileBreaksSize);
}

void CConcXml::CFreeBiblStringIndex::CreateUnionOfBiblStrings (const vector<string>&  _X1, const vector<string>&  _X2,   
						  vector<DWORD>& Transfer1, vector<DWORD>& Transfer2)
{
	m_Values.resize(_X1.size()  + _X2.size());

	vector<string>::iterator it = set_union(_X1.begin(),_X1.end(), _X2.begin(),_X2.end(), m_Values.begin());
	m_Values.resize(it - m_Values.begin());

	Transfer1.clear();
	for (size_t i=0; i< _X1.size(); i++)
		Transfer1.push_back( lower_bound(m_Values.begin(), m_Values.end(), _X1[i]) - m_Values.begin() );

	Transfer2.clear();
	for (size_t i=0; i< _X2.size(); i++)
		Transfer2.push_back( lower_bound(m_Values.begin(), m_Values.end(), _X2[i]) - m_Values.begin() );
};

void CConcXml::CFreeBiblStringIndex::CreateUnion (string Path, const CFreeBiblIndex* pIndex1, const CFreeBiblIndex* pIndex2 ) 
{
	const CFreeBiblStringIndex& I1 = *(const CFreeBiblStringIndex*)pIndex1;
	const CFreeBiblStringIndex& I2 = *(const CFreeBiblStringIndex*)pIndex2;
	m_ValuesForEachFile.clear();
	m_Values.clear();
	vector<DWORD> Old2New1, Old2New2;
	CreateUnionOfBiblStrings(I1.m_Values, I2.m_Values, Old2New1, Old2New2);

	size_t Count = I1.m_ValuesForEachFile.size();
	size_t i = 0;
	for (; i < Count; i++)
		m_ValuesForEachFile.push_back( Old2New1[I1.m_ValuesForEachFile[i]] );

	Count += I2.m_ValuesForEachFile.size();
	for (; i < Count; i++)
		m_ValuesForEachFile.push_back( Old2New2[I2.m_ValuesForEachFile[i-I2.m_ValuesForEachFile.size()]] );

	WriteBiblStringItems(m_Values, GetStringFileName(Path));
	CFreeBiblIndex::ConvertAndSaveToDiskAfterIndexing(Path);
};



bool CConcXml::CFreeBiblStringIndex::GetValueForDDCFilter (const RML_RE::Options &RegexOpts, string Value, CDDCFilterWithBounds& Filter, bool isRegex) const
{
	if (Value.empty()) return true;
	if (!isRegex && Value[0] == '*')
		return GetValueForDDCFilter(RegexOpts, string(".")+escapeRegex(Value), Filter, true);

	if (isRegex) {
		Filter.m_bRegExp = true;
        	RML_RE re(Value, RegexOpts);
		size_t Count = m_Values.size();
		for( size_t i=0; i<Count; i++ ) {
			if(  re.PartialMatch(m_Values[i])  ) 
				Filter.m_SatisfiedValues.insert(i);
		}
		if (Filter.m_SatisfiedValues.empty()) {
			Filter.m_LevelStart = 0;
			Filter.m_LevelEnd = 0;
		}
		else {
			Filter.m_LevelStart = *Filter.m_SatisfiedValues.begin();
			set<int>::const_iterator it = Filter.m_SatisfiedValues.end();
			it--;
			Filter.m_LevelEnd = (*it)+1;
		};
		return true;
	}
	else if (Value[Value.length() -1 ] == '*') {
		Value.erase(Value.end() - 1);
		vector<string>::const_iterator it =  lower_bound(m_Values.begin(), m_Values.end(), Value);
		Filter.m_LevelStart = it-m_Values.begin();
		while (	(it != m_Values.end()) && (it->substr(0, Value.length()) == Value))
			it++;
		Filter.m_LevelEnd = it-m_Values.begin();
	}
	else {
		vector<string>::const_iterator it =  lower_bound(m_Values.begin(), m_Values.end(), Value);
		if (		(it == m_Values.end())
				||	(*it  != Value)
			)
		{
			Filter.m_LevelStart = 0;
			Filter.m_LevelEnd = 0;
		}
		else
		{
			Filter.m_LevelStart = it-m_Values.begin();
			it++;
			Filter.m_LevelEnd = it-m_Values.begin();
		};
	};
	return true;
};

bool CConcXml::CFreeBiblStringIndex::RegisterBiblStringItemId(const string& ValueStr)
{
	if (m_BuildStringItems.size() == 0xffff)
	{
		fprintf(stderr, "Too many %s. Cannot be more than 65535\n", m_Name.c_str());
		return false;
	};
    if (ValueStr.length() > MaxBiblStringLen)
    {
		fprintf(stderr, "Bibl item in index %s is too long (%i chars). Cannot be more than %i chars\n", m_Name.c_str(), ValueStr.length(), MaxBiblStringLen);
		return false;
    }

	CStringItem I;
	I.m_BiblString = ValueStr;
	for (size_t i=0; i< I.m_BiblString.length(); i++)  // delete all \x1, since it is used as a delimeter
		if ((BYTE)I.m_BiblString[i] == 1) 
			I.m_BiblString[i] = ' ';

	Trim(I.m_BiblString);

	list<CStringItem>::iterator it = lower_bound(m_BuildStringItems.begin(), m_BuildStringItems.end(), I);
	if (		(it == m_BuildStringItems.end())
			||	!(*it == I)
		)
	{
		I.m_BiblId = m_BuildStringItems.size();
		m_BuildStringItems.insert(it, I);
	}
	else
		I.m_BiblId = it->m_BiblId;

	m_ValuesForEachFile.push_back(I.m_BiblId);

	return true;
};


bool CConcXml::CFreeBiblStringIndex::ConvertAndSaveToDiskAfterIndexing (string m_Path)
{
	fprintf (stderr,"sorting and saving index for %s\n", m_Name.c_str() );
	{ // converting
		vector<DWORD> Old(m_BuildStringItems.size());
		{
			list<CStringItem>::const_iterator it = m_BuildStringItems.begin();
			for (size_t i=0; i < Old.size(); i++, it++)
			{
				Old[i] = it->m_BiblId;
			}
		}
		vector<DWORD> Old2New;
		Old2New.resize(Old.size());

		for (size_t i=0; i < Old.size(); i++)
			Old2New[Old[i]] = i;

		for (size_t i=0; i< m_ValuesForEachFile.size(); i++)
			m_ValuesForEachFile[i] =  Old2New[m_ValuesForEachFile[i]];
	}

	{	// saving
		string StringFileName =  GetStringFileName(m_Path);
		FILE * fp = fopen(StringFileName.c_str(), "wb");
		if (!fp) 
		{
			fprintf(stderr, "Cannot write to %s\n", StringFileName.c_str());
			return false;
		};
		const list<CStringItem>&  Set = m_BuildStringItems;
		fprintf(stderr, "Writing %i items  to %s\n", Set.size(), StringFileName.c_str());
		
		for (list<CStringItem>::const_iterator it = Set.begin(); it != Set.end(); it++)
		{
			const string& I = it->m_BiblString;
			if (fprintf (fp,"%s\n",I.c_str()) < 0)
			{
				fclose (fp);
				fprintf(stderr, "Cannot add new item  to %s\n", StringFileName.c_str());
				return false;
			};;
		};
		fclose (fp);

		CFreeBiblIndex::ConvertAndSaveToDiskAfterIndexing(m_Path);
	};

	return true;
};


//=============================================
CConcXml::CConcXml()
{
	m_BiblBodyFile = 0;
};

CConcXml::~CConcXml()
{
	if (m_BiblBodyFile) 
	{
		fclose(m_BiblBodyFile);
	}
	FreeBiblIndices();
};

void CConcXml::FreeBiblIndices()
{
	for (FreeBiblStringMap::iterator it = m_FreeBiblIndices.begin(); it != m_FreeBiblIndices.end(); it++)
	{
		delete it->second;
	};
	m_FreeBiblIndices.clear();
};




void CConcXml::SetPath(string ProjectFileName)
{
	m_Path = ProjectFileName;
};

bool CConcXml::Start(string ProjectFileName)
{
	SetPath(ProjectFileName);

	if (m_BiblBodyFile) fclose(m_BiblBodyFile);
	m_BiblBodyFileSize = 0;
	m_EndOffsetsInBiblFile.clear();
	m_Dates.clear();

	for (FreeBiblStringMap::iterator it = m_FreeBiblIndices.begin(); it != m_FreeBiblIndices.end(); it++)
	{	
		it->second->clear();
	};
	
	
	m_BiblBodyFile = fopen (GetBiblFileName().c_str(), "wb");
	if (!m_BiblBodyFile )
	{
		fprintf (stderr, "cannot write to  file  %s\n", GetBiblFileName().c_str());
		return false;
	};
	
	return true;
};


bool CConcXml::AddIndexItem(const CBibliography& Bibliography)
{
	{
		string BiblStr =  Bibliography.WriteToString();
		fprintf (m_BiblBodyFile, "%s", BiblStr.c_str());
		m_BiblBodyFileSize += BiblStr.length();
	}

	

	// saving free bibliographical attributes
	{
		int BiblAttribNo = 0;
		assert (Bibliography.m_BiblAttribs.size()  == m_FreeBiblIndices.size() );
		for (FreeBiblStringMap::iterator it = m_FreeBiblIndices.begin(); it != m_FreeBiblIndices.end(); it++, BiblAttribNo++)
			if (!it->second->RegisterBiblStringItemId(Bibliography.m_BiblAttribs[BiblAttribNo]))
					return false;
	}

	m_EndOffsetsInBiblFile.push_back(m_BiblBodyFileSize);

	{
		int Date;
		Bibliography.ConvertDateToInt(Date);
		m_Dates.push_back(Date);
	};

	

	return true;
};

void CConcXml::DeleteFiles()
{
	remove (GetBiblFileName().c_str());
	remove (GetBiblIndexFileName().c_str());
	remove (GetBiblDateIndexFileName().c_str());
	for (FreeBiblStringMap::iterator it = m_FreeBiblIndices.begin(); it != m_FreeBiblIndices.end(); it++)
	{
		it->second->DeleteBiblFiles(m_Path);
	};

};


bool CConcXml::RegisterTextAreas(string fields, string& ErrorStr)
{
	m_TextAreas.clear();
	StringTokenizer lines(fields.c_str(), "\n\r");
	while (lines())
	{
		string OneField = lines.val();
		Trim(OneField);
		if(OneField.empty()) continue;
		StringTokenizer tok(OneField.c_str(), " \t");
		if (!tok()) 		
		{
			ErrorStr = "Error! Bad syntax in free bibliographical attribute description";
			return false;
		};
		string FieldName = tok.val();
		RmlMakeLower(FieldName, morphEnglish);
		if (FieldName != TextAreaOptionFieldName) 		
		{
			ErrorStr = "Error! Bad syntax in text area attribute description";
			return false;
		};

		if (!tok()) 
		{
			ErrorStr = "Error! Bad syntax in text area attribute description";
			return false;
		};
		CTextArea TextArea;
		TextArea.m_TextAreaName = tok.val();
		// reading xpath
		if (!tok()) 
		{
			ErrorStr = "Error! Bad syntax in text area attribute description";
			return false;
		};
		TextArea.m_Xpath = tok.val();
		if (!CheckXPath(TextArea.m_Xpath, ErrorStr))
			return false;

		
		m_TextAreas.push_back(TextArea);
	}


	return true;
}

bool CConcXml::RegisterFreeBiblAttributes(string fields, string& ErrorStr)
{
	FreeBiblIndices();
	m_OrigXPath = "";
	m_DateXPath = "";
	m_ScanXPath = "";
	m_StartPageXPath = "";
	


	StringTokenizer lines(fields.c_str(), "\n\r");
	while (lines())
	{
		string OneField = lines.val();
		Trim(OneField);
		if(OneField.empty()) continue;
		StringTokenizer tok(OneField.c_str(), " \t");

		if (!tok()) 		
		{
			ErrorStr = "Error! Bad syntax in free bibliographical attribute description";
			return false;
		};

		if (tok.val() != FreeBiblAttribOptionFieldName) 		
		{
			ErrorStr = "Error! Bad syntax in free bibliographical attribute description";
			return false;
		};

		// reading name
		if (!tok()) 
		{
			ErrorStr = "Error! Cannot read name of text area";
			return false;
		};


		string TypeStr = tok.val() ; 
		if (		 (TypeStr != StringTypeStr) 
				&&	(TypeStr != IntegerTypeStr)
	
				)
		{
			ErrorStr = Format("Error! Bad syntax in a bibliographical field, the field type (the second column) must be \"%s\"  or \"%s\" ", IntegerTypeStr, StringTypeStr);
			return false;
		};

		// reading show in header 
		if (!tok()) 
		{
			ErrorStr = "Error! Bad syntax in free bibliographical attribute description";
			return false;
		};

		bool bShowInHeader;
		{
			string ShowInHeaderStr = tok.val();
			if (ShowInHeaderStr == "0")
				bShowInHeader = false;
			else
				if (ShowInHeaderStr == "1")
					bShowInHeader = true;
				else
				{
					ErrorStr = "Error! the first column can in a free bibliographical attribute description should be 0 or 1";
					return false;	
				};
		};

		// reading name
		if (!tok()) 		
		{
			ErrorStr = "Error! Bad syntax in free bibliographical attribute description";
			return false;
		};

		string Name = tok.val();
		if (!tok()) 		
		{
			ErrorStr = "Error! Bad syntax in free bibliographical attribute description";
			return false;
		};

		// reading xpath
		string Xpath = tok.val();
		if (!CheckXPath(Xpath, ErrorStr))
			return false;

		if (Name == "orig")
			m_OrigXPath = Xpath;
		else
		if (Name == "scan")
			m_ScanXPath = Xpath;
		else
		if (Name == "date")
			m_DateXPath = Xpath;
		else
		if (Name == "page")
			m_StartPageXPath = Xpath;
		else
		{
			if ( m_FreeBiblIndices.find(Name) != m_FreeBiblIndices.end() ) 
			{ 
				ErrorStr = Format("Error! Two free bibliographical attributes with the same name (%s)", Name.c_str());
				return false;
			};

			CFreeBiblIndex* pIndex;
			if (TypeStr == StringTypeStr)
				pIndex = new CFreeBiblStringIndex;
			else
				if (TypeStr == IntegerTypeStr)
					pIndex = new CFreeBiblIndex;
				else
				{
					ErrorStr = Format("Error! Unknown type \"%s\" in the options file!", TypeStr.c_str());
					return false;
				}
				
			pIndex->m_Name = Name;
			pIndex->m_Xpath = Xpath;
			pIndex->m_bShowInHeader = bShowInHeader;
			m_FreeBiblIndices[Name] = pIndex;
		};
	};


	return true;
};


string CConcXml::GetFreeBibiAttributesDescr() const
{
	string Result;
	if (!m_OrigXPath.empty())
		Result += Format ("%s string 1 orig %s\n",FreeBiblAttribOptionFieldName.c_str(),  m_OrigXPath.c_str());
	if (!m_ScanXPath.empty())
		Result += Format ("%s string 1 scan %s\n",FreeBiblAttribOptionFieldName.c_str(),  m_ScanXPath.c_str());
	if (!m_DateXPath.empty())
		Result += Format ("%s integer 1 date %s\n",FreeBiblAttribOptionFieldName.c_str(),  m_DateXPath.c_str());
	
	if (!m_StartPageXPath.empty())
		Result += Format ("%s string 1 page %s\n",FreeBiblAttribOptionFieldName.c_str(),  m_StartPageXPath.c_str());


	for (FreeBiblStringMap::const_iterator it = m_FreeBiblIndices.begin(); it != m_FreeBiblIndices.end(); it++)
	{
		Result += it->second->GetDescriptionStr();
		Result += "\n";
	};

	return Result;
};

string CConcXml::GetTextAreasDescr() const
{
	string Result;
	for(size_t i=0; i< m_TextAreas.size(); i++)
	{
		Result += Format ("%s %s %s",
			TextAreaOptionFieldName.c_str(), 
			m_TextAreas[i].m_TextAreaName.c_str(),  
			m_TextAreas[i].m_Xpath.c_str()
			);


		Result += "\n";
	}

	return Result;
}

void CConcXml::ExitWithoutSave()
{
	if (m_BiblBodyFile)
		fclose (m_BiblBodyFile);
	m_BiblBodyFile = 0;
	m_BiblBodyFileSize = 0;
	DeleteFiles();
};

bool CConcXml::FinalSaveBibliography()
{
	fclose (m_BiblBodyFile);
	m_BiblBodyFile = 0;
	m_BiblBodyFileSize = 0;

	for (FreeBiblStringMap::iterator bibl_it = m_FreeBiblIndices.begin(); bibl_it != m_FreeBiblIndices.end(); bibl_it++)
		if (!bibl_it->second->ConvertAndSaveToDiskAfterIndexing (m_Path))
			return false;

	string BiblIndexFileName = GetBiblIndexFileName();
	remove(BiblIndexFileName.c_str());
	if (FileExists(BiblIndexFileName.c_str()) )
	{
		fprintf (stderr,"Cannot delete %s!\n", BiblIndexFileName.c_str());
		return false;
	};

	if (!WriteVector(BiblIndexFileName, m_EndOffsetsInBiblFile))
		return false;
	if (!FileExists(BiblIndexFileName.c_str()) )
	{
		fprintf (stderr,"Cannot create %s!\n", BiblIndexFileName.c_str());
		return false;
	};

	{
		string DatesFName = GetBiblDateIndexFileName();
		remove(DatesFName.c_str());
		if (!WriteVector(DatesFName, m_Dates))
			return false;
		if (!FileExists(DatesFName.c_str()) )
		{
			fprintf (stderr,"Cannot create %s!\n", DatesFName.c_str());
			return false;
		};
	}

	return true;
};


string CConcXml::GetBiblIndexFileName() const 
{
	return MakeFName(m_Path, "_bibl_idx");
};

string CConcXml::GetBiblDateIndexFileName() const 
{
	return MakeFName(m_Path, "_bibl_date");
};

string CConcXml::GetBiblFileName() const 
{
	return MakeFName(m_Path, "_bibl");
};


bool CConcXml::LoadBibl(string Path, size_t FileBreaksSize)
{
	SetPath(Path);
	// reading Bibliographical files if they exist
	if (m_BiblBodyFile) fclose (m_BiblBodyFile);
	m_BiblBodyFile = fopen(GetBiblFileName().c_str(), "rb");

	ReadVector(GetBiblIndexFileName().c_str(), m_EndOffsetsInBiblFile);
	if (m_EndOffsetsInBiblFile.size() !=  FileBreaksSize)
	{
		string s = Format("The number of corpus files should be equal to the number of bibliographical records",m_Path.c_str());
		s += Format("\nnumber of corpus files = %i",FileBreaksSize);
		s += Format("\nnumber of bibliographical records = %i",m_EndOffsetsInBiblFile.size());
		ErrorMessage (s);
		return false;
	};
	assert (m_EndOffsetsInBiblFile.size() == FileBreaksSize);

	ReadVector(GetBiblDateIndexFileName().c_str(), m_Dates);
	if (m_Dates.size() !=  FileBreaksSize)
	{
		ErrorMessage (Format ("Corrupt bibliograpical index file for dates (%s)", GetBiblDateIndexFileName().c_str()));
		return false;
	};

	for (FreeBiblStringMap::iterator bibl_it = m_FreeBiblIndices.begin(); bibl_it != m_FreeBiblIndices.end(); bibl_it++)
		if (!bibl_it->second->ReadFromDisk(m_Path, FileBreaksSize))
			return false;

	return true;
};

CBibliography CConcXml::GetFullBibliographyOfHit(size_t FileNo) const 
{
	if (!m_BiblBodyFile) return CBibliography();
	if (FileNo == m_EndOffsetsInBiblFile.size()) return CBibliography();


	file_off_t EndBiblFileOffset = m_EndOffsetsInBiblFile[FileNo];
	file_off_t StartBiblFileOffset =  (FileNo == 0) ? 0 : m_EndOffsetsInBiblFile[FileNo-1];

	string FileContent;
	//  reading FileContent
	{
		int BiblLength = EndBiblFileOffset-StartBiblFileOffset;
		char* buffer = new  char[BiblLength+1];
		if (!buffer) return CBibliography();

		if (!FSeek(m_BiblBodyFile,  StartBiblFileOffset, SEEK_SET)) 
		{
			delete buffer;
			return  CBibliography();
		};
		if ( fread(buffer, 1, BiblLength,  	m_BiblBodyFile) != BiblLength)
		{
			delete buffer;
			return  CBibliography();
		};
		buffer[BiblLength] = 0;
		FileContent = buffer;
		delete buffer;
	};
	
	CBibliography B;
	B.ReadFromString(FileContent);
	return B;
};


bool  CConcXml::CheckBibl(size_t FileBreaksNumber) const 
{
	printf ("Test %i bibl. references...\n", m_EndOffsetsInBiblFile.size());
	if (m_EndOffsetsInBiblFile.empty()) 
	{
		fprintf (stderr, "There is no bibl. index\n");
		return true;
	};

	if (FileBreaksNumber != m_EndOffsetsInBiblFile.size())
	{
		fprintf (stderr, "The number of files and and the number of bibliographical infos mismatch\n");
		return false;
	};
	
	file_off_t prev_offset = 0;
	for (size_t i = 0; i <m_EndOffsetsInBiblFile.size();i++) 
	{
		const file_off_t& In = m_EndOffsetsInBiblFile[i];
		if (prev_offset > In) 
		{
			fprintf (stderr, "Bad offset reference from bibl-index to bibl-file\n");
			return false;
		}
		prev_offset = In;

	};


	if (prev_offset != FileSize(GetBiblFileName().c_str()))
	{
		fprintf (stderr, "There are unreferenced or missing bibl. records in bibl-file\n");
		return false;
	};

	return true;

};




bool CConcXml::UniteBibliography(const CConcXml& B1, const CConcXml& B2)
{

	
	printf ("Uniting bibliographical integer indices\n");
	{
		m_EndOffsetsInBiblFile = B1.m_EndOffsetsInBiblFile;
		m_EndOffsetsInBiblFile.insert(m_EndOffsetsInBiblFile.end(), B2.m_EndOffsetsInBiblFile.begin(),B2.m_EndOffsetsInBiblFile.end());
		file_off_t BiblOffset = FileSize(B1.GetBiblFileName().c_str());
		for (size_t i = B1.m_EndOffsetsInBiblFile.size(); i < m_EndOffsetsInBiblFile.size(); i++)
			m_EndOffsetsInBiblFile[i] += BiblOffset;

		if (!m_EndOffsetsInBiblFile.empty())
			if (!WriteVector(GetBiblIndexFileName().c_str(), m_EndOffsetsInBiblFile))
				return false;
	}

	printf ("Uniting dates\n");
	{
		m_Dates = B1.m_Dates;
		m_Dates.insert(m_Dates.end(), B2.m_Dates.begin(), B2.m_Dates.end());
		if (!WriteVector(GetBiblDateIndexFileName().c_str(), m_Dates))
			return false;
	};


	printf ("Uniting free bibliographical attributes\n");
	{
		if (B1.GetFreeBibiAttributesDescr() != B1.GetFreeBibiAttributesDescr())
		{
			fprintf (stderr, "The sets of free bibliographical attributes are different\n");
			return false;
		}
		string ErrorStr;
		if (!RegisterFreeBiblAttributes(B1.GetFreeBibiAttributesDescr(), ErrorStr))
		{
			fprintf (stderr, "%s\n", ErrorStr.c_str());
			return false;
		}
		if (!RegisterTextAreas(B1.GetTextAreasDescr(), ErrorStr))
		{
			fprintf (stderr, "%s\n", ErrorStr.c_str());
			return false;
		}

		FreeBiblStringMap::const_iterator bibl_it1 = B1.m_FreeBiblIndices.begin();
		FreeBiblStringMap::const_iterator bibl_it2 = B2.m_FreeBiblIndices.begin();
		FreeBiblStringMap::iterator bibl_it = m_FreeBiblIndices.begin();
		for (; bibl_it != m_FreeBiblIndices.end(); bibl_it++, bibl_it1++, bibl_it2++)
		{
			bibl_it->second->CreateUnion(m_Path, bibl_it1->second, bibl_it2->second);
		};
	};

	
	//====================
	printf ("Uniting bibliographical strings\n");
	remove(GetBiblFileName().c_str());
	if (FileExists(B1.GetBiblFileName().c_str() ) )
		AddFile(GetBiblFileName().c_str(),B1.GetBiblFileName().c_str() );

	if (FileExists(B2.GetBiblFileName().c_str() ) )
		AddFile(GetBiblFileName().c_str(),B2.GetBiblFileName().c_str());
	return true;
};

void CConcXml::InitNoSort(vector<CHit>&	Hits) const
{
	size_t HitsCount = Hits.size();
	for (size_t HitNo=0; HitNo< HitsCount; HitNo++)
	{
		CHit&  H = Hits[HitNo];
		H.m_OrderId = HitNo;
	}
}

void CConcXml::InitLessByDate(vector<CHit>&	Hits) const
{
	size_t HitsCount = Hits.size();
	for (size_t HitNo=0; HitNo< HitsCount; HitNo++)
	{
		CHit&  H = Hits[HitNo];
		H.m_OrderId = m_Dates.empty() ? 0 : m_Dates[H.m_FileNo];
	}
}

void CConcXml::InitGreaterByDate(vector<CHit>&	Hits) const
{
	size_t HitsCount = Hits.size();
	for (size_t HitNo=0; HitNo< HitsCount; HitNo++)
	{
		CHit&  H = Hits[HitNo];
		H.m_OrderId = m_Dates.empty() ? 0 : -m_Dates[H.m_FileNo];
	}
}


void CConcXml::InitLessByBiblIntegerField(string FreeBiblAttribName, vector<CHit>&	Hits) const
{
	const CFreeBiblIndex* pFreeAttrib = 0;	

	if (!FreeBiblAttribName.empty())
	{
		FreeBiblStringMap::const_iterator it = m_FreeBiblIndices.find(FreeBiblAttribName);
		if (it != m_FreeBiblIndices.end()) 
			pFreeAttrib = it->second;
	};
	if (pFreeAttrib == 0) return InitNoSort(Hits);	
	
	size_t HitsCount = Hits.size();

	assert (pFreeAttrib);
	for (size_t HitNo=0; HitNo < HitsCount; HitNo++)
	{
		CHit&  H = Hits[HitNo];
		H.m_OrderId = pFreeAttrib->GetIntegerValue(H.m_FileNo);
	}

};


bool CConcXml::IsRegisteredBiblField(string FreeBiblAttribName) const
{
	const CFreeBiblIndex* pFreeAttrib = 0;	

	if (!FreeBiblAttribName.empty())
	{
		FreeBiblStringMap::const_iterator it = m_FreeBiblIndices.find(FreeBiblAttribName);
		if (it != m_FreeBiblIndices.end()) 
			return true;
	};
	return false;
}
void CConcXml::InitGreaterByBiblIntegerField(string FreeBiblAttribName, vector<CHit>&	Hits) const
{
	const CFreeBiblIndex* pFreeAttrib = 0;	

	if (!FreeBiblAttribName.empty())
	{
		FreeBiblStringMap::const_iterator it = m_FreeBiblIndices.find(FreeBiblAttribName);
		if (it != m_FreeBiblIndices.end()) 
			pFreeAttrib = it->second;
	};
	if (pFreeAttrib == 0) return InitNoSort(Hits);

	size_t HitsCount = Hits.size();
	assert (pFreeAttrib);
	for (size_t HitNo=0; HitNo < HitsCount; HitNo++)
	{
		CHit&  H = Hits[HitNo];
		H.m_OrderId = -pFreeAttrib->GetIntegerValue(H.m_FileNo);
	}
};



bool CConcXml::GetValueFromBiblSet (const RML_RE::Options &RegexOpts, string Value, CDDCFilterWithBounds& Filter, bool isRegex) const
{
	Filter.m_SatisfiedValues.clear();
	Filter.m_bRegExp = isRegex;
	
	FreeBiblStringMap::const_iterator it = m_FreeBiblIndices.find(Filter.m_FreeBiblAttribName);

	if (it == m_FreeBiblIndices.end()) //  the attribute is not found
		return false;

	return it->second->GetValueForDDCFilter(RegexOpts, Value, Filter, isRegex);;
};




bool CConcXml::LoadXmlAndReadBibliography(TiXmlDocument& doc, const char* pFileBuffer, CBibliography& Bibl, string& strError)
{
	string Buffer = pFileBuffer;
	doc.Parse(Buffer.c_str());

	if ( doc.Error() )
	{
		strError = Format("cannot open or parse Col=%i,  Row=%i, Error=%s", doc.ErrorCol(), doc.ErrorRow(), doc.ErrorDesc());
		return false;
	};
	Bibl.CleanBibliography();

	if (!m_OrigXPath.empty())
		Bibl.m_OrigBibl  = ReadXmlField(doc, m_OrigXPath);

	if (!m_ScanXPath.empty())
		Bibl.m_ScanBibl  = ReadXmlField(doc, m_ScanXPath);

	if (!m_DateXPath.empty())
	{
		Bibl.m_DateStr  = ReadXmlField(doc, m_DateXPath);
		int Date;
		if (!Bibl.ConvertDateToInt(Date))
		{
			if (Bibl.m_DateStr.empty())
				strError = Format("Empty date!", Bibl.m_DateStr.c_str());
			else
				strError = Format("Bad format of the date(\"%s\")", Bibl.m_DateStr.c_str());
			return false;
		};
	}

	if (!m_StartPageXPath.empty())
	{
			string page_str = ReadXmlField(doc, m_StartPageXPath);
			Bibl.m_StartPageInfo = UnknownPageNumber;
			if (!page_str.empty())
			{
				int i  = atoi(page_str.c_str());
				if (i != 0)
					Bibl.m_StartPageInfo = i;
			};
			
	}
	


	assert ( Bibl.m_BiblAttribs.empty() );
	for (FreeBiblStringMap::iterator bibl_it = m_FreeBiblIndices.begin(); bibl_it != m_FreeBiblIndices.end(); bibl_it++)
	{
		const CFreeBiblIndex* pIndexItem  =  bibl_it->second;
		string q = ReadXmlField(doc, pIndexItem ->m_Xpath);
		// push attributes in the same order as m_FreeBiblIndices is ordered
		Bibl.m_BiblAttribs.push_back(q);
	};
	
	
	return  true;
};

void  CConcXml::SetFreeBiblAttribsEmpty(CBibliography& Bibl)
{
	assert ( Bibl.m_BiblAttribs.empty() );
	for (FreeBiblStringMap::iterator bibl_it = m_FreeBiblIndices.begin(); bibl_it != m_FreeBiblIndices.end(); bibl_it++)
		Bibl.m_BiblAttribs.push_back("");
};


bool CConcXml::GetTextAreaElements(const TiXmlDocument& doc, vector<TiXmlElement*>& Result, string& strError)const 
{
	Result.clear();

	for (size_t i=0; i < m_TextAreas.size(); i++)
	{
		TiXmlNode* text = TinyXPath::XNp_xpath_node(doc.RootElement(), m_TextAreas[i].m_Xpath.c_str());
		if (!text)
		{
			strError = Format("Cannot find %s in the source document using XPath \"%s\"!", 
				m_TextAreas[i].m_TextAreaName.c_str(),
				m_TextAreas[i].m_Xpath.c_str());
			return false;
		};
		Result.push_back(text->ToElement());
	}

	return true;
};

size_t	CConcXml::GetTextAreasCount() const
{
	return m_TextAreas.size();
}


bool CConcXml::ReadMorphXmlFileIntoGraTable(string FileName,  const char* pFileBuffer, vector<CXmlToken>& GraTable, string& strError, CBibliography& Bibl)
{
	
	TiXmlDocument doc( FileName.c_str() );

	if (!LoadXmlAndReadBibliography(doc, pFileBuffer, Bibl, strError)) return false;

	vector<TiXmlElement*> TextAreas;
	if (!GetTextAreaElements(doc, TextAreas, strError))
		return false;

	for (size_t TextAreaNo = 0; TextAreaNo< TextAreas.size(); TextAreaNo++)
	{
		TiXmlElement* text = TextAreas[TextAreaNo];

		size_t AllWordsCount = 0;
		string LastReadWord;
		try {
			for (TiXmlElement* sent = text->FirstChildElement("s"); sent; sent = sent->NextSiblingElement("s"))
			{
				size_t CountOfWord = 0;
				for (TiXmlElement* xml_word = sent->FirstChildElement(); xml_word;  xml_word = xml_word->NextSiblingElement())
				{

					CXmlToken Word;
					Word.m_Type =  xml_word->Value();
					Trim(Word.m_Type);
					if (Word.m_Type == "pb")
					{
						const char*	q = xml_word->Attribute("n");
						if (q)
						{
							Word.m_WordStr = q;
							GraTable.push_back(Word);
							continue;
						}
						else
						{
							strError = Format("bad page break; cannot parse the input [WordNo=%i LastReadWord=%s]",  AllWordsCount, LastReadWord.c_str());						
							return false;
						};
					};

					{
						TiXmlNode* xml_word_str = xml_word->FirstChild();
						if (!xml_word_str)
						{
							strError = Format("cannot get the next word [WordNo=%i LastReadWord=%s]", AllWordsCount, LastReadWord.c_str());						
							return false;
						};
						Word.m_WordStr = xml_word_str->Value();
						Trim(Word.m_WordStr);
					};
					if (Word.m_WordStr.empty())
					{
						fprintf(stderr, "empty word after word WordNo=%i WordStr=%s\n", AllWordsCount, LastReadWord.c_str());
						continue;
					};

					
					for (TiXmlElement* xml_annot = xml_word->FirstChildElement("ana"); xml_annot;  xml_annot = xml_annot->NextSiblingElement("ana"))
					{
						CXmlMorphAnnot A;
						
						{
							const char*	q= xml_annot->Attribute("lex");
							string s = q ? q :"";
							for (int i=0;  i<s.length(); i++)
								if ((s[i] != '`') &&  (s[i] != '*'))
									A.m_Lemma += s[i];
						};
						
						{
							const char* s= xml_annot->Attribute("gr");
							if (s)
								A.m_GrammemsStr = s;
						};
						Word.m_Annots.push_back(A);
					};
					GraTable.push_back(Word);
					CountOfWord++;
					AllWordsCount++;
					LastReadWord = Word.m_WordStr; 
				};

				if (CountOfWord > 0)
				{
					GraTable.back().m_bLastInSentence = true;
				};
			};
		}
		catch (...)
		{
			strError = Format("an exception while reading xml WordNo=%i LastReadWord=%s", AllWordsCount, LastReadWord.c_str());
			return false;
		};
	}

	return true;
};

string CConcXml::GetVisibleFreeHeaderBiblAttributes(size_t  FileNo,  string Delim) const 
{
	string Result;
	for (FreeBiblStringMap::const_iterator bibl_it = m_FreeBiblIndices.begin(); bibl_it != m_FreeBiblIndices.end(); bibl_it++)
	{
		const CFreeBiblIndex* I = bibl_it->second;
		if (I->m_bShowInHeader)
		{
			Result += Delim;
			Result += I->GetStringValue(FileNo);
		};
	};

	return Result;

};

string CConcXml::GetFreeHeaderBiblAttributesWithNames(size_t  FileNo,  char Delim) const
{
	string Result;
	for (FreeBiblStringMap::const_iterator bibl_it = m_FreeBiblIndices.begin(); bibl_it != m_FreeBiblIndices.end(); bibl_it++)
	{
		CFreeBiblIndex* I = bibl_it->second;
		if (I->m_bShowInHeader)
		{
			Result += Delim;
			Result += I->m_Name;
			Result += Delim;
			Result += I->GetStringValue(FileNo);
		};
	};
	return Result;
};

string CConcXml::GetFreeHeaderBiblAttributesJson(size_t FileNo, bool assume_utf8) const
{
    string js("");
    for (FreeBiblStringMap::const_iterator bibl_it = m_FreeBiblIndices.begin(); bibl_it != m_FreeBiblIndices.end(); bibl_it++) {
	CFreeBiblIndex* I = bibl_it->second;
	if (I->m_bShowInHeader) {
	    if (!js.empty()) js.push_back(',');
	    js.append(jsonStr(I->m_Name, assume_utf8));
	    js.push_back(':');
	    js.append(jsonStr(I->GetStringValue(FileNo), assume_utf8));
	}
    }
    return js;
}


int CConcXml::GetTextAreaByName(const string& Name) const
{
	for(int i=0; i < m_TextAreas.size(); i++)
		if (m_TextAreas[i].m_TextAreaName == Name)
			return i;
	return UnknownTextAreaNo;
}

int CConcXml::WithinTextArea(const vector<string>& Within) const
{
	for (vector<string>::const_reverse_iterator wi=Within.rbegin(); wi != Within.rend(); wi++) {
		int TextAreaNo = GetTextAreaByName(*wi);
		if (TextAreaNo != UnknownTextAreaNo)
			return TextAreaNo;
	}
	return UnknownTextAreaNo;
}
