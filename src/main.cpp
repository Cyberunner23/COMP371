
#include <iostream>
#include <vector>

#include "GL/glew.h"
#include "glm/common.hpp"
#include "GLFW/glfw3.h"

#include "Camera.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include "objects/AxisLines.hpp"
#include "objects/Cube.hpp"
#include "objects/Horse.hpp"
#include "objects/SceneRoot.hpp"
#include "objects/FloorGrid.hpp"


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


std::unique_ptr<Window> window;
std::unique_ptr<Camera> camera;
//std::unique_ptr<HorseObject> horse;

GLenum polygonMode = GL_FILL;

const float  camSpeedFactor   = 0.05;
const float  mouseSensitivity = 1.0;
double mxPos;
double myPos;

int main(int argc, char** argv)
{

    window = std::make_unique<Window>(InitWindowWidth, InitWindowHeight, "COMP371 Project by Alex Frappier Lachapelle (40019133)");
    camera = std::make_unique<Camera>(InitWindowWidth, InitWindowHeight, 45.0f);

    window->setWindowSizeCallback(windowSizeCallback);
    window->setKeyCallback(keyCallback);
    //window->setMousePosCallback(mousePosCallback);

    //Create the camera and projection
    camera->setPos(glm::vec3(0.55f, 0.55f, 5.0f));

    //Load the shader
    std::unique_ptr<Shader> genericShader = std::make_unique<Shader>("generic");
    Renderer renderer(std::move(genericShader));

    std::shared_ptr<SceneRoot> sceneRoot = std::make_shared<SceneRoot>();
    std::shared_ptr<AxisLines> axis = std::make_shared<AxisLines>();
    std::shared_ptr<FloorGrid> floorGrid = std::make_shared<FloorGrid>();
    std::shared_ptr<Horse> horse = std::make_shared<Horse>() ;


    floorGrid->setPosition(glm::vec3(0.0f, -0.005f, 0.0f));
    sceneRoot->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    sceneRoot->setRotation(glm::vec3(0.0f, 0.0f, 0.0f));

    sceneRoot->addChildNode(floorGrid);
    sceneRoot->addChildNode(horse);

    //renderer.addRenderObject(square);
    //renderer.addRenderObject(floorGrid);
    //renderer.addRenderObject(axis);
    renderer.addRenderObject(axis);
    renderer.addRenderObject(sceneRoot);



    //Render loop
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (!window->shouldClose())
    {
        window->pollEvents();

        glm::mat4 vpMatrix = camera->getViewProjectionMatrix();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer.render(vpMatrix);

        window->swapBuffers();
        glfwPollEvents();
    }

    return 0;
}


void windowSizeCallback(GLFWwindow *glfwWindow, int width, int height)
{
    window->onWindowResize(width, height);
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
                    polygonMode = GL_POINT;
                    break;
                case GLFW_KEY_L:
                    polygonMode = GL_LINE;
                    break;
                case GLFW_KEY_T:
                    polygonMode = GL_FILL;
                    break;
                case GLFW_KEY_W:
                {
                    //glm::vec3 hPosition = horse->getPosition();
                    //hPosition = glm::vec3(hPosition.x , hPosition.y, hPosition.z - 1.0f);
                    //horse->setPosition(hPosition);
                    break;
                }
                case GLFW_KEY_S:
                {
                    //glm::vec3 hPosition = horse->getPosition();
                    //hPosition = glm::vec3(hPosition.x, hPosition.y, hPosition.z + 1.0f);
                    //horse->setPosition(hPosition);
                    break;
                }
                case GLFW_KEY_D:
                {
                    //glm::vec3 hPosition = horse->getPosition();
                    //hPosition = glm::vec3(hPosition.x + 1.0f, hPosition.y, hPosition.z);
                    //horse->setPosition(hPosition);
                    break;
                }
                case GLFW_KEY_A:
                {
                    //glm::vec3 hPosition = horse->getPosition();
                    //hPosition = glm::vec3(hPosition.x - 1.0f, hPosition.y, hPosition.z);
                    //horse->setPosition(hPosition);
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
                case GLFW_KEY_W:
                {
                    //glm::vec3 hRotation = horse->getRotation();
                    //hRotation = glm::vec3(hRotation.x, hRotation.y, hRotation.z - 5.0f);
                    //horse->setRotation(hRotation);
                    break;
                }
                case GLFW_KEY_S:
                {
                    //glm::vec3 hRotation = horse->getRotation();
                    //hRotation = glm::vec3(hRotation.x, hRotation.y, hRotation.z + 5.0f);
                    //horse->setRotation(hRotation);
                    break;
                }
                case GLFW_KEY_D:
                {
                    //glm::vec3 hRotation = horse->getRotation();
                    //hRotation = glm::vec3(hRotation.x, hRotation.y - 5.0f, hRotation.z);
                    //horse->setRotation(hRotation);
                    break;
                }
                case GLFW_KEY_A:
                {
                    //glm::vec3 hRotation = horse->getRotation();
                    //hRotation = glm::vec3(hRotation.x, hRotation.y + 5.0f, hRotation.z);
                    //horse->setRotation(hRotation);
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
                    //glm::vec3 currentPos = horse->getPosition();
                    //int min = -51;
                    //int max = 49;
                    //int x = min + (rand() % (max - min + 1));
                    //int z = min + (rand() % (max - min + 1));
                    //horse->setPosition(glm::vec3(x, currentPos.y, z));
                    //break;
                }
                case GLFW_KEY_U:
                {
                    //glm::vec3 scale = horse->getScale();
                    //scale += 0.05f;
                    //horse->setScale(scale);
                    break;
                }
                case GLFW_KEY_J:
                {
                    //glm::vec3 scale = horse->getScale();
                    //scale -= 0.05f;
                    //horse->setScale(scale);
                    break;
                }
                default:
                    break;
            }

            camera->setPos(position);
        }
    }
}

void mousePosCallback(GLFWwindow *window, double xpos, double ypos)
{

    glm::vec3 rotation = camera->getRot();

    rotation.y += mouseSensitivity * (xpos - mxPos);
    rotation.x += mouseSensitivity * (ypos - myPos);

    if (rotation.x > 90.0f) {
        rotation.x = 90.0f;
    }
    if (rotation.x < -90.0f) {
        rotation.x = -90.0f;
    }

    camera->setRot(rotation);

    mxPos = xpos;
    myPos = ypos;
    std::cout << mxPos << ":" << myPos << " " << rotation.x << ":" << rotation.y << std::endl;
}
