# DDC SERVER PROTOCOL

This manual page describes the network protocol used by the DDC (sub)corpus and distributed servers. Since ddc 3.0 it is HTTP: a request is a GET or POST of `/COMMAND` with named parameters (in the URL query string or as an `application/x-www-form-urlencoded` body), and the response body is the result. In the response descriptions, the string "\\x01" represents a literal ASCII byte with decimal value 1 (a.k.a. "SOH"), and " " a literal space character.

# SYNOPSIS

```
##=====================================================================
## Common Messages

GET|POST /version
GET|POST /status
GET|POST /vstatus     [timeout=SECS]
GET|POST /info        [timeout=SECS]
GET|POST /vinfo       [timeout=SECS]
GET|POST /nodes       [depth=DEPTH]
GET|POST /reload      [depth=DEPTH]
GET|POST /clear_cache [depth=DEPTH]

GET|POST /expand_terms pipeline=PIPELINE terms=TERMS [timeout=SECS] [corpus=CORPUS]

GET|POST /get_paradigm word=WORD lang=ILANG [lemmatize_only=0|1]

##=====================================================================
## Branch-Server Messages

GET|POST /run_query query=QUERY [corpus=CORPUS] [format=FORMAT] [start=OFFSET] [limit=LIMIT]
                    [timeout=SECS] [path=PATH] [hint=HINT]

##=====================================================================
## Leaf-Server Messages

GET|POST /get_first_hits query=QUERY timeout=SECS limit=LIMIT [path=PATH] [hint=HINT]
GET|POST /get_hit_strings format=FORMAT start=OFFSET limit=LIMIT
```

Example:

```
curl --data-urlencode 'query=Haus' -d 'format=json&limit=5' http://localhost:50000/run_query
curl --unix-socket /tmp/corpus.sock http://localhost/status
```

# DESCRIPTION

This section contains descriptions of the various requests which may be sent to a DDC server and their expected responses.

## Generic Message Format

A request is an HTTP/1.1 GET or POST request for the path `/COMMAND`; parameters are passed by name, in the URL query string (GET) or in an `application/x-www-form-urlencoded` body (POST). All texts are UTF-8. The response body (`text/plain; charset=utf-8`) is the result described below for each command; ddc-level errors (e.g. a query syntax error) are reported in the response body with HTTP status 200. An unknown command or a missing or malformed parameter gets HTTP status 400, the body is

```
STATUS " 0\n" ERROR
```

A server listens on a tcp address or on a UNIX socket (see [ddc\_cfg(5)](ddc_cfg.md)).

## Sessions

A keep-alive HTTP connection is a session: all its requests are served one after another by the same server worker. A branch server sends `get_first_hits` and then `get_hit_strings` to a daughter in one connection; the daughter keeps the query result between the two requests. The session data are freed after the last request of a session (e.g. after `get_hit_strings`). The number of workers (concurrent sessions) is the `NumThreads` option of [ddc\_server.opt(5)](ddc_server.opt.md).

## Common Messages

This section describes the messages accepted by all DDC servers.

### version

```
/version
```

Returns the version number of the running server as a string, by convention of the form `MAJOR.MINOR.MICRO-PATCHLEVEL` where `MAJOR`, `MINOR`, and `MICRO` are unsigned decimal integers, and `-PATCHLEVEL` is an optional string suffix. This should be the same string reported by **ddc\_daemon** on startup.

Since v2.0.18

### status

```
/status
```

Returns status information on the running server as a JSON object of the form:

```
{
 "name":"server",			//-- server name
 "version":"2.1.9",			//-- server DDC version
 "compat":"2.1.8",			//-- server compatibility version (>= v2.1.9)
 "hostname":"www.dwds.de",		//-- distributed server hostname if available (>= v2.0.35)
 "hostaddr":"127.0.0.1",		//-- distributed server socket hostname, address, or path ("host" for ddc < v2.0.35)
 "port":50011,                         //-- distributed server socket TCP port (if applicable)
 "sockaddr":"inet://127.0.0.1:50011",  //-- URL-style socket address ("inet://ADDR:PORT" or "unix://PATH" >= v2.2.0)
 "started":"2014-02-17T13:49:59Z",	//-- ISO-8601 timestamp of last server start
 "uptime":1392644999,			//-- server instance uptime in seconds
 "nrequests":21,			//-- number of served requests
 "nqueries":18,			//-- number of served queries (>= v2.1.0)
 "nerrors":0,				//-- number of client errors (>= v2.1.0)
 "nslow":0,				//-- number of slow queries (>= v2.1.0)
 "qtavg":0.1383,			//-- average query time over server lifetime (>= v2.1.15) or over last StatsWindow seconds (>= v2.1.1)
 "xtavg":0.0063,			//-- average term-expansion time over server lifetem (>= v2.1.15)
 "qtavgs":[0.1735,0.0685,0.0183],      //-- exponential rolling average query times for 5,15,60 minutes (>= v2.1.15)
 "xtavgs":[0.0103,0.0037,0.0009],      //-- exponential rolling average term-expansion times for 5,15,60 minutes (>= v2.1.15)
 "nworkers":4,                         //-- number of client worker-threads (>= v2.1.0)
 "hitstrings":"parallel",              //-- hit-retrieval mode ("serial" or "parallel", branch only, >= v2.1.12)
 "memkb":68152,			//-- memory resident set size in kb (>= v2.0.49, linux only)
 "vmem":{				//-- virtual memory statistics from /proc/[PID]/status in kb (see proc(5), >= v2.1.8)
         "peak":847100,		//   - VmPeak: peak virtual memory size (address space)
         "size":799100,		//   - VmSize: virtual memory size (address space)
         "hwm":270112,			//   - VmHWM: peak resident set size ("high water mark")
         "rss":143740,			//   - VmRSS: resident set size (=RssAnon+RssFile+RssShmem)
         "data":516540,		//   - VmData: size of data segment
         "stk":132,			//   - VmStk: size of stack segment
         "exe":3280,			//   - VmExe: size of text (program) segment
         "lib":13700,			//   - VmLib: shared library code size
         "swap":0,			//   - VmSwap: swapped-out virtual memory size, not including shmem
         "file":79852,			//   - RssFile: size of resident file mappings (>= v2.1.13)
         "anon":63888			//   - RssAnon: size of resident anonymous memory (>= v2.1.13)
        },
 "navcachesize":512,                   //-- size of navigation hint cache (branch servers only, >= v2.1.9)
 "navcachestep":1000,                  //-- navigation hint cache step-size (branch only, >= v2.1.11)
 "cachesize":42,			//-- size of query cache (leaf servers only)
 "curlcachesize":24,			//-- size of curl cache (leaf servers only)
 "corpora":["corpus1","corpus2",...]	//-- registered subcorpus names (branch servers only)
}
```

Very fast turnaround, since all returned data is known to the server itself, and no subcorpora need to be queried.

Since v2.0.18, optional TIMEOUT parameter since v2.0.47.

### vstatus

```
/vstatus
/vstatus?timeout=TIMEOUT
```

Like the `status` command, but the elements of the returned "corpora" list for a branch server are the JSON objects returned by the `status` command to the associated subcorpus servers, rather than just subcorpus names. If the optional TIMEOUT parameter is specified, it should be an integer value indicating the maximum time (in seconds) to wait for subcorpus responses; default=10.

Since v2.0.18, optional TIMEOUT parameter since v2.0.47.

### info

```
/info
/info?timeout=TIMEOUT
```

Returns information about associated corpora as a JSON object. For a leaf server, the returned object is of the form:

