
#include "IRenderObject.hpp"

IRenderObject::IRenderObject(Shader &shader) : _position(0.0f, 0.0f, 0.0f),
                                              _scale(1.0f, 1.0f, 1.0f),
                                              _rotation(0.0f, 0.0f, 0.0f),
                                              _modelMatrix(computeModelMatrix()),
                                              _shader(shader)
{
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_CBO);
}


void IRenderObject::render(glm::mat4 vpMatrix)
{
    glBindVertexArray(_VAO);
    _shader.useShader();

    glm::mat4 MVP = vpMatrix * _modelMatrix;
    if (!_shader.setUniformM4fv("MVP", MVP))
    {
        std::cout << "ERROR: failed to set the MVP" << std::endl;
    }

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(_renderMode, 0, (GLsizei)_mesh.size());

    _shader.unUseShader();
    glBindVertexArray(0);
}


glm::vec3 IRenderObject::getPosition()
{
    return _position;
}

void IRenderObject::setPosition(glm::vec3 pos)
{
    _position = pos;
    _modelMatrix = computeModelMatrix();
}


glm::vec3 IRenderObject::getScale()
{
    return _scale;
}

void IRenderObject::setScale(glm::vec3 scale)
{
    _scale = scale;
    _modelMatrix = computeModelMatrix();
}


glm::vec3 IRenderObject::getRotation()
{
    return _rotation;
}

void IRenderObject::setRotation(glm::vec3 rotation)
{
    _rotation = rotation;
    _modelMatrix = computeModelMatrix();
}


glm::mat4 IRenderObject::getModelMatrix()
{
    return _modelMatrix;
}

glm::mat4 IRenderObject::computeModelMatrix()
{
    glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 rotate = rotZ * rotX * rotY;

    glm::mat4 translate = glm::translate(glm::mat4(1.0f), _position);
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), _scale);

    return translate * scale * rotate;
}


void IRenderObject::uploadToGPU()
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
