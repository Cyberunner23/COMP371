
#pragma once

#include "IRenderNode.hpp"


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
        glm::vec3( 0.5f, 0.0f, -0.5f),
        glm::vec3(-0.5f, 1.0f, -0.5f),
        glm::vec3(-0.5f, 1.0f, -0.5f),
        glm::vec3( 0.5f, 0.0f, -0.5f),
        glm::vec3( 0.5f, 1.0f, -0.5f),

        glm::vec3(-0.5f, 0.0f, -0.5f), //Right
        glm::vec3(-0.5f, 0.0f,  0.5f),
        glm::vec3(-0.5f, 1.0f,  0.5f),
        glm::vec3(-0.5f, 1.0f,  0.5f),
        glm::vec3(-0.5f, 1.0f, -0.5f),
        glm::vec3(-0.5f, 0.0f, -0.5f),

        glm::vec3( 0.5f, 0.0f,  0.5f), //Left
        glm::vec3( 0.5f, 0.0f, -0.5f),
        glm::vec3( 0.5f, 1.0f, -0.5f),
        glm::vec3( 0.5f, 1.0f, -0.5f),
        glm::vec3( 0.5f, 1.0f,  0.5f),
        glm::vec3( 0.5f, 0.0f,  0.5f),

};


class Cube : public IRenderNode
{
public:
    Cube(glm::vec3 color);
};
