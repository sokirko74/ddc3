# File: ./bin/Makefile.am
# Package: *
# Description:
#   + data-level automake file
#
# Process this file with Automake to create Makefile.in.
#
# dummy directory for local "staging" in DDC build directory (RML=$(top_builddir))
#-----------------------------------------------------------------------

##-----------------------------------------------------------------------
## Includes
#include $(top_srcdir)/m4/common.am

binfiles ?= \
 ../src/ddc_console/ddc_console \
 ../src/ddc_daemon/ddc_daemon \
 ../src/ddc_index/ddc_index \
 ../src/ddc_search/ddc_search \
 ../src/ddc_simple/ddc_simple \
 ../src/ddc_stats/ddc_stats \
 ../src/ddc_dump/ddc_dump \
 ../src/ddc_union/ddc_union \
 ../src/ddc_split/ddc_split \
 ../src/ddc_morph_gen/ddc_morph_gen \
 ../src/ddc_struct_dict_loader/ddc_struct_dict_loader \
 ../src/ddc_test_lem/ddc_test_lem \
 ../src/ddc_expand/ddc_expand \
 ../src/ddc_xml/ddc_xml

all-local:
	test -z "$(binfiles)" || for f in $(binfiles) ; do \
	  rm -f `basename $$f` ;\
	  $(LN_S) $$f . ;\
	done

##--- maintainerclean: built by maintainer / by hand
MAINTAINERCLEANFILES = *~ Makefile Makefile.in

CLEANFILES = $(notdir $(binfiles))
