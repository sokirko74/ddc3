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
#include "ConcCommon.h"
#include "StringIndexator.h"






CStringIndexator::CStringIndexator()
{
	
	m_Path = "#empty_path";
	m_MaxRegExpExpansionSize = 1000000;
    m_pChunkIndex = 0;
    m_pLeftBigramsIndex = 0;
    m_pRightBigramsIndex = 0;
};

CStringIndexator::~CStringIndexator()
{
	ClearStringIndices();
	
};

void CStringIndexator::SetPath(string Path)
{
	m_Path = Path;
};

void  CStringIndexator::ClearStringIndices()
{
	for (size_t i=0; i < m_Indices.size(); i++)
		delete m_Indices[i];
	m_Indices.clear();
};

bool CStringIndexator::RegisterChunkIndex()
{
	if (GetIndexByName(ChunkIndexName))
		return false; // no one should use this name 

	m_pChunkIndex = new CStringIndexSet(this);
	m_pChunkIndex->InitIndexSet(ChunkIndexName, ChunkIndexName, false, false);
	m_Indices.push_back(m_pChunkIndex);
	return true;
};

CStringIndexSet* CStringIndexator::GetTokenIndex()
{
    return m_Indices[0];
}

const CStringIndexSet* CStringIndexator::GetTokenIndex() const
{
    return m_Indices[0];
}

bool CStringIndexator::RegisterStringIndices(string IndicesStr)
{
	ClearStringIndices();
	// to be done[name,short,archive]
	StringTokenizer tok(IndicesStr.c_str(),";");
	while (tok())
	{
		string Item = tok.val();
		Trim(Item);
		if ((Item.empty())  || (Item[0] != '[') || (Item[Item.length()-1] != ']'))
		{
			ErrorMessage ("A bad format of Indices Header !"+IndicesStr);
			return false;
		};
		Item = Item.substr(1, Item.length() - 2);
		StringTokenizer item_tok(Item.c_str(), " \t,");
		string Name = item_tok.next_token(); 
		string Short = item_tok.next_token();
		string CompressedStr = item_tok.next_token();
		string StorageStr = item_tok.next_token();
        if (Name.empty() ||  Short.empty() || CompressedStr.empty())
		{
			ErrorMessage ("A bad format of Indices Header !"+Item);
			return false;
		};

		bool bCompressed = true;
	
		if (CompressedStr == "archive")
			bCompressed = true;
		else
			if (CompressedStr == "normal")
				bCompressed = false;
			else
			{
				ErrorMessage ("A bad format of Indices Header :"+Item);
				return false;
			};
		bool bStorage = m_Indices.empty();
		if (StorageStr != "")
			if (StorageStr  == "storage")
				bStorage = true;
			else
				if (StorageStr == "storage_omit")
					bStorage = false;
				else
				{
					ErrorMessage ("A bad format of index header (storage specifier has wrong format) :"+Item);
					return false;
				};


		if (GetIndexByName(Name))
		{
			ClearStringIndices();
			assert (false);
			ErrorMessage ("A duplicate index name is found!");
			return false;
		};
		CStringIndexSet* R = new CStringIndexSet (this);
		R->InitIndexSet(Name, Short, bStorage, bCompressed);
		m_Indices.push_back(R);
	};
	
	return true;
};
		
string CStringIndexator::GetIndicesString() const
{
	string Result;
	for (size_t i=0; i < m_Indices.size(); i++)
	{
		if (m_Indices[i]->m_Name != ChunkIndexName) 
			Result += Format("[%s %s %s];", 
					m_Indices[i]->m_Name.c_str(),
					m_Indices[i]->m_ShortName.c_str(),
					m_Indices[i]->m_bCompressOccurrences ? "archive" : "normal");
	};
	Trim(Result);
	return Result;
};



bool	CStringIndexator::StartIndexing(string Path)
{
	m_Path = Path;

	for (size_t i=0; i < m_Indices.size(); i++)
		if (!m_Indices[i]->CreateTempFiles(Path))
			return false;


	return true;
};

bool	CStringIndexator::TerminateIndexing()
{
	for (size_t i=0; i < m_Indices.size(); i++)
		m_Indices[i]->DeleteTempFiles();

	return true;
};



bool	CStringIndexator::FinalSaveAllIndices(bool bAfterLoading)
{
	for (size_t i=0; i < m_Indices.size(); i++)
	{
		if (!m_Indices[i]->WriteToFile(bAfterLoading)) 
			return false;
	}

	if (!WriteVector(GetSearchPeriodsFileName().c_str(), m_SearchPeriods)) return false;

	return true;
};


