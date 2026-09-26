# Vision

Keepsake gives legacy plugins a home in modern CLAP hosts. One `.clap` plugin
exposes every legacy plugin it finds — VST2, VST3, AU v2, including 32-bit
binaries — as its own named CLAP plugin entry, carrying the original plugin's
name, vendor, version and feature tags. Each runs in an isolated helper
process, so a bad plugin produces silence and an error state instead of taking
the host session down, and 32-bit plugins are bridged to a 64-bit host
automatically. The user installs it once; the host needs no special support.

The guiding principle: these plugins are not legacy baggage to be tolerated.
They are tools with genuine value that deserve to keep working.

## Why it exists

- **VST2** — Steinberg discontinued the SDK in October 2018 and closed new
  licence agreements, so a host cannot add VST2 support directly. Useful VST2
  plugins still exist and many will never be ported.
- **32-bit plugins** — increasingly orphaned as hosts and operating systems
  drop 32-bit support. Many valuable tools will never get 64-bit ports.
- **Crash-prone plugins** — of any format, where process isolation keeps one
  bad plugin from taking down the session.

Signal (the audio engine behind Loophole) hosts CLAP natively but cannot host
VST2 directly, because it holds no pre-2018 Steinberg licence. Keepsake is the
separate product that does it:

- Signal ships no legacy bridge code. It hosts CLAP, and Keepsake is a CLAP
  plugin, so Signal's relationship with each format stays at its own native
  hosting boundary.
- Keepsake is an Inflatable Cookie product and a standalone open-source
  project, published separately under LGPL v2.1 and not bundled with Signal or
  Loophole.
- Users self-install, so the format implementations and their licence
  boundaries stay contained in Keepsake.

## What success looks like

- Legacy plugins (VST2, VST3, AU v2) appear in CLAP hosts with correct names,
  vendors and feature tags, with no special host support required.
- 32-bit plugins run through the bridge on a 64-bit host.
- A crash in a bridged plugin leaves the host session up.
- Keepsake builds on macOS, Windows and Linux from a clean checkout.
- No Steinberg VST2 SDK is present or referenced. VeSTige only for VST2.
- Keepsake is published under LGPL v2.1 with full source.

## Accepted trade-offs

| Bet | Upside | Cost or risk |
| --- | --- | --- |
| Conservative public claims | Trust; fewer support fires | Slower story about coverage |
| Subprocess isolation for everything | Crash and licence isolation | Complexity and latency |
| VeSTige-only VST2 | Legal precedent | VST2 ABI edge cases |
| CLAP as the outer format | No VST3 licence conflict | The format choice is permanent |
| Bridge-owned macOS editor window | Host-independent interaction | Two-window UX; no embedded input |
| Exact host identity for VST2 suppression | Never hides the only loadable plugin | Host coverage grows slowly |

## Not this

- Not proprietary; published under LGPL v2.1.
- Not affiliated with, endorsed by, or certified by Steinberg Media
  Technologies.
- Not a replacement for a proper native CLAP port of a legacy plugin.
- Not bundled with Signal or Loophole, and not a home for Signal's host
  integration code.
- Not a home for UI beyond the settings and preferences needed for scan paths,
  exposure and rescan.
- Not a place to overclaim: public support claims trail evidence.

## Name

*Keepsake: something kept or given to be kept as a memento.* The name reflects
the intent — these plugins are not legacy baggage to be tolerated, but tools
with genuine value that deserve to keep working. Checked clear of trademark and
product conflicts in the audio software space in April 2026; the one notable
clash considered and ruled out was "Heirloom" by Spitfire Audio.
