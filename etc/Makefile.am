# File: ./etc/Makefile.am
# Package: *
# Description:
#   + data-level automake file
#
# Process this file with Automake to create Makefile.in.
#-----------------------------------------------------------------------

##-----------------------------------------------------------------------
## Includes
#include $(top_srcdir)/m4/common.am

##-----------------------------------------------------------------------
## Data

pkgetc_DATA = \
	$(srcdir)/ddc_local_corpora.cfg \
	$(srcdir)/ddc_server.cfg \
	$(srcdir)/ddc_xml_server.cfg \
	$(srcdir)/ddc_template.xml \
	$(srcdir)/rml.ini

##--- maintainerclean: built by maintainer / by hand
MAINTAINERCLEANFILES = *~ Makefile Makefile.in

EXTRA_DIST = $(pkgetc_DATA)
