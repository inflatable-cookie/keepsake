# G02.006 — Post-Alpha Stabilization and Claim Corrections

Status: complete
Owner: Inflatable Cookie
Updated: 2026-08-17
Closed: 2026-08-17
Governing refs:
  - docs/contracts/001-working-rules.md
  - docs/contracts/007-macos-native-editor-and-host-placeholder.md
  - docs/releases/v0.1-alpha.md
  - docs/releases/v0.1-alpha-validation-matrix.md
  - docs/known-issues-v0.1-alpha.md
Auto-continuation: allowed within g02

## Scope

Handle the first real post-release wave after `v0.1-alpha`.

This milestone exists to absorb what the public release exposes:

- bug reports from real installs and hosts
- claim corrections if any release wording is too broad or too soft
- installer friction and runtime regressions on the published artifacts
- evidence refresh if the strongest claimed lane shifts materially

This is a stabilization lane, not a quiet feature stream. It continues the
`g02` release generation rather than a separate generation — the `g03`
rollover was premature and has been absorbed back into `g02`.

## Steps

### 1. Triage release-window reports

Capture the first meaningful reports against the published alpha:

- install failures
- scan failures
- GUI/runtime regressions
- host-specific lockups
- config/documentation confusion

Acceptance:
- real incoming issues are grouped into clear classes
- each class has an owner path: fix now, document now, or defer

### 2. Correct claims quickly

If public wording outruns evidence, narrow it immediately instead of waiting
for a larger docs sweep.

Acceptance:
- README, release notes, matrix, and known issues stay aligned to reality

### 3. Land the first stabilization fixes

Fix the highest-value release-window regressions in meaningful batches.

Bias:
- primary supported lane first
- installer/runtime breakage before polish
- narrow, proven fixes over speculative churn

Acceptance:
- at least one meaningful post-release stabilization batch lands with evidence

Opening batch:

- remove the failed Soundcheck companion receiver/helper experiment
- restore one host-independent macOS UI model
- attach a non-rendering Cocoa placeholder with a native-editor reopen action
  to the host parent
- keep all real interaction in the bridge-owned native plugin window
- leave screenshots to the inspection host's generic native-window capture path

### 4. Refresh evidence where the release surface moved

If a stabilization fix changes the actual supported posture, refresh the
validation surface behind that claim.

Acceptance:
- release-window evidence remains current enough to defend the public posture

## Evidence Requirements

- dated log for each meaningful stabilization batch
- release doc / known-issues / matrix diffs where claims changed
- commands and hosts used for any refreshed evidence

## Stop Conditions

- stop if a reported problem reveals a missing contract or architecture gap
- stop if the intended fix is really a new generation-scale feature

## Closeout (2026-08-17)

Operator closed this milestone early. No meaningful post-alpha user report
cluster has arrived — Keepsake has no active user base yet. Batch cards
001–002 (Soundcheck managed settings, isolation drift/glob fix) shipped useful
fixes; further stabilization triage (batch 003) is deferred until real usage
or a concrete report warrants it.

`g02.007+` (`v0.2.0` — Windows, Linux, VST3) remains unauthored until the
operator returns to spec that lane.

## Next Task

None — milestone closed. Resume via `g02.007+` when `v0.2.0` is specced.
