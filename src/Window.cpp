//
// Created by cyberunner23 on 1/23/18.
//

#include "Window.hpp"

Window::Window(int width, int height, const std::string &windowTitle)
{

    std::cout << "INFO: Initializing window..." << std::endl;

    glfwSetErrorCallback(errorCallback);

    //GLFW Init
    if (!glfwInit())
    {
        std::exit(-1);
    }

    //Hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(width, height, windowTitle.c_str(), nullptr, nullptr);

    glfwMakeContextCurrent(_window);
    glfwSetWindowUserPointer(_window, this);
    glfwSwapInterval(1);

    std::cout << "INFO: Initializing GLEW..." << std::endl;
    initGLEW();

    std::cout << "Setting up OpenGL context..." << std::endl;
    initGL();
}

Window::~Window()
{
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void Window::onWindowResize(int width, int height)
{
    glViewport(0, 0, width, height);
}

bool Window::shouldClose()
{
    return (bool)glfwWindowShouldClose(_window);
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::swapBuffers()
{
    glfwSwapBuffers(_window);
}


void Window::setWindowSizeCallback(GLFWwindowsizefun windowSizeCallback)
{
    glfwSetWindowSizeCallback(_window, windowSizeCallback);
}

void Window::setKeyCallback(GLFWkeyfun keyCallback)
{
    glfwSetKeyCallback(_window, keyCallback);
}

void Window::setMousePosCallback(GLFWcursorposfun mousePosCallback)
{
    glfwSetCursorPosCallback(_window, mousePosCallback);
}

void Window::setMouseBtnCallback(GLFWmousebuttonfun mouseBtnCallback)
{
    glfwSetMouseButtonCallback(_window, mouseBtnCallback);
}


void Window::initGLEW()
{
    glewExperimental = GL_TRUE;
    GLenum glewErr = glewInit();

    if (glewErr != GLEW_OK) {
        std::cout << "ERROR: Failed to initialize GLEW: " << glewGetErrorString(glewErr) << std::endl;
        glfwTerminate();
        std::exit(-1);
    }
}

void Window::initGL()
{
    int height, width;

    glfwGetFramebufferSize(_window, &width, &height);
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}


void Window::errorCallback(int error, const char *description)
{
    std::cout << "ERROR: GLFW encountered error ID: " << error << ", which translates to: " << description << std::endl;
}
