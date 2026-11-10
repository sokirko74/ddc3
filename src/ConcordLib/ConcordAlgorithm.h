#ifndef __ConcordAlgorithm_H_
#define __ConcordAlgorithm_H_

#include "nlp_base/common/utilit.h"
#include "CommonLib/ddcUtil.h"

void SortWithLists(std::vector<uint32_t>& V, DwordVector& Borders);
void ConvertToVariableInteger(const std::vector<uint32_t>& In,std::vector<uint32_t>& Out);
void DeconvertFromVariableInteger(const uint32_t* in_start, const uint32_t* in_end,  uint32_t* out_start, uint32_t& OutCount);

// Stream VByte (Lemire, Kurz, Rupp 2017) of the distances between sorted occurrences (index type "svbyte"):
// word 0: the number of occurrences N; then (N+3)/4 control bytes (2 bits per number: its length in bytes - 1,
// 4 numbers per byte), then the bytes of the distances (little endian), padded to a word.
// Decoding is ~7 times faster than DeconvertFromVariableInteger (SSSE3: 4 numbers by one shuffle, no branches).
void ConvertToStreamVByte(const std::vector<uint32_t>& In, std::vector<uint32_t>& Out);
// OutCount = N, out_start must have room for N numbers (N <= 4 * (in_end - in_start))
void DeconvertFromStreamVByte(const uint32_t* in_start, const uint32_t* in_end, uint32_t* out_start, uint32_t& OutCount);

#endif
