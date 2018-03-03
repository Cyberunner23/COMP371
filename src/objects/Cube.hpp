
#pragma once

#include "IRenderNode.hpp"
#include "../PNGLoader.hpp"


const std::vector<glm::vec3> CubeMesh = {

        glm::vec3(-0.5f, 0.0f, -0.5f), //Bottom
        glm::vec3( 0.5f, 0.0f,  0.5f),
        glm::vec3(-0.5f, 0.0f,  0.5f),
        glm::vec3(-0.5f, 0.0f, -0.5f),
        glm::vec3( 0.5f, 0.0f, -0.5f),
        glm::vec3( 0.5f, 0.0f,  0.5f),

        glm::vec3(-0.5f, 1.0f, -0.5f), //Top
        glm::vec3(-0.5f, 1.0f,  0.5f),
        glm::vec3( 0.5f, 1.0f,  0.5f),
        glm::vec3(-0.5f, 1.0f, -0.5f),
        glm::vec3( 0.5f, 1.0f,  0.5f),
        glm::vec3( 0.5f, 1.0f, -0.5f),

        glm::vec3(-0.5f, 0.0f,  0.5f), //Front
        glm::vec3( 0.5f, 0.0f,  0.5f),
        glm::vec3(-0.5f, 1.0f,  0.5f),
        glm::vec3(-0.5f, 1.0f,  0.5f),
        glm::vec3( 0.5f, 0.0f,  0.5f),
        glm::vec3( 0.5f, 1.0f,  0.5f),

        glm::vec3(-0.5f, 0.0f, -0.5f), //Back
        glm::vec3(-0.5f, 1.0f, -0.5f),
        glm::vec3( 0.5f, 0.0f, -0.5f),
        glm::vec3(-0.5f, 1.0f, -0.5f),
        glm::vec3( 0.5f, 1.0f, -0.5f),
        glm::vec3( 0.5f, 0.0f, -0.5f),

        glm::vec3(-0.5f, 0.0f, -0.5f), //Left
        glm::vec3(-0.5f, 0.0f,  0.5f),
        glm::vec3(-0.5f, 1.0f,  0.5f),
        glm::vec3(-0.5f, 1.0f,  0.5f),
        glm::vec3(-0.5f, 1.0f, -0.5f),
        glm::vec3(-0.5f, 0.0f, -0.5f),

        glm::vec3( 0.5f, 0.0f,  0.5f), //Right
        glm::vec3( 0.5f, 0.0f, -0.5f),
        glm::vec3( 0.5f, 1.0f, -0.5f),
        glm::vec3( 0.5f, 1.0f, -0.5f),
        glm::vec3( 0.5f, 1.0f,  0.5f),
        glm::vec3( 0.5f, 0.0f,  0.5f),

};


const std::vector<glm::vec3> CubeTestColors = {
        glm::vec3(1.0f, 1.0f, 1.0f), //Bottom
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),

        glm::vec3(0.0f, 0.0f, 0.0f), //Top
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),

        glm::vec3(0.5f, 0.5f, 0.5f), //Front
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),

        glm::vec3(1.0f, 0.0f, 0.0f), //Back
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),

        glm::vec3(0.0f, 1.0f, 0.0f), //Left
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),

        glm::vec3(0.0f, 0.0f, 1.0f), //Right
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
};


const std::vector<glm::vec3> CubeNormals = {
        glm::vec3(0.0f, -1.0f, 0.0f),//Bottom
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),

        glm::vec3(0.0f, 1.0f, 0.0f),//Top
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),

        glm::vec3(0.0f, 0.0f, 1.0f),//Front
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),

        glm::vec3(0.0f, 0.0f, -1.0f),//Back
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),

        glm::vec3(-1.0f, 0.0f, 0.0f),//Left
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),

        glm::vec3(1.0f, 0.0f, 0.0f),//Right
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),

};


const std::vector<glm::vec2> CubeUV = {
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),

        glm::vec2(0.0f, 0.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(1.0f, 0.0f),

        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),

        glm::vec2(0.0f, 0.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(1.0f, 0.0f),

        glm::vec2(0.0f, 0.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(0.0f, 0.0f),

        glm::vec2(0.0f, 1.0f),
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f),

};


class Cube : public IRenderNode
{
public:
    Cube();
    explicit Cube(glm::vec3 color);
};
