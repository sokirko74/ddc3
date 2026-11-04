#ifndef  graline_h
#define graline_h
#include "morph_dict/common/utilit.h"
#include "../CommonLib/ddcUtil.h"
#include  "gra_descr.h"




const uint16_t stSpace               = 1;
const uint16_t stEOLN                = 2;
const uint16_t stGrouped  = 4;
const uint16_t stAbbreviation       = 8;
const uint16_t stNotPrint   = 16;
const uint16_t stParagraphChar  = 64;
const uint16_t stEnglishName = 128;

const uint16_t stKeyModifier = 256;
const uint16_t stPunct     = 512;
const uint16_t stElectronicAddress  = 1024;

const uint16_t stTextAreaEnd      = 2048;
const uint16_t stSingleSpaceAfter = 4096;
const uint16_t stIdent       = 8192 ;
const uint16_t stParagraphTag      = 8192*2 ;
const uint16_t stPageBreak      = 8192*4 ;


class CGraphmatFile;


struct  CGraphemOborot {
    std::string m_UnitStr;
    uint16_t m_UnitNo;
    std::vector<uint16_t> m_TokenIds;

    bool operator == (const std::string& s)
    {
        return s == m_UnitStr;
    };
};



const uint32_t UnknownPageNumber  = 0xffffffff;

class CGraLine  
{
    // a pointer to tokens (not null-terminated)
    const char* unit;
 
    // screen length (multiply tabulation char)
    BYTE            slen;

    // unit length
    BYTE                ulen;             
    uint64_t           m_Descriptors;
    uint16_t                m_Status;
    uint32_t           m_InputOffset;

    size_t          LengthUntilDelimiters (const char *s, const CGraphmatFile* G);

public:
       
    CGraLine();
    BYTE GetTokenLength() const { return ulen; };
    const char* GetToken() const {return unit; };
    BYTE GetScreenLength() const {return slen;};
    uint32_t GetInputOffset() const {return m_InputOffset;};
    uint64_t GetDescriptors() const {return m_Descriptors; };

    bool IsNotPrint  () const;
    // we leave these function in the header, since VC doesn't want to make them inline
    bool IsSpace () const {return (m_Status & stSpace) != 0; };
    bool IsEOLN  () const {return (m_Status & stEOLN) != 0; };
    bool IsSoft  () const {return IsSpace() || IsEOLN();};
    bool IsPunct  () const {return (m_Status & stPunct) != 0;};

    bool IsIdent () const;
    ;
    bool IsEnglishName  () const;
    bool IsGrouped  () const;

    bool IsAbbreviation  () const;
    bool IsParagraphChar () const;
    bool IsPageBreak() const;
    bool IsTextAreaEnd() const;
    bool IsElectronicAddress()  const;
    bool IsParagraphTag () const;
    bool IsKeyModifier()  const;
    bool IsChar (int c) const;
    bool IsAsterisk () const;
    bool HasSingleSpaceAfter()  const;
    bool HasMacroSyntaxDelimiter () const;
    bool IsWordOrNumberOrAbbr() const;
        

    void SetSpace ();
    void SetPunct ();
    void SetEOLN  ();
    void SetNotPrint();
    void SetParagraphChar();
    void SetParagraphTag();
    void SetKeyModifier();
    void SetSingleSpaceAfter();
    void SetIdent();
    void SetElectronicAddress();
    void SetPageBreak();
    void SetTextAreaEnd();
    void SetEnglishName  ();
    void DelDes(Descriptors d);
    void SetDes(Descriptors d);  
    void AddStatus(uint16_t add_state);
    void SetToken(const char*);
    size_t          ReadWord (size_t Offset, const CGraphmatFile* G, uint32_t& PageNumber);
    bool IsSingleSpaceToDelete() const;
};


#endif
