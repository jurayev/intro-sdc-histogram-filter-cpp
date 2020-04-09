add_executable(
        run_histogram_filter_tests
        histogram_filter_tests.cpp
)

target_link_libraries(run_histogram_filter_tests filter_src)
target_link_libraries(run_histogram_filter_tests gtest gtest_main gmock gmock_main)

add_test(NAME filter_test COMMAND run_histogram_filter_tests)
