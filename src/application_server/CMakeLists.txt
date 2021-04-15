add_executable(application_server
        include/commands/IControllerCommand.hpp
        include/commands/CreateStudyStreamCommand.hpp
        include/commands/SearchStudyStreamCommand.hpp
        include/commands/UpdateStudyStreamCommand.hpp
        include/commands/DeleteStudyStreamCommand.hpp
        include/commands/SearchLessonCommand.hpp
        include/commands/CalculateLessonCommand.hpp
        include/commands/SearchSubjectCommand.hpp
        include/commands/CreateSubjectCommand.hpp
        include/commands/UpdateSubjectCommand.hpp
        include/commands/DeleteSubjectCommand.hpp
        include/commands/SearchAuditoryCommand.hpp
        include/commands/CreateAuditoryCommand.hpp
        include/commands/UpdateAuditoryCommand.hpp
        include/commands/DeleteAuditoryCommand.hpp
        include/commands/SearchTeacherCommand.hpp
        include/commands/CreateTeacherCommand.hpp
        include/commands/UpdateTeacherCommand.hpp
        include/commands/DeleteTeacherCommand.hpp
        include/commands/CreateGroupCommand.hpp
        include/commands/SearchGroupCommand.hpp
        include/commands/UpdateGroupCommand.hpp
        include/commands/DeleteGroupCommand.hpp
        include/controllers/Controller.hpp
        include/controllers/DefaultCommandRouter.hpp
        include/controllers/IControllerCommandRouter.hpp
        include/datatypes/DBContext.hpp
        include/datatypes/HttpContext.hpp
        include/datatypes/ModelContext.hpp
        include/datatypes/ControllerContext.hpp
        include/db_types/entities.hpp
        include/models/AbstractModel.hpp
        include/models/AuditoryModel.hpp
        include/models/GroupModel.hpp
        include/models/ScheduleModel.hpp
        include/models/StudyStreamModel.hpp
        include/models/SubjectModel.hpp
        include/models/TeacherModel.hpp
        include/tools/AbstractDBConnector.hpp
        include/tools/FastCGIProcessor.hpp
        include/tools/ICGIProcessor.hpp
        include/tools/PGConnector.hpp
        include/views/AbstractView.hpp
        include/views/UCTPView.hpp
        include/Application.hpp

        sources/source.cpp)

target_include_directories(application_server PUBLIC include thirdparty ${Boost_INCLUDE_DIR})

hunter_add_package(Boost COMPONENTS regex)
find_package(Boost CONFIG REQUIRED COMPONENTS regex thread)

target_link_libraries(application_server PUBLIC Boost::regex Boost::thread)
