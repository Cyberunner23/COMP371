
#include "IRenderAxisNode.hpp"

void IRenderAxisNode::showAxis(bool active)
{
    auto it = std::find(_childNodes.begin(), _childNodes.end(), _axisLines);
    bool isActive = it != _childNodes.end();

    if (isActive == active)
    {
        return;
    }

    if (active)
    {
        _childNodes.push_back(_axisLines);
    }
    else
    {
        _childNodes.erase(it);
        std::vector<std::shared_ptr<IRenderNode>>(_childNodes.begin(), _childNodes.end()).swap(_childNodes);
    }
}
