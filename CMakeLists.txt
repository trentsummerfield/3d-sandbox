cmake_minimum_required(VERSION 3.10)
project(3d-sandbox LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE bin)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(glew)
include(sdl2)
include(opengl)


include_directories(${GLEW_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS})
add_executable(3d-sandbox 
    src/App.cpp
    src/Camera.cpp
    src/grid.cpp
    src/Loader.cpp
    src/main.cpp
    src/OpenGLGeo.cpp
    src/platform.cpp
    src/Shader.cpp
    src/ShaderManager.cpp
)
add_dependencies(3d-sandbox glew sdl2)
target_link_libraries(3d-sandbox 
    ${GLEW_LIBRARIES} 
    ${SDL2_LIBRARIES} 
    ${OPENGL_LIBRARIES}
)

if(WIN32)
	add_definitions(-D_USE_MATH_DEFINES -D_CRT_SECURE_NO_WARNINGS)
	SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}")
endif()
