#!/bin/bash

##-- configuration
. `dirname $0`/ddc-common.sh

##-- functions
server_start() {
  if test "`server_status`" != "DOWN" ; then
     echo "$0: ddc_daemon appears already to be running on pid=`server_pid`" >/dev/stderr
     return 1
  fi
  runcmd $RML/bin/ddc_daemon start $DAEMON_OPTS
}
server_stop() {
  rc=0
  if test "`server_status`" = "DOWN" ; then
     echo "$0: ddc_daemon does not seem to be running" >/dev/stderr
     rc=1
  fi
  runcmd $RML/bin/ddc_daemon stop $DAEMON_OPTS
  test -w $DAEMON_PIDFILE && rm -f $DAEMON_PIDFILE
  return $rc
}
server_status() {
  pid=`server_pid`
  st=DOWN
  if test \
      -n "$pid" \
      -a -d /proc/$pid \
      -a -r /proc/$pid/cmdline
  then
      test -n "`grep ddc_daemon /proc/$pid/cmdline`" && st="UP (pid=$pid)"
  fi
  echo "$st"
}
server_client() {
  runcmd $RML/bin/ddc_daemon start_cli $DAEMON_OPTS
}

##-- main
case "$1" in
  start|up)
    server_start || exit 1
    ;;
  stop|down)
    server_stop || exit 1
    ;;
  restart)
    server_stop
    sleep 2
    server_start || exit 1
    ;;
  status|st)
    st=`server_status`
    echo "ddc_daemon:$DAEMON_PIDFILE: $st"  
    ;;
  client|cli)
    server_client || exit 1
    ;;
  debug)
    DAEMON_OPTS="$DAEMON_OPTS --protocol heavy --nofork --stderr"
    server_start || exit 1
    ;;
  *)
    echo "Usage: $0 {start|stop|debug|restart|status|client}" >/dev/stderr
    exit 1
    ;;
esac
