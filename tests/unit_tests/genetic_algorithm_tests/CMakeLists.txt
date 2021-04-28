add_executable(genetic_alg_tests genetic_algorithm_tests.cpp)
target_link_libraries(genetic_alg_tests GTest::gtest_main gen_alg)

add_test(NAME genetic_alg_tests
        COMMAND genetic_alg_tests)