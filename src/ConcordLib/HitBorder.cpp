//-*- Mode: C++ -*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2018 by Bryan Jurish
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
#include "StdConc.h"
#include "HitBorder.h"
#include "../CommonLib/bserialize.h"


inline size_t get_size_in_bytes (const CPageNumber& t)
{
    return sizeof(t.m_StartTokenNo) + sizeof(t.m_PageNumber);
};


inline size_t save_to_bytes(const CPageNumber& i, BYTE* buf)
{
    buf += save_to_bytes(i.m_StartTokenNo, buf);
    buf += save_to_bytes(i.m_PageNumber, buf);
    return get_size_in_bytes(i);
}

inline size_t restore_from_bytes(CPageNumber& i, const BYTE* buf)
{
    buf += restore_from_bytes(i.m_StartTokenNo, buf);
    buf += restore_from_bytes(i.m_PageNumber, buf);
    return get_size_in_bytes(i);
}


CHitBorders::CBreakCollection::CBreakCollection (const string& ShortName, const string& LongName)
{
    m_ShortName = ShortName;
    m_LongName = LongName;
    m_FileForIndexing = 0;
};


string CHitBorders::CBreakCollection::GetBreakFileName(string Path) const 
{
    return MakeFName(Path,Format("_%s_border", m_ShortName.c_str()));
};

void CHitBorders::CBreakCollection::ReadFromDisk(string Path, bool useMMap)
{
    m_BreakOffsets.open(GetBreakFileName(Path), useMMap);
}

bool CHitBorders::CBreakCollection::ClearAll(string Path)
{
    m_BreakOffsets.clear();

    string FileName = GetBreakFileName(Path);
    if (FileExists(FileName.c_str()))
        if (remove(FileName.c_str()))
            return false;
    return true;
}

void CHitBorders::CBreakCollection::CloseFileForIndexing()
{
    if (m_FileForIndexing) fclose (m_FileForIndexing);
    m_FileForIndexing = 0;
}

CHitBorders::CHitBorders()
{
    m_FileBreakCollectionNo = -1;   
};

void CHitBorders::CBreakCollection::AppendBreaks(const ddcBreakVector& From, CTokenNo Offset)
{
    size_t start = m_BreakOffsets.size();
    m_BreakOffsets.ensureVec();
    m_BreakOffsets.m_vec.insert(m_BreakOffsets.m_vec.end(), From.begin(), From.end());
    m_BreakOffsets.ensureData();
    for (size_t i=start; i < m_BreakOffsets.size(); ++i)
        m_BreakOffsets[i] += Offset;
};

void CHitBorders::CBreakCollection::SaveToFile(const string& FileName)
{ m_BreakOffsets.save(FileName); };

const ddcBreakVector* CHitBorders::GetBreaksByName(const string& ShortName) const
{
    map<string,int>::const_iterator it = m_ShortName2BreakCollection.find(ShortName);
    if (it == m_ShortName2BreakCollection.end())
        return NULL;
    else
        return &(m_Breaks[it->second].m_BreakOffsets);
};

string CHitBorders::GetPageBreaksFileName(string Path) const 
{
    return MakeFName(Path,"_pagebreaks");
};

bool    CHitBorders::IsRegisteredBreak(const string& ShortName) const
{
    return m_ShortName2BreakCollection.find(ShortName) !=  m_ShortName2BreakCollection.end();
};


string CHitBorders::GetShortNameByName(const string& BreakName) const
{
    for (size_t i=0; i <  m_Breaks.size(); i++)
    {
        if      (               (m_Breaks[i].m_ShortName == BreakName)
                                ||      (m_Breaks[i].m_LongName == BreakName)
            )
        {
            return m_Breaks[i].m_ShortName;
        };
    };
    return "";
};


const ddcBreakVector&  CHitBorders::GetFileBreaks() const
{
    return m_Breaks[m_FileBreakCollectionNo].m_BreakOffsets;
};

CTokenNo        CHitBorders::GetCorpusEndTokenNo() const        
{
    if (m_FileBreakCollectionNo == -1)
        return 0;
    const ddcBreakVector& FileBreaks = GetFileBreaks();
    if (FileBreaks.empty())
        return 0;  //no file in proj
    return FileBreaks[FileBreaks.size()-1];
};

