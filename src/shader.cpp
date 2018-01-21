
#include "shader.hpp"


Shader::Shader(std::string shaderName)
{
    std::string loadErr = loadShaderProgram(shaderName);
    if (!loadErr.empty())
    {
        std::cout << "ERROR: " << loadErr << std::endl;
        std::exit(-1);
    }
}

Shader::~Shader()
{
    glDeleteProgram(_programID);
}


void Shader::useShader()
{
    glUseProgram(_programID);
}


std::string Shader::loadShaderProgram(std::string &shaderName)
{
    GLuint vShaderID;
    GLuint fShaderID;
    std::string shaderErr;

    std::cout << "INFO: Loading shader \"" + shaderName + "\"..." << std::endl;

    _programID = glCreateProgram();


    //Vertex shader
    std::string vShaderPath = ShaderBasePath + "/" + shaderName + ".vert";
    std::cout << "INFO: Loading vertex shader \"" << vShaderPath << "\"" << std::endl;

    shaderErr = loadShader<GL_VERTEX_SHADER>(vShaderID, vShaderPath);
    if (!shaderErr.empty())
    {
        return "Failed to compile vertex shader for shader \"" + shaderName + "\": " + shaderErr;
    }


    //Fragment shader
    std::string fShaderPath = ShaderBasePath + "/" + shaderName + ".frag";
    std::cout << "INFO: Loading fragment shader \"" << fShaderPath << "\"" << std::endl;

    shaderErr = loadShader<GL_FRAGMENT_SHADER>(fShaderID, fShaderPath);
    if (!shaderErr.empty())
    {
        return "Failed to compile fragment shader for shader \"" + shaderName + "\": " + shaderErr;
    }


    //Link the shader
    glAttachShader(_programID, vShaderID);
    glAttachShader(_programID, fShaderID);

    shaderErr = linkShaderProgram();
    if (!shaderErr.empty())
    {
        return "Failed to link shader program for shader \"" + shaderName + "\": " + shaderErr;
    }

    return "";
}


std::string Shader::linkShaderProgram()
{
    GLint linkSuccess = GL_TRUE;

    glLinkProgram(_programID);
    glGetProgramiv(_programID, GL_LINK_STATUS, &linkSuccess);
    if (linkSuccess != GL_TRUE) {

        std::string logMsg;
        GLint       logLength = 0;

        glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &logLength);
        logMsg.reserve((GLuint)logLength + 1);
        glGetProgramInfoLog(_programID, logLength, nullptr, &logMsg[0]);

        return logMsg;
    }

    return "";
}
