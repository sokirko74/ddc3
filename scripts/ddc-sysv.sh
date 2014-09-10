#!/bin/bash
##
## File: ddc-sysv.sh
## Author: Bryan Jurish <jurish@bbaw.de>
## Description: sysV-style init script for ddc servers a la ddc-mkrml.sh
## Usage:
##  + install this script as e.g. /etc/init.d/ddc.sh
##  + create and edit /etc/default/ddc so that the variable DDC_ROOTS is
##    a list of all ddc root dirs as created e.g. by ddc-mkrml.sh
##  + start/stop all selected ddc instances by calling /etc/init.d/ddc.sh {start|stop}

### BEGIN INIT INFO
# Provides:          ddc
# Required-Start:    $all
# Required-Stop:     $local_fs $remote_fs $network
# Should-Start:      $named $syslog
# Should-Stop:       $named $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: DDC server(s)
### END INIT INFO

##======================================================================
## Configurations & Variables
##======================================================================

##-- default config file
test -z "$DDC_SYSRC" && DDC_SYSRC="/etc/default/ddc"

##======================================================================
## MAIN
##======================================================================

##-- system config file: /etc/default/ddc
if test "$1" = "-f" ; then
  shift
  DDC_SYSRC="$1"
  shift
fi
test -r "$DDC_SYSRC" && . "$DDC_SYSRC"


test "${#DDC_ROOTS}" = "0" -o -z "${DDC_ROOTS[*]}" && DDC_ROOTS=("${DDC_RMLS[@]}")
if test "${#DDC_ROOTS}" = "0" -o -z "${DDC_ROOTS[*]}" ; then
  echo "$0: DDC_ROOTS is not set; edit config file '$DDC_SYSRC' to enable" >&2
  exit 0
fi

case "$1" in
  start|stop|killall|kill|restart|debug|status|stat|sta|st|vstatus|vstat|vsta|vst|pids|ports)
    rc=ok
    cmd="$1"
    test "$cmd" = "stop" && cmd="killall"  ##-- hack: using 'killall' is safer than daemon 'stop' command
    for d in "${DDC_ROOTS[@]}" ; do
      cd "$d" \
      && ./ddc-server.sh "$cmd" \
      || rc=FAILED
    done
    test "$rc" = "ok" || exit 1
    ;;
  *)
    echo "Usage: $0 [-f SYSRC=$DDC_SYSRC] {start|stop|kill|restart|debug|status|vstatus|pids|ports}"
    exit 1
    ;;
esac
