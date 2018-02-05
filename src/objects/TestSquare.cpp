//
// Created by cyberunner23 on 1/22/18.
//

#include "TestSquare.hpp"

TestSquare::TestSquare(): IRenderNode()
{
    _debugName = "TestSquare";

    _mesh = {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.1f, 0.1f, 0.0f),
            glm::vec3(0.0f, 0.1f, 0.0f),

            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.1f, 0.0f, 0.0f),
            glm::vec3(0.1f, 0.1f, 0.0f)
    };

    _colors = {
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(1.0f, 0.0f, 0.0f),

            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
    };

    uploadToGPU();
}
