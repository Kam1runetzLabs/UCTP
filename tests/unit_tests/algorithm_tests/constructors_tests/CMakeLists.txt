add_executable(constructors_tests constructors_tests.cpp)
target_link_libraries(constructors_tests GTest::gtest_main ScheduleAlgorithm)

add_test(NAME constructors_tests
        COMMAND constructors_tests)