#include "../include/app.hpp"
#include <iostream>

int main(int argc, char** argv) {
    try {
        AppConfig config = AppConfig::FromFile("config.cfg");

        App app(config, argc, argv);
        app.Run();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
}