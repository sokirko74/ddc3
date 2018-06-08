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
 ddcMMap.h

# unix_simple_qparse.h MyFlexLexer.h

##-----------------------------------------------------------------------
## debug

#EXTRA_PROGRAMS = vertest
#vertest_SOURCES = vertest.cc
#vertest_LDADD = libDDCCommon.la

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
#DISTCLEANFILES =

## -- maintainerclean: built by maintainer / by hand
MAINTAINERCLEANFILES = \
	*~ .*~ Makefile Makefile.in \
	gmon.out

##-----------------------------------------------------------------------
## Variables: distribution
##-----------------------------------------------------------------------

##--- extra distribution files
#EXTRA_DIST = 

##--- recursion subdirectories for 'make dist'
#DIST_SUBDIRS = $(SUBDIRS)
