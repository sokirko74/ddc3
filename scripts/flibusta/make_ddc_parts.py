#!/usr/bin/env python3
"""Split a directory of corpus files into N ddc subcorpora of about equal size and
write the configs of a ddc_daemon with one leaf per subcorpus and a root server.

    make_ddc_parts.py INPUT_DIR OUTPUT_DIR OPT_FILE [--parts 8] [--name part] [--port 50300]

OUTPUT_DIR/<name>1 .. <name>N/<name>K.con (absolute file names) and <name>K.opt (a copy of
OPT_FILE); OUTPUT_DIR/ddc_local_corpora.cfg (leaves on 127.0.0.1:PORT+K),
ddc_server.cfg (root on 127.0.0.1:PORT) and ddc_xml.cfg (for ddc_xml --server).
Index each part with "ddc_index <name>K.con" in its directory (see index_parts.sh).
"""
import argparse
import heapq
import os
import shutil

EXTENSIONS = (".xml", ".xml.gz")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("input_dir")
    ap.add_argument("output_dir")
    ap.add_argument("opt_file")
    ap.add_argument("--parts", type=int, default=8)
    ap.add_argument("--name", default="part")
    ap.add_argument("--port", type=int, default=50300)
    a = ap.parse_args()

    files = []
    for d, _, names in os.walk(os.path.abspath(a.input_dir)):
        for n in names:
            if n.endswith(EXTENSIONS):
                p = os.path.join(d, n)
                files.append((os.path.getsize(p), p))
    files.sort(reverse=True)
    # greedy: the next largest file goes to the smallest part
    heap = [(0, i, []) for i in range(a.parts)]
    for size, p in files:
        total, i, lst = heapq.heappop(heap)
        lst.append(p)
        heapq.heappush(heap, (total + size, i, lst))

    os.makedirs(a.output_dir, exist_ok=True)
    local = ["//CorpusName\tIP\tPORT\tLocalName"]
    server = ["//CorpusName\tIP\tPORT", "server:root\t127.0.0.1\t%d" % a.port]
    for total, i, lst in sorted(heap, key=lambda x: x[1]):
        name = "%s%d" % (a.name, i + 1)
        d = os.path.join(a.output_dir, name)
        os.makedirs(d, exist_ok=True)
        with open(os.path.join(d, name + ".con"), "w", encoding="utf-8") as f:
            f.write("\n".join(sorted(lst)) + "\n")
        shutil.copy(a.opt_file, os.path.join(d, name + ".opt"))
        port = a.port + i + 1
        local.append("%s\t127.0.0.1\t%d\t%s/%s.con" % (name, port, name, name))
        server.append("%s\t127.0.0.1\t%d" % (name, port))
        print("%s: %d files, %d MB" % (name, len(lst), total // 2**20))
    for fn, lines in (("ddc_local_corpora.cfg", local), ("ddc_server.cfg", server),
                      ("ddc_xml.cfg", ["//CorpusName\tIP\tPORT", "server\t127.0.0.1\t%d" % a.port])):
        with open(os.path.join(a.output_dir, fn), "w", encoding="utf-8") as f:
            f.write("\n".join(lines) + "\n")


if __name__ == "__main__":
    main()
