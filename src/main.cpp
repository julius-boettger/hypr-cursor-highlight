#include "globals.hpp"

static SP<HOOK_CALLBACK_FN> g_mouseMoveCallbackHandle { nullptr };

void mouseMoveCallback(void* /*unused*/, SCallbackInfo& /*unused*/, std::any param) {
    const auto cursorPos = std::any_cast<Vector2D>(param);
    Debug::log(LOG, "[hypr-cursor-highlight] Mouse cursor at {}", cursorPos);
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

    g_mouseMoveCallbackHandle = HyprlandAPI::registerCallbackDynamic(PHANDLE, "mouseMove", mouseMoveCallback);

    Debug::log(LOG, "[hypr-cursor-highlight] Plugin initialized.");
    return { "hypr-cursor-highlight", "", "julius-boettger", "0.1" };
}

APICALL EXPORT void PLUGIN_EXIT() {
    Debug::log(LOG, "[hypr-cursor-highlight] Plugin exited.");
}