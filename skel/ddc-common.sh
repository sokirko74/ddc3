##-*- Mode: Shell-script -*-
##
## File: ddc-common.sh
## Author: Bryan Jurish <jurish@bbaw.de>
## Description:
##  + common variables for ddc utility bash scripts
##  + edit this file to suit your needs

## RML
##  + root directory of the local ddc corpus
##  + should contain at least the following subdirectories:
##     $RML/bin/   ##-- binaries, e.g. bin/ddcIndex
##     $RML/etc/   ##-- configuration files, e.g. etc/ddc_local_corpora.cfg
##     $RML/dict/  ##-- dictionary data, e.g. dict/Morph/Ger/
##     $RML/log/   ##-- server log base directory, e.g. log/concord/2011-05-31.log
##     $RML/data/  ##-- data files to index/query, e.g. data/dta_1.con
if test -z "$RML" ; then
RML=`pwd`
fi
export RML

## DUMMY
##  + if non-empty, don't actually run any commands; just print them to stderr
#DUMMY=""

## LC_CTYPE
##  + locale setting for wtoupper() etc
test -z "$LC_CTYPE" && LC_CTYPE="en_US.UTF-8"
export LC_CTYPE

## DAEMON_OPTS
##  + options for ddcDaemon
#DAEMON_OPTS="--protocol heavy --local $RML/etc/ddc_local_corpora.cfg --server $RML/etc/ddc_server.cfg --fork"
DAEMON_OPTS="--protocol weak --local $RML/etc/ddc_local_corpora.cfg --server $RML/etc/ddc_server.cfg"

## DAEMON_PIDFILE
##  + pid file for ddcDaemon
DAEMON_PIDFILE="$RML/etc/ddc_local_corpora.ddc_lck"

## MAKEFLAGS
##  + flags for make (e.g. -jN), for re-indexing
test -z "$MAKEFLAGS" && MAKEFLAGS="-j6"
test -n "$DUMMY" && MAKEFLAGS="$MAKEFLAGS -n"

## DDC_BUILD
##  + ddc index build root directory
test -z "$DDC_BUILD" && DDC_BUILD="$RML/build"

## runcmd()
##  + utility function
runcmd() {
  echo "$@" >/dev/stderr
  test -n "$DUMMY" || "$@"
}

## pid=`server_pid`
##  + get server PID from $DAEMON_PIDFILE
server_pid() {
  test -n "$DAEMON_PIDFILE" -a -r "$DAEMON_PIDFILE" && cat "$DAEMON_PIDFILE"
}

## logmsg MESSAGE...
##  + prepends program name, data to MESSAGE and prints to stderr
logmsg() {
  echo "`basename $0`[$$]: `date +'%F %T'`: $*" >/dev/stderr
}

## die MESSAGE...
##  + print MESSAGE to stderr with logmsg and exit with nonzero status
die() {
  msg="$*"
  test -z "$msg" && msg="ERROR"
  logmsg "$msg"
  exit 1
}
