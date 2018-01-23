
#pragma once

#include "IRenderObject.hpp"

class AxisLinesObject : public IRenderObject
{

public:

    AxisLinesObject() = delete;
    explicit AxisLinesObject(Shader &shader);

};

