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

##-----------------------------------------------------------------------
## primary targets

##--- libtool libraries
#lib_LTLIBRARIES = ${lib_1}.la ... ${lib_N}.la
lib_LTLIBRARIES = libDDCStructDict.la

##======================================================================
## sources

libDDCStructDict_la_SOURCES = \
 ItemsContainer.cpp ItemsContainer.h \
 Ross.cpp Ross.h \
 TempArticle.cpp TempArticle.h


noinst_HEADERS = \
 Domen.h \
 Field.h \
 ItemsContainer.h \
 LessDomItem.h \
 Ross.h \
 Signat.h \
 StdRoss.h \
 StructDictConsts.h \
 TempArticle.h \
 TextField.h

##-----------------------------------------------------------------------
## special rules


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
