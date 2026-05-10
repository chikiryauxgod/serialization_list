#pragma once

#include "../include/list_operator.hpp"
#include "../include/config.hpp"

class App {
public:
    App(const AppConfig& config, int argc, char** argv);

    void Run();

private:
    void ApplyCliOverrides();
    void ExecutePipeline();

private:
    AppConfig config_;
    int argc_;
    char** argv_;
};