#!/bin/bash

##--------------------------------------------------------------
## configuration
. $(dirname $0)/ddc-common.sh

##--------------------------------------------------------------
## globals
ddc_startcmd="$RML/bin/ddc_daemon start $DAEMON_OPTS"
ddc_stopcmd="$RML/bin/ddc_daemon stop $DAEMON_OPTS"

##--------------------------------------------------------------
server_start() {
  if test "$(server_status)" != "DOWN" ; then
     echo "$0: ddc_daemon appears already to be running on pid=$(server_pid)" >&2
     return 1
  fi

  ddcsu $ddc_startcmd || return 1

  ##-- wait for sentinel file to disappear
  sleep 1; ##-- wait for process to appear
  waited=0
  while test "$waited" -lt "$DAEMON_START_WAIT" -a -e "$DAEMON_WAITFILE" ; do
      case "$(server_status)" in
        UP*) continue ;;
	*) 
	  echo "$0: server not found after $waited second(s): $(server_status)" >&2
	  return 1
	  ;;
      esac
      let "waited=waited+1"
      sleep 1
  done

  ##-- timeout waiting for server to start
  if test -e "$DAEMON_WAITFILE" ; then
      echo "$0: wait-file '$DAEMON_WAITFILE' still exists after $waited second(s); aborting" >&2
      return 1
  fi

  return 0
}

##--------------------------------------------------------------
server_stop() {
  rc=0
  st=$(server_status)
  case "$st" in
    UP*)
     ddcsu $ddc_stopcmd || rc=1
     #test "$rc" = 0 -a -w $DAEMON_PIDFILE && ddcsu rm -f $DAEMON_PIDFILE || rc=1
     ;;
    DOWN)
     echo "$0: ddc_daemon does not seem to be running; status=$st" >&2
     rc=1
     ;;
    GONE*)
     echo "$0: cannot find ddc_daemon process; status=$st" >&2
     rc=1
     ;;
    *)
     echo "$0: cannot find ddc_daemon; status=$st" >&2
     rc=1
     ;;
  esac
  return $rc
}

##--------------------------------------------------------------
server_status() {
  pid=$(server_pid)
  st=DOWN
  if test \
      -n "$pid" \
      -a -d /proc/$pid \
      -a -r /proc/$pid/cmdline
  then
      test -n "$(grep ddc_daemon /proc/$pid/cmdline)" && st="UP (pid=$pid)"
  fi
  echo "$st"
}

##--------------------------------------------------------------
server_killall() {
  rc=0
  pass=1
  pass_max=10
  pass_wait=300
  waited_total=0
  server_pids=$(server_pgrep)
  nkills=0
  while test $pass -le $pass_max -a -n "$server_pids" ; do
    echo "$0: killall [pass=$pass/$pass_max]: pids=(" $server_pids ")"
    for p in $server_pids ; do
      ddcsu kill -TERM $p || rc=1
      let nkills="$nkills+1"
    done
    pass_waited=0
    while test $pass_waited -le $pass_wait -a -n "$server_pids" ; do
      sleep 1
      let pass_waited="$pass_waited+1"
      server_pids=$(server_pgrep)
    done
    let waited_total="$waited_total+$pass_waited"
    test -n "$server_pids" && break
    let pass="$pass+1"
  done

  server_pids=$(server_pgrep)
  if test -n "$server_pids"; then
    echo "$0: killall FAILED: processes remain after $nkills signal(s), $waited_total seconds:" $server_pids
    return 1
  fi
  echo "$0: killall: all matching server processes terminated after $nkills signal(s), $waited_total second(s)"

  ##-- wait for pid-file to disappear; force-remove it if required
  pidgone_maxwait=300
  if test "$rc" = 0 -a -e $DAEMON_PIDFILE ; then
    echo -n "$0: killall: waiting for $DAEMON_PIDFILE to disappear "
    waited=0
    while test "$waited" -lt $pidgone_maxwait ; do
      echo -n "."
      sleep 1
      test '!' -e $DAEMON_PIDFILE && echo "ok" && break
      let waited=waited+1
    done
    if test -e $DAEMON_PIDFILE ; then
      echo -e "\n$0: killall: force-removing $DAEMON_PIDFILE after $waited seconds"
      ddcsu rm -f $DAEMON_PIDFILE || rc=1
    fi
  fi
  return $rc
}

