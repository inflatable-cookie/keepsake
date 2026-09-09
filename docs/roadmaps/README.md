# Roadmaps

Roadmaps are executable Northstar tasks derived from vision, architecture,
and contracts.

## Active Generation

- `g02` — alpha through `v0.1-alpha`; `v0.2.0` planned as `007+`

## Generation Index

- [`generation-index.md`](generation-index.md)
- Long-horizon runway: [`../vision/002-strategic-horizons.md`](../vision/002-strategic-horizons.md)

## Layout

- `gNN/NNN-<slug>.md` — the sole executable planning unit, one top-level
  Northstar task per `gNN.NNN`
- `g02/` — alpha release, stabilization, and `v0.2.0` stream
- `archive/gNN.md` — non-procedural roll-ups for compacted generations
- `generation-index.md` — active generation and rollover history
- `backlog/` — deferred items with promotion criteria
- `templates/task-template.md` — task starter contract

## Status

**g01 sequencing intent met and compacted.** The core bridge, GUI, scan
robustness, CI, and codebase-health lanes are complete — see
[`archive/g01.md`](archive/g01.md).

**g02 is active.** Tasks `001`–`006` complete (outcomes collapsed into
[`g02/README.md`](g02/README.md)). **`007+`** (`v0.2.0`) is unauthored —
operator will return to spec Windows + Linux + VST3 later.

The flattened-task switchover is closed after merged PR #3; see
[`docs/logs/2026-09/09-142635-northstar-flattened-task-closeout.md`](../logs/2026-09/09/09-142635-northstar-flattened-task-closeout.md).

The brief `g03` rollover was premature and absorbed back into `g02`. See
`docs/logs/2026-08/17-153800-g03-absorbed-into-g02.md`. `g02.006` closed early
2026-08-17 — see `docs/logs/2026-08/17-154400-g02-006-early-closeout.md`.

## Task and Logging Rule

- Execute tasks in meaningful batches.
- Create logs per completed batch or update cycle, not per individual task.
- Stop execution when a batch reveals a missing contract, missing repo
  authority, or other planning gap.

## Rollover guardrail

Do not open `gNN+1` while the current generation still has live roadmap files or stale strict-lane debris in the active specs tree.

Before rollover:

- every roadmap in the closing generation must be explicitly closed, paused, superseded, or moved to backlog
- the roadmap front doors must agree that the old generation is no longer the live queue
- `docs/specs/` must be purged so only live or near-live planning artifacts remain in the active tree

## Next Task

None active. Define `g02.007+` tasks when ready to spec `v0.2.0`.
