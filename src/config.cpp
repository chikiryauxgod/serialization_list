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
        cfg.input_file = "inlet.in";
        cfg.output_file = "outlet.out";
        return cfg;
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

    if (cfg.input_file.empty()) {
        cfg.input_file = "inlet.in";
    }

    if (cfg.output_file.empty()) {
        cfg.output_file = "outlet.out";
    }

    return cfg;
}