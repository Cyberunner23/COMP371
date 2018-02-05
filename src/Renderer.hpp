
#pragma once

#include <memory>
#include <vector>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

#include "Shader.hpp"
#include "ShaderGuard.hpp"
#include "VAOGuard.hpp"
#include "objects/IRenderNode.hpp"

/*
 * Doing hierachical rendering using a recursive method
 * since it is simple and we don't need that much efficiency
 * */

class Renderer
{

public:

    explicit Renderer(std::unique_ptr<Shader>&& shader);

    void setPolygonMode(GLenum polygonMode);
    void addRenderObject(std::shared_ptr<IRenderNode> rootNode);

    void render(glm::mat4 vpMatrix);

private:

    std::unique_ptr<Shader> _shader;
    GLenum _polygonMode;

    std::vector<std::shared_ptr<IRenderNode>> _objects;

    void recursiveRender(glm::mat4 vpMatrix, glm::mat4 CTM, std::shared_ptr<IRenderNode> currentNode);

};
