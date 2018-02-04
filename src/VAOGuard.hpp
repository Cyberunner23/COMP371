
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
        std::cout << "VAO START" << std::endl;
    }

    inline ~VAOGuard()
    {
        glBindVertexArray(0);
        std::cout << "VAO END" << std::endl;
    }
};
