
#pragma once

#include "IRenderNode.hpp"

class LightObject : public IRenderNode
{
public:
    LightObject() {_debugName = "LightObject";}

    glm::vec3 getTransformedPosition()
    {
        return glm::vec3(_finalModelMat * glm::vec4(_position, 1.0f));
    }
private:
    virtual void uploadToGPU() {}
};