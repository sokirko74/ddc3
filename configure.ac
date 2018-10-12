dnl Process this file with autoconf to produce a configure script.
AC_PREREQ(2.5)

dnl Some handy macros
define([THE_PACKAGE_NAME],    [ddc])
define([THE_PACKAGE_VERSION], [2.1.18-pre1])
define([THE_PACKAGE_MAINTAINER],  [jurish@bbaw.de])
AC_INIT(THE_PACKAGE_NAME, THE_PACKAGE_VERSION, THE_PACKAGE_MAINTAINER)

dnl source && aux dir
AC_CONFIG_AUX_DIR(config)

dnl canonical target (sets $target, $target_(cpu|vendor|os) : used for bindist)
AC_CANONICAL_TARGET

dnl local autoconf macros
AC_CONFIG_MACRO_DIR([m4])

dnl use automake
dnl AM_INIT_AUTOMAKE(THE_PACKAGE_NAME, THE_PACKAGE_VERSION)
AM_INIT_AUTOMAKE([subdir-objects])

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
## headers: for mtime
AC_CHECK_HEADERS_ONCE([sys/types.h sys/stat.h])
## /headers: mtime
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

##----------------------------------------------------------------------
## headers: for malloc_trim
AC_CHECK_HEADERS_ONCE([malloc.h])
AC_CHECK_FUNCS([malloc_trim])
## /headers: malloc_trim
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

##----------------------------------------------------------------------
## headers: struct rlimit, RLIMIT_NOFILE
AC_CHECK_HEADERS_ONCE([sys/resource.h])
## /headers: rlimit
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

##----------------------------------------------------------------------
## headers: syslog
AC_CHECK_HEADERS_ONCE([syslog.h])
## /headers: syslog
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

##----------------------------------------------------------------------
## headers: for gethostname(), gethostbyname()
AC_CHECK_HEADERS_ONCE([unistd.h netdb.h])
## /headers: gethostname
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

##----------------------------------------------------------------------
## headers: time.h
AC_CHECK_HEADERS_ONCE([time.h])
## /headers: time.h
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

###----------------------------------------------------------------------
## headers: int types
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
## /headers: mtime
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

##----------------------------------------------------------------------
## libs: jemalloc

AC_CHECK_LIB(jemalloc, mallocx,
	[ddc_have_jemalloc="yes"],
	[ddc_have_jemalloc="no"])

##--------
AC_ARG_ENABLE([jemalloc],
	AC_HELP_STRING([--enable-jemalloc],[enable jemalloc allocator (default=if avavilable)]),
	[ddc_enable_jemalloc="$enableval"],
	[ddc_enable_jemalloc="auto"])
AC_MSG_CHECKING([whether to enable jemalloc allocator])
if test "$ddc_enable_jemalloc" = "no" ; then
   AC_MSG_RESULT([no])
elif test "$ddc_enable_jemalloc" = "yes" ; then  
   AC_MSG_RESULT([yes])
   if test "$ddc_have_jemalloc" = "no" ; then
     AC_MSG_FAILURE([cannot enable jemalloc because your system does not seem to support it!])
   fi
elif test "$ddc_have_jemalloc" = "no" ; then
   AC_MSG_RESULT([no (libjemalloc not found)])
   ddc_enable_jemalloc=no
else
   AC_MSG_RESULT([yes])
   ddc_enable_jemalloc=yes
fi

if test "$ddc_enable_jemalloc" = "yes" ; then
  LIBS="-ljemalloc $LIBS"
fi

## /libs:jemalloc
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


##----------------------------------------------------------------------
## libs: pthread
AC_SEARCH_LIBS(pthread_create, [pthread])
if test "$ac_cv_search_pthread_create" = "no" ; then
  AC_MSG_ERROR([could not find pthread_create(): ensure that LDFLAGS, LIBS are set to link to libpthread])
fi
AC_DEFINE(HAVE_PTHREAD,1, [Define this to enable support for POSIX threads (pthreads)])
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
## libs: iconv
AM_ICONV
if test "$am_cv_func_iconv" != "yes"; then
  AC_MSG_ERROR([could not find working libiconv: ensure that CPPFLAGS, LDFLAGS, and LIBS are set to use to libiconv])
