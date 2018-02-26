
#include "IRenderNode.hpp"

IRenderNode::IRenderNode()
        : _position(0.0f, 0.0f, 0.0f)
        , _scale(1.0f, 1.0f, 1.0f)
        , _rotation(0.0f, 0.0f, 0.0f)
        , _modelMatrix(computeModelMatrix())
        , _debugName("")
{
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_CBO);
    glGenBuffers(1, &_UVBO);
}

IRenderNode::IRenderNode(std::string name) : IRenderNode()
{
    _debugName = std::move(name);
}


void IRenderNode::addChildNode(const std::shared_ptr<IRenderNode>& node)
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

void IRenderNode::setPosition(const glm::vec3&& pos)
{
    _position = pos;
    _modelMatrix = computeModelMatrix();
}

void IRenderNode::translate(const glm::vec3& translation)
{
    _position += translation;
    _modelMatrix = computeModelMatrix();
}


glm::vec3 IRenderNode::getScale()
{
    return _scale;
}

void IRenderNode::setScale(const glm::vec3&& scale)
{
    _scale = scale;
    _modelMatrix = computeModelMatrix();
}

void IRenderNode::scale(const glm::vec3& scaling)
{
    _scale += scaling;
    _modelMatrix = computeModelMatrix();
}


glm::vec3 IRenderNode::getRotation()
{
    return _rotation;
}

void IRenderNode::setRotation(const glm::vec3&& rotation)
{
    _rotation = rotation;
    _modelMatrix = computeModelMatrix();
}

void IRenderNode::rotate(const glm::vec3& rotation)
{
    _rotation += rotation;
    _modelMatrix = computeModelMatrix();
}


GLuint IRenderNode::getVAO()
{
    return _VAO;
}

bool IRenderNode::hasTexture()
{
    return _texture.get() != nullptr;
}

GLuint IRenderNode::getTexture()
{
    return *_texture;
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

    return  translate * scale * rotate;
}


void IRenderNode::uploadToGPU()
{
    VAOGuard guard(_VAO);

    //Vertices
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*_mesh.size(), &_mesh[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    if (!hasTexture())
    {
        //Line Colors
        glBindBuffer(GL_ARRAY_BUFFER, _CBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*_colors.size(), &_colors[0], GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(1);
    }
    else
    {
        //UVs
        glBindBuffer(GL_ARRAY_BUFFER, _UVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*_uvs.size(), &_uvs[0], GL_STATIC_DRAW);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(1);
    }




}
