# macOS editor architecture

The supported macOS editor posture, and why it is the one in the tree.

## The problem

Keepsake can render a bridged plugin's editor into the host window over
IOSurface, and that render path works: crop and geometry alignment can be made
correct, and some editors — Serum-class VSTGUI editors in particular —
interact partially. But JUCE-based editors such as APC and Khords still fail a
universal embedded-interaction bar even after substantial input-delivery work.
The exhausted approaches were attach-target and parent-healing variants,
responder-chain selection, `NSPanel` versus `NSWindow`, offscreen versus visible
bridge windows, `NSEvent`-based mouse synthesis, and `CGEvent`-based mouse
synthesis.

Cross-process embedded bitmap plus injected AppKit input is therefore not a
dependable universal macOS interaction contract. This is an accepted cutoff,
not an open question.

## The decision

The product direction is a **bridge-owned interactive editor window** paired
with a **passive host-owned placeholder**:

- Keepsake advertises a non-floating Cocoa CLAP GUI and attaches a
  non-rendering placeholder to the host's parent view.
- The real legacy editor opens in the bridge-owned native window, which is the
  strongest proven interaction lane in REAPER across Serum, APC and Khords.
- The host view stays open when the editor closes and offers a reopen action.
- The IOSurface embedded preview stays in tree as an operator diagnostic only.
  It is not the supported interaction posture.

The interface rules are owned by
[macos-native-editor-and-host-placeholder.md](../contracts/macos-native-editor-and-host-placeholder.md).

## Options considered

- **A — Render-only embed plus interactive remote-window fallback.** Preserves
  the IOSurface work but keeps two editor modes and does not solve universal
  embedded interaction.
- **B — Bridge-owned interactive window (chosen).** Gives up true embed as the
  mainline path in exchange for dependable interaction; matches the strongest
  proven lane.
- **C — Stronger embedded host/bridge contract.** Different event transport or
  framework-specific hooks. Highest research risk; the evidence says it becomes
  framework-specific and stops being universal.
- **D — Format/framework-scoped support claims.** Honest and low-risk, used
  regardless, to keep public claims aligned to actual behaviour.

Option B is the default macOS UI stance, paired with Option D for messaging.
Option A's rendering baseline is retained only as a diagnostic.

## The 2026-07 companion experiment

A CARemoteLayer transport could be established but rendered black. A later
ScreenCaptureKit experiment rendered an Intel editor into Soundcheck's host
view, but needed a dedicated helper, receiver dylib, frame accumulator, input
protocol, focus emulation and Soundcheck-specific lifecycle handling; JUCE input
stayed unreliable and other editors shimmered. That experiment is closed. Its
executable, library, protocol and product integration surfaces are removed.
ScreenCaptureKit remains useful only for a host's generic screenshot of the
real native window.

## Decision gate

Do not resume remote presentation or synthetic input without a new architecture
decision and a substantially different mechanism. The product path is the
native editor plus a non-rendering host placeholder with one native-editor
reopen action.
