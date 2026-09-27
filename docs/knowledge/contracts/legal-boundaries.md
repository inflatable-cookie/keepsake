# Legal, licence and trademark boundaries

Owner: Inflatable Cookie. These boundaries are permanent product constraints,
not implementation choices. A change that would cross one is a stop-and-raise
condition; see [working-rules.md](working-rules.md).

## VST2: VeSTige only

Keepsake's VST2 ABI surface is [VeSTige](https://github.com/LMMS/lmms/blob/master/plugins/vst_base/vestige/aeffect.h),
a clean-room reverse-engineered header implementing the VST2 ABI, originally
written by Javier Serrano Polo, LGPL v2.1, used by LMMS for over 20 years. A
copy is vendored under `vendor/`.

The Steinberg VST2 SDK is **not used, not referenced, and not redistributed**,
in any form, including as an internal-only dependency. Steinberg:

- discontinued the VST2 SDK in October 2018 and closed all new licence
  agreements at that date;
- states on record that *"new products supporting VST2 are not allowed"*;
- states that *"a licence agreement is also required if the only use of the
  VST2 technology is for internal purposes"*;
- has issued DMCA takedowns for VST2 SDK distribution, though never
  successfully against VeSTige.

Sources:

- https://forums.steinberg.net/t/vst-2-sdk-discontinued/201774
- https://forums.steinberg.net/t/can-i-create-vst-2-support-for-host-application-vst-3-license/202012
- https://steinbergmedia.github.io/vst3_dev_portal/pages/FAQ/Licensing.html

Open-source precedent: LMMS and Ardour have both shipped VeSTige-based VST2
hosting for over 20 years under GPL/LGPL without successful enforcement. The
RustAudio/vst-rs crate — the Rust community's canonical VST2 reference — was
archived in March 2024 with the explicit note that a VST2 distribution licence
is no longer obtainable; the Rust audio ecosystem has conceded the commercial
hosting question. Keepsake follows the separate LGPL open-source host model.

Keepsake's own licence, LGPL v2.1, matches the VeSTige lineage.

## CLAP is the outer format, permanently

Keepsake is a CLAP plugin. Its outer format stays CLAP.

The VST3 SDK licence explicitly states: *"This Agreement neither applies to the
development nor the hosting of VST2 Plug-Ins."* A VST3 wrapper used to host
VST2 would therefore create a licence conflict. CLAP is MIT-licensed and has no
such exclusion, which is why Keepsake's outer format choice is permanent and
non-negotiable for legal reasons, not merely architectural preference.

## VST3: subprocess licence boundary

Keepsake hosts VST3 plugins with the [VST3 SDK](https://github.com/steinbergmedia/vst3sdk)
(GPLv3 or Steinberg proprietary). The VST3 loader runs in a separate
subprocess, so the licence boundary sits at the process/IPC edge. VST3 code
must not bleed into the main plugin process.

GPLv3 compatibility with the main LGPL v2.1 binary, and the exact public claim
it permits, must be resolved before VST3 support is claimed. See
[native-vst2-host-capability-policy.md](native-vst2-host-capability-policy.md)
and the plan for the current VST3 posture.

## AU v2: Apple system framework

AU v2 plugins are hosted through Apple's public AudioToolbox framework, which
is available on every macOS system and raises no special licensing concern. AU
v2 (Component Manager) is the target; AUv3 app extensions are deferred unless a
real need appears.

## Trademark

"VST" is a registered trademark of Steinberg Media Technologies GmbH (US
registrations 75584165 and 79047426; EU EUIPO 000763367).

- Keepsake does not use the VST Compatible logo.
- Keepsake does not claim Steinberg certification or affiliation.
- "VST" is not part of Keepsake's name.
- References to "the VST2 binary plugin format" are descriptive and nominative
  only.

Attribution used wherever these references appear: *VST is a registered
trademark of Steinberg Media Technologies GmbH.*

## Licence

GNU Lesser General Public License v2.1 — see [`LICENSE`](../../../LICENSE).
If Keepsake is incorporated into a non-LGPL product, the LGPL terms apply to
the Keepsake components.
