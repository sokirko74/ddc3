#ifndef graspace_h
#define graspace_h

#include "morph_dict/common/utilit.h"
#include "../CommonLib/ddcUtil.h"

#define   SEOLN        (unsigned char) 171
#define   SSpace       (unsigned char) 129
#define   STab         '\x10'


// max length of the token
const size_t CriticalTokenLength = 255;

// length of the token and its graphematical descriptors 
const size_t CriticalGraphemLineLength = CriticalTokenLength*2;

#endif
