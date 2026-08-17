# Soundcheck managed settings reader

Date: 2026-08-17
Posture: strict-ready

## Changed

- Compiled `docs/roadmaps/g02/batch-cards/001-g02-soundcheck-managed-settings-reader.md`
  as a Keepsake-owned card for the consumer half of Soundcheck's contract 002.
- Added `src/managed_settings.{h,cpp}`: Soundcheck config-root resolution,
  managed-file discovery, a strict version 1 parser, and merge over
  `KeepsakeConfig`.
- Added an `exact_plugin_id` flag to `IsolationOverride` and
  `BridgePool::Override` so managed rows match the stable exposed CLAP plugin ID
  exactly while `config.toml` rows keep their existing glob semantics.
- Called the reader once from `keepsake_factory_init`, after `config_load()` and
  before the pool is configured.
- Added `tools/managed-settings-test.cpp` and the `managed-settings` CTest case.
- Documented the seam in `docs/setup/config-reference.md`, contract 006, and the
  contract index.

## What the seam is and is not

The managed file is the whole connection. Keepsake does not open a socket,
enumerate processes, or check whether Soundcheck is running, and Soundcheck does
not touch `config.toml`. This did not revive `g01.016`; that localhost-API plan
stays superseded.

Merge rules as implemented:

- `schema_version` must be present and exactly `1`
- a valid managed `default` replaces `config.toml`'s isolation default
- managed override rows are prepended to `config.toml`'s override list, so a
  managed row wins for the plugin IDs it names while `config.toml` rows still
  cover every plugin the managed file omits
- managed rows match the stable plugin ID exactly — never globbed, never matched
  against a display name
- missing, unreadable, malformed, and unsupported-schema files are ignored as a
  whole with one bounded diagnostic; unknown keys in a valid file are ignored

## Validation

- `cmake --preset default`
- `cmake --build build --target managed-settings-test keepsake keepsake-bridge`
- `ctest --output-on-failure` — 5/5 passed, including the new `managed-settings`
  case covering all five contract 002 proofs: valid-file merge precedence,
  absent and invalid-file fallback, unsupported-schema fallback, stable-ID
  override matching, and no Soundcheck process dependency
- factory-startup proof via `clap-scan` against an isolated config root:
  - valid file → `keepsake: applied soundcheck settings (default=per-binary, 1 overrides) from '<path>'`
  - `schema_version = 2` → `keepsake: ignoring soundcheck settings at '<path>' (unsupported schema_version 2); using config.toml`
  - absent file → no Soundcheck output at all, behaviour unchanged
- `effigy qa`

Soundcheck was not running for any of this and was never launched (`pgrep -il
soundcheck` empty). The real install on this machine has no
`integrations/keepsake.toml`, so the shipped default path is the absent-file
path, and it is a no-op.

## Risks retained

- Contract 006 and `docs/setup/config-reference.md` still disagree on the global
  default (`shared` vs `per-instance`) and on what `config.toml`'s `match`
  compares against (ID/name glob vs file path). The code says `per-instance` and
  ID/name glob. The reader deliberately does not resolve this — managed rows
  match stable IDs exactly, so it is correct under either reading. The drift is
  now recorded in 006 and in card 001, unresolved.
- `BridgePool::glob_match` is a documented simplification that returns true for
  any text when a pattern both starts and ends with `*` (`*Kontakt*` matches
  everything). Pre-existing, untouched by this batch, and it does not affect
  managed rows because they never glob. It does affect `config.toml` rows.
- The managed-file parser is strict by design: multi-line arrays, inline tables,
  and unrecognized string escapes read as malformed and cause the file to be
  ignored. Safe fallback, but it is stricter than full TOML.
- Version 1 has no file watcher. Reload is host restart or plugin rescan.

## Sequencing note

This was an operator-requested insert from Soundcheck, not a silent replacement
of `g02.006`. Post-alpha stabilization remains the live lane and was not
displaced. Soundcheck's front doors already said the reader was downstream; that
claim has now changed, but no Soundcheck file was edited in this batch.

## Next task

Close the isolation-config drift as its own docs-correction pass: decide whether
contract 006 or `docs/setup/config-reference.md` is right about the global
default and about what `config.toml`'s `match` compares against, then make both
match the shipped code. Update Soundcheck's front doors to say the reader landed
only after that, and only if the operator wants the cross-repo claim refreshed.
