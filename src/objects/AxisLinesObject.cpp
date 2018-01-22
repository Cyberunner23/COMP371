//
// Created by cyberunner23 on 1/21/18.
//

#include "AxisLinesObject.hpp"

AxisLinesObject::AxisLinesObject(Shader &shader) : IRenderObject(shader)
{

    _mesh = {
            glm::vec3(0, 0, 0),
            glm::vec3(1, 0, 0), // X Line
            glm::vec3(0, 0, 0),
            glm::vec3(0, 1, 0), // Y Line
            glm::vec3(0, 0, 0),
            glm::vec3(0, 0, 1)  // Z Line
    };

    _lineColors = {
            glm::vec3(1, 0, 0),
            glm::vec3(1, 0, 0), // X Line
            glm::vec3(0, 1, 0),
            glm::vec3(0, 1, 0), // Y Line
            glm::vec3(0, 0, 1),
            glm::vec3(0, 0, 1)  // Z Line
    };

    uploadToGPU();

}


void AxisLinesObject::render(glm::mat4 vpMatrix)
{

    glBindVertexArray(_VAO);
    _shader.useShader();

    glm::mat4 MVP = vpMatrix * _modelMatrix;
    if (!_shader.setUniformM4fv("MVP", MVP))
    {
        std::cout << "ERROR: failed to set the MVP" << std::endl;
    }

    glDrawArrays(GL_LINES, 0, (GLsizei)_mesh.size());

    _shader.unUseShader();
    glBindVertexArray(0);
}


void AxisLinesObject::uploadToGPU()
{

    glBindVertexArray(_VAO);

    //Vertices
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*_mesh.size(), &_mesh[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    //Line Colors
    glBindBuffer(GL_ARRAY_BUFFER, _CBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*_lineColors.size(), &_lineColors[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

}
