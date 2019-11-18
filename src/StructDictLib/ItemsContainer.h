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

#ifndef ItemsContainer
#define ItemsContainer

#include "Domen.h"
#include "Field.h"

#include "../CommonLib/utilit.h"
#include "../CommonLib/cortege.h"
#include "../CommonLib/bserialize.h"




struct TDomNoItemStr {
    char ItemStr[100];
    BYTE DomNo;
};


struct TDomItem 
{
    DWORD   m_Data;
    BYTE    m_DomNo;

    DWORD   GetItemStrNo() const
    {
        return m_Data & ~(0xff<<24);
    };
    void    SetItemStrNo(DWORD Value) 
    {
        m_Data &= (0xff<<24);
        m_Data |= Value;
    };
    BYTE    GetItemStrLen() const
    {
        return m_Data>>24;
    };
    void    SetItemStrLen(BYTE Value) 
    {
        m_Data &= ~(0xff<<24);
        m_Data |= ((size_t)Value<<24);
    };

    BYTE    GetDomNo() const
    {
        return m_DomNo;
    };
    void    SetDomNo(BYTE Value) 
    {
        m_DomNo = Value;
    };
};




class TItemContainer  
{
public :
    MorphLanguageEnum       m_Language;
    char RossPath[_MAX_PATH];
    vector<TDomItem>  m_DomItems;
    char DomItemsFile[_MAX_PATH];
    char DomItemsTextFile[_MAX_PATH];
    char ItemsFile[_MAX_PATH];
    vector <CDomen> m_Domens;
    char DomensFile[_MAX_PATH];
    vector<CField> Fields;
    char FieldsFile[_MAX_PATH];
    bool    m_bDontLoadExamples;
    map<string,string>      m_Russian2EnglishFields;
        

    BYTE ActantsDomNo;
    BYTE LexDomNo;
    BYTE LexPlusDomNo;
    BYTE TitleDomNo;
    BYTE CollocDomNo;
    BYTE AbbrDomNo;
    BYTE FieldDomNo;
    BYTE EmptyDomNo;
    BYTE IllDomNo;
    BYTE IntegerDomNo;
    int WildCardDomItemNo;
    string m_LastError;


    TItemContainer();

    const char*                      GetDomItemStr(const TDomItem& Item) const 
    {
        assert (!m_Domens[Item.GetDomNo()].m_bFreed);
        return m_Domens[Item.GetDomNo()].m_Items+Item.GetItemStrNo();
    };

    void                    ErrorMessage (string s ) const;
    bool                    InitDomensConsts();
    int                             GetItemNoByItemStr (const char*  ItemStr, BYTE DomNo) const;
    int                             GetItemNoByItemStr (const char*  ItemStr, const char* DomStr) const;
    BYTE                    GetDomenNoByDomStr (const char* DomStr) const;
    bool                    AreEqualDomItems(const TDomItem& Item1, const TDomNoItemStr& Item2) const;

    void                    UpdateConstDomens();
    bool                    BuildDomens (char* LastReadLine);
    bool                    BuildDomItems ();
    BYTE                    GetDomNoForLePlus ( const char*  s) const;
    bool                    IsStandardRusLexeme (const char* s) const; 

    bool            CanBeRusAbbr (const char*  s) const;
    bool            CanBeRusColloc  (const char*  s) const;
    BYTE            GetFieldNoByFieldStrInner (const char* FieldStr) const; 
    bool            ClearFields ();
    bool            BuildFields(BYTE MaxNumDom);
    bool            WriteFields() const;
    bool            BuildFormats(BYTE MaxNumDom);
    bool            BuildOneFieldFormat (CSignat& Sgn, char* Frmt, char* Name, BYTE MaxNumDom);
    virtual bool    UpdateSignatsOfTheFieldInCorteges (BYTE FieldNo, vector<CSignat>& Signats)= 0; 
    bool            WriteDomens () const;
    size_t          GetDomItemsSize() const {return m_DomItems.size();};
    bool            WriteDomItems() const ;



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
