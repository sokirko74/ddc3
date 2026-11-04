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
// ==========  Dialing Structural Dictionary (www.aot.ru)
// ==========  Copyright by Alexey Sokirko (1998-2002), Bryan Jurish (2011)

#ifndef ROSS_H
#define ROSS_H

#include "morph_dict/common/utilit.h"
#include "../CommonLib/ddcUtil.h"

#include <time.h>


#include "ItemsContainer.h"


const int NullItemId = 1;

const size_t MaxItemStr = 100;

// ссылки на словaрную статью, лежащую в массиве Ross :: Cortege
const int InitialStartPos = 5000000;
const int InitialEndPos = -1;
// Индекс  - WORD
class CStructEntry {
public:
    int             m_EntryId;
    char    m_EntryStr[EntryStrSize];
    BYTE    m_MeanNum;
    int             m_StartCortegeNo;
    int             m_LastCortegeNo;
    bool    m_bSelected;
    // Графематические дескрипторы
    BYTE    __dummy;
    char    m_AuthorStr[AuthorNameSize];


    CStructEntry (const char* _Lemma = "\x0", int _MeanNum = 0) 
    {
        m_StartCortegeNo  = InitialStartPos;
        m_LastCortegeNo  = InitialEndPos;
        size_t l = strlen (_Lemma);
        if (l < EntryStrSize - 1)
            strcpy (m_EntryStr, _Lemma);
        else
        {
            strncpy (m_EntryStr, _Lemma, EntryStrSize - 1);
            m_EntryStr[EntryStrSize - 1] = 0;
        };

        m_MeanNum = _MeanNum; 
        m_bSelected = true;
    }

    bool HasEmptyArticle () const  {return m_StartCortegeNo == InitialStartPos;};

    bool operator==(const CStructEntry& X) const
    {       
        return    !strcmp (m_EntryStr, X.m_EntryStr)
            && (m_MeanNum == X.m_MeanNum); 
    }

    bool operator<(const CStructEntry& X) const
    { 
        int i = strcmp (m_EntryStr, X.m_EntryStr);
        return   (i < 0) 
            ||(    (i == 0)
                   && (m_MeanNum < X.m_MeanNum)); 
    }

};        

//===========================================
const size_t UnitCommentSize = 100;
class TUnitComment {
public:
    int  m_EntryId;
    char Editor[AuthorNameSize];
    char Comments[UnitCommentSize];
    tm   modif_tm;

    TUnitComment();
    TUnitComment(int _UnitId);

    bool operator==(const TUnitComment& X) const
    {return    m_EntryId == X.m_EntryId; }

    bool operator<(const TUnitComment& X) const
    { return    m_EntryId < X.m_EntryId;}

     
};        


class TCortegeContainer 
{
    typedef TBasicCortege<3> CortegeType3;
    typedef TBasicCortege<10> CortegeType10;

    std::vector<CortegeType3>      m_Corteges3;
    std::vector<CortegeType10>     m_Corteges10;
public :
    BYTE m_MaxNumDom;

    TCortegeContainer(BYTE MaxNumDom);
    virtual ~TCortegeContainer() {};
    TCortege10*           GetCortege (size_t i);
    const TCortege10*     GetCortege (size_t i)  const;

    void          _AddCortege(const TCortege10& C);
    size_t        _GetCortegesSize ()  const;
    void          ClearCorteges();
    void          EraseCorteges (size_t start, size_t last);
    void          WriteCorteges (const char* CortegeFile) const;
    void          ReadCorteges (const char* CortegeFile);
 
};




class TRoss  : public TCortegeContainer, public TItemContainer  
{
    char UnitsFile[_MAX_PATH];
    char CortegeFile[_MAX_PATH];
    char UnitCommentsFile[_MAX_PATH];
    char ConfigFile[_MAX_PATH];
        

public:
    BYTE                                    m_MaxMeanNum;
    std::string                                  m_DictName;
        
    std::vector<CStructEntry>    m_Units;
    std::vector<TUnitComment>    m_UnitComments;
    bool                                    m_bShouldSaveComments;


    TRoss (BYTE MaxNumDom);
    virtual ~TRoss ();
    bool    FullLoad(const char* _RossPath);
    bool    LoadOnlyConstants(const char* _RossPath);
    bool    Save ();


    // ++++++++++++++++++++++++++++++++++++++++++++++++++++
    // ++++++++       Словарный вход  +++++++++++++++++++++
    // ++++++++++++++++++++++++++++++++++++++++++++++++++++