```
{
 //-- basic information
 "name":"corpus1",			//-- subcorpus name
 "version":"2.1.8",			//-- subcorpus server version
 "project":"corpus1",			//-- project basename
 "indexed":"2014-02-17T13:49:56Z",	//-- index timestamp (mtime of PROJECT._con)
 "nfiles":4,				//-- number of successfully indexed files
 "nsources":4,                         //-- number of source files (including empty and erroneous files)
 "nmasked":0,                          //-- number of "masked" (blacklisted) files in PROJECT._masked
 "ntokens":56294,			//-- number of indexed tokens
 //
 //-- global index options (see ddc_opt(5))
 "lang":"German",
 "utf8":1,
 "mmap":1,
 "caseSensitive":1,
 "contextOperator":1,
 "dwdsThesaurus":0,
 "interpDelimiter":"\u001f",
 "tokenDelimiter":"\u001e",
 "allowUnsafeQueries":0,
 "indexPunctuation":1,
 "indexMorphPatterns":0,
 "indexChunks":0,
 //
 //-- index structure: corpus blocks ("periods")
 "periods":[100567,267265,323559],
 //
 //-- index structure: bibliographic metadata
 "bibl":[
{"name":"orig","builtin":1},
{"name":"scan","builtin":1},
{"name":"date","builtin":1},
{"name":"page","builtin":1},
{"name":"author", "visible":1, "size":4},
{"name":"title", "visible":1, "size":4},
//... other bibliographic fields ...
       {"alias":"authors", "ref":"author"}
//... other bibliographic aliases ...
 	],
 //
 //-- index structure: break collections
 "breaks":[
{"shortname":"s", "longname":"sentence", "size":2823},
//... other break collections ...
{"shortname":"textarea", "longname":"textarea", "size":4}
],
 //
 //-- index structure: token-level indices
 "indices":[
{"shortname":"w", "longname":"Token", "visible":1, "bigrams":2, "size":9369},
{"shortname":"l", "longname":"Lemma", "visible":1, "size":5706},
{"shortname":"p", "longname":"Pos", "visible":1, "size":53},
//... other token-level indices ...
{"alias":"CitationForm", "ref":"Lemma"},
//... other token-level aliases ...
],
 //
 //-- query operators: bibliographic expanders ("ExpandBibl" options)
 "xbibl":["xauthor",...]
 //
 //-- query operators: term expanders ("Expand" options)
 "expanders":["Token",...],
 //
 //-- default index names by operator ("DefaultQueryIndex" options)
 "opdefault":{ "_":"Lemma", ... },
 //
 //-- user-supplied information ("ServerInfo" and "ServerInfoFile" options)
 "user":{"foo":"bar","baz":["bonk","boffo"]},
 }
```

For a branch server, the returned object has the form:

```
{
 "name":"server",
 "version":"2.1.9",
 "corpora":[
	{
	 "name":"corpus1",
	 //... information for subcorpus "corpus1" ...
},
       //... information for other subcorpora ...
	{
	 "name":"corpusN",
	 //... information for subcorpus "corpusN" ...
}
 ]
}
```

where each object in the "corpora" array is the associated subcorpus server's response to an "info" request. If the optional TIMEOUT parameter is specified, it should be an integer value indicating the maximum time (in seconds) to wait for subcorpus responses; default=10.

Since v2.0.18, "periods" attribute since v2.0.33, user-supplied info since v2.0.34, optional TIMEOUT parameter since v2.0.47, aliases and "opdefault" attribute since v2.1.5, "mmap" attribute since v2.1.12.

### nodes

```
/nodes
/nodes?depth=DEPTH
```

