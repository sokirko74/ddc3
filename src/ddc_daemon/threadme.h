//-*- Mode: C++; c-basic-offset: 4; -*-

#ifndef DDC_THREADME_H

#include "../ConcordDmnLib/Server.h"
#include "../CommonLib/utilit.h"
#include "../ConcordLib/ConcCommon.h"
#include "../ConcordDmnLib/Corpora.h"
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

#if HAVE_SYS_RESOURCE_H
#include <sys/resource.h>
#endif

#ifdef HAVE_SYSLOG_H
#include <syslog.h>
#endif

#define USE_PTHREAD 1
#ifdef USE_PTHREAD
# include <pthread.h>
#endif

//-- suppress gcc warnings of the form "ignoring return value of `fread', declared with attribute warn_unused_result [-Wunused-result]"
#pragma GCC diagnostic ignored "-Wunused-result"

#endif /* defined(DDC_THREADME_H) */
