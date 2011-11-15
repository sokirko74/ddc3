//-*- Mode: C++; c-basic-offset: 8; -*-
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
#include "StdConc.h"
#include "HitBorder.h"
#include "../common/bserialize.h"


inline size_t get_size_in_bytes (const CPageNumber& t)
{
	return sizeof(t.m_StartTokenNo) + sizeof(t.m_PageNumber);
};


inline size_t save_to_bytes(const CPageNumber& i, BYTE* buf)
{
	buf += save_to_bytes(i.m_StartTokenNo, buf);
	buf += save_to_bytes(i.m_PageNumber, buf);
	return get_size_in_bytes(i);
}

inline size_t restore_from_bytes(CPageNumber& i, const BYTE* buf)
{
	buf += restore_from_bytes(i.m_StartTokenNo, buf);
	buf += restore_from_bytes(i.m_PageNumber, buf);
	return get_size_in_bytes(i);
}


CHitBorders::CBreakCollection::CBreakCollection (const string& ShortName, const string& LongName)
{
	m_ShortName = ShortName;
	m_LongName = LongName;
	m_FileForIndexing = 0;
};


string CHitBorders::CBreakCollection::GetBreakFileName(string Path) const 
{
	return MakeFName(Path,Format("_%s_border", m_ShortName.c_str()));
};

void CHitBorders::CBreakCollection::ReadFromDisk(string Path)
{
	string FileName = GetBreakFileName(Path);
	ReadVector(FileName.c_str(), m_BreakOffsets);
}

bool CHitBorders::CBreakCollection::ClearAll(string Path)
{
	m_BreakOffsets.clear();

	string FileName = GetBreakFileName(Path);
	if (FileExists(FileName.c_str()))
		if (remove(FileName.c_str()))
			return false;
	return true;
}

void CHitBorders::CBreakCollection::CloseFileForIndexing()
{
	if (m_FileForIndexing) fclose (m_FileForIndexing);
	m_FileForIndexing = 0;
}

CHitBorders::CHitBorders()
{
	m_FileBreakCollectionNo = -1;	
};

const vector<CTokenNo>* CHitBorders::GetBreaksByName(const string& ShortName) const
{
	map<string,int>::const_iterator it = m_ShortName2BreakCollection.find(ShortName);
	if (it == m_ShortName2BreakCollection.end())
		return 0;
	else
		return &(m_Breaks[it->second].m_BreakOffsets);
};

string CHitBorders::GetPageBreaksFileName(string Path) const 
{
	return MakeFName(Path,"_pagebreaks");
};

bool	CHitBorders::IsRegisteredBreak(const string& ShortName) const
{
	return m_ShortName2BreakCollection.find(ShortName) !=  m_ShortName2BreakCollection.end();
};


string CHitBorders::GetShortNameByName(const string& BreakName) const
{
	for (size_t i=0; i <  m_Breaks.size(); i++)
	{
		if	(		(m_Breaks[i].m_ShortName == BreakName)
				||	(m_Breaks[i].m_LongName == BreakName)
			)
		{
			return m_Breaks[i].m_ShortName;
		};
	};
	return "";
};


const vector<CTokenNo>&  CHitBorders::GetFileBreaks() const
{
	return m_Breaks[m_FileBreakCollectionNo].m_BreakOffsets;
};

CTokenNo	CHitBorders::GetCorpusEndTokenNo() const 	
{
	if (m_FileBreakCollectionNo==-1)
		return 0;
	const vector<CTokenNo>& FileBreaks = GetFileBreaks();
	if (FileBreaks.empty()) 
		return 0;
	return FileBreaks.back();
};

CTokenNo CHitBorders::GetFileStartTokenNo(size_t i) const
{
	assert (m_FileBreakCollectionNo != -1);

	if (m_FileBreakCollectionNo==-1)
		return 0;

	const vector<CTokenNo>& FileBreaks = GetFileBreaks();
	if (FileBreaks.empty()) 
		return 0;

	if ( i == 0) 
		return 0;
	else
		return FileBreaks[i-1];
};


DWORD	CHitBorders::GetPageNumber(size_t No) const
{
	if (m_PageBreaks.empty()) 
		return UnknownPageNumber;
	else
		return m_PageBreaks[No].m_PageNumber;
};


