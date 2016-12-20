#!/bin/bash

qs=(
    'der die das'
    'er sie es'
    'auf von mit'
    Mann
    Frau
    Haus
    Garten
    Maus
    Satz
    Spiel
    schön
    blöd
    'jedem jeder'
    'seine ihre'
)

./ddc-bench-multi.perl -p=52120 -c -q "${qs[@]}" "$@"
