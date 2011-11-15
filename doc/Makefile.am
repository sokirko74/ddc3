# File: ./data/Makefile.am
# Package: *
# Description:
#   + data-level automake file
#
# Process this file with Automake to create Makefile.in.
#-----------------------------------------------------------------------

##-----------------------------------------------------------------------
## Includes
include $(top_srcdir)/m4/pod2x.am

##-----------------------------------------------------------------------
## pods

HTML_PODS = ddc_opt.pod
POD_HTML  = $(HTML_PODS:.pod=.html)
man5_PODS = $(HTML_PODS) ddc_query.pod

POD2MANFLAGS ?= \
	--utf8 \
	--center="DDC Corpus Indexing System" \
	--release="$(PACKAGE_VERSION)"

POD2HTMLFLAGS = \
	 --htmlroot="." --css="pod2x.css"

ddc_query.html:
	;

all-local: $(man5_MANS) $(POD_HTML)

##-----------------------------------------------------------------------
## Data

man5_MANS = $(man5_PODS:.pod=.5)

pkgdoc_DATA = \
 $(srcdir)/DDC_ChangeLog.txt \
 $(srcdir)/DDCReadme.pdf \
 $(srcdir)/DDC_Unix.txt \
 $(srcdir)/Graphan.htm \
 $(srcdir)/GraphanReadmeRus.txt \
 $(srcdir)/Graphan_Unix.txt \
 $(srcdir)/Morph_UNIX.txt \
 \
 $(srcdir)/ddc_query.html $(srcdir)/querydoc.css \
 $(srcdir)/pod2x.css $(POD_HTML)

##-- clean: build by make
CLEANFILES = $(POD_CLEANFILES)

##--- maintainerclean: built by maintainer / by hand
MAINTAINERCLEANFILES = *~ Makefile Makefile.in

EXTRA_DIST = $(pkgdoc_DATA) $(man5_MANS)
