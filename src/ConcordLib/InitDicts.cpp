#include "ConcCommon.h"

using namespace std;

bool bEnglishMorph = false;
bool bRussianMorph = false;
bool bGermanMorph = false;
CLemmatizerEnglish *engLemmatizer = 0;
CLemmatizerRussian *rusLemmatizer = 0;
CLemmatizerGerman *gerLemmatizer = 0;

CEngGramTab *engGramTab = 0;
CRusGramTab *rusGramTab = 0;
CGerGramTab *gerGramTab = 0;

// global mutex for non-thread-safe curl operations (global init, lru-cached proxy)
pthread_mutex_t ddcMorphMutex = PTHREAD_MUTEX_INITIALIZER;

bool MorphUtf8ToSingleByte(MorphLanguageEnum Langua, const string& utf8, string& out) {
    out = convert_from_utf8(utf8.c_str(), Langua);
    return convert_to_utf8(out, Langua) == utf8;   //-- false if some characters do not exist in cp1251/cp1252
}

string MorphSingleByteToUtf8(MorphLanguageEnum Langua, const string& s) {
    return convert_to_utf8(s, Langua);
}

template<class T, class Y>
void InitMorphologySystem(T *&Lemmatizer, Y *&Gramtab) {
    pthread_mutex_lock(&ddcMorphMutex);
    Lemmatizer = new T;
    string l = GetStringByLanguage(Lemmatizer->GetLanguage());
    try {
        ddcLogDebug("   dictionary");
        Lemmatizer->LoadDictionariesRegistry();
    }
    catch (std::exception& e) {
        ddcLogError(Format("Cannot load %s  morphological dictionary: %s", l.c_str(), e.what()));
        delete Lemmatizer;
        Lemmatizer = 0;
    }

    try {
        ddcLogDebug("   gramtab");
        Gramtab = new Y;
        Gramtab->LoadFromRegistry();
    }
    catch (std::exception& e) {
        ddcLogError(Format("Cannot load %s  gramtab: %s", l.c_str(), e.what()));
        delete Gramtab;
        Gramtab = 0;
    }
    pthread_mutex_unlock(&ddcMorphMutex);
};


const CLemmatizer *GetLemmatizerByLanguage(MorphLanguageEnum Langua) {
    if (Langua == morphEnglish) {
        if (!bEnglishMorph) {
            InitMorphologySystem(engLemmatizer, engGramTab);
            bEnglishMorph = true;
        };
        return engLemmatizer;

    } else if (Langua == morphRussian) {
        if (!bRussianMorph) {
            InitMorphologySystem(rusLemmatizer, rusGramTab);
            bRussianMorph = true;
        };
        return rusLemmatizer;
    } else if (Langua == morphGerman) {
        if (!bGermanMorph) {
            InitMorphologySystem(gerLemmatizer, gerGramTab);
            bGermanMorph = true;
        };
        return gerLemmatizer;
    } else
        return 0;

};


const CAgramtab *GetGramtabByLanguage(MorphLanguageEnum Langua) {
    GetLemmatizerByLanguage(Langua); //-- lazy init
    if (Langua == morphEnglish) return engGramTab;
    if (Langua == morphRussian) return rusGramTab;
    if (Langua == morphGerman) return gerGramTab;
    return 0;
};


bool InitConcordDicts() {
    try {
        bRussianMorph = true;
        ddcLogInfo("loading Russian morphology");
        InitMorphologySystem(rusLemmatizer, rusGramTab);

        bEnglishMorph = true;
        ddcLogInfo("loading English morphology");
        InitMorphologySystem(engLemmatizer, engGramTab);

        bGermanMorph = true;
        ddcLogInfo("loading German morphology");
        InitMorphologySystem(gerLemmatizer, gerGramTab);

        return true;
    }
    catch (std::exception& c) {
        fprintf(stderr, "Exception %s \n", c.what());
        return false;
    }
    catch (...) {
        return false;
    }

}

void FreeConcordDicts() {
    if (rusLemmatizer) delete rusLemmatizer;
    if (engLemmatizer) delete engLemmatizer;
    if (gerLemmatizer) delete gerLemmatizer;
    if (rusGramTab) delete rusGramTab;
    if (engGramTab) delete engGramTab;
    if (gerGramTab) delete gerGramTab;
    rusLemmatizer = 0; engLemmatizer = 0; gerLemmatizer = 0;
    rusGramTab = 0; engGramTab = 0; gerGramTab = 0;
    bRussianMorph = bEnglishMorph = bGermanMorph = false;


};
