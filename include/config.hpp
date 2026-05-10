#pragma once

#include <string>

struct AppConfig {
    std::string input_file;
    std::string output_file;

    static AppConfig FromFile(const std::string& path);
};