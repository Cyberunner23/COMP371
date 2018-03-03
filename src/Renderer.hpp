
#pragma once

#include <memory>
#include <vector>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

#include "VAOGuard.hpp"
#include "Shader.hpp"
#include "ShaderGuard.hpp"
#include "TextureGuard.hpp"
#include "objects/IRenderNode.hpp"

/*
 * Doing hierachical rendering using a recursive method
 * since it is simple and we don't need that much efficiency
 * */

class Renderer
{

public:

    explicit Renderer(std::unique_ptr<Shader>&& genericShader, std::unique_ptr<Shader>&& textureShader);

    void setPolygonMode(GLenum polygonMode);
    void setTexRatio(float ratio);
    void addRenderObject(std::shared_ptr<IRenderNode> rootNode);

    void render(glm::mat4 vpMatrix);

private:

    float _texRatio;

    std::unique_ptr<Shader> _genericShader;
    std::unique_ptr<Shader> _blendedShader;
    GLenum _polygonMode;

    std::vector<std::shared_ptr<IRenderNode>> _objects;


    //Frame buffer to render the shadow points view
    GLuint _frameBuffer = 0;
    GLuint _depthBuffer = 0;
    //Texture that will contain depth info for shadow mapping
    GLuint _renderTexture = 0;


    void recursiveRender(glm::mat4 vpMatrix, glm::mat4 CTM, std::shared_ptr<IRenderNode> currentNode);

};
