#!/bin/bash

ddc-query.perl -p=52120 -req 'clear_cache -1'

./runq.sh -p=52120 '$l=@d $l=@d' &
./runq.sh -p=52120 '@der @die' &
sleep 1
./runq.sh -p=52120 '$l=@Katze' &

carp() {
    echo "$0 WARNING:" "$@" >&2
}

for job in `jobs -p`; do
    echo "$0: waiting on job #$job" >&2
    wait $job || warn "failed to reap job #$job"
done
