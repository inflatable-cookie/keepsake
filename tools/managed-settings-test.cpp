//
// Soundcheck managed-settings reader proofs.
//
// Covers contract 002's cross-repo completion list: valid-file merge
// precedence, absent and invalid-file fallback, unsupported-schema fallback,
// stable-ID override matching, and no Soundcheck process dependency. Nothing
// here launches, contacts, or checks for Soundcheck — the file is the seam.
//
// Refs:
//   ../soundcheck/docs/contracts/002-companion-api-and-keepsake-integration-contract.md
//   docs/roadmaps/g03/batch-cards/001-g03-soundcheck-managed-settings-reader.md
//

#include "bridge_pool.h"
#include "managed_settings.h"

#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>

namespace fs = std::filesystem;

namespace {

void require(bool condition, const char *message) {
    if (!condition) throw std::runtime_error(message);
}

// Point the platform config-root lookup at an isolated directory, exactly as
// config-cache-test does, so the proof never touches a real install.
void set_config_root(const fs::path &root) {
#ifdef _WIN32
    _putenv_s("APPDATA", root.string().c_str());
#elif defined(__APPLE__)
    setenv("HOME", root.string().c_str(), 1);
#else
    setenv("XDG_CONFIG_HOME", root.string().c_str(), 1);
#endif
}

void write_managed_file(const std::string &contents) {
    const fs::path path = soundcheck_managed_settings_path();
    fs::create_directories(path.parent_path());
    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    out << contents;
}

void remove_managed_file() {
    std::error_code ec;
    fs::remove(soundcheck_managed_settings_path(), ec);
}

// A config.toml-shaped baseline: per-instance default plus one glob row.
KeepsakeConfig baseline_config() {
    KeepsakeConfig cfg;
    cfg.isolation_default = "per-instance";
    cfg.isolation_overrides.push_back({"keepsake.vst2.a", "per-instance", false});
    cfg.isolation_overrides.push_back({"keepsake.vst3.*", "per-binary", false});
    return cfg;
}

IsolationMode to_mode(const std::string &mode) {
    if (mode == "per-binary") return IsolationMode::PER_BINARY;
    if (mode == "per-instance") return IsolationMode::PER_INSTANCE;
    return IsolationMode::SHARED;
}

// Mirror what keepsake_factory_init does with a merged config.
void configure_pool(BridgePool &pool, const KeepsakeConfig &cfg) {
    pool.set_default_mode(to_mode(cfg.isolation_default));
    for (const auto &ov : cfg.isolation_overrides)
        pool.add_override(ov.match, to_mode(ov.mode), ov.exact_plugin_id);
}

const char *kCanonicalFixture = R"(schema_version = 1

[isolation]
default = "per-instance"

[[isolation.override]]
plugin_id = "keepsake.vst2.a"
mode = "per-binary"

[[isolation.override]]
plugin_id = "keepsake.vst2.b"
mode = "shared"
)";

// --- Proof 1: valid-file merge precedence ---

void proof_valid_file_merge() {
    write_managed_file(kCanonicalFixture);

    KeepsakeConfig cfg = baseline_config();
    cfg.isolation_default = "shared"; // config.toml says shared
    ManagedSettings managed = managed_settings_load();
    require(managed.valid, "canonical fixture was rejected");
    config_apply_managed_settings(cfg, managed);

    require(cfg.isolation_default == "per-instance",
            "managed default did not override config.toml default");
    require(cfg.isolation_overrides.size() == 4,
            "managed overrides were not merged with config.toml overrides");
    require(cfg.isolation_overrides[0].exact_plugin_id &&
                cfg.isolation_overrides[1].exact_plugin_id,
            "managed overrides were not marked exact-plugin-id");
    require(!cfg.isolation_overrides[2].exact_plugin_id,
            "config.toml override lost its glob semantics");

    BridgePool pool;
    configure_pool(pool, cfg);
    // Managed row beats the config.toml row for the same plugin ID.
    require(pool.resolve_mode("keepsake.vst2.a", "Alpha") == IsolationMode::PER_BINARY,
            "managed override did not beat the config.toml override");
    require(pool.resolve_mode("keepsake.vst2.b", "Beta") == IsolationMode::SHARED,
            "second managed override was not applied");
    // A plugin the managed file never mentions still falls through to
    // config.toml, then to the merged default.
    require(pool.resolve_mode("keepsake.vst3.c", "Gamma") == IsolationMode::PER_BINARY,
            "config.toml glob override stopped applying after the merge");
    require(pool.resolve_mode("keepsake.au.d", "Unlisted") == IsolationMode::PER_INSTANCE,
            "unlisted plugin did not fall through to the merged default");
}

