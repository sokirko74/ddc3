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
#include "../ConcordLib/ConcIndexator.h"
#include "../ConcordLib/IndexSetForLoadingStage.h"
#include "ConcordAlgorithm.h"

#ifdef DETECT_MEMORY_LEAK
	#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
	#endif
#endif






bool	CStringIndexSet::ConvertLoadIndexToWorkingIndex ()
{

	FILE* main_fp = fopen(m_MainOccurTempFileName.c_str(), "rb");	
	if (!main_fp) return false;
	
	string OccursFileName = GetOccursFileName();
	FILE* res_fp = fopen(OccursFileName.c_str(), "wb");
	if (!res_fp ) 
	{
		fclose (main_fp);
		return false;
	};
	assert(	m_Index.empty() );
	m_Index.clear();
	m_EndPeriodOffsets.clear();
	const CTokenNo EndTokenNo = m_pParent->GetSearchPeriod(m_pParent->GetSearchPeriodsCount() - 1);
	
	CItemIndexForLoading M;
	if (!M.InitOccurs())
		return false;

	size_t CurrPositionInResFile = 0;
	while (!feof(main_fp))
	{
		if (!M.ReadFromTemporalFile(main_fp))
		{
			// the last index
			break;
		}
		if (!AddOneIndexItem(M,res_fp,CurrPositionInResFile, EndTokenNo))
		{
			fclose (main_fp);
			fclose(res_fp);
			return false;
		};
	};

	M.FreeOccurs();
	fclose(main_fp);
	fclose(res_fp);

	

	return  WritePeriodsDivision();
};


bool CStringIndexSet::WriteToFile(bool bAfterLoading)
{
	if (bAfterLoading) 
		if (!ConvertLoadIndexToWorkingIndex()) 
			return false;

	if (m_bUseItemStorage)
	{
		if (!ConvertTempStorageToPersistent())
			return false;
		if (!OpenStorageFile())
			return false;
	};

	DeleteTempFiles();

	m_Index.ensureVec();
	if (!WriteVector(GetOccHdrFileName().c_str(), m_Index.m_vec)) return false;

	m_StringBuffer.ensureVec();
	if (!WriteVector(GetFileNameForInfos().c_str(), m_StringBuffer.m_vec)) return false;

	EnsureSuffixIndex();
	m_rIndex.ensureVec();
	if (!WriteVector(GetSuffixFileName().c_str(), m_rIndex.m_vec)) return false;

	return true;
};


