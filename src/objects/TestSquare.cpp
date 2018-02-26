
#include "TestSquare.hpp"

TestSquare::TestSquare(float scale): IRenderNode()
{
    _debugName = "TestSquare";

    _mesh = {
            glm::vec3(0.0f,         0.0f,         0.0f), //upper
            glm::vec3(0.1f * scale, 0.1f * scale, 0.0f),
            glm::vec3(0.0f,         0.1f * scale, 0.0f),

            glm::vec3(0.0f,         0.0f,         0.0f), //lower
            glm::vec3(0.1f * scale, 0.0f,         0.0f),
            glm::vec3(0.1f * scale, 0.1f * scale, 0.0f)
    };

    _colors = {
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(1.0f, 0.0f, 0.0f),

            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
    };

    _texture = std::make_unique<GLuint>(png_texture_load("data/grass.png", nullptr, nullptr));

    _uvs = {
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f),

            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f)

    };

    uploadToGPU();
}
