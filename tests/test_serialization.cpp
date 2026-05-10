#include <gtest/gtest.h>

#include "../include/list_operator.hpp"

#include <fstream>

namespace {

void WriteFile(const std::string& file_name, const std::string& content) {
    std::ofstream out(file_name);
    out << content;
}

} // namespace

TEST(Serialization, RoundTripPreservesStructure) {
    const std::string input_file = "serialization_input.txt";
    const std::string binary_file = "serialization_output.bin";

    WriteFile(
        input_file,
        "apple;2\n"
        "banana;-1\n"
        "carrot;1\n"
    );

    ListStorage original = ListStorage::FromTextFile(input_file);

    original.Serialize(binary_file);

    ListStorage restored = ListStorage::Deserialize(binary_file);

    ASSERT_EQ(restored.nodes.size(), 3u);

    // data
    EXPECT_EQ(restored.nodes[0].data, "apple");
    EXPECT_EQ(restored.nodes[1].data, "banana");
    EXPECT_EQ(restored.nodes[2].data, "carrot");

    // prev
    EXPECT_EQ(restored.nodes[0].prev, nullptr);
    EXPECT_EQ(restored.nodes[1].prev, &restored.nodes[0]);
    EXPECT_EQ(restored.nodes[2].prev, &restored.nodes[1]);

    // next
    EXPECT_EQ(restored.nodes[0].next, &restored.nodes[1]);
    EXPECT_EQ(restored.nodes[1].next, &restored.nodes[2]);
    EXPECT_EQ(restored.nodes[2].next, nullptr);

    // rand
    EXPECT_EQ(restored.nodes[0].rand, &restored.nodes[2]);
    EXPECT_EQ(restored.nodes[1].rand, nullptr);
    EXPECT_EQ(restored.nodes[2].rand, &restored.nodes[1]);
}

TEST(Serialization, EmptyStorageRoundTrip) {
    const std::string binary_file = "empty_storage.bin";

    ListStorage original;
    original.Serialize(binary_file);

    ListStorage restored = ListStorage::Deserialize(binary_file);

    EXPECT_TRUE(restored.nodes.empty());
    EXPECT_EQ(restored.Head(), nullptr);
}