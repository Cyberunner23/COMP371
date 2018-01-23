//
// Created by cyberunner23 on 1/22/18.
//

#include "FloorGridObject.hpp"

FloorGridObject::FloorGridObject(Shader &shader) : IRenderObject(shader)
{

    for (int i = -51; i <= 49; i++)
    {
        for (int j = -51; j <= 49; j++)
        {
            generateSquare(i, j);
        }
    }

    uploadToGPU();
}


void FloorGridObject::generateSquare(int posX, int posZ)
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
    }

}