bool	CHitBorders::StartIndexing(string Path)
{
	for (size_t i=0; i <  m_Breaks.size(); i++)
	{
		CBreakCollection& C = m_Breaks[i];
		string FileName = C.GetBreakFileName(Path);
		C.m_FileForIndexing = fopen (FileName.c_str(),"wb");
		if (!C.m_FileForIndexing)
		{
			ErrorMessage (Format("Cannot create %s for indexing\n", FileName.c_str()));
			for (size_t j=0; j <  m_Breaks.size(); j++)
				if (m_Breaks[j].m_FileForIndexing)
					m_Breaks[j].CloseFileForIndexing();
			return false;
		};
	};
	
	m_PageBreaks.clear();
	return true;
};

bool	CHitBorders::BordersEndIndexing(string Path)
{
	for (size_t i=0; i <  m_Breaks.size(); i++)
		m_Breaks[i].CloseFileForIndexing();

	if (!WriteVector(GetPageBreaksFileName(Path), m_PageBreaks))
		return false;

	return true;
};

bool	CHitBorders::LoadHitBorders(string Path)
{
	m_PageBreaks.clear();
	ReadVector(GetPageBreaksFileName(Path).c_str(), m_PageBreaks);

	for (size_t i=0; i <  m_Breaks.size(); i++)
		m_Breaks[i].ReadFromDisk(Path);

	return true;
};

bool	CHitBorders::RemoveHitBordersFileAndClear(string Path)
{
	if (FileExists(GetPageBreaksFileName(Path).c_str()))
		if (remove(GetPageBreaksFileName(Path).c_str() ))
			return false;

	m_PageBreaks.clear();

	for (size_t i=0; i <  m_Breaks.size(); i++)
		m_Breaks[i].ClearAll(Path);

	return true;
};

void CHitBorders::StartTextAreaBorders()
{
	m_LastTextAreaBreaks.resize(m_Breaks.size(), DWORD_MAX);
}

bool CHitBorders::EndTextAreaBorders(DWORD TextAreaEndTokenNo)
{
	for (size_t i=0; i < m_LastTextAreaBreaks.size(); i++)
		if (m_FileBreakCollectionNo != i)
			if ( (m_LastTextAreaBreaks[i] == DWORD_MAX) || ( m_LastTextAreaBreaks[i] < TextAreaEndTokenNo))
				if (!AddBreakByIndex(i, TextAreaEndTokenNo))
					return false;
	return true;
}

bool CHitBorders::AddBreakByIndex(DWORD BreakCollectionNo, const CTokenNo& B)
{
	CBreakCollection& C = m_Breaks[BreakCollectionNo];
	BYTE TextBreakBuffer[sizeof(CTokenNo)];
	if (fwrite(TextBreakBuffer, save_to_bytes(B, TextBreakBuffer), 1, C.m_FileForIndexing) != 1) return false;
	m_LastTextAreaBreaks[BreakCollectionNo] = B;
	return true;
};

bool CHitBorders::AddBreakByName(const string& ShortName, const CTokenNo& B)
{
	map<string,int>::iterator it = m_ShortName2BreakCollection.find(ShortName);
	if (it == m_ShortName2BreakCollection.end())
		return false;
	return AddBreakByIndex(it->second, B);
};

void CHitBorders::AddPageBreak(const CPageNumber& P)
{
	if	(		!m_PageBreaks.empty()
			&&	(P.m_PageNumber != UnknownPageNumber)
			&&	(P.m_StartTokenNo == m_PageBreaks.back().m_StartTokenNo)
		)
		m_PageBreaks.back() = P;
	else
		m_PageBreaks.push_back(P);

};




struct LessPageBreak {

	bool operator () (const CPageNumber& X,  const CTokenNo& StartTokenNo) const
	{
		return X.m_StartTokenNo < StartTokenNo;
	};
	bool operator () (const CTokenNo& StartTokenNo, const CPageNumber& X)  const
	{
		return StartTokenNo < X.m_StartTokenNo;
	};
	bool operator () (const CPageNumber& X1, const CPageNumber& X2)  const
	{
		return X1.m_StartTokenNo < X2.m_StartTokenNo;
	};

};

