# ddc

The ddc package contains core C++ utilities for the DWDS/Dialing Concordance
document indexing system.

Source code: <https://github.com/sokirko74/ddc3>

The DDC-2.x branch was maintained in SVN under:

    svn+ssh://svn.code.sf.net/p/ddc-concordance/code/ddc/
    https://svn.code.sf.net/p/ddc-concordance/code/ddc/
    svn://svn.code.sf.net/p/ddc-concordance/code/ddc/

## Dependencies

- **nlp_base** (git submodule `src/nlp_base`,
  <https://github.com/sokirko74/nlp_base>, formerly morph_dict) — morphology,
  graphematics and structural dictionaries (Ross) shared with RML, with the
  dictionary sources. Fetch it with

      git submodule update --init

  (or clone with `git clone --recursive`). All dictionaries are built from it
  automatically into `build/dict` (`Morph/{Russian,English,German}`, `GraphAn`,
  `Obor`, `GerObor`, `EngObor`); ddc-morph is no longer needed.

- **zlib** (e.g. Debian/Ubuntu package `zlib1g-dev`) — required by nlp_base.

- **pugixml** (Debian/Ubuntu package `libpugixml-dev`, <https://pugixml.org>) —
  XML parser with XPath 1.0, used for XML corpora (text areas, bibliographic fields).

- **PCRE2** (8-bit library, e.g. Debian/Ubuntu package `libpcre2-dev`) —
  Perl-compatible regular expressions. URL: <https://www.pcre.org/>.
  Tested version(s): 10.46.

- **libcurl** (optional) — if available, libcurl can be used for accessing
  external HTTP-based term expanders from within a running DDC process. DDC
  should still compile and run even if libcurl is unavailable, but e.g.
  external HTTP-based term expanders will be unusable.
  URL: <http://curl.haxx.se/>.
  Tested version(s): 7.21.0, 7.38.0, 7.52.1.

- **GNU bison** — tested version(s): 2.4.1, 3.0.2, 3.0.4.

  If you get errors compiling `src/ConcordLib/yyQParser.o`, try re-extracting
  the sources and call

      touch src/ConcordLib/yyQParser.cpp src/ConcordLib/yyQParser.h

  before re-compiling.

- **GNU flex** — tested version(s): 2.5.35, 2.5.39, 2.6.1.

  If you get errors compiling `src/ConcordLib/yyQLexer.o`, try re-extracting
  the sources and call

      touch src/ConcordLib/yyQLexer.cpp src/ConcordLib/yyQLexer.h

  before re-compiling.

## Encoding

DDC 3 talks to the outside world only in UTF-8: corpus texts, queries and all
output. Single-byte (cp1251/latin1) corpora are no longer supported; convert
them with `iconv` and reindex. Morphology and graphematics work with
cp1251/cp1252 internally, DDC converts at the boundary. Texts with characters
outside these encodings (e.g. historical German with "ſ") should use the
language `Generic` (raw UTF-8, no morphology).

Input that is not valid UTF-8 is rejected with an error: corpus files
(`ddc_index`), queries (`ddc_simple`, `ddc_console`, `ddc_qparse`, the server)
and terms (`ddc_expand`, `expand_terms`).

## Building

DDC runs on Linux (POSIX) only: the daemon, sockets, threads, mmap and
process statistics use POSIX/Linux APIs. The shared libraries `nlp_base`
(and later `graphan`) stay portable, since RML uses them on Windows too.


DDC is built with CMake from the top-level directory:

    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build -j

Binaries are left in the build directory (e.g. `build/src/ddc_daemon/ddc_daemon`);
there is no install target. The tests are built with `-DCMAKE_BUILD_TYPE=Debug`
and run with `ctest` in the build directory (`RML` must be set, see below).

Set the (legacy) environment variable `RML` to a directory with the following
layout (see [Dependencies](#dependencies)):

    $RML/Bin/rml.ini     <- Bin/rml.ini from this repository
    $RML/dict            <- build/dict (built from nlp_base)

    export RML=/path/to/rml

Note that `rml.ini` now lives in `$RML/Bin` (formerly `$RML/etc`).

Take a look at the configuration files in `etc/` and the example corpora of the
tests in `src/tests/` to get started.

## Documentation

Reference documentation (formerly POD manpages) is in `doc/`:

- [ddc_query.md](doc/ddc_query.md) — query language
- [ddc_opt.md](doc/ddc_opt.md) — corpus options (`*.opt`, `*.con`)
- [ddc_cfg.md](doc/ddc_cfg.md) — server configuration (`*.cfg`)
- [ddc_server.opt.md](doc/ddc_server.opt.md) — server options
- [ddc_proto.md](doc/ddc_proto.md) — client/server protocol
- [ddc_files.md](doc/ddc_files.md) — index file formats
- [ddc_tabs.md](doc/ddc_tabs.md) — tab-separated (`ddc_dump --tabs`) format

## Build options

The following CMake options (`-DNAME=VALUE`) are supported:

| Option | Description |
|---|---|
| `CMAKE_BUILD_TYPE=Debug` | Build with debugging flags. |
| `DDC_USE_HIRES_CLOCK=ON` | Enable high-resolution clock if available. Requires `clock_gettime()`. ON by default for Debug builds, otherwise OFF. |
| `DDC_JSON_DEEP_CONTEXT=ON` | Enable deep encoding of extra-sentential context tokens in JSON output strings. OFF by default, since it breaks strict backwards-compatibility. |
| `DDC_ENABLE_MMAP=OFF` | Disable mmap virtual memory support (ON by default if available). |
| `DDC_ENABLE_CURL_UNIX_URLS=OFF` | Disable UNIX socket URL conventions for CCurl. |
| `DDC_STATIC_BUFLEN=SIZE` | Size in bytes of large static internal string buffers (default 4096). |

CURL support is enabled automatically if libcurl development files are found.

## Known bugs

Many.

## Authors

Alexey Sokirko wrote DDC.

Bryan Jurish <jurish@bbaw.de> made various improvements and maintained the
DDC-2.x branch (Copyright 2011-2021 by Bryan Jurish).

DDC is licensed under the GNU Lesser General Public License, version 3 or
later (see `COPYING` and `COPYING.LESSER`); see also `AUTHORS`. The authorship
of individual changes is recorded in the git history.
