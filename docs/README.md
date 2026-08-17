# Docs

## Start Here

- [`vision/README.md`](vision/README.md)
- [`architecture/README.md`](architecture/README.md)
- [`contracts/README.md`](contracts/README.md)
- [`roadmaps/README.md`](roadmaps/README.md)
- [`logs/README.md`](logs/README.md)
- [`releases/README.md`](releases/README.md)
- [`known-issues-v0.1-alpha.md`](known-issues-v0.1-alpha.md)
- [`demos.md`](demos.md)

Stricter delivery layer (installed):

- [`contracts/001-working-rules.md`](contracts/001-working-rules.md)
- [`specs/README.md`](specs/README.md)

Project reference material:

- [`project-brief.md`](project-brief.md)
- [`demos.md`](demos.md)

## Working Rule

The baseline docs spine is `vision/`, `architecture/`, `contracts/`,
`roadmaps/`, and `logs/`.

Keepsake also uses the stricter delivery spine: `contracts/001-working-rules.md`
and `specs/` so execution grammar and batch-card planning are explicit once
development work begins.

Start in `vision/` for long-horizon direction, `architecture/` and `contracts/`
for the canonical structure and rules, `roadmaps/` for active execution
sequencing, and `logs/` for batch evidence and decisions.

If `specs/` exists, treat it as provisional planning that should promote into
`architecture/` and `contracts/` before execution relies on it.

## Current Posture

Keepsake is an Inflatable Cookie product. The canonical repository is
[`inflatable-cookie/keepsake`](https://github.com/inflatable-cookie/keepsake).

G01 is complete. The core bridge lanes exist: config → scan → cache → factory
→ bridge → audio, plus GUI, CI, and codebase-health follow-through.

`v0.1-alpha` is now published.

G02 is active. Milestones `001`–`006` are complete. **`007+`** (`v0.2.0` —
Windows, Linux, VST3) is unauthored until the operator returns to spec it.

The strongest current proof is still the published `macOS + REAPER + VST2`
lane. Treat broader platform/format support as experimental until fresh
stabilization or `v0.2.0` matrix evidence says otherwise.

Long-horizon direction lives in
[`vision/002-strategic-horizons.md`](vision/002-strategic-horizons.md).

**Operator direction:** next scope-widening release is **`v0.2.0`** with
**Windows and Linux** as co-primary platforms and **VST3** in the push.

## Next Task

Define `g02.007+` milestones when ready to spec `v0.2.0`.
