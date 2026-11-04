#ifndef ItemsContainer
#define ItemsContainer

#include "Domen.h"
#include "Field.h"

#include "morph_dict/common/utilit.h"
#include "../CommonLib/ddcUtil.h"
#include "../CommonLib/cortege.h"
#include "../CommonLib/bserialize.h"




struct TDomNoItemStr {
    char ItemStr[100];
    BYTE DomNo;
};


struct TDomItem 
{
    uint32_t   m_Data;
    BYTE    m_DomNo;

    uint32_t   GetItemStrNo() const
    {
        return m_Data & ~(0xff<<24);
    };
    void    SetItemStrNo(uint32_t Value) 
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
    std::vector<TDomItem>  m_DomItems;
    char DomItemsFile[_MAX_PATH];
    char DomItemsTextFile[_MAX_PATH];
    char ItemsFile[_MAX_PATH];
    std::vector <CDomen> m_Domens;
    char DomensFile[_MAX_PATH];
    std::vector<CField> Fields;
    char FieldsFile[_MAX_PATH];
    bool    m_bDontLoadExamples;
    std::map<std::string,std::string>      m_Russian2EnglishFields;
        

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
    std::string m_LastError;


    TItemContainer();
    virtual ~TItemContainer() {};

    const char*                      GetDomItemStr(const TDomItem& Item) const 
    {
        assert (!m_Domens[Item.GetDomNo()].m_bFreed);
        return m_Domens[Item.GetDomNo()].m_Items+Item.GetItemStrNo();
    };

    void                    ErrorMessage (std::string s ) const;
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
    virtual bool    UpdateSignatsOfTheFieldInCorteges (BYTE FieldNo, std::vector<CSignat>& Signats)= 0; 
    bool            WriteDomens () const;
    size_t          GetDomItemsSize() const {return m_DomItems.size();};
    bool            WriteDomItems() const ;



};



#endif
