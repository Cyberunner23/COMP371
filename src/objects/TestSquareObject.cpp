//
// Created by cyberunner23 on 1/22/18.
//

#include "TestSquareObject.hpp"

TestSquareObject::TestSquareObject(Shader &shader) : IRenderObject(shader)
{

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

void TestSquareObject::render(glm::mat4 vpMatrix)
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

void TestSquareObject::uploadToGPU()
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
