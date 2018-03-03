
#include <iostream>
#include <vector>

#include "GL/glew.h"
#include "glm/common.hpp"
#include "GLFW/glfw3.h"

#include "Camera.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include "objects/AxisLines.hpp"
#include "objects/Horse.hpp"
#include "objects/SceneRoot.hpp"
#include "objects/FloorGrid.hpp"
#include "objects/Cube.hpp"


//------------------------------------------------------------------------------
// Constants
//------------------------------------------------------------------------------

const int InitWindowWidth  = 800;
const int InitWindowHeight = 800;

//------------------------------------------------------------------------------
// Function prototypes
//------------------------------------------------------------------------------

//Callbacks
void windowSizeCallback(GLFWwindow *window, int width, int height);
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mousePosCallback(GLFWwindow *window, double xpos, double ypos);
void mouseBtnCallback(GLFWwindow *window, int key, int action, int mods);


std::unique_ptr<Window> mainWindow;
std::unique_ptr<Renderer> renderer;
std::shared_ptr<SceneRoot> sceneRoot;
std::shared_ptr<Horse> horse;
std::unique_ptr<Camera> camera;


bool isLMouseButtonPressed;
bool isLMousePosRegistered;
glm::vec2 initLMousePos;

bool isRMouseButtonPressed;
bool isRMousePosRegistered;
glm::vec2 initRMousePos;

bool isMMouseButtonPressed;
bool isMMousePosRegistered;
glm::vec2 initMMousePos;

float texRatio = 0.0f;



const float  camSpeedFactor   = 0.05;
const float  mouseSensitivity = 1.0;

int main(int argc, char** argv)
{

    //Create window and camera
    mainWindow = std::make_unique<Window>(InitWindowWidth, InitWindowHeight, "COMP371 Project by Alex Frappier Lachapelle (40019133)");
    camera = std::make_unique<Camera>(InitWindowWidth, InitWindowHeight, 45.0f);

    //Set callbacks
    mainWindow->setWindowSizeCallback(windowSizeCallback);
    mainWindow->setKeyCallback(keyCallback);
    mainWindow->setMouseBtnCallback(mouseBtnCallback);
    mainWindow->setMousePosCallback(mousePosCallback);

    //Create the camera and projection
    camera->setPos(glm::vec3(0.55f, 0.55f, 5.0f));

    //Load the shader and create renderer
    std::unique_ptr<Shader> genericShader = std::make_unique<Shader>("generic");
    std::unique_ptr<Shader> blendedShader = std::make_unique<Shader>("blended");
    renderer = std::make_unique<Renderer>(std::move(genericShader), std::move(blendedShader));

    //Create Scene objects
    sceneRoot = std::make_shared<SceneRoot>();
    std::shared_ptr<AxisLines> axis = std::make_shared<AxisLines>();
    std::shared_ptr<FloorGrid> floorGrid = std::make_shared<FloorGrid>();
    horse = std::make_shared<Horse>();
    horse->setPosition(glm::vec3(0.35f, 0.52f, 0.5f));

    horse->showAxis(false);


    floorGrid->setPosition(glm::vec3(0.0f, -0.005f, 0.0f));

    //Add objects to scene root
    sceneRoot->addChildNode(axis);
    sceneRoot->addChildNode(floorGrid);
    sceneRoot->addChildNode(horse);

    //Add scene root to world
    renderer->addRenderObject(sceneRoot);



    //Render loop
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (!mainWindow->shouldClose())
    {
        mainWindow->pollEvents();

        glm::mat4 vpMatrix = camera->getViewProjectionMatrix();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer->render(vpMatrix);

        mainWindow->swapBuffers();
        glfwPollEvents();
    }

    return 0;
}


