#include "../include/list_parser.hpp"

#include <stdexcept>

constexpr char kSeparator = ';';

std::pair<std::string, int> ParseLine(
    const std::string& line,
    std::size_t line_number
) {
    const auto pos = line.rfind(kSeparator);

    if (pos == std::string::npos) {
        throw std::runtime_error("missing ';'");
    }

    std::string data = line.substr(0, pos);
    std::string rand_text = line.substr(pos + 1);

    std::size_t parsed = 0;
    int rand_index = 0;

    rand_index = std::stoi(rand_text, &parsed);

    if (parsed != rand_text.size()) {
        throw std::runtime_error("invalid rand index");
    }

    return {data, rand_index};
}