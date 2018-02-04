
#include "IRenderNode.hpp"

IRenderNode::IRenderNode() : _position(0.0f, 0.0f, 0.0f),
                             _scale(1.0f, 1.0f, 1.0f),
                             _rotation(0.0f, 0.0f, 0.0f),
                             _modelMatrix(computeModelMatrix())
{
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_CBO);
}


void IRenderNode::addChildNode(std::shared_ptr<IRenderNode> node)
{
    _childNodes.push_back(node);
}

std::vector<std::shared_ptr<IRenderNode>>* IRenderNode::getChildren()
{
    return &_childNodes;
}

glm::vec3 IRenderNode::getPosition()
{
    return _position;
}

void IRenderNode::setPosition(glm::vec3&& pos)
{
    _position = std::move(pos);
    _modelMatrix = computeModelMatrix();
}


glm::vec3 IRenderNode::getScale()
{
    return _scale;
}

void IRenderNode::setScale(glm::vec3&& scale)
{
    _scale = std::move(scale);
    _modelMatrix = computeModelMatrix();
}


glm::vec3 IRenderNode::getRotation()
{
    return _rotation;
}

void IRenderNode::setRotation(glm::vec3&& rotation)
{
    _rotation = std::move(rotation);
    _modelMatrix = computeModelMatrix();
}


GLuint IRenderNode::getVAO()
{
    return _VAO;
}

GLenum IRenderNode::getRenderMode()
{
    return _renderMode;
}

GLsizei IRenderNode::getMeshSize()
{
    return (GLsizei)_mesh.size();
}

glm::mat4 IRenderNode::getModelMatrix()
{
    return _modelMatrix;
}


glm::mat4 IRenderNode::computeModelMatrix()
{
    glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 rotate = rotZ * rotX * rotY;

    glm::mat4 translate = glm::translate(glm::mat4(1.0f), _position);
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), _scale);

    return translate * rotate * scale;
}


void IRenderNode::uploadToGPU()
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