CTokenNo CHitBorders::GetFileStartTokenNo(size_t i) const
{
    assert (m_FileBreakCollectionNo != -1);

    if (m_FileBreakCollectionNo==-1)
        return 0;

    const ddcBreakVector& FileBreaks = GetFileBreaks();
    if (FileBreaks.empty()) 
        return 0;

    if ( i == 0) 
        return 0;
    else
        return FileBreaks[i-1];
};


DWORD   CHitBorders::GetPageNumber(size_t No) const
{
    if (m_PageBreaks.empty()) 
        return UnknownPageNumber;
    else if (No >= m_PageBreaks.size())
        //throw CExpc(errRuntime, "CHitBorders::GetPageNumber(): requested item #%u not present (we only have %u)", No, m_PageBreaks.size());
        return UnknownPageNumber; //-- this should never really happen, but sometimes it does...
    else
        return m_PageBreaks[No].m_PageNumber;
};


bool    CHitBorders::StartIndexing(string Path)
{
    for (size_t i=0; i <  m_Breaks.size(); i++)
    {
        CBreakCollection& C = m_Breaks[i];
        string FileName = C.GetBreakFileName(Path);
        C.m_FileForIndexing = fopen (FileName.c_str(),"wb");
        if (!C.m_FileForIndexing)
        {
            ErrorMessage (Format("Cannot create %s for indexing\n", FileName.c_str()));
            for (size_t j=0; j <  m_Breaks.size(); j++)
                if (m_Breaks[j].m_FileForIndexing)
                    m_Breaks[j].CloseFileForIndexing();
            return false;
        };
    };
        
    m_PageBreaks.clear();
    return true;
};

void    CHitBorders::BordersEndIndexing(string Path)
{
    for (size_t i=0; i <  m_Breaks.size(); i++)
        m_Breaks[i].CloseFileForIndexing();

    SavePageBreaks(Path);

};

bool    CHitBorders::LoadHitBorders(string Path, bool useMMap)
{
    m_PageBreaks.open(GetPageBreaksFileName(Path), useMMap);

    for (size_t i=0; i <  m_Breaks.size(); i++)
        m_Breaks[i].ReadFromDisk(Path, useMMap);

    return true;
};

bool    CHitBorders::RemoveHitBordersFileAndClear(string Path)
{
    m_PageBreaks.clear();
    if (FileExists(GetPageBreaksFileName(Path).c_str()))
        if (remove(GetPageBreaksFileName(Path).c_str() ))
            return false;

    for (size_t i=0; i <  m_Breaks.size(); i++)
        m_Breaks[i].ClearAll(Path);

    return true;
};

void CHitBorders::StartTextAreaBorders()
{
    m_LastTextAreaBreaks.resize(m_Breaks.size(), DWORD_MAX);
}

void CHitBorders::EndTextAreaBorders(DWORD TextAreaEndTokenNo)
{
    for (size_t i=0; i < m_LastTextAreaBreaks.size(); i++)
        if (m_FileBreakCollectionNo != i)
            if ( (m_LastTextAreaBreaks[i] == DWORD_MAX) || ( m_LastTextAreaBreaks[i] < TextAreaEndTokenNo))
                AddBreakByIndex(i, TextAreaEndTokenNo);
}

void CHitBorders::AddBreakByIndex(DWORD BreakCollectionNo, const CTokenNo& B)
{
    if (m_LastTextAreaBreaks[BreakCollectionNo] == B) {
        return;
    }
    CBreakCollection& C = m_Breaks[BreakCollectionNo];
    BYTE TextBreakBuffer[sizeof(CTokenNo)];
    if (fwrite(TextBreakBuffer, save_to_bytes(B, TextBreakBuffer), 1, C.m_FileForIndexing) != 1) {
        throw CExpc(Format("cannot write to break collection %i, name=%s", BreakCollectionNo, C.m_LongName.c_str()));
    }
    m_LastTextAreaBreaks[BreakCollectionNo] = B;
};

