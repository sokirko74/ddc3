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
// ==========  Dialing Lemmatizer (www.aot.ru)
// ==========  Copyright by Alexey Sokirko, Bryan Jurish (2011)

#include "StdMorph.h"
#include "Predict.h"

#ifdef DETECT_MEMORY_LEAK
#ifdef _DEBUG
#define new DEBUG_NEW

#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif


CPredictBase::CPredictBase(MorphLanguageEnum langua) :m_SuffixAutomat(langua, MorphAnnotChar)
{
        
};


void CPredictBase::Load (const string &path)
{
    m_SuffixAutomat.Load(path);
};

void CPredictBase::FindRecursive(int NodeNo, string& curr_path, vector<CPredictTuple>& Infos) const
{
    const CMorphAutomNode& N = m_SuffixAutomat.GetNode(NodeNo);
    if (N.IsFinal())
    {
        int i = curr_path.find(m_SuffixAutomat.m_AnnotChar);
        assert (i != string::npos);
        int j = curr_path.find(m_SuffixAutomat.m_AnnotChar, i+1);
        assert (j != string::npos);
        int k = curr_path.find(m_SuffixAutomat.m_AnnotChar, j+1);
        assert (k != string::npos);
        CPredictTuple A;
        A.m_PartOfSpeechNo = m_SuffixAutomat.DecodeFromAlphabet(curr_path.substr(i+1,j-i-1));
        A.m_LemmaInfoNo = m_SuffixAutomat.DecodeFromAlphabet(curr_path.substr(j+1, k-j-1));
        A.m_ItemNo = m_SuffixAutomat.DecodeFromAlphabet(curr_path.substr(k+1));
        Infos.push_back(A);
    };

    size_t Count =  m_SuffixAutomat.GetChildrenCount(NodeNo);
    size_t CurrPathSize = curr_path.size();
    curr_path.resize(CurrPathSize + 1);
    for (size_t i=0; i<Count; i++)
    {
        const CMorphAutomRelation& p = m_SuffixAutomat.GetChildren(NodeNo)[i];
        curr_path[CurrPathSize] = p.GetRelationalChar();
        FindRecursive(p.GetChildNo(), curr_path, Infos);
    };
    curr_path.resize(CurrPathSize);
};

bool CPredictBase::Find(const string &ReversedWordForm, vector<CPredictTuple>& res) const
{
    //  we don't want to predict words which contains "AnnotChar" 
    //if (ReversedWordForm.find(AnnotChar) != string::npos)
    //      return false;

    size_t TextLength = ReversedWordForm.length();
    int r = 0;
    size_t i=0;
    for (; i<TextLength; i++)
    {
        int nd =  m_SuffixAutomat.NextNode(r,(BYTE)ReversedWordForm[i]);
                
        if (nd ==  -1) 
            break;          
        r = nd;
    };
    // no prediction by suffix which is less than 3
    if (i < MinimalPredictionSuffix) 
        return false;
        
    assert ( r != -1);
    string curr_path;
    FindRecursive(r, curr_path,res);
    return true;
};

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
