---
kind: northstar-handoff
title: "Retire the roadmap backlog in keepsake"
handoff_mode: worker-pr-loop
worker_mode: implementation
dispatch_authority: orchestrator
status: ready-to-launch
base_required: pushed-main
queue_dispatch: northstar-queue
queue_approval: "The operator authorized Chatterbox on 2026-09-09 to roll out the roadmap-backlog retirement across projects without Orchestrator-owned Paseo threads, using Northstar Queue."
queue:
  capability: complex
  skipPRReview: false
---

## What This Thread Was Doing

Run the one-time Northstar roadmap-backlog retirement in `keepsake`. Disposition
every item under `docs/roadmaps/backlog/`, remove the retired surface, and make
current project docs agree that roadmaps contain promoted executable tasks while
triage holds unresolved or deferred candidates until promotion.

## Why It Matters

Northstar retired the roadmap backlog because it duplicated triage and blurred
the boundary between a candidate and approved execution. Keeping both surfaces
leaves two intake queues and can turn migration into accidental authorization.

## Current State

- Integration checkout: `/Users/tom/Dev/projects/keepsake` on clean synchronized
  `main` at `66e38950f6aac5862076648bf1674e78555f9f6a` before this handoff-only commit.
- `docs/roadmaps/backlog/` exists and requires classification; do not assume its
  contents are disposable or executable.
- The flattened-task migration is closed for this repository where one was
  required. The operator states only Swallowtail and Poodle Lab are still in
  that migration, and both are outside this automatic queue lane.
- Canonical cleanup authority is Northstar commit
  `b8ce1b0da9b790ac28bf648983fc569e49fdf612`, file
  `bundle-docs/operators/retire-roadmap-backlog-prompt.md`.

## Boundaries

This handoff authorizes bounded documentation, planning, instruction-surface,
template, fixture, and local-checker changes needed for the cleanup. It permits
removing backlog files only after their current meaning has a truthful
manifested disposition.

Do not change product code, release state, workflows, dependencies, provider
settings, or product behavior. Do not start a new product lane, execute a
backlog candidate, abandon queued work, roll a generation, or invent task
approval. Do not archive, delete, rename, detach, stop, or otherwise modify any
pre-existing Paseo workspace or agent. Northstar Queue owns only the cleanup
workspace and agents it creates.

## Important Context

Read and follow the canonical retirement prompt named above. Before mutation,
inspect the project queue, active workers/reviewers, PRs, handoffs, and
worktrees. If unfinished work owns `docs/roadmaps/`, `docs/triage/`, or another
path this cleanup must change, stop with one decision-changing blocker rather
than editing around it.

Freeze a disposition manifest for every backlog item and inbound link:

- move unresolved or deferred current meaning into one unique timestamped
  triage note, preserving constraints, open questions, source references,
  promotion condition, and owner or next check when known;
- merge already-approved executable work into its owning top-level `gNN.NNN`
  task, or create a task only when existing planning authority makes scope,
  generation, dependencies, ordering, and frontier placement unambiguous;
- promote durable rules or accepted design to their canonical contract,
  architecture, policy, or other owning surface;
- remove implemented, superseded, duplicate, or useless material without
  creating placeholder notes.

Migration is not approval. Stop for an operator ruling when disposition or task
ownership is ambiguous. Keep clearly historical logs, archive roll-ups, closed
handoffs, immutable queue records, and quoted evidence unchanged unless they
contain a current broken link.

Then delete `docs/roadmaps/backlog/`, backlog-item templates, and other live
backlog scaffolding. Rewrite current front doors, doctrine, agent instructions,
templates, fixtures, checkers, and unsubmitted handoffs so roadmaps contain only
promoted executable tasks and triage stays non-authoritative. Leave no alias,
moved-to stub, empty directory, or dual terminology.

## Suggested Next Move

Perform the ownership preflight, freeze the disposition manifest, then apply the
cleanup as one reviewable documentation migration. Keep operator notifications
to one planning blocker or the final result; omit routine progress.

## Completion Protocol

Prove every removed item appears in the manifest and its current meaning is
reachable at one canonical destination or deliberately removed. Prove no live
executable surface, starter template, agent instruction, or checker requires a
roadmap backlog. Prove `find docs -type d -name backlog -print` returns nothing
except any explicitly classified non-Northstar path, triage remains
non-authoritative, current links resolve, and the approved frontier is
unchanged unless existing authority already required a correction.

Run repository-native docs checks, normal QA required for documentation
changes, and `git diff --check`. Open one PR, obtain independent exact-head
review, then let Northstar Queue merge, synchronize `main`, publish normal
closeout evidence, and retire only its own cleanup threads/workspace. Final
report must include the disposition manifest, exact files changed/deleted,
validation and review evidence, retained historical exceptions, and current
approved frontier.
