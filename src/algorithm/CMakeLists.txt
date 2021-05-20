add_library(algorithm STATIC
        include/data_for_run.hpp
        include/genetic_algorithm.hpp
        sources/genetic_algorithm.cpp
        )
target_include_directories(algorithm PUBLIC include)
