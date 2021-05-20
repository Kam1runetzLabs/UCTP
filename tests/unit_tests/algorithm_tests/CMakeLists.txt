hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

add_executable(genetic_algorithm_tests genetic_algorithm_tests.cpp)
target_link_libraries(genetic_algorithm_tests GTest::gtest_main algorithm)

add_test(NAME genetic_algorithm_tests
        COMMAND genetic_algorithm_tests)
