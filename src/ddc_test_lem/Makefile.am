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
#include $(top_srcdir)/m4/library.am

##--- executable programs
#bin_PROGRAMS = ${prog_1} ... ${prog_N}
pkgbin_PROGRAMS = ddc_test_lem

##======================================================================
## sources

ddc_test_lem_SOURCES = ddc_test_lem.cpp

ddc_test_lem_LDADD = \
 ../LemmatizerLib/libDDCLemmatizer.la \
 ../MorphWizardLib/libDDCMorphWizard.la \
 ../AgramtabLib/libDDCAgramtab.la \
 ../GraphanLib/libDDCGraphan.la \
 ../StructDictLib/libDDCStructDict.la \
 ../CommonLib/libDDCCommon.la

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
EXTRA_DIST = CMakeLists.txt

##--- recursion subdirectories for 'make dist'
#DIST_SUBDIRS = $(SUBDIRS)
