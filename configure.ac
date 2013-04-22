dnl Process this file with autoconf to produce a configure script.
AC_PREREQ(2.5)

dnl Some handy macros
define([THE_PACKAGE_NAME],    [ddc])
define([THE_PACKAGE_VERSION], [2.0.9])
define([THE_PACKAGE_MAINTAINER],  [jurish@bbaw.de])

AC_INIT(THE_PACKAGE_NAME, THE_PACKAGE_VERSION, THE_PACKAGE_MAINTAINER)

dnl source && aux dir
AC_CONFIG_AUX_DIR(config)

dnl canonical target (sets $target, $target_(cpu|vendor|os) : used for bindist)
AC_CANONICAL_TARGET

dnl local autoconf macros
AC_CONFIG_MACRO_DIR([m4])

dnl use automake
AM_INIT_AUTOMAKE(THE_PACKAGE_NAME, THE_PACKAGE_VERSION)

dnl use autoheader
AM_CONFIG_HEADER([src/common/ddcConfigAuto.h])

dnl default prefix
AC_PREFIX_DEFAULT(/usr/local)

#-------------------------------------------------------------
# save user's *FLAGS
#USER_LIBS="$LIBS"
#USER_LDFLAGS="$LDFLAGS"
#USER_CPPFLAGS="$CPPFLAGS"
USER_CFLAGS="$CFLAGS"
USER_CXXFLAGS="$CXXFLAGS"

dnl
dnl check for programs
dnl
AC_PROG_CC
AC_PROG_CXX
AC_LANG(C++)

##vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
## gnulib
dnl gl_EARLY
dnl gl_INIT
## /gnulib
## ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

##----------------------------------------------------------------------
## DISTCHECK: simulate missing development-only packages
AC_ARG_VAR(DISTCHECK,
	[(Maintainer): set to nonempty value to simulate missing development packages])
if test -n "$DISTCHECK" ; then
   test -z "$PERL"  && PERL=no
   #test -z "$DOXYGEN" && DOXYGEN=no
   test -z "$POD2X" && POD2TEXT=no
   test -z "$POD2X" && POD2MAN=no
   test -z "$POD2X" && POD2HTML=no
   test -z "$POD2X" && POD2LATEX=no
   test -z "$FLEX"  && FLEX=no
   test -z "$BISON" && BISON=no
fi
## /DISTCHECK
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

##vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
## flex
##
AC_ARG_VAR(FLEX, [Path to GNU flex; "no" to disable])
if test -z "$FLEX" ; then
  AC_PATH_PROG(FLEX,flex,[no])
fi

AC_MSG_NOTICE([setting FLEX=$FLEX])

if test "$FLEX" = "no"; then
  AC_MSG_WARN([GNU flex is missing, broken, or disabled])
  AC_MSG_WARN([- compilation from .l lexer source files disabled])
fi

AM_CONDITIONAL(HAVE_FLEX,[test "$FLEX" != "no"])
##
## /flex
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

##vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
## bison
##
AC_ARG_VAR(BISON, [Path to GNU bison; "no" to disable])
if test -z "$BISON" ; then
  AC_PATH_PROG(BISON,bison,[no])
fi

AC_MSG_NOTICE([setting BISON=$BISON])

if test "$BISON" = "no"; then
  AC_MSG_WARN([GNU bison is missing, broken, or disabled])
  AC_MSG_WARN([- compilation from .y parser source files disabled])
fi

AM_CONDITIONAL(HAVE_BISON,[test "$BISON" != "no"])
##
## /bison
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

##vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
## flex+bison: automake woes

###-- automake wants these, we want flex & bison
dnl ... and these wreak havoc
dnl AM_PROG_LEX
dnl AC_PROG_YACC
dnl
dnl ... these are goofy too
dnl LEX="$FLEX"
dnl YACC="$BISON"
dnl AC_SUBST(LEX)
dnl AC_SUBST(YACC)
dnl
dnl ... with some hacking in src/libgfsm/Makefile.am, we get:
dnl     : AM_YFLAGS = --defines --fixed-output-files --name-prefix="$*_yy"
AM_PROG_LEX
AC_PROG_YACC
LEX="$FLEX"
YACC="$BISON"
## /flex+bison: automake woes
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


##vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
## autotools magic, Part II
##
dnl v--- needed if Makefile.am uses _LTLIBRARIES targets
AC_PROG_LIBTOOL

dnl v--- for static-only libraries (non-libtool)
dnl AC_PROG_RANLIB

dnl v--- needed if Makefile.am uses lex sources (see above)
dnl AM_PROG_LEX

### --- unmangle user *FLAGS
if test "$CFLAGS" != "$USER_CFLAGS" ; then
  # autoconf likes to set this (to '-g -O2')... who knows why...
  AC_MSG_NOTICE([Restoring user's original CFLAGS="$CFLAGS"])
  CFLAGS="$USER_CFLAGS"
fi
if test "$CXXFLAGS" != "$USER_CXXFLAGS" ; then
  # autoconf likes to set this (to '-g -O2')... who knows why...
  AC_MSG_NOTICE([Restoring user's original CXXFLAGS="$CXXFLAGS"])
  CXXFLAGS="$USER_CXXFLAGS"
fi
## /autotools magic, Part II
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

##----------------------------------------------------------------------
## libs: pthread
AC_SEARCH_LIBS(pthread_create, [pthread])
if test "$ac_cv_search_pthread_create" = "no" ; then
  AC_MSG_ERROR([could not find pthread_create(): ensure that LDFLAGS, LIBS are set to link to libpthread])
fi
## /libs: pthread
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


##----------------------------------------------------------------------
## libs: pcre
dnl AC_CHECK_LIB(pcre, pcre_compile)
AC_SEARCH_LIBS(pcre_compile, [pcre])
if test "$ac_cv_search_pcre_compile" = "no" ; then
  AC_MSG_ERROR([could not find pcre_compile(): ensure that LDFLAGS, LIBS are set to link to libpcre])
fi
## /libs: pcre
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

##----------------------------------------------------------------------
## libs: pcrecpp
dnl AC_SEARCH_LIBS([pcrecpp::RE::FullMatch], [pcrecpp])
dnl AC_MSG_NOTICE([ac_cv_search_pcrecpp__RE__FullMatch="$ac_cv_search_pcrecpp__RE__FullMatch"])
dnl if test "$ac_cv_search_pcrecpp__RE__FullMatch" = "no" ; then
dnl  AC_MSG_ERROR([could not find pcrecpp::RE::FullMatch(): ensure that LDFLAGS, LIBS are set to link to libpcrecpp])
dnl fi

AC_MSG_CHECKING([for C++ class pcrecpp::RE])
LIBS="-lpcrecpp $LIBS"
AC_LINK_IFELSE(
 [AC_LANG_PROGRAM([#include <pcrecpp.h>], [pcrecpp::RE re("foo.*bar");])],
 [HAVE_PCRECPP=yes; AC_MSG_RESULT([found])],
 [HAVE_PCRECPP=no; AC_MSG_RESULT([not found])]
)
if test "$HAVE_PCRECPP" != "yes"; then
  AC_MSG_ERROR([could find C++ class pcrecpp::RE: ensure that LDFLAGS, LIBS are set to link to libpcrecpp])
fi
##
## /libs: pcrecpp
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

##----------------------------------------------------------------------
## libs: m (math)
AC_SEARCH_LIBS(log, [m])
if test "$ac_cv_search_log" = "no" ; then
  AC_MSG_ERROR([could not find log(): ensure that LDFLAGS, LIBS are set to link to libm (math library)])
fi
## /libs: m
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

##----------------------------------------------------------------------
## libs: curl
LIBCURL_CHECK_CONFIG(yes,
	[0.0.0],
	[
	 LIBS="$LIBS $LIBCURL"
	 CPPFLAGS="$CPPFLAGS $LIBCURL_CPPFLAGS"
	],
	[
	 AC_MSG_WARN([libcurl not found: CURL support disabled!])
	])
## /libs: curl
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


##----------------------------------------------------------------------
## defs: static buffer length(s)?
AC_ARG_WITH([static-buflen],
	AC_HELP_STRING([--with-static-buflen=SIZE],
		[size in bytes of static internal string buffers (default=4096)]),
	[ddc_static_buflen="$withval"],
	[ddc_static_buflen="4096"])
AC_MSG_CHECKING([for static buffer size])
AC_MSG_RESULT([$ddc_static_buflen])
AC_DEFINE_UNQUOTED(DDC_STATIC_BUFLEN, $ddc_static_buflen, [size in bytes of static ddc-internal string buffers])
## defs: static buffer length(s)
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

##vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
## debug ?
##
AC_MSG_CHECKING([whether to build debug version])
AC_ARG_ENABLE(debug,
	AC_HELP_STRING([--enable-debug], [build debug version (default=no)]))

if test "$enable_debug" = "yes" ; then
   AC_MSG_RESULT(yes)

   dnl-- this breaks default shared-library building
   dnl-- on debian/sid:
   dnl    + automake 1.9.6
   dnl    + autoconf 2.59
   dnl    + libtool  1.5.20
   dnl
   dnl AC_DISABLE_SHARED
   if test "$GCC" = "yes" ; then
     AC_MSG_NOTICE([GNU C compiler detected: setting appropriate debug flags])
     ddc_OFLAGS="-g"
   else
     AC_MSG_WARN([GNU C compiler not detected: you must use CXXFLAGS to set compiler debugging flags])
     #ddc_OFLAGS="-O3 -funroll-loops -fomit-frame-pointer"
   fi

   AC_DEFINE(DDC_DEBUG_ENABLED,1,
	     [Define this to enable debugging code])
   #DOXY_DEFINES="$DOXY_DEFINES DDC_DEBUG_ENABLED=1"
else
  AC_MSG_RESULT(no)
  if test "$GCC" = "yes"; then
   case "$CXXFLAGS" in
    *-O*|*-g*)
      AC_MSG_NOTICE([CXXFLAGS appears already to contain optimization or debugging flags - skipping])
      ddc_OFLAGS=""
      ;;
    *)
     AC_MSG_NOTICE([GNU C++ compiler detected: setting appropriate optimization flags])
     #ddc_OFLAGS="-O3 -finline-limit-10000 --param inline-unit-growth=1000"
     #ddc_OFLAGS="-O3 -funroll-loops -fomit-frame-pointer" ##-- moo: -O1 and greater imply -fomit-frame-pointer
     ddc_OFLAGS="-pipe -O3 -funroll-loops"
     ;;
   esac
  else
    AC_MSG_WARN([GNU C++ compiler not detected: you must use CXXFLAGS to set compiler optimization flags])
    ddc_OFLAGS=""
  fi
fi

AC_SUBST(ddc_OFLAGS)
##
## /debug ?
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

##vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
## common flags
CPPFLAGS="$CPPFLAGS -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64"
CFLAGS="$CFLAGS $ddc_OFLAGS"
CXXFLAGS="$CXXFLAGS $ddc_OFLAGS -ftemplate-depth-35"

##-- paranoia: always set PIC ("position independent code") flags
##    + use autoconf --with-pic
#CPPFLAGS="$CPPFLAGS -DPIC"
#CFLAGS="$CFLAGS -fPIC"
#CXXFLAGS="$CXXFLAGS -fPIC"

##-- final notice: flags
AC_MSG_NOTICE([CPPFLAGS="$CPPFLAGS"])
AC_MSG_NOTICE([CFLAGS="$CFLAGS"])
AC_MSG_NOTICE([CXXFLAGS="$CXXFLAGS"])
##
## /flags:common
##---------------------------------------------------------------

#---------------------------------------------------------------
# get real prefix
AC_CACHE_CHECK([for installation prefix], [ac_cv_install_prefix],
	[if test "$prefix" = "NONE" ; then
	   ac_cv_install_prefix="/usr/local"
	 else
           ac_cv_install_prefix="$prefix"
	 fi
	])
dnl #  ... and add it to our flags
dnl CPPFLAGS="$CPPFLAGS -I${ac_cv_install_prefix}/include"
dnl LDFLAGS="$LDFLAGS -L${ac_cv_install_prefix}/lib"

##---------------------------------------------------------------
## special dirs

dnl incpkgdir="\${includedir}/AC_PACKAGE_NAME"
dnl AC_SUBST(incpkgdir)

pkgdir="\${prefix}/AC_PACKAGE_NAME"
AC_SUBST(pkgdir)

pkgbindir="\${pkgdir}/bin"
AC_SUBST(pkgbindir)

pkgincdir="\${pkgdir}/include"
AC_SUBST(pkgincdir)

pkgetcdir="\${pkgdir}/etc"
AC_SUBST(pkgetcdir)

pkgskeldir="\${pkgdir}/skel"
AC_SUBST(pkgskeldir)

dnl pkgdictdir="\${pkgdir}/dict"
dnl AC_SUBST(pkgdictdir)

## /special dirs
##---------------------------------------------------------------


##---------------------------------------------------------------
## functions
dnl AC_CHECK_FUNC(strdup,[AC_DEFINE(HAVE_STRDUP,1,[Define this if you have the strdup() function])])

AC_CHECK_FUNCS([erand48 jrand48 nrand48 rand_r])

## /functions
##---------------------------------------------------------------

##---------------------------------------------------------------
## pkg-config (expunged)


##vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
## version-info
##
DDC_VERSION_MAJOR=`[echo ${PACKAGE_VERSION} | sed -e's/^\([0-9][0-9]*\)\..*/\1/']`
test -z "$DDC_VERSION_MAJOR" -o "$DDC_VERSION_MAJOR" = "$PACKAGE_VERSION" \
  && DDC_VERSION_MAJOR=0

DDC_VERSION_MINOR=`[echo ${PACKAGE_VERSION} | sed -e's/^[^\.]*\.0*\([0-9][0-9]*\).*/\1/']`
test -z "$DDC_VERSION_MINOR" -o "$DDC_VERSION_MINOR" = "$PACKAGE_VERSION" \
  && DDC_VERSION_MINOR=0

DDC_VERSION_MICRO=`[echo ${PACKAGE_VERSION} | sed -e's/^[^\.]*\.[^\.]*\.[^0-9]*0*\([0-9][0-9]*\).*/\1/']`
test -z "$DDC_VERSION_MICRO" -o "$DDC_VERSION_MICRO" = "$PACKAGE_VERSION" \
  && DDC_VERSION_MICRO=0

AC_DEFINE_UNQUOTED(DDC_VERSION_MAJOR, $DDC_VERSION_MAJOR, [Major ddc version])
AC_DEFINE_UNQUOTED(DDC_VERSION_MINOR, $DDC_VERSION_MINOR, [Minor ddc version])
AC_DEFINE_UNQUOTED(DDC_VERSION_MICRO, $DDC_VERSION_MICRO, [Micro ddc version])
AC_SUBST(DDC_VERSION_MAJOR)
AC_SUBST(DDC_VERSION_MINOR)
AC_SUBST(DDC_VERSION_MICRO)
##
## /version-info
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


##vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
## perl
AC_ARG_VAR(PERL, [Path to your perl interpreter, "no" to disable])
if test -z "$PERL" ; then
  AC_PATH_PROG(PERL,[perl],[no])
fi
if test -z "$PERL" -o "$PERL" = "no"; then
  AC_MSG_WARN([perl missing or disabled (probably not fatal)])
  dnl AC_MSG_WARN([- generation of alternate documentation formats disabled.])
  PERL=no
fi
AC_SUBST(PERL)
## /perl
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


##vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
## documentation (mostly expunged)
##
AC_ARG_WITH(docdir,
	AC_HELP_STRING([--with-docdir=DIR],
		[install documentation in DIR/ (default=PREFIX/ddc/doc)]),
	[pkgdocdir="$withval"],
	[pkgdocdir="\${pkgdir}/doc"])
#docpkgdir="\${docdir}/\${PACKAGE}"
AC_SUBST(pkgdocdir)

##-- expunged (see gfsmxl for a template)

  ##-- docs:pod2x
  ##
  AC_ARG_VAR(POD2TEXT, [Path to perl 'pod2text' script; "no" for none])
  AC_ARG_VAR(POD2MAN,  [Path to perl 'pod2man' script; "no" for none])
  AC_ARG_VAR(POD2HTML, [Path to perl 'pod2html' script; "no" for none])
  AC_ARG_VAR(POD2LATEX,[Path to perl 'pod2latex' script; "no" for none])
  if test -z "$POD2TEXT" ; then
     AC_PATH_PROG(POD2TEXT,pod2text,[no])
  fi
  if test -z "$POD2MAN"  ; then
     AC_PATH_PROG(POD2MAN,pod2man,[no])
  fi
  if test -z "$POD2HTML" ; then
     AC_PATH_PROG(POD2HTML,pod2html,[no])
  fi
  if test -z "$POD2LATEX"; then
     AC_PATH_PROG(POD2LATEX,pod2latex,[no])
  fi
  AC_SUBST(POD2TEXT)
  AC_SUBST(POD2MAN)
  AC_SUBST(POD2HTML)
  AC_SUBST(POD2LATEX)
  ##
  ##--/docs:pod2x

AM_CONDITIONAL(HAVE_POD2TEXT,    [test -n "$POD2TEXT"  -a "$POD2TEXT"  != "no"])
AM_CONDITIONAL(HAVE_POD2MAN,     [test -n "$POD2MAN"   -a "$POD2MAN"   != "no"]) 
AM_CONDITIONAL(HAVE_POD2HTML,    [test -n "$POD2HTML"  -a "$POD2HTML"  != "no"])
AM_CONDITIONAL(HAVE_POD2LATEX,   [test -n "$POD2LATEX" -a "$POD2LATEX" != "no"])

##
## /Documentation
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


##vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
## warnings ?
##
AC_MSG_CHECKING([whether to display compiler warnings])
AC_ARG_ENABLE(warnings,
	AC_HELP_STRING([--enable-warnings],[enable compiler warnings (default=disabled)]))

if test "$enable_warnings" = "yes" ; then
   AC_MSG_RESULT(yes)
   if test "$GCC" = "yes"; then
     AC_MSG_NOTICE([GNU C compiler detected: setting appropriate warning flags])
     CXXFLAGS="$CXXFLAGS -Wall" #-Winline
   else
     AC_MSG_NOTICE([GNU C compiler not detected: not setting warning flags])
   fi
else
  AC_MSG_RESULT(no)
fi
##
## /warnings
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

##vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
## autotest
dnl AC_CONFIG_TESTDIR(tests,tests)
## /autotest
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

dnl
dnl output
dnl
AC_CONFIG_FILES(config/Makefile)
AC_CONFIG_FILES(doc/Makefile)
AC_CONFIG_FILES(etc/Makefile)
AC_CONFIG_FILES(src/common/Makefile)
AC_CONFIG_FILES(src/ConcordLib/Makefile)
AC_CONFIG_FILES(src/GraphanLib/Makefile)
AC_CONFIG_FILES(src/StructDictLib/Makefile)
AC_CONFIG_FILES(src/LemmatizerLib/Makefile)
AC_CONFIG_FILES(src/AgramtabLib/Makefile)
AC_CONFIG_FILES(src/tinyxml/Makefile)
AC_CONFIG_FILES(src/RmlTar/Makefile)
AC_CONFIG_FILES(src/MorphWizardLib/Makefile)
AC_CONFIG_FILES(src/ConcordDmnLib/Makefile)
AC_CONFIG_FILES(src/ddc_index/Makefile)
AC_CONFIG_FILES(src/ddc_simple/Makefile)
AC_CONFIG_FILES(src/ddc_console/Makefile)
AC_CONFIG_FILES(src/ddc_daemon/Makefile)
AC_CONFIG_FILES(src/ddc_stats/Makefile)
AC_CONFIG_FILES(src/ddc_search/Makefile)
AC_CONFIG_FILES(src/ddc_xml/Makefile)
AC_CONFIG_FILES(src/ddc_struct_dict_loader/Makefile)
AC_CONFIG_FILES(src/ddc_morph_gen/Makefile)
AC_CONFIG_FILES(src/ddc_file_lem/Makefile)
AC_CONFIG_FILES(src/ddc_test_lem/Makefile)
AC_CONFIG_FILES(src/ddc_graphmat_thick/Makefile)
AC_CONFIG_FILES(src/ddc_expand/Makefile)
AC_CONFIG_FILES(src/Makefile)
AC_CONFIG_FILES(skel/Makefile)
AC_CONFIG_FILES(bin/Makefile)
dnl--
dnl AC_CONFIG_FILES(doc/libddc/mainpage.dox doc/libddc/libddc.doxy doc/libddc/Makefile)
dnl AC_CONFIG_FILES(doc/programs/Makefile)
dnl AC_CONFIG_FILES(doc/tutorial/Makefile)
dnl AC_CONFIG_FILES(doc/Makefile)
dnl AC_CONFIG_FILES(tests/atlocal tests/Makefile)
AC_CONFIG_FILES(Makefile)
AC_OUTPUT