else
  LIBS="$LIBICONV $LIBS"
fi
## /libs: iconv
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

##----------------------------------------------------------------------
## libs: curl
LIBCURL_CHECK_CONFIG(yes,
	[0.0.0],
	[
	 ddc_have_curl=yes
	 LIBS="$LIBCURL $LIBS"
	 CPPFLAGS="$CPPFLAGS $LIBCURL_CPPFLAGS"
	],
	[
	 ddc_have_curl=no
	 AC_MSG_WARN([libcurl not found: CURL support disabled!])
	])

AC_CHECK_DECL(CURLOPT_UNIX_SOCKET_PATH,
	[ddc_have_curl_unix_support=yes],
	[ddc_have_curl_unix_support=no],
	[
#include <curl/curl.h>
	])
if test "$ddc_have_curl" = "yes" -a "$ddc_have_curl_unix_support" = "yes" ; then
  AC_DEFINE(DDC_HAVE_CURL_UNIX_SUPPORT, 1, [define this if libcurl supports CURLOPT_UNIX_SOCKET_PATH (libcurl >= v7.40.0)])
fi

## /libs: curl
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

##----------------------------------------------------------------------
## unix socket URLs
AC_ARG_ENABLE([curl-unix-urls],
	AC_HELP_STRING([--enable-curl-unix-urls],[disable UNIX socket URLs for CCurl]),
	[ddc_enable_curl_unix_urls="$enableval"],
	[ddc_enable_curl_unix_urls="yes"])

AC_MSG_CHECKING([whether to enable UNIX socket URL conventions])
if  test "$ddc_enable_curl_unix_urls" = "no" ; then
   AC_MSG_RESULT([no])
else
   AC_MSG_RESULT([yes])
   AC_DEFINE([DDC_ENABLE_CURL_UNIX_URLS],1,[Define this to enable UNIX socket URL parsing]) 
fi

##----------------------------------------------------------------------
## unix sockets

##--------
ddc_have_unix_socket_headers="yes"
AC_CHECK_HEADERS([sys/types.h sys/socket.h sys/un.h],
			      [],
			      [ddc_have_unix_socket_headers=no])
if test "$ddc_have_unix_socket_headers" = "yes" ; then
  AC_DEFINE([DDC_HAVE_UNIX_SOCKET_HEADERS],1,[Define this if you have the UNIX socket headers sys/types.h, sys/socket.h, sys/un.h])
fi

##--------
AC_CHECK_DECL(CURL_SOCKOPT_ALREADY_CONNECTED,
	[ddc_have_curl_already_connected=yes],
	[ddc_have_curl_already_connected=no],
	[
#include <curl/curl.h>
	])
if test "$ddc_have_curl_already_connected" = "yes" ; then
  AC_DEFINE(DDC_HAVE_CURL_ALREADY_CONNECTED, 1, [define this if libcurl supports CURL_SOCKOPT_ALREADY_CONNECTED (libcurl >= v7.21.5)])
fi


##--------
AC_ARG_ENABLE([curl-unix-sockets],
	AC_HELP_STRING([--enable-curl-unix-sockets],[enable local UNIX socket handlers for libcurl (default=guess)]),
	[ddc_enable_curl_unix_sockets="$enableval"],
	[ddc_enable_curl_unix_sockets="guess"])
AC_MSG_CHECKING([whether to enable curl UNIX socket handlers])
if test "$ddc_enable_curl_unix_sockets" = "no" ; then
   AC_MSG_RESULT([no])
elif test "$ddc_enable_curl_unix_sockets" = "yes" ; then
   AC_MSG_RESULT([yes])
