//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2015 by Bryan Jurish
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
#ifndef __ConcordAlgorithm_H_
#define __ConcordAlgorithm_H_

#include "../CommonLib/utilit.h"

void SortWithLists(std::vector<uint32_t>& V, DwordVector& Borders);
void ConvertToVariableInteger(const std::vector<uint32_t>& In,std::vector<uint32_t>& Out);
void DeconvertFromVariableInteger(const uint32_t* in_start, const uint32_t* in_end,  uint32_t* out_start, uint32_t& OutCount);

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