    void    BuildUnits();
    uint16_t    GetUnitsSize() const { return (uint16_t)m_Units.size();     };
    bool    ClearUnits();
    void    ClearUnit(uint16_t UnitNo);
    uint16_t    LocateUnit (const char * EntryStr, int MeanNum) const;
    uint16_t    InsertUnit (CStructEntry& T);
    uint16_t    InsertUnit(const char* EntryStr, BYTE MeanNum);


    // ++++++++++++++++++++++++++++++++++++++++++++++++++++
    // ++++++++       Комментарий ко входу +++++++++++++++++++++
    // ++++++++++++++++++++++++++++++++++++++++++++++++++++

    bool                    ReadUnitComments();
    uint16_t                    InsertUnitComment (uint16_t m_EntryId);
    TUnitComment*                   GetCommentsByUnitId(uint16_t m_EntryId);
    const TUnitComment*             GetCommentsByUnitId(uint16_t EntryId)   const;


    // ++++++++++++++++++++++++++++++++++++++++++++++++++++
    // ++++++++       Словарная статья в виде кортежей ++++
    // ++++++++++++++++++++++++++++++++++++++++++++++++++++

    bool                    BuildCorteges();
    virtual bool    UpdateSignatsOfTheFieldInCorteges (BYTE FieldNo, std::vector<CSignat>& Signats);
    void                    DelCorteges (size_t start, size_t last);
                                                 
    // ++++++++++++++++++++++++++++++++++++++++++++++++++++
    // ++++++++  Чтение/запись строки словарной статьи +++++
    // ++++++++++++++++++++++++++++++++++++++++++++++++++++


    bool    ReadFromStrWithOneSignatura (const char* s, TCortege10& C, BYTE SignatNo);
    bool    ReadFromStr (const char* s, TCortege10& C);
    void    WriteToStr (const int* Items, const char* Frmt, char* OutBuffer) const;
    void    CortegeToStr (const TCortege10& C, char* OutBuffer) const;

    // ++++++++++++++++++++++++++++++++++++++++++++++++++++
    // +++++++++++++      Перечни констант  ++++++++++++++
    // ++++++++++++++++++++++++++++++++++++++++++++++++++++

    bool    InsertDomItem (const char* ItemStr, BYTE DomNo, int& ItemNo);

    const char* GetTitleFieldName() const;
    const char* GetSenseFieldName() const;
    const char* GetCommFieldName() const;
    const char* GetAuthorFieldName() const;
    const char* GetTimeCreatFieldName() const;
    const char* GetRedactFieldName() const;


    void SetUnitCommentStr(uint16_t UnitNo, const char* Str);
    void SetUnitAuthor(uint16_t UnitNo, const char* Author);
    void SetUnitModifTimeStr(uint16_t UnitNo, const char* TimeStr);
    void SetUnitEditor(uint16_t UnitNo, const char* Editor);
    std::string GetUnitModifTimeStr(uint16_t UnitNo) const;
    std::string GetUnitTextHeader(uint16_t UnitNo) const;

    bool    ReadConfig();

};


typedef enum {  iceOverwrite = 0, iceSkip = 1, iceAppend = 2} ImportConflictEnum;

struct CSourceLine 
{
    std::string m_Line;
    int m_SourceLineNo;
    CSourceLine (std::string Line,  int  SourceLineNo)
    {
        m_Line = Line;
        m_SourceLineNo = SourceLineNo;
    };
};



class CDictionary : public TRoss
{
public:
        
    /*
      By default  TCortegeContainer::m_MaxNumDom is equal to 3.
      Before invoking TRoss::Load it can be adjusted.
    */
    std::vector<CStructEntry>& GetUnits();

    CDictionary();
        
    BYTE            GetCortegeFieldNo(size_t i) const;
    const char* GetDomItemStrInner(int ItemNo) const;
    bool            IsEmptyArticle(uint16_t UnitNo) const;
    int                     GetUnitStartPos(uint16_t UnitNo) const;
    int                     GetUnitEndPos(uint16_t UnitNo) const;
    BYTE            GetFieldNoByFieldStr(const char* Str) const;
    int                     GetCortegeItem(long CortegeNo, BYTE PositionInCortege) const;
    const char*     GetDomItemStr(int ItemNo) const;

    bool            Load(const char* Path);
    bool            ProcessOneArticle ( std::vector<CSourceLine>& L, int start, int last, bool bSimulating, ImportConflictEnum ConflictSolver, std::string& Messages);
    bool            ImportFromText(std::string FileName, bool bSimulating, ImportConflictEnum ConflictSolver, int StartEntry,std::string& Messages);

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