else
  ##-- guess
  if test "$ddc_have_curl" = "no" ; then
     AC_MSG_RESULT([no (libcurl not available)])
     ddc_enable_curl_unix_sockets=no
  elif test "$ddc_have_unix_socket_headers" = "no" ; then
     AC_MSG_RESULT([no (UNIX socket headers not found)])
     ddc_enable_curl_unix_sockets=no
  elif test "$ddc_have_curl_unix_support" = "yes" ; then
     AC_MSG_RESULT([no (not needed)])
     ddc_enable_curl_unix_sockets=no
  else
     AC_MSG_RESULT([yes])
     ddc_enable_curl_unix_sockets=yes
  fi
fi

if test "$ddc_enable_curl_unix_sockets" = "yes" ; then
  AC_DEFINE([DDC_ENABLE_CURL_UNIX_SOCKETS],1,[Define this to enable curl UNIX socket support emulation (libcurl < v7.40.0)])
fi

## /unix sockets
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

##----------------------------------------------------------------------
## mmap

##--------
AC_CHECK_HEADERS([sys/stat.h sys/mman.h], [ddc_have_mmap_headers=yes], [ddc_have_mmap_headers=no])
AC_CHECK_FUNCS([mmap],[ddc_have_mmap="yes"],[ddc_have_mmap="no"])

##--------
AC_ARG_ENABLE([mmap],
	AC_HELP_STRING([--enable-mmap],[enable mmap virtual memory support (default=guess)]),
	[ddc_enable_mmap="$enableval"],
	[ddc_enable_mmap="guess"])
AC_MSG_CHECKING([whether to enable mmap virtual memory support])
if test "$ddc_enable_mmap" = "no" ; then
   AC_MSG_RESULT([no])
elif test "$ddc_enable_mmap" = "yes" ; then  
   AC_MSG_RESULT([yes])
   if test "$ddc_have_mmap_headers" = "no" -o "$ddc_have_mmap" = "no" ; then
     AC_MSG_FAILURE([cannot enable mmap because your system does not seem to support it!])
   fi
else
  ##-- guess
  if test "$ddc_have_mmap_headers" = "no" ; then
     AC_MSG_RESULT([no (mmap headers not found)])
     ddc_enable_mmap=no
  elif test "$ddc_have_mmap" = "no" ; then
     AC_MSG_RESULT([no (mmap function not found)])
     ddc_enable_mmap=no
  else
     AC_MSG_RESULT([yes])
     ddc_enable_mmap=yes
  fi
fi

if test "$ddc_enable_mmap" = "yes" ; then
  AC_DEFINE([DDC_ENABLE_MMAP],1,[Define this to enable mmap virtual memory support])
fi

## /mmap
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

##----------------------------------------------------------------------
## defs: static buffer length(s)?
AC_ARG_WITH([static-buflen],
	AC_HELP_STRING([--with-static-buflen=SIZE],
		[size in bytes of large static internal string buffers (default=4096)]),
	[ddc_static_buflen="$withval"],
	[ddc_static_buflen="4096"])
AC_MSG_CHECKING([for static buffer size])
AC_MSG_RESULT([$ddc_static_buflen])
AC_DEFINE_UNQUOTED(DDC_STATIC_BUFLEN, $ddc_static_buflen, [size in bytes of potentially large static ddc-internal string buffers])
## defs: static buffer length(s)
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

##----------------------------------------------------------------------
## funcs: strerror_r
AC_CHECK_FUNC(strerror_r)
if test "$ac_cv_func_strerror_r" = "yes" ; then
  AC_DEFINE_UNQUOTED(HAVE_STRERROR_R, 1, [Define this if you have a working strerror_r() function])
fi
## funcs: strerror_r
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

##----------------------------------------------------------------------
## defs: json-deep-context
AC_ARG_ENABLE([json-deep-context],
	AC_HELP_STRING([--enable-json-deep-context],
		[enable deep encoding of extra-sentential context tokens in JSON output strings (default=no)]),
		[ddc_json_deep_context="$enableval"],
		[ddc_json_deep_context="no"])
AC_MSG_CHECKING([whether to enable deep encoding of context tokens in JSON output strings])
AC_MSG_RESULT([$ddc_json_deep_context])
if test "$ddc_json_deep_context" != "no" ; then
  AC_DEFINE_UNQUOTED(DDC_JSON_DEEP_CONTEXT, 1, [Enable deep encoding of extra-sentential context tokens in JSON output strings?])
