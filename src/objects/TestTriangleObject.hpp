
#pragma once

#include "IRenderObject.hpp"

class TestTriangleObject : public IRenderObject
{

public:

    TestTriangleObject() = delete;
    explicit TestTriangleObject(Shader &shader);

    virtual void render(glm::mat4 vpMatrix);

private:

    std::vector<glm::vec3> _colors;

    void uploadToGPU();

};
