cmake_minimum_required(VERSION 3.0)

#------------------------------------------------------------------------------
# CMake Policies
#------------------------------------------------------------------------------

if(POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()


#------------------------------------------------------------------------------
# Hunter & Project
#
# Note: I am using the Hunter package manager for cmake
# This is an external project that I am using exclusively
# as a utility for my cmake build file. For those interested,
# it can be found at https://github.com/ruslo/hunter
#
# I am using this since I do not want to assume that the markers
# have the libraries preinstalled on their system as well as I do not
# want to assume the operating system they are using.
#------------------------------------------------------------------------------

include("cmake/HunterGate.cmake")

HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.19.232.tar.gz"
    SHA1 "a412c45fe4c5a72fed386f62dd8d753bd4fd3d11"
)

project(COMP371)

#Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)


#Hunter Packages
hunter_add_package(glew)
find_package(glew CONFIG REQUIRED)

hunter_add_package(glfw)
find_package(glfw3 CONFIG REQUIRED)

hunter_add_package(glm)
find_package(glm CONFIG REQUIRED)


#------------------------------------------------------------------------------
# Non-Hunter Dependencies
#------------------------------------------------------------------------------

find_package(OpenGL REQUIRED)


#------------------------------------------------------------------------------
# Source files
#------------------------------------------------------------------------------

set(SRCS
    src/main.cpp
    src/Camera.hpp
    src/Camera.cpp
    src/Shader.hpp
    src/Shader.cpp
    src/objects/AxisLinesObject.hpp
    src/objects/AxisLinesObject.cpp
    src/objects/IRenderObject.hpp
    src/objects/IRenderObject.cpp
    src/objects/TestTriangleObject.hpp
    src/objects/TestTriangleObject.cpp
)


#------------------------------------------------------------------------------
# Shader files
#------------------------------------------------------------------------------

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/shaders)
configure_file(shaders/generic.vert shaders/generic.vert COPYONLY)
configure_file(shaders/generic.frag shaders/generic.frag COPYONLY)


#------------------------------------------------------------------------------
# Executable
#------------------------------------------------------------------------------

add_executable(${PROJECT_NAME} ${SRCS} ${HEADERS})
target_link_libraries(${PROJECT_NAME}
    glew::glew
    glfw
    glm
    OpenGL::GL
)