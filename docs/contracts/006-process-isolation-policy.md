# 006 - Process Isolation Policy

Status: active
Owner: Inflatable Cookie
Updated: 2026-08-17
Depends on: docs/contracts/004-ipc-bridge-protocol.md
Authority owners: Inflatable Cookie
Affects: g01.010 and all subsequent milestones that touch the bridge lifecycle

## Problem

The current bridge model spawns one subprocess per plugin instance. This is
safe but expensive — a 100-instance session means 100 processes with
duplicated memory, per-process IPC overhead, and slow instantiation. Real DAW
workflows need configurable isolation: shared processes for trusted plugins,
individual isolation for problematic ones.

## Contract

### Isolation modes

Keepsake supports three isolation modes, configurable globally and
overridable per-plugin:

| Mode | Behaviour | Used for |
|---|---|---|
| `shared` | All plugins sharing this mode load in a single long-lived bridge process per architecture | Trusted plugins, or sessions where process overhead matters |
| `per-binary` | One bridge process per unique plugin binary; multiple instances of the same plugin share a process | Explicitly configured |
| `per-instance` | One bridge process per plugin instance | Crash-prone plugins, and the shipped global default |

### Default behaviour

- The global default is `per-instance` — every plugin instance gets its own
  bridge process unless overridden.
- The original design default was `shared`. It changed to `per-instance` on
  2026-04-11 (`59e916a`) after a hanging plugin in a shared process froze every
  other instance with it. Strongest isolation by default is the deliberate
  posture for a bridge hosting arbitrary legacy binaries; `shared` remains
  available for users who want the efficiency and accept the blast radius.
- In `shared` mode, separate processes exist per architecture (native, x86_64,
  32-bit) and per format (VST2, VST3, AU) — so there may be up to ~6 shared
  processes in a mixed-format session, but not one per instance.
- Per-plugin overrides in `config.toml` can move any plugin to any of the three
  modes, in either direction.
- If a shared process crashes, all plugins in that process are affected.
  Keepsake reports the crash for each affected instance and may optionally
  restart the shared process.

### Configuration

```toml
[isolation]
# Global default: "shared", "per-binary", or "per-instance"
default = "per-instance"

# Per-plugin overrides
[[isolation.override]]
match = "keepsake.vst2.58667358"  # Serum, by plugin ID
mode = "shared"

[[isolation.override]]
match = "keepsake.vst3.*"         # All VST3 plugins
mode = "per-binary"

[[isolation.override]]
match = "*Kontakt*"               # By display name
mode = "per-instance"

[[isolation.override]]
match = "/Library/Audio/Plug-Ins/VST/*"  # By file path
mode = "shared"
```

### Override matching

A `config.toml` `match` value is compared against three keys, in this order,
and the row applies if any of them matches:

1. the stable exposed CLAP plugin ID (`keepsake.<format>.<uid>`)
2. the plugin's display name
3. the plugin's file path

The first override row that matches wins; later rows are not consulted.

Matching uses one shared glob implementation (`src/glob_match.h`) supporting
`*` (any run of characters, including none) and `?` (exactly one character).
Wildcards cross path separators. A pattern with no wildcards must match a key
exactly. The same implementation backs `[[expose.plugin]]` whitelist matching.

Managed-file rows are the one exception: they match the plugin ID exactly and
are never globbed. See below.

### Managed settings source

`config.toml` is not the only source of these three modes. Soundcheck may write
a managed file that Keepsake reads once at factory startup, governed by
Soundcheck's `002-companion-api-and-keepsake-integration-contract.md`. That file
is not a second isolation model — it supplies the same `shared`, `per-binary`,
and `per-instance` modes this contract defines, and everything below still
governs what those modes mean at runtime.

Keepsake owns discovery, validation, merge, and fallback:

- a valid supported managed file replaces the equivalent `config.toml` isolation
  fields; anything it omits falls through to `config.toml`, then to defaults
- managed overrides key on the stable exposed CLAP plugin ID and match it
  exactly — they are never globbed and never matched against a display name,
  which is what keeps them distinct from `config.toml`'s `match` rows
- a missing, unreadable, malformed, or unsupported-schema file is ignored as a
  whole, with a bounded diagnostic and no partial merge
- no network request, process discovery, or Soundcheck lifecycle check occurs,
  and enumeration or instantiation never fails because central policy is absent

Reload is host restart or plugin rescan. There is no file watcher.

Implementation and proofs:
`docs/roadmaps/g02/batch-cards/001-g02-soundcheck-managed-settings-reader.md`.

### IPC protocol changes

The bridge subprocess becomes a **multi-instance host**. The IPC protocol
gains an instance ID field:

- Every host→bridge message (except SHUTDOWN) carries a `uint32_t instance_id`
  prepended to the existing payload.
- INIT creates a new instance (bridge allocates the ID and returns it in
  the OK response).
- SHUTDOWN with `instance_id = 0` shuts down the entire bridge process.
- SHUTDOWN with a specific `instance_id` removes that instance only.

New message framing:

```
[uint32_t opcode][uint32_t payload_size][uint32_t instance_id][payload...]
```

The instance ID is part of the payload (included in payload_size), not a
separate header field, to maintain backward compatibility with the message
framing.

### Bridge process lifecycle

- **Shared mode**: the factory spawns the shared bridge process on first
  `create_plugin()`. Subsequent instances reuse it. The process stays alive
  until `clap_entry.deinit()`.
- **Per-binary mode**: the factory spawns a bridge process on first
  `create_plugin()` for a given plugin binary. Subsequent instances of the
  same binary reuse it. The process exits when all its instances are
  destroyed.
- **Per-instance mode**: same as current behaviour — one process per
  `create_plugin()`, exits on destroy.

### Shared memory

Each instance still gets its own shared memory segment (different buffer
sizes, channel counts). The segment name includes the instance ID:
`/keepsake-<pid>-<instance_id>`.

### Crash handling in shared mode

If the shared bridge process crashes:
1. All plugin instances hosted in that process are marked crashed.
2. Each instance outputs silence and returns `CLAP_PROCESS_ERROR`.
3. The host is notified via `request_restart` for each affected instance.
4. Optional: the factory may restart the shared process and re-initialize
   surviving instances (deferred — not required for initial implementation).

### Thread safety

With multiple instances in one bridge process, the bridge must handle
interleaved messages. The host must not send messages for different instances
concurrently on the same pipe — messages are serialized. The bridge processes
them sequentially.

For audio processing, the host sends PROCESS for each instance in sequence
(not in parallel). This is acceptable because CLAP hosts typically call
`process()` on the audio thread sequentially across plugins anyway.

## Validation

- Verify that two instances of the same plugin share a bridge process in
  `shared` mode.
- Verify that two different plugins share a bridge process in `shared` mode.
- Verify that `per-instance` override causes a separate process.
- Verify that crashing the shared process marks all hosted instances as
  crashed.
- Verify that config.toml overrides are read and applied correctly.
- Verify that override rows match by plugin ID, display name, and file path,
  and that `*` and `?` globs behave as specified (`isolation-overrides`).
- Verify that a managed-file row matches its plugin ID exactly and never
  matches a display name, a file path, or a glob (`managed-settings`).

## Roadmap Impact

- g01.010: first implementation
- g02.006 batch card 001: Soundcheck managed-settings reader
- g02.006 batch card 002: default-mode correction and override matching fixes
- All subsequent milestones that touch bridge lifecycle or instantiation

## Next Task

Decide whether shared-process crash recovery (the deferred step 4 under crash
handling) is still wanted, or should be written out of this contract.
