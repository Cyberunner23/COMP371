
#include "Renderer.hpp"

Renderer::Renderer(std::unique_ptr<Shader>&& shader) : _polygonMode(GL_TRIANGLES), _shader(std::move(shader))
{}


inline void Renderer::setPolygonMode(GLenum polygonMode)
{
    _polygonMode = polygonMode;
}


void Renderer::addRenderObject(std::shared_ptr<IRenderNode> rootNode)
{
    _objects.push_back(rootNode);
}


void Renderer::render(glm::mat4 vpMatrix)
{
    for (std::shared_ptr<IRenderNode> root : _objects)
    {
        recursiveRender(vpMatrix, glm::mat4(1.0f), root);
    }
}

void Renderer::recursiveRender(glm::mat4 vpMatrix, glm::mat4 CTM, std::shared_ptr<IRenderNode> currentNode)
{

    if (currentNode == nullptr) return;

    if (!currentNode->getDebugName().empty())
    {
        //std::cout << "Rendering: " << currentNode->getDebugName() << std::endl;
    }

    std::vector<std::shared_ptr<IRenderNode>>* children = currentNode->getChildren();
    glm::mat4 currentModelMat = CTM * currentNode->getModelMatrix();

    //render
    VAOGuard vGuard(currentNode->getVAO());
    ShaderGuard sGuard(_shader);

    glm::mat4 MVP = vpMatrix * currentModelMat;
    if (!_shader->setUniformM4fv("MVP", MVP))
    {
        std::cout << "ERROR: failed to set the MVP" << std::endl;
    }

    glPolygonMode(GL_FRONT_AND_BACK, _polygonMode);
    glDrawArrays(currentNode->getRenderMode(), 0, (GLsizei)currentNode->getMeshSize());


    for (std::shared_ptr<IRenderNode> node : *children)
    {
        recursiveRender(vpMatrix, currentModelMat, node);
    }

    //render
    /*VAOGuard vGuard(currentNode->getVAO());
    ShaderGuard sGuard(_shader);

    std::cout << "VAO2 " << currentNode->getVAO() << std::endl;

    glm::mat4 MVP = vpMatrix * currentModelMat;
    if (!_shader->setUniformM4fv("MVP", MVP))
    {
        std::cout << "ERROR: failed to set the MVP" << std::endl;
    }

    glPolygonMode(GL_FRONT_AND_BACK, _polygonMode);
    glDrawArrays(currentNode->getRenderMode(), 0, (GLsizei)currentNode->getMeshSize());*/
}