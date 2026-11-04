#ifndef __ConcordAlgorithm_H_
#define __ConcordAlgorithm_H_

#include "morph_dict/common/utilit.h"
#include "../CommonLib/ddcUtil.h"

void SortWithLists(std::vector<uint32_t>& V, DwordVector& Borders);
void ConvertToVariableInteger(const std::vector<uint32_t>& In,std::vector<uint32_t>& Out);
void DeconvertFromVariableInteger(const uint32_t* in_start, const uint32_t* in_end,  uint32_t* out_start, uint32_t& OutCount);

#endif
