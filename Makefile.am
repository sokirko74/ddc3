# File: ./Makefile.am
# Package:
# Description:
#   + top-level automake file
#
# Process this file with Automake to create Makefile.in.
#-----------------------------------------------------------------------

##-----------------------------------------------------------------------
## includes
include $(top_srcdir)/m4/pod2x.am

#-----------------------------------------------------------------------
# Options & Subdirectories
#-----------------------------------------------------------------------

## --- automake options
#AUTOMAKE_OPTIONS = foreign dist-bzip2 dist-zip
AUTOMAKE_OPTIONS = foreign

## --- recursion subdirectories
SUBDIRS = config doc etc src bin skel
#SUBDIRS += doc
#SUBDIRS += tests

## --- pseudo-deps for '.SUFFIXES'
SUFFIXES += .pc

## --- package config data
#pkgconfig_DATA = @PACKAGE@.pc

##-- for gnulib
ACLOCAL_AMFLAGS = -I m4

#-----------------------------------------------------------------------
# Variables: cleanup
#-----------------------------------------------------------------------
## --- mostlyclean: built by 'make' & commonly rebuilt
#MOSTLYCLEANFILES =

## --- clean: built by 'make'
#CLEANFILES =

## --- distclean: built by 'configure'
DISTCLEANFILES = \
	config.log	\
	config.cache	\
	config.status

## -- maintainerclean: built by maintainer / by hand
MAINTAINERCLEANFILES = *~ \
	$(POD:.pod=.txt) \
	$(PODS:.pod=.html) \
	Makefile Makefile.in \
	aclocal.m4 \
	configure \
	install-sh \
	stamp-h.in \
	config.h.in \
	magic.local \
	magic \
	*.tmp

maintainer-clean-local:
	rm -rf autom4te.cache

#CVSCLEAN_SUBDIRS = $(SUBDIRS)

#CVSCLEANFILES = Makefile.in Makefile


##-----------------------------------------------------------------------
## Additional Variables & Rules: PODS: see m4/pod2x.am

PODS = README.pod

pkgdoc_DATA = \
	AUTHORS \
	COPYING \
	COPYING.LESSER \
	Changes \
	$(PODS:.pod=.txt) \
	$(PODS:.pod=.html)

#-----------------------------------------------------------------------
# Extra: install

all-local:
	mkdir -p log/concord

install-data-local:
	mkdir -p "$(DESTDIR)/$(pkgdir)"/log/concord

#-----------------------------------------------------------------------
# Variables: distribution
#-----------------------------------------------------------------------

## --- extra distribution files
EXTRA_DIST = \
	INSTALL \
	AUTHORS \
	COPYING \
	COPYING.LESSER \
	Changes \
	$(PODS) \
	$(PODS:.pod=.txt) \
	$(PODS:.pod=.html) \
	autoreconf.sh \
	configure

##--- dist-hook: when another 'Makefile.am' is overkill
DISTHOOK_DIRS = log/concord

dist-hook:
	test -z "$(DISTHOOK_DIRS)" || for d in $(DISTHOOK_DIRS); do\
	  mkdir -p $(distdir)/$$d ;\
	done
	test -z "$(DISTHOOK_FILES)" || for f in $(DISTHOOK_FILES); do\
	  cp -p $(srcdir)/$$f $(distdir)/$$f ;\
	done

#dist-bz2: dist-bzip2 ;


#-----------------------------------------------------------------------
# Rules: cleanup
#-----------------------------------------------------------------------
.PHONY: svnclean svnclean-hook

svnclean: maintainer-clean ;

