hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)
add_executable(tests tests.cpp)
add_test(NAME tests COMMAND tests)
