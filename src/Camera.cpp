
#include "Camera.hpp"

Camera::Camera(int windowWidth, int windowHeight, float fov) 
	: _windowSize(glm::vec2(windowWidth, windowHeight))
	, _fov(fov)
	, _camPos(0.0f, 0.0f, 0.0f)
        , _camRot(0.0f, 0.0f, 0.0f)
{
    _vpMatrix = computeViewProjectionMatrix();
}

void Camera::setPos(glm::vec3 camPos)
{
    _camPos = camPos;
    _vpMatrix = computeViewProjectionMatrix();
}

void Camera::setRot(glm::vec3 camRot)
{
     _camRot = camRot;
    _vpMatrix = computeViewProjectionMatrix();
}

glm::vec3 Camera::getPos()
{
    return _camPos;
}

glm::vec3 Camera::getRot()
{
    return _camRot;
}


void Camera::setFOV(float fov)
{
    _fov = fov;
    _vpMatrix = computeViewProjectionMatrix();
}

void Camera::onWindowResize(int newWidth, int newHeight)
{
    _windowSize = glm::vec2(newWidth, newHeight);
    _vpMatrix = computeViewProjectionMatrix();
}


glm::mat4 Camera::getViewProjectionMatrix()
{
    return _vpMatrix;
}


glm::mat4 Camera::computeViewProjectionMatrix()
{

    glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(_camRot.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(_camRot.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), glm::radians(_camRot.z), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 rotation = rotZ * rotY * rotX;
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), -_camPos);

    glm::mat4 projectionMat = glm::perspective(glm::radians(_fov), _windowSize.x / _windowSize.y, 0.1f, 100.0f);
    glm::mat4 viewMat = rotation * translation;

    return projectionMat * viewMat;
}