void CHitBorders::AddBreakByName(const string& ShortName, const CTokenNo& B)
{
    map<string,int>::iterator it = m_ShortName2BreakCollection.find(ShortName);
    if (it == m_ShortName2BreakCollection.end())
        throw CExpc("Cannot find break name=" + ShortName);
    AddBreakByIndex(it->second, B);
};

void CHitBorders::AddPageBreak(const CPageNumber& P)
{
    m_PageBreaks.ensureVec();
    if      (               !m_PageBreaks.m_vec.empty()
                            &&      (P.m_PageNumber != UnknownPageNumber)
                            &&      (P.m_StartTokenNo == m_PageBreaks.m_vec.back().m_StartTokenNo)
        )
        m_PageBreaks.m_vec.back() = P;
    else
        m_PageBreaks.m_vec.push_back(P);

};




struct LessPageBreak {

    bool operator () (const CPageNumber& X,  const CTokenNo& StartTokenNo) const
    {
        return X.m_StartTokenNo < StartTokenNo;
    };
    bool operator () (const CTokenNo& StartTokenNo, const CPageNumber& X)  const
    {
        return StartTokenNo < X.m_StartTokenNo;
    };
    bool operator () (const CPageNumber& X1, const CPageNumber& X2)  const
    {
        return X1.m_StartTokenNo < X2.m_StartTokenNo;
    };

};

// for each hit calculate a page number, at which it starts. (a hit can divided by a page break)
// 
void CHitBorders::ConvertHitsToPageBreaks (
    vector<CHit>::const_iterator hits_begin, 
    vector<CHit>::const_iterator hits_end, 
    const ddcBreakVector& Breaks, 
    DwordVector& PageBreaks)        const
{
    PageBreaks.resize( hits_end - hits_begin );

    ddcVecFile<CPageNumber>::const_iterator start_it = m_PageBreaks.begin();
    ddcVecFile<CPageNumber>::const_iterator end_it   = m_PageBreaks.end();
    DwordVector::iterator PageBreakIt = PageBreaks.begin();
        
    for (vector<CHit>::const_iterator hit_it = hits_begin;  hit_it != hits_end; hit_it++, PageBreakIt++)
    {

        // StartTokenNo  is the start token number of hit Breaks[hits[i]].m_EndTokenNo
        CTokenNo StartTokenNo = 0;
        if (hit_it->m_BreakNo > 0)
        {
            StartTokenNo = Breaks[hit_it->m_BreakNo - 1];
        };
                
        // it is the page which is the next to the page that contains the hit; it can be  m_PageBreaks.end()
        //vector<CPageNumber>::const_iterator it = lower_bound (start_it, m_PageBreaks.end(), StartTokenNo, LessPageBreak());
        ddcVecFile<CPageNumber>::const_iterator it = lower_bound (start_it, end_it, StartTokenNo, LessPageBreak());

        // for each file there should be at least one page break (the first one)        
        *PageBreakIt = (it - m_PageBreaks.begin()) - 1;

        if      (                       (it != m_PageBreaks.end())
                                        &&      (it->m_StartTokenNo ==  StartTokenNo)
            )
            (*PageBreakIt)++;
                
        // start_it = it; uncomment it if hits are sorted
    };

};


// for each hit calculate a page number, at which it starts. (a hit can divided by a page break)
ddcVecFile<CPageNumber>::const_iterator CHitBorders::GetTokenPageBreak(CTokenNo tok) const
{
    return lower_bound(m_PageBreaks.begin(), m_PageBreaks.end(), tok, LessPageBreak());
}

int CHitBorders::EnsureRegisteredBreak(string ShortName, string LongName)
{
    int i  = GetBreakCollectionIndexByName(ShortName);
    if (i != -1)
        return i;
    if (ShortName != LongName) {
        int i  = GetBreakCollectionIndexByName(LongName);
        if (i != -1)
            return i;
    }
    return RegisterBreak(ShortName, LongName);
}

