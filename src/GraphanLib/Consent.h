
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
// ==========  Dialing Graphematical Module (www.aot.ru)
// ==========  Copyright by Alexey Sokirko (1996-2001), Bryan Jurish (2011)


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

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
