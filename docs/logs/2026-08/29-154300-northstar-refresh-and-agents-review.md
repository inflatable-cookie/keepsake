# 2026-08-29 15:43 — Northstar refresh and AGENTS review

Scope: project refresh followed by the target-repository AGENTS optimization.

## Target and posture

- repository: `/Users/tom/Dev/projects/keepsake`
- posture: standalone Keepsake consumer repo with the strict delivery layer
- active generation: `g02`; `g02.007+` / `v0.2.0` remains operator-owned and unauthored
- published release: `v0.1-alpha`; strongest proof is macOS + REAPER + VST2

## Facet results

| Facet | State | Evidence / decision |
|---|---|---|
| Instruction surface | repaired | Root `AGENTS.md` rewritten for reader flow, current lane, routing, boundaries, stop rules, and validation. `CLAUDE.md` remains the exact `@AGENTS.md` bridge. |
| Docs spine | repaired | Contracts front door no longer points at pre-alpha publication; logs front door now records this refresh. |
| Triage | current | No `docs/triage/` directory or Markdown triage notes exist. No note disposition is required. |
| Architecture / authority | repaired | Repository authority map now reflects the retired Soundcheck companion/screenshot path and keeps future inspection work host-owned. |
| Planning completeness | missing | `g02.007+` / `v0.2.0` milestones and the platform-config contract are not authored. |
| Currentness / closeout | repaired | Stale canonical `Next Task` pointers in the contracts surfaces now point at the operator-owned continuation. Historical logs retain their dated context. |
| Validation | current with baseline findings | `effigy qa:northstar`, `effigy qa:docs`, and the consumer-safe Northstar agent audit pass. `effigy doctor` still reports the pre-existing 21 god-file findings; this docs-only pass does not change them. This checkout has no `test` selector, so `effigy test --plan` is not runnable. |
| Distribution | not-applicable | No release or packaging surface changed. |

## Inspected surfaces and checks

- `AGENTS.md`, `CLAUDE.md`, `README.md`
- `docs/README.md`, vision, architecture, contracts, roadmaps, specs, releases,
  setup, logs, policy, handoff, and `PAPERCUTS.md` front doors
- `effigy.toml`, `tasks/effigy.tasks.toml`, and `docs/effigy.docs.toml`
- `effigy tasks`, `effigy doctor`, `effigy graph status --json`,
  `effigy graph index --json`, `effigy qa:northstar`, `effigy qa:docs`
- `effigy --repo /Users/tom/.agents/skills/northstar northstar/check:agent-instructions /Users/tom/Dev/projects/keepsake`

## Bounded repairs

- Rewrote `AGENTS.md` from startup ritual to project-specific reader journey
  while preserving legal, format, isolation, worktree, stop, and validation
  boundaries.
- Updated the contracts front door with its active contract register and
  current next-task guidance; refreshed `docs/contracts/001-working-rules.md`.
- Updated `docs/architecture/repo-authority-map.md` to match current ownership
  and the no-companion integration boundary.
- Added this evidence log and linked it from `docs/logs/README.md`.

## Unresolved blockers and operator decisions

- No executable `g02.007+` card exists. Do not begin `v0.2.0` implementation
  until the operator authors the milestone/spec lane.
- Platform config remains a pending contract, as recorded in
  `docs/contracts/contract-index.md` and the strategic horizons.
- The god-file findings remain a separate code-architecture lane; this refresh
  does not silently refactor production code.

## Recommended next route

Run a Northstar planning-readiness review for `g02.007+` / `v0.2.0` when the
operator is ready to author the next lane.

## Execution safety

Docs-only work is safe to continue. New production execution is not yet safe:
the next milestone is unauthored and the platform-config contract is pending.
