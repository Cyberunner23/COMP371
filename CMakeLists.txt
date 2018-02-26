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
    URL "https://github.com/ruslo/hunter/archive/v0.19.245.tar.gz"
    SHA1 "34c8f443ef188adc5b3f0106ec5b06999164e1c8"
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

hunter_add_package(PNG)
find_package(PNG CONFIG REQUIRED)


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
    src/PNGLoader.hpp
    src/Renderer.hpp
    src/Renderer.cpp
    src/Shader.hpp
    src/Shader.cpp
    src/ShaderGuard.hpp
    src/TextureGuard.hpp
    src/VAOGuard.hpp
    src/Window.hpp
    src/Window.cpp
    src/objects/AxisLines.hpp
    src/objects/AxisLines.cpp
    src/objects/Cube.hpp
    src/objects/Cube.cpp
    src/objects/FloorGrid.hpp
    src/objects/FloorGrid.cpp
    src/objects/Horse.hpp
    src/objects/Horse.cpp
    src/objects/IRenderNode.hpp
    src/objects/IRenderNode.cpp
    src/objects/IRenderAxisNode.hpp
    src/objects/IRenderAxisNode.cpp
    src/objects/TestSquare.hpp
    src/objects/TestSquare.cpp
    src/objects/SceneRoot.hpp
)


#------------------------------------------------------------------------------
# Shader files
#------------------------------------------------------------------------------

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/shaders)
configure_file(shaders/generic.vert shaders/generic.vert COPYONLY)
configure_file(shaders/generic.frag shaders/generic.frag COPYONLY)
configure_file(shaders/texture.vert shaders/texture.vert COPYONLY)
configure_file(shaders/texture.frag shaders/texture.frag COPYONLY)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/data)
configure_file(data/grass.png data/grass.png COPYONLY)
configure_file(data/horse.png data/horse.png COPYONLY)


#------------------------------------------------------------------------------
# Executable
#------------------------------------------------------------------------------

add_executable(${PROJECT_NAME} ${SRCS} ${HEADERS})
target_link_libraries(${PROJECT_NAME}
    glew::glew
    glfw
    glm
    OpenGL::GL
    PNG::png
)