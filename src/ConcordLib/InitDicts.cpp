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

#include "ConcCommon.h"

bool bEnglishMorph = false;
bool bRussianMorph = false;
bool bGermanMorph = false;
CLemmatizerEnglish *engLemmatizer = 0;
CLemmatizerRussian *rusLemmatizer = 0;
CLemmatizerGerman *gerLemmatizer = 0;

CEngGramTab *engGramTab = 0;
CRusGramTab *rusGramTab = 0;
CGerGramTab *gerGramTab = 0;

//! global mutex for non-thread-safe curl operations (global init, lru-cached proxy)
pthread_mutex_t ddcMorphMutex = PTHREAD_MUTEX_INITIALIZER;

template<class T, class Y>
void InitMorphologySystem(T *&Lemmatizer, Y *&Gramtab) {
    Lemmatizer = new T;
    if (!Lemmatizer)
        return;

    pthread_mutex_lock(&ddcMorphMutex);
    try {
        string l = GetStringByLanguage(Lemmatizer->GetLanguage());
        ddcLogDebug("   dictionary");
        string strError;
        if (!Lemmatizer->LoadDictionariesRegistry(strError)) {
            ddcLogError(Format("Cannot load %s  morphological dictionary: %s", l.c_str(), strError.c_str()));
            delete Lemmatizer;
            Lemmatizer = 0;
        }

        ddcLogDebug("   gramtab");
        Gramtab = new Y;
        if (!Gramtab) {
            pthread_mutex_unlock(&ddcMorphMutex);
            return;
        }
        if (!Gramtab->LoadFromRegistry()) {
            ddcLogError(Format("Cannot load %s  gramtab", l.c_str()));
            delete Gramtab;
            Gramtab = 0;
        }
    }
    catch (...) {
        pthread_mutex_unlock(&ddcMorphMutex);
        throw;
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
    if (Langua == morphEnglish) {
        if (!bEnglishMorph) {
            InitMorphologySystem(engLemmatizer, engGramTab);
            bEnglishMorph = true;
        };
        return engGramTab;
    } else if (Langua == morphRussian) {
        if (!bRussianMorph) {
            InitMorphologySystem(rusLemmatizer, rusGramTab);
            bRussianMorph = true;
        };
        return rusGramTab;
    } else if (Langua == morphGerman) {
        if (!bGermanMorph) {
            InitMorphologySystem(gerLemmatizer, gerGramTab);
            bGermanMorph = true;
        };
        return gerGramTab;
    } else
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
    catch (CExpc c) {
        fprintf(stderr, "Exception %s \n", c.m_strCause.c_str());
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


};

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
