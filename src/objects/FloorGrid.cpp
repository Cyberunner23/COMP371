
#include "FloorGrid.hpp"

FloorGrid::FloorGrid()
{
    _debugName = "FloorGrid";

    for (int i = -51; i <= 49; i++)
    {
        for (int j = -51; j <= 49; j++)
        {
            generateSquare(i, j);
        }
    }

    _texture = std::make_unique<GLuint>(png_texture_load("data/grass.png", nullptr, nullptr));

    uploadToGPU();
}

void FloorGrid::generateSquare(int posX, int posZ)
{

    std::vector<glm::vec3> color;
    if ((posX + posZ) % 2 == 0)
    {
        for (int i = 0; i < 6; i++)
        {
            color.push_back(evenColor);
        }
    }
    else
    {
        for (int i = 0; i < 6; i++)
        {
            color.push_back(oddColor);
        }
    }

    _colors.insert(_colors.end(), color.begin(), color.end());

    for (int i = 0; i < 6; i++)
    {
        glm::vec3 translated = glm::vec3(squareXZ[i].x + posX, squareXZ[i].y , squareXZ[i].z + posZ);
        _mesh.push_back(translated);
        _normals.emplace_back(0.0f, 1.0f, 0.0f);
    }

    _uvs.insert(_uvs.end(), squareUV.begin(), squareUV.end());

}