void CStringIndexator::ProcessBigramBorders(const int BreakCollectionNo, CTokenNo occurrence)
{
  	for (size_t i=0; i < m_Indices.size(); i++)
        if (m_Indices[i]->m_BigramBorder == BreakCollectionNo)
            m_Indices[i]->ProcessBigramBorder(occurrence - 1); // we have to decrement occurrence, since it points 
                                                                // to the end of sentence, that is outside of sentence and
                                                                // therefore could not be found by regular procedures in THAT sentence
    
}

bool	CStringIndexator::IndexOneToken(const char* InputLine, const CTokenNo& TokenOffset)
{
	assert (!m_Indices.empty());
	
	size_t length = strlen(InputLine);
	if (length == 0) return false;

	const size_t MaxIndexLineLength = 4096;
	char Line[MaxIndexLineLength];

	if (length >= MaxIndexLineLength)
	{
		fprintf (stderr, "Error! Line \"%s\" is too long! It cannot be more than %i chars\n", InputLine, MaxIndexLineLength);
		return false;
	};
	strcpy(Line, InputLine);

	
	size_t IndexNo = 0;
	vector<CTokenNo> occurrences(1, TokenOffset);

	for (size_t start=0; start<length; start++)
	{
		if ( IndexNo == m_Indices.size() )
		{
			ErrorMessage(Format("Too many columns at line at line \"%s\"",Line) );
			return false;
		};

		size_t end = start;
		for (; end<length && (Line[end] != globalFieldDelimeter ); end++);
		int len = end-start;
		Line[end] = 0;

		//if	(len != 0) 
		m_Indices[IndexNo]->InsertToInputLoadIndex(Line+start, len, occurrences);


		IndexNo++;
		start = end;
	};

	// DDC has to insert a stub to each indices with storages in order to maintain 
	// so all storage files should be of the same size
	for (; IndexNo < m_Indices.size(); IndexNo++)
		if (m_Indices[IndexNo]->m_bUseItemStorage)
			m_Indices[IndexNo]->InsertToInputLoadIndex(ddc_archive_stub, strlen(ddc_archive_stub), occurrences);


	return true;
};






bool	CStringIndexator::AddInputLoadIndexToMemoryLoadIndex()
{
	try {
		for (size_t i=0; i < m_Indices.size(); i++)
			if (!m_Indices[i]->AddInputLoadIndexToMemoryLoadIndex())
				return false;

		return true;
	}
	catch (...)
	{
		fprintf (stderr, "exception in CStringIndexator::AddInputLoadIndexToMemoryLoadIndex\n");
		return false;
	}
};


bool	CStringIndexator::AddMemoryLoadIndexToMainLoadIndex()
{
	for (size_t i=0; i < m_Indices.size(); i++)
		if (!m_Indices[i]->AddMemoryLoadIndexToMainLoadIndex()) 
			return false;

	return true;
};


bool	CStringIndexator::SaveMemoryLoadIndex()
{
	for (size_t i=0; i < m_Indices.size(); i++)
		if (!m_Indices[i]->SaveMemoryLoadIndex()) 
			return false;

	return true;
};

CStringIndexSet*  CStringIndexator::GetIndexByName(const string& Name)
{
	for (size_t i=0; i < m_Indices.size(); i++)
	if (m_Indices[i]->m_Name == Name)
	{
		return m_Indices[i];
	};
	return 0;
};

CStringIndexSet*  CStringIndexator::GetIndexByNameOrShortName(const string& Name)
{
	for (size_t i=0; i < m_Indices.size(); i++)
	if	(		(m_Indices[i]->m_Name == Name) 
			|| (m_Indices[i]->m_ShortName == Name)
		)
	{
		return m_Indices[i];
	};
	return 0;
};


string CStringIndexator::GetSearchPeriodsFileName() const 
{
	return MakeFName(m_Path,"_periods");
};

bool	CStringIndexator::ReadIndicesFromTheDisk()
{
	ReadVector(GetSearchPeriodsFileName().c_str(), m_SearchPeriods);

	for (size_t i=0; i < m_Indices.size(); i++)
		if (!m_Indices[i]->ReadFromTheDisk())
			return false;

	


	return true;
};

bool	CStringIndexator::DestroyIndices()
{
	for (size_t i=0; i < m_Indices.size(); i++)
		if (!m_Indices[i]->DestroyIndexSet())
			return false;


	return true;
};
		

size_t	CStringIndexator::GetSearchPeriodsCount() const
{
	return m_SearchPeriods.size();
};
