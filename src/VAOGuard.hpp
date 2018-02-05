
/*
 * A tiny utility to bind VAOs using RAII
 * */

#pragma once

#include "GL/glew.h"

class VAOGuard
{

public:

    explicit inline VAOGuard(GLuint vao)
    {
        glBindVertexArray(vao);
    }

    inline ~VAOGuard()
    {
        glBindVertexArray(0);
    }
};
