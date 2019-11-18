//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2019 by Bryan Jurish
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

//----------------------------------------------------------------------
bool CConcIndexator::CreateAsUnion(vector<CConcIndexator* > &X, bool inheritOptions) {
    //---------------------------------------
    // general preparations
    string logname = "CConcIndexator::CreateAsUnion()";

    //-- sanity check(s)
    if (X.empty())
        throw CExpc(logname + ": Error: no source indices specified");

    string path = X[0]->m_Path;
    //---------------------------------------
    // populate: corpus files, source files
    ddcLogInfo(logname + ": populating union file-lists");
    m_CorpusFiles.clear();
    DeleteAllSourceFiles();
    for (vector<CConcIndexator* >::const_iterator xi = X.begin(); xi != X.end(); ++xi) {
        (*xi)->m_CorpusFiles.append_vector(m_CorpusFiles.m_strings);
        AddSourceFilesFrom(**xi);
    }
    if (!SaveSourceFileList(m_Path))
        throw CExpc(logname + ": failed to save source file list " + m_Path);
    if (!SaveCorpusFileList())
        throw CExpc(logname + ": failed to save corpus file list " + GetFileNameForCorpusFileNames());

    //---------------------------------------
    // populate: options (unless explicitly disabled by user)
    if (inheritOptions) {
        ddcLogInfo(logname + ": inheriting options from " + path);
        //ddcLogTrace(logname+": options =\n"+X[0].SaveOptionsToString());
        LoadOptionsFromString(X[0]->SaveOptionsToString());
        ddcLogInfo(logname + ": saving options to " + MakeFName(m_Path, "opt"));
        if (!SaveOptions(m_Path))
            throw CExpc(logname + ": Error: failed to save options for project " + m_Path);
    }

    //---------------------------------------
    // populate: "masked" files (pseudo-deletions)
    ddcLogInfo(logname + ": populating corpus mask " + GetFileNameForMaskedFileIds());
    size_t moffset = 0;
    for (vector<CConcIndexator* >::const_iterator xi = X.begin(); xi != X.end(); ++xi) {
        for (CMaskedFileSet::const_iterator xmi = (*xi)->m_MaskedFiles.begin(); xmi != (*xi)->m_MaskedFiles.end(); ++xmi) {
            m_MaskedFiles.insert(*xmi + moffset);
        }
        moffset += (*xi)->m_CorpusFiles.size();
    }
    SaveMaskedFileIds();

    //---------------------------------------
    // populate: breaks ("borders")
    // + lifted from old CHitBorders::UniteBorders()
    size_t offset;
    ddcLogInfo(logname + ": populating break collections");
    m_FileBreakCollectionNo = -1;
    for (vector<CBreakCollection>::iterator brki = m_Breaks.begin(); brki != m_Breaks.end(); ++brki) {
        offset = 0;
        ddcLogInfo(logname + ": populating break collection " + brki->m_ShortName + ":" + brki->m_LongName);
        for (vector<CConcIndexator* >::const_iterator xi = X.begin(); xi != X.end(); ++xi) {
            const CBreakCollection *xbrk = (*xi)->GetBreakCollectionByName(brki->m_ShortName);
            if (xbrk == NULL) xbrk = (*xi)->GetBreakCollectionByName(brki->m_LongName);
            if (xbrk == NULL) {
                ddcLogWarn(logname + ": Warning: break collection '" + brki->m_ShortName + ":" + brki->m_LongName +
                           "' not found in project " + (*xi)->m_Path + "; using default");
                xbrk = (*xi)->GetBreakCollectionByName((*xi)->m_DefaultBreakName);
            }
            brki->AppendBreaks(xbrk->m_BreakOffsets, offset);
            offset += (*xi)->GetCorpusEndTokenNo();

            //-- sanity checks
            if (offset >= (size_t) CIndexItem::GetMaximalNumberOfRunningTokens())
                throw CExpc(Format("%s: Error: maximum token count (=%zd) exceeded", logname.c_str(),
                                   (size_t) CIndexItem::GetMaximalNumberOfRunningTokens()));
        }
        //-- dump
        brki->SaveToFile(brki->GetBreakFileName(m_Path));
        if (PredefinedFileBreakName == brki->m_ShortName)
            m_FileBreakCollectionNo = (brki - m_Breaks.begin());
    }
    if (m_FileBreakCollectionNo == -1)
        throw CExpc(logname + ": Error: no builtin '" + PredefinedFileBreakName + "' break collection found");

    //-- count total tokens
    ddcLogInfo(Format("%s: output corpus will contain %zd tokens", logname.c_str(), GetCorpusEndTokenNo()));


    //---------------------------------------
    // populate: page-breaks
    // + lifted from old CHitBorders::UniteBorders()
    ddcLogInfo(logname + ": populating page-breaks");
    m_PageBreaks.clear();
    m_PageBreaks.ensureVec();
    offset = 0;
    for (vector<CConcIndexator* >::const_iterator xi = X.begin(); xi != X.end(); ++xi) {
        const ddcVecFile<CPageNumber> &xpbrk = (*xi)->m_PageBreaks;
        size_t xoffset = m_PageBreaks.size();
        m_PageBreaks.m_vec.insert(m_PageBreaks.m_vec.end(), xpbrk.begin(), xpbrk.end());
        for (size_t i = xoffset; i < m_PageBreaks.size(); ++i)
            m_PageBreaks.m_vec[i].m_StartTokenNo += offset;
        offset += (*xi)->GetCorpusEndTokenNo();
    }
    SavePageBreaks(m_Path);

    //---------------------------------------
    // populate: search periods
    ddcLogInfo(Format("%s: calculating search period boundaries (size ~ %zd)", logname.c_str(),
                      GetMaxTokenCountInOnePeriod()));
    CalculateSearchPeriods(GetMaxTokenCountInOnePeriod());
    ddcLogInfo(Format("%s: partitioning into %zd search period(s)", logname.c_str(), m_SearchPeriods.size()));

    //---------------------------------------
    // populate: token-level indices
    ddcLogInfo(logname + ": populating token-level indices");
    vector<size_t> TokenCounts;
    for (vector<CConcIndexator* >::const_iterator xi = X.begin(); xi != X.end(); ++xi) {
        TokenCounts.push_back((*xi)->GetCorpusEndTokenNo());
    }
    for (vector<CStringIndexSet *>::const_iterator ixi = m_Indices.begin(); ixi != m_Indices.end(); ++ixi) {
        CStringIndexSet *ixp = *ixi;
        ddcLogInfo(logname + ": populating index " + ixp->m_Name + " " + ixp->m_ShortName);

        //-- get sub-indices
        vector<CStringIndexSet *> subIndexSets;
        for (vector<CConcIndexator* >::const_iterator xi = X.begin(); xi != X.end(); ++xi) {
            CStringIndexSet *subx = (*xi)->GetIndexByAlias(ixp->m_Name);
            if (subx == NULL) subx = (*xi)->GetIndexByAlias(ixp->m_ShortName);
            if (subx == NULL) {
                ddcLogWarn(Format("%s: Warning: index '%s %s' missing from sub-project '%s' -- using empty values",
                                  logname.c_str(), ixp->m_Name.c_str(), ixp->m_ShortName.c_str(), (*xi)->m_Path.c_str()));
            }
            subIndexSets.push_back(subx);
        }

        //-- merge sub-indices
        ixp->UnionIndexSets(subIndexSets, TokenCounts);
    }

    //---------------------------------------
    // populate: finalize indices
    ddcLogInfo(logname + ": saving index item buffers");
    if (!FinalSaveAllIndices(false))
        throw CExpc(logname + ": Error: failed to save index to disk - do you have enough free disk space?");

    //---------------------------------------
    // populate: bibl
    // + lifted from old CConcXml::UniteBibliography()
    ddcLogInfo(logname + ": populating document-level metadata indices");
    m_BiblIndex.SetPath(m_Path);
    vector<const CConcXml *> bibls;
    for (vector<CConcIndexator* >::const_iterator xi = X.begin(); xi != X.end(); ++xi) {
        bibls.push_back(&((*xi)->m_BiblIndex));
    }
    m_BiblIndex.UnionBibliographies(bibls);

    //---------------------------------------
    // what now?
    //throw CExpc(logname+": so far so good -- what now?");
    return true;
}


//----------------------------------------------------------------------
// new (filenames)
bool CConcIndexator::CreateAsUnion(const vector<string> &Xfiles, bool inheritOptions) {
    vector<CConcIndexator* > Iv (Xfiles.size());
    for (size_t i = 0; i < Xfiles.size(); ++i) {
        Iv[i] = new CConcIndexator();
        ddcLogInfo("LoadProject " + Xfiles[i]);
        Iv[i]->LoadProject(Xfiles[i].c_str());
    }

    //-- guts
    bool rc = CreateAsUnion(Iv, inheritOptions);

    for (size_t i = 0; i < Iv.size(); ++i) {
        delete Iv[i];
    }
    return rc;

    //return false;
}

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
