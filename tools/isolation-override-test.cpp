//
// Isolation override matching proofs.
//
// Both user-facing glob surfaces — isolation overrides and the exposure
// whitelist — previously carried their own partial matcher and got common
// documented patterns wrong. This pins the shared matcher and the three keys
// a config.toml override row is matched against.
//
// Refs:
//   docs/contracts/006-process-isolation-policy.md
//   docs/setup/config-reference.md
//   docs/roadmaps/g03/batch-cards/002-g03-isolation-config-drift-and-override-matching.md
//

#include "bridge_pool.h"
#include "glob_match.h"

#include <stdexcept>
#include <string>

namespace {

void require(bool condition, const char *message) {
    if (!condition) throw std::runtime_error(message);
}

// --- Glob semantics ---

void proof_glob_wildcards() {
    // Exact, no wildcards.
    require(keepsake_glob_match("Serum", "Serum"), "exact match failed");
    require(!keepsake_glob_match("Serum", "Serum 2"), "exact match was too loose");
    require(!keepsake_glob_match("Serum", "eru"), "exact match matched a substring");

    // Match-all.
    require(keepsake_glob_match("*", "anything"), "* did not match");
    require(keepsake_glob_match("*", ""), "* did not match an empty string");

    // Prefix, suffix, and the surrounding form that used to match everything.
    require(keepsake_glob_match("keepsake.vst3.*", "keepsake.vst3.abcd"),
            "trailing * did not match");
    require(!keepsake_glob_match("keepsake.vst3.*", "keepsake.vst2.abcd"),
            "trailing * matched the wrong prefix");
    require(keepsake_glob_match("*.vst", "/Plug-Ins/VST/Serum.vst"),
            "leading * did not match");
    require(!keepsake_glob_match("*.vst", "/Plug-Ins/VST/Serum.vst3"),
            "leading * matched the wrong suffix");
    require(keepsake_glob_match("*Kontakt*", "Native Instruments Kontakt 7"),
            "*needle* did not match a containing string");
    require(!keepsake_glob_match("*Kontakt*", "Serum"),
            "*needle* matched a string that does not contain the needle");
    require(!keepsake_glob_match("*Kontakt*", "Kontak"),
            "*needle* matched a truncated needle");

    // Multiple wildcards and backtracking.
    require(keepsake_glob_match("*Audio*Serum*", "/Library/Audio/Plug-Ins/Serum.vst"),
            "multi-* pattern did not match");
    require(!keepsake_glob_match("*Serum*Audio*", "/Library/Audio/Plug-Ins/Serum.vst"),
            "multi-* pattern ignored segment order");
    require(keepsake_glob_match("a*b*c", "abc"), "adjacent segments did not match");
    require(keepsake_glob_match("a**b", "ab"), "consecutive stars did not match");

    // Single-character wildcard, documented but previously unimplemented.
    require(keepsake_glob_match("Serum?", "Serum2"), "? did not match one character");
    require(!keepsake_glob_match("Serum?", "Serum"), "? matched zero characters");
    require(!keepsake_glob_match("Serum?", "Serum12"), "? matched two characters");
    require(keepsake_glob_match("keepsake.vst2.????????", "keepsake.vst2.41706364"),
            "? run did not match a fixed-width ID");

    // Wildcards cross path separators — no path-component special-casing.
    require(keepsake_glob_match("/Library/*/Serum.vst", "/Library/Audio/Plug-Ins/Serum.vst"),
            "* did not cross a path separator");
}

// --- Override key matching ---

void configure(BridgePool &pool, const std::string &match, IsolationMode mode,
                bool exact_plugin_id = false) {
    pool.set_default_mode(IsolationMode::PER_INSTANCE);
    pool.add_override(match, mode, exact_plugin_id);
}

void proof_config_rows_match_id_name_and_path() {
    const std::string id = "keepsake.vst2.41706364";
    const std::string name = "Serum";
    const std::string path = "/Library/Audio/Plug-Ins/VST/Serum.vst";

    // By plugin ID.
    BridgePool by_id;
    configure(by_id, id, IsolationMode::SHARED);
    require(by_id.resolve_mode(id, name, path) == IsolationMode::SHARED,
            "override did not match by plugin ID");

    // By display name glob.
    BridgePool by_name;
    configure(by_name, "*Serum*", IsolationMode::PER_BINARY);
    require(by_name.resolve_mode(id, name, path) == IsolationMode::PER_BINARY,
            "override did not match by display name");

    // By file path — documented in the config reference since the alpha and
    // silently unmatched until now.
    BridgePool by_path;
    configure(by_path, path, IsolationMode::SHARED);
    require(by_path.resolve_mode(id, name, path) == IsolationMode::SHARED,
            "override did not match by exact file path");

    BridgePool by_path_glob;
    configure(by_path_glob, "/Library/Audio/Plug-Ins/VST/*", IsolationMode::SHARED);
    require(by_path_glob.resolve_mode(id, name, path) == IsolationMode::SHARED,
            "override did not match by path glob");

    // A row matching none of the three keys leaves the default in place.
    BridgePool unrelated;
    configure(unrelated, "*Kontakt*", IsolationMode::SHARED);
    require(unrelated.resolve_mode(id, name, path) == IsolationMode::PER_INSTANCE,
            "unrelated override was applied anyway");

    // An empty path is not a wildcard target.
    BridgePool empty_path;
    configure(empty_path, "*.vst", IsolationMode::SHARED);
    require(empty_path.resolve_mode(id, name, "") == IsolationMode::PER_INSTANCE,
            "path pattern matched a plugin with no known path");
}

void proof_managed_rows_stay_exact() {
    const std::string id = "keepsake.vst2.41706364";

    BridgePool pool;
    pool.set_default_mode(IsolationMode::PER_INSTANCE);
    pool.add_override("keepsake.vst2.*", IsolationMode::SHARED, /*exact_plugin_id=*/true);
    require(pool.resolve_mode(id, "Serum", "/x/Serum.vst") == IsolationMode::PER_INSTANCE,
            "managed row was globbed after the matcher fix");

    BridgePool exact;
    exact.set_default_mode(IsolationMode::PER_INSTANCE);
    exact.add_override(id, IsolationMode::SHARED, /*exact_plugin_id=*/true);
    require(exact.resolve_mode(id, "Serum", "/x/Serum.vst") == IsolationMode::SHARED,
            "managed row did not match its exact ID");
    require(exact.resolve_mode("other", id, "/x/Serum.vst") == IsolationMode::PER_INSTANCE,
            "managed row matched a display name");
    require(exact.resolve_mode("other", "Serum", id) == IsolationMode::PER_INSTANCE,
            "managed row matched a file path");
}

void proof_first_matching_row_wins() {
    BridgePool pool;
    pool.set_default_mode(IsolationMode::PER_INSTANCE);
    pool.add_override("*Serum*", IsolationMode::SHARED);
    pool.add_override("*Serum*", IsolationMode::PER_BINARY);
    require(pool.resolve_mode("keepsake.vst2.a", "Serum", "") == IsolationMode::SHARED,
            "a later override row beat an earlier one");
}

} // namespace

int main() {
    proof_glob_wildcards();
    proof_config_rows_match_id_name_and_path();
    proof_managed_rows_stay_exact();
    proof_first_matching_row_wins();
    return 0;
}
