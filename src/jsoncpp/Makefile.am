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
lib_LTLIBRARIES = libDDCjsoncpp.la

##======================================================================
## sources

libDDCjsoncpp_la_SOURCES = \
 json_reader.cpp json_tool.h \
 json_value.cpp json_valueiterator.inl \
 json_writer.cpp version.h.in


noinst_HEADERS = \
 include/json/assertions.h \
 include/json/autolink.h \
 include/json/config.h \
 include/json/features.h \
 include/json/forwards.h \
 include/json/json.h \
 include/json/reader.h \
 include/json/value.h \
 include/json/version.h \
 include/json/writer.h

EXTRA_DIST = \
	CMakeLists.txt \
	include/CMakeLists.txt

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
EXTRA_DIST = CMakeLists.txt

##--- recursion subdirectories for 'make dist'
#DIST_SUBDIRS = $(SUBDIRS)
