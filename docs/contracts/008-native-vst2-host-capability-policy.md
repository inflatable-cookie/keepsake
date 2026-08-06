# 008 - Native VST2 host capability policy

Status: active
Owner: Inflatable Cookie
Updated: 2026-08-06
Depends on: `docs/architecture/native-vst2-host-capabilities.md`, `docs/contracts/002-clap-factory-interface.md`
Affects: CLAP descriptor enumeration and `expose.vst2_native`

## Problem

Keepsake can expose a same-architecture VST2 as CLAP even when the receiving
DAW already loads that VST2 directly. That creates redundant plug-ins and makes
host-specific configuration leak into a global user setting. Suppressing by
name alone is also unsafe because DAWs commonly scan and load plug-ins in
helper processes.

## Contract

### Classification

The process requesting Keepsake's CLAP factory is classified as:

- `Supported`: positively identified host process whose product and platform
  support native VST2 and CLAP;
- `Unsupported`: positively identified CLAP host process whose product and
  platform do not support native VST2;
- `Unknown`: no exact, current evidence.

Product capability and runtime process identity are separate evidence gates.
Both must pass before classification becomes `Supported` or `Unsupported`.

### Descriptor exposure

- `Supported` forces `expose_vst2_native = false` for that process.
- `Unsupported` may force `expose_vst2_native = true` once the corresponding
  product and process identity are fixture-proven.
- `Unknown` preserves the operator's configured `expose_vst2_native` value.
- `expose_vst2_bridged` is independent. Host support for native VST2 must never
  suppress a VST2 that still requires Keepsake for architecture or bitness
  bridging.
- VST3 and AU exposure are unaffected.

### Identity safety

- Prefer stable platform application identifiers over display names.
- On macOS, use the running process bundle identifier.
- On Windows and Linux, capture the exact executable filename. Until a real
  scanner/helper identity is fixture-proven for that platform, report it as
  `Unknown` rather than borrowing another platform's classification.
- Use an executable-name fallback only when the process has no bundle
  identifier.
- A present but unknown bundle identifier must not fall back to executable
  matching.
- Scanner, engine, and plug-in-host helpers require their own verified entries.
- Unknown hosts fail open to configuration; they do not silently lose
  descriptors.

### Evidence authority

`docs/architecture/native-vst2-host-capabilities.md` is the dated product and
runtime identity matrix. A product row marked `Confirmed` is not automatically
an executable classifier entry.

## Validation

- Exact main, scanner, and helper identities classify as expected.
- Case differences do not change classification.
- An unknown bundle with a familiar executable name remains `Unknown`.
- A process without a bundle identifier may use the exact executable fallback.
- Unknown Windows and Linux processes expose their executable identity for
  diagnosis while preserving configured descriptor exposure.
- A `Supported` process suppresses only same-architecture VST2 descriptors.
- An unknown process preserves configuration.
- Host policy resolution is a pure decision over host support plus the two
  configured VST2 exposure flags; it cannot mutate VST3 or AU exposure.

## Risks

- Host updates can rename helpers or change bundle identifiers.
- Public format support may differ by platform or product edition.
- A stale positive is more damaging than a stale unknown because it can hide
  the only usable plug-in representation.

The runtime table therefore expands only from captured process evidence, not
from product-name inference.
