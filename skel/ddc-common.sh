##-*- Mode: Shell-script -*-
##
## File: ddc-common.sh
## Author: Bryan Jurish <jurish@bbaw.de>
## Description:
##  + common variables for ddc utility bash scripts
##  + put local overrides into ./ddc-custom.sh

## DDC_ROOT
##  + script base directory
test -z "$DDC_ROOT" && DDC_ROOT=$(dirname $0)
DDC_ROOT=`readlink -f "$DDC_ROOT"`

## local overrides
test -r "$DDC_ROOT/ddc-custom.sh" && . "$DDC_ROOT/ddc-custom.sh"

## RML
##  + root directory of the local ddc corpus
##  + should contain at least the following subdirectories:
##     $RML/bin/   ##-- binaries, e.g. bin/ddcIndex
##     $RML/dict/  ##-- dictionary data, e.g. dict/Morph/Ger/
##     $RML/log/   ##-- server log base directory, e.g. log/concord/2011-05-31.log
##    ?$RML/etc/   ##-- (optional) configuration files, e.g. etc/ddc_local_corpora.cfg  -> RML_ETC
##    ?$RML/data/  ##-- (optional) data files to index/query, e.g. data/dta_1.con
test -z "$RML" -a -d "$DDC_ROOT/rml" && RML="$DDC_ROOT/rml"
test -z "$RML"                       && RML="$DDC_ROOT"
export RML

## RML_ETC
##  + configuration directory of the local ddc corpus, should contain the following files:
##     $RML_ETC/ddc_server.cfg		##-- server configuration
##     $RML_ETC/ddc_local_corpora.cfg	##-- local corpora (may be empty)
test -z "$RML_ETC" -a -d "$DDC_ROOT/etc" && RML_ETC="$DDC_ROOT/etc"
test -z "$RML_ETC"                       && RML_ETC="$RML/etc"

## DUMMY
##  + if non-empty, don't actually run any commands; just print them to stderr
#DUMMY=""

## LC_CTYPE
##  + locale setting for wtoupper() etc
test -z "$LC_CTYPE" && LC_CTYPE="en_US.UTF-8"
export LC_CTYPE

## DAEMON_OPTS
##  + options for ddcDaemon
#test -z "$DAEMON_OPTS" && DAEMON_OPTS="--protocol heavy --local $RML_ETC/ddc_local_corpora.cfg --server $RML_ETC/ddc_server.cfg --fork"
test -z "$DAEMON_OPTS" && DAEMON_OPTS="--protocol weak --local $RML_ETC/ddc_local_corpora.cfg --server $RML_ETC/ddc_server.cfg"

## DAEMON_PIDFILE
##  + pid file for ddcDaemon
test -z "$DAEMON_PIDFILE" && DAEMON_PIDFILE="$RML_ETC/ddc_local_corpora.ddc_lck"

## DAEMON_WAITFILE
##  + wait-file for ddc_daemon (absence indicates server thread started up ok)
test -z "$DAEMON_WAITFILE" && DAEMON_WAITFILE="${DDC_LOCAL_CFG%.cfg}.ddc_wait"
test -z "$DAEMON_START_WAIT" && DAEMON_START_WAIT=300

## pid=`server_pid`
##  + get server PID from $DAEMON_PIDFILE
server_pid() {
  test -n "$DAEMON_PIDFILE" -a -r "$DAEMON_PIDFILE" && cat "$DAEMON_PIDFILE"
}

## pids=$(server_pgrep)
##  + get all matching server PIDs
server_pgrep() {
#  pgrep -U "$ddc_user" -x -f "$RML/bin/ddc_daemon start $DAEMON_OPTS"
  pgrep -x -f "$RML/bin/ddc_daemon start $DAEMON_OPTS"
}

##--------------------------------------------------------------
## privelege restriction (for cron scripts)

## DDC_USER
##  + user as whom to run the server (set to empty (default) for current user $LOGNAME)
#DDC_USER=ddc

## DDC_SSHKEY
##  + password-free ssh public key to use for gaining $DDC_USER privileges (default=none)
test -z "$DDC_SSHKEY" -a -r "$DDC_ROOT/ssh/${LOGNAME}_$(hostname -s)_ddc" && DDC_SSHKEY="$DDC_ROOT/ssh/${LOGNAME}_$(hostname -s)_ddc"
test -z "$DDC_SSHKEY" -a -r "$DDC_ROOT/ssh/$(hostname -s)_ddc"            && DDC_SSHKEY="$DDC_ROOT/ssh/$(hostname -s)_ddc"
test -z "$DDC_SSHKEY" -a -r "$DDC_ROOT/ssh/id_dsa"                        && DDC_SSHKEY="$DDC_ROOT/ssh/id_dsa"
test -z "$DDC_SSHKEY" -a -r "$HOME/.ssh/${LOGNAME}_$(hostname -s)_ddc"    && DDC_SSHKEY="$HOME/.ssh/${LOGNAME}_$(hostname -s)_ddc"
test -z "$DDC_SSHKEY" -a -r "$HOME/.ssh/$(hostname -s)_ddc"               && DDC_SSHKEY="$HOME/.ssh/$(hostname -s)_ddc"
test -z "$DDC_SSHKEY" -a -r "$HOME/.ssh/id_dsa"                           && DDC_SSHKEY="$HOME/.ssh/id_dsa"

## ddcsu CMD...
##  + run CMD as $DDC_USER
ddcsu() {
  if test -z "$DDC_USER" -o "$DDC_USER" = "$LOGNAME"  ; then
    ##-- we're already the ddc user: just run
    runcmd "$@"
  elif test -n "$DDC_SSHKEY" -a -r "$DDC_SSHKEY" ; then
    ##-- we have an ssh key: use it
    runcmd ssh -i "$DDC_SSHKEY" -o PreferredAuthentications=publickey "${DDC_USER}@localhost" "cd $PWD" \; env RML="$RML" LC_CTYPE="$LC_CTYPE" "$@"
  elif test -n "$(which sudo 2>/dev/null)" ; then
    ##-- try to use sudo
    runcmd sudo -u "$DDC_USER" env RML="$RML" LC_CTYPE="$LC_CTYPE" "$@"
  elif test "$LOGNAME" = "root" ; then
    ##-- we're root: use su (watch out for shell quotes though)
    runcmd su -p -c "$*" "$DDC_USER"
  else
    die "ddcsu($*): could not run command as DDC_USER=$DDC_USER"
  fi
}

##--------------------------------------------------------------
## command utilities

## runcmd()
##  + utility function
runcmd() {
  logmsg "SYSTEM" "$@" >&2
  test -n "$DUMMY" || "$@"
}

## runcmds($cmds)
##  + utility function; run with eval
runcmds() {
  logmsg "SYSTEM" "$@" >&2
  test -n "$DUMMY" || eval "$@"
}


##--------------------------------------------------------------
## verbosity and logging

## prog : program
test -z "$prog" && prog=$(basename $0)

## logmsg MESSAGE...
##  + prepends program name, data to MESSAGE and prints to stderr
logmsg() {
  echo "$(date +'%F %T') ${prog}[$$]: $*" >&2
}

## warn "$msg" : warning
warn() {
  logmsg "WARNING: $*"
}

## die MESSAGE...
##  + print MESSAGE to stderr with logmsg and exit with nonzero status
die() {
  msg="$*"
  test -z "$msg" && msg="ERROR"
  logmsg "$msg"
  exit 1
}
