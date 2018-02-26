//
// Created by cyberunner23 on 2/4/18.
//

#include "Cube.hpp"

Cube::Cube(glm::vec3 color)
{
    _mesh = CubeMesh;
    _uvs = CubeUV;

    _texture = std::make_unique<GLuint>(png_texture_load("data/horse.png", nullptr, nullptr));

    for (int i = 0; i < 36; i++)
    {
        _colors.emplace_back(color);
    }

    uploadToGPU();
}
