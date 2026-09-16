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
and `specs/` so execution grammar and task planning are explicit once
development work begins.

Start in `vision/` for long-horizon direction, `architecture/` and `contracts/`
for the canonical structure and rules, `roadmaps/` for active execution
sequencing, and `logs/` for batch evidence and decisions.

If `specs/` exists, treat it as provisional planning that should promote into
`architecture/` and `contracts/` before execution relies on it.

## Current Posture

Keepsake is an Inflatable Cookie product. The canonical repository is
[`inflatable-cookie/keepsake`](https://github.com/inflatable-cookie/keepsake).

G01 is complete and compacted (see
[`roadmaps/archive/g01.md`](roadmaps/archive/g01.md)). The core bridge lanes
exist: config → scan → cache → factory → bridge → audio, plus GUI, CI, and
codebase-health follow-through.

`v0.1-alpha` is now published.

G02 is active. Tasks `001`–`006` are complete with outcomes collapsed into
the generation README. **`007+`** (`v0.2.0` — Windows, Linux, VST3) is
unauthored until the operator returns to spec it.

The strongest current proof is still the published `macOS + REAPER + VST2`
lane. Treat broader platform/format support as experimental until fresh
stabilization or `v0.2.0` matrix evidence says otherwise.

Long-horizon direction lives in
[`vision/002-strategic-horizons.md`](vision/002-strategic-horizons.md).

**Operator direction:** next scope-widening release is **`v0.2.0`** with
**Windows and Linux** as co-primary platforms and **VST3** in the push.

## Next Task

None active. Define the next `v0.2.0` tasks when ready to spec that lane.
<!-- northstar:lifecycle:begin schema=northstar.lifecycle.projection.v2 digest=sha256:2f217ddd1faa0baad0c4b18dfbc2fff5a84d3e39e401359b8da81006eac71a9e -->
| Generation | Disposition | Runway state |
| --- | --- | --- |
| g02 | open | planning_required |
| Task | Status | Stage | Revision | Record digest |
| --- | --- | --- | --- | --- |
| g02.007 | complete | none | 8 | sha256:1143c63d8410a90d180b91b0b9a1273f5508a1b078ae79055003b9cc128674c9 |
| g02.008 | complete | none | 8 | sha256:6fe7e357f50fbd0a98a52dc5de323d54f865502583dad813dc7d3eb0e1042559 |
| g02.009 | complete | none | 8 | sha256:01c6e9aaee18632360ebf9f85da1fd6e230d703d60f505f2aab2676d48a44da4 |
<!-- northstar:lifecycle:end -->
