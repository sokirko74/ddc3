#include "StdGraph.h"
#include "GraphmatFile.h"
#include "Consent.h"


using namespace std;

bool ParagraphTagBeforeGraph(const CGraphmatFile &C, size_t i, size_t HB) {
    if (i == 0) return false;

    for (; i > 0; i--) {
        if (C.GetUnits()[i].IsParagraphTag())
            return  true;

        if (!C.GetUnits()[i].IsSoft())
            break;
    };
    return false;
};


RubiconEnum RubiconText(const CGraphmatFile &G, size_t i) {
    if (G.m_bEmptyLineIsSentenceDelim)
        if (G.EmptyLineBeforeGraph(i, G.GetUnits().size()))
            return rELine;

    if (ParagraphTagBeforeGraph(G, i, G.GetUnits().size()))
        return rPar;

    if (G.HasDescr(i, OPar))
        return rPar;

    return rUndef;
}

// Examples:
//   Space, Eoln, Space, Eoln, Graph => (0,4)
//   Space, Eoln, Space, Eoln, Graph, OPar => (0,4), (5,5)
//   Space, Eoln  => (0,0)
//   OPar, OPar => (0,0) (1,1)

void RecognizeSimpleCS(const CGraphmatFile &G, vector<CConSent> &CSL, size_t LB, size_t HB, RubiconEnum LB_Rubicon,
                       RubiconEnum HB_Rubicon) {
    RubiconEnum TypeRubicon = LB_Rubicon;

    size_t i = G.PSoft(LB, HB);

    while (i < HB) {
        CConSent CCS(&G);
        CCS.m_StartNo = i;
        for (i++; i < HB; i++) {
            TypeRubicon = RubiconText(G, i);
            if (TypeRubicon > 0) break;
        }
        CCS.m_EndNo = i;
        CSL.push_back(CCS);
        i = G.PSoft(i, HB);
    };
}


// Процедура приближения границ ME. Пусть даны два соседних ME A и Б,
// причем А идет раньше Б. На вход процедуры подаем Б.StartNo и A.EndNo,
// На выходе процедура добивается того, чтобы Б.StartNo == A.EndNo-1.
inline void AdjustRubiconsInSpaceCompact(const CGraphmatFile &C, size_t &StartNo, size_t &EndNo) {
    EndNo = C.PassSpace(EndNo, StartNo);

    if (EndNo == StartNo)
        EndNo = StartNo - 1;
    else {
        StartNo = C.BSpace(StartNo, EndNo);
        if (EndNo == StartNo)
            StartNo = EndNo + 1;
        else
            EndNo = StartNo - 1;
    }
}


void RecognizeCS(const CGraphmatFile &G, vector<CConSent> &CSL, size_t LB, size_t HB) {
    RecognizeSimpleCS(G, CSL, LB, HB, rBeg, rEnd);

    if (CSL.empty())
        CSL.push_back(CConSent(&G));

    CSL[0].m_StartNo = LB;

    long i = 0;
    for (; i < CSL.size() - 1; i++)
        AdjustRubiconsInSpaceCompact(G, CSL[i + 1].m_StartNo, CSL[i].m_EndNo);

    CSL[i].m_EndNo = HB - 1;
}

CConSent InitDoc(const CGraphmatFile *GraFile) {
    CConSent C(GraFile);
    C.m_Type = CS_Doc;
    C.m_StartNo = UnGroundNo;
    C.m_EndNo = UnGroundNo;
    C.m_HardGraphEndNo = 0;
    C.m_GraLineNoToMark = 0;
    return C;
}


void CGraphmatFile::MacSynHierarchy() {
    vector<CConSent> CSL;

    // если файл пуст надо выйти
    if (PSoft(1, GetUnits().size()) == GetUnits().size()) return;

    // Построение списка ME
    RecognizeCS(*this, CSL, 1, GetUnits().size());

    CSL.insert(CSL.begin(), InitDoc(this));


    for (int i = 1; i < CSL.size(); i++) {
        CSL[i].InitBasicInformation();
    };


    if (CSL.size() == 1)  return;


    for (int i = 0; i < CSL.size(); i++)
        if (CSL[i].m_GraLineNoToMark < GetUnits().size())
            SetDes(CSL[i].m_GraLineNoToMark, CSL[i].m_Type);

}
