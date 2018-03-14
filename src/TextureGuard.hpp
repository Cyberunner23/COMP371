
/*
 * A tiny utility to bind textures using RAII
 * */

#pragma once

#include "GL/glew.h"

class TextureGuard
{

public:

    TextureGuard() = delete;
    inline TextureGuard(Shader* shader, int loc, std::string name, GLuint texID)
    {
        if (!shader->setTexture(loc, name, texID))
        {
            std::cout << "Failed to set \"" << name <<"\" at location " << loc << std::endl;
        }
    }
};
