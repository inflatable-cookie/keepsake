---
kind: northstar-handoff
title: "g02.007 — Adopt the Effigy-hosted lifecycle hook"
handoff_mode: worker-pr-loop
worker_mode: implementation
dispatch_authority: orchestrator
status: ready-to-launch
owner: Tom
created: 2026-09-13
updated: 2026-09-13
base_required: pushed-main
queue_dispatch: northstar-queue
queue_approval: "Tom approved one Queue task per Northstar project on 2026-09-13; existing project Chatterboxes are Queue origins only and must be disturbed only for escalated worker or coordinator attention."
queue:
  capability: general
  skipPRReview: false
---

## What This Thread Was Doing

The operator approved a portfolio rollout of Northstar's Effigy-hosted Queue
lifecycle configuration. This repository is in the compatible active-generation
batch.

## Why It Matters

The repository should gain deterministic hook-owned lifecycle state and closeout
without copying Northstar runtime code or coupling Queue to Northstar document
structure.

## Current State

- Canonical task: [g02.007](../roadmaps/g02/007-adopt-effigy-hosted-lifecycle-hook.md).
- Northstar source proof: 36dc197f32979b86edf9376bd256d362095a3ce4.
- Required repository changes are the two configuration files named by the task.
- Existing product sequencing remains authoritative.
- Queue origin is routing metadata only. Do not notify the origin at dispatch or
  closeout; escalate there only if the worker or coordinator needs operator input.

## Boundaries

Follow the task's owned paths, acceptance oracle, and stop conditions exactly.
Do not modify product code, existing product runway decisions, Queue or Effigy
source, CI/release surfaces, or any Paseo thread/workspace.

## Important Context

The Queue origin identifies the planning thread that should receive a genuine
escalation. It is not a dispatch or completion notification target. Existing
workers and coordinators retain their own Queue callbacks and evidence.

## Suggested Next Move

Create a worker branch from the pinned synchronized main, add the exact portable
configuration, validate it, open a PR, obtain independent exact-head review,
merge, then let the required v2 closeout hook publish terminal state and consume
this handoff.

## Completion Protocol

The task completes only when Queue records the accepted implementation and
review, merges the PR, and the Effigy-hosted task.closeout hook publishes the
terminal lifecycle record and declared projections. No agent-authored closeout
commit is permitted.
