#include "../include/list_operator.hpp"

#include <iostream>
#include <stdexcept>
#include <unordered_map>

int main() {
    
    try {
        auto storage = ListStorage::FromTextFile("inlet.in");
        ListNode* head = storage.Head();
        storage.PrintList(head);
        storage.Serialize("outlet.out");

        storage = ListStorage::Deserialize("outlet.out");
        ListNode* deserialized_head = storage.Head();
        storage.PrintList(deserialized_head);
        storage.Serialize("outlet2.out");


    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
