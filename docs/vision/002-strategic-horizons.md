# 002 - Strategic Horizons

Status: active
Owner: Inflatable Cookie
Updated: 2026-08-17
Vision refs: `docs/vision/001-keepsake-vision.md`

Atlas-shaped long-horizon runway. This is strategic direction and sequencing,
not a task queue. Milestones and batch cards live in `docs/roadmaps/`.

## Destination

Keepsake gives legacy plugins — VST2, VST3, AU v2, including 32-bit binaries —
a durable home in CLAP-capable hosts with crash isolation and honest support
claims. The long-term product is broader than any single release; each public
posture must stay provable.

## Strategic Direction (outcomes, not implementation)

- Legacy plugins appear as ordinary named CLAP entries with correct metadata.
- Crash isolation and bitness bridging are default behavior, not opt-in hacks.
- Legal and format boundaries stay explicit and permanent (VeSTige only for
  VST2; CLAP outer format; subprocess license boundaries for VST3).
- Public claims trail evidence — experimental lanes stay labeled until the
  matrix defends them.
- Keepsake remains a standalone Inflatable Cookie product; Signal integration
  stays optional and mostly out of this repo.

## Operator Decisions (2026-08-17)

Recorded operator commitments that shape horizon sequencing:

| Decision | Commitment |
|---|---|
| Next primary platforms | **Windows x64 and Linux x64** — co-primary expansion alongside the retained macOS primary lane |
| Next public envelope | **`v0.2.0`** — the next scope-widening release target (not a indefinite `v0.1.x` patch stream) |
| VST3 in that push | **Yes** — VST3 support is in scope for `v0.2.0`, subject to subprocess/GPL boundary and matrix proof |
| Generation posture | **`g02` stays open** — premature `g03` rollover absorbed; `v0.2.0` continues as `g02` milestones |

Deferred by operator silence (not rejected): AU v2 promotion, 32-bit release
claims, deeper macOS host coverage as a primary-lane expansion.

## Current Shape (2026-08)

| Surface | State |
|---|---|
| `v0.1-alpha` | Published; macOS + REAPER + VST2 is the primary validated lane |
| `g02` | Active — `001`–`006` complete; `007+` (`v0.2.0`) unauthored |
| `v0.2.0` target | Operator-owned; Win + Linux + VST3 — milestones not yet authored |
| macOS editor | Bridge-owned native window + passive host placeholder (contract 007) |
| Soundcheck seam | Managed `integrations/keepsake.toml` reader shipped (no live API) |
| Host capability policy | Contract 008 active; exact macOS process identities for a small host set |
| Windows / Linux | Code + CI exist; claims remain experimental until `v0.2.0` matrix |
| VST3 | Loader exists; GPLv3 subprocess boundary must govern any non-experimental claim |
| AU v2 / 32-bit | Code exists; not in `v0.2.0` operator scope unless matrix forces a deferral |
| Platform config | Runtime implemented; durable contract still thin |
| macOS IOSurface preview | Diagnostic-only; disposition on backlog |

Material contradictions resolved recently: isolation-config drift and glob
matching (`g02.006` card 002). No open architecture-vs-claim gap on the primary
lane.

## Horizon Model

### H0 — Post-alpha stabilization (`g02.006`, closed 2026-08-17)

**Outcome:** Shipped cards 001–002 (Soundcheck reader, isolation drift fix).
Further triage closed early — no active user base yet.

**Status:** closed. Resume stabilization only if real reports arrive.

### H1 — `v0.2.0` cross-platform release (next — unauthored)

**Outcome:** **`v0.2.0` published** with Windows x64 and Linux x64 as earned
primary platforms alongside macOS, and **VST3** in the supported envelope where
the validation matrix and license boundary allow. Install, config, and release
artifacts are credible on all three OS targets.

**Depends on:** operator-authored `g02.007+` milestones; platform config
promoted to contract; refreshed validation matrix for Win/Linux hosts and VST3
paths; explicit acceptance of VST3 GPLv3/subprocess license posture for public
claims; packaging and install surfaces per platform.

**Unlocks:** Honest multi-platform CLAP bridge claims beyond the alpha envelope;
foundation for format and bitness depth in later horizons.

**Excludes:** Claiming every implemented code path; AU v3; embedded macOS
cross-process input revival; non-experimental AU v2 or 32-bit unless matrix
evidence forces inclusion or explicit operator reopen.

**Review trigger:** matrix cannot defend Win + Linux + VST3 together after one
meaningful validation round — narrow the envelope rather than slip the version.

### H2 — Format depth (post-`v0.2.0`)

