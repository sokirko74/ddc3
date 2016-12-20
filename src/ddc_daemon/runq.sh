#!/bin/bash

ddc-query.perl "$@" \
    | while read s ; do
	  echo "$0[$*]: $s"
      done
echo -e "$0[$*]: END"
