
#pragma once

#include <memory>
#include <vector>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

#include "Camera.hpp"
#include "Light.hpp"
#include "VAOGuard.hpp"
#include "Shader.hpp"
#include "ShaderGuard.hpp"
#include "TextureGuard.hpp"
#include "objects/IRenderNode.hpp"

/*
 * Doing hierachical rendering using a recursive method
 * since it is simple and we don't need that much efficiency
 * */

static const unsigned int SHADOW_WIDTH = 2000;
static const unsigned int SHADOW_HEIGHT = 2000;

class Renderer
{

public:

    Renderer(std::unique_ptr<Shader>&& genericShader,
             std::unique_ptr<Shader>&& textureShader,
             std::unique_ptr<Shader>&& shadowShader,
             std::shared_ptr<Camera> mainCamera);

    void setPolygonMode(GLenum polygonMode);
    void setTexRatio(float ratio);
    Light& mutateLight();
    void addRenderObject(std::shared_ptr<IRenderNode> rootNode);

    void render();

private:

    float _texRatio;
    Light _light;

    std::shared_ptr<Camera> _mainCamera;
    std::shared_ptr<Camera> _shadowCamera;

    std::unique_ptr<Shader> _genericShader;
    std::unique_ptr<Shader> _blendedShader;
    std::unique_ptr<Shader> _shadowShader;
    GLenum _polygonMode;

    std::vector<std::shared_ptr<IRenderNode>> _objects;

    //Frame buffer to render the shadow points view
    GLuint _depthMapFBO = 0;
    //Texture that will contain depth info for shadow mapping
    GLuint _depthMap = 0;


    void recursiveShadowRender(glm::mat4 vpMatrix, glm::mat4 CTM, std::shared_ptr<IRenderNode> currentNode);
    void recursiveRender(glm::mat4 vpMatrix, glm::mat4 CTM, std::shared_ptr<IRenderNode> currentNode);

    void setLightStruct(Shader& shader);
};
