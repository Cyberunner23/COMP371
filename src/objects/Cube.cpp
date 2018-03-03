
#include "Cube.hpp"

Cube::Cube()
{
    _mesh = CubeMesh;
    _uvs = CubeUV;

    _texture = std::make_unique<GLuint>(png_texture_load("data/horse.png", nullptr, nullptr));

    _colors = CubeTestColors;
    _normals = CubeNormals;

    uploadToGPU();
}

Cube::Cube(glm::vec3 color)
{
    _mesh = CubeMesh;
    _uvs = CubeUV;

    _texture = std::make_unique<GLuint>(png_texture_load("data/horse.png", nullptr, nullptr));
    _normals = CubeNormals;

    for (int i = 0; i < 36; i++)
    {
        _colors.emplace_back(color);
    }

    uploadToGPU();
}
