add_executable(scheduleMakerTests scheduleMakerTests.cpp)
target_link_libraries(scheduleMakerTests GTest::gtest_main ScheduleAlgorithm)

add_test(NAME scheduleMakerUTests
        COMMAND scheduleMakerUTests)