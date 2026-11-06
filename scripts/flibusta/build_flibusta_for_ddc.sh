#!/bin/bash
## Build a ddc corpus of the popular Russian books of Flibusta.
##
## Usage: build_flibusta_for_ddc.sh STEP...    (or "all": every step in this order)
##
##   download  the ratings lib.librate.sql.gz from https://flibusta.site/sql/ (updated daily)
##             and the archive index (INPX) from the archive host
##   select    select_books.py: live fb2 books of $LANG_CODE with >= $MIN_RATES ratings
##             -> $WORK/selected.tsv (archive, BookId.fb2, number of ratings)
##   extract   extract_selected.py on the archive host: the selected books from the zip archives
##             (PPMd, read with 7z) as <archive>/<BookId>.fb2.gz; hours on a slow disk,
##             restartable (existing files are skipped)
##   fetch     rsync the extracted books to $WORK/fb2
##   convert   fb2tei.py --gzip: fb2 -> TEI.2 xml (UTF-8, notes at the end) in $WORK/tei
##   split     make_ddc_parts.py: $PARTS subcorpora of about equal size + daemon configs in $WORK/ddc
##   index     ddc_index of all parts in parallel (logs in $WORK/ddc/partK/index.log)
##   serve     (re)start ddc_daemon: leaves on 127.0.0.1:$PORT+K, root on 127.0.0.1:$PORT
##
## All settings can be overridden from the environment, e.g. MIN_RATES=5 PARTS=4 ./build_flibusta_for_ddc.sh all
##
## Numbers of 2026-11-06 (MIN_RATES=3, LANG_CODE=ru): 578485 books in the index,
## 133632 selected (78 GB of fb2); extraction ~650 books/min with 2 jobs on migalka.

set -euo pipefail

SCRIPTS=$(cd "$(dirname "$0")" && pwd)
DDC3_ROOT=$(cd "$SCRIPTS/../.." && pwd)

REMOTE=${REMOTE:-migalka}                                        # host with the Flibusta archives
REMOTE_DIR=${REMOTE_DIR:-/mnt/sdb/flibusta}                      # working directory there
ARCHIVES=${ARCHIVES:-$REMOTE_DIR/Flibusta.FB2/fb2.Flibusta.Net}  # fb2-*.zip
INPX=${INPX:-$REMOTE_DIR/Flibusta.FB2/flibusta_fb2_local.inpx}
SQL_URL=${SQL_URL:-https://flibusta.site/sql}
WORK=${WORK:-$HOME/data/flibusta}
MIN_RATES=${MIN_RATES:-3}
LANG_CODE=${LANG_CODE:-ru}
PARTS=${PARTS:-8}
PORT=${PORT:-50300}
JOBS=${JOBS:-$(nproc)}
REMOTE_JOBS=${REMOTE_JOBS:-2}
BIN=${BIN:-$DDC3_ROOT/build/src}
export DDC3=${DDC3:-$DDC3_ROOT}

log() { echo "== $(date '+%F %T') $*" >&2; }

step_download() {
    mkdir -p "$WORK/sql"
    log "download $SQL_URL/lib.librate.sql.gz"
    # the server is slow and drops connections: resume and retry
    curl -sS -f -A 'Mozilla/5.0' --retry 10 --retry-all-errors -C - \
        -o "$WORK/sql/lib.librate.sql.gz" "$SQL_URL/lib.librate.sql.gz" || \
        curl -sS -f -A 'Mozilla/5.0' --retry 10 -o "$WORK/sql/lib.librate.sql.gz" "$SQL_URL/lib.librate.sql.gz"
    gzip -t "$WORK/sql/lib.librate.sql.gz"
    log "copy $REMOTE:$INPX"
    rsync -a "$REMOTE:$INPX" "$WORK/sql/"
}

step_select() {
    python3 "$SCRIPTS/select_books.py" "$WORK/sql/lib.librate.sql.gz" "$WORK/sql/$(basename "$INPX")" \
        "$WORK/selected.tsv" --min-rates "$MIN_RATES" --lang "$LANG_CODE"
}

step_extract() {
    log "extract on $REMOTE into $REMOTE_DIR/selected (log: $REMOTE_DIR/extract_selected.log)"
    rsync -a "$SCRIPTS/extract_selected.py" "$WORK/selected.tsv" "$REMOTE:$REMOTE_DIR/"
    ssh "$REMOTE" "cd '$REMOTE_DIR' && python3 extract_selected.py selected.tsv '$ARCHIVES' selected -j $REMOTE_JOBS \
        > extract_selected.log 2>&1; tail -1 extract_selected.log; grep -c ^ERROR extract_selected.log || true"
}

step_fetch() {
    log "fetch $REMOTE:$REMOTE_DIR/selected -> $WORK/fb2"
    mkdir -p "$WORK/fb2"
    rsync -a --partial "$REMOTE:$REMOTE_DIR/selected/" "$WORK/fb2/"
}

step_convert() {
    log "fb2 -> TEI xml.gz in $WORK/tei"
    python3 "$DDC3_ROOT/scripts/fb2tei.py" --gzip -j "$JOBS" "$WORK/fb2" "$WORK/tei"
}

step_split() {
    log "split into $PARTS parts in $WORK/ddc"
    python3 "$SCRIPTS/make_ddc_parts.py" "$WORK/tei" "$WORK/ddc" "$SCRIPTS/flibusta.opt" \
        --parts "$PARTS" --port "$PORT"
}

step_index() {
    log "index $PARTS parts in parallel"
    local pids=() i
    for i in $(seq 1 "$PARTS"); do
        ( cd "$WORK/ddc/part$i" && "$BIN/ddc_index/ddc_index" "part$i.con" > index.log 2>&1 ) &
        pids+=($!)
    done
    local failed=0
    for i in "${!pids[@]}"; do
        wait "${pids[$i]}" || { echo "part$((i + 1)) failed, see $WORK/ddc/part$((i + 1))/index.log" >&2; failed=1; }
    done
    return $failed
}

step_serve() {
    cd "$WORK/ddc"
    "$BIN/ddc_daemon/ddc_daemon" restart -l ddc_local_corpora.cfg -s ddc_server.cfg
    log "query: $BIN/ddc_xml/ddc_xml --server $WORK/ddc/ddc_xml.cfg --text QUERY"
}

[ $# -gt 0 ] || { sed -n 's/^## \{0,1\}//p' "$0"; exit 1; }
[ "$1" = all ] && set -- download select extract fetch convert split index serve
for s in "$@"; do
    declare -F "step_$s" > /dev/null || { echo "unknown step: $s" >&2; exit 1; }
    "step_$s"
done
