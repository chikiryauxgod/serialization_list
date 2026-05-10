#include <gtest/gtest.h>

#include "../include/list_operator.hpp"
#include "test_paths.hpp"

#include <fstream>

namespace {

void WriteTextFile(const std::string& file_name, const std::string& content) {
    std::ofstream out(file_name);
    out << content;
}

void WriteBinaryFile(const std::string& file_name, const std::string& content) {
    std::ofstream out(file_name, std::ios::binary);
    out.write(content.data(), static_cast<std::streamsize>(content.size()));
}

} // namespace

TEST(EdgeCases, EmptyTextFile) {
    const std::string file_name = TestFile("empty_input.txt");

    WriteTextFile(file_name, "");

    ListStorage storage = ListStorage::FromTextFile(file_name);

    EXPECT_TRUE(storage.nodes.empty());
    EXPECT_EQ(storage.Head(), nullptr);
}

TEST(EdgeCases, RandIndexOutOfRange) {
    const std::string file_name = TestFile("bad_rand.txt");

    WriteTextFile(
        file_name,
        "apple;3\n"
        "banana;-1\n"
    );

    EXPECT_THROW(
        ListStorage::FromTextFile(file_name),
        std::runtime_error
    );
}

TEST(EdgeCases, MissingSeparator) {
    const std::string file_name = TestFile("missing_separator.txt");

    WriteTextFile(
        file_name,
        "apple2\n"
    );

    EXPECT_THROW(
        ListStorage::FromTextFile(file_name),
        std::runtime_error
    );
}

TEST(EdgeCases, TruncatedBinaryFile) {
    const std::string file_name = TestFile("truncated.bin");

    WriteBinaryFile(file_name, "abc");

    EXPECT_THROW(
        ListStorage::Deserialize(file_name),
        std::runtime_error
    );
}

TEST(EdgeCases, InvalidBinaryRandIndex) {
    const std::string file_name = TestFile("bad_binary.bin");

    std::ofstream out(file_name, std::ios::binary);

    std::size_t count = 1;
    std::size_t data_size = 5;
    std::size_t bad_rand = 7;

    out.write(reinterpret_cast<const char*>(&count), sizeof(count));
    out.write(reinterpret_cast<const char*>(&data_size), sizeof(data_size));
    out.write("apple", 5);
    out.write(reinterpret_cast<const char*>(&bad_rand), sizeof(bad_rand));

    out.close();

    EXPECT_THROW(
        ListStorage::Deserialize(file_name),
        std::runtime_error
    );
}