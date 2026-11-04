# DDC TAB-DUMP FORMAT

This manual page describes the output format produced by the `ddc_dump` program using the `--full --tabs` (`-f -t`) option(s). When running in this mode, the `--output DIR` option specifies the directory `DIR` to which file(s) are to be written. One output file `DIR/FID.tabs` is created in the specified directory for each document represented in the index, where `FID` is the logical index-number of the corresponding document, starting from zero. The remainder of this document describes the format of the `DIR/FID.tabs` file(s).

# SYNOPSIS

```
##=====================================================================
## File Format

TABDUMP ::= HEADER BODY

##=====================================================================
## Header Section

HEADER ::= (TOKRANGE | META | PAGE | BREAK | INDEX)*

TOKRANGE    ::= TOKID_BEGIN TOKID_END
TOKID_BEGIN ::= "%%$DDC:tokid.begin=" TOKID "\n"
TOKID_END   ::= "%%$DDC:tokid.end=" TOKID "\n"

META  ::= "%%$DDC.meta." META_NAME . "=" META_VALUE "\n"

PAGE  ::= "%%$DDC:PAGE=" PAGENO "\n"
BREAK ::= "%%$DDC:BREAK." BREAK_NAME "[" BREAK_ID "]=" TOKID "\n"

INDEX ::= "%%$DDC:index[" INDEX_ID "]=" INDEX_LONG " " INDEX_SHORT "\n"

##=====================================================================
## Body Section

BODY ::= (TOKEN | BREAK | EOS)*

TOKEN ::= INDEX_VAL ("\t" INDEX_VAL)* "\n"
EOS   ::= "\n"

##=====================================================================
## Lexical Content

TOKID       ::= {integer}   /* running counter of indexed token positions */
META_NAME   ::= {string}    /* bibliographic metadata attribute name */
META_VALUE  ::= {string}    /* bibliographic metadata attribute value */
PAGENO      ::= {integer}   /* internal page counter */
BREAK_NAME  ::= {string}    /* short break-names are used */
INDEX_ID    ::= {integer}   /* position of indexed attribute-value in token-lines */
INDEX_LONG  ::= {string}    /* long token-level index name */
INDEX_SHORT ::= {string}    /* short token-level index name */
INDEX_VAL   ::= {string}    /* value of indexed attribute */
```

# DESCRIPTION

## File Format

```
TABDUMP ::= HEADER BODY
```

