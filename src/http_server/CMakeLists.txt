add_executable(http_server sources/source.cpp include/include.hpp)
target_include_directories(http_server PUBLIC include)

find_package(Boost CONFIG REQUIRED system thread)

target_link_libraries(http_server PUBLIC Boost::system Boost::thread)