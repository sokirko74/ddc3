#!/bin/bash

qs=(
    @Mann
    @Frau
    @Haus
    @Garten
    @Maus
    @Satz
    @Spiel
    @schön
    @blöd
)

./ddc-bench-multi.perl -p=52120 -c -q "${qs[@]}" "$@"
