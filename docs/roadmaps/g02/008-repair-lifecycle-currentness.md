# g02.008 — Repair lifecycle currentness

Owner: repository maintainers
Created: 2026-09-13
Governing refs: installed Northstar lifecycle currentness contract and portfolio repair route
UI classification: none

## Outcome

This repository has one mechanical lifecycle authority. Lifecycle-managed task files and declared projection targets carry no duplicate status headers or stale terminal-task frontier prose, and transient terminal-task handoffs have no durable backlink that would block safe closeout.

## Ready-State Rubric

- [x] The installed Northstar skill exposes `audit-currentness`.
- [x] The integration checkout is clean and synchronized with `origin/main`.
- [x] The read-only audit recorded exact structural violations.
- [x] The repair boundary excludes product files and semantic rewriting.

## Decisions

- Repair only findings emitted by `audit-currentness` and exact transient-handoff backlinks from the bounded inventory.
- Delete duplicate status header lines without changing surrounding semantic prose.
- Replace a stale terminal-task frontier value with task-free sequencing intent. Preserve Goal/State history.
- Repoint a transient-handoff backlink to a permanent task, contract, PR, commit, or log surface. The closeout hook alone deletes this task's submitted handoff.
- Return ambiguous meaning to Chatterbox untouched.

## UI Design Brief

Not applicable.

## Dispatch manifest

- **State:** ready; one documentation-only repair lane.
- **Owned mutable paths:** the exact files listed under Evidence, this task, and its submitted handoff.
- **Reserved closeout surfaces:** this task's lifecycle record, declared generated projection blocks, and deletion of the submitted handoff belong to the repository hook.
- **Worker:** automatic mechanical pool; independent exact-head review remains required.
- **Excluded:** product code, releases, generation rollover or compaction, new product planning, arbitrary prose cleanup, Queue/Effigy source, and Paseo thread/workspace disposal.
- **Escalation:** any finding requiring semantic judgment returns to the owning Chatterbox without edits.

## Work

1. Re-run `effigy skill run northstar/lifecycle:run -- audit-currentness --repo .` and confirm the inventory below.
2. Apply only the exact accepted removals or task-free frontier replacements.
3. Repair the exact terminal-handoff backlinks below, if any, by targeting a permanent evidence surface.
4. Prove the audit is clean, lifecycle projections verify, documentation checks and normal QA pass, and the diff contains no product files.
5. Land through Queue review and repository-hook closeout.

## Acceptance and review oracle

- `audit-currentness` reports `status: ok` with no violations.
- Lifecycle projection verification reports no drift.
- Every change outside this task/handoff is one listed mechanical repair; surrounding semantic prose remains intact.
- No durable tracked Markdown links to a terminal-task transient handoff.
- Repository docs checks, normal QA, and `git diff --check` pass.
- Exact-head independent review confirms no product or unrelated planning change.

## Stop conditions

Stop before editing when a stale pointer cannot be replaced without choosing product direction, a status-looking line carries semantic meaning, the audit differs materially from Evidence, the repository has concurrent conflicting documentation changes, or validation exposes a broader defect.

## Evidence

Read-only currentness findings:

- `docs/README.md` — `stale-frontier` in `Next Task` for `g02.007`
- `docs/roadmaps/README.md` — `stale-frontier` in `Next Task` for `g02.007`
- `docs/roadmaps/g02/README.md` — `duplicate-status-header` in `G02 — Alpha Release and Post-Alpha Stream`
- `docs/roadmaps/g02/README.md` — `stale-frontier` in `Next task` for `g02.007`

Transient-handoff backlink inventory:

- No terminal-task handoff backlink was found in the bounded inventory.

## Next task

Return to the existing project Chatterbox planning state after hook closeout. This repair authorizes no product successor.
