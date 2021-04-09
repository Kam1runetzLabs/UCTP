add_library(example STATIC include/header.hpp sources/source.cpp)
target_include_directories(example PUBLIC include/)
