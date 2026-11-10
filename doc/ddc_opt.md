# DDC \*.opt FILE SYNTAX

This manpage describes the syntax of \*.opt index option files ("opt-files") used by the DDC corpus indexing system.

# SYNOPSIS

```
##-------------------------------------------------------------
## Option Processor Directives

#comment
include "OPTFILE"

##-------------------------------------------------------------
## Required Declarations

LANG
IndexType TYPE

##-------------------------------------------------------------
## Boolean Flags and Switches

Utf8
MemoryMap
CaseInsensitive
DisableDefaultQueryLexicalExpansion
ShowNumberOfRelevantDocuments
QueryOnlyFiles
NoContextOperator
AllowUnsafeQueries
AllowCountByTokenAttribute
OutputBibliographyOfHits
LemmaQueryUsesMorphPattern

IndexChunks
IndexMorphPatterns
IndexPunctuation
UseDwdsThesaurus
UseParagraphTagToDivide
EmptyLineIsNotSentenceDelim
DontUseIndention
ArchiveIndex
ResumeOnIndexErrors

GutenbergInterface
DwdsCorpusInterface

##-------------------------------------------------------------
## Single-valued Options

Indices INDEXLIST
IndexAlias FROM TO
IndicesToShow SHOWLIST
DefaultBibl NAME
HitBorders BREAKLIST

HtmlHighlighting L;R;LL;RR
TextHighlighting L;R;LL;RR
TableHighlighting L;R;LL;RR
TokenDelimiter STRING
InterpDelimiter STRING

RightKwicContextSize N
LeftKwicContextSize N
NumberOfKwicLinesInSnippets N
MaxRegExpExpansionSize N
MaxCachedHitsCount N
MaxQueryCacheSize N
EstimateHitsCount N
UserMaxTokenCountInOnePeriod N

LocalPathPrefix VAL
InternetPathPrefix VAL

TfIdfRank FLOAT
PositionRank FLOAT
NearRank FLOAT

ServerInfo KEY VALUE
ServerInfoFile KEY FILENAME

##-------------------------------------------------------------
## Multi-valued Options

textarea ...
Bibl ...
Expand ...
ExpandBibl ...
DefaultQueryIndex ...
Bigrams ...
```

# DESCRIPTION

This section contains descriptions of the various options and flags which may occur in a DDC corpus opt-file, insofar as the author is able to provide them. These are for the most part legacy options which may or may not be fully functional. I have not tested (most of) these options for functionality. The reader is strongly advised to perform his or her own tests before using any of the options described below (but particularly the undocumented ones) in a production environment.

