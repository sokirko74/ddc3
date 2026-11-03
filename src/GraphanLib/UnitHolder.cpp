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

#include "StdGraph.h"
#include  "UnitHolder.h"
#include  "gra_descr_primitives.h"


using namespace std;

//=======================================================
//==========            CUnitHolder         =============
//=======================================================
CUnitHolder::CUnitHolder()
{
    m_Language  = morphRussian;
};



void CUnitHolder::SetState (size_t LB, size_t HB, WORD state) 
{
    for (size_t i=LB; i<HB; i++)
        m_Units[i].AddStatus(state);
}

bool  CUnitHolder::AreGrouped (size_t LB, size_t HB) const
{
    bool fl_res = true;

    for (size_t i=LB; i<HB; i++)
        fl_res = fl_res && m_Units[i].IsGrouped();

    return fl_res;
}

bool  CUnitHolder::HasGrouped (size_t LB, size_t HB) const
{
    for (size_t i=LB; i<HB; i++)
        if (m_Units[i].IsGrouped())
            return true;

    return false;
}

bool  CUnitHolder::HasAbbreviation (size_t LB, size_t HB) const
{
    for (size_t i=LB; i<HB; i++)
        if (m_Units[i].IsAbbreviation())
            return true;

    return false;
}

size_t CUnitHolder::PassSpace (size_t i, size_t HB) const
{
    if (i >= HB) return HB;
    for ( ; (i<HB)  && m_Units[i].IsSpace() ; i++);
    return  i;
}

size_t CUnitHolder::PPunctOrSoft(size_t i, size_t HB) const
{
    if (i >= HB) return HB;
    for ( ; (i<HB)  && (HasDescr (i,OPun) || m_Units[i].IsSoft()) ; i++);
    return  i;
};

size_t CUnitHolder::PPunct(size_t i, size_t HB) const
{
    if (i >= HB) return HB;
    for ( ; (i<HB)  && HasDescr (i,OPun) ; i++);
    return  i;
};


size_t CUnitHolder::BSpace (size_t i, size_t LB) const
{
    for ( ; (i>LB) && m_Units[i].IsSpace(); i--);

    return i;
}

size_t CUnitHolder::PSoft (size_t i, size_t HB) const
{
    if (i >= HB) return HB;

    for ( ;(i<HB) && m_Units[i].IsSoft(); i++);

    return i;
}

size_t CUnitHolder::BSoft (size_t i) const
{
    for ( ; (i>0) && m_Units[i].IsSoft(); i--);

    return i;
}


bool CUnitHolder::IsQuestionOrExclamationMarks (size_t i) const 
{
    return   (    (m_Units[i].GetTokenLength() > 0)
                  && (      ((unsigned  char)m_Units[i].GetToken()[0] == '?')
                            ||  ((unsigned  char)m_Units[i].GetToken()[0] == '!')
                      )
        );
};

                                    
bool CUnitHolder::IsSentenceEndMark (size_t  i) const
{
    return                  IsOneFullStop(i) 
        || IsQuestionOrExclamationMarks(i)
        || ((m_Units[i].GetTokenLength() == 1)  &&  ((BYTE)m_Units[i].GetToken()[0] == cEllipseChar))
        || (
            (m_Units[i].GetTokenLength() >1)
            &&  (m_Units[i].GetTokenLength() <6)
            &&  ((unsigned  char)m_Units[i].GetToken()[0] ==  '.')
            )
        || m_Units[i].IsTextAreaEnd();
};

bool CUnitHolder::IsOneCloseQuotationMark (size_t i) const
{
    if (i == 0) return false;
    BYTE z = (BYTE)m_Units[i].GetToken()[0];
    return  (m_Units[i].GetTokenLength() == 1)
        &&      (       ( z == (BYTE)'"')
                        ||      ( z == (BYTE)187) // Close quotation mark in Windows-1251 and windows-1252, ISO/IEC 8859-15
            ); 
};

