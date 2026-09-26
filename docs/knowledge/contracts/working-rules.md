# Working rules

Owner: Inflatable Cookie. Delivery grammar, guardrails and stop conditions for
all execution work in this repository.

## Delivery grammar

- Material work moves from intent to durable rules: shape a change while it is
  unsettled, then promote the durable parts into the owning
  [knowledge](../README.md) file (architecture, contract, or vision). Work
  should not depend on provisional planning that has not been promoted.
- Use a separate contract for a stable seam, an important boundary, or a
  durable rule that needs its own authority surface.
- Prefer real integrated behaviour over mockups, placeholders or token
  scaffolding.
- Prefer simplicity over decorative or architectural complexity the governing
  references do not require.
- Prefer end-to-end follow-through over convenient partial closure when a task
  promised a working path.
- Prefer explicit incompleteness over implied completion when a path is still
  scaffolded or unproven.
- Treat disconnected gesture work as incomplete unless the task was explicitly
  scoped as bounded substrate-only work.
- File papercuts in Queue with `papercut.add` (see the `northstar-lean` skill).
  There is no `PAPERCUTS.md`.

## Intent checkpoints

- When the next direction is not clearly determined by the current knowledge
  and plan, stop and ask the operator for intent instead of inventing a lane or
  batch.
- Treat competing plausible directions, handoff choices, and still-open product
  tradeoffs as intent checkpoints rather than routine planning work.
- Do not start work while an unresolved intent checkpoint still governs its
  scope.

## Legal guardrail (hard stop)

- Stop immediately and raise to the operator if any path would require using or
  referencing the Steinberg VST2 SDK. This is a legal constraint, not a
  preference. VeSTige only.
- Stop immediately if a change would make CLAP no longer the outer plugin
  format, or would put VST3 code outside the bridge subprocess.

The boundaries are owned by
[legal-boundaries.md](legal-boundaries.md); read them before touching a format
loader or a licence surface.

## Definition of done

- Do not call work done while it is still a mockup, placeholder or partial
  token implementation.
- Update the owning knowledge file and any dependent references so they match
  reality.
- Run the required validation and name the commands; record failures honestly.
- Name unresolved blockers or limits explicitly instead of hiding them inside a
  completion claim.
- Leave one unambiguous next step.

## Autonomy

- Agents may continue across consecutive ready tasks while they stay inside the
  same lane, the governing references still match, and the prior task's
  evidence gate passed.
- Set a local upper bound for an uninterrupted run, such as a task or time
  limit, so autonomy stays bounded.
- Stop on a missing or contradictory contract, unresolved operator intent, a
  plan-changing validation failure, or any legal-boundary violation.

## Automation runtime policy

- Prefer `effigy` when it already covers the repository operation.
- When repo-owned script logic is still needed, default to TypeScript run with
  `bun`.
- Use `bash` only for thin glue or compatibility boundaries that Effigy or
  Bun/TypeScript cannot own cleanly.
- Use `python` or another runtime only when a concrete technical requirement
  justifies it.
- Build tooling (CMake, Ninja and the like) is C/C++ project infrastructure,
  not a repo scripting exception.

## Product guardrails

- Do not add UI or interaction complexity unless the governing references make
  the user need explicit. Keepsake has no UI beyond the settings and
  preferences needed for scan paths, exposure and rescan.
- Do not use the VST Compatible logo or claim Steinberg certification. See
  [legal-boundaries.md](legal-boundaries.md).
- "Works" means: loads, initialises, and exposes a plugin through the CLAP
  factory with correct metadata — not merely compiles.
- Keep public support claims aligned to the validation evidence. If a claim is
  not proven, mark it experimental or leave it out.
- Keep the operator path direct; do not require invented side flows to complete
  normal work.

## Stop conditions

- Stop on missing or contradictory authority, or a planning gap.
- Stop when operator intent or prioritisation is unresolved across multiple
  plausible directions.
- Stop when user-facing ambiguity exceeds the product guardrails.
- Stop when validation fails in a way that changes the plan.
- Stop when a proposed change would cross a legal boundary.
