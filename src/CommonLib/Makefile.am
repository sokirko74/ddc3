## File: src/Makefile.am
## Package: *
## Description:
##   + source-level automake file 
##
## Process this file with Automake to create Makefile.in.
##-----------------------------------------------------------------------

##-----------------------------------------------------------------------
## includes
include $(top_srcdir)/m4/common.am
include $(top_srcdir)/m4/library.am
include $(top_srcdir)/m4/lexyacc.am

##-----------------------------------------------------------------------
## primary targets

##--- libtool libraries
#lib_LTLIBRARIES = ${lib_1}.la ... ${lib_N}.la
lib_LTLIBRARIES = libDDCCommon.la

##======================================================================
## sources

libDDCCommon_la_SOURCES = \
 ddcConfigNoAuto.h \
 utilit.cpp utilit.h \
 string_socket.cpp string_socket.h \
 CHost.cpp CHost.h \
 ddcThread.cpp ddcThread.h \
 ddcLocale.cpp ddcLocale.h \
 ddcLog.cpp ddcLog.h \
 ddcVersion.cpp ddcVersion.h \
 ddcString.cpp ddcString.h \
 utf8xx.cpp utf8xx.h \
 ddcTime.cpp ddcTime.h \
 ddcMMap.h \
 ddcStringEnum.h \
 ptrholder.h \
 ddcCorpusList.h

EXTRA_DIST = \
 bserialize.h \
 config.h \
 cortege.h \
 DDC_common.h \
 ddcConfigAuto.h \
 ddcConfig.h \
 DDCInternalError.h \
 ddcThreadQueue.h \
 GramInfo.h \
 string_tokenizer.h \
 util_classes.h \
 ddcConfigAuto.h.in \
 ddcIconv.h \
 ddcRandom.h \
 ddcObject.h


##-- extra sources
BUILT_SOURCES = \
	 ddcConfigNoAuto.h

##-- extra rules
ddcConfigNoAuto.h: ddcConfigAuto.h
	echo "/* src/CommonLib/ddcConfigNoAuto.h. Generated from ddcConfigAuto.h by make */" >ddcConfigNoAuto.h
	sed 's/^#define \([^ ]*\).*$$/#undef \1/;' ddcConfigAuto.h >>ddcConfigNoAuto.h


##-----------------------------------------------------------------------
## debug

#EXTRA_PROGRAMS = vertest
#vertest_SOURCES = vertest.cc
#vertest_LDADD = libDDCCommon.la

#EXTRA_PROGRAMS = ematest
#ematest_SOURCES = ematest.cc
#ematest_LDADD = libDDCCommon.la

##-----------------------------------------------------------------------
## headers

## --- installable headers: @includedir@/@pkgname@
#pkginclude_HEADERS = ${hfile_1} ... ${hfile_N}

## --- no-install headers
#noinst_HEADERS = nopackage.h

##-----------------------------------------------------------------------
## flags

##--- preprocessor flags
#AM_CPPFLAGS =
#AM_CPPFLAGS = -I. -I$(SRCDIR)/gnulib
#AM_CPPFLAGS = -I. $(ddc_CPPFLAGS)
#AM_CPPFLAGS = -I. -I$(srcdir)/../common
#AM_CPPFLAGS = -I$(srcdir)/../common

##--- compiler flags (cc)
#AM_CFLAGS = $(ddc_WFLAGS) $(ddc_OFLAGS)

##-----------------------------------------------------------------------
## Variables: cleanup

##--- mostlyclean: built by 'make' & commonly rebuilt
#MOSTLYCLEANFILES =

##--- clean:  built by 'make'
#CLEANFILES =

## --- distclean: built by 'configure'
DISTCLEANFILES = \
	ddcConfigNoAuto.h

## -- maintainerclean: built by maintainer / by hand
MAINTAINERCLEANFILES = \
	*~ .*~ Makefile Makefile.in \
	gmon.out

##-----------------------------------------------------------------------
## Variables: distribution
##-----------------------------------------------------------------------


##--- recursion subdirectories for 'make dist'
#DIST_SUBDIRS = $(SUBDIRS)
