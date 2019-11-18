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
lib_LTLIBRARIES = libDDCTinyXml.la

##======================================================================
## sources

libDDCTinyXml_la_SOURCES = \
 tinystr.cpp tinystr.h \
 tinyxml.cpp tinyxml.h \
 tinyxmlerror.cpp \
 tinyxmlparser.cpp \
 lex_util.cpp lex_util.h \
 action_store.cpp action_store.h \
 node_set.cpp node_set.h \
 tokenlist.cpp tokenlist.h \
 xml_util.cpp xml_util.h \
 xpath_expression.cpp xpath_expression.h \
 xpath_processor.cpp xpath_processor.h \
 xpath_stack.cpp xpath_stack.h \
 xpath_static.cpp xpath_static.h \
 xpath_stream.cpp xpath_stream.h \
 xpath_syntax.cpp xpath_syntax.h

EXTRA_DIST = \
 action_store.cpp \
 action_store.h \
 byte_stream.h \
 htmlutil.cpp \
 htmlutil.h \
 lex_token.h \
 lex_util.cpp \
 lex_util.h \
 main.cpp \
 node_set.cpp \
 node_set.h \
 tinystr.cpp \
 tinystr.h \
 tinyxml.cpp \
 tinyxmlerror.cpp \
 tinyxml.h \
 tinyxmlparser.cpp \
 tinyxpath_conf.h \
 tokenlist.cpp \
 tokenlist.h \
 xml_util.cpp \
 xml_util.h \
 xpath_expression.cpp \
 xpath_expression.h \
 xpath_processor.cpp \
 xpath_processor.h \
 xpath_stack.cpp \
 xpath_stack.h \
 xpath_static.cpp \
 xpath_static.h \
 xpath_stream.cpp \
 xpath_stream.h \
 xpath_syntax.cpp \
 xpath_syntax.h \
 CMakeLists.txt

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

##--- recursion subdirectories for 'make dist'
#DIST_SUBDIRS = $(SUBDIRS)
