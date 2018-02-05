
#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

class IRenderNode
{

public:

    IRenderNode();
    explicit IRenderNode(std::string name);

    void addChildNode(std::shared_ptr<IRenderNode> node);
    std::vector<std::shared_ptr<IRenderNode>>* getChildren();

    glm::vec3 getPosition();
    void setPosition(glm::vec3&& pos);

    glm::vec3 getScale();
    void setScale(glm::vec3&& scale);

    glm::vec3 getRotation();
    void setRotation(glm::vec3&& rotation);

    std::string getDebugName() {return _debugName;}
    GLuint getVAO();
    GLenum getRenderMode();
    GLsizei getMeshSize();
    glm::mat4 getModelMatrix();

protected:

    std::string _debugName;

    GLenum _renderMode = GL_TRIANGLES;

    GLuint _VAO;
    GLuint _VBO;
    GLuint _CBO;

    glm::vec3 _position;
    glm::vec3 _scale;
    glm::vec3 _rotation;
    glm::mat4 _modelMatrix;

    std::vector<glm::vec3> _mesh;
    std::vector<glm::vec3> _colors;

    std::vector<std::shared_ptr<IRenderNode>> _childNodes;

    virtual void uploadToGPU();

private:

    glm::mat4 computeModelMatrix();

};
