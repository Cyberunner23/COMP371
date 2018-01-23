
#pragma once

#include <vector>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

#include "../Shader.hpp"

class IRenderObject
{

public:

    explicit IRenderObject(Shader &shader);


    virtual void render(glm::mat4 vpMatrix);

    glm::vec3 getPosition();
    void setPosition(glm::vec3 pos);

    glm::vec3 getScale();
    void setScale(glm::vec3 scale);

    glm::vec3 getRotation();
    void setRotation(glm::vec3 rotation);

    glm::mat4 getModelMatrix();


protected:

    GLenum _renderMode = GL_TRIANGLES;
    bool _renderMesh = false;

    GLuint _VAO;
    GLuint _VBO;
    GLuint _CBO;

    glm::vec3 _position;
    glm::vec3 _scale;
    glm::vec3 _rotation;
    glm::mat4 _modelMatrix;

    Shader _shader;

    std::vector<glm::vec3> _mesh;
    std::vector<glm::vec3> _colors;

protected:

    virtual void uploadToGPU();

private:

    glm::mat4 computeModelMatrix();

};