At runtime, DDC loads exactly one "top-level" corpus opt-file (`CORPUS.opt`) for each physical (sub)corpus inventory `CORPUS.con`. Typically, the opt-files for physical subcorpora ("shards") will contain nothing more than an [include](#include) directive pointing to a superordinate shared options file.

Note that server option-files (`ddc_server.opt`) as read by the `ddc_daemon` program are documented independently; see [ddc\_server.opt(5)](ddc_server.opt.md) for details.

## Sources

DDC opt-files are parsed and processed by the method CConcIndexator::LoadOptionsFromString() after intialization of default option values by the method CConcIndexator::InitDefaultOptions(), both of which methods are defined in `src/ConcordLib/ConcordOptions.cpp`. Refer to the source code for further enlightenment.

## Option Processor Directives

### #comment

Comments are lines starting with a literal hash-mark (`#`). Such lines are ignored by the option processor **except** for the backwards-compatible [#include](#include) directive.

### include

```
include "OPTFILE"
#include "OPTFILE"
```

The `include` directive inserts the contents of an external opt-file at the current position. If OPTFILE is a relative pathname, it is interpreted relative to the directory containing the top-level opt-file for the current physical (sub)corpus.

Note that for historical reasons, the C preprocessor syntax `#include "OPTFILE"` is also supported, is **NOT** a comment, and **WILL** be evaluated. This behavior may change in the future.

## Required Declarations

Each DDC option file requires two obligatory declarations [LANG](#lang) and [IndexType](#indextype), which should occur as the first two options in an opt-file (although they may be defined by an external file loaded with the [include](#include) directive).

### IndexType

```
IndexType TYPE
```

Sets the type of the underlying corpus index. *TYPE* can be `DWDS_Index`, `MorphXML_Index`, `Free_Index`, or `TabFormat_Index`.

Future versions of DDC may support only the `TabFormat_Index` type; see [ddc\_tabs(5)](ddc_tabs.md) for details on the `TabFormat_Index` format.

### LANG

Sets language to use for runtime lexical expansion and possibly index-time analysis. Known languages are `German`, `Russian`, `English`, and (possibly) `Generic`.

## Boolean Flags and Switches

The following options represent boolean flags and switches, which are set if and only if the corresponding flag appears in the corpus opt-file. As of ddc v2.0.20, each boolean flag may appear with an optional value argument. The value arguments `no`, `n`, `false`, `off`, `disabled`, and `0` cause the corresponding boolean flag to be cleared. Omitting the value argument or specifying any other value causes the flag to be set.

Prior to ddc v2.0.20, there was no way to override a previously set boolean flag: to disable a boolean option backwards-compatibly, omit it from the opt-file or comment it out.

### Utf8

Since DDC 3 this option is always on and `Utf8 0` is ignored (with a warning): all corpus data, queries and output are UTF-8. The morphology and graphematics use single-byte encodings internally (cp1251 for Russian, cp1252 for English and German) and the conversion is done by DDC. Texts with characters outside these encodings (e.g. historical German with "ſ") should be indexed with the language `Generic`, which keeps the UTF-8 text unchanged (no morphology). DDC sets a UTF-8 LC\_CTYPE if the current locale is not UTF-8.

### MemoryMap

If specified ande true, DDC will attempt to map runtime index data from the filesystem into virtual memory on startup. If unspecified or false, DDC will fall back to the pre-v2.1.12 behavior of loading runtime index data into resident memory on startup, which tends to be both slow and resource-hungry. Use of the MemoryMap option requires a working mmap() system call and compile-time support in the underlying DDC library.

Since ddc v2.1.12.

### DisableDefaultQueryLexicalExpansion

If specified and true, DDC will not include the `infl` term expander to the default expansion pipeline for the `Token` index.

Note that a term expansion explicitly defined with an [Expand](#expand) clause for the `Token` index will override the effects of this option.

### CaseInsensitive

If specified and true, DDC will not add the `case` term expander to the default expansion pipeline for the `Token` index.

Note that a term expansion explicitly defined with an [Expand](#expand) clause for the `Token` index will override the effects of this option.

### ShowNumberOfRelevantDocuments

(from DDCReadme): If set, DDC calculates the number of relevant documents, otherwise the member that holds this number is set to 0.

### QueryOnlyFiles

(from DDCReadme): If set, DDC doesn't create a sentence break collection. Only meaningful for `DWDS_Index` or `MorphXML_Index` [Index Types](#indextype).

### NoContextOperator

(from DDCReadme): If set, prohibits context operator (#CNTXT) in the query language.

### AllowUnsafeQueries

Unless this option is set to a true value, any attempt to compile a potentially unsafe query will cause a runtime exception to be thrown. Currently, only file-list queries (`< FILENAME`) are considered "unsafe" for such purposes. False by default.

### AllowCountByTokenAttributes

Unless this option is set to a true value, any attempt to use a token-level attribute as a count-key (`#by[..., $INDEX ...]`) will cause a runtime exception to be thrown. True by default, can be disabled with e.g. `AllowCountByTokenAttributes no`.

### OutputBibliographyOfHits

(from DDCReadme): If set, then DDC outputs bibliographical information for hits instead of filenames.

### LemmaQueryUsesMorphPattern

If true (default), then DDC will treat `%LEMMA` queries as `$Lemma=[LEMMA]`, i.e. implicitly insert @-delimters around a regex `LEMMA`. Otherwise, `%LEMMA` queries will be treated as `$Lema=@LEMMA`, i.e. literal matches. Since ddc v2.0.20.

### IndexChunks

(from DDCReadme): If set, enables indexing and querying using 'chunks', otherwise chunks are ignored. Only meaningful for the `Free_Index` [Index Type](#indextype).

NOTE: seems to control implicit creation of a `Chunk` index.

### IndexMorphPatterns

(from DDCReadme): If set, DDC creates a `MorphPattern` index. Only meaningful for the `DWDS_Index` [Index Type](#indextype).

### IndexPunctuation

(from DDCReadme): Index punctuation marks only if set. Only meaningful for the `DWDS_Index` [Index Type](#indextype).

### UseDwdsThesaurus

(from DDCReadme): Enable creation and use of the `Thes` thesaurus index if set. Only meaningful for the `DWDS_Index` [Index Type](#indextype).

### UseParagraphTagToDivide

(from DDCReadme): If set, the tokenizer seeks `</p>` in the input texts in order to divide the text into paragraphs. Only meaningful for the `DWDS_Index` [Index Type](#indextype).

### EmptyLineIsNotSentenceDelim

(from DDCReadme): If set, an empty line in the input texts is not interpreted as an end of sentence. Only meaningful for the `DWDS_Index` [Index Type](#indextype).

### DontUseIndention

(from DDCReadme): If set, DDC doesn’t use indention (sic; assumedly "indentation" is meant) to find paragraph breaks. Only meaningful for the `DWDS_Index` [Index Type](#indextype).

### ArchiveIndex

    ArchiveIndex

Store the occurrences of the indices compressed: the distances between neighbouring occurrences in a variable-length
code (7 bits per byte, VByte), starting anew in each search period. The same as the type `archive` of an index in
[Indices](#indices). The lists of occurrences take about half the space (Flibusta, 234 million tokens: Token 892 → 431 MB,
MorphPattern 694 → 268 MB, the index 2.6 → 1.7 GB); the queries are about 5% slower when the index is in the page cache
and faster when it is read from the disk. Changing the option requires re-indexing.

### ResumeOnIndexErrors

    ResumeOnIndexErrors 1

If set, `ddc_index` skips a corpus file that cannot be indexed (e.g. invalid XML or UTF-8, or a text
larger than the 256 MB limit of the graphematics) with a warning and goes on; the skipped files are
listed in `<project>._error_log`. By default the first such file stops the indexing.

### GutenbergInterface

Undocumented

### DwdsCorpusInterface

(from DDCReadme): If set, enables DWDS-like formatting for output hits.

## Single-valued Options

The following options take a single argument, which may be a list of values. Each of these options should occur at most once in an opt-file. Assumedly, in the case of multiple occurrences of the same option, the most recent declaration "wins".

### Indices

```
Indices INDEXLIST
```

(largely drawn from DDCReadme): Declares index fields used by the underlying corpus index. `INDEXLIST` is a list of index declarations delimited by semicolons `;`. Each index declaration is a string of the form

```
[LONGNAME SHORTNAME ARCHIVE STORAGE]
```

where:

- LONGNAME

  is a long name for the index, conventionally in CamelCase;

- SHORTNAME

  is a short name for the index, conventionally in all lower-case and frequently only a single character;

- ARCHIVE

  is one of the strings `archive` or `normal`. If it is `archive`, the current index is archived, otherwise it is not; and

- STORAGE

  is one of the strings `storage` or `storage_omit`. If it is `storage`, then the index is supplied with a storage during indexing, otherwise storage is not built. By default the first index is built with a storage (if it is not "manually prohibited" (whatever that means)), other indices are built without storages. If you want your DDC index to **display** values of this attribute for tokens matching a user query, you should set this to `storage`. If you're only interested in **querying** this attribute, you can safely set it to `storage_omit`.

The [Indices](#indices) option is only supported for the `Free_Index` [Index Type](#indextype).

### IndexAlias

```
IndexAlias FROM TO
```

Defines a new token-level alias `FROM` for the existing index `TO`. `TO` may be a long index name declared in [Indices](#indices), a short index name declared in [Indices](#indices), or a valid index alias previously declared by another `IndexAlias` directive. Causes all runtime query operations on the pseudo-index `FROM` to be evaluated with respect to the underlying index `TO`. Useful for facilitating interoperability of heterogeneous corpora.

Since v2.1.5

### IndicesToShow

```
IndicesToShow SHOWLIST
```

Declares a list of those indices which should be returned in hit responses to user queries. `SHOWLIST` is a list of index keys, separated by whitespace, commata (',') or semicolons (';'). Each index label in `SHOWLIST` can be either:

- a long index name declared by [Indices](#indices) (since v2.1.5),

- a short index name declared by [Indices](#indices) (since v2.1.5),

- an index alias label declared by [IndexAlias](#indexalias) (since v2.1.5), or

- the integer position *i* of the corresponding index declaration in [Indices](#indices), counting from 1; i.e. for each *i*, 1 \<= *i* \<= N\_INDICES, where N\_INDICES is the number of index declarations by the [Indices](#indices) option.

By default, [IndicesToShow](#indicestoshow) is `1`, i.e. words are represented only by the value of the first index (normally the text of the token itself). If some index is mentioned in IndicesToShow, then it must have an index storage built during indexing. Prior to v2.1.5, **ONLY** whitespace-separated integer positions were allowed for `SHOWLIST`.

Only supported for the `Free_Index` [IndexType](#indextype).

Support for long and short index names, aliases, and additional separators since v2.1.5.

### DefaultBibl

```
DefaultBibl NAME
```

`NAME` is the name of a fallback bibliographic field to be queried if no literal match is found for a runtime (user) filter. `NAME` must be the name of a bibliographic metadata attribute as defined by the [Bibl](#bibl) option. This option can be used in conjunction with a `constant` bibliographic metadata attribute to provide a default value for unknown bibliographic metadata attributes, e.g. to facilitate interoperability between multiple heterogeneous corpora without the need for re-indexing or explicit definition of [Bibl](#bibl) constant fields. If omitted or set to the empty string (the default), query filters on an undefined bibliographic attribute will raise a runtime error.

**CAVEAT**: You should think **carefully** before using this feature, since it will suppress error and/or warning messages due to typographical errors for "real" attribute fields.

Since v2.0.27

### HitBorders

```
HitBorders BREAKLIST
```

(largely from DDCReadme): `BREAKLIST` is a string of break collection declarations delimited by semicolons `;`. Each break collection declaration is a colon-separated string of the form `[LONGNAME:SHORTNAME]` or `[LONGNAME:SHORTNAME:default]`, where

- LONGNAME

  is a long name for the break collection, conventionally in CamelCase;

- SHORTNAME

  is a short name for the break collection, conventionally in all lower-case and frequently only a single character; and

- `default`

  is the literal string `default`, which if present indicates that the current break collection is to be used for queries which do not specify any break collection specification (e.g. using the `#WITHIN` query operator).

The [HitBorders](#hitborders) option is only supported for the `Free_Index` [Index Type](#indextype).

### HtmlHighlighting

```
HtmlHighlighting TAGS
```

Set highlighting strings to use for identifying matched tokens in hits returned in HTML format. `TAGS` is a string of the form `L;R;LL;RR`, where the first matched token *w* in any hit is marked by `L`*w*`R`, and subsequent matched tokens in the same hit are marked as `LL`*w*`RR`. Tag strings support C-style escapes as well as JSON-style unicode (UTF-8) escapes.

Default is:

```
HtmlHighlighting <STRONG><FONT COLOR=red>;</FONT></STRONG>;<STRONG><FONT COLOR=red>;</FONT></STRONG>
```

### TextHighlighting

```
TextHighlighting TAGS
```

Set highlighting strings to use for identifying matched tokens in hits returned in text format. `TAGS` is string as described under [HtmlHighlighting](#htmlhighlighting).

Default is:

```
TextHighlighting &&;&&;_&;&_
```

### TableHighlighting

```
TableHighlighting TAGS
```

Set highlighting strings to use for identifying matched tokens in hits returned in table format. `TAGS` is string as described under [HtmlHighlighting](#htmlhighlighting).

Default is:

```
TableHighlighting &&;&&;_&;&_
```

### TokenDelimiter

```
TokenDelimiter DELIM
```

Set delimiter string to be inserted before the data for each token in HTML, Text, and Table output formats. Prior to DDC release 2.0 (branch 1.80-dx1), this option was not present and token boundaries could not be reliably determined from the built-in output formats. The string DELIM may not contain any literal whitespace, but C-style escapes and JSON-style unicode escapes are supported

For historical reasons, DELIM defaults to an empty string.

### InterpDelimiter

```
InterpDelimiter DELIM
```

Set delimiter string to be inserted between individual index fields for each token in HTML, Text, and Table output formats. The string DELIM may not contain any literal whitespace, but C-style escapes and JSON-style unicode escapes are supported Defaults to `#`.

For historical reasons, the (misspelled) option `InterpDelimeter` is an alias for `InterpDelimiter`.

### LeftKwicContextSize

```
LeftKwicContextSize N
```

(from DDCReadme): Set the length of the right context to use for each KWIC line when generating file summaries (snippets). The default value is 4.

### RightKwicContextSize

```
RightKwicContextSize N
```

(from DDCReadme): Set the length of the right context to use for each KWIC line when generating file summaries (snippets). The default value is 4.

### NumberOfKwicLinesInSnippets

```
NumberOfKwicLinesInSnippets N
```

(from DDCReadme): Set the number of kwic lines in snippets. The default value is 10.

### MaxRegExpExpansionSize

```
MaxRegExpExpansionSize N
```

(from DDCReadme): Set the maximum number of indexed items which can be included in an expansion set of one regular expression. Default value is 1000000.

### MaxCachedHitsCount

```
MaxCachedHitsCount N
```

Set maximum number of hits to store in a cache entry of an associated CConcHolder (subcorpus server). Query results with more than `N` hits will not be cached. Default=512.

Since v2.0.23 (formerly a global constant = 500).

### MaxQueryCacheSize

```
MaxQueryCacheSize N
```

Set maximum number of queries to be LRU-cached by an associated CConcHolder (subcorpus server). Default=512.

Since v2.0.23 (formerly a global constant = 500).


### EstimateHitsCount

```
EstimateHitsCount N
```

Estimate the number of hits instead of counting all of them. A query without sort operators (and not a `count()` query) is evaluated period by period (see [UserMaxTokenCountInOnePeriod](#usermaxtokencountinoneperiod)); with `N > 0` the evaluation stops as soon as at least `N` hits are found and the requested hits (`start+limit`, at least [MaxCachedHitsCount](#maxcachedhitscount)) are there. The number of hits (and of relevant documents) is then extrapolated: the hits found divided by the share of the tokens of the subcorpus searched so far. The response of [run\_query](ddc_protocol.md#run_query) has `"nhits_estimated_":1` in this case.

The hits returned are the same as without the option, since they are taken from the periods already searched, only `nhits_` is approximate (for a corpus of books in periods of 5 million tokens and `N = 10000` it differs from the exact number by up to about 10%). A query with fewer than `N` hits is counted exactly. Default: 0 (count all hits).

Since ddc3.
### UserMaxTokenCountInOnePeriod

```
UserMaxTokenCountInOnePeriod N
```

(from DDCReadme): Set the size of internal subcorpus blocks. The greater the value of this parameter is, the faster querying procedures work, and the more memory the program needs.

This parameter is basically a block-size limit for so-called "periods" (aka "partitions", "blocks") of a physical sucorpus used implicitly by the low-level query evaluation routines. A "period" is a contiguous sequence of documents within a single physical (sub)corpus. `CConcSession::GetAllHits()` iterates over all "periods" of a physical subcorpus, and (re-)populates the set of query hits within the current "period" at each step of the iteration. Query filters (sort operators, `#HAS_FIELD`, etc.) are re-evaluated for each period-local hit subset. User-supplied timeout values and hint optimization are only checked at the end of each "period"-specific iteration.

This mechanism was probably originally meant to reduce the likelihood of RAM overflow for large result-sets (e.g. function words) with nontrival filters (e.g. =#HAS\[author,...\]=) by restricting the number of hits that had to be kept in memory at any given time, under the assumption that the filter stage would substantially reduce the number of valid hits, but can lead to longer query times especially for large corpora containing many "small" documents in the presence of a non-trvial sort operator (e.g. `#ASC_DATE`).

Default if unspecified is hard-coded as 5000000 (5M).

### UserMaxInputLoadIndexSize

```
UserMaxInputLoadIndexSize N
```

Minimum number of tokens to buffer during corpus indexing before considering flushing to disk and possibly introducing a [period boundary](#usermaxtokencountinoneperiod). Must be strictly less than [UserMaxTokenCountInOnePeriod](#usermaxtokencountinoneperiod), otherwise defaults to `UserMaxTokenCountInOnePeriod/10`.

Global default if unspecified is hard-coded as 400000 (400K).

Since v2.2.0 (previously only a hard-coded constant).

### LocalPathPrefix

```
LocalPathPrefix STRING
```

(from DDCReadme): The common prefix of each corpus filename that should be replaced by the value of [InternetPathPrefix](#internetpathprefix) when DDC outputs file names.

### InternetPathPrefix

```
InternetPathPrefix STRING
```

Replaces the value of [LocalPathPrefix](#localpathprefix) in corpus filenames if and when they occur in DDC output.

### TfIdfRank

```
TfIdfRank FLOAT
```

(from DDCReadme): Float parameter (0 \<=FLOAT \< 1) for TFIDF weighting.

### PositionRank

```
PositionRank FLOAT
```

(from DDCReadme): Float parameter (0 \<=FLOAT \< 1) for position weighting.

### NearRank

```
NearRank FLOAT
```

Float parameter (0 \<=FLOAT \< 1) for NEAR weighting.

### ServerInfo

```
ServerInfo KEY VALUE
```

Sets a constant value to be returned in responses to client 'info' requests to an associated CDDCLeafServer (see [ddc\_protocol](ddc_protocol.md)). KEY is a key string optionally containing C escapes, and VALUE is a literal JSON value to be returned as the value of `user.KEY` in leaf-server 'info' responses.

Since v2.0.34.

### ServerInfoFile

```
ServerInfoFile KEY FILENAME
```

Sets an external filename value to be returned in responses to client 'info' requests to an associated CDDCLeafServer (see [ddc\_protocol](ddc_protocol.md)). KEY is a key string optionally containing C escapes, and FILENAME is a filename containing literal JSON code to be returned as the value of `user.KEY` in leaf-server 'info' responses. FILENAME is interpreted relative to the directory containing the project \*.con file associated with the leaf server. As of v2.1.5, leading and trailing whitespace will be implicitly trimmed from FILENAME.

Since v2.0.34.

## Multi-valued Options

The following options may occur multiple times in a single opt-file.

### textarea

```
textarea NAME XPATH
```

(from DDCReadme): Each `textarea` declaration describes a single text area, where NAME is name of the text area field, and XPATH is an X-Path.

### Bibl

```
Bibl alias            NAME VALUE
Bibl TYPE  VISIBILITY NAME VALUE
```

(mostly from DDCReadme): Each `Bibl` declaration describes a single bibliographic field (such as date of publication, author, and so on). The bibliographic field can be predefined ("orig", "scan", "date", "page", "pagerank") or free (user-defined). Predefined bibliographic fields have special processing in DDC, for example, field "scan" is used to build a hit header. Free bibliographic fields can contain either integer or string data: for both datatypes, one can use the general filter operator or general order operators (`#HAS` and `#LESS_BY` respectively). The arguments to free `Bibl` are:

- TYPE

  is the type of the bibliographic field; either `string`, `integer`, `constant`, or `alias`.

- VISIBILITY

  (only for non-`alias` metadata fields); either `1` or `0`: if it is "1", then DDC displays the value of the field for each hit header. For `alias` fields, the `VISIBILITY` flag should be omitted.

- NAME

  a symbolic name for this bibliographic field (by convention all lower-case); and

- VALUE

  For the `string` and `integer` types, `VALUE` should be an X-Path specification of the location of the field data in corpus source documents; for the `constant` type, it should be a literal string indicating the value to be returned, and for the `alias` type, it should be the name of the target bibliographic field (or other alias) for which the pseudo-attribute `NAME` is to serve as an alias.

  All X-Path expressions for the document-dependent `string` and `integer` metadata types should be "trivial" in the sense that for each input document, every metadata X-Path `VALUE` should resolve to a unique attribute- or element-node, whose content should be a single text node containing all and only the string to be indexed as the value of the metadata attribute `NAME` for that document (i.e. any nested elements and their content will be ignored). For best results, the X-Path should be an absolute `XPATH` is an absolute location path (beginning with `/`), and consisting only of element names (`foo`), element wildcards (`*`), slashes (`/`), and attribute restriction clauses (`[@foo="bar"]`).

  A non-empty "`date`" attribute is **required** for all input documents, and all metadata attribute values may be at most 20000 bytes (20 kB) in length: longer values in input files will cause the `ddc_index` process to abort.

Note that additions, deletions, and/or changes to `constant` bibliographic fields do **not** require re-indexing, whereas any changes to non-`constant` fields **do**.

As of v2.1.5, leading and trailing whitespace will be implicitly trimmed from `VALUE` strings for metadata fields of type "`constant`".

Prior to v2.0.30, multiple definitions of a bibliographic field `NAME` caused a fatal error when loading a corpus project. As of v2.0.30, a warning is emitted in these cases, and the most recent definition is used (later definitions effectively "clobbering" earlier ones).

Since v1.x; `alias` fields since v2.1.5, `constant` fields since v2.0.27, multiple definition since v2.0.30.

### Bigrams

```
Bigrams INDEXNAME MAXLEN BREAKNAME
```

Request construction of an n-gram index at indexing time, suitable for sorting runtime hits lexicographically by neighbor *INDEXNAME* using the `#left` and/or `#right` query operators. Up to *MAXLEN* neighbors are considered for the sort. Breaks of type *BREAKNAME* terminate the sort. Example usage: `Bigrams Token 2 s`.

**OBSOLETE** as of ddc v2.0.19, which supports generic `#left` and/or `#right` query operators on arbitrary token attributes within the current query break collection, provided the indices for the attributes in question were built with the [STORAGE](#storage) option set.

### Expand

```
Expand LABEL CLASS PARAM...
```

Declares a named term expander which can be used to expand index queries using either the explicit pipeline notation (`|LABEL|...`), or implicit expansion heuristics on a per-index basis. Conceptually, each expander in a pipeline operates on the set of terms returned by the previous expander in the pipeline, and the set returned by the final expander in the pipeline represents that set of index values which qualify as "matches" to the term queried.

*LABEL* is a label string used to identify the expander in user-specified pipelines. If *LABEL* is also the *LONGNAME* of an index field declared in [Indices](#indices), then the corresponding expander is used implicitly if no explicit pipeline is specified or if the default pipeline `|-` is used.

*CLASS* is a string representing the expansion function to use, and *PARAM...* are additional parameters to the expansion function. Currently supported expander classes are:

- Id

  ```
  Expand LABEL Id
  Expand LABEL Null
  ```

  Identity expander (no-op). Parameters: none.

- Case

  ```
  Expand LABEL Case LANG
  ```

  Letter-case expander (upper- vs. lower-case). Parameters: `LANG`, a language string as accepted by the [LANG](#lang) declaration. In particular, the "language" `Generic` can be used to specify that the C99 locale settings should be used to provide upper/lower-case mappings on wide character strings: in this case, you must ensure that the *LC\_CTYPE* enviornment variable for the DDC process is set appropriately for the corpus and runtime query data.

  Note that not all letter-case variants are created by this expander ("McTaggart problem").

- ToLower

  ```
  Expand LABEL ToLower LANG
  ```

  Forces all terms to lower-case. Parameters: `LANG`, a language string as accepted by the [LANG](#lang) declaration, or `Generic` to use the C99 locale settings.

- ToUpper

  ```
  Expand LABEL ToUpper LANG
  ```

  Forces all terms to upper-case. Parameters: `LANG`, a language string as accepted by the [LANG](#lang) declaration, or `Generic` to use the C99 locale settings.

- Infl

  ```
  Expand LABEL Infl LANG
  Expand LABEL Morph LANG
  ```

  Inflectional variant expander using built-in morphology tables. Parameters: `LANG`, a language string as accepted by the [LANG](#lang) declaration.

- Cab

  ```
  Expand LABEL Cab URL TIMEOUT DEBUG MAPMODE
  ```

  Orthographic variant expander which queries an external DTA::CAB HTTP server. Parameters:

  - URL

    URL of the DTA::CAB HTTP server to be queried with `GET` request. The underlying implementation appends a URL-encoded parameter `qd=DATA` to this URL before requesting data from the server, where *DATA* is a newline-separated list of types to be expanded. The data format returned by the server is assumed to be a list of expanded types separated by TABs, newlines, and/or carriage returns. Empty-string types in the output are ignored.

    As of ddc v2.1.8, ddc supports HTTP over UNIX domain sockets on the local machine by means of specially formatted URLs:

    ```
    http:/path/to/socket//request/uri        # perl LWP::Protocol::http::SocketUnixAlt style
    unix:/path/to/socket|http:///request/uri # apache mod_proxy style
    http+unix:/path/to/socket//request/uri   # native http+unix scheme, //-separated
    http+unix:/path/to/socket|/request/uri   # native http+unix scheme, |-separated
    ```

    ... all of these URL formats should cause ddc to query the HTTP server listening on the unix socket `/path/to/socket` with a `GET` request for the URI `/request/uri`.

  - TIMEOUT

    Timeout in seconds for the expansion query. If the timeout is exceeded, a warning is printed and the CAB expander behaves like an [Id](#id) expander, returning the same set it was passed.

  - DEBUG

    Boolean flag for debugging. If set to a true value, all data passed to and from the external DTA::CAB server will be echoed to stderr. Not for production use.

  - MAPMODE

    Boolean flag. If false or unspecified ("union-mode"), all input terms are implicitly included to the output set, regardless of whether or not they are also present in the server's response. If *MAPMODE* specified and true, only those terms explicitly included in the server's response are included in the output set.

- CabMap

  ```
  Expand LABEL CabMap URL TIMEOUT DEBUG MAPMODE
  ```

  Wrapper for the [Cab](#cab) class with a default *MAPMODE*=1.

- Chain

  ```
  Expand LABEL Chain PIPELINE...
  ```

  Assigns a label to a chain of previously defined expanders. Takes a `PIPELINE` of expander labels as its argument: expander labels in `PIPELINE` may separated by whitespace and/or the `|` symbol (multiple consecutive delimiters are ignored). Note that an empty expander chain is equivalent to an [Id](#id) expander.

DDC ensures that the following expander labels are defined, instantiating them with default parameters only if no other expander with the same label is explicitly defined in the opt-file:

- id

  Defined as `Expand id Id`

- null

  Defined as `Expand null Id`

- case

  Defined as `Expand case Generic` (DDC 3 is always [Utf8](#utf8)).

- infl

  Defined as `Expand infl LANG`.

- Token

  Default expansion chain for the *Token* index. Usually defined as `Expand Token Chain infl case`, but note that the `case` component will be omitted from the default chain unless the legacy [CaseInsensitive](#caseinsensitive) flag is set, and the `infl` component will be omitted if the legacy [DisableDefaultQueryLexicalExpansion](#disabledefaultquerylexicalexpansion) option is set.

### ExpandBibl

```
ExpandBibl LABEL TARGET CLASS PARAM...
```

Declares a named bibliographic expander which can be used in place of a physically indexed bibliographic fields (as declared with the [Bibl](#bibl) option) in #HAS\_FIELD queries.

*LABEL* is a label string used to identify the expander in user-specified pipelines. *TARGET* is the unique *NAME* associated with a physically indexed bibliographic field used for the underlying query. If *LABEL* is also the *NAME* of a physically indexed bibliographic field declared with [Bibl](#bibl), then the pseudo-field declared with `ExpandBibl` has precedence when evaluating user queries.

*CLASS* is a string representing the expansion function to use, and *PARAM...* are additional parameters to the expansion function. Currently (ddc v2.0.5), all *CLASS*es supported by the [Expand](#expand) option are also supported by `ExpandBibl`, except for the `Chain|/chain` class.

No bibliographic expanders are defined by default.

### DefaultQueryIndex

```
DefaultQueryIndex OPKEY INDEXNAME
```

Use index `INDEXNAME` if otherwise unspecified for runtime queries using operator `OPKEY`. Known values for `OPKEY`, the associated query classes, and the associated default values for `INDEXNAME` are:

```
 OPKEY	(INDEXNAME)	CLASS...
-----------------------------------------------------------------------
  _	(Token)		CQTokInfl
 @_    (Token)		CQTokExact
 %_    (Lemma)		CQTokLemma
 /_/   (Token)		CQTokRegex, CQTokSuffix, CQTokPrefix, CQTokInfix
 [_]   (MorphPattern)	CQTokMorph
:{_}   (Thes)		CQTokThes
 ^_    (Chunk)		CQTokChunk
 <_    (Token)		CQTokFile
  *    (Token)		none (generic fallback)
  .    n/a		CQTokAnchor
```

The "." operator key is used by $. queries; its `INDEXNAME` should resolve to a break name rather than a token-level index name. Default is whatever break collection was declared as the default.

# ACKNOWLEDGEMENTS

Alexey Sokirko wrote the original DDC and the DDCReadme.pdf on which much of the information in this manpage is based.

# AUTHOR

Bryan Jurish \<jurish@bbaw.de\>

# SEE ALSO

ddc\_server.opt(5), ddc\_tabs(5), ddc\_console(1), ddc\_daemon(1), ddc\_expand(1), ddc\_file\_lem(1), ddc\_graphmat\_thick(1), ddc\_index(1), ddc\_morph\_gen(1), ddc\_search(1), ddc\_simple(1), ddc\_stats(1), ddc\_struct\_dict\_loader(1), ddc\_test\_lem(1), ddc\_xml(1)
