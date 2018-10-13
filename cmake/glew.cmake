include(ExternalProject)
find_package(GLEW 2.1 QUIET)

if(GLEW_FOUND)
    message(STATUS "Found GLEW")
else()
if(WIN32)
    message(STATUS "GLEW not found - will build from source")
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/glew-CMakeLists.txt
        "cmake_minimum_required(VERSION @CMAKE_VERSION@)\n\n"
        "add_subdirectory(build/cmake)\n"
    )

    ExternalProject_Add(glew PREFIX glew
        URL https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0.zip
        URL_HASH SHA1=85ea9f4d1279b107019e48b9174c34e86c634830
        UPDATE_COMMAND ""
        PATCH_COMMAND
            ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_BINARY_DIR}/glew-CMakeLists.txt
                <SOURCE_DIR>/CMakeLists.txt
        CMAKE_ARGS
            "-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>"
            "-DCMAKE_DEBUG_POSTFIX=\"\""
        CMAKE_CACHE_ARGS
            "-DCMAKE_C_COMPILER:FILEPATH=${CMAKE_C_COMPILER}"
            "-DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}"
        LOG_DOWNLOAD 1 LOG_UPDATE 1 LOG_CONFIGURE 1 LOG_BUILD 1 LOG_INSTALL 1
    )

    ExternalProject_Get_Property(glew INSTALL_DIR)
    set(GLEW_INCLUDE_DIRS ${INSTALL_DIR}/include)
    set(GLEW_LIBRARIES ${INSTALL_DIR}/lib/glew32.lib)
    add_custom_command(
        TARGET glew POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${INSTALL_DIR}/bin/glew32.dll
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glew32.dll)
endif()
endif()

set(GLEW_INCLUDE_DIRS ${GLEW_INCLUDE_DIRS} CACHE STRING "")
set(GLEW_LIBRARIES ${GLEW_LIBRARIES} CACHE STRING "")

