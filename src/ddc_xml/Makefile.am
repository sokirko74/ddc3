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

##-----------------------------------------------------------------------
## primary targets

##--- libtool libraries
#lib_LTLIBRARIES = ${lib_1}.la ... ${lib_N}.la
#lib_LTLIBRARIES = libRmlTar.la

##--- executable programs
#bin_PROGRAMS = ${prog_1} ... ${prog_N}
pkgbin_PROGRAMS = ddc_xml

##======================================================================
## sources

ddc_xml_SOURCES = \
 ddc_xml.cpp \
 ../common/string_socket.cpp ../common/string_socket.h \
 ../common/utilit.cpp ../common/utilit.h

#ddc_xml_LDADD =

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
