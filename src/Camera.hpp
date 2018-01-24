
#pragma once;

#include <iostream>

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
    
    void setFOV(float fov);
    void onWindowResize(int newWidth, int newHeight);

    glm::mat4 getViewProjectionMatrix();


private:

    glm::vec2 _windowSize;
    float _fov;

    glm::mat4 _vpMatrix;
    glm::vec3 _camPos;
    glm::vec3 _camRot;

    glm::mat4 computeViewProjectionMatrix();

};



/*struct Camera
{

    glm::vec3 camPos;
    glm::vec3 camRot;


    Camera();

    glm::mat4 computeViewMat();
};*/
