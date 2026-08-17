# Config reference — config.toml

Keepsake reads an optional TOML configuration file on startup. If the file doesn't exist, Keepsake uses safe defaults that work for most setups out of the box.

## File location

| Platform | Path |
|---|---|
| macOS | `~/Library/Application Support/Keepsake/config.toml` |
| Windows | `%APPDATA%\Keepsake\config.toml` |
| Linux | `~/.config/keepsake/config.toml` (or `$XDG_CONFIG_HOME/keepsake/config.toml`) |

The directory is created automatically when Keepsake first runs. If the file doesn't exist, all defaults apply.

---

## Quick-start example

```toml
[scan]
vst2_paths = ["/path/to/extra/plugins"]

[expose]
vst2_bridged = true
vst2_native = false

[isolation]
default = "per-instance"
```

This is the minimal config most users need: add an extra scan path, keep the default exposure settings, and run each plugin in its own process.

---

## `[scan]` — Plugin discovery

Controls where Keepsake looks for legacy plugins.

### `rescan`

```toml
rescan = false  # default
```

Set to `true` to force a full rescan on the next host startup. Keepsake resets this to `false` after the rescan completes. Useful if you've installed new plugins and want them picked up without waiting for automatic cache expiry.

### `vst2_paths`

```toml
vst2_paths = []  # default (empty — uses platform defaults)
```

Extra directories to scan for VST2 plugins, in addition to the platform defaults. Paths are scanned recursively.

```toml
vst2_paths = [
    "/Volumes/PluginDrive/VST2",
    "/Users/you/CustomPlugins"
]
```

**Default scan paths by platform (when `vst2_paths` is empty and `replace_default_vst2_paths` is false):**

- **macOS:** `~/Library/Audio/Plug-Ins/VST/`, `/Library/Audio/Plug-Ins/VST/`
- **Windows:** `%PROGRAMFILES%\VST2\`, `%PROGRAMFILES%\VSTPlugins\`, `%PROGRAMFILES%\Steinberg\VSTPlugins\`, plus `%PROGRAMFILES(X86)%` and `%COMMONPROGRAMFILES%` variants
- **Linux:** `~/.vst/`, `/usr/lib/vst/`, `/usr/local/lib/vst/`

### `replace_default_vst2_paths`

```toml
replace_default_vst2_paths = false  # default
```

If `true`, the platform default paths are ignored entirely and only `vst2_paths` is used. Set this if your plugins live outside the standard locations and you don't want Keepsake scanning empty default folders.

```toml
[scan]
replace_default_vst2_paths = true
vst2_paths = ["/custom/only/path"]
```

### Environment variable override

Setting `KEEPSAKE_VST2_PATH` bypasses both config and defaults:

```sh
# macOS / Linux — colon-separated
export KEEPSAKE_VST2_PATH="/path/one:/path/two"

