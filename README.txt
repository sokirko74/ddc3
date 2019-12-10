    README for package ddc

    Last updated for ddc v2.2.0

DESCRIPTION
    The ddc package contains core C++ utilities for the DWDS/Dialing
    Concordance document indexing system.

    The DDC-2.x branch is maintained in SVN under:

     svn+ssh://svn.code.sf.net/p/ddc-concordance/code/ddc/
     https://svn.code.sf.net/p/ddc-concordance/code/ddc/
     svn://svn.code.sf.net/p/ddc-concordance/code/ddc/

DEPENDENCIES
    ddc-morph >= v2.0.0
        Morphology data.

        In order to use most of the runtime utilities, you will also need a
        set of morphology data files available in the ddc-morph package,
        which should be available wherever you downloaded these sources.

        You should build (and optionally install) this package BEFORE
        attempting to build ddc-morph.

        The ddc-morph sources are maintained in SVN under:

         https://ddc-concordance.svn.sourceforge.net/svnroot/ddc-morph

    libpcre, libpcrecpp
        Perl-compatibile regular expression C library and C++ wrappers.

        URL: http://www.pcre.org/

        Tested version(s): 8.02, 8.39-3

    libcurl (optional)
        If available, libcurl can be used for accessing external HTTP-based
        term expanders from within a running DDC process. DDC should still
        compile and run even if libcurl is unavailable, but e.g. external
        HTTP-based term expanders will be unuseable.

        URL: http://curl.haxx.se/

        Tested version(s): 7.21.0, 7.38.0, 7.52.1

    GNU bison (optional)
        Tested version(s): 2.4.1, 3.0.2, 3.0.4

        If you get errors compiling src/ConcordLib/yyQParser.o, try
        re-extracting the source archive and call

         $ touch src/ConcordLib/yyQParser.cpp src/ConcordLib/yyQParser.h

        before re-compiling.

    GNU flex (optional)
        Tested version(s) 2.5.35, 2.5.39, 2.6.1

        If you get errors compiling src/ConcordLib/yyQLexer.o, try
        re-extracting the source archive and call

         $ touch src/ConcordLib/yyQLexer.cpp src/ConcordLib/yyQLexer.h

        before re-compiling.

INSTALLATION
    Issue the following commands to the shell:

     cd ddc-X.Y.dx-Z       ##-- (or wherever you extracted the ddc distribution)
     sh ./configure
     make
     make install

    To build the ddc morph package, then do:

     cd ..
     cd ddc-morph-X.Y-dx-Z ##-- (or wherever the ddc-morph distribution lives)
     sh ./configure
     make
     make install

    Finally, set the (legacy) environment variable RML to the directory into
    which ddc was installed (by default /usr/local/ddc):

     export RML=/usr/local/ddc

    ... and you ought to be ready to roll. Take a look at the configuration
    files in $RML/etc/ and the example corpora in Test/ to get started.

BUILD OPTIONS
    The 'configure' script supports the following options, among others:

    --prefix=PREFIX
        Installation prefix (default=/usr/local). This package installs
        itself to:

         PREFIX/ddc          ##-- root directory (a.k.a. $RML)
         PREFIX/ddc/bin      ##-- executable programs & scripts
         PREFIX/ddc/etc      ##-- runtime configuration files
         PREFIX/ddc/include  ##-- C++ headers
         PREFIX/lib          ##-- runtime libtool libraries

        Additionally, the package requires a directory PREFIX/ddc/dict
        containing morphology data, which should be installed by the
        ddc-morph package (see "DEPENDENCIES").

    --enable-debug
        Enable debugging flags. Only works for GNU C++ compiler.

    --enable-hires-clock
        Enable high-resolution clock if available. Requires
        "clock_gettime()" function. Enabled by default if "--enable-debug"
        was specified, otherwise disabled by default.

    --enable-json-deep-context
        Enable deep encoding of extra-sentential context tokens in JSON
        output strings. Disabled by default, since it breaks strict
        backwards-compatibility.

    --enable-warnings
        Enable lots of compiler warnings. Only works for GNU C++ compiler.

    --disable-shared
        Disable compilation of shared libraries.

    --without-libcurl
        Force DDC to build without CURL support.

    --with-libiconv-prefix=DIR
        Search for libiconv in DIR/include and DIR/lib.

    --with-static-buflen=SIZE
        Size in bytes of large static internal string buffers
        (default=4096).

    See the output of `./configure --help` for details on additional
    supported options.

KNOWN BUGS
    Many.

AUTHOR
    Alexey Sokirko wrote DDC.

    Bryan Jurish <jurish@bbaw.de> made various improvements and maintains
    the DDC-2.x branch.

