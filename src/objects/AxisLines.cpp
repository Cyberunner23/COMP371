
#include "AxisLines.hpp"

AxisLines::AxisLines(float size)
{
    _debugName = "AxisLines";
    _renderMode = GL_LINES;

    _mesh = {
            glm::vec3(0.0f,        0.0f,        0.0f), // X Line
            glm::vec3(1.0f * size, 0.0f,        0.0f),
            glm::vec3(0.0f,        0.0f,        0.0f), // Y Line
            glm::vec3(0.0f,        1.0f * size, 0.0f),
            glm::vec3(0.0f,        0.0f,        0.0f), // Z Line
            glm::vec3(0.0f,        0.0f,        1.0f * size),
    };

    _colors= {
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 0.0f, 0.0f), // X Line
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f), // Y Line
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, 1.0f), // Z Line
    };

    uploadToGPU();
}