int CHitBorders::RegisterBreak(string ShortName, string LongName)
{
    CBreakCollection T (ShortName, LongName);
        
    pair<map<string,int>::iterator, bool> it = m_ShortName2BreakCollection.insert(make_pair(T.m_ShortName,m_Breaks.size()));
    if (!it.second)
    {
        throw CExpc("Error! A duplicate hit type name is found: "+T.m_LongName);
    };
    m_LongName2BreakCollection.insert(make_pair(T.m_LongName,m_Breaks.size()));
    m_Breaks.push_back(T);
    m_LastTextAreaBreaks.push_back(DWORD_MAX);
    return m_Breaks.size() - 1;
}

void CHitBorders::RegisterBorderIndices(const char* IndicesStr)
{
    m_Breaks.clear();
    m_LastTextAreaBreaks.clear();
    m_ShortName2BreakCollection.clear();
    m_LongName2BreakCollection.clear();
    m_DefaultBreakName = "";
    if (IndicesStr)
    {
        StringTokenizer tok(IndicesStr,";");
        while (tok())
        {
            string Item = tok.val();
            Trim(Item);
            if ((Item.empty())  || (Item[0] != '[') || (Item[Item.length()-1] != ']'))
            {
                throw CExpc(Format("Error! A bad format of the hit type definition (%s)!",IndicesStr));
            };
            Item = Item.substr(1, Item.length() - 2);
            StringTokenizer item_tok(Item.c_str(), ":");
            string ShortName = item_tok.next_token(); 
            if (ShortName == PredefinedTableLineTag)
            {
                throw  CExpc(("Error! Using of the predefined hit type \"l\" is prohibited"));
            };
                        

            if (ShortName.empty())
            {
                throw  CExpc ("Am empty short name in the hit type definition: "+Item);
            };
            RegisterBreak(ShortName, item_tok.next_token());
            if (item_tok.next_token() == "default")
                m_DefaultBreakName = ShortName;
        };
    };

    // register file break collection, if not already
    m_FileBreakCollectionNo = EnsureRegisteredBreak(PredefinedFileBreakName, PredefinedFileBreakName);
        

    // set default break collection, if it is not set in the options file
    if (m_DefaultBreakName.empty())
        m_DefaultBreakName = m_Breaks[0].m_ShortName;

    // register text area collection
    EnsureRegisteredBreak(PredefinedTextAreaBreakName, PredefinedTextAreaBreakName);
    assert (!m_Breaks.empty());
};


void CHitBorders::SavePageBreaks(const string& ProjectPath)
{
    m_PageBreaks.save( GetPageBreaksFileName(ProjectPath) );
};

// order breaks by short names
string CHitBorders::GetBorderIndicesString() const
{
    string Result;
    for (map<string,int>::const_iterator it = m_ShortName2BreakCollection.begin(); it !=  m_ShortName2BreakCollection.end(); it++)
    {
        const CBreakCollection& B = m_Breaks[it->second];
        if (B.m_ShortName != PredefinedFileBreakName) {
            if (B.m_ShortName == m_DefaultBreakName)
                Result += Format("[%s:%s:default];",B.m_ShortName.c_str(), B.m_LongName.c_str() );
            else
                Result += Format("[%s:%s];",        B.m_ShortName.c_str(), B.m_LongName.c_str() );
        }
    };
    Trim(Result);
    return Result;
};

string CHitBorders::WithinBreakName(const vector<string>& Within) const
{
    for (vector<string>::const_reverse_iterator wi=Within.rbegin(); wi != Within.rend(); wi++) {
        string ShortName = GetShortNameByName(*wi);
        if (!ShortName.empty())
            return ShortName;
    }
    return m_DefaultBreakName;
}


int     CHitBorders::GetBreakCollectionIndexByName(string name ) const
{
    //-- try short name first
    map<string,int>::const_iterator it = m_ShortName2BreakCollection.find(name);
    if (it != m_ShortName2BreakCollection.end())
        return it->second;

    it = m_LongName2BreakCollection.find(name);
    if (it!=m_LongName2BreakCollection.end())
        return it->second;

    return -1;
}

const CHitBorders::CBreakCollection* CHitBorders::GetBreakCollectionByName(const string& name) const
{
    int index = GetBreakCollectionIndexByName(name);
    if (index == -1) {
        return NULL;
    }
    return &m_Breaks[index];
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
