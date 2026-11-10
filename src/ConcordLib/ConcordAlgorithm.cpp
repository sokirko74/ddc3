#include "StdConc.h"
#include "ConcordAlgorithm.h"
#include <cstring>

using namespace std;





/* CSortedList is a structure, which contains two integer references (to the begin and to the end of a list)
  The class provides a less operator (less by list size).
*/
struct CSortedList : public pair<size_t, size_t>
{
    // return the size of the list
    size_t size() const {return second - first;};

    // less operator (by list size)
    bool operator < (const CSortedList& X) const { return size() < X.size(); };
};

/*
  this procedure "SortWithLists" recieves  vector V which is to sort, and 
  vector Borders, which contains ends of sorted periods in vector V,
  i.e. for i = 1...V.size(),  V[ Borders[i]] ...V[Borders[i-1]] is sorted.
  First the procedure builds  a vector of sorted lists (Lists) from vector  Borders.
  Then it sorts "Lists" by length, so the lists with similar length are now neighbours.
  Then it goes through the "Lists" and units each neighbour lists together and form a new 
  unified list. The procedure goes through the "Lists" until  only  one list is left. 
  This last list is a sorted version of input vector  V, without duplicates.
*/

void SortWithLists(vector<uint32_t>& V,   DwordVector& Borders)
{
    size_t Size = V.size();
    if( Size <= 1  ) return;


    // constructing a division of V by Borders,
    // we need to store not only the end points of sorted chunks but also the
    // beginnings
    size_t ListsCount = Borders.size();
    vector<CSortedList > Lists;
    Lists.reserve(ListsCount);
    for (size_t i=0; i<ListsCount; i++)
    {
        CSortedList P;
        P.first = 0;
        if (i>0)
            P.first = Borders[i-1];
        P.second = Borders[i];
        if (P.size() > 0)
        {
            Lists.push_back(P);
        };
                
    }
    ListsCount = Lists.size();
    sort (Lists.begin(), Lists.end());

    size_t EndListNo;
    vector<uint32_t>* pSaveV = &V;
    vector<uint32_t> Q;

    while (ListsCount > 1)
    {
        EndListNo = 0;
                
        Q.resize(Size);
        size_t CurrentQTail = 0;
                

        size_t ListNo=0;
        for (; ListNo+1 < ListsCount;ListNo+=2)
        {

            vector<uint32_t>::iterator end = set_union//_set_union_unbalanced // 
                (
                    V.begin() + Lists[ListNo].first,                V.begin() + Lists[ListNo].second, 
                    V.begin() + Lists[ListNo+1].first,      V.begin() + Lists[ListNo+1].second,
                    Q.begin() + CurrentQTail);

                        

            Lists[EndListNo].first = CurrentQTail;
            CurrentQTail = end - Q.begin();
            Lists[EndListNo].second = CurrentQTail;
            EndListNo++;
        };

        Q.resize(CurrentQTail); 

        if ( ListNo == ListsCount - 1)
        {
            Q.insert(Q.end(), V.begin()+Lists[ListNo].first, V.begin()+Lists[ListNo].second );
            Lists[EndListNo].first = CurrentQTail;
            Lists[EndListNo].second = CurrentQTail + Lists[ListNo].size();
            EndListNo++;
        };
        ListsCount = EndListNo;

        V.swap (Q);


        // after this procedure V is Q  and Q is V, so 
        // we go further with cycling since now Borders contains ends of lists for V
    };

    if (&V != pSaveV)
    {
        //  if the number of the cycle was odd then we should 
        // swap vectors, since it is vector V that we want to return, not Q
        V.swap(Q);
    };


};




// ==================================================================
//=============  Virtual integers                                               ===========
// ==================================================================

//  the idea of virtual integers was adopted from Lucene-project (http://jakarta.apache.org/lucene)
/*
  A quotation from Lucene: 

  A variable-length format for positive integers is defined where the high-order 
  bit of each byte indicates whether more bytes remain to be read. 
  The low-order seven bits are appended as increasingly more significant 
  bits in the resulting integer value. Thus values from zero to 
  127 may be stored in a single byte, values from 128 to 16,383 may 
  be stored in two bytes, and so on. 
  This provides compression while still being efficient to decode. 
*/


vector<BYTE>::iterator writeVInt(uint32_t Value, vector<BYTE>::iterator out) 
{
    uint32_t i = Value;
    while ((i & ~0x7F) != 0) 
    {
        BYTE b = (BYTE)((i & 0x7f) | 0x80);
        *out = b;
        out++;
        i >>= 7; 
    }
    *out = (BYTE)i; // writing the last byte without 0x80
    out++;
    return out;
}


