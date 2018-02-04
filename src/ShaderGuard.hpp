
#pragma once

#include <memory>

#include "Shader.hpp"

/*
 * A tiny util to bind shaders using RAII
 * */

class ShaderGuard
{

public:

    inline explicit ShaderGuard(std::unique_ptr<Shader> &shader) : _shader(shader)
    {
        _shader->useShader();
    }

    inline ~ShaderGuard()
    {
        _shader->unUseShader();
    }

private:

    std::unique_ptr<Shader>& _shader;
};