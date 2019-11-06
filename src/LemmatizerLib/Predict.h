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

#ifndef PREDICT_H
#define PREDICT_H


#pragma warning(disable:4786)
#include "../CommonLib/utilit.h"
#include "MorphAutomat.h"


//////////////////////////////////////////////////////////////////////////////
struct  CPredictTuple 
{
        WORD                                                    m_ItemNo;
        DWORD                                                   m_LemmaInfoNo;
        BYTE                                                    m_PartOfSpeechNo;
};


//////////////////////////////////////////////////////////////////////
class CPredictBase 
{       
        CMorphAutomat                           m_SuffixAutomat;
        void FindRecursive(int r, string& curr_path, vector<CPredictTuple>& Infos) const;
public:
        DwordVector                     m_ModelFreq;

        
        CPredictBase(MorphLanguageEnum);

        void Load (const string &path);
        bool Find(const string &lettId, vector<CPredictTuple>& res) const;
};





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
