#pragma once

#include <filesystem>
#include <string>

inline std::string TestFile(const std::string& name) {
    const std::filesystem::path dir = "test_data";
    std::filesystem::create_directories(dir);
    return (dir / name).string();
}