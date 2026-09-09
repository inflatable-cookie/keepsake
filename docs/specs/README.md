# Specs

Use this folder when a change needs provisional planning before it is settled
into architecture and contracts.

## Artifact Types

- `NNN-<slug>.md` — master specs for material goals or epics

Execution cards live as Northstar tasks under `docs/roadmaps/gNN/` (see
`docs/roadmaps/templates/task-template.md`); specs do not carry a nested
card hierarchy.

## Rule

Before roadmap generation rollover, purge stale generation-specific specs from the active tree so the next generation does not inherit dead planning debris.


Specs are a stepping stone, not the final authority.

Use specs to work through a change while the path is still being shaped. Once
the durable outcomes are accepted:

- structural decisions should be promoted into `docs/architecture/`
- behavioral or policy rules should be promoted into `docs/contracts/`

Roadmap execution should rely on architecture and contracts, not only on raw
spec text, once the change has moved out of planning.

Use an explicit lifecycle:

- `active` when the spec still governs live planning or an imminent task
- `retired-in-place` when the lane is closed but the artifact still deserves a
  short-lived place in the active tree for traceability
- `archived` when the artifact no longer governs live work and should move out
  of the active specs surface

Prefer archive over indefinite retired-in-place clutter. `docs/specs/archive/`
is the preservation surface.

## Current Active Specs

No active specs. Create a master spec when `g02.007+` / `v0.2.0` is specced;
execution cards for it will live as `g02` Northstar tasks.

## Templates

- `archive/README.md`
- `templates/master-spec-template.md`

## Next Task

None active. Define `g02.007+` tasks when ready to spec `v0.2.0`.
