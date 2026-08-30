# Selector Routing

A **selector** is the string the user types after `effigy` to identify a task
or built-in target: `test`, `api/test`, `qa:ci:fast`, `web/build`. Effigy
resolves tasks to one catalog. Built-ins such as `test` use the same catalog
prefixes without becoming manifest tasks.

Routing precedence, top to bottom (first match wins):

1. **Alias prefix** — colon-prefixed names (`qa:`, `release:`,
   `prepush:`) match defined aliases first.
2. **Path prefix** — slash-prefixed names (`api/test`, `web/build`) match
   the workspace at that path.
3. **CWD-nearest** — when the selector is bare (`test`), Effigy finds the
   workspace nearest to the current working directory and uses its task.
4. **Shallowest match** — when CWD doesn't disambiguate, the workspace
   closest to the repo root wins.

## Worked example

Repo layout:

```
.
├── effigy.toml                    # declares api = "api", web = "web"
├── config/tasks.toml            # defines `check`, `qa:ci:fast`
├── api/
│   └── effigy.toml               # configures `[test.suites]`
└── web/
    └── effigy.toml               # configures `[test.suites]`
```

The root declaration is explicit:

```toml
[catalog.members]
api = "api"
web = "web"
```

| User runs (CWD) | Resolves to |
|-----------------|-------------|
| `effigy test` (in repo root) | root built-in test plan |
| `effigy test` (in `api/`) | `api/` built-in test plan |
| `effigy api/test` (anywhere) | `api/` built-in test plan |
| `effigy qa:ci:fast` (anywhere) | root `qa:ci:fast` (alias prefix) |

## Disambiguation

When a selector resolves somewhere unexpected, run:

```bash
effigy doctor <selector> --
```

This shows the routing decision tree — which catalogs were considered, which
matched, and why one won.

## When to stop and ask

If `effigy doctor <selector> --` returns multiple candidates with no clear
winner, **stop and ask** the user which scope they meant. Don't guess.

Common ambiguity causes:

- Two workspaces define the same task name with no path prefix.
- A workspace was added recently and its `effigy.toml` isn't yet in the
  effective catalog membership (run `effigy doctor` for shared evidence).
- A task is defined as both an alias and a workspace task.

## Full spec

`docs/guides/016-task-routing-precedence.md` in the Effigy repo has the
complete spec including catalog inheritance, alias resolution edge cases,
and routing-related JSON envelopes.
