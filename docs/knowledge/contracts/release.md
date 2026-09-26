# Release

How Keepsake ships a version. Releases are binary artifacts built by CI from a
tag; the release procedure is the ordered steps below, and the release notes
are the product document at `docs/releases/<version>.md`.

Release mutations (tagging, publishing, changing the release page) need an
explicit operator instruction. Nothing here runs on its own.

## Versioning

- Tags use `v{label}`: `v0.1-alpha`, `v0.2.0`.
- The build version is the numeric changelog version (`v0.1-alpha` → `0.1.0`),
  recorded in `CHANGELOG.md`.
- `CHANGELOG.md` is the changelog source; the release config lives in
  `release/effigy.release.toml`.
- Suffixes `alpha`, `beta` and `rc` publish as GitHub prereleases.

## What is built

`.github/workflows/release-binaries.yml` is the artifact source of truth. It
builds three targets and packages each:

| Target | Artifact | Layout |
| --- | --- | --- |
| macOS arm64 | `keepsake-macos-arm64-<label>.zip` | `keepsake.clap` bundle with helpers under `Contents/Helpers/` |
| Linux x64 | `keepsake-linux-x64-<label>.tar.gz` | `keepsake.clap` plus adjacent `keepsake-bridge` |
| Windows x64 | `keepsake-windows-x64-<label>.zip` | `keepsake.clap` plus adjacent `keepsake-bridge.exe` |

The workflow runs the release gates (QA, build, smoke) before packaging, reads
the release notes from `docs/releases/<label>.md`, and creates or updates the
GitHub release with the artifacts plus a checksum manifest.

A local dry-run package is available with `effigy release:candidate:alpha`,
which writes `dist/<label>/` including `SHA256SUMS.txt`. Local output is a
rehearsal, not the release.

## Steps

1. **Scope freeze.** Confirm the support envelope and that no release prose
   claims more than the validation matrix defends. Confirm `CHANGELOG.md` and
   `docs/releases/<label>.md` describe the target commit.
2. **Validate the target commit.** `effigy qa` passes, release gates are green,
   and the latest commit has green CI.
3. **Write the release notes** at `docs/releases/<label>.md`, and update the
   support matrix and [known issues](../../known-issues-v0.1-alpha.md) where
   evidence moved.
4. **Build artifacts.** Dispatch or tag `.github/workflows/release-binaries.yml`
   and confirm the run is green. Note the run id and artifact names.
5. **Verify the artifact, not the tree.** Install from the packaged artifact on
   the primary platform, launch REAPER, confirm a representative bridged plugin
   appears, its editor opens, and short transport playback works.
6. **Publish.** Create the tag and let the workflow create the GitHub release;
   confirm artifacts and the checksum manifest are attached.
7. **Verify the release page** renders with the right support scope,
   experimental lanes labelled experimental, and install instructions present.

## Verify

- The tagged commit's CI and release-binaries runs are green.
- `docs/releases/<label>.md` is the notes body on the release page.
- The artifact set and `SHA256SUMS.txt` match the workflow run.
- A packaged-artifact install on the primary lane passes the step 5 checks.

## Roll back

- An artifact or release-note error is fixed by re-running the release-binaries
  workflow for the same tag; it updates the existing release in place.
- Do not move or delete a published tag. If a published release must be
  withdrawn, mark it and record why; fix forward with the next version.
- For a bad publish that never became public, delete the draft/unpublished
  release and re-dispatch.
