
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <random>

#include "GL/glew.h"
#include "glm/common.hpp"
#include "GLFW/glfw3.h"

#include "AnimationHandler.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include "objects/AxisLines.hpp"
#include "objects/Horse.hpp"
#include "objects/LightObject.hpp"
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

void initHorses();

std::unique_ptr<Window> mainWindow;
std::unique_ptr<Renderer> renderer;
std::shared_ptr<SceneRoot> sceneRoot;
std::vector<std::shared_ptr<Horse>> horses;
std::shared_ptr<Camera> camera;
std::shared_ptr<LightObject> lightObj;
std::shared_ptr<AnimationHandler> animationHandler;


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
float lightHeight = 20.0f;
Light light;

bool enableShadows = false;
bool doAnim = false;


const float  camSpeedFactor   = 0.05;
const float  mouseSensitivity = 1.0;

int main(int argc, char** argv)
{

    //Create window and camera
    mainWindow = std::make_unique<Window>(InitWindowWidth, InitWindowHeight, "COMP371 Project by Alex Frappier Lachapelle (40019133)");
    camera = std::make_shared<Camera>(InitWindowWidth, InitWindowHeight, 45.0f);

    //Set callbacks
    mainWindow->setWindowSizeCallback(windowSizeCallback);
    mainWindow->setKeyCallback(keyCallback);
    mainWindow->setMouseBtnCallback(mouseBtnCallback);
    mainWindow->setMousePosCallback(mousePosCallback);

    //Create the camera and projection
    camera->setPos(glm::vec3(0.55f, 0.55f, 5.0f));

    //Load the shader and create renderer
    light.lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    light.camPos = camera->getPos();
    light.ambientStrength = 0.2f;
    light.diffuseStrength = 1.0f;
    light.specularStrength = 0.2f;
    light.shinyCoeff = 1000.0f;

    std::unique_ptr<Shader> genericShader = std::make_unique<Shader>("generic");
    std::unique_ptr<Shader> blendedShader = std::make_unique<Shader>("blended_light");
    std::unique_ptr<Shader> shadowShader = std::make_unique<Shader>("shadow");
    renderer = std::make_unique<Renderer>(
            std::move(genericShader),
            std::move(blendedShader),
            std::move(shadowShader),
            camera);

    //Create Scene objects
    sceneRoot = std::make_shared<SceneRoot>();
    std::shared_ptr<AxisLines> axis = std::make_shared<AxisLines>();
    std::shared_ptr<FloorGrid> floorGrid = std::make_shared<FloorGrid>();

    initHorses();

    //horses[0] = std::make_shared<Horse>();
    //horses[0]->setPosition(glm::vec3(0.35f, 0.52f, 0.5f));

    lightObj = std::make_shared<LightObject>();
    lightObj->setPosition(glm::vec3(0.35, lightHeight, 0.5f));
    light.lightPos = lightObj->getTransformedPosition();

    //horses[0]->showAxis(false);


    floorGrid->setPosition(glm::vec3(0.0f, -0.005f, 0.0f));

    //Add objects to scene root
    sceneRoot->addChildNode(axis);
    sceneRoot->addChildNode(floorGrid);
//    sceneRoot->addChildNode(horses[0]);

    for (std::shared_ptr<Horse> horse : horses)
    {
        sceneRoot->addChildNode(horse);
        std::cout << "Added a horse" << std::endl;
    }

    sceneRoot->addChildNode(lightObj);

    //Add scene root to world
    renderer->addRenderObject(sceneRoot);

    double prevTime = glfwGetTime();
    double delta = 0.0;
    double FPS = 30.0;
    double FPSIntervalDuration = 1.0 / FPS;
    double sleepFor = 0.0;

    animationHandler = std::make_shared<AnimationHandler>(horses);

    animationHandler->setAnimationType(AnimationType::RUN);

    //Render loop
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (!mainWindow->shouldClose())
    {
        delta = glm::abs(prevTime - glfwGetTime());
        prevTime = glfwGetTime();


        animationHandler->tick((float)delta);

        sleepFor = FPSIntervalDuration - delta;
        if (sleepFor < 0)
        {
            sleepFor = 0;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds((long)(sleepFor * 1000)));

        mainWindow->pollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        light.lightPos = lightObj->getTransformedPosition();
        renderer->mutateLight() = light;
        renderer->render();

        mainWindow->swapBuffers();
        glfwPollEvents();
    }

    return 0;
}

