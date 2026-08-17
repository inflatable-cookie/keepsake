# Inflatable Cookie Ownership Migration

Date: 2026-07-29
Status: complete
Posture: migration complete; strict docs posture retained

## Change

GitHub transferred Keepsake from `infinite-loop-audio/keepsake` to
`inflatable-cookie/keepsake`. The repository retained GitHub ID `1207235711`
and the `main` default branch.

The local checkout now uses:

```text
git@github.com:inflatable-cookie/keepsake.git
```

The product identity moved with the repository:

- Inflatable Cookie owns and publishes Keepsake.
- Keepsake remains a separately distributed LGPL v2.1 open-source product.
- Signal and Loophole do not bundle or depend on Keepsake.
- Runtime VST2 host-vendor responses and repo test fixtures now identify
  Inflatable Cookie.
- Current architecture, contract, roadmap, release, setup, and public docs use
  Inflatable Cookie authority and canonical Keepsake URLs.

## Historical Boundary

Dated logs retain Infinite Loop Audio names when they record the owner or
literal runtime output at that time. The original handoff decision to place the
repo under `infinite-loop-audio` is historical and superseded by this
migration.

Signal still lives at `infinite-loop-audio/signal` as of this migration, so its
live link was not rewritten to a nonexistent Inflatable Cookie repository.

## Validation

- GitHub API: `inflatable-cookie/keepsake`, repository ID `1207235711`,
  admin access
- `git ls-remote origin HEAD`: `e3a26144dbba161e575c9f575f6273f02b988cca`
- transferred `v0.1-alpha` release resolves at the new canonical URL
- transferred Release Binaries run `24552158082`: completed / success
- `effigy demo:build:vst2-gui-stack`: pass for native and Rosetta helpers
- `effigy qa`: pass
- `effigy qa:docs`: pass
- `effigy qa:northstar`: pass
- `effigy doctor`: pre-existing `scan.god-files` finding only; unrelated to
  the migration

## Next Task

Commit and push the ownership migration, then resume the active `g02.006`
stabilization lane.