DDC tab-dump files are comprised of a header section followed by a body section; see [Header / Section](#section) and [Body / Section](#section) for details.

## Header Section

```
HEADER ::= (TOKRANGE | META | BREAK | INDEX)*
```

DDC tab-dump files begin with a simple header section. Header data, like all non-token data begins with the string `%%$DDC` to make it easy to identify. The header section may contain the following information:

### Token Range

```
TOKRANGE    ::= TOKID_BEGIN TOKID_END
TOKID_BEGIN ::= "%%$DDC:tokid.begin=" TOKID "\n"
TOKID_END   ::= "%%$DDC:tokid.end=" TOKID "\n"
```

Reports the range of DDC-internal token-IDs covered by the current document.

### Bibliographic Metadata

```
META  ::= "%%$DDC.meta." META_NAME . "=" META_VALUE "\n"
```

Reports the value of the bibliographic metadata attribute `META_NAME` as `META_VALUE`. Built-in metadata fields are reported with a trailing underscore for `META_NAME`:

```
"%%$DDC.meta.n_=" DOC_ID "\n"
"%%$DDC.meta.file_=" DOC_FILENAME "\n"
"%%$DDC.meta.scan_=" BIBL_SCAN "\n"
"%%$DDC.meta.orig_=" BIBL_ORIG "\n"
"%%$DDC.meta.date_=" BIBL_DATE "\n"
"%%$DDC.meta.page_=" BIBL_PAGE "\n"
```

In streaming TAB-format input mode, the `%%$DDC.meta.file_=` declaration introduces a document boundary (a.k.a. "file break").

### Initial Page

```
PAGE  ::= "%%$DDC:PAGE=" PAGENO "\n"
```

Reports the position of the first internal page-break in the current document.

### Initial Break Positions

```
BREAK ::= "%%$DDC:BREAK." BREAK_NAME "[" BREAK_ID "]" =" TOKID "\n"
```

Reports the position of the first "break" of type `BREAK_NAME` in the current document. `BREAK_NAME` is the short name of some "break collection" declared with the ["HitBorders"](ddc_opt.md#hitborders) option in the project option-file (\*.opt). `BREAK_ID` is the index of the break in the underlying break-vector, or `-1` if the break is the corpus-initial break of its type, and `TOKID` is the token-ID of the first token in the break.

### Token Index Attribute Positions

```
INDEX ::= "%%$DDC:index[" INDEX_ID "]=" INDEX_LONG " " INDEX_SHORT "\n"
```

Reports that the attributes at position `INDEX_ID` in TAB-separated token lines corresponds to the indexed token attribute with long name `INDEX_LONG` and short name `INDEX_SHORT`, as declared by the ["Indices"](ddc_opt.md#indices) option in the project option-file (\*.opt).

## Body Section

```
BODY ::= (TOKEN | PAGE | BREAK | EOS)*
```

The body section consists of zero or more lines representing the indexed document content. Each body line represents either an indexed token (`TOKEN`), a default hit-boundary (`EOS`), or an arbitrary document-internal break (`BREAK`).

### Token

```
TOKEN ::= INDEX_VAL ("\t" INDEX_VAL)* "\n"
```

Tokens are represented as TAB-separated lists of indexed values. Position `INDEX_ID` in the TAB-separated list corresponds to the index attribute declared for `INDEX_ID` in some [token index attribute position](#token-index-attribute-positions) from the [Header Section](#header-section).

### Default Hit-Boundary

```
EOS   ::= "\n"
```

Boundaries of the default break-collection are represented as blank lines.

### Interal Pagebreaks

Document-interal page-breaks are represented as for the [Initial Page](#initial-page) declaration in the [Header Section](#header-section).

### Interal Breaks

Document-interal breaks are represented as for [Initial Break Positions](#initial-break-positions) in the [Header Section](#header-section).

## Lexical Content

```
TOKID       ::= {integer}   /* running counter of indexed token positions */
META_NAME   ::= {string}    /* bibliographic metadata attribute name */
META_VALUE  ::= {string}    /* bibliographic metadata attribute value */
PAGENO      ::= {integer}   /* internal page counter */
BREAK_NAME  ::= {string}    /* short break-names are used */
INDEX_ID    ::= {integer}   /* position of indexed attribute-value in token-lines */
INDEX_LONG  ::= {string}    /* long token-level index name */
INDEX_SHORT ::= {string}    /* short token-level index name */
INDEX_VAL   ::= {string}    /* value of indexed attribute */
```

Integers are represented in decimal notation, dates are represented as `YYYY`, `YYYY-MM`, or `YYYY-MM-DD`, and strings in the [Header Section](#header-section) are printed using [JSON](http://json.org/)-style escape sequences. Token attribute value strings appear as literals.

# EXAMPLE

The following is an example file dump produced by `ddc_dump --full --tabs` for a small toy file:

```
%%$DDC:tokid.begin=0
%%$DDC:tokid.end=17
%%$DDC:meta.n_=0
%%$DDC:meta.file_=test/tiny.xml
%%$DDC:meta.scan_=
%%$DDC:meta.orig_=
%%$DDC:meta.date_=2016-02-25
%%$DDC:meta.page_=-1
%%$DDC:meta.author=Jurish, Bryan
%%$DDC:meta.collection=tiny
%%$DDC:meta.textClass=dummy:test-data
%%$DDC:meta.title=DDC test document
%%$DDC:index[0]=Token w
%%$DDC:index[1]=Pos p
%%$DDC:index[2]=Lemma l
%%$DDC:BREAK.s[-1]=0
%%$DDC:BREAK.p[-1]=0
%%$DDC:BREAK.file[-1]=0
%%$DDC:BREAK.textarea[-1]=0
This	DT	this
is	VBZ	be
a	DT	a
test	NN	test
.	SENT	.

%%$DDC:BREAK.s[0]=5
This	DT	this
is	VBZ	be
only	RB	only
a	DT	a
test	NN	test
.	SENT	.

%%$DDC:BREAK.s[1]=11
%%$DDC:BREAK.p[0]=11
This	DT	this
is	VBZ	be
still	RB	still
a	DT	a
test	NN	test
.	SENT	.
```

# ACKNOWLEDGEMENTS

Alexey Sokirko wrote DDC.

# AUTHOR

Bryan Jurish \<jurish@bbaw.de\> wrote and maintains the `ddc_dump` program.

# SEE ALSO

[ddc\_opt(5)](ddc_opt.md), ddc\_dump(1)
