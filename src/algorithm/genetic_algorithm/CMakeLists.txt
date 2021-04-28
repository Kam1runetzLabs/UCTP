add_library(gen_alg STATIC
        include/genetic_algorithm.hpp
        source/genetic_algorithm.cpp)
target_include_directories(gen_alg PUBLIC include)