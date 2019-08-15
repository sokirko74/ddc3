/*-*- Mode: C++; c-basic-offset: 8; -*-*/
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
#include "Bibliography.h"
#include "../tinyxml/xpath_static.h"
#include "../common/bserialize.h"
#include "../CommonLib/ddcString.h"
#include <typeinfo>	//-- for typeid()

const char IntegerTypeStr[] = "integer";
const char StringTypeStr[]  = "string";
const char StringConstantTypeStr[]  = "constant";
const char StringAliasTypeStr[]  = "alias";
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
		ErrStr = "Empty XPath";
		return false;
	};
#if 0
	//-- no longer required as of v2.0.19, which supports constant XPath expressions (e.g. for date)
	if (XPath[0] != '/' ) 
	{
		ErrStr = "XPath should start with '/'";
		return false;
	};
#endif
	if (XPath[XPath.length() - 1] == '/' ) 
	{
		ErrStr = "XPath should not end with '/'";
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

	string Result;
	switch (er_res.e_type) {
	case TinyXPath::e_bool:
		Result = (er_res.o_get_bool() ? "1" : "0");
		break;

	case TinyXPath::e_string:
		Result = er_res.cp_get_string();
		break;

	case TinyXPath::e_int:
		Result = Format("%d", er_res.i_get_int());
		break;

	case TinyXPath::e_double:
		Result = Format("%g", er_res.d_get_double());
		break;

	case TinyXPath::e_node_set:
		{
			TinyXPath::node_set* pSet = er_res.nsp_get_node_set();
			size_t Count = pSet->u_get_nb_node_in_set();
			for (size_t u_node= 0; u_node < Count; u_node++) {
				string s;
				const TiXmlBase* pBase = pSet->XBp_get_base_in_set(u_node);
				if (pSet->o_is_attrib(u_node)  ) {
					const TiXmlAttribute * node =  pSet->XAp_get_attribute_in_set(u_node);
					s = node->Value();
				}
				else {
					const TiXmlNode * node =  pSet->XNp_get_node_in_set(u_node);
					for (TiXmlNode* child = node->FirstChild();  child;  child = child->NextSibling())
						if (child -> Type () == TiXmlNode::TEXT) {
							string  q = child->Value();
							Trim(q);
							s += q;
						};
				}
				Result += s;
				if (u_node+1 < Count) 
					Result += ":";
			}
		}
		break;

	case TinyXPath::e_invalid:
	default:
		ErrorMessage( Format("Error: Unknown or invalid return type for XPath `%s'", XPath.c_str()) );
		break;
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

bool CBibliography::ConvertDateToInt(int& Result) const 
{
	if (m_DateStr.empty()) 
		return false;
	int  year, month, day;
	StringTokenizer tok(m_DateStr.c_str(),"-");
	if (!tok()) return false;
	year = atoi(tok.val());
	if (year > 0xffff) return false; //-- moo: year-part is 16-bit
	if (tok())
	{
		//-- Mon, 17 Feb 2015 13:26:37 +0100 moocow: allow MM > 12, YYYY-MM dates, and YYYY-MM-DD with DD > 31 
		month = atoi(tok.val());

		if (tok()) day = atoi(tok.val());
	}
	else
	{
		month = 1;
		day   = 1;
	};
	Result = date2int(year,month,day);
	return true;
};

//=============================================



//=============================================

CConcXml::CFreeBiblIndex::CFreeBiblIndex()
{}

CConcXml::CFreeBiblIndex::~CFreeBiblIndex()
{}

void	CConcXml::CFreeBiblIndex::clear()
{
	m_bShowInHeader = false;
	m_ValuesForEachFile.clear();
}

string CConcXml::CFreeBiblIndex::GetStringValue(DWORD FileNo ) const 
{
	return Format("%i", (int)m_ValuesForEachFile[FileNo]);
}

int CConcXml::CFreeBiblIndex::GetIntegerValue(DWORD FileNo ) const 
{
	return m_ValuesForEachFile[FileNo];
}



bool CConcXml::CFreeBiblIndex::ReadFromDisk (string Path,  DWORD FileBreaksSize, bool useMMap) 
{
	m_ValuesForEachFile.open(GetIndexFileName(Path), useMMap);
	

	if (m_ValuesForEachFile.size() != FileBreaksSize)
	{
		ErrorMessage (Format("The number of corpus files (%zi) should be equal to the number of bibliographical records (%zi; index name = %s)",
				     FileBreaksSize, m_ValuesForEachFile.size(), m_Name.c_str()));
		return false;
	};

	return true;
}

string  CConcXml::CFreeBiblIndex::GetDescriptionStr () const
{
	return Format ("%s %s %i %s %s", 
			FreeBiblAttribOptionFieldName.c_str(),  this->GetTypeStr().c_str(),
		       m_bShowInHeader ? 1:0,  m_Name.c_str(),  this->GetXpathStr().c_str());
}

string  CConcXml::CFreeBiblIndex::GetIndexFileName (string Path) const
{
	return MakeFName(Path, string("_bibl_")+m_Name+"_integers");
}

void CConcXml::CFreeBiblIndex::CreateUnion (const string& Path, const vector<const CFreeBiblIndex*>& Indices, const vector<size_t>& FileCounts)
{
	m_ValuesForEachFile.clear();
	m_ValuesForEachFile.ensureVec();
	for (size_t i=0; i < Indices.size(); ++i) {
		if (Indices[i] != NULL) {
			m_ValuesForEachFile.m_vec.insert(m_ValuesForEachFile.m_vec.end(), Indices[i]->m_ValuesForEachFile.begin(), Indices[i]->m_ValuesForEachFile.end());
		} else {
			m_ValuesForEachFile.m_vec.resize(m_ValuesForEachFile.m_vec.size()+FileCounts[i], 0);
		}
	}
	m_ValuesForEachFile.ensureData();
	m_ValuesForEachFile.save(GetIndexFileName(Path));
}

void CConcXml::CFreeBiblIndex::CreatePartitions(vector<CFreeBiblIndex*>& Parts, const vector<string>& Paths, const vector<DWORD>& EndFileNo) const
{
	assert(Parts.size()==Paths.size());
	assert(Parts.size()==EndFileNo.size());
	for (size_t i=0; i < Parts.size(); ++i) {
		Parts[i]->m_ValuesForEachFile.clear();
		Parts[i]->m_ValuesForEachFile.ensureVec();
		Parts[i]->m_ValuesForEachFile.m_vec.assign(m_ValuesForEachFile.begin()+(i==0 ? 0 : EndFileNo[i-1]),
							   m_ValuesForEachFile.begin()+EndFileNo[i]);
		Parts[i]->m_ValuesForEachFile.ensureData();
		Parts[i]->m_ValuesForEachFile.save(Parts[i]->GetIndexFileName(Paths[i]));
	}
}


bool CConcXml::CFreeBiblIndex::GetFilterBounds (CDDCFilterWithBounds& Filter, const string &LoValue, const string &HiValue) const
{
	Filter.m_bSet = false;
	Filter.m_KeyLo = LoValue.empty() ? INT_MIN : atoi(LoValue.c_str());
	Filter.m_KeyHi = HiValue.empty() ? INT_MAX : atoi(HiValue.c_str());
	Filter.m_BiblIndex = this;
	return true;
}

bool CConcXml::CFreeBiblIndex::GetFilterValue (CDDCFilterWithBounds& Filter, const string &Value) const
{
	Filter.m_bSet = false;
	Filter.m_KeyLo = atoi(Value.c_str());
	Filter.m_KeyHi = Filter.m_KeyLo.i+1;
	Filter.m_BiblIndex = this;
	return true;
}

bool CConcXml::CFreeBiblIndex::GetFilterValues (CDDCFilterWithBounds& Filter, const string &Regex) const
{
	throw CExpc(errLogic,"%s::GetFilterValues(): field `%s' doesn't support regular expressions", typeid(*this).name(), m_Name.c_str());
	return false;
}

bool CConcXml::CFreeBiblIndex::GetFilterValues (CDDCFilterWithBounds& Filter, const set<string> &Values) const
{
	throw CExpc(errLogic,"%s::GetFilterValues(): field `%s' doesn't support set values", typeid(*this).name(), m_Name.c_str());
	return false;
}

bool CConcXml::CFreeBiblIndex::FileMatches(DWORD FileNo, const CDDCFilterWithBounds& Filter) const
{
	// + 2019-08-15 moocow
	//   - val: cast to int so it jives with CHitSortKey::i (avoid signed/unsigned comparison)
	//   - should fixes bogus empty responses from e.g. "count(* #asc[author]) #by[textClass]"
	int val = this->GetIntegerValue(FileNo);
	return (Filter.m_bSet
		? (Filter.m_SatisfiedValues.find(val) != Filter.m_SatisfiedValues.end())
		: ((val >= Filter.m_KeyLo.i) && (val < Filter.m_KeyHi.i))
		);
}

bool CConcXml::CFreeBiblIndex::RegisterBiblStringItemId(const string& ValueStr)
{
	int u = ValueStr.empty() ? 0 : atoi(ValueStr.c_str());
	m_ValuesForEachFile.push_back(u);
	return true;
}


bool CConcXml::CFreeBiblIndex::DeleteBiblFiles (string Path) const 
{
	return		remove(GetIndexFileName(Path).c_str()) == 0;
}


bool CConcXml::CFreeBiblIndex::ConvertAndSaveToDiskAfterIndexing (string Path) 
{
	m_ValuesForEachFile.ensureVec();
	return WriteVector(GetIndexFileName(Path), m_ValuesForEachFile.m_vec);
}

string CConcXml::CFreeBiblIndex::GetTypeStr() const
{
	return IntegerTypeStr;
}

CFreeBiblIndexTypeId CConcXml::CFreeBiblIndex::GetTypeId() const
{
	return cfbiInteger;
}

const string& CConcXml::CFreeBiblIndex::GetXpathStr() const
{
	return m_Xpath;
}

DWORD CConcXml::CFreeBiblIndex::GetIntegerLowerBound(const string& Value) const
{
	return Value.empty() ? 0 : hex2int(Value);
}

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
	m_ValuesE.clear();
};

string CConcXml::CFreeBiblStringIndex::GetStringValue(DWORD FileNo ) const 
{
	return m_ValuesE[m_ValuesForEachFile[FileNo]];
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

bool CConcXml::CFreeBiblStringIndex::ReadBiblStringItems (string FileName, bool useMMap)
{
	m_ValuesE.open(FileName+"_values", FileName+"_idx", FileName, useMMap);
	return true;
};

bool CConcXml::CFreeBiblStringIndex::WriteBiblStringItems (const vector<string>&  Set, string FileName) const
{
	string ValuesFile = FileName + "_values";
	FILE *vfp = fopen(ValuesFile.c_str(), "wb");
	if (!vfp)  {
		ddcLogError(Format("CConcXml::CFreeBiblStringIndex::WriteBiblStringItems(): open failed for '%s': %s",ValuesFile.c_str(), strerror(errno)));
		return false;
	}

	string IndexFile  = FileName + "_idx";
	FILE *ifp = fopen(IndexFile.c_str(), "wb");
	if (!ifp)  {
		ddcLogError(Format("CConcXml::CFreeBiblStringIndex::WriteBiblStringItems(): open failed for '%s': %s",IndexFile.c_str(), strerror(errno)));
		return false;
	}

	for (size_t i=0; i< Set.size(); i++) {
		ddcStringEnum<>::OffT pos = ftell(vfp);
		fwrite(&pos, sizeof(ddcStringEnum<>::OffT), 1, ifp);
		fwrite(Set[i].c_str(), 1, Set[i].size()+1, vfp);
	}

	fclose(ifp);
	fclose(vfp);
	return true;
};

string CConcXml::CFreeBiblStringIndex::GetTypeStr() const
{
	return StringTypeStr;
};

CFreeBiblIndexTypeId CConcXml::CFreeBiblStringIndex::GetTypeId() const
{
	return cfbiString;
};


bool CConcXml::CFreeBiblStringIndex::ReadFromDisk (string Path, DWORD FileBreaksSize, bool useMMap) 
{
	if (!ReadBiblStringItems(GetStringFileName(Path), useMMap))
		return false;
	return CFreeBiblIndex::ReadFromDisk(Path, FileBreaksSize, useMMap);
}

void CConcXml::CFreeBiblStringIndex::CreateUnion(const string& Path, const vector<const CFreeBiblIndex*>& Indices, const vector<size_t>& FileCounts)
{
	assert(Indices.size()==FileCounts.size());
	
	//-- cast arguments to CFreeBiblStringIndex
	vector<const CFreeBiblStringIndex*> sIndices(Indices.size());
	for (size_t i=0; i < Indices.size(); ++i) {
		sIndices[i] = (const CFreeBiblStringIndex*)Indices[i];
	}
	
	//-- get set of all values (expensive)
	set<string> values;
	string s;
	for (size_t i=0; i < sIndices.size(); ++i) {
		if (sIndices[i]==NULL) {
			if (values.find("") == values.end()) values.insert("");
			continue;
		}
		for (size_t j=0; j < sIndices[i]->m_ValuesE.size(); ++j) {
			s = sIndices[i]->m_ValuesE[j];
			if (values.find(s) == values.end()) values.insert(s);
		}
	}
	ddcLogDebug(Format("found %zd value type(s) for attribute %s", values.size(), m_Name.c_str()));

	//-- populate m_ValuesE and build translation tables
	m_ValuesE.clear();
	m_ValuesE.ensureVec();
	vector< vector<DWORD> > xlateId(sIndices.size());
	for (size_t i=0; i < sIndices.size(); ++i) {
		if (sIndices[i] != NULL) xlateId[i].resize(sIndices[i]->m_ValuesE.size());
	}
	for (set<string>::const_iterator si=values.begin(); si!=values.end(); ++si) {
		m_ValuesE.m_strings.push_back(*si);
		for (size_t i=0; i < sIndices.size(); ++i) {
			if (sIndices[i]==NULL) continue;
			DWORD oldId = sIndices[i]->m_ValuesE.find(*si);
			if (oldId != sIndices[i]->m_ValuesE.NO_ID)
				xlateId[i][oldId] = m_ValuesE.m_strings.size()-1;
		}
	}
	WriteBiblStringItems(m_ValuesE.m_strings, GetStringFileName(Path));
	//CFreeBiblIndex::ConvertAndSaveToDiskAfterIndexing(Path);

	//-- write integers by file (a la CConcXml::CFreeBiblIndex::CreateUnion)
	m_ValuesForEachFile.clear();
	m_ValuesForEachFile.ensureVec();
	size_t voff = 0;
	for (size_t i=0; i < sIndices.size(); ++i) {
		m_ValuesForEachFile.m_vec.resize(voff+FileCounts[i], 0);
		if (sIndices[i] == NULL) continue;
		for (size_t j=0; j < sIndices[i]->m_ValuesForEachFile.size(); ++j)
			m_ValuesForEachFile.m_vec[voff+j] = xlateId[i][ sIndices[i]->m_ValuesForEachFile[j] ];
		voff += FileCounts[i];
	}
	m_ValuesForEachFile.ensureData();
	m_ValuesForEachFile.save(GetIndexFileName(Path));
};


void CConcXml::CFreeBiblStringIndex::CreatePartitions(vector<CFreeBiblIndex*>& Parts, const vector<string>& Paths, const vector<DWORD>& EndFileNo) const
{
	assert(Parts.size()==Paths.size());
	assert(Parts.size()==EndFileNo.size());

	for (size_t i=0; i < Parts.size(); ++i) {
		ddcLogDebug(Format("CConcXml::CFreeBiblStringIndex::CreatePartitions(%s): creating partition #%zd", m_Name.c_str(), i));
		CFreeBiblStringIndex *Part = (CFreeBiblStringIndex*)Parts[i];
		DWORD f_begin = (i==0 ? 0 : EndFileNo[i-1]);
		DWORD f_end   = EndFileNo[i];

		//-- get item-set for this partition
		set<DWORD> PartItems;
		for (DWORD fi=f_begin; fi < f_end; ++fi) {
			DWORD itemId = m_ValuesForEachFile[fi];
			if (PartItems.find(itemId) == PartItems.end()) PartItems.insert(itemId);
		}

		//-- populate m_ValuesE, build translation table
		Part->m_ValuesE.clear();
		Part->m_ValuesE.ensureVec();
		vector<DWORD> xlateId(m_ValuesE.size(), DWORD_MAX); //-- [oldId] => newId_or_DWORD_MAX
		for (set<DWORD>::const_iterator itemi=PartItems.begin(); itemi!=PartItems.end(); ++itemi) {
			xlateId[*itemi] = Part->m_ValuesE.m_strings.size();
			Part->m_ValuesE.m_strings.push_back( m_ValuesE[*itemi] );
		}
		ClearContainer(PartItems);
		Part->WriteBiblStringItems(Part->m_ValuesE.m_strings, Part->GetStringFileName(Paths[i]));

		//-- populate integers by file (a la CConcXml::CFreeBiblIndex::CreatePartitions())
		Part->m_ValuesForEachFile.clear();
		Part->m_ValuesForEachFile.ensureVec();
		Part->m_ValuesForEachFile.m_vec.assign(m_ValuesForEachFile.begin()+f_begin,
						       m_ValuesForEachFile.begin()+f_end);
		for (vector<DWORD>::iterator vali=Part->m_ValuesForEachFile.m_vec.begin(); vali!=Part->m_ValuesForEachFile.m_vec.end(); ++vali)
			*vali = xlateId[*vali];
		Part->m_ValuesForEachFile.ensureData();
		Part->m_ValuesForEachFile.save(Part->GetIndexFileName(Paths[i]));
	}
};

bool CConcXml::CFreeBiblStringIndex::GetFilterBounds (CDDCFilterWithBounds& Filter, const string &LoValue, const string &HiValue) const
{
	Filter.m_bSet = false;
	Filter.m_BiblIndex = this;

	//-- lower bound
	Filter.m_KeyLo.assign(INT_MIN,LoValue);
	if (!LoValue.empty()) {
		DWORD ilo = m_ValuesE.lower_bound(LoValue);
		Filter.m_KeyLo.i = (ilo != m_ValuesE.NO_ID ? ilo : INT_MAX);
	}

	//-- upper bound
	Filter.m_KeyHi.assign(INT_MAX,HiValue);
	if (!HiValue.empty()) {
		DWORD ihi = m_ValuesE.upper_bound(HiValue);
		Filter.m_KeyHi.i = (ihi != m_ValuesE.NO_ID ? ihi : m_ValuesE.size());
	}

	return true;
}

DWORD CConcXml::CFreeBiblStringIndex::GetIntegerLowerBound(const string& Value) const
{
	if (Value.empty())
		return INT_MIN;

	DWORD ilo = m_ValuesE.lower_bound(Value);
	return (ilo != m_ValuesE.NO_ID ? ilo : INT_MAX);
}

bool CConcXml::CFreeBiblStringIndex::GetFilterValue (CDDCFilterWithBounds& Filter, const string &Value) const
{
	Filter.m_bSet = false;
	Filter.m_BiblIndex = this;

	if (Value.empty()) return true; //-- compatibility

	if (Filter.m_bNegated) {
		//-- negative filter condition (literal): generate regex
		return GetFilterValues(Filter, string("^") + escapeRegex(Value) + "$");
	}

	//-- positive filter condition (literal)
	DWORD id = m_ValuesE.find(Value);
	if ( id == m_ValuesE.NO_ID ){
		Filter.m_KeyLo = 0;
		Filter.m_KeyHi = 0;
	}
	else {
		Filter.m_KeyLo.assign(id,                 Value);
		Filter.m_KeyHi.assign(Filter.m_KeyLo.i+1, Value);
	}
	
	return true;
};

bool CConcXml::CFreeBiblStringIndex::GetFilterValues (CDDCFilterWithBounds& Filter, const string &Regex) const
{
	RML_RE re(Regex, *m_pRegexOpts);
	size_t Count = m_ValuesE.size();

	//-- regex condition: positive or negative
	Filter.m_bSet  = true;
	Filter.m_BiblIndex = this;
	for (size_t i=0; i<Count; i++) {
		bool isMatch = re.PartialMatch(m_ValuesE[i]);
		if (Filter.m_bNegated ? (!isMatch) : isMatch)
			Filter.m_SatisfiedValues.insert(i);
	}

	//-- sanitize filter ranges (compatibility)
	if (Filter.m_SatisfiedValues.empty()) {
		Filter.m_KeyLo = 0;
		Filter.m_KeyHi = 0;
	}
	else {
		Filter.m_KeyLo.i = *Filter.m_SatisfiedValues.begin();
		Filter.m_KeyLo.s = m_ValuesE[Filter.m_KeyLo.i];

		Filter.m_KeyHi.i = *Filter.m_SatisfiedValues.rbegin();
		Filter.m_KeyHi.s = m_ValuesE[Filter.m_KeyHi.i];
		Filter.m_KeyHi.i++;
	}

	return true;
};

bool CConcXml::CFreeBiblStringIndex::GetFilterValues (CDDCFilterWithBounds& Filter, const set<string> &Values) const
{
	Filter.m_bSet = true;
	Filter.m_BiblIndex = this;

	if (!Filter.m_bNegated) {
		//-- set-valued condition: positive: iterate over argument values (assume |Values| << |m_Values|)
		for (set<string>::const_iterator vali=Values.begin(); vali != Values.end(); ++vali) {
			DWORD it = m_ValuesE.find(*vali);
			if (it != m_ValuesE.NO_ID)
				Filter.m_SatisfiedValues.insert(it);
		}
	}
	else {
		//-- set-valued condition: negative: iterate over indexed values (expensive)
		size_t Count = m_ValuesE.size();
		for (size_t i=0; i < Count; i++) {
			set<string>::const_iterator vali = Values.find(m_ValuesE[i]);
			if (vali == Values.end())
				Filter.m_SatisfiedValues.insert(i);
		}
	}

	//-- sanitize filter ranges (compatibility)
	if (Filter.m_SatisfiedValues.empty()) {
		Filter.m_KeyLo = 0;
		Filter.m_KeyHi = 0;
	}
	else {
		Filter.m_KeyLo.i = *Filter.m_SatisfiedValues.begin();
		Filter.m_KeyLo.s = m_ValuesE[Filter.m_KeyLo.i];

		Filter.m_KeyHi.i = *Filter.m_SatisfiedValues.rbegin();
		Filter.m_KeyHi.s = m_ValuesE[Filter.m_KeyHi.i];
		Filter.m_KeyHi.i++;
	}

	return true;
};


bool CConcXml::CFreeBiblStringIndex::RegisterBiblStringItemId(const string& ValueStr)
{
	if (m_BuildStringItems.size() >= DWORD_MAX)
	{
		//-- v2.0.40: moo Mon, 07 Dec 2015 11:16:00 +0100 moocow: bail out here rather than creating a corrupt index
		fprintf(stderr, "Too many values for bibl field `%s'. Cannot be more than %u\n", m_Name.c_str(), DWORD_MAX);
		abort();
		return false;
	}
	if (ValueStr.length() > MaxBiblStringLen)
	{
		//-- v2.0.40: Mon, 07 Dec 2015 11:16:00 +0100 moocow: bail out here rather than creating a corrupt index
		fprintf(stderr, "Value for bibl field `%s' is too long (%zi bytes > max=%zi bytes)\n", m_Name.c_str(), ValueStr.length(), MaxBiblStringLen);
		abort(); 
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

		m_ValuesForEachFile.ensureVec();
		for (size_t i=0; i< m_ValuesForEachFile.size(); i++)
			m_ValuesForEachFile.m_vec[i] =  Old2New[m_ValuesForEachFile.m_vec[i]];
	}

	//-- save data (v2.1.12)
	string StringFileName = GetStringFileName(m_Path);
	string ValuesFile     = StringFileName + "_values";
	string IndexFile      = StringFileName + "_idx";
	
	FILE *vfp = fopen(ValuesFile.c_str(), "wb");
	if (!vfp)  {
		ddcLogError(Format("CConcXml::CFreeBiblStringIndex::ConvertAndSaveToDiskAfterIndexing(): open failed for '%s': %s",ValuesFile.c_str(), strerror(errno)));
		return false;
	}
	FILE *ifp = fopen(IndexFile.c_str(), "wb");
	if (!ifp)  {
		ddcLogError(Format("CConcXml::CFreeBiblStringIndex::ConvertAndSaveToDiskAfterIndexing(): open failed for '%s': %s",IndexFile.c_str(), strerror(errno)));
		return false;
	}

	const list<CStringItem>&  Set = m_BuildStringItems;
	fprintf(stderr, "Writing %zi items  to %s_*\n", Set.size(), StringFileName.c_str());

	bool rc = true;
	try {
		for (list<CStringItem>::const_iterator it = Set.begin(); it != Set.end(); it++) {
			const string& I           = it->m_BiblString;
			ddcStringEnum<>::OffT pos = ftell(vfp);
			
			if (fwrite(&pos, sizeof(ddcStringEnum<>::OffT), 1, ifp) != 1)
				throw runtime_error("failed to write offset data");
			if (fwrite(I.c_str(), 1, I.size()+1, vfp) != I.size()+1)
				throw runtime_error("failed to write string data");
		}
		CFreeBiblIndex::ConvertAndSaveToDiskAfterIndexing(m_Path);
		rc = true;
	}
	catch (exception &e) {
		fprintf(stderr, "CConcXml::CFreeBiblStringIndex::ConvertAndSaveToDiskAfterIndexing(): Exception: %s\n", e.what());
		rc = false;
	}
	catch (...) {
		fprintf(stderr, "CConcXml::CFreeBiblStringIndex::ConvertAndSaveToDiskAfterIndexing(): Exception: (unhandled exception)\n");
		rc = false;
	}

	fclose(vfp);
	fclose(ifp);
	return rc;
};


//=============================================

CConcXml::CFreeBiblStringConstant::CFreeBiblStringConstant(const string &value)
{
	setValue(value);
};

CConcXml::CFreeBiblStringConstant::~CFreeBiblStringConstant()
{
};

void CConcXml::CFreeBiblStringConstant::setValue(const string& value)
{
	clear();
	m_Value = value;
	m_ValuesE.ensureVec();
	m_ValuesE.m_strings.reserve(1);
	m_ValuesE.m_strings.push_back(m_Value);
}

void CConcXml::CFreeBiblStringConstant::clear()
{
	CFreeBiblStringIndex::clear();
	ClearString(m_Value);
};

string CConcXml::CFreeBiblStringConstant::GetTypeStr() const
{
	return StringConstantTypeStr;
};

CFreeBiblIndexTypeId CConcXml::CFreeBiblStringConstant::GetTypeId() const
{
	return cfbiStringConstant;
};

const string& CConcXml::CFreeBiblStringConstant::GetXpathStr() const
{
	return m_Value;
};


string CConcXml::CFreeBiblStringConstant::GetStringValue(DWORD FileNo) const
{
	return m_Value;
};

int CConcXml::CFreeBiblStringConstant::GetIntegerValue(DWORD FileNo ) const 
{
	return 0;
};

bool CConcXml::CFreeBiblStringConstant::ReadFromDisk(string Path, DWORD FileBreaksSize, bool useMMap) 
{
	return true;
};

bool CConcXml::CFreeBiblStringConstant::ConvertAndSaveToDiskAfterIndexing(string Path) 
{
	return true;
};

void CConcXml::CFreeBiblStringConstant::CreateUnion(const string& Path, const vector<const CFreeBiblIndex*>& Indices, const vector<size_t>& FileCounts)
{
	size_t i=0;
	bool gotValue = !m_Value.empty();
	for ( ; i < Indices.size(); ++i) {
		if (Indices[i] == NULL) continue;
		if (Indices[i]->GetTypeId() != cfbiStringConstant) {
			ddcLogWarn("CConcXml::CFreeBiblStringConstant::CreateUnion(): Warning: cannot merge variable field into bibl constant "+m_Name);
			continue;
		}
		CFreeBiblStringConstant* cfb = (CFreeBiblStringConstant*)Indices[i];
		if (!gotValue) {
			setValue(cfb->m_Value);
			gotValue = true;
		}
		else if (cfb->m_Value != m_Value) {
			ddcLogWarn("CConcXml::CFreeBiblStringConstant::CreateUnion(): Warning: cannot merge distinct constants \""+m_Value+"\" != \""+cfb->m_Value+"\" for attribute "+m_Name);
		}
	}
};

void CConcXml::CFreeBiblStringConstant::CreatePartitions(vector<CFreeBiblIndex*>& Parts, const vector<string>& Paths, const vector<DWORD>& EndFileNo) const
{
	ddcLogDebug("CConcXml::CFreeBiblStringConstant::CreatePartitions(): ignoring bibl string constant "+m_Name);
};


//=============================================
CConcXml::CConcXml()
{
	m_BiblBodyFile = 0;
	m_RegexOpts = RML_RE::Options(pcrecpp::UTF8(), NULL); //-- default
	m_bMemoryMap = false;
};

CConcXml::~CConcXml()
{
	if (m_BiblBodyFile) 
	{
		fclose(m_BiblBodyFile);
	}
	FreeBiblIndices();
	FreeBiblExpanders();
};

void CConcXml::FreeBiblIndices()
{
	for (FreeBiblStringMap::iterator it = m_FreeBiblIndices.begin(); it != m_FreeBiblIndices.end(); it++)
	{
		delete it->second;
	};
	m_FreeBiblIndices.clear();
};

void CConcXml::FreeBiblExpanders()
{
	for (BiblExpanderMap::iterator it = m_BiblExpanders.begin(); it != m_BiblExpanders.end(); it++) {
		if (it->second) delete it->second;
	}
	m_BiblExpanders.clear();
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

	m_EndOffsetsInBiblFile.m_vec.push_back(m_BiblBodyFileSize);

	{
		int Date;
		Bibliography.ConvertDateToInt(Date);
		m_Dates.m_vec.push_back(Date);
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
		if (!CheckXPath(TextArea.m_Xpath, ErrorStr)) {
			ErrorStr += " for TextArea XPath";
			return false;
		};

		
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
		bool   isConstant = false;
		bool   isAlias    = false;
		if ((TypeStr == StringTypeStr) || (TypeStr == IntegerTypeStr)) {
			isConstant = false;
		} else if (TypeStr == StringConstantTypeStr) {
			isConstant = true;
		} else if (TypeStr == StringAliasTypeStr) {
			isAlias = true;
		} else {
			ErrorStr = Format("Error! Bad type \"%s\" in free bibliographical filed type; known types are \"%s\", \"%s\", \"%s\", and \"%s\"", TypeStr.c_str(), IntegerTypeStr, StringTypeStr, StringConstantTypeStr, StringAliasTypeStr);
			return false;
		};


		bool bShowInHeader;
		if (!isAlias) {
			//-- reading show in header ("visibility" flag)
			if (!tok())  {
				ErrorStr = "Error! Bad syntax in free bibliographical attribute description : missing visibility flag";
				return false;
			}

			string ShowInHeaderStr = tok.val();
			if (ShowInHeaderStr == "0")
				bShowInHeader = false;
			else
				if (ShowInHeaderStr == "1")
					bShowInHeader = true;
				else {
					ErrorStr = "Error! the first column in a non-alias free bibliographical attribute description should be 0 or 1 (visibility flag)";
					return false;	
				}
		}

		// reading name
		if (!tok()) 		
		{
			ErrorStr = "Error! Bad syntax in free bibliographical attribute description: missing attribute name";
			return false;
		}

		string Name = tok.val();
		string Xpath;
		if (isConstant) {
			Xpath = tok.get_rest_trim(); //-- trim leading & trailing whitespace from constants
		} else if (tok()) {
			Xpath = tok.val();
		}

		// check xpath (or value for constants)
		if (!isConstant && !isAlias && !CheckXPath(Xpath, ErrorStr)) {
			//-- just warn about dodgy-looking XPaths (fatal error prior to v2.0.29)
			ErrorMessage( "WARNING", ErrorStr + Format(" for free bibliographical attribte `%s'", Name.c_str()) );
			//return false;
		}

		//-- check for aliases
		if (isAlias) {
			if (Xpath.empty()) {
				ErrorStr = Format("Error! Bad syntax in free bibliographical alias `%s': missing target attribute name", Name.c_str());
				return false;
			}
			if (m_FreeBiblIndices.find(Name) != m_FreeBiblIndices.end()) {
				//-- new alias clobbers old physical field
				FreeBiblStringMap::iterator oldi = m_FreeBiblIndices.find(Name);
				delete oldi->second;
				m_FreeBiblIndices.erase(oldi);
				ddcLogWarn(Format("Warning: bibliographic attribute alias `%s' -> `%s' overrides physical attribute `%s'",
						  Name.c_str(), Xpath.c_str(), Name.c_str()));
			}
			if (m_FreeBiblAlias.find(Name) != m_FreeBiblAlias.end()) {
				//-- new alias clobbers old alias
				ddcLogWarn(Format("Warning: multiple definitions for bibliographic alias `%s', using most recent", Name.c_str()));
			}
			
			m_FreeBiblAlias[Name] = Xpath;
			continue;
		}

		//-- hacks for built-in fields
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
			if ( m_FreeBiblIndices.find(Name) != m_FreeBiblIndices.end() )  {
				//-- just warn about duplicate bibl fields and use the most recent definitition
				//   (prior to v2.0.29, multiple bibl fields with the same name caused a fatal error)
				FreeBiblStringMap::iterator oldi = m_FreeBiblIndices.find(Name);
				delete oldi->second;
				m_FreeBiblIndices.erase(oldi);
				ddcLogWarn(Format("Warning: multiple definitions for free bibliographic attribute `%s', using most recent", Name.c_str()));
			}
			if ( m_FreeBiblAlias.find(Name) != m_FreeBiblAlias.end() ) {
				//-- just warn about clobbering an existng alias
				ddcLogWarn(Format("Warning: physical free bibliographic attribute `%s' overrides alias `%s' -> `%s'",
						  Name.c_str(), Name.c_str(), m_FreeBiblAlias[Name].c_str()));
				m_FreeBiblAlias.erase(Name);
			}
			
			CFreeBiblIndex* pIndex;
			if (TypeStr == StringTypeStr) {
				pIndex = new CFreeBiblStringIndex;
			}
			else if (TypeStr ==  StringConstantTypeStr) {
				pIndex = new CFreeBiblStringConstant(unescapeCString(Xpath));
				Xpath  = "/..";
			}
			else if (TypeStr == IntegerTypeStr) {
				pIndex = new CFreeBiblIndex;
			}
			else {
				ErrorStr = Format("Error! Unknown type \"%s\" in the options file!", TypeStr.c_str());
				return false;
			}
				
			pIndex->m_Name = Name;
			pIndex->m_Xpath = Xpath;
			pIndex->m_bShowInHeader = bShowInHeader;
			pIndex->m_pRegexOpts = &m_RegexOpts;
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
	for (FreeBiblAliasMap::const_iterator it = m_FreeBiblAlias.begin(); it != m_FreeBiblAlias.end(); it++)
	{
		Result += Format("Bibl alias %s %s\n", it->first.c_str(), it->second.c_str());
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

	m_EndOffsetsInBiblFile.ensureVec();
	if (!WriteVector(BiblIndexFileName, m_EndOffsetsInBiblFile.m_vec))
		return false;
	if (!FileExists(BiblIndexFileName.c_str()) )
	{
		fprintf (stderr,"Cannot create %s!\n", BiblIndexFileName.c_str());
		return false;
	};

	{
		string DatesFName = GetBiblDateIndexFileName();
		remove(DatesFName.c_str());
		m_Dates.ensureVec();
		if (!WriteVector(DatesFName, m_Dates.m_vec))
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


bool CConcXml::LoadBibl(string Path, size_t FileBreaksSize, bool useMMap)
{
	SetPath(Path);
	m_bMemoryMap = useMMap;

	// reading Bibliographical files if they exist
	if (m_BiblBodyFile) fclose (m_BiblBodyFile);
	m_BiblBodyFile = fopen(GetBiblFileName().c_str(), "rb");

	m_EndOffsetsInBiblFile.open(GetBiblIndexFileName(), useMMap);
	if (m_EndOffsetsInBiblFile.size() !=  FileBreaksSize)
	{
		string s = Format("The number of corpus files should be equal to the number of bibliographical records in file `%s'", GetBiblIndexFileName().c_str());
		s += Format("\nnumber of corpus files = %zi",FileBreaksSize);
		s += Format("\nnumber of bibliographical records = %zi",m_EndOffsetsInBiblFile.size());
		ErrorMessage (s);
		return false;
	};

	m_Dates.open(GetBiblDateIndexFileName(), useMMap);
	if (m_Dates.size() !=  FileBreaksSize)
	{
		ErrorMessage (Format ("Corrupt bibliograpical index file for dates (%s)", GetBiblDateIndexFileName().c_str()));
		return false;
	};

	for (FreeBiblStringMap::iterator bibl_it = m_FreeBiblIndices.begin(); bibl_it != m_FreeBiblIndices.end(); bibl_it++)
		if (!bibl_it->second->ReadFromDisk(m_Path, FileBreaksSize, useMMap))
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

		lock();
		try {
			if (!FSeek(m_BiblBodyFile, StartBiblFileOffset, SEEK_SET))  {
				unlock();
				delete[] buffer;
				return  CBibliography();
			}
			if ( fread(buffer, 1, BiblLength, m_BiblBodyFile) != BiblLength) {
				unlock();
				delete[] buffer;
				return  CBibliography();
			}
		}
		catch (...) {
			unlock();
			throw;
		}

		unlock();
		buffer[BiblLength] = 0;
		FileContent = buffer;
		delete[] buffer;
	}
	
	CBibliography B;
	B.ReadFromString(FileContent);
	return B;
};


bool  CConcXml::CheckBibl(size_t FileBreaksNumber) const 
{
	printf ("Test %zi bibl. references...\n", m_EndOffsetsInBiblFile.size());
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



bool CConcXml::UnionBibliographies(const vector<const CConcXml*>& Bibls)
{
	string logname("CConcXml::UnionBibliographies()");

	//-- populate: m_EndOffsetsInBiblFile (*._bibl_idx)
	ddcLogInfo(logname+": populating "+GetBiblIndexFileName());
	m_EndOffsetsInBiblFile.clear();
	m_EndOffsetsInBiblFile.ensureVec();
	file_off_t boffset = 0;
	size_t     eobfi   = 0;
	for (size_t bi=0; bi < Bibls.size(); ++bi) {
		m_EndOffsetsInBiblFile.m_vec.insert(m_EndOffsetsInBiblFile.m_vec.end(), Bibls[bi]->m_EndOffsetsInBiblFile.begin(), Bibls[bi]->m_EndOffsetsInBiblFile.end());
		for ( ; eobfi < m_EndOffsetsInBiblFile.m_vec.size(); ++eobfi)
			m_EndOffsetsInBiblFile.m_vec[eobfi] += boffset;
		if (!m_EndOffsetsInBiblFile.m_vec.empty())
			boffset = m_EndOffsetsInBiblFile.m_vec.back();
	}
	m_EndOffsetsInBiblFile.ensureData();
	m_EndOffsetsInBiblFile.save(GetBiblIndexFileName());

	//-- populate: bibl file (*._bibl)
	ddcLogInfo(logname+": populating "+GetBiblFileName());
	if (FileExists(GetBiblFileName())) remove(GetBiblFileName().c_str());
	for (size_t bi=0; bi < Bibls.size(); ++bi) {
		if (FileExists(Bibls[bi]->GetBiblFileName()))
			FileAppend(Bibls[bi]->GetBiblFileName(), GetBiblFileName());
	}

	//-- sanity check: *._bibl <-> *._bibl_idx
	if (FileExists(GetBiblFileName()) && FileSize(GetBiblFileName()) != boffset)
		throw CExpc(Format("%s: Error: bibl index size mismatch (*._bibl_idx ~ %zd != %zd ~ *._bibl)",
				   logname.c_str(), (size_t)boffset, FileSize(GetBiblFileName())));

	//-- populate: *._bibl_date
	ddcLogInfo(logname+": populating "+GetBiblDateIndexFileName());
	m_Dates.clear();
	m_Dates.ensureVec();
	for (size_t bi=0; bi < Bibls.size(); ++bi) {
		m_Dates.m_vec.insert(m_Dates.m_vec.end(), Bibls[bi]->m_Dates.begin(), Bibls[bi]->m_Dates.end());
	}
	m_Dates.save(GetBiblDateIndexFileName());

	//-- populate: free bibl attributes
	vector<size_t> FileCounts(Bibls.size());
	for (size_t bi=0; bi < Bibls.size(); ++bi)
		FileCounts[bi] = Bibls[bi]->m_Dates.size();
	for (FreeBiblStringMap::iterator fbi=m_FreeBiblIndices.begin(); fbi!=m_FreeBiblIndices.end(); ++fbi) {
		const string&  name = fbi->first;
		CFreeBiblIndex *fbx = fbi->second;
		ddcLogInfo(logname+": populating free bibl index "+name);

		//-- get sub-indices
		vector<const CFreeBiblIndex*> bixs(Bibls.size());
		for (size_t bi=0; bi < Bibls.size(); ++bi) {
			bixs[bi] = Bibls[bi]->GetFreeBiblIndex(name);
			if (bixs[bi] == NULL)
				ddcLogWarn(logname+": Warning: no free bibl index '"+name+"' in sub-project '"+Bibls[bi]->m_Path+"' - using default values");
		}
		fbx->CreateUnion(m_Path, bixs, FileCounts);
	}
	
	
	return true;
};

bool CConcXml::SplitBibliography(vector<CConcXml*>& Bibls, const vector<DWORD>& EndFileNo) const
{
	string logname("CConcXml::SplitBibliography()");
	assert(Bibls.size() == EndFileNo.size());

	//-- split: m_EndOffsetsInBiblFile (*._bibl_idx)
	ddcLogInfo(logname+": splitting "+GetBiblIndexFileName());
	file_off_t boffset = 0;
	for (size_t i=0; i < Bibls.size(); ++i) {
		Bibls[i]->m_EndOffsetsInBiblFile.clear();
		Bibls[i]->m_EndOffsetsInBiblFile.ensureVec();
		Bibls[i]->m_EndOffsetsInBiblFile.m_vec.insert(Bibls[i]->m_EndOffsetsInBiblFile.m_vec.end(),
							      m_EndOffsetsInBiblFile.begin()+(i==0 ? 0 : EndFileNo[i-1]),
							      m_EndOffsetsInBiblFile.begin()+EndFileNo[i]);
		for (vector<file_off_t>::iterator foi=Bibls[i]->m_EndOffsetsInBiblFile.m_vec.begin(); foi!=Bibls[i]->m_EndOffsetsInBiblFile.m_vec.end(); ++foi)
			*foi -= boffset;

		ddcLogTrace(logname+": saving "+Bibls[i]->GetBiblIndexFileName());
		Bibls[i]->m_EndOffsetsInBiblFile.ensureData();
		Bibls[i]->m_EndOffsetsInBiblFile.save(Bibls[i]->GetBiblIndexFileName());

		boffset = m_EndOffsetsInBiblFile[ EndFileNo[i]-1 ];
	}

	//-- split: bibl file (*._bibl)
	ddcLogInfo(logname+": splitting "+GetBiblFileName());
	for (size_t i=0; i < Bibls.size(); ++i) {
		file_off_t bf_begin = (i==0 ? 0 : m_EndOffsetsInBiblFile[ EndFileNo[i-1]-1 ]);
		file_off_t bf_end   = m_EndOffsetsInBiblFile[ EndFileNo[i]-1 ];

		FILE *bf_out = fopen(Bibls[i]->GetBiblFileName().c_str(), "wb");
		if (bf_out == NULL)
			throw CExpc(Format("%s: Error: open failed for partition #%zd bibl file: %s", logname.c_str(), i, strerror(errno)));
		if (!FSeek(m_BiblBodyFile, bf_begin, SEEK_SET))
			throw CExpc(Format("%s: Error: seek failed for %s to position %zd", GetBiblFileName().c_str(), (size_t)bf_begin));

		FileAppendPartial(m_BiblBodyFile, bf_out, bf_end-bf_begin);
		if (fclose(bf_out) != 0)
			throw CExpc(Format("%s: Error: close failed for partition #%zd bibl file: %s", logname.c_str(), i, strerror(errno)));

		//-- sanity check: *._bibl <-> *._bibl_idx
		if (FileSize(Bibls[i]->GetBiblFileName()) != Bibls[i]->m_EndOffsetsInBiblFile.m_vec.back())
			throw CExpc(Format("%s: Error: bibl index size mismatch for patition #%zd (*._bibl_idx ~ %zd != %zd ~ *._bibl)",
					   logname.c_str(), i,
					   (size_t)Bibls[i]->m_EndOffsetsInBiblFile.m_vec.back(),
					   (size_t)FileSize(Bibls[i]->GetBiblFileName())));
	}

	//-- populate: *._bibl_date
	ddcLogInfo(logname+": splitting "+GetBiblDateIndexFileName());
	for (size_t i=0; i < Bibls.size(); ++i) {
		Bibls[i]->m_Dates.clear();
		Bibls[i]->m_Dates.ensureVec();
		Bibls[i]->m_Dates.m_vec.insert(Bibls[i]->m_Dates.m_vec.end(),
					       m_Dates.begin()+(i==0 ? 0 : EndFileNo[i-1]),
					       m_Dates.begin()+EndFileNo[i]);
		Bibls[i]->m_Dates.ensureData();
		Bibls[i]->m_Dates.save(Bibls[i]->GetBiblDateIndexFileName());
	}

	//-- populate: free bibl attributes
	for (FreeBiblStringMap::const_iterator fbi=m_FreeBiblIndices.begin(); fbi!=m_FreeBiblIndices.end(); ++fbi) {
		const string&        name = fbi->first;
		const CFreeBiblIndex *fbx = fbi->second;

		vector<CFreeBiblIndex*> parts(Bibls.size());
		vector<string>          paths(Bibls.size());
		bool canSplitBibl = true;
		for (size_t i=0; i < Bibls.size(); ++i) {
			if ((parts[i] = Bibls[i]->GetFreeBiblIndex(name)) == NULL) {
				ddcLogWarn(Format("%s: Warning: no free bibl index '%s' in partition #%zd - skipping", logname.c_str(), name.c_str(), i));
				canSplitBibl = false;
				break;
			}
			paths[i] = Bibls[i]->m_Path;
		}
		if (canSplitBibl) {
			ddcLogInfo(logname+": splitting free bibl index "+name);
			fbx->CreatePartitions(parts, paths, EndFileNo);
		}
	}

	//-- all done
	return true;
};

void CConcXml::InitNoSort(vector<CHit>&	Hits) const
{
	size_t HitsCount = Hits.size();
	for (size_t HitNo=0; HitNo< HitsCount; HitNo++)
	{
		CHit&  H = Hits[HitNo];
		H.m_SortKey = HitNo;
	}
}

void CConcXml::InitSortByDate(vector<CHit>&	Hits) const
{
	size_t HitsCount = Hits.size();
	for (size_t HitNo=0; HitNo< HitsCount; HitNo++)
	{
		CHit&  H = Hits[HitNo];
		H.m_SortKey = m_Dates.empty() ? 0 : m_Dates[H.m_FileNo];
	}
}

void CConcXml::InitSortByBiblIntegerField(string FreeBiblAttribNameOrAlias, vector<CHit>&	Hits) const
{
	const CFreeBiblIndex* pFreeAttrib = 0;	

	if (!FreeBiblAttribNameOrAlias.empty())
		pFreeAttrib = GetFreeBiblIndex(FreeBiblAttribNameOrAlias);
	if (pFreeAttrib == NULL)
		return InitNoSort(Hits);	
	
	size_t HitsCount = Hits.size();
	for (size_t HitNo=0; HitNo < HitsCount; HitNo++)
	{
		CHit&  H = Hits[HitNo];
		H.m_SortKey.assign(pFreeAttrib->GetIntegerValue(H.m_FileNo), pFreeAttrib->GetStringValue(H.m_FileNo)); //-- moo: maybe we can avoid string-copying here?
	}
}

void CConcXml::SetRegexOptions(const RML_RE::Options &opts)
{
	m_RegexOpts = opts;
	for (FreeBiblStringMap::iterator mi=m_FreeBiblIndices.begin(); mi!=m_FreeBiblIndices.end(); mi++) {
		mi->second->m_pRegexOpts = &m_RegexOpts;
	}
}

bool CConcXml::FileMatches(DWORD FileNo, const vector<CDDCFilterWithBounds>& Filters) const
{
	for (vector<CDDCFilterWithBounds>::const_iterator fi=Filters.begin(); fi != Filters.end(); ++fi) {
		CFreeBiblIndex *fbi = (CFreeBiblIndex*)(fi->m_BiblIndex);
		if (fbi && !fbi->FileMatches(FileNo, *fi)) {
			//-- free bibl filter is tested with CFreeBiblIndex::FileMatches()
			return false;
		}
		else if (!fbi && (fi->m_FilterType==LessByDate || fi->m_FilterType==GreaterByDate)) {
			//-- date filter is tested manually...
			// + 2019-08-15 moocow
			//   - fdate: cast to int so it jives with CHitSortKey::i (avoid signed/unsigned comparison)
			//   - should fixes bogus empty responses from e.g. "count(* #asc_date) #by[textClass]"
			int fdate = m_Dates[FileNo];
			if (fdate < fi->m_KeyLo.i || fdate > fi->m_KeyHi.i)
				return false;
		}
		else {
			; //-- other filter tyes are ignored
		}
	}
	return true;
}

CBiblExpander* CConcXml::AddBiblExpander(const string &spec)
{
	const char *delims = " \t\r\n";
	StringTokenizer stok(spec.c_str(), delims);
	string s_label(""), s_target(""), s_cls(""), s_param("");
	CBiblExpander *bx = NULL;;

	if (stok.has_next()) s_label  = stok.next_token();
	if (stok.has_next()) s_target = stok.next_token();
	if (stok.has_next()) s_cls    = stok.next_token();
	if (stok.has_next()) s_param  = stok.get_rest();

	//-- parse spec
	string cls(s_cls);
	Trim(cls);
	EngMakeLower(cls);
	if (cls.empty()) {
		throw CExpc(errLogic, "unknown BiblExpander class `%s'", s_cls.c_str());
	}
	else {
		//-- default: BxTermWrapper
		bx = new BxTermWrapper(s_label, s_target, s_cls + " " + s_param);

		//-- check for chains (not yet implemented)
		CTermExpander *tx = ((BxTermWrapper*)bx)->m_BxTx;
		if (tx && tx->m_Class == "Chain")
			throw CExpc(errLogic, "chained bibliographic expanders not yet supported for `%s'", s_label.c_str());
	}

	//-- sanity check(s)
	if (bx==NULL)
		throw CExpc(errRuntime, "could not create BiblExpander of class `%s'", s_cls.c_str());

	//-- check for existing expander
	BiblExpanderMap::iterator bi = m_BiblExpanders.find(s_label);
	if (bi != m_BiblExpanders.end()) {
		if (bi->second != NULL) delete bi->second;
		m_BiblExpanders.erase(bi);
	}

	//-- insert new expander
	m_BiblExpanders[s_label] = bx;

	return bx;
};

bool CConcXml::IsRegisteredBiblField(const string& FreeBiblAttribNameOrAlias) const
{
	return !FreeBiblAttribNameOrAlias.empty() && GetFreeBiblIndex(FreeBiblAttribNameOrAlias) != NULL;
}

CFreeBiblIndexTypeId CConcXml::GetBiblFieldTypeId(const string& FreeBiblAttribName) const
{
	const CFreeBiblIndex *fbi = FreeBiblAttribName.empty() ? NULL : GetFreeBiblIndex(FreeBiblAttribName);
	if (!fbi) return cfbiUnknown; //-- attribute not found
	return fbi->GetTypeId();
}

bool CConcXml::GetFilterBounds(CDDCFilterWithBounds& Filter, const string& LoValue, const string& HiValue) const
{
	Filter.clear();
	//-- filter bounds: require physically indexed bibliographic field
	const CFreeBiblIndex *fbi = GetFreeBiblIndex(Filter.m_AttrName);
	if (!fbi) return false; //-- attribute not found
	return fbi->GetFilterBounds(Filter, LoValue, HiValue);
}

bool CConcXml::GetFilterValue(CDDCFilterWithBounds& Filter, const string& Value) const
{
	Filter.clear();

	//-- bibliographic expander clobbers any indexed field with the same name
	BiblExpanderMap::const_iterator xit = m_BiblExpanders.find(Filter.m_AttrName);
	if (xit != m_BiblExpanders.end()) {
		set<string> xvalues;
		xit->second->expand(Value, xvalues);

		Filter.m_AttrName = xit->second->m_BxTarget;
		return GetFilterValues(Filter, xvalues);
	}
	
	//-- usual case: physically indexed bibliographic field or alias
	const CFreeBiblIndex* fbi = GetFreeBiblIndex(Filter.m_AttrName);
	if (!fbi) return false; //-- attribute not found
	return fbi->GetFilterValue(Filter, Value);
};

//-- initialize CDDCFilterWithBounds for a target regex
bool CConcXml::GetFilterValues(CDDCFilterWithBounds& Filter, const string &Regex) const
{
	Filter.clear();
	const CFreeBiblIndex* fbi = GetFreeBiblIndex(Filter.m_AttrName);
	if (!fbi) return false; //-- attribute not found
	return fbi->GetFilterValues(Filter, Regex);;
};

//-- initialize CDDCFilterWithBounds for a set of target values
bool CConcXml::GetFilterValues(CDDCFilterWithBounds& Filter, const set<string>& Values) const
{
	Filter.clear();

	//-- bibliographic expander clobbers any indexed field with the same name
	BiblExpanderMap::const_iterator xit = m_BiblExpanders.find(Filter.m_AttrName);
	if (xit != m_BiblExpanders.end()) {
		set<string> xvalues;
		xit->second->expand(Values, xvalues);

		Filter.m_AttrName = xit->second->m_BxTarget;
		return GetFilterValues(Filter, xvalues);
	}

	//-- usual case: physically indexed bibliographic field
	const CFreeBiblIndex* fbi = GetFreeBiblIndex(Filter.m_AttrName);
	if (!fbi) return false; //-- attribute not found
	return fbi->GetFilterValues(Filter, Values);;
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
				strError = Format("Bad date format (\"%s\")", Bibl.m_DateStr.c_str());
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
						fprintf(stderr, "empty word after word WordNo=%zi WordStr=%s\n", AllWordsCount, LastReadWord.c_str());
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

string CConcXml::GetFreeHeaderBiblAttributesJson(size_t FileNo, bool assume_utf8, bool include_invisible) const
{
    string js("");
    for (FreeBiblStringMap::const_iterator bibl_it = m_FreeBiblIndices.begin(); bibl_it != m_FreeBiblIndices.end(); bibl_it++) {
	CFreeBiblIndex* I = bibl_it->second;
	if (include_invisible || I->m_bShowInHeader) {
	    if (!js.empty()) js.push_back(',');
	    js.append(jsonStr(I->m_Name, assume_utf8));
	    js.push_back(':');
	    js.append(jsonStr(I->GetStringValue(FileNo), assume_utf8));
	}
    }
    return js;
}

string CConcXml::GetFreeHeaderBiblAttributesTabsDump(size_t FileNo, bool assume_utf8, bool include_invisible) const
{
    string ts("");
    string prefix("%%$DDC:meta.");
    for (FreeBiblStringMap::const_iterator bibl_it = m_FreeBiblIndices.begin(); bibl_it != m_FreeBiblIndices.end(); bibl_it++) {
	CFreeBiblIndex* I = bibl_it->second;
	if (include_invisible || I->m_bShowInHeader) {
		ts.append(prefix);
		ts.append(jsonStr(I->m_Name, assume_utf8, false));
		ts.push_back('=');
		ts.append(jsonStr(I->GetStringValue(FileNo), assume_utf8, false));
		ts.push_back('\n');
	}
    }
    return ts;
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

#define MAX_ALIAS_REDIR 100
CConcXml::CFreeBiblIndex* CConcXml::GetFreeBiblIndex(const string& FreeBiblAttribNameOrAlias) const
{
	string name(FreeBiblAttribNameOrAlias);
	FreeBiblAliasMap::const_iterator ai=m_FreeBiblAlias.find(name);
	for (size_t n=0; ai != m_FreeBiblAlias.end(); ++n, ai=m_FreeBiblAlias.find(name)) {
		if (n >= MAX_ALIAS_REDIR)
			throw(CExpc(errRuntime, "too many alias redirections (%zi) for metadata label `%s'", n, FreeBiblAttribNameOrAlias.c_str()));
		name = ai->second;
	}
	
	FreeBiblStringMap::const_iterator bi = m_FreeBiblIndices.find(name);
	if (bi == m_FreeBiblIndices.end()) return NULL; // attribute not found
	return bi->second;
}

CBiblExpander*  CConcXml::GetBiblExpander(const string& ExpanderName) const
{
	BiblExpanderMap::const_iterator xit = m_BiblExpanders.find(ExpanderName);
	if (xit == m_BiblExpanders.end()) return NULL; // expander not found
	return xit->second;
}
