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
lib_LTLIBRARIES = libDDCConcord.la

##======================================================================
## sources

libDDCConcord_la_SOURCES = \
 CCurl.cpp CCurl.h \
 TermExpander.cpp TermExpander.h \
 BiblExpander.cpp BiblExpander.h \
 \
 FlexLexer.h yyQLexer.cpp yyQLexer.h \
 yyQParser.cpp yyQParser.h \
 \
 Query.h Query.cpp \
 QueryFilter.h QueryFilter.cpp \
 QueryNode.cpp QueryNode.h \
 QueryCompiler.cpp QueryCompiler.h \
 \
 ConcordAlgorithm.cpp ConcordAlgorithm.h \
 ConcHolder.cpp ConcHolder.h \
 Bibliography.cpp Bibliography.h \
 ConcordUnion.cpp \
 HitBorder.cpp HitBorder.h \
 ConcordBibl.cpp \
 IndexMorphXml.cpp \
 IndexSet.cpp IndexSet.h \
 StringIndexator.cpp StringIndexator.h \
 ConcIndexator.cpp ConcIndexator.h \
 ConcordOptions.cpp \
 IndexSetForLoadingStage.cpp IndexSetForLoadingStage.h \
 IndexSetForQueryingStage.cpp IndexSetForQueryingStage.h \
 ConvertFromLoadIndexToWorking.cpp \
 LoadingBinaries.cpp \
 ../PCRE/pcre_rml.cpp ../PCRE/pcre_rml.h \
 ../common/MorphXmlToken.cpp ../common/MorphXmlToken.h \
 ../common/DwdsThesaurus.cpp ../common/DwdsThesaurus.h \
 ConcCommon.h \
 ../common/ddcString.cpp ../common/ddcString.h \
 ../common/utf8xx.h ../common/utf8xx.cpp \
 ../common/ddcRandom.h

noinst_HEADERS = \
 CCurl.h \
 TermExpander.h \
 BiblExpander.h \
 Bibliography.h \
 ConcCommon.h \
 ConcHolder.h \
 ConcIndexator.h \
 ConcordAlgorithm.h \
 DDCLessOperators.h \
 GramInfo.h \
 HitBorder.h \
 IndexSetForLoadingStage.h \
 IndexSetForQueryingStage.h \
 IndexSet.h \
 my_stl.h \
 QueryNode.h \
 QueryCompiler.h \
 SourceFileHolder.h \
 StdConc.h \
 StringIndexator.h \
 yyQLexer.h yyQParser.h FlexLexer.h

# unix_simple_qparse.h MyFlexLexer.h

##-----------------------------------------------------------------------
## special rules: lex/yacc (new)

if HAVE_FLEX
yyQLexer.cpp yyQLexer.h : yyQLexer.l
	$(LEX) $(AM_LFLAGS) -d $<
endif

if HAVE_BISON
yyQParser.cpp yyQParser.h : yyQParser.y
	$(YACC) $(AM_YFLAGS) -v $<
endif

yyQParser.o: yyQParser.cpp yyQParser.h yyQLexer.h
yyQLexer.o: yyQLexer.cpp yyQLexer.h yyQParser.h
QueryParser.o: QueryParser.cpp QueryParser.h yyQParser.h yyQLexer.h

PHONY = yyclean
yyclean:
	rm -f yyQLexer.cpp yyQLexer.h yyQParser.cpp yyQParser.h
	rm -f unix_simple_qlex.cpp unix_simple_qparse.cpp unix_simple_qparse.h

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
	gmon.out \
	yyQLexer.h yyQLexer.cpp yyQParser.h yyQParser.cpp

#	unix_simple_qparse.cpp unix_simple_qparse.h unix_simple_qlex.cpp

##-----------------------------------------------------------------------
## Variables: distribution
##-----------------------------------------------------------------------

##--- extra distribution files
EXTRA_DIST = \
	FlexLexer.h \
	yyQLexer.l yyQLexer.h yyQLexer.cpp \
	yyQParser.y yyQParser.h yyQParser.cpp

##--- recursion subdirectories for 'make dist'
#DIST_SUBDIRS = $(SUBDIRS)
