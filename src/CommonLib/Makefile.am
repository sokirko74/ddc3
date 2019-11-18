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
 CHost.cpp CHost.h \
 DDCInternalError.h \
 DDC_common.h \
 GramInfo.h \
 bserialize.h \
 config.h \
 cortege.h \
 ddcConfig.h \
 ddcConfigAuto.h \
 ddcCorpusList.h \
 ddcIconv.h \
 ddcLocale.cpp ddcLocale.h \
 ddcLog.cpp ddcLog.h \
 ddcMMap.cpp ddcMMap.h \
 ddcObject.h \
 ddcRandom.h \
 ddcString.cpp ddcString.h \
 ddcStringEnum.h \
 ddcThread.cpp ddcThread.h \
 ddcThreadQueue.h \
 ddcTime.cpp ddcTime.h \
 ddcVersion.cpp ddcVersion.h \
 ptrholder.h \
 string_socket.cpp string_socket.h \
 string_tokenizer.h \
 utf8xx.cpp utf8xx.h \
 util_classes.h \
 utilit.cpp utilit.h

##-- extra sources
nodist_libDDCCommon_la_SOURCES = \
	ddcConfigNoAuto.h

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
	ddcConfigAuto.h \
	ddcConfigNoAuto.h

## -- maintainerclean: built by maintainer / by hand
MAINTAINERCLEANFILES = \
	*~ .*~ Makefile Makefile.in \
	gmon.out

##-----------------------------------------------------------------------
## Variables: distribution
##-----------------------------------------------------------------------

##-- extra distribution files
EXTRA_DIST = \
	ddcConfigAuto.h.in \
	CMakeLists.txt

##--- recursion subdirectories for 'make dist'
#DIST_SUBDIRS = $(SUBDIRS)
