#include <chrono>
#include <format>
#include <fstream>
#include <iostream>

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

int main() {
    logfile::write_line("test");
    return 0;
}