# Keepsake agent guide

This file applies to the whole repository. `CLAUDE.md` is the one-line bridge
to this file; there are no nested agent instruction files.

## Project and current lane

Keepsake is a standalone C/C++ CLAP plugin that bridges VST2, VST3, and AU v2,
including 32-bit binaries, through isolated helper processes. It is an
Inflatable Cookie product, distributed under LGPL v2.1, and is separate from
Signal and Loophole.

The published `v0.1-alpha` is proven most strongly on macOS + REAPER + VST2.
Generation `g02` remains active: tasks `001`–`006` are complete, while
`g02.007+` (`v0.2.0`, Windows/Linux co-primary with VST3) is operator-owned
and unauthored. Do not invent that lane or broaden public claims from code
existence alone.

## Boundaries that must survive changes

- VST2 uses VeSTige only. Never use, reference, vendor, or redistribute the
  Steinberg VST2 SDK.
- CLAP remains the outer format. VST3 SDK use is subprocess-only; resolve its
  GPLv3 boundary before making a public VST3 support claim.
- 32-bit bridging is first-class: targets are macOS x86_64/arm64, Windows
  x86_64, and Linux x86_64, with platform limits stated honestly.
- Keep bridge isolation, legal/trademark guardrails, and the standalone
  Signal/Loophole boundary intact. See `docs/project-brief.md` for rationale.

## Canonical sources

- [`docs/README.md`](docs/README.md) — orientation and current posture
- [`docs/vision/README.md`](docs/vision/README.md) — direction and constraints
- [`docs/architecture/README.md`](docs/architecture/README.md) — system shape
  and ownership
- [`docs/contracts/README.md`](docs/contracts/README.md) — durable boundaries;
  start with [`001-working-rules.md`](docs/contracts/001-working-rules.md)
- [`docs/roadmaps/README.md`](docs/roadmaps/README.md) — Northstar tasks
- [`docs/specs/README.md`](docs/specs/README.md) — provisional planning only
- [`docs/releases/README.md`](docs/releases/README.md) and
  [`docs/setup/README.md`](docs/setup/README.md) — shipped claims and usage
- [`docs/logs/README.md`](docs/logs/README.md) — dated evidence and closeout
- [`docs/policy/internal-writing-style.md`](docs/policy/internal-writing-style.md)
  — glue-light internal writing

## Work and validation

Route by job; do not run a startup ritual:

- `effigy tasks` — discover repository selectors.
- `effigy graph explore "<question>" --json` — understand ownership, flow, or
  impact; use `effigy graph affected` after a change.
- `effigy doctor` — diagnose repository health or selector ambiguity.
- `effigy test --plan` — inspect test shape when a test selector is available.
- `effigy qa` — run configured docs and Northstar checks; use the narrower
  selector when it is enough.

Prefer `effigy <selector>` over raw tools when it covers the operation. Use
`--repo <PATH>` only when deliberately targeting another repository; do not
add `--repo .` from this checkout. Do not edit `.github/workflows/` or run
release mutations without an explicit operator request.

Work in meaningful batches, preserve unrelated changes, and stop on a missing
or contradictory contract, unresolved operator intent, plan-changing
validation failure, or any legal-boundary violation. Before calling work done,
update affected canonical refs and a dated log, run the relevant checks, name
remaining limits, and leave one unambiguous next task. Do not call mockups,
placeholders, or unproven paths complete.
