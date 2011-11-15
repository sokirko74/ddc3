/* 
 * Putting autoheader files within the #ifndef/#endif idiom (below)
 * is potentially a BAD IDEA, since we might need to (re-)define
 * the autoheader-generated preprocessor symbols (e.g. after
 * (#include)ing in some config.h from another autoheader package
 */
#include "ddcConfigNoAuto.h"
#include "ddcConfigAuto.h"

/* 
 * Define a sentinel preprocessor symbol _*_CONFIG_H, just
 * in case someone wants to check whether we've already
 * (#include)d this file ....
 */
#ifndef _DDC_CONFIG_H
#define _DDC_CONFIG_H

#endif /* _DDC_CONFIG_H */
