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
// ==========  Dialing Syntax Analysis (www.aot.ru)
// ==========  Copyright by Alexey Sokirko, Bryan Jurish (2011)

#ifndef utilit_classes_h
#define utilit_classes_h

#include "utilit.h"
#include "ptrholder.h"
#include "ddcMMap.h"
#include "ddcThread.h"


class CShortString
{
    vector<char>::const_iterator m_pStringPointer;
public:
    CShortString(vector<char>::const_iterator pData);

    BYTE GetLength() const;
    vector<char>::const_iterator GetData() const;
    const char*     GetString() const;
    //bool  operator <(const CShortString& s) const;
};

class IsLessShortString : public std::binary_function<const CShortString&, const char*, bool>
{
public:
    bool operator()(const CShortString& Item1,      const char* Item2) const;
    bool operator()(const char* Item1,                      const CShortString& Item2) const;
    bool operator()(const CShortString& Item1,      const CShortString& Item2) const;
};


class CShortStringHolder : public vector<CShortString> 
{
    vector<char> m_Buffer;
    template<class T>
    bool CreateFromSequence(T begin, T end);
public: 
    void    ReadShortStringHolder(string filename);
    bool    WriteShortStringHolder(const string& FileName) const;
    bool    CreateFromVector(const StringVector& in);
    bool    CreateFromSet(const StringSet& in);
};



struct CMyTimeSpan 
{
    clock_t     m_StartTime;
    double      m_TimeSpan;
    long            m_InterfaceNestId;
    long            m_SequenceId;
    long        m_InvokeCount;
    CMyTimeSpan (long SequenceId = 0, long InterfaceNestId = 0);
    void GetStrRepresentation(const char* Name, char* buffer, double AllClocksCount) const;
};


class CMyTimeSpanHolder 
{
    map<string, CMyTimeSpan>        m_TimeSpans;
    long                                            m_SequenceId;
        
public:
    bool                                            m_bTimeSpanHolderEnabled;

    typedef map<string, CMyTimeSpan>::const_iterator        ConstIterator;
    typedef map<string, CMyTimeSpan>::iterator                      Iterator;

    CMyTimeSpanHolder();
    void StartTimer(const string& Name, long NestId);
    double EndTimer(const string& Name);
    string GetStrRepresentation (double AllClocksCount = 0) const;
    void ClearTimers();
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
