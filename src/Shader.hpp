
#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"


//
// Constants
//

const std::string ShaderBasePath = "shaders";


class Shader
{

public:

    explicit Shader(std::string shaderName);
    ~Shader();

    void useShader();
    void unUseShader();

    bool setUniformM4fv(std::string uniformName, glm::mat4 &matrix);

private:

    GLuint _programID = 0;

    std::string loadShaderProgram(std::string &shaderName);
    std::string linkShaderProgram();

    template<GLenum shaderType>
    std::string loadShader(GLuint &shaderID, const std::string &filePath)
    {
        static_assert(shaderType == GL_VERTEX_SHADER
                      || shaderType == GL_TESS_CONTROL_SHADER
                      || shaderType == GL_TESS_EVALUATION_SHADER
                      || shaderType == GL_GEOMETRY_SHADER
                      || shaderType == GL_FRAGMENT_SHADER
                      || shaderType == GL_COMPUTE_SHADER,
                      "Shader type must be valid.");

        std::ifstream  file(filePath);
        std::streampos fileSize;

        //Read file
        file.seekg(0, std::ios::end);
        fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        if (fileSize == 0)
        {
            file.close();
            return "Shader file is empty, most definitely is invalid.";
        }

        std::string shaderData;
        const char* shaderDataPtr;
        shaderData.reserve((unsigned long)fileSize);
        shaderData.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
        shaderDataPtr = shaderData.c_str();

        //Compile shader
        GLint shaderCompiled = GL_FALSE;
        shaderID = glCreateShader(shaderType);

        glShaderSource(shaderID, 1, &shaderDataPtr, nullptr);
        glCompileShader(shaderID);

        //Check for errors
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompiled);
        if (shaderCompiled != GL_TRUE)
        {
            GLchar* logMsg;
            std::string logMsgStr;
            GLint logLength = 0;

            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
            logMsg = new GLchar[logLength + 1];
            glGetShaderInfoLog(shaderID, logLength, nullptr, logMsg);

            logMsgStr = std::string(logMsg);
            delete[] logMsg;

            return logMsgStr;
        }

        return "";
    }

};
