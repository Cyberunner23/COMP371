
#pragma once

#include "IRenderNode.hpp"

class SceneRoot : public IRenderNode
{
public:
    SceneRoot() {_debugName = "SceneRoot";}
private:
    virtual void uploadToGPU() {}
};