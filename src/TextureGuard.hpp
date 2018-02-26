
/*
 * A tiny utility to bind textures using RAII
 * */

#pragma once

#include "GL/glew.h"

class TextureGuard
{

public:

    explicit inline TextureGuard(GLuint texture)
    {
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    inline ~TextureGuard()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
};
