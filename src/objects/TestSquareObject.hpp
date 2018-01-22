
#pragma once

#include "IRenderObject.hpp"

class TestSquareObject : public IRenderObject
{

public:

    TestSquareObject() = delete;
    explicit TestSquareObject(Shader &shader);

    virtual void render(glm::mat4 pvMatrix);


private:
    std::vector<glm::vec3> _colors;

    void uploadToGPU();

};

