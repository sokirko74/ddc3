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
## subdirectories
#SUBDIRS = gnulib

##-----------------------------------------------------------------------
## primary targets

##--- executable programs
#bin_PROGRAMS = ${prog_1} ... ${prog_N}
#bin_PROGRAMS = dwdspp moot moot-fstgen moot-pargen

##--- libtool libraries
#lib_LTLIBRARIES = ${lib_1}.la ... ${lib_N}.la
lib_LTLIBRARIES = libDDCAgramtab.la

##--- shared data in @pkgdatadir@
#pkgdata_DATA = ${data_1} ... ${data_N}

##--- manpages -- section is auto-detected
#man_MANS = ${man_1} ... ${man_N}

##======================================================================
## sources

##--- Required sources
#${prog_i}_SOURCES = ...
#${lib_i}_la_SOURCES = ...

##--- Extra (possible) sources
#EXTRA_${prog_i}_SOURCES = ...
#EXTRA_${lib_i}_la_SOURCES = ...

##--- Additional dependencies
#target: dep...

##-- local
libDDCAgramtab_la_SOURCES = \
 agramtab_.cpp agramtab_.h \
 EngGramTab.cpp EngGramTab.h eng_consts.h \
 GerGramTab.cpp GerGramTab.h ger_consts.h \
 RusGramTab.cpp RusGramTab.h rus_consts.h

# ../common/utilit.cpp ../common/utilit.h

noinst_HEADERS = \
 agramtab_.h \
 eng_consts.h \
 EngGramTab.h \
 ger_consts.h \
 GerGramTab.h \
 morph_const.h \
 rus_consts.h \
 RusGramTab.h \
 StdGramtab.h

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
#AM_CPPFLAGS += -I.

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
