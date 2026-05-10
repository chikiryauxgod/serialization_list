cmake_minimum_required(VERSION 3.16)

project(serialization_list LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(core
    src/list_operator.cpp
    src/list_parser.cpp
    src/config.cpp
    src/app.cpp
)

target_include_directories(core PUBLIC include)

add_executable(app
    app/main.cpp
)

target_link_libraries(app PRIVATE core)
enable_testing()

add_subdirectory(googletest)
add_subdirectory(tests)