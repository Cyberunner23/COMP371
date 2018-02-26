
#pragma once

#include "IRenderNode.hpp"

class AxisLines : public IRenderNode
{
public:
    AxisLines() : AxisLines(5) {}
    AxisLines(float size);
};
