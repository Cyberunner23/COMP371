
#include <iostream>
#include <vector>

#include "GL/glew.h"
#include "glm/common.hpp"
#include "GLFW/glfw3.h"

#include "Camera.hpp"
#include "objects/AxisLinesObject.hpp"
#include "objects/FloorGridObject.hpp"
#include "objects/HorseObject.hpp"
#include "objects/CubeObject.hpp"
#include "objects/TestTriangleObject.hpp"
#include "objects/TestSquareObject.hpp"


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


void handleKeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods);
void handleMouseInput(GLFWwindow* window, double xpos, double ypos);

Camera camera;
const float  camSpeedFactor   = 0.05;
const float  mouseSensitivity = 1.0;
double mxPos;
double myPos;

int main(int argc, char** argv)
{
    std::cout << "COMP371 Project by Alex Frappier Lachapelle (40019133)" << std::endl;

    std::cout << "INFO: Initializing window..." << std::endl;
    GLFWwindow* window = initWindow();

    std::cout << "INFO: Initializing GLEW..." << std::endl;
    initGLEW();

    initGL(window);


    //Create the camera and projection
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), (float)WindowWidth / WindowHeight, 0.1f, 100.0f);
    camera.camPos.x = 0.55f;
    camera.camPos.y = 0.55f;
    camera.camPos.z = 2.0f;
    //camera.camRot.x = 20.0f;

    //Load the shader
    Shader genericShader("generic");

    AxisLinesObject axisLines(genericShader);
    //TestTriangleObject triangle(genericShader);
    //TestSquareObject square(genericShader);
    //CubeObject cube(genericShader);
    //cube.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
    //cube.setPosition(glm::vec3(0.5f, 0.5f, 0.5f));
    HorseObject horse(genericShader);

    FloorGridObject floor(genericShader);
    floor.setPosition(glm::vec3(0.0f, -0.01f, 0.0f));



    //Render loop
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (!glfwWindowShouldClose(window))
    {
        glm::mat4 vpMatrix = projectionMatrix * camera.computeViewMat();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //triangle.render(vpMatrix);
        //square.render(vpMatrix);
        //cube.render(vpMatrix);
        horse.render(vpMatrix);

        floor.render(vpMatrix);
        axisLines.render(vpMatrix);

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
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
        {

            if (key == GLFW_KEY_W )  {
                camera.camPos.z += camSpeedFactor;
            } else if (key == GLFW_KEY_S) {
                camera.camPos.z -= camSpeedFactor;
            } else if (key == GLFW_KEY_D) {
                camera.camPos.x -= camSpeedFactor;
            } else if (key == GLFW_KEY_A) {
                camera.camPos.x += camSpeedFactor;
            } else if (key == GLFW_KEY_SPACE) {
                camera.camPos.y += camSpeedFactor;
            } else if (key == GLFW_KEY_LEFT_SHIFT) {
                camera.camPos.y -= camSpeedFactor;
            }

            switch (key)
            {
                default:
                    break;
            }
        }
    }

}

void handleMouseInput(GLFWwindow* window, double xpos, double ypos) {

    camera.camRot.x += mouseSensitivity * (ypos - myPos);
    camera.camRot.y += mouseSensitivity * (xpos - mxPos);

    if (camera.camRot.x > 90.0f) {
        camera.camRot.x = 90.0f;
    }
    if (camera.camRot.x < -90.0f) {
        camera.camRot.x = -90.0f;
    }

    mxPos = xpos;
    myPos = ypos;
    //std::cout << mxPos << ":" << myPos << " " << camera.camRot.x << ":" << camera.camRot.y << std::endl;
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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WindowHeight, WindowWidth, WindowName, nullptr, nullptr);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetKeyCallback(window, glfwKeyCallback);
    glfwGetCursorPos(window, &mxPos, &myPos);
    glfwSetCursorPosCallback(window, handleMouseInput);

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
