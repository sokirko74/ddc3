//  small ddc utilities (formerly in utilit.h)

#ifndef ddcUtil_h
#define ddcUtil_h

#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>
#include <algorithm>

//-- moo: branch prediction macros; see e.g. https://www.geeksforgeeks.org/branch-prediction-macros-in-gcc/
#define likely(x)      __builtin_expect(!!(x), 1)
#define unlikely(x)    __builtin_expect(!!(x), 0)

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
