# Northstar Flattened-Task Switchover

Date: 2026-09-09
Lane: docs-only Northstar migration (worker-PR loop
`d3be99f6-7285-44f6-a8bd-66f8c1ab2bc5`)
Planning: `docs/handoffs/20260909-140500-flattened-task-switchover.md`
against Northstar planning `a30824ba2c0598f997aef0555d4afd9c12006123`
Status: closed after merge at
`ee834e722fe5cffbda54426e7ec9c23c187f829c`

## Outcome

Northstar now has one execution level in this repo. The generation README
owns the roadmap and approved frontier; `docs/roadmaps/gNN/NNN-<slug>.md`
is the sole executable planning unit (`gNN.NNN`). No milestone wrapper or
nested `batch-cards/` hierarchy remains on any active surface.

## Historic compaction

- `g01`: classified **safely closed** (generation index and all front
  doors agree it is complete; tasks 001–015 `complete`, 016
  `superseded`, 017 parked research with its live disposition on
  `docs/roadmaps/backlog/001-macos-preview-lane-disposition.md`). Unique
  rules already live on contracts `002`/`004`/`006`/`007` and the
  architecture surfaces; no open commitments remained. Compacted into
  `docs/roadmaps/archive/g01.md` (`Status: archived`, `Kind: roll-up`,
  non-procedural) and the expanded `g01/` tree deleted (18 files, all
  named in the handoff preservation manifest).
- `g03`: nothing to compact — absorbed back into `g02` on 2026-08-17, no
  tree exists.
- `g02`: **active**, unchanged in standing.

## Active-generation flattening (old → new)

No new task files: nothing executable remained, so there was nothing to
preserve as a separate top-level task. Completed groups collapsed into
`docs/roadmaps/g02/README.md`, which is now the single roadmap and
approved frontier with explicit "no active task" standing:

- `001`–`006` milestone files → `## Shipped outcomes`, each with durable
  homes (releases, known-issues, contracts `006`/`007`, config
  reference) and dated log evidence.
- `batch-cards/001` (Soundcheck managed-settings reader) and `002`
  (isolation drift + glob fix) → collapsed under the `006` outcome;
  surviving semantics already live in contract `006`,
  `docs/setup/config-reference.md`, `src/managed_settings.cpp`, and
  `src/glob_match.h`.
- `007+` (`v0.2.0`) stays unauthored and operator-owned. First task will
  be authored from `docs/roadmaps/templates/task-template.md` when the
  operator specs the lane.

Removed: `g02/001`–`006` files, `g02/batch-cards/` (2 files),
`docs/roadmaps/templates/roadmap-milestone-template.md`,
`docs/specs/templates/batch-card-template.md`.
Added: `docs/roadmaps/templates/task-template.md` (from the installed
Northstar skill template).

## Live-surface rewrites

Generation README owns the frontier; `gNN.NNN` is the planning unit;
"queue task" / "Effigy task" stay distinct from "Northstar task":

- `docs/roadmaps/README.md`, `generation-index.md`, `g02/README.md`
- `docs/roadmaps/backlog/README.md` + backlog `001` (promotion rule and
  "highest-value batch" now read as tasks)
- `docs/contracts/001-working-rules.md` (delivery grammar, intent
  checkpoints, autonomy, generation posture, currentness surfaces now
  naming `g02/README.md`, roadmap impact, next task)
- `docs/contracts/contract-index.md`, `006-process-isolation-policy.md`
  (evidence link now points at the dated log, not the deleted card),
  `002`/`004` provenance wording
- `docs/architecture/README.md`, `macos-bridged-ui-options.md` (refs now
  point at `archive/g01.md`), `product-guardrails.md`
- `docs/specs/README.md` (execution cards live as roadmaps tasks; specs
  card lane and template removed)
- `docs/README.md`, `docs/logs/README.md`, `docs/vision/README.md`,
  `docs/vision/002-strategic-horizons.md`, `docs/contracts/README.md`,
  `docs/policy/internal-writing-style.md`, root `AGENTS.md`

Historical logs, closed handoffs, and dated evidence keep their original
wording and paths; only live authority was rewritten.
One link-target repair inside a 2026-04 evidence log
(`017-iosurface-embedded-editors.md` → `archive/g01.md`, original path
noted inline) was required to keep `effigy docs check links` green.

## Validation

- `git diff --check` clean
- `effigy qa` green (link, vision index, next-action, heading, forbidden,
  path, contains checks all passed)
- `effigy qa:northstar` green
- Lifecycle/currentness inventory repeated and idempotent: only `g02`
  remains expanded; every `g02.NNN` reference resolves to the collapsed
  outcomes or the explicit `007+` absence; no live surface depends on
  `batch-cards/`, milestone wrappers, or dual status.

## Retained exceptions and limits

- `g02.007+` unauthored — operator-owned; normal dispatch has no ready
  task to resume until the operator specs `v0.2.0`.
- Contract `006` next task (shared-process crash-recovery decision) and
  backlog `001` (preview-lane disposition) carry forward unchanged.
- Historical `gNN.NNN` IDs in contracts and logs now resolve via the
  roll-up (`archive/g01.md`) and the collapsed `g02/README.md` outcomes.

## Next task

None active. Define `g02.007+` tasks when the operator is ready to spec
`v0.2.0`.

## Merge and closeout

PR #3 was merged into `main` at
`ee834e722fe5cffbda54426e7ec9c23c187f829c` after the accepted independent
review at
<https://github.com/inflatable-cookie/keepsake/pull/3#issuecomment-5602528248>.
The routine closeout record is
`docs/logs/2026-09/09-142635-northstar-flattened-task-closeout.md`.

No validation failure was deferred from this migration. The retained limits
are planning limits: `g02.007+` remains unauthored and operator-owned, while
the preview-lane disposition and platform-config promotion remain on their
existing active surfaces.
