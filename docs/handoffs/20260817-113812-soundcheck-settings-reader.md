---
title: Soundcheck settings reader handoff
kind: northstar-handoff
status: resolved
owner: Inflatable Cookie
created: 2026-08-17
updated: 2026-08-17
handoff_path: /Users/tom/Dev/projects/keepsake/docs/handoffs/20260817-113812-soundcheck-settings-reader.md
tags: [coordination, handoff, soundcheck, isolation]
---

## What This Thread Was Doing

This is a spin-off from Soundcheck, not a continuation of Keepsake's current
g03 stabilization lane.

Soundcheck already writes optional isolation policy to a managed file. The
writer, UI, and fixture are done. What still isn't true is that Keepsake ever
reads that file. Until it does, changing isolation in Soundcheck does not
change how the bridge actually runs.

The Soundcheck orchestrator asked for a Keepsake thread to take that consumer
side. The job is Keepsake-owned: discover the managed file at factory startup,
merge valid isolation fields over `config.toml`, and ignore the file entirely
when it is missing or invalid. Keepsake has to keep working when Soundcheck is
closed or never installed.

## Why It Matters

Producers are supposed to set isolation once in Soundcheck and have Keepsake
honour it. Right now that promise is one-sided. Soundcheck can write
`keepsake.toml`; the bridge still only listens to its own `config.toml`.

This is also how the two products stay decoupled. There is no live API, no
process discovery, and no Soundcheck lifecycle check. The file is the whole
seam.

## Current State

Here is the short version of where things stand:

- **Done:** Soundcheck's producer half. Card 050 wrote the version 1 schema,
  atomic writer, Integrations UI, and native proof. Contract 002 is the
  promoted seam. Keepsake's own isolation runtime already exists via
  `config.toml` and contract 006. The old Soundcheck HTTP-API plan
  (`g01.016`) is superseded and must not be revived.
- **Still open:** Keepsake has no reader for Soundcheck's managed file. There
  is no Keepsake batch card for this work yet. End-to-end proof still needs
  valid-file merge, absent/invalid fallback, unsupported-schema fallback,
  stable-ID override matching, and no Soundcheck process dependency.
- **Active spec lane:** none for this reader. Keepsake's advertised live lane
  is still `g03.001` post-alpha stabilization. This spin-off is operator-
  requested; it is not already sequenced in Keepsake's front doors.
- **Current batch card:** none in Keepsake. Do not treat Soundcheck card 050
  as executable here.
- **Canonical refs:**
  - `/Users/tom/Dev/projects/soundcheck/docs/contracts/002-companion-api-and-keepsake-integration-contract.md`
    is the consumer contract to implement
  - `/Users/tom/Dev/projects/soundcheck/docs/contracts/fixtures/keepsake-settings-v1.toml`
    is the canonical fixture
  - `/Users/tom/Dev/projects/keepsake/docs/contracts/006-process-isolation-policy.md`
    owns Keepsake's isolation modes and `config.toml` overrides
  - `/Users/tom/Dev/projects/keepsake/docs/setup/config-reference.md`
    is the user-facing `config.toml` schema
  - `/Users/tom/Dev/projects/keepsake/docs/architecture/repo-authority-map.md`
    keeps Soundcheck on the same CLAP host contract as every other host
- **Remaining continuation envelope:** compile a Keepsake-owned card, then
  implement the factory-startup reader. Stop if this would silently displace
  `g03.001` without recording the insert.
- **Lane budget / pause signal:** planning first. Keepsake working rules say
  stop on competing directions. The operator asked for this thread, so the
  work is wanted, but it still needs a Keepsake card and a clear relationship
  to g03 before C++ changes.
- **Key files:**
  - `/Users/tom/Dev/projects/soundcheck/docs/contracts/002-companion-api-and-keepsake-integration-contract.md`
  - `/Users/tom/Dev/projects/soundcheck/docs/contracts/fixtures/keepsake-settings-v1.toml`
  - `/Users/tom/Dev/projects/soundcheck/docs/roadmaps/g04/batch-cards/049-g04-companion-api-contract-gate.md`
  - `/Users/tom/Dev/projects/soundcheck/docs/roadmaps/g04/batch-cards/050-g04-companion-api-integration.md`
  - `/Users/tom/Dev/projects/keepsake/docs/roadmaps/g01/016-soundcheck-integration.md`
  - `/Users/tom/Dev/projects/keepsake/docs/roadmaps/g03/001-post-alpha-stabilization-and-claim-corrections.md`
  - `/Users/tom/Dev/projects/keepsake/docs/contracts/006-process-isolation-policy.md`
  - `/Users/tom/Dev/projects/keepsake/docs/setup/config-reference.md`
  - `/Users/tom/Dev/projects/keepsake/AGENTS.md`

## Boundaries

Please keep the next pass within these boundaries:

- **In scope:** read Soundcheck's managed `integrations/keepsake.toml` at
  factory startup; merge valid version 1 isolation default and `plugin_id`
  overrides over Keepsake's equivalent `config.toml` fields; fall back to
  `config.toml` then Keepsake defaults when the file is missing, unreadable,
  malformed, or an unsupported schema; prove that with Soundcheck closed.
