# 2026-08-17 15:30 — Northstar refresh and Atlas runway

Scope: Northstar `project-refresh` + `atlas` after upstream Northstar update.

## Refresh repairs

- Added `CLAUDE.md` bridge (`@AGENTS.md`)
- Added `PAPERCUTS.md` starter
- Fixed `AGENTS.md` Effigy references (removed broken `docs/guides/` pointers;
  project-local skill paths)
- Removed duplicate proof paragraph in `docs/README.md`
- Reconciled stale `Next Task` pointers across vision, architecture, contracts,
  roadmaps, logs, and root `README.md` (many still pointed at `g02`)
- Updated `docs/contracts/contract-index.md` roadmap readiness for `g03`

## Atlas promotion

- Authored `docs/vision/002-strategic-horizons.md` — horizon model H0–H5,
  strategic bets, operator decisions, promotion map, milestone transitions
- Linked from `docs/vision/README.md`, `docs/README.md`, `docs/roadmaps/README.md`

## Facet states (refresh report)

| Facet | State |
|---|---|
| Instruction surface | repaired |
| Docs spine | repaired |
| Architecture/authority | current |
| Planning completeness | current |
| Currentness/closeout | repaired |
| Validation | current (`effigy qa:northstar` pass; doctor god-files pre-existing) |
| Distribution | not-applicable |

## Recommended next route

Continue `g03.001` — triage the next post-alpha report cluster into batch 003.
Operator decisions for horizon `H1` recorded in strategic horizons doc.

## Validation

```sh
effigy qa:northstar
effigy --repo ~/.agents/skills/northstar northstar/check:agent-instructions .
```

Both pass (agent-instruction audit advisory only).
