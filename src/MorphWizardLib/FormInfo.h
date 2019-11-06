//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2014 by Bryan Jurish
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
#ifndef _FORM_INFO_H
#define _FORM_INFO_H

#include "string.h"

struct CMorphForm 
{
        string m_Gramcode;
        string m_FlexiaStr;
        string m_PrefixStr;

        CMorphForm (string Gramcode, string FlexiaStr, string PrefixStr)
        {
                m_Gramcode = Gramcode;
                m_FlexiaStr = FlexiaStr;
                m_PrefixStr = PrefixStr;
                assert (!m_Gramcode.empty());
        };
        bool            operator == (const CMorphForm& X) const 
        {
                return                  m_Gramcode == X.m_Gramcode
                                        &&      m_FlexiaStr == X.m_FlexiaStr
                                        &&      m_PrefixStr == X.m_PrefixStr;
        };

};

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
struct  CFlexiaModel
{
        string                          m_Comments;
        vector<CMorphForm>      m_Flexia;

        bool            operator == (const CFlexiaModel& X) const 
        {
                return  m_Flexia == X.m_Flexia;
        };
        bool            ReadFromString(string& s);
        string          ToString() const;

        string          get_first_flex() const;
        string          get_first_code() const;
        bool            has_ancode(const string& search_ancode) const;
        
};



//----------------------------------------------------------------------------
struct CAccentModel 
{
        vector<BYTE> m_Accents;

        bool operator == (const CAccentModel& X) const
        {
                return m_Accents == X.m_Accents;

        };
        bool            ReadFromString(const string& s);
        string          ToString() const;
};


//----------------------------------------------------------------------------

const size_t CommonAncodeSize = 2;
const WORD UnknownParadigmNo = 0xffff-1;
const WORD UnknownAccentModelNo = 0xffff-1;

struct CLemmaInfo
{
        WORD    m_FlexiaModelNo;
        WORD    m_AccentModelNo;
        char    m_CommonAncode[CommonAncodeSize];

        CLemmaInfo()
        {
                m_FlexiaModelNo = UnknownParadigmNo;
                m_AccentModelNo = UnknownAccentModelNo;
                m_CommonAncode[0] = 0; 
        };

        bool operator ==(const CLemmaInfo& obj) const
        {       
                return (        (m_FlexiaModelNo == obj.m_FlexiaModelNo)
                                &&      (m_AccentModelNo == obj.m_AccentModelNo)
                                &&      !strncmp(m_CommonAncode,obj.m_CommonAncode,CommonAncodeSize)
                                );      
        }

        bool operator <(const CLemmaInfo& obj) const
        {       
                if (m_FlexiaModelNo != obj.m_FlexiaModelNo)
                        return m_FlexiaModelNo < obj.m_FlexiaModelNo;

                int res = strncmp(m_CommonAncode,obj.m_CommonAncode,CommonAncodeSize);
                if (res != 0)
                        return res < 0;

                return m_AccentModelNo < obj.m_AccentModelNo;
        }

        string GetCommonAncodeIfCan()  const 
        {
                if (m_CommonAncode[0] == 0) return "";
                return string(m_CommonAncode,2);        
        }

};


extern void ReadFlexiaModels(FILE* fp, vector<CFlexiaModel>& FlexiaModels );
extern void WriteFlexiaModels(FILE* out_fp, const vector<CFlexiaModel>& FlexiaModels );
extern void ReadAccentModels (FILE* fp, vector<CAccentModel>&   AccentModels );
extern void WriteAccentModels(FILE* out_fp, const vector<CAccentModel>& AccentModels );

#endif

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-default-style: "linux"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