- **Out of scope:** editing Soundcheck; editing Keepsake's user-owned
  `config.toml`; any live Soundcheck API, process discovery, or lifecycle
  check; file watching in version 1; scan paths, exposure rules, GUI, loader
  selection, 32-bit helpers, or crash recovery in the managed file; reviving
  `g01.016`; Soundcheck-specific editor, screenshot, or companion helpers.
- **Repo constraints:** Follow `/Users/tom/Dev/projects/keepsake/AGENTS.md`.
  VeSTige only, no Steinberg VST2 SDK. Prefer `effigy` for supported work.
  Do not edit `.github/workflows/` or run release mutations unless the
  operator asks.

## Important Context

- **Planning lineage:** Soundcheck cards 049-050 chose a file seam after the
  localhost API proved unfit. Soundcheck g04.003 is complete on the producer
  side and explicitly left the reader downstream. Keepsake `g01.016` described
  the abandoned API and is marked superseded. Keepsake's live front doors
  still point at `g03.001`.
- **How the plan fits the system:** Soundcheck contract 002 is the schema and
  fallback authority for the managed file. Keepsake contract 006 remains
  authority for what isolation modes mean at runtime. The managed file is not
  a second isolation model; it is another source of the same three modes.
  Overrides in the managed file use Soundcheck's `plugin_id` key and Keepsake's
  stable `keepsake.<format>.<uid>` IDs, not paths or name globs.
- **Decisions and preferences:** Soundcheck must never edit `config.toml`. A
  valid supported managed file overrides equivalent isolation fields from
  `config.toml`. Missing fields fall through. A bad file is ignored as a
  whole. Unknown fields in a supported schema are ignored. Reload in v1 is
  host restart or plugin rescan, not a watcher. The UI in Soundcheck already
  describes this as settings for Keepsake, not live bridge control.
- **Open tensions:** contract 006 still says the Keepsake default is `shared`
  and `match` can be plugin ID or name glob. The config reference currently
  documents default `per-instance` and path-glob `match`. The Soundcheck
  fixture uses `default = "per-instance"` and exact `plugin_id` rows. Do not
  quietly pick a winner between 006 and the config reference while implementing
  the reader; the managed file must follow contract 002, and any `config.toml`
  merge has to stay honest about what Keepsake actually parses today. Also:
  inserting this into g03 vs opening a later card is an intent checkpoint if
  the operator still wants stabilization to stay first.

## Suggested Next Move

Start here: read Soundcheck contract 002 and the fixture, then Keepsake
contract 006 and the config reference, then `g01.016` so you can see the
abandoned API in writing.

After that, compile a Keepsake-owned card rather than coding against
Soundcheck's docs. The card should name the managed-file path, version 1
schema, merge/fallback rules, factory-startup timing, and the five proofs in
contract 002's cross-repo completion list. If g03.001 still has to stay first,
say so and leave this card queued instead of implementing it as an untracked
side quest.

If the 006 vs config-reference mismatch changes how merge has to work, pause
and bring that back rather than inventing a fourth isolation config dialect.

## Completion Protocol

This handoff exists because a Keepsake thread needs to take over a seam
Soundcheck cannot finish. Before you finish, please:

1. Leave a Keepsake batch card (or an explicit queued/blocked card) that
   reflects the real stopping point. Do not close Soundcheck card 050 again.
2. Update Keepsake's roadmap, contract index, and log if you actually land or
   sequence the reader. Soundcheck's front doors already say the reader is
   downstream; only update Soundcheck if the reader lands and that claim
   changes.
3. Say whether the reader card is ready, queued behind `g03.001`, or blocked
   on the isolation-config mismatch.
4. Record that this was an operator-requested insert from Soundcheck, not a
   silent replacement of g03.
5. Call out unresolved merge-key or default-mode drift plainly.
6. Leave one clear next task for the following Keepsake thread.

If the same Keepsake thread can continue after compaction, do not create
another handoff just for that reason.

## Resolution

Resolved 2026-08-17 by the Keepsake thread that picked this up.

- Card compiled and executed:
  `docs/roadmaps/g03/batch-cards/001-g03-soundcheck-managed-settings-reader.md`
  (status `complete`).
- Reader landed in `src/managed_settings.{h,cpp}`, called once from
  `keepsake_factory_init`. All five contract 002 proofs pass in the
  `managed-settings` CTest case, plus a factory-startup `clap-scan` proof with
  Soundcheck never launched.
- Evidence log:
  `docs/logs/2026-08/17-115406-soundcheck-managed-settings-reader.md`.
- `g01.016` was not revived, no Soundcheck file was edited, and `g03.001`
  remains the live lane — this went in as an operator-requested insert.
- The contract 006 vs config-reference drift was left unresolved by card 001 by
  design, then closed on the same day by
  `docs/roadmaps/g03/batch-cards/002-g03-isolation-config-drift-and-override-matching.md`.
  Both documents now agree with the shipped code, and the two broken glob
  matchers that surfaced alongside it are replaced by one correct
  implementation. Evidence:
  `docs/logs/2026-08/17-121518-isolation-config-drift-and-glob-fix.md`.
