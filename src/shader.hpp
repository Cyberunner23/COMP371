
#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "GL/glew.h"


//
// Constants
//

const std::string ShaderBasePath = "shaders";


std::string loadShaderProgram(GLuint &programID, std::string shaderName);

std::string linkShaderProgram(GLuint programID);


template<GLenum shaderType>
std::string loadShader(GLuint &shaderID, std::string filePath)
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
        std::cout << "log length " << logLength << std::endl;
        logMsg = new GLchar[logLength + 1];
        glGetShaderInfoLog(shaderID, logLength, nullptr, logMsg);

        logMsgStr = std::string(logMsg);
        delete[] logMsg;

        return logMsgStr;
    }

    return "";
}




