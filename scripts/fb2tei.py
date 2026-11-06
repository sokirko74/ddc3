#!/usr/bin/env python3
"""Convert FictionBook (fb2, fb2.gz) files into the TEI.2-like xml that ddc indexes
(the format of the Moshkov library xml, see create_xml.pl), in UTF-8.

    fb2tei.py INPUT OUTPUT [-j N]

INPUT is an .fb2/.fb2.gz file or a directory (searched recursively); OUTPUT is
the xml file or the output directory, where the input tree is mirrored
(Sorted_Books/2005/100196.fb2.gz -> OUTPUT/2005/100196.xml).
Existing output files are skipped, so an interrupted run can be restarted.
Files that cannot be parsed are listed in OUTPUT/fb2tei.errors.
"""

import argparse
import gzip
import html.entities
import os
import re
import sys
import time
import xml.etree.ElementTree as ET
from multiprocessing import Pool
from xml.sax.saxutils import escape

INDENT = "     "
NOTES_SEPARATOR = "------------"
INVALID_XML_CHARS = re.compile("[\x00-\x08\x0b\x0c\x0e-\x1f￾￿]")
SPACES = re.compile(r"\s+")
ENTITY = re.compile(r"&([A-Za-z][A-Za-z0-9]*);")
XML_DECL = re.compile(r"^\s*<\?xml[^>]*\?>")
ENCODING_DECL = re.compile(rb"""^\s*<\?xml[^>]*encoding\s*=\s*["']([^"']+)["']""")
XML_ENTITIES = {"amp", "lt", "gt", "quot", "apos"}


def local(tag):
    return tag.rsplit("}", 1)[-1] if isinstance(tag, str) else ""


def strip_namespaces(root):
    for el in root.iter():
        el.tag = local(el.tag)
        for k in list(el.attrib):
            if "}" in k:
                el.attrib[local(k)] = el.attrib.pop(k)


def replace_entity(m):
    name = m.group(1)
    if name in XML_ENTITIES:
        return m.group(0)
    ch = html.entities.name2codepoint.get(name)
    return chr(ch) if ch else " "


def parse(data):
    try:
        return ET.fromstring(data)
    except ET.ParseError:
        pass
    # second attempt: decode by hand, drop control chars and html entities
    m = ENCODING_DECL.match(data[:200])
    enc = m.group(1).decode("ascii", "replace") if m else "utf-8"
    try:
        text = data.decode(enc, "replace")
    except LookupError:
        text = data.decode("utf-8", "replace")
    text = XML_DECL.sub("", text, count=1)
    text = INVALID_XML_CHARS.sub("", text)
    text = ENTITY.sub(replace_entity, text)
    return ET.fromstring(text)


def norm(s):
    return SPACES.sub(" ", INVALID_XML_CHARS.sub("", s)).strip()


def inline_text(el):
    """Text of a paragraph-like element with all inline markup removed."""
    return norm("".join(el.itertext()))


class Writer:
    def __init__(self):
        self.lines = []

    def blank(self):
        if self.lines and self.lines[-1] != "":
            self.lines.append("")

    def line(self, s, indent=INDENT):
        if s:
            self.lines.append(indent + s)

    def block(self, el):
        tag = el.tag
        if tag in ("p", "subtitle", "text-author"):
            self.line(inline_text(el))
        elif tag == "v":
            self.line(inline_text(el), indent="")
        elif tag == "empty-line":
            self.blank()
        elif tag == "title":
            self.blank()
            for c in el:
                if c.tag == "p":
                    self.line(inline_text(c), indent="        ")
            self.blank()
        elif tag in ("poem", "stanza"):
            self.blank()
            for c in el:
                self.block(c)
            self.blank()
        elif tag == "table":
            for tr in el.iter("tr"):
                self.line(" | ".join(inline_text(td) for td in tr))
        elif tag in ("image", "binary"):
            pass
        else:  # section, epigraph, cite, annotation, date and unknown containers
            if tag == "date":
                self.line(inline_text(el))
                return
            if tag in ("section", "epigraph", "cite"):
                self.blank()
            for c in el:
                self.block(c)

    def text(self):
        while self.lines and self.lines[-1] == "":
            self.lines.pop()
        return "\n".join(self.lines)


def person_name(el):
    parts = [norm(el.findtext(t) or "") for t in ("first-name", "middle-name", "last-name")]
    name = " ".join(p for p in parts if p)
    return name or norm(el.findtext("nickname") or "")