# Windows — semicolon-separated
set KEEPSAKE_VST2_PATH=C:\path\one;C:\path\two
```

When this env var is set, `vst2_paths` and `replace_default_vst2_paths` are ignored.

---

## `[expose]` — What gets exposed to the host

Controls which discovered plugins Keepsake presents to your host. The default posture is conservative: bridge-required VST2 and VST3 on, native duplicates and AU off.

### `mode`

```toml
mode = "auto"  # default
```

| Value | Behaviour |
|---|---|
| `"auto"` | Use the format and architecture flags below |
| `"whitelist"` | Only expose plugins explicitly listed in `[[expose.plugin]]` entries |
| `"all"` | Expose everything found — useful for development and testing |

### `vst2_bridged`

```toml
vst2_bridged = true  # default
```

Expose VST2 plugins that require the bridge — cross-architecture plugins (x86_64 plugins on an Apple Silicon Mac, for example) and 32-bit plugins. This is the primary use case for most users.

### `vst2_native`

```toml
vst2_native = false  # default
```

This is a fallback for hosts whose capabilities Keepsake does not know. When
the current host or its plug-in scanner is known to support native VST2,
Keepsake suppresses same-architecture VST2 descriptors even if this setting is
`true`. Bridge-required Intel or 32-bit VST2 descriptors remain exposed. See
the dated [host capability matrix](../architecture/native-vst2-host-capabilities.md)
for product evidence and activated runtime identities.

Expose VST2 plugins that can be loaded natively (same architecture as the host). Off by default because CLAP hosts that support VST2 natively may already load these; bridging them adds overhead without benefit unless you specifically want crash isolation.

Set to `true` if you want all VST2 plugins going through Keepsake's bridge, including native ones.

### `vst3_bridged`

```toml
vst3_bridged = true  # default
```

Expose VST3 plugins that cannot load in the host architecture, such as Intel-only VST3s on Apple silicon. Experimental, but this is the useful bridge case.

### `vst3_native`

```toml
vst3_native = false  # default
```

Expose native-architecture VST3 plugins through Keepsake as well. Off by default to avoid duplicating plugins the host can load directly. The legacy `vst3 = true` setting enables both VST3 groups; `vst3 = false` keeps bridge-required VST3 enabled and native duplicates hidden.

### `au`

```toml
au = false  # default — macOS only
```

Expose Audio Unit v2 plugins. **Experimental in v0.1-alpha, macOS only.** The loader exists but this lane has not been fully validated.

### `[[expose.plugin]]` — Explicit whitelist entries

Used when `mode = "whitelist"`. Each `[[expose.plugin]]` block adds one plugin to the whitelist.

```toml
[expose]
mode = "whitelist"

[[expose.plugin]]
path = "/Library/Audio/Plug-Ins/VST/Serum.vst"

[[expose.plugin]]
path = "/Library/Audio/Plug-Ins/VST/APC.vst"
```

Only the listed plugins will be exposed to the host. Everything else Keepsake finds is ignored.

`path` is compared against the plugin's file path and accepts the same globs as `match` above — `*` and `?`. So `path = "/Library/Audio/Plug-Ins/VST/*"` whitelists a whole folder.

---

## `[isolation]` — Process isolation behaviour

Controls how many bridge processes are used and how plugins are grouped into them.

### `default`

```toml
default = "per-instance"  # default
```

| Value | Behaviour |
|---|---|
| `"per-instance"` | Each plugin instance gets its own bridge process. Strongest crash isolation. Most resource usage. |
| `"per-binary"` | All instances of the same plugin share one bridge process. A crash in one instance affects others of the same plugin, but not different plugins. |
| `"shared"` | All bridged plugins share a single bridge process. Lowest resource usage; a crash in any bridged plugin affects all of them. Not recommended for unreliable plugins. |

For most setups, `"per-instance"` is the right choice. Use `"shared"` or `"per-binary"` if you're loading many instances and process overhead becomes a concern.

### `[[isolation.override]]` — Per-plugin isolation

Override the isolation mode for specific plugins.

```toml
[isolation]
default = "per-instance"

[[isolation.override]]
match = "/Library/Audio/Plug-Ins/VST/StablePlugin.vst"
mode = "shared"

