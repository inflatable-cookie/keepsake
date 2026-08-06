#include "host_capabilities.h"

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#include <mach-o/dyld.h>
#elif defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#elif defined(__linux__)
#include <unistd.h>
#endif

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <vector>

namespace {

struct KnownHost {
    const char *bundle_id;
    const char *executable_name;
    NativeVst2HostSupport native_vst2;
};

// These entries describe verified runtime process identities, not the full
// product capability matrix. Keep the product-level research in
// docs/architecture/native-vst2-host-capabilities.md. Scanner and helper
// bundle IDs are required because DAWs may enumerate CLAP descriptors outside
// their main application process.
constexpr KnownHost kKnownHosts[] = {
    {"com.fender.studioapp", "Studio Pro", NativeVst2HostSupport::Supported},
    {"com.fender.plugscannerapp", "Plug-in Scanner", NativeVst2HostSupport::Supported},
    {"com.cockos.reaper", "REAPER", NativeVst2HostSupport::Supported},
    {"com.cockos.reaperhostx8664", "reaper_host_x86_64", NativeVst2HostSupport::Supported},
    {"com.cockos.reaperhostarm64", "reaper_host_arm64", NativeVst2HostSupport::Supported},
    {"com.bitwig.studio", "BitwigStudio", NativeVst2HostSupport::Supported},
    {"com.bitwig.studio.plugin.host32", "BitwigPluginHost-X64-SSE41", NativeVst2HostSupport::Supported},
    {"com.bitwig.studio.plugin.host32", "BitwigPluginHost-ARM64-NEON", NativeVst2HostSupport::Supported},
    {"com.bitwig.studio.engine", "BitwigAudioEngine-X64-AVX2", NativeVst2HostSupport::Supported},
    {"com.bitwig.studio.engine", "BitwigAudioEngine-ARM64-NEON", NativeVst2HostSupport::Supported},
};

std::string lowercase(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });
    return value;
}

#ifdef __APPLE__
std::string cf_string_utf8(CFStringRef value) {
    if (!value) return {};
    const CFIndex length = CFStringGetLength(value);
    const CFIndex capacity = CFStringGetMaximumSizeForEncoding(
        length, kCFStringEncodingUTF8) + 1;
    std::vector<char> buffer(static_cast<size_t>(capacity));
    if (!CFStringGetCString(value, buffer.data(), capacity, kCFStringEncodingUTF8)) {
        return {};
    }
    return buffer.data();
}

std::string current_bundle_id() {
    CFBundleRef bundle = CFBundleGetMainBundle();
    return bundle ? cf_string_utf8(CFBundleGetIdentifier(bundle)) : std::string{};
}

std::string current_executable_name() {
    uint32_t size = 0;
    _NSGetExecutablePath(nullptr, &size);
    if (size == 0) return {};
    std::vector<char> path(size + 1, '\0');
    if (_NSGetExecutablePath(path.data(), &size) != 0) return {};
    return std::filesystem::path(path.data()).filename().string();
}
#elif defined(_WIN32)
std::string wide_utf8(const std::wstring &value) {
    if (value.empty()) return {};
    const int size = WideCharToMultiByte(
        CP_UTF8, 0, value.data(), static_cast<int>(value.size()),
        nullptr, 0, nullptr, nullptr);
    if (size <= 0) return {};
    std::string result(static_cast<size_t>(size), '\0');
    if (WideCharToMultiByte(
            CP_UTF8, 0, value.data(), static_cast<int>(value.size()),
            result.data(), size, nullptr, nullptr) != size) {
        return {};
    }
    return result;
}

std::string current_executable_name() {
    std::vector<wchar_t> path(1024, L'\0');
    for (;;) {
        const DWORD length = GetModuleFileNameW(
            nullptr, path.data(), static_cast<DWORD>(path.size()));
        if (length == 0) return {};
        if (length < path.size() - 1) {
            const std::wstring executable(path.data(), length);
            const size_t separator = executable.find_last_of(L"\\/");
            return wide_utf8(separator == std::wstring::npos
                ? executable
                : executable.substr(separator + 1));
        }
        path.resize(path.size() * 2, L'\0');
    }
}
#elif defined(__linux__)
std::string current_executable_name() {
    std::vector<char> path(1024, '\0');
    for (;;) {
        const ssize_t length = readlink("/proc/self/exe", path.data(), path.size() - 1);
        if (length < 0) return {};
        if (static_cast<size_t>(length) < path.size() - 1) {
            path[static_cast<size_t>(length)] = '\0';
            return std::filesystem::path(path.data()).filename().string();
        }
        path.resize(path.size() * 2, '\0');
    }
}
#endif

} // namespace

KeepsakeHostCapabilities classify_host_capabilities(
    const std::string &bundle_id,
    const std::string &executable_name) {
    const std::string normalized_bundle = lowercase(bundle_id);
    const std::string normalized_executable = lowercase(executable_name);

    for (const auto &host : kKnownHosts) {
        const bool bundle_matches = !normalized_bundle.empty()
            && normalized_bundle == lowercase(host.bundle_id);
        const bool executable_matches = normalized_bundle.empty()
            && !normalized_executable.empty()
            && normalized_executable == lowercase(host.executable_name);
        if (bundle_matches || executable_matches) {
            return {
                !bundle_id.empty() ? bundle_id : executable_name,
                host.native_vst2,
            };
        }
    }

    return {
        !bundle_id.empty() ? bundle_id : executable_name,
        NativeVst2HostSupport::Unknown,
    };
}

KeepsakeVst2Exposure resolve_vst2_exposure(
    NativeVst2HostSupport host_support,
    bool configured_native,
    bool configured_bridged) {
    return {
        host_support == NativeVst2HostSupport::Supported
            ? false
            : configured_native,
        configured_bridged,
    };
}

KeepsakeHostCapabilities current_host_capabilities() {
#ifdef __APPLE__
    return classify_host_capabilities(current_bundle_id(), current_executable_name());
#elif defined(_WIN32) || defined(__linux__)
    // Product support is known for several Windows and Linux hosts, but their
    // real scanner/helper process identities are not yet fixture-proven.
    // Report the executable for diagnostics without borrowing macOS policy.
    return {current_executable_name(), NativeVst2HostSupport::Unknown};
#else
    return {};
#endif
}