DATE_RE = re.compile(r"(\d{4})(?:-(\d{1,2})(?:-(\d{1,2}))?)?")


def get_date(root):
    for path in ("description/title-info/date", "description/publish-info/year",
                 "description/src-title-info/date"):
        el = root.find(path)
        if el is None:
            continue
        for s in (el.get("value"), el.text):
            m = DATE_RE.search(s or "")
            if m and 1000 <= int(m.group(1)) <= 2100:
                return "%s-%02d-%02d" % (m.group(1), int(m.group(2) or 0), int(m.group(3) or 0))
    return "0000-00-00"


def convert(root):
    strip_namespaces(root)
    ti = root.find("description/title-info")
    if ti is None:
        ti = ET.Element("title-info")
    authors = [a for a in (person_name(x) for x in ti.findall("author")) if a]
    author = ", ".join(authors)
    title = norm(ti.findtext("book-title") or "")
    bibl = ". ".join(s for s in (author, title) if s)

    main, notes = Writer(), Writer()
    for body in root.findall("body"):
        if body.get("name") in ("notes", "comments", "footnotes"):
            notes.block(body)
        else:
            main.block(body)
    text = main.text()
    notes_text = notes.text()
    if notes_text:
        text += "\n\n" + NOTES_SEPARATOR + "\n" + notes_text + "\n" + NOTES_SEPARATOR

    return ('<?xml version="1.0" encoding="UTF-8"?>\n'
            '<TEI.2><teiHeader><fileDesc><sourceDesc id="orig"><bibl>%s</bibl>\n'
            '<date id="first">%s</date>\n'
            '<author>%s</author>\n'
            '</sourceDesc></fileDesc></teiHeader>\n'
            '<text><body>\n%s\n</body></text></TEI.2>\n'
            % (escape(bibl), get_date(root), escape(author), escape(text)))


def read_input(path):
    if path.endswith(".gz"):
        with gzip.open(path, "rb") as f:
            return f.read()
    with open(path, "rb") as f:
        return f.read()


def output_name(path, in_root, out_root):
    rel = os.path.relpath(path, in_root)
    for ext in (".fb2.gz", ".fb2"):
        if rel.endswith(ext):
            rel = rel[: -len(ext)]
            break
    return os.path.join(out_root, rel + ".xml")


def process(job):
    src, dst = job
    try:
        xml = convert(parse(read_input(src)))
        os.makedirs(os.path.dirname(dst), exist_ok=True)
        tmp = dst + ".tmp"
        with open(tmp, "w", encoding="utf-8") as f:
            f.write(xml)
        os.replace(tmp, dst)
        return src, None
    except Exception as e:  # noqa: BLE001 -- one bad book must not stop the run
        return src, "%s: %s" % (type(e).__name__, e)


def find_inputs(in_root):
    for dirpath, dirnames, filenames in os.walk(in_root):
        dirnames.sort()
        for fn in sorted(filenames):
            if fn.endswith(".fb2") or fn.endswith(".fb2.gz"):
                yield os.path.join(dirpath, fn)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("input")
    ap.add_argument("output")
    ap.add_argument("-j", "--jobs", type=int, default=os.cpu_count())
    args = ap.parse_args()

    if os.path.isfile(args.input):
        src, err = process((args.input, args.output))
        if err:
            sys.exit("%s: %s" % (src, err))
        return

    jobs = [(s, d) for s in find_inputs(args.input)
            for d in [output_name(s, args.input, args.output)] if not os.path.exists(d)]
    print("%d files to convert" % len(jobs), file=sys.stderr)
    os.makedirs(args.output, exist_ok=True)
    errors = 0
    start = time.time()
    with Pool(args.jobs) as pool, open(os.path.join(args.output, "fb2tei.errors"), "a", encoding="utf-8") as errf:
        for i, (src, err) in enumerate(pool.imap_unordered(process, jobs, chunksize=16), 1):
            if err:
                errors += 1
                errf.write("%s\t%s\n" % (src, err))
                errf.flush()
            if i % 1000 == 0 or i == len(jobs):
                el = time.time() - start
                print("%d/%d done, %d errors, %.0f s, eta %.0f s"
                      % (i, len(jobs), errors, el, el / i * (len(jobs) - i)), file=sys.stderr)


if __name__ == "__main__":
    main()
