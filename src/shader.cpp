
#include "shader.hpp"


// return
//    GLuint:      Program ID.
//    std::string: Printable error message.
std::string loadShaderProgram(GLuint &programID, std::string shaderName)
{
    GLuint vShaderID;
    GLuint fShaderID;
    std::string shaderErr;

    std::cout << "INFO: Loading shader \"" + shaderName + "\"..." << std::endl;

    programID = glCreateProgram();


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
    glAttachShader(programID, vShaderID);
    glAttachShader(programID, fShaderID);

    shaderErr = linkShaderProgram(programID);
    if (!shaderErr.empty())
    {
        return "Failed to link shader program for shader \"" + shaderName + "\": " + shaderErr;
    }

    return "";
}


std::string linkShaderProgram(GLuint programID)
{
    GLint linkSuccess = GL_TRUE;

    glLinkProgram(programID);
    glGetProgramiv(programID, GL_LINK_STATUS, &linkSuccess);
    if (linkSuccess != GL_TRUE) {

        std::string logMsg;
        GLint       logLength = 0;

        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);
        logMsg.reserve((GLuint)logLength + 1);
        glGetProgramInfoLog(programID, logLength, nullptr, &logMsg[0]);

        return logMsg;
    }

    return "";
}

