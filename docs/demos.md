# Proof tasks

Keepsake ships a small set of repo-owned proof tasks for its in-repo VST2
fixtures and host harnesses. They are plain Effigy tasks, so `effigy tasks`
lists them and `effigy doctor` resolves them.

List and run them with:

```sh
effigy tasks                 # every task, including the demo:* proof tasks
effigy demo:<name>           # run one proof task
effigy demo:supported-proof  # run the normal supported stack
```

## Supported Proof

These are the normal repo proof lanes for the tiny in-repo VST2 fixtures and
host harnesses.

| Task | What it proves |
|---|---|
| `demo:vst2-scan-smoke` | scan-path override, VST2 metadata extraction, CLAP factory exposure |
| `demo:vst2-host-audio-smoke` | instantiate, bridge launch, activation, process loop, audio path |
| `demo:vst2-host-threaded-smoke` | host main-thread lifecycle calls stay responsive during load/start |
| `demo:vst2-gui-smoke` | macOS live-window editor open, scripted input path, close, bridge shutdown |
| `demo:vst2-gui-param-state-smoke` | host-originated CLAP param flush, chunk save/load, state restore |

## Diagnostic Proof

This lane is intentionally not part of the supported normal posture.

| Task | What it proves | Why it is diagnostic-only |
|---|---|---|
| `demo:vst2-gui-preview-ui-state-smoke` | preview-path scripted UI click changes editor state and chunk contents | macOS preview / IOSurface is a diagnostic lane, not the supported interaction posture |

## Current Reading

- Treat `demo:vst2-gui-smoke` as the supported macOS GUI proof.
- Treat `demo:vst2-gui-preview-ui-state-smoke` as a narrow operator/debug proof
  for preview-path investigation.
- Do not treat the repo fixture proofs as a substitute for real-host REAPER
  validation on the published lane.
- The task comments in `demos/effigy.demos.toml` carry each task's proof
  statement and the artifact paths its tools write.
