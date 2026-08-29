# Contracts

Use this folder for explicit non-code contracts that constrain behavior.

## Files

- [`contract-index.md`](contract-index.md) — register of all active contracts
- [`001-working-rules.md`](001-working-rules.md) — execution grammar, done-ness, and autonomy rules
- [`002-clap-factory-interface.md`](002-clap-factory-interface.md) — CLAP
  descriptors, IDs, and factory lifecycle
- [`004-ipc-bridge-protocol.md`](004-ipc-bridge-protocol.md) — subprocess IPC,
  shared memory, and crash handling
- [`006-process-isolation-policy.md`](006-process-isolation-policy.md) — bridge
  isolation modes, overrides, and managed settings
- [`007-macos-native-editor-and-host-placeholder.md`](007-macos-native-editor-and-host-placeholder.md) — non-rendering host view with native-editor reopen control plus bridge-owned editor on macOS
- [`008-native-vst2-host-capability-policy.md`](008-native-vst2-host-capability-policy.md) —
  exact host identity gates for native VST2 suppression

## Rule

Contracts should be stable reference artifacts and link to relevant roadmap/log
evidence. Roadmap work should not proceed until the required contract exists and
is listed in the contract index.

Contracts are the hard-definition surface for behavior, interfaces, policies,
and other durable rules that should not live only in provisional specs.

For execution work in this repo, `001-working-rules.md` is the anchor contract.
Start there.

## Next Task

Promote the platform config schema into its own contract when `g02.007+`
milestones for `v0.2.0` are authored.
