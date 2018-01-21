
#include <iostream>
#include <vector>

#include "GL/glew.h"
#include "glm/common.hpp"
#include "GLFW/glfw3.h"

#include "shader.hpp"


//------------------------------------------------------------------------------
// Constants
//------------------------------------------------------------------------------

const int   WindowWidth  = 800;
const int   WindowHeight = 800;
const char* WindowName   = "COMP371 - Alex Frappier Lachapelle (40019133)";


//------------------------------------------------------------------------------
// Function prototypes
//------------------------------------------------------------------------------

//Callbacks
void glfwErrorCallback(int error, const char* description);
void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

//Utils
GLFWwindow* initWindow();
void        initGLEW();
void        initGL(GLFWwindow* window);


int main(int argc, char** argv)
{
    std::cout << "COMP371 Project by Alex Frappier Lachapelle (40019133)" << std::endl;

    std::cout << "INFO: Initializing window..." << std::endl;
    GLFWwindow* window = initWindow();

    std::cout << "INFO: Initializing GLEW..." << std::endl;
    initGLEW();

    initGL(window);


    //Load the shader
    Shader genericShader("generic");


    //Setup VAO
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //Setup VBO
    GLuint VBO;
    std::vector<glm::vec3> vertices = { glm::vec3(-1,0,0), glm::vec3(0,1,0), glm::vec3(1,0,0) };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    genericShader.useShader();

    //Render loop
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices.size());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //DeInit
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}


void glfwErrorCallback(int error, const char* description)
{
    std::cout << "ERROR: GLFW encountered error ID: " << error << ", which translates to: " << description << std::endl;
}

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    if (mods == GLFW_MOD_CONTROL)
    {
        if (action == GLFW_PRESS)
        {
            switch (key)
            {
                case GLFW_KEY_Q:
                    glfwSetWindowShouldClose(window, GLFW_TRUE);
                    break;
                default:
                    break;
            }
        }
    }
    else
    {
        if (action == GLFW_PRESS)
        {
            switch (key)
            {
                default:
                    break;
            }
        }
    }

}

GLFWwindow* initWindow()
{
    //Set error callback
    glfwSetErrorCallback(glfwErrorCallback);

    //GLFW Init
    if (!glfwInit())
    {
        std::exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WindowHeight, WindowWidth, WindowName, nullptr, nullptr);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetKeyCallback(window, glfwKeyCallback);

    return window;
}

void initGLEW()
{
    glewExperimental = GL_TRUE;
    GLenum glewErr = glewInit();

    if (glewErr != GLEW_OK) {
        std::cout << "ERROR: Failed to initialize GLEW: " << glewGetErrorString(glewErr) << std::endl;
        glfwTerminate();
        std::exit(-1);
    }
}

void initGL(GLFWwindow* window)
{
    int height, width;

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}
