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
            std::cout << "x: " << i << " y: " << j << std::endl;
            generateSquare(i, j);
        }
    }

    uploadToGPU();
}

void FloorGridObject::render(glm::mat4 vpMatrix)
{

    glBindVertexArray(_VAO);
    _shader.useShader();

    glm::mat4 MVP = vpMatrix * _modelMatrix;
    if (!_shader.setUniformM4fv("MVP", MVP))
    {
        std::cout << "ERROR: failed to set the MVP" << std::endl;
    }

    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)_mesh.size());

    _shader.unUseShader();
    glBindVertexArray(0);
}

void FloorGridObject::uploadToGPU()
{

    glBindVertexArray(_VAO);

    //Vertices
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*_mesh.size(), &_mesh[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    //Line Colors
    glBindBuffer(GL_ARRAY_BUFFER, _CBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*_colors.size(), &_colors[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

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
