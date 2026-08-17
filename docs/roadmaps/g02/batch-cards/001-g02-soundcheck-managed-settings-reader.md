# 001 - G02 Soundcheck Managed Settings Reader

Status: complete
Owner: Inflatable Cookie
Updated: 2026-08-17
Milestone refs: `docs/roadmaps/g02/006-post-alpha-stabilization-and-claim-corrections.md`
Governing refs:
  - `docs/contracts/006-process-isolation-policy.md`
  - `docs/contracts/001-working-rules.md`
  - `docs/setup/config-reference.md`
  - `../soundcheck/docs/contracts/002-companion-api-and-keepsake-integration-contract.md`
Auto-start next card: no

## Provenance

This is an operator-requested insert from Soundcheck, not a replacement for
`g02.006`. Soundcheck's producer half (its card 050) is complete and its
contract 002 explicitly leaves the consumer half to Keepsake. `g02.006`
remains the advertised live stabilization lane and is not displaced by this
card.

This card does not revive `docs/roadmaps/g01/016-soundcheck-integration.md`.
That plan described a localhost HTTP API and stays superseded. There is no
live API, no process discovery, and no Soundcheck lifecycle check anywhere in
this scope. The managed file is the whole seam.

## Objective

Read Soundcheck's managed `integrations/keepsake.toml` at factory startup,
merge valid version 1 isolation policy over `config.toml`, and ignore the file
entirely when it is missing, unreadable, malformed, or an unsupported schema.
Keepsake must behave identically to today when Soundcheck is closed or never
installed.

## Scope

- discover `integrations/keepsake.toml` below Soundcheck's platform config root
- parse and validate the version 1 schema from Soundcheck contract 002
- merge the isolation default and `plugin_id` overrides over `config.toml`
- fall back to `config.toml`, then Keepsake defaults, on any rejection
- emit one bounded diagnostic on accept and one on reject
- prove the behaviour with Soundcheck closed and never running
- Do not edit anything in the Soundcheck repository.
- Do not write, migrate, or rewrite the user-owned `config.toml`.
- Do not add file watching; host restart or plugin rescan is the reload boundary.
- Do not read scan paths, exposure, GUI, loader selection, 32-bit helpers, or
  crash recovery from the managed file.
- Do not add a fourth isolation dialect, and do not silently resolve the
  contract 006 / config-reference drift recorded below.

## Managed File

Path, below Soundcheck's platform config root:

| Platform | Path |
|---|---|
| macOS | `~/Library/Application Support/Soundcheck/integrations/keepsake.toml` |
| Windows | `%APPDATA%\Soundcheck\integrations\keepsake.toml` |
| Linux | `$XDG_CONFIG_HOME/soundcheck/integrations/keepsake.toml`, else `~/.config/soundcheck/integrations/keepsake.toml` |

Version 1 schema:

```toml
schema_version = 1

[isolation]
default = "per-instance"

[[isolation.override]]
plugin_id = "keepsake.vst2.41706364"
mode = "per-binary"
```

Allowed modes are `shared`, `per-binary`, and `per-instance`. Overrides key on
Keepsake's stable exposed CLAP plugin ID. Paths, display names, and Soundcheck
row IDs are not interoperability keys.

## Merge And Fallback Rules

1. `schema_version` must be present and exactly `1`. Anything else rejects the
   whole file.
2. A rejected file leaves `config.toml` and Keepsake defaults completely
   untouched.
3. An accepted `[isolation] default` replaces `config.toml`'s
   `isolation.default`.
4. Accepted `[[isolation.override]]` rows are prepended to `config.toml`'s
   override list, so a managed row wins for the plugin IDs it names while
   `config.toml` rows still apply to every plugin the managed file does not
   mention. This is what "missing fields fall through" means at per-plugin
   granularity.
