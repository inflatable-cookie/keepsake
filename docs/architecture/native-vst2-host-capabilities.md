# Native VST2 host capabilities

Status: active
Owner: Inflatable Cookie
Updated: 2026-08-06
Vision refs: `docs/vision/001-keepsake-vision.md`
Contract: `docs/contracts/008-native-vst2-host-capability-policy.md`

## Decision

Keepsake must not publish a same-architecture VST2 as CLAP when the receiving
host can already load that VST2 directly. It must continue to publish VST2s
that require bridging, such as Intel VST2s in an Apple Silicon host.

Automatic suppression has two independent gates:

1. Product evidence confirms that the DAW supports both CLAP and native VST2
   on the current platform and major-version line.
2. Keepsake positively identifies the exact DAW, scanner, engine, or plug-in
   host process currently enumerating its CLAP factory.

Product support alone is not enough. A guessed helper-process identity could
hide the only loadable representation of a plug-in. Unknown processes retain
the operator's `vst2_native` configuration.

## Research scope

This matrix classifies every product in the public
[CLAPDB Hosts/DAWs index](https://clapdb.tech/category/hostsdaws), plus
source-backed additions found during the same pass, as checked on 2026-08-06.
The CLAP project calls CLAPDB the most current public source while warning that
host lists cannot be guaranteed complete. New, private, and unlisted hosts
therefore remain possible.

`Confirmed` means first-party material demonstrates both formats. It does not
mean runtime suppression is enabled. Runtime activation additionally requires
verified process identity evidence.

## Conventional DAWs

| DAW | Minimum CLAP line | Both formats | Confirmed platforms | Runtime identity | Evidence |
|---|---:|---|---|---|---|
| Bass Studio | 0.6.4 | Confirmed | Windows, Linux x86_64 | Pending | [Product page](https://bass-studio.com/) names VST2, VST3, and CLAP. |
| Bitwig Studio | 4.3 | Confirmed | macOS, Windows, Linux | Active on macOS | [Current guide](https://www.bitwig.com/userguide/latest/the_dashboard/) exposes CLAP-over-VST and VST3-over-VST2 preferences. |
| FL Studio | 24 | Confirmed | macOS, Windows | Pending | [Official format guide](https://www.image-line.com/fl-studio-learning/fl-studio-beta-online-manual/html/plugins_supported.htm) names VST1/2 and CLAP on both desktop platforms. |
| Metro | 7.6 | Confirmed | macOS, Windows | Pending | [Product site](https://www.sagantech.com/) documents VST2; CLAP line is indexed by CLAPDB. Re-verify before activation. |
| Miditronic | Current | Provisional | Windows | Pending | [Vendor history](https://ultradaw.com/history/) records VST2 and later CLAP support, but product/platform wording is not precise enough for runtime activation. |
| MultitrackStudio / Lite | 10.4.1 | Confirmed | macOS, Windows | Pending | [Manual](https://www.multitrackstudio.com/manual.pdf) documents VST hosting and VST2-to-CLAP state conversion. |
| MuLab | 9.2 | Confirmed | macOS, Windows | Pending | [Official guide](https://www.mutools.com/info/M9/docs/mulab/using-vst-plugins.html) explicitly names VST2, VST3, and CLAP. |
| n-Track Studio | 10.2 | Confirmed | macOS, Windows, Linux desktop | Pending | [Current manual](https://ntrack.com/help/manual.html) documents CLAP/VST loading and VST2 project state. Verify the scanning process per platform. |
| Ongenet | Current | Confirmed | macOS, Windows, Linux | Pending | [Product page](https://onge.net/) explicitly names CLAP, LV2, VST2, VST3, and AU hosting. |
| Qtractor | 0.9.27 | Confirmed | Linux | Pending | [Official site](https://www.qtractor.org/) explicitly names native VST2 and CLAP. |
| REAPER | 6.71 | Confirmed | macOS, Windows, Linux | Active on macOS | [Official format list](https://www.reaper.fm/about.php) explicitly names VST2 and CLAP. |
| Studio One Pro / Fender Studio Pro | 7 / 8 | Confirmed | macOS, Windows, Linux | Active for Studio Pro 8 on macOS | [Official Linux guide](https://support.presonus.com/hc/en-us/articles/19214558269581-Linux-Getting-Started) names VST2, VST3, and CLAP paths. Existing Studio One identities remain pending. |
| UltraDAW | Current | Confirmed on Windows | Windows | Pending | [Quick-start guide](https://ultradaw.com/software/ULTRADAW_quick_start_en.pdf) names VST2, VST3, and CLAP. The Linux announcement only claims CLAP and VST3. |
| Zrythm | 1.0 beta | Confirmed | Published desktop builds | Pending | [Current manual](https://manual.zrythm.org/en/plugins-files/plugins/scanning.html) explicitly names CLAP and VST2. |

## Current CLAPDB entries not eligible for suppression

| Product | Classification | Reason |
|---|---|---|
| Anklang | Unconfirmed | Current public material documents CLAP/LV2; no current VST2-host claim was found. |
| blockhead | Unconfirmed | CLAP hosting has changed during development and no reliable VST2-host claim was found. |
| Dilonardo Audio Tools | Does not support VST2 | The [vendor states](https://dilonardo.com/Contents/Software/Tools/) that VST2 was removed and replaced by CLAP. |
| EXT64 | Unconfirmed | CLAP is indexed, but current first-party VST2-host evidence was insufficient. |

These products must not be treated as native-VST2-capable without new
evidence. If an exact process identity is later proven to lack native VST2,
Keepsake may classify it as `Unsupported` and force native wrapper exposure.

## Host applications that are not conventional DAWs

The same policy also matters to modular and meta-host applications, but they
stay outside the DAW list:

| Host | Both formats | Evidence |
|---|---|---|
| Carla | Confirmed | The [maintainer's project index](https://github.com/falkTX) names VST2, VST3, and CLAP hosting. |
| Element | Confirmed | The [product page](https://kushview.net/element/) names CLAP, LV2, VST, VST3, and AU. |
| Plogue Bidule | Confirmed | [Bidule documentation](https://www.plogue.com/bidule/help/ch05.html) documents VST2; the CLAP host is listed by the CLAP project. |

## Verified macOS process identities

These identities were read from installed application bundles on 2026-08-06.
They are the only product rows currently activated by Keepsake on macOS.

| Product | Bundle identifier | Executable role |
|---|---|---|
| Studio Pro 8 | `com.fender.studioapp` | Main application |
| Studio Pro 8 | `com.fender.plugscannerapp` | Plug-in scanner |
| REAPER | `com.cockos.reaper` | Main application |
| REAPER | `com.cockos.reaperhostx8664` | Intel plug-in host |
| REAPER | `com.cockos.reaperhostarm64` | Apple Silicon plug-in host |
| Bitwig Studio | `com.bitwig.studio` | Main application |
| Bitwig Studio | `com.bitwig.studio.plugin.host32` | Architecture-specific plug-in host |
| Bitwig Studio | `com.bitwig.studio.engine` | Architecture-specific audio engine |

Executable names are only a fallback when no bundle identifier exists. A
non-empty, unknown bundle identifier always wins over a coincidentally matching
executable name.

## Identity capture on other platforms

Windows and Linux builds capture the executable filename of the process loading
Keepsake. These identities are emitted once during factory initialization when
the host remains `Unknown`. No Windows or Linux suppression entries are active
yet: the diagnostic exists to collect the real main, scanner, engine, and
plug-in-host identities needed for fixtures without guessing from product
branding.

## Maintenance rule

Before adding a runtime identity:

1. Re-confirm both format claims for the platform and major-version line.
2. Capture the identity from the real process that loads or scans
   `keepsake.clap`.
3. Add a classifier fixture for the exact identity.
4. Confirm bridge-required VST2s remain published.
5. Record the evidence date here.

Do not infer scanner identities from application branding or process names.
