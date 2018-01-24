
#pragma once

#include <iostream>
#include <memory>
#include <string>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Window
{

public:

    explicit Window(int width, int height, const std::string &windowTitle);
    ~Window();

    void onWindowResize(int width, int height);
    bool shouldClose();
    void pollEvents();
    void swapBuffers();

    void setWindowSizeCallback(GLFWwindowsizefun windowSizeCallback);
    void setKeyCallback(GLFWkeyfun keyCallback);
    void setMousePosCallback(GLFWcursorposfun mousePosCallback);

private:

    GLFWwindow* _window;

    void initGLEW();
    void initGL();

    static void errorCallback(int error, const char *description);

};
