
#pragma once

#include "IRenderObject.hpp"

class TestSquareObject : public IRenderObject
{

public:

    TestSquareObject() = delete;
    explicit TestSquareObject(Shader &shader);

};

