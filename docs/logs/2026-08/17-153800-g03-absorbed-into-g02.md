# 2026-08-17 15:38 — G03 absorbed into G02

Scope: reverse premature generation rollover; keep `g02` as the active stream.

## Why

The `g03` rollover after `v0.1-alpha` was premature — only a handful of
roadmap files existed and the generation guardrail (substantial sequencing
baseline before rollover) was not met. Operator requested merging `g03` back
into `g02` and keeping `g02` open through stabilization and `v0.2.0`.

## Moves

| From (`g03`) | To (`g02`) |
|---|---|
| `001-post-alpha-stabilization-and-claim-corrections.md` | `006-post-alpha-stabilization-and-claim-corrections.md` (`g02.006`) |
| `batch-cards/001-g03-soundcheck-…` | `batch-cards/001-g02-soundcheck-…` |
| `batch-cards/002-g03-isolation-…` | `batch-cards/002-g02-isolation-…` |

- `docs/roadmaps/g03/` removed; `g02/README.md` reopened as **active**
- `docs/roadmaps/generation-index.md` — active generation is `g02`; `g03` row
  marked superseded
- Strategic horizons, vision, contracts, architecture, logs front doors updated
- `v0.2.0` continues as **`g02.007+`** milestones (not `g04`)

## Canonical posture

- Active generation: **`g02`**
- Active milestone: **`g02.006`** (post-alpha stabilization)
- Batch cards 001–002 complete; batch 003 is next triage target
- Planned: **`g02.007+`** for operator-owned `v0.2.0` (Win + Linux + VST3)

## Validation

`effigy qa:northstar` — pass after pointer updates.