// --- Proof 2: absent-file fallback ---

void proof_absent_file_fallback() {
    remove_managed_file();

    ManagedSettings managed = managed_settings_load();
    require(!managed.present, "absent managed file was reported as present");
    require(!managed.valid, "absent managed file was reported as valid");
    require(managed.reject_reason.empty(),
            "absent managed file produced a rejection diagnostic");

    KeepsakeConfig cfg = baseline_config();
    const KeepsakeConfig before = cfg;
    config_apply_managed_settings(cfg, managed);
    require(cfg.isolation_default == before.isolation_default,
            "absent managed file changed the isolation default");
    require(cfg.isolation_overrides.size() == before.isolation_overrides.size(),
            "absent managed file changed the override list");
}

// --- Proof 3: invalid-file fallback ---

void expect_rejected(const char *contents, const char *what) {
    write_managed_file(contents);
    ManagedSettings managed = managed_settings_load();
    require(managed.present, "malformed managed file was not seen at all");
    require(!managed.valid, what);
    require(!managed.reject_reason.empty(),
            "rejected managed file produced no bounded diagnostic");
    require(!managed.has_isolation_default && managed.isolation_overrides.empty(),
            "rejected managed file leaked partial values");

    KeepsakeConfig cfg = baseline_config();
    config_apply_managed_settings(cfg, managed);
    require(cfg.isolation_default == "per-instance",
            "rejected managed file changed the isolation default");
    require(cfg.isolation_overrides.size() == 2,
            "rejected managed file changed the override list");
}

void proof_invalid_file_fallback() {
    // Truncated mid-document.
    expect_rejected("schema_version = 1\n\n[isolation]\ndefault = \"per-inst",
                    "truncated file was accepted");
    // Not TOML at all.
    expect_rejected("this is not a config file\n", "garbage file was accepted");
    // Valid TOML shape, invalid mode.
    expect_rejected("schema_version = 1\n\n[isolation]\ndefault = \"isolated\"\n",
                    "invalid isolation mode was accepted");
    // Override row missing its mode.
    expect_rejected("schema_version = 1\n\n[[isolation.override]]\n"
                    "plugin_id = \"keepsake.vst2.a\"\n",
                    "override row without a mode was accepted");
    // Override row missing its plugin_id.
    expect_rejected("schema_version = 1\n\n[[isolation.override]]\n"
                    "mode = \"shared\"\n",
                    "override row without a plugin_id was accepted");
    // Policy before the version declaration.
    expect_rejected("[isolation]\ndefault = \"shared\"\nschema_version = 1\n",
                    "file without a leading schema_version was accepted");
}

// --- Proof 4: unsupported-schema fallback ---

void proof_unsupported_schema_fallback() {
    expect_rejected("schema_version = 2\n\n[isolation]\ndefault = \"shared\"\n",
                    "schema_version 2 was accepted");
    expect_rejected("schema_version = 0\n\n[isolation]\ndefault = \"shared\"\n",
                    "schema_version 0 was accepted");
    expect_rejected("[isolation]\ndefault = \"shared\"\n",
                    "file with no schema_version was accepted");
    expect_rejected("schema_version = \"1\"\n[isolation]\ndefault = \"shared\"\n",
                    "quoted schema_version was accepted");

    // A supported schema carrying unknown fields and unknown tables is still
    // accepted; the unknown parts are simply ignored.
    write_managed_file("schema_version = 1\nfuture_root_key = \"ignored\"\n\n"
                       "[isolation]\ndefault = \"shared\"\nfuture_key = 7\n\n"
                       "[scan]\npaths = \"not keepsake's business\"\n\n"
                       "[[isolation.override]]\n"
                       "plugin_id = \"keepsake.vst2.a\"\nmode = \"shared\"\n"
                       "future_row_key = \"ignored\"\n");
    ManagedSettings managed = managed_settings_load();
    require(managed.valid, "unknown fields in a supported schema were rejected");
    require(managed.isolation_default == "shared",
            "isolation default was lost among unknown fields");
    require(managed.isolation_overrides.size() == 1,
            "override row was lost among unknown fields");
}