void ConvertToVariableInteger(const vector<uint32_t>& In, vector<uint32_t>& Out)
{
    size_t count  = In.size();
    vector<BYTE> OutBytes;
    OutBytes.resize(count*5); //== (sizeof(DWORD) / 7)  
    // in principle the size of Out can be more than size of In. For example, when 
    // vector In contains only one large number, then this number can be written in 5 bytes (not 4),
    // since we use only 7 bits from the each byte.

    vector<BYTE>::iterator tail = OutBytes.begin();
    size_t PrevValue  = 0;
    for (int i = 0; i < count; i++)
    {
        if (i > 0) 
            assert (In[i] != PrevValue);
        size_t Value = In[i]-PrevValue;
        tail = writeVInt(Value, tail);
        PrevValue = In[i];
    };
    OutBytes.resize(tail - OutBytes.begin() );
    count = OutBytes.size();
        

    //  converting a list of bytes to to DWORDS
    Out.clear();
    Out.reserve(count);
    for (size_t i =0; i < count; i+=4) 
    {
        uint32_t Value = 0;
        size_t shift = 24;
        for (size_t n=i; n < min (count, i+4); n++)
        {
            Value |= ((uint32_t)OutBytes[n]) << shift;
            shift -= 8;

        };
        Out.push_back ( Value );  
    };


};


/*
// not inline version of the deconverting, but it is more understandable,
//  it contains one cycle, which 
const DWORD* readVInt(DWORD& Value, const DWORD* start, BYTE& OutBitNo) 
{
BYTE b = *start>>OutBitNo;
Value = b  & 0x7F;
for (DWORD shift = 7; (b & 0x80) != 0; shift += 7) 
{
if (OutBitNo == 0)
{
OutBitNo = 24;
start++;
}
else
OutBitNo -= 8;

b = *start>>OutBitNo;
Value |= (b & 0x7F) << shift;
}

if (OutBitNo == 0)
{
OutBitNo = 24;
start++;
}
else
OutBitNo -= 8;

return start;
}
*/

inline void Go(uint32_t& Value, const uint32_t*& start, BYTE& OutBitNo, uint32_t& shift, BYTE& b)
{
    if (OutBitNo == 0)
    {
        OutBitNo = 24;
        start++;
    }
    else
        OutBitNo -= 8;

    b = *start>>OutBitNo;
    Value |= (b & 0x7F) << shift;

    shift += 7;
};


// inline version of readVInt, it uses the fact that a cycle inside the non-inline
//  version can iterate only 4 times  for DWORD

inline const uint32_t* readVInt(uint32_t& Value, const uint32_t* start, BYTE& OutBitNo) 
{
    BYTE b = *start>>OutBitNo;
    Value = b  & 0x7F;
    if ( (b & 0x80) != 0)
    {
        uint32_t shift = 7;
        Go(Value, start, OutBitNo, shift, b);

        if ( (b & 0x80) != 0)
        {
            Go(Value, start, OutBitNo, shift, b);

            if ( (b & 0x80) != 0)
            {
                Go(Value, start, OutBitNo, shift, b);

                if ( (b & 0x80) != 0)
                {
                    Go(Value, start, OutBitNo, shift, b);
                };
        
            }
        }
    }

    if (OutBitNo == 0)
    {
        OutBitNo = 24;
        start++;
    }
    else
        OutBitNo -= 8;

    return start;
}


void DeconvertFromVariableInteger(const uint32_t* in_start, const uint32_t* in_end,  uint32_t* out_start, uint32_t& OutCount)
{
    uint32_t* save_out_start = out_start;
    size_t count  = in_end - in_start;
    if (count == 0) return;

    BYTE OutBitNo = 24;
    size_t i = 0;
    // If the first byte is 0 then we should add the first position (0).
    // After the first position no empty value can occur, since we store here distances 
    // between occurrences, and equal occurrences can not exist in the same sequence
    if ( (*in_start & 0xff000000) == 0)
    {
        *out_start = 0;
        out_start++; 
        OutBitNo-=8;
    };
        
    size_t PrevValue  = 0;
    while (in_start != in_end)
    {
        assert (i < count);
        uint32_t Value;
        in_start = readVInt(Value, in_start, OutBitNo);
        if (Value == 0) break;
                
        PrevValue += Value;
        *out_start = PrevValue;
        out_start++;
                
    };

    OutCount =  out_start - save_out_start;

};


//==============================================================================
// Stream VByte