Returns a JSON array of all subcorpus nodes directly or indirectly accessible from the current server node, or `null` if the current server node is a leaf-server. For branch servers, each element of the returned array is a `/`-separated server-tree `PATH` string as for [HINT](#hint) and suitable for use with the `:` query directive.

### reload

```
/reload
/reload?depth=DEPTH
```

Requests re-loading local (sub)corpus data from disk. If `DEPTH` is present and non-zero, a receiving branch server will send a `reload` message with paramter `DEPTH-1` to any subordinate servers on the user's behalf; a `DEPTH` parameter of -1 requests maximum depth.

Since v2.0.23, DEPTH parameter since v2.0.25.

Apparently **BROKEN** since at least v2.1.0.

### clear\_cache

```
/clear_cache
/clear_cache?depth=DEPTH
```

Request that the receiving server immediately clear any in-memory query cache(s). If `DEPTH` is present and non-zero, a receiving branch server will send a `clear_cache` message with parameter `DEPTH-1` to any subordinate servers on the user's behalf; a `DEPTH` parameter of -1 requests maximum depth.

Since v2.0.23, DEPTH parameter since v2.0.25.

### expand\_terms

```
/expand_terms pipeline=PIPELINE terms=TERMS [timeout=TIMEOUT] [corpus=CORPUS]
```

Requests online term expansion of the terms `TERMS` by the expansion pipeline `PIPELINE`, which must be known to the leaf server chosen for expansion (see [ddc\_opt / Expand](ddc_opt.md#expand)). `TIMEOUT` is a request timeout in seconds (default 10).

For branch servers, if `CORPUS` is specified, it should be the the name of an immediate subcorpus which should be queried to perform the expansion. If unspecified, the first registered subcorpus is queried.

Response data is of the form

```
STATUS " " NTERMS "\n" DATA
```

where `STATUS` is a decimal integer indicating the operation status (0 indicates success). `NTERMS` is the number of expanded terms being returned in the `DATA` portion, and `DATA` is either an error message (just in case `STATUS` is non-zero) or a list of expanded terms separated by TABs, newlines, and/or carriage returns (ASCII 0x09, 0x0a, 0x0d).

Since v2.0.0

### get\_paradigm

```
/get_paradigm word=WORD lang=ILANG [lemmatize_only=ILEMMATIZE]
```

Request morphological analysis of the word `WORD` using legacy built-in language-specific heuristics. `ILEMMATIZE` is a boolean integer; if true, only lemmatization is performed. `ILANG` is an integer indicating the built-in language rule-set to use; it should be a valid `MorphLanguageEnum` value as defined in *${DDC\_SRC}/src/CommonLib/utilit.h* ; currently recognized values are (0:unknown, 1:Russian, 2:English, 3:German, 4:Generic, 5:URL, 6:Digits).

Response is an HTML fragment.

Since v1.x

## Branch-Server Messages

This section describes the messages accepted by DDC "branch" servers, also known as "distributed" or "nonterminal" servers. A branch server is not associated directly with any phyiscal index, but functions as an aggregator for one or more (possibly indirect) subordinate ("leaf") servers.

Branch servers are prototypically used as the top-level instance for processing user queries. Prior to ddc-v2.1.0, only branch servers supported the following messages.

### run\_query

```
/run_query query=QUERY [corpus=CORPUS] [format=FORMAT] [start=OFFSET] [limit=LIMIT] [timeout=TIMEOUT] [path=PATH] [hint=HINT]
```

Top-level user query request.

- CORPUS

  is a vacuous parameter, default "Distributed".

- QUERY

  is the user query in DDC syntax (see [ddc\_query(5)](ddc_query.md) for details).

- FORMAT

  is a string representing the data format to be returned by DDC. Currently, DDC supports the following formats: "JSON", "TABLE", "TEXT", "HTML", or "DOCIDS". Default "text".

- OFFSET

  is the index of the first hit to be retrieved, starting from 0 (zero), default 0.

- LIMIT

  is the maximum number of hits to be retrieved, default 10.

- TIMEOUT

  is the maximum number of seconds to spend processing the query before returning an error response, default 10. Note that since the underlying server(s) only check for timeout conditions once for each iteration through the "corpus period" loop, an expensive query can potentially block the server(s) for much longer than the specified TIMEOUT before such an error response is actually generated and sent to the client.

- PATH

  is the server-tree path of the receiving node (used by branch servers in requests to their daughters).

- HINT

  As of DDC v2.1.9, the optional `HINT` parameter may be passed to specify a lower bound navigation hint for bandwidth and memory optimization of non-count queries. If specified, `HINT` is composed of a nested offset hint (`HINT_OFFSETS`) followed by a single space, followed by a primary sort-key lower bound (`HINT_SORTKEY`). The nested offset hint encodes the logical offset of the requested hint with respect to both the current server node (`OFFSET`) and any descendants (`DTR_OFFSETS`).

  ```
  HINT         ::= HINT_OFFSETS (" " SORTKEY)
  HINT_OFFSETS ::= OFFSET DTR_OFFSETS?
  DTR_OFFSETS  ::= "(" HINT_OFFSETS ("+" HINT_OFFSETS)* ")"
  OFFSET       ::= <unsigned integer>
  SORTKEY      ::= <string>

  PATH         ::= ("/" PATH_NODE)*
  PATH_NODE    ::= <string>
  ```

  The `HINT` parameter is ignored for count-queries.

  For context queries, each `OFFSET` should be the sum of the first level of `DTR_OFFSETS`, and `OFFSET` must be less than or equal to `START`, otherwise an exception may be thrown. If `QUERY` contains a non-trivial sort operation and `HINT` contains a non-empty `SORTKEY` component, only hits equal to or following `SORTKEY` in the requested primary sort order will be returned. If a `SORTKEY` was supplied which is inconsistent with the requested `OFFSET` or `START`, an exception will be thrown.

  The `PATH` parameter contains the labels of any superordinate branch servers(s) in the server-tree for the current request as a "/"-separated list, analogous to UNIX filesystem path notation. An empty `PATH` or indicates that the request was directly initiated by a client (e.g. a user). All other `PATH` parameters must begin with a slash (`/`). If you are writing a client, you probably don't want to specify `PATH` yourself; the DDC-internal code should take care of setting it sensibly.

  Since v2.1.9, older DDC versions do not accept a `HINT` parameter. `PATH` parameter since v2.2.8.

Server response depends on FORMAT. In `JSON` mode, the response data for a traditional context-query is a JSON object of the form:

```
{
  "istatus_" : 0,		  //-- rsp. istatus_internal status code, 0:success
  "nstatus_" : 0,		  //-- network status code, 0:success
  "error_" : null,		  //-- error string, null:no error
  "nhits_" : 31,		  //-- total number of hits
  "dhits_" : "17+4+10=31",	  //-- distribution of hits over subcorpora
  "ndocs_" : 0,		  //-- (?) number of documents containing hits (?)
  "ddocs_" : "0+0+0=0",	  //-- (?) distribution of hit-documents over subcorpora (?)
  "end_" : 10,			  //-- corpus-local offset of next available hit
  "hint_": "10(4(0+4)+1+5) foo", //-- navigation hint for next available hit
  "hits_" : [			  //-- list of hits
    { 							//-- each hit is an object
      "node_" : "/test/corpus1",                       //-- fully qualified subcorpus path (>=v2.2.8)
      "meta_" : {					//-- hit.meta_: bibliographic metadata
           "file_" : "busch_max_1865.xml",		//-- indexed filename
           "indices_" : ["w","p","l"],			//-- indexed token fields for ctx_[1]
           "date_" : "1865",				//-- indexed date (decoded)
           "orig_" : "",
           "page_" : null,
           "scan_" : "",
           //... other indexed metadata fields go here ...
      },
      "ctx_": [				     	//-- hit.ctx_ provides result context
        [ "Ach",",","was","muß","man","oft",... ],	//-- hit.ctx_[0] is left extra-sentential context (strings only <v2.0.38)
        [						//-- hit.ctx_[1] is the hit sentence itself (structured tokens)
          [ 0, "Wie",      "PWAV",    "wie" ],		//-- tok[0] is match-ID, tok[1] is field meta_.indices_[0], etc
   ...
   [ 1, "Max",      "NE",      "Max" ],		//-- tok[0] is nonzero iff token matched a term in the user query
   [ 0, "und",      "KON",     "und" ],
   [ 2, "Moritz",   "NE",      "Moritz" ],	//-- user-supplied match-IDs are reported in tok[0]
   ...
        ],
        [ ...,"heimlich","lustig","machen","." ]	//-- hit.ctx_[2] is right extra-sentential context (strings only <v2.0.38)
      ],
    },
    //... other hits go here ...
  ]
}
```

As of v2.0.34, ddc supports user-supplied match-IDs via the `=ID` query operator. Matched tokens for which an explicit nonzero match-ID was supplied in the query encode that ID as the first element of the returned token-array.

Prior to v2.0.38, ddc returned only raw token strings in the the extra-sentential context arrays hit.ctx\_\[0\] and hit.ctx\_\[2\]. As of v2.0.38, the tokens in these arrays may themselves be array-encoded as for hit.ctx\_\[1\], although sentence boundaries in the extra-sentential context arrays remain unencoded for maximum compatibility. This behavior is disabled by default, but can be enabled by specifying the `--enable-json-deep-context` option to the `configure` script when compiling ddc.

As of v2.0.23, ddc supports aggregate count-queries by means of the `count()` operator. If the requested `QUERY` was such a count-query, the query response is slightly different:

- nhits\_

  indicates the best-guess maximum number of non-zero histogram bins for this query. This number may be smaller than the actual number of non-zero histogram bins if `LIMIT` was less than the total number of non-zero bins in some subcorpus and some non-zero bins occurred in more than one subcorpus: such duplicate bins are merged by the branch server only, but only up to `LIMIT` are retrieved by the branch server for any query, so some uncertainty remains regarding the status of duplicates among the bins beyond `LIMIT`.

- dhits\_

  is of the form "N1+N2+...=NTOTAL~NMAX", where the `Ni` are the number of hits (non-zero histogram bins) in the associated subcorpora, `NTOTAL` is the total number of non-zero histogram bins in any subcorpus (regardless of duplicates), and `NMAX` is the best-guess maximum number of non-zero histogram bins as reported in `nhits_`.

- hits\_

  is not present.

- counts\_

  is a JSON array of the form:

  ```
  [ BIN1, BIN2, ..., BINn ]
  ```

  Each element `BINi` of the `counts_` array represents a single histogram bin as a JSON array

  ```
  [ COUNT, KEY(s)... ]
  ```

  where `COUNT` is the total count for the bin in question and `KEY(s)...` are the key strings as requested in the `QUERY` "#BY"-clause.

Since v1.x, JSON format and error messages since v2.0.0, leaf server support since v2.1.0, navigation hint support since v2.1.9, server-path support since v2.2.8.

## Leaf Server Messages

This section describes the messages accepted by DDC "leaf" servers, also known as "subcorpus", "local", or "terminal" servers. A leaf server is directly associated with exactly one index on the local filesystem, and has no subcorpora itself.

"Leaf-server messages" are requests sent by a branch server to its immediate daughter subcorpora. Prior to v2.1.0, a branch server could only have leaf servers as immediate daughters (no logical corpus embedding). As of v2.1.0, branch servers also support leaf-server requests, thus allowing full "deep" corpus embedding; see [ddc\_cfg(5)](ddc_cfg.md) for details.

### get\_first\_hits

```
/get_first_hits query=QUERY timeout=TIMEOUT limit=LIMIT [path=PATH] [hint=HINT]
```

Requests subcorpus-local evaluation of the user query `QUERY`, returning IDs for up to `LIMIT` hits. `TIMEOUT` is an operation timeout in seconds, and `LIMIT` is the maximum number of hit-IDs to retrieve.

As of DDC v2.1.9, the optional `HINT` parameter may be passed to specify a navigation hint for bandwidth and memory optimization. If specified, [HINT](#hint) takes the form of the [run\_query](#run_query) parameter of the same name, and causes only hits with logical offset greater than or equal to the hint's local `OFFSET` component to be returned. In other words: "get the IDs for hits \[OFFSET,OFFSET+LIMIT), ignoring any with a primary sort key preceding SORTKEY, and try not to take longer than TIMEOUT when doing so".

If an error occurs, the response is of the form:

```
STATUS " 0 0 0 0\n" ERROR
```

where `STATUS` is a non-zero decimal integer error code, and `ERROR` is a text string describing the error.

On success, responses have the form:

```
STATUS " " HITUB " " NHITS " " NDOCS " " SORT " " HITIDS
```

where `STATUS` is a decimal integer status, 0 (zero) for success, `HITUB` should be the index of the last hit returned + 1 (see CConcSession::GetHits(q, \_\_EndHitNo\_\_)), `NHITS` is the total number of hits found (see CConcHolder::m\_AllHitsCount), `NDOCS` is the number of relevant documents found (usually 0 (zero); see CConcHolder::m\_RelevantDocumentCount), `SORT` is a indicates whether and/or how the hits are to be sorted (0: no sort, 1: ascending sort, -1: descending sort), and `HITIDS` is a TAB-separated list of `NHITS` hit-identification triples (see CConcHolder::GetHitIds()), each element of which has the form:

```
INDEX " " ORDERID " " ORDER_STRING
```

where `INDEX` is the query-dependent hit index, `ORDERID` is an integer, and `ORDER_STRING` is a string. Prior to ddc version 2.0.19, `ORDERID` was a global integer primary sort-key for the hit and `ORDER_STRING` was only non-trivially populated if the query contained a context-dependend sort operation such as `#left` or `#right`, and was otherwise assigned the literal string "\<empty\>".

As of v2.0.19, `ORDERID` is the literal string "-0", and `ORDER_STRING` is the (possibly empty) actual sort key for the hit. If `ORDER_STRING` is the literal string "\<empty\>", it is treated as an empty string for compatibility reasons. `ORDER_STRING` may also be a string of the form "#XXXXXXXX" representing a 32-bit integer sort key in hexadecimal notation (msb order, high bit set for non-negative numbers only, no fill bits).

As of v2.0.23, ddc supports aggregate count-queries (by means of the `count()` operator) in addition to traditional "context" queries. If the requested `QUERY` was such a count-query, then `ORDER_STRING` is a "\\x02"-separated list of count-key components, and `INDEX` is the total count of the associated histogram bin.

Since v1.x, error message strings since v2.0.0, count-queries since v2.0.23, branch-server support since v2.1.0, navigation hint support since v2.1.9, path support since v2.2.8.

### get\_hit\_strings

```
/get_hit_strings format=FORMAT start=OFFSET limit=LIMIT
```

Requests verbose hit strings for the current query of the session (the query itself was specified in the previous `get_first_hits` request of the same keep-alive connection, see [Sessions](#sessions)). Hits are to be formatted in `FORMAT`, which should be a format known to DDC. `OFFSET` is the offset of the first hit to return, starting from zero, and `LIMIT` is the maximum number of formatted hits to return.

If an error occurred, the response will be of the form:

```
STATUS "\x01" "\n" ERROR
```

where `STATUS` is a non-zero decimal integer error code (DDCErrorEnum InternalError), and `ERROR` is a text string describing the error.

On success, the response is of the form:

```
STATUS (" " HINT_OFFSETS "\n")? "\x01" HIT_STRINGS "\x01"
```

where `STATUS` is a decimal integer zero ("0") and `HIT_STRINGS` are the formatted hit strings, separated by "\\x01". By convention, each hit is terminated by "\\n" and preceded by "\\x01". For "JSON" format hit strings, the first character of the first hit is a "\[" character, the final character of all non-final hits is a "," character, and the final character of the final hit is a "\]" character, so hits can be parsed as raw JSON data by removing the initial `STATUS` code and all "\\x01" characters from `HIT_STRINGS` before parsing.

As of DDC v2.1.9, the response includes a nested `HINT_OFFSETS` component suitable for retrieval of the next available hit; see [HINT](#hint) for details.

An example response in JSON format is:

```
0 10(4(0+4)+1+5)
\x01[{"meta_":{"file_":"dannhauer_catechismus05_1654.xml",...},"ctx_":[[],[...],[]]},
\x01{"meta_":{"file_":"frentzel_schauplatz_1744.xml",...},"ctx_":[[],[...],[]]},
...
\x01{"meta_":{"file_":"busch_max_1865.xml",...},"ctx_":[[],[...],[]]},
\x01{"meta_":{"file_":"frege_sinn_1892.xml",...},"ctx_":[[],[...],[]]}]
\x01
```

Since v1.x, JSON format and error messages since v2.0.0, branch-server support since v2.1.0, hint offsets in responses since v2.1.9.

## Error Messages

This section describes some common error messages which may be returned by a ddc server.

### std::bad\_alloc

The server attempted to allocate too much memory while processing the query. Either reformulate your query to something less memory-intensive, or provide more memory for the server machine / process.

# ACKNOWLEDGEMENTS

Alexey Sokirko wrote the original DDC.

# AUTHOR

Bryan Jurish \<jurish@bbaw.de\>

# SEE ALSO

[ddc\_opt(5)](ddc_opt.md), [ddc\_query(5)](ddc_query.md), [ddc\_cfg(5)](ddc_cfg.md) [ddc\_server.opt(5)](ddc_server.opt.md) ddc\_daemon(1), ddc\_search(1), ddc\_xml(1)
