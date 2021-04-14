add_executable(builders_tests builders_tests.cpp)
target_link_libraries(builders_tests GTest::gtest_main ScheduleAlgorithm)

add_test(NAME builders_tests
        COMMAND builders_tests)