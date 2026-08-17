# Roadmap Generation Index

Status: active
Updated: 2026-08-17

## Active generation

- `g02`

## Generation log

| Generation | Started | Reason | Notes |
|---|---|---|---|
| `g01` | 2026-04-10 | Initial roadmap sequence | Baseline generation for the initial build, CLAP factory, VeSTige loader, and proof-of-concept work |
| `g02` | 2026-04-12 | Alpha release stream | g01 proved the bridge architecture and CI lane. g02 is the release-hardening generation through `v0.1-alpha`, post-alpha stabilization, and the planned `v0.2.0` envelope. Reopened 2026-08-17 after absorbing a premature `g03` rollover. |
| `g03` | 2026-04-17 | Post-alpha stabilization (superseded) | Opened briefly after `v0.1-alpha` publication. Absorbed back into `g02` on 2026-08-17 — rollover was premature; `g02.006` and its batch cards carry the work. |

## Planned continuation (within `g02`)

Operator-owned target — **`g02.007+`** for `v0.2.0`:

- **`v0.2.0`** — Windows x64 + Linux x64 as co-primary platforms, VST3 in the
  supported envelope, refreshed validation matrix, and per-platform install
  artifacts — as further `g02` milestones (not a new generation).

See `docs/vision/002-strategic-horizons.md`.

## Rollover policy

Create a new generation only when maintainers explicitly decide the sequencing baseline needs a real reset.

Generations should be substantial. As a healthy default, expect something closer to 20 to 40 roadmap files before rollover is worth discussing. Treat that as a judgment guardrail, not an automatic counter.

Rollover is a closeout event, not a convenience move. Before opening the next generation:

- close, pause, supersede, or rehome every roadmap in the current generation
- refresh the roadmap front doors so the old generation is visibly closed
- purge stale generation-specific specs from `docs/specs/` so the active planning tree no longer carries dead lane debris

If that cleanup has not happened, stay in the current generation and finish the closeout there first.

## Next task

Define `g02.007+` milestones when ready to spec `v0.2.0`.