void ConvertToStreamVByte(const vector<uint32_t>& In, vector<uint32_t>& Out)
{
    size_t n = In.size();
    vector<BYTE> bytes(4 + (n + 3) / 4, 0);
    uint32_t n32 = (uint32_t)n;
    memcpy(&bytes[0], &n32, 4);
    uint32_t prev = 0;
    for (size_t i = 0; i < n; i++) {
        uint32_t d = In[i] - prev;
        prev = In[i];
        int len = d < (1u << 8) ? 1 : d < (1u << 16) ? 2 : d < (1u << 24) ? 3 : 4;
        bytes[4 + i / 4] |= (BYTE)((len - 1) << (2 * (i % 4)));
        for (int b = 0; b < len; b++)
            bytes.push_back((BYTE)(d >> (8 * b)));
    }
    Out.assign((bytes.size() + 3) / 4, 0);
    memcpy(&Out[0], &bytes[0], bytes.size());
}

// the decoding tables: for a control byte, the shuffle of 16 data bytes to 4 numbers and the length of the 4 numbers
struct CStreamVByteTables {
    BYTE ShuffleMask[256][16];
    BYTE GroupLength[256];
    CStreamVByteTables() {
        for (int c = 0; c < 256; c++) {
            int pos = 0;
            for (int i = 0; i < 4; i++) {
                int len = ((c >> (2 * i)) & 3) + 1;
                for (int b = 0; b < 4; b++)
                    ShuffleMask[c][4 * i + b] = (BYTE)(b < len ? pos + b : 0x80);   // 0x80: a zero byte
                pos += len;
            }
            GroupLength[c] = (BYTE)pos;
        }
    }
};
static const CStreamVByteTables StreamVByteTables;

// decodes the numbers [i, n) one by one (the tail of a portion, or everything without SSSE3)
static inline uint32_t StreamVByteScalar(const BYTE* ctrl, const BYTE*& data, size_t i, size_t n, uint32_t last, uint32_t* out)
{
    for (; i < n; i++) {
        int len = ((ctrl[i / 4] >> (2 * (i % 4))) & 3) + 1;
        uint32_t d = 0;
        for (int b = 0; b < len; b++)
            d |= (uint32_t)data[b] << (8 * b);
        data += len;
        last += d;
        out[i] = last;
    }
    return last;
}

#if defined(__x86_64__) || defined(__i386__)
#include <immintrin.h>

__attribute__((target("ssse3")))
static void DeconvertFromStreamVByteSsse3(const BYTE* ctrl, const BYTE* data, const BYTE* end, size_t n, uint32_t* out)
{
    __m128i prev = _mm_setzero_si128();
    size_t g = 0;
    // a group is decoded by a 16-byte load: only while 16 bytes are left in the portion
    for (; g < n / 4 && data + 16 <= end; g++) {
        BYTE c = ctrl[g];
        __m128i v = _mm_shuffle_epi8(_mm_loadu_si128((const __m128i*)data),
                                     _mm_loadu_si128((const __m128i*)StreamVByteTables.ShuffleMask[c]));
        data += StreamVByteTables.GroupLength[c];
        // prefix sums of the 4 distances + the last occurrence of the previous group
        v = _mm_add_epi32(v, _mm_slli_si128(v, 4));
        v = _mm_add_epi32(v, _mm_slli_si128(v, 8));
        v = _mm_add_epi32(v, prev);
        _mm_storeu_si128((__m128i*)(out + 4 * g), v);
        prev = _mm_shuffle_epi32(v, 0xff);
    }
    StreamVByteScalar(ctrl, data, 4 * g, n, (uint32_t)_mm_cvtsi128_si32(prev), out);
}

// __builtin_cpu_init() must precede __builtin_cpu_supports() in a static initializer
static const bool CpuHasSsse3 = [] { __builtin_cpu_init(); return __builtin_cpu_supports("ssse3") != 0; }();
#endif

void DeconvertFromStreamVByte(const uint32_t* in_start, const uint32_t* in_end, uint32_t* out_start, uint32_t& OutCount)
{
    OutCount = 0;
    if (in_end - in_start < 1) return;
    uint32_t n = in_start[0];
    const BYTE* ctrl = (const BYTE*)(in_start + 1);
    const BYTE* data = ctrl + (n + 3) / 4;
    const BYTE* end = (const BYTE*)in_end;
    if (data > end || n > 4 * (size_t)(in_end - in_start))
        throw CExpc("bad Stream VByte occurrences (n=%u, %zi words)", n, (size_t)(in_end - in_start));
#if defined(__x86_64__) || defined(__i386__)
    if (CpuHasSsse3)
        DeconvertFromStreamVByteSsse3(ctrl, data, end, n, out_start);
    else
#endif
        StreamVByteScalar(ctrl, data, 0, n, 0, out_start);
    OutCount = n;
}
