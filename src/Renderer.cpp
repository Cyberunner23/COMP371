
#include "Renderer.hpp"

Renderer::Renderer(std::unique_ptr<Shader>&& genericShader, std::unique_ptr<Shader>&& blendedShader)
        : _polygonMode(GL_TRIANGLES)
        , _genericShader(std::move(genericShader))
        , _blendedShader(std::move(blendedShader))
        , _texRatio(0.0f)
{
    glGenFramebuffers(1, &_frameBuffer);
    glGenRenderbuffers(1, &_depthBuffer);
    glGenTextures(1, &_renderTexture);

    glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);

    //Setup texture
    glBindTexture(GL_TEXTURE_2D, _renderTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2000, 2000, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    //Setup depth buffer
    glBindRenderbuffer(GL_RENDERBUFFER, _depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 2000, 2000);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    //Config framebuffer
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthBuffer);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, _renderTexture, 0);

    GLenum buffers[] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, buffers);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "WARN: Failed to create framebuffer" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void Renderer::setPolygonMode(GLenum polygonMode)
{
    _polygonMode = polygonMode;
}

void Renderer::setTexRatio(float ratio)
{
    _texRatio = ratio;
}

void Renderer::addRenderObject(std::shared_ptr<IRenderNode> rootNode)
{
    _objects.push_back(rootNode);
}


void Renderer::render(glm::mat4 vpMatrix)
{
    //Render all objects in world
    for (std::shared_ptr<IRenderNode> root : _objects)
    {
        recursiveRender(vpMatrix, glm::mat4(1.0f), root);
    }
}

void Renderer::recursiveRender(glm::mat4 vpMatrix, glm::mat4 CTM, std::shared_ptr<IRenderNode> currentNode)
{

    if (currentNode == nullptr) return;

    //Compute new transformation
    glm::mat4 currentModelMat = CTM * currentNode->getModelMatrix();
    std::vector<std::shared_ptr<IRenderNode>>* children = currentNode->getChildren();

    //std::cout << "HIT" << std::endl;

    //render
    VAOGuard vGuard(currentNode->getVAO());
    std::unique_ptr<ShaderGuard> sGuard;
    std::unique_ptr<TextureGuard> tGuard;
    if (!currentNode->hasTexture())
    {
        sGuard = std::make_unique<ShaderGuard>(_genericShader);
    }
    else
    {
        sGuard = std::make_unique<ShaderGuard>(_blendedShader);
        tGuard = std::make_unique<TextureGuard>(currentNode->getTexture());
        if (!_blendedShader->setUniform1f("colorTexRatio", _texRatio))
        {
            std::cout << "ERROR: failed to set the colorTexRatio" << std::endl;
        }
    }


    glm::mat4 MVP = vpMatrix * currentModelMat;
    if (!_genericShader->setUniformM4fv("MVP", MVP))
    {
        std::cout << "ERROR: failed to set the MVP" << std::endl;
    }

    glPolygonMode(GL_FRONT_AND_BACK, _polygonMode);
    glDrawArrays(currentNode->getRenderMode(), 0, (GLsizei)currentNode->getMeshSize());


    //Recurse down the tree, render the child objects
    for (std::shared_ptr<IRenderNode> const &node : *children)
    {
        recursiveRender(vpMatrix, currentModelMat, node);
    }
}