// for each hit calculate a page number, at which it starts. (a hit can divided by a page break)
// 
void CHitBorders::ConvertHitsToPageBreaks (
			vector<CHit>::const_iterator hits_begin, 
			vector<CHit>::const_iterator hits_end, 
			const vector<CTokenNo>& Breaks, 
			DwordVector& PageBreaks)	const
{
	PageBreaks.resize( hits_end - hits_begin );

	vector<CPageNumber>::const_iterator start_it = m_PageBreaks.begin();
	DwordVector::iterator PageBreakIt = PageBreaks.begin();
	
	for (vector<CHit>::const_iterator hit_it = hits_begin;  hit_it != hits_end; hit_it++, PageBreakIt++)
	{

		// StartTokenNo  is the start token number of hit Breaks[hits[i]].m_EndTokenNo
		CTokenNo StartTokenNo = 0;

		if (hit_it->m_BreakNo > 0)
		{
			StartTokenNo = Breaks[hit_it->m_BreakNo - 1];
		};
		
		// it is the page which is the next to the page that contains the hit; it can be  m_PageBreaks.end()
		vector<CPageNumber>::const_iterator it = lower_bound (start_it, m_PageBreaks.end(), StartTokenNo, LessPageBreak());

		// for each file there should be at least one page break (the first one)	
		*PageBreakIt = (it - m_PageBreaks.begin()) - 1;

		if	(			(it != m_PageBreaks.end())
					&&	(it->m_StartTokenNo ==  StartTokenNo)
			)
		(*PageBreakIt)++;
		
		// start_it = it; uncomment it if hits are sorted
	};

};


bool CHitBorders::RegisterBreak(string ShortName, string LongName)
{
	CBreakCollection T (ShortName, LongName);
	
	pair<map<string,int>::iterator, bool> it = m_ShortName2BreakCollection.insert(make_pair(T.m_ShortName,m_Breaks.size()));
	if (!it.second)
	{
		ErrorMessage ("Error! A duplicate hit type name is found: "+T.m_LongName);
		return false;
	};
	m_Breaks.push_back(T);
	m_LastTextAreaBreaks.push_back(DWORD_MAX);
	return true;
}

bool CHitBorders::RegisterBorderIndices(const char* IndicesStr)
{
	m_Breaks.clear();
	m_LastTextAreaBreaks.clear();
	m_ShortName2BreakCollection.clear();
	m_DefaultBreakName = "";
	if (IndicesStr)
	{
		StringTokenizer tok(IndicesStr,";");
		while (tok())
		{
			string Item = tok.val();
			Trim(Item);
			if ((Item.empty())  || (Item[0] != '[') || (Item[Item.length()-1] != ']'))
			{
				ErrorMessage (Format("Error! A bad format of the hit type definition (%s)!",IndicesStr));
				return false;
			};
			Item = Item.substr(1, Item.length() - 2);
			StringTokenizer item_tok(Item.c_str(), ":");
			string ShortName = item_tok.next_token(); 
			if (ShortName == PredefinedTableLineTag)
			{
				ErrorMessage ("Error! Using of the predefined hit type \"l\" is prohibited");
				return false;
			};
			

			if (ShortName.empty())
			{
				ErrorMessage ("Am empty short name in the hit type definition: "+Item);
				return false;
			};
			if (!RegisterBreak(ShortName, item_tok.next_token()))
				return false;
			if (item_tok.next_token() == "default")
				m_DefaultBreakName = ShortName;
		};
	};

	// register file break collection
	if (!RegisterBreak(PredefinedFileBreakName, PredefinedFileBreakName))
			return false;
	m_FileBreakCollectionNo = m_Breaks.size() - 1;
	

	// set default break collection, if it is not set in the options file
	if (m_DefaultBreakName.empty())
		m_DefaultBreakName = m_Breaks[0].m_ShortName;

	// register text area collection
	if (!RegisterBreak(PredefinedTextAreaBreakName, PredefinedTextAreaBreakName))
			return false;
	
	return !m_Breaks.empty();
};


bool	UnionBreaks	(const vector<CTokenNo>& V1, 
					const vector<CTokenNo>& V2, 
					DWORD EndTokenNo1,
					vector<CTokenNo>& Result)
{
	if (V1.empty() != V2.empty()) return false;
	if (V1.empty()) return false;
	Result = V1;
	Result.insert(Result.end(), V2.begin(),V2.end());
	
	// adding delta to index
	for (size_t i = V1.size(); i < Result.size(); i++)
	{
		Result[i] += EndTokenNo1;
	};
	return true;
};