// --- Proof 5: stable-ID override matching ---

void proof_stable_id_matching() {
    write_managed_file("schema_version = 1\n\n[isolation]\ndefault = \"shared\"\n\n"
                       "[[isolation.override]]\n"
                       "plugin_id = \"keepsake.vst2.41706364\"\nmode = \"per-instance\"\n");

    KeepsakeConfig cfg;
    cfg.isolation_default = "per-binary";
    config_apply_managed_settings(cfg, managed_settings_load());
    BridgePool pool;
    configure_pool(pool, cfg);

    require(pool.resolve_mode("keepsake.vst2.41706364", "Serum") == IsolationMode::PER_INSTANCE,
            "managed override did not match its exact stable plugin ID");
    // A display name equal to the ID must not pull in the policy.
    require(pool.resolve_mode("keepsake.vst2.99999999", "keepsake.vst2.41706364") ==
                IsolationMode::SHARED,
            "managed override matched a display name instead of a plugin ID");
    // Neither may a longer ID that merely contains it.
    require(pool.resolve_mode("keepsake.vst2.41706364.x86", "Serum 32") == IsolationMode::SHARED,
            "managed override matched a disambiguated ID by prefix");
    // And the value is never treated as a glob.
    write_managed_file("schema_version = 1\n\n[isolation]\ndefault = \"shared\"\n\n"
                       "[[isolation.override]]\n"
                       "plugin_id = \"keepsake.vst3.*\"\nmode = \"per-instance\"\n");
    KeepsakeConfig globbed;
    config_apply_managed_settings(globbed, managed_settings_load());
    BridgePool glob_pool;
    configure_pool(glob_pool, globbed);
    require(glob_pool.resolve_mode("keepsake.vst3.abcd1234", "Any") == IsolationMode::SHARED,
            "managed plugin_id was treated as a glob");
}

// --- Proof 6: no Soundcheck process dependency ---

void proof_no_process_dependency() {
    // Everything above ran with Soundcheck never launched. The remaining claim
    // is that reading a file Soundcheck wrote and then exited needs nothing
    // from Soundcheck at all: same bytes, no producer, correct merge.
    write_managed_file(kCanonicalFixture);
    KeepsakeConfig cfg;
    ManagedSettings managed = managed_settings_load();
    require(managed.valid, "managed file needed a live producer to be readable");
    config_apply_managed_settings(cfg, managed);
    require(cfg.isolation_default == "per-instance",
            "merge required a running Soundcheck");

    // The reader also must not resurrect the config root if Soundcheck removed
    // it — a disabled integration is an absent file, not an error.
    std::error_code ec;
    fs::remove_all(fs::path(soundcheck_config_dir()), ec);
    ManagedSettings after = managed_settings_load();
    require(!after.present && !after.valid,
            "removing Soundcheck's config root did not read as absent");
    require(!fs::exists(soundcheck_config_dir(), ec),
            "the reader recreated Soundcheck's config root");
}

} // namespace

int main() {
    const auto unique = std::chrono::steady_clock::now().time_since_epoch().count();
    const fs::path root =
        fs::temp_directory_path() / ("keepsake-managed-settings-test-" + std::to_string(unique));

    try {
        fs::create_directories(root);
        set_config_root(root);
        require(!soundcheck_managed_settings_path().empty(),
                "managed settings path could not be resolved");

        proof_valid_file_merge();
        proof_absent_file_fallback();
        proof_invalid_file_fallback();
        proof_unsupported_schema_fallback();
        proof_stable_id_matching();
        proof_no_process_dependency();

        fs::remove_all(root);
        return 0;
    } catch (...) {
        fs::remove_all(root);
        throw;
    }
}
