# Built-In Surfaces

Lookup for Effigy **built-ins** (not manifest task names). Run `effigy --help`
for the live list. Use `effigy <topic> --help` for flags.

## Default agent loop

| Built-in | First use |
|----------|-----------|
| `doctor` | Health + routing on entry |
| `tasks` | Task inventory |
| `test` | Test plan (`--plan`) and execution |
| `graph` | Code understanding (`explore`, `affected`) |
| `<selector>` | Repo work the manifest defines |

Details: `agent-operating-loop.md`, `graph-assist.md`.

## Manifest selector runtime

Managed selectors are repo tasks, not built-ins. A task with `mode = "tui"`
also supports `--headless` / `EFFIGY_MANAGED_HEADLESS=1` plus task-local
`status`, `logs [process] [--follow]`, and `stop` companions.

## Discovery and execution

| Built-in | Purpose |
|----------|---------|
| `tasks` | List catalogs/tasks; `tasks --resolve`; `tasks status` |
| `doctor` | Health checks; `doctor <selector>` explain mode; running-workspace ownership diagnosis |
| `test` | Built-in test orchestration (`--plan`, `--tui`) |
| `defer` | Run `[defer]` fallback explicitly |
| `watch` | File-triggered task reruns (`--owner` required) |
| `scan` | Repo scanners (`god-files`, `attention-markers`, …) |
| `config` | Inspect merged manifest; schema snippets; `config get/set` |
| `config completion` | Shell completion + selector candidates |
| `deps` | Inspect, link, and unlink full Cargo/Bun local dependency closures |

## Code graph

| Subcommand | Purpose |
|------------|---------|
| `graph index` | Build/refresh `.effigy/graph/graph.db` |
| `graph status` | Freshness trust (`freshness.state`) + counts |
| `graph explore` | One-call agent navigation packet |
| `graph affected` | Post-edit validation narrowing |
| `graph context` | Lower-level ranked context items |
| `graph search` | FTS term lookup |
| `graph node` / `callers` / `callees` / `impact` | Symbol neighborhoods |
| `graph watch` | Foreground incremental refresh (streaming JSON) |

Trust states on `graph status --json`: `ready`, `refresh-recommended`,
`degraded`, `missing-index`. Reindex when not `ready` and `usable` is false.

Guide: `docs/guides/076-code-graph-and-agent-workflows.md`

## Local runtime

| Built-in | Purpose |
|----------|---------|
| `container` | Compose/colima/docker lifecycle, data, cache, volume |
| `system` | Default system substrate (VM + compose + gateway) |
| `workspace` | System up + dev shell |
| `gateway` | Host DNS/TLS for container routes |
| `service` | Catalog inspect/extract |
| `exec` | One-shot command in dev workspace container; primary-service workspace identity; no TTY for non-console callers |
| `bootstrap` | Clone/bring-up repo from git URL |

## Data, deploy, and proof

| Built-in | Purpose |
|----------|---------|
| `state` | Layered schema/seed/capture stacks |
| `deploy` | Model, export, plan/apply transactions |
| `artifact` | OCI/local data artifacts |
| `demo` | Proof demos (list, run, browser, history) |
| `bundle` | Bundle source inspect/sync |
| `secrets` | Vault init/set/list/doctor/**import** |

## Release and quality

| Built-in | Purpose |
|----------|---------|
| `release` | Gates, prepare/execute, verify-install, distribution evidence |
| `changelog` | Validate/format/analyze/extract changelog |
| `docs` | Link/JSON/index/workflow-path QA checks |
| `contracts` | JSON contract validation |
| `init` | Repo setup wizard; `--check`, `--checklist`, `--apply` |
| `tasks migrate` | Import `package.json` scripts |
| `tasks unlock` / `tasks cache` | Lock recovery; task cache |

## Distribution note

There is **no** top-level `effigy distribution` command. Distribution work lives
under `effigy release validate`, `release preflight`, `release proof`, and
`release evidence …`. Guide: `docs/guides/062-distribution-system-guide.md`.

## JSON mode

```bash
effigy --json <built-in>
```

Exception: `graph watch --json` streams `effigy.graph.watch.event.v1`.

Details: `json-envelope.md`, `docs/guides/017-json-output-contracts.md`.

## Command matrix

Full flags and schemas: `docs/guides/025-command-reference-matrix.md`
