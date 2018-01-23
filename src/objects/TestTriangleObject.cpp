//
// Created by cyberunner23 on 1/21/18.
//

#include "TestTriangleObject.hpp"

TestTriangleObject::TestTriangleObject(Shader &shader) : IRenderObject(shader)
{
    _mesh = {
            glm::vec3(-1, 0, 0),
            glm::vec3(0, 1, 0),
            glm::vec3(1, 0, 0)
    };

    _colors = {
            glm::vec3(1, 0, 0),
            glm::vec3(0, 1, 0),
            glm::vec3(0, 0, 1)
    };

    uploadToGPU();
}
