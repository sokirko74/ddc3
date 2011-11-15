# File: ./skel/Makefile.am
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

pkgskel_DATA = ddc-common.sh
pkgskel_SCRIPTS = ddc-server.sh
pkgbin_SCRIPTS = ddc-mkrml.sh

skeldest = $(DESTDIR)$(pkgskeldir)
install-data-hook:
	mkdir -p $(skeldest)/log/concord
	mkdir -p $(skeldest)/etc
	grep '^//' $(srcdir)/../etc/ddc_local_corpora.cfg >$(skeldest)/etc/ddc_local_corpora.cfg
	grep '^//' $(srcdir)/../etc/ddc_server.cfg        >$(skeldest)/etc/ddc_server.cfg
	grep '^//' $(srcdir)/../etc/ddc_xml_server.cfg    >$(skeldest)/etc/ddc_xml_server.cfg
	$(INSTALL_DATA) $(srcdir)/../etc/rml.ini $(skeldest)/etc
	rm -f $(skeldest)/bin && ln -s $(DESTDIR)$(pkgbindir) $(skeldest)/bin
	rm -f $(skeldest)/dict && ln -s $(DESTDIR)$(pkgdir)/dict $(skeldest)/dict

uninstall-hook:
	-rm -rf "$(skeldest)/etc"
	-rm -f "$(skeldest)/bin"
	-rm -f "$(skeldest)/dict"

##--- maintainerclean: built by maintainer / by hand
MAINTAINERCLEANFILES = *~ Makefile Makefile.in

EXTRA_DIST = $(pkgskel_DATA) $(pkgskel_SCRIPTS) $(pkgbin_SCRIPTS)
