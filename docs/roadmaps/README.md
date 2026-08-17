# Roadmaps

Roadmaps are executable milestone plans derived from vision, architecture, and
contracts.

## Active Generation

- `g02` — alpha through `v0.1-alpha`; `v0.2.0` planned as `007+`

## Generation Index

- [`generation-index.md`](generation-index.md)
- Long-horizon runway: [`../vision/002-strategic-horizons.md`](../vision/002-strategic-horizons.md)

## Layout

- `gNN/batch-cards/` optional per-generation execution cards
- `g01/` — first generation milestones
- `g02/` — alpha release, stabilization, and `v0.2.0` stream
- `generation-index.md` — active generation and rollover history
- `backlog/` — deferred items with promotion criteria
- `templates/roadmap-milestone-template.md` — milestone starter contract

## Status

**g01 sequencing intent met.** The core bridge, GUI, scan robustness, CI, and
codebase-health lanes are complete.

**g02 is active.** Milestones `001`–`006` complete. **`007+`** (`v0.2.0`) is
unauthored — operator will return to spec Windows + Linux + VST3 later.

The brief `g03` rollover was premature and absorbed back into `g02`. See
`docs/logs/2026-08/17-153800-g03-absorbed-into-g02.md`. `g02.006` closed early
2026-08-17 — see `docs/logs/2026-08/17-154400-g02-006-early-closeout.md`.

## Batch and Logging Rule

- Execute milestones in meaningful batches.
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

Define `g02.007+` milestones when ready to spec `v0.2.0`.
