# ddc\_server.opt FILE SYNTAX

This manpage describes the syntax of `ddc_server.opt` server option files ("server-opt files") used by the DDC corpus indexing system.

# SYNOPSIS

```
##-------------------------------------------------------------
## Option Processor Directives

#comment
//comment
include "OPTFILE"

##-------------------------------------------------------------
## Logging Options

LogLevel LEVEL
SlowQueryTimeout SECONDS
#StatsWindow SECONDS

##-------------------------------------------------------------
## Client and Parallelization Options

NumThreads NTHREADS
ThreadQueueSize QSIZE
HitStringsParallel BOOL
UnixSocketPerms MODE

##-------------------------------------------------------------
## Navigation Cache Options

NavCacheSize SIZE
NavCacheStep STEP

##-------------------------------------------------------------
## Compatibility Options

VersionCompat VERSION
```

# DESCRIPTION

This section contains descriptions of the various options and flags which may occur in a DDC server opt-file as read by the `ddc_daemon` program versions v2.1.0 and later. Except where otherwise noted, options are supported by DDC versions v2.1.0 and later.

Note that corpus option-files (`CORPUS.opt`) are documented independently; see [ddc\_opt(5)](ddc_opt.md) for details.

## Option Processor Directives

### #comment

### //comment

Comments are lines starting with a literal hash-mark (`#`) or two adjacent slashes (`//`). Such lines are ignored by the option processor.

### include

```
include "OPTFILE"
```

The `include` directive reads in the contents of an external server-opt file at the current position. If OPTFILE is a relative pathname, it is interpreted relative to the directory containing the file currently being parsed.

## Logging Options

The following options control the verbosity of server log messages.

### LogLevel

```
LogLevel LEVEL
```

Aliases: LogLevel, Log, Verbose

Set the default maximum log-level for server messages to *LEVEL*, which should be one of the following:

- silent

  Suppress (almost) all log messages. Aliaes: silent, none, no, off.

- error

  Log only error messages. Aliases: error, errors.

- warning

  Log error and warning messages. Aliases: warn, warning, warnings.

- info

  Log errors, warnings, and basic info messages. Aliases: info, default, weak, light.

- debug

  Log errors, warning, info, and debugging messages. Aliases: debug, medium.

- trace

  Log everything we can. Aliases: trace, heavy.

### SlowQueryTimeout

```
SlowQueryTimeout SECONDS
```

Aliases: SlowQueryTime

Default: 10

Log any requests whose processing requires at least *SECONDS* second(s) as "slow queries". *SECONDS* is parsed as a double-precision float, so non-integral numbers can be specified, but will only be meaningful if DDC was compiled with high-resolution clock support -- in this case, your DDC logs should show nanosecond resolution.

### StatsWindow

```
StatsWindow SECONDS
```

**OBSOLETE**

Aliases: StatWindow, MovingAverageWindow

Default: 600

Size of the time window for tracking moving average statistics, in seconds. Used by DDC \<= v2.1.14 for tracking average query times (`qtavg`) using a simple moving average. As of DDC v2.1.15, average query times are tracked using an efficent exponential moving average with delay intervals (`qtavgs`) of 5, 15, and 60 minutes.

Since v2.1.1, until v2.1.14.

## Client-Thread and Parallelization Options

The following options control the behavior of per-client "worker" threads.

### NumThreads

```
NumThreads NTHREADS
```

Aliases: NumThreads, NThreads, Threads, NumWorkers, NWorkers, Workers

Default: 0

Specifies the number of client worker threads to be used. If *NTHREADS* is zero (the default), no client worker-threads are created and `ddc_daemon` runs in pure serial mode, as for DDC \< v2.1.0. Otherwise, *NTHREADS* worker threads will be initialized on server startup for each server node (branch- or leaf-server), in addition to the "main" server threads themselves (which are always allocated), and `ddc_daemon` will be started in "client-thread" mode. In this mode, the "main" server threads are only responsible for accepting incoming client connections and enqueueing them for later processing by a worker thread, so that up to *NTHREADS* simultaneous client connections can be handled in parallel.

