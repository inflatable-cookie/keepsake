# 002 - G02 Isolation Config Drift and Override Matching

Status: complete
Owner: Inflatable Cookie
Updated: 2026-08-17
Milestone refs: `docs/roadmaps/g02/006-post-alpha-stabilization-and-claim-corrections.md`
Depends on: `docs/roadmaps/g02/batch-cards/001-g02-soundcheck-managed-settings-reader.md`
Governing refs:
  - `docs/contracts/006-process-isolation-policy.md`
  - `docs/contracts/001-working-rules.md`
  - `docs/setup/config-reference.md`
Auto-start next card: no

## Objective

Close the isolation-config drift card 001 deliberately left open, and fix the
glob matching that made the published `config.toml` override and whitelist
documentation untrue in practice.

This is claim correction plus a stabilization fix — squarely `g02.006` step 2
and step 3 — not new scope.

## What Was Actually Wrong

Card 001 recorded that contract 006 and `docs/setup/config-reference.md`
disagreed and that each was half wrong. Checking the code closed both questions
without a product judgment call, and turned up a third, worse problem.

| Question | Contract 006 said | Config reference said | Code did |
|---|---|---|---|
| Global default | `shared` | `per-instance` | `per-instance` |
| `match` target | plugin ID or name glob | full plugin file path | plugin ID or name glob |
| Glob support | `*` | `*` and `?` | `*`, incorrectly |

- **Default mode.** `per-instance` was a deliberate safety change on 2026-04-11
  (`59e916a`) after a hanging plugin in a shared process froze every other
  instance. Contract 006 was simply never updated. The contract is the stale
  document; nothing was chosen here.
- **Match target.** The code never compared `match` against the file path, so
  every path-based override in the published config reference — including its
  own worked examples — silently did nothing.
- **Glob matching.** `BridgePool::glob_match` returned true for *any* text when
  a pattern both began and ended with `*`, so `match = "*Kontakt*"` captured
  every plugin in the session. It also ignored the pattern between wildcards
  entirely and never implemented `?`. `factory_helpers.cpp` carried a second,
  differently broken copy used for `[[expose.plugin]]`: `*needle*` was dead code
  behind an earlier branch, and a trailing-`*` pattern matched nothing.

## Scope

- one shared, correct glob implementation for both user-facing glob surfaces
- match isolation override rows against plugin ID, display name, and file path
- correct contract 006's default mode and match semantics
- correct the config reference's match semantics and note the behaviour change
- Do not change the shipped default mode itself — `per-instance` stays.
- Do not change managed-file row semantics; they stay exact-ID, never globbed.
- Do not touch the Soundcheck repository.

## Decision Recorded

Making `match` compare against the file path *as well as* ID and name is a
superset: it makes both documents' claims true, makes the published config
reference's examples work as written, and regresses nothing. The alternative —
declaring path matching unsupported and telling alpha users to rewrite working-
looking configs — was rejected as the worse outcome for a feature that has been
documented since release.

This is the one judgment call in the card. It is reversible by dropping the
third key from `BridgePool::resolve_mode`.

## Steps

1. Add `src/glob_match.h` with a correct `*`/`?` matcher.
2. Delete `BridgePool::glob_match` and `glob_match_simple`; point both call
   sites at the shared implementation.
3. Extend `BridgePool::resolve_mode` with the plugin path and pass
   `e.plugin_path` from the factory.
4. Add `tools/isolation-override-test.cpp` pinning glob semantics, the three
   match keys, managed-row exactness, and first-row-wins precedence.
5. Correct contract 006 and `docs/setup/config-reference.md`, including a
   behaviour-change note for anyone with existing overrides.

## Acceptance Criteria

- `*Kontakt*` matches only plugins containing "Kontakt"
- `Serum*`, `*.vst`, `a*b*c`, and `?` all behave as documented
- an override matches by plugin ID, by display name, or by file path
- a managed-file row still matches its plugin ID exactly and nothing else
- the first matching override row wins
- contract 006 and the config reference agree with each other and with the code
- no remaining second glob implementation in the tree

## Evidence Required

- `ctest` including the new `isolation-overrides` case
- `effigy qa`
- dated log recording the behaviour change for existing configs

## Stop Conditions

- stop if correcting the default mode turns out to be a live product decision
  rather than a stale document (it was not — `59e916a` settles it)
- stop if adding path matching would change which plugins an existing override
  *stops* matching (it cannot; the third key is purely additive)

## Completion Evidence

- `src/glob_match.h` added; both partial matchers deleted
- `BridgePool::resolve_mode` takes the plugin path; `src/factory.cpp` passes it
- `tools/isolation-override-test.cpp` + `isolation-overrides` CTest case
- contract 006 corrected: default is `per-instance` with the reason and the
  commit recorded, plus an explicit override-matching section
- config reference corrected with a behaviour-change note for existing overrides
- 6/6 CTest pass, full build clean, `effigy qa` green
