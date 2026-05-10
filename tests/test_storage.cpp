#include <gtest/gtest.h>

#include "../include/list_operator.hpp"
#include "test_paths.hpp"

#include <fstream>

namespace {

void WriteFile(const std::string& file_name, const std::string& content) {
    std::ofstream out(file_name);
    out << content;
}

} // namespace

TEST(Storage, FromTextFileBuildsPrevNextAndRand) {
    const std::string file_name = TestFile("test_storage_input.txt");

    WriteFile(
        file_name,
        "apple;2\n"
        "banana;-1\n"
        "carrot;1\n"
    );

    ListStorage storage = ListStorage::FromTextFile(file_name);

    ASSERT_EQ(storage.nodes.size(), 3u);

    // prev
    EXPECT_EQ(storage.nodes[0].prev, nullptr);
    EXPECT_EQ(storage.nodes[1].prev, &storage.nodes[0]);
    EXPECT_EQ(storage.nodes[2].prev, &storage.nodes[1]);

    // next
    EXPECT_EQ(storage.nodes[0].next, &storage.nodes[1]);
    EXPECT_EQ(storage.nodes[1].next, &storage.nodes[2]);
    EXPECT_EQ(storage.nodes[2].next, nullptr);

    // rand
    EXPECT_EQ(storage.nodes[0].rand, &storage.nodes[2]);
    EXPECT_EQ(storage.nodes[1].rand, nullptr);
    EXPECT_EQ(storage.nodes[2].rand, &storage.nodes[1]);
}

TEST(Storage, HeadReturnsNullForEmptyStorage) {
    ListStorage storage;

    EXPECT_EQ(storage.Head(), nullptr);
}

TEST(Storage, HeadReturnsFirstNode) {
    const std::string file_name = TestFile("test_storage_head.txt");

    WriteFile(
        file_name,
        "apple;-1\n"
        "banana;-1\n"
    );

    ListStorage storage = ListStorage::FromTextFile(file_name);

    ASSERT_EQ(storage.nodes.size(), 2u);
    EXPECT_EQ(storage.Head(), &storage.nodes[0]);
}