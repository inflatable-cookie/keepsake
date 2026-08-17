# G02 — Alpha Release and Post-Alpha Stream

Status: active
Started: 2026-04-12
Reopened: 2026-08-17

## Milestones

| Milestone | Title | Status |
|---|---|---|
| `001` | [Alpha Scope, Claims, and Docs Reconciliation](001-alpha-scope-claims-and-docs.md) | complete |
| `002` | [Release Packaging, Versioning, and Install Surface](002-release-packaging-versioning-install-surface.md) | complete |
| `003` | [Alpha Validation Matrix and Evidence Pack](003-alpha-validation-matrix-and-evidence.md) | complete |
| `004` | [Publish v0.1-alpha](004-publish-v0.1-alpha.md) | complete |
| `005` | [macOS UI Model and Interactive Fallback Prototype](005-macos-ui-model-and-fallback-prototype.md) | complete |
| `006` | [Post-Alpha Stabilization and Claim Corrections](006-post-alpha-stabilization-and-claim-corrections.md) | complete |
| `007+` | `v0.2.0` (Windows + Linux + VST3) | unauthored |

## Batch Cards (`006`)

| Card | Title | Status |
|---|---|---|
| `001` | [Soundcheck Managed Settings Reader](batch-cards/001-g02-soundcheck-managed-settings-reader.md) | complete |
| `002` | [Isolation Config Drift and Override Matching](batch-cards/002-g02-isolation-config-drift-and-override-matching.md) | complete |

Batch 003 (further triage) was never opened. `006` closed early — no active
user base yet.

## Sequencing Intent

G02 turns the working bridge into releasable artifacts and honest public
claims, then continues toward operator-owned **`v0.2.0`** without premature
generation rollover.

The alpha cut (`001`–`005`) shipped `v0.1-alpha`.

**`006`** closed 2026-08-17 after cards 001–002; post-alpha triage deferred
until real usage warrants it.

**`007+`** — operator-owned **`v0.2.0`** (Windows + Linux co-primary, VST3
in the push) — milestones not yet authored. Operator will return to spec this
lane later.

See `docs/vision/002-strategic-horizons.md`.

## Release Posture

- Primary validated lane: `macOS + REAPER + VST2` (`v0.1-alpha`).
- Windows, Linux, VST3, AU v2, and 32-bit remain experimental until matrix
  evidence moves the envelope.
- Docs drift is a release blocker, not polish.

## Next Task

Define `g02.007+` milestones when the operator is ready to spec `v0.2.0`.
