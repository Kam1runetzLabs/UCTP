add_subdirectory(algorithm)
add_subdirectory(application_server)
add_subdirectory(http_server)

SET (ASSEMBLY
        application_server
        algorithm
        http_server
        PARENT SCOPE)