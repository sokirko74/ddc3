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


#ifndef  graline_h
#define graline_h
#include  "../CommonLib/utilit.h"
#include  "gra_descr.h"




const WORD stSpace               = 1;
const WORD stEOLN                = 2;
const WORD stGrouped  = 4;
const WORD stAbbreviation       = 8;
const WORD stNotPrint   = 16;
const WORD stParagraphChar  = 64;
const WORD stEnglishName = 128;

const WORD stKeyModifier = 256;
const WORD stPunct     = 512;
const WORD stElectronicAddress  = 1024;

const WORD stTextAreaEnd      = 2048;
const WORD stSingleSpaceAfter = 4096;
const WORD stIdent       = 8192 ;
const WORD stParagraphTag      = 8192*2 ;
const WORD stPageBreak      = 8192*4 ;


class CGraphmatFile;


struct  CGraphemOborot {
    std::string m_UnitStr;
    WORD m_UnitNo;
    std::vector<WORD> m_TokenIds;

    bool operator == (const std::string& s)
    {
        return s == m_UnitStr;
    };
};



const DWORD UnknownPageNumber  = 0xffffffff;

class CGraLine  
{
    // a pointer to tokens (not null-terminated)
    const char* unit;
 
    // screen length (multiply tabulation char)
    BYTE            slen;

    // unit length
    BYTE                ulen;             
    QWORD           m_Descriptors;
    WORD                m_Status;
    DWORD           m_InputOffset;

    size_t          LengthUntilDelimiters (const char *s, const CGraphmatFile* G);

public:
       
    CGraLine();
    BYTE GetTokenLength() const { return ulen; };
    const char* GetToken() const {return unit; };
    BYTE GetScreenLength() const {return slen;};
    DWORD GetInputOffset() const {return m_InputOffset;};
    QWORD GetDescriptors() const {return m_Descriptors; };

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
    void AddStatus(WORD add_state);
    void SetToken(const char*);
    size_t          ReadWord (size_t Offset, const CGraphmatFile* G, DWORD& PageNumber);
    bool IsSingleSpaceToDelete() const;
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
