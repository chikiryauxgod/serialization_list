#pragma once

#include "list_node.hpp"

#include <string>
#include <utility>
#include <vector>

class ListStorage {
public:

    std::vector<ListNode> nodes;
    ListNode* Head();
    static ListStorage FromTextFile(const std::string& file_name);
    void PrintList(ListNode* head);

    void Serialize(const std::string& file_name) const;

private:
    static std::pair<std::string, int> ParseLine(
        const std::string& line,
        std::size_t line_number
    );

    void FillLinks(const std::vector<int>& rand_indexes);
};