bool CHitBorders::UniteBorders(const CHitBorders& H1, const CHitBorders& H2, const DWORD EndTokenNo1, const string& Path)
{
	assert(H1.GetBorderIndicesString() ==  H2.GetBorderIndicesString());
	if (H1.GetBorderIndicesString() !=  H2.GetBorderIndicesString())
		return false;
	assert (H1.m_Breaks.size() == H2.m_Breaks.size());

	if (H1.GetFileBreaks().empty() ) return false;
	
	m_Breaks.clear();
	m_LastTextAreaBreaks.clear();
	m_ShortName2BreakCollection.clear();
	m_FileBreakCollectionNo = -1;

	for (size_t i=0; i < H1.m_Breaks.size(); i++)
	{
		string ShortName = H1.m_Breaks[i].m_ShortName;
		const vector<CTokenNo>* Breaks2 = H2.GetBreaksByName(ShortName);
		if (Breaks2 == 0)
		{
			fprintf (stderr, "cannot find \"%s\" break collection in the second index\n", ShortName.c_str() );
			return false;
		}

		RegisterBreak(ShortName,  H1.m_Breaks[i].m_LongName);
		
		CBreakCollection& Result = m_Breaks.back();
		
		if (!UnionBreaks(H1.m_Breaks[i].m_BreakOffsets, *Breaks2, EndTokenNo1, Result.m_BreakOffsets))
			return false;

		string FileName = Result.GetBreakFileName(Path);
		if (!WriteVector(FileName.c_str(), Result.m_BreakOffsets))
			return false;
		if (PredefinedFileBreakName == Result.m_ShortName)
			m_FileBreakCollectionNo = m_Breaks.size() - 1;
	};
	
	if (m_FileBreakCollectionNo == -1) 
	{
		fprintf (stderr, "cannot find predefined \"%s\" break collection\n", PredefinedFileBreakName.c_str() );
		return false;
	};

	{	//uniting page \ref break_def "breaks"
		m_PageBreaks = H1.m_PageBreaks;
		m_PageBreaks.insert(m_PageBreaks.end(), H2.m_PageBreaks.begin(),H2.m_PageBreaks.end());
		
		for (size_t  i = H1.m_PageBreaks.size(); i < m_PageBreaks.size(); i++)
			m_PageBreaks[i].m_StartTokenNo += EndTokenNo1;

		if (!WriteVector(GetPageBreaksFileName(Path).c_str(), m_PageBreaks))
			return false;
	};

	m_DefaultBreakName = H1.m_DefaultBreakName;

	return true;
};

// order breaks by short names
string CHitBorders::GetBorderIndicesString() const
{
	string Result;
	for (map<string,int>::const_iterator it = m_ShortName2BreakCollection.begin(); it !=  m_ShortName2BreakCollection.end(); it++)
	{
		const CBreakCollection& B = m_Breaks[it->second];
		if (B.m_ShortName != PredefinedFileBreakName)
			if (B.m_ShortName == m_DefaultBreakName)
				Result += Format("[%s:%s:default];",B.m_ShortName.c_str(), B.m_LongName.c_str() );
			else
				Result += Format("[%s:%s];",        B.m_ShortName.c_str(), B.m_LongName.c_str() );
	};
	Trim(Result);
	return Result;
};

vector<string> CHitBorders::GetBorderIndicesStringVector() const
{
	vector<string> Result;
	for (map<string,int>::const_iterator it = m_ShortName2BreakCollection.begin(); it !=  m_ShortName2BreakCollection.end(); it++)
	{
		const CBreakCollection& B = m_Breaks[it->second];
		Result.push_back(B.m_LongName);
	};
	return Result;
};


string CHitBorders::WithinBreakName(const vector<string>& Within) const
{
	for (vector<string>::const_reverse_iterator wi=Within.rbegin(); wi != Within.rend(); wi++) {
		string ShortName = GetShortNameByName(*wi);
		if (!ShortName.empty())
			return ShortName;
	}
	return m_DefaultBreakName;
}

string	CHitBorders::GetBreakCollectionShortName(size_t i) const
{
    return m_Breaks[i].m_ShortName;
}
int	CHitBorders::GetBreakCollectionIndexByName(string ShortName ) const
{
   	map<string,int>::const_iterator it = m_ShortName2BreakCollection.find(ShortName);
	if (it == m_ShortName2BreakCollection.end())
		return -1;

    return it->second;
}
