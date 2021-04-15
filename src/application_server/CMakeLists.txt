add_executable(application_server
        main.cpp

        include/commands/IControllerCommand.hpp
        include/controllers/Controller.hpp
        include/controllers/DefaultCommandRouter.hpp
        include/controllers/IControllerCommandRouter.hpp
        include/datatypes/HttpContext.hpp
        include/datatypes/ModelContext.hpp
        include/datatypes/ControllerContext.hpp
        include/models/AbstractModel.hpp
        include/tools/FastCGIProcessor.hpp
        include/tools/ICGIProcessor.hpp
        include/views/AbstractView.hpp
        include/views/UCTPView.hpp
        include/Application.hpp

        sources/source.cpp
        )

target_include_directories(application_server PUBLIC include thirdparty ${Boost_INCLUDE_DIR})

hunter_add_package(Boost COMPONENTS regex)
find_package(Boost CONFIG REQUIRED COMPONENTS regex thread)

target_link_libraries(application_server PUBLIC Boost::regex Boost::thread nlohmann_json)
