#pragma once

#include <string>

enum class NativeVst2HostSupport {
    Unknown,
    Supported,
    Unsupported,
};

struct KeepsakeHostCapabilities {
    std::string identity;
    NativeVst2HostSupport native_vst2 = NativeVst2HostSupport::Unknown;
};

struct KeepsakeVst2Exposure {
    bool native = false;
    bool bridged = true;
};

// Classify a host identity without consulting the current process. Kept
// separate so host capability policy remains deterministic and testable.
KeepsakeHostCapabilities classify_host_capabilities(
    const std::string &bundle_id,
    const std::string &executable_name);

// Resolve the host-aware VST2 descriptor policy without mutating unrelated
// format configuration. Bridge-required exposure is never inferred from host
// support for same-architecture VST2.
KeepsakeVst2Exposure resolve_vst2_exposure(
    NativeVst2HostSupport host_support,
    bool configured_native,
    bool configured_bridged);

// Resolve the process currently loading Keepsake. macOS classification uses
// the main bundle or a verified scanner/helper bundle. Windows and Linux
// currently report executable identity without activating suppression policy.
KeepsakeHostCapabilities current_host_capabilities();
