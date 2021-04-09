hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

add_executable(tests tests.cpp)
target_link_libraries(tests GTest::gtest_main)

add_test(NAME tests COMMAND tests)
