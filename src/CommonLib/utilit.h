//-*- Mode: C++ -*-
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
// ==========  Copyright by Alexey Sokirko
// Changes and modifications 2011-2018 by Bryan Jurish

#ifndef utilit_h
#define utilit_h

//-- BEGIN moo (Wed, 11 May 2011 14:44:12 +0200): get size-limited types (e.g. uint32_t)
#include "ddcConfig.h"
#include <stdint.h>

//-- DDC_USE_UTF8 : define this to allow high bits in morphology
// + doesn't work well for "real" utf8 b/c upper-casing works byte-wise (bummer)
#undef DDC_USE_UTF8

//-- END moo
#include  <stdio.h>




#include  <assert.h>
#include  <stdarg.h>
#include  <string.h>
#include  <ctype.h>
#include  <string>
#include  <algorithm>
#include  <stdexcept>
#include  <vector>
#include  <typeinfo>  //-- moo: for typeid()
#include  "set"
#include  "stack"
#include  "map"
#include "time.h"


                




//-- common utilities shared with RML (git submodule src/morph_dict)
#include "morph_dict/common/utilit.h"



#include <cstdint>
#include <unistd.h>

//-- moo: branch prediction macros; see e.g. https://www.geeksforgeeks.org/branch-prediction-macros-in-gcc/
# define likely(x)      __builtin_expect(!!(x), 1) 
# define unlikely(x)    __builtin_expect(!!(x), 0)

//-- moo: more utilities
#include "../CommonLib/ddcLocale.h"
#include "../CommonLib/ddcVersion.h"
#include "../CommonLib/ddcString.h"


//-- ddc exceptions (CDDCExpc, CFatalExpc, ddcExpcCode)
#include "ddcExpc.h"


//-- files and paths
#include "ddcFile.h"


//-- process statistics (/proc), heap trimming
#include "ddcProcess.h"


//======================================================================



//======================================================================
// integer utilities

/** fast approximation of base-2 logarithm for unsigned integers (= most significant bit)
 *  \see https://graphics.stanford.edu/~seander/bithacks.html#IntegerLogObvious and related methods
 *  \see https://stackoverflow.com/questions/2589096/find-most-significant-bit-left-most-that-is-set-in-a-bit-array
 *  \see https://stackoverflow.com/questions/9353973/implementation-of-builtin-clz
 */
inline uint32_t log2u32(uint32_t v)
{
    //-- gcc has __builtin_clz()
    return (v==0 ? 0 : __builtin_clz(v)^31);
};

/** get average size of gap between elements of v[]
 *  \param v vector of numeric types castable to (size_t), sorted in ascending order, implicit start=0 (e.g. ddcBreakVector)
 *  \returns average size of gap between elements of v[], always >= 1
 */
template <class VecT>
inline size_t VectorStride(const VecT& v)
{
    return v.empty() ? 1 : std::max((size_t)1, (size_t)v[v.size()-1]/v.size());
};

//======================================================================



/* generic STL clear-and-swap , should free up memory better than STL clear() */
template <class ContainerT>
void ClearContainer(ContainerT& C)
{
    C.clear();
    ContainerT tmp;
    tmp.swap(C);
}

/* also clears capacity */
template <class T> 
inline void ClearVector(std::vector<T>& V)
{ ClearContainer(V); };

/* also clears capacity */
inline void ClearString(std::string& S)
{ ClearContainer(S); };



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