**Outcome:** Remaining formats move from experimental to earned support — AU v2
on macOS, broader VST2/VST3 parity, incremental macOS host capability
identities — without reopening core platform credibility.

**Depends on:** `v0.2.0` shipped; per-format validation batches; loader ABI
stability (contract 003 if VeSTige boundary drifts).

**Unlocks:** Format parity in factory and scan without special host support.

**Excludes:** Steinberg VST2 SDK; pretending macOS 32-bit is fixable on modern
macOS.

### H3 — 32-bit bridge proof

**Outcome:** 32-bit bridging is release-grade on Windows and Linux with
documented platform limits on macOS.

**Depends on:** H1 platform infrastructure stable; WoW64/multilib evidence;
bridge helper packaging.

**Unlocks:** Honest 32-bit support claims outside macOS.

**Excludes:** macOS 10.15+ 32-bit hosting.

### H4 — Ecosystem depth (mostly outside this repo)

**Outcome:** Optional Signal/Loophole integration tiers beyond "well-behaved
CLAP plugin"; Keepsake namespace as stable detection key.

**Depends on:** `v0.2.0` credibility; integration specs owned by Signal repo.

**Unlocks:** Deeper host affordances without legacy code in Signal.

**Excludes:** Bundling Keepsake with Signal; legacy bridge code in Signal.

### H5 — Maintenance generation rollover (`g03+`)

**Outcome:** New generation opens only after explicit closeout — live roadmaps
closed, specs tree purged, front doors agree.

**Depends on:** Northstar rollover policy in `docs/roadmaps/generation-index.md`.

**Unlocks:** Clean sequencing baseline for the next strategic phase.

## Strategic Bets and Trade-offs

| Bet | Upside | Cost / risk | Non-goal |
|---|---|---|---|
| Conservative claims | Trust, fewer support fires | Slower marketing story | Overclaiming breadth |
| Subprocess everything | Crash + license isolation | Complexity, latency | In-process VST3 loader |
| VeSTige-only VST2 | Legal precedent | ABI edge cases | Steinberg SDK |
| Win + Linux co-primary for `v0.2.0` | Real cross-platform product | Dual validation matrix load | One-OS-at-a-time forever |
| VST3 in `v0.2.0` push | Format value in one release | GPLv3 + subprocess complexity | Deferring VST3 indefinitely |
| `g02` continuity | No premature generation churn | Longer single generation | Rollover after every release |
| Exact host identity policy | Safe descriptor suppression | Incremental host coverage | Fuzzy host guessing |
| Soundcheck managed file only | Simple operator seam | No live companion API | HTTP discovery API |
| Bridge-owned macOS editor | Host-independent UX | Two-window model | Universal embedded input |

**Accepted uncertainty:** which Win/Linux hosts become matrix anchors; whether
AU v2 or 32-bit land in a `v0.2.x` follow-up vs H2/H3; timing of Signal
tier-2+ work.

**Irreversible choices already made:** CLAP outer format; VeSTige VST2 surface;
macOS embedded-input cutoff; superseded Soundcheck HTTP integration plan;
operator `v0.2.0` = Win + Linux + VST3; `g03` absorbed into `g02`.

## Runway (milestone transitions, not cards)

1. **Now:** `g02.006` closed — define **`g02.007+`** when operator specs
   `v0.2.0`.
2. **H1:** promote platform config contract; author Win/Linux packaging,
   validation matrix, VST3 license/claim boundary, per-platform install
   artifacts.
3. **H1 ship:** publish `v0.2.0` only when matrix defends Win + Linux + VST3
   together or a narrowed envelope is explicitly recorded.
4. **H1 → H2:** AU v2 and incremental format/host depth with contract updates.
5. **H2 → H3:** 32-bit evidence generation on Win/Linux.
6. **Parallel:** backlog disposition for macOS IOSurface preview; contract 003
   only if VeSTige loader boundary needs stabilization; reopen stabilization
   triage only on real user reports.

## Promotion Map

| Content | Destination |
|---|---|
| Long-horizon outcomes (this doc) | `docs/vision/` — here |
| `v0.2.0` milestones and batch cards | `docs/roadmaps/g02/` (`007+`) |
| System shape updates | `docs/architecture/` |
| Durable authority (config schema, VST3 license boundary) | `docs/contracts/` |
| Provisional Win/Linux/VST3 expansion plans | `docs/specs/` until promoted |
| Release envelope and matrix | `docs/releases/` |
| Evidence and closeout | `docs/logs/` |
| Deferred IOSurface disposition | `docs/roadmaps/backlog/` |

## Next Task

Define `g02.007+` milestone sequencing for `v0.2.0` when the operator is ready
to spec that lane.
