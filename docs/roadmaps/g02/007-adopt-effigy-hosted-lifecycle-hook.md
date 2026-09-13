# g02.007 Adopt the Effigy-Hosted Lifecycle Hook

Owner: repo maintainers
Created: 2026-09-13
Governing refs: installed Northstar lifecycle contract and Queue control v2
Depends on: no other Queue task
UI classification: none

## Outcome

This repository adopts Northstar's configuration-only Queue lifecycle route.
Queue invokes the installed or project-local Northstar skill through the
operator-approved Effigy runner. The repository carries configuration and
generated lifecycle state, with no copied hook runtime or host-specific path.

## Ready-State Rubric

- [x] The operator approved one rollout task for every Northstar project.
- [x] Northstar's Effigy-hosted hook completed its live self-hosting proof.
- [x] The host has an enabled, healthy trusted runner named effigy.
- [x] This task is configuration-only and does not change product priority.
- [x] Existing Queue work is represented by explicit dispatch dependencies.
- [x] UI classification is none.

## Decisions

- Commit the current paseo.queue.control.v2 manifest from Northstar's
  copy-ready lifecycle starter.
- Commit one repository-specific projection target file. It declares
  docs/README.md, docs/roadmaps/README.md, and
  docs/roadmaps/g02/README.md, with g02 active.
- Keep executable hook code, schemas, runner paths, digests, and host approval
  out of this repository.
- Queue dispatch, review, merge, and closeout stay unchanged. Once merged,
  task.closeout must run through effigy skill run northstar/queue:hook
  --stdio passthrough, publish the terminal lifecycle record and projections,
  and consume the exact handoff.
- Existing generation runway text continues to own product sequencing. This
  maintenance task authorizes no sibling product work and no generation
  rollover or compaction.

## UI Design Brief

Not applicable.

## Dispatch manifest

- **State:** ready after this planning commit is pushed.
- **Completion:** implementation and independent exact-head review pass; PR
  merges; the required v2 closeout hook publishes the terminal record, refreshes
  the three declared projections, and deletes the exact submitted handoff.
- **Owned mutable paths:** .paseo/queue.json and
  .northstar/lifecycle/v1/projection-targets.json.
- **Reserved closeout surfaces:** .northstar/lifecycle/v1/tasks/g02.007.json,
  generated projection blocks in the three declared targets, and deletion of
  the submitted handoff belong exclusively to the Queue hook after merge.
- **Worker:** automatic adequate general implementation pool; reviewer must use
  an independent provider/model identity.
- **Serial edges:** no Queue dependency; it does not reorder the product runway.
- **Excluded:** product code or behavior; copied Northstar runtime; absolute host
  paths or runner digests; Queue, Effigy, CI, release, roadmap restructuring,
  generation rollover/compaction, or thread/workspace mutation.
- **Escalation:** stop before merge if effigy is unavailable, the Northstar
  skill cannot resolve uniquely, the starter manifest differs from the frozen
  v2 route, or the existing repository shape needs more than the two owned
  configuration files.

## Work

1. Read the installed Northstar lifecycle reference and the current copy-ready
   files template-bundle/lifecycle/queue.json and
   template-bundle/lifecycle/projection-targets.json from Northstar commit
   36dc197f32979b86edf9376bd256d362095a3ce4 or its byte-equivalent installed
   release.
2. Add .paseo/queue.json with the exact v2 trusted-runner hooks. Do not add a
   repository launcher or copied hook payload.
3. Add .northstar/lifecycle/v1/projection-targets.json, retaining the two
   standard front doors and adding docs/roadmaps/g02/README.md; set
   active_generation to g02.
4. Validate both JSON files, confirm no absolute path or executable hook payload
   entered the repository, run git diff --check, and run the repository's
   advertised documentation/QA selector through Effigy.
5. Open the PR and report through Queue. After merge, make no manual closeout
   edit: the required v2 hook owns terminal publication and handoff cleanup.

## Acceptance and review oracle

| Invariant | Adversarial counterexample | Required proof |
| --- | --- | --- |
| Queue stays document-system agnostic | Queue receives Northstar task/path semantics | Manifest contains only generic events, modes, paths, and the opaque Effigy selector |
| Northstar remains portable | A local launcher, copied TypeScript runtime, or absolute install path appears | Diff contains only the two declared JSON configuration files |
| Projections cover current authority | Active generation or either front door is absent | Target file names exactly all three paths and g02 |
| Runner invocation is exact | Manifest adds --path, --json, a shell, or mutable executable lookup | Program is trusted runner effigy with argv ["skill","run","northstar/queue:hook","--stdio","passthrough"] |
| Missing prerequisites fail closed | Worker adds a manual or agent closeout fallback | Required hooks stay required; no alternate closeout route is introduced |
| Product sequencing stays intact | Adoption rewrites the approved frontier or starts another task | Product files and existing runway text are unchanged apart from this planning entry |
| Live closeout proves adoption | An agent edits lifecycle state or the handoff survives terminal publication | Queue hook creates the terminal record/projections and consumes this exact handoff |

## Stop conditions

Stop if adoption requires product changes, a copied runtime, an absolute path,
Queue or Effigy source edits, a manual closeout, weakening a required hook, or
roadmap restructuring. Preserve the task and escalate the exact incompatibility.

## Evidence

Northstar g03.010 completed the live Effigy-hosted lifecycle closeout at
36dc197f32979b86edf9376bd256d362095a3ce4. This repository has no Queue
control manifest or lifecycle state. The rollout therefore needs only the
portable manifest and repository-specific projection declaration.

## Next Task

After hook-owned closeout, return to the existing generation runway. Do not
change product priority or auto-start a successor.
