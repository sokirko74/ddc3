#!/usr/bin/env python3
"""Extract the selected books from the Flibusta zip archives as <BookId>.fb2.gz.

    extract_selected.py LIST.tsv ARCHIVE_DIR OUTPUT_DIR [-j N]

LIST.tsv: <archive.zip> TAB <BookId.fb2> [TAB ...], one book per line.
Output: OUTPUT_DIR/<archive name without .zip>/<BookId>.fb2.gz (the fb2 bytes as is,
the encoding is handled later by fb2tei.py). Existing files are skipped.
"""
import argparse
import collections
import gzip
import os
import subprocess
import sys
from multiprocessing import Pool


def extract(job):
    archive, names, out_dir = job
    done = missing = 0
    errors = []
    d = os.path.join(out_dir, os.path.basename(archive)[:-4])
    os.makedirs(d, exist_ok=True)
    # the archives use PPMd, which python's zipfile cannot read, so 7z is used;
    # names are processed in numeric order, i.e. roughly in the order of the archive
    listing = subprocess.run(["7z", "l", "-ba", "-slt", archive], stdout=subprocess.PIPE,
                             stderr=subprocess.DEVNULL).stdout.decode("utf-8", "replace")
    present = {l[7:] for l in listing.splitlines() if l.startswith("Path = ")}
    if not present:
        return archive, 0, len(names), ["%s: cannot list the archive" % archive]
    for n in sorted(names, key=lambda x: int(x.split(".")[0]) if x.split(".")[0].isdigit() else 0):
        dst = os.path.join(d, n + ".gz")
        if os.path.exists(dst):
            done += 1
            continue
        if n not in present:
            missing += 1
            continue
        try:
            r = subprocess.run(["7z", "x", "-so", archive, n], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            data = r.stdout
            if r.returncode != 0 or not data:
                raise RuntimeError("7z exit %d: %s" % (r.returncode, r.stderr.decode("utf-8", "replace").strip()[-200:]))
            with open(dst + ".tmp", "wb") as f:
                f.write(gzip.compress(data, 6, mtime=0))
            os.replace(dst + ".tmp", dst)
            done += 1
        except Exception as e:  # noqa: BLE001
            errors.append("%s/%s: %r" % (archive, n, e))
    return archive, done, missing, errors


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("list")
    ap.add_argument("archive_dir")
    ap.add_argument("output_dir")
    ap.add_argument("-j", "--jobs", type=int, default=2)
    a = ap.parse_args()
    by_arc = collections.defaultdict(list)
    for line in open(a.list, encoding="utf-8"):
        f = line.rstrip("\n").split("\t")
        by_arc[f[0]].append(f[1])
    jobs = [(os.path.join(a.archive_dir, arc), names, a.output_dir) for arc, names in sorted(by_arc.items())]
    total = sum(len(j[1]) for j in jobs)
    print("%d books in %d archives" % (total, len(jobs)), flush=True)
    done_all = missing_all = 0
    with Pool(a.jobs) as p:
        for i, (arc, done, missing, errors) in enumerate(p.imap_unordered(extract, jobs), 1):
            done_all += done
            missing_all += missing
            for e in errors:
                print("ERROR", e, flush=True)
            print("[%d/%d] %s: %d done, %d missing; total %d/%d"
                  % (i, len(jobs), os.path.basename(arc), done, missing, done_all, total), flush=True)
    print("FINISHED: %d extracted, %d missing" % (done_all, missing_all), flush=True)


if __name__ == "__main__":
    main()
