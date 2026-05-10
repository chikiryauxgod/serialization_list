add_executable(run_tests
    test_main.cpp
    test_parse.cpp
    test_storage.cpp
    test_serialization.cpp
    test_edge_cases.cpp
)

target_link_libraries(run_tests
    PRIVATE core
    gtest
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(run_tests)