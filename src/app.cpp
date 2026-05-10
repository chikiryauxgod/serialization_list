#include "../include/app.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
App::App(const AppConfig& config, int argc, char** argv)
    : config_(config), argc_(argc), argv_(argv) {}

void App::ApplyCliOverrides() {
    for (int i = 1; i < argc_; ++i) {
        std::string arg = argv_[i];

        if (arg == "--input" && i + 1 < argc_) {
            config_.input_file = argv_[++i];
        }
        else if (arg == "--output" && i + 1 < argc_) {
            config_.output_file = argv_[++i];
        }
    }
}

void App::ExecutePipeline() {
    ListStorage storage =
        ListStorage::FromTextFile(config_.input_file);

    storage.Serialize(config_.output_file);

    ListStorage restored =
        ListStorage::Deserialize(config_.output_file);

    storage.PrintList(storage.Head());
    restored.PrintList(restored.Head());
}

void App::Run() {
    ApplyCliOverrides();
    ExecutePipeline();
}