//
// Soundcheck managed settings reader.
//
// Strict version 1 parser: anything Keepsake cannot fully validate is ignored
// as a whole rather than partially applied. Falling back to config.toml is
// always safe; half-applying someone else's policy is not.
//

#include "managed_settings.h"

#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

namespace {

constexpr int kSupportedSchemaVersion = 1;
constexpr size_t kSnippetLimit = 48;

std::string trim(const std::string &s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == std::string::npos) return {};
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

// Bounded snippet for diagnostics — never echo an unbounded line to stderr.
std::string snippet(const std::string &s) {
    if (s.size() <= kSnippetLimit) return s;
    return s.substr(0, kSnippetLimit) + "...";
}

// A rejected file is ignored as a whole — never partially applied.
ManagedSettings rejected(const std::string &reason) {
    ManagedSettings out;
    out.present = true;
    out.valid = false;
    out.reject_reason = reason;
    return out;
}

std::string at_line(size_t line, const std::string &reason) {
    return "line " + std::to_string(line) + ": " + reason;
}

bool is_valid_mode(const std::string &mode) {
    return mode == "shared" || mode == "per-binary" || mode == "per-instance";
}

// Drop a trailing `#` comment, respecting quoted strings.
std::string strip_comment(const std::string &line) {
    bool in_quotes = false;
    bool escaped = false;
    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        if (escaped) { escaped = false; continue; }
        if (in_quotes && c == '\\') { escaped = true; continue; }
        if (c == '"') { in_quotes = !in_quotes; continue; }
        if (c == '#' && !in_quotes) return line.substr(0, i);
    }
    return line;
}

// Parse a TOML basic string. Returns false on anything that is not a single
// fully quoted value with recognized escapes.
bool parse_quoted(const std::string &raw, std::string &out) {
    if (raw.size() < 2 || raw.front() != '"' || raw.back() != '"') return false;
    std::string body = raw.substr(1, raw.size() - 2);
    std::string value;
    for (size_t i = 0; i < body.size(); ++i) {
        char c = body[i];
        if (c == '"') return false; // unescaped quote inside the value
        if (c != '\\') { value.push_back(c); continue; }
        if (++i >= body.size()) return false;
        switch (body[i]) {
        case '"':  value.push_back('"');  break;
        case '\\': value.push_back('\\'); break;
        case 'n':  value.push_back('\n'); break;
        case 't':  value.push_back('\t'); break;
        case 'r':  value.push_back('\r'); break;
        default: return false; // unrecognized escape — treat as malformed
        }
    }
    out = value;
    return true;
}

bool parse_integer(const std::string &raw, long &out) {
    if (raw.empty()) return false;
    char *end = nullptr;
    long value = std::strtol(raw.c_str(), &end, 10);
    if (!end || *end != '\0') return false;
    out = value;
    return true;
}

enum class Section { Root, Isolation, Override, Unknown };

} // namespace

// --- Platform paths ---

std::string soundcheck_config_dir() {
#ifdef __APPLE__
    const char *home = getenv("HOME");
    if (home && home[0] != '\0')
        return std::string(home) + "/Library/Application Support/Soundcheck";
#elif defined(_WIN32)
    const char *appdata = getenv("APPDATA");
    if (appdata && appdata[0] != '\0')
        return std::string(appdata) + "\\Soundcheck";
#else
    const char *xdg = getenv("XDG_CONFIG_HOME");
    if (xdg && xdg[0] != '\0') return std::string(xdg) + "/soundcheck";
    const char *home = getenv("HOME");
    if (home && home[0] != '\0') return std::string(home) + "/.config/soundcheck";
#endif
    return {};
}

std::string soundcheck_managed_settings_path() {
    std::string dir = soundcheck_config_dir();
    if (dir.empty()) return {};
#ifdef _WIN32
    return dir + "\\integrations\\keepsake.toml";
#else
    return dir + "/integrations/keepsake.toml";
#endif
}

// --- Version 1 parsing ---