void windowSizeCallback(GLFWwindow *glfwWindow, int width, int height)
{
    mainWindow->onWindowResize(width, height);
    camera->onWindowResize(width, height);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{

    if (action == GLFW_PRESS || action == GLFW_REPEAT)
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
                    case GLFW_KEY_D:
                    {
                        static bool showAxis = false;
                        showAxis = !showAxis;
                        horse->showAxis(showAxis);
                    }
                    default:
                        break;
                }
            }
        }
        else if (mods == GLFW_MOD_SHIFT)
        {
            switch (key)
            {
                case GLFW_KEY_P:
                    renderer->setPolygonMode(GL_POINT);
                    break;
                case GLFW_KEY_L:
                    renderer->setPolygonMode(GL_LINE);
                    break;
                case GLFW_KEY_T:
                    renderer->setPolygonMode(GL_FILL);
                    break;
                case GLFW_KEY_W:
                {
                    glm::vec3 hPosition = horse->getPosition();
                    hPosition = glm::vec3(hPosition.x , hPosition.y, hPosition.z - 1.0f);
                    horse->setPosition(std::move(hPosition));
                    break;
                }
                case GLFW_KEY_S:
                {
                    glm::vec3 hPosition = horse->getPosition();
                    hPosition = glm::vec3(hPosition.x, hPosition.y, hPosition.z + 1.0f);
                    horse->setPosition(std::move(hPosition));
                    break;
                }
                case GLFW_KEY_D:
                {
                    glm::vec3 hPosition = horse->getPosition();
                    hPosition = glm::vec3(hPosition.x + 1.0f, hPosition.y, hPosition.z);
                    horse->setPosition(std::move(hPosition));
                    break;
                }
                case GLFW_KEY_A:
                {
                    glm::vec3 hPosition = horse->getPosition();
                    hPosition = glm::vec3(hPosition.x - 1.0f, hPosition.y, hPosition.z);
                    horse->setPosition(std::move(hPosition));
                    break;
                }
                case GLFW_KEY_0:
                {
                    horse->blLegBot->rotate(glm::vec3(0.0f, 0.0f, 5.0f));
                    break;
                }
                case GLFW_KEY_1:
                {
                    horse->head->rotate(glm::vec3(0.0f, 0.0f, 5.0f));
                    break;
                }
                case GLFW_KEY_2:
                {
                    horse->neck->rotate(glm::vec3(0.0f, 0.0f, 5.0f));
                    break;
                }
                case GLFW_KEY_3:
                {
                    horse->frLegTop->rotate(glm::vec3(0.0f, 0.0f, 5.0f));
                    break;
                }
                case GLFW_KEY_4:
                {
                    horse->frLegBot->rotate(glm::vec3(0.0f, 0.0f, 5.0f));
                    break;
                }
                case GLFW_KEY_5:
                {
                    horse->brLegTop->rotate(glm::vec3(0.0f, 0.0f, 5.0f));
                    break;
                }
                case GLFW_KEY_6:
                {
                    horse->brLegBot->rotate(glm::vec3(0.0f, 0.0f, 5.0f));
                    break;
                }
                case GLFW_KEY_7:
                {
                    horse->flLegTop->rotate(glm::vec3(0.0f, 0.0f, 5.0f));
                    break;
                }
                case GLFW_KEY_8:
                {
                    horse->flLegBot->rotate(glm::vec3(0.0f, 0.0f, 5.0f));
                    break;
                }
                case GLFW_KEY_9:
                {
                    horse->blLegTop->rotate(glm::vec3(0.0f, 0.0f, 5.0f));
                    break;
                }
                default:
                    break;
            }
        }
        else
        {

            glm::vec3 position = camera->getPos();

            switch (key)
            {
                case GLFW_KEY_X:
                {
                    if (texRatio == 0.0f)
                    {
                        texRatio = 1.0f;
                    }
                    else
                    {
                        texRatio = 0.0f;
                    }

                    renderer->setTexRatio(texRatio);
                    break;
                }
                case GLFW_KEY_W:
                {
                    glm::vec3 hRotation = horse->getRotation();
                    hRotation = glm::vec3(hRotation.x, hRotation.y, hRotation.z - 5.0f);
                    horse->setRotation(std::move(hRotation));
                    break;
                }
                case GLFW_KEY_S:
                {
                    glm::vec3 hRotation = horse->getRotation();
                    hRotation = glm::vec3(hRotation.x, hRotation.y, hRotation.z + 5.0f);
                    horse->setRotation(std::move(hRotation));
                    break;
                }
                case GLFW_KEY_D:
                {
                    glm::vec3 hRotation = horse->getRotation();
                    hRotation = glm::vec3(hRotation.x, hRotation.y - 5.0f, hRotation.z);
                    horse->setRotation(std::move(hRotation));
                    break;
                }
                case GLFW_KEY_A:
                {
                    glm::vec3 hRotation = horse->getRotation();
                    hRotation = glm::vec3(hRotation.x, hRotation.y + 5.0f, hRotation.z);
                    horse->setRotation(std::move(hRotation));
                    break;
                }
                case GLFW_KEY_Q:
                    position.y += camSpeedFactor;
                    break;
                case GLFW_KEY_E:
                    position.y -= camSpeedFactor;
                    break;
                case GLFW_KEY_SPACE:
                {
                    glm::vec3 currentPos = horse->getPosition();
                    int min = -51;
                    int max = 49;
                    float x = min + (rand() % (max - min + 1)) + .35f;
                    float z = min + (rand() % (max - min + 1)) + 0.52f;
                    horse->setPosition(glm::vec3(x, currentPos.y, z));
                    break;
                }
                case GLFW_KEY_U:
                {
                    glm::vec3 scale = horse->getScale();
                    scale += 0.05f;
                    horse->setScale(std::move(scale));
                    break;
                }
                case GLFW_KEY_J:
                {
                    glm::vec3 scale = horse->getScale();
                    scale -= 0.05f;
                    horse->setScale(std::move(scale));
                    break;
                }
                case GLFW_KEY_RIGHT:
                {
                    glm::vec3 currentRotation = sceneRoot->getRotation();
                    sceneRoot->setRotation(glm::vec3(currentRotation.x, currentRotation.y + 5, currentRotation.z));
                    break;
                }
                case GLFW_KEY_LEFT:
                {
                    glm::vec3 currentRotation = sceneRoot->getRotation();
                    sceneRoot->setRotation(glm::vec3(currentRotation.x, currentRotation.y - 5, currentRotation.z));
                    break;
                }
                case GLFW_KEY_UP:
                {
                    glm::vec3 currentRotation = sceneRoot->getRotation();
                    sceneRoot->setRotation(glm::vec3(currentRotation.x + 5, currentRotation.y, currentRotation.z));
                    break;
                }
                case GLFW_KEY_DOWN:
                {
                    glm::vec3 currentRotation = sceneRoot->getRotation();
                    sceneRoot->setRotation(glm::vec3(currentRotation.x - 5, currentRotation.y, currentRotation.z));
                    break;
                }
                case GLFW_KEY_HOME:
                {
                    sceneRoot->setScale(glm::vec3(1.0f));
                    sceneRoot->setPosition(glm::vec3(0.0f));
                    sceneRoot->setRotation(glm::vec3(0.0f));
                    break;
                }
                case GLFW_KEY_0:
                {
                    horse->blLegBot->rotate(glm::vec3(0.0f, 0.0f, -5.0f));
                    break;
                }
                case GLFW_KEY_1:
                {
                    horse->head->rotate(glm::vec3(0.0f, 0.0f, -5.0f));
                    break;
                }
                case GLFW_KEY_2:
                {
                    horse->neck->rotate(glm::vec3(0.0f, 0.0f, -5.0f));
                    break;
                }
                case GLFW_KEY_3:
                {
                    horse->frLegTop->rotate(glm::vec3(0.0f, 0.0f, -5.0f));
                    break;
                }
                case GLFW_KEY_4:
                {
                    horse->frLegBot->rotate(glm::vec3(0.0f, 0.0f, -5.0f));
                    break;
                }
                case GLFW_KEY_5:
                {
                    horse->brLegTop->rotate(glm::vec3(0.0f, 0.0f, -5.0f));
                    break;
                }
                case GLFW_KEY_6:
                {
                    horse->brLegBot->rotate(glm::vec3(0.0f, 0.0f, -5.0f));
                    break;
                }
                case GLFW_KEY_7:
                {
                    horse->flLegTop->rotate(glm::vec3(0.0f, 0.0f, -5.0f));
                    break;
                }
                case GLFW_KEY_8:
                {
                    horse->flLegBot->rotate(glm::vec3(0.0f, 0.0f, -5.0f));
                    break;
                }
                case GLFW_KEY_9:
                {
                    horse->blLegTop->rotate(glm::vec3(0.0f, 0.0f, -5.0f));
                    break;
                }
                default:
                    break;
            }

            camera->setPos(position);
        }
    }
}

