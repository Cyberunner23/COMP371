
#pragma once

#include <memory>
#include <vector>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

#include "../PNGLoader.hpp"
#include "../VAOGuard.hpp"

class IRenderNode
{

public:

    IRenderNode();
    explicit IRenderNode(std::string name);

    virtual void addChildNode(const std::shared_ptr<IRenderNode>& node);
    std::vector<std::shared_ptr<IRenderNode>>* getChildren();

    glm::vec3 getPosition();
    void setPosition(const glm::vec3&& pos);
    void translate(const glm::vec3& translation);

    glm::vec3 getScale();
    void setScale(const glm::vec3&& scale);
    void scale(const glm::vec3& scaling);

    glm::vec3 getRotation();
    void setRotation(const glm::vec3&& rotation);
    void setRotation(const glm::vec3& rotation);
    void rotate(const glm::vec3& rotation);

    std::string getDebugName() {return _debugName;}
    GLuint getVAO();
    bool hasTexture();
    GLuint getTexture();
    GLenum getRenderMode();
    GLsizei getMeshSize();
    glm::mat4 getModelMatrix();
    void setFinalModelMat(const glm::mat4& mat)
    {
        _finalModelMat = mat;
    }

protected:

    std::string _debugName;

    GLenum _renderMode = GL_TRIANGLES;

    GLuint _VAO;
    GLuint _VBO;
    GLuint _CBO;
    GLuint _UVBO; //BO for the UVs
    GLuint _NBO; //BO for the norms
    std::unique_ptr<GLuint> _texture; //Texture for the object

    glm::vec3 _position;
    glm::vec3 _scale;
    glm::vec3 _rotation;
    glm::mat4 _modelMatrix;
    glm::mat4 _finalModelMat;

    std::vector<glm::vec3> _mesh;
    std::vector<glm::vec3> _colors;
    std::vector<glm::vec3> _normals;
    std::vector<glm::vec2> _uvs;

    std::vector<std::shared_ptr<IRenderNode>> _childNodes;

    virtual void uploadToGPU();

private:

    glm::mat4 computeModelMatrix();

};
