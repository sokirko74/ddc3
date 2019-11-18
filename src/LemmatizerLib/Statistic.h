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
// ==========  Copyright by Alexey Sokirko, Andrey Putrin, Bryan Jurish (2011)

#ifndef morph_statistics_h
#define morph_statistics_h

#include "../CommonLib/utilit.h"

typedef troika<int, int, int>   _homonode_t;             
typedef pair<int, int>          _statnode_t; 

class CStatistic  
{
    vector<_statnode_t>                     m_WordWeights;
    vector<_homonode_t>                     m_HomoWeights;
public:
    void    Load(const string& path);
    int             get_HomoWeight(int paradigmid, int form) const;
    int             get_WordWeight(int paradigmid) const;
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
