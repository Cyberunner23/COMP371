
#pragma once

#include "glm/glm.hpp"

struct Light
{
    glm::vec3 camPos;
    glm::vec3 lightPos;
    glm::vec3 lightColor;
    float ambientStrength;
    float diffuseStrength;
    float specularStrength;
    float shinyCoeff;
};
