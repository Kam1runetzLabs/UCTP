add_library(ScheduleAlgorithm STATIC
        include/scheduleMaker.hpp
        include/entities.hpp
        sources/scheduleMaker.cpp)
target_include_directories(ScheduleAlgorithm PUBLIC include)

