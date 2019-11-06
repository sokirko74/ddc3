#!/bin/bash

if [ $# -lt 1 -o "$1" = "-h" -o "$1" = "--help" ] ; then
    cat <<EOF >&2

Usage: $0 FILE[s]...

Description:
  Expands TABs to spaces in-place in all specified FILE(s).

EOF
    exit 0
fi

for f in "$@" ; do
  mv -i "$f" "$f.orig" && expand "$f.orig" >"$f"
done
