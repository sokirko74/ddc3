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
  -r, -request       # send a raw DDC request (not a corpus query)
  -j, -json          # select DDC-JSON format (default)
  -text              # select DDC-text format
  -table             # select DDC-table format

request queries are interpreted by the printf(1) program,
so you can use e.g. \OOO or \xXX escapes.

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
if test "$mode" != "REQUEST" ; then
    reqbody=$(printf "run_query Distributed\x01%s\x01%s\x01%d %d %d" "${req[*]}" "$mode" "$start" "$limit" "$timeout")
else
    reqbody="${req[*]}"
fi

## ddc_request_str=$(ddc_request $printf_format ...)
ddc_request() {
    local len=$(printf "$@" | wc -c)
    printf "$(printf "\\%03o" $((len&255)) $((len>>8&255)) $((len>>16&255)) $((len>>24&255)))"
    printf "$@"
}

ddc_request "$reqbody" | nc "$host" "$port" | tail -c +5 | "$postproc"
