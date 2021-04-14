add_library(ScheduleAlgorithm STATIC
        include/include.hpp
        sources/source.cpp
        include/scheduleMaker.hpp
        include/entities.hpp
        sources/scheduleMaker.cpp)
target_include_directories(ScheduleAlgorithm PUBLIC include)

