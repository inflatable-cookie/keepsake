# Config Shapes

Realistic snippets for the config sections an agent is likely to author or
modify. Not a full reference — see `docs/guides/025-command-reference-matrix.md`
for the complete schema.

Effigy splits config across:

- `effigy.toml` — project-level (catalogs, systems, containers, release).
- `config/tasks.toml` — task definitions (kept separate so task
  changes don't churn the project manifest).

**Tasks vs built-ins:** `[tasks]` defines ordinary selectors such as **`dev`** or
**`qa:ci:fast`**. Built-in commands (`test`, `init`, `doctor`, …) come from Effigy
itself; see `effigy --help` for the list.

## `[docs_policy.graph]`

This optional repository-owned profile teaches the local Markdown graph how to
classify documentation, resolve currentness, and name typed relations. It is
configuration consumed by `effigy graph index` and graph queries; it does not
ship a separate docs-context command.

```toml
[docs_policy.graph]
roots = ["README.md", "docs"]

[docs_policy.graph.fields.state]
labels = ["State"]
cardinality = "one"

[docs_policy.graph.fields.maintainer]
labels = ["Maintainer"]
cardinality = "one"

[docs_policy.graph.currentness]
field = "state"
current = ["current", "published"]
historical = ["historical", "retired"]

[docs_policy.graph.kinds.reference]
include = ["docs/reference/*.md"]
exclude = []
authority = 100
default-currentness = "unknown"

[docs_policy.graph.kinds.archive]
include = ["docs/archive/*.md"]
exclude = []
authority = 10
default-currentness = "historical"

[docs_policy.graph.relations.related]
labels = ["Related", "See also"]
headings = ["Related"]
```

Northstar consumers should keep their profile in the committed manifest emitted
by the Northstar starter; this generic example does not assume Northstar names.

The profile grammar and ranking rules live in
`docs/contracts/041-documentation-graph-profile-contract.md`; the architecture
decision is `docs/architecture/024-repository-defined-documentation-graph.md`.

## `[tasks]`

Tasks can be shell strings, refs to other tasks, or Rhai scripts. Examples:

```toml
[tasks]
# Shell string
"fmt:check" = "cargo fmt --all -- --check"

# Aggregator: chain of task refs
"qa:ci:fast" = [
  "cargo test",
  "cargo test --doc",
  { task = "qa:released-surface" },
  { task = "qa:ci:json" },
]

# Rhai script
"db:seed" = { rhai = "scripts/seed-db.rhai" }

# Rhai deploy plan wrapper
"deploy:uat:plan" = { rhai = "scripts/deploy-uat-plan.rhai" }

# Rhai distribution validation wrapper
"release:artifacts:check" = { rhai = "scripts/check-release-artifacts.rhai" }

# Mixed chain
"bootstrap:local" = [
  { rhai = "scripts/build-local-bin.rhai" },
  { rhai = "scripts/install-local-bin-links.rhai" },
]

# Cost ladder: cheap orientation -> focused gate -> full board
health = [{ task = "fmt:check" }]
validate = [{ task = "fmt:check" }, { run = "cargo check --workspace" }]
qa = [{ task = "validate" }, { task = "test" }, { task = "qa:docs" }]

# Task with explicit run block (for richer config)
[tasks."smoke:release"]
run = { rhai = "scripts/check-release-smoke.rhai" }
```

Keep `health` seconds-scale because `effigy doctor` delegates to it. Never
point `health` at `qa`, directly or through another task.

Managed multi-process tasks use the same selector surface. `start` controls
spawn order; `tab` controls presentation order:

```toml
[tasks.dev]
mode = "tui"
health_wait = true
health_wait_timeout_secs = 90
secrets = "required"
concurrent = [
  { task = "api", start = 1, tab = 2 },
  { run = "bun run web:dev", start = 2, tab = 1 },
]
```

Run `effigy dev --headless` or set `EFFIGY_MANAGED_HEADLESS=1` for an attached
supervisor without the TUI. Use `effigy dev status`, `logs [process]
[--follow]`, and `stop` from another shell. Readiness covers container-owned
routes started by the lifecycle entry. Forced local-dev secret unlock still
skips missing keys declared `required = false`.

Typical Rhai wrappers for typed deploy / distribution helpers:

```rhai
// scripts/deploy-uat-plan.rhai
let plan = deploy::plan(#{ env: "uat", write_report: true });
if !plan["ok"] { throw("deploy plan failed"); }
```

```rhai
// scripts/check-release-artifacts.rhai
let artifacts = distribution::validate_artifacts(#{
    artifacts_dir: "artifacts/release",
    expect_homebrew: true,
});
if !artifacts["ok"] { throw("artifact validation failed"); }
```

## `[systems.<name>]`

Systems group containers and workspaces. One system can have many workspaces.

```toml
[systems.release]
default_workspace = "linux"

[systems.release.workspaces.linux]
container = "linux-release"
```

## `[containers.<name>]`

Container definitions live in catalogs (often imported from a shared catalog
crate). Repo-local containers go here:

```toml
[containers.linux-release]
image = "ghcr.io/inflatable-cookie/effigy-linux-release:latest"
volumes = [
  { source = ".", target = "/workspace", mode = "rw" },
]
```

For Effigy-defined catalogs (`workspace-rust-bun`, `php-fpm`, `node`), import
from the workspace catalog crate rather than redefining.

## `[bootstrap]`

First-run setup steps, executed by `effigy bootstrap`:

```toml
[bootstrap]
run = [
  { task = "bootstrap deps sync" },
  { task = "doctor" },
]
start = "dev"                              # single selector
# start = ["container:up", "dev"]          # or array, sequential
# start = [{ task = "container:up" }, { task = "dev" }]   # table form
submodules = "recursive"
```

`start` accepts a scalar selector or an array. Array entries are either
bare selector strings or `{ task = "..." }` tables (mixed allowed).
Args travel inline in the selector string (`"dev --foo bar"`). Arrays
run in declaration order; the first failure aborts the chain.

## `[release]`

Release configuration: gates, manifest path, distribution targets.

```toml
[release]
manifest_path = "release/manifest.toml"
gates = [
  "fmt",
  "clippy",
  "test",
  "docs",
  "json-contracts",
  "released-surface",
]
```

The actual release manifest (`release/manifest.toml`) is separate and tracks
version, changelog cutoff, distribution channels.

## Catalog imports

Catalogs let you share container/system definitions across repos:

```toml
[catalog]
imports = [
  { crate = "effigy-containers", catalog = "workspace-rust-bun" },
]
```

After importing, reference the container by its catalog name:

```toml
[systems.dev.workspaces.main]
container = "workspace-rust-bun"
```
