# Roadmap Backlog Retirement

Date: 2026-09-09
Authority: handoff `docs/handoffs/20260909-151020-retire-roadmap-backlog.md`
Lane: Northstar roadmap-backlog retirement (one-time docs migration, no product change)

## Disposition manifest

The retired surface held one item plus its index. No backlog-item
templates, fixtures, or checker rules existed in this repo.

| Removed item | Current meaning | Canonical destination |
|---|---|---|
| `docs/roadmaps/backlog/001-macos-preview-lane-disposition.md` | Deferred retain-or-remove decision for the diagnostic macOS preview lane (bridge-owned live editor is the supported model; preview stays diagnostic-only) | `docs/triage/2026-09-09-macos-preview-lane-disposition.md` — deferred, non-authoritative candidate preserving constraints, open questions, source refs, promotion condition, and owner |
| `docs/roadmaps/backlog/README.md` | Index + promotion rule for the retired surface | Doctrine absorbed into `docs/triage/README.md` (non-authoritative, promotion only via unambiguous planning authority) and the `docs/roadmaps/README.md` front door |

Disposition reasoning: the item was explicitly deferred, not approved
executable work — its own promotion criteria ("when cleanup outranks
release work") do not supply the scope, generation, dependencies,
ordering, and frontier placement that existing planning authority
would require to author a task, so no `gNN.NNN` task was created.
Durable posture (live-editor-first, preview diagnostic-only) already
lives in contract `007` and `docs/architecture/macos-bridged-ui-options.md`,
so no rule or design promotion was needed. Migration is not approval.

## Files changed

- Added: `docs/triage/README.md` (non-authoritative doctrine + promotion rule)
- Added: `docs/triage/2026-09-09-macos-preview-lane-disposition.md` (sole candidate)
- Edited: `docs/roadmaps/README.md` (no-backlog doctrine; rollover guardrail
  now says closed / paused / superseded / rehomed, deferred candidates to triage)
- Edited: `docs/roadmaps/g02/README.md` (open commitment points at triage)
- Edited: `docs/roadmaps/archive/g01.md` (broken-link fix: `017` live
  decision now points at triage; archive status otherwise unchanged)
- Edited: `docs/contracts/001-working-rules.md` (rollover closeout no
  longer routes through a backlog)
- Edited: `docs/vision/002-strategic-horizons.md` (Current Shape row,
  Runway item, Promotion Map row point at triage)
- Deleted: `docs/roadmaps/backlog/` (both files; directory gone)
- This log + `docs/logs/README.md` recent-evidence entry

## Retained historical exceptions (unchanged)

- `docs/logs/2026-04/17-071000-macos-preview-lane-audit.md` — dated
  evidence describing the creation of the backlog item; left verbatim.
- `docs/logs/2026-09/09-141336-northstar-flattened-task-switchover.md` —
  dated evidence referencing the backlog surface; left verbatim.
- `docs/logs/2026-09/09-142635-northstar-flattened-task-closeout.md` —
  dated closeout stating the disposition "remains in backlog `001`";
  left verbatim, superseded by this retirement.

- `find docs -type d -name backlog -print` returns nothing.
- `grep -rn "roadmaps/backlog" docs` returns only: the immutable queue
  handoff, three dated logs left verbatim as history (`17-071000`,
  `09-141336`, this manifest), the `docs/roadmaps/README.md` doctrine
  line ("there is no roadmap backlog"), and provenance notes in
  `archive/g01.md` and the new triage files. No live surface treats a
  backlog as executable or links to one.
- No live template, agent instruction, or checker requires a roadmap
  backlog (`effigy.toml` catalog, `tasks/`, `docs/`, `demos/`,
  `release/` selectors clean; no backlog-item template ever existed).
- `git diff --check` clean; `effigy qa` + `effigy qa:northstar` (recorded below).
- Approved frontier unchanged: no active task; `g02.007+` still
  unauthored and operator-owned. Triage stays non-authoritative.

## Review

Validation actually run 2026-09-09: `effigy qa` passed (docs
next-action, heading, forbidden checks); `effigy qa:northstar` passed
(same three checks); `git diff --check` clean. Review follow-up fixed
one pre-existing broken relative link in `docs/roadmaps/README.md`
(`../logs/2026-09/09/09-142635-...` has no nested `09/` dir; corrected
to `../logs/2026-09/09-142635-...`) and re-ran `effigy qa` plus
`git diff --check`, both clean.

## Next task

None active. Define `g02.007+` tasks when the operator is ready to spec
`v0.2.0`.
