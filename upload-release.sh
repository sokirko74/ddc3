#!/bin/bash

DSTURL="mukau@frs.sourceforge.net:/home/frs/project/ddc-concordance/ddc-concordance/2.1/"

if test -z "$*" -o "$1" = "-h" -o "$1" = "--help" ; then
    cat <<EOF >&2
Usage: $0 FILE(s)...

Uploads FILE(s) to $DSTURL

EOF
    exit 0
fi

exec rsync -tzv "$@" "$DSTURL"
