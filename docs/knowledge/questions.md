# Questions

Questions that block or shape work. Reference them by ID from the plan and from
briefs. An answered question keeps only its pointer to where the answer lives.

## Q-001 — Does the diagnostic macOS IOSurface preview lane stay or go?

Status: open
The bridge-owned native editor is the supported macOS interaction model, and
`vst2-gui-preview-ui-state-smoke` exercises an IOSurface preview path that is
diagnostic-only. Keeping it costs maintenance and blurs the claim; removing it
is cleanup work with no release urgency. See
[architecture/macos-editor.md](architecture/macos-editor.md) and the
triage note.

## Q-002 — Is shared-process crash recovery still wanted?

Status: open
[process-isolation-policy.md](contracts/process-isolation-policy.md) defers
restarting a crashed shared bridge process and re-initialising surviving
instances. Decide whether to build it or write it out of the contract.

## Q-003 — Which Windows and Linux hosts anchor the `v0.2.0` matrix?

Status: open
The `v0.2.0` envelope targets Windows x64 and Linux x64 as co-primary
platforms, but no host set is chosen yet. See
[architecture/native-vst2-host-capabilities.md](architecture/native-vst2-host-capabilities.md)
and plan.

## Q-004 — Do AU v2 and public 32-bit support land in `v0.2.x` or later?

Status: open
Both have code and partial evidence, and both sit outside the current
`v0.2.0` operator scope unless the validation matrix forces a deferral. See
plan.
