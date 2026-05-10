#include "../include/list_operator.hpp"
#include "../include/list_parser.hpp"

#include <fstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <cstdint>

namespace {

constexpr std::size_t kMaxNodes = 1'000'000;
constexpr std::size_t kMaxDataSize = 1000;
constexpr char kSeparator = ';';

} // namespace


ListNode* ListStorage::Head() {
    return nodes.empty() ? nullptr : &nodes.front();
}


void ListStorage::FillLinks(const std::vector<int>& rand_indexes) {
    const std::size_t count = nodes.size();

    for (std::size_t i = 0; i < count; ++i) {
        nodes[i].prev = (i == 0) ? nullptr : &nodes[i - 1];
        nodes[i].next = (i + 1 == count) ? nullptr : &nodes[i + 1];
    }

    for (std::size_t i = 0; i < count; ++i) {
        const int rand_index = rand_indexes[i];

        if (rand_index == -1) {
            nodes[i].rand = nullptr;
            continue;
        }

        if (rand_index < 0 || static_cast<std::size_t>(rand_index) >= count) {
            throw std::runtime_error(
                "node " + std::to_string(i) + ": rand index is out of range"
            );
        }

        nodes[i].rand = &nodes[static_cast<std::size_t>(rand_index)];
    }
}


ListStorage ListStorage::FromTextFile(const std::string& file_name) {
    std::ifstream input(file_name);

    if (!input) {
        throw std::runtime_error("failed to open " + file_name);
    }

    ListStorage storage;
    std::vector<int> rand_indexes;

    std::string line;
    std::size_t line_number = 0;

    while (std::getline(input, line)) {
        ++line_number;

        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (storage.nodes.size() == kMaxNodes) {
            throw std::runtime_error("too many nodes");
        }

        auto [data, rand_index] = ParseLine(line, line_number);

        storage.nodes.push_back(ListNode{});
        storage.nodes.back().data = std::move(data);

        rand_indexes.push_back(rand_index);
    }

    storage.FillLinks(rand_indexes);

    return storage;
}


void ListStorage::PrintList(ListNode* head) {
    std::unordered_map<ListNode*, std::size_t> indexes;
    std::size_t index = 0;

    for (ListNode* current = head; current != nullptr; current = current->next) {
        indexes[current] = index++;
    }

    for (ListNode* current = head; current != nullptr; current = current->next) {
        std::cout << current->data << ';';
        if (current->rand == nullptr) {
            std::cout << -1;
        } else {
            std::cout << indexes.at(current->rand);
        }
        std::cout << '\n';
    }
}


void ListStorage::Serialize(const std::string& file_name) const {
    std::ofstream output(file_name, std::ios::binary);

    if (!output) {
        throw std::runtime_error("failed to open " + file_name);
    }

    const std::uint32_t count = static_cast<std::uint32_t>(nodes.size());

    output.write(
        reinterpret_cast<const char*>(&count),
        sizeof(count)
    );

    std::unordered_map<const ListNode*, std::uint32_t> index_by_node;
    index_by_node.reserve(nodes.size());

    for (std::uint32_t i = 0; i < count; ++i) {
        index_by_node[&nodes[i]] = i;
    }

    for (const auto& node : nodes) {
        const std::uint16_t data_size =
            static_cast<std::uint16_t>(node.data.size());

        output.write(
            reinterpret_cast<const char*>(&data_size),
            sizeof(data_size)
        );

        output.write(
            node.data.data(),
            static_cast<std::streamsize>(data_size)
        );

        std::int32_t rand_index = -1;

        if (node.rand != nullptr) {
            rand_index = static_cast<std::int32_t>(
                index_by_node.at(node.rand)
            );
        }

        output.write(
            reinterpret_cast<const char*>(&rand_index),
            sizeof(rand_index)
        );
    }

    if (!output) {
        throw std::runtime_error("failed to write " + file_name);
    }
}


ListStorage ListStorage::Deserialize(const std::string& file_name) {
    std::ifstream input(file_name, std::ios::binary);

    if (!input) {
        throw std::runtime_error("failed to open " + file_name);
    }

    ListStorage storage;

    std::uint32_t count = 0;

    if (!input.read(
            reinterpret_cast<char*>(&count),
            sizeof(count)
        )) {
        throw std::runtime_error("corrupted binary file");
    }

    if (count > kMaxNodes) {
        throw std::runtime_error("too many nodes");
    }

    std::vector<int> rand_indexes;
    rand_indexes.reserve(count);

    storage.nodes.resize(count);

    for (std::uint32_t i = 0; i < count; ++i) {
        std::uint16_t data_size = 0;

        if (!input.read(
                reinterpret_cast<char*>(&data_size),
                sizeof(data_size)
            )) {
            throw std::runtime_error("corrupted binary file");
        }

        if (data_size > kMaxDataSize) {
            throw std::runtime_error("corrupted binary file");
        }

        storage.nodes[i].data.resize(data_size);

        if (!input.read(
                storage.nodes[i].data.data(),
                static_cast<std::streamsize>(data_size)
            )) {
            throw std::runtime_error("corrupted binary file");
        }

        std::int32_t rand_index = 0;

        if (!input.read(
                reinterpret_cast<char*>(&rand_index),
                sizeof(rand_index)
            )) {
            throw std::runtime_error("corrupted binary file");
        }

        if (rand_index == -1) {
            rand_indexes.push_back(-1);
        } else {
            if (rand_index < 0 ||
                static_cast<std::uint32_t>(rand_index) >= count) {
                throw std::runtime_error("corrupted binary file");
            }

            rand_indexes.push_back(rand_index);
        }
    }

    storage.FillLinks(rand_indexes);

    return storage;
}