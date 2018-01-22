
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

glm::mat4 IRenderObject::computeRotationMatrix(glm::vec3 rot)
{
    glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), glm::radians(rot.z), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 rotate = rotZ * rotX * rotY;
}

glm::mat4 IRenderObject::computeModelMatrix()
{
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), _position);
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), _scale);

    return translate * scale * computeRotationMatrix(_rotation);
}
