# DDC \*.cfg FILE SYNTAX

This manpage describes the syntax of the `ddc_local_corpora.cfg` and `ddc_server.cfg` files ("cfg-files") used by the DDC corpus indexing system.

# DESCRIPTION

Local cfg-files (`ddc_local_corpora.cfg`) define the terminal ("leaf") nodes of a DDC server dataflow tree which are to be handled by a single server process. Server cfg-files (`ddc_server.cfg`) associate each local leaf node with at least one non-terminal ("branch") node, and may also incorporate external leaf or branch nodes as "opaque" nodes, as well as define "internal" branch nodes for the server dataflow tree. Prior to DDC v2.1.0, at most one branch-node could be declared in `ddc_server.cfg`, and all leaf nodes had to be explicitly declared, since branch nodes could not be queried as opaque leaf-like nodes.

All DDC cfg-files share a common basic format. Files are line-based, containing one server-node record per line. Blank lines (containing only whitespace) and comments (lines beginning with a hash-mark (`#`) or double-slash (`//`)) are ignored. Each content line should contain 3 or 4 fields separated by whitespace:

```
LABEL  ADDR  PORT  PATH?
```

## Label

The first field specifies a symbolic *LABEL* for the server node. Node labels should be unique within the scope of a single cfg-file.

For server-config files `ddc_server.cfg`, if *LABEL* is either the string `server` or begins with the prefix `server:`, the corresponding server-node will be created as a branch-node (a `CDDCBranchServer` object representing a non-terminal node in the server dataflow tree). Otherwise, the node is treated as an opaque (terminal) leaf-node.

## Addr

The second field specifies the address *ADDR* to be bound by a branch-node and/or that to be queried for a leaf-node. As of v2.2.0, *ADDR* may indicate either an internet (TCP) address or a UNIX socket path. The following notations are supported:

```
inet://IPADDR  # INET TCP socket on IPADDR (aliases: "inet:IPADDR", "tcp:IPADDR")
unix://PATH    # UNIX socket at local PATH (aliases: "unix:PATH")
/PATH          # UNIX socket on local absolute /PATH
IPADDR         # default: INET TCP socket on IPADDR
```

If the *IPADDR* for an internet-domain (INET) address is the special string `0.0.0.0`, all available interfaces will be bound for a branch-node, while the loopback interface (`127.0.0.1`) will be queried.

UNIX socket support since v2.2.0.

## Port

The third field specifies the TCP port-number *PORT* to be bound by a branch-node and/or to be queried for a leaf-node. It has no protocol-relevant meaning for [UNIX-domain sockets](#addr), but may be used to initialize a subcorpus-specific random seed, and will be reported in [status responses](ddc_proto.md#status) responses.

## Path

The meaning of the fourth and final field *PATH* differs between `ddc_local_corpora.cfg` and `ddc_server.cfg`.

For `ddc_local_corpora.cfg`, *PATH* is required, and specifies the local path to the associated DDC project file (`*.con`), relative to the DDC runtime root directory as stored in the environment variable `$DDC3`.

For `ddc_server.cfg`, *PATH* is optional. If non-empty, it specifies the [LABEL](#label) of the node's parent in the dataflow tree, which should be a branch node. If empty, the most recently declared branch-node is used as the parent.

# EXAMPLES

## Example 1: Flat Dataflow

- ddc\_local\_corpora.cfg

  ```
  sub1  0.0.0.0  50001  index/sub1/sub1.con
  sub2  0.0.0.0  50002  index/sub2/sub2.con
  sub3  0.0.0.0  50003  index/sub3/sub3.con
  sub4  0.0.0.0  50004  index/sub4/sub4.con
  ```

- ddc\_server.cfg

  ```
  server 0.0.0.0   50000
  sub1   127.0.0.1 50001
  sub2   127.0.0.1 50002
  sub3   127.0.0.1 50003
  sub4   127.0.0.1 50004
  ```

This example defines a basic "flat" dataflow tree with exactly 1 branch node ("server"), analagous to the dataflow trees supported by DDC \< v2.1.0.

```
       server
 _________|_________
 |     |     |     |
sub1  sub2  sub3  sub4
```

## Example 2: External Leaf Nodes / Meta-Server

- ddc\_local\_corpora.cfg

  (empty)

- ddc\_server.cfg

  ```
  server 0.0.0.0   60000
  ext1   127.0.0.1 60001
  ext2   127.0.0.1 60002
  ext3   127.0.0.1 60003
  ext4   127.0.0.1 60004
  ```

This example defines a basic "flat" dataflow tree with exactly 1 branch node as above, but without any local leaf nodes (sometimes called a "meta-server"). All leaf nodes are assumed to be handled by external processes.

```
            server
  ____________|____________
  |       |       |       |
(ext1)  (ext2)  (ext3)  (ext4)
```

## Example 3: Internal Branch Nodes

- ddc\_local\_corpora.cfg

  ```
  sub1  0.0.0.0  50001  index/sub1/sub1.con
  sub2  0.0.0.0  50002  index/sub2/sub2.con
  sub3  0.0.0.0  50003  index/sub3/sub3.con
  sub4  0.0.0.0  50004  index/sub4/sub4.con
  ```

- ddc\_server.cfg

  ```
  server:root 0.0.0.0   50000

  server:int1 0.0.0.0   50010 server:root
  sub1        127.0.0.1 50001 server:int1
  sub2        127.0.0.1 50002 server:int1

  server:int2 0.0.0.0   50020 server:root
  sub3        127.0.0.1 50003 server:int2
  sub4        127.0.0.1 50004 server:int2
  ```

- ddc\_server.cfg (alternate)

  Server declarations for leaf-nodes can be omitted if they are declared within the scope of the associated branch-nodes:

  ```
  server:root 0.0.0.0   50000

  server:int1 0.0.0.0   50010 server:root
  sub1        127.0.0.1 50001
  sub2        127.0.0.1 50002

  server:int2 0.0.0.0   50020 server:root
  sub3        127.0.0.1 50003
  sub4        127.0.0.1 50004
  ```

This example defines a binary-branching dataflow tree of depth 2, containing 2 internal branch nodes ("server:int1" and "server:int2") in addition to the root node ("server:root"). Requires ddc \>= v2.1.0.

```
       server:root
     _______|_______
     |             |
server:int1    server:int2
 ___|___         ___|___
 |     |         |     |
sub1  sub2      sub3  sub4
```

## Example 4: INET + UNIX sockets

- ddc\_local\_corpora.cfg

  ```
  sub1  unix:/tmp/ddc/sub1.sock - index/sub1/sub1.con
  sub2  unix:/tmp/ddc/sub2.sock - index/sub2/sub2.con
  ```

- ddc\_server.cfg

  ```
  server:inet 0.0.0.0                   50000

  server:unix unix:/tmp/ddc/server.sock
  sub1        unix:/tmp/ddc/sub1.sock
  sub2        unix:/tmp/ddc/sub2.sock
  ```

This example uses UNIX-domain sockets to communicate with local physical leaf corpora `sub1` and `sub2`. The logical corpus itself can be accessed from the local host via the UNIX-domain socket `/tmp/ddc/server.sock`, and from remote hosts by a "pass-through" server node listening on port `50000`.

```
server:root @ inet://0.0.0.0:5000
     |
server:unix @ unix:///tmp/ddc/server.sock
  ___|___
  |     |
 sub1  sub2
```

# ACKNOWLEDGEMENTS

Alexey Sokirko wrote the original DDC.

# AUTHOR

Bryan Jurish \<jurish@bbaw.de\>

# SEE ALSO

ddc\_server.opt(5), ddc\_daemon(1)
