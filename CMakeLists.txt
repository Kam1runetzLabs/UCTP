cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)
option(BUILD_COVERAGE "Build coverage" OFF)

include("${CMAKE_CURRENT_SOURCE_DIR}/tools/gate/cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.278.tar.gz"
        SHA1 "35fa55bc1dfcf9f4d7264f8bb26cd1759ce1ae07"
)

project(UCTP CXX)

hunter_add_package(Boost COMPONENTS log thread system)

if (BUILD_COVERAGE)
  string(APPEND CMAKE_CXX_FLAGS " -lgcov --coverage")
endif ()

if (BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif ()

string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

add_subdirectory(src)

# cxx options
if (MSVC)
  set(CMAKE_CXX_FLAGS         "/DUNICODE /D_UNICODE")
  set(CMAKE_CXX_FLAGS_DEBUG   "/DEBUG")
  set(CMAKE_CXX_FLAGS_RELEASE "/O2 /DQT_NO_DEBUG /DTF_NO_DEBUG")
else()
  set(CMAKE_CXX_FLAGS         "-Wall -W -D_REENTRANT")
  set(CMAKE_CXX_FLAGS_DEBUG   "-g")
  set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DQT_NO_DEBUG -DTF_NO_DEBUG")
endif()

# Auto generate moc files
if (POLICY CMP0071)
  cmake_policy(SET CMP0071 NEW)
endif()
set(CMAKE_AUTOMOC ON)

find_package(TreeFrog REQUIRED)
add_subdirectory(helpers)
add_subdirectory(models)
add_subdirectory(views)
add_subdirectory(controllers)

message(STATUS "Set CMAKE_GENERATOR: ${CMAKE_GENERATOR}")
message(STATUS "Set CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# Cutom target - cmake
include(${PROJECT_SOURCE_DIR}/cmake/TargetCmake.cmake)