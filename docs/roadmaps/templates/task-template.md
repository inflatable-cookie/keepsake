# <NNN> - <Task Title>

**Type: TEMPLATE** -- Copy to `docs/roadmaps/gNN/NNN-<slug>.md` and fill in for each executable task.

Status: draft
Owner: <owner>
Created: YYYY-MM-DD
Governing refs: <architecture files>, <contract files>
Depends on: <gNN.NNN or none>

## Outcome

State the exact bounded outcome for this task.

## Ready-State Rubric

- [ ] Objective is bounded enough to finish without fresh planning decisions.
- [ ] Governing refs point at current canonical surfaces.
- [ ] Scope, acceptance criteria, validation, evidence, and stop conditions are explicit.
- [ ] Review oracle below is present when acceptance is high-risk, universal, exact, or negative; otherwise explicitly noted as not required.
- [ ] Continuation envelope is explicit; the next task is ready if auto-start is enabled.
- [ ] No unresolved planning gaps or operator intent checkpoints.

## Decisions

Record provisional design the task settles, or write `None`.

## Dispatch manifest

- **State:** <ready when the rubric above holds; one lane, named siblings or none, no automatic successor unless explicit>
- **Completion:** <observable done state plus required validation>
- **Owned mutable paths:** <exact paths this task may edit>
- **Reserved closeout surfaces:** <front doors or indexes owned by another lane, if any>
- **Worker:** <capability pool; frontier justification or none>
- **Excluded:** <explicit non-goals>
- **Escalation:** <who owns semantic or compatibility decisions>

## Work

1. <ordered step>
2. <ordered step>

## Acceptance and review oracle

| Invariant | Adversarial counterexample | Required proof |
| --- | --- | --- |
| <claim> | <smallest falsifying case> | <test/check/evidence> |

## Stop conditions

- Stop on planning gaps, contract contradictions, or failed evidence gates.
- Ask for operator intent if an unresolved planning branch or generation choice appears.

## Evidence

On completion, record: outcome, validation actually run, PR link, reviewed exact head, merge commit, and material limits or blockers.

## Next task

State the next ready task or promotion step unlocked by this task, or where Chatterbox planning resumes.
