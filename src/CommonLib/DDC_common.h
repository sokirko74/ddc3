#ifndef DDC_common_h
#define DDC_common_h

#include "ddcConfig.h" /*-- moo --*/
#include "DDCInternalError.h"

const char  globalTableItemsDelim = '\x2';
const char  globalCountKeyDelim   = '\x02';

/** string global for human-readable version reporting (see also ddcVersion.h) */
const std::string DDCVersionStr = "Dialing DWDS Concordance (DDC), Version " PACKAGE_VERSION ;

#endif