### ThreadQueueSize

```
ThreadQueueSize QSIZE
```

Aliases: ThreadQueueSize, QueueSize, QSize

Default: 256

Specifies the maximum number of pending client connections in the work queue in client-thread mode (see [NumThreads](#numthreads)). If all worker threads are occupied and *QSIZE* additional client connections have been accepted and enqueued for processing, then the main accepting server thread will block until the queue shrinks below *QSIZE* before enqueueing any new client connection -- this basically just pushes the burden of client-queueing beyond *QSIZE* to the TCP stack.

### HitStringsParallel

```
HitStringsParallel BOOL
```

Aliases: HitStringsParallel ParallelHitStrings

Default: false

If specified and true, branch servers created by this process will send [get\_hit\_strings](ddc_protocol.md#get_hit_stings) requests to their immediate daughters in parallel. If the daughters need to fetch hit data from secondary storage (i.e. if you don't have excessive amounts RAM), enabling this option is likely to actually slow things down unless your secondary storage device supports ultra-low-latency random access reads, in which case it might help. The parameter `BOOL` is any string recoginized as a Boolean value; see [ddc\_opt / Boolean Flags and Switches](ddc_opt.md#boolean-flags-and-switches) for details.

Since v2.1.12.

### UnixSocketPerms

```
UnixSocketPerms MODE
```

Aliases: UnixSocketPerms, UnixSocketMode

Default: 0

If specified and nonzero, any UNIX-domain sockets bound by this process will have their access permissions set to `MODE` immediately upon creation. `MODE` should be an octal number representing socket access permissions as for `chmod(1)`. If unspecified or zero, sockets will be created with the default permissions `(0777 & ~umask())`.

Since v2.2.0.

## Navigation Cache Options

The following options control the behavior of the branch server navigation hint cache. Introduced in ddc v2.1.9, the navigation hint cache is an LRU cache used by `CDDCBranchServer` nodes to minimize bandwidth requirements and memory consumption for sequential requests through all hits for a single query string, typically with monotonically increasing offsets and result-sets of constant size.

### NavCacheSize

```
NavCacheSize SIZE
```

Aliases: NavCacheSize, NavCacheCapacity

Set the default branch-server navigation hint cache capacity to `SIZE` (default=1024).

Since v2.1.9.

### NavCacheStep

```
NavCacheStep STEP
```

Aliases: NavCacheStep, NavCacheStepSize

Set the minimum offset increment for branch server navigation cache updates to `STEP` (default=1000). If `STEP` is zero, a branch server's navigation hint cache will be updated for each page of hits retrieved. Otherwise, the cache will only be updated with a new entry if the difference between the candidate entry's offset and the maximum offset already cached for the associated query is greater than or equal to `STEP`. Setting `STEP` to a value greater than the default initial page size (usually 10) should serve to minimize cache turnover and increase the life expectancy of "real" hit-paging operations without the heavy performance penalties of ddc \<= v2.1.8.

Since v2.1.11.

## Compatibility Options

The following compatibility options are supported:

### VersionCompat

```
VersionCompat VERSION
```

Aliases: VersionCompat, CompatVersion, Compatibility, Compat

Simulate the behavior of a server running DDC version `VERSION`. In particular, a branch server with running in version `VERSION` compatibility mode should **NOT** send any requests to its immediate daughter corpora which cannot be handled by DDC version `VERSION`. By default, `VERSION` is the version of DDC used by the running server process.

Useful values:

- `VERSION` \<= 2.1.8

  Prevents server from sending navigation hints in generated `get_first_hits` requests, or returning them in `get_hit_strings` responses. See [ddc\_protocol(5)](ddc_protocol.md) for details.

Since v2.1.9.

# ACKNOWLEDGEMENTS

Alexey Sokirko wrote the original DDC.

# AUTHOR

Bryan Jurish \<jurish@bbaw.de\>

# SEE ALSO

ddc\_opt(5), ddc\_protocol(5), ddc\_daemon(1)
