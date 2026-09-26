# Windows editor architecture

How Keepsake opens a legacy VST2 editor inside a Windows host. The shape below
is what the REAPER smoke lane is host-safe and playable with for APC and Serum,
the two primary Windows GUI regression plugins. It is current truth for the
Windows bridge (`src/bridge_gui_stub_windows.cpp`, `src/plugin_gui.cpp`,
`src/bridge_loader_vst2.cpp`), not an experiment list.

## Deferred staged embedded open

The host must never block synchronously on bridge-side editor open. APC and
Serum both wedge or time out when the CLAP host waits inside the request path
for `effEditOpen()` to return. The working design removes that wait:

1. `gui_set_parent()` only **stages** the host parent handle in the bridge and
   returns quickly. It does not open the editor.
2. The bridge **owns a stable Win32 editor surface** (wrapper plus panel)
   before plugin open, and attaches it to the host parent with `SetParent()`,
   rather than creating an ad-hoc host child at `EDITOR_SET_PARENT` time. A
   pre-created surface must start life as a popup/tool window and only become a
   child on attach.
3. `gui_show()` sends `EDITOR_OPEN`, but the bridge only **queues** the staged
   embedded open and returns OK.
4. The real embedded open (`gui_open_editor_embedded_impl()`) runs on the next
   bridge GUI-loop pass (`gui_idle()`), after the synchronous `gui_show()` RPC
   has returned.

This ordering is what lets the host promote its wrapper to visible
(`style=0x50000000`, `visible=1`) before `effEditOpen()` runs, which is when
APC and Serum open successfully. Opening during `gui_set_parent()`, or opening
synchronously inside the `gui_show()` RPC, leaves the wrapper at
`style=0x40000000`, `visible=0`, and the editor never opens cleanly.

## Audio keeps flowing during editor open

In `src/bridge_loader_vst2.cpp`, audio-side `effProcessEvents` and
`processReplacing` must not wait behind the same `effect_mutex` while
`effEditOpen()` is in progress. Without that narrow exception the bridge is
host-safe but silent, because editor open starves the audio path. The exception
is deliberately limited to the editor-open window.

## Safety policy

- A failed embed must **abandon that bridge instance** rather than wedge the
  host or retry another risky GUI path on the same instance. The host stays
  responsive even when embedded open fails.
- Do not force the host wrapper visible. `ShowWindow()`/`UpdateWindow()` on the
  host's wrapper can block before `effEditOpen()` starts; host-window
  visibility is an observation, not a control knob.
- Do not suppress CLAP processing from the CLAP side while `gui_set_parent()`
  waits on `EDITOR_SET_PARENT`. That guard regressed the lane.
- `KEEPSAKE_WIN_EMBED_MODE` (`main`, `hybrid`, `window`) exists only to compare
  call-stack ownership in the smoke lane. It is a diagnostic switch, not three
  shipped architectures.

## References and rules

- JUCE and yabridge are architectural references for the "own a stable editor
  surface before open" shape. Do not copy them literally.
- No per-plugin hacks, override tables or special cases for APC or Serum.
- VST2 stays VeSTige-only; see
  [legal-boundaries.md](../contracts/legal-boundaries.md).
