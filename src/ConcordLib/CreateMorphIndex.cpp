#include "ConcCommon.h"
#include "StringIndexator.h"

using namespace std;

vector<string> GetGramInfosFromWord(const char *GraLine, MorphLanguageEnum Langua, bool bCapital) {

    const CLemmatizer *Lemmatizer = GetLemmatizerByLanguage(Langua);
    if (!Lemmatizer) return vector<string>();

    const CAgramtab *A = GetGramtabByLanguage(Langua);

    //-- "<common ancode or ??><form ancodes>;" for each homonym (formerly CLemmatizer::GetAllAncodesQuick())
    string Codes;
    {
        string Word = GraLine;
        vector<CFormInfo> Paradigms;
        Lemmatizer->CreateParadigmCollection(false, Word, bCapital, true, Paradigms, false);
        for (const CFormInfo& F : Paradigms) {
            string Common = F.GetCommonAncode();
            Codes += Common.empty() ? string("??") : Common.substr(0, 2);
            Codes += F.GetSrcAncode();
            Codes += ";";
        }
    }
    const char* SrcCodesBuffer = Codes.c_str();

    size_t len = Codes.length();
    vector<string> Result;
    uint64_t CommonGrammems = 0;
    bool bReadCommonGrammems = false;
    for (size_t i = 0; i < len; i += 2) {
        if (!bReadCommonGrammems) {
            if (SrcCodesBuffer[i] == '?')
                CommonGrammems = 0;
            else
                CommonGrammems = A->GetAllGrammems(string(SrcCodesBuffer + i, 2).c_str());
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

        uint64_t Grammems;
        Grammems = A->GetAllGrammems(string(SrcCodesBuffer + i, 2).c_str());

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

        const char *sTokenUtf8 = pTokensIndexSet->GetIndexItemStr(pTokensIndexSet->m_Index[i]);
        string Token;   //-- single-byte (cp1251/cp1252) for the morphology
        if (MorphUtf8ToSingleByte(language, sTokenUtf8, Token) && !Token.empty()
            && CheckLanguageSingleByte(Token.c_str(), language)) {
            const char *sToken = Token.c_str();
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
