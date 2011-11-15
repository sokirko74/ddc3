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
lib_LTLIBRARIES = libDDCGraphan.la

##======================================================================
## sources

libDDCGraphan_la_SOURCES = \
 ../common/gra_descr.cpp ../common/gra_descr.h \
 C_desc.cpp \
 Consent.cpp Consent.h \
 Cs_hiera.cpp \
 GraphmatFile.cpp GraphmatFile.h \
 HtmlConv.cpp \
 Nc_desc.cpp \
 Writegra.cpp \
 abbrev.cpp abbrev.h \
 graline.cpp graline.h \
 Oborots.cpp \
 UnitHolder.cpp UnitHolder.h \
 GraphanDicts.cpp GraphanDicts.h \
 Sentences.cpp

noinst_HEADERS = \
 abbrev.h \
 Consent.h \
 Descriptors.h \
 graline.h \
 GraphanDicts.h \
 GraphmatFile.h \
 HTMLConv.h \
 StdGraph.h \
 UnitHolder.h

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
