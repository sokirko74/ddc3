# File: ./src/Makefile.am
# Package: *
# Description:
#   + source-level automake file
#
# Process this file with Automake to create Makefile.in.
#-----------------------------------------------------------------------

##-----------------------------------------------------------------------
## Includes
#include $(top_srcdir)/m4/common.am

##-----------------------------------------------------------------------
## Options & Subdirectories

## --- recursion subdirectories
SUBDIRS = \
	CommonLib \
	ConcordLib \
	GraphanLib \
	StructDictLib \
	LemmatizerLib \
	AgramtabLib \
	tinyxml \
	RmlTar \
	jsoncpp \
	PCRE \
	MorphWizardLib \
	ConcordDmnLib \
	\
	ddc_index \
	ddc_union \
	ddc_split \
	ddc_dump \
	ddc_stats \
	ddc_simple \
	ddc_console \
	ddc_daemon \
	ddc_search \
	ddc_xml \
	ddc_struct_dict_loader \
	ddc_morph_gen \
	ddc_test_lem \
	ddc_expand

.PHONY: list-subdirs
list-subdirs:
	@echo $(SUBDIRS)

##-----------------------------------------------------------------------
## Variables: cleanup

##--- mostlyclean: built by 'make' & commonly rebuilt
#MOSTLYCLEANFILES =

##--- clean: built by 'make'
#CLEANFILES =

##--- distclean: built by 'configure'
DISTCLEANFILES = \
	autom4te.cache \
	config.log \
	config.status \
	config.cache

##--- maintainerclean: built by maintainer / by hand
MAINTAINERCLEANFILES = *~ \
	$(PODS:.pod=.txt) \
	Makefile Makefile.in \
	aclocal.m4 \
	configure

##-----------------------------------------------------------------------
## Variables: distribution

##--- extra distribution files
EXTRA_DIST = CMakeLists.txt

##--- recursion subdirectories for 'make dist'
DIST_SUBDIRS = $(SUBDIRS)

##--- dist-hook: when another 'Makefile.am' is overkill
#DISTHOOK_DIRS = subdir
#DISTHOOK_FILES = subdir/file1 subdir/file2

##-----------------------------------------------------------------------
## Variables: installation

##--- instal header hack
## + this should really be done in the corresponding subdirectories with
##   a _HEADERS variable, but that requires a whole mess of autoconf
##   directory variables (one for each subdirectory containing headers)
header_dirs = $(SUBDIRS)

install-data-local:
	for d in $(header_dirs) ; do \
	  test -z "$$d" && continue ;\
	  dh=`find "$$d" -name '*.h' -print` ;\
	  test -z "$$dh" && continue ;\
	  $(MKDIR_P) "$(DESTDIR)$(pkgincdir)/$$d" ;\
	  for f in $$dh ; do \
	      $(INSTALL_HEADER) "$$f" "$(DESTDIR)$(pkgincdir)/$$f" ;\
	  done ;\
	done

uninstall-local:
	for d in $(header_dirs); do \
	  test -z "$$d" || rm -rf "$(DESTDIR)$(pkgincdir)/$$d" ;\
	done
