# Keepsake

Keepsake is a standalone C/C++ CLAP plugin that bridges VST2, VST3 and AU v2
plugins, including 32-bit binaries, through isolated helper processes. It is an
Inflatable Cookie product under LGPL v2.1, separate from Signal and Loophole.
It must never use or reference the Steinberg VST2 SDK, and it must never stop
being a CLAP plugin.

## Where things live

- Current state: `docs/README.md`
- Knowledge (one owner per fact): `docs/knowledge/README.md`
- Retired concepts, which must not come back: `docs/knowledge/retired.toml`
- Open questions: `docs/knowledge/questions.md`
- Install and build guides: `docs/setup/README.md`

Tasks, briefs, status and papercuts live in Queue, never in this repository.

## Commands

Route by job; do not run a startup ritual.

- `effigy tasks` — discover repository selectors.
- `effigy graph explore "<question>" --json` — understand ownership, flow or
  impact; use `effigy graph affected` after a change.
- `effigy doctor` — diagnose repository health or selector ambiguity.
- `effigy test --plan` — inspect test shape when a test selector is available.
- `effigy qa` — run the configured docs and Northstar checks.
- `effigy demo:supported-proof` — run the primary repo proof suite.

Prefer `effigy <selector>` over raw tools when it covers the operation. Use
`--repo <PATH>` only when deliberately targeting another repository.

## Product rules

- VST2 uses VeSTige only. Never use, reference, vendor or redistribute the
  Steinberg VST2 SDK.
- Stay a CLAP plugin. The VST3 SDK is used only inside the bridge subprocess,
  and its GPLv3 boundary must be resolved before any public VST3 support claim.
- 32-bit bridging is first-class: targets are macOS x86_64/arm64, Windows
  x86_64 and Linux x86_64, with platform limits stated honestly — macOS 10.15+
  cannot host 32-bit binaries at all.
- Public support claims trail evidence. `v0.1-alpha` supports macOS + REAPER +
  VST2; Windows, Linux, VST3, AU v2 and 32-bit stay experimental until the
  validation matrix says otherwise.
- Keepsake stays standalone: no legacy bridge code in Signal, and no
  Signal/Loophole runtime dependency here.
- Hosts get the same CLAP contract and no host-specific runtime seam. Keepsake
  exposes no private screenshot or companion API.
- Full boundaries: `docs/knowledge/contracts/legal-boundaries.md`.

## Guardrails

- Do not edit `.github/workflows/` or run release mutations without an explicit
  operator request.
- When a change alters what is true, update the owning knowledge file in the
  same PR.
- An operator ruling given in conversation goes into its owning file before the
  thread ends.
- Write in `docs/knowledge/contracts/writing-style.md`: short, blunt, high
  signal.

## Papercuts

File small, recurring friction in Queue with `papercut.add` (see the
`northstar` skill). The repository holds no papercut file or triage folder.

## Validate

`effigy qa` before opening a PR.