[[isolation.override]]
match = "*Kontakt*"
mode = "per-instance"
```

`match` is compared against three things, and the row applies if **any** of them matches:

| Key | Example |
|---|---|
| The plugin ID Keepsake exposes to your host | `keepsake.vst2.41706364` |
| The plugin's display name | `Serum`, `*Kontakt*` |
| The plugin's file path | `/Library/Audio/Plug-Ins/VST/Serum.vst` |

Glob patterns are supported in all three: `*` matches any run of characters (including none) and `?` matches exactly one. A `match` with no wildcards has to match exactly. Wildcards cross `/` and `\`, so `/Library/*/Serum.vst` matches a Serum nested any number of directories deep.

The **first** matching row wins. Put your most specific rows first.

> **Fixed in this release:** glob matching previously misbehaved — `*Kontakt*` matched every plugin, `Serum*` matched nothing, `?` was not implemented at all, and `match` was never compared against the file path despite this page documenting it. If you wrote overrides against an earlier build, re-check that they still select what you intended. Whitelist patterns under `[[expose.plugin]]` had the same problem and are fixed the same way.

---

## Soundcheck managed settings

If you use [Soundcheck](https://github.com/inflatable-cookie/soundcheck), it can set your isolation policy centrally instead of you editing `config.toml` by hand. Soundcheck writes a small managed file and Keepsake reads it at startup. Soundcheck never edits your `config.toml`, and Keepsake never talks to Soundcheck — the file is the only connection, so Keepsake works exactly the same when Soundcheck is closed or not installed.

### File location

| Platform | Path |
|---|---|
| macOS | `~/Library/Application Support/Soundcheck/integrations/keepsake.toml` |
| Windows | `%APPDATA%\Soundcheck\integrations\keepsake.toml` |
| Linux | `$XDG_CONFIG_HOME/soundcheck/integrations/keepsake.toml` (or `~/.config/soundcheck/integrations/keepsake.toml`) |

### What it can set

Only isolation policy. Scan paths, exposure, GUI, and everything else stay in your `config.toml`.

```toml
schema_version = 1

[isolation]
default = "per-instance"

[[isolation.override]]
plugin_id = "keepsake.vst2.41706364"
mode = "per-binary"
```

Overrides key on the plugin ID Keepsake exposes to your host — not a path and not a name. The ID must match exactly; globs are not expanded here.

### How it combines with `config.toml`

- A valid managed `default` replaces the `default` in your `config.toml`.
- Managed overrides win for the plugin IDs they name. Your `config.toml` overrides still apply to every other plugin.
- If the managed file is missing, unreadable, malformed, or written for a schema version Keepsake does not support, it is ignored **as a whole** and your `config.toml` applies unchanged. Keepsake prints one line saying why and carries on — a bad managed file never blocks plugin scanning or loading.
- Unknown keys inside a supported file are ignored, so a newer Soundcheck will not break an older Keepsake.

Reload works the same as `config.toml`: rescan plugins in your host or restart the host.

---

## `[gui]` — GUI behaviour (macOS only)

These settings only apply on macOS. They control how plugin editor windows are managed.

### `mac_mode`

```toml
mac_mode = "live"  # default
```

| Value | Behaviour |
|---|---|
| `"live"` | Bridge-owned live editor windows. This is the validated macOS UI posture for v0.1-alpha. Plugin UIs open in a separate floating window. |
| `"auto"` | Alias for `"live"`. Resolves to the live editor posture. |

> **Note:** `"preview"` and `"iosurface"` are diagnostic-only modes for developer/operator use. Do not use them in a normal setup — they do not provide interactive editing.

### `mac_attach_target`

```toml
mac_attach_target = "auto"  # default
```

Controls how the plugin editor attaches to the host window. In most cases `"auto"` is correct and you should not need to change this.

| Value | Use case |
|---|---|
| `"auto"` | Let Keepsake choose (recommended) |
| `"requested-parent"` | Use exactly the view the host requests |
| `"content-view"` | Attach to the window's content view |
| `"frame-superview"` | Attach to the frame's superview |

If plugin editors are appearing in the wrong position or not appearing at all on a specific host, try `"requested-parent"` first.

---

## Complete example

```toml
# Scan
[scan]
vst2_paths = ["/Volumes/External/VST2"]
rescan = false
replace_default_vst2_paths = false

# What to expose
[expose]
mode = "auto"
vst2_bridged = true
vst2_native = false
vst3_bridged = true
vst3_native = false
au = false

# Optionally whitelist specific plugins:
# [expose]
# mode = "whitelist"
# [[expose.plugin]]
# path = "/Library/Audio/Plug-Ins/VST/MyPlugin.vst"

# Isolation
[isolation]
default = "per-instance"

# Per-plugin override example:
# [[isolation.override]]
# match = "/Library/Audio/Plug-Ins/VST/HeavyPlugin.vst"
# mode = "shared"

# GUI (macOS only)
[gui]
mac_mode = "live"
mac_attach_target = "auto"
```

---

## Config reload

Keepsake reads the config once at startup (when the host loads the plugin). To apply config changes, rescan plugins in your host or restart the host entirely.
