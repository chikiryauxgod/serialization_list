#pragma once

#include <string>

class AppConfig {
public:
    std::string input_file;
    std::string output_file;

    AppConfig();  

    static AppConfig FromFile(const std::string& path);
    void OverrideFromArgs(int argc, char** argv);
    void ApplyDefaults();
};