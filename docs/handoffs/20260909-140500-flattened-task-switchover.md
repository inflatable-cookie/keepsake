---
kind: northstar-handoff
title: "Flatten Northstar tasks and compact historic generations in keepsake"
handoff_mode: worker-pr-loop
worker_mode: implementation
dispatch_authority: orchestrator
status: closed
base_required: pushed-main
queue_dispatch: northstar-queue
queue_approval: "The operator authorized Chatterbox on 2026-09-09 to orchestrate the flattened-task migration across projects without Orchestrator-tagged Paseo threads, and explicitly required Northstar Queue for dispatch."
queue:
  capability: general
  skipPRReview: false
---

## What This Thread Was Doing

Run the one-time Northstar flattened-task switchover in `keepsake`. Compact
safely closed historic generations, flatten the active generation from
milestone plus nested batch cards to one top-level Northstar task per
`gNN.NNN`, and land the migration through the normal reviewed PR loop.

## Why It Matters

Northstar now has one execution level. The generation README owns the roadmap
and approved frontier; `docs/roadmaps/gNN/NNN-<slug>.md` is the sole executable
planning unit. Keeping milestone wrappers and nested `batch-cards/` leaves two
competing queues and prevents reliable lifecycle compaction.

## Current State

- Integration checkout: `/Users/tom/Dev/projects/keepsake` on clean, synchronized `main` at the commit
  containing this handoff.
- This repository has no active Paseo workspace labelled `Orchestrator` in the
  dispatch inventory. The operator reserved all Orchestrator-managed projects
  for manual migration.
- The installed Northstar skill and the canonical operator prompt at Northstar
  commit `d6b65e0` define the flattened generation-plus-task model.
- Before mutation, inspect the project queue and all active workers, reviewers,
  PRs, handoffs, and worktrees. Finish every submitted old-format record
  through accepted merge and closeout. If one cannot close, stop with one
  decision-changing blocker and leave its authority paths intact.

## Boundaries

This message authorizes bounded documentation, planning, instruction-surface,
template, and local-checker repair needed for the migration. It authorizes
removal of superseded milestone and batch-card structures only after their
current meaning and evidence are preserved.

Do not change product code, release state, workflows, or provider settings; do
not start a new product lane, abandon queued work, roll the generation, create
compatibility aliases, or preserve dual authority. Do not archive, delete,
rename, detach, stop, or otherwise modify any pre-existing Paseo workspace or
agent. Northstar Queue owns only the migration workspace and agents it creates.

## Important Context

Use the currently installed Northstar skill. Confirm its project-refresh and
lifecycle-maintenance surfaces say:

- the generation README owns the roadmap and approved frontier;
- `docs/roadmaps/gNN/NNN-<slug>.md` is the sole executable planning unit;
- the unit is a Northstar task referenced as `gNN.NNN`;
- no active milestone wrapper or nested `batch-cards/` hierarchy is supported.

If the installed skill still teaches the old model, stop. Do not reconstruct
the migration from memory.

First compact historic generations. Inventory every expanded generation and
its inbound links; classify it as active, safely closed, or unresolved from
content and front doors. Freeze a preservation manifest before deletion. Move
live rules and open commitments to active authority, retain material evidence,
write non-procedural `docs/roadmaps/archive/gNN.md` roll-ups, rewrite current
links, and delete only safely closed trees named in the manifest. Leave
unresolved or parallel-active generations intact with an explicit disposition.
Do not modernize terminology in historical roll-ups, logs, closed handoffs, or
immutable queue records.

Then flatten the active generation. Freeze an old-path/ID to new-task map.
Absorb a milestone and its card when they form one remaining outcome. Preserve
independent ready, blocked, or unresolved cards as separate top-level tasks,
keeping the milestone ID for the first genuine owner and assigning later IDs
in dependency order. Collapse completed groups only when outcome, evidence,
limits, and dependencies have durable destinations. Preserve every unresolved
unit's scope, governing refs, dependencies, acceptance oracle, validation,
ownership, dispatch boundary, evidence, and stop conditions. Stop for an
operator ruling when ownership, order, ID, or evidence destination is
ambiguous.

Make the generation README the single roadmap and frontier. Rewrite current
front doors, active planning references, live instructions, local templates and
checkers, and unsubmitted handoffs atomically. Remove consumed milestone
wrappers, legacy templates, and the active generation's `batch-cards/`
directory. Keep “queue task” and “Effigy task” distinct from “Northstar task.”

## Suggested Next Move

Perform the preflight and queue census, freeze both preservation manifests,
then execute historic compaction and active-generation flattening as one
reviewable documentation migration. Keep operator notifications to one
planning blocker or the final result; omit routine progress reports.

## Completion Protocol

Prove all current front doors agree on the active generation, active task or
explicit absence, and approved frontier. Prove every `gNN.NNN` is unique and
matches its filename and live references; no active executable surface depends
on `batch-cards/`, milestone wrappers, dual status, or an old submitted
handoff; every removed path is in the manifest; current links resolve; open
commitments remain reachable; and material evidence remains traceable.

Run repository-native docs checks, normal QA required for docs changes, and
`git diff --check`. Repeat lifecycle/currentness inventory and prove it is
idempotent. Open one PR, obtain independent exact-head review, then let
Northstar Queue merge, synchronize `main`, publish canonical closeout, and
retire only the queue-owned migration threads/workspace. Final report must give
historic classifications, preservation manifest, old-to-new mapping, exact
changes, validation/review evidence, retained exceptions, new frontier, and
whether normal dispatch resumed.

## Closeout

Status: closed

PR #3 was merged into `main` at
`ee834e722fe5cffbda54426e7ec9c23c187f829c` after the accepted exact-head
review at
<https://github.com/inflatable-cookie/keepsake/pull/3#issuecomment-5602528248>.
The merged change is the docs-only Northstar flattened-task switchover
described above. Its closeout record is
`docs/logs/2026-09/09-142635-northstar-flattened-task-closeout.md`.

The approved next pointer is unchanged: no task is active; define
`g02.007+` when the operator is ready to spec `v0.2.0`.