bool CUnitHolder::IsOneOpenQuotationMark (size_t i) const
{
    if (i == 0) return false;
    BYTE z = (BYTE)m_Units[i].GetToken()[0];
    return     (m_Units[i].GetTokenLength() == 1)
        && (     (z == (BYTE)'"')
                 || (z == (BYTE)171) // Russian open quotation mark in Windows-1251 and and windows-1252, ISO/IEC 8859-15
            ); 
};

void CUnitHolder::SetDes(size_t x, Descriptors des)
{
    m_Units[x].SetDes(des);
};


bool  CUnitHolder::IsHyphen(size_t x)  const 
{
    return  HasDescr(x,OHyp) && m_Units[x].GetTokenLength() == 1;
};


bool            CUnitHolder::is_latin_alpha (int ch) const 
{
    if (m_Language == morphGerman)
        return is_german_alpha(ch);
    else
        return is_english_alpha(ch);
};

bool            CUnitHolder::is_lowercase (int ch) const 
{
    if (m_Language == morphGerman)
        return is_german_lower(ch);
    else
        return is_russian_lower(ch) || is_english_lower(ch);

};

bool            CUnitHolder::is_uppercase (int ch) const 
{
    if (m_Language == morphGerman)
        return is_german_upper(ch);
    else
        return is_russian_upper(ch) || is_english_upper(ch);

};

bool  CUnitHolder::IsOneAlpha(size_t x) const
{
    return  ((HasDescr(x,ORLE) || HasDescr(x,OLLE)) && (m_Units[x].GetTokenLength()==1))
        || ( (m_Units[x].GetTokenLength()==1) &&  is_latin_alpha((unsigned char)m_Units[x].GetToken()[0]) );
};

bool  CUnitHolder::IsOneChar(size_t x, int i) const 
{
    return   m_Units[x].GetTokenLength() == 1 && m_Units[x].GetToken()[0] == i;
};


bool  CUnitHolder::FirstUpper(size_t x) const 
{
    return  HasDescr(x,OUp) || HasDescr(x,OUpLw); 
};

bool CUnitHolder::IsBulletWord (size_t x) const 
{
    return HasDescr(x,ODigits) || IsOneAlpha(x);
};

bool CUnitHolder::IsOneFullStop (size_t i) const
{
    return (m_Units[i].GetTokenLength() == 1)  &&  (m_Units[i].GetToken()[0] == '.');
};


// Check if there is an empty line before the line that contains i

bool  CUnitHolder::EmptyLineBeforeGraph (size_t i, size_t HB) const
{
    if ((i == 0) || m_Units[i].IsSoft()) return false;
    size_t k = BSpace (i-1,0);
    if ((k == 0) || (!m_Units[k].IsEOLN()))  return false;
    if (   (m_Units[k].GetTokenLength()>2)
           || (    (m_Units[k].GetTokenLength() == 2)
                   && (m_Units[k].GetToken()[0] == '\n')
               )
        ) return true; 
    k--;
    if ( k ==  0 ) return false;
    k = BSpace ( k,0 ); 
    return m_Units[k].IsEOLN();
};


void CUnitHolder::FreeTable()
{
    ClearVector(m_Units);
    ClearVector(m_TokenBuf);
    m_FoundOborots.clear();
    m_FoundPageBreaks.clear();
}


void  CUnitHolder :: BuildUnitBufferUpper ()
{
    m_UnitBufUpper.clear();

    for (int i = 0; i<m_Units.size(); i++)
    {
        m_UnitBufUpper.insert(m_UnitBufUpper.end(), m_Units[i].GetToken(), m_Units[i].GetToken()+m_Units[i].GetTokenLength());
        m_UnitBufUpper.push_back(0);
    };
    GerEngRusMakeUpperTemplate(m_UnitBufUpper, m_Language, m_UnitBufUpper.size());

};



const char*     CUnitHolder::GetUnitBufferStart() const
{ 
    return &(*(GetUnitBuf().begin())); 
};

