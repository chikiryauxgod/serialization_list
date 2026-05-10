#include "../include/config.hpp"

#include <fstream>
#include <stdexcept>
#include <sstream>

std::string AppConfig::Trim(const std::string& s) {
    const auto start = s.find_first_not_of(" \t\r\n");
    const auto end = s.find_last_not_of(" \t\r\n");

    if (start == std::string::npos) {
        return "";
    }
    
    return s.substr(start, end - start + 1);
}

AppConfig AppConfig::LoadConfig(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        throw std::runtime_error("failed to open config: " + path);
    }

    AppConfig cfg;

    std::string line;
    while (std::getline(in, line)) {
        line = Trim(line);

        if (line.empty() || line[0] == '#') {
            continue;
        }

        const auto eq = line.find('=');
        if (eq == std::string::npos) {
            continue;
        }

        const std::string key = Trim(line.substr(0, eq));
        const std::string value = Trim(line.substr(eq + 1));

        if (key == "input") {
            cfg.input_file = value;
        } else if (key == "output") {
            cfg.output_file = value;
        }
    }

    if (cfg.input_file.empty() || cfg.output_file.empty()) {
        throw std::runtime_error("invalid config: missing input/output");
    }

    return cfg;
}