project('hypr-cursor-highlight', 'cpp')
executable(
    'hypr-cursor-highlight',
    include_directories: 'include',
    # compiler arguments
    cpp_args: [
        '-std=c++23',
        # throw errors when using compiler extensions (compiler-specific behavior)
        '-pedantic-errors',
        # more warnings
        '-Wall', '-Weffc++', '-Wextra', '-Wconversion', '-Wsign-conversion', '-Wshadow',
    ], sources: [
        'src/main.cpp',
    ]
)