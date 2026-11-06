# ddc

The ddc package contains core C++ utilities for the DWDS/Dialing Concordance
document indexing system.

Source code: <https://github.com/sokirko74/ddc3>

The DDC-2.x branch was maintained in SVN under:

    svn+ssh://svn.code.sf.net/p/ddc-concordance/code/ddc/
    https://svn.code.sf.net/p/ddc-concordance/code/ddc/
    svn://svn.code.sf.net/p/ddc-concordance/code/ddc/

## Dependencies

- **A C++17 compiler, make, CMake** — a fresh Ubuntu has no compiler, and the
  `cmake` package does not pull it in; `cmake` then fails with
  "No CMAKE_CXX_COMPILER could be found". On Debian/Ubuntu install everything
  needed for the build with

      sudo apt install build-essential cmake git zlib1g-dev libpugixml-dev libpcre2-dev flex libfl-dev bison

  CMake picks the compiler once, on the first configure (`-DCMAKE_CXX_COMPILER`,
  else `$CXX`, else `c++` from `PATH`, i.e. g++ on Ubuntu), and stores it in
  `build/CMakeCache.txt`. After installing or changing the compiler remove the
  build directory (or `CMakeCache.txt` and `CMakeFiles/`) and configure again.

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

- **cpp-httplib** (bundled in `nlp_base/contrib/httplib`) — HTTP server and
  client. The servers speak HTTP (see [ddc_proto.md](doc/ddc_proto.md)), the
  external term expanders (DTA::CAB) are queried over HTTP as well.

- **GNU bison** >= 3.8 (the C++ parser skeleton) — tested version: 3.8.2.

- **GNU flex** — tested version(s): 2.5.35, 2.5.39, 2.6.1, 2.6.4; the C++ scanner
  needs the system `FlexLexer.h` (Debian/Ubuntu package `libfl-dev`).

  The query parser and scanner are generated from `src/ConcordLib/yyQParser.y`
  and `yyQLexer.l` into the build directory (`build/src/ConcordLib/yyQ*`);
  they are not kept in git.

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
and run with `ctest` in the build directory (`DDC3` must be set, see below).

Set the environment variable `DDC3` to the root of the repository or of an
installation, i.e. a directory with the following layout
(see [Dependencies](#dependencies)):

    $DDC3/config/rml.ini <- config/rml.ini from this repository
    $DDC3/dict           <- build/dict (built from nlp_base)

The simplest choice is the repository itself: it already has `config/rml.ini`, so
only a symlink to the built dictionaries is needed (`/dict` is git-ignored):

    ln -s build/dict dict
    export DDC3=$PWD

Without `DDC3` the programs stop with an error. ddc3 formerly used `RML`
(as the RML programs do); `RML` is now ignored, so both can be installed side by
side. The placeholder `$RML` keeps its name: in `rml.ini` it is replaced by
`$DDC3`, in the daemon config paths by `$DDC3/config`. Logs are written to
`$DDC3/log`.

`$DDC3/config` is also where the programs look for their configs by default:
`ddc_daemon` for `ddc_local_corpora.cfg`, `ddc_server.cfg` and `ddc_server.opt`,
`ddc_xml` for `ddc_xml_server.cfg` and `ddc_template.xml` (the latter is in the
repository). Examples of the configs are in `config/examples/`; copy and edit
them, or pass the files explicitly (`ddc_daemon -l ... -s ...`, `ddc_xml --server ...`).

Take a look at the configuration files in `config/examples/` and the example corpora of the
tests in `src/tests/` to get started.

## Documentation

Reference documentation (formerly POD manpages) is in `doc/`:

- [ddc_query.md](doc/ddc_query.md) — query language
- [ddc_opt.md](doc/ddc_opt.md) — corpus options (`*.opt`, `*.con`)
- [ddc_cfg.md](doc/ddc_cfg.md) — server configuration (`*.cfg`)
- [ddc_server.opt.md](doc/ddc_server.opt.md) — server options
- [ddc_proto.md](doc/ddc_proto.md) — client/server protocol (HTTP)
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
| `DDC_STATIC_BUFLEN=SIZE` | Size in bytes of large static internal string buffers (default 4096). |

## Known bugs

Many.

## Authors

Alexey Sokirko wrote DDC.

Bryan Jurish <jurish@bbaw.de> made various improvements and maintained the
DDC-2.x branch (Copyright 2011-2021 by Bryan Jurish).

DDC is licensed under the GNU Lesser General Public License, version 3 or
later (see `COPYING` and `COPYING.LESSER`); see also `AUTHORS`. The authorship
of individual changes is recorded in the git history.
