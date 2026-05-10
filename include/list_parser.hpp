#pragma once

#include <string>
#include <utility>

std::pair<std::string, int> ParseLine(
    const std::string& line,
    std::size_t line_number
);