#include "host_capabilities.h"

#include <cassert>

int main() {
    assert(classify_host_capabilities("com.fender.studioapp", "Studio Pro").native_vst2
           == NativeVst2HostSupport::Supported);
    assert(classify_host_capabilities("com.fender.plugscannerapp", "Plug-in Scanner").native_vst2
           == NativeVst2HostSupport::Supported);
    assert(classify_host_capabilities("com.cockos.reaper", "REAPER").native_vst2
           == NativeVst2HostSupport::Supported);
    assert(classify_host_capabilities("com.cockos.reaperhostx8664", "reaper_host_x86_64").native_vst2
           == NativeVst2HostSupport::Supported);
    assert(classify_host_capabilities("com.cockos.reaperhostarm64", "reaper_host_arm64").native_vst2
           == NativeVst2HostSupport::Supported);
    assert(classify_host_capabilities("com.bitwig.studio", "BitwigStudio").native_vst2
           == NativeVst2HostSupport::Supported);
    assert(classify_host_capabilities("com.bitwig.studio.plugin.host32", "BitwigPluginHost-ARM64-NEON").native_vst2
           == NativeVst2HostSupport::Supported);
    assert(classify_host_capabilities("com.bitwig.studio.engine", "BitwigAudioEngine-ARM64-NEON").native_vst2
           == NativeVst2HostSupport::Supported);
    assert(classify_host_capabilities("", "Studio Pro").native_vst2
           == NativeVst2HostSupport::Supported);
    assert(classify_host_capabilities("", "BitwigStudio").native_vst2
           == NativeVst2HostSupport::Supported);
    assert(classify_host_capabilities("COM.COCKOS.REAPER", "ignored").native_vst2
           == NativeVst2HostSupport::Supported);
    assert(classify_host_capabilities("", "bitwigaudioengine-arm64-neon").native_vst2
           == NativeVst2HostSupport::Supported);
    assert(classify_host_capabilities("unrelated.bundle", "BitwigStudio").native_vst2
           == NativeVst2HostSupport::Unknown);
    assert(classify_host_capabilities("dev.inflatablecookie.loophole", "Loophole").native_vst2
           == NativeVst2HostSupport::Unknown);

    const KeepsakeVst2Exposure supported = resolve_vst2_exposure(
        NativeVst2HostSupport::Supported, true, true);
    assert(!supported.native);
    assert(supported.bridged);

    const KeepsakeVst2Exposure supported_with_bridge_disabled = resolve_vst2_exposure(
        NativeVst2HostSupport::Supported, true, false);
    assert(!supported_with_bridge_disabled.native);
    assert(!supported_with_bridge_disabled.bridged);

    const KeepsakeVst2Exposure unknown_enabled = resolve_vst2_exposure(
        NativeVst2HostSupport::Unknown, true, false);
    assert(unknown_enabled.native);
    assert(!unknown_enabled.bridged);

    const KeepsakeVst2Exposure unknown_disabled = resolve_vst2_exposure(
        NativeVst2HostSupport::Unknown, false, true);
    assert(!unknown_disabled.native);
    assert(unknown_disabled.bridged);
    return 0;
}
