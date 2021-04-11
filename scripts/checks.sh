#!/usr/bin/env bash

set -e

export CTEST_OUTPUT_ON_FAILURE=true
export ASAN_OPTIONS=allocator_may_return_null=1
export TSAN_OPTIONS=allocator_may_return_null=1

# address sanitizer
CMAKE_CONFIG_OPTIONS="-DHUNTER_CONFIGURATION_TYPES=Debug -DCMAKE_BUILD_TYPE=Debug"
CMAKE_TOOLCHAIN_OPTIONOS="-DCMAKE_TOOLCHAIN_FILE='$(pwd)/tools/polly/sanitize-address-cxx17-pic.cmake'"
CMAKE_OPTIONS="$CMAKE_CONFIG_OPTIONS $CMAKE_TOOLCHAIN_OPTIONS "

rm -rf B_builds
cmake -H. -B_builds $CMAKE_OPTIONS
cmake --build _builds
./_builds/tests/unit_tests/tests

# thread sanitizer
# CMAKE_CONFIG_OPTIONS="-DHUNTER_CONFIGURATION_TYPE=Debug -DCMAKE_BUILD_TYPE=Debug"
# CMAKE_TOOLCHAIN_OPTIONS="-DCMAKE_TOOLCHAIN_FILE='$(pwd)/tools/polly/sanitize-thread-cxx17-pic.cmake'"
# CMAKE_OPTIONS="$CMAKE_TOOLCHAIN_OPTIONS $CMAKE_CONFIG_OPTIONS"

# rm -rf B_builds
# cmake -H. -B_builds $CMAKE_OPTIONS
# cmake --build _builds
# ./_builds/tests/unit_tests/tests

# valgrind memcheck
CMAKE_CONFIG_OPTIONS="-DHUNTER_CONFIGURATION_TYPE=Debug -DCMAKE_BUILD_TYPE=Debug"
CMAKE_PIC_OPTS="-DCMAKE_TOOLCHAIN_FILE='$(pwd)/tools/polly/gcc-pic-cxx17.cmake'"
CMAKE_OPTIONS="$CMAKE_CONFIG_OPTIONS $CMAKE_PIC_OPTS"

rm -rf B_builds
cmake -H. -B_builds $CMAKE_OPTIONS
cmake --build _builds
valgrind --tool=memcheck --leak-check=full --track-origins=yes ./_builds/tests/unit_tests/tests