void mouseBtnCallback(GLFWwindow *window, int key, int action, int mods)
{
    if(key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        isLMouseButtonPressed = true;
    }

    if(key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        isLMouseButtonPressed = false;
        isLMousePosRegistered = false;
    }


    if(key == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        isRMouseButtonPressed = true;
    }

    if(key == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        isRMouseButtonPressed = false;
        isRMousePosRegistered = false;
    }


    if(key == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
    {
        isMMouseButtonPressed = true;
    }

    if(key == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
    {
        isMMouseButtonPressed = false;
        isMMousePosRegistered = false;
    }

}

void mousePosCallback(GLFWwindow *window, double xpos, double ypos)
{

    if (!isLMousePosRegistered && isLMouseButtonPressed)
    {
        initLMousePos = glm::vec2((float) xpos, (float) ypos);
        isLMousePosRegistered = true;
        return;
    }

    if (isLMouseButtonPressed)
    {
        float scaleFactor = 0.00001;
        glm::vec3 currentScale = sceneRoot->getScale();

        float newScale = currentScale.y + ((float) (initLMousePos.y - ypos) * scaleFactor);

        if (newScale <= 0.00001f)
        {
            return;
        }

        sceneRoot->setScale(glm::vec3(newScale));
    }


    if (!isRMousePosRegistered && isRMouseButtonPressed)
    {
        initRMousePos = glm::vec2((float) xpos, (float) ypos);
        isRMousePosRegistered = true;
        return;
    }

    if (isRMouseButtonPressed)
    {
        float translateFactor = 0.00001f;
        glm::vec3 currentPosition = sceneRoot->getPosition();
        float newPos = currentPosition.x + ((float) (initRMousePos.x - xpos) * translateFactor);
        sceneRoot->setPosition(glm::vec3(newPos, currentPosition.y, currentPosition.z));
    }


    if (!isMMousePosRegistered && isMMouseButtonPressed)
    {
        initMMousePos = glm::vec2((float) xpos, (float) ypos);
        isMMousePosRegistered = true;
        return;
    }

    if (isMMouseButtonPressed)
    {
        float rotateFactor = 0.01f;
        glm::vec3 currentRotation = sceneRoot->getRotation();
        float newRot = currentRotation.x + ((float) (initMMousePos.y - ypos) * rotateFactor);
        sceneRoot->setRotation(glm::vec3(newRot, currentRotation.y, currentRotation.z));
    }
}
