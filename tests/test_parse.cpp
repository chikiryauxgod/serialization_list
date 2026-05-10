#include <gtest/gtest.h>
#include "../include/list_operator.hpp"
#include "../include/list_parser.hpp"

TEST(ParseLine, ValidInput) {
    std::string line = "apple;2";
    std::size_t line_number = 1;

    auto [data, rand_index] = ParseLine(line, line_number);

    EXPECT_EQ(data, "apple");
    EXPECT_EQ(rand_index, 2);
}

TEST(ParseLine, MissingSeparator) {
    EXPECT_THROW(
        ParseLine("apple2", 1),
        std::runtime_error
    );
}