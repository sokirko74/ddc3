# DDC INPUT FORMAT

This manual page describes the corpus files that `ddc_index` reads: the list of files, the encoding, the
markup of XML documents and the characters that must not occur in a text. The options are described in
[ddc\_opt(5)](ddc_opt.md), the tab-separated format of `TabFormat_Index` in [ddc\_tabs(5)](ddc_tabs.md).

## Corpus files

A corpus project `CORPUS.con` is a list of corpus files, one path per line (absolute, or relative to the
directory in which `ddc_index` is run); the options are in `CORPUS.opt`. The kind of a file is given by its name:

| Name | Read as |
|---|---|
| `*.xml` | an XML document (see below) |
| `*.htm`, `*.html`, `*.shtml` | HTML: the tags are removed, the text is indexed |
| `*.tar` | a tar archive; each member is a document of its own |
| `-` | the standard input (`TabFormat_Index` only) |
| anything else | plain text |
| `*.gz` | any of the above (but `.tar`) compressed with gzip, e.g. `book.xml.gz`; `.tar.gz` is rejected |

With `IndexType TabFormat_Index` each file holds one or more documents in the format of
[ddc\_tabs(5)](ddc_tabs.md).

## Encoding

All texts are UTF-8. A file that is not valid UTF-8 is rejected. The same holds for queries and terms
(`ddc_simple`, `ddc_console`, `ddc_qparse`, the servers, `ddc_expand`), and all output is UTF-8.

For the languages with morphology (Russian, English, German) a character that the morphology of the
language does not know (e.g. "ſ" in historical German) cannot be lemmatized; index such texts with the
language `Generic` (no morphology, the UTF-8 text is kept as is).

## XML documents

The elements to index are selected by XPath in the opt-file:

    TextArea body /TEI.2/text/body
    Bibl string 1 author /TEI.2/teiHeader/fileDesc/sourceDesc[@id="orig"]/author

- [TextArea](ddc_opt.md#textarea) selects the text areas; each document must contain all of them, a
  document without one is an error (see [Errors](#errors)).
- [Bibl](ddc_opt.md#bibl) selects the bibliographic fields; with
  [OutputBibliographyOfHits](ddc_opt.md#outputbibliographyofhits) they are returned with each hit.
- `<pb n="13"/>` inside a text area is a page break; the page number should be a decimal number,
  any other value (e.g. "iv") gives a page break with an unknown number.
- `<p>` ends a paragraph (with [UseParagraphTagToDivide](ddc_opt.md#useparagraphtagtodivide)).
- Other elements are transparent: their text is indexed, the tags are ignored. Comments and processing
  instructions are skipped.

The text of a document is plain text: an escaped tag such as `&lt;textarea&gt;` (e.g. in a book about
HTML) is indexed as the tokens of the text, it is not markup.

## Control characters

DDC uses the ASCII control characters 0x01–0x08 itself, therefore they are replaced by spaces in the texts
of XML documents (XML 1.0 forbids them anyway; a character reference such as `&#x2;` is replaced too):

| Character | Use |
|---|---|
| `\x02` | the end of a text area, inserted by DDC into the text for the graphematics |
| `\x03` | a page break followed by the page number (`\x03` "13"), inserted by DDC from `<pb n="13"/>` |

and, not in the index input, but in the server protocol and query results:

| Character | Use |
|---|---|
| `\x01` | the separator of the hits in `get_hit_strings` (see [ddc\_protocol(5)](ddc_protocol.md)) |
| `\x02` | the separator of the keys of a count query and of the fields of the `table` format |

The delimiters of the fields of a token in the output are set by
[InterpDelimiter](ddc_opt.md#interpdelimiter) and [TokenDelimiter](ddc_opt.md#tokendelimiter) (DWDS used
`\x1f` and `\x1e`).

## Errors

By default the first document that cannot be indexed (bad XML or UTF-8, a missing text area, a text
larger than 256 MB) stops `ddc_index`. With [ResumeOnIndexErrors](ddc_opt.md#resumeonindexerrors) such
a document is skipped with a warning and listed in `CORPUS._error_log`.
