#include "../include/list_operator.hpp"
#include "../include/config.hpp"

#include <iostream>
#include <stdexcept>

int main(int argc, char** argv) {
    try {
        AppConfig config = AppConfig::FromFile("config.cfg");

        config.OverrideFromArgs(argc, argv);

        if (config.input_file.empty()) {
            config.input_file = "inlet.in";
        }

        if (config.output_file.empty()) {
            config.output_file = "outlet.out";
        }

        ListStorage storage = ListStorage::FromTextFile(config.input_file);

        storage.Serialize(config.output_file);

        ListStorage restored = ListStorage::Deserialize(config.output_file);

        storage.PrintList(storage.Head());
        restored.PrintList(restored.Head());

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}