fi
## defs: json-deep-context
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

##----------------------------------------------------------------------
## defs: hires-clock (after debug)
AC_ARG_ENABLE([hires-clock],
	AC_HELP_STRING([--enable-hires-clock],
		[enable high-resolution clock? (default=debug-mode only)]),
		[ddc_hires_clock="$enableval"],
		[ddc_hires_clock="$enable_debug"])
AC_MSG_CHECKING([whether to enable high-resolution clock])
test "$ddc_hires_clock" = "yes" || ddc_hires_clock=no
AC_MSG_RESULT([$ddc_hires_clock])

AC_CHECK_FUNC(clock_gettime,
	[ddc_have_clock_gettime=yes],
	[ddc_have_clock_gettime=no])
if test "$ddc_have_clock_gettime" = "yes" ; then
    AC_DEFINE(HAVE_CLOCK_GETTIME, 1, [Define this if your system has the clock_gettime() function])
else
  if test "$ddc_hires_clock" != "no" ; then
    AC_MSG_WARN([could not find clock_gettime(): high-resolution clock disabled])
  fi
  ddc_hires_clock=no
fi

if test "$ddc_hires_clock" != "no" ; then
  AC_DEFINE(DDC_USE_HIRES_CLOCK, 1, [Define this to enable high-resolution clock - requires clock_gettime()])
fi
## defs: hires-clock
##^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


##vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
## common flags
CPPFLAGS="$CPPFLAGS -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64"
CFLAGS="$CFLAGS $ddc_OFLAGS"
CXXFLAGS="$CXXFLAGS $ddc_OFLAGS -ftemplate-depth-64"

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

dnl ---------------------------------------------------------------
dnl pkg-config : program
dnl
AC_ARG_VAR(PKG_CONFIG, [How to run the pkg-config program])
AC_ARG_VAR(PKG_CONFIG_PATH, [Directories to search for pkg-config])
if test -z "$PKG_CONFIG" ; then
  AC_PATH_PROG(PKG_CONFIG,pkg-config,[])
fi
dnl pkg-config: destination directory
AC_ARG_WITH(pkgconfig-dir,
	AS_HELP_STRING([--with-pkgconfig-dir=DIR],[install pkg-config metafile(s) in DIR (default=LIBDIR/pkgconfig)]),
	[ac_cv_pkgconfigdir="$withval"])
if test -z "$ac_cv_pkgconfigdir" ; then
  ac_cv_pkgconfigdir="\$(libdir)/pkgconfig"
fi
pkgconfigdir="$ac_cv_pkgconfigdir"
AC_SUBST(pkgconfigdir)
dnl
dnl pkg-config
dnl ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


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
AC_CONFIG_FILES(src/CommonLib/Makefile)
AC_CONFIG_FILES(src/ConcordLib/Makefile)
AC_CONFIG_FILES(src/GraphanLib/Makefile)
AC_CONFIG_FILES(src/StructDictLib/Makefile)
AC_CONFIG_FILES(src/LemmatizerLib/Makefile)
AC_CONFIG_FILES(src/AgramtabLib/Makefile)
AC_CONFIG_FILES(src/tinyxml/Makefile)
AC_CONFIG_FILES(src/RmlTar/Makefile)
AC_CONFIG_FILES(src/PCRE/Makefile)
AC_CONFIG_FILES(src/MorphWizardLib/Makefile)
AC_CONFIG_FILES(src/ConcordDmnLib/Makefile)
AC_CONFIG_FILES(src/ddc_index/Makefile)
AC_CONFIG_FILES(src/ddc_union/Makefile)
AC_CONFIG_FILES(src/ddc_split/Makefile)
AC_CONFIG_FILES(src/ddc_dump/Makefile)
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
AC_CONFIG_FILES(ddc.pc)
AC_CONFIG_FILES(Makefile)
AC_OUTPUT
