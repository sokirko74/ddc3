//-*- Mode: C++ -*-
//
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
#include "ConcCommon.h"
#include "StringIndexator.h"

vector<string> GetGramInfosFromWord(const char *GraLine, MorphLanguageEnum Langua, bool bCapital) {

    const CLemmatizer *Lemmatizer = GetLemmatizerByLanguage(Langua);
    if (!Lemmatizer) return vector<string>();

    const CAgramtab *A = GetGramtabByLanguage(Langua);

    char SrcCodesBuffer[2000];

    Lemmatizer->GetAllAncodesQuick((BYTE *) GraLine, bCapital, (BYTE *) SrcCodesBuffer, true);

    size_t len = strlen(SrcCodesBuffer);
    vector<string> Result;
    QWORD CommonGrammems = 0;
    bool bReadCommonGrammems = false;
    for (size_t i = 0; i < len; i += 2) {
        if (!bReadCommonGrammems) {
            if (SrcCodesBuffer[i] == '?')
                CommonGrammems = 0;
            else
                A->GetGrammems(SrcCodesBuffer + i, CommonGrammems);
            bReadCommonGrammems = true;
            continue;
        };
        if (SrcCodesBuffer[i] == ';') {
            i--;
            bReadCommonGrammems = false;
            continue;
        };

        int ResultSavedSize = Result.size();
        {
            BYTE pos = A->GetPartOfSpeech(SrcCodesBuffer + i);
            // all nouns in German are uppercase
            if (Langua == morphGerman)
                if (!bCapital)
                    if ((pos == gSUB) || (pos == gEIG))
                        continue;

            if (pos != UnknownPartOfSpeech)
                Result.push_back(A->GetPartOfSpeechStr(pos));
        };

        QWORD Grammems;
        A->GetGrammems(SrcCodesBuffer + i, Grammems);

        size_t GrammemsCount = A->GetGrammemsCount();
        for (int k = 0; k < GrammemsCount; k++)
            if (_QM(k) & (Grammems | CommonGrammems))
                Result.push_back(A->GetGrammemStr(k));

        sort(Result.begin() + ResultSavedSize, Result.end());

        Result.push_back(MorphAnnotationsDelim);
    }


    return Result;
};

bool CreateMorphIndex(const CStringIndexator* indexator, string path, MorphLanguageEnum language, size_t maxTokenCountInOnePeriod) {

    fprintf(stderr, "CreateMorphIndex...\n");
    CStringIndexSet *pMorphIndexSet = indexator->GetIndexByAlias("MorphPattern");
    if (!pMorphIndexSet) {
        ErrorMessage("Cannot find MorphPattern index");
        return false;
    };
    CStringIndexSet *pTokensIndexSet = indexator->GetIndexByAlias("Token");
    if (!pTokensIndexSet) {
        ErrorMessage("Cannot find Token index");
        return false;
    };

    pTokensIndexSet->ReadFromTheDisk(); // if the index was just created, then Token index is not loaded


    if (!pMorphIndexSet->DestroyIndexSet()) {
        ErrorMessage("Cannot destroy morph. index set (some files cannot be deleted)");
        return false;
    };
    pMorphIndexSet->CreateTempFiles(path);
    size_t CountOfTokens = pTokensIndexSet->m_Index.size();
    size_t OccursCount = 0;

    for (size_t i = 0; i < CountOfTokens; i++) {
        if ((i % 1000) == 0)
            fprintf(stderr, "%zi/%zi (%zi/%zi)             \r", i, CountOfTokens, OccursCount,
                    3 * maxTokenCountInOnePeriod);

        const char *sToken = pTokensIndexSet->GetIndexItemStr(pTokensIndexSet->m_Index[i]);
        if (CheckLanguage(sToken, language)) {
            vector<string> TokenProperties = GetGramInfosFromWord(sToken, language,
                                                                  is_upper_alpha((BYTE) sToken[0], language));

            if (!TokenProperties.empty()) {
                string GramInfoStr = GetIndexItemSetByVectorString(TokenProperties, false);

                vector<CTokenNo> occurrences;
                pTokensIndexSet->ReadAllOccurrences(i, occurrences);
                pMorphIndexSet->InsertToInputLoadIndex(GramInfoStr.c_str(), GramInfoStr.length(), occurrences);
                OccursCount += occurrences.size();
            }
        }


        if ((OccursCount > 3 * maxTokenCountInOnePeriod)
            || (i + 1 == CountOfTokens)
                ) {

            pMorphIndexSet->SortInputAndMemoryIndices();

            if (!pMorphIndexSet->AddInputLoadIndexToMemoryLoadIndex()) {
                fprintf(stderr,
                        "AddInputLoadIndexToMemoryLoadIndex returned false in CConcIndexator::CreateMorphIndex\n");
                return false;
            };

            if (!pMorphIndexSet->SaveMemoryLoadIndex()) {
                fprintf(stderr, "cannot save memory indices to disk; probably no space left on device\n");
                return false;
            };

            if (!pMorphIndexSet->AddMemoryLoadIndexToMainLoadIndex()) {
                fprintf(stderr,
                        "AddMemoryLoadIndexToMainLoadIndex returned false in CConcIndexator::CreateMorphIndex\n");
                return false;
            }
            OccursCount = 0;
        };
    };
    fprintf(stderr, "%zi/%zi                         \n", CountOfTokens, CountOfTokens);

    fprintf(stderr, "final writing morph index\n");
    if (!pMorphIndexSet->WriteToFile(true)) return false;

    fprintf(stderr, "done\n");
    return true;
};

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-default-style: "linux"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
