# System architecture

Keepsake is one `.clap` binary (plus helper binaries) that exposes a CLAP
plugin factory. The factory returns one descriptor per discovered legacy
plugin — VST2, VST3, AU v2 — so each appears as a distinct, named CLAP plugin.
Plugins load through format-specific loaders in isolated subprocesses, which
gives both crash isolation and bitness bridging. The architecture is broader
than any current release claim; support claims come from validation, not from
the existence of a code path.

## Component layout

```
keepsake.clap
  ├─ CLAP plugin factory
  │    One descriptor per discovered legacy plugin, carrying name, vendor,
  │    version and feature tags. IDs follow keepsake.<format>.<uid>
  │
  ├─ Format loaders
  │    ├─ VST2 loader (VeSTige ABI, LGPL v2.1)
  │    ├─ VST3 loader (VST3 SDK, GPLv3 — subprocess-isolated)
  │    └─ AU v2 loader (AudioToolbox — macOS only)
  │
  ├─ Plugin scanner / cache
  │    Scans configured paths per format at startup and caches results so
  │    the factory answers immediately. Rescan is triggerable via
  │    preferences or config file.
  │
  └─ Out-of-process bridge
       Isolation modes: shared, per-binary, per-instance (default).
       Crash isolation: a crashed process silences and errors the
         instances it hosts.
       Bitness bridging: helper binaries selected by plugin architecture.
       IPC between the CLAP process and the loader subprocesses.

keepsake-bridge (64-bit helper, same architecture as the .clap)
  └─ Hosts 64-bit plugins in an isolated process.

keepsake-bridge-x86_64 (cross-architecture helper)
  └─ Hosts x86_64 plugins on an arm64 macOS host.

keepsake-bridge-32 (32-bit helper, where the platform supports it)
  └─ Hosts 32-bit plugins, bridged to the 64-bit main process.
```

## Key seams

| Seam | Surface | Notes |
| --- | --- | --- |
| VST2 ABI | VeSTige header (LGPL v2.1, vendored) | No Steinberg SDK. Clean-room only. |
| VST3 ABI | VST3 SDK (GPLv3 or proprietary) | Subprocess only; licence boundary at the process/IPC edge. |
| AU v2 ABI | AudioToolbox (macOS system framework) | macOS only. No special licensing. |
| CLAP plugin interface | CLAP SDK (MIT) | Outer format. |
| IPC / subprocess model | Pipe protocol + shared memory | Governed by [ipc-bridge-protocol.md](../contracts/ipc-bridge-protocol.md); shared bridges multiplex instances. |
| Bridge helper binaries | `keepsake-bridge`, `keepsake-bridge-x86_64`, future `keepsake-bridge-32` | Native and cross-arch helpers; 32-bit still needs release-grade proof. |
| Scan path config | config and cache files per platform | Runtime implemented; schema documented in [config-reference.md](../../setup/config-reference.md). |
| Host capability policy | product matrix + exact runtime identity | Suppresses same-architecture VST2 descriptors only in positively identified CLAP hosts that already support VST2. Governed by [native-vst2-host-capability-policy.md](../contracts/native-vst2-host-capability-policy.md). |
| macOS editor posture | Passive host placeholder plus bridge-owned native editor window | Every normal CLAP host gets the same Cocoa parent view; rendering and input stay in the native window. Governed by [macos-native-editor-and-host-placeholder.md](../contracts/macos-native-editor-and-host-placeholder.md). |
| Windows editor posture | Deferred staged embedded open with a bridge-owned Win32 surface | The host never waits synchronously on bridge-side editor open. See [windows-editor.md](windows-editor.md). |

## Platform notes

- **macOS** — x86_64 and arm64. Rosetta 2 is required for x86_64 plugins on
  Apple Silicon. macOS 10.15+ cannot host 32-bit plugins at all; this is a
  platform limitation.
- **Windows** — x86_64. 32-bit plugins run through WoW64 with the 32-bit bridge
  helper.
- **Linux** — x86_64. 32-bit plugins run through multilib with the 32-bit
  bridge helper.

