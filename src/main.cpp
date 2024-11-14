#define WLR_USE_UNSTABLE

#include <chrono>
#include <format>
#include <fstream>
#include <iostream>

#include "globals.hpp"

namespace logfile {
    constexpr auto PATH { "/tmp/hypr-cursor-highlight.log" };
    // append-mode
    std::ofstream file { PATH, std::ios::app };

    constexpr void write_line(std::string_view line) {
        const auto now { std::chrono::system_clock::now() };
        // ignore fractions of seconds
        const auto now_rounded { std::chrono::floor<std::chrono::seconds>(now) };

        const auto timestamp { std::format("{:%Y-%m-%d %H:%M:%S}", now_rounded) };

        file << timestamp << ": " << line << "\n";
    }
}

// do NOT change
APICALL EXPORT std::string PLUGIN_API_VERSION() {
    return HYPRLAND_API_VERSION;
}

APICALL EXPORT PLUGIN_DESCRIPTION_INFO PLUGIN_INIT(HANDLE handle) {
    PHANDLE = handle;
    const std::string HASH = __hyprland_api_get_hash();
    if (HASH != GIT_COMMIT_HASH) {
        HyprlandAPI::addNotification(PHANDLE, "[hypr-cursor-highlight] Mismatched headers! Can't proceed.",
                                     CColor { 1.0f, 0.2f, 0.2f, 1.0f }, 5000);
        throw std::runtime_error("[hypr-cursor-highlight] Version mismatch");
    }

    logfile::write_line(std::format("Plugin started, using commit hash {}", HASH));

    return { "hypr-cursor-highlight", "", "julius-boettger", "0.1" };
}

APICALL EXPORT void PLUGIN_EXIT() {}