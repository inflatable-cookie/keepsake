#pragma once
//
// Soundcheck managed settings reader.
//
// Soundcheck writes optional central isolation policy to a managed file below
// its own config root. Keepsake reads that file once at factory startup and
// merges it over config.toml. There is no live API, no process discovery, and
// no Soundcheck lifecycle check — the file is the whole seam, and Keepsake
// must work unchanged when Soundcheck is closed or never installed.
//
// Contract refs:
//   docs/contracts/006-process-isolation-policy.md
//   ../soundcheck/docs/contracts/002-companion-api-and-keepsake-integration-contract.md
//

#include "config.h"
#include <string>
#include <vector>

struct ManagedIsolationOverride {
    std::string plugin_id; // exact stable CLAP plugin ID, never a glob
    std::string mode;      // "shared", "per-binary", "per-instance"
};

struct ManagedSettings {
    bool present = false; // the managed file exists and could be opened
    bool valid = false;   // the file parsed as a supported schema
    std::string reject_reason; // bounded diagnostic; empty when accepted
    bool has_isolation_default = false;
    std::string isolation_default;
    std::vector<ManagedIsolationOverride> isolation_overrides;
};

// Soundcheck's platform config root. Empty when it cannot be resolved.
std::string soundcheck_config_dir();

// Full path to the managed file. Empty when the root cannot be resolved.
std::string soundcheck_managed_settings_path();

// Parse the version 1 schema. A malformed or unsupported document yields
// valid = false and a bounded reject_reason; it never partially applies.
ManagedSettings managed_settings_parse(const std::string &text);

// Read and parse the managed file. An absent file yields present = false and
// valid = false with no reject_reason — absence is not a rejection.
ManagedSettings managed_settings_load();

// Merge accepted managed isolation policy over cfg. A rejected or absent file
// leaves cfg untouched. Managed overrides are prepended so they win for the
// plugin IDs they name while config.toml rows still cover everything else.
void config_apply_managed_settings(KeepsakeConfig &cfg,
                                    const ManagedSettings &managed);

// Load, merge, and report. Returns the settings that were considered so
// callers can log or test the decision.
ManagedSettings config_merge_managed_settings(KeepsakeConfig &cfg);
