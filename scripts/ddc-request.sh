#!/bin/bash

## File: ddc-request.sh
## Author: Bryan Jurish <jurish@bbaw.de>
## Description: simple ddc

if test $# -lt 3 -o "$1" = "-h" -o "$1" = "-help" -o "$1" = "--help" ; then
    cat <<EOF >&2

Usage: $0 HOST PORT REQUEST...

REQUEST is a raw DDC request printf-string; see ddc_proto(5) for details.
This script just prepends an appropriate length component
to the request body it is passed.

EOF
    echo "" >&2
    exit 1
fi
host="$1"; shift
port="$1"; shift

## ddc_request_str=$(ddc_request $printf_format ...)
ddc_request() {
    local len=$(printf "$@" | wc -c)
    printf "$(printf "\\%03o" $((len&255)) $((len>>8&255)) $((len>>16&255)) $((len>>24&255)))"
    printf "$@"
}

ddc_request "$@" | nc "$host" "$port" | tail -c +5

