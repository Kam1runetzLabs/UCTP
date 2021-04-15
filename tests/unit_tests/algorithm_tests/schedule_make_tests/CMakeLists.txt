add_executable(schedule_make_tests schedule_make_tests.cpp)
target_link_libraries(schedule_make_tests GTest::gtest_main ScheduleAlgorithm)

add_test(NAME schedule_make_tests
        COMMAND schedule_make_tests)