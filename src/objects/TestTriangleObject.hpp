
#pragma once

#include "IRenderObject.hpp"

class TestTriangleObject : public IRenderObject
{

public:

    TestTriangleObject() = delete;
    explicit TestTriangleObject(Shader &shader);

};
