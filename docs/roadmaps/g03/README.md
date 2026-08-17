# G03 — Post-Alpha Stabilization

Status: active
Started: 2026-04-17

## Milestones

| Milestone | Title | Status |
|---|---|---|
| `001` | [Post-Alpha Stabilization and Claim Corrections](001-post-alpha-stabilization-and-claim-corrections.md) | active |

## Batch Cards

| Card | Title | Status |
|---|---|---|
| `001` | [Soundcheck Managed Settings Reader](batch-cards/001-g03-soundcheck-managed-settings-reader.md) | complete |
| `002` | [Isolation Config Drift and Override Matching](batch-cards/002-g03-isolation-config-drift-and-override-matching.md) | complete |

Card 001 is an operator-requested insert from Soundcheck, not a replacement for
`g03.001`. It closed the consumer half of Soundcheck's contract 002 — Keepsake
now reads Soundcheck's managed isolation file at factory startup.

Card 002 is ordinary `g03.001` work: it closed the isolation-config drift card
001 left open and fixed the glob matching that made the published override and
whitelist documentation untrue. Stabilization remains the live lane.

## Sequencing Intent

G03 starts after `v0.1-alpha` publication.

This generation is not about broadening claims quickly. It is the short,
practical stabilization lane that follows a first public drop:

- bug intake from real users
- claim corrections where release wording outruns evidence
- installer/runtime friction on the published artifact surface
- targeted validation refresh where new regressions or weak spots show up

The goal is to make the published alpha less surprising before opening another
scope-widening or feature-heavy generation.

## Release Posture

- `v0.1-alpha` is published and is now the reference surface.
- Supported lane remains `macOS + REAPER + VST2`.
- Windows, Linux, VST3, AU v2, and 32-bit remain experimental until fresh
  evidence says otherwise.
- Post-release bugs beat roadmap curiosity.

## Next Task

Execute `g03.001` — capture the first post-alpha stabilization batch: triage
release-window bug reports, correct any overstated claims, and tighten the
published install/runtime posture where needed.