5. Managed override rows match the stable plugin ID **exactly**. They are not
   globbed and are never matched against a plugin's display name. This keeps
   the managed file on contract 002's key and keeps `config.toml`'s existing
   `match` semantics unchanged.
6. Unknown keys and unknown sections inside a valid version 1 file are ignored.
7. A malformed line, a non-mode value, or an override row missing `plugin_id`
   or `mode` makes the file malformed, and malformed means ignored as a whole.
8. The read happens once during `keepsake_factory_init`, outside the audio
   path. No network, no process discovery, no lifecycle check.

## Steps

1. Add `src/managed_settings.{h,cpp}`: Soundcheck config-root resolution,
   managed-file path, a strict version 1 parser, and a merge entry point.
2. Give `IsolationOverride` and `BridgePool::Override` an `exact_plugin_id`
   flag so managed rows can match by exact stable ID while `config.toml` rows
   keep glob matching.
3. Call the reader from `keepsake_factory_init` after `config_load()` and
   before the pool is configured.
4. Emit one bounded accept line and one bounded reject line on stderr. Never
   fail enumeration or instantiation because central policy is unavailable.
5. Add `tools/managed-settings-test.cpp` covering the five contract 002 proofs
   against an isolated config root.
6. Wire the new test into CTest and update `docs/setup/config-reference.md`,
   the contract index, and the roadmap front doors.

## Acceptance Criteria

- a valid supported managed file overrides `config.toml`'s isolation default
- managed overrides beat `config.toml` overrides for the same plugin ID, and
  `config.toml` overrides still apply to plugins the managed file omits
- an absent file leaves behaviour byte-identical to today
- an unreadable or malformed file is ignored as a whole, with a bounded reject
  diagnostic and no partial merge
- `schema_version = 2` and a missing `schema_version` are both rejected
- a managed override matches `keepsake.vst2.<uid>` exactly and does not match
  a plugin whose display name happens to contain the same text
- nothing in the path opens a socket, enumerates processes, or checks whether
  Soundcheck is running

## Evidence Required

- `ctest` run including the new `managed-settings` case
- `effigy qa`
- dated log naming the fixture used and the Soundcheck-closed condition

## Stop Conditions

- stop if honouring the managed file would require changing `config.toml`'s
  own parse or match semantics
- stop if the contract 006 / config-reference drift below turns out to change
  how the merge has to work
- stop if the seam starts to need a live Soundcheck dependency of any kind

## Recorded Drift

Contract 006 and `docs/setup/config-reference.md` disagree with each other and
each is half wrong about the code as it stands today:

| Question | Contract 006 | Config reference | Code today |
|---|---|---|---|
| Global default | `shared` | `per-instance` | `per-instance` (`src/config.h`, `src/bridge_pool.h`) |
| `config.toml` `match` target | plugin ID or name glob | full plugin file path | plugin ID or name glob (`BridgePool::resolve_mode`) |

This card deliberately does not pick a winner. The managed file follows
contract 002 and matches stable IDs exactly, so the reader is correct under
either reading and needs no fourth dialect. Closing the drift is a separate
docs-correction task.

**Closed 2026-08-17** by
[card 002](002-g02-isolation-config-drift-and-override-matching.md). Checking
the code settled both rows without a product judgment call, and turned up that
`match` never compared against the file path at all and that both glob matchers
in the tree were broken.

## Completion Evidence

- `src/managed_settings.{h,cpp}` added: Soundcheck config-root resolution,
  strict version 1 parser, and merge over `KeepsakeConfig`
- `src/config.h`, `src/bridge_pool.{h,cpp}`, `src/factory.cpp` carry the
  exact-plugin-ID override flag through to `resolve_mode`
- `tools/managed-settings-test.cpp` covers valid merge, absent, unreadable,
  malformed, unsupported schema, exact-ID matching, name non-matching, and
  `config.toml` fall-through, against an isolated config root
- proven with no Soundcheck process running and Soundcheck never launched
