# Contract Index

Status: active
Owner: Inflatable Cookie
Updated: 2026-08-17

## Coverage Rules

- Every execution-relevant boundary should map to a contract or an explicit
  pending item below.
- Roadmap milestones must reference the governing contract ids directly.
- If a required boundary has no contract, mark the roadmap blocked and close
  the gap before execution continues.

## Contract Register

| Contract | Boundary | Owning surface | Dependent roadmaps | Status |
|---|---|---|---|---|
| `001-working-rules.md` | Execution grammar and autonomy rules | keepsake repo | all | active |
| `002-clap-factory-interface.md` | Descriptor shape, plugin ID namespace (multi-format), factory lifecycle | keepsake repo | g01.001+ | active |
| `004-ipc-bridge-protocol.md` | Subprocess lifecycle, pipe protocol, shared memory layout, crash handling | keepsake repo | g01.002+ | active |
| `006-process-isolation-policy.md` | Shared/per-binary/per-instance isolation, multi-instance bridge, config overrides, Soundcheck managed-settings merge | keepsake repo | g01.010+, g02.006 card 001 | active |
| `007-macos-native-editor-and-host-placeholder.md` | Passive host-owned Cocoa view plus bridge-owned native legacy editor | keepsake repo | g02.006 | active |
| `008-native-vst2-host-capability-policy.md` | Host-aware same-architecture VST2 descriptor suppression | keepsake repo | post-alpha stabilization | active |

## External Contracts Keepsake Consumes

| Contract | Boundary | Owning surface | Keepsake side | Status |
|---|---|---|---|---|
| `../soundcheck/docs/contracts/002-companion-api-and-keepsake-integration-contract.md` | Soundcheck's managed `integrations/keepsake.toml` schema and fallback rules | soundcheck repo | reader, validation, merge, fallback — `src/managed_settings.cpp` | implemented |

Keepsake owns everything on its own side of that seam. There is no live API,
process discovery, or Soundcheck lifecycle dependency, and Keepsake behaves
identically when Soundcheck is closed or never installed.

## Missing or Pending Contracts

| Boundary | Why needed | Blocking roadmaps | Next action |
|---|---|---|---|
| VeSTige loader ABI contract | Defines which VeSTige entrypoints Keepsake calls and how | release-hardening only if loader boundary drifts again | Author as 003 only if the boundary needs stabilizing during release work |
| Platform config format | config.toml schema and scan path semantics | `v0.2.0` (`g02.007+`) planning | Author when operator specs the next release lane |

## Roadmap Readiness

G01 is complete. `v0.1-alpha` is published. G02 is active (`001`–`006`
complete; `007+` / `v0.2.0` unauthored).

The stabilization stream depends on the current contract set plus one still-thin
boundary:

- `002-clap-factory-interface.md` governs descriptor stability and IDs
- `004-ipc-bridge-protocol.md` governs bridge lifecycle and failure semantics
- `006-process-isolation-policy.md` governs shared/per-instance release
  behavior and Soundcheck managed-settings merge
- `007-macos-native-editor-and-host-placeholder.md` governs macOS editor posture
- `008-native-vst2-host-capability-policy.md` governs host-aware descriptor
  suppression
- platform config format still needs promotion before install/config docs are
  treated as fully settled (see horizon `H1` in
  `docs/vision/002-strategic-horizons.md`)

## Next Task

Promote the platform config schema into its own contract when `g02.007+`
milestones for `v0.2.0` are authored.
