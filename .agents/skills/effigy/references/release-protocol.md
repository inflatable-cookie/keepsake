# Release Protocol

> **Interim placement.** A dedicated `effigy-release` skill is planned. Until
> it ships, this reference holds the strict release rules.

## Top rule

**Do not run release commands without explicit human instruction.** Releases
have public side effects — tags, GitHub releases, distribution manifest
updates — and a wrong release is hard to recover from cleanly.

See also `footguns.md` rules 1–4.

## Read-only release commands (safe to run unprompted)

Use these for inspection, planning, and reporting:

| Command | What it does |
|---------|--------------|
| `effigy release simulate` | Dry-run the entire release flow |
| `effigy release status --check-gates` | Show current gate states |
| `effigy release prepare --plan` | Preview prepare step |
| `effigy release execute --plan` | Preview execute step |
| `effigy release gates` | List release gates |
| `effigy changelog extract --version X.Y.Z` | Extract changelog section |

## Mutating release commands (require explicit human ask)

Never run these unprompted:

| Command | Side effect |
|---------|-------------|
| `effigy release prepare --yes` | Writes prepare artifacts |
| `effigy release execute --yes` | Commits prepared files and pushes the annotated tag |
| `gh workflow run release-binaries.yml -f tag=vX.Y.Z` | Starts binary publication for the immutable tag |
| `effigy release verify-install --tag vX.Y.Z` | Effigy binary network-side verification; not for library or service repos |

## Canonical sequence

When a human explicitly asks for a release:

1. Confirm the clean candidate commit is pushed to `main`, then record
   `candidate_sha=$(git rev-parse HEAD)`.
2. `gh workflow run ci.yml --ref main`
3. Find the `workflow_dispatch` run whose `headSha` equals `$candidate_sha`,
   then run `gh run watch <RUN_ID> --exit-status`.
4. `effigy release simulate`
5. `effigy release status --check-gates`
6. `effigy release prepare --plan`
7. `effigy release prepare --yes --check-gates`
8. `effigy release execute --plan`
9. `effigy release execute --yes`
10. Run the target repo's declared publication and consumer verification.
    - Effigy itself: `gh workflow run release-binaries.yml -f tag=vX.Y.Z`
      followed by `effigy release verify-install --tag vX.Y.Z`.
    - Library or service repos: use their repo-owned consumer smoke. Do not run
      Effigy's fixed binary verifier.
11. `effigy changelog extract CHANGELOG.md --version X.Y.Z`

Use this query to select the run; never substitute a merely recent green run:

```sh
gh run list --workflow ci.yml --branch main --commit "$candidate_sha" \
  --event workflow_dispatch --limit 1 \
  --json databaseId,headSha,status,conclusion,url
```

Effigy's configured `ci` release gate checks the same exact-SHA invariant.
Missing, pending, red, or different-commit evidence blocks every gate-checked
preview and prepare. Local release gates then validate deterministic release
file mutations; they do not replace hosted CI on the candidate source.

If any step fails, **stop**. Surface the failure to the human. Do not retry
with bypass flags.

`release verify-install` is not a generic release closer. It installs the
`effigy` Cargo package and runs Effigy CLI checks against a fixture repo.
Invoking it from a non-Effigy root is a routing error, not evidence that the
target library or service tag is broken.

## Failed release recovery

If `release execute` fails partway through:

1. **Do not re-tag.** The original tag may already be on the remote.
2. Identify the underlying cause from gate output or error envelope.
3. Add a `Fixed` entry to `CHANGELOG.md` under `[Unreleased]` describing the
   problem.
4. Bump the next PATCH version.
5. Run the standard release flow for the new version.

The broken release stays in history; consumers who pulled it learn the fix
landed in the next PATCH.

## CI workflow files

`.github/workflows/` files gate the release pipeline. **Never modify them
without explicit human approval.** A silent edit can:

- Skip a required gate.
- Leak secrets.
- Break artifact uploads.
- Corrupt the distribution manifest.

If a workflow change is needed, propose it to the human and let them apply.

## Full spec

- `docs/guides/049-ci-binary-distribution-and-release-protocol.md` — CI
  policy, distribution rules, install protocol.
- `docs/guides/051-release-orchestration.md` — release command sequence,
  manifest format, gate definitions.