ManagedSettings managed_settings_parse(const std::string &text) {
    ManagedSettings out;
    out.present = true;

    Section section = Section::Root;
    bool saw_schema_version = false;
    size_t line_no = 0;
    std::istringstream stream(text);
    std::string raw_line;

    while (std::getline(stream, raw_line)) {
        ++line_no;
        std::string t = trim(strip_comment(raw_line));
        if (t.empty()) continue;

        // Section headers.
        if (t[0] == '[') {
            if (!saw_schema_version) return rejected("missing schema_version");

            if (t.rfind("[[", 0) == 0) {
                if (t.size() < 4 || t.substr(t.size() - 2) != "]]")
                    return rejected(at_line(line_no, "malformed table header"));
                std::string name = trim(t.substr(2, t.size() - 4));
                if (name == "isolation.override") {
                    out.isolation_overrides.emplace_back();
                    section = Section::Override;
                } else {
                    section = Section::Unknown;
                }
                continue;
            }

            if (t.back() != ']')
                return rejected(at_line(line_no, "malformed table header"));
            std::string name = trim(t.substr(1, t.size() - 2));
            if (name == "isolation") section = Section::Isolation;
            else section = Section::Unknown;
            continue;
        }

        // key = value.
        size_t eq = t.find('=');
        if (eq == std::string::npos)
            return rejected(at_line(line_no, "expected key = value"));
        std::string key = trim(t.substr(0, eq));
        std::string value = trim(t.substr(eq + 1));
        if (key.empty() || value.empty())
            return rejected(at_line(line_no, "expected key = value"));

        switch (section) {
        case Section::Root: {
            if (key != "schema_version") continue; // unknown root key — ignored
            long version = 0;
            if (!parse_integer(value, version))
                return rejected("schema_version is not an integer");
            if (version != kSupportedSchemaVersion)
                return rejected("unsupported schema_version " + std::to_string(version));
            saw_schema_version = true;
            break;
        }
        case Section::Isolation: {
            if (key != "default") continue; // unknown key in a known table
            std::string mode;
            if (!parse_quoted(value, mode))
                return rejected(at_line(line_no, "isolation.default is not a string"));
            if (!is_valid_mode(mode))
                return rejected("invalid isolation default '" + snippet(mode) + "'");
            out.has_isolation_default = true;
            out.isolation_default = mode;
            break;
        }
        case Section::Override: {
            if (key != "plugin_id" && key != "mode") continue;
            std::string parsed;
            if (!parse_quoted(value, parsed))
                return rejected(at_line(line_no, "override " + key + " is not a string"));
            auto &row = out.isolation_overrides.back();
            if (key == "plugin_id") row.plugin_id = parsed;
            else row.mode = parsed;
            break;
        }
        case Section::Unknown:
            break; // unknown table — contents ignored
        }
    }

    if (!saw_schema_version) return rejected("missing schema_version");

    for (const auto &row : out.isolation_overrides) {
        if (row.plugin_id.empty())
            return rejected("isolation override is missing plugin_id");
        if (!is_valid_mode(row.mode))
            return rejected("isolation override '" + snippet(row.plugin_id) +
                            "' has invalid mode '" + snippet(row.mode) + "'");
    }

    out.valid = true;
    return out;
}

// --- Discovery ---

ManagedSettings managed_settings_load() {
    ManagedSettings out;

    std::string path = soundcheck_managed_settings_path();
    if (path.empty()) return out; // no resolvable config root — treat as absent

    std::error_code ec;
    if (!fs::is_regular_file(path, ec)) return out; // absent is not a rejection

    std::ifstream f(path, std::ios::binary);
    if (!f.is_open()) {
        out.present = true;
        out.reject_reason = "file could not be opened";
        return out;
    }

    std::ostringstream buffer;
    buffer << f.rdbuf();
    if (f.bad()) {
        out.present = true;
        out.reject_reason = "file could not be read";
        return out;
    }

    return managed_settings_parse(buffer.str());
}

// --- Merge ---

void config_apply_managed_settings(KeepsakeConfig &cfg,
                                    const ManagedSettings &managed) {
    if (!managed.valid) return;

    if (managed.has_isolation_default)
        cfg.isolation_default = managed.isolation_default;

    if (managed.isolation_overrides.empty()) return;

    // Managed rows come first so they win for the plugin IDs they name, while
    // config.toml rows still apply to every plugin the managed file omits.
    std::vector<IsolationOverride> merged;
    merged.reserve(managed.isolation_overrides.size() + cfg.isolation_overrides.size());
    for (const auto &row : managed.isolation_overrides)
        merged.push_back({row.plugin_id, row.mode, /*exact_plugin_id=*/true});
    for (const auto &row : cfg.isolation_overrides) merged.push_back(row);
    cfg.isolation_overrides = std::move(merged);
}

ManagedSettings config_merge_managed_settings(KeepsakeConfig &cfg) {
    ManagedSettings managed = managed_settings_load();
    config_apply_managed_settings(cfg, managed);

    const std::string path = soundcheck_managed_settings_path();
    if (managed.valid) {
        fprintf(stderr,
                "keepsake: applied soundcheck settings (default=%s, %zu overrides) from '%s'\n",
                managed.has_isolation_default ? managed.isolation_default.c_str()
                                              : "(unset)",
                managed.isolation_overrides.size(),
                path.c_str());
    } else if (managed.present) {
        fprintf(stderr,
                "keepsake: ignoring soundcheck settings at '%s' (%s); using config.toml\n",
                path.c_str(),
                managed.reject_reason.empty() ? "invalid" : managed.reject_reason.c_str());
    }
    return managed;
}
