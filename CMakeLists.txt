cmake_minimum_required(VERSION 3.0)

project(piyo-piyo)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)

add_subdirectory(lib/glew)

include_directories(${piyo-piyo_SOURCE_DIR}/include)
include_directories(${piyo-piyo_SOURCE_DIR}/lib/glew/include)
include_directories(${OPENGL_INCLUDE_DIRS})

add_definitions(-DGLEW_STATIC)
add_executable(
    piyo-piyo
    src/Mesh.cpp
    src/GLShader.cpp
    src/Matrix.cpp
    src/Vector.cpp
    src/Component.cpp
    src/Input.cpp
    src/Window.cpp
    src/Engine.cpp
    src/main.cpp
)

target_link_libraries(piyo-piyo glew ${OPENGL_LIBRARIES})
