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
#include "StdConc.h"
#include "../ConcordLib/ConcIndexator.h"
#include "../ConcordLib/IndexSetForLoadingStage.h"



bool	CConcIndexator::CreateAsUnion(const CConcIndexator&  _X1, const CConcIndexator&  _X2)
{

    try 
    {
	    // ============
	    printf ("calculating corpus files\n");

	    m_CorpusFiles = _X1.m_CorpusFiles;
	    m_CorpusFiles.insert(m_CorpusFiles.end(), _X2.m_CorpusFiles.begin(),_X2.m_CorpusFiles.end());

	    DeleteAllSourceFiles();
	    AddSourceFilesFrom(_X1);
	    AddSourceFilesFrom(_X2);
    	

	    if (!SaveSourceFileList(m_Path))
		    throw CExpc ("Cannot save %s\n", m_Path.c_str());

	    if (!SaveCorpusFileList())
            throw CExpc ("Cannot save corpus file list %s\n", GetFileNameForCorpusFileNames().c_str());

	    // ============
	    printf ("calculating corpus options\n");
	    if (!_X1.HasEqualOptions (_X1))
            throw CExpc ("These projects have different options\n");

	    if (!LoadOptionsFromString(_X1.SaveOptionsToString()))  
            throw CExpc ("Cannot load options for the first corpus\n");

	    if (!SaveOptions(m_Path))
            throw CExpc ("Cannot save options file for %s\n", m_Path.c_str());

	    // =============
	    assert(_X1.GetIndicesString() ==  _X2.GetIndicesString());
	    if (_X1.GetIndicesString() !=  _X2.GetIndicesString())
            throw CExpc  ("the options of the corpora are different");

	    printf ("uniting text and file breaks\n");
	    if (!UniteBorders(_X1, _X2, _X1.GetCorpusEndTokenNo(), m_Path))
            throw CExpc ("cannot merge borders");

	    // ===============
	    printf ("calculating search periods\n");
	    CalculateSearchPeriods(GetMaxTokenCountInOnePeriod());

	    printf ("EndTokenNo of the first corpus: %i\n", _X1.GetCorpusEndTokenNo());

	    
	    ClearStringIndices();

	    for (size_t i=0; i < _X1.m_Indices.size(); i++)
	    {
		    printf ("unite index \"%s\"\n", _X1.m_Indices[i]->m_Name.c_str());
		    //if (_X1.m_Indices[i]->m_Name != "Thes") continue;
		    CStringIndexSet* I = new CStringIndexSet (this);
            I->InitIndexSet(_X1.m_Indices[i]->m_Name, _X1.m_Indices[i]->m_ShortName, (i==0), _X1.m_Indices[i]->m_bCompressOccurrences);
		    I->UnionIndexSet(*_X1.m_Indices[i], *_X2.m_Indices[i],  _X1.GetCorpusEndTokenNo(), _X2.GetCorpusEndTokenNo()); 
		    m_Indices.push_back(I);
	    };

    	
	    printf ("Save index items buffers\n");
	    if (!FinalSaveAllIndices(false))
            throw CExpc ("Cannot save index to disk, probably no space left!");

	    m_Bibl.SetPath(m_Path);
	    if (!m_Bibl.UniteBibliography(_X1.m_Bibl, _X2.m_Bibl))
		    throw CExpc ("cannot merge bibliography files");

	    return true;
    }
    catch (CExpc c)
    {
        fprintf (stderr,"CConcIndexator::CreateAsUnion: %s", c.m_strCause.c_str());
        return false;

    }
};


