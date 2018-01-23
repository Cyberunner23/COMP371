
#include "Camera.hpp"

Camera::Camera() : camPos(0.0f, 0.0f, 0.0f),
                   camRot(0.0f, 0.0f, 0.0f)
{}

glm::mat4 Camera::computeViewMat()
{
    glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(camRot.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(camRot.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), glm::radians(camRot.z), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 rotate = rotZ * rotY * rotX;

    glm::mat4 translate = glm::mat4(1.0f);
    translate = glm::translate(translate, -camPos);

    return rotate * translate;
}