#pragma once
//
// Shared glob matching for config.toml patterns.
//
// One implementation for every user-facing glob in Keepsake — isolation
// overrides and the exposure whitelist. Both surfaces previously carried their
// own partial matcher, and both got common patterns wrong.
//
// Supports the two wildcards documented in docs/setup/config-reference.md:
//   *  matches any run of characters, including none
//   ?  matches exactly one character
//
// Matching is literal and case-sensitive otherwise. There are no character
// classes and no path-separator special-casing: `*` crosses `/` and `\`.
//

#include <string>

inline bool keepsake_glob_match(const std::string &pattern,
                                 const std::string &text) {
    size_t p = 0, t = 0;
    size_t star = std::string::npos; // last '*' in the pattern, if any
    size_t retry = 0;                // where to resume text after that '*'

    while (t < text.size()) {
        if (p < pattern.size() &&
            (pattern[p] == '?' || pattern[p] == text[t])) {
            ++p;
            ++t;
        } else if (p < pattern.size() && pattern[p] == '*') {
            star = p++;
            retry = t;
        } else if (star != std::string::npos) {
            // Backtrack: let the last '*' swallow one more character.
            p = star + 1;
            t = ++retry;
        } else {
            return false;
        }
    }

    while (p < pattern.size() && pattern[p] == '*') ++p;
    return p == pattern.size();
}
