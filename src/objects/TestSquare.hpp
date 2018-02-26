
#pragma once

#include "IRenderNode.hpp"
#include "../PNGLoader.hpp"

class TestSquare : public IRenderNode
{
public:
    explicit TestSquare(float scale = 1);
};

