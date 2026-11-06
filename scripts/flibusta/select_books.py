#!/usr/bin/env python3
"""Select the popular books of Flibusta: live fb2 books of the given language with at
least MIN_RATES user ratings.

    select_books.py LIBRATE.sql.gz INDEX.inpx OUTPUT.tsv [--min-rates 3] [--lang ru]

LIBRATE.sql.gz  lib.librate.sql.gz from https://flibusta.site/sql/
                (librate(ID, BookId, UserId, Rate): one row per user rating)
INDEX.inpx      the index of the fb2 archives (flibusta_fb2_local.inpx): a zip with one
                <archive>.inp per <archive>.zip, a line per book, fields separated by \\x04:
                AUTHOR GENRE TITLE SERIES SERNO FILE SIZE LIBID DEL EXT DATE LANG ...
OUTPUT.tsv      <archive.zip> TAB <BookId>.fb2 TAB <number of ratings>, the input of
                extract_selected.py
"""
import argparse
import collections
import gzip
import re
import sys
import zipfile

ROW = re.compile(rb"\((\d+),(\d+),(\d+),'(\d)'\)")


def rate_counts(path):
    counts = collections.Counter()
    with gzip.open(path, "rb") as f:
        for line in f:
            if line.startswith(b"INSERT INTO `librate`"):
                for m in ROW.finditer(line):
                    counts[int(m.group(2))] += 1
    return counts


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("librate")
    ap.add_argument("inpx")
    ap.add_argument("output")
    ap.add_argument("--min-rates", type=int, default=3)
    ap.add_argument("--lang", default="ru", help="language code of the INPX LANG field, '' = any")
    a = ap.parse_args()

    counts = rate_counts(a.librate)
    print("%d rated books in librate" % len(counts), file=sys.stderr)
    selected = []
    total = 0
    z = zipfile.ZipFile(a.inpx)
    for name in z.namelist():
        if not name.endswith(".inp"):
            continue
        archive = name[:-4] + ".zip"
        for line in z.read(name).decode("utf-8", "replace").splitlines():
            f = line.split("\x04")
            if len(f) < 12:
                continue
            total += 1
            file_name, deleted, ext, lang = f[5], f[8], f[9], f[11].strip().lower()
            if deleted == "1" or ext != "fb2" or (a.lang and lang != a.lang) or not file_name.isdigit():
                continue
            n = counts.get(int(file_name), 0)
            if n >= a.min_rates:
                selected.append((archive, int(file_name), n))
    selected.sort()
    with open(a.output, "w", encoding="utf-8") as out:
        for archive, book_id, n in selected:
            out.write("%s\t%d.fb2\t%d\n" % (archive, book_id, n))
    print("%d books in the index, %d selected (lang=%r, >= %d ratings) -> %s"
          % (total, len(selected), a.lang, a.min_rates, a.output), file=sys.stderr)


if __name__ == "__main__":
    main()
