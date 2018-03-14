
#include "Shader.hpp"


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

void Shader::unUseShader()
{
    glUseProgram(0);
}

bool Shader::setUniformM4fv(std::string uniformName, glm::mat4 &matrix)
{
    GLint loc = glGetUniformLocation(_programID, uniformName.c_str());
    if (loc < 0)
    {
        return false;
    }

    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));

    return true;
}

bool Shader::setUniform1f(std::string uniformName, float &value)
{
    GLint loc = glGetUniformLocation(_programID, uniformName.c_str());
    if (loc < 0)
    {
        return false;
    }

    glUniform1f(loc, value);

    return true;
}

bool Shader::setUniform3f(std::string uniformName, glm::vec3 &value)
{
    GLint loc = glGetUniformLocation(_programID, uniformName.c_str());
    if (loc < 0)
    {
        return false;
    }

    glUniform3f(loc, value.x, value.y, value.z);

    return true;
}

bool Shader::setTexture(int location, std::string uniformName, GLuint texID)
{

    if (location < 0 || location > 2)
    {
        return false;
    }

    GLint loc = glGetUniformLocation(_programID, uniformName.c_str());
    if (loc < 0)
    {
        return false;
    }

    glUniform1i(loc, location);

    switch(location)
    {
        case 0:
            glActiveTexture(GL_TEXTURE0);
            //std::cout << "GL_TEXTURE0" << std::endl;
            break;
        case 1:
            glActiveTexture(GL_TEXTURE1);
            //std::cout << "GL_TEXTURE1" << std::endl;
            break;
        case 2:
            glActiveTexture(GL_TEXTURE2);
            //std::cout << "GL_TEXTURE2" << std::endl;
            break;
    }

    glBindTexture(GL_TEXTURE_2D, texID);

    return true;
}

bool Shader::unSetTexture(int loc, std::string uniformName)
{
    return setTexture(loc, uniformName, 0);
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