void initHorses()
{

    std::default_random_engine generator;
    std::uniform_int_distribution<int> posDistrib(-10, 10);
    std::uniform_int_distribution<int> rotDistrib(0   ,360);

    for (unsigned int i = 0; i < 20; ++i)
    {
        float x = posDistrib(generator);
        float z = posDistrib(generator);
        float r = rotDistrib(generator);

        std::cout << "x: " << x << " z: " << z << " r: " << r << std::endl;

        std::shared_ptr<Horse> horse = std::make_shared<Horse>();
        horse->setPosition(glm::vec3(x, 0.52f, z));
        horse->setRotation(glm::vec3(0.0f, r, 0.0f));

        horses.push_back(horse);
        std::cout << "Pushed back horse" << std::endl;
    }

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
                    {
                        glfwSetWindowShouldClose(window, GLFW_TRUE);
                        break;
                    }
                    case GLFW_KEY_D:
                    {
                        static bool showAxis = false;
                        showAxis = !showAxis;
                        horses[0]->showAxis(showAxis);
                    }
                    case GLFW_KEY_I:
                    {
                        animationHandler->setAnimationType(AnimationType::IDLE);
                        break;
                    }
                    case GLFW_KEY_W:
                    {
                        animationHandler->setAnimationType(AnimationType::WALK);
                        break;
                    }
                    case GLFW_KEY_R:
                    {
                        animationHandler->setAnimationType(AnimationType::RUN);
                        break;
                    }
                    case GLFW_KEY_T:
                    {
                        animationHandler->setAnimationType(AnimationType::TURN);
                        break;
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
                    glm::vec3 hPosition = horses[0]->getPosition();
                    hPosition = glm::vec3(hPosition.x , hPosition.y, hPosition.z - 1.0f);
                    lightObj->setPosition(glm::vec3(hPosition.x, lightHeight, hPosition.z));
                    light.lightPos = lightObj->getTransformedPosition();
                    horses[0]->setPosition(std::move(hPosition));
                    break;
                }
                case GLFW_KEY_S:
                {
                    glm::vec3 hPosition = horses[0]->getPosition();
                    hPosition = glm::vec3(hPosition.x, hPosition.y, hPosition.z + 1.0f);
                    lightObj->setPosition(glm::vec3(hPosition.x, lightHeight, hPosition.z));
                    light.lightPos = lightObj->getTransformedPosition();
                    horses[0]->setPosition(std::move(hPosition));
                    break;
                }
                case GLFW_KEY_D:
                {
                    glm::vec3 hPosition = horses[0]->getPosition();
                    hPosition = glm::vec3(hPosition.x + 1.0f, hPosition.y, hPosition.z);
                    lightObj->setPosition(glm::vec3(hPosition.x, lightHeight, hPosition.z));
                    light.lightPos = lightObj->getTransformedPosition();
                    horses[0]->setPosition(std::move(hPosition));
                    break;
                }
                case GLFW_KEY_A:
                {
                    glm::vec3 hPosition = horses[0]->getPosition();
                    hPosition = glm::vec3(hPosition.x - 1.0f, hPosition.y, hPosition.z);
                    lightObj->setPosition(glm::vec3(hPosition.x, lightHeight, hPosition.z));
                    light.lightPos = lightObj->getTransformedPosition();
                    horses[0]->setPosition(std::move(hPosition));
                    break;
                }
                case GLFW_KEY_0:
                {
                    horses[0]->blLegBot->rotate(glm::vec3(0.0f, 0.0f, 5.0f));
                    glm::vec3 rot = horses[0]->blLegBot->getRotation();
                    std::cout << "blLegBot " << rot.x << " " << rot.y << " " << rot.z << std::endl;
                    break;
                }
                case GLFW_KEY_1:
                {
                    horses[0]->head->rotate(glm::vec3(0.0f, 0.0f, 5.0f));
                    glm::vec3 rot = horses[0]->head->getRotation();
                    std::cout << "head" << rot.x << " " << rot.y << " " << rot.z << std::endl;
                    break;
                }
                case GLFW_KEY_2:
                {
                    horses[0]->neck->rotate(glm::vec3(0.0f, 0.0f, 5.0f));
                    glm::vec3 rot = horses[0]->neck->getRotation();
                    std::cout<< "neck" << rot.x << " " << rot.y << " " << rot.z << std::endl;
                    break;
                }
                case GLFW_KEY_3:
                {
                    horses[0]->frLegTop->rotate(glm::vec3(0.0f, 0.0f, 5.0f));
                    glm::vec3 rot = horses[0]->frLegTop->getRotation();
                    std::cout << "frLegTop " << rot.x << " " << rot.y << " " << rot.z << std::endl;
                    break;
                }
                case GLFW_KEY_4:
                {
                    horses[0]->frLegBot->rotate(glm::vec3(0.0f, 0.0f, 5.0f));
                    glm::vec3 rot = horses[0]->frLegBot->getRotation();
                    std::cout << "frLegBot " << rot.x << " " << rot.y << " " << rot.z << std::endl;
                    break;
                }
                case GLFW_KEY_5:
                {
                    horses[0]->brLegTop->rotate(glm::vec3(0.0f, 0.0f, 5.0f));
                    glm::vec3 rot = horses[0]->brLegTop->getRotation();
                    std::cout << "brLegTop " << rot.x << " " << rot.y << " " << rot.z << std::endl;
                    break;
                }
                case GLFW_KEY_6:
                {
                    horses[0]->brLegBot->rotate(glm::vec3(0.0f, 0.0f, 5.0f));
                    glm::vec3 rot = horses[0]->brLegBot->getRotation();
                    std::cout << "brLegBot " << rot.x << " " << rot.y << " " << rot.z << std::endl;
                    break;
                }
                case GLFW_KEY_7:
                {
                    horses[0]->flLegTop->rotate(glm::vec3(0.0f, 0.0f, 5.0f));
                    glm::vec3 rot = horses[0]->flLegTop->getRotation();
                    std::cout << "flLegTop " << rot.x << " " << rot.y << " " << rot.z << std::endl;
                    break;
                }
                case GLFW_KEY_8:
                {
                    horses[0]->flLegBot->rotate(glm::vec3(0.0f, 0.0f, 5.0f));
                    glm::vec3 rot = horses[0]->flLegBot->getRotation();
                    std::cout << "flLegBot " << rot.x << " " << rot.y << " " << rot.z << std::endl;
                    break;
                }
                case GLFW_KEY_9:
                {
                    horses[0]->blLegTop->rotate(glm::vec3(0.0f, 0.0f, 5.0f));
                    glm::vec3 rot = horses[0]->blLegTop->getRotation();
                    std::cout << "blLegTop " << rot.x << " " << rot.y << " " << rot.z << std::endl;
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
                case GLFW_KEY_R:
                    doAnim = !doAnim;
                    horses[0]->doAnim(doAnim);
                    break;
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
                case GLFW_KEY_B:

                    break;
                case GLFW_KEY_W:
                {
                    glm::vec3 hRotation = horses[0]->getRotation();
                    hRotation = glm::vec3(hRotation.x, hRotation.y, hRotation.z - 5.0f);
                    horses[0]->setRotation(std::move(hRotation));
                    break;
                }
                case GLFW_KEY_S:
                {
                    glm::vec3 hRotation = horses[0]->getRotation();
                    hRotation = glm::vec3(hRotation.x, hRotation.y, hRotation.z + 5.0f);
                    horses[0]->setRotation(std::move(hRotation));
                    break;
                }
                case GLFW_KEY_D:
                {
                    glm::vec3 hRotation = horses[0]->getRotation();
                    hRotation = glm::vec3(hRotation.x, hRotation.y - 5.0f, hRotation.z);
                    horses[0]->setRotation(std::move(hRotation));
                    break;
                }
                case GLFW_KEY_A:
                {
                    glm::vec3 hRotation = horses[0]->getRotation();
                    hRotation = glm::vec3(hRotation.x, hRotation.y + 5.0f, hRotation.z);
                    horses[0]->setRotation(std::move(hRotation));
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
                    glm::vec3 currentPos = horses[0]->getPosition();
                    int min = -51;
                    int max = 49;
                    float x = min + (rand() % (max - min + 1)) + .35f;
                    float z = min + (rand() % (max - min + 1)) + 0.52f;
                    horses[0]->setPosition(glm::vec3(x, currentPos.y, z));
                    break;
                }
                case GLFW_KEY_U:
                {
                    glm::vec3 scale = horses[0]->getScale();
                    scale += 0.05f;
                    horses[0]->setScale(std::move(scale));
                    break;
                }
                case GLFW_KEY_J:
                {
                    glm::vec3 scale = horses[0]->getScale();
                    scale -= 0.05f;
                    horses[0]->setScale(std::move(scale));
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
                    horses[0]->blLegBot->rotate(glm::vec3(0.0f, 0.0f, -5.0f));
                    glm::vec3 rot = horses[0]->blLegBot->getRotation();
                    std::cout << "blLegBot " << rot.x << " " << rot.y << " " << rot.z << std::endl;
                    break;
                }
                case GLFW_KEY_1:
                {
                    horses[0]->head->rotate(glm::vec3(0.0f, 0.0f, -5.0f));
                    glm::vec3 rot = horses[0]->head->getRotation();
                    std::cout << "head " << rot.x << " " << rot.y << " " << rot.z << std::endl;
                    break;
                }
                case GLFW_KEY_2:
                {
                    horses[0]->neck->rotate(glm::vec3(0.0f, 0.0f, -5.0f));
                    glm::vec3 rot = horses[0]->neck->getRotation();
                    std::cout << "neck " << rot.x << " " << rot.y << " " << rot.z << std::endl;
                    break;
                }
                case GLFW_KEY_3:
                {
                    horses[0]->frLegTop->rotate(glm::vec3(0.0f, 0.0f, -5.0f));
                    glm::vec3 rot = horses[0]->frLegTop->getRotation();
                    std::cout << "frLegTop " << rot.x << " " << rot.y << " " << rot.z << std::endl;
                    break;
                }
                case GLFW_KEY_4:
                {
                    horses[0]->frLegBot->rotate(glm::vec3(0.0f, 0.0f, -5.0f));
                    glm::vec3 rot = horses[0]->frLegBot->getRotation();
                    std::cout << "frLegBot " << rot.x << " " << rot.y << " " << rot.z << std::endl;
                    break;
                }
                case GLFW_KEY_5:
                {
                    horses[0]->brLegTop->rotate(glm::vec3(0.0f, 0.0f, -5.0f));
                    glm::vec3 rot = horses[0]->brLegTop->getRotation();
                    std::cout << "brLegTop " << rot.x << " " << rot.y << " " << rot.z << std::endl;
                    break;
                }
                case GLFW_KEY_6:
                {
                    horses[0]->brLegBot->rotate(glm::vec3(0.0f, 0.0f, -5.0f));
                    glm::vec3 rot = horses[0]->brLegBot->getRotation();
                    std::cout << "brLegBot " << rot.x << " " << rot.y << " " << rot.z << std::endl;
                    break;
                }
                case GLFW_KEY_7:
                {
                    horses[0]->flLegTop->rotate(glm::vec3(0.0f, 0.0f, -5.0f));
                    glm::vec3 rot = horses[0]->flLegTop->getRotation();
                    std::cout << "flLegTop " << rot.x << " " << rot.y << " " << rot.z << std::endl;
                    break;
                }
                case GLFW_KEY_8:
                {
                    horses[0]->flLegBot->rotate(glm::vec3(0.0f, 0.0f, -5.0f));
                    glm::vec3 rot = horses[0]->flLegBot->getRotation();
                    std::cout << "flLegBot " << rot.x << " " << rot.y << " " << rot.z << std::endl;
                    break;
                }
                case GLFW_KEY_9:
                {
                    horses[0]->blLegTop->rotate(glm::vec3(0.0f, 0.0f, -5.0f));
                    glm::vec3 rot = horses[0]->blLegTop->getRotation();
                    std::cout << "blLegTop " << rot.x << " " << rot.y << " " << rot.z << std::endl;
                    break;
                }
                default:
                    break;
            }

            camera->setPos(position);
            light.camPos = camera->getPos();
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
