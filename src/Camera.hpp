
#pragma once

#include <iostream>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{

public:
    
    Camera(int windowWidth, int windowHeight, float fov);

    void setPos(glm::vec3 camPos);
    void setRot(glm::vec3 camRot);

    glm::vec3 getPos();
    glm::vec3 getRot();

    void onWindowResize(int newWidth, int newHeight);
    void forceGLViewportResize();

    glm::mat4 getViewProjectionMatrix();


private:

    glm::vec2 _windowSize;
    float _fov;

    glm::mat4 _vpMatrix;
    glm::vec3 _camPos;
    glm::vec3 _camRot;

    glm::mat4 computeViewProjectionMatrix();

};
