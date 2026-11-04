// ============          Consent.H       ==========================
// ==================================================================
//  Этот файл заголовков - часть  макросинтаксического анализа. 
//  Здесь определен тип (ConSent); переменные этого типа будут 
//  содержать макросинтаксические  единицы. Макросинтаксические 
//  единицы  входят в макросинтаксическую структуру (CSList.H).
//==================================================================

#ifndef consent_h
#define consent_h

#include "StdGraph.h"
#include "graline.h"

class CGraphmatFile;


enum RubiconEnum {      rUndef,         rELine,         rPar,   rPoint, rBeg,   rEnd,   rQQ1,
                        rQQ2,   rMaxLimit
};


const long UnGroundNo = 0;

struct CConSent {

    // ссылка на графематическую таблицу
    const CGraphmatFile* m_GraFile;

    const CGraLine& GetUnit(size_t i) const;


    size_t m_StartNo;     /* number of the first line of the CS  in Graphematical Table*/
    size_t m_EndNo;     /* number of the last line of the CS in Graphematical Table */

    size_t m_HardGraphEndNo;   // Номер строки таблицы, в которой содержится последняя непробельная графема

    // Номер строки графематической таблицы, на которую будет поставлен дескриптор
    size_t m_GraLineNoToMark; 


    // УП,  ЗГЛ, УПВвод ... 
    Descriptors m_Type;


    void SetEmpty ()
    {
        m_GraFile = 0;
        m_Type = CS_Undef;
    };

    CConSent ()
    {
        SetEmpty();

    };
    CConSent (const CGraphmatFile* _GraFile)
    {
        SetEmpty();
        m_GraFile = _GraFile;
    };



    bool  IsSoft() const;
    bool    InitBasicInformation ();
};


#endif
