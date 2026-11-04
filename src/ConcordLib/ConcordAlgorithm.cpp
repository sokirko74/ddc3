#include "StdConc.h"
#include "ConcordAlgorithm.h"

using namespace std;





/*! CSortedList is a structure, which contains two integer references (to the begin and to the end of a list)
  The class provides a less operator (less by list size).
*/
struct CSortedList : public pair<size_t, size_t>
{
    //! return the size of the list
    size_t size() const {return second - first;};

    //! less operator (by list size)
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