## Execution-relevant surfaces

| Surface | Type | State |
| --- | --- | --- |
| `keepsake.clap` binary | Deliverable | Implemented |
| CLAP plugin factory | Code | Implemented; per-format descriptors |
| VeSTige loader | Code | Implemented; VeSTige only |
| VST3 bridge loader | Code | Implemented; release proof partial |
| AU v2 bridge loader | Code | Implemented; release proof partial, macOS only |
| Scanner and cache | Code | Implemented; per-format scan with cached metadata and rescan |
| Out-of-process host | Code | Implemented; shared / per-binary / per-instance isolation |
| IPC bridge | Code | Implemented; pipe plus shared-memory protocol |
| macOS host placeholder and native editor | Code | Implemented; validation active |
| macOS IOSurface preview path | Code | Implemented, diagnostic-only; not part of the supported interactive lane |
| Platform config and cache files | Config | Implemented; release-grade schema contract still pending |
| Native VST2 host classifier | Code + policy | Implemented on macOS; identity coverage incremental |
| Build system | Tooling | Implemented; CMake and CI on macOS, Windows, Linux |
| REAPER smoke harness | Tooling | Implemented; guarded real-host lane on macOS |
| Alpha known-issues surface | Release | Governs the published alpha caveats |

## Ownership

| Owner | Owns | Does not own |
| --- | --- | --- |
| Keepsake | CLAP descriptors, scan/cache, bridge lifecycle, non-rendering host placeholder and native-editor reopen action, bridge-owned native editor window, stable editor title | Host screenshot UI, Screen Recording permission, host-specific plugin resolution, Soundcheck lifecycle |
| CLAP host | Normal CLAP loading, host editor window, parent `NSView`, generic discovery and capture of auxiliary plugin windows | Keepsake bridge internals, legacy plugin input synthesis |
| Soundcheck | The same CLAP host contract as any other host; generic native-window screenshots for all applicable plugins | A Keepsake-only app, dylib, helper protocol, or alternate plugin-loading topology |
| Legacy plugin | Native editor rendering, input, modal windows, plugin-driven resize | Host placeholder and screenshot policy |
| macOS | AppKit windowing, ScreenCaptureKit, TCC permission | Product-specific window selection policy |

Keepsake must stay useful in any conforming CLAP host without host-specific
code. A host may use public plugin IDs and generic host facilities, but must
not become a runtime dependency or privileged companion. Screenshot flow: the
host opens Keepsake through ordinary CLAP GUI calls, Keepsake attaches its
placeholder and opens the native editor, the host observes the new auxiliary
window, and the host captures it through its general screenshot system. No
captured frame returns to Keepsake or the CLAP parent view.

## Signal integration

Signal integrates with Keepsake as a well-behaved CLAP host: no special code is
needed for bridged plugins to appear in its plugin browser. Keepsake's stable
plugin ID namespace (`keepsake.<format>.*`) is the detection key for deeper,
optional integration, which belongs in the Signal repository. Keepsake does not
depend on Signal.

| Tier | Capability | Signal change |
| --- | --- | --- |
| 1 | Bridged plugins appear with correct names | None — works through the CLAP factory |
| 2 | Detect Keepsake by known plugin ID | Small — one ID check at scan time |
| 2 | Rescan trigger in Signal settings | Small — calls a Keepsake rescan |
| 2 | "Legacy / VST2" badge on bridged plugins | Small — flag on plugin metadata |
| 2 | First-run hint when VST2 files exist but Keepsake is absent | Small — detection plus one-time notice |
| 3 | VST2 scan-path configuration in Signal preferences | Medium — forwarded to Keepsake config |
| 3 | Browser grouping by source format | Medium — browser data model |
| 3 | Crash-isolation reporting for a downed bridge | Medium — CLAP error state surfacing |

## Prior art

- LMMS VeSTige integration — 20+ year reference for VeSTige usage.
- Carla — closest reference for a multi-format plugin factory model.
- Ardour — VeSTige-lineage reference for VST2 hosting.
