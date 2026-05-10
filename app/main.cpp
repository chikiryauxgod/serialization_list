#include "../include/list_reader.hpp"

#include <iostream>
#include <stdexcept>
#include <unordered_map>

int main() {
    try {
        auto storage = ListStorage::FromTextFile("inlet.in");
        ListNode* head = storage.Head();

        storage.PrintList(head);
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
