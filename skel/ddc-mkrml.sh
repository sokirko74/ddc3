#!/bin/bash

## File: ddc-mkrml.sh
## Author: Bryan Jurish <jurish@bbaw.de>
## Description:
##  + create new template ddc RML directory

default_skeldir=`dirname $0`/../skel

if test $# -lt 1 -o "$1" = "-h" -o "$1" = "--help" ; then
  cat <<EOF

Usage: $0 NEW_RML_DIR [RML_SKEL_DIR=$default_skeldir]

 + creates a new runtime-root directory NEW_RML_DIR for a new DDC instance
 + run this script as the user who will own the new DDC process
 + after successful completion, do the following:
    - edit \$NEW_RML_DIR/etc/*.cfg and \$NEW_RML_DIR/ddc-common.sh to suit your needs
    - create and index a corpus using RML=\$NEW_RML_DIR (e.g. in \$NEW_RML_DIR/data)
    - start a DDC sever with \$NEW_RML_DIR/ddc-server.sh start

EOF
  exit 1
fi

##-- autoconf variables

##-- command-line
outdir=`readlink -m "$1"`
skeldir="$2"
test -z "$skeldir" && skeldir="$default_skeldir"

##-- oops
die() {
  echo "$0: ERROR: $*" >/dev/stderr
  exit 1
}

runcmd() {
  echo "$0: $@"
  "$@"
}

##-- test for existence
test -e "$outdir" \
  && die "output directory '$outdir' already exists!"

test -d "$skeldir" \
  || die "skeleton directory '$skeldir' not found!"

##-- create output directory
runcmd mkdir -p "$outdir" \
  || die "could not create output directory '$outdir'!"
runcmd mkdir -p "$outdir/etc" \
  || die "could not create output log directory '$outdir/etc'!"
runcmd mkdir -p "$outdir/log/concord" \
  || die "could not create output log directory '$outdir/log/concord'!"
runcmd mkdir -p "$outdir/data" \
  || die "could not create data directory '$outdir/data'!"

##-- copy skeleton
SKEL_FILES="ddc-common.sh ddc-server.sh etc bin dict"
for f in $SKEL_FILES ; do
 runcmd cp --recursive --preserve=mode,links "$skeldir/$f" "$outdir" \
   || die "could not copy '$skeldir/$f' to '$outdir/$f'"
done

##-- set skeleton variables
perl -pe "s{^\s*RML=.*\$}{RML=\"$outdir\"};" "$skeldir/ddc-common.sh" > "$outdir/ddc-common.sh" \
  || die "could not auto-edit in '$outdir/ddc-common.sh'"

##-- all done
echo "$0: created new RML directory '$outdir'"
