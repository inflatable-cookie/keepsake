# Triage — macOS Preview Lane Disposition

Status: deferred candidate (non-authoritative)
Owner: Inflatable Cookie
Created: 2026-04-17 as roadmap backlog `001`; retired to triage 2026-09-09
Source: `docs/roadmaps/backlog/001-macos-preview-lane-disposition.md` (deleted on retirement)
Depends on:
  - g02.005 complete
  - stable macOS live-editor baseline
Related refs:
  - docs/architecture/macos-bridged-ui-options.md
  - docs/contracts/007-macos-native-editor-and-host-placeholder.md
  - docs/logs/2026-04/16-221500-mac-iosurface-embedded-ui-architecture-decision.md
  - docs/logs/2026-04/17-064500-macos-live-editor-stabilization-cleanup.md
  - docs/logs/2026-04/17-071000-macos-preview-lane-audit.md

## Current meaning

Keepsake has a coherent macOS posture: the bridge-owned live editor is
the supported interaction model and preview / IOSurface remains
diagnostic-only. The remaining open question is maintenance posture,
not product behavior: whether the retained preview implementation
stays in tree as operator-only code, or moves onto a removal /
simplification track once its diagnostic value is no longer worth the
maintenance cost.

This is not blocking the current alpha support claim set. The 2026-07
companion presentation/input experiment was removed after it failed the
interaction and complexity bars; the older operator-only IOSurface
preview remains in tree. The code is already demoted behind diagnostic
posture. Removing it now would be cleanup work, not release-critical
work.

## Constraints

- Do not disturb the `v0.1-alpha` support envelope (strongest lane:
  `macOS + REAPER + VST2`).
- The live-editor-first posture in contract `007` and
  `macos-bridged-ui-options.md` stands regardless of this decision.
- Do not imply preview support in release or claim surfaces either way.

## Open questions

- Should the retained preview implementation (`src/plugin_gui_mac_embed.mm`,
  `src/plugin_gui_mac_embed.h`, `src/bridge_gui_mac_iosurface.mm`, plus
  supporting plugin/bridge call sites) stay as operator-only diagnostics
  with explicit maintenance bounds, or be removed entirely to simplify
  the macOS GUI surface?
- If retained: are the remaining diagnostics intentional and documented,
  and does the lane distort any release/support claim?
- If removed: delete unused code and config branches, remove obsolete
  docs references, and update known-issues / architecture / roadmap
  surfaces accordingly.

## Promotion condition

Promote to a `g02` task only when existing planning authority makes
scope, generation, dependencies, ordering, and frontier placement
unambiguous — for example when one of these becomes true:

- the preview lane starts causing real maintenance drag or regressions
- release work is sufficiently complete that cleanup becomes the
  highest-value task
- a maintainer explicitly wants a smaller, clearer macOS GUI surface
  before or after alpha publication

Exit state when executed: the retained-or-removed status of the macOS
preview lane is explicit, docs and code comments match that outcome,
and there is no implied support ambiguity around preview vs live
editor posture.

## Next check

Leave deferred until the alpha release lane no longer has
higher-value support, packaging, or validation work in front of it.
Owner: Inflatable Cookie.
