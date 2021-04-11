add_executable(application_server sources/source.cpp include/include.hpp)
target_include_directories(application_server PUBLIC include third_party ${Boost_INCLUDE_DIR})

hunter_add_package(Boost COMPONENTS regex)
find_package(Boost CONFIG REQUIRED COMPONENTS regex thread)

target_link_libraries(application_server PUBLIC Boost::regex Boost::thread)
