# macOS preview lane: retain or remove

Owner: Inflatable Cookie. Non-authoritative lead, carried since 2026-09-09.

## Current meaning

Keepsake's macOS posture is settled: the bridge-owned native editor is the
supported interaction model, and the IOSurface preview is diagnostic-only. The
remaining question is maintenance, not product behaviour: does the retained
preview implementation stay in tree as operator-only code, or move onto a
removal or simplification track once its diagnostic value no longer justifies
the maintenance cost?

This does not block any support claim. The 2026-07 companion presentation and
input experiment was removed after it failed the interaction and complexity
bars; the older operator-only IOSurface preview remains in tree, already
demoted behind a diagnostic posture. Removing it now would be cleanup work, not
release-critical work.

## Constraints

- Do not disturb the `v0.1-alpha` support envelope.
- The live-editor-first posture in the
  [macOS editor architecture](../knowledge/architecture/macos-editor.md) and
  [macOS editor contract](../knowledge/contracts/macos-native-editor-and-host-placeholder.md)
  stands regardless of this decision.
- Do not imply preview support either way.

## Open question

Should the retained preview implementation (`src/plugin_gui_mac_embed.mm`,
`src/plugin_gui_mac_embed.h`, `src/bridge_gui_mac_iosurface.mm`, plus
supporting plugin and bridge call sites) stay as operator-only diagnostics with
explicit maintenance bounds, or be removed entirely to simplify the macOS GUI
surface?

- If retained: are the remaining diagnostics intentional and documented, and
  does the lane distort any release or support claim?
- If removed: delete the unused code and config branches, remove obsolete doc
  references, and update the known-issues and architecture surfaces.

## Promotion condition

Promote when the preview lane starts causing real maintenance drag or
regressions, when cleanup becomes the highest-value task, or when a maintainer
wants a smaller macOS GUI surface. Exit state: the retained-or-removed status
is explicit, docs and code comments match it, and there is no support ambiguity
between preview and live editor.
