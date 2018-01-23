//
// Created by cyberunner23 on 1/21/18.
//

#include "AxisLinesObject.hpp"

AxisLinesObject::AxisLinesObject(Shader &shader) : IRenderObject(shader)
{

    _renderMode = GL_LINES;

    _mesh = {
            glm::vec3(0.0f, 0.0f, 0.0f), // X Line
            glm::vec3(5.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 0.0f), // Y Line
            glm::vec3(0.0f, 5.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 0.0f), // Z Line
            glm::vec3(0.0f, 0.0f, 5.0f),
    };

    _colors= {
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 0.0f, 0.0f), // X Line
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f), // Y Line
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, 1.0f),  // Z Line
    };

    uploadToGPU();

}
