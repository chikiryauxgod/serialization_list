#include "../include/config.hpp"

#include <fstream>
#include <stdexcept>

static std::string Trim(const std::string& s) {
    const auto start = s.find_first_not_of(" \t\r\n");
    const auto end = s.find_last_not_of(" \t\r\n");

    if (start == std::string::npos) return "";
    return s.substr(start, end - start + 1);
}


AppConfig AppConfig::FromFile(const std::string& path) {
    AppConfig cfg;

    std::ifstream in(path);
    if (!in) {
        return cfg; // fallback to defaults
    }

    std::string line;
    while (std::getline(in, line)) {
        line = Trim(line);

        if (line.empty() || line[0] == '#') continue;

        const auto eq = line.find('=');
        if (eq == std::string::npos) continue;

        const std::string key = Trim(line.substr(0, eq));
        const std::string value = Trim(line.substr(eq + 1));

        if (key == "input") {
            cfg.input_file = value;
        } else if (key == "output") {
            cfg.output_file = value;
        }
    }

    return cfg;
}


AppConfig::AppConfig() {
    ApplyDefaults();
}


void AppConfig::ApplyDefaults() {
    input_file = "inlet.in";
    output_file = "outlet.out";
}


void AppConfig::OverrideFromArgs(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "--input" && i + 1 < argc) {
            input_file = argv[++i];
        }
        else if (arg == "--output" && i + 1 < argc) {
            output_file = argv[++i];
        }
    }
}