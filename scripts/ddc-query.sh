#!/bin/bash

##======================================================================
## Globals
prog=$(basename "$0")
req=()
host="localhost"
port="50011"
timeout="60"
start=0
limit=10
mode="json"
postproc="cat"

##======================================================================
## Functions

show_help() {
    cat <<EOF >&2

Usage: $prog [OPTIONS] [--] QUERY_OR_REQUEST...

Options:
  -h, -help          # this help message
  -s, -server SRV    # set server HOST[:PORT] (default=$host)
  -p, -port  PORT    # set server port PORT (default=$port)
  -S, -start START   # index of first hit (default=$start)
  -l, -limit LIMIT   # return at most LIMIT hits (default=$limit)
  -t, -timeout SECS  # set server timeout to SECS (default=$timeout)
  -r, -request       # send a DDC request COMMAND [NAME=VALUE...] (not a corpus query)
  -j, -json          # select DDC-JSON format (default)
  -text              # select DDC-text format
  -table             # select DDC-table format

The server is queried over HTTP with curl(1), e.g.
  $prog -r status
  $prog -r vinfo timeout=5

EOF
}

##======================================================================
## Command-line

while test $# -gt 0 ; do
    opt="$1"
    shift;
    case "$opt" in
	-help|--help|-h)
	    show_help
	    exit 0
	    ;;
	
	-server|-s)
	    host="$1"
	    shift
	    case "$host" in
		*:*)
		    port="${host##*:}"
		    host="${host%:*}"
		    ;;
		*)
		    ;;
	    esac
	    ;;
	-port|-p)
	    port="$1"; shift;
	    ;;

	-start|-S)
	    start="$1"; shift;
	    ;;
	-limit|-l)
	    limit="$1"; shift;
	    ;;
	-timeout|-t)
	    timeout="$1"; shift;
	    ;;

	-request|-req|-r)
	    mode="request"
	    ;;
	-text|-txt)
	    mode="text"
	    ;;
	-table|-tbl|-tab)
	    mode="table"
	    ;;
	-json|-j)
	    mode="json"
	    ;;

	--)
	    break
	    ;;

	-*)
	    echo "$prog: ERROR: unknown option '$opt'" >&2
	    show_help
	    exit 1
	    ;;

	*)
	    req[${#req[@]}]="$opt"
	    ;;
    esac
done

req=("${req[@]}" "$@")
if test ${#req[@]} -eq 0 ; then
    echo "$prog: ERROR: no query or request specified!" >&2
    show_help
    exit 1
fi

##======================================================================
## guts

mode=$(echo "$mode" | tr a-z A-Z)
url="http://$host:$port"
if test "$mode" != "REQUEST" ; then
    curl -sS --data-urlencode "query=${req[*]}" -d "format=$mode" -d "start=$start" -d "limit=$limit" \
         -d "timeout=$timeout" "$url/run_query" | "$postproc"
else
    cmd="${req[0]}"
    args=()
    for kv in "${req[@]:1}"; do args+=(--data-urlencode "$kv"); done
    curl -sS "${args[@]}" "$url/$cmd" | "$postproc"
fi
