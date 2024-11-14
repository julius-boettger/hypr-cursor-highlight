#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#define WLR_USE_UNSTABLE

#include <hyprland/src/plugins/PluginAPI.hpp>

inline HANDLE PHANDLE = nullptr;

void mouseMoveCallback(void* /*unused*/, SCallbackInfo& /*unused*/, std::any param);

#endif