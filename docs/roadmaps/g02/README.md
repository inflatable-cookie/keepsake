# G02 — Alpha Release and Post-Alpha Stream

Status: active
Started: 2026-04-12
Reopened: 2026-08-17

This README is the single roadmap and approved frontier for the active
generation. The sole executable planning unit is a Northstar task at
`docs/roadmaps/g02/NNN-<slug>.md`, referenced as `g02.NNN`. There is no
milestone wrapper and no nested `batch-cards/` hierarchy.

## Approved frontier

**No active task.** Tasks `001`–`006` are complete (outcomes collapsed
below with their durable destinations). The next lane, **`007+`**
(`v0.2.0` — Windows + Linux co-primary, VST3 in the push), is
**unauthored and operator-owned**: the operator will return to spec it.
Do not invent that lane or broaden public claims from code existence
alone.

Author the first `007+` task from
`docs/roadmaps/templates/task-template.md` only when the operator specs
the `v0.2.0` lane. See `docs/vision/002-strategic-horizons.md`.

## Shipped outcomes (completed tasks, collapsed 2026-09-09)

- **`001` Alpha scope, claims, and docs reconciliation** — set the
  `v0.1-alpha` support envelope (strongest lane: `macOS + REAPER +
  VST2`), reconciled public docs, published the known-issues baseline.
  Durable homes: `docs/releases/v0.1-alpha-validation-matrix.md`,
  `docs/known-issues-v0.1-alpha.md`.
  Evidence: `docs/logs/2026-04/17-073000-g02-001-alpha-scope-closeout.md`.
- **`002` Release packaging, versioning, install surface** — version and
  changelog, artifact definition, install docs, release-note scaffolding.
  Durable home: `docs/releases/v0.1-alpha.md`.
  Evidence: `docs/logs/2026-04/17-073558-g02-002-release-surface-closeout.md`.
- **`003` Alpha validation matrix and evidence pack** — written matrix
  plus packaged-artifact REAPER smoke (APC, Serum, Khords).
  Durable homes: `docs/releases/v0.1-alpha-validation-matrix.md`,
  `docs/known-issues-v0.1-alpha.md`.
  Evidence: `docs/logs/2026-04/17-074232-g02-003-alpha-evidence-refresh.md`.
- **`004` Publish v0.1-alpha** — tag `v0.1-alpha`, attached artifacts
  with checksums, GitHub release, post-publication smoke.
  Evidence: `docs/logs/2026-04/17-075000-g02-004-release-artifact-proof.md`,
  `docs/logs/2026-04/17-080000-v0.1-alpha-release-checkpoint.md`.
- **`005` macOS UI model and interactive fallback prototype** — the
  bridge-owned live editor is the macOS primary path; embedded preview
  is diagnostic-only. Closed the macOS editor posture.
  Durable homes: `docs/contracts/007-macos-native-editor-and-host-placeholder.md`,
  `docs/architecture/macos-bridged-ui-options.md`.
  Evidence: `docs/logs/2026-04/16-233000-macos-live-editor-fallback-contract.md`,
  `docs/logs/2026-04/16-235500-macos-live-editor-host-batch.md`,
  `docs/logs/2026-04/16-235900-macos-live-editor-posture-closeout.md`.
- **`006` Post-alpha stabilization and claim corrections** (closed early
  2026-08-17; no active user base yet) — Soundcheck managed-settings
  reader (`src/managed_settings.{h,cpp}`, no Soundcheck process
  dependency) and the isolation-config drift plus glob-matching fix
  (shared `src/glob_match.h`, `per-instance` default corrected,
  ID/name/path match keys).
  Durable homes: `docs/contracts/006-process-isolation-policy.md`,
  `docs/setup/config-reference.md`.
  Evidence: `docs/logs/2026-08/17-115406-soundcheck-managed-settings-reader.md`,
  `docs/logs/2026-08/17-121518-isolation-config-drift-and-glob-fix.md`,
  `docs/logs/2026-08/17-154400-g02-006-early-closeout.md`.

The `g03` rollover was premature and absorbed back into `g02`. See
`docs/logs/2026-08/17-153800-g03-absorbed-into-g02.md`.

G02 turns the working bridge into releasable artifacts and honest public
claims, then continues toward operator-owned **`v0.2.0`** without
premature generation rollover. The alpha cut (`001`–`005`) shipped
`v0.1-alpha`; **`006`** closed 2026-08-17 with the two stabilization
fixes above and further triage deferred until real usage warrants it.

**`007+`** tasks are not yet authored. Operator will return to spec
this lane later.

## Release posture

- Primary validated lane: `macOS + REAPER + VST2` (`v0.1-alpha`).
- Windows, Linux, VST3, AU v2, and 32-bit remain experimental until matrix
  evidence moves the envelope.
- Docs drift is a release blocker, not polish.

## Open commitments

- `docs/roadmaps/backlog/001-macos-preview-lane-disposition.md` —
  retain-or-remove decision for the diagnostic preview lane, deferred
  until cleanup outranks release work.
- Platform config schema promotion before `v0.2.0` execution relies on
  it (see the contract index).

## Next task

None active. Define `g02.007+` tasks when the operator is ready to spec
`v0.2.0`.
