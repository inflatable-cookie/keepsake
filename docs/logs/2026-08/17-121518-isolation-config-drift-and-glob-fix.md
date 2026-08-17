# Isolation config drift closed and glob matching fixed

Date: 2026-08-17
Posture: strict-ready

## Changed

- Compiled and executed
  `docs/roadmaps/g02/batch-cards/002-g02-isolation-config-drift-and-override-matching.md`.
- Added `src/glob_match.h` — one correct `*`/`?` matcher for every user-facing
  glob in the tree.
- Deleted both partial matchers: `BridgePool::glob_match` and
  `factory_helpers.cpp`'s `glob_match_simple`.
- `BridgePool::resolve_mode` now takes the plugin file path and matches override
  rows against plugin ID, display name, and path. `src/factory.cpp` passes
  `e.plugin_path`.
- Added `tools/isolation-override-test.cpp` and the `isolation-overrides` CTest
  case.
- Corrected contract 006 (default mode, override matching, validation list,
  stale next task) and `docs/setup/config-reference.md`.

## The drift, closed

Card 001 left this open deliberately. Reading the code closed both questions
without a product judgment call:

- **Default mode.** Contract 006 said `shared`; the code and the config
  reference said `per-instance`. `per-instance` was a deliberate safety change
  on 2026-04-11 (`59e916a`) after a hanging plugin in a shared process froze
  every other instance. 006 was stale. Corrected to `per-instance`, with the
  reason and the commit recorded so the original `shared` intent is not lost.
- **Match target.** 006 said plugin ID or name glob; the config reference said
  file path. The code only ever compared ID and name, so every path-based
  override in the published config reference — including its own examples —
  silently did nothing. Resolved as a superset: `match` now compares against ID,
  name, and path. Both documents' claims are now true and nothing regressed.

## The bug this turned up

Both glob surfaces were broken, differently:

- `BridgePool::glob_match` returned true for **any** text when a pattern began
  and ended with `*`. `match = "*Kontakt*"` captured every plugin in the
  session and forced them all into that row's isolation mode. It also ignored
  whatever sat between wildcards and never implemented `?`.
- `factory_helpers.cpp`'s `glob_match_simple`, used for `[[expose.plugin]]`,
  had its `*needle*` branch sitting unreachable behind an earlier `*suffix`
  branch, and returned false for any trailing-`*` pattern. So `Serum*` matched
  nothing and `*Kontakt*` matched nothing.

Both are gone. One implementation now backs both surfaces.

## Behaviour change for existing configs

This is a real behaviour change on the published alpha surface, not just a docs
fix. Anyone with existing `config.toml` globs should re-check them:

- `match = "*Anything*"` previously matched **every** plugin. It now matches
  only plugins that actually contain that text. If a user was accidentally
  relying on the match-all, their session isolation will change.
- `match = "Serum*"` and `path = "Serum*"` previously matched nothing. They now
  work.
- `?` now works. It never did before.
- Path-based `match` rows now work. They never did before.

The config reference carries this warning inline. Adding path as a third match
key is purely additive — it can only make a row match more, never less — so no
override that worked before stops working.

## Validation

- `cmake --preset default && cmake --build build`
- `ctest --test-dir build --output-on-failure` — 6/6 passed, including the new
  `isolation-overrides` case: glob wildcard semantics, backtracking, segment
  order, `?` width, path-separator crossing, all three match keys, managed-row
  exactness under the new matcher, and first-row-wins precedence
- `effigy qa`

The one build warning is pre-existing and unrelated
(`plugin_gui_mac_embed.mm`, deprecated CoreGraphics enum conversion).

## Risks retained

- The behaviour change above is unannounced to existing alpha users beyond the
  config reference note. If a release-notes or known-issues entry is wanted, it
  has not been written.
- Adding the file path as a match key was the one judgment call in this batch.
  It is reversible by dropping the third key from `BridgePool::resolve_mode`.
- Glob matching is still literal and case-sensitive with no character classes.
  That is now stated in both documents rather than left implicit.

## Next task

Decide whether this override-matching change deserves a line in
`docs/known-issues-v0.1-alpha.md` or the next release notes, given that it
changes isolation behaviour for anyone whose `config.toml` used a `*needle*`
pattern against the published alpha.
