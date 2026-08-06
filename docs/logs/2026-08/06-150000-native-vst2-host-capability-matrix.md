# Native VST2 host capability matrix

Date: 2026-08-06
Posture: strict-ready

## Changed

- Classified every DAW in the current CLAPDB host index, plus source-backed
  additions, against native VST2 support.
- Separated product-format evidence from exact runtime process identity.
- Added contract 008 for host-aware descriptor exposure.
- Activated captured macOS identities for Studio Pro, REAPER, and Bitwig,
  including their scanner, engine, and plug-in-host helpers.
- Kept unknown hosts on the configured fallback.

## Risks retained

- The public CLAP index explicitly cannot guarantee global completeness.
- Several confirmed products still lack captured scanner identities.
- Platform support differs for UltraDAW and may differ across other product
  editions or future major versions.
- No Windows or Linux process identities are activated yet.

## Validation

- `cmake --build build --target host-capabilities-test keepsake -j 8`
- `ctest --test-dir build -R '^host-capabilities$' --output-on-failure`
- `effigy qa:docs`

## Follow-on: cross-platform identity capture

Windows and Linux now capture the executable filename loading Keepsake and emit
one bounded `native-vst2=unknown` factory diagnostic. They deliberately remain
unclassified until real per-platform scanner/helper identities are captured and
fixture-proven. macOS bundle classification is unchanged.

Host-aware exposure resolution is now a pure tested decision. A supported host
suppresses only same-architecture VST2 descriptors, bridge-required exposure is
preserved exactly, and an unknown host preserves both configured flags.

All passed. The broader `effigy doctor` posture still reports the repository's
pre-existing god-file findings; it did not govern this focused batch.

## Next task

Capture the real CLAP enumeration identities for the remaining installed or
fixtureable macOS DAWs before activating their confirmed product rows.
