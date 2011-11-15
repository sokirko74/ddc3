TARGETS ?= querydoc.html querydoc.pod

REALCLEAN_FILES ?= $(TARGETS)

all: $(TARGETS)

querydoc.xml0: yyQParser.output
	./bison2xml.perl $< > $@ || (rm -f $@; false)

querydoc.html: help2html.xsl querydoc.xml
	xsltproc --stringparam date "`date -R`" -o $@ $^

querydoc.pod: querydoc.xml help2pod.perl
	./help2pod.perl $< > $@ || (rm -f $@; false)

clean:
	test -z "$(CLEAN_FILES)" || rm -f $(CLEAN_FILES)

realclean:
	test -z "$(REALCLEAN_FILES)" || rm -f $(REALCLEAN_FILES)