const char*     CUnitHolder::GetUnitUpperBufferStart() const 
{ 
    return &(*(m_UnitBufUpper.begin())); 
};

const char*     CUnitHolder::GetUppercaseToken(DWORD LineNo) const 
{ 
    size_t Offset = ( (GetUnits()[LineNo].GetToken()+LineNo) - GetUnitBufferStart());
    return GetUnitUpperBufferStart() + Offset; 
};

string  CUnitHolder::GetToken(DWORD LineNo) const 
{
    char s[CriticalTokenLength+1];
    strncpy (s,GetUnits()[LineNo].GetToken(), GetUnits()[LineNo].GetTokenLength());
    s[GetUnits()[LineNo].GetTokenLength()] = 0;
    return string(s);
};

        
size_t  CUnitHolder::GetTokensCount() const 
{
    return GetUnits().size();
}

DWORD   CUnitHolder::GetTokenInputOffset(DWORD LineNo) const 
{
    return GetUnits()[LineNo].GetInputOffset(); 
}

BYTE    CUnitHolder::GetTokenLength(DWORD LineNo) const 
{       
    return GetUnits()[LineNo].GetTokenLength(); 
};




void    CUnitHolder::InitTokenBuffer()
{
    FreeTable();

    // the first line of the graphematical table has a special meaining
    CGraLine C;
    m_Units.push_back(C);
    SetDes(0,OBeg);

    //  While  building gra-table we use pointers into m_TokenBuf, 
    // that's why we should allocate only once m_TokenBuf in the very beginning. 
    // No reallocations are possible.
    m_TokenBuf.resize(m_InputBuffer.size());
}



bool    CUnitHolder::InitInputBuffer(const string& S)
{
    m_InputBuffer.clear();
    // copy with terminated null 
    size_t len = S.length() + 1;
    m_InputBuffer.insert(m_InputBuffer.begin(), S.c_str(), S.c_str()+len);
    return m_InputBuffer.size() == len;
};


void    CUnitHolder::ClearInputBuffer()
{
    ClearVector(m_InputBuffer);
}

void    CUnitHolder::DeleteDescr(size_t LineNo, Descriptors d)
{
    m_Units[LineNo].DelDes(d);
};


CGraLine& CUnitHolder::GetUnit(size_t UnitNo) 
{ 
    return m_Units[UnitNo]; 
};

const vector<char>& CUnitHolder::GetUnitBuf() const 
{ 
    return m_TokenBuf; 
};

const vector<BYTE>& CUnitHolder::GetInputBuffer() const 
{ 
    return m_InputBuffer; 
};

void    CUnitHolder::AddUnit(const CGraLine& NewLine)
{
    m_Units.push_back(NewLine);  
};


void CUnitHolder::SetOborotNo(size_t LineNo, short OborotNo)
{
    if (OborotNo == -1)
        m_FoundOborots.erase(m_Units[LineNo].GetInputOffset());
    else
        m_FoundOborots[m_Units[LineNo].GetInputOffset()] = OborotNo;
}

short CUnitHolder::GetOborotNo(size_t LineNo) const
{
    if (LineNo == 0) return -1;
    map<size_t, short>::const_iterator it = m_FoundOborots.find(m_Units[LineNo].GetInputOffset());
    if ( it == m_FoundOborots.end() )
        return -1;
    else
        return it->second;
}

void    CUnitHolder::SetPageNumber(size_t LineNo, DWORD PageNumber)
{
    if (PageNumber == UnknownPageNumber)
        m_FoundPageBreaks.erase(m_Units[LineNo].GetInputOffset());
    else
        m_FoundPageBreaks[m_Units[LineNo].GetInputOffset()] = PageNumber;

}

DWORD   CUnitHolder::GetPageNumber(size_t LineNo) const
{
    map<size_t, DWORD>::const_iterator it = m_FoundPageBreaks.find(m_Units[LineNo].GetInputOffset());
    if ( it == m_FoundPageBreaks.end() )
        return UnknownPageNumber;
    else
        return it->second;

}

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
