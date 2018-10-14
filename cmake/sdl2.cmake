include(ExternalProject)
find_package(SDL2 2.0 QUIET)

if(SDL2_FOUND)
    message(STATUS "Found SDL2")
    add_library(sdl2 INTERFACE)
else()
if(WIN32)
    message(STATUS "SDL2 not found - will build from source")
    ExternalProject_Add(sdl2 PREFIX sdl2
    	URL https://www.libsdl.org/release/SDL2-2.0.8.zip
        UPDATE_COMMAND ""
        CMAKE_ARGS
            "-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>"
            "-DCMAKE_DEBUG_POSTFIX=\"\""
        CMAKE_CACHE_ARGS
            "-DCMAKE_C_COMPILER:FILEPATH=${CMAKE_C_COMPILER}"
            "-DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}"
        LOG_DOWNLOAD 1 LOG_UPDATE 1 LOG_CONFIGURE 1 LOG_BUILD 1 LOG_INSTALL 1
    )

    ExternalProject_Get_Property(sdl2 INSTALL_DIR)

    set(SDL2_INCLUDE_DIRS ${INSTALL_DIR}/include)
    set(SDL2_LIBRARIES ${INSTALL_DIR}/lib/SDL2$<$<CONFIG:Debug>:d>.lib ${INSTALL_DIR}/lib/SDL2main$<$<CONFIG:Debug>:d>.lib)
    add_custom_command(
        TARGET sdl2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${INSTALL_DIR}/bin/SDL2$<$<CONFIG:Debug>:d>.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SDL2$<$<CONFIG:Debug>:d>.dll
	)
endif()
endif()

set(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIRS} CACHE STRING "")
set(SDL2_LIBRARIES ${SDL2_LIBRARIES} CACHE STRING "")
