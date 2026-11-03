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
bool CConcIndexator::SplitProject(vector<CConcIndexator *> &Subs) const {
    return SplitProject(Subs, SaveOptionsToString());
}

//----------------------------------------------------------------------
bool CConcIndexator::SplitProject(vector<CConcIndexator *> &Subs, const string &SubOptions) const {
    //---------------------------------------
    // general preparations
    string logname = "CConcIndexator::SplitProject()";

    //---------------------------------------
    // sanity check(s)
    if (Subs.empty())
        throw CDDCExpc(logname + ": Error: no destination project(s) specified");
    if (Subs.size() > GetCorpusFilesCount())
        throw CDDCExpc(Format("%s: Error: number of output corpora exceeds number of indexed files (%zd > %zd)",
                           logname.c_str(), Subs.size(), GetCorpusFilesCount()));

    //---------------------------------------
    // initialize: find split points
    size_t nTokensPerSub = GetCorpusEndTokenNo() / Subs.size();
    ddcLogInfo(Format("%s: finding %zd split points (%zd tokens total -> ca. %zd tokens/subcorpus)", logname.c_str(),
                      Subs.size(), GetCorpusEndTokenNo(), nTokensPerSub));
    //
    vector<CFileNo> splitFileBreaks(Subs.size());  //-- [splitId] => file_id_of_first_file_not_in_split
    vector<CTokenNo> splitTokenBreaks(Subs.size()); //-- [splitId] => token_id_of_first_token_not_in_split
    const ddcBreakVector &fbreaks = GetFileBreaks();
    ddcBreakVector::const_iterator fbi = fbreaks.begin();
    for (size_t i = 0; i < Subs.size(); ++i) {
        CTokenNo tok_want = (i + 1) * nTokensPerSub;
        ddcBreakVector::const_iterator fbj = lower_bound(fbi, fbreaks.end(), tok_want);
        if (i == Subs.size() - 1) {
            //-- final split partition: gobble up all remaining files
            fbj = fbreaks.end() - 1;
        } else if (fbj >= fbreaks.end()) {
            //-- this should never happen
            throw CDDCExpc(
                Format("%s: Error: no file break found for split index=%zd, target token=%zd", logname.c_str(), i,
                       tok_want));
        } else if (fbj > fbi) {
            //-- multiple possibilities: pick closest split-point
            CTokenNo delta_j0 = ((*fbj) - tok_want);
            CTokenNo delta_j1 = (tok_want - *(fbj - 1));
            if (delta_j1 < delta_j0) --fbj;
        }
        splitFileBreaks[i] = (fbj - fbreaks.begin()) + 1;
        splitTokenBreaks[i] = (fbj == fbreaks.end() ? GetCorpusEndTokenNo() : *fbj);

        //-- report
        size_t nfiles_i = splitFileBreaks[i] - (i == 0 ? 0 : splitFileBreaks[i - 1]);
        size_t ntokens_i = splitTokenBreaks[i] - (i == 0 ? 0 : splitTokenBreaks[i - 1]);
        ddcLogInfo(Format("- %s : %zd file(s), %td token(s)", Subs[i]->m_Path.c_str(), nfiles_i, ntokens_i));

        //-- update
        fbi = fbj + 1;
    }

    //---------------------------------------
    // populate: read & save options
    bool inheritOpts = SubOptions.empty();
    string MyOpts = SaveOptionsToString();
    const string *_SubOpts = inheritOpts ? &MyOpts : &SubOptions;
    ddcLogInfo(logname + ": initializing subcorpus options (" + (inheritOpts ? "inherited" : "user-specified") + ")");
    for (size_t i = 0; i < Subs.size(); ++i) {
        string SubOptFile = MakeFName(Subs[i]->m_Path, "opt");
        MakeDirP(FileDirectory(Subs[i]->m_Path));
        if (!SaveStringToFile(*_SubOpts, SubOptFile))
            throw CDDCExpc(logname + ": Error: failed to save options to '" + SubOptFile + "'");
        Subs[i]->LoadOptionsFromFile(SubOptFile);
    }

    //---------------------------------------
    // populate: corpus files & source files
    ddcLogInfo(logname + ": populating file-lists");
    for (size_t i = 0; i < Subs.size(); ++i) {
        Subs[i]->m_CorpusFiles.clear();
        Subs[i]->m_CorpusFiles.ensureVec();
        Subs[i]->DeleteAllSourceFiles();
#if 0
        //-- this actually happens e.g. in kern01
        // + looks like "empty" m_SourceFiles[] items (from *.con, indexing time) don't have a m_CorpusFiles[] equivalent)
        // + hack for SplitProject() just treats m_CorpusFiles[] as "source files"
        if (m_SourceFiles.size() != m_CorpusFiles.size())
            throw CDDCExpc(Format("%s: Error: number of source files (%zd) is not identical to number of indexed files (%zd)",
                               logname.c_str(), m_SourceFiles.size(), m_CorpusFiles.size()));
#endif
        for (size_t fi = (i == 0 ? 0 : splitFileBreaks[i - 1]); fi < splitFileBreaks[i]; ++fi) {
            Subs[i]->m_CorpusFiles.m_strings.push_back(m_CorpusFiles[fi]);
            Subs[i]->m_SourceFiles.push_back(m_CorpusFiles[fi]);
        }
        if (!Subs[i]->SaveSourceFileList(Subs[i]->m_Path))
            throw CDDCExpc(logname + ": failed to save source file list " + Subs[i]->m_Path);
        if (!Subs[i]->SaveCorpusFileList())
            throw CDDCExpc(logname + ": failed to save corpus file list " + Subs[i]->GetFileNameForCorpusFileNames());
    }


    //---------------------------------------
    // populate: "masked" files (pseudo-deletions)
    if (!m_MaskedFiles.empty()) {
        ddcLogInfo(logname + ": populating corpus file mask(s)");
        size_t suboffset = 0;
        for (size_t i = 0; i < Subs.size(); ++i) {
            Subs[i]->m_MaskedFiles.clear();

            CMaskedFileSet::const_iterator lbi = m_MaskedFiles.lower_bound(suboffset);
            CMaskedFileSet::const_iterator ubi = m_MaskedFiles.lower_bound(splitFileBreaks[i]);
            for (; lbi != ubi; ++lbi)
                Subs[i]->m_MaskedFiles.insert(*lbi - suboffset);
            if (!Subs[i]->m_MaskedFiles.empty())
                Subs[i]->SaveMaskedFileIds();
            suboffset += Subs[i]->m_CorpusFiles.size();
        }
    }

    //---------------------------------------
    // populate: breaks ("borders")
    ddcLogInfo(logname + ": populating break collections");
    for (vector<CBreakCollection>::const_iterator brki = m_Breaks.begin(); brki != m_Breaks.end(); ++brki) {
        ddcLogInfo(logname + ": populating break collection " + brki->m_ShortName + ":" + brki->m_LongName);

        for (size_t i = 0; i < Subs.size(); ++i) {
            CBreakCollection *sbrks = (CBreakCollection *) Subs[i]->GetBreakCollectionByName(brki->m_LongName);
            if (sbrks == NULL) sbrks = (CBreakCollection *) Subs[i]->GetBreakCollectionByName(brki->m_ShortName);
            if (sbrks == NULL) {
                if (i == 0)
                    ddcLogWarn(logname + ": Warning: break collection [" + brki->m_ShortName + ":" + brki->m_LongName +
                               "] missing from subcorpus - skipping");
                continue;
            }

            CTokenNo tok_beg = i == 0 ? 0 : splitTokenBreaks[i - 1];
            CTokenNo tok_end = splitTokenBreaks[i];
            sbrks->m_BreakOffsets.clear();
            sbrks->m_BreakOffsets.ensureVec();
            sbrks->m_BreakOffsets.m_vec.insert(sbrks->m_BreakOffsets.m_vec.end(),
                                               upper_bound(brki->m_BreakOffsets.begin(), brki->m_BreakOffsets.end(),
                                                           tok_beg),
                                               upper_bound(brki->m_BreakOffsets.begin(), brki->m_BreakOffsets.end(),
                                                           tok_end));
            for (size_t boffi = 0; boffi < sbrks->m_BreakOffsets.m_vec.size(); ++boffi)
                sbrks->m_BreakOffsets.m_vec[boffi] -= tok_beg;
            sbrks->m_BreakOffsets.ensureData();
            sbrks->SaveToFile(sbrks->GetBreakFileName(Subs[i]->m_Path));
        }
    }

    //---------------------------------------
    // populate: page-breaks
    ddcLogInfo(logname + ": populating page-breaks");
    for (size_t i = 0; i < Subs.size(); ++i) {
        ddcVecFile<CPageNumber> &spbrks = Subs[i]->m_PageBreaks;

        CTokenNo tok_beg = i == 0 ? 0 : splitTokenBreaks[i - 1];
        CTokenNo tok_end = splitTokenBreaks[i];
        CPageNumber pn_beg(tok_beg, 0);
        CPageNumber pn_end(tok_end, 0); // the very last page break at the corpus end is not copied (ignored)

        spbrks.clear();
        spbrks.ensureVec();
        spbrks.m_vec.insert(spbrks.m_vec.end(),
                            lower_bound(m_PageBreaks.begin(), m_PageBreaks.end(), pn_beg),
                            lower_bound(m_PageBreaks.begin(), m_PageBreaks.end(), pn_end));
        for (size_t boffi = 0; boffi < spbrks.m_vec.size(); ++boffi)
            spbrks.m_vec[boffi].m_StartTokenNo -= tok_beg;
        spbrks.ensureData();
        Subs[i]->SavePageBreaks(Subs[i]->m_Path);
    }

    //---------------------------------------
    // populate: search periods
    ddcLogInfo(Format("%s: calculating search period boundaries (size ~ %zd)", logname.c_str(),
                      Subs[0]->GetMaxTokenCountInOnePeriod()));
    for (size_t i = 0; i < Subs.size(); ++i) {
        Subs[i]->CalculateSearchPeriods(Subs[i]->GetMaxTokenCountInOnePeriod());
        ddcLogInfo(Format("- %s : %zd search period(s)", Subs[i]->m_Path.c_str(), Subs[i]->m_SearchPeriods.size()));
    }

    //---------------------------------------
    // populate: token-level indices
    ddcLogInfo(logname + ": populating token-level indices");
    for (vector<CStringIndexSet *>::const_iterator ixi = m_Indices.begin(); ixi != m_Indices.end(); ++ixi) {
        const CStringIndexSet *ixp = *ixi;

        vector<CStringIndexSet *> Partitions(Subs.size());
        for (size_t i = 0; i < Subs.size(); ++i) {
            Partitions[i] = Subs[i]->GetIndexByAlias(ixp->m_Name);;
            if (Partitions[i] == NULL) Partitions[i] = Subs[i]->GetIndexByAlias(ixp->m_ShortName);
            if (Partitions[i] == NULL) {
                ddcLogWarn(Format("%s: Warning: index [%s %s] (missing from subcorpus #%zd - skipping",
                                  logname.c_str(), ixp->m_Name.c_str(), ixp->m_ShortName.c_str(), i));
                break;
            }
        }
        if (Partitions[0] == NULL) continue;

        ddcLogInfo(logname + ": populating index " + ixp->m_Name + " " + ixp->m_ShortName);
        ixp->CreateSplitPartitions(Partitions, splitTokenBreaks);
    }

    //---------------------------------------
    // populate: finalize indices
    ddcLogInfo(logname + ": saving index item buffers");
    for (size_t i = 0; i < Subs.size(); ++i) {
        if (!Subs[i]->FinalSaveAllIndices(false))
            throw CDDCExpc(logname + ": Error: failed to save index to disk - do you have enough free disk space?");
    }

    //---------------------------------------
    // populate: bibl
    ddcLogInfo(logname + ": populating document-level metadata indices");
    vector<CConcXml *> bibls(Subs.size());
    for (size_t i = 0; i < Subs.size(); ++i) {
        Subs[i]->m_BiblIndex.SetPath(Subs[i]->m_Path);
        bibls[i] = &(Subs[i]->m_BiblIndex);
    }
    m_BiblIndex.SplitBibliography(bibls, splitFileBreaks);

    //---------------------------------------
    // all done
    return true;
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
