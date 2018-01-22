
#pragma once;

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct Camera
{

    glm::vec3 camPos;
    glm::vec3 camRot;


    Camera();

    glm::mat4 computeViewMat();
};
