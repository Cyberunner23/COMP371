
#pragma once

#include "IRenderObject.hpp"

class AxisLinesObject : public IRenderObject
{

public:

    AxisLinesObject() = delete;
    explicit AxisLinesObject(Shader &shader);

    virtual void render(glm::mat4 pvMatrix);


private:

    std::vector<glm::vec3> _lineColors;

    void uploadToGPU();

};

