
#pragma once

#include <algorithm>

#include "AxisLines.hpp"

class IRenderAxisNode : public IRenderNode
{
public:

    IRenderAxisNode() : IRenderNode() {}
    IRenderAxisNode(std::string name)
            : IRenderNode(name)
            , _axisLines(std::make_shared<AxisLines>(0.3f))
    {}

    void showAxis(bool active);

private:

    std::shared_ptr<AxisLines> _axisLines;
};
