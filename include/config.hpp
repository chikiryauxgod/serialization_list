#pragma once

#include <string>

class AppConfig {
public:
    std::string input_file;
    std::string output_file;

    static AppConfig LoadConfig(const std::string& path);
    static std::string Trim(const std::string& s);
};
