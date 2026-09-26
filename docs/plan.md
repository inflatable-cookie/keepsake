# Plan

Updated: 2026-09-26

## Now

1. **`v0.2.0`: Windows x64 and Linux x64 as co-primary platforms, with VST3 in
   the supported envelope** (lane `v0.2.0`) — the operator decision of
   2026-08-17. Needs the platform config schema promoted to a contract,
   refreshed Windows/Linux and VST3 validation, and per-platform install
   artifacts. A release ships only when the matrix defends Windows, Linux and
   VST3 together, or a narrowed envelope is recorded. The VST3 GPLv3 subprocess
   boundary must be accepted explicitly before any public VST3 claim. Open
   questions: Q-003, Q-004. See
   [vision](knowledge/vision.md),
   [architecture](knowledge/architecture/system.md) and the
   [Windows editor architecture](knowledge/architecture/windows-editor.md).

## Next

- **Promote the platform config schema to a contract** — `config.toml` and its
  scan-path semantics are implemented but only described in the
  [config reference](setup/config-reference.md) and the
  [isolation policy](knowledge/contracts/process-isolation-policy.md). Do this
  before `v0.2.0` work relies on it.

## Not now

- **Diagnostic macOS IOSurface preview lane** — retain or remove; see Q-001
  and the [triage note](triage/2026-09-09-macos-preview-lane-disposition.md).
- **Shared-process crash recovery** — deferred in the
  [isolation contract](knowledge/contracts/process-isolation-policy.md); see
  Q-002.
- **AU v2 and public 32-bit claims** — both have code and partial evidence,
  neither is in the `v0.2.0` operator scope unless the matrix forces a
  deferral. See Q-004.
