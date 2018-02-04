
#pragma once

#include "IRenderNode.hpp"

class SceneRoot : public IRenderNode
{

public:

    SceneRoot() = default;

private:

    virtual void uploadToGPU() {}

};