project(
    'hypr-cursor-highlight', 'cpp',
    version: '0.1',
    default_options: ['buildtype=release']
)

shared_module(
    meson.project_name(),

    include_directories: 'include',
    sources: [ 'src/main.cpp' ],

    install: true, # necessary for nix build
    name_prefix: '', # "lib" by default

    # compiler arguments (assuming gcc)
    cpp_args: [
        '-std=c++23',
        # throw errors when using compiler extensions
        '-pedantic-errors',
        # more warnings
        '-Wall', '-Weffc++', '-Wextra', '-Wconversion', '-Wsign-conversion', '-Wshadow',
    ],

    # copied from https://github.com/hyprwm/hyprland-plugins
    dependencies: [
        dependency('hyprland'),
        dependency('pixman-1'),
        dependency('libdrm'),
        dependency('pangocairo'),
        dependency('libinput'),
        dependency('libudev'),
        dependency('wayland-server'),
        dependency('xkbcommon'),
    ],
)