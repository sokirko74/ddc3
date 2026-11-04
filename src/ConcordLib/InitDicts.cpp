#include "ConcCommon.h"
#include "../CommonLib/ddcIconv.h"

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

//! German I/O recoding (internal morphology encoding is LATIN1)
ddcIconv *gerExt2Int = 0;
ddcIconv *gerInt2Ext = 0;

//! global mutex for non-thread-safe curl operations (global init, lru-cached proxy)
pthread_mutex_t ddcMorphMutex = PTHREAD_MUTEX_INITIALIZER;

static void InitGermanRecoding() {
    string extEncoding;
    try {
        extEncoding = ::GetRegistryString("Software\\Dialing\\Lemmatizer\\German\\ExtEncoding");
    }
    catch (...) {}
    if (extEncoding.empty())
        extEncoding = "UTF8"; //-- moo: expect UTF8 I/O for German by default
    if (extEncoding != "LATIN1") {
        gerExt2Int = new ddcIconv(extEncoding, "LATIN1//TRANSLIT");
        gerInt2Ext = new ddcIconv("LATIN1", extEncoding + "//TRANSLIT");
    }
}

string MorphRecodeExt2Int(MorphLanguageEnum Langua, const string& s) {
    return (Langua == morphGerman && gerExt2Int) ? gerExt2Int->convert(s) : s;
}

string MorphRecodeInt2Ext(MorphLanguageEnum Langua, const string& s) {
    return (Langua == morphGerman && gerInt2Ext) ? gerInt2Ext->convert(s) : s;
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
    if (Lemmatizer && Lemmatizer->GetLanguage() == morphGerman && !gerExt2Int)
        InitGermanRecoding();
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
    if (gerExt2Int) delete gerExt2Int;
    if (gerInt2Ext) delete gerInt2Ext;
    rusLemmatizer = 0; engLemmatizer = 0; gerLemmatizer = 0;
    rusGramTab = 0; engGramTab = 0; gerGramTab = 0;
    gerExt2Int = 0; gerInt2Ext = 0;
    bRussianMorph = bEnglishMorph = bGermanMorph = false;


};
