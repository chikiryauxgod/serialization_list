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
    static ListStorage Deserialize(const std::string& file_name);
    
private:
    

    void FillLinks(const std::vector<int>& rand_indexes);
};