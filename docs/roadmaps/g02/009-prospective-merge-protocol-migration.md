# g02.009 — Prospective-merge protocol migration

Owner: repository maintainers
Created: 2026-09-16
Governing refs: Northstar g03.020; Queue Spec 015
UI classification: none

## Outcome

keepsake's Queue control manifest uses `paseo.queue.control.v4` and evaluates the
required pre-merge hook against the exact prospective merge candidate.

## Ready-State Rubric

- [x] Northstar g03.020 is terminal at `f34e1c0`.
- [x] Three portfolio canaries completed the full Queue lifecycle.
- [x] The installed public migration dry-run accepts this repository exactly.
- [x] Tom authorized the portfolio rollout on 2026-09-16.

## Dispatch manifest

- **State:** ready; configuration maintenance independent of product work.
- **Owned mutable paths:** `.paseo/queue.json` only.
- **Worker:** automatic mechanical/general pool with independent review.
- **Excluded:** product code, dependencies, releases, CI, product sequencing,
  Queue state and thread/workspace disposition.

## Work

Run the installed migration dry-run, apply it with `--write`, prove the exact
two-value one-file diff, validate it, and confirm an idempotent replay.

## Acceptance and review oracle

Write mode reports `applied`, replay reports `unchanged`, the v4 manifest is
valid, and no file except `.paseo/queue.json` changes.

## Stop conditions

Stop on divergent input, dirty base, extra changed paths, missing installed
command or validation failure. Never hand-edit around a refusal.

## Next task

Return to the existing project frontier. This task authorizes no product
successor.