##--------------------------------------------------------------
server_status() {
  local pid=$(server_pid)
  st=DOWN
  if test -n "$pid" ; then
    local pcomm=$(ps -w -w -p "$pid" -o comm= 2>/dev/null)
    local puser=$(ps -w -w -p "$pid" -o user= 2>/dev/null)
    test "${pcomm#lt-}" = "ddc_daemon" && st="UP (pid=$pid, user=$puser)" || st="GONE (pid=$pid)"
  fi
  echo "$st"
}

##--------------------------------------------------------------
server_status_str() {
  echo "$(server_status) @ $(server_ports)"
}

##--------------------------------------------------------------
server_owner() {
  local pid=$(server_pid)
  ps -w -w -p "$pid" -o user= 2>/dev/null
}

##--------------------------------------------------------------
server_client() {
  runcmd $RML/bin/ddc_daemon start_cli $DAEMON_OPTS
}

##--------------------------------------------------------------
server_port() {
  grep ^server $RML_ETC/ddc_server.cfg | awk '{print $3}'
}

##--------------------------------------------------------------
server_label() {
  perl -ne 'print "$$1\n" if (/^server:(\S+)/);' $RML_ETC/ddc_server.cfg
}

##--------------------------------------------------------------
server_query() {
  port=$(server_port)
  ddc-query.perl -server=localhost:"$port" "$@"
}

##--------------------------------------------------------------
local_ports() {
  egrep -v '^(//|#)' $RML_ETC/ddc_local_corpora.cfg | awk '{print $3}'
}

##--------------------------------------------------------------
local_ports_str() {
  local ports=( $(local_ports | sort -n) )
  if [ ${#ports[@]} -eq 0 ] ; then
    echo "-none-";
  else
    local pl="${ports[0]}"
    local pr="${ports[0]}"
    local pstr="$pl"
    local prr=""
    local pi=1
    while [ $pi -lt "${#ports[@]}" ] ; do
      let prr="$pr+1"
      if [ "$prr" = "${ports[$pi]}" ] ; then
         pr=${ports[$pi]}
      else
	 [ "$pr" != "$pl" ] && pstr="${pstr}-$pr"
	 pl="${ports[$pi]}"
	 pr="$pl"
	 pstr="${pstr},$pl"
      fi
      let pi=$pi+1
    done
    [ "$pr" != "$pl" ] && pstr="${pstr}-$pr"
    echo "$pstr"
  fi
}

##--------------------------------------------------------------
server_ports() {
  echo "$(server_port) (local $(local_ports_str))"
}

##--------------------------------------------------------------
## main
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
  killall|kill)
    server_killall || exit 1
    ;;
  restart)
    #server_stop
    server_killall || exit 1
    sleep 2
    server_start || exit 1
    ;;
  status|stat|sta|st)
    st=$(server_status_str)
    echo "ddc_daemon:$DAEMON_PIDFILE: $st"
    ;;
  vstatus|vstat|vsta|vst)
    st=$(server_status_str)
    echo "ddc_daemon:$DAEMON_PIDFILE: $st"
    server_query -timeout=5 -req status
    ;;
  pgrep|pids)
    #echo "pgrep -u $ddc_user -x -f '$ddc_startcmd'"
    server_pgrep
    ;;
  ports)
    echo -e "$DDC_ROOT\t$(server_ports)"
    ;;
  client|cli)
    server_client || exit 1
    ;;
  debug)
    DAEMON_OPTS="$DAEMON_OPTS --protocol heavy --nofork --stderr"
    server_stop
    sleep 3
    server_start || exit 1
    ;;
  *)
    echo "Usage: $0 {start|stop|kill|debug|restart|status|vstatus|pids|client}" >&2
    exit 1
    ;;
esac
